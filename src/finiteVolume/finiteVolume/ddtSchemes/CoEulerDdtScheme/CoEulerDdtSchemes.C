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

#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/ddtSchemes/CoEulerDdtScheme/CoEulerDdtScheme.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/GeometricFields/GeometricField/GeometricField.H"//JK
#include "OpenFOAM-2.1.x/src/finiteVolume/surfaceMesh/surfaceMesh.H"//JK

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace fv
{
    makeFvDdtScheme(CoEulerDdtScheme)


/*
defineNamedTemplateTypeNameAndDebug(CoEulerDdtScheme<scalar>, 0);    

ddtScheme<scalar>::addIstreamConstructorToTable<CoEulerDdtScheme<scalar> >      
	addCoEulerDdtSchemescalarIstreamConstructorToTable_;

//makeFvDdtTypeScheme(CoEulerDdtScheme, vector)                
	defineNamedTemplateTypeNameAndDebug(CoEulerDdtScheme<vector>, 0);                   
ddtScheme<vector>::addIstreamConstructorToTable<CoEulerDdtScheme<vector> >      
	addCoEulerDdtSchemevectorIstreamConstructorToTable_;

//makeFvDdtTypeScheme(CoEulerDdtScheme, sphericalTensor)                
	defineNamedTemplateTypeNameAndDebug(CoEulerDdtScheme<sphericalTensor>, 0);                   
ddtScheme<sphericalTensor>::addIstreamConstructorToTable<CoEulerDdtScheme<sphericalTensor> >      
	addCoEulerDdtSchemesphericalTensorIstreamConstructorToTable_;

//makeFvDdtTypeScheme(CoEulerDdtScheme, symmTensor)                     
	defineNamedTemplateTypeNameAndDebug(CoEulerDdtScheme<symmTensor>, 0);                   
ddtScheme<symmTensor>::addIstreamConstructorToTable<CoEulerDdtScheme<symmTensor> >      
	addCoEulerDdtSchemesymmTensorIstreamConstructorToTable_;

//makeFvDdtTypeScheme(CoEulerDdtScheme, tensor)                  
	defineNamedTemplateTypeNameAndDebug(CoEulerDdtScheme<tensor>, 0);                   
ddtScheme<tensor>::addIstreamConstructorToTable<CoEulerDdtScheme<tensor> >      
	addCoEulerDdtSchemetensorIstreamConstructorToTable_;
                                                                               
template<>                                                                     
tmp<surfaceScalarField> CoEulerDdtScheme<scalar>::fvcDdtPhiCorr                              
(                                                                              
    const volScalarField& rA,                                                  
    const volScalarField& U,                                                   
    const surfaceScalarField& phi                                              
)                                                                              
{                                                                              
    notImplemented("CoEulerDdtScheme<scalar>::fvcDdtPhiCorr");                              
    return surfaceScalarField::null();                                         
}                                                                              
                                                                               
template<>                                                                     
tmp<surfaceScalarField> CoEulerDdtScheme<scalar>::fvcDdtPhiCorr                              
(                                                                              
    const volScalarField& rA,                                                  
    const volScalarField& rho,                                                 
    const volScalarField& U,                                                   
    const surfaceScalarField& phi                                              
)                                                                              
{                                                                              
    notImplemented("CoEulerDdtScheme<scalar>::fvcDdtPhiCorr");                              
    return surfaceScalarField::null();                                         
}*/

}
}

// ************************************************************************* //
