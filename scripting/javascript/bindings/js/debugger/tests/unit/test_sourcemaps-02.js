/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check basic source map integration with the "sources" packet in the RDP.
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
      test_simple_source_map();
    });
  });
  do_test_pending();
}

function test_simple_source_map()
{
  // Because we are source mapping, we should be notified of a.js, b.js, and
  // c.js as sources, and shouldn"t receive abc.js or test_sourcemaps-01.js.
  let expectedSources = new Set(["http://example.com/www/js/a.js",
                                 "http://example.com/www/js/b.js",
                                 "http://example.com/www/js/c.js"]);

  let numNewSources = 0;

  gClient.addOneTimeListener("paused", function (aEvent, aPacket) {
    gThreadClient.getSources(function (aResponse) {
      do_check_true(!aResponse.error, "Should not get an error");

      for (let s of aResponse.sources) {
        do_check_neq(s.url, "http://example.com/www/js/abc.js",
                     "Shouldn't get the generated source's url.")
        expectedSources.delete(s.url);
      }

      do_check_eq(expectedSources.size, 0,
                  "Should have found all the expected sources sources by now.");

      finishClient(gClient);
    });
  });

  let { code, map } = (new SourceNode(null, null, null, [
    new SourceNode(1, 0, "a.js", "function a() { return 'a'; }\n"),
    new SourceNode(1, 0, "b.js", "function b() { return 'b'; }\n"),
    new SourceNode(1, 0, "c.js", "function c() { return 'c'; }\n"),
    "debugger;\n"
  ])).toStringWithSourceMap({
    file: "abc.js",
    sourceRoot: "http://example.com/www/js/"
  });

  code += "//# sourceMappingURL=data:text/json;base64," + btoa(map.toString());

  Components.utils.evalInSandbox(code, gDebuggee, "1.8",
                                 "http://example.com/www/js/abc.js", 1);
}
