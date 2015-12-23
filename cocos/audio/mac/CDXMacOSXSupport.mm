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

#import <Availability.h>
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

#import "CDXMacOSXSupport.h"
#import "SimpleAudioEngine.h"
#import "CocosDenshion.h"

NSString * const AVAudioSessionCategoryAmbient = @"AVAudioSessionCategoryAmbient";
NSString *const AVAudioSessionCategorySoloAmbient = @"AVAudioSessionCategorySoloAmbient";
NSString *const AVAudioSessionCategoryPlayback = @"AVAudioSessionCategoryPlayback";
NSString *const AVAudioSessionCategoryRecord = @"AVAudioSessionCategoryRecord";
NSString *const AVAudioSessionCategoryPlayAndRecord = @"AVAudioSessionCategoryPlayAndRecord";
NSString *const AVAudioSessionCategoryAudioProcessing = @"AVAudioSessionCategoryAudioProcessing";

OSStatus AudioSessionGetProperty(UInt32 inID, UInt32 *ioDataSize, void *outData) {
	//TODO: set outData appropriately
	return 0;
}    

@implementation CCAudioPlayer

@synthesize delegate, numberOfChannels, pan, deviceCurrentTime, url, data;

- (id)initWithContentsOfURL:(NSURL *)theUrl error:(NSError **)outError {
	if ((self = [super init])) {
		_player = [[NSSound alloc] initWithContentsOfURL:theUrl byReference:YES];
		if (_player != nil) {
			_player.delegate = self;
			CDLOG(@"Denshion::CDXMacOSXSupport - NSSound allocated for %@", theUrl);
		}	
	}
	return self;
}

- (id)initWithData:(NSData *)theData error:(NSError **)outError { 
	if ((self = [super init])) {
		_player = [[NSSound alloc] initWithData:theData];
		if (_player != nil) {
			_player.delegate = self;
			CDLOG(@"Denshion::CDXMacOSXSupport - NSSound allocated for %@", theData);
		}	
	}
	return self;
}


-(void) dealloc {
	[_player release];
	[super dealloc];
}	

- (void)sound:(NSSound *)sound didFinishPlaying:(BOOL)finished {
	if (self.delegate && [self.delegate respondsToSelector:@selector(audioPlayerDidFinishPlaying:successfully:)]) {
		[self.delegate audioPlayerDidFinishPlaying:self successfully:finished];
	}	
}	

- (BOOL)play {
	BOOL result;
	result = [_player play];
	if (!result) {
		//May be paused, try resuming instead 
		result = [_player resume];
	}	
	return result;
}

- (BOOL) resume{
    BOOL result = [_player resume];
    return result;
}


-(void) pause {
	[_player pause];
}	

-(void) stop {
	[_player stop];
}	

-(BOOL) isPlaying {
	return [_player isPlaying];
}	

-(void) setVolume:(float) vol {
	[_player setVolume:vol];
}

-(float) volume {
	return [_player volume];
}	

-(void) setNumberOfLoops:(NSInteger) nOfLoops {
	if (nOfLoops < 0) {
		[_player setLoops:YES];
	} else {
		[_player setLoops:NO];
	}	
}	

-(NSInteger) numberOfLoops {
	if (_player.loops) {
		return -1;
	} else {
		return 0;
	}	
}	

-(void) setCurrentTime:(NSTimeInterval) aCurrentTime {
	[_player setCurrentTime:aCurrentTime];
}

-(NSTimeInterval) currentTime {
	return [_player currentTime];
}

-(NSTimeInterval) duration {
	return [_player duration];
}

#pragma mark unsupported
- (BOOL)prepareToPlay {
	return YES;
}	
-(BOOL)playAtTime:(NSTimeInterval)time {
	return YES;
}	
-(void) setMeteringEnabled:(BOOL) enabled {
}	
-(BOOL) isMeteringEnabled {
	return NO;
}	
- (void)updateMeters{}
- (float)peakPowerForChannel:(NSUInteger)channelNumber{return 0.0f;} 
- (float)averagePowerForChannel:(NSUInteger)channelNumber{return 0.0f;}
@end

/**
 A "do nothing" implementation - AVAudioSession is not really relevant to Mac OS X.
 */
@implementation AVAudioSession
@synthesize delegate, category, preferredHardwareSampleRate, preferredIOBufferDuration;
@synthesize inputIsAvailable, currentHardwareSampleRate, currentHardwareInputNumberOfChannels, currentHardwareOutputNumberOfChannels;

+ (id)sharedInstance {
	return nil;
}	

- (BOOL)setActive:(BOOL)beActive error:(NSError**)outError {return YES;}
- (BOOL)setActive:(BOOL)beActive withFlags:(NSInteger)flags error:(NSError**)outError {return YES;}
- (BOOL)setCategory:(NSString*)theCategory error:(NSError**)outError {return YES;}
- (BOOL)setPreferredHardwareSampleRate:(double)sampleRate error:(NSError**)outError {return YES;}
- (BOOL)setPreferredIOBufferDuration:(NSTimeInterval)duration error:(NSError**)outError {return YES;}

@end
#endif
