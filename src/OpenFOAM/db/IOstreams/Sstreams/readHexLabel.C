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

Description
    Read a non-delimited hex label

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/Sstreams/readHexLabel.H"
#include <cctype>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::label Foam::readHexLabel(ISstream& is)
{
    // Takes into account that 'a' (or 'A') is 10
    static const label alphaOffset = toupper('A') - 10;
    // Takes into account that '0' is 0
    static const label zeroOffset = int('0');

    char c = 0;

    // Get next non-whitespace character
    while (is.get(c) && isspace(c))
    {}

    register label result = 0;
    do
    {
        if (isspace(c) || c == 0) break;

        if (!isxdigit(c))
        {
            FatalIOErrorIn("readHexLabel(ISstream&)", is)
                << "Illegal hex digit: '" << c << "'"
                << exit(FatalIOError);
        }

        result <<= 4;

        if (isdigit(c))
        {
            result += int(c) - zeroOffset;
        }
        else
        {
            result += toupper(c) - alphaOffset;
        }
    } while (is.get(c));

    return result;
}


// ************************************************************************* //
