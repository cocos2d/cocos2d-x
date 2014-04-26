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
#include "CCShaderCache.h"
#include "CCGL.h"
#include "2d/CCEventType.h"
#include "CCConfiguration.h"
#include "2d/renderer/CCCustomCommand.h"
#include "2d/renderer/CCRenderer.h"
#include "2d/CCDirector.h"
#include "2d/CCEventListenerCustom.h"
#include "2d/CCEventDispatcher.h"

NS_CC_BEGIN

// Vector2 == CGPoint in 32-bits, but not in 64-bits (OS X)
// that's why the "v2f" functions are needed
static Vector2 v2fzero(0.0f,0.0f);

static inline Vector2 v2f(float x, float y)
{
    Vector2 ret(x, y);
	return ret;
}

static inline Vector2 v2fadd(const Vector2 &v0, const Vector2 &v1)
{
	return v2f(v0.x+v1.x, v0.y+v1.y);
}

static inline Vector2 v2fsub(const Vector2 &v0, const Vector2 &v1)
{
	return v2f(v0.x-v1.x, v0.y-v1.y);
}

static inline Vector2 v2fmult(const Vector2 &v, float s)
{
	return v2f(v.x * s, v.y * s);
}

static inline Vector2 v2fperp(const Vector2 &p0)
{
	return v2f(-p0.y, p0.x);
}

static inline Vector2 v2fneg(const Vector2 &p0)
{
	return v2f(-p0.x, - p0.y);
}

static inline float v2fdot(const Vector2 &p0, const Vector2 &p1)
{
	return  p0.x * p1.x + p0.y * p1.y;
}

static inline Vector2 v2fforangle(float _a_)
{
	return v2f(cosf(_a_), sinf(_a_));
}

static inline Vector2 v2fnormalize(const Vector2 &p)
{
	Vector2 r = Vector2(p.x, p.y).normalize();
	return v2f(r.x, r.y);
}

static inline Vector2 __v2f(const Vector2 &v)
{
//#ifdef __LP64__
	return v2f(v.x, v.y);
// #else
// 	return * ((Vector2*) &v);
// #endif
}

static inline Tex2F __t(const Vector2 &v)
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
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

DrawNode::~DrawNode()
{
    free(_buffer);
    _buffer = nullptr;
    
    glDeleteBuffers(1, &_vbo);
    _vbo = 0;
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_vao);
        GL::bindVAO(0);
        _vao = 0;
    }
}

DrawNode* DrawNode::create()
{
    DrawNode* ret = new DrawNode();
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

bool DrawNode::init()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR));
    
    ensureCapacity(512);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    _dirty = true;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
    /** listen the event that coming to foreground on Android */
        this->init();
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
    
    return true;
}

void DrawNode::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawNode::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void DrawNode::onDraw(const Matrix &transform, bool transformUpdated)
{
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins(transform);

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
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
    }

    glDrawArrays(GL_TRIANGLES, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
    CHECK_GL_ERROR_DEBUG();
}

void DrawNode::drawDot(const Vector2 &pos, float radius, const Color4F &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);
	
	V2F_C4B_T2F a = {Vector2(pos.x - radius, pos.y - radius), Color4B(color), Tex2F(-1.0, -1.0) };
	V2F_C4B_T2F b = {Vector2(pos.x - radius, pos.y + radius), Color4B(color), Tex2F(-1.0,  1.0) };
	V2F_C4B_T2F c = {Vector2(pos.x + radius, pos.y + radius), Color4B(color), Tex2F( 1.0,  1.0) };
	V2F_C4B_T2F d = {Vector2(pos.x + radius, pos.y - radius), Color4B(color), Tex2F( 1.0, -1.0) };
	
	V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle0 = {a, b, c};
    V2F_C4B_T2F_Triangle triangle1 = {a, c, d};
	triangles[0] = triangle0;
	triangles[1] = triangle1;
	
	_bufferCount += vertex_count;
	
	_dirty = true;
}

