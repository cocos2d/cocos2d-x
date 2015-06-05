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

#ifndef __PLATFOMR_CCNS_H__
#define __PLATFOMR_CCNS_H__

#include "math/CCGeometry.h"

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

/**
 * @brief @~english Returns a Core Graphics rectangle structure corresponding to the data in a given string.
 * @~chinese 将字符串转换为 Rect 实例。
 * @param str       @~english A string object whose contents are of the form "{{x,y},{w, h}}",
 *                  where x is the x coordinate, y is the y coordinate, w is the width, and h is the height.
 *                  These components can represent integer or float values.
 *                  An example of a valid string is "{{3,2},{4,5}}".
 *                  The string is not localized, so items are always separated with a comma.
 * @~chinese 一个格式为“{{x, y}, {w, h}}” 的字符串，
 * 其中 x 是 x 轴坐标，y 是 y 轴坐标；w 是宽度， h 是高度。
 * 这些数据可以是整数或者浮点数。
 * 例如："{ { 3,2 }, { 4,5 } }"。
 * 字符串不能本地化，数据用英文逗号分隔。
 * @return @~english A Core Graphics structure that represents a rectangle.
 *      If the string is not well-formed, the function returns Rect::ZERO.
 * @~chinese 一个 Rect 实例，如果字符串格式错误，函数返回 `Rect::ZERO`。
 */
Rect CC_DLL RectFromString(const std::string& str);

/**
 * @brief @~english Returns a Core Graphics point structure corresponding to the data in a given string.
 * @~chinese 将字符串转换为 Vec2 实例。
 * @param str   @~english A string object whose contents are of the form "{x,y}",
 *                  where x is the x coordinate and y is the y coordinate.
 *                  The x and y values can represent integer or float values.
 *                  An example of a valid string is "{3.0,2.5}".
 *                  The string is not localized, so items are always separated with a comma.
 * @~chinese 一个格式为 "{ x,y }" 的字符串，
 * 其中 x 是 x 轴坐标，y 是 y 轴坐标。
 * x 和 y 的值可以是整数或浮点值。
 * 例如："{ 3.0,2.5 }"。
 * 字符串不能本地化，数据用英文逗号分隔。
 * @return @~english A Core Graphics structure that represents a point.
 *      If the string is not well-formed, the function returns Vec2::ZERO.
 * @~chinese 一个 Vec2 实例。如果字符串格式错误，函数返回 `Vec2::ZERO`。
 */
Vec2 CC_DLL PointFromString(const std::string& str);

/**
 * @brief @~english Returns a Core Graphics size structure corresponding to the data in a given string.
 * @~chinese 返回一个 Size 实例。
 * @param str       @~english A string object whose contents are of the form "{w, h}",
 *                  where w is the width and h is the height.
 *                  The w and h values can be integer or float values.
 *                  An example of a valid string is "{3.0,2.5}".
 *                  The string is not localized, so items are always separated with a comma.
 * @~chinese 一个格式为 "{ w,h }" 的字符串，
 * w 表示宽度，h 表示高度高度。
 * w 和 h 值可以是整数或浮点值。
 * 例如："{ 3.0,2.5 }"。
 * 字符串不能本地化，数据用英文逗号分隔。
 * @return @~english A Core Graphics structure that represents a size.
 *      If the string is not well-formed, the function returns Size::ZERO.
 * @~chinese 一个 Size 实例。如果字符串格式错误，函数返回 `Size::ZERO`。
 */
Size CC_DLL SizeFromString(const std::string& str);

// end of data_structure group
/// @}

NS_CC_END

#endif // __PLATFOMR_CCNS_H__


