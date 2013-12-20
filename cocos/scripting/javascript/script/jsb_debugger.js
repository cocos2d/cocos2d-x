require('debugger/DevToolsUtils.js', "debug");
require('debugger/core/promise.js', "debug");
require('debugger/transport.js', "debug");
require('debugger/actors/root.js', "debug");
require('debugger/actors/script.js', "debug");
require('debugger/main.js', "debug");

var globalDebuggee = null;

function TestTabActor(aConnection, aGlobal)
{
  this.conn = aConnection;
  this._global = aGlobal;
  this._threadActor = new ThreadActor(this, this._global);
  this.conn.addActor(this._threadActor);
  this._attached = false;
}

TestTabActor.prototype = {
  constructor: TestTabActor,
  actorPrefix: "TestTabActor",

  grip: function() {
    return { actor: this.actorID, title: "Hello Cocos2d-X JSB", url: "http://cocos2d-x.org" };
  },

  onAttach: function(aRequest) {
    this._attached = true;
    return { type: "tabAttached", threadActor: this._threadActor.actorID };
  },

  onDetach: function(aRequest) {
    if (!this._attached) {
      return { "error":"wrongState" };
    }
    return { type: "detached" };
  },

  // Hooks for use by TestTabActors.
  addToParentPool: function(aActor) {
    this.conn.addActor(aActor);
  },

  removeFromParentPool: function(aActor) {
    this.conn.removeActor(aActor);
  }
};

TestTabActor.prototype.requestTypes = {
  "attach": TestTabActor.prototype.onAttach,
  "detach": TestTabActor.prototype.onDetach
};

function TestTabList(aConnection) {
  this.conn = aConnection;

  // An array of actors for each global added with
  // DebuggerServer.addTestGlobal.
  this._tabActors = [];

  // A pool mapping those actors' names to the actors.
  this._tabActorPool = new ActorPool(aConnection);

  // for (let global of gTestGlobals) {
    let actor = new TestTabActor(aConnection, globalDebuggee);
    actor.selected = false;
    this._tabActors.push(actor);
    this._tabActorPool.addActor(actor);
  // }
  if (this._tabActors.length > 0) {
    this._tabActors[0].selected = true;
  }

  aConnection.addActorPool(this._tabActorPool);
}

TestTabList.prototype = {
  constructor: TestTabList,
  iterator: function() {
    for (let actor of this._tabActors) {
      yield actor;
    }
  }
};

this.processInput = function (inputstr) {

    if (!inputstr) {
        return;
    }

    if (inputstr === "connected")
    {

        DebuggerServer.createRootActor = (conn => {
            return new RootActor(conn, { tabList: new TestTabList(conn) });
        });
        DebuggerServer.init(() => true);
        DebuggerServer.openListener(5086);

        if (debuggerServer && debuggerServer.onSocketAccepted)
        {
            var aTransport = {
                host: "127.0.0.1",
                port: 5086,
                openInputStream: function() {
                    return {
                        close: function(){}
                    };
                },
                openOutputStream: function() {
                    return {
                        close: function(){},
                        write: function(){},
                        asyncWait: function(){}
                    };
                },
            };

            debuggerServer.onSocketAccepted(null, aTransport);
        }
        return;
    }

    if (DebuggerServer && DebuggerServer._transport && DebuggerServer._transport.onDataAvailable)
    {
        DebuggerServer._transport.onDataAvailable(inputstr);
    }
};

this._prepareDebugger = function (global) {

    globalDebuggee = global;
};

