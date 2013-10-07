/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check a frame actor's arguments property.
 */

var gDebuggee;
var gClient;
var gThreadClient;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-stack");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-stack", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_pause_frame();
    });
  });
  do_test_pending();
}

function test_pause_frame()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    let args = aPacket.frame["arguments"];
    do_check_eq(args.length, 6);
    do_check_eq(args[0], 42);
    do_check_eq(args[1], true);
    do_check_eq(args[2], "nasu");
    do_check_eq(args[3].type, "null");
    do_check_eq(args[4].type, "undefined");
    do_check_eq(args[5].type, "object");
    do_check_eq(args[5].class, "Object");
    do_check_true(!!args[5].actor);

    gThreadClient.resume(function() {
      finishClient(gClient);
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(aNumber, aBool, aString, aNull, aUndefined, aObject) {
      debugger;
    };
    stopMe(42, true, "nasu", null, undefined, { foo: "bar" });
  } + ")()");
}
