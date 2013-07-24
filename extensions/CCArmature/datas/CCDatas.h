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


#define CS_CREATE_NO_PARAM_NO_INIT(varType)\
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

#define CS_CREATE_NO_PARAM(varType)\
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

namespace cocos2d { namespace extension { namespace armature {

/**
* the base node include a lot of attribute.
*/
class  BaseData : public Object
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(BaseData)
public:
    BaseData();
    ~BaseData(void);

    /*
    * Copy datas from node
    * @param  node A BaseData to copy datas
    */
    virtual void copy(const BaseData *_node);

    /*
    * Calculate two BaseData's between value(_to - _from) and set to self
    *
    * @param  from   from BaseData
    * @param  to     to BaseData
    */
    virtual void subtract(BaseData *_from, BaseData *_to);
public:
	float x;					//! position x attribute
	float y;					//! position y attribute
	int zOrder;					//! zorder attribute, used to order the Bone's depth order

    /**
    * x y skewX skewY scaleX scaleY used to calculate transform matrix
    * skewX, skewY can have rotation effect
    * To get more matrix information, you can have a look at this pape : http://www.senocular.com/flash/tutorials/transformmatrix/
    */
    float skewX;
    float skewY;
    float scaleX;
    float scaleY;

    float tweenRotate;			//! SkewX, SkewY, and TweenRotate effect the rotation

    bool isUseColorInfo;		//! Whether or not this frame have the color changed Info
    int a, r, g, b;

};


/**
* DisplayType distinguish which type you display is.
*/
enum DisplayType
{
    CS_DISPLAY_SPRITE,          //! display is a single Sprite
    CS_DISPLAY_ARMATURE,        //! display is a Armature
    CS_DISPLAY_PARTICLE,        //! display is a Particle.
    CS_DISPLAY_SHADER,          //! display is a shader

    CS_DISPLAY_MAX
};

class  DisplayData : public Object
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(DisplayData)

    static const char *changeDisplayToTexture(const char *);
public:
    DisplayData();
    virtual ~DisplayData(void);

    DisplayType displayType;	//! mark which type your display is
};



class  SpriteDisplayData : public DisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(SpriteDisplayData)
public:
    SpriteDisplayData();
    virtual ~SpriteDisplayData();

    inline void setParam(const char *displayName)
    {
        this->displayName = displayName;
    }
    void copy(SpriteDisplayData *displayData);
public:
    /**
    * If DisplayType is CS_DISPLAY_SPRITE, then Bone will use this image name to create a Sprite from SpriteFrameCache.
    * It should note that when use this name to create Sprite from SpriteFrameCache, you should use _displayName + ".png", because when use Texture Packer to pack single image file, the name have ".png".
    *
    * If DisplayType is CS_DISPLAY_ARMATURE, the name is the Armature's name. When Bone init display and type is CS_DISPLAY_ARMATURE,
    * then Bone will create a Armature.
    */
    std::string displayName;

};


class  ArmatureDisplayData  : public DisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(ArmatureDisplayData)
public:
    ArmatureDisplayData();
    virtual ~ArmatureDisplayData();

    inline void setParam(const char *displayName)
    {
        this->displayName = displayName;
    }
    void copy(ArmatureDisplayData *displayData);
public:
    /**
    * If DisplayType is CS_DISPLAY_SPRITE, then Bone will use this image name to create a Sprite from SpriteFrameCache.
    * It should note that when use this name to create Sprite from SpriteFrameCache, you should use _displayName + ".png", because when use Texture Packer to pack single image file, the name have ".png".
    *
    * If DisplayType is CS_DISPLAY_ARMATURE, the name is the Armature's name. When Bone init display and type is CS_DISPLAY_ARMATURE,
    * then Bone will create a Armature.
    */
    std::string displayName;

};


class  ParticleDisplayData : public DisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(ParticleDisplayData)
public:
    ParticleDisplayData();
    virtual ~ParticleDisplayData() {};

    void setParam(const char *plist)
    {
        this->plist = plist;
    }

    void copy(ParticleDisplayData *displayData);
public:
    std::string plist;
};


class  ShaderDisplayData : public DisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(ShaderDisplayData)
public:
    ShaderDisplayData();
    virtual ~ShaderDisplayData() {};

    inline void setParam(const char *vert, const char *frag)
    {
        this->vert = vert;
        this->frag = frag;
    }

    void copy(ShaderDisplayData *displayData);
