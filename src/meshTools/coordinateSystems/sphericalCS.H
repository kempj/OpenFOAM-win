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
    Foam::sphericalCS

Description
    Spherical coordinate system

SourceFiles
    sphericalCS.C

\*---------------------------------------------------------------------------*/

#ifndef sphericalCS_H
#define sphericalCS_H

#include "OpenFOAM-2.1.x/src/meshTools/coordinateSystems/coordinateSystem.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class sphericalCS Declaration
\*---------------------------------------------------------------------------*/

class sphericalCS
:
    public coordinateSystem
{
    // Private data members

        //- Are angles in degrees? (default = true)
        bool inDegrees_;


protected:

    // Protected Member Functions

        //- Convert from local coordinate system to the global Cartesian system
        //  with optional translation for the origin
        virtual vector localToGlobal(const vector&, bool translate) const;

        //- Convert from local coordinate system to the global Cartesian system
        //  with optional translation for the origin
        virtual tmp<vectorField> localToGlobal
        (
            const vectorField&,
            bool translate
        ) const;

        //- Convert from global Cartesian system to the local coordinate system
        //  with optional translation for the origin
        virtual vector globalToLocal(const vector&, bool translate) const;

        //- Convert from global Cartesian system to the local coordinate system
        //  with optional translation for the origin
        virtual tmp<vectorField> globalToLocal
        (
            const vectorField&,
            bool translate
        ) const;


public:

    //- Runtime type information
    TypeName("spherical");


    // Constructors

        //- Construct null
        sphericalCS(const bool inDegrees=true);

        //- Construct copy
        sphericalCS
        (
            const coordinateSystem&,
            const bool inDegrees=true
        );

        //- Construct copy with a different name
        sphericalCS
        (
            const word& name,
            const coordinateSystem&,
            const bool inDegrees=true
        );

        //- Construct from origin and rotation
        sphericalCS
        (
            const word& name,
            const point& origin,
            const coordinateRotation&,
            const bool inDegrees=true
        );

        //- Construct from origin and 2 axes
        sphericalCS
        (
            const word& name,
            const point& origin,
            const vector& axis,
            const vector& dirn,
            const bool inDegrees=true
        );

        //- Construct from dictionary
        sphericalCS(const word& name, const dictionary&);


    // Member Functions

        //- Are angles in degrees?
        bool  inDegrees() const;

        //- Non-const access to inDegrees
        bool& inDegrees();
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
