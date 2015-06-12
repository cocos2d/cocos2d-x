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

#ifndef __CC_EXTENTIONS_CCCOMAUDIO_H__
#define __CC_EXTENTIONS_CCCOMAUDIO_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/** 
 * @class ComAudio
 * @brief @~english ComAudio.
 * @~chinese 自定义声音组件.
 * @details @~english offers a very simple interface to play background music & sound effects.
 * @~chinese 提供播放音效和背景音乐的一系列接口.
*/
class CC_STUDIO_DLL ComAudio : public cocos2d::Component
{

    DECLARE_CLASS_COMPONENT_INFO

public:
    /**
     * @brief @~english ComAudio constructor.
     * @~chinese 声音组件构造函数。
     * @js ctor
     */
    ComAudio(void);
    /**
     * @brief @~english ComAudio destructor.
     * @~chinese 声音组件析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~ComAudio(void);
    
public:
    /**
     * @brief @~english initialize a ComAudio.
     * @~chinese 初始化声音组件。
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true 初始化成功，否则false。
     */
    virtual bool init() override;

    /**
     * @brief @~english Event callback that is invoked every time when Node enters the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
     * @~chinese 每次当Node进入“stage”时才调用事件回调。
     * 如果Node进入“stage”状态时伴随着一个转换（transition）,那么事件将会在这个转换开始的时候被调用。
     * 在onEnter过程中，你不能够接入“sister/brother”兄妹节点。
     * 如果你重写了onEnter方法，你应该调用它的父类，e.g., Node::onEnter().
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     * @brief @~english Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @~chinese 每次当Node离开“stage”时才调用事件回调。
     * 如果Node离开“stage”状态时伴随着一个转换（transition）, 那么事件将会在这个转换结束的时候被调用。
     * 在onEnter过程中中你不能够接入一个兄妹节点。
     * 如果你重写onExit, 你应该调用它的父类, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;

    /** 
     * @brief @~english Returns whether or not the ComAudio is enabled.
     * @~chinese 返回声音组件是否被启用。
     * @return @~english Whether or not the ComAudio is enabled. 
     * @~chinese 声音组件是否被启用。
     */
    virtual bool isEnabled() const override;

    /**  
     * @brief @~english enables or disables the ComAudio.
     * @~chinese 启用或禁用声音组件。
     * @param enabled @~english true enable the menu ComAudio, false disabled the ComAudio. 
     * @~chinese true，启用声音组件 false，禁用声音组件。
     */
    virtual void setEnabled(bool b) override;

    /**
     * @brief @~english deserialization export data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据。
     * @param r @~english SerData object point.
     * @~chinese SerData对象指针。
     * @return @~english true deserialize successfully false failed to deserialize.
     * @~chinese true 反序列化成功，否则false。
     */
    virtual bool serialize(void* r) override;
    /**
     * @brief @~english Allocates and initializes a create.
     * @~chinese 分配并且初始化声音组件。
     * @return @~english A initialized node which is marked as "autorelease".
     * @~chinese 一个初始化的声音组件，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static ComAudio* create(void);
   
public:
    /**
     * @brief @~english Release the shared Engine object.
     * @~chinese 释放音效引擎实例。
     * @warning @~english It must be called before the application exit, or it will lead to memory leaks.
     * @~chinese 在游戏退出时需要调用这个方法，不然的话会导致内存泄漏。
     */
    void end();

    /**
     * @brief @~english Preload background music.
     * @~chinese 预加载背景音乐。
     * @param pszFilePath @~english The path of the background music file.
     * @~chinese 背景音乐的文件路径。
     */
    void preloadBackgroundMusic(const char* pszFilePath);

