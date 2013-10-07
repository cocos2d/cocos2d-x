/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that requesting a thread-lifetime actor twice for the same
 * value returns the same actor.
 */

var gDebuggee;
var gClient;
var gThreadClient;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-grips");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-grips", function (aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_thread_lifetime();
    });
  });
  do_test_pending();
}

function test_thread_lifetime()
{
  gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
    let pauseGrip = aPacket.frame.arguments[0];

    gClient.request({ to: pauseGrip.actor, type: "threadGrip" }, function (aResponse) {
      // Successful promotion won't return an error.
      do_check_eq(aResponse.error, undefined);

      let threadGrip1 = aResponse.from;

      gClient.request({ to: pauseGrip.actor, type: "threadGrip" }, function (aResponse) {
        do_check_eq(threadGrip1, aResponse.from);
        gThreadClient.resume(function() {
          finishClient(gClient);
        });
      });
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(arg1) {
      debugger;
    };
    stopMe({obj: true});
    ")"
  } + ")()");
}
