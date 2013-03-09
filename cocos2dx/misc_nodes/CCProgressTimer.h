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
    kCCProgressTimerTypeRadial,
    /// Bar
    kCCProgressTimerTypeBar,
} CCProgressTimerType;

/**
 @brief CCProgressTimer is a subclass of CCNode.
 It renders the inner sprite according to the percentage.
 The progress can be Radial, Horizontal or vertical.
 @since v0.99.1
 */
class CC_DLL CCProgressTimer : public CCNodeRGBA
{
public:
    CCProgressTimer();
    ~CCProgressTimer(void);

    /**    Change the percentage to change progress. */
    inline CCProgressTimerType getType(void) { return m_eType; }

    /** Percentages are from 0 to 100 */
    inline float getPercentage(void) {return m_fPercentage; }

    /** The image to show the progress percentage, retain */
    inline CCSprite* getSprite(void) { return m_pSprite; }

    /** Initializes a progress timer with the sprite as the shape the timer goes through */
    bool initWithSprite(CCSprite* sp);

    void setPercentage(float fPercentage);
    void setSprite(CCSprite *pSprite);
    void setType(CCProgressTimerType type);
    void setReverseProgress(bool reverse);

    virtual void draw(void);
    void setAnchorPoint(CCPoint anchorPoint);

    virtual void setOpacityModifyRGB(bool bValue);
    virtual bool isOpacityModifyRGB(void);
    
    inline bool isReverseDirection() { return m_bReverseDirection; };
    inline void setReverseDirection(bool value) { m_bReverseDirection = value; };

public:
    /** Creates a progress timer with the sprite as the shape the timer goes through */
    static CCProgressTimer* create(CCSprite* sp);
protected:
    ccTex2F textureCoordFromAlphaPoint(CCPoint alpha);
    ccVertex2F vertexFromAlphaPoint(CCPoint alpha);
    void updateProgress(void);
    void updateBar(void);
    void updateRadial(void);
    void updateColor(void);
    CCPoint boundaryTexCoord(char index);

protected:
    CCProgressTimerType m_eType;
    float m_fPercentage;
    CCSprite *m_pSprite;
    int m_nVertexDataCount;
    ccV2F_C4B_T2F *m_pVertexData;

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
    CC_PROPERTY(CCPoint, m_tMidpoint, Midpoint);

    /**
     *    This allows the bar type to move the component at a specific rate
     *    Set the component to 0 to make sure it stays at 100%.
     *    For example you want a left to right bar but not have the height stay 100%
     *    Set the rate to be ccp(0,1); and set the midpoint to = ccp(0,.5f);
     */
    CC_SYNTHESIZE(CCPoint, m_tBarChangeRate, BarChangeRate);

    bool m_bReverseDirection;
};

// end of misc_nodes group
/// @}

NS_CC_END

#endif //__MISC_NODE_CCPROGRESS_TIMER_H__
