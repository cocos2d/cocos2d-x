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

#ifndef COCOS_2D_MARCHINGSQUARE_H__
#define COCOS_2D_MARCHINGSQUARE_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include "base/CCConsole.h"
#include "platform/CCPlatformMacros.h"
#include "math/Vec2.h"

NS_CC_BEGIN

class CC_DLL MarchingSquare
{
public:
    MarchingSquare(const std::string &filename, const unsigned int threshold = 0);
    ~MarchingSquare();
    //TODO: should return list of vec2s
    void trace();
    void setThreshold(unsigned int threshold){_threshold = threshold;};
    unsigned int getThreshold(){return _threshold;};
    ssize_t getVecCount(){return _points.size();};
    std::vector<cocos2d::Vec2> getPoints(){return _points;};
    void printPoints();
    //using Ramer–Douglas–Peucker algorithm
    void optimize(const cocos2d::Rect &rect, float level = 0);
    void expand(const cocos2d::Rect &rect, float level = 0);
    
protected:
    unsigned int findFirstNoneTransparentPixel();
    void marchSquare(int startx, int starty);
    unsigned int getSquareValue(int x, int y);

    unsigned char getAlphaAt(const unsigned int i);
    unsigned char getAlphaAt(const int x, const int y);

    int getIndexFromPos(int x, int y){return y*_width+x;};
    cocos2d::Vec2 getPosFromIndex(int i){return cocos2d::Vec2(i%_width, i/_width);};

    std::vector<cocos2d::Vec2> rdp(std::vector<cocos2d::Vec2> v);
    float perpendicularDistance(cocos2d::Vec2 i, cocos2d::Vec2 start, cocos2d::Vec2 end);

    bool isAConvexPoint(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2);
    
    cocos2d::Image* _image;
    unsigned char * _data;
    std::string _filename;
    unsigned int _width;
    unsigned int _height;
    unsigned int _threshold;
    std::vector<cocos2d::Vec2> _points;
    float _epsilon;
    float _scaleFactor;
};

NS_CC_END

#endif // #ifndef COCOS_2D_MARCHINGSQUARE_H__