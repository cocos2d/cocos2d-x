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

#ifndef __CCSKELETONNODE_H__
#define  __CCSKELETONNODE_H__

#include "CCTimelineMacro.h"
#include "renderer/CCRenderer.h"
#include "cocostudio/CocosStudioExport.h"
#include "base/CCMap.h"

#include "CCBoneNode.h"
#include <deque>

typedef std::map < std::string, std::string > StdStringMap;

NS_TIMELINE_BEGIN

class CC_STUDIO_DLL SkeletonNode : public BoneNode
{
    friend class BoneNode;

public:
    static SkeletonNode* create();

    /**
    *get bonenode in skeleton node by bone name
    */
    BoneNode* getBoneNode(const std::string& boneName);

    /**
    *get All bones in this skeleton, <bone's name, BoneNode>
    */
    const cocos2d::Map<std::string, BoneNode*>& getAllSubBonesMap() const;

    /**
    *@brief: change displays 
    *@param: boneSkinNameMap, map <name of bone, name of skin to display which added to bone>
    */
    void changeDisplays(const StdStringMap& boneSkinNameMap);

    /**
    *@brief: change displays
    *@param: suitName have
    */
    void changeDisplays(const std::string& suitName);

    /**
    * add a boneSkinNameMap asa suit
    *@param: suitName, key
    *@param: boneSkinNameMap, map <name of bone, name of skin to display which added to bone>
    */
    void addSuitInfo(std::string suitName, StdStringMap boneSkinNameMap);

    virtual cocos2d::Mat4 getBoneToSkeletonTransform() const override;

    virtual cocos2d::AffineTransform getBoneToSkeletonAffineTransform() const override;

    static cocos2d::Mat4 getSkinToSkeletonTransform(SkinNode* skin);

    static cocos2d::AffineTransform getSkinToSkeltonAffineTransform(SkinNode* skin);

    void setLength(float length) override;

    cocos2d::Rect getBoundingBox() const override;

protected:
    SkeletonNode();
    virtual ~SkeletonNode();
    virtual bool init() override;

    virtual void updateVertices() override;
    virtual void updateColor() override;

    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
    virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags) override;

protected:
    cocos2d::Map<std::string, BoneNode*> _subBonesMap;
private:
    cocos2d::Vec2          _squareVertices[8];
    cocos2d::Color4F       _squareColors[8];
    cocos2d::Vec3          _noMVPVertices[8];

    bool                           _sortedAllBonesDirty;
    cocos2d::Vector<BoneNode*>     _sortedAllBones;      // for draw faster, cache a list from _subBonesMap, sorted by z order
    std::vector<cocos2d::Vec3>     _batchedBoneVetices;
    std::vector<cocos2d::Color4F>  _batchedBoneColors;
    int                            _batchedVeticesCount;
    cocos2d::CustomCommand         _batchBoneCommand;

    void updateSortedAllBones();
    void batchDrawAllSubBones(const cocos2d::Mat4 &transform);
    void batchSubBone(BoneNode* bone);


    std::map<std::string, StdStringMap> _suitMap; // map< suit name, map< bone name, skin name> >
    CC_DISALLOW_COPY_AND_ASSIGN(SkeletonNode);
};

NS_TIMELINE_END

#endif //__CCSKELETONNODE_H__
