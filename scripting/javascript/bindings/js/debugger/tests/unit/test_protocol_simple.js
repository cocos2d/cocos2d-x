/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Test simple requests using the protocol helpers.
 */

let protocol = devtools.require("devtools/server/protocol");
let {method, Arg, Option, RetVal} = protocol;
let {defer, resolve} = devtools.require("sdk/core/promise");
let events = devtools.require("sdk/event/core");

function simpleHello() {
  return {
    from: "root",
    applicationType: "xpcshell-tests",
    traits: [],
  }
}

let RootActor = protocol.ActorClass({
  typeName: "root",
  initialize: function(conn) {
    protocol.Actor.prototype.initialize.call(this, conn);
    // Root actor owns itself.
    this.manage(this);
    this.actorID = "root";
  },

  sayHello: simpleHello,

  simpleReturn: method(function() {
    return 1;
  }, {
    response: { value: RetVal() },
  }),

  promiseReturn: method(function() {
    return resolve(1);
  }, {
    response: { value: RetVal("number") },
  }),

  simpleArgs: method(function(a, b) {
    return { firstResponse: a + 1, secondResponse: b + 1 };
  }, {
    request: {
      firstArg: Arg(0),
      secondArg: Arg(1),
    },
    response: RetVal()
  }),

  nestedArgs: method(function(a, b, c) {
    return { a: a, b: b, c: c };
  }, {
    request: {
      firstArg: Arg(0),
      nest: {
        secondArg: Arg(1),
        nest: {
          thirdArg: Arg(2)
        }
      }
    },
    response: RetVal()
  }),

  optionArgs: method(function(options) {
    return { option1: options.option1, option2: options.option2 };
  }, {
    request: {
      option1: Option(0),
      option2: Option(0)
    },
    response: RetVal()
  }),

  optionalArgs: method(function(a, b=200) {
    return b;
  }, {
    request: {
      a: Arg(0),
      b: Arg(1, "number", { optional: true })
    },
    response: {
      value: RetVal("number")
    },
  }),

  arrayArgs: method(function(a) {
    return a;
  }, {
    request: {
      a: Arg(0, "array:number")
    },
    response: {
      arrayReturn: RetVal("array:number")
    },
  }),

  nestedArrayArgs: method(function(a) {
    return a;
  }, {
    request: { a: Arg(0, "array:array:number") },
    response: { value: RetVal("array:array:number") },
  }),

  /**
   * Test that the 'type' part of the request packet works
   * correctly when the type isn't the same as the method name
   */
  renamedEcho: method(function(a) {
    if (this.conn.currentPacket.type != "echo") {
      return "goodbye";
    }
    return a;
  }, {
    request: {
      type: "echo",
      a: Arg(0),
    },
    response: {
      value: RetVal("string")
    },
  }),

  testOneWay: method(function(a) {
    // Emit to show that we got this message, because there won't be a response.
    events.emit(this, "oneway", a);
  }, {
    request: { a: Arg(0) },
    oneway: true
  }),

  events: {
    "oneway": { a: Arg(0) }
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

  check_except(() => {
    let badActor = ActorClass({
      missing: preEvent("missing-event", function() {
      })
    })
  });

  protocol.types.getType("array:array:array:number");
  protocol.types.getType("array:array:array:number");

  check_except(() => protocol.types.getType("unknown"));
  check_except(() => protocol.types.getType("array:unknown"));
  check_except(() => protocol.types.getType("unknown:number"));
  let trace = connectPipeTracing();
  let client = new DebuggerClient(trace);
  let rootClient;

  client.connect((applicationType, traits) => {
    trace.expectReceive({"from":"<actorid>","applicationType":"xpcshell-tests","traits":[]});
    do_check_eq(applicationType, "xpcshell-tests");

    rootClient = RootFront(client);

    rootClient.simpleReturn().then(ret => {
      trace.expectSend({"type":"simpleReturn","to":"<actorid>"});
      trace.expectReceive({"value":1,"from":"<actorid>"});
      do_check_eq(ret, 1);
    }).then(() => {
      return rootClient.promiseReturn();
    }).then(ret => {
      trace.expectSend({"type":"promiseReturn","to":"<actorid>"});
      trace.expectReceive({"value":1,"from":"<actorid>"});
      do_check_eq(ret, 1);
    }).then(() => {
      return rootClient.simpleArgs(5, 10)
    }).then(ret => {
      trace.expectSend({"type":"simpleArgs","firstArg":5,"secondArg":10,"to":"<actorid>"});
      trace.expectReceive({"firstResponse":6,"secondResponse":11,"from":"<actorid>"});
      do_check_eq(ret.firstResponse, 6);
      do_check_eq(ret.secondResponse, 11);
    }).then(() => {
      return rootClient.nestedArgs(1, 2, 3);
    }).then(ret => {
      trace.expectSend({"type":"nestedArgs","firstArg":1,"nest":{"secondArg":2,"nest":{"thirdArg":3}},"to":"<actorid>"});
      trace.expectReceive({"a":1,"b":2,"c":3,"from":"<actorid>"});
      do_check_eq(ret.a, 1);
      do_check_eq(ret.b, 2);
      do_check_eq(ret.c, 3);
    }).then(() => {
      return rootClient.optionArgs({
        "option1": 5,
        "option2": 10
      });
    }).then(ret => {
      trace.expectSend({"type":"optionArgs","option1":5,"option2":10,"to":"<actorid>"});
      trace.expectReceive({"option1":5,"option2":10,"from":"<actorid>"});
      do_check_eq(ret.option1, 5);
      do_check_eq(ret.option2, 10);
    }).then(() => {
      return rootClient.optionArgs({});
    }).then(ret => {
      trace.expectSend({"type":"optionArgs","to":"<actorid>"});
      trace.expectReceive({"from":"<actorid>"});
      do_check_true(typeof(ret.option1) === "undefined");
      do_check_true(typeof(ret.option2) === "undefined");
    }).then(ret => {
      // Explicitly call an optional argument...
      return rootClient.optionalArgs(5, 10);
    }).then(ret => {
      trace.expectSend({"type":"optionalArgs","a":5,"b":10,"to":"<actorid>"});
      trace.expectReceive({"value":10,"from":"<actorid>"});
      do_check_eq(ret, 10);
    }).then(() => {
      // Now don't pass the optional argument, expect the default.
      return rootClient.optionalArgs(5);
    }).then(ret => {
      trace.expectSend({"type":"optionalArgs","a":5,"to":"<actorid>"});
      trace.expectReceive({"value":200,"from":"<actorid>"});
      do_check_eq(ret, 200);
    }).then(ret => {
      return rootClient.arrayArgs([0, 1, 2, 3, 4, 5]);
    }).then(ret => {
      trace.expectSend({"type":"arrayArgs","a":[0,1,2,3,4,5],"to":"<actorid>"});
      trace.expectReceive({"arrayReturn":[0,1,2,3,4,5],"from":"<actorid>"});
      do_check_eq(ret[0], 0);
      do_check_eq(ret[5], 5);
    }).then(() => {
      return rootClient.arrayArgs([[5]]);
    }).then(ret => {
      trace.expectSend({"type":"arrayArgs","a":[[5]],"to":"<actorid>"});
      trace.expectReceive({"arrayReturn":[[5]],"from":"<actorid>"});
      do_check_eq(ret[0][0], 5);
    }).then(() => {
      return rootClient.renamedEcho("hello");
    }).then(str => {
      trace.expectSend({"type":"echo","a":"hello","to":"<actorid>"});
      trace.expectReceive({"value":"hello","from":"<actorid>"});

      do_check_eq(str, "hello");

      let deferred = defer();
      rootClient.on("oneway", (response) => {
        trace.expectSend({"type":"testOneWay","a":"hello","to":"<actorid>"});
        trace.expectReceive({"type":"oneway","a":"hello","from":"<actorid>"});

        do_check_eq(response, "hello");
        deferred.resolve();
      });
      do_check_true(typeof(rootClient.testOneWay("hello")) === "undefined");
      return deferred.promise;
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
