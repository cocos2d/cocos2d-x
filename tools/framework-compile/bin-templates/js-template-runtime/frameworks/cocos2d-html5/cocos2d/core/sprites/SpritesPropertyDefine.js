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

cc._tmp.PrototypeSprite = function () {
    var _p = cc.Sprite.prototype;

    // Override properties
    cc.defineGetterSetter(_p, "opacityModifyRGB", _p.isOpacityModifyRGB, _p.setOpacityModifyRGB);
    cc.defineGetterSetter(_p, "opacity", _p.getOpacity, _p.setOpacity);
    cc.defineGetterSetter(_p, "color", _p.getColor, _p.setColor);

    // Extended properties
    /** @expose */
    _p.dirty;
    /** @expose */
    _p.flippedX;
    cc.defineGetterSetter(_p, "flippedX", _p.isFlippedX, _p.setFlippedX);
    /** @expose */
    _p.flippedY;
    cc.defineGetterSetter(_p, "flippedY", _p.isFlippedY, _p.setFlippedY);
    /** @expose */
    _p.offsetX;
    cc.defineGetterSetter(_p, "offsetX", _p._getOffsetX);
    /** @expose */
    _p.offsetY;
    cc.defineGetterSetter(_p, "offsetY", _p._getOffsetY);
    /** @expose */
    _p.atlasIndex;
    /** @expose */
    _p.texture;
    cc.defineGetterSetter(_p, "texture", _p.getTexture, _p.setTexture);
    /** @expose */
    _p.textureRectRotated;
    cc.defineGetterSetter(_p, "textureRectRotated", _p.isTextureRectRotated);
    /** @expose */
    _p.textureAtlas;
    /** @expose */
    _p.batchNode;
    cc.defineGetterSetter(_p, "batchNode", _p.getBatchNode, _p.setBatchNode);
    /** @expose */
    _p.quad;
    cc.defineGetterSetter(_p, "quad", _p.getQuad);

};
