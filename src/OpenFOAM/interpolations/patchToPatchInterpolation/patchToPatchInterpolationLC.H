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

#ifndef patchToPatchInterpolation_H
#define patchToPatchInterpolation_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/interpolations/patchToPatchInterpolation/PatchToPatchInterpolationUC.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveMesh/PrimitivePatchUC/PrimitivePatch.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/meshShapes/face/face.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/containers/Lists/SubList/SubList.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveShapes/point/pointField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    typedef PatchToPatchInterpolation
    <
        PrimitivePatch<face, SubList, const pointField&>,
        PrimitivePatch<face, SubList, const pointField&>
    >   patchToPatchInterpolation;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
