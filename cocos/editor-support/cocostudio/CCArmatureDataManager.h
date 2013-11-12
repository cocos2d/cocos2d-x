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

#ifndef __CCARMATUREDATAMANAGER_H__
#define __CCARMATUREDATAMANAGER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"


namespace cocostudio {

struct RelativeData
{
    std::vector<std::string> plistFiles;
    std::vector<std::string> armatures;
    std::vector<std::string> animations;
    std::vector<std::string> textures;
};

/**
 *	@brief	format and manage armature configuration and armature animation
 */
class  ArmatureDataManager : public cocos2d::Object
{
public:
	/** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static ArmatureDataManager *sharedArmatureDataManager() { return ArmatureDataManager::getInstance(); }

    /** @deprecated Use destoryInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purge() { ArmatureDataManager::destoryInstance(); };
    
    static ArmatureDataManager *getInstance();
    static void destoryInstance();
    
private:
	/**
     * @js ctor
     */
    ArmatureDataManager(void);
    /**
     * @js NA
     * @lua NA
     */
    ~ArmatureDataManager(void);

public:

    /**
     * Init ArmatureDataManager
     */
    virtual bool init();

    /**
     * Add armature data
     * @param id The id of the armature data
     * @param armatureData ArmatureData *
     */
    void addArmatureData(const char *id, ArmatureData *armatureData, const char *configFilePath = "");

    /**
     *	@brief	get armature data
     *	@param	id the id of the armature data you want to get
     *  @return	ArmatureData *
     */
    ArmatureData *getArmatureData(const char *id);

    /**
     *	@brief	remove armature data
     *	@param	id the id of the armature data you want to get
     */
    void removeArmatureData(const char *id);

    /**
     *	@brief	add animation data
     *	@param 	id the id of the animation data
     *  @return AnimationData *
     */
    void addAnimationData(const char *id, AnimationData *animationData, const char *configFilePath = "");

    /**
     *	@brief	get animation data from _animationDatas(Dictionary)
     *	@param 	id the id of the animation data you want to get
     *  @return AnimationData *
     */
    AnimationData *getAnimationData(const char *id);

    /**
     *	@brief	remove animation data
     *	@param 	id the id of the animation data
     */
    void removeAnimationData(const char *id);

    /**
     *	@brief	add texture data
     *	@param 	id the id of the texture data
     *  @return TextureData *
     */
    void addTextureData(const char *id, TextureData *textureData, const char *configFilePath = "");

    /**
     *	@brief	get texture data
     *	@param 	id the id of the texture data you want to get
     *  @return TextureData *
     */
    TextureData *getTextureData(const char *id);

    /**
     *	@brief	remove texture data
     *	@param 	id the id of the texture data you want to get
     */
    void removeTextureData(const char *id);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     */
    void addArmatureFileInfo(const char *configFilePath);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     *			It will load data in a new thread
     */
    void addArmatureFileInfoAsync(const char *configFilePath, cocos2d::Object *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     */
    void addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     *			It will load data in a new thread
     */
    void addArmatureFileInfoAsync(const char *imagePath, const char *plistPath, const char *configFilePath, cocos2d::Object *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *	@brief	Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
     */
    void addSpriteFrameFromFile(const char *plistPath, const char *imagePath, const char *configFilePath = "");

    virtual void removeArmatureFileInfo(const char *configFilePath);


    /**
     *	@brief	Juge whether or not need auto load sprite file
     */
    bool isAutoLoadSpriteFile();


    cocos2d::Dictionary *getArmatureDatas() const;
    cocos2d::Dictionary *getAnimationDatas() const;
    cocos2d::Dictionary *getTextureDatas() const;

protected:
    void addRelativeData(const char* configFilePath);
    RelativeData *getRelativeData(const char* configFilePath);
private:
    /**
     *	@brief	save amature datas
     *  @key	std::string
     *  @value	ArmatureData *
     */
    cocos2d::Dictionary *_armarureDatas;

    /**
     *	@brief	save animation datas
     *  @key	std::string
     *  @value	AnimationData *
     */
    cocos2d::Dictionary *_animationDatas;

    /**
     *	@brief	save texture datas
     *  @key	std::string
     *  @value	TextureData *
     */
    cocos2d::Dictionary *_textureDatas;

    bool _autoLoadSpriteFile;

    std::map<std::string, RelativeData> _relativeDatas;
};


}

#endif/*__CCARMATUREDATAMANAGER_H__*/
