/*
 *  ThoMoTCPConnection.m
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

#import "ThoMoTCPConnection.h"

#define HEADERSIZE 4
#define CHUNKSIZE 1024

@implementation ThoMoTCPConnection

@synthesize delegate;

- (id) init
{
	return [self initWithDelegate:nil inputStream:nil outputStream:nil];
}


-(id)initWithDelegate:(id <ThoMoTCPConnectionDelegateProtocol>)theDelegate inputStream:(NSInputStream *)theInStream outputStream:(NSOutputStream *)theOutStream;
{
	self = [super init];
	if (self != nil) {
				
		if (theDelegate && theInStream && theOutStream)
		{
			inReady				= NO;
			outReady			= NO;
			streamsCanOpen		= YES;
			openCallbackSent	= NO;
			
			dataBuffer						= (uint8_t *)malloc(HEADERSIZE);
			dataBufferCursor				= dataBuffer;
			bytesMissingForNextSubpacket	= HEADERSIZE;
			nextExpectedSubpacket			= kServerStubSubPacketHeader;
			
			bytesRemainingToSend	= 0;
			sendObjectsQueue						= [[NSMutableArray alloc] initWithCapacity:5];
			currentSendObject						= nil;
			
			
			inStream			= [theInStream retain];
			outStream			= [theOutStream retain];
			delegate			= theDelegate; // do not retain the delegate
			
			threadIsPresentInMethod = NO;
		}
		else
		{
			[self release];
			self = nil;
		}
	}
	return self;	
}

- (void) dealloc
{
	[self close];
	
	[inStream release];
	[outStream release];
	
	[sendObjectsQueue release];
	
	free(dataBuffer);
	
	if (sendBuffer)
		free(sendBuffer);
	
	[super dealloc];
}

-(void)open;
{
	NSAssert(streamsCanOpen, @"Tried to re-open a stream that has already been open at some point - not possible.");
	
	[inStream setDelegate:self];
	[inStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	[inStream open];

	[outStream setDelegate:self];
	[outStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	[outStream open];
	
	[self setupKeepalive];
	
	streamsCanOpen = NO;
}

-(void)close;
{	
	[self teardownKeepalive];

	// close should also remove it from the runloop - somehow it does not release the runLoop's reference though
	[inStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	[inStream close];
	inReady = NO;
	
	// close should also remove it from the runloop - somehow it does not release the runLoop's reference though
	[outStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	[outStream close];
	outReady = NO;
}

-(void)setupKeepalive;
{
	keepaliveSendTimer = [[NSTimer scheduledTimerWithTimeInterval:2 target:self selector:@selector(sendKeepalive:) userInfo:nil repeats:YES] retain];
}

-(void)sendKeepalive:(NSTimer *)theTimer;
{
	NSData *nullData = [[NSData dataWithBytes:NULL length:0] retain];
	[self enqueueNextSendObject:nullData];
	[nullData release];
}

-(void)teardownKeepalive;
{
	if (keepaliveSendTimer) {
		[keepaliveSendTimer invalidate];
		[keepaliveSendTimer release];
		keepaliveSendTimer = nil;
	}
}

-(void)processBufferAndPrepNextRead
{	
	switch (nextExpectedSubpacket)
	{
		case kServerStubSubPacketHeader:
			// parse header and update status
			NSAssert(dataBufferCursor == &(dataBuffer[HEADERSIZE]), @"Header expected but wrong number of bytes read into buffer!");
			// ok, because HEADERSIZE == sizeof(bytesMissingForNextSubpacket)
			memcpy(&bytesMissingForNextSubpacket, dataBuffer, HEADERSIZE);
			uint32_t tmp = ntohl(bytesMissingForNextSubpacket);
			bytesMissingForNextSubpacket = tmp;
			
			//if this is just a keepalive packet it only contains of a header and we can expect another header
			if (bytesMissingForNextSubpacket == 0) {
				bytesMissingForNextSubpacket	= HEADERSIZE;
				nextExpectedSubpacket			= kServerStubSubPacketHeader;
			}
			else {
				nextExpectedSubpacket = kServerStubSubPacketData;
			}
				
			break;
			
		case kServerStubSubPacketData:
		{
			// parse data and update status
			NSData *packetData = [[NSData alloc] initWithBytes:dataBuffer length:(dataBufferCursor - dataBuffer)];
			[delegate didReceiveData:packetData onConnection:self];
			[packetData release];
			bytesMissingForNextSubpacket = HEADERSIZE;
			nextExpectedSubpacket = kServerStubSubPacketHeader;
			break;
		}
			
		default:
			NSAssert(NO, @"Packet to process is neither header nor payload");
			break;
	}
	
	// create new receive buffer
	free(dataBuffer);
	dataBuffer = (uint8_t *)malloc(bytesMissingForNextSubpacket);
	
	
	// reset cursor
	dataBufferCursor = dataBuffer;	
}

-(void)dequeueNextSendObject
{
	NSAssert(bytesRemainingToSend == 0, @"Enqueue next send object called although there are still bytes to be sent off");
	
	if (sendBuffer) {
		free(sendBuffer);
		sendBuffer = NULL;
	}
	
	if ([sendObjectsQueue count] > 0)
	{
		currentSendObject = [[sendObjectsQueue lastObject] retain];
		[sendObjectsQueue removeLastObject];
		
		// create new send buffer
		uint32_t objectSize = [currentSendObject length];
		uint32_t packetSize = objectSize + HEADERSIZE;
		sendBuffer = (uint8_t *)malloc(packetSize);
		
		// fill it
		uint32_t objectSize_n = htonl(objectSize);
		memcpy(sendBuffer, &objectSize_n, HEADERSIZE);
		memcpy(sendBuffer + HEADERSIZE, [currentSendObject bytes], objectSize);
		
		// update the cursor and byte counter
		sendBufferCursor = sendBuffer;
		bytesRemainingToSend = packetSize;
		
		// release the sendObject
		[currentSendObject release];
	}
	
	// check if we need to re-enable the stream events because we had nothing to send earlier
	if (outStreamHasSpaceAvailableEventIgnored && bytesRemainingToSend)
	{
		// HACK
		// this is a hack... not very nice :-/
		[self stream:outStream handleEvent:NSStreamEventHasSpaceAvailable];
	}
}

-(void)enqueueNextSendObject:(NSData *)theData;
{
	[sendObjectsQueue insertObject:theData atIndex:0];
	
	// if we are not sending, trigger a dequeue
	if (bytesRemainingToSend == 0)
	{
		NSAssert([sendObjectsQueue count] == 1, @"We are not sending but the objectSendQueue is not empty!");
		[self dequeueNextSendObject];
	}
}


// TODO: READ ME!
// NOTE: This method is NOT safe for reentrancy!
// We have seen in AsyncSocket that a new stream event may be issued during the stream read: and write: calls.
// This, of course, will cause a reentrancy of the same thread into this method which will break things.. badly!
// A solution would be to lock the method conditionally and cache any pending stream events that could not be processed because of the lock.
// For now we only assert that it works. We'll implement the condition if the assertion ever fires... I promise ;)
- (void) stream:(NSStream*)stream handleEvent:(NSStreamEvent)eventCode
{
	NSAssert(!threadIsPresentInMethod, @"We have been caught by the nasty AsyncSocket bug!");
	
	threadIsPresentInMethod = YES;
	
	switch(eventCode) {
		case NSStreamEventOpenCompleted:
		{
			if ([inStream streamStatus] == NSStreamStatusOpen && [outStream streamStatus] == NSStreamStatusOpen && !openCallbackSent)
			{
				[delegate streamsDidOpenOnConnection:self];
				openCallbackSent = YES;
			}
			break;
		}
		case NSStreamEventHasBytesAvailable:
		{
			//BOOL didCompletePacket = NO;
			
			while (/*didCompletePacket &&*/ [inStream hasBytesAvailable]) 
			{
				//didCompletePacket = NO;
				
				// try to read as many bytes as we need for the next subpacket
				NSInteger bytesActuallyRead = [inStream read:dataBufferCursor maxLength:bytesMissingForNextSubpacket];
				dataBufferCursor += bytesActuallyRead;
				
				// if we have enough construct the subpacket and act on it
				if (bytesActuallyRead == bytesMissingForNextSubpacket)
				{
					//didCompletePacket = YES;
					[self processBufferAndPrepNextRead];
				}
				else if (bytesActuallyRead > 0)
				{
					bytesMissingForNextSubpacket -= bytesActuallyRead;
					//didCompletePacket = NO;
				}
				else if ([stream streamStatus] == NSStreamStatusAtEnd)
				{
					// be careful! the delegate might kill us for the bad news...
					[delegate streamEndEncountered:stream onConnection:self];
					break;
				}
				else if ([stream streamStatus] == NSStreamStatusError)
				{
					// be careful! the delegate might kill us for the bad news...
					[delegate streamErrorEncountered:stream onConnection:self];
					break;
				}
				else
				{
					NSAssert(NO, @"Could not read bytes from network but stream reports no errors");
					break;
				}
				
			}
			
			
			break;
		}
		case NSStreamEventHasSpaceAvailable:
		{
			if (bytesRemainingToSend == 0)
			{
				outStreamHasSpaceAvailableEventIgnored = YES;
			}
			else
			{
				// out stream
				outStreamHasSpaceAvailableEventIgnored = NO;
				
				uint32_t	bytesToSend = ((bytesRemainingToSend >= CHUNKSIZE) ? CHUNKSIZE : bytesRemainingToSend);
				uint32_t	bytesActuallySent = [outStream write:sendBufferCursor maxLength:bytesToSend];
				
				bytesRemainingToSend -= bytesActuallySent;
				
				if (bytesRemainingToSend == 0)
				{
					// packet has been sent, prepare next
					[self dequeueNextSendObject];
				}
				else if (bytesActuallySent > 0)
				{
					// we need to send the rest later
					sendBufferCursor += bytesActuallySent;
				}
				else if ([stream streamStatus] == NSStreamStatusAtEnd)
				{
					// be careful! the delegate might kill us for the bad news...
					[delegate streamEndEncountered:stream onConnection:self];
				}
				else if ([stream streamStatus] == NSStreamStatusError || bytesActuallySent == -1)
				{
					// be careful! the delegate might kill us for the bad news...
					[delegate streamErrorEncountered:stream onConnection:self];
				}
				else
				{
					NSAssert(NO, @"Could not write bytes to network but stream reports no errors");
				}
			}
			
			break;
		}
		case NSStreamEventEndEncountered:
		{			
			// be careful! the delegate might kill us for the bad news...
			[delegate streamEndEncountered:stream onConnection:self];
			break;
		}
		case NSStreamEventErrorOccurred:
		{
			// be careful! the delegate might kill us for the bad news...
			[delegate streamErrorEncountered:stream onConnection:self];
            break;
		}
        default:
            break;
	}
	
	threadIsPresentInMethod = NO;
}

@end
