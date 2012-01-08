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

#ifndef __COCOA_CGAFFINETRANSFORM_H__
#define __COCOA_CGAFFINETRANSFORM_H__

#include "CCGeometry.h"
#include "CCPlatformMacros.h"

namespace   cocos2d {

struct CCAffineTransform {
  CGFloat a, b, c, d;
  CGFloat tx, ty;
};

CC_DLL CCAffineTransform __CCAffineTransformMake(CGFloat a, CGFloat b, CGFloat c, CGFloat d, CGFloat tx, CGFloat ty);
#define CCAffineTransformMake __CCAffineTransformMake

CC_DLL CCPoint __CCPointApplyAffineTransform(const CCPoint& point, const CCAffineTransform& t);
#define CCPointApplyAffineTransform __CCPointApplyAffineTransform

CC_DLL CCSize __CCSizeApplyAffineTransform(const CCSize& size, const CCAffineTransform& t);
#define CCSizeApplyAffineTransform __CCSizeApplyAffineTransform

CC_DLL CCAffineTransform CCAffineTransformMakeIdentity();
CC_DLL CCRect CCRectApplyAffineTransform(const CCRect& rect, const CCAffineTransform& anAffineTransform);

CC_DLL CCAffineTransform CCAffineTransformTranslate(const CCAffineTransform& t, float tx, float ty);
CC_DLL CCAffineTransform CCAffineTransformRotate(const CCAffineTransform& aTransform, CGFloat anAngle);
CC_DLL CCAffineTransform CCAffineTransformScale(const CCAffineTransform& t, CGFloat sx, CGFloat sy);
CC_DLL CCAffineTransform CCAffineTransformConcat(const CCAffineTransform& t1, const CCAffineTransform& t2);
CC_DLL bool CCAffineTransformEqualToTransform(const CCAffineTransform& t1, const CCAffineTransform& t2);
CC_DLL CCAffineTransform CCAffineTransformInvert(const CCAffineTransform& t);

extern const CCAffineTransform CCAffineTransformIdentity;
}//namespace   cocos2d 

#endif // __COCOA_CGAFFINETRANSFORM_H__
