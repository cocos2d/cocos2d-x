/****************************************************************************
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

cc._LogInfos = {
    ActionManager_addAction: "cc.ActionManager.addAction(): action must be non-null",
    ActionManager_removeAction: "cocos2d: removeAction: Target not found",
    ActionManager_removeActionByTag: "cc.ActionManager.removeActionByTag(): an invalid tag",
    ActionManager_removeActionByTag_2: "cc.ActionManager.removeActionByTag(): target must be non-null",
    ActionManager_getActionByTag: "cc.ActionManager.getActionByTag(): an invalid tag",
    ActionManager_getActionByTag_2: "cocos2d : getActionByTag(tag = %s): Action not found",

    configuration_dumpInfo: "cocos2d: **** WARNING **** CC_ENABLE_PROFILERS is defined. Disable it when you finish profiling (from ccConfig.js)",
    configuration_loadConfigFile: "Expected 'data' dict, but not found. Config file: %s",
    configuration_loadConfigFile_2: "Please load the resource first : %s",

    Director_resume: "cocos2d: Director: Error in gettimeofday",
    Director_setProjection: "cocos2d: Director: unrecognized projection",
    Director_popToSceneStackLevel: "cocos2d: Director: unrecognized projection",
    Director_popToSceneStackLevel_2: "cocos2d: Director: Error in gettimeofday",
    Director_popScene: "running scene should not null",
    Director_pushScene: "the scene should not null",

    arrayVerifyType: "element type is wrong!",

    Scheduler_scheduleCallbackForTarget: "CCSheduler#scheduleCallback. Callback already scheduled. Updating interval from:%s to %s",
    Scheduler_scheduleCallbackForTarget_2: "cc.scheduler.scheduleCallbackForTarget(): callback_fn should be non-null.",
    Scheduler_scheduleCallbackForTarget_3: "cc.scheduler.scheduleCallbackForTarget(): target should be non-null.",
    Scheduler_pauseTarget: "cc.Scheduler.pauseTarget():target should be non-null",
    Scheduler_resumeTarget: "cc.Scheduler.resumeTarget():target should be non-null",
    Scheduler_isTargetPaused: "cc.Scheduler.isTargetPaused():target should be non-null",

    Node_getZOrder: "getZOrder is deprecated. Please use getLocalZOrder instead.",
    Node_setZOrder: "setZOrder is deprecated. Please use setLocalZOrder instead.",
    Node_getRotation: "RotationX != RotationY. Don't know which one to return",
    Node_getScale: "ScaleX != ScaleY. Don't know which one to return",
    Node_addChild: "An Node can't be added as a child of itself.",
    Node_addChild_2: "child already added. It can't be added again",
    Node_addChild_3: "child must be non-null",
    Node_removeFromParentAndCleanup: "removeFromParentAndCleanup is deprecated. Use removeFromParent instead",
    Node_boundingBox: "boundingBox is deprecated. Use getBoundingBox instead",
    Node_removeChildByTag: "argument tag is an invalid tag",
    Node_removeChildByTag_2: "cocos2d: removeChildByTag(tag = %s): child not found!",
    Node_removeAllChildrenWithCleanup: "removeAllChildrenWithCleanup is deprecated. Use removeAllChildren instead",
    Node_stopActionByTag: "cc.Node.stopActionBy(): argument tag an invalid tag",
    Node_getActionByTag: "cc.Node.getActionByTag(): argument tag is an invalid tag",
    Node_resumeSchedulerAndActions: "resumeSchedulerAndActions is deprecated, please use resume instead.",
    Node_pauseSchedulerAndActions: "pauseSchedulerAndActions is deprecated, please use pause instead.",
    Node__arrayMakeObjectsPerformSelector: "Unknown callback function",
    Node_reorderChild: "child must be non-null",
    Node_runAction: "cc.Node.runAction(): action must be non-null",
    Node_schedule: "callback function must be non-null",
    Node_schedule_2: "interval must be positive",
    Node_initWithTexture: "cocos2d: Could not initialize cc.AtlasNode. Invalid Texture.",

    AtlasNode_updateAtlasValues: "cc.AtlasNode.updateAtlasValues(): Shall be overridden in subclasses",
    AtlasNode_initWithTileFile: "",
    AtlasNode__initWithTexture: "cocos2d: Could not initialize cc.AtlasNode. Invalid Texture.",

    _EventListenerKeyboard_checkAvailable: "cc._EventListenerKeyboard.checkAvailable(): Invalid EventListenerKeyboard!",
    _EventListenerTouchOneByOne_checkAvailable: "cc._EventListenerTouchOneByOne.checkAvailable(): Invalid EventListenerTouchOneByOne!",
    _EventListenerTouchAllAtOnce_checkAvailable: "cc._EventListenerTouchAllAtOnce.checkAvailable(): Invalid EventListenerTouchAllAtOnce!",
    _EventListenerAcceleration_checkAvailable: "cc._EventListenerAcceleration.checkAvailable(): _onAccelerationEvent must be non-nil",

    EventListener_create: "Invalid parameter.",

    __getListenerID: "Don't call this method if the event is for touch.",

    eventManager__forceAddEventListener: "Invalid scene graph priority!",
    eventManager_addListener: "0 priority is forbidden for fixed priority since it's used for scene graph based priority.",
    eventManager_removeListeners: "Invalid listener type!",
    eventManager_setPriority: "Can't set fixed priority with scene graph based listener.",
    eventManager_addListener_2: "Invalid parameters.",
    eventManager_addListener_3: "listener must be a cc.EventListener object when adding a fixed priority listener",
    eventManager_addListener_4: "The listener has been registered, please don't register it again.",

    LayerMultiplex_initWithLayers: "parameters should not be ending with null in Javascript",
    LayerMultiplex_switchTo: "Invalid index in MultiplexLayer switchTo message",
    LayerMultiplex_switchToAndReleaseMe: "Invalid index in MultiplexLayer switchTo message",
    LayerMultiplex_addLayer: "cc.Layer.addLayer(): layer should be non-null",

    EGLView_setDesignResolutionSize: "Resolution not valid",
    EGLView_setDesignResolutionSize_2: "should set resolutionPolicy",

    inputManager_handleTouchesBegin: "The touches is more than MAX_TOUCHES, nUnusedIndex = %s",

    swap: "cc.swap is being modified from original macro, please check usage",
    checkGLErrorDebug: "WebGL error %s",

    animationCache__addAnimationsWithDictionary: "cocos2d: cc.AnimationCache: No animations were found in provided dictionary.",
    animationCache__addAnimationsWithDictionary_2: "cc.AnimationCache. Invalid animation format",
    animationCache_addAnimations: "cc.AnimationCache.addAnimations(): File could not be found",
    animationCache__parseVersion1: "cocos2d: cc.AnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.",
    animationCache__parseVersion1_2: "cocos2d: cc.AnimationCache: Animation '%s' refers to frame '%s' which is not currently in the cc.SpriteFrameCache. This frame will not be added to the animation.",
    animationCache__parseVersion1_3: "cocos2d: cc.AnimationCache: None of the frames for animation '%s' were found in the cc.SpriteFrameCache. Animation is not being added to the Animation Cache.",
    animationCache__parseVersion1_4: "cocos2d: cc.AnimationCache: An animation in your dictionary refers to a frame which is not in the cc.SpriteFrameCache. Some or all of the frames for the animation '%s' may be missing.",
    animationCache__parseVersion2: "cocos2d: CCAnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.",
    animationCache__parseVersion2_2: "cocos2d: cc.AnimationCache: Animation '%s' refers to frame '%s' which is not currently in the cc.SpriteFrameCache. This frame will not be added to the animation.",
    animationCache_addAnimations_2: "cc.AnimationCache.addAnimations(): Invalid texture file name",

    Sprite_reorderChild: "cc.Sprite.reorderChild(): this child is not in children list",
    Sprite_ignoreAnchorPointForPosition: "cc.Sprite.ignoreAnchorPointForPosition(): it is invalid in cc.Sprite when using SpriteBatchNode",
    Sprite_setDisplayFrameWithAnimationName: "cc.Sprite.setDisplayFrameWithAnimationName(): Frame not found",
    Sprite_setDisplayFrameWithAnimationName_2: "cc.Sprite.setDisplayFrameWithAnimationName(): Invalid frame index",
    Sprite_setDisplayFrame: "setDisplayFrame is deprecated, please use setSpriteFrame instead.",
    Sprite__updateBlendFunc: "cc.Sprite._updateBlendFunc(): _updateBlendFunc doesn't work when the sprite is rendered using a cc.CCSpriteBatchNode",
    Sprite_initWithSpriteFrame: "cc.Sprite.initWithSpriteFrame(): spriteFrame should be non-null",
    Sprite_initWithSpriteFrameName: "cc.Sprite.initWithSpriteFrameName(): spriteFrameName should be non-null",
    Sprite_initWithSpriteFrameName1: " is null, please check.",
    Sprite_initWithFile: "cc.Sprite.initWithFile(): filename should be non-null",
    Sprite_setDisplayFrameWithAnimationName_3: "cc.Sprite.setDisplayFrameWithAnimationName(): animationName must be non-null",
    Sprite_reorderChild_2: "cc.Sprite.reorderChild(): child should be non-null",
    Sprite_addChild: "cc.Sprite.addChild(): cc.Sprite only supports cc.Sprites as children when using cc.SpriteBatchNode",
    Sprite_addChild_2: "cc.Sprite.addChild(): cc.Sprite only supports a sprite using same texture as children when using cc.SpriteBatchNode",
    Sprite_addChild_3: "cc.Sprite.addChild(): child should be non-null",
    Sprite_setTexture: "cc.Sprite.texture setter: Batched sprites should use the same texture as the batchnode",
    Sprite_updateQuadFromSprite: "cc.SpriteBatchNode.updateQuadFromSprite(): cc.SpriteBatchNode only supports cc.Sprites as children",
    Sprite_insertQuadFromSprite: "cc.SpriteBatchNode.insertQuadFromSprite(): cc.SpriteBatchNode only supports cc.Sprites as children",
    Sprite_addChild_4: "cc.SpriteBatchNode.addChild(): cc.SpriteBatchNode only supports cc.Sprites as children",
    Sprite_addChild_5: "cc.SpriteBatchNode.addChild(): cc.Sprite is not using the same texture",
    Sprite_initWithTexture: "Sprite.initWithTexture(): Argument must be non-nil ",
    Sprite_setSpriteFrame: "Invalid spriteFrameName",
    Sprite_setTexture_2: "Invalid argument: cc.Sprite.texture setter expects a CCTexture2D.",
    Sprite_updateQuadFromSprite_2: "cc.SpriteBatchNode.updateQuadFromSprite(): sprite should be non-null",
    Sprite_insertQuadFromSprite_2: "cc.SpriteBatchNode.insertQuadFromSprite(): sprite should be non-null",

    SpriteBatchNode_addSpriteWithoutQuad: "cc.SpriteBatchNode.addQuadFromSprite(): SpriteBatchNode only supports cc.Sprites as children",
    SpriteBatchNode_increaseAtlasCapacity: "cocos2d: CCSpriteBatchNode: resizing TextureAtlas capacity from %s to %s.",
    SpriteBatchNode_increaseAtlasCapacity_2: "cocos2d: WARNING: Not enough memory to resize the atlas",
    SpriteBatchNode_reorderChild: "cc.SpriteBatchNode.addChild(): Child doesn't belong to Sprite",
    SpriteBatchNode_removeChild: "cc.SpriteBatchNode.addChild(): sprite batch node should contain the child",
    SpriteBatchNode_addSpriteWithoutQuad_2: "cc.SpriteBatchNode.addQuadFromSprite(): child should be non-null",
    SpriteBatchNode_reorderChild_2: "cc.SpriteBatchNode.addChild(): child should be non-null",

    spriteFrameCache__getFrameConfig: "cocos2d: WARNING: originalWidth/Height not found on the cc.SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist",
    spriteFrameCache_addSpriteFrames: "cocos2d: WARNING: an alias with name %s already exists",
    spriteFrameCache__checkConflict: "cocos2d: WARNING: Sprite frame: %s has already been added by another source, please fix name conflit",
    spriteFrameCache_getSpriteFrame: "cocos2d: cc.SpriteFrameCahce: Frame %s not found",
    spriteFrameCache__getFrameConfig_2: "Please load the resource first : %s",
    spriteFrameCache_addSpriteFrames_2: "cc.SpriteFrameCache.addSpriteFrames(): plist should be non-null",
    spriteFrameCache_addSpriteFrames_3: "Argument must be non-nil",

    CCSpriteBatchNode_updateQuadFromSprite: "cc.SpriteBatchNode.updateQuadFromSprite(): cc.SpriteBatchNode only supports cc.Sprites as children",
    CCSpriteBatchNode_insertQuadFromSprite: "cc.SpriteBatchNode.insertQuadFromSprite(): cc.SpriteBatchNode only supports cc.Sprites as children",
    CCSpriteBatchNode_addChild: "cc.SpriteBatchNode.addChild(): cc.SpriteBatchNode only supports cc.Sprites as children",
    CCSpriteBatchNode_initWithTexture: "Sprite.initWithTexture(): Argument must be non-nil ",
    CCSpriteBatchNode_addChild_2: "cc.Sprite.addChild(): child should be non-null",
    CCSpriteBatchNode_setSpriteFrame: "Invalid spriteFrameName",
    CCSpriteBatchNode_setTexture: "Invalid argument: cc.Sprite texture setter expects a CCTexture2D.",
    CCSpriteBatchNode_updateQuadFromSprite_2: "cc.SpriteBatchNode.updateQuadFromSprite(): sprite should be non-null",
    CCSpriteBatchNode_insertQuadFromSprite_2: "cc.SpriteBatchNode.insertQuadFromSprite(): sprite should be non-null",
    CCSpriteBatchNode_addChild_3: "cc.SpriteBatchNode.addChild(): child should be non-null",

    TextureAtlas_initWithFile: "cocos2d: Could not open file: %s",
    TextureAtlas_insertQuad: "cc.TextureAtlas.insertQuad(): invalid totalQuads",
    TextureAtlas_initWithTexture: "cc.TextureAtlas.initWithTexture():texture should be non-null",
    TextureAtlas_updateQuad: "cc.TextureAtlas.updateQuad(): quad should be non-null",
    TextureAtlas_updateQuad_2: "cc.TextureAtlas.updateQuad(): Invalid index",
    TextureAtlas_insertQuad_2: "cc.TextureAtlas.insertQuad(): Invalid index",
    TextureAtlas_insertQuads: "cc.TextureAtlas.insertQuad(): Invalid index + amount",
    TextureAtlas_insertQuadFromIndex: "cc.TextureAtlas.insertQuadFromIndex(): Invalid newIndex",
    TextureAtlas_insertQuadFromIndex_2: "cc.TextureAtlas.insertQuadFromIndex(): Invalid fromIndex",
    TextureAtlas_removeQuadAtIndex: "cc.TextureAtlas.removeQuadAtIndex(): Invalid index",
    TextureAtlas_removeQuadsAtIndex: "cc.TextureAtlas.removeQuadsAtIndex(): index + amount out of bounds",
    TextureAtlas_moveQuadsFromIndex: "cc.TextureAtlas.moveQuadsFromIndex(): move is out of bounds",
    TextureAtlas_moveQuadsFromIndex_2: "cc.TextureAtlas.moveQuadsFromIndex(): Invalid newIndex",
    TextureAtlas_moveQuadsFromIndex_3: "cc.TextureAtlas.moveQuadsFromIndex(): Invalid oldIndex",

    textureCache_addPVRTCImage: "TextureCache:addPVRTCImage does not support on HTML5",
    textureCache_addETCImage: "TextureCache:addPVRTCImage does not support on HTML5",
    textureCache_textureForKey: "textureForKey is deprecated. Please use getTextureForKey instead.",
    textureCache_addPVRImage: "addPVRImage does not support on HTML5",
    textureCache_addUIImage: "cocos2d: Couldn't add UIImage in TextureCache",
    textureCache_dumpCachedTextureInfo: "cocos2d: '%s' id=%s %s x %s",
    textureCache_dumpCachedTextureInfo_2: "cocos2d: '%s' id= HTMLCanvasElement %s x %s",
    textureCache_dumpCachedTextureInfo_3: "cocos2d: TextureCache dumpDebugInfo: %s textures, HTMLCanvasElement for %s KB (%s MB)",
    textureCache_addUIImage_2: "cc.Texture.addUIImage(): image should be non-null",

    Texture2D_initWithETCFile: "initWithETCFile does not support on HTML5",
    Texture2D_initWithPVRFile: "initWithPVRFile does not support on HTML5",
    Texture2D_initWithPVRTCData: "initWithPVRTCData does not support on HTML5",
    Texture2D_addImage: "cc.Texture.addImage(): path should be non-null",
    Texture2D_initWithImage: "cocos2d: cc.Texture2D. Can't create Texture. UIImage is nil",
    Texture2D_initWithImage_2: "cocos2d: WARNING: Image (%s x %s) is bigger than the supported %s x %s",
    Texture2D_initWithString: "initWithString isn't supported on cocos2d-html5",
    Texture2D_initWithETCFile_2: "initWithETCFile does not support on HTML5",
    Texture2D_initWithPVRFile_2: "initWithPVRFile does not support on HTML5",
    Texture2D_initWithPVRTCData_2: "initWithPVRTCData does not support on HTML5",
    Texture2D_bitsPerPixelForFormat: "bitsPerPixelForFormat: %s, cannot give useful result, it's a illegal pixel format",
    Texture2D__initPremultipliedATextureWithImage: "cocos2d: cc.Texture2D: Using RGB565 texture since image has no alpha",
    Texture2D_addImage_2: "cc.Texture.addImage(): path should be non-null",
    Texture2D_initWithData: "NSInternalInconsistencyException",

    MissingFile: "Missing file: %s",
    radiansToDegress: "cc.radiansToDegress() should be called cc.radiansToDegrees()",
    RectWidth: "Rect width exceeds maximum margin: %s",
    RectHeight: "Rect height exceeds maximum margin: %s",

    EventManager__updateListeners: "If program goes here, there should be event in dispatch.",
    EventManager__updateListeners_2: "_inDispatch should be 1 here."
};

//+++++++++++++++++++++++++something about log start++++++++++++++++++++++++++++
cc._logToWebPage = function (msg) {
    if (!cc._canvas)
        return;

    var logList = cc._logList;
    var doc = document;
    if (!logList) {
        var logDiv = doc.createElement("Div");
        var logDivStyle = logDiv.style;

        logDiv.setAttribute("id", "logInfoDiv");
        cc._canvas.parentNode.appendChild(logDiv);
        logDiv.setAttribute("width", "200");
        logDiv.setAttribute("height", cc._canvas.height);
        logDivStyle.zIndex = "99999";
        logDivStyle.position = "absolute";
        logDivStyle.top = "0";
        logDivStyle.left = "0";

        logList = cc._logList = doc.createElement("textarea");
        var logListStyle = logList.style;

        logList.setAttribute("rows", "20");
        logList.setAttribute("cols", "30");
        logList.setAttribute("disabled", true);
        logDiv.appendChild(logList);
        logListStyle.backgroundColor = "transparent";
        logListStyle.borderBottom = "1px solid #cccccc";
        logListStyle.borderRightWidth = "0px";
        logListStyle.borderLeftWidth = "0px";
        logListStyle.borderTopWidth = "0px";
        logListStyle.borderTopStyle = "none";
        logListStyle.borderRightStyle = "none";
        logListStyle.borderLeftStyle = "none";
        logListStyle.padding = "0px";
        logListStyle.margin = 0;

    }
    logList.value = logList.value + msg + "\r\n";
    logList.scrollTop = logList.scrollHeight;
};

//to make sure the cc.log, cc.warn, cc.error and cc.assert would not throw error before init by debugger mode.
cc._formatString = function (arg) {
    if (cc.isObject(arg)) {
        try {
            return JSON.stringify(arg);
        } catch (err) {
            return "";
        }
    } else
        return arg;
};
/**
 * Init Debug setting.
 * @function
 * @param {Number} mode
 */
