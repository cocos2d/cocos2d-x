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
#include "2d/CCProgressTimer.h"

#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "2d/CCDrawingPrimitives.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "math/TransformUtils.h"

// extern
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
#if (DIRECTX_ENABLED == 1)
, _bufferVertex(nullptr)
, _bufferIndex(nullptr)
, _bufferDirty(false)
, _triCount(0)
#endif
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

    setAnchorPoint(Vec2(0.5f,0.5f));
    _type = Type::RADIAL;
    _reverseDirection = false;
    setMidpoint(Vec2(0.5f, 0.5f));
    setBarChangeRate(Vec2(1,1));
    setSprite(sp);

    // shader state
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    return true;
}

ProgressTimer::~ProgressTimer(void)
{
    CC_SAFE_FREE(_vertexData);
    CC_SAFE_RELEASE(_sprite);

#if (DIRECTX_ENABLED == 1)
	if (_bufferVertex)
		_bufferVertex->Release();
	if (_bufferIndex)
		_bufferIndex->Release();
#endif
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
Tex2F ProgressTimer::textureCoordFromAlphaPoint(Vec2 alpha)
{
    Tex2F ret(0.0f, 0.0f);
    if (!_sprite) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = _sprite->getQuad();
    Vec2 min = Vec2(quad.bl.texCoords.u,quad.bl.texCoords.v);
    Vec2 max = Vec2(quad.tr.texCoords.u,quad.tr.texCoords.v);
    //  Fix bug #1303 so that progress timer handles sprite frame texture rotation
    if (_sprite->isTextureRectRotated()) {
        CC_SWAP(alpha.x, alpha.y, float);
    }
    return Tex2F(min.x * (1.f - alpha.x) + max.x * alpha.x, min.y * (1.f - alpha.y) + max.y * alpha.y);
}

Vec3 ProgressTimer::vertexFromAlphaPoint(Vec2 alpha)
{
    Vec3 ret(0.0f, 0.0f, 0.0f);
    if (!_sprite) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = _sprite->getQuad();
    Vec3 min = Vec3(quad.bl.vertices.x,quad.bl.vertices.y, 0.0f);
	Vec3 max = Vec3(quad.tr.vertices.x, quad.tr.vertices.y, 0.0f);
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

void ProgressTimer::updateDisplayedOpacity(GLubyte parentOpacity)
{
    Node::updateDisplayedOpacity(parentOpacity);
    
    if(_sprite)
        _sprite->updateDisplayedOpacity(parentOpacity);
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
    Vec2 topMid = Vec2(_midpoint.x, 1.f);
    Vec2 percentagePt = topMid.rotateByAngle(_midpoint, angle);


    int index = 0;
    Vec2 hit = Vec2::ZERO;

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

	GLushort* indices = nullptr;
	int originalCount = _vertexDataCount;

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
        _vertexData = (V3F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V3F_C4B_T2F));
        CCASSERT( _vertexData, "CCProgressTimer. Not enough memory");

		UpdateVertexBuffer();
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
	_bufferDirty = true;

#if DIRECTX_ENABLED == 1
	if (_vertexDataCount != originalCount && _vertexDataCount > 0)
	{
		_triCount = index + 1;
		std::unique_ptr<GLushort> indices = std::unique_ptr<GLushort>(new GLushort[_triCount * 3]);

		GLushort* ptr = indices.get();
		int i = 0;
		ptr[i * 3 + 0] = (GLushort)0;
		ptr[i * 3 + 1] = (GLushort)1;
		ptr[i * 3 + 2] = (GLushort)2;
		++i;

		for (int j = 0; j < index; j++, i++)
		{
			ptr[i * 3 + 0] = (GLushort)(0);
			ptr[i * 3 + 1] = (GLushort)(j + 2);
			ptr[i * 3 + 2] = (GLushort)(j + 3);
		}
		
		UpdateIndexBuffer(indices.get(), _triCount * 3);
	}
#endif
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

	int originalCount = _vertexDataCount;

    if (!_reverseDirection) 
	{
        if(!_vertexData) {
            _vertexDataCount = 4;
            _vertexData = (V3F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V3F_C4B_T2F));
            CCASSERT( _vertexData, "CCProgressTimer. Not enough memory");
			UpdateVertexBuffer();
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
    } 
	else 
	{
        if(!_vertexData) 
		{
            _vertexDataCount = 8;
            _vertexData = (V3F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V3F_C4B_T2F));
            CCASSERT( _vertexData, "CCProgressTimer. Not enough memory");
			UpdateVertexBuffer();
			
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

	_bufferDirty = true;
    updateColor();

#if DIRECTX_ENABLED == 1
	if (_vertexDataCount != originalCount)
	{
		_triCount = _vertexDataCount / 2;
		std::unique_ptr<GLushort> indices = std::unique_ptr<GLushort>(new GLushort[_triCount * 3]);

		GLushort* ptr = indices.get();
		for (int i = 0; i < _triCount / 2; i++)
		{
			ptr[i * 6 + 0] = (GLushort)(i * 4 + 0);
			ptr[i * 6 + 1] = (GLushort)(i * 4 + 1);
			ptr[i * 6 + 2] = (GLushort)(i * 4 + 2);
			ptr[i * 6 + 3] = (GLushort)(i * 4 + 3);
			ptr[i * 6 + 4] = (GLushort)(i * 4 + 2);
			ptr[i * 6 + 5] = (GLushort)(i * 4 + 1);
		}

		UpdateIndexBuffer(indices.get(), _triCount * 3);
	}
#endif
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

void ProgressTimer::onDraw(const Mat4 &transform, uint32_t flags)
{

    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);
	getGLProgram()->set();

#if DIRECTX_ENABLED == 0
    GL::blendFunc( _sprite->getBlendFunc().src, _sprite->getBlendFunc().dst );

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );

    GL::bindTexture2D( _sprite->getTexture()->getName() );

#ifdef EMSCRIPTEN
    setGLBufferData((void*) _vertexData, (_vertexDataCount * sizeof(V3F_C4B_T2F)), 0);

    int offset = 0;
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offset);

    offset += sizeof(Vec2);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*)offset);

    offset += sizeof(Color4B);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offset);
