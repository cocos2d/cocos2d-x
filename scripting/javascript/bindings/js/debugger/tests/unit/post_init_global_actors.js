/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

function PostInitGlobalActor(aConnection) {}

PostInitGlobalActor.prototype = {
  actorPrefix: "postInitGlobal",
  onPing: function onPing(aRequest) {
    return { message: "pong" };
  },
};

PostInitGlobalActor.prototype.requestTypes = {
  "ping": PostInitGlobalActor.prototype.onPing,
};

DebuggerServer.addGlobalActor(PostInitGlobalActor, "postInitGlobalActor");
