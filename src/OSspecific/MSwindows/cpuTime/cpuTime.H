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
    cpuTime

Description
    Starts timing CPU usage and return elapsed time from start.

SourceFiles
    cpuTime.C

\*---------------------------------------------------------------------------*/

#ifndef cpuTime_H
#define cpuTime_H

#include <ctime>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class cpuTime Declaration
\*---------------------------------------------------------------------------*/

class cpuTime
{
    // Private data

        std::clock_t startTime_;
        mutable std::clock_t lastTime_;
        mutable std::clock_t newTime_;

        static void getTime(std::clock_t& t);

        static double timeDifference
        (
            const std::clock_t& start,
            const std::clock_t& end
        );


public:

    // Constructors

        //- Construct from components
        cpuTime();


    // Member Functions

        // Access

            //- Returns CPU time from start of run
            double elapsedCpuTime() const;

            //- Returns CPU time from last call of cpuTimeIncrement()
            double cpuTimeIncrement() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
