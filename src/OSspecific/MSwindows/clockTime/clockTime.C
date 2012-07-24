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

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/OSspecific/MSwindows/clockTime/clockTime.H"

//#include <sys/time.h>
#include <time.h>

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Static Members  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void clockTime::getTime(struct timeval& t)
{
    //gettimeofday(&t, NULL);
	//http://stackoverflow.com/questions/2494356/how-to-use-gettimeofday-or-something-equivalent-with-visual-studio-c-2008
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	if (NULL != &t)
	{
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS; 
		tmpres /= 10;  /*convert into microseconds*/
		t.tv_sec = (long)(tmpres / 1000000UL);
		t.tv_usec = (long)(tmpres % 1000000UL);
	}
}


double clockTime::timeDifference
(
    const struct timeval& start,
    const struct timeval& end
)
{
    return end.tv_sec - start.tv_sec + 1E-6*(end.tv_usec - start.tv_usec);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

clockTime::clockTime()
{
    getTime(startTime_);
    lastTime_ = startTime_;
    newTime_ = startTime_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

double clockTime::elapsedTime() const
{
    getTime(newTime_);
    return timeDifference(startTime_, newTime_);
}


double clockTime::timeIncrement() const
{
    lastTime_ = newTime_;
    getTime(newTime_);
    return timeDifference(lastTime_, newTime_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
