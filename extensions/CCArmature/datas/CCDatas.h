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

NS_CC_EXT_BEGIN

/**
* the base node include a lot of attribute.
*/
class  CCBaseData : public CCObject
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCBaseData)
public:
    CCBaseData();
    ~CCBaseData(void);

    /*
    * Copy datas from node
    * @param  node A CCBaseData to copy datas
    */
    virtual void copy(const CCBaseData *_node);

    /*
    * Calculate two CCBaseData's between value(_to - _from) and set to self
    *
    * @param  from   from CCBaseData
    * @param  to     to CCBaseData
    */
    virtual void subtract(CCBaseData *_from, CCBaseData *_to);

	virtual void setColor(ccColor4B &color);
	virtual ccColor4B getColor();
public:
	float x;					//! position x attribute
	float y;					//! position y attribute
	int zOrder;					//! zorder attribute, used to order the CCBone's depth order

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
    CS_DISPLAY_SPRITE,          //! display is a single CCSprite
    CS_DISPLAY_ARMATURE,        //! display is a CCArmature
    CS_DISPLAY_PARTICLE,        //! display is a CCParticle.
    CS_DISPLAY_SHADER,          //! display is a shader

    CS_DISPLAY_MAX
};

class  CCDisplayData : public CCObject
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCDisplayData)

    static const char *changeDisplayToTexture(const char *);
public:
    CCDisplayData();
    virtual ~CCDisplayData(void);

    DisplayType displayType;	//! mark which type your display is
};



class  CCSpriteDisplayData : public CCDisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCSpriteDisplayData)
public:
    CCSpriteDisplayData();
    virtual ~CCSpriteDisplayData();

    inline void setParam(const char *displayName)
    {
        this->displayName = displayName;
    }
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


class  CCArmatureDisplayData  : public CCDisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCArmatureDisplayData)
public:
    CCArmatureDisplayData();
    virtual ~CCArmatureDisplayData();

    inline void setParam(const char *displayName)
    {
        this->displayName = displayName;
    }
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


class  CCParticleDisplayData : public CCDisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCParticleDisplayData)
public:
    CCParticleDisplayData();
    virtual ~CCParticleDisplayData() {};

    void setParam(const char *plist)
    {
        this->plist = plist;
    }

    void copy(CCParticleDisplayData *displayData);
public:
    std::string plist;
};


class  CCShaderDisplayData : public CCDisplayData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCShaderDisplayData)
public:
    CCShaderDisplayData();
    virtual ~CCShaderDisplayData() {};

    inline void setParam(const char *vert, const char *frag)
    {
        this->vert = vert;
        this->frag = frag;
    }

    void copy(CCShaderDisplayData *displayData);
public:
    std::string vert;
    std::string frag;
};


/**
* CCBoneData used to init a CCBone.
* CCBoneData keeps a CCDisplayData list, a CCBone can have many display to change.
* The display information saved in the CCDisplayData
*/
class  CCBoneData : public CCBaseData
{
public:
    CS_CREATE_NO_PARAM(CCBoneData)
public:
    CCBoneData(void);
    ~CCBoneData(void);

    virtual bool init();

    void addDisplayData(CCDisplayData *displayData);
    CCDisplayData *getDisplayData(int index);
public:
    std::string name;			//! the bone's name
    std::string parentName;		//! the bone parent's name
    CCArray displayDataList;	//! save CCDisplayData informations for the CCBone
	CCAffineTransform boneDataTransform;
};


/**
* CCArmatureData saved the CCArmature name and Bonedatas needed for the Bones in this CCArmature
* When we create a CCArmature, we need to get each CCBone's CCBoneData as it's init information.
* So we can get a CCBoneData from the CCDictionary saved in the CCArmatureData.
*/
class  CCArmatureData : public CCObject
{
public:
    CS_CREATE_NO_PARAM(CCArmatureData)
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


class  CCFrameData : public CCBaseData
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCFrameData)
public:
    CCFrameData();
    ~CCFrameData();

    virtual void copy(CCFrameData *frameData);
public:
	int frameID;
    int duration;                //! The frame will last m_iDuration frames
    CCTweenType tweenEasing;     //! Every frame's tween easing effect

    /**
    * The current display index when change to this frame.
    * If value is -1, then display will not show.
    */
    int displayIndex;

    /**
    * m_strMovement, m_strEvent, m_strSound, m_strSoundEffect do not support yet
    */
    std::string strMovement;
    std::string strEvent;
    std::string strSound;
    std::string strSoundEffect;
};


class  CCMovementBoneData : public CCObject
{
public:
    CS_CREATE_NO_PARAM(CCMovementBoneData)
public:
    CCMovementBoneData();
    ~CCMovementBoneData(void);

    virtual bool init();

    void addFrameData(CCFrameData *frameData);
    CCFrameData *getFrameData(int index);
public:
    float delay;		//! movement delay percent, this value can produce a delay effect
	float scale;		//! scale this movement
    float duration;		//! this CCBone in this movement will last m_iDuration frames
    std::string name;	//! bone name

    CCArray frameList;
};


class  CCMovementData : public CCObject
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCMovementData)
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
    * Change to this movement will last m_iDurationTo frames. Use this effect can avoid too suddenly changing.
    *
    * Example : current movement is "stand", we want to change to "run", then we fill m_iDurationTo frames before
    * change to "run" instead of changing to "run" directly.
    */
    int durationTo;

    /*
    * This is different from m_iDuration, m_iDurationTween contain tween effect.
    *
    * Example : If we edit 10 frames in the flash, then m_iDuration is 10. When we set m_iDurationTween to 50, the movement will last 50 frames, the extra 40 frames will auto filled with tween effect
    */
    int durationTween;

	bool loop;           //! whether the movement is looped

    /**
    * Which tween easing effect the movement use
    * TWEEN_EASING_MAX : use the value from CCMovementData get from flash design panel
    */
    CCTweenType tweenEasing;

    /**
    * @brief	save movment bone datas
    * @key	std::string
    * @value	CCMovementBoneData *
    */
    CCDictionary movBoneDataDic;
};


/**
*  CCAnimationData include all movement infomation for the CCArmature
*  The struct is CCAnimationData -> CCMovementData -> CCMovementBoneData -> CCFrameData
*                                              -> MovementFrameData
*/
class  CCAnimationData : public CCObject
{
public:
    CS_CREATE_NO_PARAM_NO_INIT(CCAnimationData)
public:
    CCAnimationData(void);
    ~CCAnimationData(void);

    void release();
    void retain();

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
    CCContourVertex2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    float x;
    float y;
};

/*
* CCContourData include a contour vertex information
*/
class  CCContourData : public CCObject
{
public:
    CS_CREATE_NO_PARAM(CCContourData)
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
*/
class  CCTextureData : public CCObject
{
public:
    CS_CREATE_NO_PARAM(CCTextureData)
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
