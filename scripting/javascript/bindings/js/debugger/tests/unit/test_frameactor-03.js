/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Verify that a frame actor is properly expired when the frame goes away.
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
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket1) {
    gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket2) {
      let poppedFrames = aPacket2.poppedFrames;
      do_check_eq(typeof(poppedFrames), typeof([]));
      do_check_true(poppedFrames.indexOf(aPacket1.frame.actor) >= 0);
      gThreadClient.resume(function() {
        finishClient(gClient);
      });
    });
    gThreadClient.resume();
  });

  gDebuggee.eval("(" + function() {
    function stopMe() {
      debugger;
     };
    stopMe();
    debugger;
    ")"
  } + ")()");
}
