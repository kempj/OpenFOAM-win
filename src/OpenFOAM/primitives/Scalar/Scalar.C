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

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/pTraits/pTraits.H"

//#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/strings/word/word.H"//JK
//#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/IOstreams/Istream.H"//JK
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/scalar/scalar.H"//JK
//#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/floatScalar/floatScalar.H"
//#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/doubleScalar/doubleScalar.H"

//#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/Scalar.H"//JK

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/token/token.H"//JK

#include <sstream>//JK

#ifndef ScalarVGREAT
#define ScalarVGREAT doubleScalarVGREAT
#endif

#define Scalar doubleScalar//JK

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
	typedef double doubleScalar;//JK

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

const char* const pTraits<Scalar>::typeName = "scalar";
const Scalar pTraits<Scalar>::zero = 0.0;
const Scalar pTraits<Scalar>::one = 1.0;
const Scalar pTraits<Scalar>::min = -ScalarVGREAT;
const Scalar pTraits<Scalar>::max = ScalarVGREAT;

const char* pTraits<Scalar>::componentNames[] = { "x" };

pTraits<Scalar>::pTraits(const Scalar& p)
:
    p_(p)
{}


pTraits<Scalar>::pTraits(Istream& is)
{
    is >> p_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

word name(const Scalar val)
{
    std::ostringstream buf;
    buf << val;
    return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

Scalar readScalar(Istream& is)
{
    Scalar rs;
    is  >> rs;

    return rs;
}


Istream& operator>>(Istream& is, Scalar& s)
{
    token t(is);

    if (!t.good())
    {
        is.setBad();
        return is;
    }

    if (t.isNumber())
    {
        s = t.number();
    }
    else
    {
        is.setBad();
        FatalIOErrorIn("operator>>(Istream&, Scalar&)", is)
            << "wrong token type - expected Scalar, found " << t.info()
            << exit(FatalIOError);

        return is;
    }

    // Check state of Istream
    is.check("Istream& operator>>(Istream&, Scalar&)");

    return is;
}


Ostream& operator<<(Ostream& os, const Scalar s)
{
    os.write(s);
    os.check("Ostream& operator<<(Ostream&, const Scalar&)");
    return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
