/****************************************************************************
Copyright (c) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
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
  * @brief @~english ProgressTimer is a subclass of Node.
  * It renders the inner sprite according to the percentage.
  * The progress can be Radial, Horizontal or vertical.
  * @~chinese ProgressTimer是Node的子类。
  * 该类根据百分比来渲染显示内部的Sprite对象。
  * 变化方向包括径向，水平或者垂直方向。
  * @since v0.99.1
  */
class CC_DLL ProgressTimer : public Node
{
public:
    /** @~english Types of progress
     * @~chinese 进度条类型
     * @since v0.99.1
     */
    enum class Type
    {
        /** @~english Radial Counter-Clockwise.
         * @~chinese 逆时针径向
         */
        RADIAL,
        /** @~english Bar.
         * @~chinese 条形
         */
        BAR,
    };
    
    /** @brief @~english Creates a progress timer with the sprite as the shape the timer goes through.
     *         @~chinese 以Sprite对象作为进度条的图形，创建一个ProgressTimer对象。
     *
     * @param sp @~english The sprite as the shape the timer goes through.
     *           @~chinese 需要使用的 Sprite 对象的指针
     * @return @~english A ProgressTimer.
     *         @~chinese 一个进度条的实例化对象指针。
     */
    static ProgressTimer* create(Sprite* sp);

    /** @brief @~english Get the type of the ProgressTimer. 
     *         @~chinese 获取进度条的类型。
     *
     * @return @~english A Type
     *         @~chinese 进度条的类型。
     */
    inline Type getType() const { return _type; }

    /** @brief @~english Percentages are from 0 to 100.
     *         @~chinese 获取进度条的百分比，范围为 0 到 100，包含0，100
     *
     * @return @~english Percentages.
     *         @~chinese 百分比值。
     */
    inline float getPercentage() const {return _percentage; }

    /** @brief @~english The image to show the progress percentage, retain. 
     *         @~chinese 获取用来显示进度条比例的Sprite对象，已retain
     *
     * @return @~english A sprite.
     *         @~chinese Sprite 对象。
     */
    inline Sprite* getSprite() const { return _sprite; }
    
    /** @brief @~english Set the percentage values. 
     *         @~chinese 设置进度条显示的百分比。
     *
     * @param percentage @~english The percentage values.
     *                   @~chinese 百分比值。
     */
    void setPercentage(float percentage);
    
    /** @brief @~english Set the sprite as the shape. 
     *         @~chinese 设置进度条使用的 Sprite 对象。
     *
     * @param sprite @~english The sprite as the shape.
     *               @~chinese 需要使用的 Sprite 对象。
     */
    void setSprite(Sprite *sprite);
    
    /** @brief @~english Set the ProgressTimer type. 
     *         @~chinese 设置进度条的类型。
     *
     * @param type @~english Is an Type.
     *             @~chinese 进度条类型。
     */
    void setType(Type type);
    
    /** @brief @~english Set the Reverse direction.
     *         @~chinese 反转进度条的方向。
     *
     * @param reverse @~english If reverse is false it will clockwise,if is true it will Anti-clockwise.
     *                @~chinese 如果是 false，则为顺时针方向；否则为逆时针方向。
     *
     * @js setReverseDirection
     * @lua setReverseDirection
     */
    void setReverseProgress(bool reverse);
    
    /** @brief @~english Return the Reverse direction. 
     *         @~chinese 获取方向是否为反转状态。
     *
     * @return @~english If the direction is Anti-clockwise,it will return true.
     *         @~chinese 逆时针方向返回 true，顺时针方向返回 false。
     */
    inline bool isReverseDirection() { return _reverseDirection; };
    
    /** @brief @~english Set the Reverse direction.
     *         @~chinese 反转进度条的方向。
     * @param value @~english If reverse is false it will clockwise,if is true it will Anti-clockwise.
     *                @~chinese 如果是 false，则为顺时针方向；否则为逆时针方向。
     */
    inline void setReverseDirection(bool value) { _reverseDirection = value; };

    /**
     * @brief @~english Midpoint is used to modify the progress start position.
     *    If you're using radials type then the midpoint changes the center point.
     *    If you're using bar type the the midpoint changes the bar growth.
     *        it expands from the center but clamps to the sprites edge so:
     *        you want a left to right then set the midpoint all the way to Vec2(0,y).
     *        you want a right to left then set the midpoint all the way to Vec2(1,y).
     *        you want a bottom to top then set the midpoint all the way to Vec2(x,0).
     *        you want a top to bottom then set the midpoint all the way to Vec2(x,1).
     *        @~chinese 中点（Midpoint）表示进度条变化的起始位置。
     *    如果进度条是径向模式，中点代表圆心位置
     *    如果进度条是条形模式，中点代表着进度条展开的方向。
     *        进度条从中心位置向两边展开，因此：
     *        进度条是从左往右展开时，设置中点（Midpoint）为Vec2(0,y);
     *        进度条是从右往左展开时，设置中点（Midpoint）为Vec2(1,y);
     *        进度条是从下往上展开时，设置中点（Midpoint）为Vec2(x,0);
     *        进度条是从上往下展开时，设置中点（Midpoint）为Vec2(x,1);
     * @param point @~english A Vec2 point.
     *              @~chinese 中点位置。
     */
    void setMidpoint(const Vec2& point);
    
    /** @brief @~english Returns the Midpoint. 
     *         @~chinese 获取中点位置。
     *
     * @return @~english A Vec2.
     *         @~chinese 中点位置。
     */
    Vec2 getMidpoint() const;

    /**
     * @brief @~english This allows the bar type to move the component at a specific rate.
     *    Set the component to 0 to make sure it stays at 100%.
     *    For example you want a left to right bar but not have the height stay 100%.
     *    Set the rate to be Vec2(0,1); and set the midpoint to = Vec2(0,.5f).
     *        @~chinese 通过本方法设置条形模式进度条非变化方向显示的比例（barChangeRate）
     *    设置为0可以保证进度条非变化方向100%显示。
     *    例如，如果你需要一个从左往右的进度条，但是上下方向不需要100%显示，
     *    那么设置barChangeRate为Vec2(0,1),设置中点（Midpoint）为Vec2(0,.5f)。
     * @param barChangeRate @~english A Vec2.
     *                      @~chinese Vec2 对象。
     */
    inline void setBarChangeRate(const Vec2& barChangeRate ) { _barChangeRate = barChangeRate; }
    
    /** @brief @~english Returns the BarChangeRate.
     *         @~chinese 返回进度条变化比例的值
     *
     * @return @~english A barChangeRate.
     *         @~chinese 进度条的变化比例。
     */
    inline Vec2 getBarChangeRate() const { return _barChangeRate; }

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
