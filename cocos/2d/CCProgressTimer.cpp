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
#include <stddef.h> // offsetof
#include "base/ccTypes.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "2d/CCSprite.h"
#include "renderer/CCRenderer.h"
#include "base/ccUtils.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/ProgramState.h"

NS_CC_BEGIN

#define kProgressTextureCoordsCount 4
//  kProgressTextureCoords holds points {0,1} {0,0} {1,0} {1,1} we can represent it as bits
const char kProgressTextureCoords = 0x4b;

namespace
{
    backend::ProgramState* initPipelineDescriptor(cocos2d::CustomCommand& command, bool ridal, backend::UniformLocation &locMVP, backend::UniformLocation &locTexture)
    {
        auto& pipelieDescriptor = command.getPipelineDescriptor();
        auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_TEXTURE_COLOR);
        auto programState = new (std::nothrow) backend::ProgramState(program);
        CC_SAFE_RELEASE(pipelieDescriptor.programState);
        pipelieDescriptor.programState = programState;
        
        //set vertexLayout according to V2F_C4B_T2F structure
        auto vertexLayout = programState->getVertexLayout();
        const auto& attributeInfo = programState->getProgram()->getActiveAttributes();
        auto iter = attributeInfo.find("a_position");
        if(iter != attributeInfo.end())
        {
            vertexLayout->setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT2, 0, false);
        }
        iter = attributeInfo.find("a_texCoord");
        if(iter != attributeInfo.end())
        {
            vertexLayout->setAttribute("a_texCoord", iter->second.location, backend::VertexFormat::FLOAT2, offsetof(V2F_C4B_T2F, texCoords), false);
        }
        iter = attributeInfo.find("a_color");
        if(iter != attributeInfo.end())
        {
            vertexLayout->setAttribute("a_color", iter->second.location, backend::VertexFormat::UBYTE4, offsetof(V2F_C4B_T2F, colors), true);
        }
        vertexLayout->setLayout(sizeof(V2F_C4B_T2F));

        if (ridal)
        {
            command.setDrawType(CustomCommand::DrawType::ELEMENT);
            command.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE);
        }
        else
        {
            command.setDrawType(CustomCommand::DrawType::ARRAY);
            command.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE_STRIP);
        }


        locMVP = programState->getUniformLocation("u_MVPMatrix");
        locTexture = programState->getUniformLocation("u_texture");

        return programState;
    }
}


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
    setAnchorPoint(Vec2(0.5f,0.5f));
    setMidpoint(Vec2(0.5f, 0.5f));
    setBarChangeRate(Vec2(1,1));
    setSprite(sp);

    CC_SAFE_RELEASE(_programState);
    CC_SAFE_RELEASE(_programState2);
    _programState = initPipelineDescriptor(_customCommand, true, _locMVP1, _locTex1); 
    _programState2 = initPipelineDescriptor(_customCommand2, false, _locMVP2, _locTex2);
    
    return true;
}

ProgressTimer::~ProgressTimer()
{
    CC_SAFE_RELEASE(_sprite);
    CC_SAFE_RELEASE(_programState);
    CC_SAFE_RELEASE(_programState2);
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
        if (!_vertexData.empty())
        {
            _vertexData.clear();
            updateProgress();
        }
    }        
}

void ProgressTimer::setType(Type type)
{

    if (type == Type::RADIAL)
    {
        _customCommand.setDrawType(CustomCommand::DrawType::ELEMENT);
        _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE);
    }
    else
    {
        _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE_STRIP);
        _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);
    }

    if (type != _type)
    {
        //    release all previous information
        _vertexData.clear();
        _type = type;
    }
}

