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
    GL::bindVAO(0);
#endif
    CC_SAFE_RELEASE(_texture);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    NotificationCenter::getInstance()->removeObserver(this, EVNET_COME_TO_FOREGROUND);
#endif
}

int TextureAtlas::getTotalQuads() const
{
    return _totalQuads;
}

int TextureAtlas::getCapacity() const
{
    return _capacity;
}

Texture2D* TextureAtlas::getTexture() const
{
    return _texture;
}

void TextureAtlas::setTexture(Texture2D * var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_texture);
    _texture = var;
}

V3F_C4B_T2F_Quad* TextureAtlas::getQuads()
{
    //if someone accesses the quads directly, presume that changes will be made
    _dirty = true;
    return _quads;
}

void TextureAtlas::setQuads(V3F_C4B_T2F_Quad* quads)
{
    _quads = quads;
}

// TextureAtlas - alloc & init

TextureAtlas * TextureAtlas::create(const char* file, int capacity)
{
    TextureAtlas * textureAtlas = new TextureAtlas();
    if(textureAtlas && textureAtlas->initWithFile(file, capacity))
    {
        textureAtlas->autorelease();
        return textureAtlas;
    }
    CC_SAFE_DELETE(textureAtlas);
    return NULL;
}

TextureAtlas * TextureAtlas::createWithTexture(Texture2D *texture, int capacity)
{
    TextureAtlas * textureAtlas = new TextureAtlas();
    if (textureAtlas && textureAtlas->initWithTexture(texture, capacity))
    {
        textureAtlas->autorelease();
        return textureAtlas;
    }
    CC_SAFE_DELETE(textureAtlas);
    return NULL;
}

