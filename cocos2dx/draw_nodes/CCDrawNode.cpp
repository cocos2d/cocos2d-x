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

#include "CCDrawNode.h"
#include "support/CCPointExtension.h"
#include "shaders/CCShaderCache.h"

NS_CC_BEGIN

// ccVertex2F == CGPoint in 32-bits, but not in 64-bits (OS X)
// that's why the "v2f" functions are needed
static ccVertex2F v2fzero = (ccVertex2F){0,0};

static inline ccVertex2F v2f(float x, float y)
{
	return (ccVertex2F){x,y};
}

static inline ccVertex2F v2fadd(const ccVertex2F &v0, const ccVertex2F &v1)
{
	return v2f(v0.x+v1.x, v0.y+v1.y);
}

static inline ccVertex2F v2fsub(const ccVertex2F &v0, const ccVertex2F &v1)
{
	return v2f(v0.x-v1.x, v0.y-v1.y);
}

static inline ccVertex2F v2fmult(const ccVertex2F &v, float s)
{
	return v2f(v.x * s, v.y * s);
}

static inline ccVertex2F v2fperp(const ccVertex2F &p0)
{
	return v2f(-p0.y, p0.x);
}

static inline ccVertex2F v2fneg(const ccVertex2F &p0)
{
	return v2f(-p0.x, - p0.y);
}

static inline float v2fdot(const ccVertex2F &p0, const ccVertex2F &p1)
{
	return  p0.x * p1.x + p0.y * p1.y;
}

static inline ccVertex2F v2fforangle(float _a_)
{
	return v2f(cosf(_a_), sinf(_a_));
}

static inline ccVertex2F v2fnormalize(const ccVertex2F &p)
{
	CCPoint r = ccpNormalize(ccp(p.x, p.y));
	return v2f(r.x, r.y);
}

static inline ccVertex2F __v2f(const CCPoint &v)
{
#ifdef __LP64__
	return v2f(v.x, v.y);
#else
	return * ((ccVertex2F*) &v);
#endif
}

static inline ccTex2F __t(const ccVertex2F &v)
{
	return *(ccTex2F*)&v;
}

// implementation of CCDrawNode

CCDrawNode::CCDrawNode()
: m_uVao(0)
, m_uVbo(0)
, m_uBufferCapacity(0)
, m_nBufferCount(0)
, m_pBuffer(NULL)
, m_sBlendFunc((ccBlendFunc){CC_BLEND_SRC, CC_BLEND_DST})
, m_bDirty(false)
{}

CCDrawNode::~CCDrawNode()
{
    free(m_pBuffer);
    m_pBuffer = NULL;
    
    glDeleteBuffers(1, &m_uVbo);
    m_uVbo = 0;
    
    glDeleteVertexArrays(1, &m_uVao);
    m_uVao = 0;
}

CCDrawNode* CCDrawNode::create()
{
    CCDrawNode* pRet = new CCDrawNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

void CCDrawNode::ensureCapacity(unsigned int count)
{
    if(m_nBufferCount + count > m_uBufferCapacity)
    {
		m_uBufferCapacity += MAX(m_uBufferCapacity, count);
		m_pBuffer = (ccV2F_C4B_T2F*)realloc(m_pBuffer, m_uBufferCapacity*sizeof(ccV2F_C4B_T2F));
	}
}

bool CCDrawNode::init()
{
    m_sBlendFunc = (ccBlendFunc){CC_BLEND_SRC, CC_BLEND_DST};
    
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionLengthTexureColor));
    
    ensureCapacity(512);
    
    glGenVertexArrays(1, &m_uVao);
    ccGLBindVAO(m_uVao);
    
    glGenBuffers(1, &m_uVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_uVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ccV2F_C4B_T2F)* m_uBufferCapacity, m_pBuffer, GL_STREAM_DRAW);
    
    glEnableVertexAttribArray(kCCVertexAttrib_Position);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(ccV2F_C4B_T2F), (GLvoid *)offsetof(ccV2F_C4B_T2F, vertices));
    
    glEnableVertexAttribArray(kCCVertexAttrib_Color);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ccV2F_C4B_T2F), (GLvoid *)offsetof(ccV2F_C4B_T2F, colors));
    
    glEnableVertexAttribArray(kCCVertexAttrib_TexCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(ccV2F_C4B_T2F), (GLvoid *)offsetof(ccV2F_C4B_T2F, texCoords));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    ccGLBindVAO(0);
    
    CHECK_GL_ERROR_DEBUG();
    
    m_bDirty = true;
    
    return true;
}

void CCDrawNode::render()
{
    if (m_bDirty)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_uVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ccV2F_C4B_T2F)*m_uBufferCapacity, m_pBuffer, GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_bDirty = false;
    }
    
    ccGLBindVAO(m_uVao);
    glDrawArrays(GL_TRIANGLES, 0, m_nBufferCount);
    
    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();
}

void CCDrawNode::draw()
{
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    
    render();
}

