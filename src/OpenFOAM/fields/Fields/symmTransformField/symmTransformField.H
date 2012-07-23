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

Typedef
    Foam::symmTransformField

Description
    Spatial transformation functions for primitive fields.

SourceFiles
    symmTransformField.C

\*---------------------------------------------------------------------------*/

#ifndef symmTransformField_H
#define symmTransformField_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/transform/symmTransform.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/Fields/symmTensorField/symmTensorField.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/SphericalTensor/sphericalTensor/sphericalTensor.H"
//#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/Fields/transformField/transformField.H"//JK

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void transform(Field<Type>&, const symmTensorField&, const Field<Type>&);

template<class Type>
tmp<Field<Type> > transform(const symmTensorField&, const Field<Type>&);

template<class Type>
tmp<Field<Type> > transform(const symmTensorField&, const tmp<Field<Type> >&);

template<class Type>
tmp<Field<Type> > transform(const tmp<symmTensorField>&, const Field<Type>&);

template<class Type>
tmp<Field<Type> > transform
(
    const tmp<symmTensorField>&,
    const tmp<Field<Type> >&
);


template<class Type>
void transform(Field<Type>&, const tensor&, const Field<Type>&);

template<class Type>
tmp<Field<Type> > transform(const tensor&, const Field<Type>&);

template<class Type>
tmp<Field<Type> > transform(const tensor&, const tmp<Field<Type> >&);

template<class Type1, class Type2>
tmp<Field<Type1> > transformFieldMask(const Field<Type2>&);//JK

template<class Type1, class Type2>
tmp<Field<Type1> > transformFieldMask(const tmp<Field<Type2> >&);//JK

template<>
tmp<Field<sphericalTensor> > transformFieldMask<sphericalTensor>
(
    const symmTensorField&
);

template<>
tmp<Field<sphericalTensor> > transformFieldMask<sphericalTensor>
(
    const tmp<symmTensorField>&
);


template<>
tmp<Field<symmTensor> > transformFieldMask<symmTensor>
(
    const symmTensorField&
);

template<>
tmp<Field<symmTensor> > transformFieldMask<symmTensor>
(
    const tmp<symmTensorField>&
);


template<>
tmp<Field<tensor> > transformFieldMask<tensor>
(
    const symmTensorField&
);

template<>
tmp<Field<tensor> > transformFieldMask<tensor>
(
    const tmp<symmTensorField>&
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/Fields/symmTransformField/symmTransformField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
