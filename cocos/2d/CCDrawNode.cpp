/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "2d/CCActionCatmullRom.h"
#include "platform/CCGL.h"
#include "base/ccUtils.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/ProgramState.h"

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

static inline Vec2 v2fnormalize(const Vec2 &p)
{
    Vec2 r(p.x, p.y);
    r.normalize();
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

DrawNode::DrawNode(float lineWidth)
: _lineWidth(lineWidth)
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    //TODO new-renderer: interface setupBuffer removal

    // Need to listen the event only when not use batchnode, because it will use VBO
//    auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
//        /** listen the event that renderer was recreated on Android/WP8 */
//        this->setupBuffer();
//    });

//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
}

DrawNode::~DrawNode()
{
    free(_buffer);
    _buffer = nullptr;
    free(_bufferGLPoint);
    _bufferGLPoint = nullptr;
    free(_bufferGLLine);
    _bufferGLLine = nullptr;
    
    CC_SAFE_RELEASE(_programState);
    CC_SAFE_RELEASE(_programStatePoint);
    CC_SAFE_RELEASE(_programStateLine);
}

DrawNode* DrawNode::create(float defaultLineWidth)
{
    DrawNode* ret = new (std::nothrow) DrawNode(defaultLineWidth);
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

void DrawNode::ensureCapacity(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCount + count > _bufferCapacity)
    {
        _bufferCapacity += MAX(_bufferCapacity, count);
        _buffer = (V2F_C4B_T2F*)realloc(_buffer, _bufferCapacity*sizeof(V2F_C4B_T2F));
        
        _customCommand.createVertexBuffer(sizeof(V2F_C4B_T2F), _bufferCapacity, CustomCommand::BufferUsage::STATIC);
        _customCommand.updateVertexBuffer(_buffer, _bufferCapacity*sizeof(V2F_C4B_T2F));
    }
}

void DrawNode::ensureCapacityGLPoint(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCountGLPoint + count > _bufferCapacityGLPoint)
    {
        _bufferCapacityGLPoint += MAX(_bufferCapacityGLPoint, count);
        _bufferGLPoint = (V2F_C4B_T2F*)realloc(_bufferGLPoint, _bufferCapacityGLPoint*sizeof(V2F_C4B_T2F));
        
        _customCommandGLPoint.createVertexBuffer(sizeof(V2F_C4B_T2F), _bufferCapacityGLPoint, CustomCommand::BufferUsage::STATIC);
        _customCommandGLPoint.updateVertexBuffer(_bufferGLPoint, _bufferCapacityGLPoint*sizeof(V2F_C4B_T2F));
    }
}

void DrawNode::ensureCapacityGLLine(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCountGLLine + count > _bufferCapacityGLLine)
    {
        _bufferCapacityGLLine += MAX(_bufferCapacityGLLine, count);
        _bufferGLLine = (V2F_C4B_T2F*)realloc(_bufferGLLine, _bufferCapacityGLLine*sizeof(V2F_C4B_T2F));
        
        _customCommandGLLine.createVertexBuffer(sizeof(V2F_C4B_T2F), _bufferCapacityGLLine, CustomCommand::BufferUsage::STATIC);
        _customCommandGLLine.updateVertexBuffer(_bufferGLLine, _bufferCapacityGLLine*sizeof(V2F_C4B_T2F));
    }
}

bool DrawNode::init()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    updateShader();
    ensureCapacity(512);
    ensureCapacityGLPoint(64);
    ensureCapacityGLLine(256);
    
    _dirty = true;
    _dirtyGLLine = true;
    _dirtyGLPoint = true;
    return true;
}

