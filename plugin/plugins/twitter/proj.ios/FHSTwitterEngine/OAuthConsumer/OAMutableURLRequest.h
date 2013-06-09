//
//  OAMutableURLRequest.h
//  OAuthConsumer
//
//  Created by Jon Crosby on 10/19/07.
//  Copyright 2007 Kaboomerang LLC. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.


#import <Foundation/Foundation.h>
#import "OAConsumer.h"
#import "OAToken.h"
#import "OAHMAC_SHA1SignatureProvider.h"

@class OAServiceTicket;

@interface OAMutableURLRequest : NSMutableURLRequest

@property (nonatomic, assign) NSString *signature;
@property (nonatomic, assign) NSString *nonce;
@property (nonatomic, assign) NSString *timestamp;

+ (void)fetchDataForRequest:(OAMutableURLRequest *)request withCompletionHandler:(void(^)(OAServiceTicket *, NSData *, NSError *))block;

+ (OAMutableURLRequest *)requestWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken realm:(NSString *)aRealm signatureProvider:(id<OASignatureProviding, NSObject>)aProvider;

+ (OAMutableURLRequest *)requestWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken;

- (id)initWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken realm:(NSString *)aRealm signatureProvider:(id<OASignatureProviding, NSObject>)aProvider;

- (id)initWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken realm:(NSString *)aRealm signatureProvider:(id<OASignatureProviding, NSObject>)aProvider nonce:(NSString *)aNonce timestamp:(NSString *)aTimestamp;

- (void)prepare;
- (void)setOAuthParameterName:(NSString*)parameterName withValue:(NSString*)parameterValue;
- (NSArray *)parameters;
- (void)setParameters:(NSArray *)parameters;

@end
