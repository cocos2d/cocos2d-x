/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.

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

#ifndef __CC_VR_PROTOCOL_H__
#define __CC_VR_PROTOCOL_H__

#include <string>

#include "base/ccTypes.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

class Scene;
class Renderer;
class GLView;

class CC_DLL VRIHeadTracker
{
public:
    virtual ~VRIHeadTracker() {}

    // pose
    virtual Vec3 getLocalPosition() = 0;
    // rotation
    virtual Mat4 getLocalRotation() = 0;
};

class CC_DLL VRIRenderer
{
public:
    virtual ~VRIRenderer() {}

    virtual void setup(GLView* glview) = 0;
    virtual void cleanup() = 0;
    virtual void render(Scene* scene, Renderer* renderer) = 0;
    virtual VRIHeadTracker* getHeadTracker() = 0;
};


NS_CC_END

#endif // __CC_VR_PROTOCOL_H__
