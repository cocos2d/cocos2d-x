/* -*- js-indent-level: 2; indent-tabs-mode: nil -*- */
/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

// const { Cc, Ci, Cu } = require("chrome");
// const { DebuggerServer, ActorPool } = require("devtools/server/main");
// const { EnvironmentActor, ThreadActor } = require("devtools/server/actors/script");
// const { ObjectActor, LongStringActor, createValueGrip, stringIsLong } = require("devtools/server/actors/object");
// const DevToolsUtils = require("devtools/toolkit/DevToolsUtils");

// Cu.import("resource://gre/modules/XPCOMUtils.jsm");

// XPCOMUtils.defineLazyModuleGetter(this, "Services",
//                                   "resource://gre/modules/Services.jsm");
// XPCOMUtils.defineLazyGetter(this, "NetworkMonitor", () => {
//   return require("devtools/toolkit/webconsole/network-monitor")
//          .NetworkMonitor;
// });
// XPCOMUtils.defineLazyGetter(this, "NetworkMonitorChild", () => {
//   return require("devtools/toolkit/webconsole/network-monitor")
//          .NetworkMonitorChild;
// });
// XPCOMUtils.defineLazyGetter(this, "ConsoleProgressListener", () => {
//   return require("devtools/toolkit/webconsole/network-monitor")
//          .ConsoleProgressListener;
// });
// XPCOMUtils.defineLazyGetter(this, "events", () => {
//   return require("sdk/event/core");
// });
// XPCOMUtils.defineLazyGetter(this, "ServerLoggingListener", () => {
//   return require("devtools/toolkit/webconsole/server-logger")
//          .ServerLoggingListener;
// });

let webutils = require('script/debugger/webconsole/utils.js', 'debug');

Object.defineProperty(this, "JSPropertyProvider", {
  get: function() {
    // if (prop == "WebConsoleUtils") {
    //   prop = "Utils";
    // }
    return webutils["JSPropertyProvider"];
  }.bind(null, "JSPropertyProvider"),
  configurable: true,
  enumerable: true
});


/**
 * The WebConsoleActor implements capabilities needed for the Web Console
 * feature.
 *
 * @constructor
 * @param object aConnection
 *        The connection to the client, DebuggerServerConnection.
 * @param object [aParentActor]
 *        Optional, the parent actor.
 */
function WebConsoleActor(aConnection, aParentActor)
{
  this.conn = aConnection;
  this.parentActor = aParentActor;

  this._actorPool = new ActorPool(this.conn);
  this.conn.addActorPool(this._actorPool);

  this._prefs = {};

  this.dbg = this.parentActor.makeDebugger();

  this._netEvents = new Map();
  this._gripDepth = 0;
  this._listeners = new Set();
  this._lastConsoleInputEvaluation = undefined;

  this.objectGrip = this.objectGrip.bind(this);
  // this._onWillNavigate = this._onWillNavigate.bind(this);
  // this._onChangedToplevelDocument = this._onChangedToplevelDocument.bind(this);
  // events.on(this.parentActor, "changed-toplevel-document", this._onChangedToplevelDocument);
  // // this._onObserverNotification = this._onObserverNotification.bind(this);
  // if (this.parentActor.isRootActor) {
  //   Services.obs.addObserver(this._onObserverNotification,
  //                            "last-pb-context-exited", false);
  // }

  this.traits = {
    customNetworkRequest: !this._parentIsContentActor,
    evaluateJSAsync: true,
    transferredResponseSize: true
  };
}

// WebConsoleActor.l10n = new WebConsoleUtils.l10n("chrome://global/locale/console.properties");

