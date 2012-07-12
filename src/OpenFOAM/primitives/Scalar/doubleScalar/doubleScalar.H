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
    Foam::doubleScalar

Description
    Double precision floating point scalar type.

SourceFiles
    doubleScalar.C

\*---------------------------------------------------------------------------*/

#ifndef doubleScalar_H
#define doubleScalar_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/doubleFloat.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/direction/direction.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/strings/word/word.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

typedef double doubleScalar;

// Largest and smallest scalar values allowed in certain parts of the code.
// (15 is the number of significant figures in an
//  IEEE double precision number.  See limits.h or float.h)
static const doubleScalar doubleScalarGREAT = 1.0e+15;
static const doubleScalar doubleScalarVGREAT = 1.0e+300;
static const doubleScalar doubleScalarROOTVGREAT = 1.0e+150;
static const doubleScalar doubleScalarSMALL = 1.0e-15;
static const doubleScalar doubleScalarVSMALL = 1.0e-300;
static const doubleScalar doubleScalarROOTVSMALL = 1.0e-150;


#define Scalar doubleScalar
#define ScalarVGREAT doubleScalarVGREAT
#define ScalarVSMALL doubleScalarVSMALL
#define readScalar readDoubleScalar

inline Scalar mag(const Scalar s)
{
    return ::fabs(s);
}

#define transFunc(func)            \
inline Scalar func(const Scalar s) \
{                                  \
    return ::func(s);              \
}

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/Scalar.H"

inline Scalar hypot(const Scalar x, const Scalar y)
{
    return ::hypot(x, y);
}

inline Scalar atan2(const Scalar y, const Scalar x)
{
    return ::atan2(y, x);
}

inline Scalar jn(const int n, const Scalar s)
{
    return ::jn(n, s);
}

inline Scalar yn(const int n, const Scalar s)
{
    return ::yn(n, s);
}

#undef Scalar
#undef ScalarVGREAT
#undef ScalarVSMALL
#undef readScalar
#undef transFunc


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
