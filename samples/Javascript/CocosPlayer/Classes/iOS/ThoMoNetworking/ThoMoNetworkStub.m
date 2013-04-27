/*
 *  ThoMoNetworkStub.m
 *  ThoMoNetworkingFramework
 *
 *  Created by Thorsten Karrer on 2.7.09.
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

#import "ThoMoNetworkStub.h"
#import <arpa/inet.h>
#import "ThoMoTCPConnection.h"
#import <pthread.h>

NSString *const kThoMoNetworkInfoKeyUserMessage					= @"kThoMoNetworkInfoKeyUserMessage";
NSString *const kThoMoNetworkInfoKeyData						= @"kThoMoNetworkInfoKeyData";
NSString *const kThoMoNetworkInfoKeyRemoteConnectionIdString	= @"kThoMoNetworkInfoKeyRemoteConnectionIdString";
NSString *const kThoMoNetworkInfoKeyLocalNetworkStub			= @"kThoMoNetworkInfoKeyLocalNetworkStub";

NSString *const kThoMoNetworkPrefScopeSpecifierKey				= @"kThoMoNetworkPrefScopeSpecifierKey";

// interface category for main thread relay methods
@interface ThoMoNetworkStub (RelayMethods)
-(void)netServiceProblemRelayMethod:(NSDictionary *)infoDict;
-(void)didReceiveDataRelayMethod:(NSDictionary *)infoDict;
-(void)connectionEstablishedRelayMethod:(NSDictionary *)infoDict;
-(void)connectionLostRelayMethod:(NSDictionary *)infoDict;
-(void)connectionClosedRelayMethod:(NSDictionary *)infoDict;
@end

@interface ThoMoNetworkStub ()

-(void)sendDataWithInfoDict:(NSDictionary *)theInfoDict;

@end




// =====================================================================================================================
#pragma mark -
#pragma mark Public Methods
// ---------------------------------------------------------------------------------------------------------------------

@implementation ThoMoNetworkStub

#pragma mark Housekeeping

-(id)initWithProtocolIdentifier:(NSString *)theProtocolIdentifier;
{
	self = [super init];
	if (self != nil) 
	{
		// check if there is a scope specifier present in the user defaults and add it to the protocolId
		NSString *scopeSpecifier = [[NSUserDefaults standardUserDefaults] stringForKey:kThoMoNetworkPrefScopeSpecifierKey];
		if (scopeSpecifier)
		{
			protocolIdentifier = [[scopeSpecifier stringByAppendingFormat:@"-%@", theProtocolIdentifier] retain];
			NSLog(@"Warning: ThoMo Networking Protocol Prefix in effect! If your app cannot connect to its counterpart that may be the reason.");
		}
		else
		{
			protocolIdentifier = [theProtocolIdentifier copy];
		}

		if ([protocolIdentifier length] > 14)
		{
			// clean up internally
			[NSException raise:@"ThoMoInvalidArgumentException" 
						format:@"The protocol identifier plus the optional scoping prefix (\"%@\") exceed"
								" Bonjour's maximum allowed length of fourteen characters!", protocolIdentifier];
		} 
		
		connections	= [[NSMutableDictionary alloc] init];
	}
	return self;
}

-(id)init;
{
	return [self initWithProtocolIdentifier:@"thoMoNetworkStubDefaultIdentifier"];
}

// since the networkThread retains our object while it executes, this method will be called after the thread is done
- (void) dealloc
{
	[connections release];
	[protocolIdentifier release];
	[networkThread release];
	[super dealloc];
}

// these methods are called on the main thread
#pragma mark Control

-(void) start;
{
	if ([networkThread isExecuting])
	{
		[NSException raise:@"ThoMoStubAlreadyRunningException" 
					format:@"The client stub had already been started before and cannot be started twice."];
	}
	
	// TODO: check if we cannot run a start-stop-start cycle
	NSAssert(networkThread == nil, @"Network thread not released properly");
	
	networkThread = [[NSThread alloc] initWithTarget:self selector:@selector(networkThreadEntry) object:nil];
	[networkThread start];
}

-(void) stop;
{
	[networkThread cancel];
	
	// TODO: check if we can release the networkthread here
}

-(NSArray *)activeConnections;
{
	NSArray *result;
	@synchronized(self)
	{
		result = [[connections allKeys] copy];
	}
	return [result autorelease];
}

-(void)send:(id<NSCoding>)theData toConnection:(NSString *)theConnectionIdString;
{
//   NSData *sendData = [NSKeyedArchiver archivedDataWithRootObject:theData];
    NSString *errorStr;
    NSData *sendData = [NSPropertyListSerialization dataWithPropertyList:theData format:NSPropertyListBinaryFormat_v1_0 options:NULL error:&errorStr];
    
	[self sendByteData:sendData toConnection:theConnectionIdString];
}

-(void)sendByteData:(NSData *)sendData toConnection:(NSString *)theConnectionIdString;
{
	NSDictionary *infoDict = [NSDictionary dictionaryWithObjectsAndKeys:
							  sendData, @"DATA",
							  theConnectionIdString, @"ID",
							  nil];
	
	[self performSelector:@selector(sendDataWithInfoDict:) onThread:networkThread withObject:infoDict waitUntilDone:NO];
}

#pragma mark Send Data Relay

// only call on network thread
-(void)sendDataWithInfoDict:(NSDictionary *)theInfoDict;
{
	NSData *sendData = [theInfoDict objectForKey:@"DATA"];
	NSString *theConnectionIdString = [theInfoDict objectForKey:@"ID"];
	
	ThoMoTCPConnection *connection = nil;
	@synchronized(self)
	{
		connection = [[connections valueForKey:theConnectionIdString] retain];
	}
	
	if (!connection) 
	{
		[NSException raise:@"ThoMoInvalidArgumentException" 
					format:@"No connection found for id %@", theConnectionIdString];
	}
	else
	{		
		[connection enqueueNextSendObject:sendData];
	}
	[connection release];
}


#pragma mark Threading Methods

-(void)networkThreadEntry
{
	#ifdef DEBUG
		#ifdef THOMO_PTHREAD_NAMING_AVAILABLE
			pthread_setname_np("ThoMoNetworking Dispatch Thread");
		#endif
	#endif
	
	NSAutoreleasePool *networkThreadPool = [[NSAutoreleasePool alloc] init];
	
	if([self setup])
	{		
		while (![networkThread isCancelled])
		{
			NSDate *inOneSecond = [[NSDate alloc] initWithTimeIntervalSinceNow:1];
			
			// catch exceptions and propagate to main thread
			@try {
				[[NSRunLoop currentRunLoop]	runMode:NSDefaultRunLoopMode beforeDate:inOneSecond];
			}
			@catch (NSException * e) {
				[e performSelectorOnMainThread:@selector(raise) withObject:nil waitUntilDone:YES];
			}
			
			[inOneSecond release];
		}
		
		[self teardown];
	}
	
	[self performSelectorOnMainThread:@selector(networkStubDidShutDownRelayMethod) withObject:nil waitUntilDone:NO];
	
	[networkThreadPool release];
}

#pragma mark -
#pragma mark Connection Delegate Methods

/// Delegate method that gets called from ThoMoTCPConnections whenever they did receive data.
/**
 Takes the received data and relays it to a method on the main thread.
 This method is typically overridden in the subclasses of ThoMoNetworkStub and then directly called from there.
 
 \param[in]	theData			reference to the received data
 \param[in]	theConnection	reference to the connection that received the data
 */
