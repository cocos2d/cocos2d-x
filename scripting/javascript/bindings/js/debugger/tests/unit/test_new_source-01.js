/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check basic newSource packet sent from server.
 */

var gDebuggee;
var gClient;
var gThreadClient;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-stack");
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(gClient, "test-stack", function(aResponse, aTabClient, aThreadClient) {
      gThreadClient = aThreadClient;
      test_simple_new_source();
    });
  });
  do_test_pending();
}

function test_simple_new_source()
{
  gClient.addOneTimeListener("newSource", function (aEvent, aPacket) {
    do_check_eq(aEvent, "newSource");
    do_check_eq(aPacket.type, "newSource");
    do_check_true(!!aPacket.source);
    do_check_true(!!aPacket.source.url.match(/test_new_source-01.js$/));

    finishClient(gClient);
  });

  gDebuggee.eval(function inc(n) {
    return n+1;
  }.toString());
}