void DrawNode::updateShader()
{
    CC_SAFE_RELEASE(_programState);
    _programState = new (std::nothrow) backend::ProgramState(positionColorLengthTexture_vert, positionColorLengthTexture_frag);
    _customCommand.getPipelineDescriptor().programState = _programState;
    setVertexLayout(_customCommand);
    _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE);

    CC_SAFE_RELEASE(_programStatePoint);
    _programStatePoint = new (std::nothrow) backend::ProgramState(positionColorTextureAsPointsize_vert, positionColor_frag);
    _customCommandGLPoint.getPipelineDescriptor().programState = _programStatePoint;
    setVertexLayout(_customCommandGLPoint);
    _customCommandGLPoint.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommandGLPoint.setPrimitiveType(CustomCommand::PrimitiveType::POINT);

    CC_SAFE_RELEASE(_programStateLine);
    _programStateLine = new (std::nothrow) backend::ProgramState(positionColorLengthTexture_vert, positionColorLengthTexture_frag);
    _customCommandGLLine.getPipelineDescriptor().programState = _programStateLine;
    setVertexLayout(_customCommandGLLine);
    _customCommandGLLine.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommandGLLine.setPrimitiveType(CustomCommand::PrimitiveType::LINE);
}

void DrawNode::setVertexLayout(CustomCommand& cmd)
{
    auto* programState = cmd.getPipelineDescriptor().programState;
    auto& layout = cmd.getPipelineDescriptor().vertexLayout;
    const auto& attributeInfo = programState->getProgram()->getActiveAttributes();
    auto iter = attributeInfo.find("a_position");
    if(iter != attributeInfo.end())
    {
        layout.setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT2, 0, false);
    }
    
    iter = attributeInfo.find("a_texCoord");
    if(iter != attributeInfo.end())
    {
        layout.setAttribute("a_texCoord", iter->second.location, backend::VertexFormat::FLOAT2, offsetof(V2F_C4B_T2F, texCoords), false);
    }
    
    iter = attributeInfo.find("a_color");
    if(iter != attributeInfo.end())
    {
        layout.setAttribute("a_color", iter->second.location, backend::VertexFormat::UBYTE4, offsetof(V2F_C4B_T2F, colors), true);
    }
    layout.setLayout(sizeof(V2F_C4B_T2F));
}

void DrawNode::updateBlendState(CustomCommand& cmd)
{
    backend::BlendDescriptor& blendDescriptor = cmd.getPipelineDescriptor().blendDescriptor;
    blendDescriptor.blendEnabled = true;
    if (_blendFunc == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        blendDescriptor.sourceRGBBlendFactor = backend::BlendFactor::SRC_ALPHA;
        blendDescriptor.destinationRGBBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
        blendDescriptor.sourceAlphaBlendFactor = backend::BlendFactor::SRC_ALPHA;
        blendDescriptor.destinationAlphaBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
        setOpacityModifyRGB(false);
    }
    else
    {
        blendDescriptor.sourceRGBBlendFactor = backend::BlendFactor::ONE;
        blendDescriptor.destinationRGBBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
        blendDescriptor.sourceAlphaBlendFactor = backend::BlendFactor::ONE;
        blendDescriptor.destinationAlphaBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
        setOpacityModifyRGB(true);
    }
}

void DrawNode::updateUniforms(const Mat4 &transform, CustomCommand& cmd)
{
    auto& pipelineDescriptor = cmd.getPipelineDescriptor();
    const auto& matrixP = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Mat4 matrixMVP = matrixP * transform;
    auto mvpLocation = pipelineDescriptor.programState->getUniformLocation("u_MVPMatrix");
    pipelineDescriptor.programState->setUniform(mvpLocation, matrixMVP.m, sizeof(matrixMVP.m));

    float alpha = _displayedOpacity / 255.0;
    auto alphaUniformLocation = pipelineDescriptor.programState->getUniformLocation("u_alpha");
    pipelineDescriptor.programState->setUniform(alphaUniformLocation, &alpha, sizeof(alpha));
}

void DrawNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if(_bufferCount)
    {
        updateBlendState(_customCommand);
        updateUniforms(transform, _customCommand);
        _customCommand.init(_globalZOrder);
        renderer->addCommand(&_customCommand);
    }
    
    if(_bufferCountGLPoint)
    {
        updateBlendState(_customCommandGLPoint);
        updateUniforms(transform, _customCommandGLPoint);
        _customCommandGLPoint.init(_globalZOrder);
        renderer->addCommand(&_customCommandGLPoint);
    }
    
    if(_bufferCountGLLine)
    {
        updateBlendState(_customCommandGLLine);
        updateUniforms(transform, _customCommandGLLine);
        _customCommandGLLine.setLineWidth(_lineWidth);
        _customCommandGLLine.init(_globalZOrder);
        renderer->addCommand(&_customCommandGLLine);
    }
}

void DrawNode::drawPoint(const Vec2& position, const float pointSize, const Color4F &color)
{
    ensureCapacityGLPoint(1);
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLPoint + _bufferCountGLPoint);
    V2F_C4B_T2F a = {position, Color4B(color), Tex2F(pointSize,0)};
    *point = a;
    
    _customCommandGLPoint.updateVertexBuffer(point, _bufferCountGLPoint*sizeof(V2F_C4B_T2F), sizeof(V2F_C4B_T2F));
    _bufferCountGLPoint += 1;
    _dirtyGLPoint = true;
    _customCommandGLPoint.setVertexDrawInfo(0, _bufferCountGLPoint);
}

void DrawNode::drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color)
{
    drawPoints(position, numberOfPoints, 1.0, color);
}

void DrawNode::drawPoints(const Vec2 *position, unsigned int numberOfPoints, const float pointSize, const Color4F &color)
{
    ensureCapacityGLPoint(numberOfPoints);
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLPoint + _bufferCountGLPoint);
    for(unsigned int i=0; i < numberOfPoints; i++)
    {
        V2F_C4B_T2F a = {position[i], Color4B(color), Tex2F(pointSize,0)};
        *(point + i) = a;
    }
    
    _customCommandGLPoint.updateVertexBuffer(point, _bufferCountGLPoint*sizeof(V2F_C4B_T2F), numberOfPoints*sizeof(V2F_C4B_T2F));
    _bufferCountGLPoint += numberOfPoints;
    _dirtyGLPoint = true;
    _customCommandGLPoint.setVertexDrawInfo(0, _bufferCountGLPoint);
}

void DrawNode::drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color)
{
    ensureCapacityGLLine(2);
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLLine + _bufferCountGLLine);
    
    V2F_C4B_T2F a = {origin, Color4B(color), Tex2F(0.0, 0.0)};
    V2F_C4B_T2F b = {destination, Color4B(color), Tex2F(0.0, 0.0)};
    
    *point = a;
    *(point+1) = b;
    
    _customCommandGLLine.updateVertexBuffer(point, _bufferCountGLLine*sizeof(V2F_C4B_T2F), 2*sizeof(V2F_C4B_T2F));
    _bufferCountGLLine += 2;
    _dirtyGLLine = true;
    _customCommandGLLine.setVertexDrawInfo(0, _bufferCountGLLine);
}

void DrawNode::drawRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color)
{
    drawLine(Vec2(origin.x, origin.y), Vec2(destination.x, origin.y), color);
    drawLine(Vec2(destination.x, origin.y), Vec2(destination.x, destination.y), color);
    drawLine(Vec2(destination.x, destination.y), Vec2(origin.x, destination.y), color);
    drawLine(Vec2(origin.x, destination.y), Vec2(origin.x, origin.y), color);
}

