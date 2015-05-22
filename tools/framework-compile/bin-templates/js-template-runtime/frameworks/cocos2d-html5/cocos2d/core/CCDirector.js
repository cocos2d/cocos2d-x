/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

cc.g_NumberOfDraws = 0;

cc.GLToClipTransform = function (transformOut) {
    //var projection = new cc.math.Matrix4();
    //cc.kmGLGetMatrix(cc.KM_GL_PROJECTION, projection);
    cc.kmGLGetMatrix(cc.KM_GL_PROJECTION, transformOut);

    var modelview = new cc.math.Matrix4();
    cc.kmGLGetMatrix(cc.KM_GL_MODELVIEW, modelview);

    transformOut.multiply(modelview);
};
//----------------------------------------------------------------------------------------------------------------------

/**
 * <p>
 *    ATTENTION: USE cc.director INSTEAD OF cc.Director.<br/>
 *    cc.director is a singleton object which manage your game's logic flow.<br/>
 *    Since the cc.director is a singleton, you don't need to call any constructor or create functions,<br/>
 *    the standard way to use it is by calling:<br/>
 *      - cc.director.methodName(); <br/>
 *
 *    It creates and handle the main Window and manages how and when to execute the Scenes.<br/>
 *    <br/>
 *    The cc.director is also responsible for:<br/>
 *      - initializing the OpenGL context<br/>
 *      - setting the OpenGL pixel format (default on is RGB565)<br/>
 *      - setting the OpenGL pixel format (default on is RGB565)<br/>
 *      - setting the OpenGL buffer depth (default one is 0-bit)<br/>
 *      - setting the projection (default one is 3D)<br/>
 *      - setting the orientation (default one is Portrait)<br/>
 *      <br/>
 *    <br/>
 *    The cc.director also sets the default OpenGL context:<br/>
 *      - GL_TEXTURE_2D is enabled<br/>
 *      - GL_VERTEX_ARRAY is enabled<br/>
 *      - GL_COLOR_ARRAY is enabled<br/>
 *      - GL_TEXTURE_COORD_ARRAY is enabled<br/>
 * </p>
 * <p>
 *   cc.director also synchronizes timers with the refresh rate of the display.<br/>
 *   Features and Limitations:<br/>
 *      - Scheduled timers & drawing are synchronizes with the refresh rate of the display<br/>
 *      - Only supports animation intervals of 1/60 1/30 & 1/15<br/>
 * </p>
 * @class
 * @name cc.Director
 */
