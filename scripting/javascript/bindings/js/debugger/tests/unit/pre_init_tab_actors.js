/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

function PreInitTabActor(aConnection) {}

PreInitTabActor.prototype = {
  actorPrefix: "preInitTab",
  onPing: function onPing(aRequest) {
    return { message: "pong" };
  },
};

PreInitTabActor.prototype.requestTypes = {
  "ping": PreInitTabActor.prototype.onPing,
};

DebuggerServer.addGlobalActor(PreInitTabActor, "preInitTabActor");
