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

#include "2d/CCDrawNode.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "2d/CCActionCatmullRom.h"
#include "platform/CCGL.h"

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
// 	return * ((Vec2*) &v);
// #endif
}

static inline Tex2F __t(const Vec2 &v)
{
	return *(Tex2F*)&v;
}

// implementation of DrawNode

DrawNode::DrawNode()
: _vao(0)
, _vbo(0)
, _bufferCapacity(0)
, _bufferCount(0)
, _buffer(nullptr)
, _dirty(false)
, _vaoGLPoint(0)
, _vboGLPoint(0)
, _bufferCapacityGLPoint(0)
, _bufferCountGLPoint(0)
, _bufferGLPoint(nullptr)
, _pointColor(1,1,1,1)
, _pointSize(1)
, _dirtyGLPoint(false)
, _vaoGLLine(0)
, _vboGLLine(0)
, _bufferCapacityGLLine(0)
, _bufferCountGLLine(0)
, _bufferGLLine(nullptr)
, _dirtyGLLine(false)
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

DrawNode::~DrawNode()
{
    free(_buffer);
    _buffer = nullptr;
    free(_bufferGLPoint);
    _bufferGLPoint = nullptr;
    free(_bufferGLLine);
    _bufferGLLine = nullptr;
    
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_vboGLLine);
    glDeleteBuffers(1, &_vboGLPoint);
    _vbo = 0;
    _vboGLPoint = 0;
    _vboGLLine = 0;
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_vao);
        glDeleteVertexArrays(1, &_vaoGLLine);
        glDeleteVertexArrays(1, &_vaoGLPoint);
        GL::bindVAO(0);
        _vao = 0;
    }
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

void DrawNode::ensureCapacity(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCount + count > _bufferCapacity)
    {
		_bufferCapacity += MAX(_bufferCapacity, count);
		_buffer = (V2F_C4B_T2F*)realloc(_buffer, _bufferCapacity*sizeof(V2F_C4B_T2F));
	}
}

void DrawNode::ensureCapacityGLPoint(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCountGLPoint + count > _bufferCapacityGLPoint)
    {
        _bufferCapacityGLPoint += MAX(_bufferCapacityGLPoint, count);
        _bufferGLPoint = (V2F_C4B_T2F*)realloc(_bufferGLPoint, _bufferCapacityGLPoint*sizeof(V2F_C4B_T2F));
    }
}

void DrawNode::ensureCapacityGLLine(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCountGLLine + count > _bufferCapacityGLLine)
    {
        _bufferCapacityGLLine += MAX(_bufferCapacityGLLine, count);
        _bufferGLLine = (V2F_C4B_T2F*)realloc(_bufferGLLine, _bufferCapacityGLLine*sizeof(V2F_C4B_T2F));
    }
}

bool DrawNode::init()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR));
    
    ensureCapacity(512);
    ensureCapacityGLPoint(64);
    ensureCapacityGLLine(256);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    // vertex
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    // color
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    // texcood
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vaoGLLine);
        GL::bindVAO(_vaoGLLine);
    }
    glGenBuffers(1, &_vboGLLine);
    glBindBuffer(GL_ARRAY_BUFFER, _vboGLLine);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacityGLLine, _bufferGLLine, GL_STREAM_DRAW);
    // vertex
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    // color
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    // texcood
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vaoGLPoint);
        GL::bindVAO(_vaoGLPoint);
    }
    glGenBuffers(1, &_vboGLPoint);
    glBindBuffer(GL_ARRAY_BUFFER, _vboGLPoint);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacityGLPoint, _bufferGLPoint, GL_STREAM_DRAW);
    // vertex
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    // color
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    // texcood
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    _dirty = true;
    _dirtyGLLine = true;
    _dirtyGLPoint = true;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
   /** listen the event that renderer was recreated on Android/WP8 */
        this->init();
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
    
    return true;
}

void DrawNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if(_bufferCount)
    {
        _customCommand.init(_globalZOrder);
        _customCommand.func = CC_CALLBACK_0(DrawNode::onDraw, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }
    
    if(_bufferCountGLPoint)
    {
        _customCommandGLPoint.init(_globalZOrder);
        _customCommandGLPoint.func = CC_CALLBACK_0(DrawNode::onDrawGLPoint, this, transform, flags);
        renderer->addCommand(&_customCommandGLPoint);
    }
    
    if(_bufferCountGLLine)
    {
        _customCommandGLLine.init(_globalZOrder);
        _customCommandGLLine.func = CC_CALLBACK_0(DrawNode::onDrawGLLine, this, transform, flags);
        renderer->addCommand(&_customCommandGLLine);
    }
}

