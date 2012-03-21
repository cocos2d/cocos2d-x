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
#include "CCGLProgram.h"
#include "ccGLStateCache.h"
// support
#include "CCTexture2D.h"
#include "CCString.h"
#include <stdlib.h>

//According to some tests GL_TRIANGLE_STRIP is slower, MUCH slower. Probably I'm doing something very wrong

// implementation CCTextureAtlas

namespace   cocos2d {

CCTextureAtlas::CCTextureAtlas()
    :m_pIndices(NULL)
    ,m_bDirty(false)
    ,m_pTexture(NULL)
	,m_pQuads(NULL)
{}

CCTextureAtlas::~CCTextureAtlas()
{
//	CCLOGINFO("cocos2d: deallocing CCTextureAtlas.");

	CC_SAFE_FREE(m_pQuads);
	CC_SAFE_FREE(m_pIndices);

	glDeleteBuffers(2, m_pBuffersVBO);
	glDeleteVertexArrays(1, &m_uVAOname);

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
	//if someone accesses the quads directly, presume that changes will be made
	m_bDirty = true;
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
	CCAssert(texture != NULL, "texture should not be null");
	m_uCapacity = capacity;
	m_uTotalQuads = 0;

	// retained in property
	this->m_pTexture = texture;
	CC_SAFE_RETAIN(m_pTexture);

	// Re-initialization is not allowed
	CCAssert(m_pQuads == NULL && m_pIndices == NULL, "");

	m_pQuads = (ccV3F_C4B_T2F_Quad*)malloc( m_uCapacity * sizeof(ccV3F_C4B_T2F_Quad) );
	m_pIndices = (GLushort *)malloc( m_uCapacity * 6 * sizeof(GLushort) );

	if( ! ( m_pQuads && m_pIndices) && m_uCapacity > 0) {
		//CCLOG("cocos2d: CCTextureAtlas: not enough memory");
		CC_SAFE_FREE(m_pQuads);
		CC_SAFE_FREE(m_pIndices);

		// release texture, should set it to null, because the destruction will
		// release it too. see cocos2d-x issue #484
		CC_SAFE_RELEASE_NULL(m_pTexture);
		return false;
	}

	this->initIndices();
	this->initVAO();

	m_bDirty = true;

	return true;
}

const char* CCTextureAtlas::description()
{
	char* pszDescription = (char*)malloc(100*sizeof(char));
	sprintf(pszDescription, "<CCTextureAtlas | totalQuads = %u>", m_uTotalQuads);
    CCString* pRet = new CCString(pszDescription);
    pRet->autorelease();
    CC_SAFE_FREE(pszDescription);
	return pRet->c_str();
}


void CCTextureAtlas::initIndices()
{
	if (m_uCapacity == 0)
		return;

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
}

void CCTextureAtlas::initVAO()
{
	glGenVertexArrays(1, &m_uVAOname);
	glBindVertexArray(m_uVAOname);

#define kQuadSize sizeof(m_pQuads[0].bl)

	glGenBuffers(2, &m_pBuffersVBO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0]) * m_uCapacity, m_pQuads, GL_DYNAMIC_DRAW);

	// vertices
	glEnableVertexAttribArray(kCCVertexAttrib_Position);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, vertices));

	// colors
	glEnableVertexAttribArray(kCCVertexAttrib_Color);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, colors));

	// tex coords
	glEnableVertexAttribArray(kCCVertexAttrib_TexCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, texCoords));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_pIndices[0]) * m_uCapacity * 6, m_pIndices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	CHECK_GL_ERROR_DEBUG();
}

void CCTextureAtlas::mapBuffers()
{
	initIndices();
	initVAO();

	glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0]) * m_uCapacity, m_pQuads, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_pIndices[0]) * m_uCapacity * 6, m_pIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CHECK_GL_ERROR_DEBUG();
}

// TextureAtlas - Update, Insert, Move & Remove

void CCTextureAtlas::updateQuad(ccV3F_C4B_T2F_Quad *quad, unsigned int index)
{
	CCAssert( index >= 0 && index < m_uCapacity, "updateQuadWithTexture: Invalid index");

	m_uTotalQuads = MAX( index+1, m_uTotalQuads);

	m_pQuads[index] = *quad;	


	m_bDirty = true;

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


	m_bDirty = true;

}

void CCTextureAtlas::insertQuads(ccV3F_C4B_T2F_Quad* quads, unsigned int index, unsigned int amount)
{
	CCAssert(index + amount <= m_uCapacity, "insertQuadWithTexture: Invalid index + amount");

	m_uTotalQuads += amount;

	CCAssert( m_uTotalQuads <= m_uCapacity, "invalid totalQuads");

	// issue #575. index can be > totalQuads
	int remaining = (m_uTotalQuads-1) - index - amount;

	// last object doesn't need to be moved
	if( remaining > 0)
		// tex coordinates
		memmove( &m_pQuads[index+amount],&m_pQuads[index], sizeof(m_pQuads[0]) * remaining );



	unsigned int max = index + amount;
	unsigned int j = 0;
	for (unsigned int i = index; i < max ; i++)
	{
		m_pQuads[index] = quads[j];
		index++;
		j++;
	}

	m_bDirty = true;
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


	m_bDirty = true;

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


	m_bDirty = true;

}

