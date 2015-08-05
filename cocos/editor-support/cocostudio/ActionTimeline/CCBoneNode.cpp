/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"

#include "CCBoneNode.h"
#include "CCSkeletonNode.h"

NS_TIMELINE_BEGIN

BoneNode::BoneNode()
: _isRackShow(false)
, _rackColor(cocos2d::Color4F::WHITE)
, _rackLength(50)
, _rackWidth(20)
, _rootSkeleton(nullptr)
, _blendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED)
{
}


BoneNode* BoneNode::create()
{
    BoneNode* ret = new (std::nothrow) BoneNode();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


BoneNode* BoneNode::create(int length)
{
    BoneNode* ret = new (std::nothrow) BoneNode();
    if (ret && ret->init())
    {
        ret->setDebugDrawLength(length);
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void BoneNode::addChild(cocos2d::Node* child, int localZOrder, int tag)
{
    Node::addChild(child, localZOrder, tag);
    addToChildrenListHelper(child);
}

void BoneNode::addChild(Node* child, int localZOrder, const std::string &name)
{
    Node::addChild(child, localZOrder, name);
    addToChildrenListHelper(child);
}

void BoneNode::addSkin(SkinNode* skin, bool isDisplay, bool hideOthers)
{
    CCASSERT(skin != nullptr, "Argument must be non-nil");
    if (hideOthers)
    {
        for (auto &bonskin : _boneSkins)
        {
            bonskin->setVisible(false);
        }
    }
    Node::addChild(skin);
    skin->setVisible(isDisplay);
}

void BoneNode::addSkin(SkinNode* skin, bool display)
{
    addSkin(skin, display, false);
}

void BoneNode::removeChild(Node* child, bool cleanup /* = true */)
{
    Node::removeChild(child, cleanup);
    removeFromChildrenListHelper(child);
}

void BoneNode::removeFromBoneList(BoneNode* bone)
{
    auto skeletonNode = dynamic_cast<SkeletonNode*>(bone);
    if (skeletonNode == nullptr) //not a nested skeleton
    {
        bone->_rootSkeleton = nullptr;
        auto subBones = bone->getAllSubBones();
        subBones.pushBack(bone);
        for (auto &subBone : subBones)
        {
            subBone->_rootSkeleton = nullptr;
            _rootSkeleton->_subBonesMap.erase(subBone->getName());
            if (bone->_isRackShow && bone->_visible)
            {
                _rootSkeleton->_subDrawBonesDirty = true;
                _rootSkeleton->_subDrawBonesOrderDirty = true;
            }
        }
    }
    _childBones.eraseObject(bone);
}

void BoneNode::addToBoneList(BoneNode* bone)
{
    _childBones.pushBack(bone);
    if (bone->_rootSkeleton == nullptr && _rootSkeleton != nullptr)
    {
        auto subBones = bone->getAllSubBones();
        subBones.pushBack(bone);
        for (auto &subBone : subBones)
        {
            subBone->_rootSkeleton = _rootSkeleton;
            auto bonename = subBone->getName();
            if (_rootSkeleton->_subBonesMap.find(bonename) == _rootSkeleton->_subBonesMap.end())
            {
                _rootSkeleton->_subBonesMap.insert(subBone->getName(), subBone);
                if (bone->_isRackShow && bone->_visible)
                {
                    _rootSkeleton->_subDrawBonesDirty = true;
                    _rootSkeleton->_subDrawBonesOrderDirty = true;
                }
            }
            else
                CCLOG("already has a bone named %s in skeleton %s", bonename.c_str(), _rootSkeleton->getName().c_str());
        }

        if (bone->_isRackShow && bone->_visible)
        {
            _rootSkeleton->_subDrawBonesDirty = true;
            _rootSkeleton->_subDrawBonesOrderDirty = true;
        }
    }
}

void BoneNode::addToSkinList(SkinNode* skin)
{
    _boneSkins.pushBack(skin);
}

void BoneNode::removeFromSkinList(SkinNode* skin)
{
    _boneSkins.eraseObject(skin);
}

void BoneNode::displaySkin(SkinNode* skin, bool hideOthers)
{
    for (auto boneskin : _boneSkins)
    {
        if (boneskin == skin)
        {
            boneskin->setVisible(true);
        }
        else if (hideOthers)
        {
            boneskin->setVisible(false);
        }
    }
}

void BoneNode::displaySkin(const std::string &skinName, bool hideOthers)
{
    for (auto &skin : _boneSkins)
    {
        if (skinName == skin->getName())
        {
            skin->setVisible(true);
        }
        else if (hideOthers)
        {
            skin->setVisible(false);
        }
    }
}

cocos2d::Vector<SkinNode*> BoneNode::getVisibleSkins() const
{
    cocos2d::Vector<SkinNode*> displayingSkins;
    for (const auto &boneskin : _boneSkins)
    {
        if (boneskin->isVisible())
        {
            displayingSkins.pushBack(boneskin);
        }
    }
    return displayingSkins;
}

cocos2d::Rect BoneNode::getBoundingBox() const
{
    cocos2d::Rect boundingBox = getVisibleSkinsRect();
    return RectApplyAffineTransform(boundingBox, this->getNodeToParentAffineTransform());
}

cocos2d::Rect BoneNode::getVisibleSkinsRect() const
{
    float minx, miny, maxx, maxy = 0;
    minx = miny = maxx = maxy;
    bool first = true;

    cocos2d::Rect displayRect = cocos2d::Rect(0, 0, 0, 0);
    if (_isRackShow && _rootSkeleton != nullptr && _rootSkeleton->_isRackShow)
    {
        maxx = _rackLength;
        maxy = _rackWidth;
        first = false;
    }

    for (const auto& skin : _boneSkins)
    {
        cocos2d::Rect r = skin->getBoundingBox();
        if (!skin->isVisible() || r.equals(cocos2d::Rect::ZERO))
            continue;

        if (first)
        {
            minx = r.getMinX();
            miny = r.getMinY();
            maxx = r.getMaxX();
            maxy = r.getMaxY();

            first = false;
        }
        else
        {
            minx = MIN(r.getMinX(), minx);
            miny = MIN(r.getMinY(), miny);
            maxx = MAX(r.getMaxX(), maxx);
            maxy = MAX(r.getMaxY(), maxy);
        }
        displayRect.setRect(minx, miny, maxx - minx, maxy - miny);
    }
    return displayRect;
}

void BoneNode::setBlendFunc(const cocos2d::BlendFunc& blendFunc)
{
    _blendFunc = blendFunc;
}

void BoneNode::setDebugDrawLength(float length)
{
    _rackLength = length;
    updateVertices();
}

void BoneNode::setDebugDrawWidth(float width)
{
    _rackWidth = width;
    updateVertices();
}

void BoneNode::setDebugDrawEnabled(bool isDebugDraw)
{
    if (_isRackShow == isDebugDraw)
        return;
    _isRackShow = isDebugDraw;
    if (_visible && nullptr != _rootSkeleton)
    {
        _rootSkeleton->_subDrawBonesDirty = true;
        _rootSkeleton->_subDrawBonesOrderDirty = true;
    }
}

void BoneNode::setDebugDrawColor(const cocos2d::Color4F &color)
{
    _rackColor = color;
    updateColor();
}


void BoneNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    if (!_isRackShow || nullptr != _rootSkeleton)
        return;

    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(BoneNode::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);

    for (int i = 0; i < 4; ++i)
    {
        cocos2d::Vec4 pos;
        pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
        pos.w = 1;
        _modelViewTransform.transformVector(&pos);
        _noMVPVertices[i] = cocos2d::Vec3(pos.x, pos.y, pos.z) / pos.w;
    }
}

BoneNode::~BoneNode()
{
}

bool BoneNode::init()
{
    _rackLength = 50;
    _rackWidth = 20;
    updateVertices();
    updateColor();
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
    return true;
}

void BoneNode::updateVertices()
{
    if (_rackLength != _squareVertices[2].x - _anchorPointInPoints.x || _squareVertices[3].y != _rackWidth / 2 - _anchorPointInPoints.y)
    {
        _squareVertices[1].x = _squareVertices[1].y = _squareVertices[3].y = .0f;
        _squareVertices[0].x = _squareVertices[2].x = _rackLength * .1f;
        _squareVertices[2].y = _rackWidth * .5f;
        _squareVertices[0].y = -_squareVertices[2].y;
        _squareVertices[3].x = _rackLength;

        for (int i = 0; i < 4; i++)
        {
            _squareVertices[i] += _anchorPointInPoints;
        }
        _transformUpdated = _transformDirty = _inverseDirty = _contentSizeDirty = true;
    }
}

void BoneNode::updateColor()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        _squareColors[i] = _rackColor;
    }
    _transformUpdated = _transformDirty = _inverseDirty = _contentSizeDirty = true;
}

