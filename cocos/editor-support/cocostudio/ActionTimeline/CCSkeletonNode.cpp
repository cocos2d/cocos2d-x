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
#include "CCSkeletonNode.h"

#include "base/CCDirector.h"
#include "math/TransformUtils.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include <stack>

using namespace cocos2d::GL;

NS_TIMELINE_BEGIN

SkeletonNode* SkeletonNode::create()
{
    SkeletonNode* skeletonNode = new (std::nothrow) SkeletonNode();
    if (skeletonNode && skeletonNode->init())
    {
        skeletonNode->autorelease();
        return skeletonNode;
    }
    CC_SAFE_DELETE(skeletonNode);
    return nullptr;
}


bool SkeletonNode::init()
{
    _rackLength = _rackWidth = 20; 
    updateVertices();
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
    _rootSkeleton = this;
    return true;
}

cocos2d::Rect SkeletonNode::getBoundingBox() const
{
    float minx, miny, maxx, maxy = 0;
    minx = miny = maxx = maxy;
    cocos2d::Rect boundingBox = getVisibleSkinsRect();
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
        cocos2d::Rect r = RectApplyAffineTransform(bone->getVisibleSkinsRect(),
                                          bone->getNodeToParentAffineTransform(bone->getRootSkeletonNode()));
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
, _subDrawBonesDirty(true)
, _subDrawBonesOrderDirty(true)
, _batchedVeticesCount(0)
{
}

SkeletonNode::~SkeletonNode()
{
}

void SkeletonNode::updateVertices()
{
    if (_rackLength != _squareVertices[6].x - _anchorPointInPoints.x || _rackWidth != _squareVertices[3].y - _anchorPointInPoints.y)
    {
        const float radiusl = _rackLength * .5f;
        const float radiusw = _rackWidth * .5f;
        const float radiusl_2 = radiusl * .25f;
        const float radiusw_2 = radiusw * .25f;
        _squareVertices[5].y = _squareVertices[2].y = _squareVertices[1].y = _squareVertices[6].y
            = _squareVertices[0].x = _squareVertices[4].x = _squareVertices[7].x = _squareVertices[3].x = .0f;
        _squareVertices[5].x = -radiusl; _squareVertices[0].y = -radiusw;
        _squareVertices[6].x =  radiusl;  _squareVertices[3].y = radiusw;
        _squareVertices[1].x =  radiusl_2; _squareVertices[7].y = radiusw_2;
        _squareVertices[2].x = - radiusl_2; _squareVertices[4].y = - radiusw_2;


        for (int i = 0; i < 8; i++)
        {
            _squareVertices[i] += _anchorPointInPoints;
        }

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


void SkeletonNode::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
{
    BoneNode::visit(renderer, parentTransform, parentFlags);
    if (_visible && _isRackShow)
    {
        _customCommand.init(_globalZOrder, parentTransform, parentFlags);
        _customCommand.func = CC_CALLBACK_0(SkeletonNode::onDraw, this, parentTransform, parentFlags);
        renderer->addCommand(&_customCommand);
        for (int i = 0; i < 8; ++i)
        {
            cocos2d::Vec4 pos;
            pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
            pos.w = 1;
            _modelViewTransform.transformVector(&pos);
            _noMVPVertices[i] = cocos2d::Vec3(pos.x, pos.y, pos.z) / pos.w;
        }

        this->draw(renderer, parentTransform, parentFlags);
        _batchBoneCommand.init(_globalZOrder, parentTransform, parentFlags);
        _batchBoneCommand.func = CC_CALLBACK_0(SkeletonNode::batchDrawAllSubBones, this, parentTransform);
        renderer->addCommand(&_batchBoneCommand);
    }
}

void SkeletonNode::batchDrawAllSubBones(const cocos2d::Mat4 &transform)
{
    if (_subDrawBonesDirty)
    {
        updateAllDrawBones();
    }
    if (_subDrawBonesOrderDirty)
        sortAllDrawBones();

    _batchedVeticesCount = 0;
    for (const auto& bone : _subDrawBones)
    {
        batchBoneDrawToSkeleton(bone);
    }
    cocos2d::Vec3* vetices = _batchedBoneVetices.data();
    cocos2d::Color4F* veticesColor = _batchedBoneColors.data();
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION | cocos2d::GL::VERTEX_ATTRIB_FLAG_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, vetices);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, veticesColor);

    cocos2d::GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    
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

void SkeletonNode::changeSkins(const std::map<std::string, std::string>& boneSkinNameMap)
{
    for (auto &boneskin : boneSkinNameMap)
    {
        auto bone = getBoneNode(boneskin.first);
        if ( nullptr != bone)
            bone->displaySkin(boneskin.second, true);
    }
}

void SkeletonNode::changeSkins(const std::string& skinGroupName)
{
    auto suit = _skinGroupMap.find(skinGroupName);
    if (suit != _skinGroupMap.end())
    {
        changeSkins(suit->second);
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

void SkeletonNode::addSkinGroup(std::string groupName, std::map<std::string, std::string> boneSkinNameMap)
{
    _skinGroupMap.insert(std::make_pair(groupName, boneSkinNameMap));
}

void SkeletonNode::updateAllDrawBones()
{
    _subDrawBones.clear();
    for (const auto& bonepair : _subBonesMap)
    {
        auto bone = bonepair.second;
        if (bone->isVisible() && bone->isDebugDrawEnabled())
            _subDrawBones.pushBack(bone);
    }
    _subDrawBonesDirty = false;
}

void SkeletonNode::sortAllDrawBones()
{
    std::sort(_subDrawBones.begin(), _subDrawBones.end(), cocos2d::nodeComparisonLess);
    _subDrawBonesOrderDirty = false;
}

NS_TIMELINE_END