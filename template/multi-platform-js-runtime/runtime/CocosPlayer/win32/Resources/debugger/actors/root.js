/* -*- tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ft=javascript ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

/* Root actor for the remote debugging protocol. */

/**
 * Methods shared between RootActor and BrowserTabActor.
 */

/**
 * Populate |this._extraActors| as specified by |aFactories|, reusing whatever
 * actors are already there. Add all actors in the final extra actors table to
 * |aPool|.
 *
 * The root actor and the tab actor use this to instantiate actors that other
 * parts of the browser have specified with DebuggerServer.addTabActor antd
 * DebuggerServer.addGlobalActor.
 *
 * @param aFactories
 *     An object whose own property names are the names of properties to add to
 *     some reply packet (say, a tab actor grip or the "listTabs" response
 *     form), and whose own property values are actor constructor functions, as
 *     documented for addTabActor and addGlobalActor.
 *
 * @param this
 *     The BrowserRootActor or BrowserTabActor with which the new actors will
 *     be associated. It should support whatever API the |aFactories|
 *     constructor functions might be interested in, as it is passed to them.
 *     For the sake of CommonCreateExtraActors itself, it should have at least
 *     the following properties:
 *
 *     - _extraActors
 *        An object whose own property names are factory table (and packet)
 *        property names, and whose values are no-argument actor constructors,
 *        of the sort that one can add to an ActorPool.
 *
 *     - conn
 *        The DebuggerServerConnection in which the new actors will participate.
 *
 *     - actorID
 *        The actor's name, for use as the new actors' parentID.
 */
function CommonCreateExtraActors(aFactories, aPool) {
  // Walk over global actors added by extensions.
  for (let name in aFactories) {
    let actor = this._extraActors[name];
    if (!actor) {
      actor = aFactories[name].bind(null, this.conn, this);
      actor.prototype = aFactories[name].prototype;
      actor.parentID = this.actorID;
      this._extraActors[name] = actor;
    }
    aPool.addActor(actor);
  }
}

/**
 * Append the extra actors in |this._extraActors|, constructed by a prior call
 * to CommonCreateExtraActors, to |aObject|.
 *
 * @param aObject
 *     The object to which the extra actors should be added, under the
 *     property names given in the |aFactories| table passed to
 *     CommonCreateExtraActors.
 *
 * @param this
 *     The BrowserRootActor or BrowserTabActor whose |_extraActors| table we
 *     should use; see above.
 */
function CommonAppendExtraActors(aObject) {
  for (let name in this._extraActors) {
    let actor = this._extraActors[name];
    aObject[name] = actor.actorID;
  }
}

/**
 * Create a remote debugging protocol root actor.
 *
 * @param aConnection
 *     The DebuggerServerConnection whose root actor we are constructing.
 *
 * @param aParameters
 *     The properties of |aParameters| provide backing objects for the root
 *     actor's requests; if a given property is omitted from |aParameters|, the
 *     root actor won't implement the corresponding requests or notifications.
 *     Supported properties:
 *
 *     - tabList: a live list (see below) of tab actors. If present, the
 *       new root actor supports the 'listTabs' request, providing the live
 *       list's elements as its tab actors, and sending 'tabListChanged'
 *       notifications when the live list's contents change. One actor in
 *       this list must have a true '.selected' property.
 *
 *     - globalActorFactories: an object |A| describing further actors to
 *       attach to the 'listTabs' reply. This is the type accumulated by
 *       DebuggerServer.addGlobalActor. For each own property |P| of |A|,
 *       the root actor adds a property named |P| to the 'listTabs'
 *       reply whose value is the name of an actor constructed by
 *       |A[P]|.
 *
 *     - onShutdown: a function to call when the root actor is disconnected.
 *
 * Instance properties:
 *
 * - applicationType: the string the root actor will include as the
 *      "applicationType" property in the greeting packet. By default, this
 *      is "browser".
 *
 * Live lists:
 *
 * A "live list", as used for the |tabList|, is an object that presents a
 * list of actors, and also notifies its clients of changes to the list. A
 * live list's interface is two properties:
 *
 * - iterator: a method that returns an iterator. A for-of loop will call
 *             this method to obtain an iterator for the loop, so if LL is
 *             a live list, one can simply write 'for (i of LL) ...'.
 *
 * - onListChanged: a handler called, with no arguments, when the set of
 *             values the iterator would produce has changed since the last
 *             time 'iterator' was called. This may only be set to null or a
 *             callable value (one for which the typeof operator returns
 *             'function'). (Note that the live list will not call the
 *             onListChanged handler until the list has been iterated over
 *             once; if nobody's seen the list in the first place, nobody
 *             should care if its contents have changed!)
 *
 * When the list changes, the list implementation should ensure that any
 * actors yielded in previous iterations whose referents (tabs) still exist
 * get yielded again in subsequent iterations. If the underlying referent
 * is the same, the same actor should be presented for it.
 *
 * The root actor registers an 'onListChanged' handler on the appropriate
 * list when it may need to send the client 'tabListChanged' notifications,
 * and is careful to remove the handler whenever it does not need to send
 * such notifications (including when it is disconnected). This means that
 * live list implementations can use the state of the handler property (set
 * or null) to install and remove observers and event listeners.
 *
 * Note that, as the only way for the root actor to see the members of the
 * live list is to begin an iteration over the list, the live list need not
 * actually produce any actors until they are reached in the course of
 * iteration: alliterative lazy live lists.
 */
