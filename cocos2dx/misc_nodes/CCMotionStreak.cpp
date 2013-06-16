/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011 ForzeField Studios S.L.

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
#include "CCMotionStreak.h"
#include "textures/CCTextureCache.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "ccMacros.h"

#include "support/CCVertex.h"
#include "support/CCPointExtension.h"

NS_CC_BEGIN

CCMotionStreak::CCMotionStreak()
: _fastMode(false)
, _startingPositionInitialized(false)
, _texture(NULL)
, _positionR(CCPointZero)
, _stroke(0.0f)
, _fadeDelta(0.0f)
, _minSeg(0.0f)
, _maxPoints(0)
, _nuPoints(0)
, _previousNuPoints(0)
, _pointVertexes(NULL)
, _pointState(NULL)
, _vertices(NULL)
, _colorPointer(NULL)
, _texCoords(NULL)
{
    _blendFunc.src = GL_SRC_ALPHA;
    _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
}

CCMotionStreak::~CCMotionStreak()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_FREE(_pointState);
    CC_SAFE_FREE(_pointVertexes);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_colorPointer);
    CC_SAFE_FREE(_texCoords);
}

CCMotionStreak* CCMotionStreak::create(float fade, float minSeg, float stroke, ccColor3B color, const char* path)
{
    CCMotionStreak *pRet = new CCMotionStreak();
    if (pRet && pRet->initWithFade(fade, minSeg, stroke, color, path))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCMotionStreak* CCMotionStreak::create(float fade, float minSeg, float stroke, ccColor3B color, CCTexture2D* texture)
{
    CCMotionStreak *pRet = new CCMotionStreak();
    if (pRet && pRet->initWithFade(fade, minSeg, stroke, color, texture))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCMotionStreak::initWithFade(float fade, float minSeg, float stroke, ccColor3B color, const char* path)
{
    CCAssert(path != NULL, "Invalid filename");

    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(path);
    return initWithFade(fade, minSeg, stroke, color, texture);
}

bool CCMotionStreak::initWithFade(float fade, float minSeg, float stroke, ccColor3B color, CCTexture2D* texture)
{
    CCNode::setPosition(CCPointZero);
    setAnchorPoint(CCPointZero);
    ignoreAnchorPointForPosition(true);
    _startingPositionInitialized = false;

    _positionR = CCPointZero;
    _fastMode = true;
    _minSeg = (minSeg == -1.0f) ? stroke/5.0f : minSeg;
    _minSeg *= _minSeg;

    _stroke = stroke;
    _fadeDelta = 1.0f/fade;

    _maxPoints = (int)(fade*60.0f)+2;
    _nuPoints = 0;
    _pointState = (float *)malloc(sizeof(float) * _maxPoints);
    _pointVertexes = (CCPoint*)malloc(sizeof(CCPoint) * _maxPoints);

    _vertices = (ccVertex2F*)malloc(sizeof(ccVertex2F) * _maxPoints * 2);
    _texCoords = (ccTex2F*)malloc(sizeof(ccTex2F) * _maxPoints * 2);
    _colorPointer =  (GLubyte*)malloc(sizeof(GLubyte) * _maxPoints * 2 * 4);

    // Set blend mode
    _blendFunc.src = GL_SRC_ALPHA;
    _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;

    // shader program
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

    setTexture(texture);
    setColor(color);
    scheduleUpdate();

    return true;
}

void CCMotionStreak::setPosition(const CCPoint& position)
{
    _startingPositionInitialized = true;
    _positionR = position;
}

void CCMotionStreak::tintWithColor(ccColor3B colors)
{
    setColor(colors);

    // Fast assignation
    for(unsigned int i = 0; i<_nuPoints*2; i++) 
    {
        *((ccColor3B*) (_colorPointer+i*4)) = colors;
    }
}

CCTexture2D* CCMotionStreak::getTexture(void)
{
    return _texture;
}

void CCMotionStreak::setTexture(CCTexture2D *texture)
{
    if (_texture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
}

void CCMotionStreak::setBlendFunc(ccBlendFunc blendFunc)
{
    _blendFunc = blendFunc;
}

ccBlendFunc CCMotionStreak::getBlendFunc(void)
{
    return _blendFunc;
}

void CCMotionStreak::setOpacity(GLubyte opacity)
{
    CCAssert(false, "Set opacity no supported");
}

GLubyte CCMotionStreak::getOpacity(void)
{
    CCAssert(false, "Opacity no supported");
    return 0;
}

void CCMotionStreak::setOpacityModifyRGB(bool bValue)
{
    CC_UNUSED_PARAM(bValue);
}

bool CCMotionStreak::isOpacityModifyRGB(void)
{
    return false;
}

void CCMotionStreak::update(float delta)
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
        bool a1 = ccpDistanceSQ(_pointVertexes[_nuPoints-1], _positionR) < _minSeg;
        bool a2 = (_nuPoints == 1) ? false : (ccpDistanceSQ(_pointVertexes[_nuPoints-2], _positionR) < (_minSeg * 2.0f));
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
        *((ccColor3B*)(_colorPointer + offset)) = _displayedColor;
        *((ccColor3B*)(_colorPointer + offset+4)) = _displayedColor;

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
    }

    if( ! _fastMode )
    {
        ccVertexLineToPolygon(_pointVertexes, _stroke, _vertices, 0, _nuPoints);
    }

    // Updated Tex Coords only if they are different than previous step
    if( _nuPoints  && _previousNuPoints != _nuPoints ) {
        float texDelta = 1.0f / _nuPoints;
        for( i=0; i < _nuPoints; i++ ) {
            _texCoords[i*2] = tex2(0, texDelta*i);
            _texCoords[i*2+1] = tex2(1, texDelta*i);
        }

        _previousNuPoints = _nuPoints;
    }
}

void CCMotionStreak::reset()
{
    _nuPoints = 0;
}

void CCMotionStreak::draw()
{
    if(_nuPoints <= 1)
        return;

    CC_NODE_DRAW_SETUP();

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    ccGLBlendFunc( _blendFunc.src, _blendFunc.dst );

    ccGLBindTexture2D( _texture->getName() );

#ifdef EMSCRIPTEN
    // Size calculations from ::initWithFade
    setGLBufferData(_vertices, (sizeof(ccVertex2F) * _maxPoints * 2), 0);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(_texCoords, (sizeof(ccTex2F) * _maxPoints * 2), 1);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(_colorPointer, (sizeof(GLubyte) * _maxPoints * 2 * 4), 2);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
#else
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, _vertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, _texCoords);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, _colorPointer);
#endif // EMSCRIPTEN

    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nuPoints*2);

    CC_INCREMENT_GL_DRAWS(1);
}

NS_CC_END

