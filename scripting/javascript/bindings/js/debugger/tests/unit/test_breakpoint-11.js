/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Make sure that setting a breakpoint in a line with bytecodes in multiple
 * scripts, sets the breakpoint in all of them (bug 793214).
 */

var gDebuggee;
var gClient;
var gThreadClient;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-stack");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function () {
    attachTestTabAndResume(gClient, "test-stack", function (aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_child_breakpoint();
    });
  });
  do_test_pending();
}

function test_child_breakpoint()
{
  gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
    let path = getFilePath('test_breakpoint-11.js');
    let location = { url: path, line: gDebuggee.line0 + 2};
    gThreadClient.setBreakpoint(location, function (aResponse, bpClient) {
      // actualLocation is not returned when breakpoints don't skip forward.
      do_check_eq(aResponse.actualLocation, undefined);
      gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
        // Check the return value.
        do_check_eq(aPacket.type, "paused");
        do_check_eq(aPacket.why.type, "breakpoint");
        do_check_eq(aPacket.why.actors[0], bpClient.actor);
        // Check that the breakpoint worked.
        do_check_eq(gDebuggee.a, undefined);

        gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
          // Check the return value.
          do_check_eq(aPacket.type, "paused");
          do_check_eq(aPacket.why.type, "breakpoint");
          do_check_eq(aPacket.why.actors[0], bpClient.actor);
          // Check that the breakpoint worked.
          do_check_eq(gDebuggee.a.b, 1);
          do_check_eq(gDebuggee.res, undefined);

          // Remove the breakpoint.
          bpClient.remove(function (aResponse) {
            gThreadClient.resume(function () {
              finishClient(gClient);
            });
          });
        });

        // Continue until the breakpoint is hit again.
        gThreadClient.resume();

      });
      // Continue until the breakpoint is hit.
      gThreadClient.resume();

    });

  });


  gDebuggee.eval("var line0 = Error().lineNumber;\n" +
                 "debugger;\n" +                      // line0 + 1
                 "var a = { b: 1, f: function() { return 2; } };\n" + // line0+2
                 "var res = a.f();\n");               // line0 + 3
}
