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
    Foam::volPointInterpolation

Description
    Interpolate from cell centres to points (vertices) using inverse distance
    weighting

SourceFiles
    volPointInterpolation.C
    volPointInterpolate.C

\*---------------------------------------------------------------------------*/

#ifndef volPointInterpolation_H
#define volPointInterpolation_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/MeshObject/MeshObject.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/lists/scalarList.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFields.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/pointFields/pointFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class fvMesh;
class pointMesh;

/*---------------------------------------------------------------------------*\
                       Class volPointInterpolation Declaration
\*---------------------------------------------------------------------------*/

class volPointInterpolation
:
    public MeshObject<fvMesh, volPointInterpolation>
{
    // Private data

        //- Interpolation scheme weighting factor array.
        scalarListList pointWeights_;


        // Boundary handling

            //- Boundary addressing
            autoPtr<primitivePatch> boundaryPtr_;

            //- Per boundary face whether is on non-coupled patch
            boolList boundaryIsPatchFace_;

            //- Per mesh(!) point whether is on non-coupled patch (on any
            //  processor)
            boolList isPatchPoint_;

            //- Per boundary point the weights per pointFaces.
            scalarListList boundaryPointWeights_;

        // Patch-patch constraints

            //- Mesh points on which to apply special constraints
            labelList patchPatchPointConstraintPoints_;
            //- Special constraints
            tensorField patchPatchPointConstraintTensors_;



    // Private Member Functions

        //- Construct addressing over all boundary faces
        void calcBoundaryAddressing();

        //- Make weights for internal and coupled-only boundarypoints
        void makeInternalWeights(scalarField& sumWeights);

        //- Make weights for points on uncoupled patches
        void makeBoundaryWeights(scalarField& sumWeights);

        //- Construct all point weighting factors
        void makeWeights();

        //- Make patch-patch constraints
        void makePatchPatchAddressing();

        //- Helper: sync data on collocated points only
        template<class Type, class CombineOp>
        void syncUntransformedData
        (
            List<Type>& pointData,
            const CombineOp& cop
        ) const;

        //- Helper: push master point data to collocated points
        template<class Type>
        void pushUntransformedData(List<Type>&) const;

        //- Get boundary field in same order as boundary faces. Field is
        //  zero on all coupled and empty patches
        template<class Type>
        tmp<Field<Type> > flatBoundaryField
        (
            const GeometricField<Type, fvPatchField, volMesh>& vf
        ) const;

        template<class Type>
        void interpolateBoundaryField
        (
            const GeometricField<Type, fvPatchField, volMesh>& vf,
            GeometricField<Type, pointPatchField, pointMesh>& pf,
            const bool overrideFixedValue
        ) const;

        template<class Type>
        void applyCornerConstraints
        (
            GeometricField<Type, pointPatchField, pointMesh>& pf
        ) const;

        //- Add separated contributions
        template<class Type>
        void addSeparated
        (
            GeometricField<Type, pointPatchField, pointMesh>&
        ) const;

        //- Disallow default bitwise copy construct
        volPointInterpolation(const volPointInterpolation&);

        //- Disallow default bitwise assignment
        void operator=(const volPointInterpolation&);


public:

    // Declare name of the class and its debug switch
    ClassName("volPointInterpolation");


    // Constructors

        //- Constructor given fvMesh and pointMesh.
        explicit volPointInterpolation(const fvMesh&);


    //- Destructor
    ~volPointInterpolation();


    // Member functions

        // Edit

            //- Update mesh topology using the morph engine
            void updateMesh();

            //- Correct weighting factors for moving mesh.
            bool movePoints();


    // Interpolation functions

        //- Interpolate internal field from volField to pointField
        //  using inverse distance weighting
        template<class Type>
        void interpolateInternalField
        (
            const GeometricField<Type, fvPatchField, volMesh>&,
            GeometricField<Type, pointPatchField, pointMesh>&
        ) const;

        //- Interpolate from volField to pointField
        //  using inverse distance weighting
        template<class Type>
        void interpolate
        (
            const GeometricField<Type, fvPatchField, volMesh>&,
            GeometricField<Type, pointPatchField, pointMesh>&
        ) const;

        //- Interpolate volField using inverse distance weighting
        //  returning pointField with the same patchField types
        template<class Type>
        tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
        (
            const GeometricField<Type, fvPatchField, volMesh>&,
            const wordList& patchFieldTypes
        ) const;

        //- Interpolate tmp<volField> using inverse distance weighting
        //  returning pointField with the same patchField types
        template<class Type>
        tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
        (
            const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
            const wordList& patchFieldTypes
        ) const;

        //- Interpolate volField using inverse distance weighting
        //  returning pointField
        template<class Type>
        tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
        (
            const GeometricField<Type, fvPatchField, volMesh>&
        ) const;

        //- Interpolate tmp<volField> using inverse distance weighting
        //  returning pointField
        template<class Type>
        tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
        (
            const tmp<GeometricField<Type, fvPatchField, volMesh> >&
        ) const;
};


template<>
void volPointInterpolation::applyCornerConstraints<scalar>
(
    GeometricField<scalar, pointPatchField, pointMesh>& pf
) const;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include "OpenFOAM-2.1.x/src/finiteVolume/interpolation/volPointInterpolation/volPointInterpolate.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
