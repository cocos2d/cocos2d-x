
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
#include "renderer/CCRenderer.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCVertexIndexData.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "2d/CCActionCatmullRom.h"
#include "base/allocator/CCAllocatorMacros.h"

NS_CC_BEGIN

// Vec2 == CGPoint in 32-bits, but not in 64-bits (OS X)
// that's why the "v2f" functions are needed
static Vec2 v2fzero(0.0f,0.0f);

static inline Vec2 v2f(float x, float y)
{
    Vec2 ret(x, y);
    return ret;
}

static inline Vec2 v2fadd(const Vec2 &v0, const Vec2 &v1)
{
    return v2f(v0.x+v1.x, v0.y+v1.y);
}

static inline Vec2 v2fsub(const Vec2 &v0, const Vec2 &v1)
{
    return v2f(v0.x-v1.x, v0.y-v1.y);
}

static inline Vec2 v2fmult(const Vec2 &v, float s)
{
    return v2f(v.x * s, v.y * s);
}

static inline Vec2 v2fperp(const Vec2 &p0)
{
    return v2f(-p0.y, p0.x);
}

static inline Vec2 v2fneg(const Vec2 &p0)
{
    return v2f(-p0.x, - p0.y);
}

static inline float v2fdot(const Vec2 &p0, const Vec2 &p1)
{
    return  p0.x * p1.x + p0.y * p1.y;
}

static inline Vec2 v2fforangle(float _a_)
{
    return v2f(cosf(_a_), sinf(_a_));
}

static inline Vec2 v2fnormalize(const Vec2 &p)
{
    Vec2 r = Vec2(p.x, p.y).getNormalized();
    return v2f(r.x, r.y);
}

static inline Vec2 __v2f(const Vec2 &v)
{
//#ifdef __LP64__
    return v2f(v.x, v.y);
// #else
//     return * ((Vec2*) &v);
// #endif
}

static inline Tex2F __t(const Vec2 &v)
{
    return *(Tex2F*)&v;
}

// implementation of DrawNode

DrawNode::DrawNode()
    : _vbTriangles(nullptr)
    , _vdTriangles(nullptr)
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

