/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check evals against different frames.
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

    gThreadClient.getFrames(0, 2, function(aResponse) {
      let frame0 = aResponse.frames[0];
      let frame1 = aResponse.frames[1];

      // Eval against the top frame...
      gThreadClient.eval(frame0.actor, "arg", function(aResponse) {
        do_check_eq(aResponse.type, "resumed");
        gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
          // 'arg' should have been evaluated in frame0
          do_check_eq(aPacket.type, "paused");
          do_check_eq(aPacket.why.type, "clientEvaluated");
          do_check_eq(aPacket.why.frameFinished.return, "arg0");

          // Now eval against the second frame.
          gThreadClient.eval(frame1.actor, "arg", function(aResponse) {
            gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
              // 'arg' should have been evaluated in frame1
              do_check_eq(aPacket.type, "paused");
              do_check_eq(aPacket.why.frameFinished.return, "arg1");

              gThreadClient.resume(function() {
                finishClient(gClient);
              });
            });
          });
        });
      });
    });
  });

  gDebuggee.eval("(" + function() {
    function frame0(arg) {
      debugger;
    }
    function frame1(arg) {
      frame0("arg0");
    }
    frame1("arg1");
  } + ")()");
}
