/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

function PreInitGlobalActor(aConnection) {}

PreInitGlobalActor.prototype = {
  actorPrefix: "preInitGlobal",
  onPing: function onPing(aRequest) {
    return { message: "pong" };
  },
};

PreInitGlobalActor.prototype.requestTypes = {
  "ping": PreInitGlobalActor.prototype.onPing,
};

DebuggerServer.addGlobalActor(PreInitGlobalActor, "preInitGlobalActor");
