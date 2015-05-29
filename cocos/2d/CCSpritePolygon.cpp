/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCSpritePolygon.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCRenderer.h"

USING_NS_CC;
using namespace cocos2d::experimental;

SpritePolygon *SpritePolygon::create(const std::string &file, const cocos2d::Rect &rect, float optimization)
{
    SpritePolygon* spritePolygon = new (std::nothrow) SpritePolygon();
    if(spritePolygon && spritePolygon->initWithxxx(file, rect, optimization))
    {
        spritePolygon->autorelease();
        return spritePolygon;
    }
    CC_SAFE_DELETE(spritePolygon);
    return nullptr;
}

bool SpritePolygon::initWithxxx(const std::string& file, const cocos2d::Rect& rect, const float optimization)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);
    if(nullptr == texture)
    {
        CCLOG("texture was not loaded properly");
        return false;
    }
    initWithTexture(texture);
    Rect realRect  = rect;
    if(realRect.equals(Rect::ZERO))
    {
        realRect.setRect(0, 0, texture->getPixelsWide(), texture->getPixelsHigh());
    }
    _polygonInfo = SpritePolygonCache::getInstance()->getSpritePolygonCache(file, realRect, optimization);
    if(nullptr == _polygonInfo)
    {
        CCLOG("can not get the sprite polygon info.");
        return false;
    }
    setContentSize(_polygonInfo->rect.size/Director::getInstance()->getContentScaleFactor());
    setAnchorPoint(Vec2(0.5,0.5));
    
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    
    return true;
}

SpritePolygon::~SpritePolygon()
{
    CC_SAFE_RELEASE(_texture);
}

bool SpritePolygon::initWithTexture(Texture2D *texture)
{
    Node::init();
    //init the triangles command
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    setTexture(texture);
    return true;
}

void SpritePolygon::setTexture(const std::string &filename)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    setTexture(texture);
}

static unsigned char cc_2x2_white_image[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};

#define CC_2x2_WHITE_IMAGE_KEY  "/cc_2x2_white_image"
void SpritePolygon::setTexture(Texture2D *texture)
{
    // accept texture==nil as argument
    CCASSERT( !texture || dynamic_cast<Texture2D*>(texture), "setTexture expects a Texture2D. Invalid argument");
    
    if (texture == nullptr)
    {
        // Gets the texture by key firstly.
        texture = Director::getInstance()->getTextureCache()->getTextureForKey(CC_2x2_WHITE_IMAGE_KEY);
        
        // If texture wasn't in cache, create it from RAW data.
        if (texture == nullptr)
        {
            Image* image = new (std::nothrow) Image();
            bool isOK = image->initWithRawData(cc_2x2_white_image, sizeof(cc_2x2_white_image), 2, 2, 8);
            CC_UNUSED_PARAM(isOK);
            CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");
            
            texture = Director::getInstance()->getTextureCache()->addImage(image, CC_2x2_WHITE_IMAGE_KEY);
            CC_SAFE_RELEASE(image);
        }
    }
    
    if (_texture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
}

void SpritePolygon::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _tcmd.init(0, _texture->getName(), getGLProgramState(), _blendFunc, _polygonInfo->triangles, transform, flags);
    renderer->addCommand(&_tcmd);
}

const float SpritePolygon::getArea(){
    float area = 0;
    V3F_C4B_T2F *verts = _polygonInfo->triangles.verts;
    unsigned short *indices = _polygonInfo->triangles.indices;
    for(int i = 0; i < _polygonInfo->triangles.indexCount; i+=3)
    {
        auto A = verts[indices[i]].vertices;
        auto B = verts[indices[i+1]].vertices;
        auto C = verts[indices[i+2]].vertices;
        area += (A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y - B.y))/2;
    }
    return area;
}

void SpritePolygon::debugDraw()
{
    if(!_debugDrawNode)
    {
        _debugDrawNode = DrawNode::create();
        addChild(_debugDrawNode);
    }
    else{
        _debugDrawNode->clear();
    }
    //draw all points
    auto positions = new (std::nothrow) Vec2[_polygonInfo->triangles.vertCount];
    Vec2 *pos = &positions[0];
    auto verts = _polygonInfo->triangles.verts;
    auto end =  &verts[_polygonInfo->triangles.vertCount];
    for(V3F_C4B_T2F *v = verts; v != end; pos++, v++)
    {
        pos->x = v->vertices.x;
        pos->y = v->vertices.y;
    }
    _debugDrawNode->drawPoints(positions, (unsigned int)_polygonInfo->triangles.vertCount, 8, Color4F(0.0f, 1.0f, 1.0f, 1.0f));
    //draw lines
    auto last = _polygonInfo->triangles.indexCount/3;
    auto _indices = _polygonInfo->triangles.indices;
    auto _verts = _polygonInfo->triangles.verts;
    for(unsigned int i = 0; i < last; i++)
    {
        //draw 3 lines
        Vec3 from =_verts[_indices[i*3]].vertices;
        Vec3 to = _verts[_indices[i*3+1]].vertices;
        _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);
        
        from =_verts[_indices[i*3+1]].vertices;
        to = _verts[_indices[i*3+2]].vertices;
        _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);
        
        from =_verts[_indices[i*3+2]].vertices;
        to = _verts[_indices[i*3]].vertices;
        _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);

    }
    CC_SAFE_DELETE_ARRAY(positions);
}

void SpritePolygon::showDebug(const bool val)
{
    if(val)
    {
        if(!_debugDrawNode)
        {
            debugDraw();
        }
        else{
            _debugDrawNode->setVisible(val);
        }
    }
    else{
        if(_debugDrawNode)
        {
            _debugDrawNode->setVisible(val);
        }
    }
}