void BoneNode::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION | cocos2d::GL::VERTEX_ATTRIB_FLAG_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);

    cocos2d::GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#ifdef CC_STUDIO_ENABLED_VIEW
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
    
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);
#else
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
#endif //CC_STUDIO_ENABLED_VIEW

}

cocos2d::Vector<BoneNode*> BoneNode::getAllSubBones() const
{
    cocos2d::Vector<BoneNode*> allBones;
    std::stack<BoneNode*> boneStack; // for avoid recursive
    for (const auto& bone : _childBones)
    {
        boneStack.push(bone);
    }

    while (boneStack.size() > 0)
    {
        auto top = boneStack.top();
        allBones.pushBack(top);
        boneStack.pop();
        auto topchildren = top->getChildBones();
        for (const auto& childbone : topchildren)
        {
            boneStack.push(childbone);
        }
    }
    return allBones;
}

cocos2d::Vector<SkinNode*> BoneNode::getAllSubSkins() const
{
    auto allbones = getAllSubBones();
    cocos2d::Vector<SkinNode*> allskins;
    for (const auto& bone : allbones)
    {
        for (const auto& skin : bone->getSkins())
        {
            allskins.pushBack(skin);
        }
    }
    return allskins;
}


void BoneNode::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        std::sort(_childBones.begin(), _childBones.end(), cocos2d::nodeComparisonLess);
        std::sort(_boneSkins.begin(), _boneSkins.end(), cocos2d::nodeComparisonLess);
        Node::sortAllChildren();
    }
}

