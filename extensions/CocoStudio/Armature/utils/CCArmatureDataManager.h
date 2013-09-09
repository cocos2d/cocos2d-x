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
#include "CCConstValue.h"
#include "../datas/CCDatas.h"


namespace cocos2d { namespace extension { namespace armature {

/**
 *  @brief  format and manage armature configuration and armature animation
 */
class  ArmatureDataManager : public Object 
{
public:
    static ArmatureDataManager *sharedArmatureDataManager();
    static void purgeArmatureSystem();
private:
    ArmatureDataManager(void);
    ~ArmatureDataManager(void);

public:
    /**
     * Init ArmatureDataManager
     */
    virtual bool init();
    
    /**
     * @brief Add armature data.
     *
     * @param id            The id of the armature data.
     * @param armatureData  The armature data to be added.
     */
    void addArmatureData(const char *id, ArmatureData *armatureData);
    
    /**
     * @brief Get armature data.
     *
     * @param id   The id of the armature data you want to get.
     *
     * @return The ArmatureData whose id is @p id.
     */
    ArmatureData *getArmatureData(const char *id);

    /**
     *  @brief Add animation data.
     *
     *  @param id               The id of the animation data.
     *  @param animationData    The animation data to be added.
     */
    void addAnimationData(const char *id, AnimationData *animationData);
    
    /**
     * @brief Get animation data.
     *
     * @param id    The id of the animation data you want to get.
     *
     * @return The AnimationData whose id is @p id.
     */
    AnimationData *getAnimationData(const char *id);

    /**
     *  @brief Add texture data.
     *
     *  @param id           The id of the texture data.
     *  @param textureData  The texture data to be added.
     */
    void addTextureData(const char *id, TextureData *textureData);
    
    /**
     * @brief Get texture data.
     *
     * @param id   The id of the texture data you want to get.
     *
     * @return The TextureData whose id is @p id.
     */
    TextureData *getTextureData(const char *id);
    
    /**
     * @brief  Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     */
    void addArmatureFileInfo(const char *armatureName, const char *useExistFileInfo, const char *imagePath, const char *plistPath, const char *configFilePath);

    /**
     * @brief  Add ArmatureFileInfo, it is managed by ArmatureDataManager.
     */
    void addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath);

    /**
     * @brief  Add sprite frame to SpriteFrameCache, it will save display name and it's relative image name
     */
    void addSpriteFrameFromFile(const char *plistPath, const char *imagePath);

    /**
     * @brief  Clear the data in the _armarureDatas and _animationDatas, and set _armarureDatas and _animationDatas to NULL
     */
    void removeAll();

   
private:
    /**
     * Dictionary to save amature data.
     * Key type is std::string, value type is ArmatureData *.
     */
    CC_SYNTHESIZE_READONLY(Dictionary *, _armarureDatas, ArmarureDatas);

    /**
     * Dictionary to save animation data.
     * Key type is std::string, value type is AnimationData *.
     */
    CC_SYNTHESIZE_READONLY(Dictionary *, _animationDatas, AnimationDatas);

    /**
     * Dictionary to save texture data.
     * Key type is std::string, value type is TextureData *.
     */
    CC_SYNTHESIZE_READONLY(Dictionary *, _textureDatas, TextureDatas);

};


}}} // namespace cocos2d { namespace extension { namespace armature {

#endif/*__CCARMATUREDATAMANAGER_H__*/
