/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Make sure that releasing a pause-lifetime actorin a releaseMany returns an
 * error, but releases all the thread-lifetime actors.
 */

var gDebuggee;
var gClient;
var gThreadClient;
var gPauseGrip;

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

function arg_grips(aFrameArgs, aOnResponse) {
  let grips = [];
  let handler = function (aResponse) {
    if (aResponse.error) {
      grips.push(aResponse.error);
    } else {
      grips.push(aResponse.from);
    }
    if (grips.length == aFrameArgs.length) {
      aOnResponse(grips);
    }
  };
  for (let i = 0; i < aFrameArgs.length; i++) {
    gClient.request({ to: aFrameArgs[i].actor, type: "threadGrip" },
                    handler);
  }
}

function test_thread_lifetime()
{
  // Get two thread-lifetime grips.
  gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {

    let frameArgs = [ aPacket.frame.arguments[0], aPacket.frame.arguments[1] ];
    gPauseGrip = aPacket.frame.arguments[2];
    arg_grips(frameArgs, function (aGrips) {
      release_grips(frameArgs, aGrips);
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(arg1, arg2, arg3) {
      debugger;
    };
    stopMe({obj: 1}, {obj: 2}, {obj: 3});
    ")"
  } + ")()");
}


function release_grips(aFrameArgs, aThreadGrips)
{
  // Release all actors with releaseMany...
  let release = [aThreadGrips[0], aThreadGrips[1], gPauseGrip.actor];
  gThreadClient.releaseMany(release, function (aResponse) {
    do_check_eq(aResponse.error, "notReleasable");
    // Now ask for thread grips again, they should not exist.
    arg_grips(aFrameArgs, function (aNewGrips) {
      for (let i = 0; i < aNewGrips.length; i++) {
        do_check_eq(aNewGrips[i], "noSuchActor");
      }
      gThreadClient.resume(function () {
        finishClient(gClient);
      });
    });
  });
}
