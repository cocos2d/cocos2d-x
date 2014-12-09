//
//  NVGDrawNode.cpp
//  player3
//
//  Created by htl on 14/12/8.
//
//

#include "NVGDrawNode.h"

NS_CC_EXT_BEGIN

NVGDrawNode::NVGDrawNode()
: _radius(0)
, _drawType(NVGDrawType_None) {
    
}

NVGDrawNode::~NVGDrawNode() {
    
}

NVGDrawNode* NVGDrawNode::create() {
    NVGDrawNode* ret = new (std::nothrow) NVGDrawNode();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}


void NVGDrawNode::onDraw(const Mat4 &transform, uint32_t flags) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    NVGcontext *nvg = getNVGCtx();
    nvgBeginFrame(nvg, visibleSize.width, visibleSize.height, 1);
    
    //   [a c e]
    //   [b d f]
    //   [0 0 1]
    nvgTransform(nvg, transform.m[0], transform.m[1], transform.m[4], transform.m[5], transform.m[12], transform.m[13]);

    nvgBeginPath(nvg);

    switch (_drawType) {
        case NVGDrawType_Point: {
            for (int i = 0; i < _points.size(); i++) {
                nvgCircle(nvg, _points.at(i)->x, visibleSize.height - _points.at(i)->y, 1);
            }
            break;
        }
        case NVGDrawType_Line: {
            if (_points.size() < 2) {
                break;
            }
            nvgMoveTo(nvg, _points.at(0)->x, visibleSize.height - _points.at(0)->y);
            for (int i = 1; i < _points.size(); i++) {
                nvgLineTo(nvg, _points.at(i)->x, visibleSize.height - _points.at(i)->y);
            }
            nvgClosePath(nvg);
            break;
        }
        case NVGDrawType_Rect: {
            for (int i = 0; i < _rects.size(); i++) {
                nvgRect(nvg, _rects.at(i)->origin.x, visibleSize.height - _rects.at(i)->origin.y - _rects.at(i)->size.height, _rects.at(i)->size.width, _rects.at(i)->size.height);
            }
            break;
        }
        case NVGDrawType_Circle: {
            for (int i = 0; i < _points.size(); i++) {
                nvgCircle(nvg, _points.at(i)->x, visibleSize.height - _points.at(i)->y, _radius);
            }
            break;
        }
        case NVGDrawType_Bezier: {
            if (3 != _points.size() && 4 != _points.size()) {
                break;
            }
            nvgMoveTo(nvg, _points.at(0)->x, visibleSize.height - _points.at(0)->y);
            if (3 == _points.size()) {
                nvgQuadTo(nvg, _points.at(1)->x, visibleSize.height - _points.at(1)->y, _points.at(2)->x, visibleSize.height - _points.at(2)->y);
            } else {
                nvgBezierTo(nvg, _points.at(1)->x, visibleSize.height - _points.at(1)->y, _points.at(2)->x, visibleSize.height - _points.at(2)->y, _points.at(3)->x, visibleSize.height - _points.at(3)->y);
            }

            break;
        }
        case NVGDrawType_Arc: {
            nvgArc(nvg, _points.at(0)->x, visibleSize.height - _points.at(0)->y, _radius, _arc0, _arc1, _dir);
            break;
        }
        default: {
            break;
        }
    }

    if (_colorFill.a >= 0) {
        nvgFillColor(nvg, _colorFill);
        nvgFill(nvg);
    } else {
        nvgStrokeColor(nvg, _color);
        nvgStroke(nvg);
    }
    if (_bDrawStroke) {
        nvgStrokeWidth(nvg, _borderWidth);
        nvgStrokeColor(nvg, _color);
        nvgStroke(nvg);
    }
    
    nvgEndFrame(getNVGCtx());
    
    GL::bindTexture2D(0);
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_NONE);
    GL::useProgram(0);
}

void NVGDrawNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(NVGDrawNode::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void NVGDrawNode::drawPoint(const Vec2& point, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Point;
    _points.push_back(new Vec2(point));
    _radius = 1;
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Point;
    for (int i = 0; i < numberOfPoints; i++, position++) {
        _points.push_back(new Vec2(*position));
    }
    _radius = 1;
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Line;
    _points.push_back(new Vec2(origin));
    _points.push_back(new Vec2(destination));
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color) {
    _points.clear();
    _rects.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Rect;
    _rects.push_back(new Rect(origin.x, origin.y, destination.x - origin.x, destination.y - origin.y));
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawPoly(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Line;
    for (int i = 0; i < numberOfPoints; i++, poli++) {
        _points.push_back(new Vec2(*poli));
    }
    _radius = 1;
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Circle;
    _points.push_back(new Vec2(center));
    _radius = radius;
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawCircle(const Vec2 &center, float radius, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Circle;
    _points.push_back(new Vec2(center));
    _radius = radius;
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawQuadBezier(const Vec2 &origin, const Vec2 &control, const Vec2 &destination, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Bezier;
    _points.push_back(new Vec2(origin));
    _points.push_back(new Vec2(control));
    _points.push_back(new Vec2(destination));
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

/** draw a cubic bezier curve with color and number of segments */
void NVGDrawNode::drawCubicBezier(const Vec2 &origin, const Vec2 &control1, const Vec2 &control2, const Vec2 &destination, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Bezier;
    _points.push_back(new Vec2(origin));
    _points.push_back(new Vec2(control1));
    _points.push_back(new Vec2(control2));
    _points.push_back(new Vec2(destination));
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

/** draw a dot at a position, with a given radius and color */
void NVGDrawNode::drawDot(const Vec2 &pos, float radius, const Color4F &color) {
    drawCircle(pos, radius, color);
    _colorFill = clr4f2NVGClr(color);
}

void NVGDrawNode::drawRect(const Vec2 &lb, const Vec2 &lt, const Vec2 &rt, const Vec2& rb, const Color4F &color) {
    _points.clear();
    _rects.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Rect;
    _rects.push_back(new Rect(lb.x, lb.y, rt.x - lb.x, rt.y - lb.y));
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

void NVGDrawNode::drawSolidRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color) {
    drawRect(origin, destination, color);
    _colorFill = clr4f2NVGClr(color);
}

void NVGDrawNode::drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, const Color4F &color) {
    drawPoly(poli, numberOfPoints, true, color);
    _colorFill = clr4f2NVGClr(color);
}

void NVGDrawNode::drawSolidCircle(const Vec2& center, float radius, const Color4F &color) {
    drawCircle(center, radius, color);
    _colorFill = clr4f2NVGClr(color);
}

/** draw a segment with a radius and color */
void NVGDrawNode::drawArc(const Vec2 &pos, float radius, float a0, float a1, int dir, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Arc;
    _points.push_back(new Vec2(pos));
    _radius = radius;
    _color = clr4f2NVGClr(color);
    _arc0 = nvgDegToRad(a0);
    _arc1 = nvgDegToRad(a1);
    if (NVG_CW == dir) {
        _dir = NVG_CW;
    } else {
        _dir = NVG_CCW;
    }
    _colorFill.a = -1;
}

/** draw a polygon with a fill color and line color
 * @code
 * When this function bound into js or lua,the parameter will be changed
 * In js: var drawPolygon(var Arrayofpoints, var fillColor, var width, var borderColor)
 * In lua:local drawPolygon(local pointTable,local tableCount,local fillColor,local width,local borderColor)
 * @endcode
 */
void NVGDrawNode::drawPolygon(const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor) {
    _points.clear();
    _drawType = NVGDrawType_Line;
    for (int i = 0; i < count; i++) {
        _points.push_back(new Vec2(verts[i]));
    }
    _color = clr4f2NVGClr(borderColor);
    _colorFill = clr4f2NVGClr(fillColor);
    _borderWidth = borderWidth;
    _bDrawStroke = true;
}

/** draw a triangle with color */
void NVGDrawNode::drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color) {
    _points.clear();
    _bDrawStroke = false;
    _drawType = NVGDrawType_Line;
    _points.push_back(new Vec2(p1));
    _points.push_back(new Vec2(p2));
    _points.push_back(new Vec2(p3));
    _color = clr4f2NVGClr(color);
    _colorFill.a = -1;
}

/** Clear the geometry in the node's buffer. */
void NVGDrawNode::clear() {
    _points.clear();
    _rects.clear();
    _drawType = NVGDrawType_None;
    _colorFill.a = -1;
}

NVGcolor NVGDrawNode::clr4f2NVGClr(Color4F clr) {
    NVGcolor nvgClr;
    nvgClr.a = clr.a;
    nvgClr.r = clr.r;
    nvgClr.g = clr.g;
    nvgClr.b = clr.b;
    
    return nvgClr;
}

NS_CC_EXT_END