cc.Director = cc.Class.extend(/** @lends cc.Director# */{
    //Variables
    _landscape: false,
    _nextDeltaTimeZero: false,
    _paused: false,
    _purgeDirectorInNextLoop: false,
    _sendCleanupToScene: false,
    _animationInterval: 0.0,
    _oldAnimationInterval: 0.0,
    _projection: 0,
    _accumDt: 0.0,
    _contentScaleFactor: 1.0,

    _displayStats: false,
    _deltaTime: 0.0,
    _frameRate: 0.0,

    _FPSLabel: null,
    _SPFLabel: null,
    _drawsLabel: null,

    _winSizeInPoints: null,

    _lastUpdate: null,
    _nextScene: null,
    _notificationNode: null,
    _openGLView: null,
    _scenesStack: null,
    _projectionDelegate: null,
    _runningScene: null,

    _frames: 0,
    _totalFrames: 0,
    _secondsPerFrame: 0,

    _dirtyRegion: null,

    _scheduler: null,
    _actionManager: null,
    _eventProjectionChanged: null,
    _eventAfterDraw: null,
    _eventAfterVisit: null,
    _eventAfterUpdate: null,

    ctor: function () {
        var self = this;
        self._lastUpdate = Date.now();
        cc.eventManager.addCustomListener(cc.game.EVENT_SHOW, function () {
            self._lastUpdate = Date.now();
        });
    },

    init: function () {
        // scenes
        this._oldAnimationInterval = this._animationInterval = 1.0 / cc.defaultFPS;
        this._scenesStack = [];
        // Set default projection (3D)
        this._projection = cc.Director.PROJECTION_DEFAULT;
        // projection delegate if "Custom" projection is used
        this._projectionDelegate = null;

        //FPS
        this._accumDt = 0;
        this._frameRate = 0;
        this._displayStats = false;//can remove
        this._totalFrames = this._frames = 0;
        this._lastUpdate = Date.now();

        //Paused?
        this._paused = false;

        //purge?
        this._purgeDirectorInNextLoop = false;

        this._winSizeInPoints = cc.size(0, 0);

        this._openGLView = null;
        this._contentScaleFactor = 1.0;

        //scheduler
        this._scheduler = new cc.Scheduler();
        //action manager
        if(cc.ActionManager){
            this._actionManager = new cc.ActionManager();
            this._scheduler.scheduleUpdate(this._actionManager, cc.Scheduler.PRIORITY_SYSTEM, false);
        }else{
            this._actionManager = null;
        }

        this._eventAfterDraw = new cc.EventCustom(cc.Director.EVENT_AFTER_DRAW);
        this._eventAfterDraw.setUserData(this);
        this._eventAfterVisit = new cc.EventCustom(cc.Director.EVENT_AFTER_VISIT);
        this._eventAfterVisit.setUserData(this);
        this._eventAfterUpdate = new cc.EventCustom(cc.Director.EVENT_AFTER_UPDATE);
        this._eventAfterUpdate.setUserData(this);
        this._eventProjectionChanged = new cc.EventCustom(cc.Director.EVENT_PROJECTION_CHANGED);
        this._eventProjectionChanged.setUserData(this);

        return true;
    },

    /**
     * calculates delta time since last time it was called
     */
    calculateDeltaTime: function () {
        var now = Date.now();

        // new delta time.
        if (this._nextDeltaTimeZero) {
            this._deltaTime = 0;
            this._nextDeltaTimeZero = false;
        } else {
            this._deltaTime = (now - this._lastUpdate) / 1000;
        }

        if ((cc.game.config[cc.game.CONFIG_KEY.debugMode] > 0) && (this._deltaTime > 0.2))
            this._deltaTime = 1 / 60.0;

        this._lastUpdate = now;
    },

    /**
     * Converts a view coordinate to an WebGL coordinate<br/>
     * Useful to convert (multi) touches coordinates to the current layout (portrait or landscape)<br/>
     * Implementation can be found in CCDirectorWebGL
     * @function
     * @param {cc.Point} uiPoint
     * @return {cc.Point}
     */
    convertToGL: null,

    /**
     * Converts an WebGL coordinate to a view coordinate<br/>
     * Useful to convert node points to window points for calls such as glScissor<br/>
     * Implementation can be found in CCDirectorWebGL
     * @function
     * @param {cc.Point} glPoint
     * @return {cc.Point}
     */
    convertToUI: null,

    /**
     *  Draw the scene. This method is called every frame. Don't call it manually.
     */
    drawScene: function () {
        var renderer = cc.renderer;
        // calculate "global" dt
        this.calculateDeltaTime();

        //tick before glClear: issue #533
        if (!this._paused) {
            this._scheduler.update(this._deltaTime);
            cc.eventManager.dispatchEvent(this._eventAfterUpdate);
        }

        this._clear();

        /* to avoid flickr, nextScene MUST be here: after tick and before draw.
         XXX: Which bug is this one. It seems that it can't be reproduced with v0.9 */
        if (this._nextScene) {
            this.setNextScene();
        }

        if (this._beforeVisitScene)
            this._beforeVisitScene();

        // draw the scene
        if (this._runningScene) {
            if (renderer.childrenOrderDirty === true) {
                cc.renderer.clearRenderCommands();
                this._runningScene._renderCmd._curLevel = 0;                          //level start from 0;
                this._runningScene.visit();
                renderer.resetFlag();
            } else if (renderer.transformDirty() === true)
                renderer.transform();

            cc.eventManager.dispatchEvent(this._eventAfterVisit);
        }

        // draw the notifications node
        if (this._notificationNode)
            this._notificationNode.visit();

        if (this._displayStats)
            this._showStats();

        if (this._afterVisitScene)
            this._afterVisitScene();

        renderer.rendering(cc._renderContext);
        cc.eventManager.dispatchEvent(this._eventAfterDraw);
        this._totalFrames++;

        if (this._displayStats)
            this._calculateMPF();
    },

    _beforeVisitScene: null,
    _afterVisitScene: null,

    /**
     * End the life of director in the next frame
     */
    end: function () {
        this._purgeDirectorInNextLoop = true;
    },

    /**
     * Returns the size in pixels of the surface. It could be different than the screen size.<br/>
     * High-res devices might have a higher surface size than the screen size.
     * @return {Number}
     */
    getContentScaleFactor: function () {
        return this._contentScaleFactor;
    },

    /**
     * This object will be visited after the main scene is visited.<br/>
     * This object MUST implement the "visit" selector.<br/>
     * Useful to hook a notification object
     * @return {cc.Node}
     */
    getNotificationNode: function () {
        return this._notificationNode;
    },

    /**
     * Returns the size of the WebGL view in points.<br/>
     * It takes into account any possible rotation (device orientation) of the window
     * @return {cc.Size}
     */
    getWinSize: function () {
        return cc.size(this._winSizeInPoints);
    },

    /**
     * Returns the size of the OpenGL view in pixels.<br/>
     * It takes into account any possible rotation (device orientation) of the window.<br/>
     * On Mac winSize and winSizeInPixels return the same value.
     * @return {cc.Size}
     */
    getWinSizeInPixels: function () {
        return cc.size(this._winSizeInPoints.width * this._contentScaleFactor, this._winSizeInPoints.height * this._contentScaleFactor);
    },

    /**
     * getVisibleSize/getVisibleOrigin move to CCDirectorWebGL/CCDirectorCanvas
     * getZEye move to CCDirectorWebGL
     */

    /**
     * Returns the visible size of the running scene
     * @function
     * @return {cc.Size}
     */
    getVisibleSize: null,

    /**
     * Returns the visible origin of the running scene
     * @function
     * @return {cc.Point}
     */
    getVisibleOrigin: null,

    /**
     * Returns the z eye, only available in WebGL mode
     * @function
     * @return {Number}
     */
    getZEye: null,

    /**
     * Pause the director's ticker
     */
    pause: function () {
        if (this._paused)
            return;

        this._oldAnimationInterval = this._animationInterval;
        // when paused, don't consume CPU
        this.setAnimationInterval(1 / 4.0);
        this._paused = true;
    },

    /**
     * Pops out a scene from the queue.<br/>
     * This scene will replace the running one.<br/>
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.<br/>
     * ONLY call it if there is a running scene.
     */
    popScene: function () {

        cc.assert(this._runningScene, cc._LogInfos.Director_popScene);

        this._scenesStack.pop();
        var c = this._scenesStack.length;

        if (c === 0)
            this.end();
        else {
            this._sendCleanupToScene = true;
            this._nextScene = this._scenesStack[c - 1];
        }
    },

    /**
     * Removes cached all cocos2d cached data. It will purge the cc.textureCache, cc.spriteFrameCache, cc.animationCache
     */
    purgeCachedData: function () {
        cc.animationCache._clear();
        cc.spriteFrameCache._clear();
        cc.textureCache._clear();
    },

    /**
     * Purge the cc.director itself, including unschedule all schedule, remove all event listeners, clean up and exit the running scene, stops all animations, clear cached data.
     */
    purgeDirector: function () {
        //cleanup scheduler
        this.getScheduler().unscheduleAll();

        // Disable event dispatching
        if (cc.eventManager)
            cc.eventManager.setEnabled(false);

        // don't release the event handlers
        // They are needed in case the director is run again

        if (this._runningScene) {
            this._runningScene.onExitTransitionDidStart();
            this._runningScene.onExit();
            this._runningScene.cleanup();
        }

        this._runningScene = null;
        this._nextScene = null;

        // remove all objects, but don't release it.
        // runScene might be executed after 'end'.
        this._scenesStack.length = 0;

        this.stopAnimation();

        // Clear all caches
        this.purgeCachedData();

        cc.checkGLErrorDebug();
    },

    /**
     * Suspends the execution of the running scene, pushing it on the stack of suspended scenes.<br/>
     * The new scene will be executed.<br/>
     * Try to avoid big stacks of pushed scenes to reduce memory allocation.<br/>
     * ONLY call it if there is a running scene.
     * @param {cc.Scene} scene
     */
    pushScene: function (scene) {

        cc.assert(scene, cc._LogInfos.Director_pushScene);

        this._sendCleanupToScene = false;

        this._scenesStack.push(scene);
        this._nextScene = scene;
    },

    /**
     * Run a scene. Replaces the running scene with a new one or enter the first scene.
     * @param {cc.Scene} scene
     */
    runScene: function (scene) {

        cc.assert(scene, cc._LogInfos.Director_pushScene);

        if (!this._runningScene) {
            //start scene
            this.pushScene(scene);
            this.startAnimation();
        } else {
            //replace scene
            var i = this._scenesStack.length;
            if (i === 0) {
                this._sendCleanupToScene = true;
                this._scenesStack[i] = scene;
                this._nextScene = scene;
            } else {
                this._sendCleanupToScene = true;
                this._scenesStack[i - 1] = scene;
                this._nextScene = scene;
            }
        }
    },

    /**
     * Resume director after pause, if the current scene is not paused, nothing will happen.
     */
    resume: function () {
        if (!this._paused) {
            return;
        }

        this.setAnimationInterval(this._oldAnimationInterval);
        this._lastUpdate = Date.now();
        if (!this._lastUpdate) {
            cc.log(cc._LogInfos.Director_resume);
        }

        this._paused = false;
        this._deltaTime = 0;
    },

    /**
     * The size in pixels of the surface. It could be different than the screen size.<br/>
     * High-res devices might have a higher surface size than the screen size.
     * @param {Number} scaleFactor
     */
    setContentScaleFactor: function (scaleFactor) {
        if (scaleFactor !== this._contentScaleFactor) {
            this._contentScaleFactor = scaleFactor;
            this._createStatsLabel();
        }
    },

    /**
     * Enables or disables WebGL depth test.<br/>
     * Implementation can be found in CCDirectorCanvas.js/CCDirectorWebGL.js
     * @function
     * @param {Boolean} on
     */
    setDepthTest: null,

    /**
     * Sets the default values based on the CCConfiguration info
     */
    setDefaultValues: function () {

    },

    /**
     * Sets whether next delta time equals to zero
     * @param {Boolean} nextDeltaTimeZero
     */
    setNextDeltaTimeZero: function (nextDeltaTimeZero) {
        this._nextDeltaTimeZero = nextDeltaTimeZero;
    },

    /**
     * Starts the registered next scene
     */
    setNextScene: function () {
        var runningIsTransition = false, newIsTransition = false;
        if (cc.TransitionScene) {
            runningIsTransition = this._runningScene ? this._runningScene instanceof cc.TransitionScene : false;
            newIsTransition = this._nextScene ? this._nextScene instanceof cc.TransitionScene : false;
        }

        // If it is not a transition, call onExit/cleanup
        if (!newIsTransition) {
            var locRunningScene = this._runningScene;
            if (locRunningScene) {
                locRunningScene.onExitTransitionDidStart();
                locRunningScene.onExit();
            }

            // issue #709. the root node (scene) should receive the cleanup message too
            // otherwise it might be leaked.
            if (this._sendCleanupToScene && locRunningScene)
                locRunningScene.cleanup();
        }

        this._runningScene = this._nextScene;
        cc.renderer.childrenOrderDirty = true;

        this._nextScene = null;
        if ((!runningIsTransition) && (this._runningScene !== null)) {
            this._runningScene.onEnter();
            this._runningScene.onEnterTransitionDidFinish();
        }
    },

    /**
     * Sets Notification Node
     * @param {cc.Node} node
     */
    setNotificationNode: function (node) {
        this._notificationNode = node;
    },

    /**
     * Returns the cc.director delegate.
     * @return {cc.DirectorDelegate}
     */
    getDelegate: function () {
        return this._projectionDelegate;
    },

    /**
     * Sets the cc.director delegate. It shall implement the CCDirectorDelegate protocol
     * @return {cc.DirectorDelegate}
     */
    setDelegate: function (delegate) {
        this._projectionDelegate = delegate;
    },

    /**
     * Sets the view, where everything is rendered, do not call this function.<br/>
     * Implementation can be found in CCDirectorCanvas.js/CCDirectorWebGL.js.
     * @function
     * @param {cc.view} openGLView
     */
    setOpenGLView: null,

    /**
     * Sets an OpenGL projection.<br/>
     * Implementation can be found in CCDirectorCanvas.js/CCDirectorWebGL.js.
     * @function
     * @param {Number} projection
     */
    setProjection: null,

    /**
     * Update the view port.<br/>
     * Implementation can be found in CCDirectorCanvas.js/CCDirectorWebGL.js.
     * @function
     */
    setViewport: null,

    /**
     * Get the CCEGLView, where everything is rendered.<br/>
     * Implementation can be found in CCDirectorCanvas.js/CCDirectorWebGL.js.
     * @function
     * @return {cc.view}
     */
    getOpenGLView: null,

    /**
     * Sets an OpenGL projection.<br/>
     * Implementation can be found in CCDirectorCanvas.js/CCDirectorWebGL.js.
     * @function
     * @return {Number}
     */
    getProjection: null,

    /**
     * Enables/disables OpenGL alpha blending.<br/>
     * Implementation can be found in CCDirectorCanvas.js/CCDirectorWebGL.js.
     * @function
     * @param {Boolean} on
     */
    setAlphaBlending: null,

    _showStats: function () {
        this._frames++;
        this._accumDt += this._deltaTime;
        if (this._FPSLabel && this._SPFLabel && this._drawsLabel) {
            if (this._accumDt > cc.DIRECTOR_FPS_INTERVAL) {
                this._SPFLabel.string = this._secondsPerFrame.toFixed(3);

                this._frameRate = this._frames / this._accumDt;
                this._frames = 0;
                this._accumDt = 0;

                this._FPSLabel.string = this._frameRate.toFixed(1);
                this._drawsLabel.string = (0 | cc.g_NumberOfDraws).toString();
            }
            this._FPSLabel.visit();
            this._SPFLabel.visit();
            this._drawsLabel.visit();
        } else
            this._createStatsLabel();
        cc.g_NumberOfDraws = 0;
    },

    /**
     * Returns whether or not the replaced scene will receive the cleanup message.<br>
     * If the new scene is pushed, then the old scene won't receive the "cleanup" message.<br/>
     * If the new scene replaces the old one, the it will receive the "cleanup" message.
     * @return {Boolean}
     */
    isSendCleanupToScene: function () {
        return this._sendCleanupToScene;
    },

    /**
     * Returns current running Scene. Director can only run one Scene at the time
     * @return {cc.Scene}
     */
    getRunningScene: function () {
        return this._runningScene;
    },

    /**
     * Returns the FPS value
     * @return {Number}
     */
    getAnimationInterval: function () {
        return this._animationInterval;
    },

    /**
     * Returns whether or not to display the FPS informations
     * @return {Boolean}
     */
    isDisplayStats: function () {
        return this._displayStats;
    },

    /**
     * Sets whether display the FPS on the bottom-left corner
     * @param {Boolean} displayStats
     */
    setDisplayStats: function (displayStats) {
        this._displayStats = displayStats;
    },

    /**
     * Returns seconds per frame
     * @return {Number}
     */
    getSecondsPerFrame: function () {
        return this._secondsPerFrame;
    },

    /**
     * Returns whether next delta time equals to zero
     * @return {Boolean}
     */
    isNextDeltaTimeZero: function () {
        return this._nextDeltaTimeZero;
    },

    /**
     * Returns whether or not the Director is paused
     * @return {Boolean}
     */
    isPaused: function () {
        return this._paused;
    },

    /**
     * Returns how many frames were called since the director started
     * @return {Number}
     */
    getTotalFrames: function () {
        return this._totalFrames;
    },

    /**
     * Pops out all scenes from the queue until the root scene in the queue. <br/>
     * This scene will replace the running one.  <br/>
     * Internally it will call "popToSceneStackLevel(1)"
     */
    popToRootScene: function () {
        this.popToSceneStackLevel(1);
    },

    /**
     * Pops out all scenes from the queue until it reaches "level".                             <br/>
     * If level is 0, it will end the director.                                                 <br/>
     * If level is 1, it will pop all scenes until it reaches to root scene.                    <br/>
     * If level is <= than the current stack level, it won't do anything.
     * @param {Number} level
     */
    popToSceneStackLevel: function (level) {
        cc.assert(this._runningScene, cc._LogInfos.Director_popToSceneStackLevel_2);

        var locScenesStack = this._scenesStack;
        var c = locScenesStack.length;

        if (c === 0) {
            this.end();
            return;
        }
        // current level or lower -> nothing
        if (level > c)
            return;

        // pop stack until reaching desired level
        while (c > level) {
            var current = locScenesStack.pop();
            if (current.running) {
                current.onExitTransitionDidStart();
                current.onExit();
            }
            current.cleanup();
            c--;
        }
        this._nextScene = locScenesStack[locScenesStack.length - 1];
        this._sendCleanupToScene = false;
    },

    /**
     * Returns the cc.Scheduler associated with this director
     * @return {cc.Scheduler}
     */
    getScheduler: function () {
        return this._scheduler;
    },

    /**
     * Sets the cc.Scheduler associated with this director
     * @param {cc.Scheduler} scheduler
     */
    setScheduler: function (scheduler) {
        if (this._scheduler !== scheduler) {
            this._scheduler = scheduler;
        }
    },

    /**
     * Returns the cc.ActionManager associated with this director
     * @return {cc.ActionManager}
     */
    getActionManager: function () {
        return this._actionManager;
    },
    /**
     * Sets the cc.ActionManager associated with this director
     * @param {cc.ActionManager} actionManager
     */
    setActionManager: function (actionManager) {
        if (this._actionManager !== actionManager) {
            this._actionManager = actionManager;
        }
    },

    /**
     * Returns the delta time since last frame
     * @return {Number}
     */
    getDeltaTime: function () {
        return this._deltaTime;
    },

    _createStatsLabel: null,

    _calculateMPF: function () {
        var now = Date.now();
        this._secondsPerFrame = (now - this._lastUpdate) / 1000;
    }
});

