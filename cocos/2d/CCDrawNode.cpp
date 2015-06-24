
/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2015 Chukong Technologies Inc.
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

#include "2d/CCDrawNode.h"
#include "2d/CCActionCatmullRom.h"
#include "base/allocator/CCAllocatorMacros.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCVertexIndexData.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"

NS_CC_BEGIN

DrawNode::DrawNode()
    : _vdTriangles(nullptr)
    , _vbTriangles(nullptr)
    , _vdPoints(nullptr)
    , _vbPoints(nullptr)
    , _vdLines(nullptr)
    , _vbLines(nullptr)
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

DrawNode::~DrawNode()
{
    CC_SAFE_RELEASE(_vdTriangles);
    CC_SAFE_RELEASE(_vbTriangles);
    CC_SAFE_RELEASE(_vdPoints);
    CC_SAFE_RELEASE(_vbPoints);
    CC_SAFE_RELEASE(_vdLines);
    CC_SAFE_RELEASE(_vbLines);
}

bool DrawNode::init()
{
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR));

    _vbTriangles = VertexBuffer::create(sizeof(V2F_C4B_T2F), 2048, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _vdTriangles = VertexData::create(VertexData::Primitive::Triangles);
    _vdTriangles->addStream(_vbTriangles, VertexAttribute(offsetof(V2F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 2));
    _vdTriangles->addStream(_vbTriangles, VertexAttribute(offsetof(V2F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true));
    _vdTriangles->addStream(_vbTriangles, VertexAttribute(offsetof(V2F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, DataType::Float, 2));
    CC_SAFE_RETAIN(_vdTriangles);
    CC_SAFE_RETAIN(_vbTriangles);
    
    _vbLines = VertexBuffer::create(sizeof(V2F_C4B_T2F), 2048, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _vdLines = VertexData::create(VertexData::Primitive::Lines);
    _vdLines->addStream(_vbLines, VertexAttribute(offsetof(V2F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 2));
    _vdLines->addStream(_vbLines, VertexAttribute(offsetof(V2F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true));
    _vdLines->addStream(_vbLines, VertexAttribute(offsetof(V2F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, DataType::Float, 2));
    CC_SAFE_RETAIN(_vdLines);
    CC_SAFE_RETAIN(_vbLines);

    _vbPoints = VertexBuffer::create(sizeof(V2F_C4B_PF), 2048, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _vdPoints = VertexData::create(VertexData::Primitive::Points);
    _vdPoints->addStream(_vbPoints, VertexAttribute(offsetof(V2F_C4B_PF, vertices),  GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 2));
    _vdPoints->addStream(_vbPoints, VertexAttribute(offsetof(V2F_C4B_PF, colors),    GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true));
    _vdPoints->addStream(_vbPoints, VertexAttribute(offsetof(V2F_C4B_PF, pointSize), GLProgram::VERTEX_ATTRIB_POINTSIZE, DataType::Float, 1));
    CC_SAFE_RETAIN(_vdPoints);
    CC_SAFE_RETAIN(_vbPoints);
    
    return true;
}

void DrawNode::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    if (!_vdTriangles->empty())
    {
        _batchCommandTriangles.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdTriangles, transform);
        renderer->addCommand(&_batchCommandTriangles);
    }
    
    if (!_vdLines->empty())
    {
        _batchCommandLines.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdLines, transform);
        renderer->addCommand(&_batchCommandLines);
    }
    
    if (!_vdPoints->empty())
    {
        _batchCommandPoints.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdPoints, transform);
        renderer->addCommand(&_batchCommandPoints);
    }
}

// deprecated access method for DrawPrimitives to use DrawNode
CC_DEPRECATED(v3) void DrawNode::drawImmediate(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    if (!_vdTriangles->empty())
    {
        _batchCommandTriangles.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdTriangles, _transform);
        _batchCommandTriangles.execute();
    }
    
    if (!_vdLines->empty())
    {
        _batchCommandLines.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdLines, _transform);
        _batchCommandLines.execute();
    }
    
    if (!_vdPoints->empty())
    {
        _batchCommandPoints.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdPoints, _transform);
        _batchCommandPoints.execute();
    }
}

void DrawNode::drawPoint(const Vec2& position, float pointSize, const Color4F& color)
{
    _vdPoints->append<V2F_C4B_PF>({position, Color4B(color), pointSize});
}

void DrawNode::drawPoints(const Vec2* position, unsigned int numberOfPoints, const Color4F &color, float pointSize)
{
    for (auto i = 0u; i < numberOfPoints; ++i)
        _vdPoints->append<V2F_C4B_PF>({position[i], Color4B(color), pointSize});
}

CC_DEPRECATED(v3) void DrawNode::drawPoints(const Vec2* position, unsigned int numberOfPoints, double pointSize, const Color4F& color)
{
    drawPoints(position, numberOfPoints, color, pointSize);
}

void DrawNode::drawLine(const Vec2& origin, const Vec2& destination, const Color4F& color)
{
    _vdLines->append<V2F_C4B_T2F>({origin,      Color4B(color), Tex2F()});
    _vdLines->append<V2F_C4B_T2F>({destination, Color4B(color), Tex2F()});
}

void DrawNode::drawRect(const Vec2& origin, const Vec2& destination, const Color4F &color)
{
    drawLine(Vec2(origin.x, origin.y),           Vec2(destination.x, origin.y), color);
    drawLine(Vec2(destination.x, origin.y),      Vec2(destination.x, destination.y), color);
    drawLine(Vec2(destination.x, destination.y), Vec2(origin.x, destination.y), color);
    drawLine(Vec2(origin.x, destination.y),      Vec2(origin.x, origin.y), color);
}

void DrawNode::drawPoly(const Vec2* poli, unsigned int numberOfPoints, bool closePolygon, const Color4F& color)
{
    unsigned int i = 0;
    for(; i < numberOfPoints - 1; ++i)
    {
        _vdLines->append<V2F_C4B_T2F>({poli[i],   Color4B(color), Tex2F()});
        _vdLines->append<V2F_C4B_T2F>({poli[i+1], Color4B(color), Tex2F()});
    }

    if (closePolygon)
    {
        _vdLines->append<V2F_C4B_T2F>({poli[i], Color4B(color), Tex2F()});
        _vdLines->append<V2F_C4B_T2F>({poli[0], Color4B(color), Tex2F()});
    }
}

void DrawNode::drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F& color)
{
    const float coef = 2.f * (float)M_PI/segments;
    
    auto vertices = (Vec2*)CC_ALLOCA((segments + 2) * sizeof(Vec2));
    
    for (auto i = 0u; i <= segments; ++i)
    {
        float rads = i*coef;
        GLfloat j = radius * cosf(rads + angle) * scaleX + center.x;
        GLfloat k = radius * sinf(rads + angle) * scaleY + center.y;
        
        vertices[i].x = j;
        vertices[i].y = k;
    }
    if(drawLineToCenter)
    {
        vertices[segments+1].x = center.x;
        vertices[segments+1].y = center.y;
        drawPoly(vertices, segments+2, true, color);
    }
    else
        drawPoly(vertices, segments+1, true, color);
}