WebConsoleActor.prototype =
{
  /**
   * Debugger instance.
   *
   * @see jsdebugger.jsm
   */
  dbg: null,

  /**
   * This is used by the ObjectActor to keep track of the depth of grip() calls.
   * @private
   * @type number
   */
  _gripDepth: null,

  /**
   * Actor pool for all of the actors we send to the client.
   * @private
   * @type object
   * @see ActorPool
   */
  _actorPool: null,

  /**
   * Web Console-related preferences.
   * @private
   * @type object
   */
  _prefs: null,

  /**
   * Holds a map between nsIChannel objects and NetworkEventActors for requests
   * created with sendHTTPRequest.
   *
   * @private
   * @type Map
   */
  _netEvents: null,

  /**
   * Holds a set of all currently registered listeners.
   *
   * @private
   * @type Set
   */
  _listeners: null,

  /**
   * The debugger server connection instance.
   * @type object
   */
  conn: null,

  /**
   * List of supported features by the console actor.
   * @type object
   */
  traits: null,

  /**
   * Boolean getter that tells if the parent actor is a ContentActor.
   *
   * @private
   * @type boolean
   */
  get _parentIsContentActor() {
    return "ContentActor" in DebuggerServer &&
            this.parentActor instanceof DebuggerServer.ContentActor;
  },

  /**
   * The window we work with.
   * @type nsIDOMWindow
   */
  get window() {
    if (this.parentActor.isRootActor) {
      return this._getWindowForBrowserConsole();
    }
    return this.parentActor.window;
  },

  /**
   * Get a window to use for the browser console.
   *
   * @private
   * @return nsIDOMWindow
   *         The window to use, or null if no window could be found.
   */
  _getWindowForBrowserConsole: function WCA__getWindowForBrowserConsole()
  {
    // Check if our last used chrome window is still live.
    let window = this._lastChromeWindow && this._lastChromeWindow.get();
    // If not, look for a new one.
    if (!window || window.closed) {
      window = this.parentActor.window;
      if (!window) {
        // Try to find the Browser Console window to use instead.
        window = Services.wm.getMostRecentWindow("devtools:webconsole");
        // We prefer the normal chrome window over the console window,
        // so we'll look for those windows in order to replace our reference.
        let onChromeWindowOpened = () => {
          // We'll look for this window when someone next requests window()
          Services.obs.removeObserver(onChromeWindowOpened, "domwindowopened");
          this._lastChromeWindow = null;
        };
        Services.obs.addObserver(onChromeWindowOpened, "domwindowopened", false);
      }

      this._handleNewWindow(window);
    }

    return window;
  },

  /**
   * Store a newly found window on the actor to be used in the future.
   *
   * @private
   * @param nsIDOMWindow window
   *        The window to store on the actor (can be null).
   */
  _handleNewWindow: function WCA__handleNewWindow(window)
  {
    if (window) {
      if (this._hadChromeWindow) {
        let contextChangedMsg = WebConsoleActor.l10n.getStr("evaluationContextChanged");
        Services.console.logStringMessage(contextChangedMsg);
      }
      this._lastChromeWindow = Cu.getWeakReference(window);
      this._hadChromeWindow = true;
    } else {
      this._lastChromeWindow = null;
    }
  },

  /**
   * Whether we've been using a window before.
   *
   * @private
   * @type boolean
   */
  _hadChromeWindow: false,

  /**
   * A weak reference to the last chrome window we used to work with.
   *
   * @private
   * @type nsIWeakReference
   */
  _lastChromeWindow: null,

  // The evalWindow is used at the scope for JS evaluation.
  _evalWindow: null,
  get evalWindow() {
    return this._evalWindow || this.window;
  },

  set evalWindow(aWindow) {
    this._evalWindow = aWindow;

    if (!this._progressListenerActive) {
      events.on(this.parentActor, "will-navigate", this._onWillNavigate);
      this._progressListenerActive = true;
    }
  },

  /**
   * Flag used to track if we are listening for events from the progress
   * listener of the tab actor. We use the progress listener to clear
   * this.evalWindow on page navigation.
   *
   * @private
   * @type boolean
   */
  _progressListenerActive: false,

  /**
   * The ConsoleServiceListener instance.
   * @type object
   */
  consoleServiceListener: null,

  /**
   * The ConsoleAPIListener instance.
   */
  consoleAPIListener: null,

  /**
   * The NetworkMonitor instance.
   */
  networkMonitor: null,

  /**
   * The ConsoleProgressListener instance.
   */
  consoleProgressListener: null,

  /**
   * The ConsoleReflowListener instance.
   */
  consoleReflowListener: null,

  /**
   * The Web Console Commands names cache.
   * @private
   * @type array
   */
  _webConsoleCommandsCache: null,

  actorPrefix: "console",

  get globalDebugObject() {
    return this.parentActor.threadActor.globalDebugObject;
  },

  grip: function WCA_grip()
  {
    return { actor: this.actorID };
  },

  hasNativeConsoleAPI: function WCA_hasNativeConsoleAPI(aWindow) {
    let isNative = false;
    try {
      // We are very explicitly examining the "console" property of
      // the non-Xrayed object here.
      let console = aWindow.wrappedJSObject.console;
      isNative = console instanceof aWindow.Console;
    }
    catch (ex) { }
    return isNative;
  },

  _findProtoChain: ThreadActor.prototype._findProtoChain,
  _removeFromProtoChain: ThreadActor.prototype._removeFromProtoChain,

  /**
   * Destroy the current WebConsoleActor instance.
   */
  disconnect: function WCA_disconnect()
  {
    if (this.consoleServiceListener) {
      this.consoleServiceListener.destroy();
      this.consoleServiceListener = null;
    }
    if (this.consoleAPIListener) {
      this.consoleAPIListener.destroy();
      this.consoleAPIListener = null;
    }
    if (this.networkMonitor) {
      this.networkMonitor.destroy();
      this.networkMonitor = null;
    }
    if (this.consoleProgressListener) {
      this.consoleProgressListener.destroy();
      this.consoleProgressListener = null;
    }
    if (this.consoleReflowListener) {
      this.consoleReflowListener.destroy();
      this.consoleReflowListener = null;
    }
    if (this.serverLoggingListener) {
      this.serverLoggingListener.destroy();
      this.serverLoggingListener = null;
    }

    events.off(this.parentActor, "changed-toplevel-document",
               this._onChangedToplevelDocument);

    this.conn.removeActorPool(this._actorPool);

    if (this.parentActor.isRootActor) {
      Services.obs.removeObserver(this._onObserverNotification,
                                  "last-pb-context-exited");
    }

    this._actorPool = null;
    this._webConsoleCommandsCache = null;
    this._lastConsoleInputEvaluation = null;
    this._evalWindow = null;
    this._netEvents.clear();
    this.dbg.enabled = false;
    this.dbg = null;
    this.conn = null;
  },

  /**
   * Create and return an environment actor that corresponds to the provided
   * Debugger.Environment. This is a straightforward clone of the ThreadActor's
   * method except that it stores the environment actor in the web console
   * actor's pool.
   *
   * @param Debugger.Environment aEnvironment
   *        The lexical environment we want to extract.
   * @return The EnvironmentActor for aEnvironment or undefined for host
   *         functions or functions scoped to a non-debuggee global.
   */
  createEnvironmentActor: function WCA_createEnvironmentActor(aEnvironment) {
    if (!aEnvironment) {
      return undefined;
    }

    if (aEnvironment.actor) {
      return aEnvironment.actor;
    }

    let actor = new EnvironmentActor(aEnvironment, this);
    this._actorPool.addActor(actor);
    aEnvironment.actor = actor;

    return actor;
  },

  /**
   * Create a grip for the given value.
   *
   * @param mixed aValue
   * @return object
   */
  createValueGrip: function WCA_createValueGrip(aValue)
  {
    return createValueGrip(aValue, this._actorPool, this.objectGrip);
  },

  /**
   * Make a debuggee value for the given value.
   *
   * @param mixed aValue
   *        The value you want to get a debuggee value for.
   * @param boolean aUseObjectGlobal
   *        If |true| the object global is determined and added as a debuggee,
   *        otherwise |this.window| is used when makeDebuggeeValue() is invoked.
   * @return object
   *         Debuggee value for |aValue|.
   */
  makeDebuggeeValue: function WCA_makeDebuggeeValue(aValue, aUseObjectGlobal)
  {
    let global = this.window;
    if (aUseObjectGlobal && typeof aValue == "object") {
      try {
        global = Cu.getGlobalForObject(aValue);
      }
      catch (ex) {
        // The above can throw an exception if aValue is not an actual object.
      }
    }
    let dbgGlobal = this.dbg.makeGlobalObjectReference(global);
    return dbgGlobal.makeDebuggeeValue(aValue);
  },

  /**
   * Create a grip for the given object.
   *
   * @param object aObject
   *        The object you want.
   * @param object aPool
   *        An ActorPool where the new actor instance is added.
   * @param object
   *        The object grip.
   */
  objectGrip: function WCA_objectGrip(aObject, aPool)
  {
    let actor = new ObjectActor(aObject, {
      getGripDepth: () => this._gripDepth,
      incrementGripDepth: () => this._gripDepth++,
      decrementGripDepth: () => this._gripDepth--,
      createValueGrip: v => this.createValueGrip(v),
      sources: () => DevToolsUtils.reportException("WebConsoleActor",
        Error("sources not yet implemented")),
      createEnvironmentActor: (env) => this.createEnvironmentActor(env),
      getGlobalDebugObject: () => this.globalDebugObject
    });
    aPool.addActor(actor);
    return actor.grip();
  },

  /**
   * Create a grip for the given string.
   *
   * @param string aString
   *        The string you want to create the grip for.
   * @param object aPool
   *        An ActorPool where the new actor instance is added.
   * @return object
   *         A LongStringActor object that wraps the given string.
   */
  longStringGrip: function WCA_longStringGrip(aString, aPool)
  {
    let actor = new LongStringActor(aString);
    aPool.addActor(actor);
    return actor.grip();
  },

  /**
   * Create a long string grip if needed for the given string.
   *
   * @private
   * @param string aString
   *        The string you want to create a long string grip for.
   * @return string|object
   *         A string is returned if |aString| is not a long string.
   *         A LongStringActor grip is returned if |aString| is a long string.
   */
  _createStringGrip: function NEA__createStringGrip(aString)
  {
    if (aString && stringIsLong(aString)) {
      return this.longStringGrip(aString, this._actorPool);
    }
    return aString;
  },

  /**
   * Get an object actor by its ID.
   *
   * @param string aActorID
   * @return object
   */
  getActorByID: function WCA_getActorByID(aActorID)
  {
    return this._actorPool.get(aActorID);
  },

  /**
   * Release an actor.
   *
   * @param object aActor
   *        The actor instance you want to release.
   */
  releaseActor: function WCA_releaseActor(aActor)
  {
    this._actorPool.removeActor(aActor.actorID);
  },

  /**
   * Returns the latest web console input evaluation.
   * This is undefined if no evaluations have been completed.
   *
   * @return object
   */
  getLastConsoleInputEvaluation: function WCU_getLastConsoleInputEvaluation()
  {
    return this._lastConsoleInputEvaluation;
  },

  //////////////////
  // Request handlers for known packet types.
  //////////////////

  /**
   * Handler for the "startListeners" request.
   *
   * @param object aRequest
   *        The JSON request object received from the Web Console client.
   * @return object
   *         The response object which holds the startedListeners array.
   */
  onStartListeners: function WCA_onStartListeners(aRequest)
  {
    let startedListeners = [];
    let window = !this.parentActor.isRootActor ? this.window : null;
    let appId = null;
    let messageManager = null;

    if (this._parentIsContentActor) {
      appId = this.parentActor.docShell.appId;
      messageManager = this.parentActor.messageManager;
    }

    while (aRequest.listeners.length > 0) {
      let listener = aRequest.listeners.shift();
      switch (listener) {
        case "PageError":
          // if (!this.consoleServiceListener) {
          //   this.consoleServiceListener =
          //     new ConsoleServiceListener(window, this);
          //   this.consoleServiceListener.init();
          // }
          // startedListeners.push(listener);
          break;
        case "ConsoleAPI":
          if (!this.consoleAPIListener) {
            this.consoleAPIListener =
              new ConsoleAPIListener(window, this);
            this.consoleAPIListener.init();
          }
          startedListeners.push(listener);
          break;
        case "NetworkActivity":
          // if (!this.networkMonitor) {
          //   if (appId || messageManager) {
          //     this.networkMonitor =
          //       new NetworkMonitorChild(appId, messageManager,
          //                               this.parentActor.actorID, this);
          //   }
          //   else {
          //     this.networkMonitor = new NetworkMonitor({ window: window }, this);
          //   }
          //   this.networkMonitor.init();
          // }
          // startedListeners.push(listener);
          break;
        case "FileActivity":
          // if (this.window instanceof Ci.nsIDOMWindow) {
          //   if (!this.consoleProgressListener) {
          //     this.consoleProgressListener =
          //       new ConsoleProgressListener(this.window, this);
          //   }
          //   this.consoleProgressListener.startMonitor(this.consoleProgressListener.
          //                                             MONITOR_FILE_ACTIVITY);
          //   startedListeners.push(listener);
          // }
          break;
        case "ReflowActivity":
          if (!this.consoleReflowListener) {
            this.consoleReflowListener =
              new ConsoleReflowListener(this.window, this);
          }
          startedListeners.push(listener);
          break;
        case "ServerLogging":
          if (!this.serverLoggingListener) {
            this.serverLoggingListener =
              new ServerLoggingListener(this.window, this);
          }
          startedListeners.push(listener);
          break;
      }
    }

    // Update the live list of running listeners
    startedListeners.forEach(this._listeners.add, this._listeners);

    return {
      startedListeners: startedListeners,
      nativeConsoleAPI: this.hasNativeConsoleAPI(this.window),
      traits: this.traits,
    };
  },

  /**
   * Handler for the "stopListeners" request.
   *
   * @param object aRequest
   *        The JSON request object received from the Web Console client.
   * @return object
   *         The response packet to send to the client: holds the
   *         stoppedListeners array.
   */
  onStopListeners: function WCA_onStopListeners(aRequest)
  {
    let stoppedListeners = [];

    // If no specific listeners are requested to be detached, we stop all
    // listeners.
    let toDetach = aRequest.listeners ||
                   ["PageError", "ConsoleAPI", "NetworkActivity",
                    "FileActivity", "ServerLogging"];

    while (toDetach.length > 0) {
      let listener = toDetach.shift();
      switch (listener) {
        case "PageError":
          if (this.consoleServiceListener) {
            this.consoleServiceListener.destroy();
            this.consoleServiceListener = null;
          }
          stoppedListeners.push(listener);
          break;
        case "ConsoleAPI":
          if (this.consoleAPIListener) {
            this.consoleAPIListener.destroy();
            this.consoleAPIListener = null;
          }
          stoppedListeners.push(listener);
          break;
        case "NetworkActivity":
          if (this.networkMonitor) {
            this.networkMonitor.destroy();
            this.networkMonitor = null;
          }
          stoppedListeners.push(listener);
          break;
        case "FileActivity":
          if (this.consoleProgressListener) {
            this.consoleProgressListener.stopMonitor(this.consoleProgressListener.
                                                     MONITOR_FILE_ACTIVITY);
            this.consoleProgressListener = null;
          }
          stoppedListeners.push(listener);
          break;
        case "ReflowActivity":
          if (this.consoleReflowListener) {
            this.consoleReflowListener.destroy();
            this.consoleReflowListener = null;
          }
          stoppedListeners.push(listener);
          break;
        case "ServerLogging":
          if (this.serverLoggingListener) {
            this.serverLoggingListener.destroy();
            this.serverLoggingListener = null;
          }
          stoppedListeners.push(listener);
          break;
      }
    }

    // Update the live list of running listeners
    stoppedListeners.forEach(this._listeners.delete, this._listeners);

    return { stoppedListeners: stoppedListeners };
  },

  /**
   * Handler for the "getCachedMessages" request. This method sends the cached
   * error messages and the window.console API calls to the client.
   *
   * @param object aRequest
   *        The JSON request object received from the Web Console client.
   * @return object
   *         The response packet to send to the client: it holds the cached
   *         messages array.
   */
  onGetCachedMessages: function WCA_onGetCachedMessages(aRequest)
  {
    let types = aRequest.messageTypes;
    if (!types) {
      return {
        error: "missingParameter",
        message: "The messageTypes parameter is missing.",
      };
    }

    let messages = [];

    while (types.length > 0) {
      let type = types.shift();
      switch (type) {
        case "ConsoleAPI": {
          if (!this.consoleAPIListener) {
            break;
          }
          let cache = this.consoleAPIListener
                      .getCachedMessages(!this.parentActor.isRootActor);
          cache.forEach((aMessage) => {
            let message = this.prepareConsoleMessageForRemote(aMessage);
            message._type = type;
            messages.push(message);
          });
          break;
        }
        case "PageError": {
          if (!this.consoleServiceListener) {
            break;
          }
          let cache = this.consoleServiceListener
                      .getCachedMessages(!this.parentActor.isRootActor);
          cache.forEach((aMessage) => {
            let message = null;
            if (aMessage instanceof Ci.nsIScriptError) {
              message = this.preparePageErrorForRemote(aMessage);
              message._type = type;
            }
            else {
              message = {
                _type: "LogMessage",
                message: this._createStringGrip(aMessage.message),
                timeStamp: aMessage.timeStamp,
              };
            }
            messages.push(message);
          });
          break;
        }
      }
    }

    return {
      from: this.actorID,
      messages: messages,
    };
  },

  /**
   * Handler for the "evaluateJSAsync" request. This method evaluates the given
   * JavaScript string and sends back a packet with a unique ID.
   * The result will be returned later as an unsolicited `evaluationResult`,
   * that can be associated back to this request via the `resultID` field.
   *
   * @param object aRequest
   *        The JSON request object received from the Web Console client.
   * @return object
   *         The response packet to send to with the unique id in the
   *         `resultID` field.
   */
  onEvaluateJSAsync: function WCA_onEvaluateJSAsync(aRequest)
  {
    // We want to be able to run console commands without waiting
    // for the first to return (see Bug 1088861).

    // First, send a response packet with the id only.
    let resultID = Date.now();
    this.conn.send({
      from: this.actorID,
      resultID: resultID
    });

    // Then, execute the script that may pause.
    let response = this.onEvaluateJS(aRequest);
    response.resultID = resultID;

    // Finally, send an unsolicited evaluationResult packet with
    // the normal return value
    this.conn.sendActorEvent(this.actorID, "evaluationResult", response);
  },

  /**
   * Handler for the "evaluateJS" request. This method evaluates the given
   * JavaScript string and sends back the result.
   *
   * @param object aRequest
   *        The JSON request object received from the Web Console client.
   * @return object
   *         The evaluation response packet.
   */
  onEvaluateJS: function WCA_onEvaluateJS(aRequest)
  {
    let input = aRequest.text;
    let timestamp = Date.now();

    let evalOptions = {
      bindObjectActor: aRequest.bindObjectActor,
      frameActor: aRequest.frameActor,
      url: aRequest.url,
      selectedNodeActor: aRequest.selectedNodeActor,
    };

    let evalInfo = this.evalWithDebugger(input, evalOptions);
    let evalResult = evalInfo.result;
    let helperResult = evalInfo.helperResult;

    let result, errorMessage, errorGrip = null;
    if (evalResult) {
      if ("return" in evalResult) {
        result = evalResult.return;
      } else if ("yield" in evalResult) {
        result = evalResult.yield;
      } else if ("throw" in evalResult) {
        let error = evalResult.throw;
        errorGrip = this.createValueGrip(error);
        errorMessage = error && (typeof error === "object")
          ? error.unsafeDereference().toString()
          : "" + error;
      }
    }

    // If a value is encountered that the debugger server doesn't support yet,
    // the console should remain functional.
    let resultGrip;
    try {
      resultGrip = this.createValueGrip(result);
    } catch (e) {
      errorMessage = e;
    }

    this._lastConsoleInputEvaluation = result;

    return {
      from: this.actorID,
      input: input,
      result: resultGrip,
      timestamp: timestamp,
      exception: errorGrip,
      exceptionMessage: this._createStringGrip(errorMessage),
      helperResult: helperResult,
    };
  },

  /**
   * The Autocomplete request handler.
   *
   * @param object aRequest
   *        The request message - what input to autocomplete.
   * @return object
   *         The response message - matched properties.
   */
  onAutocomplete: function WCA_onAutocomplete(aRequest)
  {
    let frameActorId = aRequest.frameActor;
    let dbgObject = null;
    let environment = null;

    // This is the case of the paused debugger
    if (frameActorId) {
      let frameActor = this.conn.getActor(frameActorId);
      if (frameActor) {
        let frame = frameActor.frame;
        environment = frame.environment;
      }
      else {
        log("Web Console Actor: the frame actor was not found: " +
                       frameActorId);
      }
    }
    // This is the general case (non-paused debugger)
    else {
      dbgObject = this.dbg.makeGlobalObjectReference(this.evalWindow);
    }

    let result = JSPropertyProvider(dbgObject, environment, aRequest.text,
                                    aRequest.cursor, frameActorId) || {};
    let matches = result.matches || [];
    let reqText = aRequest.text.substr(0, aRequest.cursor);

    // We consider '$' as alphanumerc because it is used in the names of some
    // helper functions.
    let lastNonAlphaIsDot = /[.][a-zA-Z0-9$]*$/.test(reqText);
    if (!lastNonAlphaIsDot) {
      if (!this._webConsoleCommandsCache) {
        let helpers = {
          sandbox: Object.create(null)
        };
        addWebConsoleCommands(helpers);
        this._webConsoleCommandsCache =
          Object.getOwnPropertyNames(helpers.sandbox);
      }
      matches = matches.concat(this._webConsoleCommandsCache
          .filter(n => n.startsWith(result.matchProp)));
    }

    return {
      from: this.actorID,
      matches: matches.sort(),
      matchProp: result.matchProp,
    };
  },

  /**
   * The "clearMessagesCache" request handler.
   */
  onClearMessagesCache: function WCA_onClearMessagesCache()
  {
    // TODO: Bug 717611 - Web Console clear button does not clear cached errors
    let windowId = !this.parentActor.isRootActor ?
                   WebConsoleUtils.getInnerWindowId(this.window) : null;
    let ConsoleAPIStorage = Cc["@mozilla.org/consoleAPI-storage;1"]
                              .getService(Ci.nsIConsoleAPIStorage);
    ConsoleAPIStorage.clearEvents(windowId);

    CONSOLE_WORKER_IDS.forEach((aId) => {
      ConsoleAPIStorage.clearEvents(aId);
    });

    if (this.parentActor.isRootActor) {
      Services.console.logStringMessage(null); // for the Error Console
      Services.console.reset();
    }
    return {};
  },

  /**
   * The "getPreferences" request handler.
   *
   * @param object aRequest
   *        The request message - which preferences need to be retrieved.
   * @return object
   *         The response message - a { key: value } object map.
   */
  onGetPreferences: function WCA_onGetPreferences(aRequest)
  {
    let prefs = Object.create(null);
    for (let key of aRequest.preferences) {
      prefs[key] = !!this._prefs[key];
    }
    return { preferences: prefs };
  },

  /**
   * The "setPreferences" request handler.
   *
   * @param object aRequest
   *        The request message - which preferences need to be updated.
   */
  onSetPreferences: function WCA_onSetPreferences(aRequest)
  {
    for (let key in aRequest.preferences) {
      this._prefs[key] = aRequest.preferences[key];

      if (key == "NetworkMonitor.saveRequestAndResponseBodies" &&
          this.networkMonitor) {
        this.networkMonitor.saveRequestAndResponseBodies = this._prefs[key];
      }
    }
    return { updated: Object.keys(aRequest.preferences) };
  },

  //////////////////
  // End of request handlers.
  //////////////////

  /**
   * Create an object with the API we expose to the Web Console during
   * JavaScript evaluation.
   * This object inherits properties and methods from the Web Console actor.
   *
   * @private
   * @param object aDebuggerGlobal
   *        A Debugger.Object that wraps a content global. This is used for the
   *        Web Console Commands.
   * @return object
   *         The same object as |this|, but with an added |sandbox| property.
   *         The sandbox holds methods and properties that can be used as
   *         bindings during JS evaluation.
   */
  _getWebConsoleCommands: function(aDebuggerGlobal)
  {
    let helpers = {
      window: this.evalWindow,
      chromeWindow: this.chromeWindow.bind(this),
      makeDebuggeeValue: aDebuggerGlobal.makeDebuggeeValue.bind(aDebuggerGlobal),
      createValueGrip: this.createValueGrip.bind(this),
      sandbox: Object.create(null),
      helperResult: null,
      consoleActor: this,
    };
    addWebConsoleCommands(helpers);

    let evalWindow = this.evalWindow;
    function maybeExport(obj, name) {
      if (typeof obj[name] != "function") {
        return;
      }

      // By default, chrome-implemented functions that are exposed to content
      // refuse to accept arguments that are cross-origin for the caller. This
      // is generally the safe thing, but causes problems for certain console
      // helpers like cd(), where we users sometimes want to pass a cross-origin
      // window. To circumvent this restriction, we use exportFunction along
      // with a special option designed for this purpose. See bug 1051224.
      // obj[name] =
      //   Cu.exportFunction(obj[name], evalWindow, { allowCrossOriginArguments: true });
    }
    for (let name in helpers.sandbox) {
      let desc = Object.getOwnPropertyDescriptor(helpers.sandbox, name);
      maybeExport(desc, 'get');
      maybeExport(desc, 'set');
      maybeExport(desc, 'value');
      if (desc.value) {
        // Make sure the helpers can be used during eval.
        desc.value = aDebuggerGlobal.makeDebuggeeValue(desc.value);
      }
      Object.defineProperty(helpers.sandbox, name, desc);
    }
    return helpers;
  },

  /**
   * Evaluates a string using the debugger API.
   *
   * To allow the variables view to update properties from the Web Console we
   * provide the "bindObjectActor" mechanism: the Web Console tells the
   * ObjectActor ID for which it desires to evaluate an expression. The
   * Debugger.Object pointed at by the actor ID is bound such that it is
   * available during expression evaluation (executeInGlobalWithBindings()).
   *
   * Example:
   *   _self['foobar'] = 'test'
   * where |_self| refers to the desired object.
   *
   * The |frameActor| property allows the Web Console client to provide the
   * frame actor ID, such that the expression can be evaluated in the
   * user-selected stack frame.
   *
   * For the above to work we need the debugger and the Web Console to share
   * a connection, otherwise the Web Console actor will not find the frame
   * actor.
   *
   * The Debugger.Frame comes from the jsdebugger's Debugger instance, which
   * is different from the Web Console's Debugger instance. This means that
   * for evaluation to work, we need to create a new instance for the Web
   * Console Commands helpers - they need to be Debugger.Objects coming from the
   * jsdebugger's Debugger instance.
   *
   * When |bindObjectActor| is used objects can come from different iframes,
   * from different domains. To avoid permission-related errors when objects
   * come from a different window, we also determine the object's own global,
   * such that evaluation happens in the context of that global. This means that
   * evaluation will happen in the object's iframe, rather than the top level
   * window.
   *
   * @param string aString
   *        String to evaluate.
   * @param object [aOptions]
   *        Options for evaluation:
   *        - bindObjectActor: the ObjectActor ID to use for evaluation.
   *          |evalWithBindings()| will be called with one additional binding:
   *          |_self| which will point to the Debugger.Object of the given
   *          ObjectActor.
   *        - frameActor: the FrameActor ID to use for evaluation. The given
   *        debugger frame is used for evaluation, instead of the global window.
   *        - selectedNodeActor: the NodeActor ID of the currently selected node
   *        in the Inspector (or null, if there is no selection). This is used
   *        for helper functions that make reference to the currently selected
   *        node, like $0.
   * @return object
   *         An object that holds the following properties:
   *         - dbg: the debugger where the string was evaluated.
   *         - frame: (optional) the frame where the string was evaluated.
   *         - window: the Debugger.Object for the global where the string was
   *         evaluated.
   *         - result: the result of the evaluation.
   *         - helperResult: any result coming from a Web Console commands
   *         function.
   *         - url: the url to evaluate the script as. Defaults to
   *         "debugger eval code".
   */
  evalWithDebugger: function WCA_evalWithDebugger(aString, aOptions = {})
  {
    let trimmedString = aString.trim();
    // The help function needs to be easy to guess, so we make the () optional.
    if (trimmedString == "help" || trimmedString == "?") {
      aString = "help()";
    }

    // Add easter egg for console.mihai().
    if (trimmedString == "console.mihai()" || trimmedString == "console.mihai();") {
      aString = "\"http://incompleteness.me/blog/2015/02/09/console-dot-mihai/\"";
    }

    // Find the Debugger.Frame of the given FrameActor.
    let frame = null, frameActor = null;
    if (aOptions.frameActor) {
      frameActor = this.conn.getActor(aOptions.frameActor);
      if (frameActor) {
        frame = frameActor.frame;
      }
      else {
        Cu.reportError("Web Console Actor: the frame actor was not found: " +
                       aOptions.frameActor);
      }
    }

    // If we've been given a frame actor in whose scope we should evaluate the
    // expression, be sure to use that frame's Debugger (that is, the JavaScript
    // debugger's Debugger) for the whole operation, not the console's Debugger.
    // (One Debugger will treat a different Debugger's Debugger.Object instances
    // as ordinary objects, not as references to be followed, so mixing
    // debuggers causes strange behaviors.)
    let dbg = frame ? frameActor.threadActor.dbg : this.dbg;
    let dbgWindow = dbg.makeGlobalObjectReference(this.evalWindow);

    // If we have an object to bind to |_self|, create a Debugger.Object
    // referring to that object, belonging to dbg.
    let bindSelf = null;
    if (aOptions.bindObjectActor) {
      let objActor = this.getActorByID(aOptions.bindObjectActor);
      if (objActor) {
        let jsObj = objActor.obj.unsafeDereference();
        // If we use the makeDebuggeeValue method of jsObj's own global, then
        // we'll get a D.O that sees jsObj as viewed from its own compartment -
        // that is, without wrappers. The evalWithBindings call will then wrap
        // jsObj appropriately for the evaluation compartment.
        let global = Cu.getGlobalForObject(jsObj);
        dbgWindow = dbg.makeGlobalObjectReference(global);
        bindSelf = dbgWindow.makeDebuggeeValue(jsObj);
      }
    }

    // Get the Web Console commands for the given debugger window.
    let helpers = this._getWebConsoleCommands(dbgWindow);
    let bindings = helpers.sandbox;
    if (bindSelf) {
      bindings._self = bindSelf;
    }

    if (aOptions.selectedNodeActor) {
      let actor = this.conn.getActor(aOptions.selectedNodeActor);
      if (actor) {
        helpers.selectedNode = actor.rawNode;
      }
    }

    // Check if the Debugger.Frame or Debugger.Object for the global include
    // $ or $$. We will not overwrite these functions with the Web Console
    // commands.
    let found$ = false, found$$ = false;
    if (frame) {
      let env = frame.environment;
      if (env) {
        found$ = !!env.find("$");
        found$$ = !!env.find("$$");
      }
    }
    else {
      found$ = !!dbgWindow.getOwnPropertyDescriptor("$");
      found$$ = !!dbgWindow.getOwnPropertyDescriptor("$$");
    }

    let $ = null, $$ = null;
    if (found$) {
      $ = bindings.$;
      delete bindings.$;
    }
    if (found$$) {
      $$ = bindings.$$;
      delete bindings.$$;
    }

    // Ready to evaluate the string.
    helpers.evalInput = aString;

    let evalOptions;
    if (typeof aOptions.url == "string") {
      evalOptions = { url: aOptions.url };
    }

    let result;
    if (frame) {
      result = frame.evalWithBindings(aString, bindings, evalOptions);
    }
    else {
      result = dbgWindow.executeInGlobalWithBindings(aString, bindings, evalOptions);
    }

    let helperResult = helpers.helperResult;
    delete helpers.evalInput;
    delete helpers.helperResult;
    delete helpers.selectedNode;

    if ($) {
      bindings.$ = $;
    }
    if ($$) {
      bindings.$$ = $$;
    }

    if (bindings._self) {
      delete bindings._self;
    }

    return {
      result: result,
      helperResult: helperResult,
      dbg: dbg,
      frame: frame,
      window: dbgWindow,
    };
  },

  //////////////////
  // Event handlers for various listeners.
  //////////////////

  /**
   * Handler for messages received from the ConsoleServiceListener. This method
   * sends the nsIConsoleMessage to the remote Web Console client.
   *
   * @param nsIConsoleMessage aMessage
   *        The message we need to send to the client.
   */
  onConsoleServiceMessage: function WCA_onConsoleServiceMessage(aMessage)
  {
    let packet;
    if (aMessage instanceof Ci.nsIScriptError) {
      packet = {
        from: this.actorID,
        type: "pageError",
        pageError: this.preparePageErrorForRemote(aMessage),
      };
    }
    else {
      packet = {
        from: this.actorID,
        type: "logMessage",
        message: this._createStringGrip(aMessage.message),
        timeStamp: aMessage.timeStamp,
      };
    }
    this.conn.send(packet);
  },

  /**
   * Prepare an nsIScriptError to be sent to the client.
   *
   * @param nsIScriptError aPageError
   *        The page error we need to send to the client.
   * @return object
   *         The object you can send to the remote client.
   */
  preparePageErrorForRemote: function WCA_preparePageErrorForRemote(aPageError)
  {
    let stack = null;
    // Convert stack objects to the JSON attributes expected by client code
    if (aPageError.stack) {
      stack = [];
      let s = aPageError.stack;
      while (s !== null) {
        stack.push({
          filename: s.source,
          lineNumber: s.line,
          columnNumber: s.column,
          functionName: s.functionDisplayName
        });
        s = s.parent;
      }
    }
    let lineText = aPageError.sourceLine;
    if (lineText && lineText.length > DebuggerServer.LONG_STRING_INITIAL_LENGTH) {
      lineText = lineText.substr(0, DebuggerServer.LONG_STRING_INITIAL_LENGTH);
    }

    return {
      errorMessage: this._createStringGrip(aPageError.errorMessage),
      sourceName: aPageError.sourceName,
      lineText: lineText,
      lineNumber: aPageError.lineNumber,
      columnNumber: aPageError.columnNumber,
      category: aPageError.category,
      timeStamp: aPageError.timeStamp,
      warning: !!(aPageError.flags & aPageError.warningFlag),
      error: !!(aPageError.flags & aPageError.errorFlag),
      exception: !!(aPageError.flags & aPageError.exceptionFlag),
      strict: !!(aPageError.flags & aPageError.strictFlag),
      info: !!(aPageError.flags & aPageError.infoFlag),
      private: aPageError.isFromPrivateWindow,
      stacktrace: stack
    };
  },

  /**
   * Handler for window.console API calls received from the ConsoleAPIListener.
   * This method sends the object to the remote Web Console client.
   *
   * @see ConsoleAPIListener
   * @param object aMessage
   *        The console API call we need to send to the remote client.
   */
  onConsoleAPICall: function WCA_onConsoleAPICall(aMessage)
  {
    let packet = {
      from: this.actorID,
      type: "consoleAPICall",
      message: this.prepareConsoleMessageForRemote(aMessage),
    };
    this.conn.send(packet);
  },

  /**
   * Handler for network events. This method is invoked when a new network event
   * is about to be recorded.
   *
   * @see NetworkEventActor
   * @see NetworkMonitor from webconsole/utils.js
   *
   * @param object aEvent
   *        The initial network request event information.
   * @param nsIHttpChannel aChannel
   *        The network request nsIHttpChannel object.
   * @return object
   *         A new NetworkEventActor is returned. This is used for tracking the
   *         network request and response.
   */
  onNetworkEvent: function WCA_onNetworkEvent(aEvent, aChannel)
  {
    let actor = this.getNetworkEventActor(aChannel);
    actor.init(aEvent);

    let packet = {
      from: this.actorID,
      type: "networkEvent",
      eventActor: actor.grip()
    };

    this.conn.send(packet);

    return actor;
  },

  /**
   * Get the NetworkEventActor for a nsIChannel, if it exists,
   * otherwise create a new one.
   *
   * @param nsIHttpChannel aChannel
   *        The channel for the network event.
   * @return object
   *         The NetworkEventActor for the given channel.
   */
  getNetworkEventActor: function WCA_getNetworkEventActor(aChannel) {
    let actor = this._netEvents.get(aChannel);
    if (actor) {
      // delete from map as we should only need to do this check once
      this._netEvents.delete(aChannel);
      actor.channel = null;
      return actor;
    }

    actor = new NetworkEventActor(aChannel, this);
    this._actorPool.addActor(actor);
    return actor;
  },

  /**
   * Send a new HTTP request from the target's window.
   *
   * @param object aMessage
   *        Object with 'request' - the HTTP request details.
   */
  onSendHTTPRequest: function WCA_onSendHTTPRequest(aMessage)
  {
    let details = aMessage.request;

    // send request from target's window
    let request = new this.window.XMLHttpRequest();
    request.open(details.method, details.url, true);

    for (let {name, value} of details.headers) {
      request.setRequestHeader(name, value);
    }
    request.send(details.body);

    let actor = this.getNetworkEventActor(request.channel);

    // map channel to actor so we can associate future events with it
    this._netEvents.set(request.channel, actor);

    return {
      from: this.actorID,
      eventActor: actor.grip()
    };
  },

  /**
   * Handler for file activity. This method sends the file request information
   * to the remote Web Console client.
   *
   * @see ConsoleProgressListener
   * @param string aFileURI
   *        The requested file URI.
   */
  onFileActivity: function WCA_onFileActivity(aFileURI)
  {
    let packet = {
      from: this.actorID,
      type: "fileActivity",
      uri: aFileURI,
    };
    this.conn.send(packet);
  },

  /**
   * Handler for reflow activity. This method forwards reflow events to the
   * remote Web Console client.
   *
   * @see ConsoleReflowListener
   * @param Object aReflowInfo
   */
  onReflowActivity: function WCA_onReflowActivity(aReflowInfo)
  {
    let packet = {
      from: this.actorID,
      type: "reflowActivity",
      interruptible: aReflowInfo.interruptible,
      start: aReflowInfo.start,
      end: aReflowInfo.end,
      sourceURL: aReflowInfo.sourceURL,
      sourceLine: aReflowInfo.sourceLine,
      functionName: aReflowInfo.functionName
    };

    this.conn.send(packet);
  },

  /**
   * Handler for server logging. This method forwards log events to the
   * remote Web Console client.
   *
   * @see ServerLoggingListener
   * @param object aMessage
   *        The console API call on the server we need to send to the remote client.
   */
  onServerLogCall: function WCA_onServerLogCall(aMessage)
  {
    // Clone all data into the content scope (that's where
    // passed arguments comes from).
    let msg = Cu.cloneInto(aMessage, this.window);

    // All arguments within the message need to be converted into
    // debuggees to properly send it to the client side.
    // Use the default target: this.window as the global object
    // since that's the correct scope for data in the message.
    // The 'false' argument passed into prepareConsoleMessageForRemote()
    // ensures that makeDebuggeeValue uses content debuggee.
    // See also:
    // * makeDebuggeeValue()
    // * prepareConsoleMessageForRemote()
    msg = this.prepareConsoleMessageForRemote(msg, false);

    let packet = {
      from: this.actorID,
      type: "serverLogCall",
      message: msg,
    };

    this.conn.send(packet);
  },

  //////////////////
  // End of event handlers for various listeners.
  //////////////////

  /**
   * Prepare a message from the console API to be sent to the remote Web Console
   * instance.
   *
   * @param object aMessage
   *        The original message received from console-api-log-event.
   * @param boolean aUseObjectGlobal
   *        If |true| the object global is determined and added as a debuggee,
   *        otherwise |this.window| is used when makeDebuggeeValue() is invoked.
   * @return object
   *         The object that can be sent to the remote client.
   */
  prepareConsoleMessageForRemote:
  function WCA_prepareConsoleMessageForRemote(aMessage, aUseObjectGlobal = true)
  {
    let result = WebConsoleUtils.cloneObject(aMessage);

    result.workerType = CONSOLE_WORKER_IDS.indexOf(result.innerID) == -1
                          ? 'none' : result.innerID;

    delete result.wrappedJSObject;
    delete result.ID;
    delete result.innerID;
    delete result.consoleID;

    result.arguments = Array.map(aMessage.arguments || [], (aObj) => {
      let dbgObj = this.makeDebuggeeValue(aObj, aUseObjectGlobal);
      return this.createValueGrip(dbgObj);
    });

    result.styles = Array.map(aMessage.styles || [], (aString) => {
      return this.createValueGrip(aString);
    });

    result.category = aMessage.category || "webdev";

    return result;
  },

  /**
   * Find the XUL window that owns the content window.
   *
   * @return Window
   *         The XUL window that owns the content window.
   */
  chromeWindow: function WCA_chromeWindow()
  {
    let window = null;
    try {
      window = this.window.QueryInterface(Ci.nsIInterfaceRequestor)
             .getInterface(Ci.nsIWebNavigation).QueryInterface(Ci.nsIDocShell)
             .chromeEventHandler.ownerDocument.defaultView;
    }
    catch (ex) {
      // The above can fail because chromeEventHandler is not available for all
      // kinds of |this.window|.
    }

    return window;
  },

  /**
   * Notification observer for the "last-pb-context-exited" topic.
   *
   * @private
   * @param object aSubject
   *        Notification subject - in this case it is the inner window ID that
   *        was destroyed.
   * @param string aTopic
   *        Notification topic.
   */
  _onObserverNotification: function WCA__onObserverNotification(aSubject, aTopic)
  {
    switch (aTopic) {
      case "last-pb-context-exited":
        this.conn.send({
          from: this.actorID,
          type: "lastPrivateContextExited",
        });
        break;
    }
  },

  /**
   * The "will-navigate" progress listener. This is used to clear the current
   * eval scope.
   */
  _onWillNavigate: function WCA__onWillNavigate({ window, isTopLevel })
  {
    if (isTopLevel) {
      this._evalWindow = null;
      events.off(this.parentActor, "will-navigate", this._onWillNavigate);
      this._progressListenerActive = false;
    }
  },

  /**
   * This listener is called when we switch to another frame,
   * mostly to unregister previous listeners and start listening on the new document.
   */
  _onChangedToplevelDocument: function WCA__onChangedToplevelDocument()
  {
    // Convert the Set to an Array
    let listeners = [...this._listeners];

    // Unregister existing listener on the previous document
    // (pass a copy of the array as it will shift from it)
    this.onStopListeners({listeners: listeners.slice()});

    // This method is called after this.window is changed,
    // so we register new listener on this new window
    this.onStartListeners({listeners: listeners});

    // Also reset the cached top level chrome window being targeted
    this._lastChromeWindow  = null;
  },
};