void ProgressTimer::setReverseDirection(bool reverse)
{
    if( _reverseDirection != reverse ) {
        _reverseDirection = reverse;
        //    release all previous information
        _vertexData.clear();
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
    if (!_sprite)
        return;

    if (!_vertexData.empty())
    {
        const Color4B& sc = _sprite->getQuad().tl.colors;
        for (int i = 0; i < _vertexData.size(); ++i)
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

void ProgressTimer::setOpacity(uint8_t opacity)
{
    _sprite->setOpacity(opacity);
    updateColor();
}

uint8_t ProgressTimer::getOpacity() const
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
    if (_vertexData.size() != index + 3)
    {
        sameIndexCount = false;
        _vertexData.resize(index + 3);
        _customCommand.createVertexBuffer(sizeof(_vertexData[0]), (unsigned int)_vertexData.size(),  CustomCommand::BufferUsage::DYNAMIC);
    }

    if (_indexData.size() != 3 + 3 * index)
    {
        _indexData.resize(3 + 3 * index);
        _customCommand.createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, (unsigned int)_indexData.size(), CustomCommand::BufferUsage::STATIC);
    }

    if (!sameIndexCount)
    {
        //    First we populate the array with the _midpoint, then all
        //    vertices/texcoords/colors of the 12 'o clock start and edges and the hitpoint
        _vertexData[0].texCoords = textureCoordFromAlphaPoint(_midpoint);
        _vertexData[0].vertices = vertexFromAlphaPoint(_midpoint);

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(topMid);
        _vertexData[1].vertices = vertexFromAlphaPoint(topMid);

        for(int i = 0; i < index; ++i)
        {
            Vec2 alphaPoint = boundaryTexCoord(i);
            _vertexData[i+2].texCoords = textureCoordFromAlphaPoint(alphaPoint);
            _vertexData[i+2].vertices = vertexFromAlphaPoint(alphaPoint);
        }

        for (int i = 0; i < index + 1; i++)
        {
            _indexData[i * 3] = 0;
            _indexData[i * 3 + 1] = i + 2;
            _indexData[i * 3 + 2] = i + 1;
        }

        _customCommand.updateIndexBuffer(_indexData.data(), (unsigned int)(_indexData.size() * sizeof(_indexData[0])) );
    }

    //    hitpoint will go last
    _vertexData[_vertexData.size() - 1].texCoords = textureCoordFromAlphaPoint(hit);
    _vertexData[_vertexData.size() - 1].vertices = vertexFromAlphaPoint(hit);

    updateColor();
    _customCommand.updateVertexBuffer(_vertexData.data(), (unsigned int)(sizeof(_vertexData[0]) * _vertexData.size()) );
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
    if (!_sprite)
        return;
    
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
        
        if (_vertexData.size() != 4)
        {
            _vertexData.resize(4);
            _customCommand.createVertexBuffer(sizeof(_vertexData[0]),(unsigned int) _vertexData.size(), CustomCommand::BufferUsage::DYNAMIC);
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

        updateColor();

        _customCommand.updateVertexBuffer(_vertexData.data(), (unsigned int)(sizeof(_vertexData[0]) * _vertexData.size()));
    } else {
        if(_vertexData.size() != 8) {
            _vertexData.resize(8);
            _customCommand.createVertexBuffer(sizeof(_vertexData[0]), (unsigned int)(_vertexData.size() / 2), CustomCommand::BufferUsage::DYNAMIC);
            _customCommand2.createVertexBuffer(sizeof(_vertexData[0]), (unsigned int)(_vertexData.size() / 2), CustomCommand::BufferUsage::DYNAMIC);
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

        updateColor();

        _customCommand.updateVertexBuffer(_vertexData.data(), (unsigned int)(sizeof(_vertexData[0]) * _vertexData.size() / 2));
        _customCommand2.updateVertexBuffer((char*)_vertexData.data() + sizeof(_vertexData[0]) * _vertexData.size() / 2,
                                           (unsigned int)(sizeof(_vertexData[0]) * _vertexData.size() / 2));
    }
}

Vec2 ProgressTimer::boundaryTexCoord(char index)
{
    if (index < kProgressTextureCoordsCount)
    {
        if (_reverseDirection)
            return Vec2((kProgressTextureCoords>>(7-(index<<1)))&1,(kProgressTextureCoords>>(7-((index<<1)+1)))&1);
        else
            return Vec2((kProgressTextureCoords>>((index<<1)+1))&1,(kProgressTextureCoords>>(index<<1))&1);
    }
    else
        return Vec2::ZERO;
}

void ProgressTimer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if( _vertexData.empty() || ! _sprite)
        return;

    const cocos2d::Mat4& projectionMat = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Mat4 finalMat = projectionMat * transform;
    _programState->setUniform(_locMVP1, finalMat.m, sizeof(finalMat.m));
    _programState->setTexture(_locTex1, 0, _sprite->getTexture()->getBackendTexture());

    if(_type == Type::BAR)
    {
        if (!_reverseDirection)
        {
            _customCommand.init(_globalZOrder, _sprite->getBlendFunc());
            renderer->addCommand(&_customCommand);
        }
        else
        {
            _customCommand.init(_globalZOrder, _sprite->getBlendFunc());
            renderer->addCommand(&_customCommand);

            _customCommand2.init(_globalZOrder, _sprite->getBlendFunc());
            _programState2->setUniform(_locMVP2, finalMat.m, sizeof(finalMat.m));
            _programState2->setTexture(_locTex2, 0, _sprite->getTexture()->getBackendTexture());
            renderer->addCommand(&_customCommand2);
        }
    }
    else
    {
        _customCommand.init(_globalZOrder, _sprite->getBlendFunc());
        renderer->addCommand(&_customCommand);
    }
}


NS_CC_END
