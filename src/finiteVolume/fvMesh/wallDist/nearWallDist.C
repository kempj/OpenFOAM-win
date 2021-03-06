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

#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/wallDist/nearWallDist.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"
#include "OpenFOAM-2.1.x/src/meshTools/cellDist/cellDistFuncs.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvPatches/derived/wall/wallFvPatch.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/surfaceFields/surfaceFields.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::nearWallDist::doAll()
{
    cellDistFuncs wallUtils(mesh_);

    // Get patch ids of walls
    labelHashSet wallPatchIDs(wallUtils.getPatchIDs<wallPolyPatch>());

    // Size neighbours array for maximum possible

    labelList neighbours(wallUtils.maxPatchSize(wallPatchIDs));


    // Correct all cells with face on wall

    const volVectorField& cellCentres = mesh_.C();

    forAll(mesh_.boundary(), patchI)
    {
        fvPatchScalarField& ypatch = operator[](patchI);

        const fvPatch& patch = mesh_.boundary()[patchI];

        if (isA<wallFvPatch>(patch))
        {
            const polyPatch& pPatch = patch.patch();

            const labelUList& faceCells = patch.faceCells();

            // Check cells with face on wall
            forAll(patch, patchFaceI)
            {
                label nNeighbours = wallUtils.getPointNeighbours
                (
                    pPatch,
                    patchFaceI,
                    neighbours
                );

                label minFaceI = -1;

                ypatch[patchFaceI] = wallUtils.smallestDist
                (
                    cellCentres[faceCells[patchFaceI]],
                    pPatch,
                    nNeighbours,
                    neighbours,
                    minFaceI
                );
            }
        }
        else
        {
            ypatch = 0.0;
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::nearWallDist::nearWallDist(const Foam::fvMesh& mesh)
:
    volScalarField::GeometricBoundaryField
    (
        mesh.boundary(),
        mesh.V(),           // Dummy internal field,
        calculatedFvPatchScalarField::typeName
    ),
    mesh_(mesh)
{
    doAll();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::nearWallDist::~nearWallDist()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::nearWallDist::correct()
{
    if (mesh_.changing())
    {
        // Update size of GeometricBoundaryField
        forAll(mesh_.boundary(), patchI)
        {
            operator[](patchI).setSize(mesh_.boundary()[patchI].size());
        }
    }

    doAll();
}


// ************************************************************************* //