void DrawNode::drawPoly(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon, const Color4F &color)
{
    unsigned int vertex_count;
    if(closePolygon)
    {
        vertex_count = 2 * numberOfPoints;
        ensureCapacityGLLine(vertex_count);
    }
    else
    {
        vertex_count = 2 * (numberOfPoints - 1);
        ensureCapacityGLLine(vertex_count);
    }
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLLine + _bufferCountGLLine);
    V2F_C4B_T2F *cursor = point;
    
    unsigned int i = 0;
    for(; i<numberOfPoints-1; i++)
    {
        V2F_C4B_T2F a = {poli[i], Color4B(color), Tex2F(0.0, 0.0)};
        V2F_C4B_T2F b = {poli[i+1], Color4B(color), Tex2F(0.0, 0.0)};
        
        *point = a;
        *(point+1) = b;
        point += 2;
    }
    if(closePolygon)
    {
        V2F_C4B_T2F a = {poli[i], Color4B(color), Tex2F(0.0, 0.0)};
        V2F_C4B_T2F b = {poli[0], Color4B(color), Tex2F(0.0, 0.0)};
        *point = a;
        *(point+1) = b;
    }
    
    _customCommandGLLine.updateVertexBuffer(cursor, _bufferCountGLLine*sizeof(V2F_C4B_T2F), vertex_count*sizeof(V2F_C4B_T2F));
    _bufferCountGLLine += vertex_count;
    _customCommandGLLine.setVertexDrawInfo(0, _bufferCountGLLine);
}

