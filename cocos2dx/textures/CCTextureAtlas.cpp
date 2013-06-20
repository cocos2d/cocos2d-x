/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "support/CCNotificationCenter.h"
#include "CCEventType.h"
#include "CCGL.h"
// support
#include "CCTexture2D.h"
#include "cocoa/CCString.h"
#include <stdlib.h>

//According to some tests GL_TRIANGLE_STRIP is slower, MUCH slower. Probably I'm doing something very wrong

// implementation TextureAtlas

NS_CC_BEGIN

TextureAtlas::TextureAtlas()
    :_indices(NULL)
    ,_dirty(false)
    ,_texture(NULL)
    ,_quads(NULL)
{}

TextureAtlas::~TextureAtlas()
{
    CCLOGINFO("cocos2d: TextureAtlas deallocing %p.", this);

    CC_SAFE_FREE(_quads);
    CC_SAFE_FREE(_indices);

    glDeleteBuffers(2, _buffersVBO);

#if CC_TEXTURE_ATLAS_USE_VAO
    glDeleteVertexArrays(1, &_VAOname);
#endif
    CC_SAFE_RELEASE(_texture);
    
    NotificationCenter::sharedNotificationCenter()->removeObserver(this, EVNET_COME_TO_FOREGROUND);
}

unsigned int TextureAtlas::getTotalQuads() const
{
    return _totalQuads;
}

unsigned int TextureAtlas::getCapacity() const
{
    return _capacity;
}

Texture2D* TextureAtlas::getTexture()
{
    return _texture;
}

void TextureAtlas::setTexture(Texture2D * var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_texture);
    _texture = var;
}

ccV3F_C4B_T2F_Quad* TextureAtlas::getQuads()
{
    //if someone accesses the quads directly, presume that changes will be made
    _dirty = true;
    return _quads;
}

void TextureAtlas::setQuads(ccV3F_C4B_T2F_Quad *var)
{
    _quads = var;
}

// TextureAtlas - alloc & init

TextureAtlas * TextureAtlas::create(const char* file, unsigned int capacity)
{
    TextureAtlas * pTextureAtlas = new TextureAtlas();
    if(pTextureAtlas && pTextureAtlas->initWithFile(file, capacity))
    {
        pTextureAtlas->autorelease();
        return pTextureAtlas;
    }
    CC_SAFE_DELETE(pTextureAtlas);
    return NULL;
}

TextureAtlas * TextureAtlas::createWithTexture(Texture2D *texture, unsigned int capacity)
{
    TextureAtlas * pTextureAtlas = new TextureAtlas();
    if (pTextureAtlas && pTextureAtlas->initWithTexture(texture, capacity))
    {
        pTextureAtlas->autorelease();
        return pTextureAtlas;
    }
    CC_SAFE_DELETE(pTextureAtlas);
    return NULL;
}

bool TextureAtlas::initWithFile(const char * file, unsigned int capacity)
{
    // retained in property
    Texture2D *texture = TextureCache::sharedTextureCache()->addImage(file);

    if (texture)
    {
        return initWithTexture(texture, capacity);
    }
    else
    {
        CCLOG("cocos2d: Could not open file: %s", file);
        return false;
    }
}

bool TextureAtlas::initWithTexture(Texture2D *texture, unsigned int capacity)
{
//    CCAssert(texture != NULL, "texture should not be null");
    _capacity = capacity;
    _totalQuads = 0;

    // retained in property
    this->_texture = texture;
    CC_SAFE_RETAIN(_texture);

    // Re-initialization is not allowed
    CCAssert(_quads == NULL && _indices == NULL, "");

    _quads = (ccV3F_C4B_T2F_Quad*)malloc( _capacity * sizeof(ccV3F_C4B_T2F_Quad) );
    _indices = (GLushort *)malloc( _capacity * 6 * sizeof(GLushort) );
    
    if( ! ( _quads && _indices) && _capacity > 0) 
    {
        //CCLOG("cocos2d: TextureAtlas: not enough memory");
        CC_SAFE_FREE(_quads);
        CC_SAFE_FREE(_indices);

        // release texture, should set it to null, because the destruction will
        // release it too. see cocos2d-x issue #484
        CC_SAFE_RELEASE_NULL(_texture);
        return false;
    }

    memset( _quads, 0, _capacity * sizeof(ccV3F_C4B_T2F_Quad) );
    memset( _indices, 0, _capacity * 6 * sizeof(GLushort) );
    
    // listen the event when app go to background
    NotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                           callfuncO_selector(TextureAtlas::listenBackToForeground),
                                                           EVNET_COME_TO_FOREGROUND,
                                                           NULL);

    this->setupIndices();