void CCTextureAtlas::removeQuadsAtIndex(unsigned int index, unsigned int amount)
{
	CCAssert(index + amount <= m_uTotalQuads, "removeQuadAtIndex: index + amount out of bounds");

	unsigned int remaining = (m_uTotalQuads) - (index + amount);

	m_uTotalQuads -= amount;

	if ( remaining )
		memmove( &m_pQuads[index], &m_pQuads[index+amount], sizeof(m_pQuads[0]) * remaining );

	m_bDirty = true;
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
	m_uTotalQuads = MIN(m_uTotalQuads, newCapacity);
	m_uCapacity = newCapacity;

	void * tmpQuads = NULL;
	void * tmpIndices = NULL;
	
	// when calling initWithTexture(fileName, 0) on bada device, calloc(0, 1) will fail and return NULL,
	// so here must judge whether m_pQuads and m_pIndices is NULL.
	if (m_pQuads == NULL)
    {
		tmpQuads = malloc(m_uCapacity * sizeof(m_pQuads[0]));
    }
    else
    {
		tmpQuads = realloc( m_pQuads, sizeof(m_pQuads[0]) * m_uCapacity );
    }

	if (m_pIndices == NULL)
    {	
        tmpIndices = malloc( m_uCapacity * 6 * sizeof(m_pIndices[0]));
    }
    else
    {
		tmpIndices = realloc( m_pIndices, sizeof(m_pIndices[0]) * m_uCapacity * 6 );
    }

	if( ! ( tmpQuads && tmpIndices) ) {
		CCLOG("cocos2d: CCTextureAtlas: not enough memory");
        CC_SAFE_FREE(tmpQuads);
        CC_SAFE_FREE(tmpIndices);
        CC_SAFE_FREE(m_pQuads);
        CC_SAFE_FREE(m_pIndices);
		m_uCapacity = m_uTotalQuads = 0;
		return false;
	}

	m_pQuads = (ccV3F_C4B_T2F_Quad *)tmpQuads;
	m_pIndices = (GLushort *)tmpIndices;


	glDeleteBuffers(2, m_pBuffersVBO);
	glDeleteVertexArrays(1, &m_uVAOname);
	// initial binding
	glGenBuffers(2, &m_pBuffersVBO[0]);	

	this->mapBuffers();

	m_bDirty = true;

	return true;
}

void CCTextureAtlas::increaseTotalQuadsWith(unsigned int amount)
{
	m_uTotalQuads += amount;
}

void CCTextureAtlas::moveQuadsFromIndex(unsigned int oldIndex, unsigned int amount, unsigned int newIndex)
{
	CCAssert(newIndex + amount <= m_uTotalQuads, "insertQuadFromIndex:atIndex: Invalid index");
	CCAssert(oldIndex < m_uTotalQuads, "insertQuadFromIndex:atIndex: Invalid index");

	if( oldIndex == newIndex )
		return;

	//create buffer
	size_t quadSize = sizeof(ccV3F_C4B_T2F_Quad);
	ccV3F_C4B_T2F_Quad* tempQuads = (ccV3F_C4B_T2F_Quad*)malloc( quadSize * amount);
	memcpy( tempQuads, &m_pQuads[oldIndex], quadSize * amount );

	if (newIndex < oldIndex)
	{
		// move quads from newIndex to newIndex + amount to make room for buffer
		memmove( &m_pQuads[newIndex], &m_pQuads[newIndex+amount], (oldIndex-newIndex)*quadSize);
	}
	else
	{
		// move quads above back
		memmove( &m_pQuads[oldIndex], &m_pQuads[oldIndex+amount], (newIndex-oldIndex)*quadSize);
	}
	memcpy( &m_pQuads[newIndex], tempQuads, amount*quadSize);

	free(tempQuads);

	m_bDirty = true;
}

void CCTextureAtlas::moveQuadsFromIndex(unsigned int index, unsigned int newIndex)
{
	CCAssert(newIndex + (m_uTotalQuads - index) <= m_uCapacity, "moveQuadsFromIndex move is out of bounds");

	memmove(m_pQuads + newIndex,m_pQuads + index, (m_uTotalQuads - index) * sizeof(m_pQuads[0]));
}

void CCTextureAtlas::fillWithEmptyQuadsFromIndex(unsigned int index, unsigned int amount)
{
	ccV3F_C4B_T2F_Quad* quad = (ccV3F_C4B_T2F_Quad*)calloc(1,sizeof(ccV3F_C4B_T2F_Quad));

	unsigned int to = index + amount;
	for (int i = index ; i < to ; i++)
	{
		m_pQuads[i] = *quad;
	}
}

// TextureAtlas - Drawing

void CCTextureAtlas::drawQuads()
{
	this->drawNumberOfQuads(m_uTotalQuads, 0);
}

void CCTextureAtlas::drawNumberOfQuads(unsigned int n)
{
	this->drawNumberOfQuads(n, 0);
}

void CCTextureAtlas::drawNumberOfQuads(unsigned int n, unsigned int start)
{	
    if (0 == n) return;
	ccGLBindTexture2D( m_pTexture->getName() );

	// XXX: update is done in draw... perhaps it should be done in a timer
	if (m_bDirty) {
		glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0])*start, sizeof(m_pQuads[0]) * n , &m_pQuads[start] );

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_bDirty = false;
	}

	glBindVertexArray( m_uVAOname );

/* FIXME: Because start always is zero, the result of (start*6*sizeof(m_pIndices[0])) will always be zero too. And crash will appear on some devices.
          I'm not familiar with opengles, but my change works. --By James Chen.
*/
#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
	glDrawElements(GL_TRIANGLE_STRIP, (GLsizei) n*6, GL_UNSIGNED_SHORT, (GLvoid*) (m_pIndices)/*(start*6*sizeof(m_pIndices[0]))*/ );
#else
	glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, (GLvoid*) (m_pIndices)/*(start*6*sizeof(m_pIndices[0]))*/ );
#endif // CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP


	glBindVertexArray(0);

	CHECK_GL_ERROR_DEBUG();
}


}//namespace   cocos2d 