-(void)didReceiveData:(NSData *)theData onConnection:(ThoMoTCPConnection *)theConnection;
{
	// look up the connection
	NSString *connectionKey = [self keyForConnection:theConnection];
	
	// unarchive the data
	//id receivedData = [NSKeyedUnarchiver unarchiveObjectWithData:theData];
	
    NSString *errorStr;
    NSDictionary *receivedData = [NSPropertyListSerialization propertyListWithData:theData options:NULL format:NULL error:&errorStr];
    
    NSLog(@"DICT: %@", [receivedData description]);
    // package the parameters into an info dict and relay them to the main thread
	NSDictionary *infoDict = [NSDictionary dictionaryWithObjectsAndKeys:	
							  connectionKey,	kThoMoNetworkInfoKeyRemoteConnectionIdString,
							  self,				kThoMoNetworkInfoKeyLocalNetworkStub,
							  receivedData,		kThoMoNetworkInfoKeyData,
							  nil];
	
	[self performSelectorOnMainThread:@selector(didReceiveDataRelayMethod:) withObject:infoDict waitUntilDone:NO];
}

-(void)streamsDidOpenOnConnection:(ThoMoTCPConnection *)theConnection;
{
	// look up the connection
	NSString *connectionKey = [self keyForConnection:theConnection];
	
	// package the parameters into an info dict and relay them to the main thread
	NSDictionary *infoDict = [NSDictionary dictionaryWithObjectsAndKeys:	
							  self,				kThoMoNetworkInfoKeyLocalNetworkStub,
							  connectionKey,	kThoMoNetworkInfoKeyRemoteConnectionIdString,
							  nil];
	
	[self performSelectorOnMainThread:@selector(connectionEstablishedRelayMethod:) withObject:infoDict waitUntilDone:NO];
}

-(void)streamEndEncountered:(NSStream *)theStream onConnection:(ThoMoTCPConnection *)theConnection;
{
	NSString *connectionKey = [self keyForConnection:theConnection];
	
	NSString *userMessage = [NSString stringWithFormat:@"Stream end event encountered on stream to %@! Closing connection.", connectionKey];
	
	[theConnection close];
	
	@synchronized(self)
	{
		[connections removeObjectForKey:connectionKey];
	}
	
	NSDictionary *infoDict = [NSDictionary dictionaryWithObjectsAndKeys:	
							  self,				kThoMoNetworkInfoKeyLocalNetworkStub,
							  connectionKey,	kThoMoNetworkInfoKeyRemoteConnectionIdString,	
							  userMessage,		kThoMoNetworkInfoKeyUserMessage,
							  nil];
	
	[self performSelectorOnMainThread:@selector(connectionClosedRelayMethod:) withObject:infoDict waitUntilDone:NO];
}