bool TextureAtlas::initWithFile(const char * file, int capacity)
{
    // retained in property
    Texture2D *texture = TextureCache::getInstance()->addImage(file);

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

bool TextureAtlas::initWithTexture(Texture2D *texture, int capacity)
{
    CCASSERT(capacity>=0, "Capacity must be >= 0");
    
//    CCASSERT(texture != NULL, "texture should not be null");
    _capacity = capacity;
    _totalQuads = 0;

    // retained in property
    this->_texture = texture;
    CC_SAFE_RETAIN(_texture);

    // Re-initialization is not allowed
    CCASSERT(_quads == NULL && _indices == NULL, "");

    _quads = (V3F_C4B_T2F_Quad*)malloc( _capacity * sizeof(V3F_C4B_T2F_Quad) );
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

    memset( _quads, 0, _capacity * sizeof(V3F_C4B_T2F_Quad) );
    memset( _indices, 0, _capacity * 6 * sizeof(GLushort) );
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // listen the event when app go to background
    NotificationCenter::getInstance()->addObserver(this,
                                                           callfuncO_selector(TextureAtlas::listenBackToForeground),
                                                           EVNET_COME_TO_FOREGROUND,
                                                           NULL);
#endif
    
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

const char* TextureAtlas::description() const
{
    return String::createWithFormat("<TextureAtlas | totalQuads = %u>", _totalQuads)->getCString();
}


void TextureAtlas::setupIndices()
{
    if (_capacity == 0)
        return;

    for( int i=0; i < _capacity; i++)
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
    GL::bindVAO(_VAOname);

#define kQuadSize sizeof(_quads[0].bl)

    glGenBuffers(2, &_buffersVBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _capacity, _quads, GL_DYNAMIC_DRAW);

    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, vertices));

    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, colors));

    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 6, _indices, GL_STATIC_DRAW);

    // Must unbind the VAO before changing the element buffer.
    GL::bindVAO(0);
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
	GL::bindVAO(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _capacity, _quads, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 6, _indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

// TextureAtlas - Update, Insert, Move & Remove

void TextureAtlas::updateQuad(V3F_C4B_T2F_Quad *quad, int index)
{
    CCASSERT( index >= 0 && index < _capacity, "updateQuadWithTexture: Invalid index");

    _totalQuads = MAX( index+1, _totalQuads);

    _quads[index] = *quad;    


    _dirty = true;

}

void TextureAtlas::insertQuad(V3F_C4B_T2F_Quad *quad, int index)
{
    CCASSERT( index>=0 && index<_capacity, "insertQuadWithTexture: Invalid index");

    _totalQuads++;
    CCASSERT( _totalQuads <= _capacity, "invalid totalQuads");

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

void TextureAtlas::insertQuads(V3F_C4B_T2F_Quad* quads, int index, int amount)
{
    CCASSERT(index>=0 && amount>=0 && index+amount<=_capacity, "insertQuadWithTexture: Invalid index + amount");

    _totalQuads += amount;

    CCASSERT( _totalQuads <= _capacity, "invalid totalQuads");

    // issue #575. index can be > totalQuads
    int remaining = (_totalQuads-1) - index - amount;

    // last object doesn't need to be moved
    if( remaining > 0)
    {
        // tex coordinates
        memmove( &_quads[index+amount],&_quads[index], sizeof(_quads[0]) * remaining );
    }


    int max = index + amount;
    int j = 0;
    for (int i = index; i < max ; i++)
    {
        _quads[index] = quads[j];
        index++;
        j++;
    }

    _dirty = true;
}

void TextureAtlas::insertQuadFromIndex(int oldIndex, int newIndex)
{
    CCASSERT( newIndex >= 0 && newIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
    CCASSERT( oldIndex >= 0 && oldIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");

    if( oldIndex == newIndex )
    {
        return;
    }
    // because it is ambiguous in iphone, so we implement abs ourselves
    // unsigned int howMany = abs( oldIndex - newIndex);
    int howMany = (oldIndex - newIndex) > 0 ? (oldIndex - newIndex) :  (newIndex - oldIndex);
    int dst = oldIndex;
    int src = oldIndex + 1;
    if( oldIndex > newIndex)
    {
        dst = newIndex+1;
        src = newIndex;
    }

    // texture coordinates
    V3F_C4B_T2F_Quad quadsBackup = _quads[oldIndex];
    memmove( &_quads[dst],&_quads[src], sizeof(_quads[0]) * howMany );
    _quads[newIndex] = quadsBackup;


    _dirty = true;
}

void TextureAtlas::removeQuadAtIndex(int index)
{
    CCASSERT( index>=0 && index<_totalQuads, "removeQuadAtIndex: Invalid index");

    int remaining = (_totalQuads-1) - index;

    // last object doesn't need to be moved
    if( remaining ) 
    {
        // texture coordinates
        memmove( &_quads[index],&_quads[index+1], sizeof(_quads[0]) * remaining );
    }

    _totalQuads--;


    _dirty = true;
}

void TextureAtlas::removeQuadsAtIndex(int index, int amount)
{
    CCASSERT(index>=0 && amount>=0 && index+amount<=_totalQuads, "removeQuadAtIndex: index + amount out of bounds");

    int remaining = (_totalQuads) - (index + amount);

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
bool TextureAtlas::resizeCapacity(int newCapacity)
{
    CCASSERT(newCapacity>=0, "capacity >= 0");
    if( newCapacity == _capacity )
    {
        return true;
    }
    int oldCapactiy = _capacity;
    // update capacity and totolQuads
    _totalQuads = MIN(_totalQuads, newCapacity);
    _capacity = newCapacity;

    V3F_C4B_T2F_Quad* tmpQuads = NULL;
    GLushort* tmpIndices = NULL;
    
    // when calling initWithTexture(fileName, 0) on bada device, calloc(0, 1) will fail and return NULL,
    // so here must judge whether _quads and _indices is NULL.
    if (_quads == NULL)
    {
        tmpQuads = (V3F_C4B_T2F_Quad*)malloc( _capacity * sizeof(_quads[0]) );
        if (tmpQuads != NULL)
        {
            memset(tmpQuads, 0, _capacity * sizeof(_quads[0]) );
        }
    }
    else
    {
        tmpQuads = (V3F_C4B_T2F_Quad*)realloc( _quads, sizeof(_quads[0]) * _capacity );
        if (tmpQuads != NULL && _capacity > oldCapactiy)
        {
            memset(tmpQuads+oldCapactiy, 0, (_capacity - oldCapactiy)*sizeof(_quads[0]) );
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
        if (tmpIndices != NULL && _capacity > oldCapactiy)
        {
            memset( tmpIndices+oldCapactiy, 0, (_capacity-oldCapactiy) * 6 * sizeof(_indices[0]) );
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

void TextureAtlas::increaseTotalQuadsWith(int amount)
{
    CCASSERT(amount>=0, "amount >= 0");
    _totalQuads += amount;
}

void TextureAtlas::moveQuadsFromIndex(int oldIndex, int amount, int newIndex)
{
    CCASSERT(oldIndex>=0 && amount>=0 && newIndex>=0, "values must be >= 0");
    CCASSERT(newIndex + amount <= _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
    CCASSERT(oldIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");

    if( oldIndex == newIndex )
    {
        return;
    }
    //create buffer
    size_t quadSize = sizeof(V3F_C4B_T2F_Quad);
    V3F_C4B_T2F_Quad* tempQuads = (V3F_C4B_T2F_Quad*)malloc( quadSize * amount);
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

void TextureAtlas::moveQuadsFromIndex(int index, int newIndex)
{
    CCASSERT(index>=0 && newIndex>=0, "values must be >= 0");
    CCASSERT(newIndex + (_totalQuads - index) <= _capacity, "moveQuadsFromIndex move is out of bounds");

    memmove(_quads + newIndex,_quads + index, (_totalQuads - index) * sizeof(_quads[0]));
}

void TextureAtlas::fillWithEmptyQuadsFromIndex(int index, int amount)
{
    CCASSERT(index>=0 && amount>=0, "values must be >= 0");
    V3F_C4B_T2F_Quad quad;
    memset(&quad, 0, sizeof(quad));

    int to = index + amount;
    for (int i = index ; i < to ; i++)
    {
        _quads[i] = quad;
    }
}

// TextureAtlas - Drawing

void TextureAtlas::drawQuads()
{
    this->drawNumberOfQuads(_totalQuads, 0);
}

void TextureAtlas::drawNumberOfQuads(int numberOfQuads)
{
    CCASSERT(numberOfQuads>=0, "numberOfQuads must be >= 0");
    this->drawNumberOfQuads(numberOfQuads, 0);
}

void TextureAtlas::drawNumberOfQuads(int numberOfQuads, int start)
{
    CCASSERT(numberOfQuads>=0 && start>=0, "numberOfQuads and start must be >= 0");

    if(!numberOfQuads)
        return;

    GL::bindTexture2D(_texture->getName());

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
		glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * (numberOfQuads-start), NULL, GL_DYNAMIC_DRAW);
		void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		memcpy(buf, _quads, sizeof(_quads[0])* (numberOfQuads-start));
		glUnmapBuffer(GL_ARRAY_BUFFER);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

        _dirty = false;
    }

    GL::bindVAO(_VAOname);

#if CC_REBIND_INDICES_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
#endif

#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    glDrawElements(GL_TRIANGLE_STRIP, (GLsizei) numberOfQuads*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])) );
#else
    glDrawElements(GL_TRIANGLES, (GLsizei) numberOfQuads*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])) );
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
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * numberOfQuads , &_quads[start] );
        _dirty = false;
    }

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

    // vertices
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));

    // colors
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, colors));

    // tex coords
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);

#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)numberOfQuads*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])));
#else
    glDrawElements(GL_TRIANGLES, (GLsizei)numberOfQuads*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])));
#endif // CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#endif // CC_TEXTURE_ATLAS_USE_VAO

    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();
}


NS_CC_END