#if CC_TEXTURE_ATLAS_USE_VAO
    setupVBOandVAO();    
#else    
    setupVBO();
#endif

    _dirty = true;

    return true;
}

void TextureAtlas::listenBackToForeground(Object *obj)
{  
#if CC_TEXTURE_ATLAS_USE_VAO
    setupVBOandVAO();    
#else    
    setupVBO();
#endif
    
    // set _dirty to true to force it rebinding buffer
    _dirty = true;
}

const char* TextureAtlas::description()
{
    return String::createWithFormat("<TextureAtlas | totalQuads = %u>", _totalQuads)->getCString();
}


void TextureAtlas::setupIndices()
{
    if (_capacity == 0)
        return;

    for( unsigned int i=0; i < _capacity; i++)
    {
#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
        _indices[i*6+0] = i*4+0;
        _indices[i*6+1] = i*4+0;
        _indices[i*6+2] = i*4+2;        
        _indices[i*6+3] = i*4+1;
        _indices[i*6+4] = i*4+3;
        _indices[i*6+5] = i*4+3;
#else
        _indices[i*6+0] = i*4+0;
        _indices[i*6+1] = i*4+1;
        _indices[i*6+2] = i*4+2;

        // inverted index. issue #179
        _indices[i*6+3] = i*4+3;
        _indices[i*6+4] = i*4+2;
        _indices[i*6+5] = i*4+1;        
#endif    
    }
}

//TextureAtlas - VAO / VBO specific

#if CC_TEXTURE_ATLAS_USE_VAO
void TextureAtlas::setupVBOandVAO()
{
    glGenVertexArrays(1, &_VAOname);
    ccGLBindVAO(_VAOname);

#define kQuadSize sizeof(_quads[0].bl)

    glGenBuffers(2, &_buffersVBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _capacity, _quads, GL_DYNAMIC_DRAW);

    // vertices
    glEnableVertexAttribArray(kVertexAttrib_Position);
    glVertexAttribPointer(kVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, vertices));

    // colors
    glEnableVertexAttribArray(kVertexAttrib_Color);
    glVertexAttribPointer(kVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, colors));

    // tex coords
    glEnableVertexAttribArray(kVertexAttrib_TexCoords);
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( ccV3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 6, _indices, GL_STATIC_DRAW);

    // Must unbind the VAO before changing the element buffer.
    ccGLBindVAO(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}
#else // CC_TEXTURE_ATLAS_USE_VAO
void TextureAtlas::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);

    mapBuffers();
}
#endif // ! // CC_TEXTURE_ATLAS_USE_VAO

