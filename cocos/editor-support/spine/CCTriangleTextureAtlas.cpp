/******************************************************************************
 * Spine Runtimes Software License
 * Version 2
 *
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software, you may not (a) modify, translate, adapt or
 * otherwise create derivative works, improvements of the Software or develop
 * new applications using the Software or (b) remove, delete, alter or obscure
 * any trademarks or any copyright, trademark, patent or other intellectual
 * property or proprietary rights notices on or in the Software, including
 * any copy thereof. Redistributions in binary or source form must include
 * this license and terms. THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

//
//  CCTriangleTextureAtlas.m
//  spine-cocos2d-iphone-ios
//
//  Created by Wojciech Trzasko CodingFingers on 24.02.2014.
//

#include "CCTriangleTextureAtlas.h"

#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "CCDirector.h"
#include "CCConfiguration.h"
#include "CCDirector.h"
#include "renderer/CCRenderer.h"
#include "CCEventType.h"

#include "CCEventDispatcher.h"
#include "CCEventListenerCustom.h"


#include <stdlib.h>

#define kTriangleSize sizeof(V3F_C4B_T2F_Triangle)
#define kVerticleSize sizeof(V3F_C4B_T2F)

TriangleTextureAtlas * TriangleTextureAtlas::createWithTexture(Texture2D * texture, ssize_t capacity)
{
    TriangleTextureAtlas *atlas = new TriangleTextureAtlas();
    if (atlas && atlas->initWithTexture(texture, capacity))
    {
        atlas->autorelease();
        return atlas;
    }
    CC_SAFE_DELETE(atlas);
    return nullptr;
}

TriangleTextureAtlas::TriangleTextureAtlas()
: _indices(nullptr)
, _VAOname(0)
, _capacity(0)
, _texture(nullptr)
, _vertices(nullptr)
, _totalVertices(0)
, _totalTriangles(0)
, _currentTriangles(0)
, _dirtyVertices(false)
, _dirtyIndices(false)
#if CC_ENABLE_CACHE_TEXTURE_DATA
,_backToForegroundlistener(nullptr)
#endif
{
}

TriangleTextureAtlas::~TriangleTextureAtlas()
{
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_indices);
    
    glDeleteBuffers(2, _buffersVBO);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_VAOname);
        GL::bindVAO(0);
    }
    CC_SAFE_RELEASE(_texture);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundlistener);
#endif
    
}

bool TriangleTextureAtlas::initWithTexture(Texture2D * texture, ssize_t capacity)
{
    CCASSERT(capacity>=0, "Capacity must be >= 0");
    
    _capacity = capacity;
    _totalVertices = 0;
    _totalTriangles = 0;
    _currentTriangles = 0;
    
    // retained in property
    this->_texture = texture;
    CC_SAFE_RETAIN(_texture);
    
    // Re-initialization is not allowed
    CCASSERT(_vertices == nullptr && _indices == nullptr, "");
    
    _vertices = (V3F_C4B_T2F*)malloc( sizeof(_vertices[0]) * _capacity * 3 );
    _indices = (GLushort *)malloc( sizeof(_indices[0]) * _capacity * 3 );
    
    if( ! ( _vertices && _indices) && _capacity > 0)
    {
        //CCLOG("cocos2d: TextureAtlas: not enough memory");
        CC_SAFE_FREE(_vertices);
        CC_SAFE_FREE(_indices);
        
        // release texture, should set it to null, because the destruction will
        // release it too. see cocos2d-x issue #484
        CC_SAFE_RELEASE_NULL(_texture);
        return false;
    }
    
    memset( _vertices, 0,  sizeof(_vertices[0]) * _capacity * 3 );
    memset( _indices, 0,  sizeof(_indices[0]) * _capacity * 3 );
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // listen the event when app go to background
    _backToForegroundlistener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(TriangleTextureAtlas::listenBackToForeground, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundlistener, -1);
#endif
    
    this->setupIndices();
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        setupVBOandVAO();
    }
    else
    {
        setupVBO();
    }
    
    _dirtyVertices = true;
    _dirtyIndices = true;
    
    return true;
}

void TriangleTextureAtlas::listenBackToForeground(EventCustom* event)
{
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        setupVBOandVAO();
    }
    else
    {
        setupVBO();
    }
    
    // set dirtys to true to force it rebinding buffer
    _dirtyVertices = true;
    _dirtyIndices = true;
}


void TriangleTextureAtlas::setupIndices()
{
    if (_capacity == 0)
        return;
    
    for (int i = 0; i < _capacity; i++)
    {
        _indices[3*i + 0] = 3*i + 0;
        _indices[3*i + 1] = 3*i + 1;
        _indices[3*i + 2] = 3*i + 2;
    }
}

void TriangleTextureAtlas::mapBuffers()
{
    // Avoid changing the element buffer for whatever VAO might be bound.
    GL::bindVAO(0);
    
	glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, kVerticleSize * _capacity * 3, _vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 3, _indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
	CHECK_GL_ERROR_DEBUG();
}

void TriangleTextureAtlas::setupVBOandVAO()
{
    glGenVertexArrays(1, &_VAOname);
    GL::bindVAO(_VAOname);
    
    glGenBuffers(2, &_buffersVBO[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, kVerticleSize * _capacity * 3, _vertices, GL_DYNAMIC_DRAW);
    
    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kVerticleSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));
    
    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kVerticleSize, (GLvoid*) offsetof( V3F_C4B_T2F, colors));
    
    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kVerticleSize, (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 3, _indices, GL_STATIC_DRAW);
    
    // Must unbind the VAO before changing the element buffer.
    GL::bindVAO(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CHECK_GL_ERROR_DEBUG();
}

void TriangleTextureAtlas::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);
    
    mapBuffers();
}

void TriangleTextureAtlas::removeAllVertices()
{
    _totalVertices = 0;
}

void TriangleTextureAtlas::removeAllTriangles()
{
    _totalTriangles = 0;
}

void TriangleTextureAtlas::removeTrianglesFrom(ssize_t triangleNr)
{
    _totalTriangles = triangleNr;
}

bool TriangleTextureAtlas::resizeCapacity(ssize_t n)
{
    if (n == _capacity) return true;
    
    _totalTriangles = MIN(_totalTriangles, n);
    _totalVertices = MIN(_totalVertices, n * 3);
    _capacity = n;
    
    V3F_C4B_T2F * tmpVertices = (V3F_C4B_T2F*)realloc( _vertices, sizeof(_vertices[0]) * _capacity * 3);
    GLushort * tmpIndices = (GLushort*)realloc( _indices, sizeof(_indices[0]) * _capacity * 3);
    
    if ( ! ( tmpVertices && tmpIndices) )
    {
        CCLOG("cocos2d: TriangleTextureAtlas: not enough memory");
        CC_SAFE_FREE(tmpVertices);
        CC_SAFE_FREE(tmpIndices);
        CC_SAFE_FREE(_vertices);
        CC_SAFE_FREE(_indices);
        _capacity = _totalVertices = _totalTriangles = 0;
        return false;
    }
    
    _vertices = tmpVertices;
	_indices = tmpIndices;
    
	// Update Indices
    setupIndices();
    mapBuffers();
    
	_dirtyVertices = true;
    _dirtyIndices = true;
    
	return true;
}

void TriangleTextureAtlas::updateTrianglesIndices(int *indices, size_t length, size_t offset)
{
    CCASSERT(_totalTriangles + (length / 3) <= _capacity, "updateTrianglesIndices: Not enough space in buffer.");
    
    int i, j;
    int indicesStart = _totalTriangles * 3;
    for (i = indicesStart, j = 0; i < indicesStart + length; i += 3, j += 3)
    {
        _indices[i] = offset + indices[j];
        _indices[i + 1] = offset + indices[j + 1];
        _indices[i + 2] = offset + indices[j + 2];
        
        _totalTriangles = MAX(i / 3 + 1, _totalTriangles);
    }
    
	_dirtyIndices = true;
}

void TriangleTextureAtlas::updateVertex(V3F_C4B_T2F *vertex, ssize_t n)
{
    CCASSERT(n < _capacity * 3, "updateVertexAtIndex: Invalid index");
    
	_totalVertices =  MAX( n + 1, _totalVertices);
	_vertices[n] = *vertex;
	_dirtyVertices = true;
}

void TriangleTextureAtlas::updateVertices(V3F_C4B_T2F *vertices, ssize_t n, ssize_t length)
{
    CCASSERT(n + length < _capacity * 3, "TriangleTextureAtlas::updateVertices : given value exceeds array length");
    for (int i = 0; i < length; ++i)
    {
        _totalVertices =  MAX( n + i + 1, _totalVertices);
        _vertices[n + i] = vertices[i];
    }
    _dirtyVertices = true;
}

void TriangleTextureAtlas::transferBuffers()
{
    if(_dirtyVertices || _dirtyIndices)
    {
        GL::bindVAO(0);
        
        if (_dirtyVertices)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B_T2F) * _totalVertices, _vertices, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            _dirtyVertices = false;
        }
        
        if(_dirtyIndices)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _totalTriangles * 3, _indices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            _dirtyIndices = false;
        }
    }
}

void TriangleTextureAtlas::drawTriangles()
{
    drawTriangles(0, _totalTriangles);
}

void TriangleTextureAtlas::drawTriangles(ssize_t n)
{
    drawTriangles(0, n);
}

void TriangleTextureAtlas::drawTriangles(ssize_t start, ssize_t n)
{
    transferBuffers();
    
    GL::bindTexture2D(_texture->getName());
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        //
        // Using VBO and VAO
        //
        
        GL::bindVAO(_VAOname);
        
#if CC_REBIND_INDICES_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
#endif
        glDrawElements(GL_TRIANGLES,
                       (GLsizei)n * 3,
                       GL_UNSIGNED_SHORT,
                       (GLvoid*)(start * 3 * sizeof(_indices[0])));
        
#if CC_REBIND_INDICES_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
        
        //        GL::bindVAO(0);
    }
    else
    {
        //
        // Using VBO without VAO
        //
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
        
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
        
        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kVerticleSize, (GLvoid*) offsetof( V3F_C4B_T2F, vertices));
        
        // colors
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kVerticleSize, (GLvoid*) offsetof( V3F_C4B_T2F, colors));
        
        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kVerticleSize, (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
        
        glDrawElements(GL_TRIANGLES,
                       (GLsizei)n * 3,
                       GL_UNSIGNED_SHORT,
                       (GLvoid*)(start * 3 * sizeof(_indices[0])));
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_totalVertices);
	CHECK_GL_ERROR_DEBUG();
}

ssize_t TriangleTextureAtlas::getCapacity() const
{
    return _capacity;
}
ssize_t TriangleTextureAtlas::getTotalTriangles() const
{
    return _totalTriangles;
}

ssize_t TriangleTextureAtlas::getTotalVertices() const
{
    return _totalVertices;
}

V3F_C4B_T2F * TriangleTextureAtlas::getVertices()
{
    // Assuming that every get make changes
    _dirtyVertices = true;
    return _vertices;
}

Texture2D * TriangleTextureAtlas::getTexture()
{
    return _texture;
}

ssize_t TriangleTextureAtlas::getCurrentTriangles() const
{
    return _currentTriangles;
}

void TriangleTextureAtlas::setCurrentTriangles(ssize_t n)
{
    _currentTriangles = n;
}
