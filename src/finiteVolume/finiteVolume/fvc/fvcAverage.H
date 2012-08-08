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

InNamespace
    Foam::fvc

Description
    Area-weighted average a surfaceField creating a volField

SourceFiles
    fvcAverage.C

\*---------------------------------------------------------------------------*/


#ifndef fvcAverage_H
#define fvcAverage_H

#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFieldsFwd.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/surfaceFields/surfaceFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
	template<class T> class tmp;//JK
/*---------------------------------------------------------------------------*\
                     Namespace fvc functions Declaration
\*---------------------------------------------------------------------------*/

namespace fvc
{
    //- Area-weighted average a surfaceField creating a volField
    template<class Type>
    tmp<GeometricField<Type, fvPatchField, volMesh> > average
    (
        const GeometricField<Type, fvsPatchField, surfaceMesh>&
    );

    //- Area-weighted average a surfaceField creating a volField
    template<class Type>
    tmp<GeometricField<Type, fvPatchField, volMesh> > average
    (
        const tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >&
    );


    //- Area-weighted average a surfaceField creating a volField
    template<class Type>
    tmp<GeometricField<Type, fvPatchField, volMesh> > average
    (
        const GeometricField<Type, fvPatchField, volMesh>&
    );

    //- Area-weighted average a surfaceField creating a volField
    template<class Type>
    tmp<GeometricField<Type, fvPatchField, volMesh> > average
    (
        const tmp<GeometricField<Type, fvPatchField, volMesh> >&
    );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/fvc/fvcAverage.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
