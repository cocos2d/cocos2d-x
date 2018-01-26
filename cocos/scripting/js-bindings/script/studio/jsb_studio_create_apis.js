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

/************************  Cocostudio  *************************/

ccs.Armature.prototype._ctor = function(name, parentBone) {
    // parentBone !== undefined && ccs.Armature.prototype.init.call(this, name, parentBone);
    if(parentBone !== undefined)
        ccs.Armature.prototype.init.call(this, name, parentBone);
    else if(name !== undefined)
        ccs.Armature.prototype.init.call(this, name);
};

ccs.Bone.prototype._ctor = function(name) {
    name !== undefined && ccs.Bone.prototype.init.call(this, name);
};

ccs.ArmatureAnimation.prototype._ctor = function(armature) {
    armature !== undefined && ccs.ArmatureAnimation.prototype.init.call(this, armature);
};

ccs.Tween.prototype._ctor = function(bone) {
    bone !== undefined && ccs.Tween.prototype.init.call(this, bone);
};

ccs.BatchNode.prototype._ctor = function() {
    ccs.BatchNode.prototype.init.call(this);
};

ccs.DecorativeDisplay.prototype._ctor = function() {
    ccs.DecorativeDisplay.prototype.init.call(this);
};

ccs.DisplayManager.prototype._ctor = function(bone) {
    bone !== undefined && ccs.DisplayManager.prototype.init.call(this, bone);
};

ccs.Skin.prototype._ctor = function(fileName, rect) {
    if (fileName == null || fileName == "") {
        ccs.Skin.prototype.init.call(this);
    } else {
        if(fileName[0] == "#"){
            ccs.Skin.prototype.initWithSpriteFrameName.call(this, fileName.substr(1));
        } else {
            rect ? ccs.Skin.prototype.initWithFile.call(this, fileName, rect)
                : ccs.Skin.prototype.initWithFile.call(this, fileName);
        }
    }
};

ccs.ColliderDetector.prototype._ctor = function(bone) {
    bone !== undefined && ccs.ColliderDetector.prototype.init.call(this, bone);
};

ccs.TriggerObj.prototype._ctor = function() {
    ccs.TriggerObj.prototype.init.call(this);
};

ccs.ComAttribute.prototype._ctor = function() {
    ccs.ComAttribute.prototype.init.call(this);
};

ccs.ComAudio.prototype._ctor = function() {
    ccs.ComAudio.prototype.init.call(this);
};

ccs.ComController.prototype._ctor = function() {
    ccs.ComController.prototype.init.call(this);
};

ccs.ComRender.prototype._ctor = function() {
    ccs.ComRender.prototype.init.call(this);
};

ccs.ActionTimelineData.prototype._ctor = function(actionTag) {
    if (actionTag !== undefined)
    {
        ccs.ActionTimelineData.prototype.init.call(this,actionTag);
    }
};

ccs.ComExtensionData.prototype._ctor = function() {
    ccs.ComExtensionData.prototype.init.call(this);
};

ccs.BoneNode.prototype._ctor = function (length) {
    ccs.BoneNode.prototype.init.call(this);
    length !== undefined && this.setDebugDrawLength(length);
};

ccs.SkeletonNode.prototype._ctor = function () {
    ccs.SkeletonNode.prototype.init.call(this);
};