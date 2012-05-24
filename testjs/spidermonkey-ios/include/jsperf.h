/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * the Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Zack Weinberg <zweinberg@mozilla.com>  (original author)
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef jsperf_h___
#define jsperf_h___

#include "jsapi.h"

namespace JS {

/*
 * JS::PerfMeasurement is a generic way to access detailed performance
 * measurement APIs provided by your operating system.  The details of
 * exactly how this works and what can be measured are highly
 * system-specific, but this interface is (one hopes) implementable
 * on top of all of them.
 *
 * To use this API, create a PerfMeasurement object, passing its
 * constructor a bitmask indicating which events you are interested
 * in.  Thereafter, Start() zeroes all counters and starts timing;
 * Stop() stops timing again; and the counters for the events you
 * requested are available as data values after calling Stop().  The
 * object may be reused for many measurements.
 */
class JS_FRIEND_API(PerfMeasurement)
{
  protected:
    // Implementation-specific data, if any.
    void* impl;

  public:
    /*
     * Events that may be measured.  Taken directly from the list of
     * "generalized hardware performance event types" in the Linux
     * perf_event API, plus some of the "software events".
     */
    enum EventMask {
        CPU_CYCLES          = 0x00000001,
        INSTRUCTIONS        = 0x00000002,
        CACHE_REFERENCES    = 0x00000004,
        CACHE_MISSES        = 0x00000008,
        BRANCH_INSTRUCTIONS = 0x00000010,
        BRANCH_MISSES       = 0x00000020,
        BUS_CYCLES          = 0x00000040,
        PAGE_FAULTS         = 0x00000080,
        MAJOR_PAGE_FAULTS   = 0x00000100,
        CONTEXT_SWITCHES    = 0x00000200,
        CPU_MIGRATIONS      = 0x00000400,

        ALL                 = 0x000007ff,
        NUM_MEASURABLE_EVENTS  = 11
    };

    /*
     * Bitmask of events that will be measured when this object is
     * active (between Start() and Stop()).  This may differ from the
     * bitmask passed to the constructor if the platform does not
     * support measuring all of the requested events.
     */
    const EventMask eventsMeasured;

    /*
     * Counters for each measurable event.
     * Immediately after one of these objects is created, all of the
     * counters for enabled events will be zero, and all of the
     * counters for disabled events will be uint64_t(-1).
     */
    uint64_t cpu_cycles;
    uint64_t instructions;
    uint64_t cache_references;
    uint64_t cache_misses;
    uint64_t branch_instructions;
    uint64_t branch_misses;
    uint64_t bus_cycles;
    uint64_t page_faults;
    uint64_t major_page_faults;
    uint64_t context_switches;
    uint64_t cpu_migrations;

    /*
     * Prepare to measure the indicated set of events.  If not all of
     * the requested events can be measured on the current platform,
     * then the eventsMeasured bitmask will only include the subset of
     * |toMeasure| corresponding to the events that can be measured.
     */
    PerfMeasurement(EventMask toMeasure);

    /* Done with this set of measurements, tear down OS-level state. */
    ~PerfMeasurement();

    /* Start a measurement cycle. */
    void start();

    /*
     * End a measurement cycle, and for each enabled counter, add the
     * number of measured events of that type to the appropriate
     * visible variable.
     */
    void stop();

    /* Reset all enabled counters to zero. */
    void reset();

    /*
     * True if this platform supports measuring _something_, i.e. it's
     * not using the stub implementation.
     */
    static bool canMeasureSomething();
};

/* Inject a Javascript wrapper around the above C++ class into the
 * Javascript object passed as an argument (this will normally be a
 * global object).  The JS-visible API is identical to the C++ API.
 */
extern JS_FRIEND_API(JSObject*)
    RegisterPerfMeasurement(JSContext *cx, JSObject *global);

/*
 * Given a jsval which contains an instance of the aforementioned
 * wrapper class, extract the C++ object.  Returns NULL if the
 * jsval is not an instance of the wrapper.
 */
extern JS_FRIEND_API(PerfMeasurement*)
    ExtractPerfMeasurement(jsval wrapper);

} // namespace JS

#endif // jsperf_h___