/**
 * The event projection changed of cc.Director
 * @constant
 * @type {string}
 * @example
 *   cc.eventManager.addCustomListener(cc.Director.EVENT_PROJECTION_CHANGED, function(event) {
 *           cc.log("Projection changed.");
 *       });
 */
cc.Director.EVENT_PROJECTION_CHANGED = "director_projection_changed";

/**
 * The event after draw of cc.Director
 * @constant
 * @type {string}
 * @example
 *   cc.eventManager.addCustomListener(cc.Director.EVENT_AFTER_DRAW, function(event) {
 *           cc.log("after draw event.");
 *       });
 */
cc.Director.EVENT_AFTER_DRAW = "director_after_draw";

/**
 * The event after visit of cc.Director
 * @constant
 * @type {string}
 * @example
 *   cc.eventManager.addCustomListener(cc.Director.EVENT_AFTER_VISIT, function(event) {
 *           cc.log("after visit event.");
 *       });
 */
cc.Director.EVENT_AFTER_VISIT = "director_after_visit";

/**
 * The event after update of cc.Director
 * @constant
 * @type {string}
 * @example
 *   cc.eventManager.addCustomListener(cc.Director.EVENT_AFTER_UPDATE, function(event) {
 *           cc.log("after update event.");
 *       });
 */
