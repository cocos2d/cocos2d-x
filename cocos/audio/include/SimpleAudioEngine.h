/****************************************************************************
Copyright (c) 2010      Steve Oldmeadow
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef _SIMPLE_AUDIO_ENGINE_H_
#define _SIMPLE_AUDIO_ENGINE_H_

#include <stddef.h>
#include "Export.h"
#include <typeinfo>
#include <ctype.h>
#include <string.h>

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define CC_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#define CC_DEPRECATED_ATTRIBUTE
#endif

namespace CocosDenshion {

/**
  @class          SimpleAudioEngine
  @brief          提供播放音效和背景音乐的一系列接口
  @note           当不再使用音效系统时，确保调用了SimpleAudioEngine::end()来释放所有分配出来的资源
 */

class EXPORT_DLL SimpleAudioEngine
{
public:
    /**
     @brief 获取共享的实例，如果是第一次调用，会自动创建一个实例
     */
    static SimpleAudioEngine* getInstance();
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static SimpleAudioEngine* sharedEngine() { return SimpleAudioEngine::getInstance(); }

    /**
     @brief 释放音效引擎实例
     @warning 在游戏退出时需要调用这个方法，不然的话会导致内存泄漏
     */
    static void end();

protected:
    SimpleAudioEngine();
    virtual ~SimpleAudioEngine();

public:

    /**
     @brief 预加载背景音乐
     @param pszFilePath 背景音乐的文件路径
     * @js preloadMusic
     * @lua preloadMusic
     */
    virtual void preloadBackgroundMusic(const char* pszFilePath);
    
    /**
     @brief 播放背景音乐
     @param pszFilePath 背景音乐的文件路径活T_SoundResInfo中的FileName字段
     @param bLoop 背景音乐是否循环播放
     * @js playMusic
     * @lua playMusic
     */
    virtual void playBackgroundMusic(const char* pszFilePath, bool bLoop = false);

    /**
     @brief 停止播放背景音乐
     @param bReleaseData 是否释放背景音乐的数据，默认值为false
     * @js stopMusic
     * @lua stopMusic
     */
    virtual void stopBackgroundMusic(bool bReleaseData = false);

    /**
     @brief 暂停播放背景音乐
     * @js pauseMusic
     * @lua pauseMusic
     */
    virtual void pauseBackgroundMusic();

    /**
     @brief 恢复播放背景音乐
     * @js resumeMusic
     * @lua resumeMusic
     */
    virtual void resumeBackgroundMusic();

    /**
     @brief 把背景音乐倒过来放
     * @js rewindMusic
     * @lua rewindMusic
     */
    virtual void rewindBackgroundMusic();

    /**
     @brief 是否会播放背景音乐
     @return 如果背景音乐会被播放返回<i>true</i>,否则返回<i>false</i>.
     * @js willPlayMusic
     * @lua willPlayMusic
     */
    virtual bool willPlayBackgroundMusic();

    /**
     @brief 背景音乐是否在播放
     @return 正在播放返回<i>true</i>,否则返回<i>false</i>
     * @js isMusicPlaying
     * @lua isMusicPlaying
     */
    virtual bool isBackgroundMusicPlaying();

    // 
    // properties
    //

    /**
     @brief 获取背景音乐的音量，音量的值的范围为0.0到1.0
     * @js getMusicVolume
     * @lua getMusicVolume
     */
    virtual float getBackgroundMusicVolume();

    /**
     @brief 设置背景音乐音量
     @param volume 背景音乐音量大小，范围必须为0.0到1.0之间
     * @js setMusicVolume
     * @lua setMusicVolume
     */
    virtual void setBackgroundMusicVolume(float volume);

    /**
    @brief 获取音效的音量大小,音量大小范围为0.0到1.0
    */
    virtual float getEffectsVolume();

    /**
    @brief 设置音效的音量大小
    @param volume 音效的音量大小，范围为0.0到1.0
    */
    virtual void setEffectsVolume(float volume);

    // 
    // for sound effects

    /**
    @brief 播放音效
    @param pszFilePath 音效文件的路径
    @param bLoop 是否循环播放,默认为false,不循环
    @param pitch 频率，正常情况下为1.0,在播放时也可以改变该值
    @param pan   声道，范围为-1到1，为-1时表示只有左声道，为1时表示只有右声道
    @param gain  音量增益, 范围为0到1，默认值为1
    @return OpenAL的资源id

    @note 现在还不能完全支持所有参数，限制的功能如下：
        - 在Samsung Galaxy S2上如果启用了OpenSL那么pitch参数无效；
        - 在emscrippten, win32, marmalade上pitch/pan/gain参数无效
    */
    virtual unsigned int playEffect(const char* pszFilePath, bool bLoop = false,
                                    float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);

    /**
    @brief 暂停播放音效
    @param nSoundId playEffect返回的资源id
    */
    virtual void pauseEffect(unsigned int nSoundId);

    /**
    @brief 暂停所有播放的音效
    */
    virtual void pauseAllEffects();

    /**
    @brief 恢复暂停播放的音效
    @param nSoundId playEffect返回的资源id
    */
    virtual void resumeEffect(unsigned int nSoundId);

    /**
    @brief 恢复所有暂停的音效
    */
    virtual void resumeAllEffects();

    /**
    @brief 停止播放音效
    @param nSoundId playEffect返回的资源id
    */
    virtual void stopEffect(unsigned int nSoundId);

    /**
    @brief 停止所有播放的音效
    */
    virtual void stopAllEffects();

    /**
    @brief          加载压缩过的音效文件
    @details        压缩过的音频文件会解码成wave文件，并且写入SimpleAudioEngine的内存中
    @param pszFilePath 音效文件路径
    */
    virtual void preloadEffect(const char* pszFilePath);

    /**
    @brief          卸载预加载到内存中的音效文件
    @param pszFilePath        音效文件的路径
    */
    virtual void unloadEffect(const char* pszFilePath);
};

} // end of namespace CocosDenshion

#endif // _SIMPLE_AUDIO_ENGINE_H_
