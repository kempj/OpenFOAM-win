/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/finiteVolume/cfdTools/general/MRF/MRFZone.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/surfaceFields/surfaceFields.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/geometricOneField/geometricOneField.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
void Foam::MRFZone::relativeRhoFlux
(
    const RhoFieldType& rho,
    surfaceScalarField& phi
) const
{
    const surfaceVectorField& Cf = mesh_.Cf();
    const surfaceVectorField& Sf = mesh_.Sf();

    const vector& origin = origin_.value();
    const vector& Omega = Omega_.value();

    const vectorField& Cfi = Cf.internalField();
    const vectorField& Sfi = Sf.internalField();
    scalarField& phii = phi.internalField();

    // Internal faces
    forAll(internalFaces_, i)
    {
        label facei = internalFaces_[i];
        phii[facei] -= rho[facei]*(Omega ^ (Cfi[facei] - origin)) & Sfi[facei];
    }

    // Included patches
    forAll(includedFaces_, patchi)
    {
        forAll(includedFaces_[patchi], i)
        {
            label patchFacei = includedFaces_[patchi][i];

            phi.boundaryField()[patchi][patchFacei] = 0.0;
        }
    }

    // Excluded patches
    forAll(excludedFaces_, patchi)
    {
        forAll(excludedFaces_[patchi], i)
        {
            label patchFacei = excludedFaces_[patchi][i];

            phi.boundaryField()[patchi][patchFacei] -=
                rho.boundaryField()[patchi][patchFacei]
              * (Omega ^ (Cf.boundaryField()[patchi][patchFacei] - origin))
              & Sf.boundaryField()[patchi][patchFacei];
        }
    }
}


template<class RhoFieldType>
void Foam::MRFZone::absoluteRhoFlux
(
    const RhoFieldType& rho,
    surfaceScalarField& phi
) const
{
    const surfaceVectorField& Cf = mesh_.Cf();
    const surfaceVectorField& Sf = mesh_.Sf();

    const vector& origin = origin_.value();
    const vector& Omega = Omega_.value();

    const vectorField& Cfi = Cf.internalField();
    const vectorField& Sfi = Sf.internalField();
    scalarField& phii = phi.internalField();

    // Internal faces
    forAll(internalFaces_, i)
    {
        label facei = internalFaces_[i];
        phii[facei] += rho[facei]*(Omega ^ (Cfi[facei] - origin)) & Sfi[facei];
    }

    // Included patches
    forAll(includedFaces_, patchi)
    {
        forAll(includedFaces_[patchi], i)
        {
            label patchFacei = includedFaces_[patchi][i];

            phi.boundaryField()[patchi][patchFacei] +=
                rho.boundaryField()[patchi][patchFacei]
              * (Omega ^ (Cf.boundaryField()[patchi][patchFacei] - origin))
              & Sf.boundaryField()[patchi][patchFacei];
        }
    }

    // Excluded patches
    forAll(excludedFaces_, patchi)
    {
        forAll(excludedFaces_[patchi], i)
        {
            label patchFacei = excludedFaces_[patchi][i];

            phi.boundaryField()[patchi][patchFacei] +=
                rho.boundaryField()[patchi][patchFacei]
              * (Omega ^ (Cf.boundaryField()[patchi][patchFacei] - origin))
              & Sf.boundaryField()[patchi][patchFacei];
        }
    }
}


// ************************************************************************* //
