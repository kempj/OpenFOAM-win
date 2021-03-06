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

#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvPatches/constraint/cyclicAMI/cyclicAMIFvPatch.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/runTimeSelection/construction/addToRunTimeSelectionTable.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/transform/transform.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(cyclicAMIFvPatch, 0);
    addToRunTimeSelectionTable(fvPatch, cyclicAMIFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::cyclicAMIFvPatch::makeWeights(scalarField& w) const
{
    const cyclicAMIFvPatch& nbrPatch = neighbFvPatch();

    const scalarField deltas(nf() & fvPatch::delta());

    const scalarField nbrDeltas
    (
        interpolate(nbrPatch.nf() & nbrPatch.fvPatch::delta())
    );

    forAll(deltas, faceI)
    {
        scalar di = deltas[faceI];
        scalar dni = nbrDeltas[faceI];

        w[faceI] = dni/(di + dni);
    }
}


Foam::tmp<Foam::vectorField> Foam::cyclicAMIFvPatch::delta() const
{
    const vectorField patchD(fvPatch::delta());

    const cyclicAMIFvPatch& nbrPatch = neighbFvPatch();
    const vectorField nbrPatchD(interpolate(nbrPatch.fvPatch::delta()));

    tmp<vectorField> tpdv(new vectorField(patchD.size()));
    vectorField& pdv = tpdv();

    // do the transformation if necessary
    if (parallel())
    {
        forAll(patchD, faceI)
        {
            vector ddi = patchD[faceI];
            vector dni = nbrPatchD[faceI];

            pdv[faceI] = ddi - dni;
        }
    }
    else
    {
        forAll(patchD, faceI)
        {
            vector ddi = patchD[faceI];
            vector dni = nbrPatchD[faceI];

            pdv[faceI] = ddi - transform(forwardT()[0], dni);
        }
    }

    return tpdv;
}


Foam::tmp<Foam::labelField> Foam::cyclicAMIFvPatch::interfaceInternalField
(
    const labelUList& internalData
) const
{
    return patchInternalField(internalData);
}


Foam::tmp<Foam::labelField> Foam::cyclicAMIFvPatch::internalFieldTransfer
(
    const Pstream::commsTypes commsType,
    const labelUList& iF
) const
{
    return neighbFvPatch().patchInternalField(iF);
}


// ************************************************************************* //
