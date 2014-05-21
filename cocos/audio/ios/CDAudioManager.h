/*
 Copyright (c) 2010 Steve Oldmeadow
 
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
 
 $Id$
 */

#import "CocosDenshion.h"
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
    #import <AVFoundation/AVFoundation.h>
#else
    #import "CDXMacOSXSupport.h"
#endif

/** 音频引擎的不同模式 */
typedef enum {
    kAMM_FxOnly,                    //!其他app也可以播放音频
    kAMM_FxPlusMusic,                //!只有当前app可以播放音频
    kAMM_FxPlusMusicIfNoOtherAudio,    //!如果其他app正在播放音频，允许它继续播放，取消现在的播放请求
    kAMM_MediaPlayback,                //!播放当前音频
    kAMM_PlayAndRecord                //!当前音频接管音频输入和输出
} tAudioManagerMode;

/** 音频引擎的状态值 */
typedef enum {
    kAMStateUninitialised, //!音频管理对象未初始化-不能使用
    kAMStateInitialising,  //!音频管理对象正在初始化中-不能使用
    kAMStateInitialised       //!音频管理对象已经初始化完成-可以安全使用
} tAudioManagerState;

typedef enum {
    kAMRBDoNothing,                //音频管理对象不会改变当前任何操作
    kAMRBStopPlay,                //背景音乐将会暂停并在播放完成后恢复播放
    kAMRBStop                    //背景音乐将会停止并且不会被恢复-也许你在游戏里面会想用这种模式
} tAudioManagerResignBehavior;

/** Notifications */
extern NSString * const kCDN_AudioManagerInitialised;

@interface CDAsynchInitialiser : NSOperation {}    
@end

/** CDAudioManager 提供两个声道，左声道和右声道*/
typedef enum {
    kASC_Left = 0,
    kASC_Right = 1
} tAudioSourceChannel;    

typedef enum {
    kLAS_Init,
    kLAS_Loaded,
    kLAS_Playing,
    kLAS_Paused,
    kLAS_Stopped,
} tLongAudioSourceState;

@class CDLongAudioSource;
@protocol CDLongAudioSourceDelegate <NSObject>
@optional
/** 声道播放完成 */
- (void) cdAudioSourceDidFinishPlaying:(CDLongAudioSource *) audioSource;
/** 声道播放的音频源有变化 */
- (void) cdAudioSourceFileDidChange:(CDLongAudioSource *) audioSource;
@end

/**
 CDLongAudioSource represents an audio source that has a long duration which makes
 it costly to load into memory for playback as an effect using CDSoundEngine. Examples
 include background music and narration tracks. The audio file may or may not be compressed.
 Bear in mind that current iDevices can only use hardware to decode a single compressed
 audio file at a time and playing multiple compressed files will result in a performance drop
 as software decompression will take place.
 CDLongAudioSource表示的是需要花费较长时间来加载音频文件到内存中，并且使用CDSoundEngine来播放的音频源。比如：
 背景音乐或者叙述性的语音。这类的语音文件有可能被压缩，目前的设备只能硬解码单个的这类文件，如果同时播放多个这类
 文件只能通过软解码来代替。
 @since v0.99
 */
@interface CDLongAudioSource : NSObject <AVAudioPlayerDelegate, CDAudioInterruptProtocol>{
    AVAudioPlayer    *audioSourcePlayer;
    NSString        *audioSourceFilePath;
    NSInteger        numberOfLoops;
    float            volume;
    id<CDLongAudioSourceDelegate> delegate; 
    BOOL            mute;
    BOOL            enabled_;
    BOOL            backgroundMusic;
    // whether background music is paused
    BOOL            paused;
    BOOL            stopped;
@public    
    BOOL            systemPaused;//Used for auto resign handling
    NSTimeInterval    systemPauseLocation;//Used for auto resign handling
@protected
    tLongAudioSourceState state;
}    
@property (readonly) AVAudioPlayer *audioSourcePlayer;
@property (readonly) NSString *audioSourceFilePath;
@property (readwrite, nonatomic) NSInteger numberOfLoops;
@property (readwrite, nonatomic) float volume;
@property (assign) id<CDLongAudioSourceDelegate> delegate;
/* This long audio source functions as background music */
@property (readwrite, nonatomic) BOOL backgroundMusic;
@property (readonly) BOOL paused;

/** 加载文件到音频源中 */
-(void) load:(NSString*) filePath;
/** 播放音频源 */
-(void) play;
/** 停止播放音频源 */
-(void) stop;
/** 暂停播放音频源 */
-(void) pause;
/** 将音频源倒放 */
-(void) rewind;
/** 恢复暂停播放的音频源 */
-(void) resume;
/** 音频源是否在播放中 */
-(BOOL) isPlaying;

@end

