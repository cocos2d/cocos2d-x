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

#ifndef __CCARMATURE_DATAS_H__
#define __CCARMATURE_DATAS_H__

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "base/CCMap.h"
#include "math/CCAffineTransform.h"

#include "cocostudio/CCArmatureDefine.h"
#include "2d/CCTweenFunction.h"
#include "cocostudio/CocosStudioExport.h"


#define CC_CREATE_NO_PARAM_NO_INIT(varType)\
public: \
    static inline varType *create(void){ \
    varType *var = new varType();\
    if (var)\
{\
    var->autorelease();\
    return var;\
}\
    CC_SAFE_DELETE(var);\
    return nullptr;\
}

#define CC_CREATE_NO_PARAM(varType)\
public: \
    static inline varType *create(void){ \
    varType *var = new varType();\
    if (var && var->init())\
{\
    var->autorelease();\
    return var;\
}\
    CC_SAFE_DELETE(var);\
    return nullptr;\
}

namespace cocostudio {

/**
 * @~english The base node include a lot of attributes.
 * @~chinese 根节点包含很多属性。
 * @js NA
 * @lua NA
 */
class CC_STUDIO_DLL BaseData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(BaseData)
public:
    /**
     * @js ctor
     */
    BaseData();
    /**
     * @js NA
     * @lua NA
     */
    ~BaseData(void);

    /*
    * @~english Copy data from node.
    * @~chinese 从节点复制数据。
    * @param node @~english A `BaseData` to be copied.
    * @~chinese 要复制的`BaseData`对象。
    */
    virtual void copy(const BaseData *node);

    /*
    * @~english Calculate two `BaseData`'s between value(to - from) and set to self.
    * @~chinese 计算两个`BaseData`的间距，并设置到自身。
    * @param from @~english from `BaseData`. @~chinese 自`BaseData`。
    * @param to @~english to `BaseData`. @~chinese 到`BaseData`。
    */
    virtual void subtract(BaseData *from, BaseData *to, bool limit);

    /*
    * @~english Set color.
    * @~chinese 设置颜色。
    * @param color @~english Color. 
    * @~chinese 颜色。
    */
    virtual void setColor(const cocos2d::Color4B &color);

    /*
    * @~english Get color.
    * @~chinese 获取颜色。
    * @return @~english Color.
    * @~chinese 颜色。
    */
    virtual cocos2d::Color4B getColor();
public:
    float x;                    //! position x attribute
    float y;                    //! position y attribute
    int zOrder;            //! zorder attribute, used to order the Bone's depth order

    /**
    * x y skewX skewY scaleX scaleY used to calculate transform matrix
    * skewX, skewY can have rotation effect
    * To get more matrix information, you can have a look at this pape : http://www.senocular.com/flash/tutorials/transformmatrix/
    */
    float skewX;
    float skewY;
    float scaleX;
    float scaleY;

    float tweenRotate;       //! SkewX, SkewY, and TweenRotate effect the rotation

    bool isUseColorInfo;    //! Whether or not this frame have the color changed Info
    int a, r, g, b;

};


/**
* DisplayType distinguish which type your display is.
*/
enum DisplayType
{
    CS_DISPLAY_SPRITE,                //! display is a single Sprite
    CS_DISPLAY_ARMATURE,         //! display is a Armature
    CS_DISPLAY_PARTICLE,            //! display is a CCParticle.

    CS_DISPLAY_MAX
};
/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DisplayData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(DisplayData)

    /*
    * @~english Change display to texutre.
    * @~chinese 将显示更换至材质。。
    * @param displayName @~english Display name.
    * @~chinese 显示名称。
    * @return @~english New display name.
    * @~chinese 新的显示名称。
    */
    static const std::string changeDisplayToTexture(const std::string& displayName);
