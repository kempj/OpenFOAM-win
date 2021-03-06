/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenFOAM Foundation
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

#include "isobaricPerfectGas.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline Foam::isobaricPerfectGas::isobaricPerfectGas(const specie& sp)
:
    specie(sp)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::isobaricPerfectGas::isobaricPerfectGas
(
    const word& name,
    const isobaricPerfectGas& pg
)
:
    specie(name, pg)
{}


inline Foam::autoPtr<Foam::isobaricPerfectGas> Foam::isobaricPerfectGas::
clone() const
{
    return autoPtr<isobaricPerfectGas>(new isobaricPerfectGas(*this));
}


inline Foam::autoPtr<Foam::isobaricPerfectGas> Foam::isobaricPerfectGas::New
(
    Istream& is
)
{
    return autoPtr<isobaricPerfectGas>(new isobaricPerfectGas(is));
}


inline Foam::autoPtr<Foam::isobaricPerfectGas> Foam::isobaricPerfectGas::New
(
    const dictionary& dict
)
{
    return autoPtr<isobaricPerfectGas>(new isobaricPerfectGas(dict));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline Foam::scalar Foam::isobaricPerfectGas::rho(scalar p, scalar T) const
{
    return pRef_/(R()*T);
}


inline Foam::scalar Foam::isobaricPerfectGas::psi(scalar, scalar T) const
{
    return 0.0;
}


inline Foam::scalar Foam::isobaricPerfectGas::Z(scalar, scalar) const
{
    return 0.0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void Foam::isobaricPerfectGas::operator+=(const isobaricPerfectGas& pg)
{
    specie::operator+=(pg);
}


inline void Foam::isobaricPerfectGas::operator-=(const isobaricPerfectGas& pg)
{
    specie::operator-=(pg);
}


inline void Foam::isobaricPerfectGas::operator*=(const scalar s)
{
    specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

inline Foam::isobaricPerfectGas Foam::operator+
(
    const isobaricPerfectGas& pg1,
    const isobaricPerfectGas& pg2
)
{
    return isobaricPerfectGas
    (
        static_cast<const specie&>(pg1)
      + static_cast<const specie&>(pg2)
    );
}


inline Foam::isobaricPerfectGas Foam::operator-
(
    const isobaricPerfectGas& pg1,
    const isobaricPerfectGas& pg2
)
{
    return isobaricPerfectGas
    (
        static_cast<const specie&>(pg1)
      - static_cast<const specie&>(pg2)
    );
}


inline Foam::isobaricPerfectGas Foam::operator*
(
    const scalar s,
    const isobaricPerfectGas& pg
)
{
    return isobaricPerfectGas(s*static_cast<const specie&>(pg));
}


inline Foam::isobaricPerfectGas Foam::operator==
(
    const isobaricPerfectGas& pg1,
    const isobaricPerfectGas& pg2
)
{
    return pg2 - pg1;
}


// ************************************************************************* //