cc.Director.EVENT_AFTER_UPDATE = "director_after_update";

/***************************************************
 * implementation of DisplayLinkDirector
 **************************************************/
cc.DisplayLinkDirector = cc.Director.extend(/** @lends cc.Director# */{
    invalid: false,

    /**
     * Starts Animation
     */
    startAnimation: function () {
        this._nextDeltaTimeZero = true;
        this.invalid = false;
    },

    /**
     * Run main loop of director
     */
    mainLoop: function () {
        if (this._purgeDirectorInNextLoop) {
            this._purgeDirectorInNextLoop = false;
            this.purgeDirector();
        }
        else if (!this.invalid) {
            this.drawScene();
        }
    },

    /**
     * Stops animation
     */
    stopAnimation: function () {
        this.invalid = true;
    },

    /**
     * Sets animation interval
     * @param {Number} value the animation interval desired
     */
    setAnimationInterval: function (value) {
        this._animationInterval = value;
        if (!this.invalid) {
            this.stopAnimation();
            this.startAnimation();
        }
    }
});

cc.Director.sharedDirector = null;
cc.Director.firstUseDirector = true;

cc.Director._getInstance = function () {
    if (cc.Director.firstUseDirector) {
        cc.Director.firstUseDirector = false;
        cc.Director.sharedDirector = new cc.DisplayLinkDirector();
        cc.Director.sharedDirector.init();
    }
    return cc.Director.sharedDirector;
};