#else
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]) , &_vertexData[0].vertices);
    glVertexAttribPointer( GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]), &_vertexData[0].texCoords);
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
#else
	if (_triCount == 0)
		return;

	DXStateCache::getInstance().setPSTexture(0, _sprite->getTexture()->getView());
	DXStateCache::getInstance().setBlend(_sprite->getBlendFunc().src, _sprite->getBlendFunc().dst);

	auto view = GLView::sharedOpenGLView();

	if (_bufferDirty)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		view->GetContext()->Map(_bufferVertex, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, _vertexData, sizeof(_vertexData[0]) * _vertexDataCount);
		view->GetContext()->Unmap(_bufferVertex, 0);

		_bufferDirty = false;
	}
	
	DXStateCache::getInstance().setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DXStateCache::getInstance().setVertexBuffer(_bufferVertex, sizeof(V3F_C4B_T2F), 0);
	DXStateCache::getInstance().setIndexBuffer(_bufferIndex);

	view->GetContext()->DrawIndexed(_triCount * 3, 0, 0);
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _vertexDataCount);
#endif
}

void ProgressTimer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if( ! _vertexData || ! _sprite)
        return;

    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(ProgressTimer::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

#if DIRECTX_ENABLED == 1
void ProgressTimer::UpdateVertexBuffer()
{
	if (_bufferVertex)
		_bufferVertex->Release();

	auto view = GLView::sharedOpenGLView();

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = _vertexData;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(_vertexData[0]) * _vertexDataCount, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
	DX::ThrowIfFailed(
		view->GetDevice()->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		&_bufferVertex));
}

void ProgressTimer::UpdateIndexBuffer(GLushort* indices, int count)
{
	if (_bufferIndex)
		_bufferIndex->Release();

	auto view = GLView::sharedOpenGLView();

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = indices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(indices[0]) * count, D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		view->GetDevice()->CreateBuffer(
		&indexBufferDesc,
		&indexBufferData,
		&_bufferIndex));
}
#endif

NS_CC_END
