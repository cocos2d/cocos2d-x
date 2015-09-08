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

#include "3d/CCAttachNode.h"
#include "3d/CCSkeleton3D.h"

NS_CC_BEGIN

AttachNode* AttachNode::create(Bone3D* attachBone)
{
  return AttachNode::create(attachBone, Mat4::IDENTITY);
}

AttachNode* AttachNode::create(const Mat4& offset) {
  return AttachNode::create(nullptr, offset);
}

AttachNode* AttachNode::create(Bone3D* attachBone, const Mat4& offset)
{
  auto attachnode = new (std::nothrow) AttachNode();
  attachnode->_attachBone = attachBone;
  attachnode->autorelease();
  attachnode->_attachOffset = offset;
  return attachnode;
}

AttachNode::AttachNode()
: _attachBone(nullptr)
{
  _attachOffset = Mat4::IDENTITY;
}
AttachNode::~AttachNode()
{
    
}

Mat4 AttachNode::getWorldToNodeTransform() const
{
    static Mat4 mat;
    mat.setIdentity();
    auto parent = getParent();
    if (parent)
    {
        mat = parent->getWorldToNodeTransform();
    }
  
    mat = mat *  _attachBone->getWorldMat() * Node::getNodeToParentTransform();
  
    return mat;
}

Mat4 AttachNode::getFullAttachTransform() const
{
  if (_attachBone) {
    return _attachBone->getWorldMat() * _attachOffset;
  } else {
    return _attachOffset;
  }
}

void AttachNode::setOffsetTransform(const Mat4& offset)
{
  _attachOffset = offset;
}

Mat4 AttachNode::getNodeToWorldTransform() const
{
    return Node::getNodeToWorldTransform();
}

const Mat4& AttachNode::getNodeToParentTransform() const
{
    Node::getNodeToParentTransform();
    _transformToParent = getFullAttachTransform() * _transform;
    return _transformToParent;
}

void AttachNode::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    Node::visit(renderer, parentTransform, Node::FLAGS_DIRTY_MASK);
}
NS_CC_END

