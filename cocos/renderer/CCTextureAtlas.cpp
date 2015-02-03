/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#include "renderer/CCTextureAtlas.h"
#include "renderer/CCVertexIndexData.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCTexture2D.h"
#include "base/allocator/CCAllocatorMacros.h"

//#include <stdlib.h>
//
#include "base/ccMacros.h"
//#include "base/CCEventType.h"
#include "base/CCDirector.h"
//#include "base/CCConfiguration.h"
//#include "base/CCEventDispatcher.h"
//#include "base/CCEventListenerCustom.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
//#include "platform/CCGL.h"
#include "deprecated/CCString.h"

//According to some tests GL_TRIANGLE_STRIP is slower, MUCH slower. Probably I'm doing something very wrong

// implementation TextureAtlas

NS_CC_BEGIN

TextureAtlas::TextureAtlas()
    : _texture(nullptr)
    , _vdAtlas(nullptr)
    , _vbAtlas(nullptr)
    , _ibAtlas(nullptr)
//    :_indices(nullptr)
//    ,_dirty(false)
//    ,_texture(nullptr)
//    ,_quads(nullptr)
//#if CC_ENABLE_CACHE_TEXTURE_DATA
//    ,_rendererRecreatedListener(nullptr)
//#endif
{}

TextureAtlas::~TextureAtlas()
{
    CCLOGINFO("deallocing TextureAtlas: %p", this);

    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_vdAtlas);
    CC_SAFE_RELEASE(_vbAtlas);
    CC_SAFE_RELEASE(_ibAtlas);
    
//    CC_SAFE_FREE(_quads);
//    CC_SAFE_FREE(_indices);

//    glDeleteBuffers(2, _buffersVBO);

//    if (Configuration::getInstance()->supportsShareableVAO())
//    {
//        glDeleteVertexArrays(1, &_VAOname);
//        GL::bindVAO(0);
//    }
    
//#if CC_ENABLE_CACHE_TEXTURE_DATA
//    Director::getInstance()->getEventDispatcher()->removeEventListener(_rendererRecreatedListener);
//#endif
}

ssize_t TextureAtlas::getTotalQuads() const
{
    //return _totalQuads;
    return _vdAtlas->getCount() / 4;
}

ssize_t TextureAtlas::getCapacity() const
{
    //return _capacity;
    return _vdAtlas->getCapacity() / 4;
}

Texture2D* TextureAtlas::getTexture() const
{
    return _texture;
}

void TextureAtlas::setTexture(Texture2D* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_texture);
    _texture = var;
}

V3F_C4B_T2F_Quad* TextureAtlas::getQuads()
{
    //return _quads;
    //if someone accesses the quads directly, presume that changes will be made
    // jag. ugh really? surely the burden should be on the changer of verts?
    _vdAtlas->setDirty(true);
    return _vbAtlas->getElementsT<V3F_C4B_T2F_Quad>();
}

void TextureAtlas::setQuads(V3F_C4B_T2F_Quad* quads)
{
    _vbAtlas->updateElementsT<V3F_C4B_T2F_Quad>(quads, _vbAtlas->getElementCount() / 4, 0);
}

// TextureAtlas - alloc & init

TextureAtlas * TextureAtlas::create(const std::string& file, ssize_t capacity)
{
    TextureAtlas * textureAtlas = new (std::nothrow) TextureAtlas();
    if(textureAtlas && textureAtlas->initWithFile(file, capacity))
    {
        textureAtlas->autorelease();
        return textureAtlas;
    }
    CC_SAFE_DELETE(textureAtlas);
    return nullptr;
}

TextureAtlas * TextureAtlas::createWithTexture(Texture2D *texture, ssize_t capacity)
{
    TextureAtlas * textureAtlas = new (std::nothrow) TextureAtlas();
    if (textureAtlas && textureAtlas->initWithTexture(texture, capacity))
    {
        textureAtlas->autorelease();
        return textureAtlas;
    }
    CC_SAFE_DELETE(textureAtlas);
    return nullptr;
}

bool TextureAtlas::initWithFile(const std::string& file, ssize_t capacity)
{
    // retained in property
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);

    if (texture)
    {   
        return initWithTexture(texture, capacity);
    }
    else
    {
        CCLOG("cocos2d: Could not open file: %s", file.c_str());
        return false;
    }
}

