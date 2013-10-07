/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

var gClient;
var gActors;

/**
 * The purpose of these tests is to verify that it's possible to add actors
 * both before and after the DebuggerServer has been initialized, so addons
 * that add actors don't have to poll the object for its initialization state
 * in order to add actors after initialization but rather can add actors anytime
 * regardless of the object's state.
 */
function run_test()
{
  DebuggerServer.addActors("resource://test/pre_init_global_actors.js");
  DebuggerServer.addActors("resource://test/pre_init_tab_actors.js");

  DebuggerServer.init(function () { return true; });
  DebuggerServer.addBrowserActors();

  DebuggerServer.addActors("resource://test/post_init_global_actors.js");
  DebuggerServer.addActors("resource://test/post_init_tab_actors.js");

  add_test(init);
  add_test(test_pre_init_global_actor);
  add_test(test_pre_init_tab_actor);
  add_test(test_post_init_global_actor);
  add_test(test_post_init_tab_actor);
  add_test(close_client);
  run_next_test();
}

function init()
{
  gClient = new DebuggerClient(DebuggerServer.connectPipe());
  gClient.connect(function onConnect() {
    gClient.listTabs(function onListTabs(aResponse) {
      gActors = aResponse;
      run_next_test();
    });
  });
}

function test_pre_init_global_actor()
{
  gClient.request({ to: gActors.preInitGlobalActor, type: "ping" },
    function onResponse(aResponse) {
      do_check_eq(aResponse.message, "pong");
      run_next_test();
    }
  );
}

function test_pre_init_tab_actor()
{
  gClient.request({ to: gActors.preInitTabActor, type: "ping" },
    function onResponse(aResponse) {
      do_check_eq(aResponse.message, "pong");
      run_next_test();
    }
  );
}

function test_post_init_global_actor()
{
  gClient.request({ to: gActors.postInitGlobalActor, type: "ping" },
    function onResponse(aResponse) {
      do_check_eq(aResponse.message, "pong");
      run_next_test();
    }
  );
}

function test_post_init_tab_actor()
{
  gClient.request({ to: gActors.postInitTabActor, type: "ping" },
    function onResponse(aResponse) {
      do_check_eq(aResponse.message, "pong");
      run_next_test();
    }
  );
}

function close_client() {
  gClient.close(() => run_next_test());
}
