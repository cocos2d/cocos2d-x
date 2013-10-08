/* -*- Mode: javascript; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; js-indent-level: 2; -*- */
/* vim: set ft=javascript ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

/**
 * JSD2 actors.
 */
/**
 * Creates a ThreadActor.
 *
 * ThreadActors manage a JSInspector object and manage execution/inspection
 * of debuggees.
 *
 * @param aHooks object
 *        An object with preNest and postNest methods for calling when entering
 *        and exiting a nested event loop, addToParentPool and
 *        removeFromParentPool methods for handling the lifetime of actors that
 *        will outlive the thread, like breakpoints.
 * @param aGlobal object [optional]
 *        An optional (for content debugging only) reference to the content
 *        window.
 */
function ThreadActor(aHooks, aGlobal)
{
  this._state = "detached";
  this._frameActors = [];
  this._environmentActors = [];
  this._hooks = aHooks;
  this.global = aGlobal;

  this.findGlobals = this.globalManager.findGlobals.bind(this);
  this.onNewGlobal = this.globalManager.onNewGlobal.bind(this);
  this.onNewSource = this.onNewSource.bind(this);

  this._options = {
    useSourceMaps: false
  };
}

/**
 * The breakpoint store must be shared across instances of ThreadActor so that
 * page reloads don't blow away all of our breakpoints.
 */
ThreadActor._breakpointStore = {};

