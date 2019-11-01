/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "2d/CCGrid.h"

#include "base/ccMacros.h"
#include "base/ccUtils.h"
#include "2d/CCNode.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTexture2D.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Device.h"
#include "2d/CCCamera.h"


NS_CC_BEGIN
// implementation of GridBase

bool GridBase::initWithSize(const Size& gridSize)
{
    return initWithSize(gridSize, Rect::ZERO);
}

bool GridBase::initWithSize(const cocos2d::Size &gridSize, const cocos2d::Rect &rect)
{
    Director *director = Director::getInstance();
    Size s = director->getWinSizeInPixels();
    
    auto POTWide = ccNextPOT((unsigned int)s.width);
    auto POTHigh = ccNextPOT((unsigned int)s.height);
    
    Texture2D *texture = new (std::nothrow) Texture2D();
    if (! texture)
    {
        CCLOG("cocos2d: Grid: error creating texture");
        return false;
    }

    backend::TextureDescriptor descriptor;
    descriptor.width = POTWide;
    descriptor.height = POTHigh;
    descriptor.textureUsage = backend::TextureUsage::RENDER_TARGET;
    descriptor.textureFormat = backend::PixelFormat::RGBA8888;
    auto backendTexture = backend::Device::getInstance()->newTexture(descriptor);
    texture->initWithBackendTexture(backendTexture);
    backendTexture->release();
    
    initWithSize(gridSize, texture, false, rect);
    
    texture->release();
    
    return true;
}

bool GridBase::initWithSize(const Size& gridSize, Texture2D *texture, bool flipped)
{
    return initWithSize(gridSize, texture, flipped, Rect::ZERO);
}

bool GridBase::initWithSize(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect)
{
    bool ret = true;
    
    _active = false;
    _reuseGrid = 0;
    _gridSize = gridSize;
    
    _texture = texture;
    CC_SAFE_RETAIN(_texture);
    _isTextureFlipped = flipped;

#ifdef CC_USE_METAL
    _isTextureFlipped = !flipped;
#endif
    
    if (rect.equals(Rect::ZERO)) {
        auto size = _texture->getContentSize();
        _gridRect.setRect(0, 0, size.width, size.height);
    }
    else{
        _gridRect = rect;
    }
    _step.x = _gridRect.size.width/_gridSize.width;
    _step.y = _gridRect.size.height/_gridSize.height;

    auto& pipelineDescriptor = _drawCommand.getPipelineDescriptor();
    CC_SAFE_RELEASE(_programState);
    auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_TEXTURE);
    _programState = new (std::nothrow) backend::ProgramState(program);
    pipelineDescriptor.programState = _programState;
    _mvpMatrixLocation = pipelineDescriptor.programState->getUniformLocation("u_MVPMatrix");
    _textureLocation = pipelineDescriptor.programState->getUniformLocation("u_texture");
    
#define VERTEX_POSITION_SIZE 3
#define VERTEX_TEXCOORD_SIZE 2
    uint32_t texcoordOffset = (VERTEX_POSITION_SIZE)*sizeof(float);
    uint32_t totalSize = (VERTEX_POSITION_SIZE+VERTEX_TEXCOORD_SIZE)*sizeof(float);
    auto vertexLayout = _programState->getVertexLayout();
    const auto& attributeInfo = _programState->getProgram()->getActiveAttributes();
    auto iter = attributeInfo.find("a_position");
    if(iter != attributeInfo.end())
    {
        vertexLayout->setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT3, 0, false);
    }
    iter = attributeInfo.find("a_texCoord");
    if(iter != attributeInfo.end())
    {
        vertexLayout->setAttribute("a_texCoord", iter->second.location, backend::VertexFormat::FLOAT2, texcoordOffset, false);
    }
    vertexLayout->setLayout(totalSize);

    calculateVertexPoints();
    updateBlendState();
    return ret;
}

void GridBase::updateBlendState()
{
    if (! _texture || ! _texture->hasPremultipliedAlpha())
    {
        _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
    }
    else
    {
        _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    }
}

