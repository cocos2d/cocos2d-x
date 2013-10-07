/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that promoting multiple pause-lifetime actors to thread-lifetime actors
 * works as expected.
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
    let actors = [];
    let last;
    for (let aGrip of aPacket.frame.arguments) {
      actors.push(aGrip.actor);
      last = aGrip.actor;
    }

    // Create thread-lifetime actors for these objects.
    gThreadClient.threadGrips(actors, function(aResponse) {
      // Successful promotion won't return an error.
      do_check_eq(aResponse.error, undefined);

      gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
        // Verify that the promoted actors are returned again.
        actors.forEach(function(actor, i) {
          do_check_eq(actor, aPacket.frame.arguments[i].actor);
        });
        // Now that we've resumed, release the thread-lifetime grips.
        gThreadClient.releaseMany(actors, function(aResponse) {
          // Successful release won't return an error.
          do_check_eq(aResponse.error, undefined);

          gClient.request({ to: last, type: "bogusRequest" }, function(aResponse) {
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
    function stopMe(arg1, arg2, arg3) {
      debugger;
      debugger;
    };
    stopMe({obj: 1}, {obj: 2}, {obj: 3});
    ")"
  } + ")()");
}
