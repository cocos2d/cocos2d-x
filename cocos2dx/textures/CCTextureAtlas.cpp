/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

// cocos2d
#include "CCTextureAtlas.h"
#include "CCTextureCache.h"
#include "ccMacros.h"

// support
#include "CCTexture2D.h"

#include <stdlib.h>

//According to some tests GL_TRIANGLE_STRIP is slower, MUCH slower. Probably I'm doing something very wrong

// implementation CCTextureAtlas

namespace   cocos2d {

CCTextureAtlas::CCTextureAtlas()
    :m_pIndices(NULL)
	,m_pTexture(NULL)	
	,m_pQuads(NULL)
#if CC_USES_VBO
	, m_bDirty(false)
#endif
{}

CCTextureAtlas::~CCTextureAtlas()
{
//	CCLOGINFO("cocos2d: deallocing CCTextureAtlas.");

	CC_SAFE_FREE(m_pQuads)
	CC_SAFE_FREE(m_pIndices)

#if CC_USES_VBO
	glDeleteBuffers(2, m_pBuffersVBO);
#endif // CC_USES_VBO

	CC_SAFE_RELEASE(m_pTexture);
}

unsigned int CCTextureAtlas::getTotalQuads()
{
	return m_uTotalQuads;
}

unsigned int CCTextureAtlas::getCapacity()
{
	return m_uCapacity;
}

CCTexture2D* CCTextureAtlas::getTexture()
{
	return m_pTexture;
}

void CCTextureAtlas::setTexture(CCTexture2D * var)
{
	CC_SAFE_RETAIN(var);
	CC_SAFE_RELEASE(m_pTexture);
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

CCTextureAtlas * CCTextureAtlas::textureAtlasWithFile(const char* file, unsigned int capacity)
{
	CCTextureAtlas * pTextureAtlas = new CCTextureAtlas();
	if(pTextureAtlas && pTextureAtlas->initWithFile(file, capacity))
	{
		pTextureAtlas->autorelease();
		return pTextureAtlas;
	}
	CC_SAFE_DELETE(pTextureAtlas);
	return NULL;
}

CCTextureAtlas * CCTextureAtlas::textureAtlasWithTexture(CCTexture2D *texture, unsigned int capacity)
{
	CCTextureAtlas * pTextureAtlas = new CCTextureAtlas();
	if (pTextureAtlas && pTextureAtlas->initWithTexture(texture, capacity))
	{
		pTextureAtlas->autorelease();
		return pTextureAtlas;
	}
	CC_SAFE_DELETE(pTextureAtlas);
	return NULL;
}

bool CCTextureAtlas::initWithFile(const char * file, unsigned int capacity)
{
	// retained in property
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(file);

	if (texture)
	{
        return initWithTexture(texture, capacity);
	}
	else
	{
		CCLOG("cocos2d: Could not open file: %s", file);
		delete this;

		return NULL;
	}
}

bool CCTextureAtlas::initWithTexture(CCTexture2D *texture, unsigned int capacity)
{
	assert(texture != NULL);
	m_uCapacity = capacity;
	m_uTotalQuads = 0;

	// retained in property
	this->m_pTexture = texture;
	CC_SAFE_RETAIN(m_pTexture);

	// Re-initialization is not allowed
	assert(m_pQuads == NULL && m_pIndices == NULL);

	m_pQuads = (ccV3F_C4B_T2F_Quad*)calloc( sizeof(ccV3F_C4B_T2F_Quad) * m_uCapacity, 1 );
	m_pIndices = (GLushort *)calloc( sizeof(GLushort) * m_uCapacity * 6, 1 );

	if( ! ( m_pQuads && m_pIndices) ) {
		//CCLOG("cocos2d: CCTextureAtlas: not enough memory");
		CC_SAFE_FREE(m_pQuads)
		CC_SAFE_FREE(m_pIndices)

		// release texture, should set it to null, because the destruction will
		// release it too. see cocos2d-x issue #484
		CC_SAFE_RELEASE_NULL(m_pTexture);
		return false;
	}

#if CC_USES_VBO
	// initial binding
	glGenBuffers(2, &m_pBuffersVBO[0]);	
	m_bDirty = true;
#endif // CC_USES_VBO

	this->initIndices();

	return true;
}

char * CCTextureAtlas::description()
{
	char *ret = new char[100];
	sprintf(ret, "<CCTextureAtlas | totalQuads = %u>", m_uTotalQuads);
	return ret;
}


void CCTextureAtlas::initIndices()
{
	for( unsigned int i=0; i < m_uCapacity; i++)
	{
#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
		m_pIndices[i*6+0] = i*4+0;
		m_pIndices[i*6+1] = i*4+0;
		m_pIndices[i*6+2] = i*4+2;		
		m_pIndices[i*6+3] = i*4+1;
		m_pIndices[i*6+4] = i*4+3;
		m_pIndices[i*6+5] = i*4+3;
#else
		m_pIndices[i*6+0] = (GLushort)(i*4+0);
		m_pIndices[i*6+1] = (GLushort)(i*4+1);
		m_pIndices[i*6+2] = (GLushort)(i*4+2);

		// inverted index. issue #179
		m_pIndices[i*6+3] = (GLushort)(i*4+3);
		m_pIndices[i*6+4] = (GLushort)(i*4+2);
		m_pIndices[i*6+5] = (GLushort)(i*4+1);		
		//		m_pIndices[i*6+3] = i*4+2;
		//		m_pIndices[i*6+4] = i*4+3;
		//		m_pIndices[i*6+5] = i*4+1;	
#endif	
	}

#if CC_USES_VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0]) * m_uCapacity, m_pQuads, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_pIndices[0]) * m_uCapacity * 6, m_pIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif // CC_USES_VBO
}

// TextureAtlas - Update, Insert, Move & Remove

void CCTextureAtlas::updateQuad(ccV3F_C4B_T2F_Quad *quad, unsigned int index)
{
	CCAssert( index >= 0 && index < m_uCapacity, "updateQuadWithTexture: Invalid index");

	m_uTotalQuads = max( index+1, m_uTotalQuads);

	m_pQuads[index] = *quad;	

#if CC_USES_VBO
	m_bDirty = true;
#endif
}

void CCTextureAtlas::insertQuad(ccV3F_C4B_T2F_Quad *quad, unsigned int index)
{
	CCAssert( index < m_uCapacity, "insertQuadWithTexture: Invalid index");

	m_uTotalQuads++;
	CCAssert( m_uTotalQuads <= m_uCapacity, "invalid totalQuads");

	// issue #575. index can be > totalQuads
	unsigned int remaining = (m_uTotalQuads-1) - index;

	// last object doesn't need to be moved
	if( remaining > 0) {
		// texture coordinates
		memmove( &m_pQuads[index+1],&m_pQuads[index], sizeof(m_pQuads[0]) * remaining );		
	}

	m_pQuads[index] = *quad;

#if CC_USES_VBO
	m_bDirty = true;
#endif
}

void CCTextureAtlas::insertQuadFromIndex(unsigned int oldIndex, unsigned int newIndex)
{
	CCAssert( newIndex >= 0 && newIndex < m_uTotalQuads, "insertQuadFromIndex:atIndex: Invalid index");
	CCAssert( oldIndex >= 0 && oldIndex < m_uTotalQuads, "insertQuadFromIndex:atIndex: Invalid index");

	if( oldIndex == newIndex )
		return;

	// because it is ambigious in iphone, so we implement abs ourself
	// unsigned int howMany = abs( oldIndex - newIndex);
	unsigned int howMany = (oldIndex - newIndex) > 0 ? (oldIndex - newIndex) :  (newIndex - oldIndex);
	unsigned int dst = oldIndex;
	unsigned int src = oldIndex + 1;
	if( oldIndex > newIndex) {
		dst = newIndex+1;
		src = newIndex;
	}

	// texture coordinates
	ccV3F_C4B_T2F_Quad quadsBackup = m_pQuads[oldIndex];
	memmove( &m_pQuads[dst],&m_pQuads[src], sizeof(m_pQuads[0]) * howMany );
	m_pQuads[newIndex] = quadsBackup;

#if CC_USES_VBO
	m_bDirty = true;
#endif
}

void CCTextureAtlas::removeQuadAtIndex(unsigned int index)
{
	CCAssert( index < m_uTotalQuads, "removeQuadAtIndex: Invalid index");

	unsigned int remaining = (m_uTotalQuads-1) - index;


	// last object doesn't need to be moved
	if( remaining ) {
		// texture coordinates
		memmove( &m_pQuads[index],&m_pQuads[index+1], sizeof(m_pQuads[0]) * remaining );
	}

	m_uTotalQuads--;

#if CC_USES_VBO
	m_bDirty = true;
#endif
}

void CCTextureAtlas::removeAllQuads()
{
	m_uTotalQuads = 0;
}

// TextureAtlas - Resize
bool CCTextureAtlas::resizeCapacity(unsigned int newCapacity)
{
	if( newCapacity == m_uCapacity )
		return true;

	// update capacity and totolQuads
	m_uTotalQuads = min(m_uTotalQuads, newCapacity);
	m_uCapacity = newCapacity;

	void * tmpQuads = realloc( m_pQuads, sizeof(m_pQuads[0]) * m_uCapacity );
	void * tmpIndices = realloc( m_pIndices, sizeof(m_pIndices[0]) * m_uCapacity * 6 );

	if( ! ( tmpQuads && tmpIndices) ) {
		//CCLOG("cocos2d: CCTextureAtlas: not enough memory");
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

#if CC_USES_VBO
	m_bDirty = true;
#endif

	return true;
}

// TextureAtlas - Drawing

void CCTextureAtlas::drawQuads()
{
	this->drawNumberOfQuads(m_uTotalQuads, 0);
}

void CCTextureAtlas::drawNumberOfQuads(unsigned int n)
{
	this->drawNumberOfQuads(m_uTotalQuads, 0);
}

void CCTextureAtlas::drawNumberOfQuads(unsigned int n, unsigned int start)
{	
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Unneeded states: -

	glBindTexture(GL_TEXTURE_2D, m_pTexture->getName());

#define kQuadSize sizeof(m_pQuads[0].bl)


#if CC_USES_VBO

    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);

#if CC_ENABLE_CACHE_TEXTTURE_DATA
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0]) * m_uCapacity, m_pQuads, GL_DYNAMIC_DRAW);
#endif

	// XXX: update is done in draw... perhaps it should be done in a timer
	if (m_bDirty)
	{
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0]) * start, sizeof(m_pQuads[0]) * n, &m_pQuads[start]);
		m_bDirty = false;
	}
	

	// vertices
	glVertexPointer(3, GL_FLOAT, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, vertices));

	// colors
	glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, colors));

	// texture coords
	glTexCoordPointer(2, GL_FLOAT, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, texCoords));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);

