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
     Orders the local points on the patch for most efficient search

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/OpenFOAM/containers/LinkedLists/user/SLList.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/bools/lists/boolList.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveMesh/primitivePatchLC/primitivePatch.H"//JK

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template
<
    class Face,
    template<class> class FaceList,
    class PointField,
    class PointType
>
void
Foam::PrimitivePatch<Face, FaceList, PointField, PointType>::
calcLocalPointOrder() const
{
    // Note: Cannot use bandCompressing as point-point addressing does
    // not exist and is not considered generally useful.
    //

    if (debug)
    {
        Pout<< "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            << "calcLocalPointOrder() : "
            << "calculating local point order"
            << endl;
    }

    if (localPointOrderPtr_)
    {
        // it is considered an error to attempt to recalculate
        // if already allocated
        FatalErrorIn
        (
            "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            "calcLocalPointOrder()"
        )   << "local point order already calculated"
            << abort(FatalError);
    }

    const List<Face>& lf = localFaces();

    const labelListList& ff = faceFaces();

    boolList visitedFace(lf.size(), false);

    localPointOrderPtr_ = new labelList(meshPoints().size(), -1);

    labelList& pointOrder = *localPointOrderPtr_;

    boolList visitedPoint(pointOrder.size(), false);

    label nPoints = 0;

    forAll(lf, faceI)
    {
        if (!visitedFace[faceI])
        {
            SLList<label> faceOrder(faceI);

            do
            {
                const label curFace = faceOrder.first();

                faceOrder.removeHead();

                if (!visitedFace[curFace])
                {
                    visitedFace[curFace] = true;

                    const labelList& curPoints = lf[curFace];

                    // mark points
                    forAll(curPoints, pointI)
                    {
                        if (!visitedPoint[curPoints[pointI]])
                        {
                            visitedPoint[curPoints[pointI]] = true;

                            pointOrder[nPoints] = curPoints[pointI];

                            nPoints++;
                        }
                    }

                    // add face neighbours to the list
                    const labelList& nbrs = ff[curFace];

                    forAll(nbrs, nbrI)
                    {
                        if (!visitedFace[nbrs[nbrI]])
                        {
                            faceOrder.append(nbrs[nbrI]);
                        }
                    }
                }
            } while (faceOrder.size());
        }
    }

    if (debug)
    {
        Pout<< "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            << "calcLocalPointOrder() "
            << "finished calculating local point order"
            << endl;
    }
}


// ************************************************************************* //
