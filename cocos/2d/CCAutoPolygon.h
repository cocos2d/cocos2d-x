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

#ifndef COCOS_2D_CCAUTOPOLYGON_H__
#define COCOS_2D_CCAUTOPOLYGON_H__

#include <string>
#include <vector>
#include "platform/CCImage.h"
#include "renderer/CCTrianglesCommand.h"

NS_CC_BEGIN

class CC_DLL PolygonInfo
{
public:
    PolygonInfo():
    triangles(),
    isVertsOwner(true),
    rect()
    {
    };
    PolygonInfo(const PolygonInfo& other);
    
    PolygonInfo& operator= (const PolygonInfo &other);
    ~PolygonInfo();
    
    void setQuad(V3F_C4B_T2F_Quad *quad);
    
    Rect rect;
    std::string filename;
    TrianglesCommand::Triangles triangles;
    
    const unsigned int getVertCount() const;
    const float getArea() const;
    
protected:
    bool isVertsOwner;
};

class CC_DLL AutoPolygon
{
public:
    AutoPolygon(const std::string &filename);
    AutoPolygon();
    ~AutoPolygon();
    
    //using Ramer–Douglas–Peucker algorithm
    std::vector<Vec2> trace(const cocos2d::Rect& rect, const float& threshold = 0.0);
    std::vector<Vec2> reduce(const std::vector<Vec2>& points, const Rect& rect, const float& epsilon = 2.0);
    std::vector<Vec2> expand(const std::vector<Vec2>& points, const Rect& rect, const float& epsilon);
    TrianglesCommand::Triangles triangulate(const std::vector<Vec2>& points);
    void calculateUV(const Rect& rect, V3F_C4B_T2F* verts, const ssize_t& count);
    
    PolygonInfo generateTriangles(const Rect& rect = Rect::ZERO, const float& epsilon = 2.0, const float& threshold = 0.05);
    static PolygonInfo generatePolygon(const std::string& filename, const Rect& rect = Rect::ZERO, const float epsilon = 2.0, const float threshold = 0.05);
protected:
    Vec2 findFirstNoneTransparentPixel(const Rect& rect, const float& threshold);
    std::vector<cocos2d::Vec2> marchSquare(const Rect& rect, const Vec2& first, const float& threshold);
    unsigned int getSquareValue(const unsigned int& x, const unsigned int& y, const Rect& rect, const float& threshold);

    unsigned char getAlphaByIndex(const unsigned int& i);
    unsigned char getAlphaByPos(const Vec2& i);

    int getIndexFromPos(const unsigned int& x, const unsigned int& y){return y*_width+x;};
    cocos2d::Vec2 getPosFromIndex(const unsigned int& i){return cocos2d::Vec2(i%_width, i/_width);};

    std::vector<cocos2d::Vec2> rdp(std::vector<cocos2d::Vec2> v, const float& optimization);
    float perpendicularDistance(const cocos2d::Vec2& i, const cocos2d::Vec2& start, const cocos2d::Vec2& end);

    bool isAConvexPoint(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2);
    //real rect is the size that is in scale with the texture file
    Rect getRealRect(const Rect& rect);
    
    Image* _image;
    unsigned char * _data;
    std::string _filename;
    unsigned int _width;
    unsigned int _height;
    float _scaleFactor;
    unsigned int _threshold;
};

NS_CC_END

#endif // #ifndef COCOS_2D_CCAUTOPOLYGON_H__