GridBase::~GridBase()
{
    CCLOGINFO("deallocing GridBase: %p", this);

    //TODO: ? why 2.0 comments this line:        setActive(false);
    CC_SAFE_RELEASE(_texture);
    
    CC_SAFE_RELEASE(_programState);
}

// properties
void GridBase::setActive(bool active)
{
    _active = active;
    if (! active)
    {
        Director *pDirector = Director::getInstance();
        Director::Projection proj = pDirector->getProjection();
        pDirector->setProjection(proj);
    }
}

void GridBase::setTextureFlipped(bool flipped)
{
    if (_isTextureFlipped != flipped)
    {
        _isTextureFlipped = flipped;
        calculateVertexPoints();
    }
}

void GridBase::set2DProjection()
{
    Director *director = Director::getInstance();
    Size    size = director->getWinSizeInPixels();

    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    Mat4 orthoMatrix;
    Mat4::createOrthographicOffCenter(0, size.width, 0, size.height, -1, 1, &orthoMatrix);
    director->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);

    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void GridBase::setGridRect(const cocos2d::Rect &rect)
{
    _gridRect = rect;
}

void GridBase::beforeDraw()
{
    // save projection
    Director *director = Director::getInstance();

    auto renderer = director->getRenderer();

    renderer->addCommand(&_groupCommand);
    renderer->pushGroup(_groupCommand.getRenderQueueID());

    _beforeDrawCommand.func = [=]() -> void {
        _directorProjection = director->getProjection();
        set2DProjection();
        Size    size = director->getWinSizeInPixels();
        renderer->setViewPort(0, 0, (unsigned int)size.width, (unsigned int)size.height);

        RenderTargetFlag flags = RenderTargetFlag::COLOR;
        _oldColorAttachment = renderer->getColorAttachment();
        _oldDepthAttachment = renderer->getDepthAttachment();
        _oldStencilAttachment = renderer->getStencilAttachment();
        _oldRenderTargetFlag = renderer->getRenderTargetFlag();

        renderer->setRenderTarget(flags, _texture, nullptr, nullptr);
    };
    renderer->addCommand(&_beforeDrawCommand);
    renderer->clear(ClearFlag::COLOR, _clearColor, 1, 0, 0.0);
}

void GridBase::afterDraw(cocos2d::Node * /*target*/)
{
    // restore projection
    Director *director = Director::getInstance();
    auto renderer = director->getRenderer();

    _afterDrawCommand.func = [=]() -> void {
        director->setProjection(_directorProjection);
        const auto& vp = Camera::getDefaultViewport();
        renderer->setViewPort(vp.x, vp.y, vp.w, vp.h);
        renderer->setRenderTarget(_oldRenderTargetFlag, _oldColorAttachment, _oldDepthAttachment, _oldStencilAttachment);
    };
    renderer->addCommand(&_afterDrawCommand);

    renderer->popGroup();

//    if (target->getCamera()->isDirty())
//    {
//        Vec2 offset = target->getAnchorPointInPoints();
//
//        //
//        // FIXME: Camera should be applied in the AnchorPoint
//        //
//        kmGLTranslatef(offset.x, offset.y, 0);
//        target->getCamera()->locate();
//        kmGLTranslatef(-offset.x, -offset.y, 0);
//    }

    // restore projection for default FBO .fixed bug #543 #544
    //TODO:         Director::getInstance()->setProjection(Director::getInstance()->getProjection());
    //TODO:         Director::getInstance()->applyOrientation();
    _beforeBlitCommand.func = [=]() -> void {
        beforeBlit();
    };
    renderer->addCommand(&_beforeBlitCommand);

    blit();

    _afterBlitCommand.func = [=]() -> void {
        afterBlit();
    };
    renderer->addCommand(&_afterBlitCommand);
}

// implementation of Grid3D

Grid3D* Grid3D::create(const Size& gridSize)
{
    Grid3D *ret= new (std::nothrow) Grid3D();

    if (ret)
    {
        if (ret->initWithSize(gridSize))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }

    return ret;
}

