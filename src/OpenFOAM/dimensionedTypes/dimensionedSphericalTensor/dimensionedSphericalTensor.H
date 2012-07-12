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

Typedef
    Foam::dimensionedSphericalTensor

Description
    Dimensioned sphericalTensor obtained from generic dimensioned type.

SourceFiles
    dimensionedSphericalTensor.C

\*---------------------------------------------------------------------------*/

#ifndef dimensionedSphericalTensor_H
#define dimensionedSphericalTensor_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/dimensionedTypes/dimensionedType/dimensionedType.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/SphericalTensor/sphericalTensor/sphericalTensor.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

typedef dimensioned<sphericalTensor> dimensionedSphericalTensor;


// global functions

dimensionedScalar tr(const dimensionedSphericalTensor&);
dimensionedScalar det(const dimensionedSphericalTensor&);
dimensionedSphericalTensor inv(const dimensionedSphericalTensor&);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

