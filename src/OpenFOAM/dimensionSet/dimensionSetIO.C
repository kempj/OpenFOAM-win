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

#include "OpenFOAM-2.1.x/src/OpenFOAM/dimensionSet/dimensionSet.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/IOstreams.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::dimensionSet::dimensionSet(Istream& is)
{
    is >> *this;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

Foam::Istream& Foam::operator>>(Istream& is, dimensionSet& dset)
{
    // Read begining of dimensionSet
    if (token(is) != token::BEGIN_SQR)
    {
        Info<< "expected a " << token::BEGIN_SQR << " in dimensionSet"
            << endl << "in stream " << is.info() << endl;
    }

    // Read first five dimensions
    for (int Dimension=0; Dimension<dimensionSet::CURRENT; Dimension++)
    {
        is >> dset.exponents_[Dimension];
    }

    // Read next token
    token nextToken(is);

    // If next token is another number
    // read last two dimensions
    // and then read another token for the end of the dimensionSet
    if (nextToken.isNumber())
    {
        dset.exponents_[dimensionSet::CURRENT] = nextToken.number();
        is >> dset.exponents_[dimensionSet::LUMINOUS_INTENSITY];
        is >> nextToken;
    }
    else
    {
        dset.exponents_[dimensionSet::CURRENT] = 0;
        dset.exponents_[dimensionSet::LUMINOUS_INTENSITY] = 0;
    }

    // Check end of dimensionSet
    if (nextToken != token::END_SQR)
    {
        Info<< "expected a " << token::END_SQR << " in dimensionSet"
            << endl << "in stream " << is.info() << endl;
    }

    // Check state of Istream
    is.check("Istream& operator>>(Istream&, dimensionSet&)");

    return is;
}


Foam::Ostream& Foam::operator<<(Ostream& os, const dimensionSet& dset)
{
    os << token::BEGIN_SQR;

    for (int Dimension=0; Dimension<dimensionSet::nDimensions-1; Dimension++)
    {
        os << dset.exponents_[Dimension] << token::SPACE;
    }
    os << dset.exponents_[dimensionSet::nDimensions-1] << token::END_SQR;

    // Check state of Ostream
    os.check("Ostream& operator<<(Ostream&, const dimensionSet&)");

    return os;
}


// ************************************************************************* //
