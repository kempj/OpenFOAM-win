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

#include "OpenFOAM-2.1.x/src/meshTools/indexedOctree/treeDataPoint.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/treeBoundBox/treeBoundBox.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/algorithms/indexedOctree/indexedOctree.H"
#include "OpenFOAM-2.1.x/src/meshTools/triSurface/triangleFuncs/triangleFuncs.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(Foam::treeDataPoint, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::treeDataPoint::treeDataPoint(const pointField& points)
:
    points_(points),
    useSubset_(false)
{}


Foam::treeDataPoint::treeDataPoint
(
    const pointField& points,
    const labelList& pointLabels
)
:
    points_(points),
    pointLabels_(pointLabels),
    useSubset_(true)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::pointField Foam::treeDataPoint::shapePoints() const
{
    if (useSubset_)
    {
        return pointField(points_, pointLabels_);
    }
    else
    {
        return points_;
    }
}


//- Get type (inside,outside,mixed,unknown) of point w.r.t. surface.
//  Only makes sense for closed surfaces.
Foam::label Foam::treeDataPoint::getVolumeType
(
    const indexedOctree<treeDataPoint>& oc,
    const point& sample
) const
{
    return indexedOctree<treeDataPoint>::UNKNOWN;
}


// Check if any point on shape is inside cubeBb.
bool Foam::treeDataPoint::overlaps
(
    const label index,
    const treeBoundBox& cubeBb
) const
{
    label pointI = (useSubset_ ? pointLabels_[index] : index);
    return cubeBb.contains(points_[pointI]);
}


// Calculate nearest point to sample. Updates (if any) nearestDistSqr, minIndex,
// nearestPoint.
void Foam::treeDataPoint::findNearest
(
    const labelUList& indices,
    const point& sample,

    scalar& nearestDistSqr,
    label& minIndex,
    point& nearestPoint
) const
{
    forAll(indices, i)
    {
        const label index = indices[i];
        label pointI = (useSubset_ ? pointLabels_[index] : index);

        const point& pt = points_[pointI];

        scalar distSqr = magSqr(pt - sample);

        if (distSqr < nearestDistSqr)
        {
            nearestDistSqr = distSqr;
            minIndex = index;
            nearestPoint = pt;
        }
    }
}


//- Calculates nearest (to line) point in shape.
//  Returns point and distance (squared)
void Foam::treeDataPoint::findNearest
(
    const labelUList& indices,
    const linePointRef& ln,

    treeBoundBox& tightest,
    label& minIndex,
    point& linePoint,
    point& nearestPoint
) const
{
    // Best so far
    scalar nearestDistSqr = magSqr(linePoint - nearestPoint);

    forAll(indices, i)
    {
        const label index = indices[i];
        label pointI = (useSubset_ ? pointLabels_[index] : index);

        const point& shapePt = points_[pointI];

        if (tightest.contains(shapePt))
        {
            // Nearest point on line
            pointHit pHit = ln.nearestDist(shapePt);
            scalar distSqr = sqr(pHit.distance());

            if (distSqr < nearestDistSqr)
            {
                nearestDistSqr = distSqr;
                minIndex = index;
                linePoint = pHit.rawPoint();
                nearestPoint = shapePt;

                {
                    point& minPt = tightest.min();
                    minPt = min(ln.start(), ln.end());
                    minPt.x() -= pHit.distance();
                    minPt.y() -= pHit.distance();
                    minPt.z() -= pHit.distance();
                }
                {
                    point& maxPt = tightest.max();
                    maxPt = max(ln.start(), ln.end());
                    maxPt.x() += pHit.distance();
                    maxPt.y() += pHit.distance();
                    maxPt.z() += pHit.distance();
                }
            }
        }
    }
}


// ************************************************************************* //
