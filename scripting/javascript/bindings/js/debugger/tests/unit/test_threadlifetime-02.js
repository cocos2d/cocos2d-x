/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that thread-lifetime grips last past a resume.
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
    attachTestTabAndResume(gClient, "test-grips", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_thread_lifetime();
    });
  });
  do_test_pending();
}

function test_thread_lifetime()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    let pauseGrip = aPacket.frame.arguments[0];

    // Create a thread-lifetime actor for this object.
    gClient.request({ to: pauseGrip.actor, type: "threadGrip" }, function(aResponse) {
      // Successful promotion won't return an error.
      do_check_eq(aResponse.error, undefined);
      gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
        // Verify that the promoted actor is returned again.
        do_check_eq(pauseGrip.actor, aPacket.frame.arguments[0].actor);
        // Now that we've resumed, release the thread-lifetime grip.
        gClient.release(pauseGrip.actor, function(aResponse) {
          gClient.request({ to: pauseGrip.actor, type: "bogusRequest" }, function(aResponse) {
            do_check_eq(aResponse.error, "noSuchActor");
            gThreadClient.resume(function(aResponse) {
              finishClient(gClient);
            });
          });
        });
      });
      gThreadClient.resume();
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(arg1) {
      debugger;
      debugger;
    };
    stopMe({obj: true});
    ")"
  } + ")()");
}