SkeletonNode* BoneNode::getRootSkeletonNode() const
{
    return _rootSkeleton;
}

#ifdef CC_STUDIO_ENABLED_VIEW
bool BoneNode::isPointOnRack(const cocos2d::Vec2& bonePoint)
{

    if (bonePoint.x >= 0.0f && bonePoint.y >= _squareVertices[0].y
        && bonePoint.x <= _rackLength &&
        bonePoint.y <= _squareVertices[2].y)
    {
        if (_rackLength != 0.0f && _rackWidth != 0.0f)
        {
            float a1 = (_squareVertices[2].y - _squareVertices[3].y ) / (_squareVertices[3].x - _squareVertices[0].x);
            float a2 = (_squareVertices[2].y - _squareVertices[3].y) / (_squareVertices[0].x - _squareVertices[1].x);;
            float b1 = a1 * _squareVertices[3].x;
            float y1 = bonePoint.y - _squareVertices[1].y;
            if (y1 >= a1 * bonePoint.x - b1 &&
                y1 <= a2 * bonePoint.x &&
                y1 >= -a2 * bonePoint.x &&
                y1 <= -a1 * bonePoint.x + b1)
                return true;
        }
    }
    return false;
}
#endif //CC_STUDIO_ENABLED_VIEW

void BoneNode::batchBoneDrawToSkeleton(BoneNode* bone) const
{
    cocos2d::Vec3 vpos[4];
    for (int i = 0; i < 4; i++)
    {
        cocos2d::Vec4 pos;
        pos.x = bone->_squareVertices[i].x; pos.y = bone->_squareVertices[i].y; pos.z = bone->_positionZ;
        pos.w = 1;
        bone->_modelViewTransform.transformVector(&pos);  // call after visit
        vpos[i] = cocos2d::Vec3(pos.x, pos.y, pos.z) / pos.w;
    }

    int count = bone->_rootSkeleton->_batchedVeticesCount;
    if (count + 8 >(int)(bone->_rootSkeleton->_batchedBoneVetices.capacity()))
    {
        bone->_rootSkeleton->_batchedBoneVetices.resize(count + 100);
        bone->_rootSkeleton->_batchedBoneColors.resize(count + 100);
    }
    for (int i = 0; i < 4; i++)
    {
        bone->_rootSkeleton->_batchedBoneVetices[count + i] = vpos[i];
        bone->_rootSkeleton->_batchedBoneColors[count + i] = bone->_squareColors[i];
    }
    bone->_rootSkeleton->_batchedVeticesCount += 4;
    count += 4;
#ifdef CC_STUDIO_ENABLED_VIEW
    for (int i = 0; i < 4; i++)
    {
        bone->_rootSkeleton->_batchedBoneVetices[count + i] = vpos[i];
        bone->_rootSkeleton->_batchedBoneColors[count + i] = bone->_squareColors[i];
    }
    bone->_rootSkeleton->_batchedVeticesCount += 4;
#endif //CC_STUDIO_ENABLED_VIEW
}

