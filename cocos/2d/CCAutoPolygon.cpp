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

#include "CCAutoPolygon.h"
#include "poly2tri/poly2tri.h"
#include "CCDirector.h"
#include "CCTextureCache.h"
#include "external/clipper/clipper.h"
#include <algorithm>
#include <math.h>

USING_NS_CC;

PolygonInfo::PolygonInfo(const PolygonInfo& other):
triangles(),
isVertsOwner(true)
{
    triangles.verts = new V3F_C4B_T2F[other.triangles.vertCount];
    triangles.indices = new unsigned short[other.triangles.indexCount];
    triangles.vertCount = other.triangles.vertCount;
    triangles.indexCount = other.triangles.indexCount;
    memcpy(triangles.verts, other.triangles.verts, other.triangles.vertCount*sizeof(V3F_C4B_T2F));
    memcpy(triangles.indices, other.triangles.indices, other.triangles.indexCount*sizeof(unsigned short));
};
PolygonInfo::PolygonInfo(V3F_C4B_T2F_Quad *quad):
triangles(),
isVertsOwner(true)
{
    isVertsOwner = false;
    unsigned short *indices  = new unsigned short[6]{0,1,2, 3,2,1};
    triangles.indices = indices;
    triangles.vertCount = 4;
    triangles.indexCount = 6;
    triangles.verts = (V3F_C4B_T2F*)quad;
    
}
PolygonInfo::~PolygonInfo()
{
    if(nullptr != triangles.verts && isVertsOwner)
    {
        CC_SAFE_DELETE_ARRAY(triangles.verts);
    }
    
    if(nullptr != triangles.indices)
    {
        CC_SAFE_DELETE_ARRAY(triangles.indices);
    }
}



AutoPolygon::AutoPolygon(const std::string &filename)
:_image(nullptr)
,_data(nullptr)
,_filename("")
,_width(0)
,_height(0)
,_scaleFactor(0)
{
    _filename = filename;
    _image = new Image();
    _image->initWithImageFile(filename);
    CCASSERT(_image->getRenderFormat()==Texture2D::PixelFormat::RGBA8888, "unsupported format, currently only supports rgba8888");
    _data = _image->getData();
    _width = _image->getWidth();
    _height = _image->getHeight();
    _scaleFactor = Director::getInstance()->getContentScaleFactor();
}

AutoPolygon::~AutoPolygon()
{
    CC_SAFE_DELETE(_image);
}

std::vector<Vec2> AutoPolygon::trace(const Rect& rect, const float& threshold)
{
    Vec2 first = findFirstNoneTransparentPixel(rect);
    return marchSquare(rect, first, threshold);
}

Vec2 AutoPolygon::findFirstNoneTransparentPixel(const Rect& rect)
{
    Vec2 first;
    bool found;
    Vec2 i;
    for(i.y = rect.origin.y; i.y < rect.origin.y+rect.size.height; i.y++)
    {
        for(i.x = rect.origin.x; i.x < rect.origin.x+rect.size.height; i.x++)
        {
            if(getAlphaByPos(i))
            {
                found = true;
                break;
            }
        }
    }
    CCASSERT(found, "image is all transparent!");
    return i;
}

unsigned char AutoPolygon::getAlphaByIndex(const unsigned int& i)
{
//    CCASSERT(i < _width*_height, "coordinate is out of range.");
//    unsigned int x = i % (int)_rect.size.width;
//    unsigned int y = i / (int)_rect.size.width;
//     CCLOG("i=%d, x=%d,y=%d",i,x,y);
//    x += _rect.origin.x;
//    y += _height - _rect.origin.y - _rect.size.height;
//    y = _height - _rect.origin.y -_rect.size.height + y;
//    return getAlphaByPos(x, y);
    return *(_data+i*4+3);
}
unsigned char AutoPolygon::getAlphaByPos(const Vec2& i)
{
//    CCASSERT(x <= _width-1 && y <= _height-1, "coordinate is out of range.");
//    if (x<_rect.origin.x || x>_rect.origin.x+_rect.size.width
//        || y<_rect.origin.y || y>_rect.origin.y+_rect.size.height) {
//        return 0;
//    }
    return *(_data+((int)i.y*_width+(int)i.x)*4+3);
}

unsigned int AutoPolygon::getSquareValue(const unsigned int& x, const unsigned int& y, const Rect& rect, const float& threshold)
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
    /* because the rect is from bottom left, while the texure if from left top */
    Vec2 tl = Vec2(x-1, _height-(y-1));
    sv += (rect.containsPoint(tl) && getAlphaByPos(tl) > threshold)? 1 : 0;
    Vec2 tr = Vec2(x, _height-(y-1));
    sv += (rect.containsPoint(tr) && getAlphaByPos(tr) > threshold)? 2 : 0;
    Vec2 bl = Vec2(x-1, _height-y);
    sv += (rect.containsPoint(bl) && getAlphaByPos(bl) > threshold)? 4 : 0;
    Vec2 br = Vec2(x, _height-y);
    sv += (rect.containsPoint(br) && getAlphaByPos(br) > threshold)? 8 : 0;
    return sv;
}

