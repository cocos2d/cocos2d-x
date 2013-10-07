/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check setting breakpoints in source mapped sources.
 */

var gDebuggee;
var gClient;
var gThreadClient;

Components.utils.import('resource:///modules/devtools/SourceMap.jsm');

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-source-map");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-source-map", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_simple_source_map();
    });
  });
  do_test_pending();
}

function testBreakpointMapping(aName, aCallback)
{
  // Pause so we can set a breakpoint.
  gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
    do_check_true(!aPacket.error);
    do_check_eq(aPacket.why.type, "debuggerStatement");

    gThreadClient.setBreakpoint({
      url: "http://example.com/www/js/" + aName + ".js",
      // Setting the breakpoint on an empty line so that it is pushed down one
      // line and we can check the source mapped actualLocation later.
      line: 3,
      column: 0
    }, function (aResponse) {
      do_check_true(!aResponse.error);

      // Actual location should come back source mapped still so that
      // breakpoints are displayed in the UI correctly, etc.
      do_check_eq(aResponse.actualLocation.line, 4);
      do_check_eq(aResponse.actualLocation.url,
                  "http://example.com/www/js/" + aName + ".js");

      // The eval will cause us to resume, then we get an unsolicited pause
      // because of our breakpoint, we resume again to finish the eval, and
      // finally receive our last pause which has the result of the client
      // evaluation.
      gThreadClient.eval(null, aName + "()", function (aResponse) {
        do_check_true(!aResponse.error, "Shouldn't be an error resuming to eval");
        do_check_eq(aResponse.type, "resumed");

        gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
          do_check_eq(aPacket.why.type, "breakpoint");
          // Assert that we paused because of the breakpoint at the correct
          // location in the code by testing that the value of `ret` is still
          // undefined.
          do_check_eq(aPacket.frame.environment.bindings.variables.ret.value.type,
                      "undefined");

          gThreadClient.resume(function (aResponse) {
            do_check_true(!aResponse.error);

            gThreadClient.addOneTimeListener("paused", function (aEvent, aPacket) {
              do_check_eq(aPacket.why.type, "clientEvaluated");
              do_check_eq(aPacket.why.frameFinished.return, aName);

              gThreadClient.resume(function (aResponse) {
                do_check_true(!aResponse.error);
                aCallback();
              });
            });
          });
        });
      });
    });
  });

  gDebuggee.eval("(" + function () {
    debugger;
  } + "());");
}

function test_simple_source_map()
{
  let expectedSources = new Set([
    "http://example.com/www/js/a.js",
    "http://example.com/www/js/b.js",
    "http://example.com/www/js/c.js"
  ]);

  gClient.addListener("newSource", function _onNewSource(aEvent, aPacket) {
    expectedSources.delete(aPacket.source.url);
    if (expectedSources.size > 0) {
      return;
    }
    gClient.removeListener("newSource", _onNewSource);

    testBreakpointMapping("a", function () {
      testBreakpointMapping("b", function () {
        testBreakpointMapping("c", function () {
          finishClient(gClient);
        });
      });
    });
  });

  let a = new SourceNode(null, null, null, [
    new SourceNode(1, 0, "a.js", "function a() {\n"),
    new SourceNode(2, 0, "a.js", "  var ret;\n"),
    new SourceNode(3, 0, "a.js", "  // Empty line\n"),
    new SourceNode(4, 0, "a.js", "  ret = 'a';\n"),
    new SourceNode(5, 0, "a.js", "  return ret;\n"),
    new SourceNode(6, 0, "a.js", "}\n")
  ]);
  let b = new SourceNode(null, null, null, [
    new SourceNode(1, 0, "b.js", "function b() {\n"),
    new SourceNode(2, 0, "b.js", "  var ret;\n"),
    new SourceNode(3, 0, "b.js", "  // Empty line\n"),
    new SourceNode(4, 0, "b.js", "  ret = 'b';\n"),
    new SourceNode(5, 0, "b.js", "  return ret;\n"),
    new SourceNode(6, 0, "b.js", "}\n")
  ]);
  let c = new SourceNode(null, null, null, [
    new SourceNode(1, 0, "c.js", "function c() {\n"),
    new SourceNode(2, 0, "c.js", "  var ret;\n"),
    new SourceNode(3, 0, "c.js", "  // Empty line\n"),
    new SourceNode(4, 0, "c.js", "  ret = 'c';\n"),
    new SourceNode(5, 0, "c.js", "  return ret;\n"),
    new SourceNode(6, 0, "c.js", "}\n")
  ]);

  let { code, map } = (new SourceNode(null, null, null, [
    a, b, c
  ])).toStringWithSourceMap({
    file: "http://example.com/www/js/abc.js",
    sourceRoot: "http://example.com/www/js/"
  });

  code += "//# sourceMappingURL=data:text/json;base64," + btoa(map.toString());

  Components.utils.evalInSandbox(code, gDebuggee, "1.8",
                                 "http://example.com/www/js/abc.js", 1);
}
