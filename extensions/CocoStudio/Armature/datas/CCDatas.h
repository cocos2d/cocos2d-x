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

NS_CC_EXT_BEGIN

/**
* The base node include a lot of attributes.
* @js NA
* @lua NA
*/
class  CCBaseData : public CCObject
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCBaseData)
public:
    CCBaseData();
    ~CCBaseData(void);

    /*
    * Copy data from node
    * @param  node A CCBaseData to copy data
    */
    virtual void copy(const CCBaseData *node);

    /*
    * Calculate two CCBaseData's between value(to - from) and set to self
    *
    * @param  from   from CCBaseData
    * @param  to     to CCBaseData
    */
    virtual void subtract(CCBaseData *from, CCBaseData *to, bool limit);

    virtual void setColor(const ccColor4B &color);
    virtual ccColor4B getColor();
public:
    float x;					//! position x attribute
    float y;					//! position y attribute
    int zOrder;			//! zorder attribute, used to order the CCBone's depth order

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
    CS_DISPLAY_SPRITE,                //! display is a single CCSprite
    CS_DISPLAY_ARMATURE,         //! display is a CCArmature
    CS_DISPLAY_PARTICLE,            //! display is a CCParticle.

    CS_DISPLAY_MAX
};
/**
*   @js NA
*   @lua NA
*/
class  CCDisplayData : public CCObject
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCDisplayData)

    static const char *changeDisplayToTexture(const char *displayName);
public:
    CCDisplayData();
    virtual ~CCDisplayData(void);

    DisplayType displayType;	//! mark which type your display is
};


/**
*   @js NA
*   @lua NA
*/
class  CCSpriteDisplayData : public CCDisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCSpriteDisplayData)
public:
    CCSpriteDisplayData();
    virtual ~CCSpriteDisplayData();

    void setParam(const char *pszDisplayName) { this->displayName = pszDisplayName; }
    void copy(CCSpriteDisplayData *displayData);
public:
    /**
    * If DisplayType is CS_DISPLAY_SPRITE, then CCBone will use this image name to create a CCSprite from CCSpriteFrameCache.
    * It should note that when use this name to create CCSprite from CCSpriteFrameCache, you should use m_strDisplayName + ".png", because when use Texture Packer to pack single image file, the name have ".png".
    *
    * If DisplayType is CS_DISPLAY_ARMATURE, the name is the CCArmature's name. When CCBone init display and type is CS_DISPLAY_ARMATURE,
    * then CCBone will create a CCArmature.
    */
    std::string displayName;

    CCBaseData skinData;
};

/**
*   @js NA
*   @lua NA
*/
class  CCArmatureDisplayData  : public CCDisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCArmatureDisplayData)
public:
    CCArmatureDisplayData();
    virtual ~CCArmatureDisplayData();

    void setParam(const char *pszDisplayName) { this->displayName = pszDisplayName; }
    void copy(CCArmatureDisplayData *displayData);
public:
    /**
    * If DisplayType is CS_DISPLAY_SPRITE, then CCBone will use this image name to create a CCSprite from CCSpriteFrameCache.
    * It should note that when use this name to create CCSprite from CCSpriteFrameCache, you should use m_strDisplayName + ".png", because when use Texture Packer to pack single image file, the name have ".png".
    *
    * If DisplayType is CS_DISPLAY_ARMATURE, the name is the CCArmature's name. When CCBone init display and type is CS_DISPLAY_ARMATURE,
    * then CCBone will create a CCArmature.
    */
    std::string displayName;

};

/**
*   @js NA
*   @lua NA
*/
class  CCParticleDisplayData : public CCDisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCParticleDisplayData)
public:
    CCParticleDisplayData();
    virtual ~CCParticleDisplayData() {};

    void setParam(const char *pszPlist) { this->plist = pszPlist; }

    void copy(CCParticleDisplayData *displayData);
public:
    std::string plist;
};



/**
* CCBoneData used to init a CCBone.
* CCBoneData keeps a CCDisplayData list, a CCBone can have many display to change.
* The display information saved in the CCDisplayData
* @js NA
* @lua NA
*/
class  CCBoneData : public CCBaseData
{
public:
    CC_CREATE_NO_PARAM(CCBoneData)
public:
    CCBoneData(void);
    ~CCBoneData(void);

    virtual bool init();