void DrawNode::drawSegment(const Vector2 &from, const Vector2 &to, float radius, const Color4F &color)
{
    unsigned int vertex_count = 6*3;
    ensureCapacity(vertex_count);
	
	Vector2 a = __v2f(from);
	Vector2 b = __v2f(to);
	
	
	Vector2 n = v2fnormalize(v2fperp(v2fsub(b, a)));
	Vector2 t = v2fperp(n);
	
	Vector2 nw = v2fmult(n, radius);
	Vector2 tw = v2fmult(t, radius);
	Vector2 v0 = v2fsub(b, v2fadd(nw, tw));
	Vector2 v1 = v2fadd(b, v2fsub(nw, tw));
	Vector2 v2 = v2fsub(b, nw);
	Vector2 v3 = v2fadd(b, nw);
	Vector2 v4 = v2fsub(a, nw);
	Vector2 v5 = v2fadd(a, nw);
	Vector2 v6 = v2fsub(a, v2fsub(nw, tw));
	Vector2 v7 = v2fadd(a, v2fadd(nw, tw));
	
	
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

void DrawNode::drawPolygon(Vector2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor)
{
    CCASSERT(count >= 0, "invalid count value");

    struct ExtrudeVerts {Vector2 offset, n;};
	struct ExtrudeVerts* extrude = (struct ExtrudeVerts*)malloc(sizeof(struct ExtrudeVerts)*count);
	memset(extrude, 0, sizeof(struct ExtrudeVerts)*count);
	
	for (int i = 0; i < count; i++)
    {
		Vector2 v0 = __v2f(verts[(i-1+count)%count]);
		Vector2 v1 = __v2f(verts[i]);
		Vector2 v2 = __v2f(verts[(i+1)%count]);
        
		Vector2 n1 = v2fnormalize(v2fperp(v2fsub(v1, v0)));
		Vector2 n2 = v2fnormalize(v2fperp(v2fsub(v2, v1)));
		
		Vector2 offset = v2fmult(v2fadd(n1, n2), 1.0/(v2fdot(n1, n2) + 1.0));
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
		Vector2 v0 = v2fsub(__v2f(verts[0  ]), v2fmult(extrude[0  ].offset, inset));
		Vector2 v1 = v2fsub(__v2f(verts[i+1]), v2fmult(extrude[i+1].offset, inset));
		Vector2 v2 = v2fsub(__v2f(verts[i+2]), v2fmult(extrude[i+2].offset, inset));
		
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
		Vector2 v0 = __v2f(verts[i]);
		Vector2 v1 = __v2f(verts[j]);
		
		Vector2 n0 = extrude[i].n;
		
		Vector2 offset0 = extrude[i].offset;
		Vector2 offset1 = extrude[j].offset;
		
		if(outline)
        {
			Vector2 inner0 = v2fsub(v0, v2fmult(offset0, borderWidth));
			Vector2 inner1 = v2fsub(v1, v2fmult(offset1, borderWidth));
			Vector2 outer0 = v2fadd(v0, v2fmult(offset0, borderWidth));
			Vector2 outer1 = v2fadd(v1, v2fmult(offset1, borderWidth));
			
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
			Vector2 inner0 = v2fsub(v0, v2fmult(offset0, 0.5));
			Vector2 inner1 = v2fsub(v1, v2fmult(offset1, 0.5));
			Vector2 outer0 = v2fadd(v0, v2fmult(offset0, 0.5));
			Vector2 outer1 = v2fadd(v1, v2fmult(offset1, 0.5));
			
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

void DrawNode::drawTriangle(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Color4F &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);

    Color4B col = Color4B(color);
    V2F_C4B_T2F a = {Vector2(p1.x, p1.y), col, Tex2F(0.0, 0.0) };
    V2F_C4B_T2F b = {Vector2(p2.x, p2.y), col, Tex2F(0.0,  0.0) };
    V2F_C4B_T2F c = {Vector2(p3.x, p3.y), col, Tex2F(0.0,  0.0) };

    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle = {a, b, c};
    triangles[0] = triangle;

    _bufferCount += vertex_count;
    _dirty = true;
}

void DrawNode::drawCubicBezier(const Vector2& from, const Vector2& control1, const Vector2& control2, const Vector2& to, unsigned int segments, const Color4F &color)
{
    unsigned int vertex_count = (segments + 1) * 3;
    ensureCapacity(vertex_count);

    Tex2F texCoord = Tex2F(0.0, 0.0);
    Color4B col = Color4B(color);
    Vector2 vertex;
    Vector2 firstVertex = Vector2(from.x, from.y);
    Vector2 lastVertex = Vector2(to.x, to.y);

    float t = 0;
    for(unsigned int i = segments + 1; i > 0; i--)
    {
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;
        vertex = Vector2(x, y);

        V2F_C4B_T2F a = {firstVertex, col, texCoord };
        V2F_C4B_T2F b = {lastVertex, col, texCoord };
        V2F_C4B_T2F c = {vertex, col, texCoord };
        V2F_C4B_T2F_Triangle triangle = {a, b, c};
        ((V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount))[0] = triangle;

        lastVertex = vertex;
        t += 1.0f / segments;
        _bufferCount += 3;
    }
    _dirty = true;
}

void DrawNode::drawQuadraticBezier(const Vector2& from, const Vector2& control, const Vector2& to, unsigned int segments, const Color4F &color)
{
    unsigned int vertex_count = (segments + 1) * 3;
    ensureCapacity(vertex_count);

    Tex2F texCoord = Tex2F(0.0, 0.0);
    Color4B col = Color4B(color);
    Vector2 vertex;
    Vector2 firstVertex = Vector2(from.x, from.y);
    Vector2 lastVertex = Vector2(to.x, to.y);

    float t = 0;
    for(unsigned int i = segments + 1; i > 0; i--)
    {
        float x = powf(1 - t, 2) * from.x + 2.0f * (1 - t) * t * control.x + t * t * to.x;
        float y = powf(1 - t, 2) * from.y + 2.0f * (1 - t) * t * control.y + t * t * to.y;
        vertex = Vector2(x, y);

        V2F_C4B_T2F a = {firstVertex, col, texCoord };
        V2F_C4B_T2F b = {lastVertex, col, texCoord };
        V2F_C4B_T2F c = {vertex, col, texCoord };
        V2F_C4B_T2F_Triangle triangle = {a, b, c};
        ((V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount))[0] = triangle;

        lastVertex = vertex;
        t += 1.0f / segments;
        _bufferCount += 3;
    }
    _dirty = true;
}

void DrawNode::clear()
{
    _bufferCount = 0;
    _dirty = true;
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