    /**
     * @~brief @~english Play background music.
     * @~chinese 播放背景音乐。
     * 
     * @param pszFilePath @~english The path of the background music file,or the FileName of T_SoundResInfo.
     * @~chinese 背景音乐的文件路径或T_SoundResInfo中的FileName字段。
     * @param loop @~english Whether the background music loop or not.
     * @~chinese 背景音乐是否循环播放。
     */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);

    /**
     * @~brief @~english Play background music based _loop of property. 
     * @~chinese 播放背景音乐。
     * @param pszFilePath @~english The path of the background music file,or the FileName of T_SoundResInfo.
     * @~chinese 背景音乐的文件路径或T_SoundResInfo中的FileName字段。
     */
    void playBackgroundMusic(const char* pszFilePath);

    /**
     * @~brief @~english Play background music based _loop and _filePath of property. 
     * @~chinese 播放背景音乐。
     */
    void playBackgroundMusic();

    /**
     * @brief @~english Stop playing background music.
     * @~chinese 停止播放背景音乐。
     * @param releaseData @~english If release the background music data or not.As default value is false.
     * @~chinese 是否释放背景音乐的数据，默认值为false。
     */
    void stopBackgroundMusic(bool bReleaseData);

    /**
     * @brief @~english Stop playing background music.
     * @~chinese 停止播放背景音乐。
     */
    void stopBackgroundMusic();

    /**
     * @brief @~english Pause playing background music.
     * @~chinese 暂停播放背景音乐。
     */
    void pauseBackgroundMusic();

    /**
     * @brief @~english Resume playing background music.
     * @~chinese 恢复播放背景音乐。
     */
    void resumeBackgroundMusic();

    /**
     * @brief @~english Rewind playing background music.
     * @~chinese 将背景音乐倒回起始点播放。
     */
    void rewindBackgroundMusic();

    /**
     * @brief @~english Indicates whether any background music can be played or not.
     * @~chinese 是否会播放背景音乐。
     * @return true @~english if background music can be played, otherwise false.
     * @~chinese 如果背景音乐会被播放返回true，否则返回false。
     */
    bool willPlayBackgroundMusic();

    /**
     * @brief @~english Indicates whether the background music is playing.
     * @~chinese 背景音乐是否在播放。
     * @return true @~english if the background music is playing, otherwise false.
     * @~chinese 正在播放返回true，否则返回false。
     */
    bool isBackgroundMusicPlaying();

    /**
     * @brief @~english The volume of the background music within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese 获取背景音乐的音量，音量的值的范围为0.0到1.0。
     */
    float getBackgroundMusicVolume();


    void setBackgroundMusicVolume(float volume);

    /**
     * @brief @~english The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese 获取音效的音量大小,音量大小范围为0.0到1.0。
     */
    float getEffectsVolume();

    /**
     * @brief @~english Set the volume of sound effects.
     * @~chinese 设置音效的音量大小。
     * @param volume @~english must be within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese 音效的音量大小，范围为0.0到1.0。
     */
    void setEffectsVolume(float volume);

    /**
     * @brief @~english Play sound effect with a file path and loop.
     * @~chinese 播放音效
     * @param pszFilePath @~english The path of the effect file. 
     * @~chinese 音效文件的路径。
     * @param bLoop @~english Determines whether to loop the effect playing or not. 
     * @~chinese 是否循环播放,默认为false,不循环。
     * @return @~english The sound id. 
     * @~chinese 声音id。
     */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);

    /**
     * @brief @~english Play sound effect with a file path and _loop of property
     * @~chinese 播放音效
     * @param pszFilePath @~english The path of the effect file. 
     * @~chinese 音效文件的路径。
     * @param bLoop @~english Determines whether to loop the effect playing or not. 
     * @~chinese 是否循环播放,默认为false,不循环。
     * @return @~english The sound id. 
     * @~chinese 声音id。
     */
    unsigned int playEffect(const char* pszFilePath);

    /**
     * @brief @~english Play sound effect with _filePath and _loop of property
     * @~chinese 播放音效
     * @return @~english The sound id. 
     * @~chinese 声音id。
     */
    unsigned int playEffect();

    /**
     * @brief @~english Pause playing sound effect.
     * @~chinese 暂停播放指定音效。
     * @param nSoundId @~english The return value of function playEffect.
     * @~chinese 音效id。
     */
    void pauseEffect(unsigned int nSoundId);

    /**
     * @brief @~english Pause all playing sound effect.
     * @~chinese 暂停所有播放的音效。
     */
    void pauseAllEffects();

    /**
     * @brief @~english Resume playing sound effect.
     * @~chinese 恢复暂停播放指定的音效。
     * @param nSoundId @~english The return value of function playEffect.
     * @~chinese playEffect返回的资源id。
     */
    void resumeEffect(unsigned int nSoundId);

    /**
     * @brief @~english Resume all playing sound effect.
     * @~chinese 恢复所有暂停的音效。
     */
    void resumeAllEffects();

    /**
     * @brief @~english Stop playing sound effect.
     * @~chinese 停止播放指定的音效。
     *
     * @param nSoundId @~english The return value of function playEffect.
     * @~chinese playEffect返回的资源id。
     */
    void stopEffect(unsigned int nSoundId);

    /**
     * @brief @~english Stop all playing sound effects.
     * @~chinese 停止所有播放的音效。
     */
    void stopAllEffects();

    /**
     * @brief @~english Preload a compressed audio file.
     * The compressed audio will be decoded to wave, then written into an internal buffer in SimpleAudioEngine.
     * @~chinese 预加载音效文件。
     *
     * @param pszFilePath @~english The path of the effect file. 
     * @~chinese 音效文件路径。
     * @js NA
     */
    void preloadEffect(const char* pszFilePath);

    /**
     * @brief @~english Unload the preloaded effect from internal buffer.
     * @~chinese 卸载预加载到内存中的音效文件。
     *
     * @param pszFilePath @~english The path of the effect file.
     * @~chinese 音效文件的路径。
     */
    void unloadEffect(const char* pszFilePath);

    /**
     * @brief @~english Set file path.
     * @~chinese 设置路径。
     */
    void setFile(const char* pszFilePath);

    /**
     * @brief @~english Get file path.
     * @~chinese 获取路径。
     * @return @~english file path.
     * @~chinese 声音文件。
     */
    const char* getFile();

    /**  
     * @brief @~english Sets hether or not the sound is loop.
     * @~chinese 设置声音是否循环。
     * @param bLoop @~english true ComAudio is loop, false ComAudio is not loop. 
     * @~chinese true，开启声音组件循环 false，声音组件不循环。
     */
    void setLoop(bool bLoop);

    /** 
     * @brief @~english Returns whether or not the sound is loop.
     * @~chinese 返回声音组件是否循环。
     * @return @~english Whether or not the ComAudio is loop. 
     * @~chinese 声音组件是否循环。
     */
    bool isLoop();
private:
	std::string _filePath;
	bool _loop;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
