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

#ifndef SkEventSink_DEFINED
#define SkEventSink_DEFINED

#include "SkRefCnt.h"
#include "SkEvent.h"

struct SkTagList;

/** \class SkEventSink

    SkEventSink is the base class for all objects that receive SkEvents.
*/
class SkEventSink : public SkRefCnt {
public:
            SkEventSink();
    virtual ~SkEventSink();

    /** Returns this eventsink's unique ID. Use this to post SkEvents to
        this eventsink.
    */
    SkEventSinkID getSinkID() const { return fID; }

    /** Call this to pass an event to this object for processing. Returns true if the
        event was handled.
    */
    bool doEvent(const SkEvent&);
    /** Returns true if the sink (or one of its subclasses) understands the event as a query.
        If so, the sink may modify the event to communicate its "answer".
    */
    bool doQuery(SkEvent* query);

    /** Add sinkID to the list of listeners, to receive events from calls to sendToListeners()
        and postToListeners(). If sinkID already exists in the listener list, no change is made.
    */
    void    addListenerID(SkEventSinkID sinkID);
    /** Copy listeners from one event sink to another, typically from parent to child.
        @param from the event sink to copy the listeners from
    */
    void copyListeners(const SkEventSink& from);
    /** Remove sinkID from the list of listeners. If sinkID does not appear in the list,
        no change is made.
    */
    void    removeListenerID(SkEventSinkID);
    /** Returns true if there are 1 or more listeners attached to this eventsink
    */
    bool    hasListeners() const;
    /** Posts a copy of evt to each of the eventsinks in the lisener list.
    */
    void    postToListeners(const SkEvent& evt, SkMSec delay = 0);

    enum EventResult {
        kHandled_EventResult,       //!< the eventsink returned true from its doEvent method
        kNotHandled_EventResult,    //!< the eventsink returned false from its doEvent method
        kSinkNotFound_EventResult   //!< no matching eventsink was found for the event's getSink().
    };
    /** DoEvent handles searching for an eventsink object that matches the targetID.
        If one is found, it calls the sink's doEvent method, returning
        either kHandled_EventResult or kNotHandled_EventResult. If no matching
        eventsink is found, kSinkNotFound_EventResult is returned.
    */
    static EventResult DoEvent(const SkEvent&, SkEventSinkID targetID);

    /** Returns the matching eventsink, or null if not found
    */
    static SkEventSink* FindSink(SkEventSinkID);

protected:
    /** Override this to handle events in your subclass. Be sure to call the inherited version
        for events that you don't handle.
    */
    virtual bool onEvent(const SkEvent&);
    virtual bool onQuery(SkEvent*);

    SkTagList*  findTagList(U8CPU tag) const;
    void        addTagList(SkTagList*);
    void        removeTagList(U8CPU tag);

private:
    SkEventSinkID   fID;
    SkTagList*      fTagHead;

    // for our private link-list
    SkEventSink*    fNextSink;
};

#endif

