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

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/finiteVolume/cfdTools/general/MRF/MRFZones.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/Time/Time.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTemplateTypeNameAndDebug(IOPtrList<MRFZone>, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::MRFZones::MRFZones(const fvMesh& mesh)
:
    IOPtrList<MRFZone>
    (
        IOobject
        (
            "MRFZones",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        ),
        MRFZone::iNew(mesh)
    ),
    mesh_(mesh)
{
    if
    (
        Pstream::parRun()
     &&
     (
        regIOobject::fileModificationChecking == timeStampMaster
     || regIOobject::fileModificationChecking == inotifyMaster
     )
    )
    {
        WarningIn("MRFZones(const fvMesh&)")
            << "The MRFZones are not run time modifiable\n"
            << "    using 'timeStampMaster' or 'inotifyMaster'\n"
            << "    for the entry fileModificationChecking\n"
            << "    in the etc/controlDict.\n"
            << "    Use 'timeStamp' instead."
            << endl;
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::MRFZones::addCoriolis
(
    const volVectorField& U,
    volVectorField& ddtU
) const
{
    forAll(*this, i)
    {
        operator[](i).addCoriolis(U, ddtU);
    }
}


void Foam::MRFZones::addCoriolis(fvVectorMatrix& UEqn) const
{
    forAll(*this, i)
    {
        operator[](i).addCoriolis(UEqn);
    }
}


void Foam::MRFZones::addCoriolis
(
    const volScalarField& rho,
    fvVectorMatrix& UEqn
) const
{
    forAll(*this, i)
    {
        operator[](i).addCoriolis(rho, UEqn);
    }
}


void Foam::MRFZones::relativeVelocity(volVectorField& U) const
{
    forAll(*this, i)
    {
        operator[](i).relativeVelocity(U);
    }
}


void Foam::MRFZones::absoluteVelocity(volVectorField& U) const
{
    forAll(*this, i)
    {
        operator[](i).absoluteVelocity(U);
    }
}


void Foam::MRFZones::relativeFlux(surfaceScalarField& phi) const
{
    forAll(*this, i)
    {
        operator[](i).relativeFlux(phi);
    }
}


void Foam::MRFZones::relativeFlux
(
    const surfaceScalarField& rho,
    surfaceScalarField& phi
) const
{
    forAll(*this, i)
    {
        operator[](i).relativeFlux(rho, phi);
    }
}


void Foam::MRFZones::absoluteFlux(surfaceScalarField& phi) const
{
    forAll(*this, i)
    {
        operator[](i).absoluteFlux(phi);
    }
}


void Foam::MRFZones::absoluteFlux
(
    const surfaceScalarField& rho,
    surfaceScalarField& phi
) const
{
    forAll(*this, i)
    {
        operator[](i).absoluteFlux(rho, phi);
    }
}


void Foam::MRFZones::correctBoundaryVelocity(volVectorField& U) const
{
    forAll(*this, i)
    {
        operator[](i).correctBoundaryVelocity(U);
    }
}


bool Foam::MRFZones::readData(Istream& is)
{
    PtrList<MRFZone>::read(is, MRFZone::iNew(mesh_));
    return is.good();
}

// ************************************************************************* //