void DrawNode::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    if (_dirty)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacity, _buffer, GL_STREAM_DRAW);
        
        _dirty = false;
    }
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vao);
    }
    else
    {
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // vertex
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
        // color
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
        // texcood
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
    }

    glDrawArrays(GL_TRIANGLES, 0, _bufferCount);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _bufferCount);
    CHECK_GL_ERROR_DEBUG();
}

void DrawNode::onDrawGLLine(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR);
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    if (_dirtyGLLine)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vboGLLine);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacityGLLine, _bufferGLLine, GL_STREAM_DRAW);
        _dirtyGLLine = false;
    }
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vaoGLLine);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vboGLLine);
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
        // vertex
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
        // color
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
        // texcood
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
    }
    glLineWidth(2);
    glDrawArrays(GL_LINES, 0, _bufferCountGLLine);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCountGLLine);
    CHECK_GL_ERROR_DEBUG();
}

void DrawNode::onDrawGLPoint(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    glProgram->setUniformLocationWith4fv(glProgram->getUniformLocation("u_color"), (GLfloat*) &_pointColor.r, 1);
    glProgram->setUniformLocationWith1f(glProgram->getUniformLocation("u_pointSize"), _pointSize);
    
    if (_dirtyGLPoint)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vboGLPoint);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacityGLPoint, _bufferGLPoint, GL_STREAM_DRAW);
        
        _dirtyGLPoint = false;
    }
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vaoGLPoint);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vboGLPoint);
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
        glBindBuffer(GL_ARRAY_BUFFER, _vboGLPoint);
    }
    
    glDrawArrays(GL_POINTS, 0, _bufferCountGLPoint);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCountGLPoint);
    CHECK_GL_ERROR_DEBUG();
}

void DrawNode::drawPoint(const Vec2& position, const float pointSize, const Color4F &color)
{
    ensureCapacityGLPoint(1);
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLPoint + _bufferCountGLPoint);
    V2F_C4B_T2F a = {position, Color4B(color), Tex2F(0.0, 0.0) };
    *point = a;
    
    _pointSize = pointSize;
    _pointColor = color;
    
    _bufferCountGLPoint += 1;
    _dirtyGLPoint = true;
}

void DrawNode::drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color)
{
    ensureCapacityGLPoint(numberOfPoints);
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLPoint + _bufferCountGLPoint);
    
    for(unsigned int i=0; i < numberOfPoints; i++,point++)
    {
        V2F_C4B_T2F a = {position[i], Color4B(color), Tex2F(0.0, 0.0) };
        *point = a;
    }
    
    _pointColor = color;
    
    _bufferCountGLPoint += numberOfPoints;
    _dirtyGLPoint = true;
}

void DrawNode::drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color)
{
    ensureCapacityGLLine(2);
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLLine + _bufferCountGLLine);
    
    V2F_C4B_T2F a = {origin, Color4B(color), Tex2F(0.0, 0.0)};
    V2F_C4B_T2F b = {destination, Color4B(color), Tex2F(0.0, 0.0)};
    
    *point = a;
    *(point+1) = b;
    
    _bufferCountGLLine += 2;
    _dirtyGLLine = true;
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
    unsigned int vertext_count;
    if(closePolygon)
    {
        vertext_count = 2 * numberOfPoints;
        ensureCapacityGLLine(vertext_count);
    }
    else
    {
        vertext_count = 2 * (numberOfPoints - 1);
        ensureCapacityGLLine(vertext_count);
    }
    
    V2F_C4B_T2F *point = (V2F_C4B_T2F*)(_bufferGLLine + _bufferCountGLLine);
 
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
    
    _bufferCountGLLine += vertext_count;
}

