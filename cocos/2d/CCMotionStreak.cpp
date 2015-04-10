/****************************************************************************
Copyright (c) 2011      ForzeField Studios S.L.
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "2d/CCMotionStreak.h"
#include "math/CCVertex.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"

NS_CC_BEGIN

MotionStreak::MotionStreak()
: _fastMode(false)
, _startingPositionInitialized(false)
, _texture(nullptr)
, _blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _positionR(Vec2::ZERO)
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
, _batchCommand()
, _vd(nullptr)
, _vbPosition(nullptr)
, _vbColor(nullptr)
, _vbTexel(nullptr)
{
}

MotionStreak::~MotionStreak()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_FREE(_pointState);
    CC_SAFE_FREE(_pointVertexes);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_colorPointer);
    CC_SAFE_FREE(_texCoords);
    
    CC_SAFE_RELEASE(_vbTexel);
    CC_SAFE_RELEASE(_vbColor);
    CC_SAFE_RELEASE(_vbPosition);
    CC_SAFE_RELEASE(_vd);
}

MotionStreak* MotionStreak::create(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path)
{
    MotionStreak *ret = new (std::nothrow) MotionStreak();
    if (ret && ret->initWithFade(fade, minSeg, stroke, color, path))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

MotionStreak* MotionStreak::create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture)
{
    MotionStreak *ret = new (std::nothrow) MotionStreak();
    if (ret && ret->initWithFade(fade, minSeg, stroke, color, texture))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MotionStreak::initWithFade(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path)
{
    CCASSERT(!path.empty(), "Invalid filename");

    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(path);
    return initWithFade(fade, minSeg, stroke, color, texture);
}

bool MotionStreak::initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture)
{
    Node::setPosition(Vec2::ZERO);
    setAnchorPoint(Vec2::ZERO);
    ignoreAnchorPointForPosition(true);
    _startingPositionInitialized = false;

    _positionR = Vec2::ZERO;
    _fastMode = true;
    _minSeg = (minSeg == -1.0f) ? stroke/5.0f : minSeg;
    _minSeg *= _minSeg;

    _stroke = stroke;
    _fadeDelta = 1.0f/fade;

    _maxPoints = (int)(fade*60.0f)+2;
    _nuPoints = 0;
    _pointState = (float *)malloc(sizeof(float) * _maxPoints);
    _pointVertexes = (Vec2*)malloc(sizeof(Vec2) * _maxPoints);

    _vertices = (Vec2*)malloc(sizeof(Vec2) * _maxPoints * 2);
    _texCoords = (Tex2F*)malloc(sizeof(Tex2F) * _maxPoints * 2);
    _colorPointer =  (uint8_t*)malloc(sizeof(uint8_t) * _maxPoints * 2 * 4);

    _vd = VertexData::create(VertexData::Primitive::TriangleStrip);
    _vbPosition = VertexBuffer::create(sizeof(Vec2),    2 * _maxPoints, VertexBuffer::ArrayType::Native, VertexBuffer::ArrayMode::Dynamic);
    _vbColor    = VertexBuffer::create(sizeof(Color4B), 2 * _maxPoints, VertexBuffer::ArrayType::Native, VertexBuffer::ArrayMode::Dynamic);
    _vbTexel    = VertexBuffer::create(sizeof(Tex2F),   2 * _maxPoints, VertexBuffer::ArrayType::Native, VertexBuffer::ArrayMode::Dynamic);
    _vd->addStream(_vbPosition, {0, GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 2});
    _vd->addStream(_vbColor,    {0, GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true});
    _vd->addStream(_vbTexel,    {0, GLProgram::VERTEX_ATTRIB_TEX_COORD, DataType::Float, 2});
    CC_SAFE_RETAIN(_vd);
    CC_SAFE_RETAIN(_vbPosition);
    CC_SAFE_RETAIN(_vbColor);
    CC_SAFE_RETAIN(_vbTexel);
    
    // Set blend mode
    _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;

    // shader state
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    setTexture(texture);
    setColor(color);
    scheduleUpdate();

    return true;
}

void MotionStreak::setPosition(const Vec2& position)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR = position;
}

void MotionStreak::setPosition(float x, float y)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.x = x;
    _positionR.y = y;
}

const Vec2& MotionStreak::getPosition() const
{
    return _positionR;
}

void MotionStreak::getPosition(float* x, float* y) const
{
    *x = _positionR.x;
    *y = _positionR.y;
}

float MotionStreak::getPositionX() const
{
    return _positionR.x;
}

Vec3 MotionStreak::getPosition3D() const
{
    return Vec3(_positionR.x, _positionR.y, getPositionZ());
}

void MotionStreak::setPositionX(float x)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.x = x;
}

float MotionStreak::getPositionY() const
{
    return  _positionR.y;
}

void MotionStreak::setPositionY(float y)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.y = y;
}

void MotionStreak::tintWithColor(const Color3B& colors)
{
    setColor(colors);

    // Fast assignation
    for(unsigned int i = 0; i<_nuPoints*2; i++) 
    {
        *((Color3B*) (_colorPointer+i*4)) = colors;
    }
}

Texture2D* MotionStreak::getTexture(void) const
{
    return _texture;
}

void MotionStreak::setTexture(Texture2D *texture)
{
    if (_texture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
}

void MotionStreak::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

const BlendFunc& MotionStreak::getBlendFunc(void) const
{
    return _blendFunc;
}

void MotionStreak::setOpacity(uint8_t opacity)
{
    CCASSERT(false, "Set opacity no supported");
}

uint8_t MotionStreak::getOpacity(void) const
{
    CCASSERT(false, "Opacity no supported");
    return 0;
}

void MotionStreak::setOpacityModifyRGB(bool bValue)
{
    CC_UNUSED_PARAM(bValue);
}

bool MotionStreak::isOpacityModifyRGB(void) const
{
    return false;
}

void MotionStreak::update(float delta)
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

            const uint8_t op = (uint8_t)(_pointState[newIdx] * 255.0f);
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
        bool a1 = _pointVertexes[_nuPoints-1].getDistanceSq(_positionR) < _minSeg;
        bool a2 = (_nuPoints == 1) ? false : (_pointVertexes[_nuPoints-2].getDistanceSq(_positionR)< (_minSeg * 2.0f));
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
        if(_nuPoints > 0 && _fastMode )
        {
            if(_nuPoints > 1)
            {
                ccVertexLineToPolygon(_pointVertexes, _stroke, _vertices, _nuPoints, 1);
            }
            else
            {
                ccVertexLineToPolygon(_pointVertexes, _stroke, _vertices, 0, 2);
            }
        }

        _nuPoints ++;
        
        _vbPosition->setElements(_vertices, 2 * _nuPoints);
        _vbColor->setElements(_colorPointer, 2 * _nuPoints);
    }

    if( ! _fastMode )
    {
        ccVertexLineToPolygon(_pointVertexes, _stroke, _vertices, 0, _nuPoints);
        
        _vbPosition->setElements(_vertices, 2 * _nuPoints);
        _vbColor->setElements(_colorPointer, 2 * _nuPoints);
    }

    // Updated Tex Coords only if they are different than previous step
    if( _nuPoints  && _previousNuPoints != _nuPoints ) {
        float texDelta = 1.0f / _nuPoints;
        for( i=0; i < _nuPoints; i++ ) {
            _texCoords[i*2] = Tex2F(0, texDelta*i);
            _texCoords[i*2+1] = Tex2F(1, texDelta*i);
        }

        _vbTexel->setElements(_texCoords, 2 * _nuPoints);

        _previousNuPoints = _nuPoints;
    }
}

void MotionStreak::reset()
{
    _nuPoints = 0;
}

void MotionStreak::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if(_nuPoints <= 1)
        return;
    
    _batchCommand.init(_globalZOrder, getGLProgram(), _blendFunc, _texture, _vd, transform);
    renderer->addCommand(&_batchCommand);
}

NS_CC_END
