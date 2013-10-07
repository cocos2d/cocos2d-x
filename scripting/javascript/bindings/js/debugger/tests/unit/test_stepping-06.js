/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that stepping out of a function returns the right return value.
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
      test_simple_stepping();
    });
  });
  do_test_pending();
}

function test_simple_stepping()
{
  gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
    gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
      // Check that the return value is 10.
      do_check_eq(aPacket.type, "paused");
      do_check_eq(aPacket.frame.where.line, gDebuggee.line0 + 4);
      do_check_eq(aPacket.why.type, "resumeLimit");
      do_check_eq(aPacket.why.frameFinished.return, 10);

      gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
        gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
          // Check that the return value is undefined.
          do_check_eq(aPacket.type, "paused");
          do_check_eq(aPacket.frame.where.line, gDebuggee.line0 + 7);
          do_check_eq(aPacket.why.type, "resumeLimit");
          do_check_eq(aPacket.why.frameFinished.return.type, "undefined");

          gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
            gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
              // Check that the exception was thrown.
              do_check_eq(aPacket.type, "paused");
              do_check_eq(aPacket.frame.where.line, gDebuggee.line0 + 12);
              do_check_eq(aPacket.why.type, "resumeLimit");
              do_check_eq(aPacket.why.frameFinished.throw, "ah");

              gThreadClient.resume(function () {
                finishClient(gClient);
              });
            });
            gThreadClient.stepOut();
          });
          gThreadClient.resume();
        });
        gThreadClient.stepOut();
      });
      gThreadClient.resume();
    });
    gThreadClient.stepOut();

  });

  gDebuggee.eval("var line0 = Error().lineNumber;\n" +
                 "function f() {\n" + // line0 + 1
                 "  debugger;\n" +    // line0 + 2
                 "  var a = 10;\n" +  // line0 + 3
                 "  return a;\n" +    // line0 + 4
                 "}\n" +              // line0 + 5
                 "function g() {\n" + // line0 + 6
                 "  debugger;\n" +    // line0 + 7
                 "}\n" +              // line0 + 8
                 "function h() {\n" + // line0 + 9
                 "  debugger;\n" +    // line0 + 10
                 "  throw 'ah';\n" +  // line0 + 11
                 "  return 2;\n" +    // line0 + 12
                 "}\n" +              // line0 + 13
                 "f();\n" +           // line0 + 14
                 "g();\n" +           // line0 + 15
                 "h();\n");           // line0 + 16
}