std::vector<cocos2d::Vec2> AutoPolygon::marchSquare(const Rect& rect, const Vec2& start, const float& threshold)
{
    int stepx = 0;
    int stepy = 0;
    int prevx = 0;
    int prevy = 0;
    int startx = start.x;
    int starty = start.y;
    int curx = startx;
    int cury = starty;
    unsigned int count = 0;
    unsigned int totalPixel = _width*_height;
    bool problem = false;
    std::vector<int> case9s;
    std::vector<int> case6s;
    int i;
    std::vector<int>::iterator it;
    std::vector<cocos2d::Vec2> _points;
    do{
        int sv = getSquareValue(curx, cury, rect, threshold);
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
    return _points;
}

//void AutoPolygon::printPoints()
//{
//    for(auto p : _points)
//    {
//        CCLOG("%.1f %.1f", p.x, _height-p.y);
//    }
//}

float AutoPolygon::perpendicularDistance(const cocos2d::Vec2& i, const cocos2d::Vec2& start, const cocos2d::Vec2& end)
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
std::vector<cocos2d::Vec2> AutoPolygon::rdp(std::vector<cocos2d::Vec2> v, const float& optimization)
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
    if (dist>optimization)
    {
        std::vector<Vec2>::const_iterator begin = v.begin();
        std::vector<Vec2>::const_iterator end   = v.end();
        std::vector<Vec2> l1(begin, begin+index+1);
        std::vector<Vec2> l2(begin+index, end);
        
        std::vector<Vec2> r1 = rdp(l1, optimization);
        std::vector<Vec2> r2 = rdp(l2, optimization);
        
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
std::vector<Vec2> AutoPolygon::reduce(const std::vector<Vec2>& points, const float& epsilon)
{
    CCASSERT(points.size()>3, "points are just a triangle, no need further reduction");
    if(epsilon <= 0)
        return points;
    std::vector<Vec2> result = rdp(points, epsilon);
    auto last = result.back();
    
    if(last.y > result.front().y)
        result.front().y = last.y;
    result.pop_back();
    return result;
}

std::vector<Vec2> AutoPolygon::expand(const std::vector<Vec2>& points, const cocos2d::Rect &rect, const float& epsilon)
{
    ClipperLib::Path subj;
    ClipperLib::PolyTree solution;
    ClipperLib::Paths out;
    for(std::vector<Vec2>::const_iterator it = points.begin(); it<points.end(); it++)
    {
        subj << ClipperLib::IntPoint(it->x, it->y);
    }
    ClipperLib::ClipperOffset co;
    co.AddPath(subj, ClipperLib::jtMiter, ClipperLib::etClosedPolygon);
    co.Execute(solution, epsilon);

    //turn the result into simply polygon (AKA, fix overlap)
    ClipperLib::SimplifyPolygon(solution.Childs[0]->Contour, out);
    std::vector<Vec2> outPoints;
    auto end = out[0].end();
    for(std::vector<ClipperLib::IntPoint>::const_iterator pt = out[0].begin(); pt < end; pt++)
    {
        outPoints.push_back(Vec2(pt->X, pt->Y));
    }
    return outPoints;
}

bool AutoPolygon::isAConvexPoint(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2)
{
    return p1.cross(p2) >0 ? true : false;
}

TrianglesCommand::Triangles AutoPolygon::triangulate(const std::vector<Vec2>& points)
{
    CCASSERT(points.size()>=3, "the points size is less than 3.");
    std::vector<p2t::Point*> p2points;
    for(std::vector<Vec2>::const_iterator it = points.begin(); it<points.end(); it++)
    {
        p2t::Point * p = new p2t::Point(it->x, it->y);
        p2points.push_back(p);
    }
    p2t::CDT cdt(p2points);
    cdt.Triangulate();
    std::vector<p2t::Triangle*> tris = cdt.GetTriangles();
    
    V3F_C4B_T2F* verts= new V3F_C4B_T2F[points.size()];
    unsigned short* indices = new unsigned short[tris.size()*3];
    unsigned short idx = 0;
    unsigned short vdx = 0;

    for(std::vector<p2t::Triangle*>::const_iterator ite = tris.begin(); ite < tris.end(); ite++)
    {
        for(int i = 0; i < 3; i++)
        {
            auto p = (*ite)->GetPoint(i);
            auto v3 = Vec3(p->x, p->y, 0);
            bool found = false;
            int j;
            size_t length = vdx;
            for(j = 0; j < length; j++)
            {
                if(verts[j].vertices == v3)
                {
                    found = true;
                    break;
                }
            }
            if(found)
            {
                //if we found the same vertice, don't add to verts, but use the same vert with indices
                indices[idx] = j;
                idx++;
            }
            else
            {
                //vert does not exist yet, so we need to create a new one,
                auto c4b = Color4B::WHITE;
                auto t2f = Tex2F(0,0); // don't worry about tex coords now, we calculate that later
                V3F_C4B_T2F vert = {v3,c4b,t2f};
                verts[vdx] = vert;
                indices[idx] = vdx;
                idx++;
                vdx++;
            }
        }
    }
    for(auto j : p2points)
    {
        delete j;
    };
    TrianglesCommand::Triangles triangles = {verts, indices, vdx, idx};
    return triangles;
}

void AutoPolygon::calculateUV(V3F_C4B_T2F* verts, const ssize_t& count)
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
    
//    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(_filename);
    CCASSERT(_width && _height, "please specify width and height for this AutoPolygon instance");
    float texWidth  = _width/_scaleFactor;
    float texHeight = _height/_scaleFactor;

    
    auto end = &verts[count];
    for(auto i = verts; i != end; i++)
    {
        // for every point, offset with the centerpoint
        float u = i->vertices.x / texWidth;
        float v = (texHeight - i->vertices.y) / texHeight;
        i->texCoords.u = u;
        i->texCoords.v = v;
    }
}

PolygonInfo AutoPolygon::generateTriangles(const Rect& rect, const float& epsilon, const float& threshold)
{
    auto p = trace(rect, threshold);
    p = reduce(p, epsilon);
    p = expand(p, rect, epsilon);
    auto tri = triangulate(p);
    calculateUV(tri.verts, tri.vertCount);
    PolygonInfo ret = PolygonInfo();
    ret.triangles = tri;
    ret.filename = _filename;
    return ret;
}