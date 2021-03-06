/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 3 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*----------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/finiteVolume/cfdTools/general/fieldSources/basicSource/radialActuationDiskSource/radialActuationDiskSource.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/geometricOneField/geometricOneField.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

#include "OpenFOAM-2.1.x/src/finiteVolume/fvMatrices/fvMatrix/fvMatrix.H"//JK

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(radialActuationDiskSource, 0);
    addToRunTimeSelectionTable
    (
        basicSource,
        radialActuationDiskSource,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::radialActuationDiskSource::radialActuationDiskSource
(
    const word& name,
    const word& modelType,
    const dictionary& dict,
    const fvMesh& mesh
)
:
    actuationDiskSource(name, modelType, dict, mesh),
    radialCoeffs_(coeffs_.lookup("coeffs"))
{
    Info<< "    - creating radial actuation disk zone: " << name_ << endl;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::radialActuationDiskSource::addSup
(
    fvMatrix<vector>& eqn,
    const label fieldI
)
{
    bool compressible = false;
    if (eqn.dimensions() == dimForce)
    {
        compressible = true;
    }

    const scalarField& cellsV = mesh_.V();
    vectorField& Usource = eqn.source();
    const vectorField& U = eqn.psi();

    if (V_ > VSMALL)
    {
        if (compressible)
        {
            addRadialActuationDiskAxialInertialResistance
            (
                Usource,
                cells_,
                cellsV,
                mesh_.lookupObject<volScalarField>("rho"),
                U
            );
        }
        else
        {
            addRadialActuationDiskAxialInertialResistance
            (
                Usource,
                cells_,
                cellsV,
                geometricOneField(),
                U
            );
        }
    }
}


void Foam::radialActuationDiskSource::writeData(Ostream& os) const
{
    actuationDiskSource::writeData(os);
}


bool Foam::radialActuationDiskSource::read(const dictionary& dict)
{
    if (basicSource::read(dict))
    {
        coeffs_.readIfPresent("diskDir", diskDir_);
        coeffs_.readIfPresent("Cp", Cp_);
        coeffs_.readIfPresent("Ct", Ct_);
        coeffs_.readIfPresent("diskArea", diskArea_);
        coeffs_.lookup("coeffs") >> radialCoeffs_;
        return true;
    }
    else
    {
        return false;
    }
}


// ************************************************************************* //
