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

/**
 * tag for scene redial
 * @constant
 * @type Number
 */
cc.SCENE_RADIAL = 0xc001;

/**
 * cc.TransitionProgress transition.
 * @class
 * @extends cc.TransitionScene
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @example
 * var trans = new cc.TransitionProgress(time,scene);
 */
cc.TransitionProgress = cc.TransitionScene.extend(/** @lends cc.TransitionProgress# */{
    _to:0,
    _from:0,
    _sceneToBeModified:null,
    _className:"TransitionProgress",

    /**
     * @param {Number} t time
     * @param {cc.Scene} scene
     */
    ctor:function (t, scene) {
        cc.TransitionScene.prototype.ctor.call(this);
        scene && this.initWithDuration(t, scene);
    },

	_setAttrs: function(node, x, y) {
		node.attr({
			x: x,
			y: y,
			anchorX: 0.5,
			anchorY: 0.5
		});
	},

    /**
     * @override
     * custom on enter
     */
    onEnter:function () {
        cc.TransitionScene.prototype.onEnter.call(this);
        this._setupTransition();

        // create a transparent color layer
        // in which we are going to add our rendertextures
        var winSize = cc.director.getWinSize();

        // create the second render texture for outScene
        var texture = new cc.RenderTexture(winSize.width, winSize.height);
        texture.sprite.anchorX = 0.5;
	    texture.sprite.anchorY = 0.5;
        this._setAttrs(texture, winSize.width / 2, winSize.height / 2);

        // render outScene to its texturebuffer
        texture.clear(0, 0, 0, 1);
        texture.begin();
        this._sceneToBeModified.visit();
        texture.end();

        //    Since we've passed the outScene to the texture we don't need it.
        if (this._sceneToBeModified === this._outScene)
            this.hideOutShowIn();

        //    We need the texture in RenderTexture.
        var pNode = this._progressTimerNodeWithRenderTexture(texture);

        // create the blend action
        var layerAction = cc.sequence(
            cc.progressFromTo(this._duration, this._from, this._to),
            cc.callFunc(this.finish, this));
        // run the blend action
        pNode.runAction(layerAction);

        // add the layer (which contains our two rendertextures) to the scene
        this.addChild(pNode, 2, cc.SCENE_RADIAL);
    },

    /**
     * @override
     * custom on exit
     */
    onExit:function () {
        // remove our layer and release all containing objects
        this.removeChildByTag(cc.SCENE_RADIAL, true);
        cc.TransitionScene.prototype.onExit.call(this);
    },

    _setupTransition:function () {
        this._sceneToBeModified = this._outScene;
        this._from = 100;
        this._to = 0;
    },

    _progressTimerNodeWithRenderTexture:function (texture) {
        cc.log("cc.TransitionProgress._progressTimerNodeWithRenderTexture(): should be overridden in subclass");
        return null;
    },

    _sceneOrder:function () {
        this._isInSceneOnTop = false;
    }
});

/**
 * create a cc.TransitionProgress object
 * @deprecated since v3.0,please use new cc.TransitionProgress(t, scene) instead.
 * @function
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @return {cc.TransitionProgress}
 */
cc.TransitionProgress.create = function (t, scene) {
    return new cc.TransitionProgress(t, scene);
};

/**
 *  cc.TransitionRadialCCW transition.<br/>
 *  A counter clock-wise radial transition to the next scene
 * @class
 * @extends cc.TransitionProgress
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @example
 * var trans = new cc.TransitionProgressRadialCCW(t, scene);
 */
cc.TransitionProgressRadialCCW = cc.TransitionProgress.extend(/** @lends cc.TransitionProgressRadialCCW# */{

    /**
     * @param {Number} t time
     * @param {cc.Scene} scene
     */
    ctor:function (t, scene) {
        cc.TransitionProgress.prototype.ctor.call(this);
        scene && this.initWithDuration(t, scene);
    },

    _progressTimerNodeWithRenderTexture:function (texture) {
        var size = cc.director.getWinSize();

        var pNode = new cc.ProgressTimer(texture.sprite);

        // but it is flipped upside down so we flip the sprite
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            pNode.sprite.flippedY = true;
        pNode.type = cc.ProgressTimer.TYPE_RADIAL;

        //    Return the radial type that we want to use
        pNode.reverseDir = false;
        pNode.percentage = 100;
        this._setAttrs(pNode, size.width / 2, size.height / 2);

        return pNode;
    }
});

