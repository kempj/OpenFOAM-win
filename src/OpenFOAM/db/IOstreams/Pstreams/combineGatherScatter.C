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

Description
    Variant of gather, scatter.
    Normal gather uses:
    - construct null and read (>>) from Istream
    - binary operator and assignment operator to combine values

    combineGather uses:
    - construct from Istream
    - modify operator which modifies its lhs

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/Pstreams/OPstream.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/Pstreams/IPstream.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/IOstreams.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/primitives/contiguous/contiguous.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template <class T, class CombineOp>
void Pstream::combineGather
(
    const List<UPstream::commsStruct>& comms,
    T& Value,
    const CombineOp& cop,
    const int tag
)
{
    if (UPstream::parRun())
    {
        // Get my communication order
        const commsStruct& myComm = comms[UPstream::myProcNo()];

        // Receive from my downstairs neighbours
        forAll(myComm.below(), belowI)
        {
            label belowID = myComm.below()[belowI];

            if (contiguous<T>())
            {
                T value;
                UIPstream::read
                (
                    UPstream::scheduled,
                    belowID,
                    reinterpret_cast<char*>(&value),
                    sizeof(T),
                    tag
                );

                if (debug & 2)
                {
                    Pout<< " received from "
                        << belowID << " data:" << value << endl;
                }

                cop(Value, value);
            }
            else
            {
                IPstream fromBelow(UPstream::scheduled, belowID, 0, tag);
                T value(fromBelow);

                if (debug & 2)
                {
                    Pout<< " received from "
                        << belowID << " data:" << value << endl;
                }

                cop(Value, value);
            }
        }

        // Send up Value
        if (myComm.above() != -1)
        {
            if (debug & 2)
            {
                Pout<< " sending to " << myComm.above()
                    << " data:" << Value << endl;
            }

            if (contiguous<T>())
            {
                UOPstream::write
                (
                    UPstream::scheduled,
                    myComm.above(),
                    reinterpret_cast<const char*>(&Value),
                    sizeof(T),
                    tag
                );
            }
            else
            {
                OPstream toAbove(UPstream::scheduled, myComm.above(), 0, tag);
                toAbove << Value;
            }
        }
    }
}


template <class T, class CombineOp>
void Pstream::combineGather(T& Value, const CombineOp& cop, const int tag)
{
    if (UPstream::nProcs() < UPstream::nProcsSimpleSum)
    {
        combineGather(UPstream::linearCommunication(), Value, cop, tag);
    }
    else
    {
        combineGather(UPstream::treeCommunication(), Value, cop, tag);
    }
}


template <class T>
void Pstream::combineScatter
(
    const List<UPstream::commsStruct>& comms,
    T& Value,
    const int tag
)
{
    if (UPstream::parRun())
    {
        // Get my communication order
        const UPstream::commsStruct& myComm = comms[UPstream::myProcNo()];

        // Reveive from up
        if (myComm.above() != -1)
        {
            if (contiguous<T>())
            {
                UIPstream::read
                (
                    UPstream::scheduled,
                    myComm.above(),
                    reinterpret_cast<char*>(&Value),
                    sizeof(T),
                    tag
                );
            }
            else
            {
                IPstream fromAbove(UPstream::scheduled, myComm.above(), 0, tag);
                Value = T(fromAbove);
            }

            if (debug & 2)
            {
                Pout<< " received from "
                    << myComm.above() << " data:" << Value << endl;
            }
        }

        // Send to my downstairs neighbours
        forAll(myComm.below(), belowI)
        {
            label belowID = myComm.below()[belowI];

            if (debug & 2)
            {
                Pout<< " sending to " << belowID << " data:" << Value << endl;
            }

            if (contiguous<T>())
            {
                UOPstream::write
                (
                    UPstream::scheduled,
                    belowID,
                    reinterpret_cast<const char*>(&Value),
                    sizeof(T),
                    tag
                );
            }
            else
            {
                OPstream toBelow(UPstream::scheduled, belowID, 0, tag);
                toBelow << Value;
            }
        }
    }
}


