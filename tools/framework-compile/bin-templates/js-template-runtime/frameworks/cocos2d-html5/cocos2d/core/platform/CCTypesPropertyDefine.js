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

cc._tmp.PrototypeColor = function () {
    var _p = cc.color;
    /**
     * White color (255, 255, 255, 255)
     * @returns {cc.Color}
     * @private
     */
    _p._getWhite = function () {
        return _p(255, 255, 255);
    };

    /**
     *  Yellow color (255, 255, 0, 255)
     * @returns {cc.Color}
     * @private
     */
    _p._getYellow = function () {
        return _p(255, 255, 0);
    };

    /**
     *  Blue color (0, 0, 255, 255)
     * @type {cc.Color}
     * @private
     */
    _p._getBlue = function () {
        return  _p(0, 0, 255);
    };

    /**
     *  Green Color (0, 255, 0, 255)
     * @type {cc.Color}
     * @private
     */
    _p._getGreen = function () {
        return _p(0, 255, 0);
    };

    /**
     *  Red Color (255, 0, 0, 255)
     * @type {cc.Color}
     * @private
     */
    _p._getRed = function () {
        return _p(255, 0, 0);
    };

    /**
     *  Magenta Color (255, 0, 255, 255)
     * @type {cc.Color}
     * @private
     */
    _p._getMagenta = function () {
        return _p(255, 0, 255);
    };

    /**
     *  Black Color (0, 0, 0, 255)
     * @type {cc.Color}
     * @private
     */
    _p._getBlack = function () {
        return _p(0, 0, 0);
    };

    /**
     *  Orange Color (255, 127, 0, 255)
     * @type {_p}
     * @private
     */
    _p._getOrange = function () {
        return _p(255, 127, 0);
    };

    /**
     *  Gray Color (166, 166, 166, 255)
     * @type {_p}
     * @private
     */
    _p._getGray = function () {
        return _p(166, 166, 166);
    };

    /** @expose */
    _p.WHITE;
    cc.defineGetterSetter(_p, "WHITE", _p._getWhite);
    /** @expose */
    _p.YELLOW;
    cc.defineGetterSetter(_p, "YELLOW", _p._getYellow);
    /** @expose */
    _p.BLUE;
    cc.defineGetterSetter(_p, "BLUE", _p._getBlue);
    /** @expose */
    _p.GREEN;
    cc.defineGetterSetter(_p, "GREEN", _p._getGreen);
    /** @expose */
    _p.RED;
    cc.defineGetterSetter(_p, "RED", _p._getRed);
    /** @expose */
    _p.MAGENTA;
    cc.defineGetterSetter(_p, "MAGENTA", _p._getMagenta);
    /** @expose */
    _p.BLACK;
    cc.defineGetterSetter(_p, "BLACK", _p._getBlack);
    /** @expose */
    _p.ORANGE;
    cc.defineGetterSetter(_p, "ORANGE", _p._getOrange);
    /** @expose */
    _p.GRAY;
    cc.defineGetterSetter(_p, "GRAY", _p._getGray);

    cc.BlendFunc._disable = function(){
        return new cc.BlendFunc(cc.ONE, cc.ZERO);
    };
    cc.BlendFunc._alphaPremultiplied = function(){
        return new cc.BlendFunc(cc.ONE, cc.ONE_MINUS_SRC_ALPHA);
    };
    cc.BlendFunc._alphaNonPremultiplied = function(){
        return new cc.BlendFunc(cc.SRC_ALPHA, cc.ONE_MINUS_SRC_ALPHA);
    };
    cc.BlendFunc._additive = function(){
        return new cc.BlendFunc(cc.SRC_ALPHA, cc.ONE);
    };

    /** @expose */
    cc.BlendFunc.DISABLE;
    cc.defineGetterSetter(cc.BlendFunc, "DISABLE", cc.BlendFunc._disable);
    /** @expose */
    cc.BlendFunc.ALPHA_PREMULTIPLIED;
    cc.defineGetterSetter(cc.BlendFunc, "ALPHA_PREMULTIPLIED", cc.BlendFunc._alphaPremultiplied);
    /** @expose */
    cc.BlendFunc.ALPHA_NON_PREMULTIPLIED;
    cc.defineGetterSetter(cc.BlendFunc, "ALPHA_NON_PREMULTIPLIED", cc.BlendFunc._alphaNonPremultiplied);
    /** @expose */
    cc.BlendFunc.ADDITIVE;
    cc.defineGetterSetter(cc.BlendFunc, "ADDITIVE", cc.BlendFunc._additive);
};


