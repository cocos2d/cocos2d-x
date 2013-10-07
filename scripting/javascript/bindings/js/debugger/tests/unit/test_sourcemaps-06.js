/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that we can load sources whose content is embedded in the
 * "sourcesContent" field of a source map.
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
      test_source_content();
    });
  });
  do_test_pending();
}

function test_source_content()
{
  let numNewSources = 0;

  gClient.addListener("newSource", function _onNewSource(aEvent, aPacket) {
    if (++numNewSources !== 3) {
      return;
    }
    gClient.removeListener("newSource", _onNewSource);

    gThreadClient.getSources(function (aResponse) {
      do_check_true(!aResponse.error, "Should not get an error");

      testContents(aResponse.sources, () => {
        finishClient(gClient);
      });
    });
  });

  let node = new SourceNode(null, null, null, [
    new SourceNode(1, 0, "a.js", "function a() { return 'a'; }\n"),
    new SourceNode(1, 0, "b.js", "function b() { return 'b'; }\n"),
    new SourceNode(1, 0, "c.js", "function c() { return 'c'; }\n"),
  ]);

  node.setSourceContent("a.js", "content for a.js");
  node.setSourceContent("b.js", "content for b.js");
  node.setSourceContent("c.js", "content for c.js");

  let { code, map } = node.toStringWithSourceMap({
    file: "abc.js"
  });

  code += "//# sourceMappingURL=data:text/json;base64," + btoa(map.toString());

  Components.utils.evalInSandbox(code, gDebuggee, "1.8",
                                 "http://example.com/www/js/abc.js", 1);
}

function testContents(aSources, aCallback) {
  if (aSources.length === 0) {
    return aCallback();
  }

  let source = aSources[0];
  let sourceClient = gThreadClient.source(aSources[0]);

  sourceClient.source((aResponse) => {
    do_check_true(!aResponse.error,
                  "Should not get an error loading the source from sourcesContent");

    let expectedContent = "content for " + source.url;
    do_check_eq(aResponse.source, expectedContent,
                "Should have the expected source content");

    testContents(aSources.slice(1), aCallback);
  });
}
