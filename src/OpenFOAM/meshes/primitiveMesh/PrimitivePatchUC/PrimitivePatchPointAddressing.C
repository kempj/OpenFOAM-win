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
     Point addressing on the patch: pointEdges and pointFaces.

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveMesh/PrimitivePatchUC/PrimitivePatch.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/containers/LinkedLists/user/SLList.H"


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
calcPointEdges() const
{
    if (debug)
    {
        Info<< "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            << "calcPointEdges() : calculating pointEdges"
            << endl;
    }

    if (pointEdgesPtr_)
    {
        // it is considered an error to attempt to recalculate
        // if already allocated
        FatalErrorIn
        (
            "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            "calcPointEdges()"
        )   << "pointEdges already calculated"
            << abort(FatalError);
    }

    const edgeList& e = edges();

    // set up storage for pointEdges
    List<SLList<label> > pointEdges(meshPoints().size());

    forAll(e, edgeI)
    {
        pointEdges[e[edgeI].start()].append(edgeI);
        pointEdges[e[edgeI].end()].append(edgeI);
    }

    // sort out the list
    pointEdgesPtr_ = new labelListList(pointEdges.size());

    labelListList& pe = *pointEdgesPtr_;

    forAll(pointEdges, pointI)
    {
        const SLList<label>& pEdge = pointEdges[pointI];

        pe[pointI].setSize(pEdge.size());

        label i = 0;
        forAllConstIter(SLList<label>, pEdge, iter)
        {
            pe[pointI][i++] = iter();
        }
    }

    if (debug)
    {
        Info<< "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            << "calcPointEdges() finished calculating pointEdges"
            << endl;
    }
}


template
<
    class Face,
    template<class> class FaceList,
    class PointField,
    class PointType
>
void
Foam::PrimitivePatch<Face, FaceList, PointField, PointType>::
calcPointFaces() const
{
    if (debug)
    {
        Info<< "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            << "calcPointFaces() : calculating pointFaces"
            << endl;
    }

    if (pointFacesPtr_)
    {
        // it is considered an error to attempt to recalculate
        // if already allocated
        FatalErrorIn
        (
            "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            "calcPointFaces()"
        )   << "pointFaces already calculated"
            << abort(FatalError);
    }

    const List<Face>& f = localFaces();

    // set up storage for pointFaces
    List<SLList<label> > pointFcs(meshPoints().size());

    forAll(f, faceI)
    {
        const Face& curPoints = f[faceI];

        forAll(curPoints, pointI)
        {
            pointFcs[curPoints[pointI]].append(faceI);
        }
    }

    // sort out the list
    pointFacesPtr_ = new labelListList(pointFcs.size());

    labelListList& pf = *pointFacesPtr_;

    forAll(pointFcs, pointI)
    {
        pf[pointI].setSize(pointFcs[pointI].size());

        label i = 0;
        forAllIter(SLList<label>, pointFcs[pointI], curFacesIter)
        {
            pf[pointI][i++] = curFacesIter();
        }
    }

    if (debug)
    {
        Info<< "PrimitivePatch<Face, FaceList, PointField, PointType>::"
            << "calcPointFaces() finished calculating pointFaces"
            << endl;
    }
}


// ************************************************************************* //
