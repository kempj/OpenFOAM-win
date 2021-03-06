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
    Foam::coupledFvPatchField

Description
    Foam::coupledFvPatchField

SourceFiles
    coupledFvPatchField.C

\*---------------------------------------------------------------------------*/

#ifndef coupledFvPatchField_H
#define coupledFvPatchField_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/matrices/lduMatrix/lduAddressing/lduInterfaceFields/lduInterfaceField/lduInterfaceField.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/fvPatchField/fvPatchField.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvPatches/basic/coupled/coupledFvPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class coupledFvPatch Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class coupledFvPatchField
:
    public lduInterfaceField,
    public fvPatchField<Type>
{

public:

    //- Runtime type information
    TypeName(coupledFvPatch::typeName_());


    // Constructors

        //- Construct from patch and internal field
        coupledFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct from patch and internal field and patch field
        coupledFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const Field<Type>&
        );

        //- Construct from patch, internal field and dictionary
        coupledFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping the given coupledFvPatchField onto a new patch
        coupledFvPatchField
        (
            const coupledFvPatchField<Type>&,
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        coupledFvPatchField
        (
            const coupledFvPatchField<Type>&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchField<Type> > clone() const = 0;

        //- Construct as copy setting internal field reference
        coupledFvPatchField
        (
            const coupledFvPatchField<Type>&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchField<Type> > clone
        (
            const DimensionedField<Type, volMesh>&
        ) const = 0;


    // Member functions

        // Access

            //- Return true if this patch field is derived from
            //  coupledFvPatchField<Type>.
            virtual bool coupled() const
            {
                return true;
            }

            //- Return neighbour field of internal field
            virtual tmp<Field<Type> > patchNeighbourField() const = 0;


        // Evaluation functions

            //- Return patch-normal gradient
            virtual tmp<Field<Type> > snGrad() const;

            //- Initialise the evaluation of the patch field
            virtual void initEvaluate
            (
                const Pstream::commsTypes commsType
            );

            //- Evaluate the patch field
            virtual void evaluate
            (
                const Pstream::commsTypes commsType
            );

            //- Return the matrix diagonal coefficients corresponding to the
            //  evaluation of the value of this patchField with given weights
            virtual tmp<Field<Type> > valueInternalCoeffs
            (
                const tmp<scalarField>&
            ) const;

            //- Return the matrix source coefficients corresponding to the
            //  evaluation of the value of this patchField with given weights
            virtual tmp<Field<Type> > valueBoundaryCoeffs
            (
                const tmp<scalarField>&
            ) const;

            //- Return the matrix diagonal coefficients corresponding to the
            //  evaluation of the gradient of this patchField
            virtual tmp<Field<Type> > gradientInternalCoeffs() const;

            //- Return the matrix source coefficients corresponding to the
            //  evaluation of the gradient of this patchField
            virtual tmp<Field<Type> > gradientBoundaryCoeffs() const;


        // Coupled interface functionality

            //- Update result field based on interface functionality
            virtual void updateInterfaceMatrix
            (
                const scalarField& psiInternal,
                scalarField& result,
                const lduMatrix&,
                const scalarField& coeffs,
                const direction,
                const Pstream::commsTypes commsType
            ) const = 0;

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/basic/coupled/coupledFvPatchField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
