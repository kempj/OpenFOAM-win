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
    Foam::IObasicSourceList

Description
    IObasicSourceList

SourceFiles
    IObasicSourceList.C

\*---------------------------------------------------------------------------*/

#ifndef IObasicSourceList_H
#define IObasicSourceList_H

#include "OpenFOAM-2.1.x/src/finiteVolume/cfdTools/general/fieldSources/basicSource/basicSource/basicSourceList.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOobjects/IOdictionary/IOdictionary.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/memory/autoPtr/autoPtr.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class IObasicSourceList Declaration
\*---------------------------------------------------------------------------*/

class IObasicSourceList
:
    public IOdictionary,
    public basicSourceList
{
private:

    // Private Member Functions

        //- Create IO object if dictionary is present
        IOobject createIOobject(const fvMesh& mesh) const;

        //- Disallow default bitwise copy construct
        IObasicSourceList(const IObasicSourceList&);

        //- Disallow default bitwise assignment
        void operator=(const IObasicSourceList&);


public:

    // Constructors

        //- Construct from components with list of field names
        IObasicSourceList(const fvMesh& mesh);


        //- Destructor
        virtual ~IObasicSourceList()
        {}


    // Member Functions

        //- Read dictionary
        virtual bool read();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
