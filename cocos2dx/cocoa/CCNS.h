/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCGeometry.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

/**
@brief Returns a Core Graphics rectangle structure corresponding to the data in a given string.
@param pszContent   A string object whose contents are of the form "{{x,y},{w, h}}",
                    where x is the x coordinate, y is the y coordinate, w is the width, and h is the height.
                    These components can represent integer or float values.
                    An example of a valid string is "{{3,2},{4,5}}".
                    The string is not localized, so items are always separated with a comma.
@return A Core Graphics structure that represents a rectangle.
        If the string is not well-formed, the function returns CCRectZero.
*/
CCRect CC_DLL CCRectFromString(const char* pszContent);

/**
@brief Returns a Core Graphics point structure corresponding to the data in a given string.
@param pszContent   A string object whose contents are of the form "{x,y}",
                    where x is the x coordinate and y is the y coordinate.
                    The x and y values can represent integer or float values.
                    An example of a valid string is "{3.0,2.5}".
                    The string is not localized, so items are always separated with a comma.
@return A Core Graphics structure that represents a point.
        If the string is not well-formed, the function returns CCPointZero.
*/
CCPoint CC_DLL CCPointFromString(const char* pszContent);

/**
@brief Returns a Core Graphics size structure corresponding to the data in a given string.
@param pszContent   A string object whose contents are of the form "{w, h}",
                    where w is the width and h is the height.
                    The w and h values can be integer or float values.
                    An example of a valid string is "{3.0,2.5}".
                    The string is not localized, so items are always separated with a comma.
@return A Core Graphics structure that represents a size.
        If the string is not well-formed, the function returns CCSizeZero.
*/
CCSize CC_DLL CCSizeFromString(const char* pszContent);

// end of data_structure group
/// @}

NS_CC_END

#endif // __PLATFOMR_CCNS_H__


