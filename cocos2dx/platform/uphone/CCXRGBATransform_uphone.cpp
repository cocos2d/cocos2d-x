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
#include "CCXRGBATransform_uphone.h"
#include "ccTypes.h"

namespace cocos2d
{


ccColor4B CCXRGBATransform::transformRGBA(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a)
{
#ifdef _TRANZDA_VM_
	ccColor4B c4 = {r, g, b, a};
#else
	ccColor4B c4 = {b, g, r, a};
#endif

	return c4;
}

ccColor3B CCXRGBATransform::transformRGBA(const GLubyte r, const GLubyte g, const GLubyte b)
{
#ifdef _TRANZDA_VM_
	ccColor3B c3 = {r, g, b};
#else
	ccColor3B c3 = {b, g, r};
#endif

	return c3;
}


} // end of namespace cocos2d
