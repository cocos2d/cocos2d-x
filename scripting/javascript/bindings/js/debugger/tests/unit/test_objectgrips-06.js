/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * This test checks that sealed objects report themselves as sealed in their
 * grip.
 */

var gDebuggee;
var gClient;
var gThreadClient;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-grips");
  gDebuggee.eval(function stopMe(arg1, arg2) {
    debugger;
  }.toString());

  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-grips", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_object_grip();
    });
  });
  do_test_pending();
}

function test_object_grip()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    let obj1 = aPacket.frame.arguments[0];
    do_check_true(obj1.sealed);

    let obj1Client = gThreadClient.pauseGrip(obj1);
    do_check_true(obj1Client.isSealed);

    let obj2 = aPacket.frame.arguments[1];
    do_check_false(obj2.sealed);

    let obj2Client = gThreadClient.pauseGrip(obj2);
    do_check_false(obj2Client.isSealed);

    gThreadClient.resume(_ => {
      finishClient(gClient);
    });
  });

  gDebuggee.eval("(" + function () {
    let obj1 = {};
    Object.seal(obj1);
    stopMe(obj1, {});
  } + "())");
}

