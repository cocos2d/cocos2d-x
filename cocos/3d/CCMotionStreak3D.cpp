/****************************************************************************
Copyright (c) 2011      ForzeField Studios S.L.
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
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "3d/CCMotionStreak3D.h"
#include <stddef.h> // offsetof
#include "base/ccTypes.h"
#include "math/CCVertex.h"
#include "base/CCDirector.h"
#include "base/ccUtils.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/ccShaders.h"

NS_CC_BEGIN

MotionStreak3D::MotionStreak3D()
: _startingPositionInitialized(false)
, _texture(nullptr)
, _blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _positionR2D(0.f, 0.f)
, _sweepAxis(0.f, 1.f, 0.f)
, _stroke(0.0f)
, _fadeDelta(0.0f)
, _minSeg(0.0f)
, _maxPoints(0)
, _nuPoints(0)
, _previousNuPoints(0)
{
}

MotionStreak3D::~MotionStreak3D()
{
    CC_SAFE_RELEASE(_texture);
}

MotionStreak3D* MotionStreak3D::create(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path)
{
    MotionStreak3D *ret = new (std::nothrow) MotionStreak3D();
    if (ret && ret->initWithFade(fade, minSeg, stroke, color, path))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

MotionStreak3D* MotionStreak3D::create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture)
{
    MotionStreak3D *ret = new (std::nothrow) MotionStreak3D();
    if (ret && ret->initWithFade(fade, minSeg, stroke, color, texture))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MotionStreak3D::initWithFade(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path)
{
    CCASSERT(!path.empty(), "Invalid filename");

    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(path);
    return initWithFade(fade, minSeg, stroke, color, texture);
}

bool MotionStreak3D::initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture)
{
    Node::setPosition(Vec2::ZERO);
    setAnchorPoint(Vec2::ZERO);
    setIgnoreAnchorPointForPosition(true);
    _startingPositionInitialized = false;

    _positionR.setZero();
    _minSeg = (minSeg == -1.0f) ? stroke/5.0f : minSeg;
    _minSeg *= _minSeg;

    _stroke = stroke;
    _fadeDelta = 1.0f/fade;

    _maxPoints = (int)(fade*60.0f)+2;
    _nuPoints = 0;
    
    _pointState.resize(_maxPoints);
    _pointVertexes.resize(_maxPoints);

    _vertexData.resize(_maxPoints * 2);

    // Set blend mode
    _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;

    // shader state
    auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_TEXTURE_COLOR);
    _programState = new backend::ProgramState(program);

    _customCommand.getPipelineDescriptor().programState = _programState;

    initCustomCommand();

    setTexture(texture);
    setColor(color);
    scheduleUpdate();

    return true;
}

void MotionStreak3D::initCustomCommand()
{
    _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE_STRIP);

    auto& pipelineDescriptor = _customCommand.getPipelineDescriptor();
    auto layout = _programState->getVertexLayout();
    const auto& attributeInfo = _programState->getProgram()->getActiveAttributes();
    auto iter = attributeInfo.find("a_position");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT3, 0, false);
    }
    
    iter = attributeInfo.find("a_color");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_color", iter->second.location, backend::VertexFormat::UBYTE4, offsetof(VertexData, color), true);
    }
    
    iter = attributeInfo.find("a_texCoord");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_texCoord", iter->second.location, backend::VertexFormat::FLOAT2, offsetof(VertexData, texPos), false);
    }
    layout->setLayout(sizeof(VertexData));

    auto &blend = pipelineDescriptor.blendDescriptor;
    blend.blendEnabled = true;
    blend.sourceAlphaBlendFactor = blend.sourceRGBBlendFactor = _blendFunc.src;
    blend.destinationAlphaBlendFactor = blend.destinationRGBBlendFactor = _blendFunc.dst;

    _locMVP = _programState->getUniformLocation("u_MVPMatrix");
    _locTexture = _programState->getUniformLocation("u_texture");

    _customCommand.createVertexBuffer(sizeof(VertexData), _vertexData.size(), CustomCommand::BufferUsage::DYNAMIC);
}

void MotionStreak3D::setPosition(const Vec2& position)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR = Vec3(position.x, position.y, 0);
}

void MotionStreak3D::setPosition(float x, float y)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.x = x;
    _positionR.y = y;
}

void MotionStreak3D::setPosition3D(const Vec3& position)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR = position;
}

void MotionStreak3D::setRotation3D(const Vec3& /*rotation*/)
{}

void MotionStreak3D::setRotationQuat(const Quaternion& /*quat*/)
{}

const Vec2& MotionStreak3D::getPosition() const
{
    _positionR2D.x = _positionR.x;
    _positionR2D.y = _positionR.y;
    return _positionR2D;
}

void MotionStreak3D::getPosition(float* x, float* y) const
{
    *x = _positionR.x;
    *y = _positionR.y;
}

float MotionStreak3D::getPositionX() const
{
    return _positionR.x;
}

Vec3 MotionStreak3D::getPosition3D() const
{
    return Vec3(_positionR.x, _positionR.y, getPositionZ());
}

void MotionStreak3D::setPositionX(float x)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.x = x;
}

float MotionStreak3D::getPositionY() const
{
    return  _positionR.y;
}

void MotionStreak3D::setPositionY(float y)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.y = y;
}

void MotionStreak3D::tintWithColor(const Color3B& colors)
{
    setColor(colors);

    // Fast assignation
    for(unsigned int i = 0; i<_nuPoints*2; i++) 
    {
        auto &color = _vertexData[i].color;
        color.set(colors.r, colors.g, colors.b, color.a);
    }
}

