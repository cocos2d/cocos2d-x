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

#ifndef __PLATFORM_CCMATH_H__
#define __PLATFORM_CCMATH_H__

#include <float.h>

namespace cocos2d
{

	/************************************************************************/
	// VC have the function _isnan()
	// In other compiler(such as gcc), we may implement ourself.
	// We use a simple way: if it is a number, it should equal to itself.
	/************************************************************************/
	class CCMath
	{
	public:
		static inline int isnanCocos2d(double fValue)
		{
	 #ifdef WIN32
 			return _isnan(fValue);
	 #else
 			if (fValue != fValue)
 			{
 				return 1;
 			}
 			else
 			{
 				return 0;
 			}
	 #endif // WIN32
		}
	};
	  
	} // end of namespace cocos2d

#endif // __PLATFORM_CCMATH_H__
