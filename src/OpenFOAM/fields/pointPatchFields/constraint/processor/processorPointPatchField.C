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

#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/pointPatchFields/constraint/processor/processorPointPatchField.H"
//#include "transformField.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/polyMesh/polyPatches/constraint/processor/processorPolyPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Type>
processorPointPatchField<Type>::processorPointPatchField
(
    const pointPatch& p,
    const DimensionedField<Type, pointMesh>& iF
)
:
    coupledPointPatchField<Type>(p, iF),
    procPatch_(refCast<const processorPointPatch>(p))
{}


template<class Type>
processorPointPatchField<Type>::processorPointPatchField
(
    const pointPatch& p,
    const DimensionedField<Type, pointMesh>& iF,
    const dictionary& dict
)
:
    coupledPointPatchField<Type>(p, iF, dict),
    procPatch_(refCast<const processorPointPatch>(p))
{}


template<class Type>
processorPointPatchField<Type>::processorPointPatchField
(
    const processorPointPatchField<Type>& ptf,
    const pointPatch& p,
    const DimensionedField<Type, pointMesh>& iF,
    const pointPatchFieldMapper& mapper
)
:
    coupledPointPatchField<Type>(ptf, p, iF, mapper),
    procPatch_(refCast<const processorPointPatch>(ptf.patch()))
{}


template<class Type>
processorPointPatchField<Type>::processorPointPatchField
(
    const processorPointPatchField<Type>& ptf,
    const DimensionedField<Type, pointMesh>& iF
)
:
    coupledPointPatchField<Type>(ptf, iF),
    procPatch_(refCast<const processorPointPatch>(ptf.patch()))
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class Type>
processorPointPatchField<Type>::~processorPointPatchField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void processorPointPatchField<Type>::initSwapAddSeparated
(
    const Pstream::commsTypes commsType,
    Field<Type>& pField
)
const
{
//    if (Pstream::parRun())
//    {
//        // Get internal field into correct order for opposite side
//        Field<Type> pf
//        (
//            this->patchInternalField
//            (
//                pField,
//                procPatch_.reverseMeshPoints()
//            )
//        );
//
//        OPstream::write
//        (
//            commsType,
//            procPatch_.neighbProcNo(),
//            reinterpret_cast<const char*>(pf.begin()),
//            pf.byteSize(),
//            procPatch_.tag()
//        );
//    }
}


template<class Type>
void processorPointPatchField<Type>::swapAddSeparated
(
    const Pstream::commsTypes commsType,
    Field<Type>& pField
) const
{
//    if (Pstream::parRun())
//    {
//        Field<Type> pnf(this->size());
//
//        IPstream::read
//        (
//            commsType,
//            procPatch_.neighbProcNo(),
//            reinterpret_cast<char*>(pnf.begin()),
//            pnf.byteSize(),
//            procPatch_.tag()
//        );
//
//        if (doTransform())
//        {
//            const processorPolyPatch& ppp = procPatch_.procPolyPatch();
//            const tensor& forwardT = ppp.forwardT();
//
//            transform(pnf, forwardT, pnf);
//        }
//
//        addToInternalField(pField, pnf, procPatch_.separatedPoints());
//    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
