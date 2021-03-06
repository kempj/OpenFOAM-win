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
    Merge points. See below.

SourceFiles
    mergePoints.C

\*---------------------------------------------------------------------------*/

#ifndef mergePoints_H
#define mergePoints_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/Fields/scalarField/scalarField.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveShapes/point/pointField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Function mergePoints Declaration
\*---------------------------------------------------------------------------*/

//- Sort & merge points. All points closer than/equal mergeTol get merged.
//  Outputs the new unique points and a map from old to new. Returns
//  true if anything merged, false otherwise.
bool mergePoints
(
    const UList<point>& points,
    const scalar mergeTol,
    const bool verbose,
    labelList& pointMap,
    List<point>& newPoints,
    const point& origin = point::zero
);

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
