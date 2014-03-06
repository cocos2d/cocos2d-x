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

#include "CCDrawNode.h"
#include "CCShaderCache.h"
#include "CCGL.h"
#include "CCEventType.h"
#include "CCConfiguration.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderer.h"
#include "CCDirector.h"
#include "CCEventListenerCustom.h"
#include "CCEventDispatcher.h"

NS_CC_BEGIN

// Vertex2F == CGPoint in 32-bits, but not in 64-bits (OS X)
// that's why the "v2f" functions are needed
static Vertex2F v2fzero(0.0f,0.0f);

static inline Vertex2F v2f(float x, float y)
{
    Vertex2F ret(x, y);
	return ret;
}

static inline Vertex2F v2fadd(const Vertex2F &v0, const Vertex2F &v1)
{
	return v2f(v0.x+v1.x, v0.y+v1.y);
}

static inline Vertex2F v2fsub(const Vertex2F &v0, const Vertex2F &v1)
{
	return v2f(v0.x-v1.x, v0.y-v1.y);
}

static inline Vertex2F v2fmult(const Vertex2F &v, float s)
{
	return v2f(v.x * s, v.y * s);
}

static inline Vertex2F v2fperp(const Vertex2F &p0)
{
	return v2f(-p0.y, p0.x);
}

static inline Vertex2F v2fneg(const Vertex2F &p0)
{
	return v2f(-p0.x, - p0.y);
}

static inline float v2fdot(const Vertex2F &p0, const Vertex2F &p1)
{
	return  p0.x * p1.x + p0.y * p1.y;
}

static inline Vertex2F v2fforangle(float _a_)
{
	return v2f(cosf(_a_), sinf(_a_));
}

static inline Vertex2F v2fnormalize(const Vertex2F &p)
{
	Point r = Point(p.x, p.y).normalize();
	return v2f(r.x, r.y);
}

static inline Vertex2F __v2f(const Point &v)
{
//#ifdef __LP64__
	return v2f(v.x, v.y);
// #else
// 	return * ((Vertex2F*) &v);
// #endif
}

static inline Tex2F __t(const Vertex2F &v)
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

void DrawNode::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawNode::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void DrawNode::onDraw(const kmMat4 &transform, bool transformUpdated)
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

void DrawNode::drawDot(const Point &pos, float radius, const Color4F &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);
	
	V2F_C4B_T2F a = {Vertex2F(pos.x - radius, pos.y - radius), Color4B(color), Tex2F(-1.0, -1.0) };
	V2F_C4B_T2F b = {Vertex2F(pos.x - radius, pos.y + radius), Color4B(color), Tex2F(-1.0,  1.0) };
	V2F_C4B_T2F c = {Vertex2F(pos.x + radius, pos.y + radius), Color4B(color), Tex2F( 1.0,  1.0) };
	V2F_C4B_T2F d = {Vertex2F(pos.x + radius, pos.y - radius), Color4B(color), Tex2F( 1.0, -1.0) };
	
	V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle0 = {a, b, c};
    V2F_C4B_T2F_Triangle triangle1 = {a, c, d};
	triangles[0] = triangle0;
	triangles[1] = triangle1;
	
	_bufferCount += vertex_count;
	
	_dirty = true;
}

