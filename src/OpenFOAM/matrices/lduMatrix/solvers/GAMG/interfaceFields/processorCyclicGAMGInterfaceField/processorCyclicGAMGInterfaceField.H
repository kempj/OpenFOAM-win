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
    Foam::processorCyclicGAMGInterfaceField

Description
    GAMG agglomerated processor interface field.

SourceFiles
    processorCyclicGAMGInterfaceField.C

\*---------------------------------------------------------------------------*/

#ifndef processorCyclicGAMGInterfaceField_H
#define processorCyclicGAMGInterfaceField_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/matrices/lduMatrix/solvers/GAMG/interfaceFields/processorGAMGInterfaceField/processorGAMGInterfaceField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
               Class processorCyclicGAMGInterfaceField Declaration
\*---------------------------------------------------------------------------*/

class processorCyclicGAMGInterfaceField
:
    public processorGAMGInterfaceField
{
    // Private data

//        //- Local reference cast into the processor interface
//        const processorCyclicGAMGInterface& procInterface_;
//
//        //- Is the transform required
//        bool doTransform_;
//
//        //- Rank of component for transformation
//        int rank_;
//

    // Private Member Functions

        //- Disallow default bitwise copy construct
        processorCyclicGAMGInterfaceField
        (
            const processorCyclicGAMGInterfaceField&
        );

        //- Disallow default bitwise assignment
        void operator=(const processorCyclicGAMGInterfaceField&);


public:

    //- Runtime type information
    TypeName("processorCyclic");


    // Constructors

        //- Construct from GAMG interface and fine level interface field
        processorCyclicGAMGInterfaceField
        (
            const GAMGInterface& GAMGCp,
            const lduInterfaceField& fineInterface
        );


    // Destructor

        virtual ~processorCyclicGAMGInterfaceField();


    // Member Functions

//        // Access
//
//            //- Return size
//            label size() const
//            {
//                return procInterface_.size();
//            }
//
//
//        // Interface matrix update
//
//            //- Initialise neighbour matrix update
//            virtual void initInterfaceMatrixUpdate
//            (
//                const scalarField& psiInternal,
//                scalarField& result,
//                const lduMatrix& m,
//                const scalarField& coeffs,
//                const direction cmpt,
//                const Pstream::commsTypes commsType
//            ) const;
//
//            //- Update result field based on interface functionality
//            virtual void updateInterfaceMatrix
//            (
//                const scalarField& psiInternal,
//                scalarField& result,
//                const lduMatrix&,
//                const scalarField& coeffs,
//                const direction cmpt,
//                const Pstream::commsTypes commsType
//            ) const;
//
//
//        //- Processor interface functions
//
//            //- Return processor number
//            virtual int myProcNo() const
//            {
//                return procInterface_.myProcNo();
//            }
//
//            //- Return neigbour processor number
//            virtual int neighbProcNo() const
//            {
//                return procInterface_.neighbProcNo();
//            }
//
//            //- Does the interface field perform the transfromation
//            virtual bool doTransform() const
//            {
//                return doTransform_;
//            }
//
//            //- Return face transformation tensor
//            virtual const tensorField& forwardT() const
//            {
//                return procInterface_.forwardT();
//            }
//
//            //- Return rank of component for transform
//            virtual int rank() const
//            {
//                return rank_;
//            }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