WebConsoleActor.prototype.requestTypes =
{
  startListeners: WebConsoleActor.prototype.onStartListeners,
  stopListeners: WebConsoleActor.prototype.onStopListeners,
  getCachedMessages: WebConsoleActor.prototype.onGetCachedMessages,
  evaluateJS: WebConsoleActor.prototype.onEvaluateJS,
  evaluateJSAsync: WebConsoleActor.prototype.onEvaluateJSAsync,
  autocomplete: WebConsoleActor.prototype.onAutocomplete,
  clearMessagesCache: WebConsoleActor.prototype.onClearMessagesCache,
  getPreferences: WebConsoleActor.prototype.onGetPreferences,
  setPreferences: WebConsoleActor.prototype.onSetPreferences,
  sendHTTPRequest: WebConsoleActor.prototype.onSendHTTPRequest
};

exports.WebConsoleActor = WebConsoleActor;

/**
 * Creates an actor for a network event.
 *
 * @constructor
 * @param object aChannel
 *        The nsIChannel associated with this event.
 * @param object aWebConsoleActor
 *        The parent WebConsoleActor instance for this object.
 */
function NetworkEventActor(aChannel, aWebConsoleActor)
{
  this.parent = aWebConsoleActor;
  this.conn = this.parent.conn;
  this.channel = aChannel;

  this._request = {
    method: null,
    url: null,
    httpVersion: null,
    headers: [],
    cookies: [],
    headersSize: null,
    postData: {},
  };

  this._response = {
    headers: [],
    cookies: [],
    content: {},
  };

  this._timings = {};

  // Keep track of LongStringActors owned by this NetworkEventActor.
  this._longStringActors = new Set();
}

