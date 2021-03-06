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
    Foam::uniformTotalPressureFvPatchScalarField

Description
    A time-varying form of a uniform total pressure boundary condition. The
    variation is specified as an DataEntry (see Foam::DataEntry).

See Also
    Foam::uniformFixedValueFvPatchField.H
    and Foam::totalPressureFvPatchScalarField.H

SourceFiles
    uniformTotalPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#ifndef uniformTotalPressureFvPatchScalarField_H
#define uniformTotalPressureFvPatchScalarField_H

#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/basic/fixedValue/fixedValueFvPatchFields.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/interpolations/interpolationTable/interpolationTable.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/DataEntry/DataEntry.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
              Class uniformTotalPressureFvPatchField Declaration
\*---------------------------------------------------------------------------*/

class uniformTotalPressureFvPatchScalarField
:
    public fixedValueFvPatchScalarField
{
    // Private data

        //- Name of the velocity field
        word UName_;

        //- Name of the flux transporting the field
        word phiName_;

        //- Name of the density field used to normalise the mass flux
        //  if neccessary
        word rhoName_;

        //- Name of the compressibility field used to calculate the wave speed
        word psiName_;

        //- Heat capacity ratio
        scalar gamma_;

        //- Total pressure
        scalar p0_;

        //- Table of time vs total pressure, including the bounding treatment
        autoPtr<DataEntry<scalar> > pressure_;


public:

    //- Runtime type information
    TypeName("uniformTotalPressure");


    // Constructors

        //- Construct from patch and internal field
        uniformTotalPressureFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        uniformTotalPressureFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given patch field onto a new patch
        uniformTotalPressureFvPatchScalarField
        (
            const uniformTotalPressureFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        uniformTotalPressureFvPatchScalarField
        (
            const uniformTotalPressureFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new uniformTotalPressureFvPatchScalarField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        uniformTotalPressureFvPatchScalarField
        (
            const uniformTotalPressureFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new uniformTotalPressureFvPatchScalarField(*this, iF)
            );
        }


    // Member functions

        // Access

            //- Return the name of the velocity field
            const word& UName() const
            {
                return UName_;
            }

            //- Return reference to the name of the velocity field
            //  to allow adjustment
            word& UName()
            {
                return UName_;
            }

            //- Return the heat capacity ratio
            scalar gamma() const
            {
                return gamma_;
            }

            //- Return reference to the heat capacity ratio to allow adjustment
            scalar& gamma()
            {
                return gamma_;
            }

            //- Return the total pressure
            scalar p0() const
            {
                return p0_;
            }

            //- Return reference to the total pressure to allow adjustment
            scalar p0()
            {
                return p0_;
            }


        // Evaluation functions

            //- Update the coefficients associated with the patch field
            //  using the given patch velocity field
            virtual void updateCoeffs(const vectorField& Up);

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
