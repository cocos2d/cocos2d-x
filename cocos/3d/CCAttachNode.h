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

#ifndef __CCATTACHNODE_H__
#define __CCATTACHNODE_H__

#include "math/CCMath.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

class Bone3D;

/** 
 * attach a node to a bone
 * usage: auto sprite = Sprite3D::create("girl.c3b");
 *        auto weapon = Sprite3D::create("weapon.c3b");
 *        auto attachNode = sprite->getAttachNode("left hand");
 *        attachNode->addChild(weapon);
 */
class CC_DLL AttachNode : public Node
{
public:
    /** 
     * creates an AttachNode
     * @param attachBone The bone to which the AttachNode is going to attach, the attacheBone must be a bone of the AttachNode's parent
     */
    static AttachNode* create(Bone3D* attachBone);
    
    virtual Mat4 getWorldToNodeTransform() const override;
    virtual Mat4 getNodeToWorldTransform() const override;
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

CC_CONSTRUCTOR_ACCESS:
    
    AttachNode();
    virtual ~AttachNode();
    

protected:
    Bone3D* _attachBone;
};


NS_CC_END
#endif // __CCATTACHNODE_H__