public:
    /**
     * @js ctor
     */
    DisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~DisplayData(void) {}

    /*
    * @~english Copy data from displayData.
    * @~chinese 从显示数据复制数据。
    * @param node @~english A `DisplayData` to be copied.
    * @~chinese 要复制的`DisplayData`对象。
    */
    virtual void copy(DisplayData *displayData);

    DisplayType displayType;    //! mark which type your display is
    std::string displayName;
};


/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL SpriteDisplayData : public DisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(SpriteDisplayData)
public:
    /**
     * @js ctor
     */
    SpriteDisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteDisplayData() {};

    /*
    * @~english Copy data from displayData.
    * @~chinese 从显示数据复制数据。
    * @param node @~english A `DisplayData` to be copied.
    * @~chinese 要复制的`DisplayData`对象。
    */
    void copy(DisplayData *displayData);
public:
    BaseData skinData;
};

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL ArmatureDisplayData  : public DisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(ArmatureDisplayData)
public:
    /**
     * @js ctor
     */
    ArmatureDisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ArmatureDisplayData() {}
};

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL ParticleDisplayData : public DisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(ParticleDisplayData)
public:
    /**
     * @js ctor
     */
    ParticleDisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleDisplayData() {};
};



/**
* @~english BoneData used to init a Bone.
* BoneData keeps a DisplayData list, a Bone can have many display to change.
* The display information saved in the DisplayData
* @~chinese 用来初始化一段骨头的骨头数据。含有一个显示数据列表，骨头可以据据此进行多个显示的切换。
* 显示数据中包含显示信息。
* @js NA
* @lua NA
*/
class CC_STUDIO_DLL BoneData : public BaseData
{
public:
    CC_CREATE_NO_PARAM(BoneData)
public:
    /**
     * @js ctor
     */
    BoneData(void);
    /**
     * @js NA
     * @lua NA
     */
    ~BoneData(void);

    virtual bool init();

    /*
    * @~english Add displayData.
    * @~chinese 增加显示数据。
    * @param displayData @~english A `DisplayData` to be added.
    * @~chinese 要增加的`DisplayData`对象。
    */
    void addDisplayData(DisplayData *displayData);

    /*
    * @~english Get displayData.
    * @~chinese 获取显示数据。
    * @param index @~english The displayData's index.
    * @~chinese 显示数据的索引。
    * @return @~english The displayData.
    * @~chinese 显示数据。
    */
    DisplayData *getDisplayData(int index);
public:
    std::string name;                //! the bone's name
    std::string parentName;     //! the bone parent's name
    cocos2d::Vector<DisplayData*> displayDataList;    //! save DisplayData informations for the Bone
    cocos2d::AffineTransform boneDataTransform;
};


/**
* @~english ArmatureData saved the Armature name and Bonedata needed for the CCBones in this Armature
* When we create a Armature, we need to get each Bone's BoneData as it's init information.
* So we can get a `BoneData` from the Dictionary saved in the ArmatureData.
* @~chinese 骨骼数据保存骨骼的名称和骨骼中的`CCBone`对象们所需的骨头数据，当创建骨骼的时候，需要获得每段骨头的骨头数据作为其初始化信息。
* 因此可以从骨骼数据中保存的`BoneData`集合中获取其中的骨头数据。
* @js NA
* @lua NA
*/
class CC_STUDIO_DLL ArmatureData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(ArmatureData)
public:
    /**
     * @js ctor
     */
    ArmatureData();
    /**
     * @js NA
     * @lua NA
     */
    ~ArmatureData();

    bool init();

    /*
    * @~english Add boneData.
    * @~chinese 增加骨头数据。
    * @param boneData @~english A `BoneData` to be added.
    * @~chinese 要增加的`BoneData`对象。
    */
    void addBoneData(BoneData *boneData);

    /*
    * @~english Get boneData.
    * @~chinese 获取骨头数据。
    * @param boneName @~english The boneData's name.
    * @~chinese 骨头数据的名称。
    * @return @~english The boneData.
    * @~chinese 骨头数据。
    */
    BoneData *getBoneData(const std::string& boneName);
