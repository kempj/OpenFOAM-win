/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenFOAM Foundation
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

#include "OpenFOAM-2.1.x/src/meshTools/sets/cellSources/targetVolumeToCell/targetVolumeToCell.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/polyMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/globalMeshData/globalMeshData.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveShapes/plane/plane.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/Pstreams/PstreamReduceOps.H"//JK

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

defineTypeNameAndDebug(targetVolumeToCell, 0);

addToRunTimeSelectionTable(topoSetSource, targetVolumeToCell, word);

addToRunTimeSelectionTable(topoSetSource, targetVolumeToCell, istream);

}


Foam::topoSetSource::addToUsageTable Foam::targetVolumeToCell::usage_
(
    targetVolumeToCell::typeName,
    "\n    Usage: targetVolumeToCell (nx ny nz)\n\n"
    "    Adjust plane until obtained selected volume\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Foam::scalar Foam::targetVolumeToCell::volumeOfSet
(
    const PackedBoolList& selected
) const
{
    scalar sumVol = 0.0;
    forAll(selected, cellI)
    {
        if (selected[cellI])
        {
            sumVol += mesh_.cellVolumes()[cellI];
        }
    }
    return returnReduce(sumVol, sumOp<scalar>());
}


Foam::label Foam::targetVolumeToCell::selectCells
(
    const scalar normalComp,
    PackedBoolList& selected
) const
{
    selected.setSize(mesh_.nCells());
    selected = false;

    label nSelected = 0;

    forAll(mesh_.cellCentres(), cellI)
    {
        const point& cc = mesh_.cellCentres()[cellI];

        if ((cc&n_) < normalComp)
        {
            selected[cellI] = true;
            nSelected++;
        }
    }
    return returnReduce(nSelected, sumOp<label>());
}


void Foam::targetVolumeToCell::combine(topoSet& set, const bool add) const
{
    if (vol_ <= 0)
    {
        // Select no cells
        return;
    }
    else if (gSum(mesh_.cellVolumes()) < vol_)
    {
        // Select all cells
        forAll(mesh_.cellVolumes(), cellI)
        {
            addOrDelete(set, cellI, add);
        }
        return;
    }


    // Get plane for min,max volume.
    // Planes all have base (0 0 0) and fixed normal so work only on normal
    // component.

    scalar maxComp = -GREAT;
    label maxCells = 0;
    scalar maxVol = 0;
    scalar minComp = GREAT;
    {
        const boundBox& bb = mesh_.bounds();
        pointField points(bb.points());

        label minPointI = -1;
        label maxPointI = -1;
        forAll(points, pointI)
        {
            scalar c = (points[pointI]&n_);
            if (c > maxComp)
            {
                maxComp = c;
                maxPointI = pointI;
            }
            else if (c < minComp)
            {
                minComp = c;
                minPointI = pointI;
            }
        }

        PackedBoolList maxSelected(mesh_.nCells());
        maxCells = selectCells(maxComp, maxSelected);
        maxVol = volumeOfSet(maxSelected);

        // Check that maxPoint indeed selects all cells
        if (maxCells != mesh_.globalData().nTotalCells())
        {
            WarningIn("targetVolumeToCell::combine(topoSet&, const bool) const")
                << "Plane " << plane(points[maxPointI], n_)
                << " selects " << maxCells
                << " cells instead of all " << mesh_.globalData().nTotalCells()
                << " cells. Results might be wrong." << endl;
        }
    }



    // Bisection
    // ~~~~~~~~~

    PackedBoolList selected(mesh_.nCells());
    label nSelected = -1;
    scalar selectedVol = 0.0;
    scalar selectedComp = 0.0;


    scalar low = minComp;
    scalar high = maxComp;

    const scalar tolerance = SMALL*100*(maxComp-minComp);

    while ((high-low) > tolerance)
    {
        scalar mid = 0.5*(low + high);

        nSelected = selectCells(mid, selected);
        selectedVol = volumeOfSet(selected);

        //Pout<< "High:" << high << " low:" << low << " mid:" << mid << nl
        //    << "    nSelected:" << nSelected << nl
        //    << "    vol      :" << selectedVol << nl
        //    << endl;

        if (selectedVol < vol_)
        {
            low = mid;

            PackedBoolList highSelected(mesh_.nCells());
            label nHigh = selectCells(high, selected);
            if (nSelected == nHigh)
            {
                break;
            }
        }
        else
        {
            high = mid;

            PackedBoolList lowSelected(mesh_.nCells());
            label nLow = selectCells(low, selected);
            if (nSelected == nLow)
            {
                break;
            }
        }
    }

    nSelected = selectCells(high, selected);
    selectedVol = volumeOfSet(selected);

    if (selectedVol < vol_)
    {
        selectedComp = high;
    }
    else
    {
        nSelected = selectCells(low, selected);
        selectedVol = volumeOfSet(selected);

        if (selectedVol < vol_)
        {
            selectedComp = low;
        }
        else
        {
            WarningIn("targetVolumeToCell::combine(topoSet&, const bool) const")
                << "Did not converge onto plane. " << nl
                << "high plane:"
                << plane(high*n_, n_)
                << nl
                << "low plane :"
                << plane(low*n_, n_)
                << endl;
        }
    }


    Info<< "    Selected " << nSelected << " with actual volume " << selectedVol
        << endl;

    forAll(selected, cellI)
    {
        if (selected[cellI])
        {
            addOrDelete(set, cellI, add);
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
Foam::targetVolumeToCell::targetVolumeToCell
(
    const polyMesh& mesh,
    const scalar vol,
    const vector& n
)
:
    topoSetSource(mesh),
    vol_(vol),
    n_(n)
{}


// Construct from dictionary
Foam::targetVolumeToCell::targetVolumeToCell
(
    const polyMesh& mesh,
    const dictionary& dict
)
:
    topoSetSource(mesh),
    vol_(readScalar(dict.lookup("volume"))),
    n_(dict.lookup("normal"))
{}


// Construct from Istream
Foam::targetVolumeToCell::targetVolumeToCell
(
    const polyMesh& mesh,
    Istream& is
)
:
    topoSetSource(mesh),
    vol_(readScalar(checkIs(is))),
    n_(checkIs(is))
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::targetVolumeToCell::~targetVolumeToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::targetVolumeToCell::applyToSet
(
    const topoSetSource::setAction action,
    topoSet& set
) const
{
    if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
    {
        Info<< "    Adding cells up to target volume " << vol_
            << " out of total volume " << gSum(mesh_.cellVolumes()) << endl;

        combine(set, true);
    }
    else if (action == topoSetSource::DELETE)
    {
        Info<< "    Removing cells up to target volume " << vol_
            << " out of total volume " << gSum(mesh_.cellVolumes()) << endl;

        combine(set, false);
    }
}


// ************************************************************************* //
