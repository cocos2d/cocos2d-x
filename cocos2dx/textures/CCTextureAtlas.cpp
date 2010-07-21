/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "Cocos2dDefine.h"
// cocos2d
#include "CCTextureAtlas.h"
#include "CCTextureCache.h"
#include "ccMacros.h"
#include "ccConfig.h"

// support
#include "CCTexture2D.h"

//According to some tests GL_TRIANGLE_STRIP is slower, MUCH slower. Probably I'm doing something very wrong

// implementation CCTextureAtlas


CCTextureAtlas::CCTextureAtlas()
{

}

CCTextureAtlas::~CCTextureAtlas()
{
	CCLOGINFO("cocos2d: deallocing CCTextureAtlas.");

	CCX_SAFE_FREE(m_pQuads)
	CCX_SAFE_FREE(m_pIndices)

#if CC_TEXTURE_ATLAS_USES_VBO
	glDeleteBuffers(2, m_pBuffersVBO);
#endif // CC_TEXTURE_ATLAS_USES_VBO

	m_pTexture->release();
}

UINT32 CCTextureAtlas::getTotalQuads()
{
	return m_uTotalQuads;
}

UINT32 CCTextureAtlas::getCapacity()
{
	return m_uCapacity;
}

CCTexture2D* CCTextureAtlas::getTexture()
{
	return m_pTexture;
}

void CCTextureAtlas::setTexture(CCTexture2D * var)
{
	m_pTexture = var;
}

ccV3F_C4B_T2F_Quad* CCTextureAtlas::getQuads()
{
	return m_pQuads;
}

void CCTextureAtlas::setQuads(ccV3F_C4B_T2F_Quad *var)
{
	m_pQuads = var;
}

// TextureAtlas - alloc & init

CCTextureAtlas * CCTextureAtlas::textureAtlasWithFile(const std::string & file, UINT32 capacity)
{
	CCTextureAtlas * pTextureAtlas = new CCTextureAtlas();
	pTextureAtlas->initWithFile(file, capacity);
	pTextureAtlas->autorelease();
	return pTextureAtlas;
}

CCTextureAtlas * CCTextureAtlas::textureAtlasWithTexture(CCTexture2D *tex, UINT32 capacity)
{
	CCTextureAtlas * pTextureAtlas = new CCTextureAtlas();
	pTextureAtlas->initWithTexture(tex, capacity);
	pTextureAtlas->autorelease();
	return pTextureAtlas;
}

CCTextureAtlas * CCTextureAtlas::initWithFile(const std::string & file, UINT32 capacity)
{
	// retained in property
	CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addImage(file);	

	return initWithTexture(tex, capacity);
}

CCTextureAtlas * CCTextureAtlas::initWithTexture(CCTexture2D *tex, UINT32 capacity)
{

	m_uCapacity = capacity;
	m_uTotalQuads = 0;

	// retained in property
	this->m_pTexture = tex;

	m_pQuads = (ccV3F_C4B_T2F_Quad*)calloc( sizeof(ccV3F_C4B_T2F_Quad) * m_uCapacity, 1 );
	m_pIndices = (GLushort *)calloc( sizeof(GLushort) * m_uCapacity * 6, 1 );

	if( ! ( m_pQuads && m_pIndices) ) {
		CCLOG("cocos2d: CCTextureAtlas: not enough memory");
		CCX_SAFE_FREE(m_pQuads)
		CCX_SAFE_FREE(m_pIndices)
		return NULL;
	}

#if CC_TEXTURE_ATLAS_USES_VBO
	// initial binding
	glGenBuffers(2, &m_pBuffersVBO[0]);		
#endif // CC_TEXTURE_ATLAS_USES_VBO

	this->initIndices();

	return this;
}

std::string CCTextureAtlas::description()
{
	char des[100];
	sprintf_s(des, 100, "<CCTextureAtlas | totalQuads = %u>", m_uTotalQuads);
	string ret(des);

	return ret;
}


void CCTextureAtlas::initIndices()
{
	for( UINT32 i=0; i < m_uCapacity; i++)
	{
#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
		m_pIndices[i*6+0] = i*4+0;
		m_pIndices[i*6+1] = i*4+0;
		m_pIndices[i*6+2] = i*4+2;		
		m_pIndices[i*6+3] = i*4+1;
		m_pIndices[i*6+4] = i*4+3;
		m_pIndices[i*6+5] = i*4+3;
#else
		m_pIndices[i*6+0] = i*4+0;
		m_pIndices[i*6+1] = i*4+1;
		m_pIndices[i*6+2] = i*4+2;

		// inverted index. issue #179
		m_pIndices[i*6+3] = i*4+3;
		m_pIndices[i*6+4] = i*4+2;
		m_pIndices[i*6+5] = i*4+1;		
		//		m_pIndices[i*6+3] = i*4+2;
		//		m_pIndices[i*6+4] = i*4+3;
		//		m_pIndices[i*6+5] = i*4+1;	
#endif	
	}

#if CC_TEXTURE_ATLAS_USES_VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0]) * m_uCapacity, m_pQuads, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_pIndices[0]) * m_uCapacity * 6, m_pIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif // CC_TEXTURE_ATLAS_USES_VBO
}

// TextureAtlas - Update, Insert, Move & Remove

void CCTextureAtlas::updateQuad(ccV3F_C4B_T2F_Quad *quad, UINT32 index)
{
	NSAssert( index >= 0 && index < m_uCapacity, "updateQuadWithTexture: Invalid index");

	m_uTotalQuads = MAX( index+1, m_uTotalQuads);

	m_pQuads[index] = *quad;	
}

