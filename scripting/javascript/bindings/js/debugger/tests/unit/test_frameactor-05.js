/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Verify that frame actors retrieved with the frames request
 * are included in the pause packet's popped-frames property.
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

function test_frame_slice() {
  if (gSliceTests.length == 0) {
    gThreadClient.resume(function() { finishClient(gClient); });
    return;
  }

  let test = gSliceTests.shift();
  gThreadClient.getFrames(test.start, test.count, function(aResponse) {
    var testFrames = gFrames.slice(test.start, test.count ? test.start + test.count : undefined);
    do_check_eq(testFrames.length, aResponse.frames.length);
    for (var i = 0; i < testFrames.length; i++) {
      let expected = testFrames[i];
      let actual = aResponse.frames[i];

      if (test.resetActors) {
        expected.actor = actual.actor;
      }

      for (var key in expected) {
        do_check_eq(expected[key], actual[key]);
      }
    }
    test_frame_slice();
  });
}

function test_pause_frame()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket1) {
    gThreadClient.getFrames(0, null, function(aFrameResponse) {
      do_check_eq(aFrameResponse.frames.length, 5);
      // Now wait for the next pause, after which the three
      // youngest actors should be popped..
      let expectPopped = [frame.actor for each (frame in aFrameResponse.frames.slice(0, 3))];
      expectPopped.sort()

      gThreadClient.addOneTimeListener("paused", function(aEvent, aPausePacket) {
        let popped = aPausePacket.poppedFrames.sort();
        do_check_eq(popped.length, 3);
        for (let i = 0; i < 3; i++) {
          do_check_eq(expectPopped[i], popped[i]);
        }

        gThreadClient.resume(function() { finishClient(gClient); });
      });
      gThreadClient.resume();
    });
  });

  gDebuggee.eval("(" + function() {
    function depth3() {
      debugger;
    }
    function depth2() {
      depth3();
    }
    function depth1() {
      depth2();
    };
    depth1();
    debugger;
    ")"
  } + ")()");
}
