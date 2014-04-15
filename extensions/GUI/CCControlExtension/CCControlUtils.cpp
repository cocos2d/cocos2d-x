/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

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

#include "CCControlUtils.h"

NS_CC_EXT_BEGIN

Sprite* ControlUtils::addSpriteToTargetWithPosAndAnchor(const char* spriteName, Node * target, Vector2 pos, Vector2 anchor)
{
    Sprite *sprite =Sprite::createWithSpriteFrameName(spriteName);
    
    if (!sprite)
        return NULL;

    sprite->setPosition(pos);
    sprite->setAnchorPoint(anchor);
    target->addChild(sprite);

    return sprite;
}


HSV ControlUtils::HSVfromRGB(RGBA value)
{
    HSV         out;
    double      min, max, delta;
    
    min = value.r < value.g ? value.r : value.g;
    min = min  < value.b ? min  : value.b;
    
    max = value.r > value.g ? value.r : value.g;
    max = max  > value.b ? max  : value.b;
    
    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 )
    {
        out.s = (delta / max);                  // s
    } else
    {
        // r = g = b = 0                        // s = 0, v is undefined
        out.s = 0.0;
        out.h = -1;                            // its now undefined (don't know if setting to NAN is a good idea)
        return out;
    }
    if( value.r >= max )                        // > is bogus, just keeps compilor happy
    {
        out.h = ( value.g - value.b ) / delta;        // between yellow & magenta
    } else
    {
        if( value.g >= max )
            out.h = 2.0 + ( value.b - value.r ) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + ( value.r - value.g ) / delta;  // between magenta & cyan
    }
    
    out.h *= 60.0;                              // degrees
    
    if( out.h < 0.0 )
        out.h += 360.0;
    
    return out;
}

RGBA ControlUtils::RGBfromHSV(HSV value)
{
    double      hh, p, q, t, ff;
    long        i;
    RGBA        out;
    out.a        = 1;
    
    if (value.s <= 0.0) // < is bogus, just shuts up warnings
    {       
        if (isnan(value.h)) // value.h == NAN
        {   
            out.r = value.v;
            out.g = value.v;
            out.b = value.v;
            return out;
        }
        
        // error - should never happen
        out.r = 0.0;
        out.g = 0.0;
        out.b = 0.0;
        return out;
    }
    
    hh = value.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = value.v * (1.0 - value.s);
    q = value.v * (1.0 - (value.s * ff));
    t = value.v * (1.0 - (value.s * (1.0 - ff)));
    
    switch(i)
    {
        case 0:
            out.r = value.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = value.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = value.v;
            out.b = t;
            break;
            
        case 3:
            out.r = p;
            out.g = q;
            out.b = value.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = value.v;
            break;
        case 5:
        default:
            out.r = value.v;
            out.g = p;
            out.b = q;
            break;
    }
    return out;     
}

Rect ControlUtils::RectUnion(const Rect& src1, const Rect& src2) 
{
    Rect result;
    
    float x1 = MIN(src1.getMinX(), src2.getMinX());
    float y1 = MIN(src1.getMinY(), src2.getMinY());
    float x2 = MAX(src1.getMaxX(), src2.getMaxX());
    float y2 = MAX(src1.getMaxY(), src2.getMaxY());
    
    result.origin=Vector2(x1,y1);
    result.size=Size(x2-x1, y2-y1);
    return result;
}

NS_CC_EXT_END