void TextureAtlas::mapBuffers()
{
    // Avoid changing the element buffer for whatever VAO might be bound.
	ccGLBindVAO(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _capacity, _quads, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 6, _indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

// TextureAtlas - Update, Insert, Move & Remove

void TextureAtlas::updateQuad(ccV3F_C4B_T2F_Quad *quad, unsigned int index)
{
    CCAssert( index >= 0 && index < _capacity, "updateQuadWithTexture: Invalid index");

    _totalQuads = MAX( index+1, _totalQuads);

    _quads[index] = *quad;    


    _dirty = true;

}

void TextureAtlas::insertQuad(ccV3F_C4B_T2F_Quad *quad, unsigned int index)
{
    CCAssert( index < _capacity, "insertQuadWithTexture: Invalid index");

    _totalQuads++;
    CCAssert( _totalQuads <= _capacity, "invalid totalQuads");

    // issue #575. index can be > totalQuads
    unsigned int remaining = (_totalQuads-1) - index;

    // last object doesn't need to be moved
    if( remaining > 0) 
    {
        // texture coordinates
        memmove( &_quads[index+1],&_quads[index], sizeof(_quads[0]) * remaining );        
    }

    _quads[index] = *quad;


    _dirty = true;

}

void TextureAtlas::insertQuads(ccV3F_C4B_T2F_Quad* quads, unsigned int index, unsigned int amount)
{
    CCAssert(index + amount <= _capacity, "insertQuadWithTexture: Invalid index + amount");

    _totalQuads += amount;

    CCAssert( _totalQuads <= _capacity, "invalid totalQuads");

    // issue #575. index can be > totalQuads
    int remaining = (_totalQuads-1) - index - amount;

    // last object doesn't need to be moved
    if( remaining > 0)
    {
        // tex coordinates
        memmove( &_quads[index+amount],&_quads[index], sizeof(_quads[0]) * remaining );
    }


    unsigned int max = index + amount;
    unsigned int j = 0;
    for (unsigned int i = index; i < max ; i++)
    {
        _quads[index] = quads[j];
        index++;
        j++;
    }

    _dirty = true;
}

void TextureAtlas::insertQuadFromIndex(unsigned int oldIndex, unsigned int newIndex)
{
    CCAssert( newIndex >= 0 && newIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
    CCAssert( oldIndex >= 0 && oldIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");

    if( oldIndex == newIndex )
    {
        return;
    }
    // because it is ambiguous in iphone, so we implement abs ourselves
    // unsigned int howMany = abs( oldIndex - newIndex);
    unsigned int howMany = (oldIndex - newIndex) > 0 ? (oldIndex - newIndex) :  (newIndex - oldIndex);
    unsigned int dst = oldIndex;
    unsigned int src = oldIndex + 1;
    if( oldIndex > newIndex)
    {
        dst = newIndex+1;
        src = newIndex;
    }

    // texture coordinates
    ccV3F_C4B_T2F_Quad quadsBackup = _quads[oldIndex];
    memmove( &_quads[dst],&_quads[src], sizeof(_quads[0]) * howMany );
    _quads[newIndex] = quadsBackup;


    _dirty = true;

}

void TextureAtlas::removeQuadAtIndex(unsigned int index)
{
    CCAssert( index < _totalQuads, "removeQuadAtIndex: Invalid index");

    unsigned int remaining = (_totalQuads-1) - index;


    // last object doesn't need to be moved
    if( remaining ) 
    {
        // texture coordinates
        memmove( &_quads[index],&_quads[index+1], sizeof(_quads[0]) * remaining );
    }

    _totalQuads--;


    _dirty = true;

}

void TextureAtlas::removeQuadsAtIndex(unsigned int index, unsigned int amount)
{
    CCAssert(index + amount <= _totalQuads, "removeQuadAtIndex: index + amount out of bounds");

    unsigned int remaining = (_totalQuads) - (index + amount);

    _totalQuads -= amount;

    if ( remaining )
    {
        memmove( &_quads[index], &_quads[index+amount], sizeof(_quads[0]) * remaining );
    }

    _dirty = true;
}

void TextureAtlas::removeAllQuads()
{
    _totalQuads = 0;
}

// TextureAtlas - Resize
bool TextureAtlas::resizeCapacity(unsigned int newCapacity)
{
    if( newCapacity == _capacity )
    {
        return true;
    }
    unsigned int uOldCapactiy = _capacity; 
    // update capacity and totolQuads
    _totalQuads = MIN(_totalQuads, newCapacity);
    _capacity = newCapacity;

    ccV3F_C4B_T2F_Quad* tmpQuads = NULL;
    GLushort* tmpIndices = NULL;
    
    // when calling initWithTexture(fileName, 0) on bada device, calloc(0, 1) will fail and return NULL,
    // so here must judge whether _quads and _indices is NULL.
    if (_quads == NULL)
    {
        tmpQuads = (ccV3F_C4B_T2F_Quad*)malloc( _capacity * sizeof(_quads[0]) );
        if (tmpQuads != NULL)
        {
            memset(tmpQuads, 0, _capacity * sizeof(_quads[0]) );
        }
    }
    else
    {
        tmpQuads = (ccV3F_C4B_T2F_Quad*)realloc( _quads, sizeof(_quads[0]) * _capacity );
        if (tmpQuads != NULL && _capacity > uOldCapactiy)
        {
            memset(tmpQuads+uOldCapactiy, 0, (_capacity - uOldCapactiy)*sizeof(_quads[0]) );
        }
    }

    if (_indices == NULL)
    {    
        tmpIndices = (GLushort*)malloc( _capacity * 6 * sizeof(_indices[0]) );
        if (tmpIndices != NULL)
        {
            memset( tmpIndices, 0, _capacity * 6 * sizeof(_indices[0]) );
        }
        
    }
    else
    {
        tmpIndices = (GLushort*)realloc( _indices, sizeof(_indices[0]) * _capacity * 6 );
        if (tmpIndices != NULL && _capacity > uOldCapactiy)
        {
            memset( tmpIndices+uOldCapactiy, 0, (_capacity-uOldCapactiy) * 6 * sizeof(_indices[0]) );
        }
    }

    if( ! ( tmpQuads && tmpIndices) ) {
        CCLOG("cocos2d: TextureAtlas: not enough memory");
        CC_SAFE_FREE(tmpQuads);
        CC_SAFE_FREE(tmpIndices);
        CC_SAFE_FREE(_quads);
        CC_SAFE_FREE(_indices);
        _capacity = _totalQuads = 0;
        return false;
    }

    _quads = tmpQuads;
    _indices = tmpIndices;


    setupIndices();
    mapBuffers();

    _dirty = true;

    return true;
}

void TextureAtlas::increaseTotalQuadsWith(unsigned int amount)
{
    _totalQuads += amount;
}

void TextureAtlas::moveQuadsFromIndex(unsigned int oldIndex, unsigned int amount, unsigned int newIndex)
{
    CCAssert(newIndex + amount <= _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
    CCAssert(oldIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");

    if( oldIndex == newIndex )
    {
        return;
    }
    //create buffer
    size_t quadSize = sizeof(ccV3F_C4B_T2F_Quad);
    ccV3F_C4B_T2F_Quad* tempQuads = (ccV3F_C4B_T2F_Quad*)malloc( quadSize * amount);
    memcpy( tempQuads, &_quads[oldIndex], quadSize * amount );

    if (newIndex < oldIndex)
    {
        // move quads from newIndex to newIndex + amount to make room for buffer
        memmove( &_quads[newIndex], &_quads[newIndex+amount], (oldIndex-newIndex)*quadSize);
    }
    else
    {
        // move quads above back
        memmove( &_quads[oldIndex], &_quads[oldIndex+amount], (newIndex-oldIndex)*quadSize);
    }
    memcpy( &_quads[newIndex], tempQuads, amount*quadSize);

    free(tempQuads);

    _dirty = true;
}

void TextureAtlas::moveQuadsFromIndex(unsigned int index, unsigned int newIndex)
{
    CCAssert(newIndex + (_totalQuads - index) <= _capacity, "moveQuadsFromIndex move is out of bounds");

    memmove(_quads + newIndex,_quads + index, (_totalQuads - index) * sizeof(_quads[0]));
}

void TextureAtlas::fillWithEmptyQuadsFromIndex(unsigned int index, unsigned int amount)
{
    ccV3F_C4B_T2F_Quad quad;
    memset(&quad, 0, sizeof(quad));

    unsigned int to = index + amount;
    for (unsigned int i = index ; i < to ; i++)
    {
        _quads[i] = quad;
    }
}

// TextureAtlas - Drawing

void TextureAtlas::drawQuads()
{
    this->drawNumberOfQuads(_totalQuads, 0);
}

void TextureAtlas::drawNumberOfQuads(unsigned int n)
{
    this->drawNumberOfQuads(n, 0);
}

void TextureAtlas::drawNumberOfQuads(unsigned int n, unsigned int start)
{    
    if (0 == n) 
    {
        return;
    }
    ccGLBindTexture2D(_texture->getName());

#if CC_TEXTURE_ATLAS_USE_VAO

    //
    // Using VBO and VAO
    //

    // XXX: update is done in draw... perhaps it should be done in a timer
    if (_dirty) 
    {
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
        // option 1: subdata
        //glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * n , &_quads[start] );
		
		// option 2: data
        //		glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * (n-start), &quads_[start], GL_DYNAMIC_DRAW);
		
		// option 3: orphaning + glMapBuffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * (n-start), NULL, GL_DYNAMIC_DRAW);
		void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		memcpy(buf, _quads, sizeof(_quads[0])* (n-start));
		glUnmapBuffer(GL_ARRAY_BUFFER);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

        _dirty = false;
    }

    ccGLBindVAO(_VAOname);

#if CC_REBIND_INDICES_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
#endif

#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    glDrawElements(GL_TRIANGLE_STRIP, (GLsizei) n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])) );
#else
    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])) );
#endif // CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP

#if CC_REBIND_INDICES_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif

//    glBindVertexArray(0);

#else // ! CC_TEXTURE_ATLAS_USE_VAO

    //
    // Using VBO without VAO
    //

#define kQuadSize sizeof(_quads[0].bl)
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

    // XXX: update is done in draw... perhaps it should be done in a timer
    if (_dirty) 
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * n , &_quads[start] );
        _dirty = false;
    }

    ccGLEnableVertexAttribs(kVertexAttribFlag_PosColorTex);

    // vertices
    glVertexAttribPointer(kVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(ccV3F_C4B_T2F, vertices));

    // colors
    glVertexAttribPointer(kVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(ccV3F_C4B_T2F, colors));

    // tex coords
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(ccV3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);

#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])));
#else
    glDrawElements(GL_TRIANGLES, (GLsizei)n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])));
#endif // CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#endif // CC_TEXTURE_ATLAS_USE_VAO

    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();
}


NS_CC_END

