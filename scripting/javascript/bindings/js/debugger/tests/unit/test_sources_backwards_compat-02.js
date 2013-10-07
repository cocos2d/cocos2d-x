/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check getting sources before there are any, in backwards compatibility mode.
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
  // Make sure that the eval script from addTestGlobal() won't interfere with
  // the test.
  gc();
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-sources-compat", function (aResponse,
                                                                     aTabClient,
                                                                     aThreadClient) {
      gTabClient = aTabClient;
      gThreadClient = aThreadClient;
      test_listing_zero_sources_compat();
    });
  });
  do_test_pending();
}

function test_listing_zero_sources_compat()
{
  gThreadClient.getSources(function (aPacket) {
    do_check_true(!aPacket.error);
    do_check_true(!!aPacket.sources);
    do_check_eq(aPacket.sources.length, 0);
    do_check_true(gNumTimesSourcesSent <= 1,
                  "Should only send one sources request, even though we might "
                  + "have had to send one to determine feature support.");
    finishClient(gClient);
  });
}
