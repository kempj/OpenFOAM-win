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

#include "OpenFOAM-2.1.x/src/meshTools/sets/cellSources/zoneToCell/zoneToCell.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/polyMesh.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

defineTypeNameAndDebug(zoneToCell, 0);

addToRunTimeSelectionTable(topoSetSource, zoneToCell, word);

addToRunTimeSelectionTable(topoSetSource, zoneToCell, istream);

}


Foam::topoSetSource::addToUsageTable Foam::zoneToCell::usage_
(
    zoneToCell::typeName,
    "\n    Usage: zoneToCell zone\n\n"
    "    Select all cells in the cellZone."
    " Note:accepts wildcards for zone.\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::zoneToCell::combine(topoSet& set, const bool add) const
{
    bool hasMatched = false;

    forAll(mesh_.cellZones(), i)
    {
        const cellZone& zone = mesh_.cellZones()[i];

        if (zoneName_.match(zone.name()))
        {
            const labelList& cellLabels = mesh_.cellZones()[i];

            Info<< "    Found matching zone " << zone.name()
                << " with " << cellLabels.size() << " cells." << endl;

            hasMatched = true;

            forAll(cellLabels, i)
            {
                // Only do active cells
                if (cellLabels[i] < mesh_.nCells())
                {
                    addOrDelete(set, cellLabels[i], add);
                }
            }
        }
    }

    if (!hasMatched)
    {
        WarningIn("zoneToCell::combine(topoSet&, const bool)")
            << "Cannot find any cellZone named " << zoneName_ << endl
            << "Valid names are " << mesh_.cellZones().names() << endl;
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
Foam::zoneToCell::zoneToCell
(
    const polyMesh& mesh,
    const word& zoneName
)
:
    topoSetSource(mesh),
    zoneName_(zoneName)
{}


// Construct from dictionary
Foam::zoneToCell::zoneToCell
(
    const polyMesh& mesh,
    const dictionary& dict
)
:
    topoSetSource(mesh),
    zoneName_(dict.lookup("name"))
{}


// Construct from Istream
Foam::zoneToCell::zoneToCell
(
    const polyMesh& mesh,
    Istream& is
)
:
    topoSetSource(mesh),
    zoneName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::zoneToCell::~zoneToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::zoneToCell::applyToSet
(
    const topoSetSource::setAction action,
    topoSet& set
) const
{
    if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
    {
        Info<< "    Adding all cells of cellZone " << zoneName_ << " ..."
            << endl;

        combine(set, true);
    }
    else if (action == topoSetSource::DELETE)
    {
        Info<< "    Removing all cells of cellZone " << zoneName_ << " ..."
            << endl;

        combine(set, false);
    }
}


// ************************************************************************* //
