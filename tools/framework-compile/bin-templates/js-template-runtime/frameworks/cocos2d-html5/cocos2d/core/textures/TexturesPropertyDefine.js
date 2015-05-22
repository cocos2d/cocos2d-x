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

cc._tmp.PrototypeTexture2D = function () {

    var _c = cc.Texture2D;

    /**
     * <p>
     *    treats (or not) PVR files as if they have alpha premultiplied.                                                <br/>
     *    Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is       <br/>
     *    possible load them as if they have (or not) the alpha channel premultiplied.                                  <br/>
     *                                                                                                                  <br/>
     *    By default it is disabled.                                                                                    <br/>
     * </p>
     * @param haveAlphaPremultiplied
     */
    _c.PVRImagesHavePremultipliedAlpha = function (haveAlphaPremultiplied) {
        cc.PVRHaveAlphaPremultiplied_ = haveAlphaPremultiplied;
    };

    /**
     * 32-bit texture: RGBA8888
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_RGBA8888
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_RGBA8888 = 2;

    /**
     * 24-bit texture: RGBA888
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_RGB888
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_RGB888 = 3;

    /**
     * 16-bit texture without Alpha channel
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_RGB565
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_RGB565 = 4;

    /**
     * 8-bit textures used as masks
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_A8
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_A8 = 5;

    /**
     * 8-bit intensity texture
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_I8
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_I8 = 6;

    /**
     * 16-bit textures used as masks
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_AI88
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_AI88 = 7;

    /**
     * 16-bit textures: RGBA4444
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_RGBA4444
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_RGBA4444 = 8;

    /**
     * 16-bit textures: RGB5A1
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_RGB5A1
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_RGB5A1 = 7;

    /**
     * 4-bit PVRTC-compressed texture: PVRTC4
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_PVRTC4
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_PVRTC4 = 9;

    /**
     * 2-bit PVRTC-compressed texture: PVRTC2
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_PVRTC2
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_PVRTC2 = 10;

    /**
     * Default texture format: RGBA8888
     * @memberOf cc.Texture2D
     * @name PIXEL_FORMAT_DEFAULT
     * @static
     * @constant
     * @type {Number}
     */
    _c.PIXEL_FORMAT_DEFAULT = _c.PIXEL_FORMAT_RGBA8888;

    var _M = cc.Texture2D._M = {};
    _M[_c.PIXEL_FORMAT_RGBA8888] = "RGBA8888";
    _M[_c.PIXEL_FORMAT_RGB888] = "RGB888";
    _M[_c.PIXEL_FORMAT_RGB565] = "RGB565";
    _M[_c.PIXEL_FORMAT_A8] = "A8";
    _M[_c.PIXEL_FORMAT_I8] = "I8";
    _M[_c.PIXEL_FORMAT_AI88] = "AI88";
    _M[_c.PIXEL_FORMAT_RGBA4444] = "RGBA4444";
    _M[_c.PIXEL_FORMAT_RGB5A1] = "RGB5A1";
    _M[_c.PIXEL_FORMAT_PVRTC4] = "PVRTC4";
    _M[_c.PIXEL_FORMAT_PVRTC2] = "PVRTC2";

    var _B = cc.Texture2D._B = {};
    _B[_c.PIXEL_FORMAT_RGBA8888] = 32;
    _B[_c.PIXEL_FORMAT_RGB888] = 24;
    _B[_c.PIXEL_FORMAT_RGB565] = 16;
    _B[_c.PIXEL_FORMAT_A8] = 8;
    _B[_c.PIXEL_FORMAT_I8] = 8;
    _B[_c.PIXEL_FORMAT_AI88] = 16;
    _B[_c.PIXEL_FORMAT_RGBA4444] = 16;
    _B[_c.PIXEL_FORMAT_RGB5A1] = 16;
    _B[_c.PIXEL_FORMAT_PVRTC4] = 4;
    _B[_c.PIXEL_FORMAT_PVRTC2] = 3;

    var _p = cc.Texture2D.prototype;

    // Extended properties
    /** @expose */
    _p.name;
    cc.defineGetterSetter(_p, "name", _p.getName);
    /** @expose */
    _p.pixelFormat;
    cc.defineGetterSetter(_p, "pixelFormat", _p.getPixelFormat);
    /** @expose */
    _p.pixelsWidth;
    cc.defineGetterSetter(_p, "pixelsWidth", _p.getPixelsWide);
    /** @expose */
    _p.pixelsHeight;
    cc.defineGetterSetter(_p, "pixelsHeight", _p.getPixelsHigh);
    //cc.defineGetterSetter(_p, "size", _p.getContentSize, _p.setContentSize);
    /** @expose */
    _p.width;
    cc.defineGetterSetter(_p, "width", _p._getWidth);
    /** @expose */
    _p.height;
    cc.defineGetterSetter(_p, "height", _p._getHeight);

    _c.defaultPixelFormat = _c.PIXEL_FORMAT_DEFAULT;
};

cc._tmp.PrototypeTextureAtlas = function () {

    var _p = cc.TextureAtlas.prototype;

    // Extended properties
    /** @expose */
    _p.totalQuads;
    cc.defineGetterSetter(_p, "totalQuads", _p.getTotalQuads);
    /** @expose */
    _p.capacity;
    cc.defineGetterSetter(_p, "capacity", _p.getCapacity);
    /** @expose */
    _p.quads;
    cc.defineGetterSetter(_p, "quads", _p.getQuads, _p.setQuads);

};

