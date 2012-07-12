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

#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/pointMesh/pointPatches/facePointPatch/facePointPatch.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/pointMesh/pointBoundaryMesh/pointBoundaryMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/pointMesh/pointMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/include/demandDrivenData.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/bools/lists/boolList.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(facePointPatch, 0);
defineRunTimeSelectionTable(facePointPatch, polyPatch);

addToRunTimeSelectionTable
(
    facePointPatch,
    facePointPatch,
    polyPatch
);


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void facePointPatch::initGeometry(PstreamBuffers&)
{}


void facePointPatch::calcGeometry(PstreamBuffers&)
{}


void facePointPatch::initMovePoints(PstreamBuffers&, const pointField&)
{}


void facePointPatch::movePoints(PstreamBuffers&, const pointField&)
{}


void facePointPatch::initUpdateMesh(PstreamBuffers& pBufs)
{
    facePointPatch::initGeometry(pBufs);
}


void facePointPatch::updateMesh(PstreamBuffers&)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

facePointPatch::facePointPatch
(
    const polyPatch& p,
    const pointBoundaryMesh& bm
)
:
    pointPatch(bm),
    polyPatch_(p)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
