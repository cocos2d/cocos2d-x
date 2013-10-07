/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check that "sources" and "newSource" packets are handled in a backwards
 * compatible way.
 */

var gDebuggee;
var gClient;
var gTabClient;
var gThreadClient;

var gNumTimesSourcesSent = 0;

function run_test()
{
  initSourcesBackwardsCompatDebuggerServer();
  gDebuggee = addTestGlobal("test-sources-compat");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.request = (function (request) {
    return function (aRequest, aOnResponse) {
      if (aRequest.type === "sources") {
        ++gNumTimesSourcesSent;
      }
      return request.call(this, aRequest, aOnResponse);
    };
  }(gClient.request));
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-sources-compat", function (aResponse,
                                                                     aTabClient,
                                                                     aThreadClient) {
      gTabClient = aTabClient;
      gThreadClient = aThreadClient;
      test_new_source_compatibility();
    });
  });
  do_test_pending();
}

function test_new_source_compatibility()
{
  gClient.addOneTimeListener("newSource", function (aEvent, aPacket) {
    do_check_eq(aEvent, "newSource");
    do_check_eq(aPacket.type, "newSource");
    do_check_true(!!aPacket.source);
    do_check_true(
      !!aPacket.source.url.match(/test_sources_backwards_compat-01.js$/));

    gClient.compat.supportsFeature("sources").then(function () {
      do_check_true(
        false,
        "The server shouldn't support sources since we mocked it not to.");
    }, test_sources_compatibility);
  });

  gDebuggee.eval(function inc(n) {
    return n+1;
  }.toString());
}

function test_sources_compatibility()
{
  gThreadClient.getSources(function (aResponse) {
    do_check_true(!aResponse.error);

    do_check_true(aResponse.sources.some(function (s) {
      return s.url.match(/test_sources_backwards_compat-01.js$/);
    }));

    do_check_true(gNumTimesSourcesSent <= 1,
                  "Should only send one sources request at most, even though we"
                  + " might have had to send one to determine feature support.");

    finishClient(gClient);
  });
}
