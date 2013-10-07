/* -*- Mode: javascript; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; js-indent-level: 2; -*- */
/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

function run_test()
{
  Cu.import("resource://gre/modules/jsdebugger.jsm");
  addDebuggerToGlobal(this);
  let loader = Cc["@mozilla.org/moz/jssubscript-loader;1"]
    .getService(Components.interfaces.mozIJSSubScriptLoader);
  loader.loadSubScript("resource://gre/modules/devtools/server/actors/script.js");

  test_LSA_disconnect();
  test_LSA_grip();
  test_LSA_onSubstring();
}

const TEST_STRING = "This is a very long string!";

function makeMockLongStringActor()
{
  let string = TEST_STRING;
  let actor = new LongStringActor(string);
  actor.actorID = "longString1";
  actor.registeredPool = {
    longStringActors: {
      longString1: actor
    }
  };
  return actor;
}

function test_LSA_disconnect()
{
  let actor = makeMockLongStringActor();
  do_check_eq(actor.registeredPool.longStringActors[actor.actorID], actor);

  actor.disconnect();
  do_check_eq(actor.registeredPool.longStringActors[actor.actorID], void 0);
}

function test_LSA_substring()
{
  let actor = makeMockLongStringActor();
  do_check_eq(actor._substring(0, 4), TEST_STRING.substring(0, 4));
  do_check_eq(actor._substring(6, 9), TEST_STRING.substring(6, 9));
  do_check_eq(actor._substring(0, TEST_STRING.length), TEST_STRING);
}

function test_LSA_grip()
{
  let actor = makeMockLongStringActor();

  let grip = actor.grip();
  do_check_eq(grip.type, "longString");
  do_check_eq(grip.initial, TEST_STRING.substring(0, DebuggerServer.LONG_STRING_INITIAL_LENGTH));
  do_check_eq(grip.length, TEST_STRING.length);
  do_check_eq(grip.actor, actor.actorID);
}

function test_LSA_onSubstring()
{
  let actor = makeMockLongStringActor();
  let response;

  // From the start
  response = actor.onSubstring({
    start: 0,
    end: 4
  });
  do_check_eq(response.from, actor.actorID);
  do_check_eq(response.substring, TEST_STRING.substring(0, 4));

  // In the middle
  response = actor.onSubstring({
    start: 5,
    end: 8
  });
  do_check_eq(response.from, actor.actorID);
  do_check_eq(response.substring, TEST_STRING.substring(5, 8));

  // Whole string
  response = actor.onSubstring({
    start: 0,
    end: TEST_STRING.length
  });
  do_check_eq(response.from, actor.actorID);
  do_check_eq(response.substring, TEST_STRING);

  // Negative index
  response = actor.onSubstring({
    start: -5,
    end: TEST_STRING.length
  });
  do_check_eq(response.from, actor.actorID);
  do_check_eq(response.substring,
              TEST_STRING.substring(-5, TEST_STRING.length));

  // Past the end
  response = actor.onSubstring({
    start: TEST_STRING.length - 5,
    end: 100
  });
  do_check_eq(response.from, actor.actorID);
  do_check_eq(response.substring,
              TEST_STRING.substring(TEST_STRING.length - 5, 100));
}
