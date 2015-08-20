/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "network/CCDownloader-apple.h"

#import <Foundation/Foundation.h>
#import <Foundation/NSData.h>

@interface Conn : NSObject
{
    std::string name;
}
@property (retain) NSURLConnection *connection;

@end

@implementation Conn

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    NSLog(@"didReceiveResponse");
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    NSLog(@"didReceiveData");
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    
    NSLog(@"didFailWithError");
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    NSLog(@"Succeeded! Receive  bytes of data(unsigned long)");

}

@end
NS_CC_BEGIN

using namespace network;

DownloaderImpl::DownloaderImpl()
: IDownloaderImpl()
{
}

DownloaderImpl::~DownloaderImpl()
{

}

bool DownloaderImpl::init()
{
    return true;
}

int DownloaderImpl::performDownload(DownloadUnit* unit,
                    const WriterCallback& writerCallback,
                    const ProgressCallback& progressCallback
                    )
{
    _lastErrCode = 0;
    _lastErrStr = "";
    
    NSString *urlStr = [NSString stringWithCString: unit->srcUrl.c_str() encoding:NSUTF8StringEncoding];
    NSURL *url = [NSURL URLWithString: urlStr];
    NSURLRequest *request = [NSURLRequest requestWithURL: url];

    // due to this function is sync implement, so send a sync request by NSURLConnection
    NSURLResponse *response = nil;
    NSError *err = nil;
    NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&err];
    if (err)
    {
        _lastErrCode = (int)err.code;
        NSString *errStr = [err localizedDescription];
        if (errStr)
        {
            _lastErrStr = [errStr UTF8String];
        }
    }
    else
    {
        int dataLen = 0;
        if (data)
        {
            dataLen = (int)[data length];
            writerCallback((void*)[data bytes], 1, dataLen, unit);
        }
        progressCallback(unit, dataLen, dataLen);
    }
    return _lastErrCode;
}

int DownloaderImpl::performBatchDownload(const DownloadUnits& units,
                         const WriterCallback& writerCallback,
                         const ProgressCallback& progressCallback,
                         const ErrorCallback& errorCallback
                         )
{
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    queue.maxConcurrentOperationCount = 4;
    
    NSMutableArray *operations = [NSMutableArray arrayWithCapacity: units.size()];
    
    for (auto it = units.begin(), end = units.end(); it != end; it++)
    {
        DownloadUnit *unit = (DownloadUnit *)&(it->second);
        NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
            NSString *urlStr = [NSString stringWithCString: unit->srcUrl.c_str() encoding:NSUTF8StringEncoding];
            NSURL *url = [NSURL URLWithString: urlStr];
            NSError *err = nil;
            NSData *data = [NSData dataWithContentsOfURL: url  options: NSDataReadingUncached  error: &err];
            if (err)
            {
                NSString *errStr = [err localizedDescription];
                if (errStr)
                {
                    const char * c_errStr = [errStr UTF8String];
                    errorCallback(c_errStr, (int)err.code, c_errStr);
                }
            }
            else
            {
                int dataLen = 0;
                if (data)
                {
                    dataLen = (int)[data length];
                    writerCallback((void*)[data bytes], 1, dataLen, unit);
                }
                progressCallback(unit, dataLen, dataLen);
            }
        }];
        [operations addObject:operation];
    }
    
    [queue addOperations:operations waitUntilFinished:YES];
    NSLog(@"performBatchDownload end");
    return 0;
}

int DownloaderImpl::getHeader(const std::string& url, HeaderInfo* headerInfo)
{
    return 0;
}

std::string DownloaderImpl::getStrError() const
{
    return _lastErrStr;
}

void DownloaderImpl::setConnectionTimeout(int timeout)
{

}

bool DownloaderImpl::supportsResume(const std::string& url)
{
    return false;
}

NS_CC_END

#endif  //  (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)