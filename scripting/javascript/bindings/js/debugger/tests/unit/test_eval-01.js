/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check basic eval resume/re-pause
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
      test_simple_eval();
    });
  });
  do_test_pending();
}

function test_simple_eval()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    let arg1Actor = aPacket.frame.arguments[0].actor;
    gThreadClient.eval(null, "({ obj: true })", function(aResponse) {
      do_check_eq(aResponse.type, "resumed");
      // Expect a pause notification immediately.
      gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
        // Check the return value...
        do_check_eq(aPacket.type, "paused");
        do_check_eq(aPacket.why.type, "clientEvaluated");
        do_check_eq(aPacket.why.frameFinished.return.type, "object");
        do_check_eq(aPacket.why.frameFinished.return.class, "Object");

        // Make sure the previous pause lifetime was correctly dropped.
        gClient.request({ to: arg1Actor, type: "bogusRequest" }, function(aResponse) {
          do_check_eq(aResponse.error, "noSuchActor");
          gThreadClient.resume(function() {
            finishClient(gClient);
          });
        });

      });

    });

  });

  gDebuggee.eval("(" + function() {
    function stopMe(arg1) { debugger; };
    stopMe({obj: true});
  } + ")()");
}
