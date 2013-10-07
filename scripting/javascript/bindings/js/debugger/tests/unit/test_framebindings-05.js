/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Check the environment bindings of a |with| in global scope.
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

    let objClient = gThreadClient.pauseGrip(env.object);
    objClient.getPrototypeAndProperties(function(aResponse) {
      do_check_eq(aResponse.ownProperties.PI.value, Math.PI);
      do_check_eq(aResponse.ownProperties.cos.value.type, "object");
      do_check_eq(aResponse.ownProperties.cos.value.class, "Function");
      do_check_true(!!aResponse.ownProperties.cos.value.actor);

      let parentEnv = env.parent;
      do_check_neq(parentEnv, undefined);

      let parentClient = gThreadClient.pauseGrip(parentEnv.object);
      parentClient.getPrototypeAndProperties(function(aResponse) {
        do_check_eq(aResponse.ownProperties.a.value, Math.PI * 100);
        do_check_eq(aResponse.ownProperties.r.value, 10);
        do_check_eq(aResponse.ownProperties.Object.value.type, "object");
        do_check_eq(aResponse.ownProperties.Object.value.class, "Function");
        do_check_true(!!aResponse.ownProperties.Object.value.actor);

        gThreadClient.resume(function() {
          finishClient(gClient);
        });
      });
    });
  });

  gDebuggee.eval("var a, r = 10;\n" +
                 "with (Math) {\n" +
                 "  a = PI * r * r;\n" +
                 "  debugger;\n" +
                 "}");
}
