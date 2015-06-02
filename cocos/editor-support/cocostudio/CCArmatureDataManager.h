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
 *	@brief	@~english  format and manage armature configuration and armature animation
 * @~chinese 格式化与管理骨骼配置和骨骼动画
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
     * @~english  Init ArmatureDataManager
     * @~chinese 初始化骨骼数据管理器
     */
    virtual bool init();

    /**
    * @~english Add armature data
    * @~chinese 增加骨骼数据
    * @param id @~english The id of the armature data
    * @~chinese 骨骼数据标识
    * @param @~english armatureData ArmatureData *
    * @~chinese 骨骼数据
    */
    void addArmatureData(const std::string& id, ArmatureData *armatureData, const std::string& configFilePath = "");

    /**
     *	@brief	@~english get armature data
     * @~chinese 获取骨骼数据
     *	@param	@~english id the id of the armature data you want to get
     * @~chinese 要获取骨骼数据的标识
     *  @return	@~english ArmatureData *
     * @~chinese 骨骼数据
     */
    ArmatureData *getArmatureData(const std::string& id);

    /**
     *	@brief	@~english remove armature data
     * @~chinese 移除骨骼数据
     *	@param	id @~english the id of the armature data you want to get
     * @~chinese 要移除骨骼数据的标识
     */
    void removeArmatureData(const std::string& id);

    /**
     *	@brief	@~english add animation data
     * @~chinese 增加动画数据
     *	@param id @~english the id of the animation data
     * @~chinese 动画数据的标识
     *  @return @~english AnimationData *
     * @~chinese 动画数据
     */
    void addAnimationData(const std::string& id, AnimationData *animationData, const std::string& configFilePath = "");

    /**
     *	@brief	@~english get animation data from _animationDatas(Dictionary)
     * @~chinese 从_animationDatas(Dictionary)中获取动画数据
     *	@param id @~english the id of the animation data you want to get
     * @~chinese 要获取动画数据的标识
     * @return @~english AnimationData *
     * @~chinese 动画数据
     */
    AnimationData *getAnimationData(const std::string& id);

    /**
     *	@brief	@~english remove animation data
     * @~chinese 移除动画数据
     *	@param id @~english the id of the animation data
     * @~chinese 要移除动画数据的标识
     */
    void removeAnimationData(const std::string& id);

    /**
     *	@brief	@~english add texture data
     * @~chinese 增加材质数据
     *	@param id @~english the id of the texture data
     * @~chinese 材质数据的标识
     */
    void addTextureData(const std::string& id, TextureData *textureData, const std::string& configFilePath = "");

    /**
     *	@brief	@~english get texture data
     * @~chinese 获取材质数据
     *	@param id @~english the id of the texture data you want to get
     * @~chinese 要获取材质数据的标识
     *  @return @~english TextureData *
     * @~chinese 材质数据
     */
    TextureData *getTextureData(const std::string& id);

    /**
     *	@brief	@~english remove texture data
     * @~chinese 移除材质数据
     *	@param id @~english the id of the texture data you want to get
     * @~chinese 要移除材质数据的标识
     */
    void removeTextureData(const std::string& id);

    /**
     *	@brief	@~english Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     * @~chinese 添加骨骼文件信息，由骨骼数据管理器管理
     */
    void addArmatureFileInfo(const std::string& configFilePath);

    /**
     *	@brief	@~english Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     *			It will load data in a new thread
     * @~chinese 添加骨骼文件信息，由骨骼数据管理器管理，将在新线程中加载数据。
     */
    void addArmatureFileInfoAsync(const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *	@brief	@~english Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     * @~chinese 添加骨骼文件信息，由骨骼数据管理器管理。
     */
    void addArmatureFileInfo(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath);

    /**
    *	@brief	@~english Add ArmatureFileInfo, it is managed by ArmatureDataManager.
    *			It will load data in a new thread
    * @~chinese 添加骨骼文件信息，由骨骼数据管理器管理，将在新线程中加载数据。
    */
    void addArmatureFileInfoAsync(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *	@brief	@~english Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
     * @~chinese 为CCSpriteFrameCache添加精灵帧，将会保存显示名称及相关图片名称。
     */
    void addSpriteFrameFromFile(const std::string& plistPath, const std::string& imagePath, const std::string& configFilePath = "");

    virtual void removeArmatureFileInfo(const std::string& configFilePath);


    /**
     *	@brief	@~english Judge whether or not need auto load sprite file
     * @~chinese 判断是否需要自动加载精灵文件。
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
     *	@brief	save amature datas
     *  @key	std::string
     *  @value	ArmatureData *
     */
    cocos2d::Map<std::string, ArmatureData*> _armarureDatas;

    /**
     *	@brief	save animation datas
     *  @key	std::string
     *  @value	AnimationData *
     */
    cocos2d::Map<std::string, AnimationData*> _animationDatas;

    /**
     *	@brief	save texture datas
     *  @key	std::string
     *  @value	TextureData *
     */
    cocos2d::Map<std::string, TextureData*> _textureDatas;

    bool _autoLoadSpriteFile;

    std::unordered_map<std::string, RelativeData> _relativeDatas;
};


}

#endif/*__CCARMATUREDATAMANAGER_H__*/
