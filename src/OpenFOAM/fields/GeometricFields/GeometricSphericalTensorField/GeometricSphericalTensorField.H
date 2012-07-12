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

InClass
    Foam::GeometricSphericalTensorField

Description
    SphericalTensor specific part of the implementation of GeometricField.

SourceFiles
    GeometricSphericalTensorField.C

\*---------------------------------------------------------------------------*/

#ifndef GeometricSphericalTensorField_H
#define GeometricSphericalTensorField_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/GeometricField/GeometricField.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/SphericalTensor/sphericalTensor/sphericalTensor.H"

#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/GeometricField/GeometricFieldFunctionsM.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

UNARY_FUNCTION(scalar, sphericalTensor, tr, transform)
UNARY_FUNCTION(sphericalTensor, sphericalTensor, sph, transform)
UNARY_FUNCTION(scalar, sphericalTensor, det, transform)
UNARY_FUNCTION(sphericalTensor, sphericalTensor, inv, inv)

BINARY_OPERATOR(sphericalTensor, scalar, sphericalTensor, /, '|', divide)
BINARY_TYPE_OPERATOR(sphericalTensor, scalar, sphericalTensor, /, '|', divide)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/Fields/Field/undefFieldFunctionsM.H"

#ifdef NoRepository
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/GeometricSphericalTensorField/GeometricSphericalTensorField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
