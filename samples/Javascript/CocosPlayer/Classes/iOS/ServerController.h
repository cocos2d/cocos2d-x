/*
 * CocosBuilder: http://www.cocosbuilder.com
 *
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#import <Foundation/Foundation.h>
#import "ThoMoServerStub.h"
#import "cocos2d.h"

// Network status states
typedef enum {
    kCCBNetworkUninitialized = -1,
	kCCBNetworkStatusWaiting,
	kCCBNetworkStatusTooMany,
	kCCBNetworkStatusConnected,
	kCCBNetworkStatusShutDown,
} CCBNetworkStatus;

// Player status states
typedef enum {
    kCCBPlayerStatuskUninitialized = -1,
	kCCBPlayerStatusIdle,
	kCCBPlayerStatusPlay,
	kCCBPlayerStatusUnzip,
	kCCBPlayerStatusStop,
	kCCBPlayerStatusNotConnected,
	kCCBPlayerStatusExecuteScript,
} CCBPlayerStatus;

// Predefined messages
extern NSString *kCCBNetworkStatusStringWaiting;
extern NSString *kCCBNetworkStatusStringTooMany;
extern NSString *kCCBNetworkStatusStringConnected;
extern NSString *kCCBNetworkStatusStringShutDown;

extern NSString *kCCBPlayerStatusStringNotConnected;
extern NSString *kCCBPlayerStatusStringIdle;
extern NSString *kCCBPlayerStatusStringUnzip;
extern NSString *kCCBPlayerStatusStringStop;
extern NSString *kCCBPlayerStatusStringPlay;
extern NSString *kCCBPlayerStatusStringScript;

@interface ServerController : NSObject <ThoMoServerDelegateProtocol>
{
    ThoMoServerStub* server;
    
    NSMutableSet* connectedClients;
    
    NSFileHandle* pipeReadHandle;

	CCBNetworkStatus networkStatus;
	CCBPlayerStatus playerStatus;
	BOOL playerWindowDisplayed;
}

/** Network status: who is the network connection */
@property (nonatomic, readwrite) CCBNetworkStatus networkStatus;

/** State of the player: playing, unzipping, stopping, etc.  */
@property (nonatomic, readwrite) CCBPlayerStatus playerStatus;

@property (nonatomic, readwrite) BOOL playerWindowDisplayed;
@property (nonatomic, readwrite) BOOL isRetina;
@property (nonatomic, readwrite) BOOL isIPhone;


@property (nonatomic,copy) NSString* serverStatus;

- (void) start;
- (void) stop;
- (void) setPairingCode: (NSString *)code;
- (void) startIfNotStarted;
- (void) updatePairing;

- (void) sendDeviceName;
- (void) sendResultString:(NSString*) str;
- (void) sendLog:(NSString*)log;
- (void) sendFileList;

@end
