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

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/dictionary/functionEntries/includeIfPresentEntry/includeIfPresentEntry.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/dictionary/dictionary.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/Fstreams/IFstream.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/runTimeSelection/memberFunctions/addToMemberFunctionSelectionTable.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/dictionary/primitiveEntry/primitiveEntry.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const Foam::word Foam::functionEntries::includeIfPresentEntry::typeName
(
    Foam::functionEntries::includeIfPresentEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeIfPresentEntry
int Foam::functionEntries::includeIfPresentEntry::debug(0);

namespace Foam
{
namespace functionEntries
{
    addToMemberFunctionSelectionTable
    (
        functionEntry,
        includeIfPresentEntry,
        execute,
        dictionaryIstream
    );

    addToMemberFunctionSelectionTable
    (
        functionEntry,
        includeIfPresentEntry,
        execute,
        primitiveEntryIstream
    );
}
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::functionEntries::includeIfPresentEntry::execute
(
    dictionary& parentDict,
    Istream& is
)
{
    const fileName fName(includeFileName(is));
    IFstream ifs(fName);

    if (ifs)
    {
        if (Foam::functionEntries::includeEntry::report)
        {
            Info<< fName << endl;
        }
        parentDict.read(ifs);
    }

    return true;
}


bool Foam::functionEntries::includeIfPresentEntry::execute
(
    const dictionary& parentDict,
    primitiveEntry& entry,
    Istream& is
)
{
    const fileName fName(includeFileName(is));
    IFstream ifs(fName);

    if (ifs)
    {
        if (Foam::functionEntries::includeEntry::report)
        {
            Info<< fName << endl;
        }
        entry.read(parentDict, ifs);
    }

    return true;
}

// ************************************************************************* //