template <class T>
void Pstream::combineScatter(T& Value, const int tag)
{
    if (UPstream::nProcs() < UPstream::nProcsSimpleSum)
    {
        combineScatter(UPstream::linearCommunication(), Value, tag);
    }
    else
    {
        combineScatter(UPstream::treeCommunication(), Value, tag);
    }
}


// Same thing but for whole list at a time
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


template <class T, class CombineOp>
void Pstream::listCombineGather
(
    const List<UPstream::commsStruct>& comms,
    List<T>& Values,
    const CombineOp& cop,
    const int tag
)
{
    if (UPstream::parRun())
    {
        // Get my communication order
        const commsStruct& myComm = comms[UPstream::myProcNo()];

        // Receive from my downstairs neighbours
        forAll(myComm.below(), belowI)
        {
            label belowID = myComm.below()[belowI];

            if (contiguous<T>())
            {
                List<T> receivedValues(Values.size());

                UIPstream::read
                (
                    UPstream::scheduled,
                    belowID,
                    reinterpret_cast<char*>(receivedValues.begin()),
                    receivedValues.byteSize(),
                    tag
                );

                if (debug & 2)
                {
                    Pout<< " received from "
                        << belowID << " data:" << receivedValues << endl;
                }

                forAll(Values, i)
                {
                    cop(Values[i], receivedValues[i]);
                }
            }
            else
            {
                IPstream fromBelow(UPstream::scheduled, belowID, 0, tag);
                List<T> receivedValues(fromBelow);

                if (debug & 2)
                {
                    Pout<< " received from "
                        << belowID << " data:" << receivedValues << endl;
                }

                forAll(Values, i)
                {
                    cop(Values[i], receivedValues[i]);
                }
            }
        }

        // Send up Value
        if (myComm.above() != -1)
        {
            if (debug & 2)
            {
                Pout<< " sending to " << myComm.above()
                    << " data:" << Values << endl;
            }

            if (contiguous<T>())
            {
                UOPstream::write
                (
                    UPstream::scheduled,
                    myComm.above(),
                    reinterpret_cast<const char*>(Values.begin()),
                    Values.byteSize(),
                    tag
                );
            }
            else
            {
                OPstream toAbove(UPstream::scheduled, myComm.above(), 0, tag);
                toAbove << Values;
            }
        }
    }
}


template <class T, class CombineOp>
void Pstream::listCombineGather
(
    List<T>& Values,
    const CombineOp& cop,
    const int tag
)
{
    if (UPstream::nProcs() < UPstream::nProcsSimpleSum)
    {
        listCombineGather(UPstream::linearCommunication(), Values, cop, tag);
    }
    else
    {
        listCombineGather(UPstream::treeCommunication(), Values, cop, tag);
    }
}


template <class T>
void Pstream::listCombineScatter
(
    const List<UPstream::commsStruct>& comms,
    List<T>& Values,
    const int tag
)
{
    if (UPstream::parRun())
    {
        // Get my communication order
        const UPstream::commsStruct& myComm = comms[UPstream::myProcNo()];

        // Reveive from up
        if (myComm.above() != -1)
        {
            if (contiguous<T>())
            {
                UIPstream::read
                (
                    UPstream::scheduled,
                    myComm.above(),
                    reinterpret_cast<char*>(Values.begin()),
                    Values.byteSize(),
                    tag
                );
            }
            else
            {
                IPstream fromAbove(UPstream::scheduled, myComm.above(), 0, tag);
                fromAbove >> Values;
            }

            if (debug & 2)
            {
                Pout<< " received from "
                    << myComm.above() << " data:" << Values << endl;
            }
        }

        // Send to my downstairs neighbours
        forAll(myComm.below(), belowI)
        {
            label belowID = myComm.below()[belowI];

            if (debug & 2)
            {
                Pout<< " sending to " << belowID << " data:" << Values << endl;
            }

            if (contiguous<T>())
            {
                UOPstream::write
                (
                    UPstream::scheduled,
                    belowID,
                    reinterpret_cast<const char*>(Values.begin()),
                    Values.byteSize(),
                    tag
                );
            }
            else
            {
                OPstream toBelow(UPstream::scheduled, belowID, 0, tag);
                toBelow << Values;
            }
        }
    }
}