/**
 * create a cc.TransitionProgressRadialCCW object
 * @deprecated since v3.0,please use new cc.TransitionProgressRadialCCW(t, scene) instead.
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @return {cc.TransitionProgressRadialCCW}
 * @example
 * var trans = new cc.TransitionProgressRadialCCW(time,scene);
 */
cc.TransitionProgressRadialCCW.create = function (t, scene) {
    return new cc.TransitionProgressRadialCCW(t, scene);
};

/**
 * cc.TransitionRadialCW transition.<br/>
 * A counter colock-wise radial transition to the next scene
 * @class
 * @extends cc.TransitionProgress
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @example
 * var trans = new cc.TransitionProgressRadialCW(t, scene);
 */
cc.TransitionProgressRadialCW = cc.TransitionProgress.extend(/** @lends cc.TransitionProgressRadialCW# */{
    /**
     * @param {Number} t time
     * @param {cc.Scene} scene
     */
    ctor:function (t, scene) {
        cc.TransitionProgress.prototype.ctor.call(this);
        scene && this.initWithDuration(t, scene);
    },

    _progressTimerNodeWithRenderTexture:function (texture) {
        var size = cc.director.getWinSize();

        var pNode = new cc.ProgressTimer(texture.sprite);

        // but it is flipped upside down so we flip the sprite
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            pNode.sprite.flippedY = true;
        pNode.type = cc.ProgressTimer.TYPE_RADIAL;

        //    Return the radial type that we want to use
        pNode.reverseDir = true;
        pNode.percentage = 100;
        this._setAttrs(pNode, size.width / 2, size.height / 2);

        return pNode;
    }
});

/**
 * create a cc.TransitionProgressRadialCW object
 * @deprecated since v3.0,please use cc.TransitionProgressRadialCW(t, scene) instead.
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @return {cc.TransitionProgressRadialCW}
 */
cc.TransitionProgressRadialCW.create = function (t, scene) {
    var tempScene = new cc.TransitionProgressRadialCW();
    if ((tempScene !== null) && (tempScene.initWithDuration(t, scene))) {
        return tempScene;
    }
    return new cc.TransitionProgressRadialCW(t, scene);
};

/**
 * cc.TransitionProgressHorizontal transition.<br/>
 * A  colock-wise radial transition to the next scene
 * @class
 * @extends cc.TransitionProgress
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @example
 * var trans = new cc.TransitionProgressHorizontal(t, scene);
 */
cc.TransitionProgressHorizontal = cc.TransitionProgress.extend(/** @lends cc.TransitionProgressHorizontal# */{
    /**
     * @param {Number} t time
     * @param {cc.Scene} scene
     */
    ctor:function (t, scene) {
        cc.TransitionProgress.prototype.ctor.call(this);
        scene && this.initWithDuration(t, scene);
    },

    _progressTimerNodeWithRenderTexture:function (texture) {
        var size = cc.director.getWinSize();

        var pNode = new cc.ProgressTimer(texture.sprite);

        // but it is flipped upside down so we flip the sprite
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            pNode.sprite.flippedY = true;
        pNode.type = cc.ProgressTimer.TYPE_BAR;

        pNode.midPoint = cc.p(1, 0);
        pNode.barChangeRate = cc.p(1, 0);

        pNode.percentage = 100;
        this._setAttrs(pNode, size.width / 2, size.height / 2);

        return pNode;
    }
});

/**
 * create a cc.TransitionProgressHorizontal object
 * @deprecated since v3.0,please use new cc.TransitionProgressHorizontal(t, scene) instead.
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @return {cc.TransitionProgressHorizontal}
 */
cc.TransitionProgressHorizontal.create = function (t, scene) {
    return new cc.TransitionProgressHorizontal(t, scene);
};

/**
 * cc.TransitionProgressVertical transition.
 * @class
 * @extends cc.TransitionProgress
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @example
 * var trans = new cc.TransitionProgressVertical(t, scene);
 */
