/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that setting breakpoints when the debuggee is running works.
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
      test_breakpoint_running();
    });
  });
  do_test_pending();
}

function test_breakpoint_running()
{
  gDebuggee.eval("var line0 = Error().lineNumber;\n" +
                 "var a = 1;\n" +  // line0 + 1
                 "var b = 2;\n");  // line0 + 2

  let path = getFilePath('test_breakpoint-02.js');
  let location = { url: path, line: gDebuggee.line0 + 2};

  // Setting the breakpoint later should interrupt the debuggee.
  gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
    do_check_eq(aPacket.type, "paused");
    do_check_eq(aPacket.why.type, "interrupted");
  });

  gThreadClient.setBreakpoint(location, function(aResponse) {
    // Eval scripts don't stick around long enough for the breakpoint to be set,
    // so just make sure we got the expected response from the actor.
    do_check_neq(aResponse.error, "noScript");

    do_execute_soon(function() {
      finishClient(gClient);
    });
  });
}
