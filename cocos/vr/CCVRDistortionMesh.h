/****************************************************************************
 Copyright (c) 2016 Google Inc.
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

#ifndef CCVRDistortionMesh_hpp
#define CCVRDistortionMesh_hpp

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class Distortion;

class DistortionMesh
{
public:
    DistortionMesh();
    DistortionMesh(Distortion *distortion,
                   float screenWidth, float screenHeight,
                   float xEyeOffsetScreen, float yEyeOffsetScreen,
                   float textureWidth, float textureHeight,
                   float xEyeOffsetTexture, float yEyeOffsetTexture,
                   float viewportXTexture, float viewportYTexture,
                   float viewportWidthTexture,
                   float viewportHeightTexture,
                   bool vignetteEnabled);

    int _indices;
    int _arrayBufferID;
    int _elementBufferID;
};

NS_CC_END

#endif /* CCVRDistortionMesh_h */
