/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 Copyright 2012 Stewart Hamilton-Arrandale.
 http://creativewax.co.uk

 Modified by Yannick Loriot.
 http://yannickloriot.com

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
 * An RGBA color class, its value present as percent
 * @param {Number} r
 * @param {Number} g
 * @param {Number} b
 * @param {Number} a
 * @constructor
 */
cc.RGBA = function(r,g,b,a){
    this.r = r ;    // percent
    this.g = g ;    // percent
    this.b = b ;    // percent
    this.a = a ;    // percent
};

cc.HSV = function(h,s,v){
    this.h = h ;     // angle in degrees
    this.s = s ;     // percent
    this.v = v ;     // percent
};

cc.ControlUtils = {};

cc.ControlUtils.addSpriteToTargetWithPosAndAnchor = function(spriteName,target,pos,anchor){
    var sprite = new cc.Sprite("#" + spriteName);

    if (!sprite)
        return null;

    sprite.setPosition(pos);
    sprite.setAnchorPoint(anchor);
    target.addChild(sprite);
    return sprite;
};

cc.ControlUtils.HSVfromRGB = function(rgbaValue){
    var out = new cc.HSV();
    var min, max, delta;

    min = rgbaValue.r < rgbaValue.g ? rgbaValue.r : rgbaValue.g;
    min = min  < rgbaValue.b ? min  : rgbaValue.b;

    max = rgbaValue.r > rgbaValue.g ? rgbaValue.r : rgbaValue.g;
    max = max  > rgbaValue.b ? max  : rgbaValue.b;

    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ){
        out.s = (delta / max);                  // s
    } else {
        // r = g = b = 0                        // s = 0, v is undefined
        out.s = 0.0;
        out.h = -1;                            // its now undefined (don't know if setting to NAN is a good idea)
        return out;
    }

    if( rgbaValue.r >= max ){                        // > is bogus, just keeps compilor happy
        out.h = ( rgbaValue.g - rgbaValue.b ) / delta;        // between yellow & magenta
    } else {
        if( rgbaValue.g >= max )
            out.h = 2.0 + ( rgbaValue.b - rgbaValue.r ) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + ( rgbaValue.r - rgbaValue.g ) / delta;  // between magenta & cyan
    }

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
};

cc.ControlUtils.RGBfromHSV = function(hsvValue){
    var hh, p, q, t, ff;
    var i;
    var out = new cc.RGBA();
    out.a = 1;

    if (hsvValue.s <= 0.0){ // < is bogus, just shuts up warnings

        if (!hsvValue.h){ // value.h == NAN
            out.r = hsvValue.v;
            out.g = hsvValue.v;
            out.b = hsvValue.v;
            return out;
        }

        // error - should never happen
        out.r = 0.0;
        out.g = 0.0;
        out.b = 0.0;
        return out;
    }

    hh = hsvValue.h;
    if(hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;

    i = 0 | hh;
    ff = hh - i;
    p = hsvValue.v * (1.0 - hsvValue.s);
    q = hsvValue.v * (1.0 - (hsvValue.s * ff));
    t = hsvValue.v * (1.0 - (hsvValue.s * (1.0 - ff)));

    switch(i) {
        case 0:
            out.r = hsvValue.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = hsvValue.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = hsvValue.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = hsvValue.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = hsvValue.v;
            break;
        default:
            out.r = hsvValue.v;
            out.g = p;
            out.b = q;
            break;
    }
    return out;
};

cc.ControlUtils.CCRectUnion = function(rect1, rect2){
    return cc.rectUnion(rect1,rect2);
};