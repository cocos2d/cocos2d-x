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
 Node that draws dots, segments and polygons.
 Faster than the "drawing primitives" since they it draws everything in one single batch.
 
 @since v2.1
 */
class CC_DLL DrawNode : public Node
{
public:
    /** creates and initialize a DrawNode node */
    static DrawNode* create();

    /** draw a dot at a position, with a given radius and color */
    void drawDot(const Vec2 &pos, float radius, const Color4F &color);
    
    /** draw a segment with a radius and color */
    void drawSegment(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color);
    
    /** draw a polygon with a fill color and line color
    * @code
    * When this function bound into js or lua,the parameter will be changed
    * In js: var drawPolygon(var Arrayofpoints, var fillColor, var width, var borderColor)
    * In lua:local drawPolygon(local pointTable,local tableCount,local fillColor,local width,local borderColor)
    * @endcode
    */
    void drawPolygon(Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
	
    /** draw a triangle with color */
    void drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color);

    /** draw a cubic bezier curve with color and number of segments */
    void drawCubicBezier(const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, unsigned int segments, const Color4F &color);

    /** draw a quadratic bezier curve with color and number of segments */
    void drawQuadraticBezier(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments, const Color4F &color);
    
    /** Clear the geometry in the node's buffer. */
    void clear();
    /**
    * @js NA
    * @lua NA
    */
    const BlendFunc& getBlendFunc() const;
    /**
    * @code
    * When this function bound into js or lua,the parameter will be changed
    * In js: var setBlendFunc(var src, var dst)
    * @endcode
    * @lua NA
    */
    void setBlendFunc(const BlendFunc &blendFunc);

    void onDraw(const Mat4 &transform, bool transformUpdated);
    
    // Overrides
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
