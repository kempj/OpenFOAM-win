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

#include "OpenFOAM-2.1.x/src/finiteVolume/interpolation/surfaceInterpolation/schemes/linearUpwind/linearUpwindV.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/surfaceFields/surfaceFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::fvsPatchField, Foam::surfaceMesh> >
Foam::linearUpwindV<Type>::correction
(
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    const fvMesh& mesh = this->mesh();

    tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tsfCorr
    (
        new GeometricField<Type, fvsPatchField, surfaceMesh>
        (
            IOobject
            (
                "linearUpwindV::correction(" + vf.name() + ')',
                mesh.time().timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                false
            ),
            mesh,
            dimensioned<Type>
            (
                vf.name(),
                vf.dimensions(),
                pTraits<Type>::zero
            )
        )
    );

    GeometricField<Type, fvsPatchField, surfaceMesh>& sfCorr = tsfCorr();

    const surfaceScalarField& faceFlux = this->faceFlux_;
    const surfaceScalarField& w = mesh.weights();

    const labelList& own = mesh.owner();
    const labelList& nei = mesh.neighbour();

    const vectorField& C = mesh.C();
    const vectorField& Cf = mesh.Cf();

    tmp
    <
        GeometricField
        <
            typename outerProduct<vector, Type>::type,
            fvPatchField,
            volMesh
        >
    > tgradVf = gradScheme_().grad(vf, gradSchemeName_);

    const GeometricField
    <
        typename outerProduct<vector, Type>::type,
        fvPatchField,
        volMesh
    >& gradVf = tgradVf();

    forAll(faceFlux, facei)
    {
        vector maxCorr;

        if (faceFlux[facei] > 0.0)
        {
            maxCorr =
                (1.0 - w[facei])
               *(vf[nei[facei]] - vf[own[facei]]);

            sfCorr[facei] =
                (Cf[facei] - C[own[facei]]) & gradVf[own[facei]];
        }
        else
        {
            maxCorr =
                w[facei]*(vf[own[facei]] - vf[nei[facei]]);

            sfCorr[facei] =
               (Cf[facei] - C[nei[facei]]) & gradVf[nei[facei]];
        }

        scalar sfCorrs = magSqr(sfCorr[facei]);
        scalar maxCorrs = sfCorr[facei] & maxCorr;

        if (sfCorrs > 0)
        {
            if (maxCorrs < 0)
            {
                sfCorr[facei] = vector::zero;
            }
            else if (sfCorrs > maxCorrs)
            {
                sfCorr[facei] *= maxCorrs/(sfCorrs + VSMALL);
            }
        }
        else if (sfCorrs < 0)
        {
            if (maxCorrs > 0)
            {
                sfCorr[facei] = vector::zero;
            }
            else if (sfCorrs < maxCorrs)
            {
                sfCorr[facei] *= maxCorrs/(sfCorrs - VSMALL);
            }
        }
    }

    return tsfCorr;
}


namespace Foam
{
    makelimitedSurfaceInterpolationTypeScheme(linearUpwindV, vector)
}

// ************************************************************************* //
