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
  // Get three thread-lifetime grips.
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    let grips = [];

    let handler = function(aResponse) {
      if (aResponse.error) {
        do_check_eq(aResponse.error, '');
        finishClient(gClient);
      }
      grips.push(aResponse.from);
      if (grips.length == 3) {
        test_release_many(grips);
      }
    };
    for (let i = 0; i < 3; i++) {
      gClient.request({ to: aPacket.frame.arguments[i].actor, type: "threadGrip" },
                      handler);
    }
  });

  gDebuggee.eval("(" + function() {
    function stopMe(arg1, arg2, arg3) {
      debugger;
    };
    stopMe({obj: 1}, {obj: 2}, {obj: 3});
    ")"
  } + ")()");
}

function test_release_many(grips)
{
  // Release the first two grips, leave the third alive.

  let release = [grips[0], grips[1]];

  gThreadClient.releaseMany(release, function(aResponse) {
    // First two actors should return a noSuchActor error, because
    // they're gone now.
    gClient.request({ to: grips[0], type: "bogusRequest" }, function(aResponse) {
      do_check_eq(aResponse.error, "noSuchActor");
      gClient.request({ to: grips[1], type: "bogusRequest" }, function(aResponse) {
        do_check_eq(aResponse.error, "noSuchActor");

        // Last actor should return unrecognizedPacketType, because it's still
        // alive.
        gClient.request({ to: grips[2], type: "bogusRequest" }, function(aResponse) {
          do_check_eq(aResponse.error, "unrecognizedPacketType");
          gThreadClient.resume(function() {
            finishClient(gClient);
          });
        });
      });
    });
  });
}
