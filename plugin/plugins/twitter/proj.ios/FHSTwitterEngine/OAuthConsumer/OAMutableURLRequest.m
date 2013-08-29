//
//  OAMutableURLRequest.m
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


#import "OAMutableURLRequest.h"
#import "OARequestParameter.h"
#import "OAServiceTicket.h"

@interface OAMutableURLRequest ()
- (void)_generateTimestamp;
- (void)_generateNonce;
- (NSString *)_signatureBaseString;

@property (nonatomic, retain) OAConsumer *consumer;
@property (nonatomic, retain) OAToken *token;
@property (nonatomic, retain) NSString *realm;
@property (nonatomic, retain) id <OASignatureProviding> signatureProvider;
@property (nonatomic, retain) NSMutableDictionary *extraOAuthParameters;

@end

@interface NSURL (OABaseAdditions)
- (NSString *)URLStringWithoutQuery;
@end

@implementation NSURL (OABaseAdditions)

- (NSString *)URLStringWithoutQuery {
    if (self.absoluteString.length == 0) {
        return nil;
    }
    
    NSArray *parts = [self.absoluteString componentsSeparatedByString:@"?"];
    return (parts.count == 0)?nil:[parts objectAtIndex:0];
}

@end

@implementation OAMutableURLRequest

+ (void)fetchDataForRequest:(OAMutableURLRequest *)request withCompletionHandler:(void(^)(OAServiceTicket *, NSData *, NSError *))block {
    [request prepare];
    
    [NSURLConnection sendAsynchronousRequest:request queue:[[[NSOperationQueue alloc]init]autorelease] completionHandler:^(NSURLResponse *response, NSData *data, NSError *error) {
        OAServiceTicket *ticket = [[[OAServiceTicket alloc]initWithRequest:request response:response didSucceed:(error == nil)]autorelease];
        block(ticket, data, error);
    }];
}

+ (OAMutableURLRequest *)requestWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken {
    return [[[[self class]alloc]initWithURL:aUrl consumer:aConsumer token:aToken realm:nil signatureProvider:nil]autorelease];
}

+ (OAMutableURLRequest *)requestWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken realm:(NSString *)aRealm signatureProvider:(id<OASignatureProviding, NSObject>)aProvider {
    return [[[[self class]alloc]initWithURL:aUrl consumer:aConsumer token:aToken realm:aRealm signatureProvider:aProvider]autorelease];
}

- (id)initWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken realm:(NSString *)aRealm signatureProvider:(id<OASignatureProviding, NSObject>)aProvider {
    
    self = [super initWithURL:aUrl cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:25];
    
    if (self) {
        [self setConsumer:aConsumer];
		
		// empty token for Unauthorized Request Token transaction
		if (aToken == nil) {
            [self setToken:[OAToken token]];
		} else {
            [self setToken:aToken];
        }
        
		if (aRealm == nil) {
            [self setRealm:@""];
		} else {
            [self setRealm:aRealm];
        }
		
		// default to HMAC-SHA1
		if (aProvider == nil) {
            [self setSignatureProvider:[OAHMAC_SHA1SignatureProvider OAHMAC_SHA1SignatureProvider]];
		} else {
            [self setSignatureProvider:aProvider];
        }
		
		[self _generateTimestamp];
		[self _generateNonce];
	}
    return self;
}

// Setting a timestamp and nonce to known values. Can be helpful for testing
- (id)initWithURL:(NSURL *)aUrl consumer:(OAConsumer *)aConsumer token:(OAToken *)aToken realm:(NSString *)aRealm signatureProvider:(id<OASignatureProviding, NSObject>)aProvider nonce:(NSString *)aNonce timestamp:(NSString *)aTimestamp {
	
    self = [super initWithURL:aUrl cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:10.0];
    
    if (self) {    
		[self setConsumer:aConsumer];
		
		// empty token for Unauthorized Request Token transaction
		if (aToken == nil) {
            [self setToken:[OAToken token]];
		} else {
            [self setToken:aToken];
        }
        
		if (aRealm == nil) {
            [self setRealm:@""];
		} else {
            [self setRealm:aRealm];
        }
		
		// default to HMAC-SHA1
		if (aProvider == nil) {
            [self setSignatureProvider:[OAHMAC_SHA1SignatureProvider OAHMAC_SHA1SignatureProvider]];
		} else {
            [self setSignatureProvider:aProvider];
        }

        [self setTimestamp:aTimestamp];
        [self setNonce:aNonce];
	}
    return self;
}

