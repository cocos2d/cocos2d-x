/****************************************************************************
Copyright (c) 2010      Steve Oldmeadow
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#include "Export.h"

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define CC_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#define CC_DEPRECATED_ATTRIBUTE
#endif

/**
* @addtogroup core
* @{
*/

namespace CocosDenshion {

/**
 * @class SimpleAudioEngine
 *
 * @brief @~english Offers a very simple interface to play background music & sound effects.
 * @~chinese 提供播放音效和背景音乐的一系列接口。
 *
 * @note @~english Make sure to call SimpleAudioEngine::end() when the sound engine is not needed anymore to release allocated resources.
 * @~chinese 当不再使用音效系统时，确保调用了SimpleAudioEngine::end()来释放所有分配出来的资源。
 * @js cc.audioEngine
 */

class EXPORT_DLL SimpleAudioEngine
{
public:
    /**
     * @brief @~english Returns a shared instance of the SimpleAudioEngine.
     * @~chinese 获取共享的实例，如果是第一次调用，会自动创建一个实例。
     * @js NA
     */
    static SimpleAudioEngine* getInstance();

    /**
     * @deprecated Use `getInstance` instead.
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static SimpleAudioEngine* sharedEngine() { return SimpleAudioEngine::getInstance(); }

    /**
     * @brief @~english Release the shared Engine object.
     * @~chinese 释放音效引擎实例。
     *
     * @warning @~english It must be called before the application exit, or it will lead to memory leaks.
     * @~chinese 在游戏退出时需要调用这个方法，不然的话会导致内存泄漏。
     * @lua destroyInstance
     */
    static void end();

    /**
     * @brief @~english Preload background music.
     * @~chinese 预加载背景音乐。
     *
     * @param filePath @~english The path of the background music file.
     * @~chinese 背景音乐的文件路径。
     * @js NA
     * @lua preloadMusic
     */
    virtual void preloadBackgroundMusic(const char* filePath);
    
    /**
     * @~brief @~english Play background music.
     * @~chinese 播放背景音乐。
     * 
     * @param filePath @~english The path of the background music file,or the FileName of T_SoundResInfo.
     * @~chinese 背景音乐的文件路径或T_SoundResInfo中的FileName字段。
     * @param loop @~english Whether the background music loop or not.
     * @~chinese 背景音乐是否循环播放。
     * @js playMusic
     * @lua playMusic
     */
    virtual void playBackgroundMusic(const char* filePath, bool loop = false);

    /**
     * @brief @~english Stop playing background music.
     * @~chinese 停止播放背景音乐。
     *
     * @param releaseData @~english If release the background music data or not.As default value is false.
     * @~chinese 是否释放背景音乐的数据，默认值为false。
     * @js stopMusic
     * @lua stopMusic
     */
    virtual void stopBackgroundMusic(bool releaseData = false);

    /**
     * @brief @~english Pause playing background music.
     * @~chinese 暂停播放背景音乐。
     * @js pauseMusic
     * @lua pauseMusic
     */
    virtual void pauseBackgroundMusic();

    /**
     * @brief @~english Resume playing background music.
     * @~chinese 恢复播放背景音乐。
     * @js resumeMusic
     * @lua resumeMusic
     */
    virtual void resumeBackgroundMusic();

    /**
     * @brief @~english Rewind playing background music.
     * @~chinese 将背景音乐倒回起始点播放。
     * @js rewindMusic
     * @lua rewindMusic
     */
    virtual void rewindBackgroundMusic();

    /**
     * @brief @~english Indicates whether any background music can be played or not.
     * @~chinese 是否会播放背景音乐。
     *
     * @return true @~english if background music can be played, otherwise false.
     * @~chinese 如果背景音乐会被播放返回true，否则返回false。
     * @js willPlayMusic
     * @lua willPlayMusic
     */
    virtual bool willPlayBackgroundMusic();

    /**
     * @brief @~english Indicates whether the background music is playing.
     * @~chinese 背景音乐是否在播放。
     *
     * @return true @~english if the background music is playing, otherwise false.
     * @~chinese 正在播放返回true，否则返回false。
     * @js isMusicPlaying
     * @lua isMusicPlaying
     */
    virtual bool isBackgroundMusicPlaying();

    // 
    // properties
    //

    /**
     * @brief @~english The volume of the background music within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese 获取背景音乐的音量，音量的值的范围为0.0到1.0。
     * @js getMusicVolume
     * @lua getMusicVolume
     */
    virtual float getBackgroundMusicVolume();

