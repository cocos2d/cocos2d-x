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

cc._tmp.PrototypeCCNode = function () {

    var _p = cc.Node.prototype;

    cc.defineGetterSetter(_p, "x", _p.getPositionX, _p.setPositionX);
    cc.defineGetterSetter(_p, "y", _p.getPositionY, _p.setPositionY);
    /** @expose */
    _p.width;
    cc.defineGetterSetter(_p, "width", _p._getWidth, _p._setWidth);
    /** @expose */
    _p.height;
    cc.defineGetterSetter(_p, "height", _p._getHeight, _p._setHeight);
    /** @expose */
    _p.anchorX;
    cc.defineGetterSetter(_p, "anchorX", _p._getAnchorX, _p._setAnchorX);
    /** @expose */
    _p.anchorY;
    cc.defineGetterSetter(_p, "anchorY", _p._getAnchorY, _p._setAnchorY);
    /** @expose */
    _p.skewX;
    cc.defineGetterSetter(_p, "skewX", _p.getSkewX, _p.setSkewX);
    /** @expose */
    _p.skewY;
    cc.defineGetterSetter(_p, "skewY", _p.getSkewY, _p.setSkewY);
    /** @expose */
    _p.zIndex;
    cc.defineGetterSetter(_p, "zIndex", _p.getLocalZOrder, _p.setLocalZOrder);
    /** @expose */
    _p.vertexZ;
    cc.defineGetterSetter(_p, "vertexZ", _p.getVertexZ, _p.setVertexZ);
    /** @expose */
    _p.rotation;
    cc.defineGetterSetter(_p, "rotation", _p.getRotation, _p.setRotation);
    /** @expose */
    _p.rotationX;
    cc.defineGetterSetter(_p, "rotationX", _p.getRotationX, _p.setRotationX);
    /** @expose */
    _p.rotationY;
    cc.defineGetterSetter(_p, "rotationY", _p.getRotationY, _p.setRotationY);
    /** @expose */
    _p.scale;
    cc.defineGetterSetter(_p, "scale", _p.getScale, _p.setScale);
    /** @expose */
    _p.scaleX;
    cc.defineGetterSetter(_p, "scaleX", _p.getScaleX, _p.setScaleX);
    /** @expose */
    _p.scaleY;
    cc.defineGetterSetter(_p, "scaleY", _p.getScaleY, _p.setScaleY);
    /** @expose */
    _p.children;
    cc.defineGetterSetter(_p, "children", _p.getChildren);
    /** @expose */
    _p.childrenCount;
    cc.defineGetterSetter(_p, "childrenCount", _p.getChildrenCount);
    /** @expose */
    _p.parent;
    cc.defineGetterSetter(_p, "parent", _p.getParent, _p.setParent);
    /** @expose */
    _p.visible;
    cc.defineGetterSetter(_p, "visible", _p.isVisible, _p.setVisible);
    /** @expose */
    _p.running;
    cc.defineGetterSetter(_p, "running", _p.isRunning);
    /** @expose */
    _p.ignoreAnchor;
    cc.defineGetterSetter(_p, "ignoreAnchor", _p.isIgnoreAnchorPointForPosition, _p.ignoreAnchorPointForPosition);
    /** @expose */
    _p.tag;
    /** @expose */
    _p.userData;
    /** @expose */
    _p.userObject;
    /** @expose */
    _p.arrivalOrder;
    /** @expose */
    _p.actionManager;
    cc.defineGetterSetter(_p, "actionManager", _p.getActionManager, _p.setActionManager);
    /** @expose */
    _p.scheduler;
    cc.defineGetterSetter(_p, "scheduler", _p.getScheduler, _p.setScheduler);
    //cc.defineGetterSetter(_p, "boundingBox", _p.getBoundingBox);
    /** @expose */
    _p.shaderProgram;
    cc.defineGetterSetter(_p, "shaderProgram", _p.getShaderProgram, _p.setShaderProgram);

    /** @expose */
    _p.opacity;
    cc.defineGetterSetter(_p, "opacity", _p.getOpacity, _p.setOpacity);
    /** @expose */
    _p.opacityModifyRGB;
    cc.defineGetterSetter(_p, "opacityModifyRGB", _p.isOpacityModifyRGB);
    /** @expose */
    _p.cascadeOpacity;
    cc.defineGetterSetter(_p, "cascadeOpacity", _p.isCascadeOpacityEnabled, _p.setCascadeOpacityEnabled);
    /** @expose */
    _p.color;
    cc.defineGetterSetter(_p, "color", _p.getColor, _p.setColor);
    /** @expose */
    _p.cascadeColor;
    cc.defineGetterSetter(_p, "cascadeColor", _p.isCascadeColorEnabled, _p.setCascadeColorEnabled);
};