/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Lam Pham

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
#ifndef __MISC_NODE_CCPROGRESS_TIMER_H__
#define __MISC_NODE_CCPROGRESS_TIMER_H__

#include "sprite_nodes/CCSprite.h"
#ifdef EMSCRIPTEN
#include "base_nodes/CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

/**
 * @addtogroup misc_nodes
 * @{
 */

/** Types of progress
 @since v0.99.1
 */
typedef enum {
    /// Radial Counter-Clockwise
    kProgressTimerTypeRadial,
    /// Bar
    kProgressTimerTypeBar,
} ProgressTimerType;

/**
 @brief ProgressTimer is a subclass of Node.
 It renders the inner sprite according to the percentage.
 The progress can be Radial, Horizontal or vertical.
 @since v0.99.1
 */
class CC_DLL ProgressTimer : public NodeRGBA
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    ProgressTimer();
    ~ProgressTimer(void);

    /**    Change the percentage to change progress. */
    inline ProgressTimerType getType(void) { return _type; }

    /** Percentages are from 0 to 100 */
    inline float getPercentage(void) {return _percentage; }

    /** The image to show the progress percentage, retain */
    inline Sprite* getSprite(void) { return _sprite; }

    /** Initializes a progress timer with the sprite as the shape the timer goes through */
    bool initWithSprite(Sprite* sp);

    void setPercentage(float fPercentage);
    void setSprite(Sprite *pSprite);
    void setType(ProgressTimerType type);
    void setReverseProgress(bool reverse);

    virtual void draw(void);
    void setAnchorPoint(Point anchorPoint);

    virtual void setOpacityModifyRGB(bool bValue);
    virtual bool isOpacityModifyRGB(void);
    
    inline bool isReverseDirection() { return _reverseDirection; };
    inline void setReverseDirection(bool value) { _reverseDirection = value; };

public:
    /** Creates a progress timer with the sprite as the shape the timer goes through */
    static ProgressTimer* create(Sprite* sp);
protected:
    ccTex2F textureCoordFromAlphaPoint(Point alpha);
    ccVertex2F vertexFromAlphaPoint(Point alpha);
    void updateProgress(void);
    void updateBar(void);
    void updateRadial(void);
    void updateColor(void);
    Point boundaryTexCoord(char index);

protected:
    ProgressTimerType _type;
    float _percentage;
    Sprite *_sprite;
    int _vertexDataCount;
    ccV2F_C4B_T2F *_vertexData;

    /**
     *    Midpoint is used to modify the progress start position.
     *    If you're using radials type then the midpoint changes the center point
     *    If you're using bar type the the midpoint changes the bar growth
     *        it expands from the center but clamps to the sprites edge so:
     *        you want a left to right then set the midpoint all the way to ccp(0,y)
     *        you want a right to left then set the midpoint all the way to ccp(1,y)
     *        you want a bottom to top then set the midpoint all the way to ccp(x,0)
     *        you want a top to bottom then set the midpoint all the way to ccp(x,1)
     */
    CC_PROPERTY(Point, _midpoint, Midpoint);

    /**
     *    This allows the bar type to move the component at a specific rate
     *    Set the component to 0 to make sure it stays at 100%.
     *    For example you want a left to right bar but not have the height stay 100%
     *    Set the rate to be ccp(0,1); and set the midpoint to = ccp(0,.5f);
     */
    CC_SYNTHESIZE(Point, _barChangeRate, BarChangeRate);

    bool _reverseDirection;
};

// end of misc_nodes group
/// @}

NS_CC_END

#endif //__MISC_NODE_CCPROGRESS_TIMER_H__