DrawNode* DrawNode::create()
{
    DrawNode* ret = new (std::nothrow) DrawNode();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool DrawNode::init()
{
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR));

    _vbTriangles = VertexBuffer::create(sizeof(V2F_C4B_T2F), 2048, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _vdTriangles = VertexData::create(VertexData::Primitive::Triangles);
    _vdTriangles->addStream(_vbTriangles, VertexStreamAttribute(offsetof(V2F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION, GL_FLOAT, 2));
    _vdTriangles->addStream(_vbTriangles, VertexStreamAttribute(offsetof(V2F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR, GL_UNSIGNED_BYTE, 4, true));
    _vdTriangles->addStream(_vbTriangles, VertexStreamAttribute(offsetof(V2F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, GL_FLOAT, 2));
    CC_SAFE_RETAIN(_vdTriangles);
    CC_SAFE_RETAIN(_vbTriangles);
    
    _vbLines = VertexBuffer::create(sizeof(V2F_C4B_T2F), 2048, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _vdLines = VertexData::create(VertexData::Primitive::Lines);
    _vdLines->addStream(_vbLines, VertexStreamAttribute(offsetof(V2F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION, GL_FLOAT, 2));
    _vdLines->addStream(_vbLines, VertexStreamAttribute(offsetof(V2F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR, GL_UNSIGNED_BYTE, 4));
    _vdLines->addStream(_vbLines, VertexStreamAttribute(offsetof(V2F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, GL_FLOAT, 2));
    CC_SAFE_RETAIN(_vdLines);
    CC_SAFE_RETAIN(_vbLines);

    _vbPoints = VertexBuffer::create(sizeof(V2F_C4B_PF), 2048, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _vdPoints = VertexData::create(VertexData::Primitive::Points);
    _vdPoints->addStream(_vbPoints, VertexStreamAttribute(offsetof(V2F_C4B_PF, vertices),  GLProgram::VERTEX_ATTRIB_POSITION, GL_FLOAT, 2));
    _vdPoints->addStream(_vbPoints, VertexStreamAttribute(offsetof(V2F_C4B_PF, colors),    GLProgram::VERTEX_ATTRIB_COLOR, GL_UNSIGNED_BYTE, 4));
    _vdPoints->addStream(_vbPoints, VertexStreamAttribute(offsetof(V2F_C4B_PF, pointSize), GLProgram::VERTEX_ATTRIB_POINTSIZE, GL_FLOAT, 2));
    CC_SAFE_RETAIN(_vdPoints);
    CC_SAFE_RETAIN(_vbPoints);
    
    return true;
}

void DrawNode::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    if (!_vdTriangles->empty())
    {
        _batchCommandTriangles.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdTriangles, _transform);
        renderer->addCommand(&_batchCommandTriangles);
    }
    
    if (!_vdLines->empty())
    {
        _batchCommandLines.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdLines, _transform);
        renderer->addCommand(&_batchCommandLines);
    }
    
    if (!_vdPoints->empty())
    {
        _batchCommandPoints.init(_globalZOrder, getGLProgram(), _blendFunc, nullptr, _vdPoints, _transform);
        renderer->addCommand(&_batchCommandPoints);
    }
}

void DrawNode::drawPoint(const Vec2& position, const float pointSize, const Color4F &color)
{
    _vdPoints->append<V2F_C4B_PF>({position, Color4B(color), pointSize});
}

void DrawNode::drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color, float pointSize)
{
    for (auto i = 0; i < numberOfPoints; ++i)
        _vdPoints->append<V2F_C4B_PF>({position[i], Color4B(color), pointSize});
}

void DrawNode::drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color)
{
    _vdLines->append<V2F_C4B_T2F>({origin,      Color4B(color), Tex2F(0.0, 0.0)});
    _vdLines->append<V2F_C4B_T2F>({destination, Color4B(color), Tex2F(0.0, 0.0)});
}

void DrawNode::drawRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color)
{
    drawLine(Vec2(origin.x, origin.y),           Vec2(destination.x, origin.y), color);
    drawLine(Vec2(destination.x, origin.y),      Vec2(destination.x, destination.y), color);
    drawLine(Vec2(destination.x, destination.y), Vec2(origin.x, destination.y), color);
    drawLine(Vec2(origin.x, destination.y),      Vec2(origin.x, origin.y), color);
}

void DrawNode::drawPoly(const Vec2* poli, unsigned int numberOfPoints, bool closePolygon, const Color4F &color)
{
    int i = 0;
    for(; i < numberOfPoints - 1; ++i)
    {
        _vdLines->append<V2F_C4B_T2F>({poli[i],   Color4B(color), Tex2F(0.0, 0.0)});
        _vdLines->append<V2F_C4B_T2F>({poli[i+1], Color4B(color), Tex2F(0.0, 0.0)});
    }

    if (closePolygon)
    {
        _vdLines->append<V2F_C4B_T2F>({poli[i], Color4B(color), Tex2F(0.0, 0.0)});
        _vdLines->append<V2F_C4B_T2F>({poli[0], Color4B(color), Tex2F(0.0, 0.0)});
    }
}

void DrawNode::drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color)
{
    const float coef = 2.0f * (float)M_PI/segments;
    
    auto vertices = (Vec2*)CC_ALLOCA((segments + 2) * sizeof(Vec2));
    
    for (auto i = 0; i <= segments; ++i)
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

void DrawNode::drawCircle(const Vec2 &center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const Color4F &color)
{
    drawCircle(center, radius, angle, segments, drawLineToCenter, 1.0f, 1.0f, color);
}

void DrawNode::drawQuadBezier(const Vec2 &origin, const Vec2 &control, const Vec2 &destination, unsigned int segments, const Color4F &color)
{
    auto vertices = (Vec2*)CC_ALLOCA((segments + 1) * sizeof(Vec2));
    
    float t = 0.0f;
    for (auto i = 0; i < segments; ++i)
    {
        vertices[i].x = powf(1 - t, 2) * origin.x + 2.0f * (1 - t) * t * control.x + t * t * destination.x;
        vertices[i].y = powf(1 - t, 2) * origin.y + 2.0f * (1 - t) * t * control.y + t * t * destination.y;
        t += 1.0f / segments;
    }
    vertices[segments].x = destination.x;
    vertices[segments].y = destination.y;
    
    drawPoly(vertices, segments+1, false, color);
}

void DrawNode::drawCubicBezier(const Vec2 &origin, const Vec2 &control1, const Vec2 &control2, const Vec2 &destination, unsigned int segments, const Color4F &color)
{
    auto vertices = (Vec2*)CC_ALLOCA((segments + 1) * sizeof(Vec2));
    
    float t = 0;
    for (unsigned int i = 0; i < segments; i++)
    {
        vertices[i].x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
        vertices[i].y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
        t += 1.0f / segments;
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
    float deltaT = 1.0f / config->count();
    
    for( unsigned int i=0; i < segments+1;i++) {
        
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
        
        Vec2 newPos = ccCardinalSplineAt( pp0, pp1, pp2, pp3, tension, lt);
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

void DrawNode::drawSegment(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color)
{
    Vec2 a = __v2f(from);
    Vec2 b = __v2f(to);
    
    
    Vec2 n = v2fnormalize(v2fperp(v2fsub(b, a)));
    Vec2 t = v2fperp(n);
    
    Vec2 nw = v2fmult(n, radius);
    Vec2 tw = v2fmult(t, radius);
    Vec2 v0 = v2fsub(b, v2fadd(nw, tw));
    Vec2 v1 = v2fadd(b, v2fsub(nw, tw));
    Vec2 v2 = v2fsub(b, nw);
    Vec2 v3 = v2fadd(b, nw);
    Vec2 v4 = v2fsub(a, nw);
    Vec2 v5 = v2fadd(a, nw);
    Vec2 v6 = v2fsub(a, v2fsub(nw, tw));
    Vec2 v7 = v2fadd(a, v2fadd(nw, tw));

    _vdTriangles->append<V2F_C4B_T2F>({v0, Color4B(color), __t(v2fneg(v2fadd(n, t)))});
    _vdTriangles->append<V2F_C4B_T2F>({v1, Color4B(color), __t(v2fsub(n, t))});
    _vdTriangles->append<V2F_C4B_T2F>({v2, Color4B(color), __t(v2fneg(n))});
    _vdTriangles->append<V2F_C4B_T2F>({v3, Color4B(color), __t(n)});
    _vdTriangles->append<V2F_C4B_T2F>({v1, Color4B(color), __t(v2fsub(n, t))});
    _vdTriangles->append<V2F_C4B_T2F>({v2, Color4B(color), __t(v2fneg(n))});
    _vdTriangles->append<V2F_C4B_T2F>({v3, Color4B(color), __t(n)});
    _vdTriangles->append<V2F_C4B_T2F>({v4, Color4B(color), __t(v2fneg(n))});
    _vdTriangles->append<V2F_C4B_T2F>({v2, Color4B(color), __t(v2fneg(n))});
    _vdTriangles->append<V2F_C4B_T2F>({v3, Color4B(color), __t(n)});
    _vdTriangles->append<V2F_C4B_T2F>({v4, Color4B(color), __t(v2fneg(n))});
    _vdTriangles->append<V2F_C4B_T2F>({v5, Color4B(color), __t(n)});
    _vdTriangles->append<V2F_C4B_T2F>({v6, Color4B(color), __t(v2fsub(t, n))});
    _vdTriangles->append<V2F_C4B_T2F>({v4, Color4B(color), __t(v2fneg(n))});
    _vdTriangles->append<V2F_C4B_T2F>({v5, Color4B(color), __t(n)});
    _vdTriangles->append<V2F_C4B_T2F>({v6, Color4B(color), __t(v2fsub(t, n))});
    _vdTriangles->append<V2F_C4B_T2F>({v7, Color4B(color), __t(v2fadd(n, t))});
    _vdTriangles->append<V2F_C4B_T2F>({v5, Color4B(color), __t(n)});
}

void DrawNode::drawPolygon(const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor)
{
    CCASSERT(count >= 0, "invalid count value");
    
    bool outline = (borderColor.a > 0.0 && borderWidth > 0.0);
    
    for (int i = 0; i < count-2; i++)
    {
        _vdTriangles->append<V2F_C4B_T2F>({verts[0],   Color4B(fillColor), __t(v2fzero)});
        _vdTriangles->append<V2F_C4B_T2F>({verts[i+1], Color4B(fillColor), __t(v2fzero)});
        _vdTriangles->append<V2F_C4B_T2F>({verts[i+2], Color4B(fillColor), __t(v2fzero)});
    }
    
    if (outline)
    {
        struct ExtrudeVerts {Vec2 offset, n;};
        struct ExtrudeVerts* extrude = (struct ExtrudeVerts*)CC_ALLOCA(sizeof(struct ExtrudeVerts)*count);
        memset(extrude, 0, sizeof(struct ExtrudeVerts)*count);
        
        for (int i = 0; i < count; i++)
        {
            Vec2 v0 = __v2f(verts[(i-1+count)%count]);
            Vec2 v1 = __v2f(verts[i]);
            Vec2 v2 = __v2f(verts[(i+1)%count]);
            
            Vec2 n1 = v2fnormalize(v2fperp(v2fsub(v1, v0)));
            Vec2 n2 = v2fnormalize(v2fperp(v2fsub(v2, v1)));
            
            Vec2 offset = v2fmult(v2fadd(n1, n2), 1.0/(v2fdot(n1, n2) + 1.0));
            struct ExtrudeVerts tmp = {offset, n2};
            extrude[i] = tmp;
        }
        
        for(int i = 0; i < count; i++)
        {
            int j = (i+1)%count;
            Vec2 v0 = __v2f(verts[i]);
            Vec2 v1 = __v2f(verts[j]);
            
            Vec2 n0 = extrude[i].n;
            
            Vec2 offset0 = extrude[i].offset;
            Vec2 offset1 = extrude[j].offset;
            
            Vec2 inner0 = v2fsub(v0, v2fmult(offset0, borderWidth));
            Vec2 inner1 = v2fsub(v1, v2fmult(offset1, borderWidth));
            Vec2 outer0 = v2fadd(v0, v2fmult(offset0, borderWidth));
            Vec2 outer1 = v2fadd(v1, v2fmult(offset1, borderWidth));
            
            _vdTriangles->append<V2F_C4B_T2F>({inner0, Color4B(borderColor), __t(v2fneg(n0))});
            _vdTriangles->append<V2F_C4B_T2F>({inner1, Color4B(borderColor), __t(v2fneg(n0))});
            _vdTriangles->append<V2F_C4B_T2F>({outer1, Color4B(borderColor), __t(n0)});
            _vdTriangles->append<V2F_C4B_T2F>({inner0, Color4B(borderColor), __t(v2fneg(n0))});
            _vdTriangles->append<V2F_C4B_T2F>({outer0, Color4B(borderColor), __t(n0)});
            _vdTriangles->append<V2F_C4B_T2F>({outer1, Color4B(borderColor), __t(n0)});
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
    drawPolygon(poli, numberOfPoints, color, 0.0, Color4F(0.0, 0.0, 0.0, 0.0));
}

void DrawNode::drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY, const Color4F &color)
{
    const float coef = 2.0f * (float)M_PI/segments;
    
    Vec2 *vertices = new (std::nothrow) Vec2[segments];
    if( ! vertices )
        return;
    
    for(unsigned int i = 0;i < segments; i++)
    {
        float rads = i*coef;
        GLfloat j = radius * cosf(rads + angle) * scaleX + center.x;
        GLfloat k = radius * sinf(rads + angle) * scaleY + center.y;
        
        vertices[i].x = j;
        vertices[i].y = k;
    }
    
    drawSolidPoly(vertices, segments, color);
    
    CC_SAFE_DELETE_ARRAY(vertices);
}

void DrawNode::drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments, const Color4F& color)
{
    drawSolidCircle(center, radius, angle, segments, 1.0f, 1.0f, color);
}

void DrawNode::drawTriangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Color4F& color)
{
    Color4B col = Color4B(color);
    _vdTriangles->append<V2F_C4B_T2F>({Vec2(p1.x, p1.y), col, Tex2F(0.0, 0.0)});
    _vdTriangles->append<V2F_C4B_T2F>({Vec2(p2.x, p2.y), col, Tex2F(0.0, 0.0)});
    _vdTriangles->append<V2F_C4B_T2F>({Vec2(p3.x, p3.y), col, Tex2F(0.0, 0.0)});
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

const BlendFunc& DrawNode::getBlendFunc() const
{
    return _blendFunc;
}

void DrawNode::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

NS_CC_END