function RootActor(aConnection, aParameters) {
  this.conn = aConnection;
  this._parameters = aParameters;
  this._onTabListChanged = this.onTabListChanged.bind(this);
  this._onAddonListChanged = this.onAddonListChanged.bind(this);
  this._extraActors = {};
}

RootActor.prototype = {
  constructor: RootActor,
  applicationType: "browser",

  /**
   * Return a 'hello' packet as specified by the Remote Debugging Protocol.
   */
  sayHello: function() {
    return {
      from: this.actorID,
      applicationType: this.applicationType,
      /* This is not in the spec, but it's used by tests. */
      testConnectionPrefix: this.conn.prefix,
      traits: {
        sources: true,
        editOuterHTML: true
      }
    };
  },

  /**
   * This is true for the root actor only, used by some child actors
   */
  get isRootActor() true,

  /**
   * The (chrome) window, for use by child actors
   */
  get window() Services.wm.getMostRecentWindow(DebuggerServer.chromeWindowType),

  /**
   * Disconnects the actor from the browser window.
   */
  disconnect: function() {
    /* Tell the live lists we aren't watching any more. */
    if (this._parameters.tabList) {
      this._parameters.tabList.onListChanged = null;
    }
    if (this._parameters.addonList) {
      this._parameters.addonList.onListChanged = null;
    }
    if (typeof this._parameters.onShutdown === 'function') {
      this._parameters.onShutdown();
    }
    this._extraActors = null;
  },

  /* The 'listTabs' request and the 'tabListChanged' notification. */

  /**
   * Handles the listTabs request. The actors will survive until at least
   * the next listTabs request.
   */
  onListTabs: function() {
    let tabList = this._parameters.tabList;
    if (!tabList) {
      return { from: this.actorID, error: "noTabs",
               message: "This root actor has no browser tabs." };
    }

    /*
     * Walk the tab list, accumulating the array of tab actors for the
     * reply, and moving all the actors to a new ActorPool. We'll
     * replace the old tab actor pool with the one we build here, thus
     * retiring any actors that didn't get listed again, and preparing any
     * new actors to receive packets.
     */
    let newActorPool = new ActorPool(this.conn);
    let tabActorList = [];
    let selected;
    return tabList.getList().then((tabActors) => {
      for (let tabActor of tabActors) {
        if (tabActor.selected) {
          selected = tabActorList.length;
        }
        tabActor.parentID = this.actorID;
        newActorPool.addActor(tabActor);
        tabActorList.push(tabActor);
      }

      /* DebuggerServer.addGlobalActor support: create actors. */
      this._createExtraActors(this._parameters.globalActorFactories, newActorPool);

      /*
       * Drop the old actorID -> actor map. Actors that still mattered were
       * added to the new map; others will go away.
       */
      if (this._tabActorPool) {
        this.conn.removeActorPool(this._tabActorPool);
      }
      this._tabActorPool = newActorPool;
      this.conn.addActorPool(this._tabActorPool);

      let reply = {
        "from": this.actorID,
        "selected": selected || 0,
        "tabs": [actor.form() for (actor of tabActorList)],
      };

      /* DebuggerServer.addGlobalActor support: name actors in 'listTabs' reply. */
      this._appendExtraActors(reply);

      /*
       * Now that we're actually going to report the contents of tabList to
       * the client, we're responsible for letting the client know if it
       * changes.
       */
      tabList.onListChanged = this._onTabListChanged;

      return reply;
    });
  },

  onTabListChanged: function () {
    this.conn.send({ from: this.actorID, type:"tabListChanged" });
    /* It's a one-shot notification; no need to watch any more. */
    this._parameters.tabList.onListChanged = null;
  },

  onListAddons: function () {
    let addonList = this._parameters.addonList;
    if (!addonList) {
      return { from: this.actorID, error: "noAddons",
               message: "This root actor has no browser addons." };
    }

    return addonList.getList().then((addonActors) => {
      let addonActorPool = new ActorPool(this.conn);
      for (let addonActor of addonActors) {
          addonActorPool.addActor(addonActor);
      }

      if (this._addonActorPool) {
        this.conn.removeActorPool(this._addonActorPool);
      }
      this._addonActorPool = addonActorPool;
      this.conn.addActorPool(this._addonActorPool);

      addonList.onListChanged = this._onAddonListChanged;

      return {
        "from": this.actorID,
        "addons": [addonActor.form() for (addonActor of addonActors)]
      };
    });
  },

  onAddonListChanged: function () {
    this.conn.send({ from: this.actorID, type: "addonListChanged" });
    this._parameters.addonList.onListChanged = null;
  },

  /* This is not in the spec, but it's used by tests. */
  onEcho: function (aRequest) {
    /*
     * Request packets are frozen. Copy aRequest, so that
     * DebuggerServerConnection.onPacket can attach a 'from' property.
     */
    return JSON.parse(JSON.stringify(aRequest));
  },

  /* Support for DebuggerServer.addGlobalActor. */
  _createExtraActors: CommonCreateExtraActors,
  _appendExtraActors: CommonAppendExtraActors,

  /* ThreadActor hooks. */

  /**
   * Prepare to enter a nested event loop by disabling debuggee events.
   */
  preNest: function() {
    // Disable events in all open windows.
    let e = windowMediator.getEnumerator(null);
    while (e.hasMoreElements()) {
      let win = e.getNext();
      let windowUtils = win.QueryInterface(Ci.nsIInterfaceRequestor)
                           .getInterface(Ci.nsIDOMWindowUtils);
      windowUtils.suppressEventHandling(true);
      windowUtils.suspendTimeouts();
    }
  },

  /**
   * Prepare to exit a nested event loop by enabling debuggee events.
   */
  postNest: function(aNestData) {
    // Enable events in all open windows.
    let e = windowMediator.getEnumerator(null);
    while (e.hasMoreElements()) {
      let win = e.getNext();
      let windowUtils = win.QueryInterface(Ci.nsIInterfaceRequestor)
                           .getInterface(Ci.nsIDOMWindowUtils);
      windowUtils.resumeTimeouts();
      windowUtils.suppressEventHandling(false);
    }
  },

  /* ChromeDebuggerActor hooks. */

  /**
   * Add the specified actor to the default actor pool connection, in order to
   * keep it alive as long as the server is. This is used by breakpoints in the
   * thread and chrome debugger actors.
   *
   * @param actor aActor
   *        The actor object.
   */
  addToParentPool: function(aActor) {
    this.conn.addActor(aActor);
  },

  /**
   * Remove the specified actor from the default actor pool.
   *
   * @param BreakpointActor aActor
   *        The actor object.
   */
  removeFromParentPool: function(aActor) {
    this.conn.removeActor(aActor);
  }
}

RootActor.prototype.requestTypes = {
  "listTabs": RootActor.prototype.onListTabs,
  "listAddons": RootActor.prototype.onListAddons,
  "echo": RootActor.prototype.onEcho
};
