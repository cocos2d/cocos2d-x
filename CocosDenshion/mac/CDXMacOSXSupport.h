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

/**
 A set of proxy classes to allow iOS audio code to run on MacOS X. AVAudioPlayer is implemented using NSSound.
 AVAudioSession is a "do nothing" class as it isn't really relevant on MacOS X.
 
 Limitations:
 AVAudioPlayer numberOfLoops not correctly supported.  Looping is either on or off, can not specify a specific number of loops.
 AVAudioPlayer panning not supported.
 AVAudioPlayer metering not supported.
 AVAudioSession nothing is supported, not applicable to MacOS X.
 */

#import <Availability.h>
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

#import <Foundation/Foundation.h>
#import <AppKit/NSSound.h>

enum AudioSessionProperties {
	kAudioSessionProperty_OtherAudioIsPlaying,
	kAudioSessionProperty_AudioRoute	
};
#ifdef __cplusplus
extern "C" {
#endif	
	
extern OSStatus AudioSessionGetProperty(UInt32 inID, UInt32 *ioDataSize, void *outData);    

#ifdef __cplusplus
}
#endif
/**
 Based on AVAudioPlayer.h header in AVFoundation headers
 */
@class NSData, NSURL, NSError, NSDictionary;
@protocol AVAudioPlayerDelegate;

/* This class is available with iPhone 2.2 or later */
@interface AVAudioPlayer : NSObject <NSSoundDelegate> {
	
	// properties
	id<AVAudioPlayerDelegate> delegate;
	NSUInteger numberOfChannels;
	BOOL playing;
	NSTimeInterval duration; 
	NSURL *url;
	NSData *data;
	float pan;
	float volume;
	NSTimeInterval currentTime;
	NSTimeInterval deviceCurrentTime; 
	NSInteger numberOfLoops;
	BOOL meteringEnabled;
	

@private
    NSSound* _player;
}

/* For all of these init calls, if a return value of nil is given you can check outError to see what the problem was.
 If not nil, then the object is usable for playing
 */

/* all data must be in the form of an audio file understood by CoreAudio */
- (id)initWithContentsOfURL:(NSURL *)theUrl error:(NSError **)outError;
- (id)initWithData:(NSData *)theData error:(NSError **)outError;

/* transport control */
/* methods that return BOOL return YES on success and NO on failure. */
- (BOOL)prepareToPlay;	/* get ready to play the sound. happens automatically on play. */
- (BOOL)play;			/* sound is played asynchronously. */
- (BOOL)playAtTime:(NSTimeInterval) time;  /* play a sound some time in the future. time should be greater than deviceCurrentTime. */
- (void)pause;			/* pauses playback, but remains ready to play. */
- (void)stop;			/* stops playback. no longer ready to play. */

/* properties */

@property(readonly, getter=isPlaying) BOOL playing;

@property(readonly) NSUInteger numberOfChannels;
@property(readonly) NSTimeInterval duration; /* the duration of the sound. */

@property(assign) id<AVAudioPlayerDelegate> delegate; /* the delegate will be sent playerDidFinishPlaying */ 

/* one of these three properties will be non-nil based on the init... method used */
@property(readonly) NSURL *url; /* returns nil if object was not created with a URL */
@property(readonly) NSData *data; /* returns nil if object was not created with a data object */
@property float pan; /* set panning. -1.0 is left, 0.0 is center, 1.0 is right. */
@property float volume; /* The volume for the sound. The nominal range is from 0.0 to 1.0. */

/*  If the sound is playing, currentTime is the offset into the sound of the current playback position.  
 If the sound is not playing, currentTime is the offset into the sound where playing would start. */
@property NSTimeInterval currentTime;

/* returns the current time associated with the output device */
@property(readonly) NSTimeInterval deviceCurrentTime; 

/* "numberOfLoops" is the number of times that the sound will return to the beginning upon reaching the end. 
 A value of zero means to play the sound just once.
 A value of one will result in playing the sound twice, and so on..
 Any negative number will loop indefinitely until stopped.
 */
