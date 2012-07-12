#ifndef curveTools_H
#define curveTools_H

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Scalar/scalar/scalar.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/Vector/vector/vector.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/graph/curve/curve.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

#define curveSmall 1.0e-8
#define curveGreat 1.0e8

#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/chars/char/char.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/containers/Lists/List/List.H"

typedef List<char> charList;
typedef List<charList> charListList;


scalar distance(const vector&, const vector&);


bool stepForwardsToNextPoint
(
    const vector&,
    vector&,
    label&,
    label&,
    scalar,
    const curve&
);


bool stepBackwardsToNextPoint
(
    const vector&,
    vector&,
    label&,
    label&,
    scalar,
    const curve&
);


bool interpolate
(
    const vector&,
    const vector&,
    const vector&,
    vector&,
    scalar
);


bool XstepForwardsToNextPoint
(
    const vector&,
    vector&,
    label&,
    label&,
    scalar,
    const curve&
);


bool Xinterpolate
(
    const vector&,
    const vector&,
    const vector&,
    vector&,
    scalar
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

#endif
