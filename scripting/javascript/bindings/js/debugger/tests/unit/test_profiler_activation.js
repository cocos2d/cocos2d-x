/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

"use strict";

const Profiler = Cc["@mozilla.org/tools/profiler;1"].getService(Ci.nsIProfiler);

function connectClient(callback) {
  let client = new DebuggerClient(DebuggerServer.connectPipe());
  client.connect(function () {
    client.listTabs(function(response) {
      callback(client, response.profilerActor);
    });
  });
}

function run_test()
{
  // Ensure the profiler is not running when the test starts (it could
  // happen if the MOZ_PROFILER_STARTUP environment variable is set)
  Profiler.StopProfiler();

  DebuggerServer.init(function () { return true; });
  DebuggerServer.addBrowserActors();

  connectClient((client1, actor1) => {
    connectClient((client2, actor2) => {
      activate_first(client1, actor1, client2, actor2);
    });
  })

  do_test_pending();
}

function activate_first(client1, actor1, client2, actor2) {
  // Start the profiler on the first connection....
  client1.request({ to: actor1, type: "startProfiler", features: ['js']}, startResponse => {
    // Profiler should be active now.
    do_check_true(Profiler.IsActive());

    // But on the next connection just make sure the actor has been
    // instantiated.
    client2.request({ to: actor2, type: "getFeatures" }, featureResponse => {

      let connectionClosed = DebuggerServer._connectionClosed;
      DebuggerServer._connectionClosed = function(conn) {
        connectionClosed.call(this, conn);

        // Client1 is the only actor that started the profiler,
        // it shouldn't be active anymore.
        do_check_false(Profiler.IsActive());

        DebuggerServer._connectionClosed = function(conn) {
          connectionClosed.call(this, conn);

          // Now there are no open clients at all, it should *definitely*
          // be deactivated by now.
          do_check_false(Profiler.IsActive());
          do_test_finished();
        }
        client2.close();
      };
      client1.close();
    });
  });
}
