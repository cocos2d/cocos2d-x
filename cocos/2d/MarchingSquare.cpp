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

#include "MarchingSquare.h"
#include <algorithm>
#include <math.h>

USING_NS_CC;

MarchingSquare::MarchingSquare(const std::string &filename, const unsigned int threshold)
:_image(nullptr)
,_data(nullptr)
,_filename("")
,_threshold(0)
,_width(0)
,_height(0)
,_scaleFactor(0)
,_epsilon(0)
{
    _filename = filename;
    _threshold = threshold;
    _image = new Image();
    _image->initWithImageFile(filename);
    CCASSERT(_image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888, "unsupported format, currently only supports rgba8888");
    _data = _image->getData();
    _width = _image->getWidth();
    _height = _image->getHeight();
    _scaleFactor = Director::getInstance()->getContentScaleFactor();
}

MarchingSquare::~MarchingSquare()
{
    CC_SAFE_DELETE(_image);
    _points.clear();
}

void MarchingSquare::trace(const Rect& rect)
{
    unsigned int first = findFirstNoneTransparentPixel();
    auto start = Vec2(first%_width, first/_width);
    marchSquare(start.x, start.y);
}

unsigned int MarchingSquare::findFirstNoneTransparentPixel()
{
    unsigned int first = -1;
    for(unsigned int i = 0; i < _width*_height; i++)
    {
        if(getAlphaByIndex(i) > _threshold)
        {
            first = i;
            break;
        }
    }
    CCASSERT(-1 != first, "image is all transparent!");
    return first;
}

unsigned char MarchingSquare::getAlphaByIndex(const unsigned int& i)
{
    CCASSERT(i < _width*_height, "coordinate is out of range.");
    return *(_data+i*4+3);
}
unsigned char MarchingSquare::getAlphaByPos(const unsigned int& x, const unsigned int& y)
{
    CCASSERT(x < _width-1 && y < _height-1, "coordinate is out of range.");
    return *(_data+(y*_width+x)*4+3);
}

unsigned int MarchingSquare::getSquareValue(const unsigned int& x, const unsigned int& y)
{
    /*
     checking the 2x2 pixel grid, assigning these values to each pixel, if not transparent
     +---+---+
     | 1 | 2 |
     +---+---+
     | 4 | 8 | <- current pixel (curx,cury)
     +---+---+
     */
    unsigned int sv = 0;
    if(getAlphaByPos(x-1, y-1) > _threshold)
        sv += 1;
    if(getAlphaByPos(x,y-1) > _threshold)
        sv += 2;
    if(getAlphaByPos(x-1, y) > _threshold)
        sv += 4;
    if(getAlphaByPos(x, y) > _threshold)
        sv += 8;
    return sv;
}

void MarchingSquare::marchSquare(const unsigned int& startx, const unsigned int& starty)
{
    int stepx = 0;
    int stepy = 0;
    int prevx = 0;
    int prevy = 0;
    int curx = startx;
    int cury = starty;
    unsigned int count = 0;
    unsigned int totalPixel = _width*_height;
    bool problem = false;
    std::vector<int> case9s;
    std::vector<int> case6s;
    int i;
    std::vector<int>::iterator it;
    do{
        int sv = getSquareValue(curx, cury);
        switch(sv){

            case 1:
            case 5:
            case 13:
                /* going UP with these cases:
                 1          5           13
                 +---+---+  +---+---+  +---+---+ 
                 | 1 |   |  | 1 |   |  | 1 |   | 
                 +---+---+  +---+---+  +---+---+ 
                 |   |   |  | 4 |   |  | 4 | 8 | 
                 +---+---+  +---+---+  +---+---+
                 */
                stepx = 0;
                stepy = -1;
                break;

                
            case 8:
            case 10:
            case 11:
                /* going DOWN with these cases:
                 8          10          11
                 +---+---+  +---+---+   +---+---+
                 |   |   |  |   | 2 |   | 1 | 2 |
                 +---+---+  +---+---+   +---+---+
                 |   | 8 |  |   | 8 |   |   | 8 |
                 +---+---+  +---+---+  	+---+---+
                 */
                stepx = 0;
                stepy = 1;
                break;

                
            case 4:
            case 12:
            case 14:
                /* going LEFT with these cases:
                 4          12          14
                 +---+---+  +---+---+   +---+---+
                 |   |   |  |   |   |   |   | 2 |
                 +---+---+  +---+---+   +---+---+
                 | 4 |   |  | 4 | 8 |   | 4 | 8 |
                 +---+---+  +---+---+  	+---+---+
                 */
                stepx = -1;
                stepy = 0;
                break;
                
                
            case 2 :
            case 3 :
            case 7 :
                /* going RIGHT with these cases:
                 2          3           7        
                 +---+---+  +---+---+   +---+---+
                 |   | 2 |  | 1 | 2 |   | 1 | 2 |
                 +---+---+  +---+---+   +---+---+
                 |   |   |  |   |   |   | 4 |   |
                 +---+---+  +---+---+  	+---+---+
                 */
                stepx=1;
                stepy=0;
                break;
            case 9 :
                /*
                 +---+---+
                 | 1 |   |
                 +---+---+
                 |   | 8 |
                 +---+---+
                 this should normaly go UP, but if we already been here, we go down
                */
                //find index from xy;
                i = getIndexFromPos(curx, cury);
                it = find (case9s.begin(), case9s.end(), i);
                if (it != case9s.end())
                {
                    //found, so we go down, and delete from case9s;
                    stepx = 0;
                    stepy = 1;
                    case9s.erase(it);
                    problem = true;
                }
                else
                {
                    //not found, we go up, and add to case9s;
                    stepx = 0;
                    stepy = -1;
                    case9s.push_back(i);
                }
                break;
            case 6 :
                /*
                 6
                 +---+---+
                 |   | 2 |
                 +---+---+
                 | 4 |   |
                 +---+---+
                 this normally go RIGHT, but if its coming from UP, it should go LEFT
                 */
                i = getIndexFromPos(curx, cury);
                it = find (case6s.begin(), case6s.end(), i);
                if (it != case6s.end())
                {
                    //found, so we go down, and delete from case9s;
                    stepx = -1;
                    stepy = 0;
                    case6s.erase(it);
                    problem = true;
                }
                else{
                    //not found, we go up, and add to case9s;
                    stepx = 1;
                    stepy = 0;
                    case6s.push_back(i);
                }
                break;
            default:
                CCLOG("this shouldn't happen.");
        }
        //little optimization
        // if previous direction is same as current direction,
        // then we should modify the last vec to current
        curx += stepx;
        cury += stepy;
        if(stepx == prevx && stepy == prevy)
        {
            _points.back().x = (float)(curx) / _scaleFactor;
            _points.back().y = (float)(_height-cury) / _scaleFactor;
        }
        else if(problem)
        {
            //TODO: we triangulation cannot work collineer points, so we need to modify same point a little
            //TODO: maybe we can detect if we go into a hole and coming back the hole, we should extract those points and remove them
            _points.back().x -= 0.00001;
            _points.back().y -= 0.00001;
            _points.push_back(Vec2((float)curx, (float)_height-cury)/ _scaleFactor);
        }
        else{
            _points.push_back(Vec2((float)curx, (float)_height-cury)/ _scaleFactor);
        }

        count++;
        prevx = stepx;
        prevy = stepy;
        problem = false;
        CCASSERT(count <= totalPixel, "oh no, marching square cannot find starting position");
    } while(curx != startx || cury != starty);
}