void DrawNode::drawCircle(const Vec2 &center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const Color4F& color)
{
    drawCircle(center, radius, angle, segments, drawLineToCenter, 1.f, 1.f, color);
}

void DrawNode::drawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments, const Color4F& color)
{
    auto vertices = (Vec2*)CC_ALLOCA((segments + 1) * sizeof(Vec2));
    
    float t = 0.f;
    for (auto i = 0u; i < segments; ++i)
    {
        vertices[i].x = powf(1 - t, 2) * origin.x + 2.f * (1 - t) * t * control.x + t * t * destination.x;
        vertices[i].y = powf(1 - t, 2) * origin.y + 2.f * (1 - t) * t * control.y + t * t * destination.y;
        t += 1.f / segments;
    }
    vertices[segments].x = destination.x;
    vertices[segments].y = destination.y;
    
    drawPoly(vertices, segments+1, false, color);
}

void DrawNode::drawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments, const Color4F& color)
{
    auto vertices = (Vec2*)CC_ALLOCA((segments + 1) * sizeof(Vec2));
    
    float t = 0;
    for (unsigned int i = 0; i < segments; i++)
    {
        vertices[i].x = powf(1 - t, 3) * origin.x + 3.f * powf(1 - t, 2) * t * control1.x + 3.f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
        vertices[i].y = powf(1 - t, 3) * origin.y + 3.f * powf(1 - t, 2) * t * control1.y + 3.f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
        t += 1.f / segments;
    }
    vertices[segments].x = destination.x;
    vertices[segments].y = destination.y;
    
    drawPoly(vertices, segments+1, false, color);
}

void DrawNode::drawCardinalSpline(PointArray *config, float tension,  unsigned int segments, const Color4F &color)
{
    auto vertices = (Vec2*)CC_ALLOCA((segments + 1) * sizeof(Vec2));
    
    ssize_t p;
    float lt;
    float deltaT = 1.f / config->count();
    
    for (unsigned i = 0; i <= segments; ++i)
    {
        float dt = (float)i / segments;
        
        // border
        if( dt == 1 ) {
            p = config->count() - 1;
            lt = 1;
        } else {
            p = dt / deltaT;
            lt = (dt - deltaT * (float)p) / deltaT;
        }
        
        // Interpolate
        Vec2 pp0 = config->getControlPointAtIndex(p-1);
        Vec2 pp1 = config->getControlPointAtIndex(p+0);
        Vec2 pp2 = config->getControlPointAtIndex(p+1);
        Vec2 pp3 = config->getControlPointAtIndex(p+2);
        
        Vec2 newPos = ccCardinalSplineAt(pp0, pp1, pp2, pp3, tension, lt);
        vertices[i].x = newPos.x;
        vertices[i].y = newPos.y;
    }
    
    drawPoly(vertices, segments+1, false, color);
}

