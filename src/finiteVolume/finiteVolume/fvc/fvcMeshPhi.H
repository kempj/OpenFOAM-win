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
    Calculate the mesh motion flux and convert fluxes from absolute to relative
    and back.

SourceFiles
    fvcMeshPhi.C

\*---------------------------------------------------------------------------*/


#ifndef fvcMeshPhi_H
#define fvcMeshPhi_H

#include "OpenFOAM-2.1.x/src/finiteVolume/fields/volFields/volFieldsFwd.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/surfaceFields/surfaceFieldsFwd.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/dimensionedTypes/dimensionedTypes.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
	template<class T> class tmp;//JK

/*---------------------------------------------------------------------------*\
                     Namespace fvc functions Declaration
\*---------------------------------------------------------------------------*/

namespace fvc
{
    tmp<surfaceScalarField> meshPhi
    (
        const volVectorField& U
    );

    tmp<surfaceScalarField> meshPhi
    (
        const dimensionedScalar& rho,
        const volVectorField& U
    );

    tmp<surfaceScalarField> meshPhi
    (
        const volScalarField& rho,
        const volVectorField& U
    );


    //- Make the given flux relative
    void makeRelative
    (
        surfaceScalarField& phi,
        const volVectorField& U
    );

    //- Make the given flux relative
    void makeRelative
    (
        surfaceScalarField& phi,
        const dimensionedScalar& rho,
        const volVectorField& U
    );

    //- Make the given flux relative
    void makeRelative
    (
        surfaceScalarField& phi,
        const volScalarField& rho,
        const volVectorField& U
    );


    //- Make the given flux absolute
    void makeAbsolute
    (
        surfaceScalarField& phi,
        const volVectorField& U
    );

    //- Make the given flux absolute
    void makeAbsolute
    (
        surfaceScalarField& phi,
        const dimensionedScalar& rho,
        const volVectorField& U
    );

    //- Make the given flux absolute
    void makeAbsolute
    (
        surfaceScalarField& phi,
        const volScalarField& rho,
        const volVectorField& U
    );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