template <class T>
void Pstream::listCombineScatter(List<T>& Values, const int tag)
{
    if (UPstream::nProcs() < UPstream::nProcsSimpleSum)
    {
        listCombineScatter(UPstream::linearCommunication(), Values, tag);
    }
    else
    {
        listCombineScatter(UPstream::treeCommunication(), Values, tag);
    }
}




// Same thing but for sparse list (map)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


template <class Container, class CombineOp>
void Pstream::mapCombineGather
(
    const List<UPstream::commsStruct>& comms,
    Container& Values,
    const CombineOp& cop,
    const int tag
)
{
    if (UPstream::parRun())
    {
        // Get my communication order
        const commsStruct& myComm = comms[UPstream::myProcNo()];

        // Receive from my downstairs neighbours
        forAll(myComm.below(), belowI)
        {
            label belowID = myComm.below()[belowI];

            IPstream fromBelow(UPstream::scheduled, belowID, 0, tag);
            Container receivedValues(fromBelow);

            if (debug & 2)
            {
                Pout<< " received from "
                    << belowID << " data:" << receivedValues << endl;
            }

            for
            (
                typename Container::const_iterator slaveIter =
                    receivedValues.begin();
                slaveIter != receivedValues.end();
                ++slaveIter
            )
            {
                typename Container::iterator
                    masterIter = Values.find(slaveIter.key());

                if (masterIter != Values.end())
                {
                    cop(masterIter(), slaveIter());
                }
                else
                {
                    Values.insert(slaveIter.key(), slaveIter());
                }
            }
        }

        // Send up Value
        if (myComm.above() != -1)
        {
            if (debug & 2)
            {
                Pout<< " sending to " << myComm.above()
                    << " data:" << Values << endl;
            }

            OPstream toAbove(UPstream::scheduled, myComm.above(), 0, tag);
            toAbove << Values;
        }
    }
}


template <class Container, class CombineOp>
void Pstream::mapCombineGather
(
    Container& Values,
    const CombineOp& cop,
    const int tag
)
{
    if (UPstream::nProcs() < UPstream::nProcsSimpleSum)
    {
        mapCombineGather(UPstream::linearCommunication(), Values, cop, tag);
    }
    else
    {
        mapCombineGather(UPstream::treeCommunication(), Values, cop, tag);
    }
}


template <class Container>
void Pstream::mapCombineScatter
(
    const List<UPstream::commsStruct>& comms,
    Container& Values,
    const int tag
)
{
    if (UPstream::parRun())
    {
        // Get my communication order
        const UPstream::commsStruct& myComm = comms[UPstream::myProcNo()];

        // Reveive from up
        if (myComm.above() != -1)
        {
            IPstream fromAbove(UPstream::scheduled, myComm.above(), 0, tag);
            fromAbove >> Values;

            if (debug & 2)
            {
                Pout<< " received from "
                    << myComm.above() << " data:" << Values << endl;
            }
        }

        // Send to my downstairs neighbours
        forAll(myComm.below(), belowI)
        {
            label belowID = myComm.below()[belowI];

            if (debug & 2)
            {
                Pout<< " sending to " << belowID << " data:" << Values << endl;
            }

            OPstream toBelow(UPstream::scheduled, belowID, 0, tag);
            toBelow << Values;
        }
    }
}


template <class Container>
void Pstream::mapCombineScatter(Container& Values, const int tag)
{
    if (UPstream::nProcs() < UPstream::nProcsSimpleSum)
    {
        mapCombineScatter(UPstream::linearCommunication(), Values, tag);
    }
    else
    {
        mapCombineScatter(UPstream::treeCommunication(), Values, tag);
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
