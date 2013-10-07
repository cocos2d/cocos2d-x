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
    attachTestTab(gClient, "test-1", test_attach);
  });
  do_test_pending();
}

function test_attach(aResponse, aTabClient)
{
  gClient.attachThread(aResponse.threadActor, function(aResponse, aThreadClient) {
    do_check_eq(aThreadClient.paused, true);
    aThreadClient.resume(function() {
      test_interrupt();
    });
  });
}

function test_interrupt()
{
  do_check_eq(gClient.activeThread.paused, false);
  gClient.activeThread.interrupt(function(aResponse) {
    do_check_eq(gClient.activeThread.paused, true);
    gClient.activeThread.resume(function() {
      do_check_eq(gClient.activeThread.paused, false);
      cleanup();
    });
  });
}

function cleanup()
{
  gClient.addListener("closed", function(aEvent) {
    do_test_finished();
  });
  gClient.close();
}

