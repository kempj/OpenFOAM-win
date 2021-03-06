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

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/fv/fv.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/objectRegistry/objectRegistry.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/matrices/solution/solution.H"

#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/gradSchemes/gradScheme/gradScheme.H"//JK

// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class Type>
Foam::tmp<Foam::fv::gradScheme<Type> > Foam::fv::gradScheme<Type>::New
(
    const fvMesh& mesh,
    Istream& schemeData
)
{
    if (fv::debug)
    {
        Info<< "gradScheme<Type>::New"
               "(const fvMesh& mesh, Istream& schemeData) : "
               "constructing gradScheme<Type>"
            << endl;
    }

    if (schemeData.eof())
    {
        FatalIOErrorIn
        (
            "gradScheme<Type>::New"
            "(const fvMesh& mesh, Istream& schemeData)",
            schemeData
        )   << "Grad scheme not specified" << endl << endl
            << "Valid grad schemes are :" << endl
            << IstreamConstructorTablePtr_->sortedToc()
            << exit(FatalIOError);
    }

    const word schemeName(schemeData);

    typename IstreamConstructorTable::iterator cstrIter =
        IstreamConstructorTablePtr_->find(schemeName);

    if (cstrIter == IstreamConstructorTablePtr_->end())
    {
        FatalIOErrorIn
        (
            "gradScheme<Type>::New"
            "(const fvMesh& mesh, Istream& schemeData)",
            schemeData
        )   << "Unknown grad scheme " << schemeName << nl << nl
            << "Valid grad schemes are :" << endl
            << IstreamConstructorTablePtr_->sortedToc()
            << exit(FatalIOError);
    }

    return cstrIter()(mesh, schemeData);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
Foam::fv::gradScheme<Type>::~gradScheme()
{}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    template<class Type>
    inline void cachePrintMessage
    (
        const char* message,
        const word& name,
        const GeometricField<Type, fvPatchField, volMesh>& vf
    )
    {
        if (solution::debug)
        {
            Info<< "Cache: " << message << token::SPACE << name
                << ", " << vf.name() << " event No. " << vf.eventNo()
                << endl;
        }
    }
}

template<class Type>
Foam::tmp
<
    Foam::GeometricField
    <
        typename Foam::outerProduct<Foam::vector, Type>::type,
        Foam::fvPatchField,
        Foam::volMesh
    >
>
Foam::fv::gradScheme<Type>::grad
(
    const GeometricField<Type, fvPatchField, volMesh>& vsf,
    const word& name
) const
{
    typedef typename outerProduct<vector, Type>::type GradType;
    typedef GeometricField<GradType, fvPatchField, volMesh> GradFieldType;

    if (!this->mesh().changing() && this->mesh().cache(name))
    {
        if (!mesh().objectRegistry::template foundObject<GradFieldType>(name))
        {
            cachePrintMessage("Calculating and caching", name, vsf);
            tmp<GradFieldType> tgGrad = calcGrad(vsf, name);
            regIOobject::store(tgGrad.ptr());
        }

        cachePrintMessage("Retrieving", name, vsf);
        GradFieldType& gGrad = const_cast<GradFieldType&>
        (
            mesh().objectRegistry::template lookupObject<GradFieldType>(name)
        );

        if (gGrad.upToDate(vsf))
        {
            return gGrad;
        }
        else
        {
            cachePrintMessage("Deleting", name, vsf);
            gGrad.release();
            delete &gGrad;

            cachePrintMessage("Recalculating", name, vsf);
            tmp<GradFieldType> tgGrad = calcGrad(vsf, name);

            cachePrintMessage("Storing", name, vsf);
            regIOobject::store(tgGrad.ptr());
            GradFieldType& gGrad = const_cast<GradFieldType&>
            (
                mesh().objectRegistry::template lookupObject<GradFieldType>
                (
                    name
                )
            );

            return gGrad;
        }
    }
    else
    {
        if (mesh().objectRegistry::template foundObject<GradFieldType>(name))
        {
            GradFieldType& gGrad = const_cast<GradFieldType&>
            (
                mesh().objectRegistry::template lookupObject<GradFieldType>
                (
                    name
                )
            );

            if (gGrad.ownedByRegistry())
            {
                cachePrintMessage("Deleting", name, vsf);
                gGrad.release();
                delete &gGrad;
            }
        }

        cachePrintMessage("Calculating", name, vsf);
        return calcGrad(vsf, name);
    }
}


template<class Type>
Foam::tmp
<
    Foam::GeometricField
    <
        typename Foam::outerProduct<Foam::vector, Type>::type,
        Foam::fvPatchField,
        Foam::volMesh
    >
>
Foam::fv::gradScheme<Type>::grad
(
    const GeometricField<Type, fvPatchField, volMesh>& vsf
) const
{
    return grad(vsf, "grad(" + vsf.name() + ')');
}


template<class Type>
Foam::tmp
<
    Foam::GeometricField
    <
        typename Foam::outerProduct<Foam::vector, Type>::type,
        Foam::fvPatchField,
        Foam::volMesh
    >
>
Foam::fv::gradScheme<Type>::grad
(
    const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvsf
) const
{
    typedef typename outerProduct<vector, Type>::type GradType;
    typedef GeometricField<GradType, fvPatchField, volMesh> GradFieldType;

    tmp<GradFieldType> tgrad = grad(tvsf());
    tvsf.clear();
    return tgrad;
}


// ************************************************************************* //
