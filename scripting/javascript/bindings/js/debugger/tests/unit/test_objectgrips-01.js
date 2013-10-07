/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

var gDebuggee;
var gClient;
var gThreadClient;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-grips");
  gDebuggee.eval(function stopMe(arg1) {
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
    let args = aPacket.frame.arguments;

    do_check_eq(args[0].class, "Object");

    let objClient = gThreadClient.pauseGrip(args[0]);
    objClient.getOwnPropertyNames(function(aResponse) {
      do_check_eq(aResponse.ownPropertyNames.length, 3);
      do_check_eq(aResponse.ownPropertyNames[0], "a");
      do_check_eq(aResponse.ownPropertyNames[1], "b");
      do_check_eq(aResponse.ownPropertyNames[2], "c");

      gThreadClient.resume(function() {
        finishClient(gClient);
      });
    });

  });

  gDebuggee.eval("stopMe({ a: 1, b: true, c: 'foo' })");
}

