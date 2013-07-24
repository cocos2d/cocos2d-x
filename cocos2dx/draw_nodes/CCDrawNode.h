/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
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

#include "base_nodes/CCNode.h"
#include "ccTypes.h"

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
    DrawNode();
    virtual ~DrawNode();
    
    virtual bool init();

    /** draw a dot at a position, with a given radius and color */
    void drawDot(const Point &pos, float radius, const Color4F &color);
    
    /** draw a segment with a radius and color */
    void drawSegment(const Point &from, const Point &to, float radius, const Color4F &color);
    
    /** draw a polygon with a fill color and line color */
    void drawPolygon(Point *verts, unsigned int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
    
    /** Clear the geometry in the node's buffer. */
    void clear();
    
    const BlendFunc& getBlendFunc() const;
    void setBlendFunc(const BlendFunc &blendFunc);
    
    /** listen the event that coming to foreground on Android
     */
    void listenBackToForeground(Object *obj);

    // Overrides
    virtual void draw() override;

protected:
    void ensureCapacity(int count);
    void render();

    GLuint      _vao;
    GLuint      _vbo;

    int         _bufferCapacity;
    GLsizei     _bufferCount;
    V2F_C4B_T2F *_buffer;

    BlendFunc   _blendFunc;

    bool        _dirty;
};

NS_CC_END

#endif // __CCDRAWNODES_CCDRAW_NODE_H__