void DrawNode::drawCatmullRom(PointArray *points, unsigned int segments, const Color4F &color)
{
    drawCardinalSpline( points, 0.5f, segments, color);
}

void DrawNode::drawDot(const Vec2 &pos, float radius, const Color4F &color)
{
    V2F_C4B_T2F a = {Vec2(pos.x - radius, pos.y - radius), Color4B(color), Tex2F(-1.0, -1.0) };
    V2F_C4B_T2F b = {Vec2(pos.x - radius, pos.y + radius), Color4B(color), Tex2F(-1.0,  1.0) };
    V2F_C4B_T2F c = {Vec2(pos.x + radius, pos.y + radius), Color4B(color), Tex2F( 1.0,  1.0) };
    V2F_C4B_T2F d = {Vec2(pos.x + radius, pos.y - radius), Color4B(color), Tex2F( 1.0, -1.0) };
    _vdTriangles->append<V2F_C4B_T2F>(a);
    _vdTriangles->append<V2F_C4B_T2F>(b);
    _vdTriangles->append<V2F_C4B_T2F>(c);
    _vdTriangles->append<V2F_C4B_T2F>(a);
    _vdTriangles->append<V2F_C4B_T2F>(c);
    _vdTriangles->append<V2F_C4B_T2F>(d);
}

void DrawNode::drawRect(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2& p4, const Color4F &color)
{
    drawLine(Vec2(p1.x, p1.y), Vec2(p2.x, p2.y), color);
    drawLine(Vec2(p2.x, p2.y), Vec2(p3.x, p3.y), color);
    drawLine(Vec2(p3.x, p3.y), Vec2(p4.x, p4.y), color);
    drawLine(Vec2(p4.x, p4.y), Vec2(p1.x, p1.y), color);
}

void DrawNode::drawSegment(const Vec2& from, const Vec2& to, float radius, const Color4F& color)
{
    Vec2 a = from;
    Vec2 b = to;
    
    Vec2 d = b - a;
    Vec2 p = d.getPerp();
    Vec2 n = p.getNormalized();
    Vec2 t = n.getPerp();
    
    Vec2 nw = n * radius;
    Vec2 tw = t * radius;
    Vec2 v0 = b - (nw + tw);
    Vec2 v1 = b + (nw - tw);
    Vec2 v2 = b - nw;
    Vec2 v3 = b + nw;
    Vec2 v4 = a - nw;
    Vec2 v5 = a + nw;
    Vec2 v6 = a - (nw - tw);
    Vec2 v7 = a + (nw + tw);
    
    Color4B c(color);

    _vdTriangles->append<V2F_C4B_T2F>({v0, c, -(n + t)});
    _vdTriangles->append<V2F_C4B_T2F>({v1, c, n - t});
    _vdTriangles->append<V2F_C4B_T2F>({v2, c, -n});
    _vdTriangles->append<V2F_C4B_T2F>({v3, c, n});
    _vdTriangles->append<V2F_C4B_T2F>({v1, c, n - t});
    _vdTriangles->append<V2F_C4B_T2F>({v2, c, -n});
    _vdTriangles->append<V2F_C4B_T2F>({v3, c, n});
    _vdTriangles->append<V2F_C4B_T2F>({v4, c, -n});
    _vdTriangles->append<V2F_C4B_T2F>({v2, c, -n});
    _vdTriangles->append<V2F_C4B_T2F>({v3, c, n});
    _vdTriangles->append<V2F_C4B_T2F>({v4, c, -n});
    _vdTriangles->append<V2F_C4B_T2F>({v5, c, n});
    _vdTriangles->append<V2F_C4B_T2F>({v6, c, t - n});
    _vdTriangles->append<V2F_C4B_T2F>({v4, c, -n});
    _vdTriangles->append<V2F_C4B_T2F>({v5, c, n});
    _vdTriangles->append<V2F_C4B_T2F>({v6, c, t - n});
    _vdTriangles->append<V2F_C4B_T2F>({v7, c, n + t});
    _vdTriangles->append<V2F_C4B_T2F>({v5, c, n});
}

