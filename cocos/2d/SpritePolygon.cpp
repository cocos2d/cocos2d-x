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
SpritePolygon *SpritePolygon::create(const std::string& file, std::vector<cocos2d::Vec2>& verts,std::vector<unsigned short>& indices,  const cocos2d::Rect& rect)
{
    SpritePolygon *ret = new (std::nothrow) SpritePolygon();
    if (ret && ret->initWithRect(file, verts, indices, rect))
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
SpritePolygon *SpritePolygon::create(const std::string& file, std::vector<cocos2d::Vec2>& verts,  const cocos2d::Rect& rect)
{
    SpritePolygon *ret = new (std::nothrow) SpritePolygon();
    if (ret && ret->initWithPoly2tri(file, verts, rect))
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
SpritePolygon *SpritePolygon::create(const std::string &file, const cocos2d::Rect &rect, float optimization)
{
    SpritePolygon *ret = new (std::nothrow) SpritePolygon();
    if (ret)
    {
        auto info = SpritePolygonCache::getInstance()->getSpritePolygonCache(file, rect);
        if(info)
        {
//            CCLOG("created from cache");
            ret->initWithCache(file, info);
        }
        else{
//            CCLOG("created with marching square");
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


void SpritePolygon::calculateUVandContentSize()
{
    /*
     whole texture UV coordination
     0,0                  1,0
     +---------------------+
     |                     |0.1
     |                     |0.2
     |     +--------+      |0.3
     |     |texRect |      |0.4
     |     |        |      |0.5
     |     |        |      |0.6
     |     +--------+      |0.7
     |                     |0.8
     |                     |0.9
     +---------------------+
     0,1                  1,1
     
     because when we scanned the image upside down, our uv is now upside down too
     */
    
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    float texWidth  = _texture->getPixelsWide()/scaleFactor;
    float texHeight = _texture->getPixelsHigh()/scaleFactor;
    
    // the texture rect in pixels, for example, an image is 32x32 pixels
    Rect* textRect = &_polygonInfo->_rect;

    
    bool needDelete = false;
    if(textRect->equals(Rect::ZERO))
    {
        //zero sized rect specified, so it means the whole image, for our calculation, we need actual image rect
        textRect = new Rect(0,0, texWidth, texHeight);
        needDelete = true;
    }
    setContentSize(textRect->size);


    auto end = &_polygonInfo->_triangles.verts[_polygonInfo->_triangles.vertCount];
    for(auto i = _polygonInfo->_triangles.verts; i != end; i++)
    {
        // for every point, offset with the centerpoint
        float u = i->vertices.x / texWidth;
        float v = (texHeight - i->vertices.y) / texHeight;
        i->texCoords.u = u;
        i->texCoords.v = v;
    }
    
    if(needDelete)
        delete textRect;
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
    unsigned short idx = 0;
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
                auto t2f = Tex2F(0,0); // don't worry about tex coords now, we calculate that later
                V3F_C4B_T2F vert = {v3,c4b,t2f};
                _verts->push_back(vert);
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

    TrianglesCommand::Triangles triangles = {&(*_verts)[0], &(*_indices)[0], (ssize_t)_verts->size(), (ssize_t)_indices->size()};
    return triangles;
}
bool SpritePolygon::initWithCache(const std::string &file, SpritePolygonInfo *info)
{
    CCASSERT(file.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);
    CCASSERT(texture, "texture was not loaded properly");
    _polygonInfo = info;
    initWithTexture(texture);
    if(_polygonInfo->_rect.equals(Rect::ZERO))
    {
        setContentSize(Size(texture->getPixelsWide(), texture->getPixelsHigh())/Director::getInstance()->getContentScaleFactor());
    }
    else
    {
        setContentSize(_polygonInfo->_rect.size);
    }
    

    setAnchorPoint(Vec2(0.5,0.5));
    return true;
}
bool SpritePolygon::initWithMarching(const std::string &file, const cocos2d::Rect &rect, float optimization)
{
    CCASSERT(file.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(file);
    CCASSERT(texture, "texture was not loaded properly");
    initWithTexture(texture);
    optimization = (optimization < 0)? (float)texture->getPixelsHigh()*(float)texture->getPixelsWide()*0.00015/Director::getInstance()->getContentScaleFactor() : optimization/Director::getInstance()->getContentScaleFactor();
    
    //Marching Square
    auto marcher = new MarchingSquare(file);
    marcher->trace();
    marcher->optimize(optimization);
//    marcher->test();
    
    auto p = marcher->getPoints();
    auto triangles = triangulate(p);
    delete marcher;
    
    //save result to cache
    _polygonInfo = SpritePolygonCache::getInstance()->addSpritePolygonCache(file, rect, triangles);
    setAnchorPoint(Vec2(0.5,0.5));
    calculateUVandContentSize();

//    SpritePolygonCache::printInfo(*_polygonInfo);
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    return true;
}
bool SpritePolygon::initWithPoly2tri(const std::string &filename, std::vector<cocos2d::Vec2> & verts, const cocos2d::Rect &Rect)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    CCASSERT(texture, "texture was not loaded properly");
    initWithTexture(texture);
    _polygonInfo = SpritePolygonCache::getInstance()->addSpritePolygonCache(filename, Rect, triangulate(verts));
    setAnchorPoint(Vec2(0.5,0.5));
    calculateUVandContentSize();
    #if CC_SPRITE_DEBUG_DRAW
        debugDraw();
    #endif
    return true;
}
Rect SpritePolygon::getTextRectFromTriangles(std::vector<cocos2d::V3F_C4B_T2F>& _verts)
{
//    CCASSERT(_polygonInfo, "cannot get texture rect because triangles were not defined");
    auto text = getTexture();
    int width = text->getPixelsWide();
    int height = text->getPixelsHigh();
    auto firstV = _verts[0];
    auto left = firstV.texCoords.u;
    auto right = firstV.texCoords.u;
    auto top = firstV.texCoords.v;
    auto bot = firstV.texCoords.v;
    for(std::vector<V3F_C4B_T2F>::const_iterator v = _verts.begin(); v < _verts.end(); v++)
    {
        if(v->texCoords.u < left)
        {
            left = v->texCoords.u;
        }
        else if (v->texCoords.u > right)
        {
            right = v->texCoords.u;
        }
        if(v->texCoords.v < bot)
        {
            bot = v->texCoords.v;
        }
        else if (v->texCoords.v > top)
        {
            top = v->texCoords.v;
        }
    }
    return Rect(left*width, bot*height, right*width, top*height);
}

bool SpritePolygon::initWithVerts(const std::string& filename,std::vector<cocos2d::V3F_C4B_T2F>& verts, std::vector<unsigned short>& indices)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    CCASSERT(texture, "texture was not loaded properly");


    initWithTexture(texture);
    auto _textureRect = getTextRectFromTriangles(verts);
    setContentSize(_textureRect.size/Director::getInstance()->getContentScaleFactor());
        setAnchorPoint(Vec2(0.5,0.5));
    _transformDirty = true;
    TrianglesCommand::Triangles triangles = {&verts[0], &indices[0], (ssize_t)verts.size(), (ssize_t)indices.size()};
    _polygonInfo = SpritePolygonCache::getInstance()->addSpritePolygonCache(filename, _textureRect, triangles);

#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    return true;
}

bool SpritePolygon::initWithRect(const std::string& filename, std::vector<cocos2d::Vec2>& verts, std::vector<unsigned short>& indices, const cocos2d::Rect& rect)
{
    CCASSERT(filename.size()>0, "Invalid filename for sprite");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    CCASSERT(texture, "texture was not loaded properly");
    initWithTexture(texture);
    //build v3f_c4b_t2f verts from vec2 vector
    vector<V3F_C4B_T2F> _verts;
    for(std::vector<Vec2>::const_iterator it = verts.begin(); it<verts.end(); it++)
    {
        auto v3 = Vec3(it->x, it->y, 0);
        auto c4b = Color4B::WHITE;
        auto t2f = Tex2F(0,0);
        V3F_C4B_T2F vert = {v3,c4b,t2f};
        _verts.push_back(vert);
    }

    TrianglesCommand::Triangles triangles = {&_verts[0], &indices[0], (ssize_t)_verts.size(), (ssize_t)indices.size()};
    _polygonInfo = SpritePolygonCache::getInstance()->addSpritePolygonCache(filename, rect, triangles);
    calculateUVandContentSize();
        setAnchorPoint(Vec2(0.5,0.5));
#if CC_SPRITE_DEBUG_DRAW
    debugDraw();
#endif
    return true;
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
    renderer->addCommand(&_tcmd);
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
    auto positions = new (std::nothrow) Vec2[_polygonInfo->_triangles.vertCount];
    Vec2 *pos = &positions[0];
    auto verts = _polygonInfo->_triangles.verts;
    auto end =  &verts[_polygonInfo->_triangles.vertCount];
    for(V3F_C4B_T2F *v = verts; v != end; pos++, v++)
    {
        pos->x = v->vertices.x;
        pos->y = v->vertices.y;
    }
    _debugDrawNode->drawPoints(positions, (unsigned int)_polygonInfo->_triangles.vertCount, 8, Color4F(0.0f, 1.0f, 1.0f, 1.0f));
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
