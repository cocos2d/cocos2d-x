/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

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

using namespace cocos2d;

NS_TIMELINE_BEGIN

BoneNode::BoneNode()
: _isRackShow(true)
, _rackColor(Color4F::WHITE)
, _rootSkeleton(nullptr)
, _blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
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


BoneNode* BoneNode::create(const int &length)
{
    BoneNode* ret = new (std::nothrow) BoneNode();
    if (ret && ret->init())
    {
        ret->setLength(length);
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void BoneNode::addToBoneChildren(BoneNode* bone)
{
    _childBones.pushBack(bone);
    if (bone->_rootSkeleton == nullptr && _rootSkeleton != nullptr)
    {
        auto subBones = getAllSubBones();
        for (auto &subBone : subBones)
        {
            subBone->_rootSkeleton = _rootSkeleton;
            auto bonename = subBone->getName();
            if (_rootSkeleton->_subBonesMap.find(bonename) == _rootSkeleton->_subBonesMap.end())
            {
                _rootSkeleton->_subBonesMap.insert(subBone->getName(), subBone);
                _rootSkeleton->_sortedAllBonesDirty = true;
            }
            else
                CCLOG("already has a bone named %s in skeleton %s", bonename.c_str(), _rootSkeleton->getName().c_str());
        }
    }
}

void BoneNode::addChildBone(BoneNode* bone)
{
    Node::addChild(bone);
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

void BoneNode::removeFromBoneChildren(BoneNode* bone)
{
    _childBones.eraseObject(bone);
    bone->_rootSkeleton = nullptr;
    auto subBones = getAllSubBones();
    for (auto &subBone : subBones)
    {
        subBone->_rootSkeleton = nullptr;
        _rootSkeleton->_subBonesMap.erase(subBone->getName());
        _rootSkeleton->_sortedAllBonesDirty = true;
    }
}

void BoneNode::removeFromParent()
{
    removeFromParentBone();
}

void BoneNode::removeFromParentBone()
{
    auto parentBone = dynamic_cast<BoneNode*>(_parent);
    CCASSERT (nullptr != _parent, "Not a child of a BoneNode");

    parentBone->removeFromBoneChildren(this);
}

void BoneNode::addToSkinList(SkinNode* skin)
{
    _boneSkins.pushBack(skin);
}

void BoneNode::removeFromSkinList(SkinNode* skin)
{
    _boneSkins.eraseObject(skin);
}

void BoneNode::displaySkin(SkinNode* skin, bool hideOthers /*= false*/)
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

void BoneNode::displaySkins(const std::string &skinName, bool hideOthers)
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

cocos2d::Vector<SkinNode*> BoneNode::getDisplayingSkins() const
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

void BoneNode::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

void BoneNode::setLength(float length)
{
    setContentSize(cocos2d::Size(length, _contentSize.height));
}

void BoneNode::setWidth(float width)
{
    setContentSize(cocos2d::Size(_contentSize.width, width));
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
        Vec4 pos;
        pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
        pos.w = 1;
        _modelViewTransform.transformVector(&pos);
        _noMVPVertices[i] = Vec3(pos.x, pos.y, pos.z) / pos.w;
    }
}


void BoneNode::setContentSize(const cocos2d::Size &size)
{
    if (!size.equals(_contentSize))
    {
        _contentSize = size;
        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);

        updateVertices();
    }
}

bool BoneNode::init()
{
    _anchorPoint = Vec2(0, .5f);
    setContentSize(Size(20, 20));
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
    return true;
}

void BoneNode::updateVertices()
{
    float length = _contentSize.width, width = _contentSize.height;
    if (length != _squareVertices[2].x || _squareVertices[3].y != width / 2)
    {
         _squareVertices[0].x = _squareVertices[2].x = length * .1f;
         _squareVertices[1].y = _squareVertices[3].y = width * .5f;
         _squareVertices[2].y = width;
         _squareVertices[3].x = length;

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

void BoneNode::onDraw(const Mat4& transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

#ifdef EMSCRIPTEN
    setGLBufferData(_noMVPVertices, 4 * sizeof(Vec3), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(_squareColors, 4 * sizeof(Color4F), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
#endif // EMSCRIPTEN

    cocos2d::GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#ifdef CC_STUDIO_ENABLED_VIEW
#ifdef EMSCRIPTEN
    setGLBufferData(_noMVPVertices, 4 * sizeof(Vec3), 0);
#else
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
#endif
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);
#else
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
#endif

}

BoneNode::~BoneNode()
{
}

void BoneNode::setDebugDrawEnabled(bool isDebugDraw)
{
    _isRackShow = isDebugDraw;
}


void BoneNode::setDebugDrawColor(const cocos2d::Color4F &color)
{
    _rackColor = color;
    updateColor();
}

cocos2d::Rect BoneNode::getVisibleSkinsRect() const
{
    float minx, miny, maxx, maxy = 0;
    minx = miny = maxx = maxy;
    bool first = true;

    Rect displayRect = Rect(0, 0, 0, 0);
    if (_isRackShow && _rootSkeleton != nullptr && _rootSkeleton->_isRackShow)
    {
        maxx = _contentSize.width;
        maxy = _contentSize.height;
        first = false;
    }

    for (const auto& skin : _boneSkins)
    {
        Rect r = skin->getBoundingBox();
        if (!skin->isVisible() || r.equals(Rect::ZERO))
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
        displayRect.setRect(minx, miny, maxx - minx, maxy- miny);
    }
    return displayRect;
}

cocos2d::Rect BoneNode::getBoundingBox() const
{
    Rect boundingBox = getVisibleSkinsRect();
    return RectApplyAffineTransform(boundingBox, this->getNodeToParentAffineTransform());
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
        if (topchildren.size() > 0)
        {
            for (const auto& childbone : topchildren)
            {
                boneStack.push(childbone);
            }
        }
    }
    return allBones;
}

cocos2d::Vector<SkinNode*> BoneNode::getAllSubDisplays() const
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

void BoneNode::addChild(Node* child, int localZOrder, const std::string &name)
{
    Node::addChild(child, localZOrder, name);
    BoneNode* bone = dynamic_cast<BoneNode*>(child);
    if (nullptr != bone)
    {
        addToBoneChildren(bone);
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

void BoneNode::removeChild(Node* child, bool cleanup)
{
    Node::removeChild(child, cleanup);
    BoneNode* bone = dynamic_cast<BoneNode*>(child);
    if (nullptr != bone)
    {
        removeFromBoneChildren(bone);
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

void BoneNode::sortAllChildren()
{
    Node::sortAllChildren();
    std::sort(_childBones.begin(), _childBones.end(), nodeComparisonLess);
    std::sort(_boneSkins.begin(), _boneSkins.end(), nodeComparisonLess);
}

cocos2d::Mat4 BoneNode::getBoneToSkeletonTransform() const
{
    auto retMat = Mat4::IDENTITY;
    if (_rootSkeleton == nullptr)
    {
        CCLOG("can not tranform before added to Skeleton");
        return retMat;
    }

    retMat = this->getNodeToParentTransform();
    for (Node *p = _parent; p != _rootSkeleton; p = p->getParent())
    {
        retMat = p->getNodeToParentTransform() * retMat;
    }
    return retMat;
}

cocos2d::AffineTransform BoneNode::getBoneToSkeletonAffineTransform() const
{

    auto retTrans = AffineTransform::IDENTITY;
    if (_rootSkeleton == nullptr)
    {
        CCLOG("can not tranform before added to Skeleton");
        return retTrans;
    }
    retTrans = this->getNodeToParentAffineTransform();
    for (Node *p = _parent; p != _rootSkeleton; p = p->getParent())
        retTrans = AffineTransformConcat(retTrans, p->getNodeToParentAffineTransform());
    return retTrans;
}

SkeletonNode* BoneNode::getRootSkeletonNode() const
{
    return _rootSkeleton;
}

#ifdef CC_STUDIO_ENABLED_VIEW
bool BoneNode::isPointOnRack(const cocos2d::Vec2& bonePoint)
{
    if (bonePoint.x >= 0 && bonePoint.y >= 0
        && bonePoint.x <= _contentSize.width &&
        bonePoint.y <= _contentSize.height)
    {
        if (_contentSize.width != 0)
        {
            float a1 = _squareVertices[1].y / (_squareVertices[3].x - _squareVertices[0].x);
            float a2 = _squareVertices[1].y / _squareVertices[0].x;
            float b1 = a1 * _squareVertices[0].x;
            float b2 = a1 * _squareVertices[3].x + _squareVertices[1].y;

            if (bonePoint.y >= a1 * bonePoint.x - b1 &&
                bonePoint.y <= a2 * bonePoint.x + _squareVertices[1].y &&
                bonePoint.y >= -a2 * bonePoint.x + _squareVertices[1].y &&
                bonePoint.y <= -a1 * bonePoint.x + b2)
                return true;
        }
    }
    return false;
}
#endif

void BoneNode::batchToSkeleton() const
{
    //auto skeletonTrans = getBoneToSkeletonTransform();
    Vec3 vpos[4];
    for (int i = 0; i < 4; i++)
    {
        Vec4 pos;
        pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
        pos.w = 1;
        //skeletonTrans.transformVector(&pos);
        _modelViewTransform.transformVector(&pos);  // call after visit
        vpos[i] = Vec3(pos.x, pos.y, pos.z) / pos.w;
    }

    int count = _rootSkeleton->_batchedVeticesCount;
    if (count + 4 > _rootSkeleton->_batchedBoneVetices.capacity())
    {
        _rootSkeleton->_batchedBoneVetices.resize(count + 100);
        _rootSkeleton->_batchedBoneColors.resize(count + 100);
    }
    for (int i = 0; i < 4; i++)
    {
        _rootSkeleton->_batchedBoneVetices[count + i] = vpos[i];
        _rootSkeleton->_batchedBoneColors[count + i] = _squareColors[i];
    }
    _rootSkeleton->_batchedVeticesCount += 4;
    count += 4;
#ifdef CC_STUDIO_ENABLED_VIEW
    for (int i = 0; i < 4; i++)
    {
        _rootSkeleton->_batchedBoneVetices[count + i] = vpos[i];
        _rootSkeleton->_batchedBoneColors[count + i] = _squareColors[i];
    }
    _rootSkeleton->_batchedVeticesCount += 4;
#endif
}

NS_TIMELINE_END