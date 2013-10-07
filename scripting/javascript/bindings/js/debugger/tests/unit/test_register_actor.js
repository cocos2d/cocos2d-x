/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

"use strict";

const Profiler = Cc["@mozilla.org/tools/profiler;1"].getService(Ci.nsIProfiler);

function check_actors(expect) {
  do_check_eq(expect, DebuggerServer.tabActorFactories.hasOwnProperty("registeredActor1"));
  do_check_eq(expect, DebuggerServer.tabActorFactories.hasOwnProperty("registeredActor2"));

  do_check_eq(expect, DebuggerServer.globalActorFactories.hasOwnProperty("registeredActor2"));
  do_check_eq(expect, DebuggerServer.globalActorFactories.hasOwnProperty("registeredActor1"));
}

function run_test()
{
  DebuggerServer.init(function () { return true; });
  // The xpcshell-test/ path maps to resource://test/
  DebuggerServer.registerModule("xpcshell-test/registertestactors-01");
  DebuggerServer.registerModule("xpcshell-test/registertestactors-02");

  check_actors(true);

  check_except(() => {
    DebuggerServer.registerModule("xpcshell-test/registertestactors-01");
  });
  check_except(() => {
    DebuggerServer.registerModule("xpcshell-test/registertestactors-02");
  });

  DebuggerServer.unregisterModule("xpcshell-test/registertestactors-01");
  DebuggerServer.unregisterModule("xpcshell-test/registertestactors-02");
  check_actors(false);

  DebuggerServer.registerModule("xpcshell-test/registertestactors-01");
  DebuggerServer.registerModule("xpcshell-test/registertestactors-02");
  check_actors(true);

  DebuggerServer.destroy();
  check_actors(false);
}

