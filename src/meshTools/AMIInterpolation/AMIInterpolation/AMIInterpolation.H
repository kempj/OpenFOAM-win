/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2012 OpenFOAM Foundation
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
    Foam::AMIInterpolation

Description
    Interpolation class dealing with transfer of data between two
    primitive patches with an arbitrary mesh interface (AMI).

    Based on the algorithm given in:

        Conservative interpolation between volume meshes by local Galerkin
        projection, Farrell PE and Maddison JR, 2011, Comput. Methods Appl.
        Mech Engrg, Volume 200, Issues 1-4, pp 89-100

    Interpolation requires that the two patches should have opposite
    orientations (opposite normals).  The 'reverseTarget' flag can be used to
    reverse the orientation of the target patch.


SourceFiles
    AMIInterpolation.C
    AMIInterpolationName.C

\*---------------------------------------------------------------------------*/

#ifndef AMIInterpolation_H
#define AMIInterpolation_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/typeInfo/className.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/containers/Lists/DynamicList/DynamicList.H"
#include "OpenFOAM-2.1.x/src/meshTools/searchableSurface/searchableSurface.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/bools/lists/boolList.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveMesh/primitivePatchLC/primitivePatch.H"
#include "OpenFOAM-2.1.x/src/meshTools/AMIInterpolation/faceAreaIntersect/faceAreaIntersect.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/algorithms/indexedOctree/indexedOctree.H"
#include "OpenFOAM-2.1.x/src/meshTools/indexedOctree/treeDataPrimitivePatch.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/treeBoundBox/treeBoundBoxList.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/globalMeshData/globalIndex.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/ops/ops.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                    Class AMIInterpolationName Declaration
\*---------------------------------------------------------------------------*/

TemplateName(AMIInterpolation);


/*---------------------------------------------------------------------------*\
                      Class AMIInterpolation Declaration
\*---------------------------------------------------------------------------*/

