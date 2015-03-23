/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "HttpAsynConnection.h"

@interface HttpAsynConnection ()

@property (readwrite) NSString *statusString;

@end

@implementation HttpAsynConnection

@synthesize srcURL;
@synthesize sslFile;
@synthesize responseHeader;
@synthesize responseData;
@synthesize getDataTime;
@synthesize responseCode;
@synthesize statusString;
@synthesize responseError;
@synthesize connError;
@synthesize conn;
@synthesize finish;
@synthesize runLoop;

- (void)dealloc
{
    [srcURL release];
    [sslFile release];
    [responseHeader release];
    [responseData release];
    [statusString release];
    [responseError release];
    [conn release];
    [runLoop release];
    
    [super dealloc];
}

- (void) startRequest:(NSURLRequest *)request
{
    NSLog(@"Starting to load %@", srcURL);
    finish = false;

    self.responseData = [NSMutableData data];
    getDataTime = 0;

    self.responseError = nil;
    self.connError = nil;
    
    // create the connection with the target request and this class as the delegate
    self.conn = [[[NSURLConnection alloc] initWithRequest:request
                                                 delegate:self
                                         startImmediately:NO] autorelease];
    
    [self.conn scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    // start the connection
    [self.conn start];
}

#pragma mark NSURLConnectionDelegate methods
/**
 * This delegate method is called when the NSURLConnection connects to the server.  It contains the 
 * NSURLResponse object with the headers returned by the server.  This method may be called multiple times.
 * Therefore, it is important to reset the data on each call.  Do not assume that it is the first call
 * of this method.
 **/
- (void) connection:(NSURLConnection *)connection 
 didReceiveResponse:(NSURLResponse *)response {
    NSLog(@"Received response from request to url %@", srcURL);
    
    NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;
    //NSLog(@"All headers = %@", [httpResponse allHeaderFields]);
    self.responseHeader = [httpResponse allHeaderFields];

    responseCode = httpResponse.statusCode;
    self.statusString = [NSHTTPURLResponse localizedStringForStatusCode:responseCode];
    if(responseCode == 200)
        self.statusString = @"OK";
 
    /*The individual values of the numeric status codes defined for HTTP/1.1
    | “200”  ; OK
    | “201”  ; Created
    | “202”  ; Accepted
    | “203”  ; Non-Authoritative Information
    | “204”  ; No Content
    | “205”  ; Reset Content
    | “206”  ; Partial Content
    */
    if (responseCode < 200 || responseCode >= 300)
    {// something went wrong, abort the whole thing
        self.responseError = [NSError errorWithDomain:@"CCBackendDomain"
                                            code:responseCode
                                        userInfo:@{NSLocalizedDescriptionKey: @"Bad HTTP Response Code"}];        
    }
    
    [responseData setLength:0];
}

/**
 * This delegate method is called for each chunk of data received from the server.  The chunk size
 * is dependent on the network type and the server configuration.  
 */
- (void)connection:(NSURLConnection *)connection 
    didReceiveData:(NSData *)data
{
    //NSLog(@"get some data");
    [responseData appendData:data];
    getDataTime++;
}

/**
 * This delegate methodis called if the connection cannot be established to the server.  
 * The error object will have a description of the error
 **/
- (void)connection:(NSURLConnection *)connection 
  didFailWithError:(NSError *)error
{
    //NSLog(@"Load failed with error %@", [error localizedDescription]);
    self.connError = error;
    
    finish = true;
}

/**
 * This delegate method is called when the data load is complete.  The delegate will be released 
 * following this call
 **/
- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    finish = true;
}

//Server evaluates client's certificate
- (BOOL) shouldTrustProtectionSpace:(NSURLProtectionSpace*)protectionSpace
{
    if(sslFile == nil)
        return YES;
    //load the bundle client certificate
    NSString *certPath = [[NSBundle mainBundle] pathForResource:sslFile ofType:@"der"];
    NSData *certData = [[NSData alloc] initWithContentsOfFile:certPath];
    CFDataRef certDataRef = (CFDataRef)certData;
    SecCertificateRef cert = SecCertificateCreateWithData(NULL, certDataRef);
    
    //Establish a chain of trust anchored on our bundled certificate
    CFArrayRef certArrayRef = CFArrayCreate(NULL, (void*)&cert, 1, NULL);
    SecTrustRef serverTrust = protectionSpace.serverTrust;
    SecTrustSetAnchorCertificates(serverTrust, certArrayRef);
    
    //Verify that trust
    SecTrustResultType trustResult;
    SecTrustEvaluate(serverTrust, &trustResult);
    
    if(trustResult == kSecTrustResultRecoverableTrustFailure)
    {
        CFDataRef errDataRef = SecTrustCopyExceptions(serverTrust);
        SecTrustSetExceptions(serverTrust, errDataRef);
        
        SecTrustEvaluate(serverTrust, &trustResult);
    }
    
    //Did our custom trust chain evaluate successfully?
    return trustResult = kSecTrustResultUnspecified || trustResult == kSecTrustResultProceed;    
}

- (void) connection:(NSURLConnection *)connection willSendRequestForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge
{
    id <NSURLAuthenticationChallengeSender> sender = challenge.sender;
    NSURLProtectionSpace *protectionSpace = challenge.protectionSpace;
    
    //Should server trust client?
    if([self shouldTrustProtectionSpace:protectionSpace])
    {
        SecTrustRef trust = [protectionSpace serverTrust];
//        
//        SecCertificateRef certificate = SecTrustGetCertificateAtIndex(trust, 0);
//        
//        NSData *serverCertificateData = (NSData*)SecCertificateCopyData(certificate);
//        NSString *serverCertificateDataHash = [[serverCertificateData base64EncodedString] ]
        NSURLCredential *credential = [NSURLCredential credentialForTrust:trust];
        [sender useCredential:credential forAuthenticationChallenge:challenge];
    }
    else
    {
        [sender cancelAuthenticationChallenge:challenge];
    }
}

@end
