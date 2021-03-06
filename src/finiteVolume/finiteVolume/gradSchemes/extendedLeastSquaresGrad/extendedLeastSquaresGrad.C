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

#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/gradSchemes/extendedLeastSquaresGrad/extendedLeastSquaresGrad.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/gradSchemes/extendedLeastSquaresGrad/extendedLeastSquaresVectors.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/gradSchemes/gaussGrad/gaussGrad.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/volMesh/volMesh.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/surfaceMesh/surfaceMesh.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/GeometricField/GeometricField.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/basic/zeroGradient/zeroGradientFvPatchField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

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
Foam::fv::extendedLeastSquaresGrad<Type>::calcGrad
(
    const GeometricField<Type, fvPatchField, volMesh>& vsf,
    const word& name
) const
{
    typedef typename outerProduct<vector, Type>::type GradType;

    const fvMesh& mesh = vsf.mesh();

    tmp<GeometricField<GradType, fvPatchField, volMesh> > tlsGrad
    (
        new GeometricField<GradType, fvPatchField, volMesh>
        (
            IOobject
            (
                name,
                vsf.instance(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensioned<GradType>
            (
                "zero",
                vsf.dimensions()/dimLength,
                pTraits<GradType>::zero
            ),
            zeroGradientFvPatchField<GradType>::typeName
        )
    );
    GeometricField<GradType, fvPatchField, volMesh>& lsGrad = tlsGrad();

    // Get reference to least square vectors
    const extendedLeastSquaresVectors& lsv = extendedLeastSquaresVectors::New
    (
        mesh,
        minDet_
    );

    const surfaceVectorField& ownLs = lsv.pVectors();
    const surfaceVectorField& neiLs = lsv.nVectors();

    const labelUList& owner = mesh.owner();
    const labelUList& neighbour = mesh.neighbour();

    forAll(owner, facei)
    {
        label own = owner[facei];
        label nei = neighbour[facei];

        Type deltaVsf = vsf[nei] - vsf[own];

        lsGrad[own] += ownLs[facei]*deltaVsf;
        lsGrad[nei] -= neiLs[facei]*deltaVsf;
    }

    // Boundary faces
    forAll(vsf.boundaryField(), patchi)
    {
        const fvsPatchVectorField& patchOwnLs = ownLs.boundaryField()[patchi];

        const labelUList& faceCells =
            lsGrad.boundaryField()[patchi].patch().faceCells();

        if (vsf.boundaryField()[patchi].coupled())
        {
            const Field<Type> neiVsf
            (
                vsf.boundaryField()[patchi].patchNeighbourField()
            );

            forAll(neiVsf, patchFaceI)
            {
                lsGrad[faceCells[patchFaceI]] +=
                    patchOwnLs[patchFaceI]
                   *(neiVsf[patchFaceI] - vsf[faceCells[patchFaceI]]);
            }
        }
        else
        {
            const fvPatchField<Type>& patchVsf = vsf.boundaryField()[patchi];

            forAll(patchVsf, patchFaceI)
            {
                lsGrad[faceCells[patchFaceI]] +=
                     patchOwnLs[patchFaceI]
                    *(patchVsf[patchFaceI] - vsf[faceCells[patchFaceI]]);
            }
        }
    }


    const List<labelPair>& additionalCells = lsv.additionalCells();
    const vectorField& additionalVectors = lsv.additionalVectors();

    forAll(additionalCells, i)
    {
        lsGrad[additionalCells[i][0]] +=
            additionalVectors[i]
           *(vsf[additionalCells[i][1]] - vsf[additionalCells[i][0]]);
    }


    lsGrad.correctBoundaryConditions();
    gaussGrad<Type>::correctBoundaryConditions(vsf, lsGrad);

    return tlsGrad;
}


// ************************************************************************* //
