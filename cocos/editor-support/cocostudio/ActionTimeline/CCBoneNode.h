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


#ifndef __CCBONENODE_H__
#define __CCBONENODE_H__

#include "base/CCProtocols.h"
#include "2d/CCLayer.h"
#include "CCTimelineMacro.h"
#include "cocostudio/CocosStudioExport.h"

#include "CCSkinNode.h"

NS_TIMELINE_BEGIN

class SkeletonNode;

class CC_STUDIO_DLL BoneNode : public cocos2d::Node, public cocos2d::BlendProtocol
{
public:
    static BoneNode* create();
    static BoneNode* create(const int &length);

    using Node::addChild;
    // add child, deal with BoneNode and SkinNode
    virtual void addChild(cocos2d::Node* child, int localZOrder, const std::string &name) override;
    virtual void addChild(cocos2d::Node* child, int localZOrder, int tag) override;

    virtual void removeChild(Node* child, bool cleanup) override;

    virtual const  cocos2d::Vector<BoneNode*>& getChildBones() const { return _childBones; }
    virtual cocos2d::Vector<BoneNode*>&  getChildBones() { return _childBones; }

    /**
    *@brief: add a skin
    *@param: display, whether display this skin
    */
    virtual void addSkin(SkinNode* skin, bool display);

    /**
    *@brief: add a skin
    *@param: display, whether display this skin
    *@param: hideOthers, whether hide other skins added to this bone
    */
    virtual void addSkin(SkinNode* skin, bool display, bool hideOthers);

    virtual const  cocos2d::Vector<SkinNode*>& getSkins() const { return _boneSkins; }
    virtual  cocos2d::Vector<SkinNode*>&  getSkins() { return _boneSkins; }

    /**
    * @brief: display skin
    * @param: hideOthers, set other skins invisible 
    */
    virtual void displaySkin(SkinNode* skin, bool hideOthers);

    /**
    * @brief: display all skins named skinName, if hide display only one skin,
    *         prefer to use display(SkinNode* skin, bool hideOthers = false)
    * @param: hideOthers, set other skins invisible
    */
    virtual void displaySkin(const std::string &skinName, bool hideOthers );

    // get the skins which is visible (displaying skins)
    virtual cocos2d::Vector<SkinNode*> getVisibleSkins() const;
    
    virtual SkeletonNode* getRootSkeletonNode() const;

    /**
    * @brief: get all bones in this bone tree
    */
    cocos2d::Vector<BoneNode*> getAllSubBones() const;

    /**
    * @brief: get all skins in this bone tree
    */
    cocos2d::Vector<SkinNode*> getAllSubSkins() const;

    // blendFunc
    virtual void setBlendFunc(const cocos2d::BlendFunc &blendFunc) override;
    virtual const cocos2d::BlendFunc & getBlendFunc() const override { return _blendFunc; }

    // is rack show, bone can be drawn when bone is visible && enable debug draw
    virtual void setDebugDrawEnabled(bool isDebugDraw);
    virtual bool isDebugDrawEnabled() const { return _isRackShow; }

    virtual void setDebugDrawLength(float length);
    virtual float getDebugDrawLength() const { return _rackLength; }

    virtual void setDebugDrawWidth(float width);
    virtual float getDebugDrawWidth() const { return _rackWidth; }

    virtual void setDebugDrawColor(const cocos2d::Color4F &color);
    virtual cocos2d::Color4F getDebugDrawColor() const { return _rackColor; }

    // get bone's bondingbox, depends on getVisibleSkinsRect, apply on node to parent's tranform
    cocos2d::Rect getBoundingBox() const override;

    /**
    *get displayings rect in self transform
    */
    virtual cocos2d::Rect getVisibleSkinsRect() const;

    // transform & draw
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

    virtual void setLocalZOrder(int localZOrder) override;

    virtual void setName(const std::string& name) override;

    virtual void setVisible(bool visible) override;

    virtual void setContentSize(const cocos2d::Size& contentSize);

    virtual void setAnchorPoint(const cocos2d::Vec2& anchorPoint);
    
#ifdef CC_STUDIO_ENABLED_VIEW
    // hit test , bonePoint is in self coordinate
    virtual bool isPointOnRack(const cocos2d::Vec2& bonePoint);
#endif

CC_CONSTRUCTOR_ACCESS:
    BoneNode();
    virtual ~BoneNode();
    virtual bool init() override;

protected:

    virtual void addToChildrenListHelper(Node * child);
    virtual void removeFromChildrenListHelper(Node * child);

    // add bone to children bone list, and add bone to skeleton's subbone map
    virtual void addToBoneList(BoneNode* bone);

    // remove bone from children bone list, and remove bone from skeleton's subbone map
    virtual void removeFromBoneList(BoneNode* bone);

    // add skin to skin list
    virtual void addToSkinList(SkinNode* skin);

    // remove skin from skin list
    virtual void removeFromSkinList(SkinNode* skin);

    // sort all _children ,  bone list and skin list
    virtual void sortAllChildren() override;

    virtual void updateVertices();
    virtual void updateColor() override;

    virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags); 

    // a help function for SkeletonNode
    // for batch bone's draw to _rootSkeleton
    virtual void batchBoneDrawToSkeleton(BoneNode* bone) const; 

protected:
    cocos2d::CustomCommand _customCommand;
    cocos2d::BlendFunc     _blendFunc;

    bool              _isRackShow;
    cocos2d::Color4F  _rackColor;
    int               _rackLength;
    int               _rackWidth;

    cocos2d::Vector<BoneNode*> _childBones;
    cocos2d::Vector<SkinNode*> _boneSkins;
    SkeletonNode*              _rootSkeleton;
private:
    cocos2d::Vec2          _squareVertices[4];
    cocos2d::Color4F       _squareColors[4];
    cocos2d::Vec3          _noMVPVertices[4];
    CC_DISALLOW_COPY_AND_ASSIGN(BoneNode);
};

NS_TIMELINE_END
#endif //__CCBONENODE_H__