Grid3D* Grid3D::create(const Size& gridSize, const Rect& rect)
{
    Grid3D *ret= new (std::nothrow) Grid3D();
    
    if (ret)
    {
        if (ret->initWithSize(gridSize, rect))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}

Grid3D* Grid3D::create(const Size& gridSize, Texture2D *texture, bool flipped)
{
    Grid3D *ret= new (std::nothrow) Grid3D();
    
    if (ret)
    {
        if (ret->initWithSize(gridSize, texture, flipped))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}

Grid3D* Grid3D::create(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect)
{
    Grid3D *ret= new (std::nothrow) Grid3D();
    
    if (ret)
    {
        if (ret->initWithSize(gridSize, texture, flipped, rect))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}


Grid3D::Grid3D()
{
}

Grid3D::~Grid3D()
{
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_indices);
    CC_SAFE_FREE(_originalVertices);
    CC_SAFE_FREE(_vertexBuffer);
}

void Grid3D::beforeBlit()
{
    auto renderer = Director::getInstance()->getRenderer();

    if(_needDepthTestForBlit)
    {
        _oldDepthTest = renderer->getDepthTest();
        renderer->setDepthTest(true);

        _oldDepthWrite = renderer->getDepthWrite();
        renderer->setDepthWrite(true);
    }
}

void Grid3D::afterBlit()
{
    auto renderer = Director::getInstance()->getRenderer();
    if(_needDepthTestForBlit)
    {
       renderer->setDepthTest(_oldDepthTest);
       renderer->setDepthWrite(_oldDepthWrite);
    }
}

void Grid3D::blit()
{
    updateVertexBuffer();
    _drawCommand.init(0, _blendFunc);
    Director::getInstance()->getRenderer()->addCommand(&_drawCommand);
    cocos2d::Mat4 projectionMat = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto programState = _drawCommand.getPipelineDescriptor().programState;
    programState->setUniform(_mvpMatrixLocation, projectionMat.m, sizeof(projectionMat.m));
    programState->setTexture(_textureLocation, 0, _texture->getBackendTexture());
}

void Grid3D::calculateVertexPoints()
{
    float width = (float)_texture->getPixelsWide();
    float height = (float)_texture->getPixelsHigh();
    float imageH = _texture->getContentSizeInPixels().height;

    int x = 0, y = 0, i = 0;
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_originalVertices);
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_vertexBuffer);
    CC_SAFE_FREE(_indices);

    size_t numOfPoints = static_cast<size_t>((_gridSize.width+1) * (_gridSize.height+1));

    _vertices = malloc(numOfPoints * sizeof(Vec3));
    _originalVertices = malloc(numOfPoints * sizeof(Vec3));
    _texCoordinates = malloc(numOfPoints * sizeof(Vec2));
    _vertexBuffer = malloc(numOfPoints * (sizeof(Vec3) + sizeof(Vec2)));
    _indices = (unsigned short*)malloc(static_cast<size_t>(_gridSize.width * _gridSize.height * sizeof(unsigned short) * 6));

    float *vertArray = (float*)_vertices;
    float *texArray = (float*)_texCoordinates;
    unsigned short *idxArray = _indices;

    for (x = 0; x < _gridSize.width; ++x)
    {
        for (y = 0; y < _gridSize.height; ++y)
        {
            int idx = (int)(y * _gridSize.width) + x;

            float x1 = x * _step.x + _gridRect.origin.x;
            float x2 = x1 + _step.x;
            float y1 = y * _step.y + _gridRect.origin.y;
            float y2= y1 + _step.y;

            unsigned short a = (unsigned short)(x * (_gridSize.height + 1) + y);
            unsigned short b = (unsigned short)((x + 1) * (_gridSize.height + 1) + y);
            unsigned short c = (unsigned short)((x + 1) * (_gridSize.height + 1) + (y + 1));
            unsigned short d = (unsigned short)(x * (_gridSize.height + 1) + (y + 1));

            unsigned short tempidx[6] = {a, b, d, b, c, d};

            memcpy(&idxArray[6*idx], tempidx, 6*sizeof(unsigned short));

            int l1[4] = {a*3, b*3, c*3, d*3};

            Vec3 e(x1, y1, 0);
            Vec3 f(x2, y1, 0);
            Vec3 g(x2, y2, 0);
            Vec3 h(x1, y2, 0);

            Vec3 l2[4] = {e, f, g, h};

            int tex1[4] = {a*2, b*2, c*2, d*2};
            Vec2 Tex2F[4] = {Vec2(x1, y1), Vec2(x2, y1), Vec2(x2, y2), Vec2(x1, y2)};

            for (i = 0; i < 4; ++i)
            {
                vertArray[l1[i]] = l2[i].x;
                vertArray[l1[i] + 1] = l2[i].y;
                vertArray[l1[i] + 2] = l2[i].z;

                texArray[tex1[i]] = Tex2F[i].x / width;
                if (_isTextureFlipped)
                {
                    texArray[tex1[i] + 1] = (imageH - Tex2F[i].y) / height;
                }
                else
                {
                    texArray[tex1[i] + 1] = Tex2F[i].y / height;
                }
            }
        }
    }

    updateVertexAndTexCoordinate();

    memcpy(_originalVertices, _vertices, static_cast<size_t>((_gridSize.width+1) * (_gridSize.height+1) * sizeof(Vec3)));
}