void BoneNode::setLocalZOrder(int localZOrder)
{
    Node::setLocalZOrder(localZOrder);
    if (_rootSkeleton != nullptr && this->_visible && this->_isRackShow)
        _rootSkeleton->_subDrawBonesOrderDirty = true;
}

void BoneNode::setName(const std::string& name)
{
    auto oldname = getName();
    Node::setName(name);
    if (_rootSkeleton != nullptr)
    {
        auto oiter = _rootSkeleton->_subBonesMap.find(oldname);
        auto niter = _rootSkeleton->_subBonesMap.find(name);
        if (oiter != _rootSkeleton->_subBonesMap.end() &&
            niter == _rootSkeleton->_subBonesMap.end())
        {
            auto node = oiter->second;
            _rootSkeleton->_subBonesMap.erase(oiter);
            _rootSkeleton->_subBonesMap.insert(name, node);
        }
    }
}

void BoneNode::addToChildrenListHelper(Node * child)
{
    BoneNode* bone = dynamic_cast<BoneNode*>(child);
    if (nullptr != bone)
    {
        addToBoneList(bone);
    }
    else
    {
        SkinNode* skin = dynamic_cast<SkinNode*>(child);
        if (nullptr != skin)
        {
            addToSkinList(skin);
        }
    }
}

void BoneNode::removeFromChildrenListHelper(Node * child)
{
    BoneNode* bone = dynamic_cast<BoneNode*>(child);
    if (nullptr != bone)
    {
        removeFromBoneList(bone);
        if (bone->_isRackShow)
        {
            _rootSkeleton->_subDrawBonesDirty = true;
            _rootSkeleton->_subDrawBonesOrderDirty = true;
        }
    }
    else
    {
        SkinNode* skin = dynamic_cast<SkinNode*>(child);
        if (nullptr != skin)
        {
            removeFromSkinList(skin);
        }
    }
}

void BoneNode::setVisible(bool visible)
{
    if (_visible == visible)
        return;

    Node::setVisible(visible);
    if (_isRackShow && _rootSkeleton != nullptr)
    {
        _rootSkeleton->_subDrawBonesDirty = true;
        _rootSkeleton->_subDrawBonesOrderDirty = true;
    }
}

void BoneNode::setContentSize(const cocos2d::Size& contentSize)
{
    Node::setContentSize(contentSize);
    updateVertices();
}

void BoneNode::setAnchorPoint(const cocos2d::Vec2& anchorPoint)
{
    Node::setAnchorPoint(anchorPoint);
    updateVertices();
}

NS_TIMELINE_END