void CCTextureAtlas::insertQuad(ccV3F_C4B_T2F_Quad *quad, UINT32 index)
{
	NSAssert( index >= 0 && index < m_uCapacity, "insertQuadWithTexture: Invalid index");

	m_uTotalQuads++;
	NSAssert( m_uTotalQuads <= m_uCapacity, "invalid totalQuads");

	// issue #575. index can be > totalQuads
	int remaining = (m_uTotalQuads-1) - index;

	// last object doesn't need to be moved
	if( remaining > 0) {
		// tex coordinates
		memmove( &m_pQuads[index+1],&m_pQuads[index], sizeof(m_pQuads[0]) * remaining );		
	}

	m_pQuads[index] = *quad;
}

void CCTextureAtlas::insertQuadFromIndex(UINT32 oldIndex, UINT32 newIndex)
{
	NSAssert( newIndex >= 0 && newIndex < m_uTotalQuads, "insertQuadFromIndex:atIndex: Invalid index");
	NSAssert( oldIndex >= 0 && oldIndex < m_uTotalQuads, "insertQuadFromIndex:atIndex: Invalid index");

	if( oldIndex == newIndex )
		return;

	UINT32 howMany = std::abs( oldIndex - newIndex);
	int dst = oldIndex;
	int src = oldIndex + 1;
	if( oldIndex > newIndex) {
		dst = newIndex+1;
		src = newIndex;
	}

	// tex coordinates
	ccV3F_C4B_T2F_Quad quadsBackup = m_pQuads[oldIndex];
	memmove( &m_pQuads[dst],&m_pQuads[src], sizeof(m_pQuads[0]) * howMany );
	m_pQuads[newIndex] = quadsBackup;
}

void CCTextureAtlas::removeQuadAtIndex(UINT32 index)
{
	NSAssert( index >= 0 && index < m_uTotalQuads, "removeQuadAtIndex: Invalid index");

	UINT32 remaining = (m_uTotalQuads-1) - index;


	// last object doesn't need to be moved
	if( remaining ) {
		// tex coordinates
		memmove( &m_pQuads[index],&m_pQuads[index+1], sizeof(m_pQuads[0]) * remaining );
	}

	m_uTotalQuads--;

	NSAssert( m_uTotalQuads >= 0, "invalid totalQuads");
}

void CCTextureAtlas::removeAllQuads()
{
	m_uTotalQuads = 0;
}

// TextureAtlas - Resize
bool CCTextureAtlas::resizeCapacity(UINT32 newCapacity)
{
	if( newCapacity == m_uCapacity )
		return true;

	// update capacity and totolQuads
	m_uTotalQuads = MIN(m_uTotalQuads, newCapacity);
	m_uCapacity = newCapacity;

	void * tmpQuads = realloc( m_pQuads, sizeof(m_pQuads[0]) * m_uCapacity );
	void * tmpIndices = realloc( m_pIndices, sizeof(m_pIndices[0]) * m_uCapacity * 6 );

	if( ! ( tmpQuads && tmpIndices) ) {
		CCLOG("cocos2d: CCTextureAtlas: not enough memory");
		if( tmpQuads )
			free(tmpQuads);
		else
			free(m_pQuads);

		if( tmpIndices )
			free(tmpIndices);
		else
			free(m_pIndices);

		m_pQuads = NULL;
		m_pIndices = NULL;
		m_uCapacity = m_uTotalQuads = 0;
		return false;
	}

	m_pQuads = (ccV3F_C4B_T2F_Quad *)tmpQuads;
	m_pIndices = (GLushort *)tmpIndices;

	this->initIndices();

	return true;
}

// TextureAtlas - Drawing

void CCTextureAtlas::drawQuads()
{
	this->drawNumberOfQuads(m_uTotalQuads);
}

void CCTextureAtlas::drawNumberOfQuads(UINT32 n)
{	

	glBindTexture(GL_TEXTURE_2D, m_pTexture->getName());

#define kQuadSize sizeof(m_pQuads[0].bl)


#if CC_TEXTURE_ATLAS_USES_VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);

	// XXX: update is done in draw... perhaps it should be done in a timer
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_pQuads[0]) * n, m_pQuads);

	// vertices
	glVertexPointer(3, GL_FLOAT, kQuadSize, (void*) offsetof( ccV3F_C4B_T2F, vertices));

	// colors
	glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (void*) offsetof( ccV3F_C4B_T2F, colors));

	// tex coords
	glTexCoordPointer(2, GL_FLOAT, kQuadSize, (void*) offsetof( ccV3F_C4B_T2F, texCoords));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);
#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
	glDrawElements(GL_TRIANGLE_STRIP, n*6, GL_UNSIGNED_SHORT, (void*)0);    
#else
	glDrawElements(GL_TRIANGLES, n*6, GL_UNSIGNED_SHORT, (void*)0); 
#endif // CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#else // ! CC_TEXTURE_ATLAS_USES_VBO
	
	int offset = (int)m_pQuads;/// @todo my god! how to understand this

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexPointer(3, GL_FLOAT, kQuadSize, (void*) (offset + diff) );

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (void*)(offset + diff));

	// tex coords
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glTexCoordPointer(2, GL_FLOAT, kQuadSize, (void*)(offset + diff));

#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
	glDrawElements(GL_TRIANGLE_STRIP, n*6, GL_UNSIGNED_SHORT, m_pIndices);	
#else
	glDrawElements(GL_TRIANGLES, n*6, GL_UNSIGNED_SHORT, m_pIndices);	
#endif

#endif // CC_TEXTURE_ATLAS_USES_VBO
}