Vec3 Grid3D::getVertex(const Vec2& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    
    int index = (int)(pos.x * (_gridSize.height+1) + pos.y) * 3;
    float *vertArray = (float*)_vertices;

    Vec3 vert(vertArray[index], vertArray[index+1], vertArray[index+2]);

    return vert;
}

Vec3 Grid3D::getOriginalVertex(const Vec2& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    
    int index = (int)(pos.x * (_gridSize.height+1) + pos.y) * 3;
    float *vertArray = (float*)_originalVertices;

    Vec3 vert(vertArray[index], vertArray[index+1], vertArray[index+2]);

    return vert;
}

void Grid3D::setVertex(const Vec2& pos, const Vec3& vertex)
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int index = (int)(pos.x * (_gridSize.height + 1) + pos.y) * 3;
    float *vertArray = (float*)_vertices;
    vertArray[index] = vertex.x;
    vertArray[index+1] = vertex.y;
    vertArray[index+2] = vertex.z;
}

void Grid3D::reuse()
{
    if (_reuseGrid > 0)
    {
        memcpy(_originalVertices, _vertices, static_cast<size_t>((_gridSize.width+1) * (_gridSize.height+1) * sizeof(Vec3)));
        --_reuseGrid;
    }
}

void Grid3D::updateVertexBuffer()
{
    size_t numOfPoints = static_cast<size_t>((_gridSize.width+1) * (_gridSize.height+1));
    auto tempVecPointer = (Vec3*)_vertices;
    for (size_t i = 0; i < numOfPoints; ++i)
    {
        auto offset = i * (sizeof(Vec3) + sizeof(Vec2));
        memcpy((char*)_vertexBuffer + offset, &tempVecPointer[i], sizeof(Vec3));
    }
    _drawCommand.updateVertexBuffer(_vertexBuffer, (unsigned int)(numOfPoints * sizeof(Vec3) + numOfPoints * sizeof(Vec2)) );

    _drawCommand.updateIndexBuffer(_indices, static_cast<unsigned int>(_gridSize.width * _gridSize.height * 6 * sizeof(unsigned short)));
}

void Grid3D::updateVertexAndTexCoordinate()
{
    unsigned int numOfPoints = static_cast<unsigned int>((_gridSize.width+1) * (_gridSize.height+1));
    auto tempVecPointer = (Vec3*)_vertices;
    auto tempTexPointer = (Vec2*)_texCoordinates;
    for (unsigned int i = 0; i < numOfPoints; ++i)
    {
        auto offset = i * (sizeof(Vec3) + sizeof(Vec2));
        memcpy((char*)_vertexBuffer + offset, &tempVecPointer[i], sizeof(Vec3));
        memcpy((char*)_vertexBuffer + offset + sizeof(Vec3), &tempTexPointer[i], sizeof(Vec2));
    }
    _drawCommand.createVertexBuffer((unsigned int)(sizeof(Vec3) + sizeof(Vec2)), numOfPoints, CustomCommand::BufferUsage::DYNAMIC);
    _drawCommand.updateVertexBuffer(_vertexBuffer, numOfPoints * sizeof(Vec3) + numOfPoints * sizeof(Vec2));

    unsigned int capacity = (unsigned int)(_gridSize.width * _gridSize.height) * 6;
    _drawCommand.createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, capacity, CustomCommand::BufferUsage::DYNAMIC);
    _drawCommand.updateIndexBuffer(_indices, capacity * sizeof(unsigned short));
}

