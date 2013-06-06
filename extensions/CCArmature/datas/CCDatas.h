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

#ifndef __CCDATA_H__
#define __CCDATA_H__

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
	
#pragma region Node
/**
* the base node include a lot of attribute.
*/
class  Node : public cocos2d::CCObject
{
public:
	CS_CREATE_NO_PARAM_NO_INIT(Node)
public:
	Node();
	~Node(void);

	/*
	* Copy datas from node
	* @param  node A Node to copy datas
	*/
	virtual void copy(const Node *_node);

	/*
	* Calculate two Node's between value(_to - _from) and set to self
	*
	* @param  from   from Node
	* @param  to     to Node
	*/
	virtual void subtract(Node *_from, Node *_to);
public:
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

	float x;					//! position x attribute
	float y;					//! position y attribute
	int zOrder;					//! zorder attribute, used to order the CCBone's depth order
};
#pragma endregion

#pragma region DisplayData
/**
* DisplayType distinguish which type you display is.
*/
enum DisplayType{
	CS_DISPLAY_SPRITE,          //! display is a single CCSprite
	CS_DISPLAY_ARMATURE,        //! display is a CCArmature
	CS_DISPLAY_PARTICLE,        //! display is a CCParticle.
	CS_DISPLAY_SHADER,          //! display is a shader

	CS_DISPLAY_MAX
};

class  DisplayData : public cocos2d::CCObject
{
public:
	CS_CREATE_NO_PARAM_NO_INIT(DisplayData)

		static const char *changeDisplayToTexture(const char *);
public:
	DisplayData();
	virtual ~DisplayData(void);

	DisplayType displayType;	//! mark which type your display is
};
#pragma endregion



#pragma region SpriteDisplayData
class  SpriteDisplayData : public DisplayData
{
public:
	CS_CREATE_NO_PARAM_NO_INIT(SpriteDisplayData)
public:
	SpriteDisplayData();
	virtual ~SpriteDisplayData();

	inline void setParam(const char *displayName){ this->displayName = displayName; }
	void copy(SpriteDisplayData *displayData);
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
#pragma endregion


#pragma region ArmatureDisplayData
class  ArmatureDisplayData  : public DisplayData
{    
public:
	CS_CREATE_NO_PARAM_NO_INIT(ArmatureDisplayData)
public:
	ArmatureDisplayData();
	virtual ~ArmatureDisplayData();

	inline void setParam(const char *displayName){ this->displayName = displayName; }
	void copy(ArmatureDisplayData *displayData);
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
#pragma endregion


#pragma region ParticleDisplayData
class  ParticleDisplayData : public DisplayData
{
public:
	CS_CREATE_NO_PARAM_NO_INIT(ParticleDisplayData)
public:
	ParticleDisplayData();
	virtual ~ParticleDisplayData(){};

	void setParam(const char *plist){ this->plist = plist; }

	void copy(ParticleDisplayData *displayData);
public:    
	std::string plist;
};
#pragma endregion


#pragma region ShaderDisplayData
class  ShaderDisplayData : public DisplayData
{
public:
	CS_CREATE_NO_PARAM_NO_INIT(ShaderDisplayData)
public:
	ShaderDisplayData();
	virtual ~ShaderDisplayData(){};

	inline void setParam(const char *vert, const char *frag){ this->vert = vert; this->frag = frag;}

	void copy(ShaderDisplayData *displayData);
public:
	std::string vert;    
	std::string frag;
};
#pragma endregion


#pragma region BoneData
/**
* BoneData used to init a CCBone.
* BoneData keeps a DisplayData list, a CCBone can have many display to change.
* The display information saved in the DisplayData
*/
class  BoneData : public Node
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
	std::string name;					//! the bone's name
	std::string parentName;		//! the bone parent's name
	cocos2d::CCArray displayDataList;		//! save DisplayData informations for the CCBone
};
#pragma  endregion

#pragma  region ArmatureData
/**
* ArmatureData saved the CCArmature name and Bonedatas needed for the Bones in this CCArmature
* When we create a CCArmature, we need to get each CCBone's BoneData as it's init information.
* So we can get a BoneData from the cocos2d::CCDictionary saved in the ArmatureData.
*/
class  ArmatureData : public cocos2d::CCObject
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
	cocos2d::CCDictionary boneDataDic;
	cocos2d::CCArray boneList;
};
#pragma  endregion

#pragma region FrameData
class  FrameData : public Node
{
public:
	CS_CREATE_NO_PARAM_NO_INIT(FrameData)
public:
	FrameData();
	~FrameData();

	virtual void copy(FrameData *frameData);
public:
	int duration;			//! The frame will last m_iDuration frames
	CCTweenType tweenEasing;	//! Every frame's tween easing effect

	/**
	* The current display index when change to this frame.
	* If value is -1, then display will not show.
	*/
	int displayIndex;

	/**
	* m_strMovement, m_strEvent, m_strSound, m_strSoundEffect do not support yet
	*/
	std::string m_strMovement;
	std::string m_strEvent;
	std::string m_strSound;
	std::string m_strSoundEffect;
};
#pragma endregion

#pragma region MovementBoneData
class  MovementBoneData : public cocos2d::CCObject
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
	float duration;		//! this CCBone in this movement will last m_iDuration frames
	std::string name;	//! bone name

	cocos2d::CCArray frameList;
};
#pragma endregion

#pragma region MovementData
class  MovementData : public cocos2d::CCObject
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
	int duration;		 //! the frames this movement will last
	bool loop;			//! whether the movement is looped

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

	/**
	* Which tween easing effect the movement use
	* TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
	*/
	CCTweenType tweenEasing;

	/**
	* @brief	save movment bone datas
	* @key	std::string
	* @value	MovementBoneData *
	*/
	cocos2d::CCDictionary movBoneDataDic;
};
#pragma endregion

#pragma region AnimationData
/**
*  AnimationData include all movement infomation for the CCArmature
*  The struct is AnimationData -> MovementData -> MovementBoneData -> FrameData
*                                              -> MovementFrameData
*/
class  AnimationData : public cocos2d::CCObject
{
public:
	CS_CREATE_NO_PARAM_NO_INIT(AnimationData)
public:
	AnimationData(void);
	~AnimationData(void);

	void release();
	void retain();

	void addMovement(MovementData* movData);
	MovementData *getMovement(const char *movementName);
	int getMovementCount();
public:
	std::string name;
	cocos2d::CCDictionary movementDataDic;
	std::vector<std::string> movementNames;
};
#pragma endregion

#pragma region ContourData
struct ContourVertex2 : public cocos2d::CCObject
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
class  ContourData : public cocos2d::CCObject
{
public:
	CS_CREATE_NO_PARAM(ContourData)
public:
	ContourData();
	~ContourData(void);

	virtual bool init();
public:
	cocos2d::CCArray vertexList;	//! Save contour vertex info, vertex saved in a CCPoint
};
#pragma endregion




#pragma region TextureData
/*
* TextureData include a texture's information 
*/
class  TextureData : public cocos2d::CCObject
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
	std::string name;	//! The texture's name

	float pivotX;		//! The texture's anchor point
	float pivotY;

	float width;		//! The texture's width, height
	float height;

	cocos2d::CCArray contourDataList;
};
#pragma endregion

NS_CC_EXT_END

#endif /*__CCDATA_H__*/