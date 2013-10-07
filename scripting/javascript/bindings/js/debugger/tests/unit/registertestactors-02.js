/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

function Actor() {}

exports.register = function(handle) {
  handle.addGlobalActor(Actor, "registeredActor2");
  handle.addTabActor(Actor, "registeredActor2");
}

exports.unregister = function(handle) {
}

