/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that setting a breakpoint in a line with multiple entry points
 * triggers no matter which entry point we reach.
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
    let path = getFilePath('test_breakpoint-10.js');
    let location = { url: path, line: gDebuggee.line0 + 3};
    gThreadClient.setBreakpoint(location, function (aResponse, bpClient) {
      // actualLocation is not returned when breakpoints don't skip forward.
      do_check_eq(aResponse.actualLocation, undefined);
      gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
        // Check the return value.
        do_check_eq(aPacket.type, "paused");
        do_check_eq(aPacket.why.type, "breakpoint");
        do_check_eq(aPacket.why.actors[0], bpClient.actor);
        // Check that the breakpoint worked.
        do_check_eq(gDebuggee.i, 0);

        gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
          // Check the return value.
          do_check_eq(aPacket.type, "paused");
          do_check_eq(aPacket.why.type, "breakpoint");
          do_check_eq(aPacket.why.actors[0], bpClient.actor);
          // Check that the breakpoint worked.
          do_check_eq(gDebuggee.i, 1);

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
                 "var a, i = 0;\n" +                  // line0 + 2
                 "for (i = 1; i <= 2; i++) {\n" +     // line0 + 3
                 "  a = i;\n" +                       // line0 + 4
                 "}\n");                              // line0 + 5
}
