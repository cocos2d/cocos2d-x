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
#include "cocos2d.h"
#include <algorithm>

USING_NS_CC;

MarchingSquare::MarchingSquare(const std::string &filename, const unsigned int threshold)
{
    _filename = filename;
    _threshold = threshold;
    Image *image = new Image();
    image->initWithImageFile(filename);
    CCASSERT(image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888, "unsupported format, currently only supports rgba8888");
    data = image->getData();
    width = image->getWidth();
    height = image->getHeight();
    scaleFactor = Director::getInstance()->getContentScaleFactor();
}

void MarchingSquare::trace()
{
    unsigned int first = findFirstNoneTransparentPixel();
    start = Vec2(first%width, first/width);
    marchSquare(start.x, start.y);
}

unsigned int MarchingSquare::findFirstNoneTransparentPixel()
{
    for(unsigned int i = 0; i < width*height; i++)
    {
        if(getAlphaAt(i) > _threshold)
        {
//            CCLOG("first non transparent is at x:%d, y%d", i%width, i/width);
            return i;
        }
    }
    throw "image is all transparent!";
}

unsigned char MarchingSquare::getAlphaAt(const unsigned int i)
{
    return *(data+i*4+3);
}
unsigned char MarchingSquare::getAlphaAt(const int x, const int y)
{
    if(x < 0 || y < 0 || x > width-1 || y > height-1)
        return 0;
    return *(data+(y*width+x)*4+3);
}

unsigned int MarchingSquare::getSquareValue(int x, int y)
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
    if(getAlphaAt(x-1, y-1) > _threshold)
        sv += 1;
    if(getAlphaAt(x,y-1) > _threshold)
        sv += 2;
    if(getAlphaAt(x-1, y) > _threshold)
        sv += 4;
    if(getAlphaAt(x, y) > _threshold)
        sv += 8;
    return sv;
}

void MarchingSquare::marchSquare(int startx, int starty)
{
    int stepx = 0;
    int stepy = 0;
    int prevx = 0;
    int prevy = 0;
    int curx = startx;
    int cury = starty;
    unsigned int count = 0;
    unsigned int totalPixel = width*height;
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
            case 0:
                CCLOG("case 0 at x:%d, y:%d, coming from %d, %d", curx, cury, prevx, prevy);
                throw "this shoudln't happen";
            case 15:
                CCLOG("case 15 at x:%d, y:%d, coming from %d, %d", curx, cury, prevx, prevy);
                throw "this shoudln't happen";
        }
        //little optimization
        // if previous direction is same as current direction,
        // then we should modify the last vec to current
        curx += stepx;
        cury += stepy;
        if(stepx == prevx && stepy == prevy)
        {
            points.back().x = (float)(curx) / scaleFactor;
            points.back().y = (float)(height-cury) / scaleFactor;
        }
        else if(problem)
        {
            //TODO: we triangulation cannot work collineer points, so we need to modify same point a little
            //TODO: maybe we can detect if we go into a hole and coming back the hole, we should extract those points and remove them
            points.back().x -= 0.00001;
            points.back().y -= 0.00001;
            points.push_back(Vec2((float)curx, (float)height-cury)/ scaleFactor);
        }
        else{
            points.push_back(Vec2((float)curx, (float)height-cury)/ scaleFactor);
        }

        count++;
        prevx = stepx;
        prevy = stepy;
        problem = false;
        if(count > totalPixel)
            throw "oh no, marching square cannot find starting position";
    } while(curx != startx || cury != starty);
}

void MarchingSquare::printPoints()
{
    for(auto p : points)
    {
        CCLOG("%.1f %.1f", p.x, height-p.y);
    }
}

float MarchingSquare::perpendicularDistance(cocos2d::Vec2 ii, cocos2d::Vec2 ss, cocos2d::Vec2 ee)
{
    float res;
    float slope;
    float intercept;
    
    if(ss.x == ee.x)
    {
        res = fabsf(ii.x- ee.x);
    }
    else if (ss.y == ee.y)
    {
        res = fabsf(ii.y - ee.y);
    }
    else{
        slope = (ee.y - ss.y) / (ee.x - ss.x);
        intercept = ss.y - (slope*ss.x);
        res = fabsf(slope * ii.x - ii.y + intercept) / sqrtf(powf(slope, 2)+1);
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
    if (dist>epsilon)
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
void MarchingSquare::optimize(float level)
{
    if(level <= 0 || points.size()<4)
        return;
    epsilon = level;
    points = rdp(points);
    auto last = points.back();
    
    if(last.y > points.front().y)
        points.front().y = last.y;
    points.pop_back();
    
    //delete the last point, because its almost the same as the starting point
//    CCLOG("%.1f, %.1f, %.1f, %.1f", points[0].x, points[0].y, points.back().x, points.back().y);
}