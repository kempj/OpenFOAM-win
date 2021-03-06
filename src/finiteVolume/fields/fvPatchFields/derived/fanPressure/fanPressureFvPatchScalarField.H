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
    Foam::fanPressureFvPatchScalarField

Description
    Assigns pressure inlet or outlet total pressure condition for a fan.

    User specifies:
    - pressure drop vs volumetric flow rate table (fan curve) file name;
    - direction of normal flow through the fan, in or out;
    - total pressure of the environment.

    Example of the boundary condition specification:
    \verbatim
        inlet
        {
            type            fanPressure;
            fileName        "fanCurve"; // Fan curve file name
            outOfBounds     clamp;      // (error|warn|clamp|repeat)
            direction       in;         // Direction of flow through fan
            p0              uniform 0;  // Environmental total pressure
            value           uniform 0;  // Initial pressure
        }

        outlet
        {
            type            fanPressure;
            fileName        "fanCurve"; // Fan curve file name
            outOfBounds     clamp;      // (error|warn|clamp|repeat)
            direction       out;        // Direction of flow through fan
            p0              uniform 0;  // Environmental total pressure
            value           uniform 0;  // Initial pressure
        }
    \endverbatim

See Also
    Foam::totalPressureFvPatchScalarField and
    Foam::interpolationTable

SourceFiles
    fanPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#ifndef fanPressureFvPatchScalarField_H
#define fanPressureFvPatchScalarField_H

#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/derived/totalPressure/totalPressureFvPatchScalarField.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/interpolations/interpolationTable/interpolationTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
              Class fanPressureFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class fanPressureFvPatchScalarField
:
    public totalPressureFvPatchScalarField
{

public:

        //- Fan flow direction
        enum fanFlowDirection
        {
            ffdIn,
            ffdOut
        };

        static const NamedEnum<fanFlowDirection, 2> fanFlowDirectionNames_;

private:

    // Private data

        //- Tabulated fan curve
        interpolationTable<scalar> fanCurve_;

        //- Direction of flow through the fan relative to patch
        fanFlowDirection direction_;


public:

    //- Runtime type information
    TypeName("fanPressure");


    // Constructors

        //- Construct from patch and internal field
        fanPressureFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        fanPressureFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  fanPressureFvPatchScalarField
        //  onto a new patch
        fanPressureFvPatchScalarField
        (
            const fanPressureFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        fanPressureFvPatchScalarField
        (
            const fanPressureFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new fanPressureFvPatchScalarField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        fanPressureFvPatchScalarField
        (
            const fanPressureFvPatchScalarField&,
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
                new fanPressureFvPatchScalarField
                (
                    *this,
                    iF
                )
            );
        }


    // Member functions

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
