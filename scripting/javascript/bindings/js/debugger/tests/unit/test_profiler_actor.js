/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

"use strict";

const Profiler = Cc["@mozilla.org/tools/profiler;1"].getService(Ci.nsIProfiler);

function run_test()
{
  // Ensure the profiler is not running when the test starts (it could
  // happen if the MOZ_PROFILER_STARTUP environment variable is set)
  Profiler.StopProfiler();
  DebuggerServer.init(function () { return true; });
  DebuggerServer.addBrowserActors();
  var client = new DebuggerClient(DebuggerServer.connectPipe());
  client.connect(function () {
    client.listTabs(function(aResponse) {
      test_profiler_actor(client, aResponse.profilerActor);
    });
  });
  do_test_pending();
}

function test_profiler_actor(aClient, aProfiler)
{
  aClient.request({ to: aProfiler, type: "isActive" }, function (aResponse) {
    do_check_false(aResponse.isActive);

    aClient.request({ to: aProfiler, type: "getFeatures" }, function (aResponse) {
      var features = Profiler.GetFeatures([]);
      do_check_eq(aResponse.features.length, features.length);
      for (var i = 0; i < features.length; i++)
        do_check_eq(aResponse.features[i], features[i]);

      aClient.request({ to: aProfiler, type: "startProfiler", features: ['jank', 'js'] }, function (aResponse) {
        do_check_eq(typeof aResponse.msg, "string");
        aClient.request({ to: aProfiler, type: "isActive" }, function (aResponse) {
          do_check_true(aResponse.isActive);

          aClient.request({ to: aProfiler, type: "getResponsivenessTimes" }, function (aResponse) {
            do_check_eq(typeof aResponse.responsivenessTimes, "object");

            aClient.request({ to: aProfiler, type: "getSharedLibraryInformation" }, function (aResponse) {
              do_check_eq(typeof aResponse.sharedLibraryInformation, "string");
              try {
                JSON.parse(aResponse.sharedLibraryInformation);
              } catch(e) {
                do_throw(e.toString(), Components.stack.caller);
              }

              test_event_notifications(aClient, aProfiler);
            });
          });
        });
      });
    });
  });
}

function test_event_notifications(aClient, aProfiler)
{
  aClient.request({ to: aProfiler, type: "registerEventNotifications", events: ["foo", "bar"] }, function (aResponse) {
    do_check_eq(typeof aResponse.registered, "object");
    do_check_eq(aResponse.registered.length, 2);
    do_check_eq(aResponse.registered[0], "foo");
    do_check_eq(aResponse.registered[1], "bar");

    aClient.request({ to: aProfiler, type: "registerEventNotifications", events: ["foo"] }, function (aResponse) {
      do_check_eq(typeof aResponse.registered, "object");
      do_check_eq(aResponse.registered.length, 0);

      aClient.addListener("eventNotification", function (aType, aData) {
        do_check_eq(aType, "eventNotification");
        do_check_eq(aData.event, "foo");
        do_check_eq(typeof aData.subject, "object");
        do_check_eq(aData.subject.foo, "foo");
        do_check_eq(aData.data, "foo");
      });
      var subject = { foo: "foo" };
      subject.wrappedJSObject = subject;
      Services.obs.notifyObservers(subject, "foo", "foo");

      aClient.request({ to: aProfiler, type: "unregisterEventNotifications", events: ["foo", "bar", "qux"] }, function (aResponse) {
        do_check_eq(typeof aResponse.unregistered, "object");
        do_check_eq(aResponse.unregistered.length, 2);
        do_check_eq(aResponse.unregistered[0], "foo");
        do_check_eq(aResponse.unregistered[1], "bar");

        // All events being now unregistered, sending an event shouldn't
        // do anything. If it does, the eventNotification listener above
        // will catch the event and fail on the aData.event test.
        Services.obs.notifyObservers(null, "bar", null);

        test_profile(aClient, aProfiler);
      });
    });
  });
}

function test_profile(aClient, aProfiler)
{
  // No idea why, but Components.stack.sourceLine returns null.
  var funcLine = Components.stack.lineNumber - 3;
  // Busy wait a few milliseconds
  var start = Date.now();
  var stack;
  while (Date.now() - start < 200) { stack = Components.stack; }
  aClient.request({ to: aProfiler, type: "getProfile" }, function (aResponse) {
    do_check_eq(typeof aResponse.profile, "object");
    do_check_eq(typeof aResponse.profile.meta, "object");
    do_check_eq(typeof aResponse.profile.meta.platform, "string");
    do_check_eq(typeof aResponse.profile.threads, "object");
    do_check_eq(typeof aResponse.profile.threads[0], "object");
    do_check_eq(typeof aResponse.profile.threads[0].samples, "object");
    do_check_neq(aResponse.profile.threads[0].samples.length, 0);

    let location = stack.name + " (" + stack.filename + ":" + funcLine + ")";
    // At least one sample is expected to have been in the busy wait above.
    do_check_true(aResponse.profile.threads[0].samples.some(function(sample) {
      return sample.name == "(root)" &&
             typeof sample.frames == "object" &&
             sample.frames.length != 0 &&
             sample.frames.some(function(f) {
               return (f.line == stack.lineNumber) &&
                      (f.location == location);
             });
    }));

    aClient.request({ to: aProfiler, type: "stopProfiler" }, function (aResponse) {
      do_check_eq(typeof aResponse.msg, "string");
      aClient.request({ to: aProfiler, type: "isActive" }, function (aResponse) {
        do_check_false(aResponse.isActive);
        aClient.close(function() {
          test_profiler_status();
        });
      });
    });
  });
}

function test_profiler_status()
{
  var connectionClosed = DebuggerServer._connectionClosed;
  var client = new DebuggerClient(DebuggerServer.connectPipe());

  client.connect(() => {
    client.listTabs((aResponse) => {
      DebuggerServer._connectionClosed = function (conn) {
        connectionClosed.call(this, conn);

        // Check that closing the last (only?) connection stops the profiler.
        do_check_false(Profiler.IsActive());
        do_test_finished();
      }

      var profiler = aResponse.profilerActor;
      do_check_false(Profiler.IsActive());
      client.request({
        to: profiler,
        type: "startProfiler",
        features: []
      }, function (aResponse) {
        do_check_true(Profiler.IsActive());
        client.close();
      });
    });
  });
}