// implementation of TiledGrid3D

TiledGrid3D::~TiledGrid3D()
{
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_originalVertices);
    CC_SAFE_FREE(_indices);
}

TiledGrid3D* TiledGrid3D::create(const Size& gridSize)
{
    TiledGrid3D *ret= new (std::nothrow) TiledGrid3D();

    if (ret)
    {
        if (ret->initWithSize(gridSize))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }

    return ret;
}

TiledGrid3D* TiledGrid3D::create(const Size& gridSize, const Rect& rect)
{
    TiledGrid3D *ret= new (std::nothrow) TiledGrid3D();
    
    if (ret)
    {
        if (ret->initWithSize(gridSize, rect))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}

TiledGrid3D* TiledGrid3D::create(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect)
{
    TiledGrid3D *ret= new (std::nothrow) TiledGrid3D();
    
    if (ret)
    {
        if (ret->initWithSize(gridSize, texture, flipped, rect))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}

TiledGrid3D* TiledGrid3D::create(const Size& gridSize, Texture2D *texture, bool flipped)
{
    TiledGrid3D *ret= new (std::nothrow) TiledGrid3D();
    
    if (ret)
    {
        if (ret->initWithSize(gridSize, texture, flipped))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}

void TiledGrid3D::blit()
{
    updateVertexBuffer();
    Director::getInstance()->getRenderer()->addCommand(&_drawCommand);
    cocos2d::Mat4 projectionMat = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto programState = _drawCommand.getPipelineDescriptor().programState;
    programState->setUniform(_mvpMatrixLocation, projectionMat.m, sizeof(projectionMat.m));
    programState->setTexture(_textureLocation, 0, _texture->getBackendTexture());
}

void TiledGrid3D::calculateVertexPoints()
{
    float width = (float)_texture->getPixelsWide();
    float height = (float)_texture->getPixelsHigh();
    float imageH = _texture->getContentSizeInPixels().height;
    
    int numQuads = (int)(_gridSize.width * _gridSize.height);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_originalVertices);
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_indices);
    CC_SAFE_FREE(_vertexBuffer);

    _vertices = malloc(numQuads*4*sizeof(Vec3));
    _originalVertices = malloc(numQuads*4*sizeof(Vec3));
    _texCoordinates = malloc(numQuads*4*sizeof(Vec2));
    _indices = (unsigned short*)malloc(numQuads*6*sizeof(unsigned short));
    _vertexBuffer = malloc(numQuads * 4 * (sizeof(Vec3) + sizeof(Vec2) ) );

    float *vertArray = (float*)_vertices;
    float *texArray = (float*)_texCoordinates;
    unsigned short *idxArray = _indices;
    

    for (int x = 0; x < _gridSize.width; ++x)
    {
        for (int y = 0; y < _gridSize.height; ++y)
        {
            float x1 = x * _step.x + _gridRect.origin.x;
            float x2 = x1 + _step.x;
            float y1 = y * _step.y + _gridRect.origin.y;
            float y2 = y1 + _step.y;
            
            *vertArray++ = x1;
            *vertArray++ = y1;
            *vertArray++ = 0;
            *vertArray++ = x2;
            *vertArray++ = y1;
            *vertArray++ = 0;
            *vertArray++ = x1;
            *vertArray++ = y2;
            *vertArray++ = 0;
            *vertArray++ = x2;
            *vertArray++ = y2;
            *vertArray++ = 0;
            
            float newY1 = y1;
            float newY2 = y2;
            
            if (_isTextureFlipped) 
            {
                newY1 = imageH - y1;
                newY2 = imageH - y2;
            }

            *texArray++ = x1 / width;
            *texArray++ = newY1 / height;
            *texArray++ = x2 / width;
            *texArray++ = newY1 / height;
            *texArray++ = x1 / width;
            *texArray++ = newY2 / height;
            *texArray++ = x2 / width;
            *texArray++ = newY2 / height;
        }
    }
    
    for (int x = 0; x < numQuads; x++)
    {
        idxArray[x*6+0] = (unsigned short)(x * 4 + 0);
        idxArray[x*6+1] = (unsigned short)(x * 4 + 1);
        idxArray[x*6+2] = (unsigned short)(x * 4 + 2);
        
        idxArray[x*6+3] = (unsigned short)(x * 4 + 1);
        idxArray[x*6+4] = (unsigned short)(x * 4 + 2);
        idxArray[x*6+5] = (unsigned short)(x * 4 + 3);
    }

    updateVertexAndTexCoordinate();
    memcpy(_originalVertices, _vertices, numQuads * 12 * sizeof(float));
}

void TiledGrid3D::setTile(const Vec2& pos, const Quad3& coords)
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (int)(_gridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)_vertices;
    memcpy(&vertArray[idx], &coords, sizeof(Quad3));
}

