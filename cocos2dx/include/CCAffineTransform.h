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
namespace   cocos2d {

struct CCAffineTransform {
  CGFloat a, b, c, d;
  CGFloat tx, ty;
};

CCAffineTransform __CCAffineTransformMake(CGFloat a, CGFloat b, CGFloat c, CGFloat d, CGFloat tx, CGFloat ty);
#define CCAffineTransformMake __CCAffineTransformMake

CCPoint __CCPointApplyAffineTransform(CCPoint point, CCAffineTransform t);
#define CCPointApplyAffineTransform __CCPointApplyAffineTransform

CCSize __CCSizeApplyAffineTransform(CCSize size, CCAffineTransform t);
#define CCSizeApplyAffineTransform __CCSizeApplyAffineTransform

CCAffineTransform CCAffineTransformMakeIdentity();
CCRect CCRectApplyAffineTransform(CCRect rect, CCAffineTransform anAffineTransform);

CCAffineTransform CCAffineTransformTranslate(CCAffineTransform t, float tx, float ty);
CCAffineTransform CCAffineTransformRotate(CCAffineTransform aTransform, CGFloat anAngle);
CCAffineTransform CCAffineTransformScale(CCAffineTransform t, CGFloat sx, CGFloat sy);
CCAffineTransform CCAffineTransformConcat(CCAffineTransform t1,CCAffineTransform t2);
bool CCAffineTransformEqualToTransform(CCAffineTransform t1,CCAffineTransform t2);
CCAffineTransform CCAffineTransformInvert(CCAffineTransform t);

extern const CCAffineTransform CCAffineTransformIdentity;
}//namespace   cocos2d 

#endif // __COCOA_CGAFFINETRANSFORM_H__