NetworkEventActor.prototype =
{
  _request: null,
  _response: null,
  _timings: null,
  _longStringActors: null,

  actorPrefix: "netEvent",

  /**
   * Returns a grip for this actor for returning in a protocol message.
   */
  grip: function NEA_grip()
  {
    return {
      actor: this.actorID,
      startedDateTime: this._startedDateTime,
      timeStamp: Date.parse(this._startedDateTime),
      url: this._request.url,
      method: this._request.method,
      isXHR: this._isXHR,
      fromCache: this._fromCache,
      private: this._private,
    };
  },

  /**
   * Releases this actor from the pool.
   */
  release: function NEA_release()
  {
    for (let grip of this._longStringActors) {
      let actor = this.parent.getActorByID(grip.actor);
      if (actor) {
        this.parent.releaseActor(actor);
      }
    }
    this._longStringActors = new Set();

    if (this.channel) {
      this.parent._netEvents.delete(this.channel);
    }
    this.parent.releaseActor(this);
  },

  /**
   * Handle a protocol request to release a grip.
   */
  onRelease: function NEA_onRelease()
  {
    this.release();
    return {};
  },

  /**
   * Set the properties of this actor based on it's corresponding
   * network event.
   *
   * @param object aNetworkEvent
   *        The network event associated with this actor.
   */
  init: function NEA_init(aNetworkEvent)
  {
    this._startedDateTime = aNetworkEvent.startedDateTime;
    this._isXHR = aNetworkEvent.isXHR;
    this._fromCache = aNetworkEvent.fromCache;

    for (let prop of ['method', 'url', 'httpVersion', 'headersSize']) {
      this._request[prop] = aNetworkEvent[prop];
    }

    this._discardRequestBody = aNetworkEvent.discardRequestBody;
    this._discardResponseBody = aNetworkEvent.discardResponseBody;
    this._private = aNetworkEvent.private;
  },

  /**
   * The "getRequestHeaders" packet type handler.
   *
   * @return object
   *         The response packet - network request headers.
   */
  onGetRequestHeaders: function NEA_onGetRequestHeaders()
  {
    return {
      from: this.actorID,
      headers: this._request.headers,
      headersSize: this._request.headersSize,
      rawHeaders: this._request.rawHeaders,
    };
  },

  /**
   * The "getRequestCookies" packet type handler.
   *
   * @return object
   *         The response packet - network request cookies.
   */
  onGetRequestCookies: function NEA_onGetRequestCookies()
  {
    return {
      from: this.actorID,
      cookies: this._request.cookies,
    };
  },

  /**
   * The "getRequestPostData" packet type handler.
   *
   * @return object
   *         The response packet - network POST data.
   */
  onGetRequestPostData: function NEA_onGetRequestPostData()
  {
    return {
      from: this.actorID,
      postData: this._request.postData,
      postDataDiscarded: this._discardRequestBody,
    };
  },

  /**
   * The "getSecurityInfo" packet type handler.
   *
   * @return object
   *         The response packet - connection security information.
   */
  onGetSecurityInfo: function NEA_onGetSecurityInfo()
  {
    return {
      from: this.actorID,
      securityInfo: this._securityInfo,
    };
  },

  /**
   * The "getResponseHeaders" packet type handler.
   *
   * @return object
   *         The response packet - network response headers.
   */
  onGetResponseHeaders: function NEA_onGetResponseHeaders()
  {
    return {
      from: this.actorID,
      headers: this._response.headers,
      headersSize: this._response.headersSize,
      rawHeaders: this._response.rawHeaders,
    };
  },

  /**
   * The "getResponseCookies" packet type handler.
   *
   * @return object
   *         The response packet - network response cookies.
   */
  onGetResponseCookies: function NEA_onGetResponseCookies()
  {
    return {
      from: this.actorID,
      cookies: this._response.cookies,
    };
  },

  /**
   * The "getResponseContent" packet type handler.
   *
   * @return object
   *         The response packet - network response content.
   */
  onGetResponseContent: function NEA_onGetResponseContent()
  {
    return {
      from: this.actorID,
      content: this._response.content,
      contentDiscarded: this._discardResponseBody,
    };
  },

  /**
   * The "getEventTimings" packet type handler.
   *
   * @return object
   *         The response packet - network event timings.
   */
  onGetEventTimings: function NEA_onGetEventTimings()
  {
    return {
      from: this.actorID,
      timings: this._timings,
      totalTime: this._totalTime
    };
  },

  /******************************************************************
   * Listeners for new network event data coming from NetworkMonitor.
   ******************************************************************/

  /**
   * Add network request headers.
   *
   * @param array aHeaders
   *        The request headers array.
   * @param string aRawHeaders
   *        The raw headers source.
   */
  addRequestHeaders: function NEA_addRequestHeaders(aHeaders, aRawHeaders)
  {
    this._request.headers = aHeaders;
    this._prepareHeaders(aHeaders);

    var rawHeaders = this.parent._createStringGrip(aRawHeaders);
    if (typeof rawHeaders == "object") {
      this._longStringActors.add(rawHeaders);
    }
    this._request.rawHeaders = rawHeaders;

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "requestHeaders",
      headers: aHeaders.length,
      headersSize: this._request.headersSize,
    };

    this.conn.send(packet);
  },

  /**
   * Add network request cookies.
   *
   * @param array aCookies
   *        The request cookies array.
   */
  addRequestCookies: function NEA_addRequestCookies(aCookies)
  {
    this._request.cookies = aCookies;
    this._prepareHeaders(aCookies);

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "requestCookies",
      cookies: aCookies.length,
    };

    this.conn.send(packet);
  },

  /**
   * Add network request POST data.
   *
   * @param object aPostData
   *        The request POST data.
   */
  addRequestPostData: function NEA_addRequestPostData(aPostData)
  {
    this._request.postData = aPostData;
    aPostData.text = this.parent._createStringGrip(aPostData.text);
    if (typeof aPostData.text == "object") {
      this._longStringActors.add(aPostData.text);
    }

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "requestPostData",
      dataSize: aPostData.text.length,
      discardRequestBody: this._discardRequestBody,
    };

    this.conn.send(packet);
  },

  /**
   * Add the initial network response information.
   *
   * @param object aInfo
   *        The response information.
   * @param string aRawHeaders
   *        The raw headers source.
   */
  addResponseStart: function NEA_addResponseStart(aInfo, aRawHeaders)
  {
    var rawHeaders = this.parent._createStringGrip(aRawHeaders);
    if (typeof rawHeaders == "object") {
      this._longStringActors.add(rawHeaders);
    }
    this._response.rawHeaders = rawHeaders;

    this._response.httpVersion = aInfo.httpVersion;
    this._response.status = aInfo.status;
    this._response.statusText = aInfo.statusText;
    this._response.headersSize = aInfo.headersSize;
    this._discardResponseBody = aInfo.discardResponseBody;

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "responseStart",
      response: aInfo
    };

    this.conn.send(packet);
  },

  /**
   * Add connection security information.
   *
   * @param object info
   *        The object containing security information.
   */
  addSecurityInfo: function NEA_addSecurityInfo(info)
  {
    this._securityInfo = info;

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "securityInfo",
      state: info.state,
    };

    this.conn.send(packet);
  },

  /**
   * Add network response headers.
   *
   * @param array aHeaders
   *        The response headers array.
   */
  addResponseHeaders: function NEA_addResponseHeaders(aHeaders)
  {
    this._response.headers = aHeaders;
    this._prepareHeaders(aHeaders);

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "responseHeaders",
      headers: aHeaders.length,
      headersSize: this._response.headersSize,
    };

    this.conn.send(packet);
  },

  /**
   * Add network response cookies.
   *
   * @param array aCookies
   *        The response cookies array.
   */
  addResponseCookies: function NEA_addResponseCookies(aCookies)
  {
    this._response.cookies = aCookies;
    this._prepareHeaders(aCookies);

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "responseCookies",
      cookies: aCookies.length,
    };

    this.conn.send(packet);
  },

  /**
   * Add network response content.
   *
   * @param object aContent
   *        The response content.
   * @param boolean aDiscardedResponseBody
   *        Tells if the response content was recorded or not.
   */
  addResponseContent:
  function NEA_addResponseContent(aContent, aDiscardedResponseBody)
  {
    this._response.content = aContent;
    aContent.text = this.parent._createStringGrip(aContent.text);
    if (typeof aContent.text == "object") {
      this._longStringActors.add(aContent.text);
    }

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "responseContent",
      mimeType: aContent.mimeType,
      contentSize: aContent.text.length,
      transferredSize: aContent.transferredSize,
      discardResponseBody: aDiscardedResponseBody,
    };

    this.conn.send(packet);
  },

  /**
   * Add network event timing information.
   *
   * @param number aTotal
   *        The total time of the network event.
   * @param object aTimings
   *        Timing details about the network event.
   */
  addEventTimings: function NEA_addEventTimings(aTotal, aTimings)
  {
    this._totalTime = aTotal;
    this._timings = aTimings;

    let packet = {
      from: this.actorID,
      type: "networkEventUpdate",
      updateType: "eventTimings",
      totalTime: aTotal
    };

    this.conn.send(packet);
  },

  /**
   * Prepare the headers array to be sent to the client by using the
   * LongStringActor for the header values, when needed.
   *
   * @private
   * @param array aHeaders
   */
  _prepareHeaders: function NEA__prepareHeaders(aHeaders)
  {
    for (let header of aHeaders) {
      header.value = this.parent._createStringGrip(header.value);
      if (typeof header.value == "object") {
        this._longStringActors.add(header.value);
      }
    }
  },
};

NetworkEventActor.prototype.requestTypes =
{
  "release": NetworkEventActor.prototype.onRelease,
  "getRequestHeaders": NetworkEventActor.prototype.onGetRequestHeaders,
  "getRequestCookies": NetworkEventActor.prototype.onGetRequestCookies,
  "getRequestPostData": NetworkEventActor.prototype.onGetRequestPostData,
  "getResponseHeaders": NetworkEventActor.prototype.onGetResponseHeaders,
  "getResponseCookies": NetworkEventActor.prototype.onGetResponseCookies,
  "getResponseContent": NetworkEventActor.prototype.onGetResponseContent,
  "getEventTimings": NetworkEventActor.prototype.onGetEventTimings,
  "getSecurityInfo": NetworkEventActor.prototype.onGetSecurityInfo,
};