public:
    std::string name;
    cocos2d::Map<std::string, BoneData*> boneDataDic;
    float dataVersion;
};

enum BlendType
{
    BLEND_NORMAL,
    BLEND_LAYER,
    BLEND_DARKEN,
    BLEND_MULTIPLY,
    BLEND_LIGHTEN,
    BLEND_SCREEN,
    BLEND_OVERLAY,
    BLEND_HARD_LIGHT,
    BLEND_ADD,
    BLEND_SUBSTRACT,
    BLEND_DIFFERENCE,
    BLEND_INVERT,
    BLEND_ALPHA,
    BLEND_ERASE
};

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL FrameData : public BaseData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(FrameData)
public:
    /**
     * @js ctor
     */
    FrameData();
    /**
     * @js NA
     * @lua NA
     */
    ~FrameData();

    /*
    * @~english Copy data from node.
    * @~chinese 从节点复制数据。
    * @param node @~english A `BaseData` to be copied.
    * @~chinese 要复制的`BaseData`对象。
    */
    virtual void copy(const BaseData *baseData);
public:
    int frameID;
    int duration;                //! The frame will last duration frames

    cocos2d::tweenfunc::TweenType tweenEasing;     //! Every frame's tween easing effect
    int easingParamNumber;
    float *easingParams;

    bool isTween;                //! Whether it's a tween key frame

    /**
    * The current display index when change to this frame.
    * If value is -1, then display will not be shown.
    */
    int displayIndex;

    cocos2d::BlendFunc blendFunc;

    std::string strEvent;
    /**
    * strMovement, strEvent, strSound, strSoundEffect do not support yet
    */
    std::string strMovement;
    std::string strSound;
    std::string strSoundEffect;
};

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL MovementBoneData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(MovementBoneData)
public:
    /**
     * @js ctor
     */
    MovementBoneData();
    /**
     * @js NA
     * @lua NA
     */
    ~MovementBoneData(void);

    virtual bool init();

    /*
    * @~english Add frameData.
    * @~chinese 增加帧数据。
    * @param boneData @~english A `FrameData` to be added.
    * @~chinese 要增加的`FrameData`对象。
    */
    void addFrameData(FrameData *frameData);

    /*
    * @~english Get frameData.
    * @~chinese 获取帧数据。
    * @param index @~english The frameData's index.
    * @~chinese 帧数据的索引。
    * @return @~english The frameData.
    * @~chinese 帧数据。
    */
    FrameData *getFrameData(int index);
public:
    float delay;             //! movement delay percent, this value can produce a delay effect
    float scale;             //! scale this movement
    float duration;        //! this Bone in this movement will last m_iDuration frames
    std::string name;    //! bone name

    cocos2d::Vector<FrameData*> frameList;
};

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL MovementData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(MovementData)
public:
    /**
     * @js ctor
     */
    MovementData(void);
    /**
     * @js NA
     * @lua NA
     */
    ~MovementData(void);

    /*
    * @~english Add movBoneData.
    * @~chinese 增加活动骨头数据。
    * @param movBoneData @~english A `MovementBoneData` to be added.
    * @~chinese 要增加的`MovementBoneData`对象。
    */
    void addMovementBoneData(MovementBoneData *movBoneData);

    /*
    * @~english Get movBoneData.
    * @~chinese 获取活动骨头数据。
    * @param boneName @~english The boneData's name.
    * @~chinese 活动骨头数据的名称。
    * @return @~english The movBoneData.
    * @~chinese 活动骨头数据。
    */
    MovementBoneData *getMovementBoneData(const std::string& boneName);
