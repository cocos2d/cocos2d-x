/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Test that requesting a pause actor for the same value multiple
 * times returns the same actor.
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
    let args = aPacket.frame.arguments;
    let objActor1 = args[0].actor;

    gThreadClient.getFrames(0, 1, function(aResponse) {
      let frame = aResponse.frames[0];
      do_check_eq(objActor1, frame.arguments[0].actor);
      gThreadClient.resume(function () {
        finishClient(gClient);
      });
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(aObject) {
      debugger;
    };
    stopMe({ foo: "bar" });
    ")"
  } + ")()");
}
