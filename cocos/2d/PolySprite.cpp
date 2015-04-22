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

#include "PolySprite.h"
#include "3d/CCMesh.h"
#include "3d/CCMeshVertexIndexData.h"

#include "MarchingSquare.h"

#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include <vector>

#include "poly2tri/poly2tri.h"
#include "PolySpriteCache.h"
#include "platform/CCFileUtils.h"
using namespace std;


USING_NS_CC;
using namespace cocos2d::experimental;

PolySprite *PolySprite::create(const std::string& file, std::vector<cocos2d::V3F_C4B_T2F>& verts, std::vector<unsigned short>& indices)
{
    PolySprite *ret = new (std::nothrow) PolySprite();
    if (ret && ret->initWithVerts(file, verts, indices))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
PolySprite *PolySprite::create(const std::string& file, std::vector<cocos2d::Vec2>& verts,std::vector<unsigned short>& indices,  const cocos2d::Rect& rect, bool rotated)
{
    PolySprite *ret = new (std::nothrow) PolySprite();
    if (ret && ret->initWithRect(file, verts, indices, rect, rotated))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
PolySprite *PolySprite::create(const std::string& file, std::vector<cocos2d::Vec2>& verts,  const cocos2d::Rect& rect, bool rotated)
{
    PolySprite *ret = new (std::nothrow) PolySprite();
    if (ret && ret->initWithPoly2tri(file, verts, rect, rotated))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
PolySprite *PolySprite::create(const std::string &file, const cocos2d::Rect &rect, unsigned short optimization)
{
    PolySprite *ret = new (std::nothrow) PolySprite();
    if (ret && ret->initWithMarching(file, rect, optimization))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}




static Texture2D * getDummyTexture()
{
    auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("/dummyTexture");
    if(!texture)
    {
        unsigned char data[] ={255,0,0,255};//1*1 pure red picture
        Image * image =new (std::nothrow) Image();
        image->initWithRawData(data,sizeof(data),1,1,sizeof(unsigned char));
        texture=Director::getInstance()->getTextureCache()->addImage(image,"/dummyTexture");
        image->release();
    }
    return texture;
}
void PolySprite::triangulate(std::vector<cocos2d::Vec2> & verts)
{
    std::vector<p2t::Point*> points;
    for(std::vector<Vec2>::const_iterator it = verts.begin(); it<verts.end(); it++)
    {
        p2t::Point * p = new p2t::Point(it->x, it->y);
        points.push_back(p);
    }
    auto cdt = new p2t::CDT(points);
    cdt->Triangulate();
    std::vector<p2t::Triangle*> tris = cdt->GetTriangles();
    
    _verts.clear();
    _indices.clear();
    auto bb = setContentSizeFromVecs(verts);
//    auto bb = Rect(_textureRect);
//    bb.origin.x = -bb.size.width/2;
//    bb.origin.y = -bb.size.height/2;
    unsigned short idx = 0;
    auto texture = _texture;
    auto textureWidth = (float)texture->getPixelsWide();
    auto textureHeight = (float)texture->getPixelsHigh();
    auto scaledRect = CC_RECT_POINTS_TO_PIXELS(_textureRect);
    for(std::vector<p2t::Triangle*>::const_iterator ite = tris.begin(); ite < tris.end(); ite++)
    {
        for(int i = 0; i < 3; i++)
        {
            auto p = (*ite)->GetPoint(i);
            auto v3 = Vec3(p->x, p->y, 0);
            auto c4b = Color4B::WHITE;
            auto u = (scaledRect.origin.x + scaledRect.size.width* (p->x - bb.origin.x)/_contentSize.width)/textureWidth;
            auto v = (scaledRect.origin.y + scaledRect.size.height* (p->y - bb.origin.y)/_contentSize.height)/textureHeight;
            auto t2f = Tex2F(u,1-v);
            _verts.push_back(V3F_C4B_T2F{v3,c4b,t2f});
            _indices.push_back(idx);
            idx++;
        }
    }
    for(auto j : points)
    {
        delete j;
    }
    delete cdt;
    _triangles = TrianglesCommand::Triangles{&_verts[0], &_indices[0], (ssize_t)_verts.size(), (ssize_t)_indices.size()};
}
bool PolySprite::initWithMarching(const std::string &file, const cocos2d::Rect &rect, unsigned short optimization)
{
    CCASSERT(file.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);
    if (texture)
    {
        init(texture, rect);
    }
    else{
        throw "some error";
    }
    
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(file);
    PolySpriteInfo* info = PolySpriteCache::getInstance()->getPolySpriteCache(fullpath, rect);
    if (nullptr != info)
    {
        _textureRect = info->_textureRect;
        _triangles   = TrianglesCommand::Triangles{info->_triangles.verts, info->_triangles.indices, info->_triangles.vertCount, info->_triangles.indexCount};
#if CC_SPRITE_DEBUG_DRAW
        debugDraw();
#endif
    }
    
    
    //Marching Square
    auto marcher = new MarchingSquare(file);
    marcher->trace();
//    marcher->printPoints();
    marcher->optimize(3);
    auto p = marcher->getPoints();
    auto calculatedRect = setContentSizeFromVecs(p);
    _textureRect = Rect(rect.origin.x,rect.origin.y,calculatedRect.size.width, calculatedRect.size.height);
    triangulate(p);
    delete marcher;
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    PolySpriteInfo storeInfo = {rect, _triangles, _textureRect };
    PolySpriteCache::getInstance()->addPolySpriteCache(fullpath, storeInfo);
    return true;
}
bool PolySprite::initWithPoly2tri(const std::string &filename, std::vector<cocos2d::Vec2> & verts, const cocos2d::Rect &Rect, bool rotated)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
        init(texture, Rect);
    }
    else{
        throw "some error";
    }
    triangulate(verts);
    #if CC_SPRITE_DEBUG_DRAW
        debugDraw();
    #endif
    return true;
}
bool PolySprite::initWithVerts(const std::string& filename,std::vector<cocos2d::V3F_C4B_T2F>& verts, std::vector<unsigned short>& indices)
{

    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
//        rect.size = texture->getContentSize();
        init(texture);
//        return initWithTexture(texture, rect);
    }
    else{
        throw "some error";
    }
    _verts = verts;
    _indices = indices;
    _triangles = TrianglesCommand::Triangles{&_verts[0], &_indices[0], (ssize_t)_verts.size(), (ssize_t)_indices.size()};
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    return true;
}
Rect PolySprite::setContentSizeFromVecs(std::vector<cocos2d::Vec2>& verts)
{
    //find min max x,y coords
    auto firstV = &verts.front();
    auto left = firstV->x;
    auto right = firstV->x;
    auto top = firstV->y;
    auto bot = firstV->y;
    for(std::vector<Vec2>::const_iterator i = verts.begin()+1; i<verts.end(); i++)
    {
        if(i->x < left)
        {
            left = i->x;
        }
        else if (i->x > right)
        {
            right = i->x;
        }
        if(i->y < bot)
        {
            bot = i->y;
        }
        else if (i->y > top)
        {
            top = i->y;
        }
    }
    auto width = right - left;
    auto height = top - bot;
    setContentSize(Size(width, height));
    return Rect(left,bot,width,height);
}
bool PolySprite::initWithRect(const std::string& filename, std::vector<cocos2d::Vec2>& verts, std::vector<unsigned short>& indices, const cocos2d::Rect& rect, bool rotated)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    _rectRotated = rotated;
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
        init(texture, rect);
    }
    else{
        throw "some error";
    }
    auto bb = setContentSizeFromVecs(verts);
    //build v3f_c4b_t2f verts from vec2 vector
    _verts.clear();
    _indices.clear();
    unsigned short idx = 0;
    auto textureWidth = (float)texture->getPixelsWide();
    auto textureHeight = (float)texture->getPixelsHigh();
    auto scaledRect = CC_RECT_POINTS_TO_PIXELS(rect);
    for(std::vector<Vec2>::const_iterator it = verts.begin(); it<verts.end(); it++, idx++)
    {
        auto v3 = Vec3(it->x, it->y, 0);
        auto c4b = Color4B::WHITE;
        
        auto u = (scaledRect.origin.x + scaledRect.size.width* (it->x - bb.origin.x)/_contentSize.width)/textureWidth;
        auto v = (scaledRect.origin.y + scaledRect.size.height* (it->y - bb.origin.y)/_contentSize.height)/textureHeight;
        auto t2f = Tex2F(u,1-v);
        _verts.push_back(V3F_C4B_T2F{v3,c4b,t2f});
//        _indices.push_back(idx);
    }
    _indices = indices;
    _triangles = TrianglesCommand::Triangles{&_verts[0], &_indices[0], (ssize_t)_verts.size(), (ssize_t)_indices.size()};
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    return true;
}

