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

Class
    Foam::cellPointWeightWallModified

Description
    Foam::cellPointWeightWallModified

SourceFiles
    cellPointWeightWallModified.C

\*---------------------------------------------------------------------------*/

#ifndef cellPointWeightWallModified_H
#define cellPointWeightWallModified_H

#include "OpenFOAM-2.1.x/src/finiteVolume/interpolation/interpolation/interpolationCellPoint/cellPointWeight/cellPointWeight.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/polyPatches/derived/wall/wallPolyPatch.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/polyMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/polyBoundaryMesh/polyBoundaryMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class polyMesh;

/*---------------------------------------------------------------------------*\
                 Class cellPointWeightWallModified Declaration
\*---------------------------------------------------------------------------*/

class cellPointWeightWallModified
:
    public cellPointWeight
{
public:

    // Constructors

        //- Construct from components
        cellPointWeightWallModified
        (
            const polyMesh& mesh,
            const vector& position,
            const label cellI,
            const label faceI = -1
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
