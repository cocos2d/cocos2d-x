/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "3d/CCBillBoard.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCDirector.h"
#include "base/CCCamera.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramCache.h"

NS_CC_BEGIN

BillBorad::BillBorad()
: _zDepthInView(0.0f)
{

}

BillBorad::~BillBorad()
{
}

BillBorad* BillBorad::createWithTexture(Texture2D *texture)
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->initWithTexture(texture))
    {
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}


BillBorad* BillBorad::create(const std::string& filename)
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->initWithFile(filename))
    {
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

BillBorad* BillBorad::create(const std::string& filename, const Rect& rect)
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->initWithFile(filename, rect))
    {
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

BillBorad* BillBorad::create()
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->init())
    {
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

void BillBorad::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    auto camera = Camera::getVisitingCamera();
    const Mat4 &viewMat = camera->getViewMatrix();
//    const Mat4& camWorldMat = camera->getNodeToWorldTransform();
//    Vec3 camDir(transform.m[12] - camWorldMat.m[12], transform.m[13] - camWorldMat.m[13], transform.m[14] - camWorldMat.m[14]);
//    camDir.normalize();
//    static Vec3 upAxis(0.0f, 1.0f, 0.0f);
//    Vec3 x, y;
//    camWorldMat.transformVector(upAxis, &y);
//    Vec3::cross(camDir, y, &x);
//    x.normalize();
//    Vec3::cross(x, camDir, &y);
//    Mat4 newTransform;
//    newTransform.m[0] = x.x; newTransform.m[1] = x.y; newTransform.m[2] = x.z;
//    newTransform.m[4] = y.x; newTransform.m[5] = y.y; newTransform.m[6] = y.z;
//    newTransform.m[8] = -camDir.x; newTransform.m[9] = -camDir.y; newTransform.m[10] = -camDir.z;
//    newTransform.m[12] = transform.m[12]; newTransform.m[13] = transform.m[13]; newTransform.m[14] = transform.m[14];
    
    
    if (memcmp(_preViewMat.m, viewMat.m, sizeof(float) * 16) != 0)
    {
        Mat4 viewInverseMat =  camera->getInverseViewMatrix();
        viewInverseMat.m[12] = viewInverseMat.m[13] = viewInverseMat.m[14] = 0;
        Mat4 modelViewMat = viewMat * transform;
        _preViewMat = viewMat;
        _zDepthInView = -modelViewMat.m[14];
        _mv = viewInverseMat;
    }

    //FIXME: frustum culling here
    {
            _quadCommand.init(_zDepthInView, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, newTransform/*transform * _mv*/);
            renderer->addTransparentCommand(&_quadCommand);
    }
}

NS_CC_END