ThreadActor.prototype = {
  actorPrefix: "context",

  get state() { return this._state; },
  get attached() this.state == "attached" ||
                 this.state == "running" ||
                 this.state == "paused",

  get _breakpointStore() { return ThreadActor._breakpointStore; },

  get threadLifetimePool() {
    if (!this._threadLifetimePool) {
      this._threadLifetimePool = new ActorPool(this.conn);
      this.conn.addActorPool(this._threadLifetimePool);
      this._threadLifetimePool.objectActors = new WeakMap();
    }
    return this._threadLifetimePool;
  },

  get sources() {
    if (!this._sources) {
      this._sources = new ThreadSources(this, this._options.useSourceMaps,
                                        this._allowSource, this.onNewSource);
    }
    return this._sources;
  },

  clearDebuggees: function TA_clearDebuggees() {
    if (this.dbg) {
      this.dbg.removeAllDebuggees();
    }
    this.conn.removeActorPool(this._threadLifetimePool || undefined);
    this._threadLifetimePool = null;
    this._sources = null;
  },

  /**
   * Add a debuggee global to the Debugger object.
   */
  addDebuggee: function TA_addDebuggee(aGlobal) {
    try {
      this.dbg.addDebuggee(aGlobal);
    } catch (e) {
      // Ignore attempts to add the debugger's compartment as a debuggee.
      dumpn("Ignoring request to add the debugger's compartment as a debuggee");
    }
  },

  /**
   * Initialize the Debugger.
   */
  _initDebugger: function TA__initDebugger() {
    this.dbg = new Debugger();
    this.dbg.uncaughtExceptionHook = this.uncaughtExceptionHook.bind(this);
    this.dbg.onDebuggerStatement = this.onDebuggerStatement.bind(this);
    this.dbg.onNewScript = this.onNewScript.bind(this);
    this.dbg.onNewGlobalObject = this.globalManager.onNewGlobal.bind(this);
    // Keep the debugger disabled until a client attaches.
    this.dbg.enabled = this._state != "detached";
  },

  /**
   * Remove a debuggee global from the JSInspector.
   */
  removeDebugee: function TA_removeDebuggee(aGlobal) {
    try {
      this.dbg.removeDebuggee(aGlobal);
    } catch(ex) {
      // XXX: This debuggee has code currently executing on the stack,
      // we need to save this for later.
    }
  },

  /**
   * Add the provided window and all windows in its frame tree as debuggees.
   */
  _addDebuggees: function TA__addDebuggees(aWindow) {
    this.addDebuggee(aWindow);
    let frames = aWindow.frames;
    if (frames) {
      for (let i = 0; i < frames.length; i++) {
        this._addDebuggees(frames[i]);
      }
    }
  },

  /**
   * An object that will be used by ThreadActors to tailor their behavior
   * depending on the debugging context being required (chrome or content).
   */
  globalManager: {
    findGlobals: function TA_findGlobals() {
      this._addDebuggees(this.global);
    },

    /**
     * A function that the engine calls when a new global object has been
     * created.
     *
     * @param aGlobal Debugger.Object
     *        The new global object that was created.
     */
    onNewGlobal: function TA_onNewGlobal(aGlobal) {
      // Content debugging only cares about new globals in the contant window,
      // like iframe children.
      if (aGlobal.hostAnnotations &&
          aGlobal.hostAnnotations.type == "document" &&
          aGlobal.hostAnnotations.element === this.global) {
        this.addDebuggee(aGlobal);
        // Notify the client.
        this.conn.send({
          from: this.actorID,
          type: "newGlobal",
          // TODO: after bug 801084 lands see if we need to JSONify this.
          hostAnnotations: aGlobal.hostAnnotations
        });
      }
    }
  },

  disconnect: function TA_disconnect() {
    dumpn("in ThreadActor.prototype.disconnect");
    if (this._state == "paused") {
      this.onResume();
    }

    this._state = "exited";

    this.clearDebuggees();

    if (!this.dbg) {
      return;
    }
    this.dbg.enabled = false;
    this.dbg = null;
  },

  /**
   * Disconnect the debugger and put the actor in the exited state.
   */
  exit: function TA_exit() {
    this.disconnect();
  },

  // Request handlers
  onAttach: function TA_onAttach(aRequest) {
    if (this.state === "exited") {
      return { type: "exited" };
    }

    if (this.state !== "detached") {
      return { error: "wrongState" };
    }

    this._state = "attached";

    update(this._options, aRequest.options || {});

    if (!this.dbg) {
      this._initDebugger();
    }
    this.findGlobals();
    this.dbg.enabled = true;
    try {
      // Put ourselves in the paused state.
      let packet = this._paused();
      if (!packet) {
        return { error: "notAttached" };
      }
      packet.why = { type: "attached" };

      this._restoreBreakpoints();

      // Send the response to the attach request now (rather than
      // returning it), because we're going to start a nested event loop
      // here.
      this.conn.send(packet);

      // Start a nested event loop.
      this._nest();

      // We already sent a response to this request, don't send one
      // now.
      return null;
    } catch (e) {
      reportError(e);
      return { error: "notAttached", message: e.toString() };
    }
  },

  onDetach: function TA_onDetach(aRequest) {
    this.disconnect();
    dumpn("ThreadActor.prototype.onDetach: returning 'detached' packet");
    return {
      type: "detached"
    };
  },

  onReconfigure: function TA_onReconfigure(aRequest) {
    if (this.state == "exited") {
      return { error: "wrongState" };
    }

    update(this._options, aRequest.options || {});
    // Clear existing sources, so they can be recreated on next access.
    this._sources = null;

    return {};
  },

  /**
   * Pause the debuggee, by entering a nested event loop, and return a 'paused'
   * packet to the client.
   *
   * @param Debugger.Frame aFrame
   *        The newest debuggee frame in the stack.
   * @param object aReason
   *        An object with a 'type' property containing the reason for the pause.
   * @param function onPacket
   *        Hook to modify the packet before it is sent. Feel free to return a
   *        promise.
   */
  _pauseAndRespond: function TA__pauseAndRespond(aFrame, aReason,
                                                 onPacket=function (k) k) {
    try {
      let packet = this._paused(aFrame);
      if (!packet) {
        return undefined;
      }
      packet.why = aReason;
      resolve(onPacket(packet)).then(this.conn.send.bind(this.conn));
      _lockVM(aFrame, aFrame.script);
      return this._nest();
    } catch(e) {
      let msg = "Got an exception during TA__pauseAndRespond: " + e +
                ": " + e.stack;
      // Cu.reportError(msg);
      dumpn(msg);
      return undefined;
    }
  },

  /**
   * Handle a protocol request to resume execution of the debuggee.
   */
  onResume: function TA_onResume(aRequest) {
    if (this._state !== "paused") {
      return {
        error: "wrongState",
        message: "Can't resume when debuggee isn't paused. Current state is '"
          + this._state + "'"
      };
    }

    // In case of multiple nested event loops (due to multiple debuggers open in
    // different tabs or multiple debugger clients connected to the same tab)
    // only allow resumption in a LIFO order.
    // if (DebuggerServer.xpcInspector.eventLoopNestLevel > 1) {
    //   let lastNestRequestor = DebuggerServer.xpcInspector.lastNestRequestor;
    //   if (lastNestRequestor.connection != this.conn) {
    //     return { error: "wrongOrder",
    //              message: "trying to resume in the wrong order.",
    //              lastPausedUrl: lastNestRequestor.url };
    //   }
    // }

    _unlockVM();

    if (aRequest && aRequest.forceCompletion) {
      // TODO: remove this when Debugger.Frame.prototype.pop is implemented in
      // bug 736733.
      if (typeof this.frame.pop != "function") {
        return { error: "notImplemented",
                 message: "forced completion is not yet implemented." };
      }

      this.dbg.getNewestFrame().pop(aRequest.completionValue);
      let packet = this._resumed();
      // DebuggerServer.xpcInspector.exitNestedEventLoop();
      _unlockVM();
      return { type: "resumeLimit", frameFinished: aRequest.forceCompletion };
    }

    if (aRequest && aRequest.resumeLimit) {
      log("resumeLimit...");
      // Bind these methods because some of the hooks are called with 'this'
      // set to the current frame.
      let pauseAndRespond = (aFrame, onPacket=function (k) k) => {
        this._pauseAndRespond(aFrame, { type: "resumeLimit" }, onPacket);
      };
      let createValueGrip = this.createValueGrip.bind(this);

      let startFrame = this.youngestFrame;
      let startLine;
      if (this.youngestFrame.script) {
        let offset = this.youngestFrame.offset;
        startLine = this.youngestFrame.script.getOffsetLine(offset);
      }

      // Define the JS hook functions for stepping.

      let onEnterFrame = aFrame => {
        if (this.sources.isBlackBoxed(aFrame.script.url)) {
          return undefined;
        }
        return pauseAndRespond(aFrame);
      };

      let thread = this;

      let onPop = function TA_onPop(aCompletion) {
        // onPop is called with 'this' set to the current frame.
        if (thread.sources.isBlackBoxed(this.script.url)) {
          return undefined;
        }

        // Note that we're popping this frame; we need to watch for
        // subsequent step events on its caller.
        this.reportedPop = true;

        return pauseAndRespond(this, (aPacket) => {
          aPacket.why.frameFinished = {};
          if (!aCompletion) {
            aPacket.why.frameFinished.terminated = true;
          } else if (aCompletion.hasOwnProperty("return")) {
            aPacket.why.frameFinished.return = createValueGrip(aCompletion.return);
          } else if (aCompletion.hasOwnProperty("yield")) {
            aPacket.why.frameFinished.return = createValueGrip(aCompletion.yield);
          } else {
            aPacket.why.frameFinished.throw = createValueGrip(aCompletion.throw);
          }
          return aPacket;
        });
      };

      let onStep = function TA_onStep() {
        // onStep is called with 'this' set to the current frame.

        if (thread.sources.isBlackBoxed(this.script.url)) {
          return undefined;
        }

        // If we've changed frame or line, then report that.
        if (this !== startFrame ||
            (this.script &&
             this.script.getOffsetLine(this.offset) != startLine)) {
          return pauseAndRespond(this);
        }

        // Otherwise, let execution continue.
        return undefined;
      };

      let steppingType = aRequest.resumeLimit.type;
      if (["step", "next", "finish"].indexOf(steppingType) == -1) {
            return { error: "badParameterType",
                     message: "Unknown resumeLimit type" };
      }
      // Make sure there is still a frame on the stack if we are to continue
      // stepping.
      let stepFrame = this._getNextStepFrame(startFrame);
      if (stepFrame) {
        switch (steppingType) {
          case "step":
            log("--> step...");
            this.dbg.onEnterFrame = onEnterFrame;
            // Fall through.
          case "next":
            log("--> next...");
            stepFrame.onStep = onStep;
            stepFrame.onPop = onPop;
            break;
          case "finish":
            log("--> finish...");
            stepFrame.onPop = onPop;
        }
      }

    }

    if (aRequest && aRequest.pauseOnExceptions) {
      this.dbg.onExceptionUnwind = this.onExceptionUnwind.bind(this);
    }
    let packet = this._resumed();
    _unlockVM();
    // DebuggerServer.xpcInspector.exitNestedEventLoop();
    return packet;
  },

  /**
   * Helper method that returns the next frame when stepping.
   */
  _getNextStepFrame: function TA__getNextStepFrame(aFrame) {
    let stepFrame = aFrame.reportedPop ? aFrame.older : aFrame;
    if (!stepFrame || !stepFrame.script) {
      stepFrame = null;
    }
    return stepFrame;
  },

  onClientEvaluate: function TA_onClientEvaluate(aRequest) {
    if (this.state !== "paused") {
      return { error: "wrongState",
               message: "Debuggee must be paused to evaluate code." };
    };

    let frame = this._requestFrame(aRequest.frame);
    if (!frame) {
      return { error: "unknownFrame",
               message: "Evaluation frame not found" };
    }

    if (!frame.environment) {
      return { error: "notDebuggee",
               message: "cannot access the environment of this frame." };
    };

    // We'll clobber the youngest frame if the eval causes a pause, so
    // save our frame now to be restored after eval returns.
    // XXX: or we could just start using dbg.getNewestFrame() now that it
    // works as expected.
    let youngest = this.youngestFrame;

    // Put ourselves back in the running state and inform the client.
    let resumedPacket = this._resumed();
    this.conn.send(resumedPacket);

    // Run the expression.
    // XXX: test syntax errors
    let completion = frame.eval(aRequest.expression);

    // Put ourselves back in the pause state.
    let packet = this._paused(youngest);
    packet.why = { type: "clientEvaluated",
                   frameFinished: this.createProtocolCompletionValue(completion) };

    // Return back to our previous pause's event loop.
    return packet;
  },

  onFrames: function TA_onFrames(aRequest) {
    if (this.state !== "paused") {
      return { error: "wrongState",
               message: "Stack frames are only available while the debuggee is paused."};
    }

    let start = aRequest.start ? aRequest.start : 0;
    let count = aRequest.count;

    // Find the starting frame...
    let frame = this.youngestFrame;
    let i = 0;
    while (frame && (i < start)) {
      frame = frame.older;
      i++;
    }

    // Return request.count frames, or all remaining
    // frames if count is not defined.
    let frames = [];
    let promises = [];
    for (; frame && (!count || i < (start + count)); i++, frame=frame.older) {
      let form = this._createFrameActor(frame).form();
      form.depth = i;
      frames.push(form);

      let promise = this.sources.getOriginalLocation(form.where.url,
                                                     form.where.line)
        .then(function (aOrigLocation) {
          form.where = aOrigLocation;
        });
      promises.push(promise);
    }

    return all(promises).then(function () {
      return { frames: frames };
    });
  },

  onReleaseMany: function TA_onReleaseMany(aRequest) {
    if (!aRequest.actors) {
      return { error: "missingParameter",
               message: "no actors were specified" };
    }

    let res;
    for each (let actorID in aRequest.actors) {
      let actor = this.threadLifetimePool.get(actorID);
      if (!actor) {
        if (!res) {
          res = { error: "notReleasable",
                  message: "Only thread-lifetime actors can be released." };
        }
        continue;
      }
      actor.onRelease();
    }
    return res ? res : {};
  },

  /**
   * Handle a protocol request to set a breakpoint.
   */
  onSetBreakpoint: function TA_onSetBreakpoint(aRequest) {
    if (this.state !== "paused") {
      return { error: "wrongState",
               message: "Breakpoints can only be set while the debuggee is paused."};
    }

    // XXX: `originalColumn` is never used. See bug 827639.
    let { url: originalSource,
          line: originalLine,
          column: originalColumn } = aRequest.location;

    let locationPromise = this.sources.getGeneratedLocation(originalSource,
                                                            originalLine)
    return locationPromise.then((aLocation) => {
      let line = aLocation.line;
      if (this.dbg.findScripts({ url: aLocation.url }).length == 0 ||
          line < 0 ||
          line == null) {
        return { error: "noScript" };
      }

      // Add the breakpoint to the store for later reuse, in case it belongs to a
      // script that hasn't appeared yet.
      if (!this._breakpointStore[aLocation.url]) {
        this._breakpointStore[aLocation.url] = [];
      }
      let scriptBreakpoints = this._breakpointStore[aLocation.url];
      scriptBreakpoints[line] = {
        url: aLocation.url,
        line: line,
        column: aLocation.column
      };

      let response = this._setBreakpoint(aLocation);
      // If the original location of our generated location is different from
      // the original location we attempted to set the breakpoint on, we will
      // need to know so that we can set actualLocation on the response.
      let originalLocation = this.sources.getOriginalLocation(aLocation.url,
                                                              aLocation.line);

      return all([response, originalLocation])
        .then(([aResponse, {url, line}]) => {
          if (aResponse.actualLocation) {
            let actualOrigLocation = this.sources.getOriginalLocation(
              aResponse.actualLocation.url, aResponse.actualLocation.line);
            return actualOrigLocation.then(function ({ url, line }) {
              if (url !== originalSource || line !== originalLine) {
                aResponse.actualLocation = { url: url, line: line };
              }
              return aResponse;
            });
          }

          if (url !== originalSource || line !== originalLine) {
            aResponse.actualLocation = { url: url, line: line };
          }

          return aResponse;
        });
    });
  },

  /**
   * Set a breakpoint using the jsdbg2 API. If the line on which the breakpoint
   * is being set contains no code, then the breakpoint will slide down to the
   * next line that has runnable code. In this case the server breakpoint cache
   * will be updated, so callers that iterate over the breakpoint cache should
   * take that into account.
   *
   * @param object aLocation
   *        The location of the breakpoint as specified in the protocol.
   */
  _setBreakpoint: function TA__setBreakpoint(aLocation) {
    let breakpoints = this._breakpointStore[aLocation.url];

    // Get or create the breakpoint actor for the given location
    let actor;
    if (breakpoints[aLocation.line].actor) {
      actor = breakpoints[aLocation.line].actor;
    } else {
      actor = breakpoints[aLocation.line].actor = new BreakpointActor(this, {
        url: aLocation.url,
        line: aLocation.line
      });
      this._hooks.addToParentPool(actor);
    }

    // Find all scripts matching the given location
    let scripts = this.dbg.findScripts(aLocation);
    if (scripts.length == 0) {
      return {
        error: "noScript",
        actor: actor.actorID
      };
    }

   /**
     * For each script, if the given line has at least one entry point, set
     * breakpoint on the bytecode offet for each of them.
     */
    let found = false;
    for (let script of scripts) {
      let offsets = script.getLineOffsets(aLocation.line);
      if (offsets.length > 0) {
        for (let offset of offsets) {
          script.setBreakpoint(offset, actor);
        }
        actor.addScript(script, this);
        found = true;
      }
    }
    if (found) {
      return {
        actor: actor.actorID
      };
    }

   /**
     * If we get here, no breakpoint was set. This is because the given line
     * has no entry points, for example because it is empty. As a fallback
     * strategy, we try to set the breakpoint on the smallest line greater
     * than or equal to the given line that as at least one entry point.
     */

    // Find all innermost scripts matching the given location
    let scripts = this.dbg.findScripts({
      url: aLocation.url,
      line: aLocation.line,
      innermost: true
    });

    /**
     * For each innermost script, look for the smallest line greater than or
     * equal to the given line that has one or more entry points. If found, set
     * a breakpoint on the bytecode offset for each of its entry points.
     */
    let actualLocation;
    let found = false;
    for (let script of scripts) {
      let offsets = script.getAllOffsets();
      for (let line = aLocation.line; line < offsets.length; ++line) {
        if (offsets[line]) {
          for (let offset of offsets[line]) {
            script.setBreakpoint(offset, actor);
          }
          actor.addScript(script, this);
          if (!actualLocation) {
            actualLocation = {
              url: aLocation.url,
              line: line,
              column: 0
            };
          }
          found = true;
          break;
        }
      }
    }
    if (found) {
      if (breakpoints[actualLocation.line] &&
          breakpoints[actualLocation.line].actor) {
        /**
         * We already have a breakpoint actor for the actual location, so
         * actor we created earlier is now redundant. Delete it, update the
         * breakpoint store, and return the actor for the actual location.
         */
        actor.onDelete();
        delete breakpoints[aLocation.line];
        return {
          actor: breakpoints[actualLocation.line].actor.actorID,
          actualLocation: actualLocation
        };
      } else {
        /**
         * We don't have a breakpoint actor for the actual location yet.
         * Instead or creating a new actor, reuse the actor we created earlier,
         * and update the breakpoint store.
         */
        actor.location = actualLocation;
        breakpoints[actualLocation.line] = breakpoints[aLocation.line];
        delete breakpoints[aLocation.line];
        // WARNING: This overwrites aLocation.line
        breakpoints[actualLocation.line].line = actualLocation.line;
        return {
          actor: actor.actorID,
          actualLocation: actualLocation
        };
      }
    }

    /**
     * If we get here, no line matching the given line was found, so just
     * epically.
     */
    return {
      error: "noCodeAtLineColumn",
      actor: actor.actorID
    };
  },

  /**
   * Get the script and source lists from the debugger.
   *
   * TODO bug 637572: we should be dealing with sources directly, not inferring
   * them through scripts.
   */
  _discoverSources: function TA__discoverSources() {
    // Only get one script per url.
    let scriptsByUrl = {};
    for (let s of this.dbg.findScripts()) {
      scriptsByUrl[s.url] = s;
    }

    return all([this.sources.sourcesForScript(scriptsByUrl[s])
                for (s of Object.keys(scriptsByUrl))]);
  },

  onSources: function TA_onSources(aRequest) {
    return this._discoverSources().then(() => {
      return {
        sources: [s.form() for (s of this.sources.iter())]
      };
    });
  },

  /**
   * Disassociate all breakpoint actors from their scripts and clear the
   * breakpoint handlers. This method can be used when the thread actor intends
   * to keep the breakpoint store, but needs to clear any actual breakpoints,
   * e.g. due to a page navigation. This way the breakpoint actors' script
   * caches won't hold on to the Debugger.Script objects leaking memory.
   */
  disableAllBreakpoints: function () {
    for (let url in this._breakpointStore) {
      for (let line in this._breakpointStore[url]) {
        let bp = this._breakpointStore[url][line];
        bp.actor.removeScripts();
      }
    }
  },

  /**
   * Handle a protocol request to pause the debuggee.
   */
  onInterrupt: function TA_onInterrupt(aRequest) {
    if (this.state == "exited") {
      return { type: "exited" };
    } else if (this.state == "paused") {
      // TODO: return the actual reason for the existing pause.
      return { type: "paused", why: { type: "alreadyPaused" } };
    } else if (this.state != "running") {
      return { error: "wrongState",
               message: "Received interrupt request in " + this.state +
                        " state." };
    }

    try {
      // Put ourselves in the paused state.
      let packet = this._paused();
      if (!packet) {
        return { error: "notInterrupted" };
      }
      packet.why = { type: "interrupted" };

      // Send the response to the interrupt request now (rather than
      // returning it), because we're going to start a nested event loop
      // here.
      this.conn.send(packet);

      // Start a nested event loop.
      this._nest();

      // We already sent a response to this request, don't send one
      // now.
      return null;
    } catch (e) {
      reportError(e);
      return { error: "notInterrupted", message: e.toString() };
    }
  },

  /**
   * Return the Debug.Frame for a frame mentioned by the protocol.
   */
  _requestFrame: function TA_requestFrame(aFrameID) {
    if (!aFrameID) {
      return this.youngestFrame;
    }

    if (this._framePool.has(aFrameID)) {
      return this._framePool.get(aFrameID).frame;
    }

    return undefined;
  },

  _paused: function TA_paused(aFrame) {
    // We don't handle nested pauses correctly.  Don't try - if we're
    // paused, just continue running whatever code triggered the pause.
    // We don't want to actually have nested pauses (although we
    // have nested event loops).  If code runs in the debuggee during
    // a pause, it should cause the actor to resume (dropping
    // pause-lifetime actors etc) and then repause when complete.

    if (this.state === "paused") {
      return undefined;
    }

    // Clear stepping hooks.
    this.dbg.onEnterFrame = undefined;
    this.dbg.onExceptionUnwind = undefined;
    if (aFrame) {
      aFrame.onStep = undefined;
      aFrame.onPop = undefined;
    }

    this._state = "paused";

    // Save the pause frame (if any) as the youngest frame for
    // stack viewing.
    this.youngestFrame = aFrame;

    // Create the actor pool that will hold the pause actor and its
    // children.
    dbg_assert(!this._pausePool);
    this._pausePool = new ActorPool(this.conn);
    this.conn.addActorPool(this._pausePool);

    // Give children of the pause pool a quick link back to the
    // thread...
    this._pausePool.threadActor = this;

    // Create the pause actor itself...
    dbg_assert(!this._pauseActor);
    this._pauseActor = new PauseActor(this._pausePool);
    this._pausePool.addActor(this._pauseActor);

    // Update the list of frames.
    let poppedFrames = this._updateFrames();

    // Send off the paused packet and spin an event loop.
    let packet = { from: this.actorID,
                   type: "paused",
                   actor: this._pauseActor.actorID };
    if (aFrame) {
      packet.frame = this._createFrameActor(aFrame).form();
    }

    if (poppedFrames) {
      packet.poppedFrames = poppedFrames;
    }

    return packet;
  },

  _nest: function TA_nest() {
    if (this._hooks.preNest) {
      var nestData = this._hooks.preNest();
    }

    let requestor = Object.create(null);
    requestor.url = this._hooks.url;
    requestor.connection = this.conn;
    // DebuggerServer.xpcInspector.enterNestedEventLoop(requestor);

    dbg_assert(this.state === "running");

    if (this._hooks.postNest) {
      this._hooks.postNest(nestData)
    }

    // "continue" resumption value.
    return undefined;
  },

  _resumed: function TA_resumed() {
    this._state = "running";

    // Drop the actors in the pause actor pool.
    this.conn.removeActorPool(this._pausePool);

    this._pausePool = null;
    this._pauseActor = null;
    this.youngestFrame = null;

    return { from: this.actorID, type: "resumed" };
  },

  /**
   * Expire frame actors for frames that have been popped.
   *
   * @returns A list of actor IDs whose frames have been popped.
   */
  _updateFrames: function TA_updateFrames() {
    let popped = [];

    // Create the actor pool that will hold the still-living frames.
    let framePool = new ActorPool(this.conn);
    let frameList = [];

    for each (let frameActor in this._frameActors) {
      if (frameActor.frame.live) {
        framePool.addActor(frameActor);
        frameList.push(frameActor);
      } else {
        popped.push(frameActor.actorID);
      }
    }

    // Remove the old frame actor pool, this will expire
    // any actors that weren't added to the new pool.
    if (this._framePool) {
      this.conn.removeActorPool(this._framePool);
    }

    this._frameActors = frameList;
    this._framePool = framePool;
    this.conn.addActorPool(framePool);

    return popped;
  },

  _createFrameActor: function TA_createFrameActor(aFrame) {
    if (aFrame.actor) {
      return aFrame.actor;
    }

    let actor = new FrameActor(aFrame, this);
    this._frameActors.push(actor);
    this._framePool.addActor(actor);
    aFrame.actor = actor;

    return actor;
  },

  /**
   * Create and return an environment actor that corresponds to the provided
   * Debugger.Environment.
   * @param Debugger.Environment aEnvironment
   *        The lexical environment we want to extract.
   * @param object aPool
   *        The pool where the newly-created actor will be placed.
   * @return The EnvironmentActor for aEnvironment or undefined for host
   *         functions or functions scoped to a non-debuggee global.
   */
  createEnvironmentActor:
  function TA_createEnvironmentActor(aEnvironment, aPool) {
    if (!aEnvironment) {
      return undefined;
    }

    if (aEnvironment.actor) {
      return aEnvironment.actor;
    }

    let actor = new EnvironmentActor(aEnvironment, this);
    this._environmentActors.push(actor);
    aPool.addActor(actor);
    aEnvironment.actor = actor;

    return actor;
  },

  /**
   * Create a grip for the given debuggee value.  If the value is an
   * object, will create an actor with the given lifetime.
   */
  createValueGrip: function TA_createValueGrip(aValue, aPool=false) {
    if (!aPool) {
      aPool = this._pausePool;
    }
    let type = typeof(aValue);

    if (type === "string" && this._stringIsLong(aValue)) {
      return this.longStringGrip(aValue, aPool);
    }

    if (type === "boolean" || type === "string" || type === "number") {
      return aValue;
    }

    if (aValue === null) {
      return { type: "null" };
    }

    if (aValue === undefined) {
      return { type: "undefined" }
    }

    if (typeof(aValue) === "object") {
      return this.objectGrip(aValue, aPool);
    }

    dbg_assert(false, "Failed to provide a grip for: " + aValue);
    return null;
  },

  /**
   * Return a protocol completion value representing the given
   * Debugger-provided completion value.
   */
  createProtocolCompletionValue:
  function TA_createProtocolCompletionValue(aCompletion) {
    let protoValue = {};
    if ("return" in aCompletion) {
      protoValue.return = this.createValueGrip(aCompletion.return);
    } else if ("yield" in aCompletion) {
      protoValue.return = this.createValueGrip(aCompletion.yield);
    } else if ("throw" in aCompletion) {
      protoValue.throw = this.createValueGrip(aCompletion.throw);
    } else {
      protoValue.terminated = true;
    }
    return protoValue;
  },

  /**
   * Create a grip for the given debuggee object.
   *
   * @param aValue Debugger.Object
   *        The debuggee object value.
   * @param aPool ActorPool
   *        The actor pool where the new object actor will be added.
   */
  objectGrip: function TA_objectGrip(aValue, aPool) {
    if (!aPool.objectActors) {
      aPool.objectActors = new WeakMap();
    }

    if (aPool.objectActors.has(aValue)) {
      return aPool.objectActors.get(aValue).grip();
    } else if (this.threadLifetimePool.objectActors.has(aValue)) {
      return this.threadLifetimePool.objectActors.get(aValue).grip();
    }

    let actor = new PauseScopedObjectActor(aValue, this);
    aPool.addActor(actor);
    aPool.objectActors.set(aValue, actor);
    return actor.grip();
  },

  /**
   * Create a grip for the given debuggee object with a pause lifetime.
   *
   * @param aValue Debugger.Object
   *        The debuggee object value.
   */
  pauseObjectGrip: function TA_pauseObjectGrip(aValue) {
    if (!this._pausePool) {
      throw "Object grip requested while not paused.";
    }

    return this.objectGrip(aValue, this._pausePool);
  },

  /**
   * Extend the lifetime of the provided object actor to thread lifetime.
   *
   * @param aActor object
   *        The object actor.
   */
  threadObjectGrip: function TA_threadObjectGrip(aActor) {
    // We want to reuse the existing actor ID, so we just remove it from the
    // current pool's weak map and then let pool.addActor do the rest.
    aActor.registeredPool.objectActors.delete(aActor.obj);
    this.threadLifetimePool.addActor(aActor);
    this.threadLifetimePool.objectActors.set(aActor.obj, aActor);
  },

  /**
   * Handle a protocol request to promote multiple pause-lifetime grips to
   * thread-lifetime grips.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onThreadGrips: function OA_onThreadGrips(aRequest) {
    if (this.state != "paused") {
      return { error: "wrongState" };
    }

    if (!aRequest.actors) {
      return { error: "missingParameter",
               message: "no actors were specified" };
    }

    for (let actorID of aRequest.actors) {
      let actor = this._pausePool.get(actorID);
      if (actor) {
        this.threadObjectGrip(actor);
      }
    }
    return {};
  },

  /**
   * Create a grip for the given string.
   *
   * @param aString String
   *        The string we are creating a grip for.
   * @param aPool ActorPool
   *        The actor pool where the new actor will be added.
   */
  longStringGrip: function TA_longStringGrip(aString, aPool) {
    if (!aPool.longStringActors) {
      aPool.longStringActors = {};
    }

    if (aPool.longStringActors.hasOwnProperty(aString)) {
      return aPool.longStringActors[aString].grip();
    }

    let actor = new LongStringActor(aString, this);
    aPool.addActor(actor);
    aPool.longStringActors[aString] = actor;
    return actor.grip();
  },

  /**
   * Create a long string grip that is scoped to a pause.
   *
   * @param aString String
   *        The string we are creating a grip for.
   */
  pauseLongStringGrip: function TA_pauseLongStringGrip (aString) {
    return this.longStringGrip(aString, this._pausePool);
  },

  /**
   * Create a long string grip that is scoped to a thread.
   *
   * @param aString String
   *        The string we are creating a grip for.
   */
  threadLongStringGrip: function TA_pauseLongStringGrip (aString) {
    return this.longStringGrip(aString, this._threadLifetimePool);
  },

  /**
   * Returns true if the string is long enough to use a LongStringActor instead
   * of passing the value directly over the protocol.
   *
   * @param aString String
   *        The string we are checking the length of.
   */
  _stringIsLong: function TA__stringIsLong(aString) {
    return aString.length >= DebuggerServer.LONG_STRING_LENGTH;
  },

  // JS Debugger API hooks.

  /**
   * A function that the engine calls when a call to a debug event hook,
   * breakpoint handler, watchpoint handler, or similar function throws some
   * exception.
   *
   * @param aException exception
   *        The exception that was thrown in the debugger code.
   */
  uncaughtExceptionHook: function TA_uncaughtExceptionHook(aException) {
    dumpn("Got an exception: " + aException.message + "\n" + aException.stack);
  },

  /**
   * A function that the engine calls when a debugger statement has been
   * executed in the specified frame.
   *
   * @param aFrame Debugger.Frame
   *        The stack frame that contained the debugger statement.
   */
  onDebuggerStatement: function TA_onDebuggerStatement(aFrame) {
    if (this.sources.isBlackBoxed(aFrame.script.url)) {
      return undefined;
    }
    return this._pauseAndRespond(aFrame, { type: "debuggerStatement" });
  },

  /**
   * A function that the engine calls when an exception has been thrown and has
   * propagated to the specified frame.
   *
   * @param aFrame Debugger.Frame
   *        The youngest remaining stack frame.
   * @param aValue object
   *        The exception that was thrown.
   */
  onExceptionUnwind: function TA_onExceptionUnwind(aFrame, aValue) {
    if (this.sources.isBlackBoxed(aFrame.script.url)) {
      return undefined;
    }
    try {
      let packet = this._paused(aFrame);
      if (!packet) {
        return undefined;
      }

      packet.why = { type: "exception",
                     exception: this.createValueGrip(aValue) };
      this.conn.send(packet);
      return this._nest();
    } catch(e) {
      log("Got an exception during TA_onExceptionUnwind: " + e +
                     ": " + e.stack);
      return undefined;
    }
  },

  /**
   * A function that the engine calls when a new script has been loaded into the
   * scope of the specified debuggee global.
   *
   * @param aScript Debugger.Script
   *        The source script that has been loaded into a debuggee compartment.
   * @param aGlobal Debugger.Object
   *        A Debugger.Object instance whose referent is the global object.
   */
  onNewScript: function TA_onNewScript(aScript, aGlobal) {
    this._addScript(aScript);
    this.sources.sourcesForScript(aScript);
  },

  onNewSource: function TA_onNewSource(aSource) {
    this.conn.send({
      from: this.actorID,
      type: "newSource",
      source: aSource.form()
    });
  },

  /**
   * Check if scripts from the provided source URL are allowed to be stored in
   * the cache.
   *
   * @param aSourceUrl String
   *        The url of the script's source that will be stored.
   * @returns true, if the script can be added, false otherwise.
   */
  _allowSource: function TA__allowSource(aSourceUrl) {
    // Ignore anything we don't have a URL for (eval scripts, for example).
    if (!aSourceUrl)
      return false;
    // Ignore XBL bindings for content debugging.
    if (aSourceUrl.indexOf("chrome://") == 0) {
      return false;
    }
    // Ignore about:* pages for content debugging.
    if (aSourceUrl.indexOf("about:") == 0) {
      return false;
    }
    return true;
  },

  /**
   * Restore any pre-existing breakpoints to the scripts that we have access to.
   */
  _restoreBreakpoints: function TA__restoreBreakpoints() {
    for (let s of this.dbg.findScripts()) {
      this._addScript(s);
    }
  },

  /**
   * Add the provided script to the server cache.
   *
   * @param aScript Debugger.Script
   *        The source script that will be stored.
   * @returns true, if the script was added; false otherwise.
   */
  _addScript: function TA__addScript(aScript) {
    if (!this._allowSource(aScript.url)) {
      return false;
    }

    // Set any stored breakpoints.
    let existing = this._breakpointStore[aScript.url];
    if (existing) {
      let endLine = aScript.startLine + aScript.lineCount - 1;
      // Iterate over the lines backwards, so that sliding breakpoints don't
      // affect the loop.
      for (let line = existing.length - 1; line >= aScript.startLine; line--) {
        let bp = existing[line];
        // Only consider breakpoints that are not already associated with
        // scripts, and limit search to the line numbers contained in the new
        // script.
        if (bp && !bp.actor.scripts.length && line <= endLine) {
          this._setBreakpoint(bp);
        }
      }
    }
    return true;
  },

};

