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

#include "OpenFOAM-2.1.x/src/finiteVolume/interpolation/surfaceInterpolation/multivariateSchemes/multivariateIndependentScheme/multivariateIndependentScheme.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/interpolation/surfaceInterpolation/limitedSchemes/limitedSurfaceInterpolationScheme/limitedSurfaceInterpolationScheme.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/surfaceFields/surfaceFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/interpolation/surfaceInterpolation/limitedSchemes/upwind/upwind.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
Foam::multivariateIndependentScheme<Type>::multivariateIndependentScheme
(
    const fvMesh& mesh,
    const typename multivariateSurfaceInterpolationScheme<Type>::
        fieldTable& fields,
    const surfaceScalarField& faceFlux,
    Istream& schemeData
)
:
    multivariateSurfaceInterpolationScheme<Type>
    (
        mesh,
        fields,
        faceFlux,
        schemeData
    ),
    schemes_(schemeData),
    faceFlux_(faceFlux)
{}


// ************************************************************************* //