- (void)setOAuthParameterName:(NSString*)parameterName withValue:(NSString*)parameterValue {
    
    if (!parameterName && !parameterValue) {
        NSLog(@"%s There was not parameter name nor value specified.", __PRETTY_FUNCTION__);
        return;
    }
    
	if (self.extraOAuthParameters == nil) {
        [self setExtraOAuthParameters:[NSMutableDictionary dictionary]];
	}
	
	[self.extraOAuthParameters setObject:parameterValue forKey:parameterName];
}

- (void)prepare {
    // sign
	// Secrets must be urlencoded before concatenated with '&'
	// TODO: if later RSA-SHA1 support is added then a little code redesign is needed
    self.signature = [self.signatureProvider signClearText:[self _signatureBaseString] withSecret:[NSString stringWithFormat:@"%@&%@", [self.consumer.secret URLEncodedString], [self.token.secret URLEncodedString]]];
    
    // set OAuth headers
	NSString *oauthToken;
    
	if ([self.token.key isEqualToString:@""]) {
		oauthToken = @"oauth_callback=\"oob\", ";
    } else if (self.token.verifier.length == 0) {
		oauthToken = [NSString stringWithFormat:@"oauth_token=\"%@\", ", [self.token.key URLEncodedString]];
	} else {
		oauthToken = [NSString stringWithFormat:@"oauth_token=\"%@\", oauth_verifier=\"%@\", ", [self.token.key URLEncodedString], [self.token.verifier URLEncodedString]];
    }
    
	NSMutableString *extraParameters = [NSMutableString string];
	
	// Adding the optional parameters in sorted order isn't required by the OAuth spec, but it makes it possible to hard-code expected values in the unit tests.
	for (NSString *parameterName in [[self.extraOAuthParameters allKeys]sortedArrayUsingSelector:@selector(compare:)]) {
		[extraParameters appendFormat:@", %@=\"%@\"",[parameterName URLEncodedString],[[self.extraOAuthParameters objectForKey:parameterName]URLEncodedString]];
	}	
    
    NSString *oauthHeader = [NSString stringWithFormat:@"OAuth realm=\"%@\", oauth_consumer_key=\"%@\", %@oauth_signature_method=\"%@\", oauth_signature=\"%@\", oauth_timestamp=\"%@\", oauth_nonce=\"%@\", oauth_version=\"1.0\"%@", [self.realm URLEncodedString], [self.consumer.key URLEncodedString], oauthToken, [[self.signatureProvider name] URLEncodedString], [self.signature URLEncodedString], self.timestamp, self.nonce, extraParameters];
	
    [self setValue:oauthHeader forHTTPHeaderField:@"Authorization"];
}

