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

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/Pstreams/PstreamBuffers.H"

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace Foam
{

    DynamicList<char> PstreamBuffers::nullBuf(0);
}


// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

Foam::PstreamBuffers::PstreamBuffers
(
    const UPstream::commsTypes commsType,
    const int tag,
    IOstream::streamFormat format,
    IOstream::versionNumber version
)
:
    commsType_(commsType),
    tag_(tag),
    format_(format),
    version_(version),
    sendBuf_(UPstream::nProcs()),
    recvBuf_(UPstream::nProcs()),
    recvBufPos_(UPstream::nProcs(),  0),
    finishedSendsCalled_(false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::PstreamBuffers::~PstreamBuffers()
{
    // Check that all data has been consumed.
    forAll(recvBufPos_, procI)
    {
        if (recvBufPos_[procI] < recvBuf_[procI].size())
        {
            FatalErrorIn("PstreamBuffers::~PstreamBuffers()")
                << "Message from processor " << procI
                << " not fully consumed. messageSize:" << recvBuf_[procI].size()
                << " bytes of which only " << recvBufPos_[procI]
                << " consumed."
                << Foam::abort(FatalError);
        }
    }
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::PstreamBuffers::finishedSends(const bool block)
{
    finishedSendsCalled_ = true;

    if (commsType_ == UPstream::nonBlocking)
    {
        labelListList sizes;
        Pstream::exchange<DynamicList<char>, char>
        (
            sendBuf_,
            recvBuf_,
            sizes,
            tag_,
            block
        );
    }
}


void Foam::PstreamBuffers::finishedSends(labelListList& sizes, const bool block)
{
    finishedSendsCalled_ = true;

    if (commsType_ == UPstream::nonBlocking)
    {
        Pstream::exchange<DynamicList<char>, char>
        (
            sendBuf_,
            recvBuf_,
            sizes,
            tag_,
            block
        );
    }
    else
    {
        FatalErrorIn
        (
            "PstreamBuffers::finishedSends(labelListList&, const bool)"
        )   << "Obtaining sizes not supported in "
            << UPstream::commsTypeNames[commsType_] << endl
            << " since transfers already in progress. Use non-blocking instead."
            << exit(FatalError);

        // Note: possible only if using different tag from write started
        // by ~UOPstream. Needs some work.
        //sizes.setSize(UPstream::nProcs());
        //labelList& nsTransPs = sizes[UPstream::myProcNo()];
        //nsTransPs.setSize(UPstream::nProcs());
        //
        //forAll(sendBuf_, procI)
        //{
        //    nsTransPs[procI] = sendBuf_[procI].size();
        //}
        //
        //// Send sizes across.
        //int oldTag = UPstream::msgType();
        //UPstream::msgType() = tag_;
        //combineReduce(sizes, UPstream::listEq());
        //UPstream::msgType() = oldTag;
    }
}


// ************************************************************************* //
