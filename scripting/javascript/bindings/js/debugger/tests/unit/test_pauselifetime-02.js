/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that pause-lifetime grips go away correctly after a resume.
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

function test_pause_frame()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    let args = aPacket.frame.arguments;
    let objActor = args[0].actor;
    do_check_eq(args[0].class, "Object");
    do_check_true(!!objActor);

    // Make a bogus request to the grip actor.  Should get
    // unrecognized-packet-type (and not no-such-actor).
    gClient.request({ to: objActor, type: "bogusRequest" }, function(aResponse) {
      do_check_eq(aResponse.error, "unrecognizedPacketType");

      gThreadClient.resume(function() {
        // Now that we've resumed, should get no-such-actor for the
        // same request.
        gClient.request({ to: objActor, type: "bogusRequest" }, function(aResponse) {
          do_check_eq(aResponse.error, "noSuchActor");
          finishClient(gClient);
        });
      });
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(aObject) {
      debugger;
    };
    stopMe({ foo: "bar" });
    ")"
  } + ")()");
}
