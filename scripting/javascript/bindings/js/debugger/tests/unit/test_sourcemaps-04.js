/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that absolute source map urls work.
 */

var gDebuggee;
var gClient;
var gThreadClient;

Components.utils.import('resource:///modules/devtools/SourceMap.jsm');

// Deep in the complicated labyrinth of code that this test invokes, beneath
// debugger callbacks, sandboxes and nested event loops, lies an exception.
// This exception lay sleeping since the dawn of time, held captive in a
// delicate balance of custom xpcshell error reporters and garbage data about
// the XPCCallContext stack. But bholley dug too greedily, and too deep, and
// awoke shadow and flame in the darkness of nsExternalHelperAppService.cpp.
// We must now trust in deep magic to ensure that it does not awaken again.
ignoreReportedErrors(true);

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-source-map");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-source-map", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_absolute_source_map();
    });
  });
  do_test_pending();
}

function test_absolute_source_map()
{
  gClient.addOneTimeListener("newSource", function _onNewSource(aEvent, aPacket) {
    do_check_eq(aEvent, "newSource");
    do_check_eq(aPacket.type, "newSource");
    do_check_true(!!aPacket.source);

    do_check_true(aPacket.source.url.indexOf("sourcemapped.coffee") !== -1,
                  "The new source should be a coffee file.");
    do_check_eq(aPacket.source.url.indexOf("sourcemapped.js"), -1,
                "The new source should not be a js file.");

    finishClient(gClient);
  });

  code = readFile("sourcemapped.js")
    + "\n//# sourceMappingURL=" + getFileUrl("source-map-data/sourcemapped.map");

  Components.utils.evalInSandbox(code, gDebuggee, "1.8",
                                 getFileUrl("sourcemapped.js"), 1);
}
