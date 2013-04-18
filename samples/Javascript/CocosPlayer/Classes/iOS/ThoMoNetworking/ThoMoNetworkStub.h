/*
 *  ThoMoNetworkStub.h
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

#import "ThoMoTCPConnectionDelegateProtocol.h"


/// Mixin class that encapsulates the network worker thread and the handling of ThoMoTCPConnections.
/**
	You should never instantiate a ThoMoNetworkStub directly. Instead, you should use its subclasses ThoMoServerStub and ThoMoClientStub.
	Note: the implementation of this class is Bonjour-agnostic and should remain so.
 */

@interface ThoMoNetworkStub : NSObject <ThoMoTCPConnectionDelegateProtocol, NSNetServiceDelegate>
{
	NSMutableDictionary	*connections;
	NSString			*protocolIdentifier;
	NSThread			*networkThread;
}

-(id)initWithProtocolIdentifier:(NSString *)theProtocolIdentifier;

-(void) start;
-(void) stop;

-(NSArray *)activeConnections;

-(void)send:(id<NSCoding>)theData toConnection:(NSString *)theConnectionIdString;
-(void)sendByteData:(NSData *)theData toConnection:(NSString *)theConnectionIdString;






// protected
-(BOOL)setup;
-(void)teardown;
-(NSString *)keyStringFromAddress:(NSData *)addr;
/// Returns the key for theConnection from the connections dictionary.
-(NSString *)keyForConnection:(ThoMoTCPConnection *)theConnection;
-(void) openNewConnection:(NSString *)theConnectionKey inputStream:(NSInputStream *)istr outputStream:(NSOutputStream *)ostr;



@end

NSString *const kThoMoNetworkInfoKeyUserMessage;
NSString *const kThoMoNetworkInfoKeyData;
NSString *const kThoMoNetworkInfoKeyRemoteConnectionIdString;
NSString *const kThoMoNetworkInfoKeyLocalNetworkStub;