public:
    std::string name;
    int duration;        //! the frames this movement will last
    float scale;          //! scale this movement

    /**
    * Change to this movement will last durationTo frames. Use this effect can avoid too suddenly changing.
    *
    * Example : current movement is "stand", we want to change to "run", then we fill durationTo frames before
    * change to "run" instead of changing to "run" directly.
    */
    int durationTo;

    /*
    * This is different from duration, durationTween contain tween effect.
    * duration is the raw time that the animation will last, it's the same with the time you edit in the Action Editor.
    * durationTween is the actual time you want this animation last.
    * Example : If we edit 10 frames in the flash, then duration is 10. When we set durationTween to 50, the movement will last 50 frames, the extra 40 frames will auto filled with tween effect
    */
    int durationTween;

    bool loop;           //! whether the movement was looped

    /**
    * Which tween easing effect the movement use
    * TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
    */
    cocos2d::tweenfunc::TweenType tweenEasing;

    /**
    * @brief    save movment bone data
    * @key    const std::string& 
    * @value    MovementBoneData *
    */
    cocos2d::Map<std::string, MovementBoneData*> movBoneDataDic;
};


/**
*  AnimationData include all movement information for the Armature
*  The struct is AnimationData -> MovementData -> MovementBoneData -> FrameData
*                                              -> MovementFrameData
*  @js NA
*  @lua NA
*/
class CC_STUDIO_DLL AnimationData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(AnimationData)
public:
    /**
     * @js ctor
     */
    AnimationData(void);
    /**
     * @js NA
     * @lua NA
     */
    ~AnimationData(void);

    /*
    * @~english Add movement data.
    * @~chinese 增加活动数据。
    * @param movData @~english A `MovementData` to be added.
    * @~chinese 要增加的`MovementData`对象。
    */
    void addMovement(MovementData *movData);

    /*
    * @~english Get movement data.
    * @~chinese 获取活动数据。
    * @param movementName @~english The movement data's name.
    * @~chinese 活动数据的名称。
    * @return @~english The movement data.
    * @~chinese 活动数据。
    */
    MovementData *getMovement(const std::string& movementName);

    /*
    * @~english Get movement data's count.
    * @~chinese 获取活动数据的总数。
    * @return @~english Movement data's count.
    * @~chinese 活动数据的总数。
    */
    ssize_t getMovementCount();
public:
    std::string name;
    cocos2d::Map<std::string, MovementData*> movementDataDic;
    std::vector<std::string> movementNames;
};



/*
* ContourData include a contour vertex information
* @js NA
* @lua NA
*/
class CC_STUDIO_DLL ContourData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(ContourData)
public:
    /**
     * @js ctor
     */
    ContourData();
    /**
     * @js NA
     * @lua NA
     */
    ~ContourData(void);

    virtual bool init();
    /*
    * @~english Add vertext.
    * @~chinese 增加顶点。
    * @param vertex @~english A vertex to be added.
    * @~chinese 要增加的顶点。
    */
    virtual void addVertex(cocos2d::Vec2 &vertex);
public:
    std::vector<cocos2d::Vec2> vertexList;    //! Save contour vertex info, vertex saved in a Vec2
};




/*
* TextureData include a texture's information
* @js NA
* @lua NA
*/
class CC_STUDIO_DLL TextureData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(TextureData)
public:
    /**
     * @js ctor
     */
    TextureData();
    /**
     * @js NA
     * @lua NA
     */
    ~TextureData(void);

    virtual bool init();

    /*
    * @~english Add contour data.
    * @~chinese 增加轮廓数据。
    * @param contourData @~english A `ContourData` to be added.
    * @~chinese 要增加的`ContourData`对象。
    */
    void addContourData(ContourData *contourData);

    /*
    * @~english Get contour data.
    * @~chinese 获取轮廓数据。
    * @param index @~english The contour data's index.
    * @~chinese 轮廓数据的索引。
    * @return @~english The contour data.
    * @~chinese 轮廓数据。
    */
    ContourData *getContourData(int index);
public:

    float height;        //! The texture's width, height
    float width;

    float pivotX;        //! The texture's anchor point
    float pivotY;

    std::string name;    //! The texture's name

    cocos2d::Vector<ContourData*> contourDataList;
};


}

#endif /*__CCARMATURE_DATAS_H__*/
