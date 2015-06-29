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

#ifndef __CCARMATUREDATAMANAGER_H__
#define __CCARMATUREDATAMANAGER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

struct RelativeData
{
    std::vector<std::string> plistFiles;
    std::vector<std::string> armatures;
    std::vector<std::string> animations;
    std::vector<std::string> textures;
};

/**
 *    @brief    format and manage armature configuration and armature animation
 */
class CC_STUDIO_DLL ArmatureDataManager : public cocos2d::Ref
{
public:
    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static ArmatureDataManager *sharedArmatureDataManager() { return ArmatureDataManager::getInstance(); }

    /** @deprecated Use destoryInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purge() { ArmatureDataManager::destroyInstance(); };
    
    static ArmatureDataManager *getInstance();
    static void destroyInstance();
    
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
    void addArmatureData(const std::string& id, ArmatureData *armatureData, const std::string& configFilePath = "");

    /**
     *    @brief    get armature data
     *    @param    id the id of the armature data you want to get
     *  @return    ArmatureData *
     */
    ArmatureData *getArmatureData(const std::string& id);

    /**
     *    @brief    remove armature data
     *    @param    id the id of the armature data you want to get
     */
    void removeArmatureData(const std::string& id);

    /**
     *    @brief    add animation data
     *    @param     id the id of the animation data
     *  @return AnimationData *
     */
    void addAnimationData(const std::string& id, AnimationData *animationData, const std::string& configFilePath = "");

    /**
     *    @brief    get animation data from _animationDatas(Dictionary)
     *    @param     id the id of the animation data you want to get
     *  @return AnimationData *
     */
    AnimationData *getAnimationData(const std::string& id);

    /**
     *    @brief    remove animation data
     *    @param     id the id of the animation data
     */
    void removeAnimationData(const std::string& id);

    /**
     *    @brief    add texture data
     *    @param     id the id of the texture data
     *  @return TextureData *
     */
    void addTextureData(const std::string& id, TextureData *textureData, const std::string& configFilePath = "");

    /**
     *    @brief    get texture data
     *    @param     id the id of the texture data you want to get
     *  @return TextureData *
     */
    TextureData *getTextureData(const std::string& id);

    /**
     *    @brief    remove texture data
     *    @param     id the id of the texture data you want to get
     */
    void removeTextureData(const std::string& id);

    /**
     *    @brief    Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     */
    void addArmatureFileInfo(const std::string& configFilePath);

    /**
     *    @brief    Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     *            It will load data in a new thread
     */
    void addArmatureFileInfoAsync(const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *    @brief    Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     */
    void addArmatureFileInfo(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath);

    /**
     *    @brief    Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     *            It will load data in a new thread
     */
    void addArmatureFileInfoAsync(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *    @brief    Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
     */
    void addSpriteFrameFromFile(const std::string& plistPath, const std::string& imagePath, const std::string& configFilePath = "");

    virtual void removeArmatureFileInfo(const std::string& configFilePath);


    /**
     *    @brief    Juge whether or not need auto load sprite file
     */
    bool isAutoLoadSpriteFile();


    const cocos2d::Map<std::string, ArmatureData*>&     getArmatureDatas() const;
    const cocos2d::Map<std::string, AnimationData*>&    getAnimationDatas() const;
    const cocos2d::Map<std::string, TextureData*>&      getTextureDatas() const;

protected:
    void addRelativeData(const std::string& configFilePath);
    RelativeData *getRelativeData(const std::string& configFilePath);
private:
    /**
     *    @brief    save amature datas
     *  @key    std::string
     *  @value    ArmatureData *
     */
    cocos2d::Map<std::string, ArmatureData*> _armarureDatas;

    /**
     *    @brief    save animation datas
     *  @key    std::string
     *  @value    AnimationData *
     */
    cocos2d::Map<std::string, AnimationData*> _animationDatas;

    /**
     *    @brief    save texture datas
     *  @key    std::string
     *  @value    TextureData *
     */
    cocos2d::Map<std::string, TextureData*> _textureDatas;

    bool _autoLoadSpriteFile;

    std::unordered_map<std::string, RelativeData> _relativeDatas;
};


}

#endif/*__CCARMATUREDATAMANAGER_H__*/
