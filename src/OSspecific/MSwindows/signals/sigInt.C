/*---------------------------------------------------------------------------*\
    Copyright            : (C) 2011 Symscape
    Website              : www.symscape.com
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

Class
    sigInt

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/OpenFOAM/db/error/error.H"
#include "OpenFOAM-2.1.x/src/OSspecific/MSwindows/signals/sigInt.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/global/JobInfo/JobInfo.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/db/IOstreams/IOstreams.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

__p_sig_fn_t Foam::sigInt::oldAction_ = SIG_DFL;

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::sigInt::sigIntHandler(int)
{
    // Reset old handling
    const __p_sig_fn_t success = ::signal(SIGINT, oldAction_);

    if (SIG_ERR == success)
    {
        FatalErrorIn
        (
            "Foam::sigInt::sigIntHandler()"
        )   << "Cannot reset SIGINT trapping"
            << abort(FatalError);
    }

    // Update jobInfo file
    jobInfo.signalEnd();

    // Throw signal (to old handler)
    ::raise(SIGINT);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::sigInt::sigInt()
{
    oldAction_ = SIG_DFL;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::sigInt::~sigInt()
{
    // Reset old handling
    const __p_sig_fn_t success = ::signal(SIGINT, oldAction_);
    oldAction_ = SIG_DFL;

    if (SIG_ERR == success)
    {
         FatalErrorIn
        (
            "Foam::sigInt::~sigInt()"
        )   << "Cannot reset SIGINT trapping"
            << abort(FatalError);    
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::sigInt::set(const bool verbose)
{
    if (SIG_DFL != oldAction_)
    {
        FatalErrorIn
        (
            "Foam::sigInt::set()"
        )   << "Cannot call sigInt::set() more than once"
            << abort(FatalError);
    }

    oldAction_ = ::signal(SIGINT, &Foam::sigInt::sigIntHandler);        

    if (SIG_ERR == oldAction_)
    {
        oldAction_ = SIG_DFL;
 
        FatalErrorIn
        (
            "Foam::sigInt::set()"
        )   << "Cannot set SIGINT trapping"
            << abort(FatalError);    
    }
}


// ************************************************************************* //