Texture2D* MotionStreak3D::getTexture() const
{
    return _texture;
}

void MotionStreak3D::setTexture(Texture2D *texture)
{
    if (_texture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
        _programState->setTexture(_locTexture, 0, _texture->getBackendTexture());
    }
}

void MotionStreak3D::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

const BlendFunc& MotionStreak3D::getBlendFunc() const
{
    return _blendFunc;
}

void MotionStreak3D::setOpacity(uint8_t /*opacity*/)
{
    CCASSERT(false, "Set opacity no supported");
}

uint8_t MotionStreak3D::getOpacity() const
{
    CCASSERT(false, "Opacity no supported");
    return 0;
}

void MotionStreak3D::setOpacityModifyRGB(bool /*bValue*/)
{
}

bool MotionStreak3D::isOpacityModifyRGB() const
{
    return false;
}

void MotionStreak3D::update(float delta)
{
    if (!_startingPositionInitialized)
    {
        return;
    }
    
    delta *= _fadeDelta;

    unsigned int newIdx, newIdx2, i, i2;
    unsigned int mov = 0;

    // Update current points
    for(i = 0; i<_nuPoints; i++)
    {
        _pointState[i]-=delta;

        if(_pointState[i] <= 0)
            mov++;
        else
        {
            newIdx = i-mov;

            if(mov>0)
            {
                // Move data
                _pointState[newIdx] = _pointState[i];

                // Move point
                _pointVertexes[newIdx] = _pointVertexes[i];

                // Move vertices
                i2 = i*2;
                newIdx2 = newIdx*2;
                _vertexData[newIdx2].pos = _vertexData[i2].pos;
                _vertexData[newIdx2+1].pos = _vertexData[i2+1].pos;

                // Move color
                _vertexData[newIdx2].color = _vertexData[i2].color;
                _vertexData[newIdx2 + 1].color = _vertexData[i2 + 1].color;
            }else
                newIdx2 = newIdx*2;

            const uint8_t op = (uint8_t)(_pointState[newIdx] * 255.0f);
            _vertexData[newIdx2].color.a = op;
            _vertexData[newIdx2+1].color.a = op;
        }
    }
    _nuPoints-=mov;

    // Append new point
    bool appendNewPoint = true;
    if(_nuPoints >= _maxPoints)
    {
        appendNewPoint = false;
    }

    else if(_nuPoints>0)
    {
        bool a1 = (_pointVertexes[_nuPoints-1] - _positionR).lengthSquared() < _minSeg;
        bool a2 = (_nuPoints == 1) ? false : ((_pointVertexes[_nuPoints-2] - _positionR).lengthSquared() < (_minSeg * 2.0f));
        if(a1 || a2)
        {
            appendNewPoint = false;
        }
    }

    if(appendNewPoint)
    {
        _pointVertexes[_nuPoints] = _positionR;
        _pointState[_nuPoints] = 1.0f;

        // Color assignment
        _vertexData[_nuPoints * 2].color = Color4B(_displayedColor, 255);
        _vertexData[_nuPoints * 2 + 1].color = Color4B(_displayedColor, 255);


        // Generate polygon
        {
            float stroke = _stroke * 0.5f;
            _vertexData[_nuPoints * 2].pos = _pointVertexes[_nuPoints] + (_sweepAxis * stroke);
            _vertexData[_nuPoints * 2 + 1].pos = _pointVertexes[_nuPoints] - (_sweepAxis * stroke);
        }

        _nuPoints ++;
    }

    // Updated Tex Coords only if they are different than previous step
    if( _nuPoints  && _previousNuPoints != _nuPoints ) {
        float texDelta = 1.0f / _nuPoints;
        for( i=0; i < _nuPoints; i++ ) {
            _vertexData[i*2].texPos = Tex2F(0, texDelta*i);
            _vertexData[i*2+1].texPos = Tex2F(1, texDelta*i);
        }

        _previousNuPoints = _nuPoints;
    }
}

void MotionStreak3D::reset()
{
    _nuPoints = 0;
}

void MotionStreak3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if(_nuPoints <= 1)
        return;
    _beforeCommand.init(_globalZOrder);
    _afterCommand.init(_globalZOrder);
    _customCommand.init(_globalZOrder, transform, flags);
    
    auto pmatrix = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto mvpMatrix = pmatrix * transform;
    
    _programState->setUniform(_locMVP, mvpMatrix.m, sizeof(mvpMatrix.m));

    _beforeCommand.func = CC_CALLBACK_0(MotionStreak3D::onBeforeDraw, this);
    _afterCommand.func = CC_CALLBACK_0(MotionStreak3D::onAfterDraw, this);
    
    _customCommand.updateVertexBuffer(_vertexData.data(), sizeof(_vertexData[0]) * _nuPoints * 2);

    _customCommand.setVertexDrawInfo(0, _nuPoints * 2);

    renderer->addCommand(&_beforeCommand);
    renderer->addCommand(&_customCommand);
    renderer->addCommand(&_afterCommand);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _nuPoints*2);
}

void MotionStreak3D::onBeforeDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    _rendererDepthTest = renderer->getDepthTest();
    _rendererCullface = renderer->getCullMode();

    renderer->setCullMode(CullMode::NONE);
    renderer->setDepthTest(true);
}

void MotionStreak3D::onAfterDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    renderer->setDepthTest(_rendererDepthTest);
    renderer->setCullMode(_rendererCullface);
}

NS_CC_END