void CCDrawNode::drawDot(const CCPoint &pos, float radius, const ccColor4F &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);
	
	ccV2F_C4B_T2F a = {{pos.x - radius, pos.y - radius}, ccc4BFromccc4F(color), {-1.0, -1.0} };
	ccV2F_C4B_T2F b = {{pos.x - radius, pos.y + radius}, ccc4BFromccc4F(color), {-1.0,  1.0} };
	ccV2F_C4B_T2F c = {{pos.x + radius, pos.y + radius}, ccc4BFromccc4F(color), { 1.0,  1.0} };
	ccV2F_C4B_T2F d = {{pos.x + radius, pos.y - radius}, ccc4BFromccc4F(color), { 1.0, -1.0} };
	
	ccV2F_C4B_T2F_Triangle *triangles = (ccV2F_C4B_T2F_Triangle *)(m_pBuffer + m_nBufferCount);
	triangles[0] = (ccV2F_C4B_T2F_Triangle){a, b, c};
	triangles[1] = (ccV2F_C4B_T2F_Triangle){a, c, d};
	
	m_nBufferCount += vertex_count;
	
	m_bDirty = true;
}

void CCDrawNode::drawSegment(const CCPoint &from, const CCPoint &to, float radius, const ccColor4F &color)
{
    unsigned int vertex_count = 6*3;
    ensureCapacity(vertex_count);
	
	ccVertex2F a = __v2f(from);
	ccVertex2F b = __v2f(to);
	
	
	ccVertex2F n = v2fnormalize(v2fperp(v2fsub(b, a)));
	ccVertex2F t = v2fperp(n);
	
	ccVertex2F nw = v2fmult(n, radius);
	ccVertex2F tw = v2fmult(t, radius);
	ccVertex2F v0 = v2fsub(b, v2fadd(nw, tw));
	ccVertex2F v1 = v2fadd(b, v2fsub(nw, tw));
	ccVertex2F v2 = v2fsub(b, nw);
	ccVertex2F v3 = v2fadd(b, nw);
	ccVertex2F v4 = v2fsub(a, nw);
	ccVertex2F v5 = v2fadd(a, nw);
	ccVertex2F v6 = v2fsub(a, v2fsub(nw, tw));
	ccVertex2F v7 = v2fadd(a, v2fadd(nw, tw));
	
	
	ccV2F_C4B_T2F_Triangle *triangles = (ccV2F_C4B_T2F_Triangle *)(m_pBuffer + m_nBufferCount);
	
	triangles[0] = (ccV2F_C4B_T2F_Triangle)
    {
		{v0, ccc4BFromccc4F(color), __t(v2fneg(v2fadd(n, t)))},
		{v1, ccc4BFromccc4F(color), __t(v2fsub(n, t))},
		{v2, ccc4BFromccc4F(color), __t(v2fneg(n))},
	};
	
	triangles[1] = (ccV2F_C4B_T2F_Triangle)
    {
		{v3, ccc4BFromccc4F(color), __t(n)},
		{v1, ccc4BFromccc4F(color), __t(v2fsub(n, t))},
		{v2, ccc4BFromccc4F(color), __t(v2fneg(n))},
	};
	
	triangles[2] = (ccV2F_C4B_T2F_Triangle)
    {
		{v3, ccc4BFromccc4F(color), __t(n)},
		{v4, ccc4BFromccc4F(color), __t(v2fneg(n))},
		{v2, ccc4BFromccc4F(color), __t(v2fneg(n))},
	};
	triangles[3] = (ccV2F_C4B_T2F_Triangle)
    {
		{v3, ccc4BFromccc4F(color), __t(n)},
		{v4, ccc4BFromccc4F(color), __t(v2fneg(n))},
		{v5, ccc4BFromccc4F(color), __t(n) },
	};
	triangles[4] = (ccV2F_C4B_T2F_Triangle){
		{v6, ccc4BFromccc4F(color), __t(v2fsub(t, n))},
		{v4, ccc4BFromccc4F(color), __t(v2fneg(n)) },
		{v5, ccc4BFromccc4F(color), __t(n)},
	};
	triangles[5] = (ccV2F_C4B_T2F_Triangle)
    {
		{v6, ccc4BFromccc4F(color), __t(v2fsub(t, n))},
		{v7, ccc4BFromccc4F(color), __t(v2fadd(n, t))},
		{v5, ccc4BFromccc4F(color), __t(n)},
	};
	
	m_nBufferCount += vertex_count;
	
	m_bDirty = true;
}

