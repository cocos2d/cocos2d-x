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
    objClient.getProperty("x", function(aResponse) {
      do_check_eq(aResponse.descriptor.configurable, true);
      do_check_eq(aResponse.descriptor.enumerable, true);
      do_check_eq(aResponse.descriptor.writable, true);
      do_check_eq(aResponse.descriptor.value, 10);

      objClient.getProperty("y", function(aResponse) {
        do_check_eq(aResponse.descriptor.configurable, true);
        do_check_eq(aResponse.descriptor.enumerable, true);
        do_check_eq(aResponse.descriptor.writable, true);
        do_check_eq(aResponse.descriptor.value, "kaiju");

        objClient.getProperty("a", function(aResponse) {
          do_check_eq(aResponse.descriptor.configurable, true);
          do_check_eq(aResponse.descriptor.enumerable, true);
          do_check_eq(aResponse.descriptor.get.type, "object");
          do_check_eq(aResponse.descriptor.get.class, "Function");
          do_check_eq(aResponse.descriptor.set.type, "undefined");

          gThreadClient.resume(function() {
            finishClient(gClient);
          });
        });
      });
    });

  });

  gDebuggee.eval("stopMe({ x: 10, y: 'kaiju', get a() { return 42; } })");
}