void DrawNode::drawPolygon(const Vec2* verts, int count, const Color4F& fillColor, float borderWidth, const Color4F& borderColor)
{
    CCASSERT(count >= 0, "invalid count value");
    
    Color4B fc(fillColor);
    Color4B bc(borderColor);
    
    bool outline = (borderColor.a > 0.0 && borderWidth > 0.0);
    
    for (int i = 0; i < count-2; ++i)
    {
        _vdTriangles->append<V2F_C4B_T2F>({verts[0],   fc, Tex2F()});
        _vdTriangles->append<V2F_C4B_T2F>({verts[i+1], fc, Tex2F()});
        _vdTriangles->append<V2F_C4B_T2F>({verts[i+2], fc, Tex2F()});
    }
    
    if (outline)
    {
        struct ExtrudeVerts {Vec2 offset, n;};
        auto extrude = (struct ExtrudeVerts*)CC_ALLOCA(sizeof(struct ExtrudeVerts)*count);
        memset(extrude, 0, sizeof(struct ExtrudeVerts)*count);
        
        for (auto i = 0; i < count; ++i)
        {
            Vec2 v0 = verts[(i-1+count)%count];
            Vec2 v1 = verts[i];
            Vec2 v2 = verts[(i+1)%count];
            
            Vec2 n1 = (v1 - v0).getPerp().getNormalized();
            Vec2 n2 = (v2 - v1).getPerp().getNormalized();
            
            Vec2 offset = (n1 + n2) * (1.f / (Vec2::dot(n1, n2) + 1.f));
            extrude[i] = {offset, n2};
        }
        
        for (auto i = 0; i < count; ++i)
        {
            int j = (i+1)%count;
            Vec2 v0 = verts[i];
            Vec2 v1 = verts[j];
            
            Vec2 n0 = extrude[i].n;
            
            Vec2 offset0 = extrude[i].offset;
            Vec2 offset1 = extrude[j].offset;
            
            Vec2 inner0 = v0 - offset0 * borderWidth;
            Vec2 inner1 = v1 - offset1 * borderWidth;
            Vec2 outer0 = v0 + offset0 * borderWidth;
            Vec2 outer1 = v1 + offset1 * borderWidth;
            
            _vdTriangles->append<V2F_C4B_T2F>({inner0, bc, -n0});
            _vdTriangles->append<V2F_C4B_T2F>({inner1, bc, -n0});
            _vdTriangles->append<V2F_C4B_T2F>({outer1, bc,  n0});
            
            _vdTriangles->append<V2F_C4B_T2F>({inner0, bc, -n0});
            _vdTriangles->append<V2F_C4B_T2F>({outer0, bc,  n0});
            _vdTriangles->append<V2F_C4B_T2F>({outer1, bc,  n0});
        }
    }
}

void DrawNode::drawSolidRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color)
{
    Vec2 vertices[] = {
        origin,
        Vec2(destination.x, origin.y),
        destination,
        Vec2(origin.x, destination.y)
    };
    
    drawSolidPoly(vertices, 4, color );
}

void DrawNode::drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, const Color4F &color)
{
    drawPolygon(poli, numberOfPoints, color, 0.f, Color4F());
}

void DrawNode::drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY, const Color4F &color)
{
    const float coef = 2.f * (float)M_PI/segments;
    
    Vec2* vertices = (Vec2*)CC_ALLOCA(segments * sizeof(Vec2));
    if (!vertices)
        return;
    
    for (auto i = 0u; i < segments; ++i)
    {
        float rads = i*coef;
        float j = radius * cosf(rads + angle) * scaleX + center.x;
        float k = radius * sinf(rads + angle) * scaleY + center.y;
        
        vertices[i].x = j;
        vertices[i].y = k;
    }
    
    drawSolidPoly(vertices, segments, color);
}

void DrawNode::drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments, const Color4F& color)
{
    drawSolidCircle(center, radius, angle, segments, 1.f, 1.f, color);
}

void DrawNode::drawTriangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Color4F& color)
{
    Color4B col(color);
    _vdTriangles->append<V2F_C4B_T2F>({Vec2(p1.x, p1.y), col, Tex2F(0.f, 0.f)});
    _vdTriangles->append<V2F_C4B_T2F>({Vec2(p2.x, p2.y), col, Tex2F(0.f, 0.f)});
    _vdTriangles->append<V2F_C4B_T2F>({Vec2(p3.x, p3.y), col, Tex2F(0.f, 0.f)});
}

void DrawNode::drawQuadraticBezier(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments, const Color4F &color)
{
    drawQuadBezier(from, control, to, segments, color);
}

void DrawNode::clear()
{
    _vdTriangles->clear();
    _vdLines->clear();
    _vdPoints->clear();
}

NS_CC_END
