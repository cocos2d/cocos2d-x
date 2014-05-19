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

#include "2d/CCSprite.h"
#include "renderer/CCCustomCommand.h"
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

/**
 * @addtogroup misc_nodes
 * @{
 */

/**
 @brief ProgressTimer是Node的子类。
 该类根据百分比来渲染显示内部的Sprite对象。
 变化方向包括径向，水平或者垂直方向。
 @since v0.99.1
 */
class CC_DLL ProgressTimer : public Node
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** 进度条类型
     @since v0.99.1
     */
    enum class Type
    {
        /// 逆时针径向
        RADIAL,
        /// 条形
        BAR,
    };
    
	/** 以Sprite对象作为进度条的图形，创建一个ProgressTimer对象 */
    static ProgressTimer* create(Sprite* sp);

    inline Type getType() const { return _type; }

	/** 百分比范围为0到100，包含0，100 */
    inline float getPercentage() const {return _percentage; }

	/** 获取用来显示进度条比例的Sprite对象，已retain*/
    inline Sprite* getSprite() const { return _sprite; }

	/** 设置进度条显示的百分比*/
    void setPercentage(float percentage);
    void setSprite(Sprite *sprite);
    void setType(Type type);
    /**
     * @js setReverseDirection
     * @lua setReverseDirection
     */
    void setReverseProgress(bool reverse);

    inline bool isReverseDirection() { return _reverseDirection; };
    inline void setReverseDirection(bool value) { _reverseDirection = value; };

    /**
	 *    中点（Midpoint）表示进度条变化的起始位置。
	 *    如果进度条是径向模式，中点代表圆心位置
	 *    如果进度条是条形模式，中点代表着进度条展开的方向。
	 *        进度条从中心位置向两边展开，因此：
	 *        进度条是从左往右展开时，设置中点（Midpoint）为Vec2(0,y);
	 *        进度条是从右往左展开时，设置中点（Midpoint）为Vec2(1,y);
	 *        进度条是从下往上展开时，设置中点（Midpoint）为Vec2(x,0);
	 *        进度条是从上往下展开时，设置中点（Midpoint）为Vec2(x,1);
     */
    void setMidpoint(const Vec2& point);
	/** 返回中点(Midpoint) */
    Vec2 getMidpoint() const;

    /**
	 *    通过本方法设置条形模式进度条非变化方向显示的比例（barChangeRate）
	 *    设置为0可以保证进度条非变化方向100%显示。
	 *    例如，如果你需要一个从左往右的进度条，但是上下方向不需要100%显示，
	 *    那么设置barChangeRate为Vec2(0,1),设置中点（Midpoint）为Vec2(0,.5f)。
     */
    inline void setBarChangeRate(const Vec2& barChangeRate ) { _barChangeRate = barChangeRate; }
	/** 返回BarChangeRate */
    inline Vec2 getBarChangeRate() const { return _barChangeRate; }

    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
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
    /** 以Sprite对象作为进度条的图形来初始化进度条 */
    bool initWithSprite(Sprite* sp);
    
protected:
    void onDraw(const Mat4 &transform, bool transformUpdated);
    
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
