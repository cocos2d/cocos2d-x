/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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

#include "3d/CCBillBoard.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCDirector.h"
#include "2d/CCCamera.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramCache.h"

NS_CC_BEGIN

BillBoard::BillBoard()
: _mode(Mode::VIEW_POINT_ORIENTED)
, _modeDirty(false)
{
    Node::setAnchorPoint(Vec2(0.5f,0.5f));
}

BillBoard::~BillBoard()
{
}

BillBoard* BillBoard::createWithTexture(Texture2D *texture, Mode mode)
{
    BillBoard *billboard = new (std::nothrow) BillBoard();
    if (billboard && billboard->initWithTexture(texture))
    {
        billboard->_mode = mode;
        billboard->autorelease();
        return billboard;
    }
    CC_SAFE_DELETE(billboard);
    return nullptr;
}


BillBoard* BillBoard::create(const std::string& filename, Mode mode)
{
    BillBoard *billboard = new (std::nothrow) BillBoard();
    if (billboard && billboard->initWithFile(filename))
    {
        billboard->_mode = mode;
        billboard->autorelease();
        return billboard;
    }
    CC_SAFE_DELETE(billboard);
    return nullptr;
}

BillBoard* BillBoard::create(const std::string& filename, const Rect& rect, Mode mode)
{
    BillBoard *billboard = new (std::nothrow) BillBoard();
    if (billboard && billboard->initWithFile(filename, rect))
    {
        billboard->_mode = mode;
        billboard->autorelease();
        return billboard;
    }
    CC_SAFE_DELETE(billboard);
    return nullptr;
}

BillBoard* BillBoard::create(Mode mode)
{
    BillBoard *billboard = new (std::nothrow) BillBoard();
    if (billboard && billboard->init())
    {
        billboard->_mode = mode;
        billboard->autorelease();
        return billboard;
    }
    CC_SAFE_DELETE(billboard);
    return nullptr;
}

void BillBoard::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    bool visibleByCamera = isVisitableByVisitingCamera();
    // quick return if not visible by camera and has no children.
    if (!visibleByCamera && _children.empty())
    {
        return;
    }
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    
    //Add 3D flag so all the children will be rendered as 3D object
    flags |= FLAGS_RENDER_AS_3D;
    
    //Update Billboard transform
    bool dirty = calculateBillboardTransform();
    if(dirty)
    {
        flags |= FLAGS_TRANSFORM_DIRTY;
    }
    
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    int i = 0;
    
    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for(auto size = _children.size(); i < size; ++i)
        {
            auto node = _children.at(i);
            
            if (node && node->getLocalZOrder() < 0)
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }
        // self draw
        if (visibleByCamera)
            this->draw(renderer, _modelViewTransform, flags);

        for(auto it=_children.cbegin()+i, itCend = _children.cend(); it != itCend; ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

bool BillBoard::calculateBillboardTransform()
{
    //Get camera world position
    auto camera = Camera::getVisitingCamera();
    const Mat4& camWorldMat = camera->getNodeToWorldTransform();
    
    //TODO: use math lib to calculate math lib Make it easier to read and maintain
    if (memcmp(_camWorldMat.m, camWorldMat.m, sizeof(float) * 16) != 0 || memcmp(_mvTransform.m, _modelViewTransform.m, sizeof(float) * 16) != 0 || _modeDirty || true)
    {
        //Rotate based on anchor point
        Vec3 anchorPoint(_anchorPointInPoints.x , _anchorPointInPoints.y , 0.0f);
        Mat4 localToWorld = _modelViewTransform;
        localToWorld.translate(anchorPoint);
        
        //Decide billboard mode
        Vec3 camDir;
        switch (_mode)
        {
            case Mode::VIEW_POINT_ORIENTED:
                camDir.set(localToWorld.m[12] - camWorldMat.m[12], localToWorld.m[13] - camWorldMat.m[13], localToWorld.m[14] - camWorldMat.m[14]);
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

        Mat4 rotationMatrix;
        rotationMatrix.setIdentity();

        Vec3 upAxis(rotationMatrix.m[4],rotationMatrix.m[5],rotationMatrix.m[6]);
        Vec3 x, y;
        camWorldMat.transformVector(upAxis, &y);
        Vec3::cross(camDir, y, &x);
        x.normalize();
        Vec3::cross(x, camDir, &y);
        y.normalize();
        
        float xlen = sqrtf(localToWorld.m[0] * localToWorld.m[0] + localToWorld.m[1] * localToWorld.m[1] + localToWorld.m[2] * localToWorld.m[2]);
        float ylen = sqrtf(localToWorld.m[4] * localToWorld.m[4] + localToWorld.m[5] * localToWorld.m[5] + localToWorld.m[6] * localToWorld.m[6]);
        float zlen = sqrtf(localToWorld.m[8] * localToWorld.m[8] + localToWorld.m[9] * localToWorld.m[9] + localToWorld.m[10] * localToWorld.m[10]);
        
        Mat4 billboardTransform;
        
        billboardTransform.m[0] = x.x * xlen; billboardTransform.m[1] = x.y * xlen; billboardTransform.m[2] = x.z * xlen;
        billboardTransform.m[4] = y.x * ylen; billboardTransform.m[5] = y.y * ylen; billboardTransform.m[6] = y.z * ylen;
        billboardTransform.m[8] = -camDir.x * zlen; billboardTransform.m[9] = -camDir.y * zlen; billboardTransform.m[10] = -camDir.z * zlen;
        billboardTransform.m[12] = localToWorld.m[12]; billboardTransform.m[13] = localToWorld.m[13]; billboardTransform.m[14] = localToWorld.m[14];
        
        billboardTransform.translate(-anchorPoint);
        _mvTransform = _modelViewTransform = billboardTransform;
        
        _camWorldMat = camWorldMat;
        
        return true;
    }
    
    return false;
}

bool BillBoard::calculateBillbaordTransform()
{
    return calculateBillboardTransform();
}

void BillBoard::draw(Renderer *renderer, const Mat4 &/*transform*/, uint32_t flags)
{
    //FIXME: frustum culling here
    flags |= Node::FLAGS_RENDER_AS_3D;
    _trianglesCommand.init(0, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, _modelViewTransform, flags);
    _trianglesCommand.setTransparent(true);
    _trianglesCommand.set3D(true);
    renderer->addCommand(&_trianglesCommand);
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
