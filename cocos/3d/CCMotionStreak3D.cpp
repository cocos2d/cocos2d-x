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
#include "math/CCVertex.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderState.h"

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
, _pointVertexes(nullptr)
, _pointState(nullptr)
, _vertices(nullptr)
, _colorPointer(nullptr)
, _texCoords(nullptr)
{
}

MotionStreak3D::~MotionStreak3D()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_FREE(_pointState);
    CC_SAFE_FREE(_pointVertexes);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_colorPointer);
    CC_SAFE_FREE(_texCoords);
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
    _pointState = (float *)malloc(sizeof(float) * _maxPoints);
    _pointVertexes = (Vec3*)malloc(sizeof(Vec3) * _maxPoints);

    _vertices = (Vec3*)malloc(sizeof(Vec3) * _maxPoints * 2);
    _texCoords = (Tex2F*)malloc(sizeof(Tex2F) * _maxPoints * 2);
    _colorPointer =  (GLubyte*)malloc(sizeof(GLubyte) * _maxPoints * 2 * 4);

    // Set blend mode
    _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;

    // shader state
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR, texture));

    setTexture(texture);
    setColor(color);
    scheduleUpdate();

    return true;
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
        *((Color3B*) (_colorPointer+i*4)) = colors;
    }
}

Texture2D* MotionStreak3D::getTexture(void) const
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
    }
}

void MotionStreak3D::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

const BlendFunc& MotionStreak3D::getBlendFunc(void) const
{
    return _blendFunc;
}

void MotionStreak3D::setOpacity(GLubyte /*opacity*/)
{
    CCASSERT(false, "Set opacity no supported");
}

GLubyte MotionStreak3D::getOpacity(void) const
{
    CCASSERT(false, "Opacity no supported");
    return 0;
}

void MotionStreak3D::setOpacityModifyRGB(bool /*bValue*/)
{
}

bool MotionStreak3D::isOpacityModifyRGB(void) const
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
                _vertices[newIdx2] = _vertices[i2];
                _vertices[newIdx2+1] = _vertices[i2+1];

                // Move color
                i2 *= 4;
                newIdx2 *= 4;
                _colorPointer[newIdx2+0] = _colorPointer[i2+0];
                _colorPointer[newIdx2+1] = _colorPointer[i2+1];
                _colorPointer[newIdx2+2] = _colorPointer[i2+2];
                _colorPointer[newIdx2+4] = _colorPointer[i2+4];
                _colorPointer[newIdx2+5] = _colorPointer[i2+5];
                _colorPointer[newIdx2+6] = _colorPointer[i2+6];
            }else
                newIdx2 = newIdx*8;

            const GLubyte op = (GLubyte)(_pointState[newIdx] * 255.0f);
            _colorPointer[newIdx2+3] = op;
            _colorPointer[newIdx2+7] = op;
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
        const unsigned int offset = _nuPoints*8;
        *((Color3B*)(_colorPointer + offset)) = _displayedColor;
        *((Color3B*)(_colorPointer + offset+4)) = _displayedColor;

        // Opacity
        _colorPointer[offset+3] = 255;
        _colorPointer[offset+7] = 255;

        // Generate polygon
        {
            float stroke = _stroke * 0.5f;
            _vertices[_nuPoints * 2] = _pointVertexes[_nuPoints] + (_sweepAxis * stroke);
            _vertices[_nuPoints * 2 + 1] = _pointVertexes[_nuPoints] - (_sweepAxis * stroke);
        }

        _nuPoints ++;
    }

    // Updated Tex Coords only if they are different than previous step
    if( _nuPoints  && _previousNuPoints != _nuPoints ) {
        float texDelta = 1.0f / _nuPoints;
        for( i=0; i < _nuPoints; i++ ) {
            _texCoords[i*2] = Tex2F(0, texDelta*i);
            _texCoords[i*2+1] = Tex2F(1, texDelta*i);
        }

        _previousNuPoints = _nuPoints;
    }
}

void MotionStreak3D::reset()
{
    _nuPoints = 0;
}

void MotionStreak3D::onDraw(const Mat4 &transform, uint32_t /*flags*/)
{  
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    GL::bindTexture2D( _texture->getName() );
    
    glDisable(GL_CULL_FACE);
    RenderState::StateBlock::_defaultState->setCullFace(false);
    glEnable(GL_DEPTH_TEST);
    RenderState::StateBlock::_defaultState->setDepthTest(true);

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, _colorPointer);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nuPoints*2);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _nuPoints*2);
}

void MotionStreak3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if(_nuPoints <= 1)
        return;
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(MotionStreak3D::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

NS_CC_END
