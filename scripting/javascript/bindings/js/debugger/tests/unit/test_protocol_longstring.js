/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Test simple requests using the protocol helpers.
 */
let protocol = devtools.require("devtools/server/protocol");
let {method, RetVal, Arg, Option} = protocol;
let {defer, resolve} = devtools.require("sdk/core/promise");
let events = devtools.require("sdk/event/core");
let {LongStringActor} = devtools.require("devtools/server/actors/string");

function simpleHello() {
  return {
    from: "root",
    applicationType: "xpcshell-tests",
    traits: [],
  }
}

DebuggerServer.LONG_STRING_LENGTH = DebuggerServer.LONG_STRING_INITIAL_LENGTH = DebuggerServer.LONG_STRING_READ_LENGTH = 5;

let SHORT_STR = "abc";
let LONG_STR = "abcdefghijklmnop";

let rootActor = null;

let RootActor = protocol.ActorClass({
  typeName: "root",

  initialize: function(conn) {
    rootActor = this;
    protocol.Actor.prototype.initialize.call(this, conn);
    // Root actor owns itself.
    this.manage(this);
    this.actorID = "root";
  },

  sayHello: simpleHello,

  shortString: method(function() {
    return new LongStringActor(this.conn, SHORT_STR);
  }, {
    response: { value: RetVal("longstring") },
  }),

  longString: method(function() {
    return new LongStringActor(this.conn, LONG_STR);
  }, {
    response: { value: RetVal("longstring") },
  }),

  emitShortString: method(function() {
    events.emit(this, "string-event", new LongStringActor(this.conn, SHORT_STR));
  }, {
    oneway: true,
  }),

  emitLongString: method(function() {
    events.emit(this, "string-event", new LongStringActor(this.conn, LONG_STR));
  }, {
    oneway: true,
  }),

  events: {
    "string-event": {
      str: Arg(0, "longstring")
    }
  }
});

let RootFront = protocol.FrontClass(RootActor, {
  initialize: function(client) {
    this.actorID = "root";
    protocol.Front.prototype.initialize.call(this, client);
    // Root owns itself.
    this.manage(this);
  }
});

function run_test()
{
  DebuggerServer.createRootActor = (conn => {
    return RootActor(conn);
  });

  DebuggerServer.init(() => true);
  let trace = connectPipeTracing();
  let client = new DebuggerClient(trace);
  let rootClient;

  let strfront = null;

  let expectRootChildren = function(size) {
    do_check_eq(rootActor.__poolMap.size, size + 1);
    do_check_eq(rootClient.__poolMap.size, size + 1);
  }


  client.connect((applicationType, traits) => {
    rootClient = RootFront(client);

    // Root actor has no children yet.
    expectRootChildren(0);

    trace.expectReceive({"from":"<actorid>","applicationType":"xpcshell-tests","traits":[]});
    do_check_eq(applicationType, "xpcshell-tests");
    rootClient.shortString().then(ret => {
      trace.expectSend({"type":"shortString","to":"<actorid>"});
      trace.expectReceive({"value":"abc","from":"<actorid>"});

      // Should only own the one reference (itself) at this point.
      expectRootChildren(0);
      strfront = ret;
    }).then(() => {
      return strfront.string();
    }).then(ret => {
      do_check_eq(ret, SHORT_STR);
    }).then(() => {
      return rootClient.longString();
    }).then(ret => {
      trace.expectSend({"type":"longString","to":"<actorid>"});
      trace.expectReceive({"value":{"type":"longString","actor":"<actorid>","length":16,"initial":"abcde"},"from":"<actorid>"});

      strfront = ret;
      // Should own a reference to itself and an extra string now.
      expectRootChildren(1);
    }).then(() => {
      return strfront.string();
    }).then(ret => {
      trace.expectSend({"type":"substring","start":5,"end":10,"to":"<actorid>"});
      trace.expectReceive({"substring":"fghij","from":"<actorid>"});
      trace.expectSend({"type":"substring","start":10,"end":15,"to":"<actorid>"});
      trace.expectReceive({"substring":"klmno","from":"<actorid>"});
      trace.expectSend({"type":"substring","start":15,"end":20,"to":"<actorid>"});
      trace.expectReceive({"substring":"p","from":"<actorid>"});

      do_check_eq(ret, LONG_STR);
    }).then(() => {
      return strfront.release();
    }).then(() => {
      trace.expectSend({"type":"release","to":"<actorid>"});
      trace.expectReceive({"from":"<actorid>"});

      // That reference should be removed now.
      expectRootChildren(0);
    }).then(() => {
      let deferred = defer();
      rootClient.once("string-event", (str) => {
        trace.expectSend({"type":"emitShortString","to":"<actorid>"});
        trace.expectReceive({"type":"string-event","str":"abc","from":"<actorid>"});

        do_check_true(!!str);
        strfront = str;
        // Shouldn't generate any new references
        expectRootChildren(0);
        // will generate no packets.
        strfront.string().then((value) => { deferred.resolve(value) });
      });
      rootClient.emitShortString();
      return deferred.promise;
    }).then(value => {
      do_check_eq(value, SHORT_STR);
    }).then(() => {
      // Will generate no packets
      return strfront.release();
    }).then(() => {
      let deferred = defer();
      rootClient.once("string-event", (str) => {
        trace.expectSend({"type":"emitLongString","to":"<actorid>"});
        trace.expectReceive({"type":"string-event","str":{"type":"longString","actor":"<actorid>","length":16,"initial":"abcde"},"from":"<actorid>"});

        do_check_true(!!str);
        // Should generate one new reference
        expectRootChildren(1);
        strfront = str;
        strfront.string().then((value) => {
          trace.expectSend({"type":"substring","start":5,"end":10,"to":"<actorid>"});
          trace.expectReceive({"substring":"fghij","from":"<actorid>"});
          trace.expectSend({"type":"substring","start":10,"end":15,"to":"<actorid>"});
          trace.expectReceive({"substring":"klmno","from":"<actorid>"});
          trace.expectSend({"type":"substring","start":15,"end":20,"to":"<actorid>"});
          trace.expectReceive({"substring":"p","from":"<actorid>"});

          deferred.resolve(value);
        });
      });
      rootClient.emitLongString();
      return deferred.promise;
    }).then(value => {
      do_check_eq(value, LONG_STR);
    }).then(() => {
      return strfront.release();
    }).then(() => {
      trace.expectSend({"type":"release","to":"<actorid>"});
      trace.expectReceive({"from":"<actorid>"});
      expectRootChildren(0);
    }).then(() => {
      client.close(() => {
        do_test_finished();
      });
    }).then(null, err => {
      do_report_unexpected_exception(err, "Failure executing test");
    });
  });
  do_test_pending();
}