ThreadActor.prototype.requestTypes = {
  "attach": ThreadActor.prototype.onAttach,
  "detach": ThreadActor.prototype.onDetach,
  "reconfigure": ThreadActor.prototype.onReconfigure,
  "resume": ThreadActor.prototype.onResume,
  "clientEvaluate": ThreadActor.prototype.onClientEvaluate,
  "frames": ThreadActor.prototype.onFrames,
  "interrupt": ThreadActor.prototype.onInterrupt,
  "releaseMany": ThreadActor.prototype.onReleaseMany,
  "setBreakpoint": ThreadActor.prototype.onSetBreakpoint,
  "sources": ThreadActor.prototype.onSources,
  "threadGrips": ThreadActor.prototype.onThreadGrips
};


/**
 * Creates a PauseActor.
 *
 * PauseActors exist for the lifetime of a given debuggee pause.  Used to
 * scope pause-lifetime grips.
 *
 * @param ActorPool aPool
 *        The actor pool created for this pause.
 */
function PauseActor(aPool)
{
  this.pool = aPool;
}

PauseActor.prototype = {
  actorPrefix: "pause"
};


/**
 * A base actor for any actors that should only respond receive messages in the
 * paused state. Subclasses may expose a `threadActor` which is used to help
 * determine when we are in a paused state. Subclasses should set their own
 * "constructor" property if they want better error messages. You should never
 * instantiate a PauseScopedActor directly, only through subclasses.
 */
