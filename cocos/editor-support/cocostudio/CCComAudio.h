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
 @类名 ComAudio
 @主题 声音组件
 @细节 保存声音文件路径，封装播放背景音乐，效果接口，方便以组件式编程，配合解析cocos studio 1.x场景编辑器导出的数据
 @组 组件
 */
class CC_STUDIO_DLL ComAudio : public cocos2d::Component
{

    DECLARE_CLASS_COMPONENT_INFO

public:
    /**
     * @js ctor
     */
    /**
    @主题 声音组件构造函数
    */
    ComAudio(void);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 声音组件析构函数
    */
    virtual ~ComAudio(void);
    
public:
    /**
    @主题 初始化声音组件
    @返回 true 初始化成功，否则false
    */
    virtual bool init() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 node调用onEnter的时候，会调用组件的onEnter
    @返回 无
    */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 node调用onExit的时候，会调用组件的onExit
    @返回 无
    */
    virtual void onExit() override;
    /**
    @主题 判断声音组件是否可用
    @返回 可用返回true，否则返回false
    */
    virtual bool isEnabled() const override;
    /**
    @主题 设置当前声音组件是否可用
    @参数 b true为可用，false为不可用
    @返回 无
    */
    virtual void setEnabled(bool b) override;
    /**
    @主题 根据cocos studio 1.x 场景编辑器导出的json数据反序列化本身
    @参数 r SerData对象指针
    @返回 true 反序列化成功，false 反序列化失败
    */
    virtual bool serialize(void* r) override;
   /**
    @主题 创建声音组件
    @返回 声音组件指针
    */
    static ComAudio* create(void);
   
public:
   /**
    @主题 释放声音引擎对象，停止播放所有背景音与音效
    @返回 无
    */
    void end();
    /**
    @主题 预加载背景音乐
    @参数 pszFilePath 背景音乐路径
    @返回 无
    */
    void preloadBackgroundMusic(const char* pszFilePath);
    /**
    @主题 播放背景音乐，如果发现没有预加载此音乐，会先预加载，然后执行播放
    @参数 pszFilePath 背景音乐路径
    @参数 bLoop true 循环播放 false 播放一次
    @返回 无
    */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    /**
    @主题 播放背景音乐，如果发现没有预加载此音乐，会先预加载，然后播放，根据成员变量_loop判断是否循环播放
    @参数 pszFilePath 背景音乐路径
    @返回 无
    */
    void playBackgroundMusic(const char* pszFilePath);
    /**
    @主题 根据_filePath与_loop来播放背景音乐
    @返回 无
    */
    void playBackgroundMusic();
    /**
    @主题 停止播放背景音乐并是否释放音乐缓存
    @参数 bReleaseData true 停止并释放缓存 false 仅停止播放
    @返回 无
    */
    void stopBackgroundMusic(bool bReleaseData);
    /**
    @主题 停止播放背景音乐
    @返回 无
    */
    void stopBackgroundMusic();
    /**
    @主题 暂停播放背景音乐
    @返回 无
    */
    void pauseBackgroundMusic();
    /**
    @主题 恢复暂停，继续播放背景音乐
    @返回 无
    */
    void resumeBackgroundMusic();
    /**
    @主题 倒带播放背景音乐
    @返回 无
    */
    void rewindBackgroundMusic();
    /**
    @主题 背景音乐是否可以将要播放
    @返回 true 可以播放 false 将不能播放
    */
    bool willPlayBackgroundMusic();
    /**
    @主题 背景音乐是否正在播放
    @返回 true 正在播放 否则 false
    */
    bool isBackgroundMusicPlaying();
    /**
    @主题 获取背景音乐音量
    @返回 背景音乐的音量
    */
    float getBackgroundMusicVolume();
    /**
    @主题 设置背景音乐音量
    @参数 volume 音量大小
    @返回 无
    */
    void setBackgroundMusicVolume(float volume);
    /**
    @主题 获取效果音乐音量
    @返回 背景效果的音量
    */
    float getEffectsVolume();
    /**
    @主题 设置效果音乐音量
    @参数 volume 音量大小
    @返回 无
    */
    void setEffectsVolume(float volume);
    /**
    @主题 播放效果音乐，如果发现没有预加载此音乐，会先预加载，然后播放
    @参数 pszFilePath 效果音乐路径
    @参数 bLoop true 循环播放 false 播放一次
    @返回 效果音乐ID
    */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);
    /**
    @主题 播放效果音乐，如果发现没有预加载此音乐，会先预加载，然后播放，根据成员变量_loop判断是否循环播放
    @参数 pszFilePath 背景音乐路径
    @返回 效果音乐ID
    */
    unsigned int playEffect(const char* pszFilePath);
    /**
    @主题 根据_filePath与_loop来播放播放音乐
    @返回 效果音乐ID
    */
    unsigned int playEffect();
    /**
    @主题 暂停播放效果音乐
    @参数 nSoundID 效果音乐ID
    @返回 无
    */
    void pauseEffect(unsigned int nSoundId);
    /**
    @主题 暂停所有效果音乐
    @返回 无
    */
    void pauseAllEffects();
    /**
    @主题 恢复暂停效果音乐，继续播放
    @参数 nSoundID 效果音乐ID
    @返回 无
    */
    void resumeEffect(unsigned int nSoundId);
    /**
    @主题 恢复暂停的所有效果音乐，继续播放
    @返回 无
    */
    void resumeAllEffects();
    /**
    @主题 停止播放效果音乐
    @参数 nSoundID 效果音乐ID
    @返回 无
    */
    void stopEffect(unsigned int nSoundId);
    /**
    @主题 停止所有效果音乐
    @返回 无
    */
    void stopAllEffects();
    /**
    @主题 预加载效果音乐
    @参数 pszFilePath 背景音乐路径
    @返回 无
    */
    void preloadEffect(const char* pszFilePath);
    /**
    @主题 释放预加载效果音乐缓存
    @参数 pszFilePath 背景音乐路径
    @返回 无
    */
    void unloadEffect(const char* pszFilePath);
    /**
    @主题 设置音乐路径
    @参数 pszFilePath 音乐路径
    @返回 无
    */
    void setFile(const char* pszFilePath);
    /**
    @主题 获取音乐路径
    @返回 _filePath 音乐路径
    */
    const char* getFile();
    /**
    @主题 设置是否循环
    @参数 bLoop 是否循环
    @返回 无
    */
    void setLoop(bool bLoop);
    /**
    @主题 判断是否循环
    @返回 true 循环 false 不循环
    */
    bool isLoop();
private:
	std::string _filePath;
	bool _loop;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