/**
 * Default fps is 60
 * @type {Number}
 */
cc.defaultFPS = 60;

//Possible OpenGL projections used by director
/**
 * Constant for 2D projection (orthogonal projection)
 * @constant
 * @type {Number}
 */
cc.Director.PROJECTION_2D = 0;

/**
 * Constant for 3D projection with a fovy=60, znear=0.5f and zfar=1500.
 * @constant
 * @type {Number}
 */
cc.Director.PROJECTION_3D = 1;

/**
 * Constant for custom projection, if cc.Director's projection set to it, it calls "updateProjection" on the projection delegate.
 * @constant
 * @type {Number}
 */
cc.Director.PROJECTION_CUSTOM = 3;

/**
 * Constant for default projection of cc.Director, default projection is 3D projection
 * @constant
 * @type {Number}
 */
cc.Director.PROJECTION_DEFAULT = cc.Director.PROJECTION_3D;

if (cc._renderType === cc._RENDER_TYPE_CANVAS) {

    var _p = cc.Director.prototype;

    _p.setProjection = function (projection) {
        this._projection = projection;
        cc.eventManager.dispatchEvent(this._eventProjectionChanged);
    };

    _p.setDepthTest = function () {
    };

    _p.setOpenGLView = function (openGLView) {
        // set size
        this._winSizeInPoints.width = cc._canvas.width;      //this._openGLView.getDesignResolutionSize();
        this._winSizeInPoints.height = cc._canvas.height;
        this._openGLView = openGLView || cc.view;
        if (cc.eventManager)
            cc.eventManager.setEnabled(true);
    };

    _p._clear = function () {
        var viewport = this._openGLView.getViewPortRect();
        var context = cc._renderContext.getContext();
        context.setTransform(1,0,0,1, 0, 0);
        context.clearRect(-viewport.x, viewport.y, viewport.width, viewport.height);
    };

    _p._createStatsLabel = function () {
        var _t = this;
        var fontSize = 0;
        if (_t._winSizeInPoints.width > _t._winSizeInPoints.height)
            fontSize = 0 | (_t._winSizeInPoints.height / 320 * 24);
        else
            fontSize = 0 | (_t._winSizeInPoints.width / 320 * 24);

        _t._FPSLabel = new cc.LabelTTF("000.0", "Arial", fontSize);
        _t._SPFLabel = new cc.LabelTTF("0.000", "Arial", fontSize);
        _t._drawsLabel = new cc.LabelTTF("0000", "Arial", fontSize);

        var locStatsPosition = cc.DIRECTOR_STATS_POSITION;
        _t._drawsLabel.setPosition(_t._drawsLabel.width / 2 + locStatsPosition.x, _t._drawsLabel.height * 5 / 2 + locStatsPosition.y);
        _t._SPFLabel.setPosition(_t._SPFLabel.width / 2 + locStatsPosition.x, _t._SPFLabel.height * 3 / 2 + locStatsPosition.y);
        _t._FPSLabel.setPosition(_t._FPSLabel.width / 2 + locStatsPosition.x, _t._FPSLabel.height / 2 + locStatsPosition.y);
    };

    _p.getVisibleSize = function () {
        //if (this._openGLView) {
        //return this._openGLView.getVisibleSize();
        //} else {
        return this.getWinSize();
        //}
    };

    _p.getVisibleOrigin = function () {
        //if (this._openGLView) {
        //return this._openGLView.getVisibleOrigin();
        //} else {
        return cc.p(0, 0);
        //}
    };
} else {
    cc.Director._fpsImage = new Image();
    cc._addEventListener(cc.Director._fpsImage, "load", function () {
        cc.Director._fpsImageLoaded = true;
    });
    if (cc._fpsImage) {
        cc.Director._fpsImage.src = cc._fpsImage;
    }
}