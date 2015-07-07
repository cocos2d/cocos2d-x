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

#include "CCPlatformMacros.h"
#include "CCTimelineMacro.h"
#include "renderer/CCRenderer.h"
#include "cocostudio/CocosStudioExport.h"
#include "base/CCMap.h"

#include "CCBoneNode.h"



// for test

#ifndef ENABLE_PHYSICS_BOX2D_DETECT
#define  ENABLE_PHYSICS_BOX2D_DETECT    1
#endif // !ENABLE_PHYSICS_BOX2D_DETECT

//end test

class b2Body;
struct cpBody;

NS_TIMELINE_BEGIN

class CC_STUDIO_DLL SkeletonNode : public BoneNode
{
    friend class BoneNode;

public:
    static SkeletonNode* create();

    void setAllRackShow(bool showRack);

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
    *@param: boneSkinNameMap, map <bone name, name of skin to display which added to bone>
    */
    void changeDisplays(const std::map<std::string, std::string> &boneSkinNameMap);

    virtual cocos2d::Mat4 getBoneToSkeletonTransform() const override;

    virtual cocos2d::AffineTransform getBoneToSkeletonAffineTransform() const override;

    static cocos2d::Mat4 getSkinToSkeletonTransform(SkinNode* skin);

    static cocos2d::AffineTransform getSkinToSkeltonAffineTransform(SkinNode* skin);

    //override

    void setLength(float length) override;
    void setContentSize(const cocos2d::Size &size) override;


    bool isAllRackShow() const { return _isAllRackShow; }

    cocos2d::Rect getBoundingBox() const override;

// 
//      //physics
//  
//  #if ENABLE_PHYSICS_BOX2D_DETECT
//      virtual b2Fixture *getShapeList();
//      /**
//      *  @js NA
//      *  @lua NA
//      */
//      virtual void setBody(b2Body *body);
//      /**
//      *  @js NA
//      *  @lua NA
//      */
//      virtual b2Body *getBody() const;
//  #elif ENABLE_PHYSICS_CHIPMUNK_DETECT
//      /**
//      *  @js NA
//      *  @lua NA
//      */
//      virtual cpShape *getShapeList();
//      /**
//      *  @js NA
//      *  @lua NA
//      */
//      virtual void setBody(cpBody *body);
//      /**
//      *  @js NA
//      *  @lua NA
//      */
//      virtual cpBody *getBody() const;
//  #endif

protected:
    SkeletonNode();
    virtual ~SkeletonNode();
    virtual bool init() override;

    virtual void updateVertices() override;
    virtual void updateColor() override;

    virtual void visit(cocos2d::Renderer *renderer, const  cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags) override;

protected:
    bool _isAllRackShow;

    cocos2d::Map<std::string, BoneNode*> _subBonesMap;
private:
    cocos2d::Vec2          _squareVertices[8];
    cocos2d::Color4F       _squareColors[8];
    cocos2d::Vec3          _noMVPVertices[8];


#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Body *_body;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpBody *_body;
#endif

    CC_DISALLOW_COPY_AND_ASSIGN(SkeletonNode);
};

NS_TIMELINE_END

#endif //__CCSKELETONNODE_H__
