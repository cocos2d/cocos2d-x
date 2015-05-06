/*
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

let promise = null;
var globalDebuggee = null;

var gTestGlobals = [];


// A mock tab list, for use by tests. This simply presents each global in
// gTestGlobals as a tab, and the list is fixed: it never calls its
// onListChanged handler.
//
// As implemented now, we consult gTestGlobals when we're constructed, not
// when we're iterated over, so tests have to add their globals before the
// root actor is created.
function TestTabList(aConnection) {
  this.conn = aConnection;

  // An array of actors for each global added with
  // DebuggerServer.addTestGlobal.
  this._tabActors = [];

  // A pool mapping those actors' names to the actors.
  this._tabActorPool = new ActorPool(aConnection);

  for (let global of gTestGlobals) {
    let actor = new TestTabActor(aConnection, global);
    actor.selected = false;
    this._tabActors.push(actor);
    this._tabActorPool.addActor(actor);
  }
  if (this._tabActors.length > 0) {
    this._tabActors[0].selected = true;
  }

  aConnection.addActorPool(this._tabActorPool);
}

TestTabList.prototype = {
  constructor: TestTabList,
  getList: function () {
    return promise.resolve([tabActor for (tabActor of this._tabActors)]);
  }
};

function createRootActor(aConnection)
{
  let root = new RootActor(aConnection,
                           { tabList: new TestTabList(aConnection) });
  root.applicationType = "xpcshell-tests";
  return root;
}

function TestTabActor(aConnection, aGlobal)
{
  this.conn = aConnection;
  this._global = aGlobal;
  this._threadActor = new ThreadActor(this, this._global);
  this.conn.addActor(this._threadActor);
  this._attached = false;
  this._extraActors = {};
}

TestTabActor.prototype = {
  constructor: TestTabActor,
  actorPrefix: "TestTabActor",

  get window() {
    return { wrappedJSObject: this._global };
  },

  form: function() {
    let response = { actor: this.actorID, title: "Hello Cocos2d-X JSB", url: "http://cocos2d-x.org" };

    // Walk over tab actors added by extensions and add them to a new ActorPool.
    let actorPool = new ActorPool(this.conn);
//    this._createExtraActors(DebuggerServer.tabActorFactories, actorPool);
    if (!actorPool.isEmpty()) {
      this._tabActorPool = actorPool;
      this.conn.addActorPool(this._tabActorPool);
    }

//    this._appendExtraActors(response);

    return response;
  },

  onAttach: function(aRequest) {
    this._attached = true;

    let response = { type: "tabAttached", threadActor: this._threadActor.actorID };
//    this._appendExtraActors(response);

    return response;
  },

  onDetach: function(aRequest) {
    if (!this._attached) {
      return { "error":"wrongState" };
    }
    return { type: "detached" };
  },

  /* Support for DebuggerServer.addTabActor. */
  // _createExtraActors: CommonCreateExtraActors,
  // _appendExtraActors: CommonAppendExtraActors,

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
    require = global.require;
    cc = global.cc;

    require('script/debugger/DevToolsUtils.js', "debug");
    require('script/debugger/core/promise.js', "debug");
    require('script/debugger/transport.js', "debug");
    require('script/debugger/actors/root.js', "debug");
    require('script/debugger/actors/script.js', "debug");
    require('script/debugger/main.js', "debug");

    promise = exports;
    //DebuggerServer.addTestGlobal = function(aGlobal) {
      gTestGlobals.push(global);
    //};

};

