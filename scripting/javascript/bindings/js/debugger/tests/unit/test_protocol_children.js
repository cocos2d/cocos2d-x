/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Test simple requests using the protocol helpers.
 */
let protocol = devtools.require("devtools/server/protocol");
let {method, preEvent, types, Arg, Option, RetVal} = protocol;

let {resolve} = devtools.require("sdk/core/promise");
let events = devtools.require("sdk/event/core");

function simpleHello() {
  return {
    from: "root",
    applicationType: "xpcshell-tests",
    traits: [],
  }
}

let testTypes = {};

// Predeclaring the actor type so that it can be used in the
// implementation of the child actor.
types.addActorType("childActor");

let ChildActor = protocol.ActorClass({
  typeName: "childActor",

  // Actors returned by this actor should be owned by the root actor.
  marshallPool: function() { return this.parent() },

  toString: function() "[ChildActor " + this.childID + "]",

  initialize: function(conn, id) {
    protocol.Actor.prototype.initialize.call(this, conn);
    this.childID = id;
  },

  destroy: function() {
    protocol.Actor.prototype.destroy.call(this);
    this.destroyed = true;
  },

  form: function(detail) {
    return {
      actor: this.actorID,
      childID: this.childID,
      detail: detail
    };
  },

  echo: method(function(str) {
    return str;
  }, {
    request: { str: Arg(0) },
    response: { str: RetVal("string") },
    telemetry: "ECHO"
  }),

  getDetail1: method(function() {
    return this;
  }, {
    // This also exercises return-value-as-packet.
    response: RetVal("childActor#detail1"),
  }),

  getDetail2: method(function() {
    return this;
  }, {
    // This also exercises return-value-as-packet.
    response: RetVal("childActor#detail2"),
  }),

  getSibling: method(function(id) {
    return this.parent().getChild(id);
  }, {
    request: { id: Arg(0) },
    response: { sibling: RetVal("childActor") }
  }),

  emitEvents: method(function() {
    events.emit(this, "event1", 1, 2, 3);
    events.emit(this, "named-event", 1, 2, 3);
    events.emit(this, "object-event", this);
    events.emit(this, "array-object-event", [this]);
  }, {
    response: { value: "correct response" },
  }),

  release: method(function() { }, { release: true }),

  events: {
    "event1" : {
      a: Arg(0),
      b: Arg(1),
      c: Arg(2)
    },
    "named-event": {
      type: "namedEvent",
      a: Arg(0),
      b: Arg(1),
      c: Arg(2)
    },
    "object-event": {
      type: "objectEvent",
      detail: Arg(0, "childActor#detail1"),
    },
    "array-object-event": {
      type: "arrayObjectEvent",
      detail: Arg(0, "array:childActor#detail2"),
    }
  }
});

let ChildFront = protocol.FrontClass(ChildActor, {
  initialize: function(client, form) {
    protocol.Front.prototype.initialize.call(this, client, form);
  },

  destroy: function() {
    this.destroyed = true;
    protocol.Front.prototype.destroy.call(this);
  },

  marshallPool: function() { return this.parent() },

  toString: function() "[child front " + this.childID + "]",

  form: function(form) {
    this.childID = form.childID;
    this.detail = form.detail;
  },

  onEvent1: preEvent("event1", function(a, b, c) {
    this.event1arg3 = c;
  }),
});

types.addDictType("manyChildrenDict", {
  child5: "childActor",
  more: "array:childActor",
});

types.addLifetime("temp", "_temporaryHolder");

let rootActor = null;
let RootActor = protocol.ActorClass({
  typeName: "root",

  toString: function() "[root actor]",

  initialize: function(conn) {
    rootActor = this;
    this.actorID = "root";
    this._children = {};
    protocol.Actor.prototype.initialize.call(this, conn);
    // Root actor owns itself.
    this.manage(this);
  },

  toString: function() "root actor",

  sayHello: simpleHello,

  getChild: method(function(id) {
    if (id in this._children) {
      return this._children[id];
    }
    let child = new ChildActor(this.conn, id);
    this._children[id] = child;
    return child;
  }, {
    request: { str: Arg(0) },
    response: { actor: RetVal("childActor") },
  }),

  getChildren: method(function(ids) {
    return [this.getChild(id) for (id of ids)];
  }, {
    request: { ids: Arg(0, "array:string") },
    response: { children: RetVal("array:childActor") },
  }),

  getManyChildren: method(function() {
    return {
      foo: "bar", // note that this isn't in the specialization array.
      child5: this.getChild("child5"),
      more: [ this.getChild("child6"), this.getChild("child7") ]
    }
  }, {
    response: RetVal("manyChildrenDict")
  }),

  // This should remind you of a pause actor.
  getTemporaryChild: method(function(id) {
    if (!this._temporaryHolder) {
      this._temporaryHolder = this.manage(new protocol.Actor(this.conn));
    }
    return new ChildActor(this.conn, id);
  }, {
    request: { id: Arg(0) },
    response: { child: RetVal("temp:childActor") }
  }),

  clearTemporaryChildren: method(function(id) {
    if (!this._temporaryHolder) {
      return;
    }
    this._temporaryHolder.destroy();
    delete this._temporaryHolder;
  })
});