cc._initDebugSetting = function (mode) {
    var ccGame = cc.game;
    if(mode === ccGame.DEBUG_MODE_NONE)
        return;

    var locLog;
    if(mode > ccGame.DEBUG_MODE_ERROR){
        //log to web page
        locLog = cc._logToWebPage.bind(cc);
        cc.error = function(){
            locLog("ERROR :  " + cc.formatStr.apply(cc, arguments));
        };
        cc.assert = function(cond, msg) {
            if (!cond && msg) {
                for (var i = 2; i < arguments.length; i++)
                    msg = msg.replace(/(%s)|(%d)/, cc._formatString(arguments[i]));
                locLog("Assert: " + msg);
            }
        };
        if(mode !== ccGame.DEBUG_MODE_ERROR_FOR_WEB_PAGE){
            cc.warn = function(){
                locLog("WARN :  " + cc.formatStr.apply(cc, arguments));
            };
        }
        if(mode === ccGame.DEBUG_MODE_INFO_FOR_WEB_PAGE){
            cc.log = function(){
                locLog(cc.formatStr.apply(cc, arguments));
            };
        }
    } else if(console && console.log.apply){//console is null when user doesn't open dev tool on IE9
        //log to console

        cc.error = function(){
            return console.error.apply(console, arguments);
        };
        cc.assert = function (cond, msg) {
            if (!cond && msg) {
                for (var i = 2; i < arguments.length; i++)
                    msg = msg.replace(/(%s)|(%d)/, cc._formatString(arguments[i]));
                throw msg;
            }
        };
        if(mode !== ccGame.DEBUG_MODE_ERROR)
            cc.warn = function(){
                return console.warn.apply(console, arguments);
            };
        if(mode === ccGame.DEBUG_MODE_INFO)
            cc.log = function(){
                return console.log.apply(console, arguments);
            };
    }
};
cc._initDebugSetting(cc.game.config[cc.game.CONFIG_KEY.debugMode]);
//+++++++++++++++++++++++++something about log end+++++++++++++++++++++++++++++