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
#include "2d/CCCamera.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramCache.h"

NS_CC_BEGIN

BillBoard::BillBoard()
: _zDepthInView(0.0f)
, _mode(Mode::VIEW_POINT_ORIENTED)
, _modeDirty(false)
{
    Node::setAnchorPoint(Vec2(0.5f,0.5f));
}

BillBoard::~BillBoard()
{
}

BillBoard* BillBoard::createWithTexture(Texture2D *texture, Mode mode)
{
    BillBoard *billborad = new (std::nothrow) BillBoard();
    if (billborad && billborad->initWithTexture(texture))
    {
        billborad->_mode = mode;
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}


BillBoard* BillBoard::create(const std::string& filename, Mode mode)
{
    BillBoard *billborad = new (std::nothrow) BillBoard();
    if (billborad && billborad->initWithFile(filename))
    {
        billborad->_mode = mode;
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

BillBoard* BillBoard::create(const std::string& filename, const Rect& rect, Mode mode)
{
    BillBoard *billborad = new (std::nothrow) BillBoard();
    if (billborad && billborad->initWithFile(filename, rect))
    {
        billborad->_mode = mode;
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

BillBoard* BillBoard::create(Mode mode)
{
    BillBoard *billborad = new (std::nothrow) BillBoard();
    if (billborad && billborad->init())
    {
        billborad->_mode = mode;
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

void BillBoard::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    auto camera = Camera::getVisitingCamera();
    const Mat4& camWorldMat = camera->getNodeToWorldTransform();
    if (memcmp(_camWorldMat.m, camWorldMat.m, sizeof(float) * 16) != 0 || memcmp(_mvTransform.m, transform.m, sizeof(float) * 16) != 0 || _modeDirty)
    {
        Vec3 anchorPoint(_anchorPointInPoints.x , _anchorPointInPoints.y , 0.0f);
        Mat4 localToWorld = transform;
        localToWorld.translate(anchorPoint);
        Vec3 camDir;
        switch (_mode)
        {
        case Mode::VIEW_POINT_ORIENTED:
            camDir = Vec3(localToWorld.m[12] - camWorldMat.m[12], localToWorld.m[13] - camWorldMat.m[13], localToWorld.m[14] - camWorldMat.m[14]);
            break;
        case Mode::VIEW_PLANE_ORIENTED:
            camWorldMat.transformVector(Vec3(0.0f, 0.0f, -1.0f), &camDir);
            break;
        default:
                CCASSERT(false, "invalid billboard mode");
            break;
        }
        _modeDirty = false;
        if (camDir.length() < MATH_TOLERANCE)
        {
            camDir.set(camWorldMat.m[8], camWorldMat.m[9], camWorldMat.m[10]);
        }
        camDir.normalize();
        Quaternion rotationQuaternion;
        this->getNodeToWorldTransform().getRotation(&rotationQuaternion);
        // fetch the rotation angle of z
        float rotationZ = atan2(2*(rotationQuaternion.w*rotationQuaternion.z + rotationQuaternion.x*rotationQuaternion.y),
            (1 - 2* (rotationQuaternion.y*rotationQuaternion.y + rotationQuaternion.z *rotationQuaternion.z)));
        Mat4 rotationMatrix;
        rotationMatrix.setIdentity();
        rotationMatrix.rotateZ(rotationZ);
        Vec3 upAxis = Vec3(rotationMatrix.m[4],rotationMatrix.m[5],rotationMatrix.m[6]);
        Vec3 x, y;
        camWorldMat.transformVector(upAxis, &y);
        Vec3::cross(camDir, y, &x);
        x.normalize();
        Vec3::cross(x, camDir, &y);
        y.normalize();

        float xlen = sqrtf(localToWorld.m[0] * localToWorld.m[0] + localToWorld.m[1] * localToWorld.m[1] + localToWorld.m[2] * localToWorld.m[2]);
        float ylen = sqrtf(localToWorld.m[4] * localToWorld.m[4] + localToWorld.m[5] * localToWorld.m[5] + localToWorld.m[6] * localToWorld.m[6]);
        float zlen = sqrtf(localToWorld.m[8] * localToWorld.m[8] + localToWorld.m[9] * localToWorld.m[9] + localToWorld.m[10] * localToWorld.m[10]);

        _billboardTransform.m[0] = x.x * xlen; _billboardTransform.m[1] = x.y * xlen; _billboardTransform.m[2] = x.z * xlen;
        _billboardTransform.m[4] = y.x * ylen; _billboardTransform.m[5] = y.y * ylen; _billboardTransform.m[6] = y.z * ylen;
        _billboardTransform.m[8] = -camDir.x * zlen; _billboardTransform.m[9] = -camDir.y * zlen; _billboardTransform.m[10] = -camDir.z * zlen;
        _billboardTransform.m[12] = localToWorld.m[12]; _billboardTransform.m[13] = localToWorld.m[13]; _billboardTransform.m[14] = localToWorld.m[14];

        _billboardTransform.translate(-anchorPoint);

        const Mat4 &viewMat = camWorldMat.getInversed();
        _zDepthInView = -(viewMat.m[2] * _billboardTransform.m[12] + viewMat.m[6] * _billboardTransform.m[13] + viewMat.m[10] * _billboardTransform.m[14] + viewMat.m[14]);
        _mvTransform = transform;
        _camWorldMat = camWorldMat;
    }

    //FIXME: frustum culling here
    {
        _quadCommand.init(_zDepthInView, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, _billboardTransform);
        _quadCommand.setTransparent(true);
        renderer->addCommand(&_quadCommand);
    }
}

void BillBoard::setMode( Mode mode )
{
    _mode = mode;
    _modeDirty = true;
}

BillBoard::Mode BillBoard::getMode() const
{
    return _mode;
}

NS_CC_END
