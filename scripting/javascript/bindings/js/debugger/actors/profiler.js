/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

var startedProfilers = 0;
var startTime = 0;

function getCurrentTime() {
  return (new Date()).getTime() - startTime;
}

/**
 * Creates a ProfilerActor. ProfilerActor provides remote access to the
 * built-in profiler module.
 */
function ProfilerActor(aConnection)
{
  this._profiler = Cc["@mozilla.org/tools/profiler;1"].getService(Ci.nsIProfiler);
  this._started = false;
  this._observedEvents = [];
}

ProfilerActor.prototype = {
  actorPrefix: "profiler",

  disconnect: function() {
    for (var event of this._observedEvents) {
      Services.obs.removeObserver(this, event);
    }

    this.stopProfiler();
    this._profiler = null;
  },

  stopProfiler: function() {
    // We stop the profiler only after the last client has
    // stopped profiling. Otherwise there's a problem where
    // we stop the profiler as soon as you close the devtools
    // panel in one tab even though there might be other
    // profiler instances running in other tabs.
    if (!this._started) {
      return;
    }
    this._started = false;
    startedProfilers -= 1;
    if (startedProfilers <= 0) {
      this._profiler.StopProfiler();
    }
  },

  onStartProfiler: function(aRequest) {
    this._profiler.StartProfiler(aRequest.entries, aRequest.interval,
                           aRequest.features, aRequest.features.length);
    this._started = true;
    startedProfilers += 1;
    startTime = (new Date()).getTime();
    return { "msg": "profiler started" }
  },
  onStopProfiler: function(aRequest) {
    this.stopProfiler();
    return { "msg": "profiler stopped" }
  },
  onGetProfileStr: function(aRequest) {
    var profileStr = this._profiler.GetProfile();
    return { "profileStr": profileStr }
  },
  onGetProfile: function(aRequest) {
    var profile = this._profiler.getProfileData();
    return { "profile": profile, "currentTime": getCurrentTime() }
  },
  onIsActive: function(aRequest) {
    var isActive = this._profiler.IsActive();
    var currentTime = isActive ? getCurrentTime() : null;
    return { "isActive": isActive, "currentTime": currentTime }
  },
  onGetResponsivenessTimes: function(aRequest) {
    var times = this._profiler.GetResponsivenessTimes({});
    return { "responsivenessTimes": times }
  },
  onGetFeatures: function(aRequest) {
    var features = this._profiler.GetFeatures([]);
    return { "features": features }
  },
  onGetSharedLibraryInformation: function(aRequest) {
    var sharedLibraries = this._profiler.getSharedLibraryInformation();
    return { "sharedLibraryInformation": sharedLibraries }
  },
  onRegisterEventNotifications: function(aRequest) {
    let registered = [];
    for (var event of aRequest.events) {
      if (this._observedEvents.indexOf(event) != -1)
        continue;
      Services.obs.addObserver(this, event, false);
      this._observedEvents.push(event);
      registered.push(event);
    }
    return { registered: registered }
  },
  onUnregisterEventNotifications: function(aRequest) {
    let unregistered = [];
    for (var event of aRequest.events) {
      let idx = this._observedEvents.indexOf(event);
      if (idx == -1)
        continue;
      Services.obs.removeObserver(this, event);
      this._observedEvents.splice(idx, 1);
      unregistered.push(event);
    }
    return { unregistered: unregistered }
  },
  observe: makeInfallible(function(aSubject, aTopic, aData) {
    /*
     * this.conn.send can only transmit acyclic values. However, it is
     * idiomatic for wrapped JS objects like aSubject (and possibly aData?)
     * to have a 'wrappedJSObject' property pointing to themselves.
     *
     * this.conn.send also assumes that it can retain the object it is
     * passed to be handled on later event ticks; and that it's okay to
     * freeze it. Since we don't really know what aSubject and aData are,
     * we need to pass this.conn.send a copy of them, not the originals.
     *
     * We break the cycle and make the copy by JSON.stringifying those
     * values with a replacer that omits properties known to introduce
     * cycles, and then JSON.parsing the result. This spends processor
     * time, but it's simple.
     */
    function cycleBreaker(key, value) {
      if (key === 'wrappedJSObject') {
        return undefined;
      }
      return value;
    }

    /*
     * If these values are objects with a non-null 'wrappedJSObject'
     * property, use its value. Otherwise, use the value unchanged.
     */
    aSubject = (aSubject && aSubject.wrappedJSObject) || aSubject;
    aData    = (aData    && aData.wrappedJSObject)    || aData;

    let subj = JSON.parse(JSON.stringify(aSubject, cycleBreaker));
    let data = JSON.parse(JSON.stringify(aData,    cycleBreaker));

    let send = (extra) => {
      data = data || {};

      if (extra)
        data.extra = extra;

      this.conn.send({
        from:    this.actorID,
        type:    "eventNotification",
        event:   aTopic,
        subject: subj,
        data:    data
      });
    }

    if (aTopic !== "console-api-profiler")
      return void send();

    // If the event was generated from console.profile or
    // console.profileEnd we need to start the profiler
    // right away and only then notify our client. Otherwise,
    // we'll lose precious samples.

    let name = subj.arguments[0];

    if (subj.action === "profile") {
      let resp = this.onIsActive();

      if (resp.isActive) {
        return void send({
          name: name,
          currentTime: resp.currentTime,
          action: "profile"
        });
      }

      this.onStartProfiler({
        entries: 1000000,
        interval: 1,
        features: ["js"]
      });

      return void send({ currentTime: 0, action: "profile", name: name });
    }

    if (subj.action === "profileEnd") {
      let resp = this.onGetProfile();
      resp.action = "profileEnd";
      resp.name = name;
      send(resp);
    }

    return undefined; // Otherwise xpcshell tests fail.
  }, "ProfilerActor.prototype.observe"),
};

/**
 * The request types this actor can handle.
 */
ProfilerActor.prototype.requestTypes = {
  "startProfiler": ProfilerActor.prototype.onStartProfiler,
  "stopProfiler": ProfilerActor.prototype.onStopProfiler,
  "getProfileStr": ProfilerActor.prototype.onGetProfileStr,
  "getProfile": ProfilerActor.prototype.onGetProfile,
  "isActive": ProfilerActor.prototype.onIsActive,
  "getResponsivenessTimes": ProfilerActor.prototype.onGetResponsivenessTimes,
  "getFeatures": ProfilerActor.prototype.onGetFeatures,
  "getSharedLibraryInformation": ProfilerActor.prototype.onGetSharedLibraryInformation,
  "registerEventNotifications": ProfilerActor.prototype.onRegisterEventNotifications,
  "unregisterEventNotifications": ProfilerActor.prototype.onUnregisterEventNotifications
};

DebuggerServer.addGlobalActor(ProfilerActor, "profilerActor");
