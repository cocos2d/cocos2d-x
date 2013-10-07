/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check basic source map integration with the "newSource" packet in the RDP.
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

function test_simple_source_map()
{
  // Because we are source mapping, we should be notified of a.js, b.js, and
  // c.js as sources, and shouldn't receive abc.js or test_sourcemaps-01.js.
  let expectedSources = new Set(["http://example.com/www/js/a.js",
                                 "http://example.com/www/js/b.js",
                                 "http://example.com/www/js/c.js"]);

  gClient.addListener("newSource", function _onNewSource(aEvent, aPacket) {
    do_check_eq(aEvent, "newSource");
    do_check_eq(aPacket.type, "newSource");
    do_check_true(!!aPacket.source);

    do_check_true(expectedSources.has(aPacket.source.url),
                  "The source url should be one of our original sources.");
    expectedSources.delete(aPacket.source.url);

    if (expectedSources.size === 0) {
      gClient.removeListener("newSource", _onNewSource);
      finishClient(gClient);
    }
  });

  let { code, map } = (new SourceNode(null, null, null, [
    new SourceNode(1, 0, "a.js", "function a() { return 'a'; }\n"),
    new SourceNode(1, 0, "b.js", "function b() { return 'b'; }\n"),
    new SourceNode(1, 0, "c.js", "function c() { return 'c'; }\n"),
  ])).toStringWithSourceMap({
    file: "abc.js",
    sourceRoot: "http://example.com/www/js/"
  });

  code += "//# sourceMappingURL=data:text/json;base64," + btoa(map.toString());

  Components.utils.evalInSandbox(code, gDebuggee, "1.8",
                                 "http://example.com/www/js/abc.js", 1);
}