void DrawNode::drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color)
{
    const float coef = 2.0f * (float)M_PI/segments;
    
    Vec2 *vertices = new (std::nothrow) Vec2[segments+2];
    if( ! vertices )
        return;
    
    for(unsigned int i = 0;i <= segments; i++) {
        float rads = i*coef;
        float j = radius * cosf(rads + angle) * scaleX + center.x;
        float k = radius * sinf(rads + angle) * scaleY + center.y;
        
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
    
    CC_SAFE_DELETE_ARRAY(vertices);
}

void DrawNode::drawCircle(const Vec2 &center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const Color4F &color)
{
    drawCircle(center, radius, angle, segments, drawLineToCenter, 1.0f, 1.0f, color);
}

void DrawNode::drawQuadBezier(const Vec2 &origin, const Vec2 &control, const Vec2 &destination, unsigned int segments, const Color4F &color)
{
    Vec2* vertices = new (std::nothrow) Vec2[segments + 1];
    if( ! vertices )
        return;
    
    float t = 0.0f;
    for(unsigned int i = 0; i < segments; i++)
    {
        vertices[i].x = powf(1 - t, 2) * origin.x + 2.0f * (1 - t) * t * control.x + t * t * destination.x;
        vertices[i].y = powf(1 - t, 2) * origin.y + 2.0f * (1 - t) * t * control.y + t * t * destination.y;
        t += 1.0f / segments;
    }
    vertices[segments].x = destination.x;
    vertices[segments].y = destination.y;
    
    drawPoly(vertices, segments+1, false, color);

    CC_SAFE_DELETE_ARRAY(vertices);
}

void DrawNode::drawCubicBezier(const Vec2 &origin, const Vec2 &control1, const Vec2 &control2, const Vec2 &destination, unsigned int segments, const Color4F &color)
{
    Vec2* vertices = new (std::nothrow) Vec2[segments + 1];
    if( ! vertices )
        return;
    
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

    CC_SAFE_DELETE_ARRAY(vertices);
}

void DrawNode::drawCardinalSpline(PointArray *config, float tension,  unsigned int segments, const Color4F &color)
{
    Vec2* vertices = new (std::nothrow) Vec2[segments + 1];
    if( ! vertices )
        return;
    
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
    
    CC_SAFE_DELETE_ARRAY(vertices);
}

void DrawNode::drawCatmullRom(PointArray *points, unsigned int segments, const Color4F &color)
{
    drawCardinalSpline( points, 0.5f, segments, color);
}

void DrawNode::drawDot(const Vec2 &pos, float radius, const Color4F &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);
    
    V2F_C4B_T2F a = {Vec2(pos.x - radius, pos.y - radius), Color4B(color), Tex2F(-1.0, -1.0) };
    V2F_C4B_T2F b = {Vec2(pos.x - radius, pos.y + radius), Color4B(color), Tex2F(-1.0,  1.0) };
    V2F_C4B_T2F c = {Vec2(pos.x + radius, pos.y + radius), Color4B(color), Tex2F( 1.0,  1.0) };
    V2F_C4B_T2F d = {Vec2(pos.x + radius, pos.y - radius), Color4B(color), Tex2F( 1.0, -1.0) };
    
    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle0 = {a, b, c};
    V2F_C4B_T2F_Triangle triangle1 = {a, c, d};
    triangles[0] = triangle0;
    triangles[1] = triangle1;
    
    _customCommand.updateVertexBuffer(triangles, _bufferCount*sizeof(V2F_C4B_T2F), vertex_count*sizeof(V2F_C4B_T2F));
    _bufferCount += vertex_count;
    _dirty = true;
    _customCommand.setVertexDrawInfo(0, _bufferCount);
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
    unsigned int vertex_count = 6*3;
    ensureCapacity(vertex_count);
    
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
    
    
    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    
    V2F_C4B_T2F_Triangle triangles0 = {
        {v0, Color4B(color), __t(v2fneg(v2fadd(n, t)))},
        {v1, Color4B(color), __t(v2fsub(n, t))},
        {v2, Color4B(color), __t(v2fneg(n))},
    };
    triangles[0] = triangles0;
    
    V2F_C4B_T2F_Triangle triangles1 = {
        {v3, Color4B(color), __t(n)},
        {v1, Color4B(color), __t(v2fsub(n, t))},
        {v2, Color4B(color), __t(v2fneg(n))},
    };
    triangles[1] = triangles1;
    
    V2F_C4B_T2F_Triangle triangles2 = {
        {v3, Color4B(color), __t(n)},
        {v4, Color4B(color), __t(v2fneg(n))},
        {v2, Color4B(color), __t(v2fneg(n))},
    };
    triangles[2] = triangles2;

    V2F_C4B_T2F_Triangle triangles3 = {
        {v3, Color4B(color), __t(n)},
        {v4, Color4B(color), __t(v2fneg(n))},
        {v5, Color4B(color), __t(n) },
    };
    triangles[3] = triangles3;

    V2F_C4B_T2F_Triangle triangles4 = {
        {v6, Color4B(color), __t(v2fsub(t, n))},
        {v4, Color4B(color), __t(v2fneg(n)) },
        {v5, Color4B(color), __t(n)},
    };
    triangles[4] = triangles4;

    V2F_C4B_T2F_Triangle triangles5 = {
        {v6, Color4B(color), __t(v2fsub(t, n))},
        {v7, Color4B(color), __t(v2fadd(n, t))},
        {v5, Color4B(color), __t(n)},
    };
    triangles[5] = triangles5;
    
    _customCommand.updateVertexBuffer(triangles, _bufferCount*sizeof(V2F_C4B_T2F), vertex_count*sizeof(V2F_C4B_T2F));
    _bufferCount += vertex_count;
    _dirty = true;
    _customCommand.setVertexDrawInfo(0, _bufferCount);
}