function PauseScopedActor()
{
}

/**
 * A function decorator for creating methods to handle protocol messages that
 * should only be received while in the paused state.
 *
 * @param aMethod Function
 *        The function we are decorating.
 */
PauseScopedActor.withPaused = function PSA_withPaused(aMethod) {
  return function () {
    if (this.isPaused()) {
      return aMethod.apply(this, arguments);
    } else {
      return this._wrongState();
    }
  };
};

PauseScopedActor.prototype = {

  /**
   * Returns true if we are in the paused state.
   */
  isPaused: function PSA_isPaused() {
    // When there is not a ThreadActor available (like in the webconsole) we
    // have to be optimistic and assume that we are paused so that we can
    // respond to requests.
    return this.threadActor ? this.threadActor.state === "paused" : true;
  },

  /**
   * Returns the wrongState response packet for this actor.
   */
  _wrongState: function PSA_wrongState() {
    return {
      error: "wrongState",
      message: this.constructor.name +
        " actors can only be accessed while the thread is paused."
    };
  }
};


/**
 * A SourceActor provides information about the source of a script.
 *
 * @param aUrl String
 *        The url of the source we are representing.
 * @param aThreadActor ThreadActor
 *        The current thread actor.
 * @param aSourceMap SourceMapConsumer
 *        Optional. The source map that introduced this source, if available.
 */
function SourceActor(aUrl, aThreadActor, aSourceMap=null) {
  this._threadActor = aThreadActor;
  this._url = aUrl;
  this._sourceMap = aSourceMap;
}

