/*
 *  ThoMoClientStub.m
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

#import "ThoMoClientStub_private.h"
#import "ThoMoTCPConnection.h"

// =====================================================================================================================
#pragma mark -
#pragma mark defines
// ---------------------------------------------------------------------------------------------------------------------

#define kThoMoNetworkInfoKeyServer kThoMoNetworkInfoKeyRemoteConnectionIdString
#define kThoMoNetworkInfoKeyClient kThoMoNetworkInfoKeyLocalNetworkStub

// =====================================================================================================================





// =====================================================================================================================
#pragma mark -
#pragma mark Class Extensions
// ---------------------------------------------------------------------------------------------------------------------

@interface ThoMoClientStub()

-(void)netServiceProblemRelayMethod:(NSDictionary *)infoDict;
-(void)didReceiveDataRelayMethod:(NSDictionary *)infoDict;

-(void)resolveNetService:(NSNetService *)theNetService;

@end
// =====================================================================================================================





// =====================================================================================================================
#pragma mark -
#pragma mark ThoMoClientStub implementation
// ---------------------------------------------------------------------------------------------------------------------

@implementation ThoMoClientStub


#pragma mark -
#pragma mark Properties

@synthesize delegate;
@synthesize offeredNetServices;
@synthesize connectedNetServices;


#pragma mark -
#pragma mark Housekeeping

-(id)initWithProtocolIdentifier:(NSString *)theProtocolIdentifier;
{
	self = [super initWithProtocolIdentifier:theProtocolIdentifier];
	if (self != nil) {
		// add inits here
		self.offeredNetServices		= [[NSMutableArray alloc] init];
		self.connectedNetServices	= [[NSMutableDictionary alloc] init];
	}
	return self;
}


- (void) dealloc
{
	[self stop];
	self.offeredNetServices		= nil;
	self.connectedNetServices	= nil;
	[super dealloc];
}



#pragma mark -
#pragma mark Control

-(NSArray *)connectedServers;
{
	return [super activeConnections];
}

-(void)send:(id<NSCoding>)anObject toServer:(NSString *)theServerIdString;
{
	[super send:anObject toConnection:theServerIdString];
}

-(void)sendToAllServers:(id<NSCoding>)anObject;
{
	for (NSString *aServer in [self connectedServers])
	{
		[self send:anObject toServer:aServer];
	}
}

// DEPRECATED
-(void)sendData:(id<NSCoding>)theData toServer:(NSString *)theServerIdString;
{
	[self send:theData toServer:theServerIdString];
}

// PRIVATE API
-(void)sendBytes:(NSData *)theBytes toServer:(NSString *)theServerIdString;
{
	[super sendByteData:theBytes toConnection:theServerIdString];
}



#pragma mark -
#pragma mark Private Methods

// override
-(BOOL)setup;
{
	if (![super setup])
		return NO;
	
	//start NSNetServiceBrowser
	browser = [[NSNetServiceBrowser alloc] init]; 
	[browser setDelegate:self];
	[browser searchForServicesOfType:[NSString stringWithFormat:@"_%@._tcp.", protocolIdentifier] inDomain:@"local"]; 
	
	return YES;
}


// override
-(void)teardown;
{
	[browser stop]; 
	[browser release]; 
	browser = nil;
	
	[super teardown];
}


// get a key string ("ip_address:port") for a resolved service
-(NSString *)keyStringFromResolvedService:(NSNetService *)theService;
{
	NSData *addr = [[theService addresses] objectAtIndex:0];
	
	NSMutableString *peerKey = [[[self keyStringFromAddress:addr] mutableCopy] autorelease];
	
	return peerKey;
}

#pragma mark -
#pragma mark Delegate Methods

#pragma mark NSNetServiceBrowserDelegate

// notification when service was found
- (void) netServiceBrowser:(NSNetServiceBrowser*)browser didFindService:(NSNetService*)service moreComing:(BOOL)moreComing
{
	NSLog(@"NetService %@ offered by %@", [service type], [service name]);
	
	//need to hold a reference to the service
	[self.offeredNetServices addObject:service];
	
	//resolve net service
	[service retain]; // retain - will be released after the resolve comes back!
	[service setDelegate:self];
	[service resolveWithTimeout:0.0];
}


//notification when service was removed
- (void) netServiceBrowser:(NSNetServiceBrowser*)browser didRemoveService:(NSNetService*)service moreComing:(BOOL)moreComing
{
	NSLog(@"NetService %@ no longer offered by %@", [service type], [service name]);
	
	// remove the service from the list
	[self.offeredNetServices removeObject:service];	
}


#pragma mark NSNetServiceDelegate

//notification when netservice was resolved
- (void)netServiceDidResolveAddress:(NSNetService *)sender
{
	NSLog(@"Resolved Server Address %@", [sender hostName]);

	// get a key string ("ip_address:port") for the service
	NSString *key = [self keyStringFromResolvedService:sender];
	NSAssert(key != nil, @"Could not create key string for resolved service");
	
	// Tho 04.01.10: changed. Connections are only established if the service is not present in the connectedNetServices dict.
	// This dict should now always contain exactly those services for which we have an open connection
	
	if (![self.connectedNetServices objectForKey:key])
	{
		
		//connect to server and cache the NetService if the NetService can build us the I/O-Streams
		NSInputStream	*istream;
		NSOutputStream	*ostream;

		// -[NSNetService getInputStream:outputStream:] currently returns the stream 
		// with a reference that we have to release (something that's counter to the 
		// standard Cocoa memory management rules <rdar://problem/6868813>).
		BOOL gotStreams = [sender getInputStream:&istream outputStream:&ostream];
		
		if (gotStreams)
		{
			[self openNewConnection:key inputStream:istream outputStream:ostream];
			[istream release];
			[ostream release];
						
			[self.connectedNetServices setObject:sender forKey:key];
		}
		
	}
	
	// we're done here, stop resolving
	[sender stop];
	[sender release];
}


- (void)netService:(NSNetService *)sender didNotResolve:(NSDictionary *)errorDict 
{
	NSString *errorString;
	switch ([(NSNumber *)[errorDict objectForKey:NSNetServicesErrorCode] intValue])
	{
		case NSNetServicesBadArgumentError:
			errorString = @"NSNetServicesBadArgumentError";
			break;
		case NSNetServicesCancelledError:
			errorString = @"NSNetServicesCancelledError";
			break;
		case NSNetServicesCollisionError:
			errorString = @"NSNetServicesCollisionError";
			break;
		case NSNetServicesInvalidError:
			errorString = @"NSNetServicesInvalidError";
			break;
		case NSNetServicesNotFoundError:
			errorString = @"NSNetServicesNotFoundError";
			break;
		case NSNetServicesTimeoutError:
			errorString = @"NSNetServicesTimeoutError";
			break;
		case NSNetServicesUnknownError:
			errorString = @"NSNetServicesUnknownError";
			break;
		default:
			errorString = @"Unknown. Possibly an error on the Mach layer.";
			break;
	}
	
	NSLog(@"Could not resolve service %@ because of error %@", sender, errorString);
	
	// stop the resolve
	[sender stop];
	[sender release];
}



#pragma mark Connection Delegate Methods

// override
-(void)streamsDidOpenOnConnection:(ThoMoTCPConnection *)theConnection;
{
	// let the super class issue the user notifications on the main thread
	[super streamsDidOpenOnConnection:theConnection];	
}


// override
-(void)streamEndEncountered:(NSStream *)theStream onConnection:(ThoMoTCPConnection *)theConnection;
{
	NSString *connectionKey = [self keyForConnection:theConnection];
	
	// this closes the connection, removes it from the connections array, and schedules the connectionLostRelayMethod selector on the main run loop
	[super streamEndEncountered:theStream onConnection:theConnection];
	
	// remove the connection's service from the connectedNetServices dict (it may still be contained in the offered array)
	NSNetService *connectionNetService = [[self.connectedNetServices objectForKey:connectionKey] retain]; // retain - will be released after the resolve comes back!
	[self.connectedNetServices removeObjectForKey:connectionKey];
	
	// try to re-resolve the netService if it is still offered by Bonjour
	if ([offeredNetServices containsObject:connectionNetService])
	{
		[self performSelector:@selector(resolveNetService:) withObject:connectionNetService afterDelay:1];
	}	
}


// override
-(void)streamErrorEncountered:(NSStream *)theStream onConnection:(ThoMoTCPConnection *)theConnection;
{
	NSString *connectionKey = [self keyForConnection:theConnection];
	
	// this closes the connection, removes it from the connections array, and schedules the connectionLostRelayMethod selector on the main run loop
	[super streamErrorEncountered:theStream onConnection:theConnection];
	
	// remove the connection's service from the connectedNetServices dict (it may still be contained in the offered array)
	NSNetService *connectionNetService = [[self.connectedNetServices objectForKey:connectionKey] retain]; // retain - will be released after the resolve comes back!
	[self.connectedNetServices removeObjectForKey:connectionKey];
	
	// try to re-resolve the netService if it is still offered by Bonjour
	if ([offeredNetServices containsObject:connectionNetService])
	{
		[self performSelector:@selector(resolveNetService:) withObject:connectionNetService afterDelay:1];
	}
}

#pragma mark -
#pragma mark Hacking Relays
-(void)resolveNetService:(NSNetService *)theNetService;
{
	[theNetService resolveWithTimeout:5.0];	
}


#pragma mark -
#pragma mark Main Thread Relay Methods

// override
-(void)netWorkStubDidShutDownRelayMethod
{
	if ([delegate respondsToSelector:@selector(clientDidShutDown:)])
		[delegate clientDidShutDown:self];	
}

// override
-(void)netServiceProblemRelayMethod:(NSDictionary *)infoDict
{
	if ([delegate respondsToSelector:@selector(netServiceProblemEncountered:onClient:)])
		[delegate netServiceProblemEncountered:[infoDict objectForKey:@"kThoMoTCPInfoKeyUserMessage"] onClient:self];
}

// required
// override
-(void)didReceiveDataRelayMethod:(NSDictionary *)infoDict;
{
	[delegate client:[infoDict objectForKey:kThoMoNetworkInfoKeyClient] 
	  didReceiveData:[infoDict objectForKey:kThoMoNetworkInfoKeyData] 
		  fromServer:[infoDict objectForKey:kThoMoNetworkInfoKeyServer]];
}

// override
-(void)connectionEstablishedRelayMethod:(NSDictionary *)infoDict;
{
	if ([delegate respondsToSelector:@selector(client:didConnectToServer:)])
		[delegate client:[infoDict objectForKey:kThoMoNetworkInfoKeyClient] 
	  didConnectToServer:[infoDict objectForKey:kThoMoNetworkInfoKeyServer]];
}

// override
-(void)connectionLostRelayMethod:(NSDictionary *)infoDict;
{
	if ([delegate respondsToSelector:@selector(client:didDisconnectFromServer:errorMessage:)])
		[delegate client:[infoDict objectForKey:kThoMoNetworkInfoKeyClient] 
 didDisconnectFromServer:[infoDict objectForKey:kThoMoNetworkInfoKeyServer]
			errorMessage:[infoDict objectForKey:kThoMoNetworkInfoKeyUserMessage]];
}

// override
-(void)connectionClosedRelayMethod:(NSDictionary *)infoDict;
{
	if ([delegate respondsToSelector:@selector(client:didDisconnectFromServer:errorMessage:)])
		[delegate client:[infoDict objectForKey:kThoMoNetworkInfoKeyClient] 
 didDisconnectFromServer:[infoDict objectForKey:kThoMoNetworkInfoKeyServer]
			errorMessage:[infoDict objectForKey:kThoMoNetworkInfoKeyUserMessage]];
}




@end
