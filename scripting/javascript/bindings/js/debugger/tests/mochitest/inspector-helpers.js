var Cu = Components.utils;

Cu.import("resource://gre/modules/Services.jsm");

// Always log packets when running tests.
Services.prefs.setBoolPref("devtools.debugger.log", true);
SimpleTest.registerCleanupFunction(function() {
  Services.prefs.clearUserPref("devtools.debugger.log");
});

Cu.import("resource://gre/modules/devtools/Loader.jsm");
Cu.import("resource://gre/modules/devtools/dbg-client.jsm");
Cu.import("resource://gre/modules/devtools/dbg-server.jsm");

const {_documentWalker} = devtools.require("devtools/server/actors/inspector");

if (!DebuggerServer.initialized) {
  DebuggerServer.init(() => true);
  DebuggerServer.addBrowserActors();
  SimpleTest.registerCleanupFunction(function() {
    DebuggerServer.destroy();
  });
}

var gAttachCleanups = [];

SimpleTest.registerCleanupFunction(function() {
  for (let cleanup of gAttachCleanups) {
    cleanup();
  }
});

/**
 * Open a tab, load the url, wait for it to signal its readiness,
 * find the tab with the debugger server, and call the callback.
 *
 * Returns a function which can be called to close the opened ta
 * and disconnect its debugger client.
 */
function attachURL(url, callback) {
  var win = window.open(url, "_blank");
  var client = null;

  let cleanup = () => {
    if (client) {
      client.close();
      client = null;
    }
    if (win) {
      win.close();
      win = null;
    }
  };
  gAttachCleanups.push(cleanup);

  window.addEventListener("message", function loadListener(event) {
    if (event.data === "ready") {
      client = new DebuggerClient(DebuggerServer.connectPipe());
      client.connect((applicationType, traits) => {
        client.listTabs(response => {
          for (let tab of response.tabs) {
            if (tab.url === url) {
              window.removeEventListener("message", loadListener, false);
              try {
                callback(null, client, tab, win.document);
              } catch(ex) {
                Cu.reportError(ex);
                dump(ex);
              }
              break;
            }
          }
        });
      });
    }
  }, false);

  return cleanup;
}

function promiseOnce(target, event) {
  let deferred = Promise.defer();
  target.on(event, (...args) => {
    if (args.length === 1) {
      deferred.resolve(args[0]);
    } else {
      deferred.resolve(args);
    }
  });
  return deferred.promise;
}

function sortOwnershipChildren(children) {
  return children.sort((a, b) => a.name.localeCompare(b.name));
}

function serverOwnershipSubtree(walker, node) {
  let actor = walker._refMap.get(node);
  if (!actor) {
    return undefined;
  }

  let children = [];
  let docwalker = _documentWalker(node);
  let child = docwalker.firstChild();
  while (child) {
    let item = serverOwnershipSubtree(walker, child);
    if (item) {
      children.push(item);
    }
    child = docwalker.nextSibling();
  }
  return {
    name: actor.actorID,
    children: sortOwnershipChildren(children)
  }
}

function serverOwnershipTree(walker) {
  let serverConnection = walker.conn._transport._serverConnection;
  let serverWalker = serverConnection.getActor(walker.actorID);

  return {
    root: serverOwnershipSubtree(serverWalker, serverWalker.rootDoc ),
    orphaned: [serverOwnershipSubtree(serverWalker, o.rawNode) for (o of serverWalker._orphaned)],
    retained: [serverOwnershipSubtree(serverWalker, o.rawNode) for (o of serverWalker._retainedOrphans)]
  };
}

function clientOwnershipSubtree(node) {
  return {
    name: node.actorID,
    children: sortOwnershipChildren([clientOwnershipSubtree(child) for (child of node.treeChildren())])
  }
}

function clientOwnershipTree(walker) {
  return {
    root: clientOwnershipSubtree(walker.rootNode),
    orphaned: [clientOwnershipSubtree(o) for (o of walker._orphaned)],
    retained: [clientOwnershipSubtree(o) for (o of walker._retainedOrphans)]
  }
}