void MarchingSquare::printPoints()
{
    for(auto p : _points)
    {
        CCLOG("%.1f %.1f", p.x, _height-p.y);
    }
}

float MarchingSquare::perpendicularDistance(const cocos2d::Vec2& i, const cocos2d::Vec2& start, const cocos2d::Vec2& end)
{
    float res;
    float slope;
    float intercept;
    
    if(start.x == end.x)
    {
        res = fabsf(i.x- end.x);
    }
    else if (start.y == end.y)
    {
        res = fabsf(i.y - end.y);
    }
    else{
        slope = (end.y - start.y) / (end.x - start.x);
        intercept = start.y - (slope*start.x);
        res = fabsf(slope * i.x - i.y + intercept) / sqrtf(powf(slope, 2)+1);
    }
    return res;
}
std::vector<cocos2d::Vec2> MarchingSquare::rdp(std::vector<cocos2d::Vec2> v)
{
    if(v.size() < 3)
        return v;
    
    int index = -1;
    float dist = 0;
    //not looping first and last point
    for(int i = 1; i < v.size()-1; i++)
    {
        float cdist = perpendicularDistance(v[i], v.front(), v.back());
        if(cdist > dist)
        {
            dist = cdist;
            index = i;
        }
    }
    if (dist>_epsilon)
    {
        std::vector<Vec2>::const_iterator begin = v.begin();
        std::vector<Vec2>::const_iterator end   = v.end();
        std::vector<Vec2> l1(begin, begin+index+1);
        std::vector<Vec2> l2(begin+index, end);
        
        std::vector<Vec2> r1 = rdp(l1);
        std::vector<Vec2> r2 = rdp(l2);
        
        r1.insert(r1.end(), r2.begin()+1, r2.end());
        return r1;
    }
    else {
        std::vector<Vec2> ret;
        ret.push_back(v.front());
        ret.push_back(v.back());
        return ret;
    }
}
void MarchingSquare::optimize(const float& optimization)
{
    if(optimization <= 0 || _points.size()<4)
        return;
    _epsilon = optimization;
    _points = rdp(_points);
    auto last = _points.back();
    
    if(last.y > _points.front().y)
        _points.front().y = last.y;
    _points.pop_back();
}

void MarchingSquare::expand(const cocos2d::Rect &rect, const float& optimization)
{
    std::vector<cocos2d::Vec2> offsets;
    size_t length = _points.size();
    Vec2 v1,v2,v3;
    for (int i=0; i<length; i++) {
        if (i == 0) {
            v1.set(_points[i]-_points[length-1]);
            v2.set(_points[i]-_points[i+1]);
        }
        else if(i == length-1){
            v1.set(_points[i]-_points[i-1]);
            v2.set(_points[i]-_points[0]);
        }
        else{
            v1.set(_points[i]-_points[i-1]);
            v2.set(_points[i]-_points[i+1]);
        }
        v1.normalize();
        v2.normalize();
        v3 = isAConvexPoint(v1, -v2)? (v1 + v2) : (-v1-v2);
        v3.normalize();
        offsets.push_back(v3);
     }
    for (int i=0; i<length; i++) {
        _points[i].x = _points[i].x + offsets[i].x * optimization;
        _points[i].y = _points[i].y + offsets[i].y * optimization;
        _points[i].clamp(rect.origin, rect.origin+rect.size);
    }
}

bool MarchingSquare::isAConvexPoint(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2)
{
    if(p1.cross(p2)>0)
        return true;
    else
        return false;
}