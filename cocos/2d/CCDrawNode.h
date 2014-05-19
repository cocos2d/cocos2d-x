/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Code copied & pasted from SpacePatrol game https://github.com/slembcke/SpacePatrol
 *
 * Renamed and added some changes for cocos2d
 *
 */

#ifndef __CCDRAWNODES_CCDRAW_NODE_H__
#define __CCDRAWNODES_CCDRAW_NODE_H__

#include "2d/CCNode.h"
#include "base/ccTypes.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

/** DrawNode
 Node由于在一个单独的批处理中绘制了所以元素，因此它绘制点、线段、多边形都要比“drawing primitives”快。
 
 @since v2.1
 */
class CC_DLL DrawNode : public Node
{
public:
    /** 创建并初始化DrawNode节点 */
    static DrawNode* create();

    /** 给定半径以及颜色，绘制预定位置的点 */
    void drawDot(const Vec2 &pos, float radius, const Color4F &color);
    
    /** 给定半径以及颜色绘制一条线段 */
    void drawSegment(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color);
    
    /** 给定填充颜色以及线条颜色绘制一个多边形
    * @code
    * 在lua和js版本中这个函数的参数将会发生改变
    * 在 js版本中: var drawPolygon(var Arrayofpoints, var fillColor, var width, var borderColor)
    * 在lua版本中:local drawPolygon(local pointTable,local tableCount,local fillColor,local width,local borderColor)
    * @endcode
    */
    void drawPolygon(Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
	
    /** 给定颜色绘制三角形 */
    void drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color);

    /** 给定颜色以及线段总数绘制一个cubic贝塞尔曲线 */
    void drawCubicBezier(const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, unsigned int segments, const Color4F &color);

    /** 给定颜色以及线段总数绘制一个quadratic贝塞尔曲线 */
    void drawQuadraticBezier(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments, const Color4F &color);
    
    /** 清除节点缓冲区中的几何结构数据。 */
    void clear();
    /**
    * @js NA
    * @lua NA
    */
    const BlendFunc& getBlendFunc() const;
    /**
    * @code
    * 在js和lua版本中，这个函数的参数将会发生变化
    * 在js版本: var setBlendFunc(var src, var dst)
    * @endcode
    * @lua NA
    */
    void setBlendFunc(const BlendFunc &blendFunc);

    void onDraw(const Mat4 &transform, bool transformUpdated);
    
    // 重载函数
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    
CC_CONSTRUCTOR_ACCESS:
    DrawNode();
    virtual ~DrawNode();
    virtual bool init();

protected:
    void ensureCapacity(int count);

    GLuint      _vao;
    GLuint      _vbo;

    int         _bufferCapacity;
    GLsizei     _bufferCount;
    V2F_C4B_T2F *_buffer;

    BlendFunc   _blendFunc;
    CustomCommand _customCommand;

    bool        _dirty;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode);
};

NS_CC_END

#endif // __CCDRAWNODES_CCDRAW_NODE_H__
