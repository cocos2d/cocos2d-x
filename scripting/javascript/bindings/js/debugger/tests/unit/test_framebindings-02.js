/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check a frame actor's parent bindings.
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
      test_pause_frame();
    });
  });
  do_test_pending();
}

function test_pause_frame()
{
  gThreadClient.addOneTimeListener("paused", function(aEvent, aPacket) {
    let parentEnv = aPacket.frame.environment.parent;
    let bindings = parentEnv.bindings;
    let args = bindings.arguments;
    let vars = bindings.variables;
    do_check_neq(parentEnv, undefined);
    do_check_eq(args.length, 0);
    do_check_eq(vars.stopMe.value.type, "object");
    do_check_eq(vars.stopMe.value.class, "Function");
    do_check_true(!!vars.stopMe.value.actor);

    parentEnv = parentEnv.parent;
    do_check_neq(parentEnv, undefined);
    let objClient = gThreadClient.pauseGrip(parentEnv.object);
    objClient.getPrototypeAndProperties(function(aResponse) {
      do_check_eq(aResponse.ownProperties.Object.value.type, "object");
      do_check_eq(aResponse.ownProperties.Object.value.class, "Function");
      do_check_true(!!aResponse.ownProperties.Object.value.actor);

      gThreadClient.resume(function() {
        finishClient(gClient);
      });
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(aNumber, aBool, aString, aNull, aUndefined, aObject) {
      var a = 1;
      var b = true;
      var c = { a: "a" };
      debugger;
    };
    stopMe(42, true, "nasu", null, undefined, { foo: "bar" });
  } + ")()");
}
