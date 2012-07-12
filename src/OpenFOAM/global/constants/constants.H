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

Namespace
    Foam::constant

Description
    Collection of constants

\*---------------------------------------------------------------------------*/

#ifndef constants_H
#define constants_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Dimensionless coefficents

// Mathematical constants
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/constants/mathematical/mathematicalConstants.H"


// Dimensioned constants

// Fundamental constants
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/constants/fundamental/fundamentalConstants.H"

// Derived constants
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/constants/universal/universalConstants.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/constants/electromagnetic/electromagneticConstants.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/constants/atomic/atomicConstants.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/constants/physicoChemical/physicoChemicalConstants.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
