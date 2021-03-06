{
    if (pimple.nCorrPIMPLE() == 1)
    {
        p =
        (
            rho
          - (1.0 - gamma)*rhol0
          - ((gamma*psiv + (1.0 - gamma)*psil) - psi)*pSat
        )/psi;
    }

    surfaceScalarField rhof(fvc::interpolate(rho, "rhof"));

    volScalarField rAU(1.0/UEqn.A());
    surfaceScalarField rAUf("rAUf", rhof*fvc::interpolate(rAU));
    volVectorField HbyA(rAU*UEqn.H());

    phiv = (fvc::interpolate(HbyA) & mesh.Sf())
         + fvc::ddtPhiCorr(rAU, rho, U, phiv);

    p.boundaryField().updateCoeffs();

    surfaceScalarField phiGradp(rAUf*mesh.magSf()*fvc::snGrad(p));

    phiv -= phiGradp/rhof;

    #include "resetPhivPatches.H"

    while (pimple.correctNonOrthogonal())
    {
        fvScalarMatrix pEqn
        (
            fvm::ddt(psi, p)
          - (rhol0 + (psil - psiv)*pSat)*fvc::ddt(gamma) - pSat*fvc::ddt(psi)
          + fvc::div(phiv, rho)
          + fvc::div(phiGradp)
          - fvm::laplacian(rAUf, p)
        );

        pEqn.solve(mesh.solver(p.select(pimple.finalInnerIter())));

        if (pimple.finalNonOrthogonalIter())
        {
            phiv += (phiGradp + pEqn.flux())/rhof;
        }
    }

    Info<< "Predicted p max-min : " << max(p).value()
        << " " << min(p).value() << endl;

    rho == max
    (
        psi*p
      + (1.0 - gamma)*rhol0
      + ((gamma*psiv + (1.0 - gamma)*psil) - psi)*pSat,
        rhoMin
    );

    #include "gammaPsi.H"

    p =
    (
        rho
      - (1.0 - gamma)*rhol0
      - ((gamma*psiv + (1.0 - gamma)*psil) - psi)*pSat
    )/psi;

    p.correctBoundaryConditions();

    Info<< "Phase-change corrected p max-min : " << max(p).value()
        << " " << min(p).value() << endl;

    // Correct velocity

    U = HbyA - rAU*fvc::grad(p);

    // Remove the swirl component of velocity for "wedge" cases
    if (pimple.dict().found("removeSwirl"))
    {
        label swirlCmpt(readLabel(pimple.dict().lookup("removeSwirl")));

        Info<< "Removing swirl component-" << swirlCmpt << " of U" << endl;
        U.field().replace(swirlCmpt, 0.0);
    }

    U.correctBoundaryConditions();

    Info<< "max(U) " << max(mag(U)).value() << endl;
}
