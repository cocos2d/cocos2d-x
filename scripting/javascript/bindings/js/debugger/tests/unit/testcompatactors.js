/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

var gTestGlobals = [];

function createRootActor()
{
  let actor = {
    sayHello: function() {
      this._tabActors = [];
      for each (let g in gTestGlobals) {
        let actor = new BrowserTabActor(this.conn);
        actor.thread = new ThreadActor({});
        actor.thread.addDebuggee(g);
        actor.thread.global = g;

        actor.json = function() {
          return { actor: actor.actorID,
                   url: "http://www.example.com/",
                   title: actor.thread.global.__name };
        };

        actor.requestTypes["attach"] = function (aRequest) {
          dump("actor.thread.actorID = " + actor.thread.actorID + "\n");
          return {
            from: actor.actorID,
            type: "tabAttached",
            threadActor: actor.thread.actorID
          };
        };

        actor.thread.requestTypes["scripts"] = function (aRequest) {
          return this._discoverSources().then(function () {
            let scripts = [];
            for (let s of this.dbg.findScripts()) {
              if (!s.url) {
                continue;
              }
              let script = {
                url: s.url,
                startLine: s.startLine,
                lineCount: s.lineCount,
                source: this.sources.source(s.url).form()
              };
              scripts.push(script);
            }

            return {
              from: this.actorID,
              scripts: scripts
            };
          }.bind(this));
        };

        // Pretend that we do not know about the "sources" packet to force the
        // client to go into its backwards compatibility mode.
        actor.thread.requestTypes["sources"] = function () {
          return {
            error: "unrecognizedPacketType"
          };
        };

        let { conn } = this;
        actor.thread.onNewScript = (function (oldOnNewScript) {
          return function (aScript) {
            oldOnNewScript.call(this, aScript);
            conn.send({
              from: actor.thread.actorID,
              type: "newScript",
              url: aScript.url,
              startLine: aScript.startLine,
              lineCount: aScript.lineCount,
              source: actor.thread.sources.source(aScript.url).form()
            });
          };
        }(actor.thread.onNewScript));

        this.conn.addActor(actor);
        this.conn.addActor(actor.thread);
        this._tabActors.push(actor);
      }

      this.conn.send = (function (aOldSend) {
        return function (aPacket) {
          if (aPacket.type === "newSource") {
            // Don't send newSource Packets b/c we are an old version of the
            // RDP!
            return undefined;
          } else {
            return aOldSend.call(this, aPacket);
          }
        };
      }(this.conn.send));

      return { from: "root",
               applicationType: "xpcshell-tests",
               traits: {} };
    },

    listTabs: function(aRequest) {
      return {
        from: "root",
        selected: 0,
        tabs: [ actor.json() for (actor of this._tabActors) ]
      };
    },
  };

  actor.requestTypes = {
    "listTabs": actor.listTabs,
    "echo": function(aRequest) { return aRequest; },
  };
  return actor;
}

DebuggerServer.addTestGlobal = function addTestGlobal(aGlobal)
{
  gTestGlobals.push(aGlobal);
}
