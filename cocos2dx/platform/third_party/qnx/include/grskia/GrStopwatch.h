/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrStopwatch_DEFINED
#define GrStopwatch_DEFINED

#include "GrTypes.h"

template <typename PLATFORM_TIMER>
/**
 * Base class for stopwatch. Relies on PLATFORM_TIMER for platform-specific
 * timer functions. PLATFORM_TIMER provides:
 *      - typename TIMESTAMP : a timestamp value that can be used with Diff()
 *      - static TIMESTAMP Now() : gets current timestamp
 *      - static double Diff(const TIMESTAMP& begin, const TIMESTAMP& end) : 
 *           computes delta in seconds between two timestamps
 */
class GrStopwatchBase {
public:
    /**
     * Contructor - implicit reset()
     */
    GrStopwatchBase() {
        fRunning = false;
        fTotalElapsed = 0.0;        
    }

    /**
     * begins a new lap
     */
    void start() {
        double lastLap = lapTime();
        fTotalElapsed += lastLap;
        fRunning = true;
        fLastStart = PLATFORM_TIMER::Now();
    }
    
    /**
     * ends current lap (or no effect if lap not started)
     */
    void stop() {
        double lastLap = lapTime();
        fTotalElapsed += lastLap;
        fRunning = false;
    }

    /**
     * ends current lap, resets total time
     */
    void reset() {
        fRunning = false;
        fTotalElapsed = 0.f;
    }
    
    /**
     * Computes the time of all laps since last reset() including current lap
     * if lap is still running.
     *
     * @return the sum time in seconds of all laps since last reset().
     */
    double totalTime() const {
        return fTotalElapsed + lapTime();
    }

    /**
     * Current lap time.
     *
     * @return time in seconds of current lap if one is running otherwise 0.
     */
    double lapTime() const {
        if (fRunning) {
            PLATFORM_TIMER::Timestamp now = PLATFORM_TIMER::Now();
            return PLATFORM_TIMER::Elapsed(fLastStart, now);
        }
        return 0.0;
    }

private:
    double fTotalElapsed;

    typename PLATFORM_TIMER::Timestamp fLastStart;
    bool                               fRunning;
};

#if GR_WIN32_BUILD

    #include <Windows.h>

    class GrWin32Timer {
    public:
        typedef LARGE_INTEGER Timestamp;  

        static Timestamp Now() {
            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            return now;
        }

        static double Elapsed(const Timestamp& begin, const Timestamp& end) {
            double diff = (double)(end.QuadPart - begin.QuadPart);
            return diff * Scale();
        }
    private:
        static double Scale() {
            static double scale;
            if (0.0 == scale) {
                LARGE_INTEGER freq;
                QueryPerformanceFrequency(&freq);
                GrAssert(0 != freq.QuadPart);
                scale = 1 / (double) freq.QuadPart;
            }
            return scale;
        }
    };
    typedef GrStopwatchBase<GrWin32Timer> GrStopwatch;
#else
    #error "Implement platform timer for stopwatch"
#endif


#endif
