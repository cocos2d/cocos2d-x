/*
 *  ThoMoTCPConnection.h
 *  ThoMoNetworkingFramework
 *
 *  Created by Thorsten Karrer on 30.6.09.
 *  Copyright 2010 media computing group - RWTH Aachen University.
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#import "ThoMoTCPConnectionDelegateProtocol.h"

typedef enum ServerStubSubPackets {
	kServerStubSubPacketHeader,
	kServerStubSubPacketData,
	kServerStubSubPacketCount
} ServerStubSubPacket;

@class ThoMoServerStub;

@interface ThoMoTCPConnection : NSObject <NSStreamDelegate>
{
	id <ThoMoTCPConnectionDelegateProtocol>		delegate;
	
	NSInputStream	*inStream;
	NSOutputStream	*outStream;
	
	BOOL			inReady;
	BOOL			outReady;
	
	BOOL			streamsCanOpen;
	
	BOOL			openCallbackSent;
	
	// receiving
	ServerStubSubPacket	nextExpectedSubpacket;
	uint32_t		bytesMissingForNextSubpacket;
	uint8_t			*dataBuffer;
	uint8_t			*dataBufferCursor;
	
	//sending
	NSMutableArray	*sendObjectsQueue;
	NSMutableData	*currentSendObject;
	uint32_t			bytesRemainingToSend;
	uint8_t			*sendBuffer;
	uint8_t			*sendBufferCursor;
	BOOL			outStreamHasSpaceAvailableEventIgnored;
	
	//keepalive
	NSTimer			*keepaliveSendTimer;	
	
	// reentrancy tracking
	BOOL threadIsPresentInMethod;
}

@property (assign) id <ThoMoTCPConnectionDelegateProtocol>		delegate;

-(id)initWithDelegate:(id <ThoMoTCPConnectionDelegateProtocol>)theDelegate inputStream:(NSInputStream *)theInStream outputStream:(NSOutputStream *)theOutStream;

-(void)open;
-(void)close;

-(void)setupKeepalive;
-(void)teardownKeepalive;

-(void)enqueueNextSendObject:(NSData *)theData;

@end
