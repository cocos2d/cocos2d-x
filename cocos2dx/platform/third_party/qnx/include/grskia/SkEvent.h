/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkEvent_DEFINED
#define SkEvent_DEFINED

#include "SkDOM.h"
#include "SkMetaData.h"
#include "SkString.h"

/** Unique 32bit id used to identify an instance of SkEventSink. When events are
    posted, they are posted to a specific sinkID. When it is time to dispatch the
    event, the sinkID is used to find the specific SkEventSink object. If it is found,
    its doEvent() method is called with the event.
*/
typedef uint32_t SkEventSinkID;

/** \class SkEvent

    SkEvents are used to communicate type-safe information to SkEventSinks.
    SkEventSinks (including SkViews) each have a unique ID, which is stored
    in an event. This ID is used to target the event once it has been "posted".
*/
class SkEvent {
public:
    /** Default construct, creating an empty event.
    */
    SkEvent();
    /** Construct a new event with the specified type.
    */
    explicit SkEvent(const SkString& type);
    /** Construct a new event with the specified type.
    */
    explicit SkEvent(const char type[]);
    /** Construct a new event by copying the fields from the src event.
    */
    SkEvent(const SkEvent& src);
    ~SkEvent();

//  /** Return the event's type (will never be null) */
//  const char* getType() const;
    /** Copy the event's type into the specified SkString parameter */
    void    getType(SkString* str) const;
    /** Returns true if the event's type matches exactly the specified type (case sensitive) */
    bool    isType(const SkString& str) const;
    /** Returns true if the event's type matches exactly the specified type (case sensitive) */
    bool    isType(const char type[], size_t len = 0) const;
    /** Set the event's type to the specified string.
        In XML, use the "type" attribute.
    */
    void    setType(const SkString&);
    /** Set the event's type to the specified string.
        In XML, use the "type" attribute.
    */
    void    setType(const char type[], size_t len = 0);

    /** Return the event's unnamed 32bit field. Default value is 0 */
    uint32_t getFast32() const { return f32; }
    /** Set the event's unnamed 32bit field. In XML, use
        the subelement <data fast32=... />
    */
    void    setFast32(uint32_t x) { f32 = x; }

    /** Return true if the event contains the named 32bit field, and return the field
        in value (if value is non-null). If there is no matching named field, return false
        and ignore the value parameter.
    */
    bool    findS32(const char name[], int32_t* value = NULL) const { return fMeta.findS32(name, value); }
    /** Return true if the event contains the named SkScalar field, and return the field
        in value (if value is non-null). If there is no matching named field, return false
        and ignore the value parameter.
    */
    bool    findScalar(const char name[], SkScalar* value = NULL) const { return fMeta.findScalar(name, value); }
    /** Return true if the event contains the named SkScalar field, and return the fields
        in value[] (if value is non-null), and return the number of SkScalars in count (if count is non-null).
        If there is no matching named field, return false and ignore the value and count parameters.
    */
    const SkScalar* findScalars(const char name[], int* count, SkScalar values[] = NULL) const { return fMeta.findScalars(name, count, values); }
    /** Return the value of the named string field, or if no matching named field exists, return null.
    */
    const char* findString(const char name[]) const { return fMeta.findString(name); }
    /** Return true if the event contains the named pointer field, and return the field
        in value (if value is non-null). If there is no matching named field, return false
        and ignore the value parameter.
    */
    bool    findPtr(const char name[], void** value) const { return fMeta.findPtr(name, value); }
    bool    findBool(const char name[], bool* value) const { return fMeta.findBool(name, value); }
    const void* findData(const char name[], size_t* byteCount = NULL) const {
        return fMeta.findData(name, byteCount);
    }

    /** Returns true if ethe event contains the named 32bit field, and if it equals the specified value */
    bool    hasS32(const char name[], int32_t value) const { return fMeta.hasS32(name, value); }
    /** Returns true if ethe event contains the named SkScalar field, and if it equals the specified value */
    bool    hasScalar(const char name[], SkScalar value) const { return fMeta.hasScalar(name, value); }
    /** Returns true if ethe event contains the named string field, and if it equals (using strcmp) the specified value */
    bool    hasString(const char name[], const char value[]) const { return fMeta.hasString(name, value); }
    /** Returns true if ethe event contains the named pointer field, and if it equals the specified value */
    bool    hasPtr(const char name[], void* value) const { return fMeta.hasPtr(name, value); }
    bool    hasBool(const char name[], bool value) const { return fMeta.hasBool(name, value); }
    bool hasData(const char name[], const void* data, size_t byteCount) const {
        return fMeta.hasData(name, data, byteCount);
    }

