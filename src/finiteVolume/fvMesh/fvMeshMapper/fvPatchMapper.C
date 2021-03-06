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

#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMeshMapper/fvPatchMapper.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvPatches/fvPatch/fvPatch.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvBoundaryMesh/fvBoundaryMesh.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/mapPolyMesh/mapPolyMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/mapPolyMesh/faceMapper/faceMapper.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::fvPatchMapper::calcAddressing() const
{
    if
    (
        directAddrPtr_
     || interpolationAddrPtr_
     || weightsPtr_
    )
    {
        FatalErrorIn
        (
            "void fvPatchMapper::calcAddressing() const)"
        )   << "Addressing already calculated"
            << abort(FatalError);
    }

    // Mapping
    const label oldPatchStart =
        faceMap_.oldPatchStarts()[patch_.index()];

    const label oldPatchEnd =
        oldPatchStart + faceMap_.oldPatchSizes()[patch_.index()];

    // Assemble the maps: slice to patch
    if (direct())
    {
        // Direct mapping - slice to size
        directAddrPtr_ = new labelList
        (
            patch_.patchSlice
            (
                static_cast<const labelList&>(faceMap_.directAddressing())
            )
        );
        labelList& addr = *directAddrPtr_;

        // Adjust mapping to manage hits into other patches and into
        // internal
        forAll(addr, faceI)
        {
            if
            (
                addr[faceI] >= oldPatchStart
             && addr[faceI] < oldPatchEnd
            )
            {
                addr[faceI] -= oldPatchStart;
            }
            else
            {
                addr[faceI] = 0;
            }
        }

        if (fvMesh::debug)
        {
            if (min(addr) < 0)
            {
                FatalErrorIn
                (
                    "void fvPatchMapper::calcAddressing() const"
                )   << "Error in patch mapping for patch "
                    << patch_.index() << " named " << patch_.name()
                    << abort(FatalError);
            }
        }
    }
    else
    {
        // Interpolative mapping
        interpolationAddrPtr_ =
            new labelListList
            (
                patch_.patchSlice(faceMap_.addressing())
            );
        labelListList& addr = *interpolationAddrPtr_;

        weightsPtr_ =
            new scalarListList
            (
                patch_.patchSlice(faceMap_.weights())
            );
        scalarListList& w = *weightsPtr_;

        // Adjust mapping to manage hits into other patches and into
        // internal
        forAll(addr, faceI)
        {
            labelList& curAddr = addr[faceI];
            scalarList& curW = w[faceI];

            if
            (
                min(curAddr) >= oldPatchStart
             && max(curAddr) < oldPatchEnd
            )
            {
                // No adjustment of weights, just subtract patch start
                forAll(curAddr, i)
                {
                    curAddr[i] -= oldPatchStart;
                }
            }
            else
            {
                // Need to recalculate weights to exclude hits into internal
                labelList newAddr(curAddr.size(), false);
                scalarField newWeights(curAddr.size());
                label nActive = 0;

                forAll(curAddr, lfI)
                {
                    if
                    (
                        curAddr[lfI] >= oldPatchStart
                     && curAddr[lfI] < oldPatchEnd
                    )
                    {
                        newAddr[nActive] = curAddr[lfI] - oldPatchStart;
                        newWeights[nActive] = curW[lfI];
                        nActive++;
                    }
                }

                // Cater for bad mapping
                if (nActive == 0)
                {
                    newAddr[nActive] = 0;
                    newWeights[nActive] = 1;
                    nActive++;
                }

                newAddr.setSize(nActive);
                newWeights.setSize(nActive);

                // Re-scale the weights
                newWeights /= sum(newWeights);

                // Reset addressing and weights
                curAddr = newAddr;
                curW = newWeights;
            }
        }

        if (fvMesh::debug)
        {
            forAll(addr, i)
            {
                if (min(addr[i]) < 0)
                {
                    FatalErrorIn
                    (
                        "void fvPatchMapper::calcAddressing() const"
                    )   << "Error in patch mapping for patch "
                        << patch_.index() << " named " << patch_.name()
                        << abort(FatalError);
                }
            }
        }
    }
}


void Foam::fvPatchMapper::clearOut()
{
    deleteDemandDrivenData(directAddrPtr_);
    deleteDemandDrivenData(interpolationAddrPtr_);
    deleteDemandDrivenData(weightsPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
Foam::fvPatchMapper::fvPatchMapper
(
    const fvPatch& patch,
    const faceMapper& faceMap
)
:
    patch_(patch),
    faceMap_(faceMap),
    sizeBeforeMapping_(faceMap.oldPatchSizes()[patch_.index()]),
    directAddrPtr_(NULL),
    interpolationAddrPtr_(NULL),
    weightsPtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::fvPatchMapper::~fvPatchMapper()
{
    clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const Foam::labelUList& Foam::fvPatchMapper::directAddressing() const
{
    if (!direct())
    {
        FatalErrorIn
        (
            "const labelUList& fvPatchMapper::directAddressing() const"
        )   << "Requested direct addressing for an interpolative mapper."
            << abort(FatalError);
    }

    if (!directAddrPtr_)
    {
        calcAddressing();
    }

    return *directAddrPtr_;
}


const Foam::labelListList& Foam::fvPatchMapper::addressing() const
{
    if (direct())
    {
        FatalErrorIn
        (
            "const labelListList& fvPatchMapper::addressing() const"
        )   << "Requested interpolative addressing for a direct mapper."
            << abort(FatalError);
    }

    if (!interpolationAddrPtr_)
    {
        calcAddressing();
    }

    return *interpolationAddrPtr_;
}


const Foam::scalarListList& Foam::fvPatchMapper::weights() const
{
    if (direct())
    {
        FatalErrorIn
        (
            "const scalarListList& fvPatchMapper::weights() const"
        )   << "Requested interpolative weights for a direct mapper."
            << abort(FatalError);
    }

    if (!weightsPtr_)
    {
        calcAddressing();
    }

    return *weightsPtr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //
