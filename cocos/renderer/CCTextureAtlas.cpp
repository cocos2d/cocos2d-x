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
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTexture2D.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "platform/CCGL.h"

//According to some tests GL_TRIANGLE_STRIP is slower, MUCH slower. Probably I'm doing something very wrong

// implementation TextureAtlas

NS_CC_BEGIN

TextureAtlas::TextureAtlas()
    : _texture(nullptr)
    , _vdAtlas(nullptr)
    , _vbAtlas(nullptr)
    , _ibAtlas(nullptr)
    , _quadCount(0)
    , _quadCapacity(0)
{}

TextureAtlas::~TextureAtlas()
{
    CCLOGINFO("deallocing TextureAtlas: %p", this);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_vdAtlas);
    CC_SAFE_RELEASE(_vbAtlas);
    CC_SAFE_RELEASE(_ibAtlas);
}

size_t TextureAtlas::getTotalQuads() const
{
    return _quadCount;
}

size_t TextureAtlas::getCapacity() const
{
    return _quadCapacity;
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
    // return _quads;
    // if someone accesses the quads directly, presume that changes will be made
    // jag. ugh really? surely the burden should be on the changer of verts?
    _vbAtlas->setDirty(true);
    return _vbAtlas->getElementsOfType<V3F_C4B_T2F_Quad>();
}

void TextureAtlas::setQuads(V3F_C4B_T2F_Quad* quads)
{
    _vbAtlas->updateElementsOfType<V3F_C4B_T2F_Quad>(quads, _quadCount, 0);
}

// TextureAtlas - alloc & init

TextureAtlas * TextureAtlas::create(const std::string& file, size_t capacity)
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

TextureAtlas * TextureAtlas::createWithTexture(Texture2D *texture, size_t capacity)
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

bool TextureAtlas::initWithFile(const std::string& file, size_t capacity)
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

bool TextureAtlas::initWithTexture(Texture2D *texture, size_t capacity)
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

    this->_texture = texture;
    CC_SAFE_RETAIN(_texture);
    
    _quadCapacity = capacity;
    setupIndices(_quadCapacity);

    return true;
}

std::string TextureAtlas::getDescription() const
{
    return StringUtils::format("<TextureAtlas | totalQuads = %zu>", getTotalQuads());
}

// count and begin are both quad indices
void TextureAtlas::setupIndices(size_t count, size_t begin)
{
    if (0 == count)
        return;

    auto indices = 6 * begin + _ibAtlas->getElementsOfType<uint16_t>();
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
    
    _ibAtlas->setDirty(true);
}

// TextureAtlas - Update, Insert, Move & Remove

void TextureAtlas::updateQuad(V3F_C4B_T2F_Quad *quad, size_t index)
{
    _quadCount = std::max(index + 1, _quadCount);
    _vbAtlas->updateElementsOfType<V3F_C4B_T2F_Quad>(quad, 1, index);
}

void TextureAtlas::insertQuad(V3F_C4B_T2F_Quad *quad, size_t index)
{
    ++_quadCount;
    _vbAtlas->insertElementsOfType<V3F_C4B_T2F_Quad>(quad, 1, index);
}

void TextureAtlas::insertQuads(V3F_C4B_T2F_Quad* quads, size_t index, size_t amount)
{
    _quadCount += amount;
    _vbAtlas->insertElementsOfType<V3F_C4B_T2F_Quad>(quads, amount, index);
}

void TextureAtlas::insertQuadFromIndex(size_t oldIndex, size_t newIndex)
{
    _vbAtlas->swapElementsOfType<V3F_C4B_T2F_Quad>(oldIndex, newIndex, 1);
}

void TextureAtlas::removeQuadAtIndex(size_t index)
{
    --_quadCount;
    _vbAtlas->removeElementsOfType<V3F_C4B_T2F_Quad>(1, index);
}

void TextureAtlas::removeQuadsAtIndex(size_t index, size_t amount)
{
    _quadCount -= amount;
    _vbAtlas->removeElementsOfType<V3F_C4B_T2F_Quad>(amount, index);
}

void TextureAtlas::removeAllQuads()
{
    _quadCount = 0;
    _vdAtlas->clear();
}

bool TextureAtlas::resizeCapacity(size_t newCapacity)
{
    auto amount = newCapacity - getCapacity();
    if (amount > 0)
    {
        auto begin = _ibAtlas->getCapacity() / 6;     // determine first quad to update
        _ibAtlas->addCapacityOfType<uint16_t>(6 * amount); // add capacity 6 indices per quad
        setupIndices(amount, begin);                  // update new indices for quads
        
        _vbAtlas->addCapacityOfType<V3F_C4B_T2F_Quad>(amount);
        
        _quadCapacity = newCapacity;
    }
    return true;
}

void TextureAtlas::increaseTotalQuadsWith(size_t amount)
{
    CCASSERT(amount >= 0, "increaseTotalQuadsWith amount >= 0");
    auto count = _vbAtlas->getElementCount();
    _vbAtlas->setElementCount(count + 4 * amount);
    _quadCount += amount;
}

void TextureAtlas::moveQuadsFromIndex(size_t oldIndex, size_t amount, size_t newIndex)
{
    _vbAtlas->swapElementsOfType<V3F_C4B_T2F_Quad>(oldIndex, newIndex, amount);
}

void TextureAtlas::moveQuadsFromIndex(size_t index, size_t newIndex)
{
    CCASSERT(newIndex + (_quadCount - index) <= _vbAtlas->getCapacity(), "moveQuadsFromIndex move is out of bounds");
    _vbAtlas->moveElementsOfType<V3F_C4B_T2F_Quad>(index, newIndex, _quadCount - index);
}

void TextureAtlas::fillWithEmptyQuadsFromIndex(size_t index, size_t amount)
{
    _vbAtlas->updateElementsOfType<V3F_C4B_T2F_Quad>(nullptr, amount, index);
}

// TextureAtlas - Drawing

void TextureAtlas::drawNumberOfQuads(size_t n)
{
    _ibAtlas->setElementCount(6 * _quadCount);
    GL::bindTexture2D(_texture->getName()); // ugh, have to have this here for now until I get rid of Label custom commands
    _vdAtlas->draw(0, n);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, n);
}

void TextureAtlas::drawNumberOfQuads(size_t numberOfQuads, size_t start)
{
    _ibAtlas->setElementCount(6 * _quadCount);
    GL::bindTexture2D(_texture->getName()); // ugh, have to have this here for now until I get rid of Label custom commands
    _vdAtlas->draw(start, numberOfQuads);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, numberOfQuads);
}

void TextureAtlas::drawQuads()
{
    _ibAtlas->setElementCount(6 * _quadCount);
    GL::bindTexture2D(_texture->getName()); // ugh, have to have this here for now until I get rid of Label custom commands
    _vdAtlas->draw();
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _vbAtlas->getElementCount());
}

bool TextureAtlas::isDirty()
{
    return _vdAtlas->isDirty();
}

void TextureAtlas::setDirty(bool dirty)
{
    _vdAtlas->setDirty(dirty);
}

NS_CC_END

