/****************************************************************************
Copyright (c) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "renderer/CCCustomCommand.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

class Sprite;

/**
 * @addtogroup _2d
 * @{
 */

/**
  * @brief ProgressTimer is a subclass of Node.
  * It renders the inner sprite according to the percentage.
  * The progress can be Radial, Horizontal or vertical.
  * @since v0.99.1
  */
class CC_DLL ProgressTimer : public Node
{
public:
    /** Types of progress
     * @since v0.99.1
     */
    enum class Type
    {
        RADIAL,/** Radial Counter-Clockwise. */
        BAR,/** Bar. */
    };
    
    /** Creates a progress timer with the sprite as the shape the timer goes through.
     *
     * @param sp The sprite as the shape the timer goes through.
     * @return A ProgressTimer.
     */
    static ProgressTimer* create(Sprite* sp);

    /** Change the percentage to change progress. 
     *
     * @return A Type
     */
    Type getType() const { return _type; }

    /** Percentages are from 0 to 100.
     *
     * @return Percentages.
     */
    float getPercentage() const { return _percentage; }

    /** The image to show the progress percentage, retain. 
     *
     * @return A sprite.
     */
    Sprite* getSprite() const { return _sprite; }
    
    /** Set the initial percentage values. 
     *
     * @param percentage The initial percentage values.
     */
    void setPercentage(float percentage);
    
    /** Set the sprite as the shape. 
     *
     * @param sprite The sprite as the shape.
     */
    void setSprite(Sprite *sprite);
    
    /** Set the ProgressTimer type. 
     *
     * @param type Is an Type.
     */
    void setType(Type type);
    
    /** Return the Reverse direction.
     *
     * @return If the direction is Anti-clockwise,it will return true.
     */
    bool isReverseDirection() { return _reverseDirection; };
    
    /** Set the Reverse direction.
     *
     * @param value If value is false it will clockwise,if is true it will Anti-clockwise.
     */
    void setReverseDirection(bool value);

    /** Set the Reverse direction.
     * @js setReverseDirection
     * @lua setReverseDirection
     * @param reverse If reverse is false it will clockwise,if is true it will Anti-clockwise.
     */
    CC_DEPRECATED_ATTRIBUTE void setReverseProgress(bool reverse) { setReverseDirection(reverse); }


    /**
     *    Midpoint is used to modify the progress start position.
     *    If you're using radials type then the midpoint changes the center point.
     *    If you're using bar type then the midpoint changes the bar growth.
     *        it expands from the center but clamps to the sprites edge so:
     *        you want a left to right then set the midpoint all the way to Vec2(0,y).
     *        you want a right to left then set the midpoint all the way to Vec2(1,y).
     *        you want a bottom to top then set the midpoint all the way to Vec2(x,0).
     *        you want a top to bottom then set the midpoint all the way to Vec2(x,1).
     * @param point A Vec2 point.
     */
    void setMidpoint(const Vec2& point);
    
    /** Returns the Midpoint. 
     *
     * @return A Vec2.
     */
    Vec2 getMidpoint() const;

    /**
     *    This allows the bar type to move the component at a specific rate.
     *    Set the component to 0 to make sure it stays at 100%.
     *    For example you want a left to right bar but not have the height stay 100%.
     *    Set the rate to be Vec2(0,1); and set the midpoint to = Vec2(0,.5f).
     * @param barChangeRate A Vec2.
     */
    void setBarChangeRate(const Vec2& barChangeRate ) { _barChangeRate = barChangeRate; }
    
    /** Returns the BarChangeRate.
     *
     * @return A barChangeRate.
     */
    Vec2 getBarChangeRate() const { return _barChangeRate; }

    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void setAnchorPoint(const Vec2& anchorPoint) override;
    virtual void setColor(const Color3B &color) override;
    virtual const Color3B& getColor() const override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual GLubyte getOpacity() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ProgressTimer();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ProgressTimer();
    
    /** Initializes a progress timer with the sprite as the shape the timer goes through */
    bool initWithSprite(Sprite* sp);
    
protected:
    void onDraw(const Mat4 &transform, uint32_t flags);
    
    Tex2F textureCoordFromAlphaPoint(Vec2 alpha);
    Vec2 vertexFromAlphaPoint(Vec2 alpha);
    void updateProgress(void);
    void updateBar(void);
    void updateRadial(void);
    virtual void updateColor(void) override;
    Vec2 boundaryTexCoord(char index);

    Type _type;
    Vec2 _midpoint;
    Vec2 _barChangeRate;
    float _percentage;
    Sprite *_sprite;
    int _vertexDataCount;
    V2F_C4B_T2F *_vertexData;
    
    CustomCommand _customCommand;

    bool _reverseDirection;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressTimer);
};

// end of misc_nodes group
/// @}

NS_CC_END

#endif //__MISC_NODE_CCPROGRESS_TIMER_H__
