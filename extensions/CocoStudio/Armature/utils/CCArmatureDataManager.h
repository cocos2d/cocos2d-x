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

#include "CCArmatureDefine.h"
#include "../datas/CCDatas.h"


NS_CC_EXT_BEGIN

struct CCRelativeData
{
    std::vector<std::string> plistFiles;
    std::vector<std::string> armatures;
    std::vector<std::string> animations;
    std::vector<std::string> textures;
};

/**
 *	@brief	format and manage armature configuration and armature animation
 *  @lua NA
 */
class  CC_EX_DLL CCArmatureDataManager : public CCObject
{
public:
    /**
     *  @js getInstance
     */
    static CCArmatureDataManager *sharedArmatureDataManager();

    static void purge();
private:
    CCArmatureDataManager(void);
    ~CCArmatureDataManager(void);

public:

    /**
     * Init CCArmatureDataManager
     */
    virtual bool init();



    /**
     * Add armature data
     * @param id The id of the armature data
     * @param armatureData CCArmatureData *
     */
    void addArmatureData(const char *id, CCArmatureData *armatureData, const char *configFilePath = "");

    /**
     *	@brief	get armature data
     *	@param	id the id of the armature data you want to get
     *  @return	CCArmatureData *
     */
    CCArmatureData *getArmatureData(const char *id);

    /**
     *	@brief	remove armature data
     *	@param	id the id of the armature data you want to get
     */
    void removeArmatureData(const char *id);

    /**
     *	@brief	add animation data
     *	@param 	id the id of the animation data
     *  @return CCAnimationData *
     */
    void addAnimationData(const char *id, CCAnimationData *animationData, const char *configFilePath = "");

    /**
     *	@brief	get animation data from m_pAnimationDatas(CCDictionary)
     *	@param 	id the id of the animation data you want to get
     *  @return CCAnimationData *
     */
    CCAnimationData *getAnimationData(const char *id);

    /**
     *	@brief	remove animation data
     *	@param 	id the id of the animation data
     */
    void removeAnimationData(const char *id);

    /**
     *	@brief	add texture data
     *	@param 	id the id of the texture data
     *  @return CCTextureData *
     */
    void addTextureData(const char *id, CCTextureData *textureData, const char *configFilePath = "");

    /**
     *	@brief	get texture data
     *	@param 	id the id of the texture data you want to get
     *  @return CCTextureData *
     */
    CCTextureData *getTextureData(const char *id);

    /**
     *	@brief	remove texture data
     *	@param 	id the id of the texture data you want to get
     */
    void removeTextureData(const char *id);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by CCArmatureDataManager.
     */
    void addArmatureFileInfo(const char *configFilePath);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by CCArmatureDataManager.
     *			It will load data in a new thread
     */
    void addArmatureFileInfoAsync(const char *configFilePath, CCObject *target, SEL_SCHEDULE selector);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by CCArmatureDataManager.
     */
    void addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath);

    /**
     *	@brief	Add ArmatureFileInfo, it is managed by CCArmatureDataManager.
     *			It will load data in a new thread
     */
    void addArmatureFileInfoAsync(const char *imagePath, const char *plistPath, const char *configFilePath, CCObject *target, SEL_SCHEDULE selector);


    virtual void removeArmatureFileInfo(const char *configFilePath);


    /**
     *	@brief	Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
     */
    void addSpriteFrameFromFile(const char *plistPath, const char *imagePath, const char *configFilePath = "");


    /**
     *	@brief	Juge whether or not need auto load sprite file
     */
    bool isAutoLoadSpriteFile();


    CCDictionary *getArmatureDatas() const;
    CCDictionary *getAnimationDatas() const;
    CCDictionary *getTextureDatas() const;

protected:
    void addRelativeData(const char* configFilePath);
    CCRelativeData *getRelativeData(const char* configFilePath);
private:
    /**
     *	@brief	save amature datas
     *  @key	std::string
     *  @value	CCArmatureData *
     */
    CCDictionary *m_pArmarureDatas;

    /**
     *	@brief	save animation datas
     *  @key	std::string
     *  @value	CCAnimationData *
     */
    CCDictionary *m_pAnimationDatas;

    /**
     *	@brief	save texture datas
     *  @key	std::string
     *  @value	CCTextureData *
     */
    CCDictionary *m_pTextureDatas;

    bool m_bAutoLoadSpriteFile;

    std::map<std::string, CCRelativeData> m_sRelativeDatas;
};


NS_CC_EXT_END

#endif/*__CCARMATUREDATAMANAGER_H__*/