    /**
     * @brief @~english Set the volume of background music.
     * @~chinese 设置背景音乐音量。
     *
     * @param volume @~english must be within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese 背景音乐音量大小，范围必须为0.0到1.0之间。
     * @js setMusicVolume
     * @lua setMusicVolume
     */
    virtual void setBackgroundMusicVolume(float volume);

    /**
     * @brief @~english The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese 获取音效的音量大小,音量大小范围为0.0到1.0。
     */
    virtual float getEffectsVolume();

    /**
     * @brief @~english Set the volume of sound effects.
     * @~chinese 设置音效的音量大小。
     *
     * @param volume @~english must be within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese 音效的音量大小，范围为0.0到1.0。
     */
    virtual void setEffectsVolume(float volume);

    // 
    // for sound effects

    /**
     * @brief @~english Play sound effect with a file path, pitch, pan and gain.
     * @~chinese 播放音效
     *
     * @param filePath @~english The path of the effect file. @~chinese 音效文件的路径。
     * @param loop @~english Determines whether to loop the effect playing or not. The default value is false. @~chinese 是否循环播放,默认为false,不循环。
     * @param pitch @~english Frequency, normal value is 1.0. Will also change effect play time. @~chinese 频率，正常情况下为1.0,在播放时也可以改变该值。
     * @param pan @~english Stereo effect, in the range of [-1..1] where -1 enables only left channel. @~chinese 声道，范围为-1到1，为-1时表示只有左声道，为1时表示只有右声道。
     * @param gain @~english Volume, in the range of [0..1]. The normal value is 1. @~chinese 音量增益, 范围为0到1，默认值为1。
     * @return @~english The sound id. @~chinese 声音id。
     * 
     * @note @~english Full support is under development, now there are limitations:
     *     - no pitch effect on Samsung Galaxy S2 with OpenSL backend enabled;
     *     - no pitch/pan/gain on win32.
     * @~chinese 现在还不能完全支持所有参数，限制的功能如下：
     *     - 在Samsung Galaxy S2上如果启用了OpenSL那么pitch参数无效；
     *     - 在emscrippten, win32, marmalade上pitch/pan/gain参数无效
     */
    virtual unsigned int playEffect(const char* filePath, bool loop = false,
                                    float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);

    /**
     * @brief @~english Pause playing sound effect.
     * @~chinese 暂停播放指定音效。
     *
     * @param soundId @~english The return value of function playEffect.
     * @~chinese 音效id。
     */
    virtual void pauseEffect(unsigned int soundId);

    /**
     * @brief @~english Pause all playing sound effect.
     * @~chinese 暂停所有播放的音效。
     */
    virtual void pauseAllEffects();

    /**
     * @brief @~english Resume playing sound effect.
     * @~chinese 恢复暂停播放指定的音效。
     *
     * @param soundId @~english The return value of function playEffect.
     * @~chinese playEffect返回的资源id。
     */
    virtual void resumeEffect(unsigned int soundId);

    /**
     * @brief @~english Resume all playing sound effect.
     * @~chinese 恢复所有暂停的音效。
     */
    virtual void resumeAllEffects();

    /**
     * @brief @~english Stop playing sound effect.
     * @~chinese 停止播放指定的音效。
     *
     * @param soundId @~english The return value of function playEffect.
     * @~chinese playEffect返回的资源id。
     */
    virtual void stopEffect(unsigned int soundId);

    /**
     * @brief @~english Stop all playing sound effects.
     * @~chinese 停止所有播放的音效。
     */
    virtual void stopAllEffects();

    /**
     * @brief @~english Preload a compressed audio file.
     * The compressed audio will be decoded to wave, then written into an internal buffer in SimpleAudioEngine.
     * @~chinese 预加载音效文件。
     *
     * @param filePath @~english The path of the effect file. 
     * @~chinese 音效文件路径。
     * @js NA
     */
    virtual void preloadEffect(const char* filePath);

    /**
     * @brief @~english Unload the preloaded effect from internal buffer.
     * @~chinese 卸载预加载到内存中的音效文件。
     *
     * @param filePath @~english The path of the effect file.
     * @~chinese 音效文件的路径。
     */
    virtual void unloadEffect(const char* filePath);

protected:
    /**
    * Constructor of SimpleAudioEngine.
    */
    SimpleAudioEngine();

    /**
    * Destructor of SimpleAudioEngine.
    */
    virtual ~SimpleAudioEngine();
};

} // end of namespace CocosDenshion

// end audio group
/// @}

#endif // _SIMPLE_AUDIO_ENGINE_H_
