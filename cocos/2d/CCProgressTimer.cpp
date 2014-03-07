/****************************************************************************
Copyright (c) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc

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
#include "CCProgressTimer.h"

#include "ccMacros.h"
#include "CCTextureCache.h"
#include "CCGLProgram.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CCDirector.h"
#include "TransformUtils.h"
#include "CCDrawingPrimitives.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

// extern
#include "kazmath/GL/matrix.h"

#include <float.h>

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
    ProgressTimer *progressTimer = new ProgressTimer();
    if (progressTimer->initWithSprite(sp))
    {
        progressTimer->autorelease();
    }
    else
    {
        delete progressTimer;
        progressTimer = nullptr;
    }        

    return progressTimer;
}

bool ProgressTimer::initWithSprite(Sprite* sp)
{
    setPercentage(0.0f);
    _vertexData = nullptr;
    _vertexDataCount = 0;

    setAnchorPoint(Point(0.5f,0.5f));
    _type = Type::RADIAL;
    _reverseDirection = false;
    setMidpoint(Point(0.5f, 0.5f));
    setBarChangeRate(Point(1,1));
    setSprite(sp);
    // shader program
    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    return true;
}

ProgressTimer::~ProgressTimer(void)
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
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(_sprite);
        _sprite = sprite;
        setContentSize(_sprite->getContentSize());

        //    Every time we set a new sprite, we free the current vertex data
        if (_vertexData)
        {
            CC_SAFE_FREE(_vertexData);
            _vertexDataCount = 0;
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

void ProgressTimer::setReverseProgress(bool reverse)
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
Tex2F ProgressTimer::textureCoordFromAlphaPoint(Point alpha)
{
    Tex2F ret(0.0f, 0.0f);
    if (!_sprite) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = _sprite->getQuad();
    Point min = Point(quad.bl.texCoords.u,quad.bl.texCoords.v);
    Point max = Point(quad.tr.texCoords.u,quad.tr.texCoords.v);
    //  Fix bug #1303 so that progress timer handles sprite frame texture rotation
    if (_sprite->isTextureRectRotated()) {
        CC_SWAP(alpha.x, alpha.y, float);
    }
    return Tex2F(min.x * (1.f - alpha.x) + max.x * alpha.x, min.y * (1.f - alpha.y) + max.y * alpha.y);
}

Vertex2F ProgressTimer::vertexFromAlphaPoint(Point alpha)
{
    Vertex2F ret(0.0f, 0.0f);
    if (!_sprite) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = _sprite->getQuad();
    Point min = Point(quad.bl.vertices.x,quad.bl.vertices.y);
    Point max = Point(quad.tr.vertices.x,quad.tr.vertices.y);
    ret.x = min.x * (1.f - alpha.x) + max.x * alpha.x;
    ret.y = min.y * (1.f - alpha.y) + max.y * alpha.y;
    return ret;
}

void ProgressTimer::updateColor(void)
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

void ProgressTimer::updateProgress(void)
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

void ProgressTimer::setAnchorPoint(const Point& anchorPoint)
{
    Node::setAnchorPoint(anchorPoint);
}

Point ProgressTimer::getMidpoint() const
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

void ProgressTimer::setMidpoint(const Point& midPoint)
{
    _midpoint = midPoint.getClampPoint(Point::ZERO, Point(1, 1));
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
void ProgressTimer::updateRadial(void)
{
    if (!_sprite) {
        return;
    }
    float alpha = _percentage / 100.f;

    float angle = 2.f*((float)M_PI) * ( _reverseDirection ? alpha : 1.0f - alpha);

    //    We find the vector to do a hit detection based on the percentage
    //    We know the first vector is the one @ 12 o'clock (top,mid) so we rotate
    //    from that by the progress angle around the _midpoint pivot
    Point topMid = Point(_midpoint.x, 1.f);
    Point percentagePt = topMid.rotateByAngle(_midpoint, angle);


    int index = 0;
    Point hit = Point::ZERO;

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

            Point edgePtA = boundaryTexCoord(i % kProgressTextureCoordsCount);
            Point edgePtB = boundaryTexCoord(pIndex);

            //    Remember that the top edge is split in half for the 12 o'clock position
            //    Let's deal with that here by finding the correct endpoints
            if(i == 0){
                edgePtB = edgePtA.lerp(edgePtB, 1-_midpoint.x);
            } else if(i == 4){
                edgePtA = edgePtA.lerp(edgePtB, 1-_midpoint.x);
            }

            //    s and t are returned by ccpLineIntersect
            float s = 0, t = 0;
            if(Point::isLineIntersect(edgePtA, edgePtB, _midpoint, percentagePt, &s, &t))
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
            Point alphaPoint = boundaryTexCoord(i);
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
void ProgressTimer::updateBar(void)
{
    if (!_sprite) {
        return;
    }
    float alpha = _percentage / 100.0f;
    Point alphaOffset = Point(1.0f * (1.0f - _barChangeRate.x) + alpha * _barChangeRate.x, 1.0f * (1.0f - _barChangeRate.y) + alpha * _barChangeRate.y) * 0.5f;
    Point min = _midpoint - alphaOffset;
    Point max = _midpoint + alphaOffset;

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
        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Point(min.x,max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Point(min.x,max.y));

        //    BOTLEFT
        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Point(min.x,min.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Point(min.x,min.y));

        //    TOPRIGHT
        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Point(max.x,max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Point(max.x,max.y));

        //    BOTRIGHT
        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Point(max.x,min.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Point(max.x,min.y));
    } else {
        if(!_vertexData) {
            _vertexDataCount = 8;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT( _vertexData, "CCProgressTimer. Not enough memory");
            //    TOPLEFT 1
            _vertexData[0].texCoords = textureCoordFromAlphaPoint(Point(0,1));
            _vertexData[0].vertices = vertexFromAlphaPoint(Point(0,1));

            //    BOTLEFT 1
            _vertexData[1].texCoords = textureCoordFromAlphaPoint(Point(0,0));
            _vertexData[1].vertices = vertexFromAlphaPoint(Point(0,0));

            //    TOPRIGHT 2
            _vertexData[6].texCoords = textureCoordFromAlphaPoint(Point(1,1));
            _vertexData[6].vertices = vertexFromAlphaPoint(Point(1,1));

            //    BOTRIGHT 2
            _vertexData[7].texCoords = textureCoordFromAlphaPoint(Point(1,0));
            _vertexData[7].vertices = vertexFromAlphaPoint(Point(1,0));
        }

        //    TOPRIGHT 1
        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Point(min.x,max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Point(min.x,max.y));

        //    BOTRIGHT 1
        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Point(min.x,min.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Point(min.x,min.y));

        //    TOPLEFT 2
        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Point(max.x,max.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Point(max.x,max.y));

        //    BOTLEFT 2
        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Point(max.x,min.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Point(max.x,min.y));
    }
    updateColor();
}

Point ProgressTimer::boundaryTexCoord(char index)
{
    if (index < kProgressTextureCoordsCount) {
        if (_reverseDirection) {
            return Point((kProgressTextureCoords>>(7-(index<<1)))&1,(kProgressTextureCoords>>(7-((index<<1)+1)))&1);
        } else {
            return Point((kProgressTextureCoords>>((index<<1)+1))&1,(kProgressTextureCoords>>(index<<1))&1);
        }
    }
    return Point::ZERO;
}

void ProgressTimer::onDraw(const kmMat4 &transform, bool transformUpdated)
{

    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins(transform);

    GL::blendFunc( _sprite->getBlendFunc().src, _sprite->getBlendFunc().dst );

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );

    GL::bindTexture2D( _sprite->getTexture()->getName() );

#ifdef EMSCRIPTEN
    setGLBufferData((void*) _vertexData, (_vertexDataCount * sizeof(V2F_C4B_T2F)), 0);

    int offset = 0;
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid*)offset);

    offset += sizeof(Vertex2F);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid*)offset);

    offset += sizeof(Color4B);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid*)offset);
#else
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]) , &_vertexData[0].vertices);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]), &_vertexData[0].texCoords);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(_vertexData[0]), &_vertexData[0].colors);
#endif // EMSCRIPTEN

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

void ProgressTimer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    if( ! _vertexData || ! _sprite)
        return;

    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(ProgressTimer::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}


NS_CC_END
