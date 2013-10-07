/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check eval resume/re-pause with a throw.
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
      test_throw_eval();
    });
  });
  do_test_pending();
}

function test_throw_eval()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    gThreadClient.eval(null, "throw 'failure'", function(aResponse) {
      do_check_eq(aResponse.type, "resumed");
      // Expect a pause notification immediately.
      gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
        // Check the return value...
        do_check_eq(aPacket.type, "paused");
        do_check_eq(aPacket.why.type, "clientEvaluated");
        do_check_eq(aPacket.why.frameFinished.throw, "failure");
        gThreadClient.resume(function() {
          finishClient(gClient);
        });
      });
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(arg1) { debugger; };
    stopMe({obj: true});
  } + ")()");
}
