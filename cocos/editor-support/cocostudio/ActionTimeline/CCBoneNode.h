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

    /**
    * add a child bone named bone->getName()
    */
    virtual void addChildBone(BoneNode* bone);

    virtual const  cocos2d::Vector<BoneNode*>& getChildBones() const { return _childBones; }
    virtual  cocos2d::Vector<BoneNode*>&  getChildBones() { return _childBones; }

    virtual void removeFromParent() override;

    virtual const  cocos2d::Vector<SkinNode*>& getSkins() const { return _boneSkins; }
    virtual  cocos2d::Vector<SkinNode*>&  getSkins() { return _boneSkins; }

    /**
    *
    * @brief: display skin
    * @param: hideOthers, set other skins visible 
    */
    virtual void displaySkin(SkinNode* skin, bool hideOthers);

    /**
    *
    * @brief: display all skins named skinName, if hide display only one skin,
    *          prefer to use display(SkinNode* skin, bool hideOthers = false)
    * @param: hideOthers, set other skins visible
    */
    virtual void displaySkins(const std::string &skinName, bool hideOthers );

    virtual cocos2d::Vector<SkinNode*> getDisplayingSkins() const;

    virtual SkeletonNode* getRootSkeletonNode() const;

    /**
    * @brief: get all bones in this bone tree
    */
    cocos2d::Vector<BoneNode*> getAllSubBones() const;

    /**
    * @brief: get all skins in this bone tree
    */
    cocos2d::Vector<SkinNode*> getAllSubDisplays() const;

    virtual void addChild(cocos2d::Node* child, int localZOrder, const std::string &name) override;
    virtual void removeChild(Node* child, bool cleanup ) override;

    // blendFunc
    virtual void setBlendFunc(const cocos2d::BlendFunc &blendFunc) override;
    virtual const cocos2d::BlendFunc & getBlendFunc() const override { return _blendFunc; }


    // bone operate
    virtual void setLength(float length);
    virtual float getLength() const { return _contentSize.width; }

    // no need to change this at usual
    virtual void setWidth(float width);
    virtual float getWidth() const { return _contentSize.height; }

    // is rack show
    virtual void setDebugDrawEnabled(bool isDebugDraw);
    virtual bool isDebugDrawEnabled() const { return _isRackShow; }

    virtual void setDebugDrawColor(const cocos2d::Color4F &color);
    virtual cocos2d::Color4F getDebugDrawColor() const { return _rackColor; }

    /**
    *get displayings rect in self transform
    */
    virtual cocos2d::Rect getVisibleSkinsRect() const;

    /**
    * boundingbox depends getDisplayingRect, apply it in parent transform
    */
    virtual cocos2d::Rect getBoundingBox() const override;

    virtual cocos2d::Mat4 getBoneToSkeletonTransform() const;

    virtual cocos2d::AffineTransform getBoneToSkeletonAffineTransform() const;

    // transform & draw
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

    /**
    * get bone debugdraw's vertices, return a Vec2[4]
    */
    virtual void batchToSkeleton() const;

    // override
    virtual void setContentSize(const cocos2d::Size &size) override;

    virtual void setLocalZOrder(int localZOrder) override;

    virtual void setName(const std::string& name) override;

#ifdef CC_STUDIO_ENABLED_VIEW
    virtual bool isPointOnRack(const cocos2d::Vec2& bonePoint);
#endif

CC_CONSTRUCTOR_ACCESS :
    BoneNode();
    virtual ~BoneNode();
    virtual bool init() override;

protected:
    virtual void addToBoneChildren(BoneNode* bone);

    virtual void removeFromBoneChildren(BoneNode* bone);

    virtual void removeFromParentBone();
   
    virtual void addToSkinList(SkinNode* skin);
    virtual void removeFromSkinList(SkinNode* skin);

    virtual void sortAllChildren() override;

    virtual void updateVertices();
    virtual void updateColor() override;

    virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags); 


protected:
    cocos2d::CustomCommand _customCommand;
    cocos2d::BlendFunc     _blendFunc;

    bool              _isRackShow;
    cocos2d::Color4F  _rackColor;

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