void DrawNode::drawSegment(const Point &from, const Point &to, float radius, const Color4F &color)
{
    unsigned int vertex_count = 6*3;
    ensureCapacity(vertex_count);
	
	Vertex2F a = __v2f(from);
	Vertex2F b = __v2f(to);
	
	
	Vertex2F n = v2fnormalize(v2fperp(v2fsub(b, a)));
	Vertex2F t = v2fperp(n);
	
	Vertex2F nw = v2fmult(n, radius);
	Vertex2F tw = v2fmult(t, radius);
	Vertex2F v0 = v2fsub(b, v2fadd(nw, tw));
	Vertex2F v1 = v2fadd(b, v2fsub(nw, tw));
	Vertex2F v2 = v2fsub(b, nw);
	Vertex2F v3 = v2fadd(b, nw);
	Vertex2F v4 = v2fsub(a, nw);
	Vertex2F v5 = v2fadd(a, nw);
	Vertex2F v6 = v2fsub(a, v2fsub(nw, tw));
	Vertex2F v7 = v2fadd(a, v2fadd(nw, tw));
	
	
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

void DrawNode::drawPolygon(Point *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor)
{
    CCASSERT(count >= 0, "invalid count value");

    struct ExtrudeVerts {Vertex2F offset, n;};
	struct ExtrudeVerts* extrude = (struct ExtrudeVerts*)malloc(sizeof(struct ExtrudeVerts)*count);
	memset(extrude, 0, sizeof(struct ExtrudeVerts)*count);
	
	for (int i = 0; i < count; i++)
    {
		Vertex2F v0 = __v2f(verts[(i-1+count)%count]);
		Vertex2F v1 = __v2f(verts[i]);
		Vertex2F v2 = __v2f(verts[(i+1)%count]);
        
		Vertex2F n1 = v2fnormalize(v2fperp(v2fsub(v1, v0)));
		Vertex2F n2 = v2fnormalize(v2fperp(v2fsub(v2, v1)));
		
		Vertex2F offset = v2fmult(v2fadd(n1, n2), 1.0/(v2fdot(n1, n2) + 1.0));
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
		Vertex2F v0 = v2fsub(__v2f(verts[0  ]), v2fmult(extrude[0  ].offset, inset));
		Vertex2F v1 = v2fsub(__v2f(verts[i+1]), v2fmult(extrude[i+1].offset, inset));
		Vertex2F v2 = v2fsub(__v2f(verts[i+2]), v2fmult(extrude[i+2].offset, inset));
		
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
		Vertex2F v0 = __v2f(verts[i]);
		Vertex2F v1 = __v2f(verts[j]);
		
		Vertex2F n0 = extrude[i].n;
		
		Vertex2F offset0 = extrude[i].offset;
		Vertex2F offset1 = extrude[j].offset;
		
		if(outline)
        {
			Vertex2F inner0 = v2fsub(v0, v2fmult(offset0, borderWidth));
			Vertex2F inner1 = v2fsub(v1, v2fmult(offset1, borderWidth));
			Vertex2F outer0 = v2fadd(v0, v2fmult(offset0, borderWidth));
			Vertex2F outer1 = v2fadd(v1, v2fmult(offset1, borderWidth));
			
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
			Vertex2F inner0 = v2fsub(v0, v2fmult(offset0, 0.5));
			Vertex2F inner1 = v2fsub(v1, v2fmult(offset1, 0.5));
			Vertex2F outer0 = v2fadd(v0, v2fmult(offset0, 0.5));
			Vertex2F outer1 = v2fadd(v1, v2fmult(offset1, 0.5));
			
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

void DrawNode::drawTriangle(const Point &p1, const Point &p2, const Point &p3, const Color4F &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);

    Color4B col = Color4B(color);
    V2F_C4B_T2F a = {Vertex2F(p1.x, p1.y), col, Tex2F(0.0, 0.0) };
    V2F_C4B_T2F b = {Vertex2F(p2.x, p2.y), col, Tex2F(0.0,  0.0) };
    V2F_C4B_T2F c = {Vertex2F(p3.x, p3.y), col, Tex2F(0.0,  0.0) };

    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle = {a, b, c};
    triangles[0] = triangle;

    _bufferCount += vertex_count;
    _dirty = true;
}

void DrawNode::drawCubicBezier(const Point& from, const Point& control1, const Point& control2, const Point& to, unsigned int segments, const Color4F &color)
{
    unsigned int vertex_count = (segments + 1) * 3;
    ensureCapacity(vertex_count);

    Tex2F texCoord = Tex2F(0.0, 0.0);
    Color4B col = Color4B(color);
    Vertex2F vertex;
    Vertex2F firstVertex = Vertex2F(from.x, from.y);
    Vertex2F lastVertex = Vertex2F(to.x, to.y);

    float t = 0;
    for(unsigned int i = segments + 1; i > 0; i--)
    {
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;
        vertex = Vertex2F(x, y);

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

void DrawNode::drawQuadraticBezier(const Point& from, const Point& control, const Point& to, unsigned int segments, const Color4F &color)
{
    unsigned int vertex_count = (segments + 1) * 3;
    ensureCapacity(vertex_count);

    Tex2F texCoord = Tex2F(0.0, 0.0);
    Color4B col = Color4B(color);
    Vertex2F vertex;
    Vertex2F firstVertex = Vertex2F(from.x, from.y);
    Vertex2F lastVertex = Vertex2F(to.x, to.y);

    float t = 0;
    for(unsigned int i = segments + 1; i > 0; i--)
    {
        float x = powf(1 - t, 2) * from.x + 2.0f * (1 - t) * t * control.x + t * t * to.x;
        float y = powf(1 - t, 2) * from.y + 2.0f * (1 - t) * t * control.y + t * t * to.y;
        vertex = Vertex2F(x, y);

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