    void addDisplayData(CCDisplayData *displayData);
    CCDisplayData *getDisplayData(int index);
public:
    std::string name;                //! the bone's name
    std::string parentName;     //! the bone parent's name
    CCArray displayDataList;    //! save CCDisplayData informations for the CCBone
    CCAffineTransform boneDataTransform;
};


/**
* CCArmatureData saved the CCArmature name and Bonedata needed for the CCBones in this CCArmature
* When we create a CCArmature, we need to get each CCBone's CCBoneData as it's init information.
* So we can get a CCBoneData from the CCDictionary saved in the CCArmatureData.
* @js NA
* @lua NA
*/
class  CCArmatureData : public CCObject
{
public:
    CC_CREATE_NO_PARAM(CCArmatureData)
public:
    CCArmatureData();
    ~CCArmatureData();

    bool init();
    void addBoneData(CCBoneData *boneData);
    CCBoneData *getBoneData(const char *boneName);
public:
    std::string name;
    CCDictionary boneDataDic;
    float dataVersion;
};

enum CCBlendType
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
* @js NA
* @lua NA
*/
class  CCFrameData : public CCBaseData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCFrameData)
public:
    CCFrameData();
    ~CCFrameData();

    virtual void copy(const CCBaseData *node);
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

    CCBlendType blendType;

    std::string strEvent;
    /**
    * strMovement, strEvent, strSound, strSoundEffect do not support yet
    */
    std::string strMovement;
    std::string strSound;
    std::string strSoundEffect;
};

/**
* @js NA
* @lua NA
*/
class  CCMovementBoneData : public CCObject
{
public:
    CC_CREATE_NO_PARAM(CCMovementBoneData)
public:
    CCMovementBoneData();
    ~CCMovementBoneData(void);

    virtual bool init();

    void addFrameData(CCFrameData *frameData);
    CCFrameData *getFrameData(int index);
public:
    float delay;             //! movement delay percent, this value can produce a delay effect
    float scale;             //! scale this movement
    float duration;        //! this CCBone in this movement will last m_iDuration frames
    std::string name;    //! bone name

    CCArray frameList;
};

/**
* @js NA
* @lua NA
*/
class  CCMovementData : public CCObject
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCMovementData)
public:
    CCMovementData(void);
    ~CCMovementData(void);

    void addMovementBoneData(CCMovementBoneData *movBoneData);
    CCMovementBoneData *getMovementBoneData(const char *boneName);
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
    * TWEEN_EASING_MAX : use the value from CCMovementData get from flash design panel
    */
    CCTweenType tweenEasing;

    /**
    * @brief	save movment bone data
    * @key	const char *
    * @value	CCMovementBoneData *
    */
    CCDictionary movBoneDataDic;
};


/**
*  CCAnimationData include all movement infomation for the CCArmature
*  The struct is CCAnimationData -> CCMovementData -> CCMovementBoneData -> CCFrameData
*                                              -> MovementFrameData
*  @js NA
*  @lua NA
*/
class  CCAnimationData : public CCObject
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(CCAnimationData)
public:
    CCAnimationData(void);
    ~CCAnimationData(void);

    void addMovement(CCMovementData *movData);
    CCMovementData *getMovement(const char *movementName);
    int getMovementCount();
public:
    std::string name;
    CCDictionary movementDataDic;
    std::vector<std::string> movementNames;
};


struct CCContourVertex2 : public CCObject
{
    CCContourVertex2(float xx, float yy)
    {
        this->x = xx;
        this->y = yy;
    }

    float x;
    float y;
};

/*
* CCContourData include a contour vertex information
* @js NA
* @lua NA
*/
class  CCContourData : public CCObject
{
public:
    CC_CREATE_NO_PARAM(CCContourData)
public:
    CCContourData();
    ~CCContourData(void);

    virtual bool init();
    virtual void addVertex(CCPoint *vertex);
public:
    CCArray vertexList;	//! Save contour vertex info, vertex saved in a CCPoint
};




/*
* CCTextureData include a texture's information
* @js NA
* @lua NA
*/
class  CCTextureData : public CCObject
{
public:
    CC_CREATE_NO_PARAM(CCTextureData)
public:
    CCTextureData();
    ~CCTextureData(void);

    virtual bool init();

    void addContourData(CCContourData *contourData);
    CCContourData *getContourData(int index);
public:

    float height;		//! The texture's width, height
    float width;

    float pivotX;		//! The texture's anchor point
    float pivotY;

    std::string name;	//! The texture's name

    CCArray contourDataList;
};


NS_CC_EXT_END

#endif /*__CCARMATURE_DATAS_H__*/