void CCDrawNode::drawPolygon(CCPoint *verts, unsigned int count, const ccColor4F &fillColor, float borderWidth, const ccColor4F &borderColor)
{
    struct ExtrudeVerts {ccVertex2F offset, n;};
	struct ExtrudeVerts extrude[count];
	bzero(extrude, sizeof(extrude) );
	
	for(int i = 0; i < count; i++)
    {
		ccVertex2F v0 = __v2f(verts[(i-1+count)%count]);
		ccVertex2F v1 = __v2f(verts[i]);
		ccVertex2F v2 = __v2f(verts[(i+1)%count]);
        
		ccVertex2F n1 = v2fnormalize(v2fperp(v2fsub(v1, v0)));
		ccVertex2F n2 = v2fnormalize(v2fperp(v2fsub(v2, v1)));
		
		ccVertex2F offset = v2fmult(v2fadd(n1, n2), 1.0/(v2fdot(n1, n2) + 1.0));
		extrude[i] = (struct ExtrudeVerts){offset, n2};
	}
	
	bool outline = (fillColor.a > 0.0 && borderWidth > 0.0);
	
	unsigned int triangle_count = 3*count - 2;
	unsigned int vertex_count = 3*triangle_count;
    ensureCapacity(vertex_count);
	
	ccV2F_C4B_T2F_Triangle *triangles = (ccV2F_C4B_T2F_Triangle *)(m_pBuffer + m_nBufferCount);
	ccV2F_C4B_T2F_Triangle *cursor = triangles;
	
	float inset = (outline == 0.0 ? 0.5 : 0.0);
	for(int i = 0; i < count-2; i++)
    {
		ccVertex2F v0 = v2fsub(__v2f(verts[0  ]), v2fmult(extrude[0  ].offset, inset));
		ccVertex2F v1 = v2fsub(__v2f(verts[i+1]), v2fmult(extrude[i+1].offset, inset));
		ccVertex2F v2 = v2fsub(__v2f(verts[i+2]), v2fmult(extrude[i+2].offset, inset));
		
		*cursor++ = (ccV2F_C4B_T2F_Triangle){
			{v0, ccc4BFromccc4F(fillColor), __t(v2fzero)},
			{v1, ccc4BFromccc4F(fillColor), __t(v2fzero)},
			{v2, ccc4BFromccc4F(fillColor), __t(v2fzero)},
		};
	}
	
	for(int i = 0; i < count; i++)
    {
		int j = (i+1)%count;
		ccVertex2F v0 = __v2f(verts[i]);
		ccVertex2F v1 = __v2f(verts[j]);
		
		ccVertex2F n0 = extrude[i].n;
		
		ccVertex2F offset0 = extrude[i].offset;
		ccVertex2F offset1 = extrude[j].offset;
		
		if(outline)
        {
			ccVertex2F inner0 = v2fsub(v0, v2fmult(offset0, borderWidth));
			ccVertex2F inner1 = v2fsub(v1, v2fmult(offset1, borderWidth));
			ccVertex2F outer0 = v2fadd(v0, v2fmult(offset0, borderWidth));
			ccVertex2F outer1 = v2fadd(v1, v2fmult(offset1, borderWidth));
			
			*cursor++ = (ccV2F_C4B_T2F_Triangle){
				{inner0, ccc4BFromccc4F(borderColor), __t(v2fneg(n0))},
				{inner1, ccc4BFromccc4F(borderColor), __t(v2fneg(n0))},
				{outer1, ccc4BFromccc4F(borderColor), __t(n0)}
			};
			*cursor++ = (ccV2F_C4B_T2F_Triangle){
				{inner0, ccc4BFromccc4F(borderColor), __t(v2fneg(n0))},
				{outer0, ccc4BFromccc4F(borderColor), __t(n0)},
				{outer1, ccc4BFromccc4F(borderColor), __t(n0)}
			};
		}
        else {
			ccVertex2F inner0 = v2fsub(v0, v2fmult(offset0, 0.5));
			ccVertex2F inner1 = v2fsub(v1, v2fmult(offset1, 0.5));
			ccVertex2F outer0 = v2fadd(v0, v2fmult(offset0, 0.5));
			ccVertex2F outer1 = v2fadd(v1, v2fmult(offset1, 0.5));
			
			*cursor++ = (ccV2F_C4B_T2F_Triangle){
				{inner0, ccc4BFromccc4F(fillColor), __t(v2fzero)},
				{inner1, ccc4BFromccc4F(fillColor), __t(v2fzero)},
				{outer1, ccc4BFromccc4F(fillColor), __t(n0)}
			};
			*cursor++ = (ccV2F_C4B_T2F_Triangle){
				{inner0, ccc4BFromccc4F(fillColor), __t(v2fzero)},
				{outer0, ccc4BFromccc4F(fillColor), __t(n0)},
				{outer1, ccc4BFromccc4F(fillColor), __t(n0)}
			};
		}
	}
	
	m_nBufferCount += vertex_count;
	
	m_bDirty = true;
}

void CCDrawNode::clear()
{
    m_nBufferCount = 0;
    m_bDirty = true;
}

ccBlendFunc CCDrawNode::getBlendFunc() const
{
    return m_sBlendFunc;
}

void CCDrawNode::setBlendFunc(const ccBlendFunc &blendFunc)
{
    m_sBlendFunc = blendFunc;
}

NS_CC_END
