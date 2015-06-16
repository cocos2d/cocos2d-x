/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#ifndef __MATH_CCGEOMETRY_H__
#define __MATH_CCGEOMETRY_H__

#include <math.h>

#include "platform/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include "math/CCMath.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/**
@class Size
@brief
@~english A size, which has width and height, could be used to represent the size in 2D.
@~chinese Size包含宽度和高度，可以用来在2D空间表示大小。
*/
class CC_DLL Size
{
public:
    /**@~english Width of the Size. @~chinese 宽度。*/
    float width;
    /**@~english Height of the Size. @~chinese 高度。*/
    float height;
public:
    /**@~english Conversion from Vec2 to Size. @~chinese 从Vec2转换为Size。*/
    operator Vec2() const
    {
        return Vec2(width, height);
    }

public:
    /**
    @~english
    Constructor.
     * @~chinese 
     * 构造函数。
     */
    Size();
    /**
    @~english
    Constructor.
     * @~chinese 
     * 构造函数。
    @param width @~english Width of the size.
     * @~chinese 宽度。
    @param height @~english Height of the size.
     * @~chinese 高度。
     */
    Size(float width, float height);
    /**
    @~english
    Constructor.
     * @~chinese 
     * 拷贝构造函数。
     */
    Size(const Size& other);
    /**
    @~english
    Constructor.
     * @~chinese 
     * 构造函数, 从一个点进行转换。
    @param point @~english a point.
     * @~chinese 一个点。
     */
    explicit Size(const Vec2& point);

    /**
    @~english assign another value to this.
    @~chinese 赋值函数。
     * @js NA
     * @lua NA
     */
    Size& operator= (const Size& other);
    /**
    @~english assign another Vec2 value to this.
    @~chinese 将一个Vec2赋值给自己。
    @param point @~english A Vec2. @~chinese 一个Vec2数据。
     * @js NA
     * @lua NA
     */
    Size& operator= (const Vec2& point);
    /**
    @~english add another Size to this.
    @~chinese 加上一个值。
     * @js NA
     * @lua NA
     */
    Size operator+(const Size& right) const;
    /**
    @~english substract another Size to this.
    @~chinese 减去一个值。
     * @js NA
     * @lua NA
     */
    Size operator-(const Size& right) const;
    /**
    @~english scale the size by a.
    @~chinese 将Size放大a倍。
     * @js NA
     * @lua NA
     */
    Size operator*(float a) const;
    /**
    @~english shrink the size by a.
    @~chinese 将Size缩小a倍。
     * @js NA
     * @lua NA
     */
    Size operator/(float a) const;
    /**@~english
    Set the width and height of Size.
     * @~chinese 
     * 设置宽度和高度。
     * @js NA
     * @lua NA
     */
    void setSize(float width, float height);
    /**@~english
    Check if two size is the same.
     * @~chinese 
     * 检查两个Size是否相同。
     * @js NA
     */
    bool equals(const Size& target) const;
    /**@~english Size(0,0). @~chinese  等价于Size(0,0)。*/
    static const Size ZERO;
};

/**@~english Rectangle area. @~chinese 矩形区域。*/
class CC_DLL Rect
{
public:
    /**@~english Low left point of rect. @~chinese 矩形的左下角点。*/
    Vec2 origin;
    /**@~english Width and height of the rect. @~chinese 矩形的宽度和高度。*/
    Size  size;

public:
    /**@~english
    Constructor an empty Rect.
     * @~chinese 
     * 构造一个空的矩形。
     * @js NA
     */
    Rect();
    /**@~english
    Constructor a rect.
     * @~chinese 
     * 构造函数一个矩形。
     @param x @~english The x coordinate of low left point. @~chinese 左下角点的x坐标。
     @param y @~english The y coordinate of low left point. @~chinese 左下角点的y坐标。
     @param width @~english Width of rect. @~chinese rect的宽度。
     @param height @~english Height of the rect. @~chinese rect的高度。
     * @js NA
     */
    Rect(float x, float y, float width, float height);
    /**@~english
    Copy constructor.
     * @~chinese 
     * 拷贝构造函数。
     * @js NA
     * @lua NA
     */
    Rect(const Rect& other);
    /**
    @~english assign function.
    @~chinese 赋值函数。
     * @js NA
     * @lua NA
     */
    Rect& operator= (const Rect& other);
    /**@~english
    Set the x, y, width and height of Rect.
     * @~chinese 
     * 设置矩形的x,y,矩形的宽度和高度。
     * @js NA
     * @lua NA
     */
    void setRect(float x, float y, float width, float height);
    /**@~english
    Get the left of the rect.
     * @~chinese 
     * 得到矩形最小的X。
     * @js NA
     */
    float getMinX() const; /// return the leftmost x-value of current rect
    /**@~english
    Get the X coordinate of center point.
     * @~chinese 
     * 中心点的X坐标。
     * @js NA
     */
    float getMidX() const; /// return the midpoint x-value of current rect
    /**@~english
    Get the right of rect.
     * @~chinese 
     * 得到矩形最大的X。
     * @js NA
     */
    float getMaxX() const; /// return the rightmost x-value of current rect
    /**@~english
    Get the bottom of rect.
     * @~chinese 
     * 得到矩形最小的Y。
     * @js NA
     */
    float getMinY() const; /// return the bottommost y-value of current rect
    /**@~english
    Get the Y coordinate of center point.
     * @~chinese 
     * 中心点的Y坐标。
     * @js NA
     */
    float getMidY() const; /// return the midpoint y-value of current rect
    /**@~english
    Get top of rect.
     * @~chinese 
     * 得到矩形最大的X。
     * @js NA
     */
    float getMaxY() const; /// return the topmost y-value of current rect
    /**@~english
    Compare two rects.
     * @~chinese 
     * 比较两个矩形，看是否相等。
     * @js NA
     */
    bool equals(const Rect& rect) const;
    /**@~english
    Check if the points is contained in the rect.
     * @~chinese 
     * 检查一个点是否包含在矩形中。
     * @js NA
     */
    bool containsPoint(const Vec2& point) const;
    /**@~english
    Check the intersect status of two rects.
     * @~chinese 
     * 检查两个矩形是否相交。
     * @js NA
     */
    bool intersectsRect(const Rect& rect) const;
    /**@~english
    Check the intersect status of the rect and a circle.
     * @~chinese 
     * 检查的矩形和圆是否相交。
     * @js NA
     */
    bool intersectsCircle(const Vec2& center, float radius) const;
    /**@~english
    Get the min rect which can contain this and rect.
     * @~chinese 
     * 计算一个最小矩形,其可以包含this和参数rect矩形
     @param rect @~english another rect. @~chinese 另一个要包含的矩形。
     @return @~english the result rect. @~chinese 得到的矩形。
     * @js NA
     * @lua NA
     */
    Rect unionWithRect(const Rect & rect) const;
    /**
    @~english Compute the min rect which can contain this and rect, assign it to this. 
    @~chinese 计算一个最小矩形,其可以包含this和参数rect矩形,将其分配给自己。
    @param rect @~english another rect. @~chinese 另一个要包含的矩形。
    */
    void merge(const Rect& rect);
    /**@~english An empty Rect. @~chinese 一个空的矩形。*/
    static const Rect ZERO;
};

NS_CC_END

// end of base group
/// @}

#endif // __MATH_CCGEOMETRY_H__