template<class SourcePatch, class TargetPatch>
class AMIInterpolation
:
    public AMIInterpolationName
{
    //- local typedef to octree tree-type
    typedef treeDataPrimitivePatch<face, SubList, const pointField&> treeType;

    //- Helper class for list
    template<class T>
    class ListPlusEqOp
    {
        public:
        void operator()(List<T>& x, const List<T> y) const
        {
            if (y.size())
            {
                if (x.size())
                {
                    label sz = x.size();
                    x.setSize(sz + y.size());
                    forAll(y, i)
                    {
                        x[sz++] = y[i];
                    }
                }
                else
                {
                    x = y;
                }
            }
        }
    };


    // Private data

        //- Flag to indicate that the two patches are co-directional and
        //  that the orientation of the target patch should be reversed
        const bool reverseTarget_;

        //- Index of processor that holds all of both sides. -1 in all other
        //  cases
        label singlePatchProc_;

        // Source patch

            //- Source face areas
            scalarField srcMagSf_;

            //- Addresses of target faces per source face
            labelListList srcAddress_;

            //- Weights of target faces per source face
            scalarListList srcWeights_;

            //- Sum of weights of target faces per source face
            scalarField srcWeightsSum_;


        // Target patch

            //- Target face areas
            scalarField tgtMagSf_;

            //- Addresses of source faces per target face
            labelListList tgtAddress_;

            //- Weights of source faces per target face
            scalarListList tgtWeights_;

            //- Sum of weights of source faces per target face
            scalarField tgtWeightsSum_;


        //- Octree used to find face seeds
        autoPtr<indexedOctree<treeType> > treePtr_;

        //- Starting face seed index
        label startSeedI_;

        //- Face triangulation mode
        const faceAreaIntersect::triangulationMode triMode_;

        //- Source map pointer - parallel running only
        autoPtr<mapDistribute> srcMapPtr_;

        //- Target map pointer - parallel running only
        autoPtr<mapDistribute> tgtMapPtr_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        AMIInterpolation(const AMIInterpolation&);

        //- Disallow default bitwise assignment
        void operator=(const AMIInterpolation&);


        // Helper functions

            //- Write triangle intersection to OBJ file
            void writeIntersectionOBJ
            (
                const scalar area,
                const face& f1,
                const face& f2,
                const pointField& f1Points,
                const pointField& f2Points
            ) const;

            //- Check that patches are valid
            void checkPatches
            (
                const primitivePatch& srcPatch,
                const primitivePatch& tgtPatch
            );

            //- Reset the octree for the traget patch face search
            void resetTree(const primitivePatch& tgtPatch);



        // Parallel functionality

            //- Calculate if patches are on multiple processors
            label calcDistribution
            (
                const primitivePatch& srcPatch,
                const primitivePatch& tgtPatch
            );

            label calcOverlappingProcs
            (
                const List<treeBoundBoxList>& procBb,
                const treeBoundBox& bb,
                boolList& overlaps
            );

            void distributePatches
            (
                const mapDistribute& map,
                const primitivePatch& pp,
                const globalIndex& gi,
                List<faceList>& faces,
                List<pointField>& points,
                List<labelList>& tgtFaceIDs
            );

            void distributeAndMergePatches
            (
                const mapDistribute& map,
                const primitivePatch& tgtPatch,
                const globalIndex& gi,
                faceList& tgtFaces,
                pointField& tgtPoints,
                labelList& tgtFaceIDs
            );

            autoPtr<mapDistribute> calcProcMap
            (
                const primitivePatch& srcPatch,
                const primitivePatch& tgtPatch
            );


        // Initialisation

            //- Project points to surface
            void projectPointsToSurface
            (
                const searchableSurface& surf,
                pointField& pts
            ) const;


        // Marching front

            //- Find face on target patch that overlaps source face
            label findTargetFace
            (
                const label srcFaceI,
                const primitivePatch& srcPatch
            ) const;

            //- Add faces neighbouring faceI to the ID list
            void appendNbrFaces
            (
                const label faceI,
                const primitivePatch& patch,
                const DynamicList<label>& visitedFaces,
                DynamicList<label>& faceIDs
            ) const;

            //- Set the source and target seed faces
            void setNextFaces
            (
                label& srcFaceI,
                label& tgtFaceI,
                const primitivePatch& srcPatch0,
                const primitivePatch& tgtPatch0,
                const boolList& mapFlag,
                labelList& seedFaces,
                const DynamicList<label>& visitedFaces
            );


        // Evaluation

            //- Area of intersection between source and target faces
            scalar interArea
            (
                const label srcFaceI,
                const label tgtFaceI,
                const primitivePatch& srcPatch,
                const primitivePatch& tgtPatch
            ) const;

            //- Calculate addressing
            void calcAddressing
            (
                const primitivePatch& srcPatch,
                const primitivePatch& tgtPatch,
                label srcFaceI = -1,
                label tgtFaceI = -1
            );

            //- Normalise the (area) weights - suppresses numerical error in
            //  weights calculation
            //  NOTE: if area weights are incorrect by 'a significant amount'
            //     normalisation may stabilise the solution, but will introduce
            //     numerical error!
            static void normaliseWeights
            (
                const scalarField& patchAreas,
                const word& patchName,
                const labelListList& addr,
                scalarListList& wght,
                scalarField& wghtSum,
                const bool output
            );

        // Constructor helper

            static void agglomerate
            (
                const autoPtr<mapDistribute>& targetMap,
                const scalarField& fineSrcMagSf,
                const labelListList& fineSrcAddress,
                const scalarListList& fineSrcWeights,

                const labelList& sourceRestrictAddressing,
                const labelList& targetRestrictAddressing,

                scalarField& srcMagSf,
                labelListList& srcAddress,
                scalarListList& srcWeights,
                scalarField& srcWeightsSum,
                autoPtr<mapDistribute>& tgtMap
            );

public:

    // Constructors

        //- Construct from components
        AMIInterpolation
        (
            const SourcePatch& srcPatch,
            const TargetPatch& tgtPatch,
            const faceAreaIntersect::triangulationMode& triMode,
            const bool reverseTarget = false
        );

        //- Construct from components, with projection surface
        AMIInterpolation
        (
            const SourcePatch& srcPatch,
            const TargetPatch& tgtPatch,
            const autoPtr<searchableSurface>& surf,
            const faceAreaIntersect::triangulationMode& triMode,
            const bool reverseTarget = false
        );

        //- Construct from agglomeration of AMIInterpolation. Agglomeration
        //  passed in as new coarse size and addressing from fine from coarse
        AMIInterpolation
        (
            const AMIInterpolation<SourcePatch, TargetPatch>& fineAMI,
            const labelList& sourceRestrictAddressing,
            const labelList& neighbourRestrictAddressing
        );


    //- Destructor
    ~AMIInterpolation();


    // Member Functions

        // Access

            //- Set to -1, or the processor holding all faces (both sides) of
            //  the AMI
            label singlePatchProc() const;


            // Source patch

                //- Return const access to source patch face areas
                inline const scalarField& srcMagSf() const;

                //- Return const access to source patch addressing
                inline const labelListList& srcAddress() const;

                //- Return const access to source patch weights
                inline const scalarListList& srcWeights() const;

                //- Return const access to normalisation factor of source
                //  patch weights (i.e. the sum before normalisation)
                inline const scalarField& srcWeightsSum() const;

                //- Source map pointer - valid only if singlePatchProc=-1.
                //  This gets
                //  source data into a form to be consumed by
                //  tgtAddress, tgtWeights
                inline const mapDistribute& srcMap() const;


            // Target patch

                //- Return const access to target patch face areas
                inline const scalarField& tgtMagSf() const;

                //- Return const access to target patch addressing
                inline const labelListList& tgtAddress() const;

                //- Return const access to target patch weights
                inline const scalarListList& tgtWeights() const;

                //- Return const access to normalisation factor of target
                //  patch weights (i.e. the sum before normalisation)
                inline const scalarField& tgtWeightsSum() const;

                //- Target map pointer -  valid only if singlePatchProc=-1.
                //  This gets
                //  target data into a form to be consumed by
                //  srcAddress, srcWeights
                inline const mapDistribute& tgtMap() const;


        // Manipulation

            //- Update addressing and weights
            void update
            (
                const primitivePatch& srcPatch,
                const primitivePatch& tgtPatch
            );


        // Evaluation

            // Low-level

                //- Interpolate from target to source with supplied op
                //  to combine existing value with remote value and weight
                template<class Type, class CombineOp>
                void interpolateToSource
                (
                    const UList<Type>& fld,
                    const CombineOp& bop,
                    List<Type>& result
                ) const;

                //- Interpolate from source to target with supplied op
                //  to combine existing value with remote value and weight
                template<class Type, class CombineOp>
                void interpolateToTarget
                (
                    const UList<Type>& fld,
                    const CombineOp& bop,
                    List<Type>& result
                ) const;


            //- Interpolate from target to source with supplied binary op
            template<class Type, class CombineOp>
            tmp<Field<Type> > interpolateToSource
            (
                const Field<Type>& fld,
                const CombineOp& cop
            ) const;

            //- Interpolate from target tmp field to source with supplied
            //  binary op
            template<class Type, class CombineOp>
            tmp<Field<Type> > interpolateToSource
            (
                const tmp<Field<Type> >& tFld,
                const CombineOp& cop
            ) const;

            //- Interpolate from source to target with supplied op
            template<class Type, class CombineOp>
            tmp<Field<Type> > interpolateToTarget
            (
                const Field<Type>& fld,
                const CombineOp& cop
            ) const;

            //- Interpolate from source tmp field to target with supplied op
            template<class Type, class CombineOp>
            tmp<Field<Type> > interpolateToTarget
            (
                const tmp<Field<Type> >& tFld,
                const CombineOp& cop
            ) const;

            //- Interpolate from target to source
            template<class Type>
            tmp<Field<Type> > interpolateToSource
            (
                const Field<Type>& fld
            ) const;

            //- Interpolate from target tmp field
            template<class Type>
            tmp<Field<Type> > interpolateToSource
            (
                const tmp<Field<Type> >& tFld
            ) const;

            //- Interpolate from source to target
            template<class Type>
            tmp<Field<Type> > interpolateToTarget
            (
                const Field<Type>& fld
            ) const;

            //- Interpolate from source tmp field
            template<class Type>
            tmp<Field<Type> > interpolateToTarget
            (
                const tmp<Field<Type> >& tFld
            ) const;


        // Checks

            //- Write face connectivity as OBJ file
            void writeFaceConnectivity
            (
                const primitivePatch& srcPatch,
                const primitivePatch& tgtPatch,
                const labelListList& srcAddress
            ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "OpenFOAM-2.1.x/src/meshTools/AMIInterpolation/AMIInterpolation/AMIInterpolationI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include "OpenFOAM-2.1.x/src/meshTools/AMIInterpolation/AMIInterpolation/AMIInterpolation.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
