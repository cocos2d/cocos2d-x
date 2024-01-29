/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#ifndef CCVRGenericRenderer_hpp
#define CCVRGenericRenderer_hpp

#include "vr/CCVRProtocol.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCFrameBuffer.h"

NS_CC_BEGIN

class Camera;
class Sprite;
class DistortionMesh;
class Distortion;
class GLProgramState;
class VRGenericHeadTracker;

struct CC_DLL VREye
{
    enum class EyeType {
        MONO,
        LEFT,
        RIGHT,
    };

    EyeType type;
    experimental::Viewport viewport;
};

class CC_DLL VRGenericRenderer : public VRIRenderer
{
public:
    VRGenericRenderer();
    virtual ~VRGenericRenderer();

    virtual void setup(GLView* glview) override;
    virtual void cleanup() override;
    virtual void render(Scene* scene, Renderer* renderer) override;
    virtual VRIHeadTracker* getHeadTracker() override;

protected:
    void setupGLProgram();
    void renderDistortionMesh(DistortionMesh *mesh, Texture2D* texture);
    DistortionMesh* createDistortionMesh(VREye::EyeType eyeType);

    experimental::FrameBuffer* _fb;
    Size _texSize;
    VREye _leftEye;
    VREye _rightEye;
    DistortionMesh* _leftDistortionMesh;
    DistortionMesh* _rightDistortionMesh;
    Distortion* _distortion;
    bool _vignetteEnabled;
    
    GLProgramState* _glProgramState;
    VRGenericHeadTracker* _headTracker;
};

NS_CC_END

#endif // CCVRGenericRenderer_hpp
