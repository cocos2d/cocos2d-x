/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

function Actor() {}

exports.register = function(handle) {
  handle.addTabActor(Actor, "registeredActor1");
  handle.addGlobalActor(Actor, "registeredActor1");
}

exports.unregister = function(handle) {
  handle.removeTabActor(Actor);
  handle.removeGlobalActor(Actor);
}

