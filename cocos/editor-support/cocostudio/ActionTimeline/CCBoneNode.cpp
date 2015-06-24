/****************************************************************************
Copyright (c) 2015 cocos2d-x.org

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

#include "CCBoneNode.h"
#include "CCSkeletonNode.h"

using namespace cocos2d;

NS_TIMELINE_BEGIN

bool nodePairComparisonLess(std::pair<std::string, Node*> p1, std::pair<std::string, Node*> p2)
{
    return nodeComparisonLess(p1.second, p2.second);
}


BoneNode::BoneNode()
: _length(50)
, _width(20)
, _isRackShow(true)
, _rootBoneNode(nullptr)
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
    if (bone->_rootBoneNode == nullptr && _rootBoneNode != nullptr)
    {
        bone->_rootBoneNode = _rootBoneNode;
        auto subBones = getAllSubBones();
        for (auto &subBone : subBones)
        {
            subBone->_rootBoneNode = _rootBoneNode;
        }
    }
}

void BoneNode::removeChildBone(BoneNode* bone, bool cleaup /*= false*/)
{
    _childBones.eraseObject(bone);
    bone->_rootBoneNode = nullptr;
    auto subBones = getAllSubBones();
    for (auto &subBone : subBones)
    {
        subBone->_rootBoneNode = nullptr;
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
    if (!skin->isVisible())
        skin->setVisible(true);

    if (hideOthers)
    {
        for (auto boneskin : _boneSkins)
        {
            if (boneskin != skin)
            {
                boneskin->setVisible(false);
            }
        }
    }
}

cocos2d::Vector<SkinNode*> BoneNode::getDisplaying() const
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
// 
//     auto rootSkeleton = static_cast<SkeletonNode*>(_rootBoneNode);
//     if (nullptr == rootSkeleton) // batch bones to SkeletonNode
//     {
        _customCommand.init(_globalZOrder, transform, flags);
        _customCommand.func = CC_CALLBACK_0(BoneNode::onDraw, this, transform, flags);
        renderer->addCommand(&_customCommand);
//    }

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
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
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
        _squareColors[i].r = _displayedColor.r / 255.0f;
        _squareColors[i].g = _displayedColor.g / 255.0f;
        _squareColors[i].b = _displayedColor.b / 255.0f;
        _squareColors[i].a = _displayedOpacity / 255.0f;
    }
    _transformUpdated = _transformDirty = _inverseDirty = _contentSizeDirty = true;
}

void BoneNode::onDraw(const Mat4& transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

    //
    // Attributes
    //
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

cocos2d::Rect BoneNode::getBoundingBox() const
{
    float minx, miny, maxx, maxy = 0;

    bool first = true;

    Rect boundingBox = Rect(0, 0, 0, 0);

    for (const auto& skin : _boneSkins)
    {
        Rect r = skin->getBoundingBox();
        if (r.equals(Rect::ZERO))
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
            minx = r.getMinX() < boundingBox.getMinX() ? r.getMinX() : boundingBox.getMinX();
            miny = r.getMinY() < boundingBox.getMinY() ? r.getMinY() : boundingBox.getMinY();
            maxx = r.getMaxX() > boundingBox.getMaxX() ? r.getMaxX() : boundingBox.getMaxX();
            maxy = r.getMaxY() > boundingBox.getMaxY() ? r.getMaxY() : boundingBox.getMaxY();
        }
        boundingBox.setRect(minx, miny, maxx - minx, maxy - miny);
    }

    return RectApplyTransform(boundingBox, getNodeToParentTransform());
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
    // self draw
    //if (this->_rootBoneNode == nullptr)
    //    this->draw(renderer, _modelViewTransform, flags);

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

NS_TIMELINE_END