- (NSArray *)parameters {
    
    NSString *encodedParameters = nil;

    if ([self.HTTPMethod isEqualToString:@"GET"] || [self.HTTPMethod isEqualToString:@"DELETE"]) {
        encodedParameters = self.URL.query;
	} else if ([self.HTTPMethod isEqualToString:@"POST"] || [self.HTTPMethod isEqualToString:@"PUT"]) {
        encodedParameters = [[[NSString alloc]initWithData:self.HTTPBody encoding:NSASCIIStringEncoding]autorelease];
    }

    if (encodedParameters.length == 0) {
        return nil;
    }
    
    NSArray *encodedParameterPairs = [encodedParameters componentsSeparatedByString:@"&"];
    NSMutableArray *requestParameters = [NSMutableArray arrayWithCapacity:16];
    
    for (NSString *encodedPair in encodedParameterPairs) {
        NSArray *encodedPairElements = [encodedPair componentsSeparatedByString:@"="];
        OARequestParameter *parameter = [OARequestParameter requestParameterWithName:[[encodedPairElements objectAtIndex:0] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding] value:[[encodedPairElements objectAtIndex:1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
        [requestParameters addObject:parameter];
    }

    return requestParameters;
}

- (void)setParameters:(NSArray *)parameters {
    NSMutableString *encodedParameterPairs = [NSMutableString stringWithCapacity:256];
    
    int position = 1;
    for (OARequestParameter *requestParameter in parameters) {
        [encodedParameterPairs appendString:[requestParameter URLEncodedNameValuePair]];
        if (position < parameters.count) {
            [encodedParameterPairs appendString:@"&"];
        }
        position++;
    }
    
    if ([self.HTTPMethod isEqualToString:@"GET"] || [self.HTTPMethod isEqualToString:@"DELETE"]) {
        [self setURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@?%@", [self.URL URLStringWithoutQuery], encodedParameterPairs]]];
    } else if ([self.HTTPMethod isEqualToString:@"POST"] || [self.HTTPMethod isEqualToString:@"PUT"]) {
        NSData *postData = [encodedParameterPairs dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:YES];
        [self setHTTPBody:postData];
        [self setValue:[NSString stringWithFormat:@"%d",postData.length] forHTTPHeaderField:@"Content-Length"];
        [self setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    }
}

- (void)_generateTimestamp {
    [self setTimestamp:[NSString stringWithFormat:@"%ld", time(nil)]];
}

- (void)_generateNonce {
    CFUUIDRef theUUID = CFUUIDCreate(nil);
    CFStringRef string = CFUUIDCreateString(nil, theUUID);
    CFRelease(theUUID);
    [self setNonce:[NSString stringWithString:(NSString *)string]];
    CFRelease(string);
}

- (NSString *)_signatureBaseString {
    // OAuth Spec, Section 9.1.1 "Normalize Request Parameters"
    // build a sorted array of both request parameters and OAuth header parameters
    NSArray *parameters = [self parameters];
    
    NSMutableArray *parameterPairs = [NSMutableArray  arrayWithCapacity:(6+parameters.count)]; // 6 being the number of OAuth params in the Signature Base String
    
	[parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_consumer_key" value:self.consumer.key]URLEncodedNameValuePair]];
	[parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_signature_method" value:[self.signatureProvider name]] URLEncodedNameValuePair]];
	[parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_timestamp" value:self.timestamp]URLEncodedNameValuePair]];
	[parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_nonce" value:self.nonce]URLEncodedNameValuePair]];
	[parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_version" value:@"1.0"]URLEncodedNameValuePair]];

    if (self.token.key.length > 0) {
        [parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_token" value:self.token.key]URLEncodedNameValuePair]];
        if (self.token.verifier.length > 0) {
			[parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_verifier" value:self.token.verifier]URLEncodedNameValuePair]];
		}
    } else {
		[parameterPairs addObject:[[OARequestParameter requestParameterWithName:@"oauth_callback" value:@"oob"]URLEncodedNameValuePair]];
	}

    for (OARequestParameter *param in parameters) {
        [parameterPairs addObject:[param URLEncodedNameValuePair]];
    }

    NSArray *sortedPairs = [parameterPairs sortedArrayUsingSelector:@selector(compare:)];
    NSString *normalizedRequestParameters = [sortedPairs componentsJoinedByString:@"&"];
    
    // OAuth Spec, Section 9.1.2 "Concatenate Request Elements"
    NSString *ret = [NSString stringWithFormat:@"%@&%@&%@", self.HTTPMethod, [[self.URL URLStringWithoutQuery]URLEncodedString], [normalizedRequestParameters URLEncodedString]];
	return ret;
}

- (void)dealloc {
    [self setExtraOAuthParameters:nil];
    [self setConsumer:nil];
    [self setToken:nil];
    [self setRealm:nil];
    [self setSignatureProvider:nil];
    [self setTimestamp:nil];
    [self setNonce:nil];
    [self setSignature:nil];
	[super dealloc];
}

@end
