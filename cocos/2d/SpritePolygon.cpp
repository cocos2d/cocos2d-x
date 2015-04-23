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

#include "SpritePolygon.h"
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
#include "SpritePolygonCache.h"
#include "platform/CCFileUtils.h"
using namespace std;


USING_NS_CC;
using namespace cocos2d::experimental;

SpritePolygon *SpritePolygon::create(const std::string& file, std::vector<cocos2d::V3F_C4B_T2F>& verts, std::vector<unsigned short>& indices)
{
    SpritePolygon *ret = new (std::nothrow) SpritePolygon();
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
SpritePolygon *SpritePolygon::create(const std::string& file, std::vector<cocos2d::Vec2>& verts,std::vector<unsigned short>& indices,  const cocos2d::Rect& rect, bool rotated)
{
    SpritePolygon *ret = new (std::nothrow) SpritePolygon();
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
SpritePolygon *SpritePolygon::create(const std::string& file, std::vector<cocos2d::Vec2>& verts,  const cocos2d::Rect& rect, bool rotated)
{
    SpritePolygon *ret = new (std::nothrow) SpritePolygon();
    if (ret)
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
SpritePolygon *SpritePolygon::create(const std::string &file, const cocos2d::Rect &rect, unsigned short optimization)
{
    
    SpritePolygon *ret = new (std::nothrow) SpritePolygon();
    if (ret)
    {
        auto info = SpritePolygonCache::getInstance()->getSpritePolygonCache(file, rect);
        if(info)
        {
            CCLOG("created from cache");
            ret->initWithCache(file, info);
        }
        else{
            CCLOG("created with marching square");
            ret->initWithMarching(file, rect, optimization);
        }
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}




TrianglesCommand::Triangles SpritePolygon::triangulate(std::vector<cocos2d::Vec2> & verts)
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
    
    vector<V3F_C4B_T2F> *_verts = new vector<V3F_C4B_T2F>();
    vector<unsigned short> *_indices = new vector<unsigned short>;
    auto bb = setContentSizeFromVecs(verts);
//    auto bb = Rect(_textureRect);
//    bb.origin.x = -bb.size.width/2;
//    bb.origin.y = -bb.size.height/2;
    unsigned short idx = 0;
    auto texture = _texture;
    auto textureWidth = (float)texture->getPixelsWide();
    auto textureHeight = (float)texture->getPixelsHigh();
    auto scaledRect = CC_RECT_POINTS_TO_PIXELS(Rect(0,0, bb.size.width, bb.size.height));
    for(std::vector<p2t::Triangle*>::const_iterator ite = tris.begin(); ite < tris.end(); ite++)
    {
        for(int i = 0; i < 3; i++)
        {
            auto p = (*ite)->GetPoint(i);
            auto v3 = Vec3(p->x, p->y, 0);
            bool found = false;
            int j;
            for(j = 0; j < _verts->size(); j++)
            {
                if((*_verts)[j].vertices == v3)
                {
                    found = true;
                    break;
                }
            }
            if(found)
            {
                //if we found the same vertice, don't add to verts, but use the same vert with indices
                _indices->push_back(j);
            }
            else
            {
                //vert does not exist yet, so we need to create a new one,
                auto c4b = Color4B::WHITE;
                auto u = (scaledRect.origin.x + scaledRect.size.width* (p->x - bb.origin.x)/_contentSize.width)/textureWidth;
                auto v = (scaledRect.origin.y + scaledRect.size.height* (p->y - bb.origin.y)/_contentSize.height)/textureHeight;
                auto t2f = Tex2F(u,1-v);
                _verts->push_back(V3F_C4B_T2F{v3,c4b,t2f});
                _indices->push_back(idx);
                idx++;
            }



        }
    }
    for(auto j : points)
    {
        delete j;
    }
    delete cdt;
    return TrianglesCommand::Triangles{&(*_verts)[0], &(*_indices)[0], (ssize_t)_verts->size(), (ssize_t)_indices->size()};
}
bool SpritePolygon::initWithCache(const std::string &file, const SpritePolygonInfo *info)
{
    CCASSERT(file.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);
    if (texture)
    {
        initWithTexture(texture, info->_rect);
    }
    else{
        throw "some error";
    }
//    _textureRect = info->_textureRect;
//    _triangles = info->_triangles;
    return true;
}
bool SpritePolygon::initWithMarching(const std::string &file, const cocos2d::Rect &rect, unsigned short optimization)
{
    CCASSERT(file.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);
    if (texture)
    {
        initWithTexture(texture, rect);
    }
    else{
        throw "some error";
    }
    //Marching Square
    auto marcher = new MarchingSquare(file);
    marcher->trace();

    marcher->optimize(2);
        marcher->printPoints();
    auto p = marcher->getPoints();
    auto calculatedRect = setContentSizeFromVecs(p);
    auto _textureRect = Rect(rect.origin.x,rect.origin.y,calculatedRect.size.width, calculatedRect.size.height);
    auto _triangles = triangulate(p);
    delete marcher;

    
    //save result to cache
    SpritePolygonInfo *info = new SpritePolygonInfo();
    info->_rect = rect;
    info->_textureRect = _textureRect;
    info->_triangles = _triangles;
    _polygonInfo = SpritePolygonCache::getInstance()->addSpritePolygonCache(file, *info);
//    _polygonInfo = info;
    delete _triangles.verts;
    delete _triangles.indices;
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    SpritePolygonCache::printInfo(*info);
    return true;
}
bool SpritePolygon::initWithPoly2tri(const std::string &filename, std::vector<cocos2d::Vec2> & verts, const cocos2d::Rect &Rect, bool rotated)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
        initWithTexture(texture, Rect);
    }
    else{
        throw "some error";
    }
    SpritePolygonInfo info = SpritePolygonInfo{Rect, triangulate(verts), Rect};
    SpritePolygonCache::getInstance()->addSpritePolygonCache(filename, info);
    #if CC_SPRITE_DEBUG_DRAW
        debugDraw();
    #endif
    return true;
}
Rect SpritePolygon::getTextRectFromTriangles()
{
    CCASSERT(_polygonInfo, "cannot get texture rect because triangles were not defined");
    auto text = getTexture();
    int width = text->getPixelsWide();
    int height = text->getPixelsHigh();
    auto _verts = _polygonInfo->_triangles.verts;
    auto firstV = _verts[0];
    auto left = firstV.texCoords.u;
    auto right = firstV.texCoords.u;
    auto top = firstV.texCoords.v;
    auto bot = firstV.texCoords.v;
    for(int i = 0; i < _polygonInfo->_triangles.vertCount; i++)
    {
        if(_verts[i].texCoords.u < left)
        {
            left = _verts[i].texCoords.u;
        }
        else if (_verts[i].texCoords.u > right)
        {
            right = _verts[i].texCoords.u;
        }
        if(_verts[i].texCoords.v < bot)
        {
            bot = _verts[i].texCoords.v;
        }
        else if (_verts[i].texCoords.v > top)
        {
            top = _verts[i].texCoords.v;
        }
    }
    return Rect(left*width, bot*height, right*width, top*height);
}

bool SpritePolygon::initWithVerts(const std::string& filename,std::vector<cocos2d::V3F_C4B_T2F>& verts, std::vector<unsigned short>& indices)
{

    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
        initWithTexture(texture);
    }
    else{
        throw "some error";
    }
//    _verts = verts;
//    _indices = indices;
    auto _textureRect = getTextRectFromTriangles();

    auto _triangles = TrianglesCommand::Triangles{&verts[0], &indices[0], (ssize_t)verts.size(), (ssize_t)indices.size()};
    SpritePolygonInfo info = SpritePolygonInfo{_textureRect, _triangles, _textureRect};
    _polygonInfo = SpritePolygonCache::getInstance()->addSpritePolygonCache(filename, info);
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    return true;
}
Rect SpritePolygon::setContentSizeFromVecs(std::vector<cocos2d::Vec2>& verts)
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
bool SpritePolygon::initWithRect(const std::string& filename, std::vector<cocos2d::Vec2>& verts, std::vector<unsigned short>& indices, const cocos2d::Rect& rect, bool rotated)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    _rectRotated = rotated;
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (texture)
    {
        initWithTexture(texture, rect);
    }
    else{
        throw "some error";
    }
    auto bb = setContentSizeFromVecs(verts);
    //build v3f_c4b_t2f verts from vec2 vector
    vector<V3F_C4B_T2F> _verts;
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
    auto _triangles = TrianglesCommand::Triangles{&_verts[0], &indices[0], (ssize_t)_verts.size(), (ssize_t)indices.size()};
    
    SpritePolygonInfo info = SpritePolygonInfo{rect, _triangles, rect};
    SpritePolygonCache::getInstance()->addSpritePolygonCache(filename, info);
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    return true;
}

