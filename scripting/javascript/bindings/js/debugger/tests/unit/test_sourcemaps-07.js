/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Test that we don't permanently cache sources from source maps.
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
      test_cached_original_sources();
    });
  });
  do_test_pending();
}

function test_cached_original_sources()
{
  writeFile("temp.foobar", "initial content");

  gClient.addOneTimeListener("newSource", onNewSource);

  let node = new SourceNode(1, 0,
                            getFileUrl("temp.foobar"),
                            "function funcFromTemp() {}\n");
  let { code, map } = node.toStringWithSourceMap({
    file: "abc.js"
  });
  code += "//# sourceMappingURL=data:text/json;base64," + btoa(map.toString());


  Components.utils.evalInSandbox(code, gDebuggee, "1.8",
                                 "http://example.com/www/js/abc.js", 1);
}

function onNewSource(aEvent, aPacket) {
  let sourceClient = gThreadClient.source(aPacket.source);
  sourceClient.source(function (aResponse) {
    do_check_true(!aResponse.error,
                  "Should not be an error grabbing the source");
    do_check_eq(aResponse.source, "initial content",
                "The correct source content should be sent");

    writeFile("temp.foobar", "new content");

    sourceClient.source(function (aResponse) {
      do_check_true(!aResponse.error,
                    "Should not be an error grabbing the source");
      do_check_eq(aResponse.source, "new content",
                  "The correct source content should not be cached, so we should get the new content");

      do_get_file("temp.foobar").remove(false);
      finishClient(gClient);
    });
  });
}