#if CC_ENABLE_CACHE_TEXTTURE_DATA
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_pIndices[0]) * m_uCapacity * 6, m_pIndices, GL_STATIC_DRAW);
#endif

#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
	glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)n*6, GL_UNSIGNED_SHORT, (GLvoid*)(start * 6 * sizeof(m_pIndices[0])));    
#else
	glDrawElements(GL_TRIANGLES, (GLsizei)n*6, GL_UNSIGNED_SHORT, (GLvoid*)(start * 6 * sizeof(m_pIndices[0]))); 
#endif // CC_USES_VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#else // ! CC_USES_VBO
	
	unsigned int offset = (unsigned int)m_pQuads;

	// vertex
	unsigned int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexPointer(3, GL_FLOAT, kQuadSize, (GLvoid*) (offset + diff) );

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (GLvoid*)(offset + diff));

	// texture coords
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glTexCoordPointer(2, GL_FLOAT, kQuadSize, (GLvoid*)(offset + diff));

#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
	glDrawElements(GL_TRIANGLE_STRIP, n*6, GL_UNSIGNED_SHORT, m_pIndices + start * 6);	
#else
	glDrawElements(GL_TRIANGLES, n*6, GL_UNSIGNED_SHORT, m_pIndices + start * 6);	
#endif

#endif // CC_USES_VBO
}


}//namespace   cocos2d 
