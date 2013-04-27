/*
 *  ThoMoServerStub.h
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

#import "ThoMoServerDelegateProtocol.h"
#import "ThoMoNetworkStub.h"

@interface ThoMoServerStub : ThoMoNetworkStub {
	
	id<ThoMoServerDelegateProtocol> delegate; 
	
	uint16_t			listenPort;
	CFSocketRef			listenSocket;
	NSNetService		*netService;
	
}

@property (assign) id<ThoMoServerDelegateProtocol> delegate;

-(NSArray *)connectedClients;

-(void)sendData:(id<NSCoding>)theData toClient:(NSString *)theClientIdString DEPRECATED_ATTRIBUTE;
-(void)sendBytes:(NSData *)theBytes toClient:(NSString *)theClientIdString;

-(void)send:(id<NSCoding>)anObject toClient:(NSString *)theClientIdString;
-(void)sendToAllClients:(id<NSCoding>)theData;

@end