function ownershipTreeSize(tree) {
  let size = 1;
  for (let child of tree.children) {
    size += ownershipTreeSize(child);
  }
  return size;
}

function assertOwnershipTrees(walker) {
  let serverTree = serverOwnershipTree(walker);
  let clientTree = clientOwnershipTree(walker);
  is(JSON.stringify(clientTree, null, ' '), JSON.stringify(serverTree, null, ' '), "Server and client ownership trees should match.");

  return ownershipTreeSize(clientTree.root);
}

// Verify that an actorID is inaccessible both from the client library and the server.
function checkMissing(client, actorID) {
  let deferred = Promise.defer();
  let front = client.getActor(actorID);
  ok(!front, "Front shouldn't be accessible from the client for actorID: " + actorID);

  let deferred = Promise.defer();
  client.request({
    to: actorID,
    type: "request",
  }, response => {
    is(response.error, "noSuchActor", "node list actor should no longer be contactable.");
    deferred.resolve(undefined);
  });
  return deferred.promise;
}

// Verify that an actorID is accessible both from the client library and the server.
function checkAvailable(client, actorID) {
  let deferred = Promise.defer();
  let front = client.getActor(actorID);
  ok(front, "Front should be accessible from the client for actorID: " + actorID);

  let deferred = Promise.defer();
  client.request({
    to: actorID,
    type: "garbageAvailableTest",
  }, response => {
    is(response.error, "unrecognizedPacketType", "node list actor should be contactable.");
    deferred.resolve(undefined);
  });
  return deferred.promise;
}

function promiseDone(promise) {
  promise.then(null, err => {
    ok(false, "Promise failed: " + err);
    if (err.stack) {
      dump(err.stack);
    }
    SimpleTest.finish();
  });
}

// Mutation list testing

function isSrcChange(change) {
  return (change.type === "attributes" && change.attributeName === "src");
}

function assertAndStrip(mutations, message, test) {
  let size = mutations.length;
  mutations = mutations.filter(test);
  ok((mutations.size != size), message);
  return mutations;
}

function isSrcChange(change) {
  return change.type === "attributes" && change.attributeName === "src";
}

function isUnload(change) {
  return change.type === "documentUnload";
}

function isFrameLoad(change) {
  return change.type === "frameLoad";
}

function isUnretained(change) {
  return change.type === "unretained";
}

function isChildList(change) {
  return change.type === "childList";
}

// Make sure an iframe's src attribute changed and then
// strip that mutation out of the list.
function assertSrcChange(mutations) {
  return assertAndStrip(mutations, "Should have had an iframe source change.", isSrcChange);
}

// Make sure there's an unload in the mutation list and strip
// that mutation out of the list
function assertUnload(mutations) {
  return assertAndStrip(mutations, "Should have had a document unload change.", isUnload);
}

// Make sure there's a frame load in the mutation list and strip
// that mutation out of the list
function assertFrameLoad(mutations) {
  return assertAndStrip(mutations, "Should have had a frame load change.", isFrameLoad);
}

// Make sure there's a childList change in the mutation list and strip
// that mutation out of the list
function assertChildList(mutations) {
  return assertAndStrip(mutations, "Should have had a frame load change.", isChildList);
}

// Load mutations aren't predictable, so keep accumulating mutations until
// the one we're looking for shows up.
function waitForMutation(walker, test, mutations=[]) {
  let deferred = Promise.defer();
  for (let change of mutations) {
    if (test(change)) {
      deferred.resolve(mutations);
    }
  }

  walker.once("mutations", newMutations => {
    waitForMutation(walker, test, mutations.concat(newMutations)).then(finalMutations => {
      deferred.resolve(finalMutations);
    })
  });

  return deferred.promise;
}


var _tests = [];
function addTest(test) {
  _tests.push(test);
}

function runNextTest() {
  if (_tests.length == 0) {
    SimpleTest.finish()
    return;
  }
  _tests.shift()();
}
