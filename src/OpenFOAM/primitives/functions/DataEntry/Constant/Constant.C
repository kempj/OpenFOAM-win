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

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/Constant/Constant.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
Foam::Constant<Type>::Constant(const word& entryName, const dictionary& dict)
:
    DataEntry<Type>(entryName),
    value_(pTraits<Type>::zero)
{
    Istream& is(dict.lookup(entryName));
    word entryType(is);

    is  >> value_;
}


template<class Type>
Foam::Constant<Type>::Constant(const Constant<Type>& cnst)
:
    DataEntry<Type>(cnst),
    value_(cnst.value_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
Foam::Constant<Type>::~Constant()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type Foam::Constant<Type>::value(const scalar x) const
{
    return value_;
}


template<class Type>
Type Foam::Constant<Type>::integrate(const scalar x1, const scalar x2) const
{
    return (x2 - x1)*value_;
}


// * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * * * //

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/Constant/ConstantIO.C"


// ************************************************************************* //
