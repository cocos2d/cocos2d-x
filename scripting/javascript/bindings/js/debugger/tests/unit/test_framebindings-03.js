/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check a |with| frame actor's bindings.
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
    let env = aPacket.frame.environment;
    do_check_neq(env, undefined);

    let parentEnv = env.parent;
    do_check_neq(parentEnv, undefined);

    let bindings = parentEnv.bindings;
    let args = bindings.arguments;
    let vars = bindings.variables;
    do_check_eq(args.length, 1);
    do_check_eq(args[0].aNumber.value, 10);
    do_check_eq(vars.r.value, 10);
    do_check_eq(vars.a.value, Math.PI * 100);
    do_check_eq(vars.arguments.value.class, "Arguments");
    do_check_true(!!vars.arguments.value.actor);

    let objClient = gThreadClient.pauseGrip(env.object);
    objClient.getPrototypeAndProperties(function(aResponse) {
      do_check_eq(aResponse.ownProperties.PI.value, Math.PI);
      do_check_eq(aResponse.ownProperties.cos.value.type, "object");
      do_check_eq(aResponse.ownProperties.cos.value.class, "Function");
      do_check_true(!!aResponse.ownProperties.cos.value.actor);

      gThreadClient.resume(function() {
        finishClient(gClient);
      });
    });
  });

  gDebuggee.eval("(" + function() {
    function stopMe(aNumber) {
      var a;
      var r = aNumber;
      with (Math) {
        a = PI * r * r;
        debugger;
      }
    };
    stopMe(10);
  } + ")()");
}
