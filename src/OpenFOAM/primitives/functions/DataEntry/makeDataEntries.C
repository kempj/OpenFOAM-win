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

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/CompatibilityConstant/CompatibilityConstant.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/Constant/Constant.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/CSV/CSV.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/DataEntry/DataEntry.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/Table/Table.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/functions/DataEntry/TableFile/TableFile.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/ints/label/label.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/scalar/scalar.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Vector/vector/vector.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/SphericalTensor/sphericalTensor/sphericalTensor.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/SymmTensor/symmTensor/symmTensor.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Tensor/tensor/tensor.H"

namespace Foam
{
    makeDataEntry(label);
    makeDataEntryType(CompatibilityConstant, label);
    makeDataEntryType(Constant, label);
//    makeDataEntryType(CSV, label);
    makeDataEntryType(Table, label);
    makeDataEntryType(TableFile, label);

    makeDataEntry(scalar);
    makeDataEntryType(CompatibilityConstant, scalar);
    makeDataEntryType(Constant, scalar);
    makeDataEntryType(CSV, scalar);
    makeDataEntryType(Table, scalar);
    makeDataEntryType(TableFile, scalar);

    makeDataEntry(vector);
    makeDataEntryType(CompatibilityConstant, vector);
    makeDataEntryType(Constant, vector);
    makeDataEntryType(CSV, vector);
    makeDataEntryType(Table, vector);
    makeDataEntryType(TableFile, vector);

    makeDataEntry(sphericalTensor);
    makeDataEntryType(CompatibilityConstant, sphericalTensor);
    makeDataEntryType(Constant, sphericalTensor);
    makeDataEntryType(CSV, sphericalTensor);
    makeDataEntryType(Table, sphericalTensor);
    makeDataEntryType(TableFile, sphericalTensor);

    makeDataEntry(symmTensor);
    makeDataEntryType(CompatibilityConstant, symmTensor);
    makeDataEntryType(Constant, symmTensor);
    makeDataEntryType(CSV, symmTensor);
    makeDataEntryType(Table, symmTensor);
    makeDataEntryType(TableFile, symmTensor);

    makeDataEntry(tensor);
    makeDataEntryType(CompatibilityConstant, tensor);
    makeDataEntryType(Constant, tensor);
    makeDataEntryType(CSV, tensor);
    makeDataEntryType(Table, tensor);
    makeDataEntryType(TableFile, tensor);
}


// ************************************************************************* //