bool PolySprite::init(Texture2D *texture, const Rect &rect)
{
    Node::init();
    //init the triangles command
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    
    setTexture(texture);
    _textureRect = (rect.equals(Rect::ZERO))? Rect(0,0,texture->getPixelsWide(), texture->getPixelsHigh()) : rect;
    
    #if CC_SPRITE_DEBUG_DRAW
        _debugDrawNode = DrawNode::create();
        addChild(_debugDrawNode);
    #endif //CC_SPRITE_DEBUG_DRAW
    return true;
}
void PolySprite::setTexture(const std::string &filename)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    setTexture(texture);
    
//    Rect rect = Rect::ZERO;
//    if (texture)
//        rect.size = texture->getContentSize();
//    setTextureRect(rect);
}
static unsigned char cc_2x2_white_image[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};
#define CC_2x2_WHITE_IMAGE_KEY  "/cc_2x2_white_image"
void PolySprite::setTexture(Texture2D *texture)
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
//        updateBlendFunc();
    }
}
const float PolySprite::getArea(){
    float area = 0;
    for(int i = 0; i < _indices.size(); i=i+3)
    {
        auto A = _verts[_indices[i]].vertices;
        auto B = _verts[_indices[i+1]].vertices;
        auto C = _verts[_indices[i+2]].vertices;
        area += (A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y - B.y))/2;
    }
    return area;
}

void PolySprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _tcmd.init(0, _texture->getName(), getGLProgramState(), _blendFunc, _triangles, transform, flags);
    
    renderer->addCommand(&_tcmd);
    
}
#if CC_SPRITE_DEBUG_DRAW
void PolySprite::debugDraw()
{
    //draw all points
    auto positions = new (std::nothrow) Vec2[_verts.size()];
    for(unsigned int i = 0; i < _verts.size(); i++)
    {
        positions[i].x = _verts[i].vertices.x;
        positions[i].y = _verts[i].vertices.y;
    }
    _debugDrawNode->drawPoints(positions, _verts.size(), 8, Color4F{0.0,1.0,1.0,1.0});
    //draw lines
    for(unsigned int i = 0; i < _indices.size()/3; i++)
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
#endif //CC_SPRITE_DEBUG_DRAW