bool SpritePolygon::initWithTexture(Texture2D *texture, const Rect &rect)
{
    Node::init();
    //init the triangles command
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    
    setTexture(texture);
//    _textureRect = (rect.equals(Rect::ZERO))? Rect(0,0,texture->getPixelsWide(), texture->getPixelsHigh()) : rect;
    
    #if CC_SPRITE_DEBUG_DRAW
        _debugDrawNode = DrawNode::create();
        addChild(_debugDrawNode);
    #endif //CC_SPRITE_DEBUG_DRAW
    return true;
}
void SpritePolygon::setTexture(const std::string &filename)
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
//        updateBlendFunc();
    }
}
const float SpritePolygon::getArea(){
    float area = 0;
    V3F_C4B_T2F *verts = _polygonInfo->_triangles.verts;
    unsigned short *indices = _polygonInfo->_triangles.indices;
    for(int i = 0; i < _polygonInfo->_triangles.indexCount; i=i+3)
    {
        auto A = verts[indices[i]].vertices;
        auto B = verts[indices[i+1]].vertices;
        auto C = verts[indices[i+2]].vertices;
        area += (A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y - B.y))/2;
    }
    return area;
}

void SpritePolygon::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _tcmd.init(0, _texture->getName(), getGLProgramState(), _blendFunc, _polygonInfo->_triangles, transform, flags);
    
    SpritePolygonCache::printInfo(*_polygonInfo);
    
    renderer->addCommand(&_tcmd);
}
#if CC_SPRITE_DEBUG_DRAW
void SpritePolygon::debugDraw()
{
    //draw all points
    auto positions = new (std::nothrow) Vec2[_polygonInfo->_triangles.vertCount];
    auto verts = _polygonInfo->_triangles.verts;
    Vec2 *pos = positions;
    auto end =&verts[_polygonInfo->_triangles.vertCount];
    for(V3F_C4B_T2F *v = verts; v < end; pos++, v++)
    {
        pos->x = v->vertices.x;
        pos->y = v->vertices.y;
    }
    _debugDrawNode->drawPoints(positions, _polygonInfo->_triangles.vertCount, 8, Color4F{0.0,1.0,1.0,1.0});
    //draw lines
    auto last = _polygonInfo->_triangles.indexCount/3;
    auto _indices = _polygonInfo->_triangles.indices;
    auto _verts = _polygonInfo->_triangles.verts;
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
#endif //CC_SPRITE_DEBUG_DRAW