Quad3 TiledGrid3D::getOriginalTile(const Vec2& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (int)(_gridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)_originalVertices;

    Quad3 ret;
    memcpy(&ret, &vertArray[idx], sizeof(Quad3));

    return ret;
}

Quad3 TiledGrid3D::getTile(const Vec2& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (int)(_gridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)_vertices;

    Quad3 ret;
    memcpy(&ret, &vertArray[idx], sizeof(Quad3));

    return ret;
}

void TiledGrid3D::reuse()
{
    if (_reuseGrid > 0)
    {
        int numQuads = (int)(_gridSize.width * _gridSize.height);

        memcpy(_originalVertices, _vertices, numQuads * 12 * sizeof(float));
        --_reuseGrid;
    }
}

void TiledGrid3D::updateVertexBuffer()
{
    size_t gradSize = static_cast<size_t>(_gridSize.width * _gridSize.height);
    size_t numOfPoints = gradSize * 4;
    auto tempVecPointer = (Vec3*)_vertices;
    for (size_t i = 0; i < numOfPoints; ++i)
    {
        auto offset = i * (sizeof(Vec3) + sizeof(Vec2));
        memcpy((char*)_vertexBuffer + offset, &tempVecPointer[i], sizeof(Vec3));
    }
    _drawCommand.updateVertexBuffer(_vertexBuffer, (unsigned int)(numOfPoints * sizeof(Vec3) + numOfPoints * sizeof(Vec2)) );

    _drawCommand.updateIndexBuffer(_indices, gradSize * 6 * sizeof(unsigned short));
}

void TiledGrid3D::updateVertexAndTexCoordinate()
{
    size_t gradSize = static_cast<size_t>(_gridSize.width * _gridSize.height);
    auto numOfPoints = gradSize * 4;
    auto tempVecPointer = (Vec3*)_vertices;
    auto tempTexPointer = (Vec2*)_texCoordinates;
    for (size_t i = 0; i < numOfPoints; ++i)
    {
        auto offset = i * (sizeof(Vec3) + sizeof(Vec2));
        memcpy((char*)_vertexBuffer + offset, &tempVecPointer[i], sizeof(Vec3));
        memcpy((char*)_vertexBuffer + offset + sizeof(Vec3), &tempTexPointer[i], sizeof(Vec2));
    }
    _drawCommand.createVertexBuffer((sizeof(Vec3) + sizeof(Vec2) ), numOfPoints, CustomCommand::BufferUsage::DYNAMIC);
    _drawCommand.updateVertexBuffer(_vertexBuffer, numOfPoints * sizeof(Vec3) + numOfPoints * sizeof(Vec2));

    _drawCommand.createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, gradSize * 6, CustomCommand::BufferUsage::DYNAMIC);
    _drawCommand.updateIndexBuffer(_indices, gradSize * 6 * sizeof(unsigned short));
}

NS_CC_END
