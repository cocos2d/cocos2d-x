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
    
    const Mat4& camWorldMat = camera->getNodeToWorldTransform();
    if (memcmp(_camWorldMat.m, camWorldMat.m, sizeof(float) * 16) != 0 || memcmp(_transform.m, transform.m, sizeof(float) * 16) != 0)
    {
        Vec3 camDir(transform.m[12] - camWorldMat.m[12], transform.m[13] - camWorldMat.m[13], transform.m[14] - camWorldMat.m[14]);
        
        if (camDir.length() < MATH_TOLERANCE)
        {
            camDir.set(camWorldMat.m[8], camWorldMat.m[9], camWorldMat.m[10]);
        }
        camDir.normalize();
        
        static Vec3 upAxis(0.0f, 1.0f, 0.0f);
        Vec3 x, y;
        camWorldMat.transformVector(upAxis, &y);
        Vec3::cross(camDir, y, &x);
        x.normalize();
        Vec3::cross(x, camDir, &y);
        float xlen = sqrtf(transform.m[0] * transform.m[0] + transform.m[1] * transform.m[1] + transform.m[2] * transform.m[2]);
        float ylen = sqrtf(transform.m[4] * transform.m[4] + transform.m[5] * transform.m[5] + transform.m[6] * transform.m[6]);
        float zlen = sqrtf(transform.m[8] * transform.m[8] + transform.m[9] * transform.m[9] + transform.m[10] * transform.m[10]);
        
        _billboardTransform.m[0] = x.x * xlen; _billboardTransform.m[1] = x.y * xlen; _billboardTransform.m[2] = x.z * xlen;
        _billboardTransform.m[4] = y.x * ylen; _billboardTransform.m[5] = y.y * ylen; _billboardTransform.m[6] = y.z * ylen;
        _billboardTransform.m[8] = -camDir.x * zlen; _billboardTransform.m[9] = -camDir.y * zlen; _billboardTransform.m[10] = -camDir.z * zlen;
        _billboardTransform.m[12] = transform.m[12]; _billboardTransform.m[13] = transform.m[13]; _billboardTransform.m[14] = transform.m[14];
        
        const Mat4 &viewMat = camWorldMat.getInversed();
        _zDepthInView = -(viewMat.m[2] * transform.m[12] + viewMat.m[6] * transform.m[13] + viewMat.m[10] * transform.m[14] + viewMat.m[14]);
        _transform = transform;
        _camWorldMat = camWorldMat;
    }

    //FIXME: frustum culling here
    {
            _quadCommand.init(_zDepthInView, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, _billboardTransform);
            renderer->addTransparentCommand(&_quadCommand);
    }
}

NS_CC_END