/** 
 CDAudioManager 管理游戏的音频。它用于提供通过CDSoundEngine对象来播放音效的权限。CDAudioManager内部包含两个CDLongAudioSource
 对象(左右声道)，用来播放长间隔的音频比如背景音乐和叙述性的语音。另外，它来管理同其他app声音之间的切换和交互。
 环境要求:
 - Firmware: OS 2.2 or greater 
 - Files: CDAudioManager.*, CocosDenshion.*
 - Frameworks: OpenAL, AudioToolbox, AVFoundation
 @since v0.8
 */
@interface CDAudioManager : NSObject <CDLongAudioSourceDelegate, CDAudioInterruptProtocol, AVAudioSessionDelegate> {
    CDSoundEngine        *soundEngine;
    CDLongAudioSource    *backgroundMusic;
    NSMutableArray        *audioSourceChannels;
    NSString*            _audioSessionCategory;
    BOOL                _audioWasPlayingAtStartup;
    tAudioManagerMode    _mode;
    SEL backgroundMusicCompletionSelector;
    id backgroundMusicCompletionListener;
    BOOL willPlayBackgroundMusic;
    BOOL _mute;
    BOOL _resigned;
    BOOL _interrupted;
    BOOL _audioSessionActive;
    BOOL enabled_;
    
    //For handling resign/become active
    BOOL _isObservingAppEvents;
    tAudioManagerResignBehavior _resignBehavior;
}

@property (readonly) CDSoundEngine *soundEngine;
@property (readonly) CDLongAudioSource *backgroundMusic;
@property (readonly) BOOL willPlayBackgroundMusic;

/** 返回共享的单例 */
+ (CDAudioManager *) sharedManager;
+ (tAudioManagerState) sharedManagerState;
/** 设置单例的模式*/
+ (void) configure: (tAudioManagerMode) mode;
/** 异步的初始化音频引擎的模式*/
+ (void) initAsynchronously: (tAudioManagerMode) mode;
/** 同步的初始化引擎的模式，声道定义和声道数量 */
- (id) init: (tAudioManagerMode) mode;
-(void) audioSessionInterrupted;
-(void) audioSessionResumed;
-(void) setResignBehavior:(tAudioManagerResignBehavior) resignBehavior autoHandle:(BOOL) autoHandle;
/** 返回音频是否硬件层的将设备设为静音 */
-(BOOL) isDeviceMuted;
/** 返回是否有其他app在播放音频，比如iPod音乐播放程序 */
-(BOOL) isOtherAudioPlaying;
/** 设置音频管理同操作系统交互的方式，比如是否同其他app交互使用音频输出设备或者允许静音开关 */
-(void) setMode:(tAudioManagerMode) mode;
/** 关闭音频管理对象，以便于重新初始化 */
+(void) end;

/** 如果你需要使用内置的挂起行为又想在挂起时执行一些自己的音频处理操作，实现这个方法 */
- (void) applicationWillResignActive;
/** 如果你需要使用内置的恢复行为又想在恢复时执行一些自己的音频处理操作，实现这个方法. */
- (void) applicationDidBecomeActive;

//New AVAudioPlayer API
/** 从指定音频文件中加载数据到声道的音频源中 */
-(CDLongAudioSource*) audioSourceLoad:(NSString*) filePath channel:(tAudioSourceChannel) channel;
/** 恢复指定声道的音频源 */
-(CDLongAudioSource*) audioSourceForChannel:(tAudioSourceChannel) channel;

//Legacy AVAudioPlayer API
/** 播放背景音乐，可以循环也可以不循环
推荐使用.acc格式的背景音乐，因为这种格式文件可以硬件解码
 */
-(void) playBackgroundMusic:(NSString*) filePath loop:(BOOL) loop;
/** 预加载背景音乐 */
-(void) preloadBackgroundMusic:(NSString*) filePath;
/** 停止播放背景音乐 */
-(void) stopBackgroundMusic;
/** 暂停背景音乐播放 */
-(void) pauseBackgroundMusic;
/** 倒序播放背景音乐 */
-(void) rewindBackgroundMusic;
/** 恢复播放背景音乐 */
-(void) resumeBackgroundMusic;
/** 背景音乐是否正在播放中 */
-(BOOL) isBackgroundMusicPlaying;

-(void) setBackgroundMusicCompletionListener:(id) listener selector:(SEL) selector;

@end

/** 长音频源对象的增益调节器 */
@interface CDLongAudioSourceFader : CDPropertyModifier{}
@end

static const int kCDNoBuffer = -1;

/** 让缓冲区和文件名关联起来 */
@interface CDBufferManager:NSObject{
    NSMutableDictionary* loadedBuffers;
    NSMutableArray    *freedBuffers;
    CDSoundEngine *soundEngine;
    int nextBufferId;
}

-(id) initWithEngine:(CDSoundEngine *) theSoundEngine;
-(int) bufferForFile:(NSString*) filePath create:(BOOL) create;
-(void) releaseBufferForFile:(NSString *) filePath;

@end

