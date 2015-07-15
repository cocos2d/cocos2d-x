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

using namespace cocos2d;
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
    _anchorPoint = Vec2(.5f, .5f);
    setContentSize(Size(20, 20));
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
    _rootSkeleton = this;
    return true;
}

Rect SkeletonNode::getBoundingBox() const
{
    float minx, miny, maxx, maxy = 0;
    minx = miny = maxx = maxy;
    Rect boundingBox = getVisibleSkinsRect();
    bool first = true;
    if (!boundingBox.equals(Rect::ZERO))
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
        Rect r = RectApplyAffineTransform(bone->getVisibleSkinsRect(), bone->getBoneToSkeletonAffineTransform());
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
{
}

SkeletonNode::~SkeletonNode()
{
}

void SkeletonNode::updateVertices()
{
    const float radius = _contentSize.width * .5f;
    const float radius_2 = radius * .25f;
    if (radius != _squareVertices[0].x )
    {
        _squareVertices[0].x = _squareVertices[4].x = _squareVertices[7].x = _squareVertices[3].x = radius;
        _squareVertices[5].y = _squareVertices[2].y = _squareVertices[1].y = _squareVertices[6].y = radius;
        _squareVertices[6].x = _squareVertices[3].y = _contentSize.width;
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


void SkeletonNode::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    BoneNode::visit(renderer, parentTransform, parentFlags);
    if (_isRackShow)
    {
        _customCommand.init(_globalZOrder, parentTransform, parentFlags);
        _customCommand.func = CC_CALLBACK_0(SkeletonNode::onDraw, this, parentTransform, parentFlags);
        renderer->addCommand(&_customCommand);
        for (int i = 0; i < 8; ++i)
        {
            Vec4 pos;
            pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
            pos.w = 1;
            _modelViewTransform.transformVector(&pos);
            _noMVPVertices[i] = Vec3(pos.x, pos.y, pos.z) / pos.w;
        }


        this->draw(renderer, parentTransform, parentFlags);
        _batchBoneCommand.init(_globalZOrder, parentTransform, parentFlags);
        _batchBoneCommand.func = CC_CALLBACK_0(SkeletonNode::batchDrawAllSubBones, this, parentTransform);
        renderer->addCommand(&_batchBoneCommand);
    }
}

void SkeletonNode::batchDrawAllSubBones(const Mat4 &transform)
{
    if (_sortedAllBonesDirty)
        updateSortedAllBones();

    //_batchedBoneVetices.clear();
    //_batchedBoneColors.clear();
    _batchedVeticesCount = 0;
    for (const auto& bone : _sortedAllBones)
    {
        bone->batchToSkeleton();
    }
    Vec3* vetices = _batchedBoneVetices.data();
    Color4F* veticesColor = _batchedBoneColors.data();
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

#ifdef EMSCRIPTEN
    setGLBufferData(vetices, _batchedVeticesCount * sizeof(Vec3), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(veticesColor, _batchedVeticesCount * sizeof(Color4F), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, vetices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, veticesColor);
#endif // EMSCRIPTEN

    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    
#ifdef CC_STUDIO_ENABLED_VIEW
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    for(int i= 0; i < _batchedVeticesCount; i += 8)
    {
        glDrawArrays(GL_TRIANGLE_FAN, i, 4);
        glDrawArrays(GL_LINE_LOOP, i + 4, 4);
    }
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _batchedVeticesCount);
#else
    for (int i = 0; i < _batchedVeticesCount; i += 4)
    {
        glDrawArrays(GL_TRIANGLE_FAN, i, 4);
    }
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _batchedVeticesCount);
#endif //CC_STUDIO_ENABLED_VIEW
}


void SkeletonNode::onDraw(const Mat4 &transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

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
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
#endif // EMSCRIPTEN

    GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);
}

void SkeletonNode::setLength(float length)
{
    setContentSize(Size(length, length));
}

void SkeletonNode::changeDisplays(const StdStringMap& boneSkinNameMap)
{
    for (auto &boneskin : boneSkinNameMap)
    {
        auto bone = getBoneNode(boneskin.first);
        if ( nullptr != bone)
            bone->displaySkins(boneskin.second, true);
    }
}

void SkeletonNode::changeDisplays(const std::string& suitName)
{
    auto suit = _suitMap.find(suitName);
    if (suit != _suitMap.end())
    {
        changeDisplays(suit->second);
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

const Map<std::string, BoneNode*>& SkeletonNode::getAllSubBonesMap() const
{
    return _subBonesMap;
}

Mat4 SkeletonNode::getBoneToSkeletonTransform() const
{
    if(nullptr != dynamic_cast<BoneNode*>(_parent))
        return BoneNode::getBoneToSkeletonTransform();
    return Mat4::IDENTITY;
}

AffineTransform SkeletonNode::getBoneToSkeletonAffineTransform() const
{
    if(nullptr != dynamic_cast<BoneNode*>(_parent))
        return BoneNode::getBoneToSkeletonAffineTransform();
    return AffineTransform::IDENTITY;
}

Mat4 SkeletonNode::getSkinToSkeletonTransform(SkinNode* skin)
{
    auto boneParent = dynamic_cast<BoneNode*>(skin->getParent());
    if (boneParent == nullptr)
    {
        CCLOG("skin %s is not a skin or have not been added to a bone", skin->getName().c_str());
        return Mat4::IDENTITY;
    }
    return boneParent->getBoneToSkeletonTransform() * skin->getNodeToParentTransform();
}

AffineTransform SkeletonNode::getSkinToSkeltonAffineTransform(SkinNode* skin)
{
    auto boneParent = dynamic_cast<BoneNode*>(skin->getParent());
    if (boneParent == nullptr)
    {
        CCLOG("skin %s is not a skin or have not been added to a bone", skin->getName().c_str());
        return AffineTransform::IDENTITY;
    }
    return AffineTransformConcat(skin->getNodeToParentAffineTransform(), boneParent->getBoneToSkeletonAffineTransform());
}

void SkeletonNode::addSuitInfo(std::string suitName, StdStringMap boneSkinNameMap)
{
    _suitMap.insert(std::make_pair(suitName, boneSkinNameMap));
}

void SkeletonNode::updateSortedAllBones()
{
    _sortedAllBones.clear();
    for (const auto& bonepair : _subBonesMap)
    {
        _sortedAllBones.pushBack(bonepair.second);
    }
    std::sort(_sortedAllBones.begin(), _sortedAllBones.end(), nodeComparisonLess);
    _sortedAllBonesDirty = false;
}

NS_TIMELINE_END