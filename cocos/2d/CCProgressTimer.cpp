/****************************************************************************
Copyright (c) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc
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
#include "2d/CCProgressTimer.h"

#include <algorithm>

#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "2d/CCSprite.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

#define kProgressTextureCoordsCount 4
//  kProgressTextureCoords holds points {0,1} {0,0} {1,0} {1,1} we can represent it as bits
const char kProgressTextureCoords = 0x4b;


ProgressTimer::ProgressTimer()
:_type(Type::RADIAL)
,_midpoint(0,0)
,_barChangeRate(0,0)
,_percentage(0.0f)
,_sprite(nullptr)
,_vertexDataCount(0)
,_vertexData(nullptr)
,_reverseDirection(false)
{}

ProgressTimer* ProgressTimer::create(Sprite* sp)
{
    ProgressTimer *progressTimer = new (std::nothrow) ProgressTimer();
    if (progressTimer && progressTimer->initWithSprite(sp))
    {
        progressTimer->autorelease();
        return progressTimer;
    }
    
    delete progressTimer;
    return nullptr;
}

bool ProgressTimer::initWithSprite(Sprite* sp)
{
    setPercentage(0.0f);
    _vertexData = nullptr;
    _vertexDataCount = 0;

    setAnchorPoint(Vec2(0.5f,0.5f));
    _type = Type::RADIAL;
    _reverseDirection = false;
    setMidpoint(Vec2(0.5f, 0.5f));
    setBarChangeRate(Vec2(1,1));
    setSprite(sp);

    // shader state
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR, sp->getTexture()));
    return true;
}

ProgressTimer::~ProgressTimer()
{
    CC_SAFE_FREE(_vertexData);
    CC_SAFE_RELEASE(_sprite);
}

void ProgressTimer::setPercentage(float percentage)
{
    if (_percentage != percentage)
    {
        _percentage = clampf(percentage, 0, 100);
        updateProgress();
    }
}

void ProgressTimer::setSprite(Sprite *sprite)
{
    if (_sprite != sprite)
    {
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
        if (sEngine)
        {
            if (_sprite)
                sEngine->releaseScriptObject(this, _sprite);
            if (sprite)
                sEngine->retainScriptObject(this, sprite);
        }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(_sprite);
        _sprite = sprite;
        setContentSize(_sprite->getContentSize());

        //    Every time we set a new sprite, we free the current vertex data
        if (_vertexData)
        {
            CC_SAFE_FREE(_vertexData);
            _vertexDataCount = 0;
            updateProgress();
        }
    }        
}

void ProgressTimer::setType(Type type)
{
    if (type != _type)
    {
        //    release all previous information
        if (_vertexData)
        {
            CC_SAFE_FREE(_vertexData);
            _vertexData = nullptr;
            _vertexDataCount = 0;
        }

        _type = type;
    }
}

void ProgressTimer::setReverseDirection(bool reverse)
{
    if( _reverseDirection != reverse ) {
        _reverseDirection = reverse;

        //    release all previous information
        CC_SAFE_FREE(_vertexData);
        _vertexDataCount = 0;
    }
}

// Interval

///
//    @returns the vertex position from the texture coordinate
///
Tex2F ProgressTimer::textureCoordFromAlphaPoint(Vec2 alpha)
{
    Tex2F ret(0.0f, 0.0f);
    if (!_sprite) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = _sprite->getQuad();
    Vec2 min(quad.bl.texCoords.u,quad.bl.texCoords.v);
    Vec2 max(quad.tr.texCoords.u,quad.tr.texCoords.v);
    //  Fix bug #1303 so that progress timer handles sprite frame texture rotation
    if (_sprite->isTextureRectRotated()) {
        std::swap(alpha.x, alpha.y);
    }
    return Tex2F(min.x * (1.f - alpha.x) + max.x * alpha.x, min.y * (1.f - alpha.y) + max.y * alpha.y);
}

Vec2 ProgressTimer::vertexFromAlphaPoint(Vec2 alpha)
{
    Vec2 ret(0.0f, 0.0f);
    if (!_sprite) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = _sprite->getQuad();
    Vec2 min(quad.bl.vertices.x,quad.bl.vertices.y);
    Vec2 max(quad.tr.vertices.x,quad.tr.vertices.y);
    ret.x = min.x * (1.f - alpha.x) + max.x * alpha.x;
    ret.y = min.y * (1.f - alpha.y) + max.y * alpha.y;
    return ret;
}

void ProgressTimer::updateColor()
{
    if (!_sprite) {
        return;
    }

    if (_vertexData)
    {
        Color4B sc = _sprite->getQuad().tl.colors;
        for (int i = 0; i < _vertexDataCount; ++i)
        {
            _vertexData[i].colors = sc;
        }            
    }
}

void ProgressTimer::updateProgress()
{
    switch (_type)
    {
    case Type::RADIAL:
        updateRadial();
        break;
    case Type::BAR:
        updateBar();
        break;
    default:
        break;
    }
}

void ProgressTimer::setAnchorPoint(const Vec2& anchorPoint)
{
    Node::setAnchorPoint(anchorPoint);
}

Vec2 ProgressTimer::getMidpoint() const
{
    return _midpoint;
}

void ProgressTimer::setColor(const Color3B &color)
{
    _sprite->setColor(color);
    updateColor();
}

const Color3B& ProgressTimer::getColor() const
{
    return _sprite->getColor();
}

void ProgressTimer::setOpacity(GLubyte opacity)
{
    _sprite->setOpacity(opacity);
    updateColor();
}

GLubyte ProgressTimer::getOpacity() const
{
    return _sprite->getOpacity();
}

void ProgressTimer::setMidpoint(const Vec2& midPoint)
{
    _midpoint = midPoint.getClampPoint(Vec2::ZERO, Vec2(1, 1));
}

///
//    Update does the work of mapping the texture onto the triangles
//    It now doesn't occur the cost of free/alloc data every update cycle.
//    It also only changes the percentage point but no other points if they have not
//    been modified.
//    
//    It now deals with flipped texture. If you run into this problem, just use the
//    sprite property and enable the methods flipX, flipY.
///
void ProgressTimer::updateRadial()
{
    if (!_sprite) {
        return;
    }
    float alpha = _percentage / 100.f;

    float angle = 2.f*((float)M_PI) * ( _reverseDirection ? alpha : 1.0f - alpha);

    //    We find the vector to do a hit detection based on the percentage
    //    We know the first vector is the one @ 12 o'clock (top,mid) so we rotate
    //    from that by the progress angle around the _midpoint pivot
    Vec2 topMid(_midpoint.x, 1.f);
    Vec2 percentagePt = topMid.rotateByAngle(_midpoint, angle);


    int index = 0;
    Vec2 hit;

    if (alpha == 0.f) {
        //    More efficient since we don't always need to check intersection
        //    If the alpha is zero then the hit point is top mid and the index is 0.
        hit = topMid;
        index = 0;
    } else if (alpha == 1.f) {
        //    More efficient since we don't always need to check intersection
        //    If the alpha is one then the hit point is top mid and the index is 4.
        hit = topMid;
        index = 4;
    } else {
        //    We run a for loop checking the edges of the texture to find the
        //    intersection point
        //    We loop through five points since the top is split in half

        float min_t = FLT_MAX;

        for (int i = 0; i <= kProgressTextureCoordsCount; ++i) {
            int pIndex = (i + (kProgressTextureCoordsCount - 1))%kProgressTextureCoordsCount;

            Vec2 edgePtA = boundaryTexCoord(i % kProgressTextureCoordsCount);
            Vec2 edgePtB = boundaryTexCoord(pIndex);

            //    Remember that the top edge is split in half for the 12 o'clock position
            //    Let's deal with that here by finding the correct endpoints
            if(i == 0){
                edgePtB = edgePtA.lerp(edgePtB, 1-_midpoint.x);
            } else if(i == 4){
                edgePtA = edgePtA.lerp(edgePtB, 1-_midpoint.x);
            }

            //    s and t are returned by ccpLineIntersect
            float s = 0, t = 0;
            if(Vec2::isLineIntersect(edgePtA, edgePtB, _midpoint, percentagePt, &s, &t))
            {

                //    Since our hit test is on rays we have to deal with the top edge
                //    being in split in half so we have to test as a segment
                if ((i == 0 || i == 4)) {
                    //    s represents the point between edgePtA--edgePtB
                    if (!(0.f <= s && s <= 1.f)) {
                        continue;
                    }
                }
                //    As long as our t isn't negative we are at least finding a
                //    correct hitpoint from _midpoint to percentagePt.
                if (t >= 0.f) {
                    //    Because the percentage line and all the texture edges are
                    //    rays we should only account for the shortest intersection
                    if (t < min_t) {
                        min_t = t;
                        index = i;
                    }
                }
            }
        }

        //    Now that we have the minimum magnitude we can use that to find our intersection
        hit = _midpoint+ ((percentagePt - _midpoint) * min_t);

    }


    //    The size of the vertex data is the index from the hitpoint
    //    the 3 is for the _midpoint, 12 o'clock point and hitpoint position.

    bool sameIndexCount = true;
    if(_vertexDataCount != index + 3){
        sameIndexCount = false;
        CC_SAFE_FREE(_vertexData);
        _vertexDataCount = 0;
    }


    if(!_vertexData) {
        _vertexDataCount = index + 3;
        _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
        CCASSERT( _vertexData, "CCProgressTimer. Not enough memory");
    }
    updateColor();

    if (!sameIndexCount) {

        //    First we populate the array with the _midpoint, then all
        //    vertices/texcoords/colors of the 12 'o clock start and edges and the hitpoint
        _vertexData[0].texCoords = textureCoordFromAlphaPoint(_midpoint);
        _vertexData[0].vertices = vertexFromAlphaPoint(_midpoint);

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(topMid);
        _vertexData[1].vertices = vertexFromAlphaPoint(topMid);

        for(int i = 0; i < index; ++i){
            Vec2 alphaPoint = boundaryTexCoord(i);
            _vertexData[i+2].texCoords = textureCoordFromAlphaPoint(alphaPoint);
            _vertexData[i+2].vertices = vertexFromAlphaPoint(alphaPoint);
        }
    }

    //    hitpoint will go last
    _vertexData[_vertexDataCount - 1].texCoords = textureCoordFromAlphaPoint(hit);
    _vertexData[_vertexDataCount - 1].vertices = vertexFromAlphaPoint(hit);

}

///
//    Update does the work of mapping the texture onto the triangles for the bar
//    It now doesn't occur the cost of free/alloc data every update cycle.
//    It also only changes the percentage point but no other points if they have not
//    been modified.
//    
//    It now deals with flipped texture. If you run into this problem, just use the
//    sprite property and enable the methods flipX, flipY.
///
void ProgressTimer::updateBar()
{
    if (!_sprite) {
        return;
    }
    float alpha = _percentage / 100.0f;
    Vec2 alphaOffset = Vec2(1.0f * (1.0f - _barChangeRate.x) + alpha * _barChangeRate.x, 1.0f * (1.0f - _barChangeRate.y) + alpha * _barChangeRate.y) * 0.5f;
    Vec2 min = _midpoint - alphaOffset;
    Vec2 max = _midpoint + alphaOffset;

    if (min.x < 0.f) {
        max.x += -min.x;
        min.x = 0.f;
    }

    if (max.x > 1.f) {
        min.x -= max.x - 1.f;
        max.x = 1.f;
    }

    if (min.y < 0.f) {
        max.y += -min.y;
        min.y = 0.f;
    }

    if (max.y > 1.f) {
        min.y -= max.y - 1.f;
        max.y = 1.f;
    }


    if (!_reverseDirection) {
        if(!_vertexData) {
            _vertexDataCount = 4;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT( _vertexData, "CCProgressTimer. Not enough memory");
        }
        //    TOPLEFT
        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(min.x,max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(min.x,max.y));

        //    BOTLEFT
        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(min.x,min.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(min.x,min.y));

        //    TOPRIGHT
        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(max.x,max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(max.x,max.y));

        //    BOTRIGHT
        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(max.x,min.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(max.x,min.y));
    } else {
        if(!_vertexData) {
            _vertexDataCount = 8;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT( _vertexData, "CCProgressTimer. Not enough memory");
            //    TOPLEFT 1
            _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(0,1));
            _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(0,1));

            //    BOTLEFT 1
            _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(0,0));
            _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(0,0));

            //    TOPRIGHT 2
            _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(1,1));
            _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(1,1));

            //    BOTRIGHT 2
            _vertexData[7].texCoords = textureCoordFromAlphaPoint(Vec2(1,0));
            _vertexData[7].vertices = vertexFromAlphaPoint(Vec2(1,0));
        }

        //    TOPRIGHT 1
        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x,max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x,max.y));

        //    BOTRIGHT 1
        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(min.x,min.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(min.x,min.y));

        //    TOPLEFT 2
        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(max.x,max.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(max.x,max.y));

        //    BOTLEFT 2
        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(max.x,min.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(max.x,min.y));
    }
    updateColor();
}

Vec2 ProgressTimer::boundaryTexCoord(char index)
{
    if (index < kProgressTextureCoordsCount) {
        if (_reverseDirection) {
            return Vec2((kProgressTextureCoords>>(7-(index<<1)))&1,(kProgressTextureCoords>>(7-((index<<1)+1)))&1);
        } else {
            return Vec2((kProgressTextureCoords>>((index<<1)+1))&1,(kProgressTextureCoords>>(index<<1))&1);
        }
    }
    return Vec2::ZERO;
}

void ProgressTimer::onDraw(const Mat4 &transform, uint32_t /*flags*/)
{

    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::blendFunc( _sprite->getBlendFunc().src, _sprite->getBlendFunc().dst );

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );

    GL::bindTexture2D( _sprite->getTexture() );

    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]) , &_vertexData[0].vertices);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]), &_vertexData[0].texCoords);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(_vertexData[0]), &_vertexData[0].colors);

    if(_type == Type::RADIAL)
    {
        glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexDataCount);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_vertexDataCount);
    }
    else if (_type == Type::BAR)
    {
        if (!_reverseDirection) 
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexDataCount);
            CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_vertexDataCount);
        }
        else 
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexDataCount/2);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, _vertexDataCount/2);
            // 2 draw calls
            CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(2,_vertexDataCount);
        }
    }
}

void ProgressTimer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if( ! _vertexData || ! _sprite)
        return;

    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(ProgressTimer::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}


NS_CC_END
