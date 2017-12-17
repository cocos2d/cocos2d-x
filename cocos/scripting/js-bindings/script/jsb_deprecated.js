/*
 * Copyright (c) 2013-2017 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Deprecated functions

var cc = cc || {};

(function() {

    var logW = function(old_name, new_name) {
        cc.log("\n********** \n"+old_name +" was deprecated, please use "+ new_name +" instead.\n**********");
    };

    // Deprecated static functions
    cc.AnimationCache.purgeSharedAnimationCache = function() {
        logW("cc.AnimationCache.purgeSharedAnimationCache", "cc.AnimationCache.destroyInstance");
        cc.AnimationCache.destroyInstance();
    };

    cc.TextureCache.getInstance = function() {
        return cc.Director.getInstance().getTextureCache();
    };

    // Deprecated member functions
    cc.Action.prototype.copy = function() {
        logW("cc.Action.copy", "cc.Action.clone");
        return cc.Action.prototype.clone.apply(this, arguments);
    };

    cc.Animation.prototype.copy = function() {
        logW("cc.Animation.copy", "cc.Animation.clone");
        return cc.Animation.prototype.clone.apply(this, arguments);
    };

    cc.Node.prototype.nodeToWorldTransform = function() {
        logW("cc.Node.nodeToWorldTransform", "cc.Node.getNodeToWorldTransform");
        return cc.Node.prototype.getNodeToWorldTransform.apply(this, arguments);
    };

    cc.Node.prototype.getZOrder = function() {
        logW("cc.Node.getZOrder", "cc.Node.getLocalZOrder");
        return cc.Node.prototype.getLocalZOrder.apply(this, arguments);
    };

    cc.Node.prototype.setZOrder = function() {
        logW("cc.Node.setZOrder", "cc.Node.setLocalZOrder");
        cc.Node.prototype.setLocalZOrder.apply(this, arguments);
    };

    // Not deprecated in the web engine yet, so no need to log
    cc.Node.prototype.ignoreAnchorPointForPosition = cc.Node.prototype.setIgnoreAnchorPointForPosition;

    cc.Node.prototype.nodeToParentTransform = function() {
        logW("cc.Node.nodeToParentTransform", "cc.Node.getNodeToParentTransform");
        return cc.Node.prototype.getNodeToParentTransform.apply(this, arguments);
    };

    cc.Node.prototype.worldToNodeTransform = function() {
        logW("cc.Node.worldToNodeTransform", "cc.Node.getWorldToNodeTransform");
        return cc.Node.prototype.getWorldToNodeTransform.apply(this, arguments);
    };

    cc.Node.prototype.parentToNodeTransform = function() {
        logW("cc.Node.parentToNodeTransform", "cc.Node.getParentToNodeTransform");
        return cc.Node.prototype.getParentToNodeTransform.apply(this, arguments);
    };
    
    cc.Node.prototype.numberOfRunningActions = function() {
        logW("cc.Node.numberOfRunningActions", "cc.Node.getNumberOfRunningActions");
        return cc.Node.prototype.getNumberOfRunningActions.apply(this, arguments);
    };

    cc.Node.prototype.numberOfRunningActionsInTarget = function() {
        logW("cc.Node.numberOfRunningActionsInTarget", "cc.Node.getNumberOfRunningActionsInTarget");
        return cc.Node.prototype.getNumberOfRunningActionsInTarget.apply(this, arguments);
    };

    cc.Menu.prototype.setHandlerPriority = function() {
        cc.log("cc.Menu.setHandlerPriority was deprecated, 3.0 uses new event dispatcher to dispatch touch event based on draw order, so setHandlerPriority is not needed now.");
    };

    cc.Layer.prototype.setKeypadEnabled = function() {
        logW("cc.Layer.setKeypadEnabled", "cc.Layer.setKeyboardEnabled");
        return cc.Layer.prototype.setKeyboardEnabled.apply(this, arguments);
    };

    cc.Layer.prototype.isKeypadEnabled = function() {
        logW("cc.Layer.isKeypadEnabled", "cc.Layer.isKeyboardEnabled");
        return cc.Layer.prototype.isKeyboardEnabled.apply(this, arguments);
    };

    cc.registerTargettedDelegate = function() {
        logW("cc.registerTargettedDelegate", "cc.registerTargetedDelegate");
        return cc.registerTargetedDelegate.apply(this, arguments);
    };

    cc.Touch.prototype.getId = function(){
        logW("cc.Touch.getId", "cc.Touch.getID");
        return this.getID();
    };

})();
