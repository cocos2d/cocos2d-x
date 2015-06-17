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

#ifndef COCOS_2D_SpritePolygon_H__
#define COCOS_2D_SpritePolygon_H__

#include <vector>
#include "platform/CCPlatformMacros.h"
#include "2d/CCNode.h"
#include "renderer/CCTrianglesCommand.h"
#include "CCDrawNode.h"
#include "SpritePolygonCache.h"

NS_CC_BEGIN

namespace experimental{

class CC_DLL SpritePolygon : public cocos2d::Node
{
public:
    //create with manually created vertices, color and uv and
    static SpritePolygon *create(const std::string&, std::vector<cocos2d::V3F_C4B_T2F>&, std::vector<unsigned short>&);
    bool initWithVerts(const std::string&, std::vector<cocos2d::V3F_C4B_T2F>&, std::vector<unsigned short>&);

    //create from list of vertices, with texture rect, and triangle indices, UV is calculated from the texture rect
    static SpritePolygon *create(const std::string&, std::vector<cocos2d::Vec2>&, std::vector<unsigned short>&, const cocos2d::Rect&rect = cocos2d::Rect::ZERO);
    bool initWithRect(const std::string&, std::vector<cocos2d::Vec2>&, std::vector<unsigned short>&, const cocos2d::Rect&rect = cocos2d::Rect::ZERO);
    
//    //create from ordered list of vertices, with texture rect, Triangles and UV is calculated on the fly
    static SpritePolygon *create(const std::string&, std::vector<cocos2d::Vec2>&,  const cocos2d::Rect& rect = cocos2d::Rect::ZERO);
    bool initWithPoly2tri(const std::string&, std::vector<cocos2d::Vec2>&,  const cocos2d::Rect&);
    
    //create from a texture (rect), and automatically trace and optimize the points.
    //not recommended for production, its better to use the vec2 list for better performance
    static SpritePolygon *create(const std::string&, const cocos2d::Rect& rect = cocos2d::Rect::ZERO, float optimization = -1);
    bool initWithMarching(const std::string &file, const cocos2d::Rect &rect, float optimization);
    bool initWithCache(const std::string &file, SpritePolygonInfo *info);
    
    bool initWithTexture(cocos2d::Texture2D *texture);
    
    virtual void setTexture(const std::string &filename );
    virtual void setTexture(cocos2d::Texture2D *texture);
    
    /** returns the Texture2D object used by the sprite */
    virtual cocos2d::Texture2D* getTexture(){return _texture;};
    const float getArea();
    const ssize_t getTrianglesCount(){return _polygonInfo->_triangles.indexCount/3;};
    const ssize_t getVertCount(){return _polygonInfo->_triangles.vertCount;};
    
    void showDebug(const bool val);
protected:
    SpritePolygon()
        : _debugDrawNode(nullptr)
        , _texture(nullptr)
        , _polygonInfo(nullptr)
    {

    }

    cocos2d::DrawNode *_debugDrawNode;
    void debugDraw();
    
    void calculateUVandContentSize();
    
    cocos2d::TrianglesCommand               _tcmd;
    cocos2d::BlendFunc                      _blendFunc;
    cocos2d::Texture2D                     *_texture;
    SpritePolygonInfo                          *_polygonInfo;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    
    cocos2d::Rect getTextRectFromTriangles(std::vector<cocos2d::V3F_C4B_T2F>& verts);
    
    //======Triangulation
    cocos2d::TrianglesCommand::Triangles triangulate(std::vector<cocos2d::Vec2> & verts);
    
    
    //TODO: move those to ccUtils

};
}

NS_CC_END

#endif // #ifndef COCOS_2D_SpritePolygon_H__