bool TextureAtlas::initWithTexture(Texture2D *texture, ssize_t capacity)
{
    CCASSERT(capacity >= 0, "Capacity must be >= 0");
    
    _vdAtlas = VertexData::create(VertexData::Primitive::Triangles);
    _vbAtlas = VertexBuffer::create(sizeof(V3F_C4B_T2F), 4 * capacity, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _ibAtlas = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6 * capacity, IndexBuffer::ArrayType::All);
    _vdAtlas->setIndexBuffer(_ibAtlas);

    _vdAtlas->addStream(_vbAtlas, VertexAttribute(offsetof(V3F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 3));
    _vdAtlas->addStream(_vbAtlas, VertexAttribute(offsetof(V3F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true));
    _vdAtlas->addStream(_vbAtlas, VertexAttribute(offsetof(V3F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, DataType::Float, 2));
    
    CC_SAFE_RETAIN(_vdAtlas);
    CC_SAFE_RETAIN(_vbAtlas);
    CC_SAFE_RETAIN(_ibAtlas);

    
////    CCASSERT(texture != nullptr, "texture should not be null");
//    _capacity = capacity;
//    _totalQuads = 0;

    // retained in property
    this->_texture = texture;
    CC_SAFE_RETAIN(_texture);

    // Re-initialization is not allowed
//    CCASSERT(_quads == nullptr && _indices == nullptr, "");
//
//    _quads = (V3F_C4B_T2F_Quad*)malloc( _capacity * sizeof(V3F_C4B_T2F_Quad) );
//    _indices = (GLushort *)malloc( _capacity * 6 * sizeof(GLushort) );
//    
//    if( ! ( _quads && _indices) && _capacity > 0) 
//    {
//        //CCLOG("cocos2d: TextureAtlas: not enough memory");
//        CC_SAFE_FREE(_quads);
//        CC_SAFE_FREE(_indices);
//
//        // release texture, should set it to null, because the destruction will
//        // release it too. see cocos2d-x issue #484
//        CC_SAFE_RELEASE_NULL(_texture);
//        return false;
//    }

//    memset( _quads, 0, _capacity * sizeof(V3F_C4B_T2F_Quad) );
//    memset( _indices, 0, _capacity * 6 * sizeof(GLushort) );
    
//#if CC_ENABLE_CACHE_TEXTURE_DATA
//    /** listen the event that renderer was recreated on Android/WP8 */
//    _rendererRecreatedListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, CC_CALLBACK_1(TextureAtlas::listenRendererRecreated, this));
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_rendererRecreatedListener, -1);
//#endif
    
    setupIndices(getCapacity());

//    if (Configuration::getInstance()->supportsShareableVAO())
//    {
//        setupVBOandVAO();
//    }
//    else
//    {
//        setupVBO();
//    }
//
//    _dirty = true;

    return true;
}

//void TextureAtlas::listenRendererRecreated(EventCustom* event)
//{  
//    if (Configuration::getInstance()->supportsShareableVAO())
//    {
//        setupVBOandVAO();
//    }
//    else
//    {
//        setupVBO();
//    }
//    
//    // set _dirty to true to force it rebinding buffer
//    _dirty = true;
//}

std::string TextureAtlas::getDescription() const
{
    return StringUtils::format("<TextureAtlas | totalQuads = %d>", static_cast<int>(_vbAtlas->getElementCount()));
}

// count and begin are both quad indices
void TextureAtlas::setupIndices(size_t count, size_t begin)
{
    if (0 == count)
        return;

    auto indices = 6 * begin + _ibAtlas->getElementsT<uint16_t>();
    auto end = begin + count;
    
    // count is in quads, begin is in indices, so quads * 6
    for (auto i = begin; i < end; ++i)
    {
        *indices++ = i*4+0;
        *indices++ = i*4+1;
        *indices++ = i*4+2;
        *indices++ = i*4+3;
        *indices++ = i*4+2;
        *indices++ = i*4+1;
    }
    
    // manually set the count since we are modifying
    // the element array outside of the buffer.
    _ibAtlas->setElementCount(6 * end);
    _ibAtlas->setDirty(true);
}

//TextureAtlas - VAO / VBO specific

//void TextureAtlas::setupVBOandVAO()
//{
//    glGenVertexArrays(1, &_VAOname);
//    GL::bindVAO(_VAOname);
//
//#define kQuadSize sizeof(_quads[0].bl)
//
//    glGenBuffers(2, &_buffersVBO[0]);
//
//    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _capacity, _quads, GL_DYNAMIC_DRAW);
//
//    // vertices
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, vertices));
//
//    // colors
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, colors));
//
//    // tex coords
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 6, _indices, GL_STATIC_DRAW);
//
//    // Must unbind the VAO before changing the element buffer.
//    GL::bindVAO(0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    CHECK_GL_ERROR_DEBUG();
//}

//void TextureAtlas::setupVBO()
//{
//    glGenBuffers(2, &_buffersVBO[0]);
//
//    mapBuffers();
//}
//
//void TextureAtlas::mapBuffers()
//{
//    // Avoid changing the element buffer for whatever VAO might be bound.
//	GL::bindVAO(0);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _capacity, _quads, GL_DYNAMIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _capacity * 6, _indices, GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//    CHECK_GL_ERROR_DEBUG();
//}

// TextureAtlas - Update, Insert, Move & Remove

void TextureAtlas::updateQuad(V3F_C4B_T2F_Quad *quad, ssize_t index)
{
    _vbAtlas->updateElementsT<V3F_C4B_T2F_Quad>(quad, 1, index);
}

void TextureAtlas::insertQuad(V3F_C4B_T2F_Quad *quad, ssize_t index)
{
    _vbAtlas->insertElementsT<V3F_C4B_T2F_Quad>(quad, 1, index);
}

void TextureAtlas::insertQuads(V3F_C4B_T2F_Quad* quads, ssize_t index, ssize_t amount)
{
    _vbAtlas->insertElementsT<V3F_C4B_T2F_Quad>(quads, amount, index);
}

//void TextureAtlas::insertQuadFromIndex(ssize_t oldIndex, ssize_t newIndex)
//{
//    CCASSERT( newIndex >= 0 && newIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
//    CCASSERT( oldIndex >= 0 && oldIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
//
//    if( oldIndex == newIndex )
//    {
//        return;
//    }
//    // because it is ambiguous in iphone, so we implement abs ourselves
//    // unsigned int howMany = abs( oldIndex - newIndex);
//    auto howMany = (oldIndex - newIndex) > 0 ? (oldIndex - newIndex) :  (newIndex - oldIndex);
//    auto dst = oldIndex;
//    auto src = oldIndex + 1;
//    if( oldIndex > newIndex)
//    {
//        dst = newIndex+1;
//        src = newIndex;
//    }
//
//    // texture coordinates
//    V3F_C4B_T2F_Quad quadsBackup = _quads[oldIndex];
//    memmove( &_quads[dst],&_quads[src], sizeof(_quads[0]) * howMany );
//    _quads[newIndex] = quadsBackup;
//
//
//    _dirty = true;
//}

void TextureAtlas::removeQuadAtIndex(ssize_t index)
{
    _vbAtlas->removeElementsT<V3F_C4B_T2F_Quad>(1, index);
}

void TextureAtlas::removeQuadsAtIndex(ssize_t index, ssize_t amount)
{
    _vbAtlas->removeElementsT<V3F_C4B_T2F_Quad>(amount, index);
}

void TextureAtlas::removeAllQuads()
{
    //_totalQuads = 0;
    _vdAtlas->clear();
}

bool TextureAtlas::resizeCapacity(ssize_t newCapacity)
{
    auto amount = newCapacity - getCapacity();
    if (amount > 0)
    {
        auto begin = _ibAtlas->getCapacity() / 6;     // determine first quad to update
        _ibAtlas->addCapacityT<uint16_t>(6 * amount); // add capacity 6 indices per quad
        setupIndices(amount, begin);                  // update new indices for quads
        
        _vbAtlas->addCapacityT<V3F_C4B_T2F_Quad>(amount);
    }
    return true;
}

void TextureAtlas::increaseTotalQuadsWith(ssize_t amount)
{
    CCASSERT(amount >= 0, "increaseTotalQuadsWith amount >= 0");
    auto count = _vbAtlas->getElementCount();
    _vbAtlas->setElementCount(count + amount);
}

