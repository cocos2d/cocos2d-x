/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

var gClient;
var gDebuggee;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = testGlobal("test-1");
  DebuggerServer.addTestGlobal(gDebuggee);

  let transport = DebuggerServer.connectPipe();
  gClient = new DebuggerClient(transport);
  gClient.connect(function(aType, aTraits) {
    attachTestTab(gClient, "test-1", function(aReply, aTabClient) {
      test_attach(aReply.threadActor);
    });
  });
  do_test_pending();
}

function test_attach(aThreadActorID)
{
  gClient.attachThread(aThreadActorID, function(aResponse, aThreadClient) {
    do_check_eq(aThreadClient.state, "paused");
    aThreadClient.resume(cleanup);
  });
}

function cleanup()
{
  gClient.addListener("closed", function(aEvent) {
    do_test_finished();
  });
  gClient.close();
}
