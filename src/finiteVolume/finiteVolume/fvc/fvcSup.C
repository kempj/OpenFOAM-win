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

#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/surfaceFields/surfaceFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace fvc
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
Su
(
    const GeometricField<Type, fvPatchField, volMesh>& su,
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    return su;
}

template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
Su
(
    const tmp<GeometricField<Type, fvPatchField, volMesh> >& tsu,
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    return tsu;
}


template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
Sp
(
    const volScalarField& sp,
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    return sp*vf;
}

template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
Sp
(
    const tmp<volScalarField>& tsp,
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    return tsp*vf;
}


template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
Sp
(
    const dimensionedScalar& sp,
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    return sp*vf;
}


template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
SuSp
(
    const volScalarField& sp,
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    return sp*vf;
}

template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
SuSp
(
    const tmp<volScalarField>& tsp,
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    return tsp*vf;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fvc

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
