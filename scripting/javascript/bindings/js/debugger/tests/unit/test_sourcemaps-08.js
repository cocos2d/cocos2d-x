/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Regression test for bug 882986 regarding sourcesContent and absolute source
 * URLs.
 */

var gDebuggee;
var gClient;
var gThreadClient;

Components.utils.import("resource:///modules/devtools/SourceMap.jsm");

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-source-map");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-source-map", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_source_maps();
    });
  });
  do_test_pending();
}

function test_source_maps()
{
  gClient.addOneTimeListener("newSource", function (aEvent, aPacket) {
    let sourceClient = gThreadClient.source(aPacket.source);
    sourceClient.source(function ({error, source}) {
      do_check_true(!error, "should be able to grab the source");
      do_check_eq(source, "foo",
                  "Should load the source from the sourcesContent field");
      finishClient(gClient);
    });
  });

  let code = "'nothing here';\n";
  code += "//# sourceMappingURL=data:text/json," + JSON.stringify({
    version: 3,
    file: "foo.js",
    sources: ["/a"],
    names: [],
    mappings: "AACA",
    sourcesContent: ["foo"]
  });
  Components.utils.evalInSandbox(code, gDebuggee, "1.8",
                                 "http://example.com/foo.js", 1);
}