void DrawNode::drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color)
{
    const float coef = 2.0f * (float)M_PI/segments;
    
    Vec2 *vertices = new (std::nothrow) Vec2[segments+2];
    if( ! vertices )
        return;
    
    for(unsigned int i = 0;i <= segments; i++) {
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
	
	_bufferCount += vertex_count;
	
	_dirty = true;
}

void DrawNode::drawRect(const Vec2 &lb, const Vec2 &lt, const Vec2 &rt, const Vec2& rb, const Color4F &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);
	
    V2F_C4B_T2F a = {lb, Color4B(color), Tex2F(-1.0, -1.0) };
    V2F_C4B_T2F b = {lt, Color4B(color), Tex2F(-1.0,  1.0) };
    V2F_C4B_T2F c = {rt, Color4B(color), Tex2F( 1.0,  1.0) };
    V2F_C4B_T2F d = {rb, Color4B(color), Tex2F( 1.0, -1.0) };

    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle0 = {a, b, c};
    V2F_C4B_T2F_Triangle triangle1 = {a, c, d};
    triangles[0] = triangle0;
    triangles[1] = triangle1;
	
    _bufferCount += vertex_count;

    _dirty = true;
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
	
	_bufferCount += vertex_count;
	
	_dirty = true;
}

void DrawNode::drawPolygon(const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor)
{
    CCASSERT(count >= 0, "invalid count value");

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
		
		Vec2 offset = v2fmult(v2fadd(n1, n2), 1.0/(v2fdot(n1, n2) + 1.0));
        struct ExtrudeVerts tmp = {offset, n2};
		extrude[i] = tmp;
	}
	
	bool outline = (borderColor.a > 0.0 && borderWidth > 0.0);
	
	auto triangle_count = 3*count - 2;
	auto vertex_count = 3*triangle_count;
    ensureCapacity(vertex_count);
	
	V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
	V2F_C4B_T2F_Triangle *cursor = triangles;
	
	float inset = (outline == false ? 0.5 : 0.0);
	for (int i = 0; i < count-2; i++)
    {
		Vec2 v0 = v2fsub(__v2f(verts[0  ]), v2fmult(extrude[0  ].offset, inset));
		Vec2 v1 = v2fsub(__v2f(verts[i+1]), v2fmult(extrude[i+1].offset, inset));
		Vec2 v2 = v2fsub(__v2f(verts[i+2]), v2fmult(extrude[i+2].offset, inset));
		
        V2F_C4B_T2F_Triangle tmp = {
            {v0, Color4B(fillColor), __t(v2fzero)},
            {v1, Color4B(fillColor), __t(v2fzero)},
            {v2, Color4B(fillColor), __t(v2fzero)},
        };

		*cursor++ = tmp;
	}
	
	for(int i = 0; i < count; i++)
    {
		int j = (i+1)%count;
		Vec2 v0 = __v2f(verts[i]);
		Vec2 v1 = __v2f(verts[j]);
		
		Vec2 n0 = extrude[i].n;
		
		Vec2 offset0 = extrude[i].offset;
		Vec2 offset1 = extrude[j].offset;
		
		if(outline)
        {
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
        else {
			Vec2 inner0 = v2fsub(v0, v2fmult(offset0, 0.5));
			Vec2 inner1 = v2fsub(v1, v2fmult(offset1, 0.5));
			Vec2 outer0 = v2fadd(v0, v2fmult(offset0, 0.5));
			Vec2 outer1 = v2fadd(v1, v2fmult(offset1, 0.5));
			
            V2F_C4B_T2F_Triangle tmp1 = {
                {inner0, Color4B(fillColor), __t(v2fzero)},
                {inner1, Color4B(fillColor), __t(v2fzero)},
                {outer1, Color4B(fillColor), __t(n0)}
            };
			*cursor++ = tmp1;

            V2F_C4B_T2F_Triangle tmp2 = {
                {inner0, Color4B(fillColor), __t(v2fzero)},
                {outer0, Color4B(fillColor), __t(n0)},
                {outer1, Color4B(fillColor), __t(n0)}
            };
			*cursor++ = tmp2;
		}
	}
	
	_bufferCount += vertex_count;
	
	_dirty = true;

    free(extrude);
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

    _bufferCount += vertex_count;
    _dirty = true;
}

void DrawNode::drawQuadraticBezier(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments, const Color4F &color)
{
    drawQuadBezier(from, control, to, segments, color);
}

void DrawNode::clear()
{
    _bufferCount = 0;
    _dirty = true;
    _bufferCountGLLine = 0;
    _dirtyGLLine = true;
    _bufferCountGLPoint = 0;
    _dirtyGLPoint = true;
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