cc.TransitionProgressVertical = cc.TransitionProgress.extend(/** @lends cc.TransitionProgressVertical# */{

    /**
     * @param {Number} t time
     * @param {cc.Scene} scene
     */
    ctor:function (t, scene) {
        cc.TransitionProgress.prototype.ctor.call(this);
        scene && this.initWithDuration(t, scene);
    },

    _progressTimerNodeWithRenderTexture:function (texture) {
        var size = cc.director.getWinSize();

        var pNode = new cc.ProgressTimer(texture.sprite);

        // but it is flipped upside down so we flip the sprite
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            pNode.sprite.flippedY = true;
        pNode.type = cc.ProgressTimer.TYPE_BAR;

        pNode.midPoint = cc.p(0, 0);
        pNode.barChangeRate = cc.p(0, 1);

        pNode.percentage = 100;
        this._setAttrs(pNode, size.width / 2, size.height / 2);

        return pNode;
    }
});

/**
 * create a cc.TransitionProgressVertical object
 * @deprecated since v3.0,please use new cc.TransitionProgressVertical(t, scene) instead.
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @return {cc.TransitionProgressVertical}
 */
cc.TransitionProgressVertical.create = function (t, scene) {
    return new cc.TransitionProgressVertical(t, scene);
};

/**
 * cc.TransitionProgressInOut transition.
 * @class
 * @extends cc.TransitionProgress
 */
cc.TransitionProgressInOut = cc.TransitionProgress.extend(/** @lends cc.TransitionProgressInOut# */{

    /**
     * The constructor of cc.TransitionProgressInOut. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {Number} t time
     * @param {cc.Scene} scene
     */
    ctor:function (t, scene) {
        cc.TransitionProgress.prototype.ctor.call(this);
        scene && this.initWithDuration(t, scene);
    },

    _progressTimerNodeWithRenderTexture:function (texture) {
        var size = cc.director.getWinSize();
        var pNode = new cc.ProgressTimer(texture.sprite);

        // but it is flipped upside down so we flip the sprite
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            pNode.sprite.flippedY = true;
        pNode.type = cc.ProgressTimer.TYPE_BAR;

        pNode.midPoint = cc.p(0.5, 0.5);
        pNode.barChangeRate = cc.p(1, 1);

        pNode.percentage = 0;
        this._setAttrs(pNode, size.width / 2, size.height / 2);

        return pNode;
    },
    _sceneOrder:function () {
        this._isInSceneOnTop = false;
    },
    _setupTransition:function () {
        this._sceneToBeModified = this._inScene;
        this._from = 0;
        this._to = 100;
    }
});

/**
 * create a cc.TransitionProgressInOut object
 * @function
 * @deprecated
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @return {cc.TransitionProgressInOut}
 */
cc.TransitionProgressInOut.create = function (t, scene) {
    return new cc.TransitionProgressInOut(t, scene);
};

/**
 * cc.TransitionProgressOutIn transition.
 * @class
 * @extends cc.TransitionProgress
 */
cc.TransitionProgressOutIn = cc.TransitionProgress.extend(/** @lends cc.TransitionProgressOutIn# */{

    /**
     * The constructor of cc.TransitionProgressOutIn. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {Number} t time
     * @param {cc.Scene} scene
     */
    ctor:function (t, scene) {
        cc.TransitionProgress.prototype.ctor.call(this);
        scene && this.initWithDuration(t, scene);
    },
    
    _progressTimerNodeWithRenderTexture:function (texture) {
        var size = cc.director.getWinSize();
        var pNode = new cc.ProgressTimer(texture.sprite);

        // but it is flipped upside down so we flip the sprite
        if (cc._renderType === cc._RENDER_TYPE_WEBGL)
            pNode.sprite.flippedY = true;
        pNode.type = cc.ProgressTimer.TYPE_BAR;

        pNode.midPoint = cc.p(0.5, 0.5);
        pNode.barChangeRate = cc.p(1, 1);

        pNode.percentage = 100;
        this._setAttrs(pNode, size.width / 2, size.height / 2);

        return pNode;
    }
});

/**
 * create a cc.TransitionProgressOutIn object
 * @function
 * @deprecated
 * @param {Number} t time
 * @param {cc.Scene} scene
 * @return {cc.TransitionProgressOutIn}
 */
cc.TransitionProgressOutIn.create = function (t, scene) {
    return new cc.TransitionProgressOutIn(t, scene);
};
