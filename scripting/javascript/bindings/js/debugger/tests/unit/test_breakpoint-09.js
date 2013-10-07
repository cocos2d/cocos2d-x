/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that removing a breakpoint works.
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
      test_remove_breakpoint();
    });
  });
  do_test_pending();
}

function test_remove_breakpoint()
{
  let done = false;
  gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
    let path = getFilePath('test_breakpoint-09.js');
    let location = { url: path, line: gDebuggee.line0 + 2};
    gThreadClient.setBreakpoint(location, function (aResponse, bpClient) {
      gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
        // Check the return value.
        do_check_eq(aPacket.type, "paused");
        do_check_eq(aPacket.frame.where.url, path);
        do_check_eq(aPacket.frame.where.line, location.line);
        do_check_eq(aPacket.why.type, "breakpoint");
        do_check_eq(aPacket.why.actors[0], bpClient.actor);
        // Check that the breakpoint worked.
        do_check_eq(gDebuggee.a, undefined);

        // Remove the breakpoint.
        bpClient.remove(function (aResponse) {
          done = true;
          gThreadClient.addOneTimeListener("paused",
                                           function (aEvent, aPacket) {
            // The breakpoint should not be hit again.
            gThreadClient.resume(function () {
              do_check_true(false);
            });
          });
          gThreadClient.resume();
        });

      });
      // Continue until the breakpoint is hit.
      gThreadClient.resume();

    });

  });

  gDebuggee.eval("var line0 = Error().lineNumber;\n" +
                 "function foo(stop) {\n" + // line0 + 1
                 "  this.a = 1;\n" +        // line0 + 2
                 "  if (stop) return;\n" +  // line0 + 3
                 "  delete this.a;\n" +     // line0 + 4
                 "  foo(true);\n" +         // line0 + 5
                 "}\n" +                    // line0 + 6
                 "debugger;\n" +            // line1 + 7
                 "foo();\n");               // line1 + 8
  if (!done) {
    do_check_true(false);
  }
  finishClient(gClient);
}
