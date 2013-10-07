/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check pauses within evals.
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
      test_syntax_error_eval();
    });
  });
  do_test_pending();
}

function test_syntax_error_eval()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    gThreadClient.eval(null, "debugger", function(aResponse) {
      // Expect a resume then a debuggerStatement pause.
      do_check_eq(aResponse.type, "resumed");
      gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
        do_check_eq(aPacket.why.type, "debuggerStatement");
        // Resume from the debugger statement should immediately re-pause
        // with a clientEvaluated reason.
        gThreadClient.resume(function(aPacket) {
          do_check_eq(aPacket.type, "resumed");
          gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
            do_check_eq(aPacket.why.type, "clientEvaluated");
            gThreadClient.resume(function() {
              finishClient(gClient);
            });
          });
        });
      });
    });
  });
  gDebuggee.eval("(" + function() {
    function stopMe(arg) {
      debugger;
    }
    stopMe();
  } + ")()");
}