    /** Add/replace the named 32bit field to the event. In XML use the subelement <data name=... s32=... /> */
    void    setS32(const char name[], int32_t value) { fMeta.setS32(name, value); }
    /** Add/replace the named SkScalar field to the event. In XML use the subelement <data name=... scalar=... /> */
    void    setScalar(const char name[], SkScalar value) { fMeta.setScalar(name, value); }
    /** Add/replace the named SkScalar[] field to the event. */
    SkScalar* setScalars(const char name[], int count, const SkScalar values[] = NULL) { return fMeta.setScalars(name, count, values); }
    /** Add/replace the named string field to the event. In XML use the subelement <data name=... string=... */
    void    setString(const char name[], const SkString& value) { fMeta.setString(name, value.c_str()); }
    /** Add/replace the named string field to the event. In XML use the subelement <data name=... string=... */
    void    setString(const char name[], const char value[]) { fMeta.setString(name, value); }
    /** Add/replace the named pointer field to the event. There is no XML equivalent for this call */
    void    setPtr(const char name[], void* value) { fMeta.setPtr(name, value); }
    void    setBool(const char name[], bool value) { fMeta.setBool(name, value); }
    void setData(const char name[], const void* data, size_t byteCount) {
        fMeta.setData(name, data, byteCount);
    }

    /** Return the underlying metadata object */
    SkMetaData&         getMetaData() { return fMeta; }
    /** Return the underlying metadata object */
    const SkMetaData&   getMetaData() const { return fMeta; }

    void tron() { SkDEBUGCODE(fDebugTrace = true;) }
    void troff() { SkDEBUGCODE(fDebugTrace = false;) }
    bool isDebugTrace() const
    {
#ifdef SK_DEBUG
        return fDebugTrace;
#else
        return false;
#endif
    }

    /** Call this to initialize the event from the specified XML node */
    void    inflate(const SkDOM&, const SkDOM::Node*);

    SkDEBUGCODE(void dump(const char title[] = NULL);)

    /** Post the specified event to the event queue, targeting the specified eventsink, with an optional
        delay. The event must be dynamically allocated for this. It cannot be a global or on the stack.
        After this call, ownership is transfered to the system, so the caller must not retain
        the event's ptr. Returns false if the event could not be posted (which means it will have been deleted).
    */
    static bool Post(SkEvent* evt, SkEventSinkID targetID, SkMSec delay = 0);
    /** Post the specified event to the event queue, targeting the specified eventsink, to be delivered on/after the
        specified millisecond time. The event must be dynamically allocated for this. It cannot be a global or on the stack.
        After this call, ownership is transfered to the system, so the caller must not retain
        the event's ptr. Returns false if the event could not be posted (which means it will have been deleted).
    */
    static bool PostTime(SkEvent* evt, SkEventSinkID targetID, SkMSec time);

    /** Helper method for calling SkEvent::PostTime(this, ...), where the caller specifies a delay.
        The real "time" will be computed automatically by sampling the clock and adding its value
        to delay.
    */
    bool post(SkEventSinkID sinkID, SkMSec delay = 0)
    {
        return SkEvent::Post(this, sinkID, delay);
    }

    void postTime(SkEventSinkID sinkID, SkMSec time)
    {
        SkEvent::PostTime(this, sinkID, time);
    }

    ///////////////////////////////////////////////
    /** Porting layer must call these functions **/
    ///////////////////////////////////////////////

    /** Global initialization function for the SkEvent system. Should be called exactly
        once before any other event method is called, and should be called after the
        call to SkGraphics::Init().
    */
    static void     Init();
    /** Global cleanup function for the SkEvent system. Should be called exactly once after
        all event methods have been called, and should be called before calling SkGraphics::Term().
    */
    static void     Term();

    /** Call this to process one event from the queue. If it returns true, there are more events
        to process.
    */
    static bool     ProcessEvent();
    /** Call this whenever the requested timer has expired (requested by a call to SetQueueTimer).
        It will post any delayed events whose time as "expired" onto the event queue.
        It may also call SignalQueueTimer() and SignalNonEmptyQueue().
    */
    static void     ServiceQueueTimer();

    /** Return the number of queued events. note that this value may be obsolete
        upon return, since another thread may have called ProcessEvent() or
        Post() after the count was made.
     */
    static int CountEventsOnQueue();

    ////////////////////////////////////////////////////
    /** Porting layer must implement these functions **/
    ////////////////////////////////////////////////////

    /** Called whenever an SkEvent is posted to an empty queue, so that the OS
        can be told to later call Dequeue().
    */
    static void SignalNonEmptyQueue();
    /** Called whenever the delay until the next delayed event changes. If zero is
        passed, then there are no more queued delay events.
    */
    static void SignalQueueTimer(SkMSec delay);

#ifndef SK_USE_WXWIDGETS
#ifdef SK_BUILD_FOR_WIN
    static bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#elif defined(SK_BUILD_FOR_UNIXx)
  static uint32_t HandleTimer(uint32_t, void*);
  static bool WndProc(Display*, Window, XEvent&);
#endif
#else
    // Don't know yet what this will be
    //static bool CustomEvent();
#endif

private:
    SkMetaData      fMeta;
    mutable char*   fType;  // may be characters with low bit set to know that it is not a pointer
    uint32_t        f32;
    SkDEBUGCODE(bool fDebugTrace;)

    // these are for our implementation of the event queue
    SkEventSinkID   fTargetID;
    SkMSec          fTime;
    SkEvent*        fNextEvent; // either in the delay or normal event queue
    void initialize(const char* type, size_t typeLen);

    static bool Enqueue(SkEvent* evt);
    static SkMSec EnqueueTime(SkEvent* evt, SkMSec time);
    static SkEvent* Dequeue(SkEventSinkID* targetID);
    static bool     QHasEvents();
};

#endif