SourceActor.prototype = {
  constructor: SourceActor,
  actorPrefix: "source",

  get threadActor() this._threadActor,
  get url() this._url,

  form: function SA_form() {
    return {
      actor: this.actorID,
      url: this._url,
      isBlackBoxed: this.threadActor.sources.isBlackBoxed(this.url)
      // TODO bug 637572: introductionScript
    };
  },

  disconnect: function LSA_disconnect() {
    if (this.registeredPool && this.registeredPool.sourceActors) {
      delete this.registeredPool.sourceActors[this.actorID];
    }
  },

  /**
   * Handler for the "source" packet.
   */
  onSource: function SA_onSource(aRequest) {
    let sourceContent = null;
    if (this._sourceMap) {
      sourceContent = this._sourceMap.sourceContentFor(this._url);
    }

    if (sourceContent) {
      return {
        from: this.actorID,
        source: this.threadActor.createValueGrip(
          sourceContent, this.threadActor.threadLifetimePool)
      };
    }

    // XXX bug 865252: Don't load from the cache if this is a source mapped
    // source because we can't guarantee that the cache has the most up to date
    // content for this source like we can if it isn't source mapped.
    return fetch(this._url, { loadFromCache: !this._sourceMap })
      .then((aSource) => {
        return this.threadActor.createValueGrip(
          aSource, this.threadActor.threadLifetimePool);
      })
      .then((aSourceGrip) => {
        return {
          from: this.actorID,
          source: aSourceGrip
        };
      }, (aError) => {
        let msg = "Got an exception during SA_onSource: " + aError +
          "\n" + aError.stack;
        // Cu.reportError(msg);
        dumpn(msg);
        return {
          "from": this.actorID,
          "error": "loadSourceError",
          "message": "Could not load the source for " + this._url + "."
        };
      });
  },

  /**
   * Handler for the "blackbox" packet.
   */
  onBlackBox: function SA_onBlackBox(aRequest) {
    this.threadActor.sources.blackBox(this.url);
    let packet = {
      from: this.actorID
    };
    if (this.threadActor.state == "paused"
        && this.threadActor.youngestFrame
        && this.threadActor.youngestFrame.script.url == this.url) {
      packet.pausedInSource = true;
    }
    return packet;
  },

  /**
   * Handler for the "unblackbox" packet.
   */
  onUnblackBox: function SA_onUnblackBox(aRequest) {
    this.threadActor.sources.unblackBox(this.url);
    return {
      from: this.actorID
    };
  }
};

SourceActor.prototype.requestTypes = {
  "source": SourceActor.prototype.onSource,
  "blackbox": SourceActor.prototype.onBlackBox,
  "unblackbox": SourceActor.prototype.onUnblackBox
};


/**
 * Creates an actor for the specified object.
 *
 * @param aObj Debugger.Object
 *        The debuggee object.
 * @param aThreadActor ThreadActor
 *        The parent thread actor for this object.
 */
function ObjectActor(aObj, aThreadActor)
{
  this.obj = aObj;
  this.threadActor = aThreadActor;
}

