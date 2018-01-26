/*
 * Copyright (c) 2014-2017 Chukong Technologies Inc.
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

/**
 * @type {Object} Format and manage armature configuration and armature animation
 * @name ccs.armatureDataManager
 */
ccs.armatureDataManager = null;
cc.defineGetterSetter(ccs, "armatureDataManager", function() {
    return ccs.ArmatureDataManager.getInstance();
});
ccs.ArmatureDataManager.prototype.clear = function() {
    ccs.ArmatureDataManager.destroyInstance();
};

/**
 * @type {Object} Base singleton object for ccs.ActionManager
 * @name ccs.actionManager
 */
ccs.actionManager = ccs.ActionManager.getInstance();
ccs.ActionManager.prototype.clear = function() {
    this.releaseActions();
};
ccs.ActionManager.prototype.initWithDictionary = function(file, dic, node, version) {
    ccs.actionManager.initWithDictionaryEx(file, JSON.stringify(dic), node, version);
}

/**
 * The same as cc.Node
 * @class
 * @extends ccs.Class
 */
ccs.Node = ccs.Node || cc.Node;
ccs.Node.extend = ccs.Node.extend || cc.Node.extend;

/**
 * The same as cc.Sprite
 * @class
 * @extends ccs.Class
 */
ccs.Sprite = ccs.Sprite || cc.Sprite;
ccs.Sprite.extend = ccs.Sprite.extend || cc.Sprite.extend;

/**
 * The same as cc.Component
 * @class
 * @extends ccs.Class
 */
ccs.Component = ccs.Component || cc.Component;
ccs.Component.extend = ccs.Component.extend || cc.Component.extend;

ccs.SkinNode = cc.Node;
ccs.BoneNode.extend = cc.Class.extend;
ccs.SkeletonNode.extend = cc.Class.extend;
