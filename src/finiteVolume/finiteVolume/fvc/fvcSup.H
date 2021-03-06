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
    Calculate the field for explicit evaluation of implicit and explicit
    sources.

SourceFiles
    fvcSup.C

\*---------------------------------------------------------------------------*/

#ifndef fvcSup_H
#define fvcSup_H

#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                     Namespace fvc functions Declaration
\*---------------------------------------------------------------------------*/

namespace fvc
{
   // Explicit source

        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > Su
        (
            const GeometricField<Type, fvPatchField, volMesh>&,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > Su
        (
            const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
            GeometricField<Type, fvPatchField, volMesh>&
        );


    // Implicit source

        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > Sp
        (
            const volScalarField&,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > Sp
        (
            const tmp<volScalarField>&,
            GeometricField<Type, fvPatchField, volMesh>&
        );


        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > Sp
        (
            const dimensionedScalar&,
            GeometricField<Type, fvPatchField, volMesh>&
        );


    // Implicit/Explicit source depending on sign of coefficient

        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > SuSp
        (
            const volScalarField&,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > SuSp
        (
            const tmp<volScalarField>&,
            GeometricField<Type, fvPatchField, volMesh>&
        );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/fvc/fvcSup.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
