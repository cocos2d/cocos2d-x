/* -*- Mode: javascript; js-indent-level: 2; -*- */
/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

var gDebuggee;
var gClient;
var gThreadClient;

// This test ensures that we can create SourceActors and SourceClients properly,
// and that they can communicate over the protocol to fetch the source text for
// a given script.

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-grips");
  gDebuggee.eval(function stopMe(arg1) {
    debugger;
  }.toString());

  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-grips", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      gThreadClient.addListener("unsolicitedPause", unsolicitedPauseListener);
      test_source();
    });
  });
  do_test_pending();
}

function unsolicitedPauseListener(aEvent, aPacket, aContinue) {
  gContinue = aContinue;
}

function test_source()
{
  DebuggerServer.LONG_STRING_LENGTH = 200;

  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    gThreadClient.getSources(function (aResponse) {
      do_check_true(!!aResponse);
      do_check_true(!!aResponse.sources);
      gClient.compat.supportsFeature("sources").then(function (supported) {
        do_check_true(supported);

      });

      let source = aResponse.sources.filter(function (s) {
        return s.url.match(/test_source-01.js$/);
      })[0];

      do_check_true(!!source);

      let sourceClient = gThreadClient.source(source);
      sourceClient.source(function (aResponse) {
        do_check_true(!!aResponse);
        do_check_true(!aResponse.error);
        do_check_true(!!aResponse.source);

        do_check_eq(readFile("test_source-01.js"),
                    aResponse.source);

        gThreadClient.resume(function () {
          finishClient(gClient);
        });
      });
    });
  });

  gDebuggee.eval('stopMe()');
}
