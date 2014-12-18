//
//  NVGDrawNode.h
//  player3
//
//  Created by htl on 14/12/8.
//
//

#ifndef __NVGDrawNode__
#define __NVGDrawNode__

#include <vector>
#include "NVGNode.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

typedef enum _NVGDrawType {
    NVGDrawType_None = 0,
    NVGDrawType_Point = 1,
    NVGDrawType_Line = 2,
    NVGDrawType_Rect = 3,
    NVGDrawType_Circle = 4,
    NVGDrawType_Bezier = 5,
    NVGDrawType_Arc = 6,
    
    NVGDrawType_MAX = 0x7FFFFFFF
}NVGDrawType;

class NVGDrawNode : public NVGNode {

public:
    
    static NVGDrawNode* create();
    
    /** 点 */
    void drawPoint(const Vec2& point, const Color4F &color);
    
    /** 多点 */
    void drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color);
    
    /** 线 */
    void drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** 矩形 */
    void drawRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    void drawRect(const Rect &rect, const Color4F &color);
    
    void drawRect(const Vec2 &lb, const Vec2 &lt, const Vec2 &rt, const Vec2& rb, const Color4F &color);
    
    /** 多边形(闭合或不闭合) */
    void drawPolygon(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon, const Color4F &color);
    
    /** 圆 */
    void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color);
    
    void drawCircle(const Vec2 &center, float radius, const Color4F &color);
    
    /** 曲线 */
    void drawQuadBezier(const Vec2 &origin, const Vec2 &control, const Vec2 &destination, const Color4F &color);
    
    /** draw a cubic bezier curve with color and number of segments */
    void drawCubicBezier(const Vec2 &origin, const Vec2 &control1, const Vec2 &control2, const Vec2 &destination, const Color4F &color);
    
    /** draw a dot at a position, with a given radius and color */
    void drawDot(const Vec2 &pos, float radius, const Color4F &color);
    
    void drawSolidRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    void drawSolidCircle(const Vec2& center, float radius, const Color4F &color);
    
    /** draw a segment with a radius and color */
    void drawArc(const Vec2 &pos, float radius, float a0, float a1, int dir, const Color4F &color);

    void drawSolidPolygon(const Vec2 *verts, int count, const Color4F &color);

    void setColor(const Color4F &color);
    void setFillColor(const Color4F &color);
    void setFill(bool bFill);
    void setLineColor(const Color4F &color);
    void setLineWidth(float width);
    void setRadius(float radius);
    void setOpacityf(float opacity);
    
    void addPoint(const Vec2 &point);
    void setPoints(const Vec2 *poli, unsigned int numberOfPoints);

    /** Clear the geometry in the node's buffer. */
    void clear();
    
    void onDraw(const Mat4 &transform, uint32_t flags);
    
    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

CC_CONSTRUCTOR_ACCESS:
    NVGDrawNode();
    virtual ~NVGDrawNode();
    
protected:
    
    NVGcolor clr4f2NVGClr(Color4F clr);
    
    CustomCommand _customCommand;
    
    NVGDrawType _drawType;
    std::vector<Vec2*> _points;
    NVGcolor _color;
    NVGcolor _colorFill;
    float _radius;
    float _arc0;
    float _arc1;
    float _dir;
    float _borderWidth;
    std::vector<Rect*> _rects;
    bool _bFill;
    bool _bClose;

};

NS_CC_EXT_END

#endif /* defined(__NVGDrawNode__) */