-(void)streamErrorEncountered:(NSStream *)theStream onConnection:(ThoMoTCPConnection *)theConnection;
{
	NSString *connectionKey = [self keyForConnection:theConnection];
	
	NSError *theError = [theStream streamError];
	NSString *userMessage = [NSString stringWithFormat:@"Error %i: \"%@\" on stream to %@! Terminating connection.", (int)[theError code], [theError localizedDescription], connectionKey];
	
	[theConnection close];
	
	@synchronized(self)
	{
		[connections removeObjectForKey:connectionKey];
	}
	
	NSDictionary *infoDict = [NSDictionary dictionaryWithObjectsAndKeys:	
							  self,				kThoMoNetworkInfoKeyLocalNetworkStub,
							  connectionKey,	kThoMoNetworkInfoKeyRemoteConnectionIdString,	
							  userMessage,		kThoMoNetworkInfoKeyUserMessage,
							  nil];
	
	[self performSelectorOnMainThread:@selector(connectionLostRelayMethod:) withObject:infoDict waitUntilDone:NO];
}



// =====================================================================================================================
#pragma mark -
#pragma mark Protected Methods
// ---------------------------------------------------------------------------------------------------------------------


-(BOOL)setup
{
	return YES;
}

-(void)teardown
{
	// close all open connections
	@synchronized(self)
	{
		for (ThoMoTCPConnection *connection in [connections allValues]) {
			[connection close];
		}
		
		[connections removeAllObjects];		
	}
}

-(NSString *)keyStringFromAddress:(NSData *)addr;
{
	// get the peer socket address from the NSData object
	// NOTE:	there actually is a struct sockaddr in there, NOT a struct sockaddr_in! 
	//			I heard from beej (<http://www.retran.com/beej/sockaddr_inman.html>) that they share the same 15 first bytes so casting should not be a problem. 
	//			You've been warned, though...
	struct sockaddr_in *peerSocketAddress = (struct sockaddr_in *)[addr bytes];
	
	// convert in_addr to ascii (note: returns a pointer to a statically allocated buffer inside inet_ntoa! calling again will overwrite)
	char *humanReadableAddress	= inet_ntoa(peerSocketAddress->sin_addr);
	NSString *peerAddress		= [NSString stringWithCString:humanReadableAddress encoding:NSUTF8StringEncoding];
	NSString *peerPort			= [NSString stringWithFormat:@"%d", ntohs(peerSocketAddress->sin_port)];
	NSString *peerKey			= [NSString stringWithFormat:@"%@:%@", peerAddress, peerPort];
	
	return peerKey;
}

-(NSString *)keyForConnection:(ThoMoTCPConnection *)theConnection;
{
	NSString	*connectionKey;
	NSArray		*keys;
	@synchronized(self)
	{
		keys = [connections allKeysForObject:theConnection];
		NSAssert([keys count] == 1, @"More than one connection record in dict for a single connection.");
		connectionKey = [[keys objectAtIndex:0] copy];
	}
	
	return [connectionKey autorelease];
}


-(void) openNewConnection:(NSString *)theConnectionKey inputStream:(NSInputStream *)istr outputStream:(NSOutputStream *)ostr;
{
	// create a new ThoMoTCPConnection object and set ourselves as the delegate to forward the incoming data to our own delegate
	ThoMoTCPConnection *newConnection = [[ThoMoTCPConnection alloc] initWithDelegate:self inputStream:istr outputStream:ostr];
	
	// store in our dictionary, open, and release our copy
	@synchronized(self)
	{
		// it should never happen that we overwrite a connection
		NSAssert(![connections valueForKey:theConnectionKey], @"ERROR: Tried to create a connection with an IP and port that we already have a connection for.");
		
		[connections setValue:newConnection forKey:theConnectionKey];
	}
	[newConnection open];
	[newConnection release];
}

@end



#pragma mark -
#pragma mark Main Thread Relay Methods

@implementation ThoMoNetworkStub (RelayMethods)

-(void)networkStubDidShutDownRelayMethod
{
	NSLog(@"%@ :: %@", [self description], NSStringFromSelector(_cmd));
}

-(void)netServiceProblemRelayMethod:(NSDictionary *)infoDict
{
	NSLog(@"%@ :: %@", [self description], NSStringFromSelector(_cmd));
}

-(void)didReceiveDataRelayMethod:(NSDictionary *)infoDict;
{
	NSLog(@"%@ :: %@", [self description], NSStringFromSelector(_cmd));
}

-(void)connectionEstablishedRelayMethod:(NSDictionary *)infoDict;
{
	NSLog(@"%@ :: %@", [self description], NSStringFromSelector(_cmd));
}

-(void)connectionLostRelayMethod:(NSDictionary *)infoDict;
{
	NSLog(@"%@ :: %@", [self description], NSStringFromSelector(_cmd));
}

-(void)connectionClosedRelayMethod:(NSDictionary *)infoDict;
{
	NSLog(@"%@ :: %@", [self description], NSStringFromSelector(_cmd));
}


#pragma mark -
#pragma mark Debugging


@end
