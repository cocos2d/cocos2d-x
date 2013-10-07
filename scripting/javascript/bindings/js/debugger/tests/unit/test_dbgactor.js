/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

Cu.import("resource://gre/modules/devtools/dbg-server.jsm");
Cu.import("resource://gre/modules/devtools/dbg-client.jsm");

var gClient;
var gDebuggee;

const xpcInspector = Cc["@mozilla.org/jsinspector;1"].getService(Ci.nsIJSInspector);

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = testGlobal("test-1");
  DebuggerServer.addTestGlobal(gDebuggee);

  let transport = DebuggerServer.connectPipe();
  gClient = new DebuggerClient(transport);
  gClient.addListener("connected", function(aEvent, aType, aTraits) {
    gClient.listTabs((aResponse) => {
      do_check_true('tabs' in aResponse);
      for (let tab of aResponse.tabs) {
        if (tab.title == "test-1") {
          test_attach_tab(tab.actor);
          return false;
        }
      }
      do_check_true(false); // We should have found our tab in the list.
    });
  });

  gClient.connect();

  do_test_pending();
}

// Attach to |aTabActor|, and check the response.
function test_attach_tab(aTabActor)
{
  gClient.request({ to: aTabActor, type: "attach" }, function(aResponse) {
    do_check_false("error" in aResponse);
    do_check_eq(aResponse.from, aTabActor);
    do_check_eq(aResponse.type, "tabAttached");
    do_check_true(typeof aResponse.threadActor === "string");

    test_attach_thread(aResponse.threadActor);
  });
}

// Attach to |aThreadActor|, check the response, and resume it.
function test_attach_thread(aThreadActor)
{
  gClient.request({ to: aThreadActor, type: "attach" }, function(aResponse) {
    do_check_false("error" in aResponse);
    do_check_eq(aResponse.from, aThreadActor);
    do_check_eq(aResponse.type, "paused");
    do_check_true("why" in aResponse);
    do_check_eq(aResponse.why.type, "attached");

    test_resume_thread(aThreadActor);
  });
}

// Resume |aThreadActor|, and see that it stops at the 'debugger'
// statement.
function test_resume_thread(aThreadActor)
{
  // Allow the client to resume execution.
  gClient.request({ to: aThreadActor, type: "resume" }, function (aResponse) {
    do_check_false("error" in aResponse);
    do_check_eq(aResponse.from, aThreadActor);
    do_check_eq(aResponse.type, "resumed");

    do_check_eq(xpcInspector.eventLoopNestLevel, 0);

    // Now that we know we're resumed, we can make the debuggee do something.
    Cu.evalInSandbox("var a = true; var b = false; debugger; var b = true;", gDebuggee);
    // Now make sure that we've run the code after the debugger statement...
    do_check_true(gDebuggee.b);
  });

  gClient.addListener("paused", function(aName, aPacket) {
    do_check_eq(aName, "paused");
    do_check_false("error" in aPacket);
    do_check_eq(aPacket.from, aThreadActor);
    do_check_eq(aPacket.type, "paused");
    do_check_true("actor" in aPacket);
    do_check_true("why" in aPacket)
    do_check_eq(aPacket.why.type, "debuggerStatement");

    // Reach around the protocol to check that the debuggee is in the state
    // we expect.
    do_check_true(gDebuggee.a);
    do_check_false(gDebuggee.b);

    do_check_eq(xpcInspector.eventLoopNestLevel, 1);

    // Let the debuggee continue execution.
    gClient.request({ to: aThreadActor, type: "resume" }, cleanup);
  });
}

function cleanup()
{
  gClient.addListener("closed", function(aEvent, aResult) {
    do_test_finished();
  });

  try {
    let xpcInspector = Cc["@mozilla.org/jsinspector;1"].getService(Ci.nsIJSInspector);
    do_check_eq(xpcInspector.eventLoopNestLevel, 0);
  } catch(e) {
    dump(e);
  }

  gClient.close();
}