ObjectActor.prototype = {
  actorPrefix: "obj",

  /**
   * Returns a grip for this actor for returning in a protocol message.
   */
  grip: function OA_grip() {
    let g = {
      "type": "object",
      "class": this.obj.class,
      "actor": this.actorID,
      "extensible": this.obj.isExtensible(),
      "frozen": this.obj.isFrozen(),
      "sealed": this.obj.isSealed()
    };

    // Add additional properties for functions.
    if (this.obj.class === "Function") {
      if (this.obj.name) {
        g.name = this.obj.name;
      } else if (this.obj.displayName) {
        g.displayName = this.obj.displayName;
      }

      // Check if the developer has added a de-facto standard displayName
      // property for us to use.
      let desc = this.obj.getOwnPropertyDescriptor("displayName");
      if (desc && desc.value && typeof desc.value == "string") {
        g.userDisplayName = this.threadActor.createValueGrip(desc.value);
      }
    }

    return g;
  },

  /**
   * Releases this actor from the pool.
   */
  release: function OA_release() {
    if (this.registeredPool.objectActors) {
      this.registeredPool.objectActors.delete(this.obj);
    }
    this.registeredPool.removeActor(this);
  },

  /**
   * Handle a protocol request to provide the names of the properties defined on
   * the object and not its prototype.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onOwnPropertyNames: function OA_onOwnPropertyNames(aRequest) {
    return { from: this.actorID,
             ownPropertyNames: this.obj.getOwnPropertyNames() };
  },

  /**
   * Handle a protocol request to provide the prototype and own properties of
   * the object.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onPrototypeAndProperties: function OA_onPrototypeAndProperties(aRequest) {
    let ownProperties = Object.create(null);
    let names;
    try {
      names = this.obj.getOwnPropertyNames();
    } catch (ex) {
      // The above can throw if this.obj points to a dead object.
      // TODO: we should use Cu.isDeadWrapper() - see bug 885800.
      return { from: this.actorID,
               prototype: this.threadActor.createValueGrip(null),
               ownProperties: ownProperties,
               safeGetterValues: Object.create(null) };
    }
    for (let name of names) {
      ownProperties[name] = this._propertyDescriptor(name);
    }
    return { from: this.actorID,
             prototype: this.threadActor.createValueGrip(this.obj.proto),
             ownProperties: ownProperties,
             safeGetterValues: this._findSafeGetterValues(ownProperties) };
  },

  /**
   * Find the safe getter values for the current Debugger.Object, |this.obj|.
   *
   * @private
   * @param object aOwnProperties
   *        The object that holds the list of known ownProperties for
   *        |this.obj|.
   * @return object
   *         An object that maps property names to safe getter descriptors as
   *         defined by the remote debugging protocol.
   */
  _findSafeGetterValues: function OA__findSafeGetterValues(aOwnProperties)
  {
    let safeGetterValues = Object.create(null);
    let obj = this.obj;
    let level = 0;

    while (obj) {
      let getters = this._findSafeGetters(obj);
      for (let name of getters) {
        // Avoid overwriting properties from prototypes closer to this.obj. Also
        // avoid providing safeGetterValues from prototypes if property |name|
        // is already defined as an own property.
        if (name in safeGetterValues ||
            (obj != this.obj && name in aOwnProperties)) {
          continue;
        }

        let desc = null, getter = null;
        try {
          desc = obj.getOwnPropertyDescriptor(name);
          getter = desc.get;
        } catch (ex) {
          // The above can throw if the cache becomes stale.
        }
        if (!getter) {
          obj._safeGetters = null;
          continue;
        }

        let result = getter.call(this.obj);
        if (result && !("throw" in result)) {
          let getterValue = undefined;
          if ("return" in result) {
            getterValue = result.return;
          } else if ("yield" in result) {
            getterValue = result.yield;
          }
          // WebIDL attributes specified with the LenientThis extended attribute
          // return undefined and should be ignored.
          if (getterValue !== undefined) {
            safeGetterValues[name] = {
              getterValue: this.threadActor.createValueGrip(getterValue),
              getterPrototypeLevel: level,
              enumerable: desc.enumerable,
              writable: level == 0 ? desc.writable : true,
            };
          }
        }
      }

      obj = obj.proto;
      level++;
    }

    return safeGetterValues;
  },

  /**
   * Find the safe getters for a given Debugger.Object. Safe getters are native
   * getters which are safe to execute.
   *
   * @private
   * @param Debugger.Object aObject
   *        The Debugger.Object where you want to find safe getters.
   * @return Set
   *         A Set of names of safe getters. This result is cached for each
   *         Debugger.Object.
   */
  _findSafeGetters: function OA__findSafeGetters(aObject)
  {
    if (aObject._safeGetters) {
      return aObject._safeGetters;
    }

    let getters = new Set();
    for (let name of aObject.getOwnPropertyNames()) {
      let desc = null;
      try {
        desc = aObject.getOwnPropertyDescriptor(name);
      } catch (e) {
        // Calling getOwnPropertyDescriptor on wrapped native prototypes is not
        // allowed (bug 560072).
      }
      if (!desc || desc.value !== undefined || !("get" in desc)) {
        continue;
      }

      let fn = desc.get;
      if (fn && fn.callable && fn.class == "Function" &&
          fn.script === undefined) {
        getters.add(name);
      }
    }

    aObject._safeGetters = getters;
    return getters;
  },

  /**
   * Handle a protocol request to provide the prototype of the object.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onPrototype: function OA_onPrototype(aRequest) {
    return { from: this.actorID,
             prototype: this.threadActor.createValueGrip(this.obj.proto) };
  },

  /**
   * Handle a protocol request to provide the property descriptor of the
   * object's specified property.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onProperty: function OA_onProperty(aRequest) {
    if (!aRequest.name) {
      return { error: "missingParameter",
               message: "no property name was specified" };
    }

    return { from: this.actorID,
             descriptor: this._propertyDescriptor(aRequest.name) };
  },

  /**
   * A helper method that creates a property descriptor for the provided object,
   * properly formatted for sending in a protocol response.
   *
   * @param string aName
   *        The property that the descriptor is generated for.
   */
  _propertyDescriptor: function OA_propertyDescriptor(aName) {
    let desc;
    try {
      desc = this.obj.getOwnPropertyDescriptor(aName);
    } catch (e) {
      // Calling getOwnPropertyDescriptor on wrapped native prototypes is not
      // allowed (bug 560072). Inform the user with a bogus, but hopefully
      // explanatory, descriptor.
      return {
        configurable: false,
        writable: false,
        enumerable: false,
        value: e.name
      };
    }

    let retval = {
      configurable: desc.configurable,
      enumerable: desc.enumerable
    };

    if ("value" in desc) {
      retval.writable = desc.writable;
      retval.value = this.threadActor.createValueGrip(desc.value);
    } else {
      if ("get" in desc) {
        retval.get = this.threadActor.createValueGrip(desc.get);
      }
      if ("set" in desc) {
        retval.set = this.threadActor.createValueGrip(desc.set);
      }
    }
    return retval;
  },

  /**
   * Handle a protocol request to provide the source code of a function.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onDecompile: function OA_onDecompile(aRequest) {
    if (this.obj.class !== "Function") {
      return { error: "objectNotFunction",
               message: "decompile request is only valid for object grips " +
                        "with a 'Function' class." };
    }

    return { from: this.actorID,
             decompiledCode: this.obj.decompile(!!aRequest.pretty) };
  },

  /**
   * Handle a protocol request to provide the parameters of a function.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onParameterNames: function OA_onParameterNames(aRequest) {
    if (this.obj.class !== "Function") {
      return { error: "objectNotFunction",
               message: "'parameterNames' request is only valid for object " +
                        "grips with a 'Function' class." };
    }

    return { parameterNames: this.obj.parameterNames };
  },

  /**
   * Handle a protocol request to release a thread-lifetime grip.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onRelease: function OA_onRelease(aRequest) {
    this.release();
    return {};
  },
};

ObjectActor.prototype.requestTypes = {
  "parameterNames": ObjectActor.prototype.onParameterNames,
  "prototypeAndProperties": ObjectActor.prototype.onPrototypeAndProperties,
  "prototype": ObjectActor.prototype.onPrototype,
  "property": ObjectActor.prototype.onProperty,
  "ownPropertyNames": ObjectActor.prototype.onOwnPropertyNames,
  "decompile": ObjectActor.prototype.onDecompile,
  "release": ObjectActor.prototype.onRelease,
};


/**
 * Creates a pause-scoped actor for the specified object.
 * @see ObjectActor
 */
function PauseScopedObjectActor()
{
  ObjectActor.apply(this, arguments);
}

PauseScopedObjectActor.prototype = Object.create(PauseScopedActor.prototype);

update(PauseScopedObjectActor.prototype, ObjectActor.prototype);

update(PauseScopedObjectActor.prototype, {
  constructor: PauseScopedObjectActor,

  onOwnPropertyNames:
    PauseScopedActor.withPaused(ObjectActor.prototype.onOwnPropertyNames),

  onPrototypeAndProperties:
    PauseScopedActor.withPaused(ObjectActor.prototype.onPrototypeAndProperties),

  onPrototype: PauseScopedActor.withPaused(ObjectActor.prototype.onPrototype),
  onProperty: PauseScopedActor.withPaused(ObjectActor.prototype.onProperty),
  onDecompile: PauseScopedActor.withPaused(ObjectActor.prototype.onDecompile),

  onParameterNames:
    PauseScopedActor.withPaused(ObjectActor.prototype.onParameterNames),

  /**
   * Handle a protocol request to provide the lexical scope of a function.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onScope: PauseScopedActor.withPaused(function OA_onScope(aRequest) {
    if (this.obj.class !== "Function") {
      return { error: "objectNotFunction",
               message: "scope request is only valid for object grips with a" +
                        " 'Function' class." };
    }

    let envActor = this.threadActor.createEnvironmentActor(this.obj.environment,
                                                           this.registeredPool);
    if (!envActor) {
      return { error: "notDebuggee",
               message: "cannot access the environment of this function." };
    }

    return { from: this.actorID, scope: envActor.form() };
  }),

  /**
   * Handle a protocol request to promote a pause-lifetime grip to a
   * thread-lifetime grip.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onThreadGrip: PauseScopedActor.withPaused(function OA_onThreadGrip(aRequest) {
    this.threadActor.threadObjectGrip(this);
    return {};
  }),

  /**
   * Handle a protocol request to release a thread-lifetime grip.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onRelease: PauseScopedActor.withPaused(function OA_onRelease(aRequest) {
    if (this.registeredPool !== this.threadActor.threadLifetimePool) {
      return { error: "notReleasable",
               message: "Only thread-lifetime actors can be released." };
    }

    this.release();
    return {};
  }),
});

update(PauseScopedObjectActor.prototype.requestTypes, {
  "scope": PauseScopedObjectActor.prototype.onScope,
  "threadGrip": PauseScopedObjectActor.prototype.onThreadGrip,
});


/**
 * Creates an actor for the specied "very long" string. "Very long" is specified
 * at the server's discretion.
 *
 * @param aString String
 *        The string.
 */
function LongStringActor(aString)
{
  this.string = aString;
  this.stringLength = aString.length;
}

LongStringActor.prototype = {

  actorPrefix: "longString",

  disconnect: function LSA_disconnect() {
    // Because longStringActors is not a weak map, we won't automatically leave
    // it so we need to manually leave on disconnect so that we don't leak
    // memory.
    if (this.registeredPool && this.registeredPool.longStringActors) {
      delete this.registeredPool.longStringActors[this.actorID];
    }
  },

  /**
   * Returns a grip for this actor for returning in a protocol message.
   */
  grip: function LSA_grip() {
    return {
      "type": "longString",
      "initial": this.string.substring(
        0, DebuggerServer.LONG_STRING_INITIAL_LENGTH),
      "length": this.stringLength,
      "actor": this.actorID
    };
  },

  /**
   * Handle a request to extract part of this actor's string.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onSubstring: function LSA_onSubString(aRequest) {
    return {
      "from": this.actorID,
      "substring": this.string.substring(aRequest.start, aRequest.end)
    };
  },

  /**
   * Handle a request to release this LongStringActor instance.
   */
  onRelease: function LSA_onRelease() {
    // TODO: also check if registeredPool === threadActor.threadLifetimePool
    // when the web console moves aray from manually releasing pause-scoped
    // actors.
    if (this.registeredPool.longStringActors) {
      delete this.registeredPool.longStringActors[this.actorID];
    }
    this.registeredPool.removeActor(this);
    return {};
  },
};

LongStringActor.prototype.requestTypes = {
  "substring": LongStringActor.prototype.onSubstring,
  "release": LongStringActor.prototype.onRelease
};


/**
 * Creates an actor for the specified stack frame.
 *
 * @param aFrame Debugger.Frame
 *        The debuggee frame.
 * @param aThreadActor ThreadActor
 *        The parent thread actor for this frame.
 */
function FrameActor(aFrame, aThreadActor)
{
  this.frame = aFrame;
  this.threadActor = aThreadActor;
}

FrameActor.prototype = {
  actorPrefix: "frame",

  /**
   * A pool that contains frame-lifetime objects, like the environment.
   */
  _frameLifetimePool: null,
  get frameLifetimePool() {
    if (!this._frameLifetimePool) {
      this._frameLifetimePool = new ActorPool(this.conn);
      this.conn.addActorPool(this._frameLifetimePool);
    }
    return this._frameLifetimePool;
  },

  /**
   * Finalization handler that is called when the actor is being evicted from
   * the pool.
   */
  disconnect: function FA_disconnect() {
    this.conn.removeActorPool(this._frameLifetimePool);
    this._frameLifetimePool = null;
  },

  /**
   * Returns a frame form for use in a protocol message.
   */
  form: function FA_form() {
    let form = { actor: this.actorID,
                 type: this.frame.type };
    if (this.frame.type === "call") {
      form.callee = this.threadActor.createValueGrip(this.frame.callee);
    }

    if (this.frame.environment) {
      let envActor = this.threadActor
        .createEnvironmentActor(this.frame.environment,
                                this.frameLifetimePool);
      form.environment = envActor.form();
    }
    form.this = this.threadActor.createValueGrip(this.frame.this);
    form.arguments = this._args();
    if (this.frame.script) {
      form.where = { url: this.frame.script.url,
                     line: this.frame.script.getOffsetLine(this.frame.offset) };
      form.isBlackBoxed = this.threadActor.sources.isBlackBoxed(this.frame.script.url)
    }

    if (!this.frame.older) {
      form.oldest = true;
    }

    return form;
  },

  _args: function FA__args() {
    if (!this.frame.arguments) {
      return [];
    }

    return [this.threadActor.createValueGrip(arg)
            for each (arg in this.frame.arguments)];
  },

  /**
   * Handle a protocol request to pop this frame from the stack.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onPop: function FA_onPop(aRequest) {
    // TODO: remove this when Debugger.Frame.prototype.pop is implemented
    if (typeof this.frame.pop != "function") {
      return { error: "notImplemented",
               message: "Popping frames is not yet implemented." };
    }

    while (this.frame != this.threadActor.dbg.getNewestFrame()) {
      this.threadActor.dbg.getNewestFrame().pop();
    }
    this.frame.pop(aRequest.completionValue);

    // TODO: return the watches property when frame pop watch actors are
    // implemented.
    return { from: this.actorID };
  }
};

FrameActor.prototype.requestTypes = {
  "pop": FrameActor.prototype.onPop,
};


/**
 * Creates a BreakpointActor. BreakpointActors exist for the lifetime of their
 * containing thread and are responsible for deleting breakpoints, handling
 * breakpoint hits and associating breakpoints with scripts.
 *
 * @param ThreadActor aThreadActor
 *        The parent thread actor that contains this breakpoint.
 * @param object aLocation
 *        The location of the breakpoint as specified in the protocol.
 */
function BreakpointActor(aThreadActor, aLocation)
{
  this.scripts = [];
  this.threadActor = aThreadActor;
  this.location = aLocation;
}

BreakpointActor.prototype = {
  actorPrefix: "breakpoint",

  /**
   * Called when this same breakpoint is added to another Debugger.Script
   * instance, in the case of a page reload.
   *
   * @param aScript Debugger.Script
   *        The new source script on which the breakpoint has been set.
   * @param ThreadActor aThreadActor
   *        The parent thread actor that contains this breakpoint.
   */
  addScript: function BA_addScript(aScript, aThreadActor) {
    this.threadActor = aThreadActor;
    this.scripts.push(aScript);
  },

  /**
   * Remove the breakpoints from associated scripts and clear the script cache.
   */
  removeScripts: function () {
    for (let script of this.scripts) {
      script.clearBreakpoint(this);
    }
    this.scripts = [];
  },

  /**
   * A function that the engine calls when a breakpoint has been hit.
   *
   * @param aFrame Debugger.Frame
   *        The stack frame that contained the breakpoint.
   */
  hit: function BA_hit(aFrame) {
    if (this.threadActor.sources.isBlackBoxed(this.location.url)) {
      return undefined;
    }

    // TODO: add the rest of the breakpoints on that line (bug 676602).
    let reason = { type: "breakpoint", actors: [ this.actorID ] };
    return this.threadActor._pauseAndRespond(aFrame, reason, (aPacket) => {
      log("pause callback ...");

      let { url, line } = aPacket.frame.where;
      return this.threadActor.sources.getOriginalLocation(url, line)
        .then(function (aOrigPosition) {
          aPacket.frame.where = aOrigPosition;
          return aPacket;
        });
    });
  },

  /**
   * Handle a protocol request to remove this breakpoint.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onDelete: function BA_onDelete(aRequest) {
    // Remove from the breakpoint store.
    let scriptBreakpoints = this.threadActor._breakpointStore[this.location.url];
    delete scriptBreakpoints[this.location.line];
    this.threadActor._hooks.removeFromParentPool(this);
    // Remove the actual breakpoint from the associated scripts.
    this.removeScripts();

    return { from: this.actorID };
  }
};

BreakpointActor.prototype.requestTypes = {
  "delete": BreakpointActor.prototype.onDelete
};


/**
 * Creates an EnvironmentActor. EnvironmentActors are responsible for listing
 * the bindings introduced by a lexical environment and assigning new values to
 * those identifier bindings.
 *
 * @param Debugger.Environment aEnvironment
 *        The lexical environment that will be used to create the actor.
 * @param ThreadActor aThreadActor
 *        The parent thread actor that contains this environment.
 */
function EnvironmentActor(aEnvironment, aThreadActor)
{
  this.obj = aEnvironment;
  this.threadActor = aThreadActor;
}

EnvironmentActor.prototype = {
  actorPrefix: "environment",

  /**
   * Return an environment form for use in a protocol message.
   */
  form: function EA_form() {
    let form = { actor: this.actorID };

    // What is this environment's type?
    if (this.obj.type == "declarative") {
      form.type = this.obj.callee ? "function" : "block";
    } else {
      form.type = this.obj.type;
    }

    // Does this environment have a parent?
    if (this.obj.parent) {
      form.parent = (this.threadActor
                     .createEnvironmentActor(this.obj.parent,
                                             this.registeredPool)
                     .form());
    }

    // Does this environment reflect the properties of an object as variables?
    if (this.obj.type == "object" || this.obj.type == "with") {
      form.object = this.threadActor.createValueGrip(this.obj.object);
    }

    // Is this the environment created for a function call?
    if (this.obj.callee) {
      form.function = this.threadActor.createValueGrip(this.obj.callee);
    }

    // Shall we list this environment's bindings?
    if (this.obj.type == "declarative") {
      form.bindings = this._bindings();
    }

    return form;
  },

  /**
   * Return the identifier bindings object as required by the remote protocol
   * specification.
   */
  _bindings: function EA_bindings() {
    let bindings = { arguments: [], variables: {} };

    // TODO: this part should be removed in favor of the commented-out part
    // below when getVariableDescriptor lands (bug 725815).
    if (typeof this.obj.getVariable != "function") {
    //if (typeof this.obj.getVariableDescriptor != "function") {
      return bindings;
    }

    let parameterNames;
    if (this.obj.callee) {
      parameterNames = this.obj.callee.parameterNames;
    }
    for each (let name in parameterNames) {
      let arg = {};
      // TODO: this part should be removed in favor of the commented-out part
      // below when getVariableDescriptor lands (bug 725815).
      let desc = {
        value: this.obj.getVariable(name),
        configurable: false,
        writable: true,
        enumerable: true
      };

      // let desc = this.obj.getVariableDescriptor(name);
      let descForm = {
        enumerable: true,
        configurable: desc.configurable
      };
      if ("value" in desc) {
        descForm.value = this.threadActor.createValueGrip(desc.value);
        descForm.writable = desc.writable;
      } else {
        descForm.get = this.threadActor.createValueGrip(desc.get);
        descForm.set = this.threadActor.createValueGrip(desc.set);
      }
      arg[name] = descForm;
      bindings.arguments.push(arg);
    }

    for each (let name in this.obj.names()) {
      if (bindings.arguments.some(function exists(element) {
                                    return !!element[name];
                                  })) {
        continue;
      }

      // TODO: this part should be removed in favor of the commented-out part
      // below when getVariableDescriptor lands.
      let desc = {
        configurable: false,
        writable: true,
        enumerable: true
      };
      try {
        desc.value = this.obj.getVariable(name);
      } catch (e) {
        // Avoid "Debugger scope is not live" errors for |arguments|, introduced
        // in bug 746601.
        if (name != "arguments") {
          throw e;
        }
      }
      //let desc = this.obj.getVariableDescriptor(name);
      let descForm = {
        enumerable: true,
        configurable: desc.configurable
      };
      if ("value" in desc) {
        descForm.value = this.threadActor.createValueGrip(desc.value);
        descForm.writable = desc.writable;
      } else {
        descForm.get = this.threadActor.createValueGrip(desc.get);
        descForm.set = this.threadActor.createValueGrip(desc.set);
      }
      bindings.variables[name] = descForm;
    }

    return bindings;
  },

  /**
   * Handle a protocol request to change the value of a variable bound in this
   * lexical environment.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onAssign: function EA_onAssign(aRequest) {
    // TODO: enable the commented-out part when getVariableDescriptor lands
    // (bug 725815).
    /*let desc = this.obj.getVariableDescriptor(aRequest.name);

    if (!desc.writable) {
      return { error: "immutableBinding",
               message: "Changing the value of an immutable binding is not " +
                        "allowed" };
    }*/

    try {
      this.obj.setVariable(aRequest.name, aRequest.value);
    } catch (e) {
      if (e instanceof Debugger.DebuggeeWouldRun) {
        return { error: "threadWouldRun",
                 cause: e.cause ? e.cause : "setter",
                 message: "Assigning a value would cause the debuggee to run" };
      }
      // This should never happen, so let it complain loudly if it does.
      throw e;
    }
    return { from: this.actorID };
  },

  /**
   * Handle a protocol request to fully enumerate the bindings introduced by the
   * lexical environment.
   *
   * @param aRequest object
   *        The protocol request object.
   */
  onBindings: function EA_onBindings(aRequest) {
    return { from: this.actorID,
             bindings: this._bindings() };
  }
};

EnvironmentActor.prototype.requestTypes = {
  "assign": EnvironmentActor.prototype.onAssign,
  "bindings": EnvironmentActor.prototype.onBindings
};

/**
 * Override the toString method in order to get more meaningful script output
 * for debugging the debugger.
 */
Debugger.Script.prototype.toString = function() {
  let output = "";
  if (this.url) {
    output += this.url;
  }
  if (typeof this.startLine != "undefined") {
    output += ":" + this.startLine;
    if (this.lineCount && this.lineCount > 1) {
      output += "-" + (this.startLine + this.lineCount - 1);
    }
  }
  if (this.strictMode) {
    output += ":strict";
  }
  return output;
};

/**
 * Helper property for quickly getting to the line number a stack frame is
 * currently paused at.
 */
Object.defineProperty(Debugger.Frame.prototype, "line", {
  configurable: true,
  get: function() {
    if (this.script) {
      return this.script.getOffsetLine(this.offset);
    } else {
      return null;
    }
  }
});


/**
 * Creates an actor for handling chrome debugging. ChromeDebuggerActor is a
 * thin wrapper over ThreadActor, slightly changing some of its behavior.
 *
 * @param aConnection object
 *        The DebuggerServerConnection with which this ChromeDebuggerActor
 *        is associated. (Currently unused, but required to make this
 *        constructor usable with addGlobalActor.)
 *
 * @param aHooks object
 *        An object with preNest and postNest methods for calling when entering
 *        and exiting a nested event loop and also addToParentPool and
 *        removeFromParentPool methods for handling the lifetime of actors that
 *        will outlive the thread, like breakpoints.
 */
function ChromeDebuggerActor(aConnection, aHooks)
{
  ThreadActor.call(this, aHooks);
}

ChromeDebuggerActor.prototype = Object.create(ThreadActor.prototype);

update(ChromeDebuggerActor.prototype, {
  constructor: ChromeDebuggerActor,

  // A constant prefix that will be used to form the actor ID by the server.
  actorPrefix: "chromeDebugger",

  /**
   * Override the eligibility check for scripts and sources to make sure every
   * script and source with a URL is stored when debugging chrome.
   */
  _allowSource: function(aSourceURL) !!aSourceURL,

   /**
   * An object that will be used by ThreadActors to tailor their behavior
   * depending on the debugging context being required (chrome or content).
   * The methods that this object provides must be bound to the ThreadActor
   * before use.
   */
  globalManager: {
    findGlobals: function CDA_findGlobals() {
      // Add every global known to the debugger as debuggee.
      this.dbg.addAllGlobalsAsDebuggees();
    },

    /**
     * A function that the engine calls when a new global object has been
     * created.
     *
     * @param aGlobal Debugger.Object
     *        The new global object that was created.
     */
    onNewGlobal: function CDA_onNewGlobal(aGlobal) {
      this.addDebuggee(aGlobal);
      // Notify the client.
      this.conn.send({
        from: this.actorID,
        type: "newGlobal",
        // TODO: after bug 801084 lands see if we need to JSONify this.
        hostAnnotations: aGlobal.hostAnnotations
      });
    }
  }
});


/**
 * Manages the sources for a thread. Handles source maps, locations in the
 * sources, etc for ThreadActors.
 */
function ThreadSources(aThreadActor, aUseSourceMaps, aAllowPredicate,
                       aOnNewSource) {
  this._thread = aThreadActor;
  this._useSourceMaps = aUseSourceMaps;
  this._allow = aAllowPredicate;
  this._onNewSource = aOnNewSource;

  // source map URL --> promise of SourceMapConsumer
  this._sourceMaps = Object.create(null);
  // generated source url --> promise of SourceMapConsumer
  this._sourceMapsByGeneratedSource = Object.create(null);
  // original source url --> promise of SourceMapConsumer
  this._sourceMapsByOriginalSource = Object.create(null);
  // source url --> SourceActor
  this._sourceActors = Object.create(null);
  // original url --> generated url
  this._generatedUrlsByOriginalUrl = Object.create(null);
}

/**
 * Must be a class property because it needs to persist across reloads, same as
 * the breakpoint store.
 */
ThreadSources._blackBoxedSources = new Set();

ThreadSources.prototype = {
  /**
   * Return the source actor representing |aURL|, creating one if none
   * exists already. Returns null if |aURL| is not allowed by the 'allow'
   * predicate.
   *
   * Right now this takes a URL, but in the future it should
   * take a Debugger.Source. See bug 637572.
   *
   * @param String aURL
   *        The source URL.
   * @param optional SourceMapConsumer aSourceMap
   *        The source map that introduced this source, if any.
   * @returns a SourceActor representing the source at aURL or null.
   */
  source: function TS_source(aURL, aSourceMap=null) {
    if (!this._allow(aURL)) {
      return null;
    }

    if (aURL in this._sourceActors) {
      return this._sourceActors[aURL];
    }

    let actor = new SourceActor(aURL, this._thread, aSourceMap);
    this._thread.threadLifetimePool.addActor(actor);
    this._sourceActors[aURL] = actor;
    try {
      this._onNewSource(actor);
    } catch (e) {
      reportError(e);
    }
    return actor;
  },

  /**
   * Return a promise of an array of source actors representing all the
   * sources of |aScript|.
   *
   * If source map handling is enabled and |aScript| has a source map, then
   * use it to find all of |aScript|'s *original* sources; return a promise
   * of an array of source actors for those.
   */
  sourcesForScript: function TS_sourcesForScript(aScript) {
    if (!this._useSourceMaps || !aScript.sourceMapURL) {
      return resolve([this.source(aScript.url)].filter(isNotNull));
    }

    return this.sourceMap(aScript)
      .then((aSourceMap) => {
        return [
          this.source(s, aSourceMap) for (s of aSourceMap.sources)
        ];
      })
      .then(null, (e) => {
        reportError(e);
        delete this._sourceMaps[this._normalize(aScript.sourceMapURL, aScript.url)];
        delete this._sourceMapsByGeneratedSource[aScript.url];
        return [this.source(aScript.url)];
      })
      .then(function (aSources) {
        return aSources.filter(isNotNull);
      });
  },

  /**
   * Return a promise of a SourceMapConsumer for the source map for
   * |aScript|; if we already have such a promise extant, return that.
   * |aScript| must have a non-null sourceMapURL.
   */
  sourceMap: function TS_sourceMap(aScript) {
    if (aScript.url in this._sourceMapsByGeneratedSource) {
      return this._sourceMapsByGeneratedSource[aScript.url];
    }
    dbg_assert(aScript.sourceMapURL);
    let sourceMapURL = this._normalize(aScript.sourceMapURL, aScript.url);
    let map = this._fetchSourceMap(sourceMapURL)
      .then((aSourceMap) => {
        for (let s of aSourceMap.sources) {
          this._generatedUrlsByOriginalUrl[s] = aScript.url;
          this._sourceMapsByOriginalSource[s] = resolve(aSourceMap);
        }
        return aSourceMap;
      });
    this._sourceMapsByGeneratedSource[aScript.url] = map;
    return map;
  },

  /**
   * Return a promise of a SourceMapConsumer for the source map located at
   * |aAbsSourceMapURL|, which must be absolute. If there is already such a
   * promise extant, return it.
   */
  _fetchSourceMap: function TS__fetchSourceMap(aAbsSourceMapURL) {
    if (aAbsSourceMapURL in this._sourceMaps) {
      return this._sourceMaps[aAbsSourceMapURL];
    } else {
      let promise = fetch(aAbsSourceMapURL).then((rawSourceMap) => {
        let map = new SourceMapConsumer(rawSourceMap);
        let base = aAbsSourceMapURL.replace(/\/[^\/]+$/, '/');
        if (base.indexOf("data:") !== 0) {
          map.sourceRoot = map.sourceRoot
            ? this._normalize(map.sourceRoot, base)
            : base;
        }
        return map;
      });
      this._sourceMaps[aAbsSourceMapURL] = promise;
      return promise;
    }
  },

  /**
   * Returns a promise of the location in the original source if the source is
   * source mapped, otherwise a promise of the same location.
   *
   * TODO bug 637572: take/return a column
   */
  getOriginalLocation: function TS_getOriginalLocation(aSourceUrl, aLine) {
    if (aSourceUrl in this._sourceMapsByGeneratedSource) {
      return this._sourceMapsByGeneratedSource[aSourceUrl]
        .then(function (aSourceMap) {
          let { source, line } = aSourceMap.originalPositionFor({
            source: aSourceUrl,
            line: aLine,
            column: Infinity
          });
          return {
            url: source,
            line: line
          };
        });
    }

    // No source map
    return resolve({
      url: aSourceUrl,
      line: aLine
    });
  },

  /**
   * Returns a promise of the location in the generated source corresponding to
   * the original source and line given.
   *
   * When we pass a script S representing generated code to |sourceMap|,
   * above, that returns a promise P. The process of resolving P populates
   * the tables this function uses; thus, it won't know that S's original
   * source URLs map to S until P is resolved.
   *
   * TODO bug 637572: take/return a column
   */
  getGeneratedLocation: function TS_getGeneratedLocation(aSourceUrl, aLine) {
    if (aSourceUrl in this._sourceMapsByOriginalSource) {
      return this._sourceMapsByOriginalSource[aSourceUrl]
        .then((aSourceMap) => {
          let { line } = aSourceMap.generatedPositionFor({
            source: aSourceUrl,
            line: aLine,
            column: Infinity
          });
          return {
            url: this._generatedUrlsByOriginalUrl[aSourceUrl],
            line: line
          };
        });
    }

    // No source map
    return resolve({
      url: aSourceUrl,
      line: aLine
    });
  },

  /**
   * Returns true if URL for the given source is black boxed.
   *
   * @param aURL String
   *        The URL of the source which we are checking whether it is black
   *        boxed or not.
   */
  isBlackBoxed: function TS_isBlackBoxed(aURL) {
    return ThreadSources._blackBoxedSources.has(aURL);
  },

  /**
   * Add the given source URL to the set of sources that are black boxed. If the
   * thread is currently paused and we are black boxing the yougest frame's
   * source, this will force a step.
   *
   * @param aURL String
   *        The URL of the source which we are black boxing.
   */
  blackBox: function TS_blackBox(aURL) {
    ThreadSources._blackBoxedSources.add(aURL);
  },

  /**
   * Remove the given source URL to the set of sources that are black boxed.
   *
   * @param aURL String
   *        The URL of the source which we are no longer black boxing.
   */
  unblackBox: function TS_unblackBox(aURL) {
    ThreadSources._blackBoxedSources.delete(aURL);
  },

  /**
   * Normalize multiple relative paths towards the base paths on the right.
   */
  _normalize: function TS__normalize(...aURLs) {
    dbg_assert(aURLs.length > 1);
    let base = Services.io.newURI(aURLs.pop(), null, null);
    let url;
    while ((url = aURLs.pop())) {
      base = Services.io.newURI(url, null, base);
    }
    return base.spec;
  },

  iter: function TS_iter() {
    for (let url in this._sourceActors) {
      yield this._sourceActors[url];
    }
  }
};

// Utility functions.

/**
 * Utility function for updating an object with the properties of another
 * object.
 *
 * @param aTarget Object
 *        The object being updated.
 * @param aNewAttrs Object
 *        The new attributes being set on the target.
 */
function update(aTarget, aNewAttrs) {
  for (let key in aNewAttrs) {
    let desc = Object.getOwnPropertyDescriptor(aNewAttrs, key);

    if (desc) {
      Object.defineProperty(aTarget, key, desc);
    }
  }
}

/**
 * Returns true if its argument is not null.
 */
function isNotNull(aThing) {
  return aThing !== null;
}

/**
 * Performs a request to load the desired URL and returns a promise.
 *
 * @param aURL String
 *        The URL we will request.
 * @returns Promise
 *        A promise of the document at that URL, as a string.
 *
 * XXX: It may be better to use nsITraceableChannel to get to the sources
 * without relying on caching when we can (not for eval, etc.):
 * http://www.softwareishard.com/blog/firebug/nsitraceablechannel-intercept-http-traffic/
 */
function fetch(aURL, aOptions={ loadFromCache: true }) {
  let deferred = defer();
  let scheme;
  let url = aURL.split(" -> ").pop();
  let charset;
  let filePath = url;
  // try {
  //   scheme = Services.io.extractScheme(url);
  // } catch (e) {
    // In the xpcshell tests, the script url is the absolute path of the test
    // file, which will make a malformed URI error be thrown. Add the file
    // scheme prefix ourselves.
    url = "file://" + url;
  //   scheme = Services.io.extractScheme(url);
  // }
  scheme = "file";

  switch (scheme) {
    case "file":
    case "chrome":
    case "resource":
      try {
        // NetUtil.asyncFetch(url, function onFetch(aStream, aStatus) {
          // if (!Components.isSuccessCode(aStatus)) {
          //   deferred.reject("Request failed: " + url);
          //   return;
          // }
          let cc = globalDebuggee.cc;
          let fileUtils = cc.FileUtils.getInstance();
          let source = fileUtils.getStringFromFile(filePath);//NetUtil.readInputStreamToString(aStream, aStream.available());
          if (!source)
          {
            deferred.reject("Request failed: " + url);
          }
          else
          {
            deferred.resolve(source);
          }
          // aStream.close();
        // });
      } catch (ex) {
        deferred.reject("Request failed: " + url);
      }
      break;

    default:
      let channel;
      try {
        channel = Services.io.newChannel(url, null, null);
      } catch (e if e.name == "NS_ERROR_UNKNOWN_PROTOCOL") {
        // On Windows xpcshell tests, c:/foo/bar can pass as a valid URL, but
        // newChannel won't be able to handle it.
        url = "file:///" + url;
        channel = Services.io.newChannel(url, null, null);
      }
      let chunks = [];
      let streamListener = {
        onStartRequest: function(aRequest, aContext, aStatusCode) {
          if (!Components.isSuccessCode(aStatusCode)) {
            deferred.reject("Request failed: " + url);
          }
        },
        onDataAvailable: function(aRequest, aContext, aStream, aOffset, aCount) {
          chunks.push(NetUtil.readInputStreamToString(aStream, aCount));
        },
        onStopRequest: function(aRequest, aContext, aStatusCode) {
          if (!Components.isSuccessCode(aStatusCode)) {
            deferred.reject("Request failed: " + url);
            return;
          }

          charset = channel.contentCharset;
          deferred.resolve(chunks.join(""));
        }
      };

      channel.loadFlags = aOptions.loadFromCache
        ? channel.LOAD_FROM_CACHE
        : channel.LOAD_BYPASS_CACHE;
      channel.asyncOpen(streamListener, null);
      break;
  }

  return deferred.promise.then(function (source) {
    return convertToUnicode(source, charset);
  });
}

/**
 * Convert a given string, encoded in a given character set, to unicode.
 *
 * @param string aString
 *        A string.
 * @param string aCharset
 *        A character set.
 */
function convertToUnicode(aString, aCharset=null) {
  // Decoding primitives.
  // let converter = Cc["@mozilla.org/intl/scriptableunicodeconverter"]
  //   .createInstance(Ci.nsIScriptableUnicodeConverter);
  // try {
  //   converter.charset = aCharset || "UTF-8";
  //   return converter.ConvertToUnicode(aString);
  // } catch(e) {
    return aString;
  // }
}

/**
 * Report the given error in the error console and to stdout.
 */
function reportError(aError) {
  // Cu.reportError(aError);
  dumpn(aError.message + ":\n" + aError.stack);
}
