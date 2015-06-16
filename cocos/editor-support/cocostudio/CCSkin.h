/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCSKIN_H__
#define __CCSKIN_H__

#include "2d/CCSprite.h"
#include "renderer/CCQuadCommand.h"

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

class CC_STUDIO_DLL Skin : public cocos2d::Sprite
{
public:
    static Skin *create();
    static Skin *createWithSpriteFrameName(const std::string& pszSpriteFrameName);
    static Skin *create(const std::string& pszFileName);
public:
    /**
     *  @js ctor
     */
    Skin();

    virtual bool initWithSpriteFrameName(const std::string& spriteFrameName) override;
    virtual bool initWithFile(const std::string& filename) override;

    /**
    * @~english Updates the quad according the armature.
    * @~chinese 通过骨骼变换矩阵更新。
    */
    void updateArmatureTransform();
    void updateTransform() override;

    cocos2d::Mat4 getNodeToWorldTransform() const override;

    /**
    * @~english Returns the armature world affine transform matrix. The matrix is in Pixels.
    * @~chinese 返回节点到骨骼世界坐标仿射变换矩阵。矩阵单位是像素。
    *
    * @return @~english transformation matrix, in pixels. @~chinese 节点到骨骼世界坐标仿射变换矩阵
    */
    cocos2d::Mat4 getNodeToWorldTransformAR() const;
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
    /**
     *  @js NA
     *  @lua NA
     * @~english Set skin data.
     * @~chinese 设置皮肤数据。
     * @param data @~english Skin data.
     * @~chinese 皮肤数据。
     */
    virtual void setSkinData(const BaseData &data);
    /**
    *  @js NA
    *  @lua NA
    * @~english Get skin data.
    * @~chinese 获取皮肤数据。
    * @return @~english Skin data.
    * @~chinese 皮肤数据。
    */
    virtual const BaseData &getSkinData() const;

    /**
    * @~english Set bone.
    * @~chinese 设置骨头。
    * @param bone @~english Bone.
    * @~chinese 骨头。
    */
    virtual void setBone(Bone *bone);
    /**
    * @~english Get bone.
    * @~chinese 获取骨头。
    * @return @~english Bone.
    * @~chinese 骨头。
    */
    virtual Bone *getBone() const;

    /**
    * @~english Get display name.
    * @~chinese 获取显示名称。
    * @return @~english Display name.
    * @~chinese 显示名称。
    */
    virtual const std::string &getDisplayName() const { return _displayName; }
protected:
    BaseData _skinData;
    Bone *_bone;
    Armature *_armature;
    cocos2d::Mat4 _skinTransform;
    std::string _displayName;
    cocos2d::QuadCommand _quadCommand;     // quad command
};

}

#endif /*__CCSKIN_H__*/
