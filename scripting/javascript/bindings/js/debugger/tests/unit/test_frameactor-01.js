/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Verify that we get a frame actor along with a debugger statement.
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
    do_check_true(!!aPacket.frame);
    do_check_true(!!aPacket.frame.actor);
    do_check_eq(aPacket.frame.callee.name, "stopMe");
    gThreadClient.resume(function() {
      finishClient(gClient);
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe() {
      debugger;
    };
    stopMe();
    ")"
  } + ")()");
}