public:
    std::string vert;
    std::string frag;
};


/**
* BoneData used to init a Bone.
* BoneData keeps a DisplayData list, a Bone can have many display to change.
* The display information saved in the DisplayData
*/
class  BoneData : public BaseData
{
public:
    CS_CREATE_NO_PARAM(BoneData)
public:
    BoneData(void);
    ~BoneData(void);

    virtual bool init();

    void addDisplayData(DisplayData *displayData);
    DisplayData *getDisplayData(int index);
public:
    std::string name;			//! the bone's name
    std::string parentName;		//! the bone parent's name
    Array displayDataList;	//! save DisplayData informations for the Bone
};


/**
* ArmatureData saved the Armature name and Bonedatas needed for the Bones in this Armature
* When we create a Armature, we need to get each Bone's BoneData as it's init information.
* So we can get a BoneData from the Dictionary saved in the ArmatureData.
*/
class  ArmatureData : public Object
{
public:
    CS_CREATE_NO_PARAM(ArmatureData)
public:
    ArmatureData();
    ~ArmatureData();

    bool init();
    void addBoneData(BoneData *boneData);
    BoneData *getBoneData(const char *boneName);
public:
    std::string name;
    Dictionary boneDataDic;
    Array boneList;
};


class  FrameData : public BaseData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(FrameData)
public:
    FrameData();
    ~FrameData();

    virtual void copy(FrameData *frameData);
public:
    int duration;                //! The frame will last _duration frames
    TweenType tweenEasing;     //! Every frame's tween easing effect

    /**
    * The current display index when change to this frame.
    * If value is -1, then display will not show.
    */
    int displayIndex;

    /**
    * _movement, _event, _sound, _soundEffect do not support yet
    */
    std::string _movement;
    std::string _event;
    std::string _sound;
    std::string _soundEffect;
};


class  MovementBoneData : public Object
{
public:
    CS_CREATE_NO_PARAM(MovementBoneData)
public:
    MovementBoneData();
    ~MovementBoneData(void);

    virtual bool init();

    void addFrameData(FrameData *frameData);
    FrameData *getFrameData(int index);
public:
    float delay;		//! movement delay percent, this value can produce a delay effect
    float scale;		//! scale this movement
    float duration;		//! this Bone in this movement will last _duration frames
    std::string name;	//! bone name

    Array frameList;
};


class  MovementData : public Object
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(MovementData)
public:
    MovementData(void);
    ~MovementData(void);

    void addMovementBoneData(MovementBoneData *movBoneData);
    MovementBoneData *getMovementBoneData(const char *boneName);
public:
    std::string name;
    int duration;        //! the frames this movement will last

    /**
    * Change to this movement will last _durationTo frames. Use this effect can avoid too suddenly changing.
    *
    * Example : current movement is "stand", we want to change to "run", then we fill _durationTo frames before
    * change to "run" instead of changing to "run" directly.
    */
    int durationTo;

    /*
    * This is different from _duration, _durationTween contain tween effect.
    *
    * Example : If we edit 10 frames in the flash, then _duration is 10. When we set _durationTween to 50, the movement will last 50 frames, the extra 40 frames will auto filled with tween effect
    */
    int durationTween;

	bool loop;           //! whether the movement is looped

    /**
    * Which tween easing effect the movement use
    * TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
    */
    TweenType tweenEasing;

    /**
    * @brief	save movment bone datas
    * @key	std::string
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
    CS_CREATE_NO_PARAM_NO_INIT(AnimationData)
public:
    AnimationData(void);
    ~AnimationData(void);

    void release();
    void retain();

    void addMovement(MovementData *movData);
    MovementData *getMovement(const char *movementName);
    int getMovementCount();
public:
    std::string name;
    Dictionary movementDataDic;
    std::vector<std::string> movementNames;
};


struct ContourVertex2F : public Object
{
    ContourVertex2F(float x, float y)
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
    CS_CREATE_NO_PARAM(ContourData)
public:
    ContourData();
    ~ContourData(void);

    virtual bool init();
public:
    Array vertexList;	//! Save contour vertex info, vertex saved in a Point
};




/*
* TextureData include a texture's information
*/
class  TextureData : public Object
{
public:
    CS_CREATE_NO_PARAM(TextureData)
public:
    TextureData();
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


}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCARMATURE_DATAS_H__*/
