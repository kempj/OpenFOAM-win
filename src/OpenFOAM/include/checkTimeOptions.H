//
// checkTimeOptions.H
// ~~~~~~~~~~~~~~~~~~

Foam::label startTime = 0;
Foam::label endTime = Times.size();

// unless -constant is present, skip startTime if it is "constant"
#include "OpenFOAM-2.1.x/src/OpenFOAM/include/checkConstantOption.H"

// check -time and -latestTime options
#include "OpenFOAM-2.1.x/src/OpenFOAM/include/checkTimeOption.H"