@property NSInteger numberOfLoops;

/* metering */

@property(getter=isMeteringEnabled) BOOL meteringEnabled; /* turns level metering on or off. default is off. */

- (void)updateMeters; /* call to refresh meter values */
- (float)peakPowerForChannel:(NSUInteger)channelNumber; /* returns peak power in decibels for a given channel */
- (float)averagePowerForChannel:(NSUInteger)channelNumber; /* returns average power in decibels for a given channel */

@end

/* A protocol for delegates of AVAudioPlayer */
@protocol AVAudioPlayerDelegate <NSObject>
@optional 
/* audioPlayerDidFinishPlaying:successfully: is called when a sound has finished playing. This method is NOT called if the player is stopped due to an interruption. */
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;

/* if an error occurs while decoding it will be reported to the delegate. */
- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error;

/* audioPlayerBeginInterruption: is called when the audio session has been interrupted while the player was playing. The player will have been paused. */
- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player;

/* audioPlayerEndInterruption:withFlags: is called when the audio session interruption has ended and this player had been interrupted while playing. */
/* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withFlags:(NSUInteger)flags;

/* audioPlayerEndInterruption: is called when the preferred method, audioPlayerEndInterruption:withFlags:, is not implemented. */
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player;
@end


/**
 Taken from AVAudioSession.h header in AVFoundation headers
 */

/* This protocol is available with iPhone 3.0 or later */
@protocol AVAudioSessionDelegate;
@class NSError, NSString;

/* values for the category property */
extern NSString *const AVAudioSessionCategoryAmbient;
extern NSString *const AVAudioSessionCategorySoloAmbient;
extern NSString *const AVAudioSessionCategoryPlayback;
extern NSString *const AVAudioSessionCategoryRecord;
extern NSString *const AVAudioSessionCategoryPlayAndRecord;
extern NSString *const AVAudioSessionCategoryAudioProcessing;

enum {
	AVAudioSessionInterruptionFlags_ShouldResume = 1
};

enum {	
	AVAudioSessionSetActiveFlags_NotifyOthersOnDeactivation = 1
};

@interface AVAudioSession : NSObject {
	
	// properties
	NSString* category;
	double preferredHardwareSampleRate;
	NSTimeInterval preferredIOBufferDuration;
	
	BOOL inputIsAvailable;
	double currentHardwareSampleRate;
	NSInteger currentHardwareInputNumberOfChannels;
	NSInteger currentHardwareOutputNumberOfChannels;
	id<AVAudioSessionDelegate> delegate;

@private
    __strong void *_impl;
}

/* returns singleton instance */
+ (id)sharedInstance;

@property(assign) id<AVAudioSessionDelegate> delegate;

- (BOOL)setActive:(BOOL)beActive error:(NSError**)outError;
- (BOOL)setActive:(BOOL)beActive withFlags:(NSInteger)flags error:(NSError**)outError;

- (BOOL)setCategory:(NSString*)theCategory error:(NSError**)outError;
- (BOOL)setPreferredHardwareSampleRate:(double)sampleRate error:(NSError**)outError;
- (BOOL)setPreferredIOBufferDuration:(NSTimeInterval)duration error:(NSError**)outError;

@property(readonly) NSString* category;
@property(readonly) double preferredHardwareSampleRate;
@property(readonly) NSTimeInterval preferredIOBufferDuration;

@property(readonly) BOOL inputIsAvailable;
@property(readonly) double currentHardwareSampleRate;
@property(readonly) NSInteger currentHardwareInputNumberOfChannels;
@property(readonly) NSInteger currentHardwareOutputNumberOfChannels;

@end


/* A protocol for delegates of AVAudioSession */
@protocol AVAudioSessionDelegate <NSObject>
@optional 

- (void)beginInterruption;

- (void)endInterruptionWithFlags:(NSUInteger)flags;

- (void)endInterruption; /* endInterruptionWithFlags: will be called instead if implemented. */

- (void)inputIsAvailableChanged:(BOOL)isInputAvailable;
@end

#endif