let RootFront = protocol.FrontClass(RootActor, {
  toString: function() "[root front]",
  initialize: function(client) {
    this.actorID = "root";
    protocol.Front.prototype.initialize.call(this, client);
    // Root actor owns itself.
    this.manage(this);
  },

  getTemporaryChild: protocol.custom(function(id) {
    if (!this._temporaryHolder) {
      this._temporaryHolder = this.manage(new protocol.Front(this.conn, {actor: this.actorID + "_temp"}));
    }
    return this._getTemporaryChild(id);
  },{
   impl: "_getTemporaryChild"
  }),

  clearTemporaryChildren: protocol.custom(function() {
    if (!this._temporaryHolder) {
      return;
    }
    this._temporaryHolder.destroy();
    delete this._temporaryHolder;
    return this._clearTemporaryChildren();
  }, {
    impl: "_clearTemporaryChildren"
  })
});

function run_test()
{
  DebuggerServer.createRootActor = (conn => {
    return RootActor(conn);
  });
  DebuggerServer.init(() => true);

  let trace = connectPipeTracing();
  let client = new DebuggerClient(trace);
  client.connect((applicationType, traits) => {
    trace.expectReceive({"from":"<actorid>","applicationType":"xpcshell-tests","traits":[]})
    do_check_eq(applicationType, "xpcshell-tests");

    let rootFront = RootFront(client);
    let childFront = null;

    let expectRootChildren = size => {
      do_check_eq(rootActor._poolMap.size, size + 1);
      do_check_eq(rootFront._poolMap.size, size + 1);
      if (childFront) {
        do_check_eq(childFront._poolMap.size, 0);
      }
    };

    rootFront.getChild("child1").then(ret => {
      trace.expectSend({"type":"getChild","str":"child1","to":"<actorid>"})
      trace.expectReceive({"actor":"<actorid>","from":"<actorid>"})

      childFront = ret;
      do_check_true(childFront instanceof ChildFront);
      do_check_eq(childFront.childID, "child1");
      expectRootChildren(1);
    }).then(() => {
      // Request the child again, make sure the same is returned.
      return rootFront.getChild("child1");
    }).then(ret => {
      trace.expectSend({"type":"getChild","str":"child1","to":"<actorid>"})
      trace.expectReceive({"actor":"<actorid>","from":"<actorid>"})

      expectRootChildren(1);
      do_check_true(ret === childFront);
    }).then(() => {
      return childFront.echo("hello");
    }).then(ret => {
      trace.expectSend({"type":"echo","str":"hello","to":"<actorid>"})
      trace.expectReceive({"str":"hello","from":"<actorid>"})

      do_check_eq(ret, "hello");
    }).then(() => {
      return childFront.getDetail1();
    }).then(ret => {
      trace.expectSend({"type":"getDetail1","to":"<actorid>"});
      trace.expectReceive({"actor":"<actorid>","childID":"child1","detail":"detail1","from":"<actorid>"});
      do_check_true(ret === childFront);
      do_check_eq(childFront.detail, "detail1");
    }).then(() => {
      return childFront.getDetail2();
    }).then(ret => {
      trace.expectSend({"type":"getDetail2","to":"<actorid>"});
      trace.expectReceive({"actor":"<actorid>","childID":"child1","detail":"detail2","from":"<actorid>"});
      do_check_true(ret === childFront);
      do_check_eq(childFront.detail, "detail2");
    }).then(() => {
      return childFront.getSibling("siblingID");
    }).then(ret => {
      trace.expectSend({"type":"getSibling","id":"siblingID","to":"<actorid>"});
      trace.expectReceive({"sibling":{"actor":"<actorid>","childID":"siblingID"},"from":"<actorid>"});

      expectRootChildren(2);
    }).then(ret => {
      return rootFront.getTemporaryChild("temp1").then(temp1 => {
        trace.expectSend({"type":"getTemporaryChild","id":"temp1","to":"<actorid>"});
        trace.expectReceive({"child":{"actor":"<actorid>","childID":"temp1"},"from":"<actorid>"});

        // At this point we expect two direct children, plus the temporary holder
        // which should hold 1 itself.
        do_check_eq(rootActor._temporaryHolder.__poolMap.size, 1);
        do_check_eq(rootFront._temporaryHolder.__poolMap.size, 1);

        expectRootChildren(3);
        return rootFront.getTemporaryChild("temp2").then(temp2 => {
          trace.expectSend({"type":"getTemporaryChild","id":"temp2","to":"<actorid>"});
          trace.expectReceive({"child":{"actor":"<actorid>","childID":"temp2"},"from":"<actorid>"});

          // Same amount of direct children, and an extra in the temporary holder.
          expectRootChildren(3);
          do_check_eq(rootActor._temporaryHolder.__poolMap.size, 2);
          do_check_eq(rootFront._temporaryHolder.__poolMap.size, 2);

          // Get the children of the temporary holder...
          let checkActors = [entry[1] for (entry of rootActor._temporaryHolder.__poolMap)];
          let checkFronts = [entry[1] for (entry of rootFront._temporaryHolder.__poolMap)];

          // Now release the temporary holders and expect them to drop again.
          return rootFront.clearTemporaryChildren().then(() => {
            trace.expectSend({"type":"clearTemporaryChildren","to":"<actorid>"});
            trace.expectReceive({"from":"<actorid>"});

            expectRootChildren(2);
            do_check_false(!!rootActor._temporaryHolder);
            do_check_false(!!rootFront._temporaryHolder);
            for (let checkActor of checkActors) {
              do_check_true(checkActor.destroyed);
              do_check_true(checkActor.destroyed);
            }
          });
        });
      })
    }).then(ret => {
      return rootFront.getChildren(["child1", "child2"]);
    }).then(ret => {
      trace.expectSend({"type":"getChildren","ids":["child1","child2"],"to":"<actorid>"});
      trace.expectReceive({"children":[{"actor":"<actorid>","childID":"child1"},{"actor":"<actorid>","childID":"child2"}],"from":"<actorid>"});

      expectRootChildren(3);
      do_check_true(ret[0] === childFront);
      do_check_true(ret[1] !== childFront);
      do_check_true(ret[1] instanceof ChildFront);

      // On both children, listen to events.  We're only
      // going to trigger events on the first child, so an event
      // triggered on the second should cause immediate failures.

      let set = new Set(["event1", "named-event", "object-event", "array-object-event"]);

      childFront.on("event1", (a, b, c) => {
        do_check_eq(a, 1);
        do_check_eq(b, 2);
        do_check_eq(c, 3);
        // Verify that the pre-event handler was called.
        do_check_eq(childFront.event1arg3, 3);
        set.delete("event1");
      });
      childFront.on("named-event", (a, b, c) => {
        do_check_eq(a, 1);
        do_check_eq(b, 2);
        do_check_eq(c, 3);
        set.delete("named-event");
      });
      childFront.on("object-event", (obj) => {
        do_check_true(obj === childFront);
        do_check_eq(childFront.detail, "detail1");
        set.delete("object-event");
      });
      childFront.on("array-object-event", (array) => {
        do_check_true(array[0] === childFront);
        do_check_eq(childFront.detail, "detail2");
        set.delete("array-object-event");
      });

      let fail = function() {
        do_throw("Unexpected event");
      }
      ret[1].on("event1", fail);
      ret[1].on("named-event", fail);
      ret[1].on("object-event", fail);
      ret[1].on("array-object-event", fail);

      return childFront.emitEvents().then(() => {
        trace.expectSend({"type":"emitEvents","to":"<actorid>"});
        trace.expectReceive({"type":"event1","a":1,"b":2,"c":3,"from":"<actorid>"});
        trace.expectReceive({"type":"namedEvent","a":1,"b":2,"c":3,"from":"<actorid>"});
        trace.expectReceive({"type":"objectEvent","detail":{"actor":"<actorid>","childID":"child1","detail":"detail1"},"from":"<actorid>"});
        trace.expectReceive({"type":"arrayObjectEvent","detail":[{"actor":"<actorid>","childID":"child1","detail":"detail2"}],"from":"<actorid>"});
        trace.expectReceive({"value":"correct response","from":"<actorid>"});


        do_check_eq(set.size, 0);
      });
    }).then(ret => {
      return rootFront.getManyChildren();
    }).then(ret => {
      trace.expectSend({"type":"getManyChildren","to":"<actorid>"});
      trace.expectReceive({"foo":"bar","child5":{"actor":"<actorid>","childID":"child5"},"more":[{"actor":"<actorid>","childID":"child6"},{"actor":"<actorid>","childID":"child7"}],"from":"<actorid>"});

      // Check all the crazy stuff we did in getManyChildren
      do_check_eq(ret.foo, "bar");
      do_check_eq(ret.child5.childID, "child5");
      do_check_eq(ret.more[0].childID, "child6");
      do_check_eq(ret.more[1].childID, "child7");
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
