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
    Foam::pressureInletOutletVelocityFvPatchVectorField

Description
    Velocity inlet/outlet boundary condition patches for where the pressure is
    specified.  zero-gradient is applied for outflow (as defined by the flux)
    and for inflow the velocity is obtained from the patch-face normal
    component of the internal-cell value.

SourceFiles
    pressureInletOutletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef pressureInletOutletVelocityFvPatchVectorField_H
#define pressureInletOutletVelocityFvPatchVectorField_H

#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/fvPatchField/fvPatchFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/basic/directionMixed/directionMixedFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
              Class pressureInletOutletVelocityFvPatch Declaration
\*---------------------------------------------------------------------------*/

class pressureInletOutletVelocityFvPatchVectorField
:
    public directionMixedFvPatchVectorField
{
    // Private data

        word phiName_;

        //- Optional tangential velocity component
        vectorField tangentialVelocity_;


public:

    //- Runtime type information
    TypeName("pressureInletOutletVelocity");


    // Constructors

        //- Construct from patch and internal field
        pressureInletOutletVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        pressureInletOutletVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  pressureInletOutletVelocityFvPatchVectorField onto a new patch
        pressureInletOutletVelocityFvPatchVectorField
        (
            const pressureInletOutletVelocityFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        pressureInletOutletVelocityFvPatchVectorField
        (
            const pressureInletOutletVelocityFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new pressureInletOutletVelocityFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        pressureInletOutletVelocityFvPatchVectorField
        (
            const pressureInletOutletVelocityFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
            (
                new pressureInletOutletVelocityFvPatchVectorField(*this, iF)
            );
        }


    // Member functions

        // Access

            //- Return the name of phi
            const word& phiName() const
            {
                return phiName_;
            }

            //- Return reference to the name of phi to allow adjustment
            word& phiName()
            {
                return phiName_;
            }

            //- Return the tangential velocity
            const vectorField& tangentialVelocity() const
            {
                return tangentialVelocity_;
            }

            //- Reset the tangential velocity
            void setTangentialVelocity(const vectorField& tangentialVelocity);


        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const fvPatchFieldMapper&
            );

            //- Reverse map the given fvPatchField onto this fvPatchField
            virtual void rmap
            (
                const fvPatchVectorField&,
                const labelList&
            );


        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;


    // Member operators

        virtual void operator=(const fvPatchField<vector>& pvf);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
