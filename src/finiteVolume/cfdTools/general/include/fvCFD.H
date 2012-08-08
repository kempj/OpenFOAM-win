#ifndef fvCFD_H
#define fvCFD_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/global/argList/parRun.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/Time/Time.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMesh/fvMesh.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/fvc/fvc.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fvMatrices/fvMatrices.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/finiteVolume/fvm/fvm.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/interpolation/surfaceInterpolation/schemes/linear/linear.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/fields/UniformDimensionedFields/uniformDimensionedFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/basic/calculated/calculatedFvPatchFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/fields/fvPatchFields/basic/fixedValue/fixedValueFvPatchFields.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/cfdTools/general/adjustPhi/adjustPhi.H"
#include "OpenFOAM-2.1.x/src/finiteVolume/cfdTools/general/findRefCell/findRefCell.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/constants/constants.H"

#include "OpenFOAM-2.1.x/src/OpenFOAM/include/OSspecific.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/argList/argList.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/Time/timeSelector.H"

#ifndef namespaceFoam
#define namespaceFoam
    using namespace Foam;
#endif

#endif
