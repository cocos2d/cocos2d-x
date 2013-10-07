/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

var gDebuggee;
var gClient;
var gThreadClient;

function run_test()
{
  initTestDebuggerServer();
  gDebuggee = addTestGlobal("test-grips");
  gDebuggee.eval(function stopMe(arg1) {
    debugger;
  }.toString());

  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function() {
    attachTestTabAndResume(
      gClient, "test-grips", function(aResponse, aTabClient, aThreadClient) {
        gThreadClient = aThreadClient;
        test_longstring_grip();
      });
  });
  do_test_pending();
}

function test_longstring_grip()
{
  DebuggerServer.LONG_STRING_LENGTH = 200;

  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    try {
      let fakeLongStringGrip = {
        type: "longString",
        length: 1000000,
        actor: "123fakeActor123",
        initial: ""
      };
      let longStringClient = gThreadClient.pauseLongString(fakeLongStringGrip);
      longStringClient.substring(22, 28, function (aResponse) {
        try {
          do_check_true(!!aResponse.error,
                        "We should not get a response, but an error.");
        } finally {
          gThreadClient.resume(function() {
            finishClient(gClient);
          });
        }
      });
    } catch(error) {
      gThreadClient.resume(function() {
        finishClient(gClient);
        do_throw(error);
      });
    }
  });

  gDebuggee.eval('stopMe()');
}

