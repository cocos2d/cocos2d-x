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
#include "CCSkeletonNode.h"

#include "base/CCDirector.h"
#include "math/TransformUtils.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include <stack>

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif


NS_TIMELINE_BEGIN


SkeletonNode* SkeletonNode::create()
{
    SkeletonNode* skeletionNode = new (std::nothrow) SkeletonNode();
    if (skeletionNode && skeletionNode->init())
    {
        skeletionNode->autorelease();
        return skeletionNode;
    }
    CC_SAFE_DELETE(skeletionNode);
    return nullptr;
}


bool SkeletonNode::init()
{
    _anchorPoint = cocos2d::Vec2(.5f, .5f);
    setContentSize(cocos2d::Size(20, 20));
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
    _rootSkeleton = this;
    return true;
}


cocos2d::Rect SkeletonNode::getBoundingBox() const
{
    float minx, miny, maxx, maxy = 0;
    minx = miny = maxx = maxy;
    cocos2d::Rect boundingBox = getDisplayingRect();
    bool first = true;
    if (!boundingBox.equals(cocos2d::Rect::ZERO))
    {
        minx = boundingBox.getMinX();
        miny = boundingBox.getMinY();
        maxx = boundingBox.getMaxX();
        maxy = boundingBox.getMaxY();
        first = false;
    }
    auto allbones = getAllSubBones();
    for (const auto& bone : allbones)
    {
        cocos2d::Rect r = RectApplyAffineTransform(bone->getDisplayingRect(), bone->getBoneToSkeletonAffineTransform());
        if (r.equals(cocos2d::Rect::ZERO))
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
    }
    boundingBox.setRect(minx, miny, maxx - minx, maxy - miny);
    return RectApplyAffineTransform(boundingBox, this->getNodeToParentAffineTransform());;
}

SkeletonNode::SkeletonNode()
    : BoneNode()
    , _isAllRackShow(true)
{
}

SkeletonNode::~SkeletonNode()
{
}

void SkeletonNode::updateVertices()
{
    const float radius = _width * .5f;
    const float radius_2 = radius * .25f;
    if (radius != _squareVertices[0].x )
    {
        _squareVertices[0].x = _squareVertices[4].x = _squareVertices[7].x = _squareVertices[3].x = radius;
        _squareVertices[5].y = _squareVertices[2].y = _squareVertices[1].y = _squareVertices[6].y = radius;
        _squareVertices[6].x = _squareVertices[3].y = _width;
        _squareVertices[1].x = _squareVertices[7].y = radius + radius_2;
        _squareVertices[2].x = _squareVertices[4].y = radius - radius_2;

        _transformUpdated = _transformDirty = _inverseDirty = _contentSizeDirty = true;
    }
}

void SkeletonNode::updateColor()
{
    for (unsigned int i = 0; i < 8; i++)
    {
        _squareColors[i] = _rackColor;
    }
    _transformUpdated = _transformDirty = _inverseDirty = _contentSizeDirty = true;
}


void SkeletonNode::visit(cocos2d::Renderer *renderer, const  cocos2d::Mat4& parentTransform, uint32_t parentFlags)
{
    BoneNode::visit(renderer, parentTransform, parentFlags);
    if (this->_visible)
    {
        this->draw(renderer, parentTransform, parentFlags);
    }
}

void SkeletonNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    if (_isAllRackShow)
    {
        if (_isRackShow)
        {
            _customCommand.init(_globalZOrder, transform, flags);
            _customCommand.func = CC_CALLBACK_0(SkeletonNode::onDraw, this, transform, flags);
            renderer->addCommand(&_customCommand);

            for (int i = 0; i < 8; ++i)
            {
                cocos2d::Vec4 pos;
                pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
                pos.w = 1;
                _modelViewTransform.transformVector(&pos);
                _noMVPVertices[i] = cocos2d::Vec3(pos.x, pos.y, pos.z) / pos.w;
            }
        }

        //auto transp = this->getWorldToNodeTransform();
        auto allbones = getAllSubBones();
        for (auto &subbone : allbones)
        {
            //auto ptran = subbone->getParent()->getNodeToWorldTransform();
            //ptran.multiply(transp);
            subbone->draw(renderer, transform/*ptran*/, flags);
        }
    }
}

void SkeletonNode::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION | cocos2d::GL::VERTEX_ATTRIB_FLAG_COLOR);

    //
    // Attributes
    //
#ifdef EMSCRIPTEN
    setGLBufferData(_noMVPVertices, 8 * sizeof(Vec3), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(_squareColors, 8 * sizeof(Color4F), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
#endif // EMSCRIPTEN

    cocos2d::GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);
}

void SkeletonNode::setAllRackShow(bool showRack)
{
    _isAllRackShow = showRack;
}

void SkeletonNode::setLength(float length)
{
    _width = _length = length;
    _contentSize.width = _contentSize.height = length;
    _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
    updateVertices();
}

void SkeletonNode::setContentSize(const cocos2d::Size &size)
{
    _length = size.width;
    _width = size.height;
    if (!size.equals(_contentSize))
    {
        _contentSize = size;
        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
    }
    updateVertices();
}

void SkeletonNode::changeDisplays(const std::map<std::string, std::string> &boneSkinNameMap)
{
    for (auto &boneskin : boneSkinNameMap)
    {
        auto bone = getBoneNode(boneskin.first);
        if ( nullptr != bone)
            bone->display(boneskin.second, true);
    }
}

BoneNode* SkeletonNode::getBoneNode(const std::string& boneName)
{
    auto iter = _subBonesMap.find(boneName);
    if (iter != _subBonesMap.end())
    {
        return iter->second;
    }
    return nullptr;
}

const cocos2d::Map<std::string, BoneNode*>& SkeletonNode::getAllSubBonesMap() const
{
    return _subBonesMap;
}

cocos2d::Mat4 SkeletonNode::getBoneToSkeletonTransform() const
{
    return _transform;
}

cocos2d::AffineTransform SkeletonNode::getBoneToSkeletonAffineTransform() const
{
    cocos2d::AffineTransform ret;
    cocos2d::GLToCGAffine(_transform.m, &ret);

    return ret;
}

cocos2d::Mat4 SkeletonNode::getSkinToSkeletonTransform(SkinNode* skin)
{
    auto boneParent = dynamic_cast<BoneNode*>(skin->getParent());
    if (boneParent == nullptr)
    {
        CCLOG("skin %s is not a skin or have not been added to a bone");
        return cocos2d::Mat4::IDENTITY;
    }
    return boneParent->getBoneToSkeletonTransform() * skin->getNodeToParentTransform();
}

cocos2d::AffineTransform SkeletonNode::getSkinToSkeltonAffineTransform(SkinNode* skin)
{
    auto boneParent = dynamic_cast<BoneNode*>(skin->getParent());
    if (boneParent == nullptr)
    {
        CCLOG("skin %s is not a skin or have not been added to a bone", skin->getName().c_str());
        return cocos2d::AffineTransform::IDENTITY;
    }
    return AffineTransformConcat(skin->getNodeToParentAffineTransform(), boneParent->getBoneToSkeletonAffineTransform());
}

NS_TIMELINE_END