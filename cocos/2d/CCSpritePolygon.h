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

#ifndef COCOS_2D_CCSpritePolygon_H__
#define COCOS_2D_CCSpritePolygon_H__

#include "CCNode.h"
#include "CCDrawNode.h"
#include "CCSpritePolygonCache.h"

NS_CC_BEGIN

namespace experimental{

class CC_DLL SpritePolygon : public cocos2d::Node
{
public:
    static SpritePolygon *create(const std::string& file, const cocos2d::Rect& rect = cocos2d::Rect::ZERO, const float optimization = -1);
    bool initWithxxx(const std::string& file, const cocos2d::Rect& rect, const float optimization);
    bool initWithTexture(cocos2d::Texture2D *texture);
    
    virtual void setTexture(const std::string &file );
    virtual void setTexture(cocos2d::Texture2D *texture);
    
    virtual cocos2d::Texture2D* getTexture(){return _texture;};
    const float getArea();
    const ssize_t getTrianglesCount(){return _polygonInfo->triangles.indexCount/3;};
    const ssize_t getVertCount(){return _polygonInfo->triangles.vertCount;};
    
    void showDebug(const bool val);
protected:
    SpritePolygon()
        : _debugDrawNode(nullptr)
        , _texture(nullptr)
        , _polygonInfo(nullptr)
    {

    }
    ~SpritePolygon();

    cocos2d::DrawNode *_debugDrawNode;
    void debugDraw();
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    
    cocos2d::TrianglesCommand _tcmd;
    cocos2d::BlendFunc _blendFunc;
    cocos2d::Texture2D *_texture;
    SpritePolygonInfo *_polygonInfo;
};
}

NS_CC_END

#endif // #ifndef COCOS_2D_CCSpritePolygon_H__
