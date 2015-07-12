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
: _length(50)
, _width(20)
, _isRackShow(true)
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
    ret->_length = length;
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

BoneNode* BoneNode::create(const int &length, const cocos2d::Color4F & color)
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

void BoneNode::addChildBone(BoneNode* bone, int localZOrder, const std::string &name)
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
                _rootSkeleton->_subBonesMap.insert(subBone->getName(), subBone);
            else
                CCLOG("already has a bone named %s in skeleton %s", bonename.c_str(), _rootSkeleton->getName().c_str());
        }
    }
}

void BoneNode::addChildBone(BoneNode* bone)
{
    Node::addChild(bone);
}


void BoneNode::addDisplay(SkinNode* skin, bool isDisplay, bool hideOthers /*= false*/)
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


void BoneNode::removeChildBone(BoneNode* bone, bool cleaup /*= false*/)
{
    _childBones.eraseObject(bone);
    bone->_rootSkeleton = nullptr;
    auto subBones = getAllSubBones();
    for (auto &subBone : subBones)
    {
        subBone->_rootSkeleton = nullptr;
        _rootSkeleton->_subBonesMap.erase(subBone->getName());
    }
}

void BoneNode::removeFromParentBone(bool cleanup)
{
    auto parentBone = dynamic_cast<BoneNode*>(_parent);
    CCASSERT (nullptr != _parent, "Not a child of a BoneNode");

    parentBone->removeChildBone(this, cleanup);
}

void BoneNode::addSkin(SkinNode* skin, bool hide /*= false*/)
{
    _boneSkins.pushBack(skin);
}

void BoneNode::removeSkin(SkinNode* skin)
{
    _boneSkins.eraseObject(skin);
}

void BoneNode::display(SkinNode* skin, bool hideOthers /*= false*/)
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

void BoneNode::display(const std::string &skinName, bool hideOthers)
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

cocos2d::Vector<SkinNode*> BoneNode::getDisplayings() const
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
    _length = length;
    _contentSize.width = length;
    _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
    updateVertices();
}

void BoneNode::setWidth(float width)
{
    _width = width;
    _contentSize.height = width;
    _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
    updateVertices();
}

void BoneNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    if (!_isRackShow)
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
    }
    _length = _contentSize.width;
    _width  = _contentSize.height;
    updateVertices();
}

bool BoneNode::init()
{
    _anchorPoint = Vec2(0, .5f);
    setContentSize(cocos2d::Size(_length, _width));
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
    return true;
}

void BoneNode::updateVertices()
{
    if (_length != _squareVertices[2].x || _squareVertices[3].y != _width / 2)
    {
        _squareVertices[0].x = _squareVertices[3].x = _length * .1f;
        _squareVertices[1].y = _squareVertices[2].y = _width * .5f;
        _squareVertices[3].y = _width;
        _squareVertices[2].x = _length;
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

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
}

BoneNode::~BoneNode()
{
}

void BoneNode::setRackShow(bool ishow)
{
    _isRackShow = ishow;
}


void BoneNode::setRackColor(const cocos2d::Color4F &color)
{
    _rackColor = color;
    updateColor();
}

cocos2d::Rect BoneNode::getDisplayingRect() const
{
    float minx, miny, maxx, maxy = 0;
    minx = miny = maxx = maxy;
    bool first = true;

    Rect displayRect = Rect(0, 0, 0, 0);
    if (_isRackShow && _rootSkeleton != nullptr && _rootSkeleton->_isAllRackShow)
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
    Rect boundingBox = getDisplayingRect();
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
        for (const auto& skin : bone->getDisplays())
        {
            allskins.pushBack(skin);
        }
    }
    return allskins;
}

void BoneNode::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }

    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);


    int i = 0;

    if (!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for (; i < _children.size(); i++)
        {
            auto node = _children.at(i);

            if (node && node->getLocalZOrder() < 0)
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }

        for (auto it = _children.cbegin() + i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);

    }
    _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void BoneNode::addChild(Node* child, int localZOrder, const std::string &name)
{
    Node::addChild(child, localZOrder, name);
    BoneNode* bone = dynamic_cast<BoneNode*>(child);
    if (nullptr != bone)
    {
        addChildBone(bone, localZOrder, name);
    }
    else
    {
        SkinNode* skin = dynamic_cast<SkinNode*>(child);
        if (nullptr != skin)
        {
            addSkin(skin);
        }
    }
}

void BoneNode::removeChild(Node* child, bool cleanup /* = true */)
{
    Node::removeChild(child, cleanup);
    BoneNode* bone = dynamic_cast<BoneNode*>(child);
    if (nullptr != bone)
    {
        removeChildBone(bone);
    }
    else
    {
        SkinNode* skin = dynamic_cast<SkinNode*>(child);
        if (nullptr != skin)
        {
            removeSkin(skin);
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

NS_TIMELINE_END