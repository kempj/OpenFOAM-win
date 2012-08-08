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
    Foam::surfZone

Description
    A surface zone on a MeshedSurface.

    Similar in concept to a faceZone, but the face list is contiguous.

SourceFiles
    surfZone.C

\*---------------------------------------------------------------------------*/

#ifndef surfZone_H
#define surfZone_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/strings/word/word.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/ints/label/label.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/typeInfo/className.H"
#include "OpenFOAM-2.1.x/src/surfMesh/surfZone/surfZoneIdentifier/surfZoneIdentifier.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/memory/autoPtr/autoPtr.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/dictionary/dictionary.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

class surfZone;

Istream& operator>>(Istream&, surfZone&);
Ostream& operator<<(Ostream&, const surfZone&);

/*---------------------------------------------------------------------------*\
                          Class surfZone Declaration
\*---------------------------------------------------------------------------*/

class surfZone
:
    public surfZoneIdentifier
{
    // Private data

        //- size of this group in the face list
        label size_;

        //- Start label of this group in the face list
        label start_;


public:

    //- Runtime type information
    ClassName("surfZone");


    // Constructors

        //- Construct null
        surfZone();

        //- Construct from components
        surfZone
        (
            const word& name,
            const label size,
            const label start,
            const label index,
            const word& geometricType = word::null
        );

        //- Construct from Istream
        surfZone(Istream& is, const label index);

        //- Construct from dictionary
        surfZone
        (
            const word& name,
            const dictionary& dict,
            const label index
        );

        //- Construct as copy
        surfZone(const surfZone&);

        //- Construct from another zone, resetting the index
        surfZone(const surfZone&, const label index);

        //- Return clone
        autoPtr<surfZone> clone() const
        {
            notImplemented("autoPtr<surfZone> clone() const");
            return autoPtr<surfZone>(NULL);
        }

        static autoPtr<surfZone> New(Istream& is)
        {
            word name(is);
            dictionary dict(is);

            return autoPtr<surfZone>(new surfZone(name, dict, 0));
        }


    // Member Functions

        //- Return start label of this zone in the face list
        label start() const
        {
            return start_;
        }

        //- Return start label of this zone in the face list
        label& start()
        {
            return start_;
        }

        //- Return size of this zone in the face list
        label size() const
        {
            return size_;
        }

        //- Return size of this zone in the face list
        label& size()
        {
            return size_;
        }

        //- Write
        void write(Ostream&) const;

        //- Write dictionary
        void writeDict(Ostream&) const;


    // Member Operators

        bool operator!=(const surfZone&) const;

        //- compare.
        bool operator==(const surfZone&) const;


    // IOstream Operators

        friend Istream& operator>>(Istream&, surfZone&);
        friend Ostream& operator<<(Ostream&, const surfZone&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
