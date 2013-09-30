/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "../utils/CCArmatureDefine.h"
#include "../utils/CCTweenFunction.h"


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
	return NULL;\
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
	return NULL;\
}

NS_CC_EXT_ARMATURE_BEGIN

/**
* The base node include a lot of attributes.
*/
class  BaseData : public Object
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
    * Copy data from node
    * @param  node A BaseData to copy data
    */
    virtual void copy(const BaseData *node);

    /*
    * Calculate two BaseData's between value(to - from) and set to self
    *
    * @param  from   from BaseData
    * @param  to     to BaseData
    */
    virtual void subtract(BaseData *from, BaseData *to, bool limit);

    virtual void setColor(const Color4B &color);
    virtual Color4B getColor();
public:
    float x;					//! position x attribute
    float y;					//! position y attribute
    int zOrder;			//! zorder attribute, used to order the Bone's depth order

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

class  DisplayData : public Object
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(DisplayData)

    static const char *changeDisplayToTexture(const char *displayName);
public:
	/**
     * @js ctor
     */
    DisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~DisplayData(void);

    DisplayType displayType;	//! mark which type your display is
};



class  SpriteDisplayData : public DisplayData
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
    virtual ~SpriteDisplayData();

    inline void setParam(const char *displayName)
    {
        this->displayName = displayName;
    }
    void copy(SpriteDisplayData *displayData);
public:
    /**
    * If DisplayType is CS_DISPLAY_SPRITE, then Bone will use this image name to create a Sprite from CCSpriteFrameCache.
    * It should note that when use this name to create Sprite from CCSpriteFrameCache, you should use _displayName + ".png", because when use Texture Packer to pack single image file, the name have ".png".
    *
    * If DisplayType is CS_DISPLAY_ARMATURE, the name is the Armature's name. When Bone init display and type is CS_DISPLAY_ARMATURE,
    * then Bone will create a Armature.
    */
    std::string displayName;

    BaseData skinData;
};


class  ArmatureDisplayData  : public DisplayData
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
    virtual ~ArmatureDisplayData();

    inline void setParam(const char *displayName)
    {
        this->displayName = displayName;
    }
    void copy(ArmatureDisplayData *displayData);
public:
    /**
    * If DisplayType is CS_DISPLAY_SPRITE, then Bone will use this image name to create a Sprite from CCSpriteFrameCache.
    * It should note that when use this name to create Sprite from CCSpriteFrameCache, you should use _displayName + ".png", because when use Texture Packer to pack single image file, the name have ".png".
    *
    * If DisplayType is CS_DISPLAY_ARMATURE, the name is the Armature's name. When Bone init display and type is CS_DISPLAY_ARMATURE,
    * then Bone will create a Armature.
    */
    std::string displayName;

};


class  ParticleDisplayData : public DisplayData
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

    void setParam(const char *plist)
    {
        this->plist = plist;
    }

    void copy(ParticleDisplayData *displayData);
public:
    std::string plist;
};



/**
* BoneData used to init a Bone.
* BoneData keeps a DisplayData list, a Bone can have many display to change.
* The display information saved in the DisplayData
*/
class  BoneData : public BaseData
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

    void addDisplayData(DisplayData *displayData);
    DisplayData *getDisplayData(int index);
public:
    std::string name;                //! the bone's name
    std::string parentName;     //! the bone parent's name
    Array displayDataList;    //! save DisplayData informations for the Bone
    AffineTransform boneDataTransform;
};


/**
* ArmatureData saved the Armature name and Bonedata needed for the CCBones in this Armature
* When we create a Armature, we need to get each Bone's BoneData as it's init information.
* So we can get a BoneData from the Dictionary saved in the ArmatureData.
*/
class  ArmatureData : public Object
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
    void addBoneData(BoneData *boneData);
    BoneData *getBoneData(const char *boneName);
public:
    std::string name;
    Dictionary boneDataDic;
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


class  FrameData : public BaseData
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

    virtual void copy(const BaseData *baseData);
public:
    int frameID;
    int duration;                //! The frame will last duration frames
    CCTweenType tweenEasing;     //! Every frame's tween easing effect
    bool isTween;                //! Whether it's a tween key frame

    /**
    * The current display index when change to this frame.
    * If value is -1, then display will not be shown.
    */
    int displayIndex;

    BlendType blendType;

    std::string strEvent;
    /**
    * strMovement, strEvent, strSound, strSoundEffect do not support yet
    */
    std::string strMovement;
    std::string strSound;
    std::string strSoundEffect;
};


class  MovementBoneData : public Object
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

    void addFrameData(FrameData *frameData);
    FrameData *getFrameData(int index);
public:
    float delay;             //! movement delay percent, this value can produce a delay effect
    float scale;             //! scale this movement
    float duration;        //! this Bone in this movement will last m_iDuration frames
    std::string name;    //! bone name

    Array frameList;
};


class  MovementData : public Object
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

    void addMovementBoneData(MovementBoneData *movBoneData);
    MovementBoneData *getMovementBoneData(const char *boneName);
public:
    std::string name;
    int duration;        //! the frames this movement will last
    float scale;		  //! scale this movement

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
    CCTweenType tweenEasing;

    /**
    * @brief	save movment bone data
    * @key	const char *
    * @value	MovementBoneData *
    */
    Dictionary movBoneDataDic;
};


/**
*  AnimationData include all movement infomation for the Armature
*  The struct is AnimationData -> MovementData -> MovementBoneData -> FrameData
*                                              -> MovementFrameData
*/
class  AnimationData : public Object
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

    void addMovement(MovementData *movData);
    MovementData *getMovement(const char *movementName);
    int getMovementCount();
public:
    std::string name;
    Dictionary movementDataDic;
    std::vector<std::string> movementNames;
};


struct ContourVertex2 : public Object
{
    ContourVertex2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    float x;
    float y;
};

/*
* ContourData include a contour vertex information
*/
class  ContourData : public Object
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
    virtual void addVertex(Point *vertex);
public:
    Array vertexList;	//! Save contour vertex info, vertex saved in a Point
};




/*
* TextureData include a texture's information
*/
class  TextureData : public Object
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

    void addContourData(ContourData *contourData);
    ContourData *getContourData(int index);
public:

    float height;		//! The texture's width, height
    float width;

    float pivotX;		//! The texture's anchor point
    float pivotY;

    std::string name;	//! The texture's name

    Array contourDataList;
};


NS_CC_EXT_ARMATURE_END

#endif /*__CCARMATURE_DATAS_H__*/