void DrawNode::drawPolygon(const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor)
{
    CCASSERT(count >= 0, "invalid count value");
    
    bool outline = (borderColor.a > 0.0f && borderWidth > 0.0f);
    
    auto  triangle_count = outline ? (3*count - 2) : (count - 2);
    auto vertex_count = 3*triangle_count;
    ensureCapacity(vertex_count);
    
    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle *cursor = triangles;
    
    for (int i = 0; i < count-2; i++)
    {
        V2F_C4B_T2F_Triangle tmp = {
            {verts[0], Color4B(fillColor), __t(v2fzero)},
            {verts[i+1], Color4B(fillColor), __t(v2fzero)},
            {verts[i+2], Color4B(fillColor), __t(v2fzero)},
        };
        
        *cursor++ = tmp;
    }
    
    if(outline)
    {
        struct ExtrudeVerts {Vec2 offset, n;};
        struct ExtrudeVerts* extrude = (struct ExtrudeVerts*)malloc(sizeof(struct ExtrudeVerts)*count);
        memset(extrude, 0, sizeof(struct ExtrudeVerts)*count);
        
        for (int i = 0; i < count; i++)
        {
            Vec2 v0 = __v2f(verts[(i-1+count)%count]);
            Vec2 v1 = __v2f(verts[i]);
            Vec2 v2 = __v2f(verts[(i+1)%count]);
            
            Vec2 n1 = v2fnormalize(v2fperp(v2fsub(v1, v0)));
            Vec2 n2 = v2fnormalize(v2fperp(v2fsub(v2, v1)));
            
            Vec2 offset = v2fmult(v2fadd(n1, n2), 1.0f / (v2fdot(n1, n2) + 1.0f));
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
            
            V2F_C4B_T2F_Triangle tmp1 = {
                {inner0, Color4B(borderColor), __t(v2fneg(n0))},
                {inner1, Color4B(borderColor), __t(v2fneg(n0))},
                {outer1, Color4B(borderColor), __t(n0)}
            };
            *cursor++ = tmp1;
            
            V2F_C4B_T2F_Triangle tmp2 = {
                {inner0, Color4B(borderColor), __t(v2fneg(n0))},
                {outer0, Color4B(borderColor), __t(n0)},
                {outer1, Color4B(borderColor), __t(n0)}
            };
            *cursor++ = tmp2;
        }
        
        free(extrude);
    }
    
    _customCommand.updateVertexBuffer(triangles, _bufferCount*sizeof(V2F_C4B_T2F), vertex_count*sizeof(V2F_C4B_T2F));
    _bufferCount += vertex_count;
    _customCommand.setVertexDrawInfo(0, _bufferCount);
    _dirty = true;
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
        float j = radius * cosf(rads + angle) * scaleX + center.x;
        float k = radius * sinf(rads + angle) * scaleY + center.y;
        
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

void DrawNode::drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color)
{
    unsigned int vertex_count = 3;
    ensureCapacity(vertex_count);

    Color4B col = Color4B(color);
    V2F_C4B_T2F a = {Vec2(p1.x, p1.y), col, Tex2F(0.0, 0.0) };
    V2F_C4B_T2F b = {Vec2(p2.x, p2.y), col, Tex2F(0.0,  0.0) };
    V2F_C4B_T2F c = {Vec2(p3.x, p3.y), col, Tex2F(0.0,  0.0) };

    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle = {a, b, c};
    triangles[0] = triangle;

    _customCommand.updateVertexBuffer(triangles, _bufferCount*sizeof(V2F_C4B_T2F), vertex_count*sizeof(V2F_C4B_T2F));
    _bufferCount += vertex_count;
    _dirty = true;
    _customCommand.setVertexDrawInfo(0, _bufferCount);
}

void DrawNode::clear()
{
    _bufferCount = 0;
    _dirty = true;
    _bufferCountGLLine = 0;
    _dirtyGLLine = true;
    _bufferCountGLPoint = 0;
    _dirtyGLPoint = true;
    _lineWidth = 0;
}

const BlendFunc& DrawNode::getBlendFunc() const
{
    return _blendFunc;
}

void DrawNode::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

void DrawNode::setLineWidth(float lineWidth)
{
    _lineWidth = lineWidth;
}

float DrawNode::getLineWidth()
{
    return this->_lineWidth;
}

void DrawNode::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (_isolated)
    {
        //ignore `parentTransform` from parent
        Node::visit(renderer, Mat4::IDENTITY, parentFlags);
    }
    else
    {
        Node::visit(renderer, parentTransform, parentFlags);
    }
}

NS_CC_END
