/*
 *  ThoMoServerStub.m
 *  ThoMoNetworkingFramework
 *
 *  Created by Thorsten Karrer on 29.6.09.
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


#import "ThoMoServerStub_private.h"
#import <sys/socket.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import "ThoMoTCPConnection.h"

#ifdef THOMO_NEEDS_NETWORKING_INCLUDES
#import <unistd.h>
#import <CFNetwork/CFNetwork.h>
#endif

#define kThoMoNetworkInfoKeyServer kThoMoNetworkInfoKeyLocalNetworkStub
#define kThoMoNetworkInfoKeyClient kThoMoNetworkInfoKeyRemoteConnectionIdString

#define NO_INFO_RETAIN_CALLBACK NULL
#define NO_INFO_RELEASE_CALLBACK NULL
#define NO_INFO_COPY_DESCRIPTION_CALLBACK NULL
#define APPLE_DEFINED_ZERO 0
#define SOME_FREE_PORT 0


// =====================================================================================================================

#pragma mark -
#pragma mark Private Interfaces
#pragma mark -

// interface extension for 'private' properties
@interface ThoMoServerStub() 
@property (nonatomic, retain)	NSNetService	*netService;
@property (assign)				uint16_t		listenPort;
@end

// interface category for private methods
@interface ThoMoServerStub(Private)
-(void) handleNewConnectionFromAddress:(NSData *)addr inputStream:(NSInputStream *)istr outputStream:(NSOutputStream *)ostr;
@end

// interface category for main thread relay methods
@interface ThoMoServerStub(RelayMethods)
-(void)netServiceProblemRelayMethod:(NSDictionary *)infoDict;
-(void)didReceiveDataRelayMethod:(NSDictionary *)infoDict;
-(void)clientDidConnectToServerRelayMethod:(NSDictionary *)infoDict;
-(void)clientDidDisconnectFromServerRelayMethod:(NSDictionary *)infoDict;
@end

// =====================================================================================================================





// =====================================================================================================================

#pragma mark -
#pragma mark ServerStub
#pragma mark -

@implementation ThoMoServerStub

#pragma mark Properties

@synthesize delegate;


#pragma mark Housekeeping

-(id)initWithProtocolIdentifier:(NSString *)theProtocolIdentifier andPort:(uint16_t)thePort;
{
	self = [super initWithProtocolIdentifier:theProtocolIdentifier];
	if (self != nil) {
		// add inits here
		self.listenPort = thePort;
	}
	return self;
}


-(id)initWithProtocolIdentifier:(NSString *)theProtocolIdentifier;
{
	self = [self initWithProtocolIdentifier:theProtocolIdentifier andPort:SOME_FREE_PORT];
	return self;
}



#pragma mark Control

-(NSArray *)connectedClients;
{
	return [super activeConnections];
}

-(void)send:(id<NSCoding>)anObject toClient:(NSString *)theClientIdString;
{
	[super send:anObject toConnection:theClientIdString];
}

-(void)sendToAllClients:(id<NSCoding>)theData;
{
	for (NSString *aClientId in [self connectedClients])
	{
		// TODO: this might raise an exception - we should take care to catch and probably re-raise to have the data be sent to at least the rest of the connections
		[self send:theData toClient:aClientId];
	}
}

-(void)sendData:(id<NSCoding>)theData toClient:(NSString *)theClientIdString;
{
	[self send:theData toClient:theClientIdString];
}

-(void)sendBytes:(NSData *)theBytes toClient:(NSString *)theClientIdString;
{
	[super sendByteData:theBytes toConnection:theClientIdString];
}




// ---------------------------------------------------------------------------------------------------------------------
#pragma mark -
#pragma mark Private
// ---------------------------------------------------------------------------------------------------------------------

#pragma mark Properties

@synthesize netService;
@synthesize listenPort;


#pragma mark Callbacks

// This function is called by CFSocket when a new connection comes in at our listening socket.
static void ServerStubAcceptCallback(CFSocketRef listenSocket, CFSocketCallBackType callbackType, CFDataRef address, const void *pChildSocketNativeHandle, void *info)
{	
	// check if this is the right callback
	if (callbackType == kCFSocketAcceptCallBack) {
		
		// we have packaged up the server object in the info pointer
		ThoMoServerStub *server = (ThoMoServerStub *)info;
		
		// get the BSD child socket for the new connection
		CFSocketNativeHandle childSocketNativeHandle = *(CFSocketNativeHandle *)pChildSocketNativeHandle;
		
		// get the socket address of the peer that connected on our listening socket using the peer's name
		uint8_t		peerName[SOCK_MAXADDRLEN];
		socklen_t	namelength = sizeof(peerName);		
		NSData		*peerSocketAddress = nil;
		if (0 == getpeername(childSocketNativeHandle, (struct sockaddr *)peerName, &namelength))
			peerSocketAddress = [NSData dataWithBytes:peerName length:namelength];
		
		// create a pair of input and output streams on the child socket
		CFReadStreamRef		readStream	= NULL;
		CFWriteStreamRef	writeStream	= NULL;
		CFStreamCreatePairWithSocket(kCFAllocatorDefault, childSocketNativeHandle, &readStream, &writeStream);
		
		// set the stream properties to close the socket when we're done with the streams
		// announce the streams and peer address to the server object (remember, this is just a C callback)
		if (readStream && writeStream)
		{
			CFReadStreamSetProperty(readStream, kCFStreamPropertyShouldCloseNativeSocket, kCFBooleanTrue);
			CFWriteStreamSetProperty(writeStream, kCFStreamPropertyShouldCloseNativeSocket, kCFBooleanTrue);
			[server handleNewConnectionFromAddress:peerSocketAddress inputStream:(NSInputStream *)readStream outputStream:(NSOutputStream *)writeStream];
		}
		else
		{
			// on any failure, need to destroy the CFSocketNativeHandle 
            // since we are not going to use it any more
			close(childSocketNativeHandle);
		}
		
		// clean up
		if (readStream)		CFRelease(readStream);
		if (writeStream)	CFRelease(writeStream);
	}
}


#pragma mark Methods

-(void) handleNewConnectionFromAddress:(NSData *)addr inputStream:(NSInputStream *)istr outputStream:(NSOutputStream *)ostr;
{
	// first convert addr to a key string of format "IP-Address:Port"
	// the whole retain thing is because of all the threads bouncing around
	NSString *connectionKey = [[[self keyStringFromAddress:addr] retain] autorelease];
	
	// now let the superclass create, open, and register a new ThoMoTCPConnection object
	[super openNewConnection:connectionKey inputStream:istr outputStream:ostr];	
}


-(BOOL)setup;
{
	if (![super setup])
		return NO;
	
	// ----------- SOCKET STUFF -----------
	
	// create socket context. we pass the server object as the info pointer to access it later from the callbacks
	CFSocketContext socketContext = {APPLE_DEFINED_ZERO, self, NO_INFO_RETAIN_CALLBACK, NO_INFO_RELEASE_CALLBACK, NO_INFO_COPY_DESCRIPTION_CALLBACK};
	
	// create the socket we will use to listen for incoming connections. Here, we can directly install an auto-accepting callback on the socket - handy!
	listenSocket = CFSocketCreate(kCFAllocatorDefault, PF_INET, SOCK_STREAM, IPPROTO_TCP, kCFSocketAcceptCallBack, (CFSocketCallBack)&ServerStubAcceptCallback, &socketContext);
	if (NULL == listenSocket)
		//TODO: raise exception etc...
		return NO;
	
	// set socket options to reuse socket if the connection breaks
	int yes = 1;
	setsockopt(CFSocketGetNative(listenSocket), SOL_SOCKET, SO_REUSEADDR, (void *)&yes, sizeof(yes));
	
	// fill in the address structure we will use to bind the socket (let the kernel choose the port automatically)
	struct sockaddr_in listenSocketAddress;
	memset(&listenSocketAddress, 0, sizeof(listenSocketAddress));
	listenSocketAddress.sin_len			= sizeof(listenSocketAddress);
	listenSocketAddress.sin_family		= AF_INET;
	listenSocketAddress.sin_port		= htons(self.listenPort);	// 0 means some free port
	listenSocketAddress.sin_addr.s_addr	= htonl(INADDR_ANY);		// our own address
	NSData *listenSocketAddressData		= [NSData dataWithBytes:&listenSocketAddress length:sizeof(listenSocketAddress)];
	
	// bind & listen (in cocoa this is done via the CFSocketSetAddress call)
	if (kCFSocketSuccess != CFSocketSetAddress(listenSocket, (CFDataRef)listenSocketAddressData))
	{
		if (listenSocket) CFRelease(listenSocket);
		listenSocket = NULL;
		//TODO: raise exception etc...
		return NO;
	}
	
	// get the port number the kernel chose for us (we need it for bonjour)
	listenSocketAddressData = [(NSData *)CFSocketCopyAddress(listenSocket) autorelease];
	memcpy(&listenSocketAddress, [listenSocketAddressData bytes], [listenSocketAddressData length]);
		
	self.listenPort = ntohs(listenSocketAddress.sin_port);
	
	// create a RunLoopSource from the socket
	CFRunLoopRef		runLoop				= CFRunLoopGetCurrent();
	CFRunLoopSourceRef	listenSocketSource	= CFSocketCreateRunLoopSource(kCFAllocatorDefault, listenSocket, 0);
	
	// add it to the runloop
	CFRunLoopAddSource(runLoop, listenSocketSource, kCFRunLoopCommonModes);
	CFRelease(listenSocketSource);
	
	
	// ----------- BONJOUR STUFF -----------
	
	// use default name and local domain for our bonjour service
	NSString *domain	= @"local.";
	NSString *name		= @"";
	
	// The Bonjour application protocol, which must:
	// 1) be no longer than 14 characters
	// 2) contain only lower-case letters, digits, and hyphens
	// 3) begin and end with lower-case letter or digit
	// It should also be descriptive and human-readable
	// See the following for more information:
	// http://developer.apple.com/networking/bonjour/faq.html
	NSString *protocol	= [NSString stringWithFormat:@"_%@._tcp.", protocolIdentifier];
	
	// create our service object which we want to publish
	self.netService = [[[NSNetService alloc] initWithDomain:domain type:protocol name:name port:self.listenPort] autorelease];
	if(nil == self.netService) {
		if (listenSocket) CFRelease(listenSocket);
		listenSocket = NULL;
		//TODO: raise exception etc...
		return NO;
	}
	
	// register ourselves as delegate so we know if the publishing did work
	[self.netService setDelegate:self];
	
	// publish the service
	[self.netService scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
	[self.netService publish];
	
	return YES;
}


-(void)teardown
{
	// disable our bonjour service
	if (self.netService) {
		[self.netService stop];
		[self.netService removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
	}
	
	self.netService = nil;
	
	// invalidate the socket (also removes it from the run loop and releases the socket context structure)
	if (listenSocket) {
		CFSocketInvalidate(listenSocket);
	}
	
	// release the socket
	if (listenSocket) {
		CFRelease(listenSocket);
		listenSocket = NULL;
	}
	
	[super teardown];
}



// ---------------------------------------------------------------------------------------------------------------------
#pragma mark -
#pragma mark Delegate Methods
// ---------------------------------------------------------------------------------------------------------------------

#pragma mark Bonjour

- (void)netServiceWillPublish:(NSNetService *)sender;
{
	NSLog(@"Netservice is about to be published.");
}


- (void)netService:(NSNetService *)sender didNotPublish:(NSDictionary *)errorDict;
{
	if([sender isEqual:netService])
	{
		NSString *userMessage = [NSString stringWithFormat:@"Our Netservice did not publish. Error %@", [errorDict objectForKey:NSNetServicesErrorCode]];
		
		NSDictionary *infoDict = [NSDictionary dictionaryWithObjectsAndKeys:
								  self,			kThoMoNetworkInfoKeyServer,
								  userMessage,	kThoMoNetworkInfoKeyUserMessage,
								  nil];
		
		[self performSelectorOnMainThread:@selector(netServiceProblemRelayMethod:) withObject:infoDict waitUntilDone:NO];
	}
}


- (void)netServiceDidPublish:(NSNetService *)sender;
{
	NSLog(@"Netservice has been published.");
}


- (void)netServiceDidStop:(NSNetService *)sender;
{
	if([sender isEqual:netService])
	{
		NSString *userMessage = [NSString stringWithFormat:@"Our Netservice did stop!"];
		
		NSDictionary *infoDict = [NSDictionary dictionaryWithObjectsAndKeys:
								  self,			kThoMoNetworkInfoKeyServer,
								  userMessage,	kThoMoNetworkInfoKeyUserMessage,
								  nil];
		
		[self performSelectorOnMainThread:@selector(netServiceProblemRelayMethod:) withObject:infoDict waitUntilDone:NO];
	}
}



// ---------------------------------------------------------------------------------------------------------------------
#pragma mark -
#pragma mark Main Thread Relay Methods
// ---------------------------------------------------------------------------------------------------------------------

-(void)networkStubDidShutDownRelayMethod
{
	if ([delegate respondsToSelector:@selector(serverDidShutDown:)])
		[delegate serverDidShutDown:self];
}


-(void)netServiceProblemRelayMethod:(NSDictionary *)infoDict
{
	if ([delegate respondsToSelector:@selector(netServiceProblemEncountered:onServer:)])
		[delegate netServiceProblemEncountered:[infoDict objectForKey:kThoMoNetworkInfoKeyUserMessage] onServer:self];
}


// required
-(void)didReceiveDataRelayMethod:(NSDictionary *)infoDict;
{
	[delegate server:[infoDict objectForKey:kThoMoNetworkInfoKeyServer] 
	  didReceiveData:[infoDict objectForKey:kThoMoNetworkInfoKeyData] 
		  fromClient:[infoDict objectForKey:kThoMoNetworkInfoKeyClient]];
}


-(void)connectionEstablishedRelayMethod:(NSDictionary *)infoDict;
{
	if ([delegate respondsToSelector:@selector(server:acceptedConnectionFromClient:)])
		[delegate server:[infoDict objectForKey:kThoMoNetworkInfoKeyServer] acceptedConnectionFromClient:[infoDict objectForKey:kThoMoNetworkInfoKeyClient]];
}


-(void)connectionLostRelayMethod:(NSDictionary *)infoDict;
{
	if ([delegate respondsToSelector:@selector(server:lostConnectionToClient:errorMessage:)])
		[delegate server:[infoDict objectForKey:kThoMoNetworkInfoKeyServer]
  lostConnectionToClient:[infoDict objectForKey:kThoMoNetworkInfoKeyClient]
			errorMessage:[infoDict objectForKey:kThoMoNetworkInfoKeyUserMessage]];
}


-(void)connectionClosedRelayMethod:(NSDictionary *)infoDict;
{
	if ([delegate respondsToSelector:@selector(server:lostConnectionToClient:errorMessage:)])
		[delegate server:[infoDict objectForKey:kThoMoNetworkInfoKeyServer]
  lostConnectionToClient:[infoDict objectForKey:kThoMoNetworkInfoKeyClient]
			errorMessage:[infoDict objectForKey:kThoMoNetworkInfoKeyUserMessage]];
}


// ---------------------------------------------------------------------------------------------------------------------
#pragma mark -
#pragma mark Debugging
// ---------------------------------------------------------------------------------------------------------------------

// empty

@end