void TextureAtlas::moveQuadsFromIndex(ssize_t oldIndex, ssize_t amount, ssize_t newIndex)
{
//    CCASSERT(oldIndex>=0 && amount>=0 && newIndex>=0, "values must be >= 0");
//    CCASSERT(newIndex + amount <= _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
//    CCASSERT(oldIndex < _totalQuads, "insertQuadFromIndex:atIndex: Invalid index");
//
//    if( oldIndex == newIndex )
//    {
//        return;
//    }
//    //create buffer
//    size_t quadSize = sizeof(V3F_C4B_T2F_Quad);
//    V3F_C4B_T2F_Quad* tempQuads = (V3F_C4B_T2F_Quad*)malloc( quadSize * amount);
//    memcpy( tempQuads, &_quads[oldIndex], quadSize * amount );
//
//    if (newIndex < oldIndex)
//    {
//        // move quads from newIndex to newIndex + amount to make room for buffer
//        memmove( &_quads[newIndex], &_quads[newIndex+amount], (oldIndex-newIndex)*quadSize);
//    }
//    else
//    {
//        // move quads above back
//        memmove( &_quads[oldIndex], &_quads[oldIndex+amount], (newIndex-oldIndex)*quadSize);
//    }
//    memcpy( &_quads[newIndex], tempQuads, amount*quadSize);
//
//    free(tempQuads);
//
//    _dirty = true;
}

void TextureAtlas::moveQuadsFromIndex(ssize_t index, ssize_t newIndex)
{
//    CCASSERT(index>=0 && newIndex>=0, "values must be >= 0");
//    CCASSERT(newIndex + (_totalQuads - index) <= _capacity, "moveQuadsFromIndex move is out of bounds");
//
//    memmove(_quads + newIndex,_quads + index, (_totalQuads - index) * sizeof(_quads[0]));
}

void TextureAtlas::fillWithEmptyQuadsFromIndex(ssize_t index, ssize_t amount)
{
    _vbAtlas->updateElementsT<V3F_C4B_T2F_Quad>(nullptr, amount, index);
}

// TextureAtlas - Drawing

void TextureAtlas::drawQuads()
{
    GL::bindTexture2D(_texture->getName()); // ugh, have to have this here for now until I get rid of Label custom commands
    _vdAtlas->draw();
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _vbAtlas->getElementCount());
}

//
//void TextureAtlas::drawNumberOfQuads(ssize_t numberOfQuads)
//{
//    CCASSERT(numberOfQuads>=0, "numberOfQuads must be >= 0");
//    this->drawNumberOfQuads(numberOfQuads, 0);
//}
//
//void TextureAtlas::drawNumberOfQuads(ssize_t numberOfQuads, ssize_t start)
//{
//    CCASSERT(numberOfQuads>=0 && start>=0, "numberOfQuads and start must be >= 0");
//
//    if(!numberOfQuads)
//        return;
//    
//    GL::bindTexture2D(_texture->getName());
//
//    if (Configuration::getInstance()->supportsShareableVAO())
//    {
//        //
//        // Using VBO and VAO
//        //
//
//        // FIXME:: update is done in draw... perhaps it should be done in a timer
//        if (_dirty) 
//        {
//            glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
//            // option 1: subdata
////            glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * n , &_quads[start] );
//
//            // option 2: data
////            glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * (n-start), &quads_[start], GL_DYNAMIC_DRAW);
//
//            // option 3: orphaning + glMapBuffer
//            glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _capacity, nullptr, GL_DYNAMIC_DRAW);
//            void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//            memcpy(buf, _quads, sizeof(_quads[0])* _totalQuads);
//            glUnmapBuffer(GL_ARRAY_BUFFER);
//            
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//            _dirty = false;
//        }
//
//        GL::bindVAO(_VAOname);
//
//#if CC_REBIND_INDICES_BUFFER
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
//#endif
//
//        glDrawElements(GL_TRIANGLES, (GLsizei) numberOfQuads*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])) );
//        
//        GL::bindVAO(0);
//        
//#if CC_REBIND_INDICES_BUFFER
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//#endif
//
////    glBindVertexArray(0);
//    }
//    else
//    {
//        //
//        // Using VBO without VAO
//        //
//
//#define kQuadSize sizeof(_quads[0].bl)
//        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
//
//        // FIXME:: update is done in draw... perhaps it should be done in a timer
//        if (_dirty) 
//        {
//            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_quads[0]) * _totalQuads , &_quads[0] );
//            _dirty = false;
//        }
//
//        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
//
//        // vertices
//        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));
//
//        // colors
//        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, colors));
//
//        // tex coords
//        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, texCoords));
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
//
//        glDrawElements(GL_TRIANGLES, (GLsizei)numberOfQuads*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(_indices[0])));
//
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    }
//
//    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,numberOfQuads*6);
//    
//    CHECK_GL_ERROR_DEBUG();
//}
//

bool TextureAtlas::isDirty()
{
    return _vdAtlas->isDirty();
}

void TextureAtlas::setDirty(bool dirty)
{
    _vdAtlas->setDirty(dirty);
}

NS_CC_END

