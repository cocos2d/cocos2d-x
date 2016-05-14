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

#include "network/CCDownloader-apple.h"

#include "network/CCDownloader.h"
#include "deprecated/CCString.h"
#include <queue>

////////////////////////////////////////////////////////////////////////////////
//  OC Classes Declaration
#import <Foundation/NSData.h>

// this wrapper used to wrap C++ class DownloadTask into NSMutableDictionary
@interface DownloadTaskWrapper : NSObject
{
    std::shared_ptr<const cocos2d::network::DownloadTask> _task;
    NSMutableArray *_dataArray;
}
// temp vars for dataTask: didReceivedData callback
@property (nonatomic) int64_t bytesReceived;
@property (nonatomic) int64_t totalBytesReceived;

-(id)init:(std::shared_ptr<const cocos2d::network::DownloadTask>&)t;
-(const cocos2d::network::DownloadTask *)get;
-(void) addData:(NSData*) data;
-(int64_t) transferDataToBuffer:(void*)buffer lengthOfBuffer:(int64_t)len;

@end

@interface DownloaderAppleImpl : NSObject <NSURLSessionDataDelegate, NSURLSessionDownloadDelegate>
{
    const cocos2d::network::DownloaderApple *_outer;
    cocos2d::network::DownloaderHints _hints;
    std::queue<NSURLSessionTask*> _taskQueue;
}
@property (nonatomic, strong) NSURLSession *downloadSession;
@property (nonatomic, strong) NSMutableDictionary *taskDict;    // ocTask: DownloadTaskWrapper

-(id)init:(const cocos2d::network::DownloaderApple *)o hints:(const cocos2d::network::DownloaderHints&) hints;
-(const cocos2d::network::DownloaderHints&)getHints;
-(NSURLSessionDataTask *)createDataTask:(std::shared_ptr<const cocos2d::network::DownloadTask>&) task;
-(NSURLSessionDownloadTask *)createFileTask:(std::shared_ptr<const cocos2d::network::DownloadTask>&) task;
-(void)doDestroy;

@end

////////////////////////////////////////////////////////////////////////////////
//  C++ Classes Implementation

namespace cocos2d { namespace network {

    struct DownloadTaskApple : public IDownloadTask
    {
        DownloadTaskApple()
        : dataTask(nil)
        , downloadTask(nil)
        {
            DLLOG("Construct DownloadTaskApple %p", this);
        }
        
        virtual ~DownloadTaskApple()
        {
            DLLOG("Destruct DownloadTaskApple %p", this);
        }
        
        NSURLSessionDataTask *dataTask;
        NSURLSessionDownloadTask *downloadTask;
    };
#define DeclareDownloaderImplVar DownloaderAppleImpl *impl = (__bridge DownloaderAppleImpl *)_impl
    // the _impl's type is id, we should convert it to subclass before call it's methods
    DownloaderApple::DownloaderApple(const DownloaderHints& hints)
    : _impl(nil)
    {
        DLLOG("Construct DownloaderApple %p", this);
        _impl = (__bridge void*)[[DownloaderAppleImpl alloc] init: this hints:hints];
    }
    
    DownloaderApple::~DownloaderApple()
    {
        DeclareDownloaderImplVar;
        [impl doDestroy];
        DLLOG("Destruct DownloaderApple %p", this);
    }
    IDownloadTask *DownloaderApple::createCoTask(std::shared_ptr<const DownloadTask>& task)
    {
        DownloadTaskApple* coTask = new (std::nothrow) DownloadTaskApple();
        DeclareDownloaderImplVar;
        if (task->storagePath.length())
        {
            coTask->downloadTask = [impl createFileTask:task];
        }
        else
        {
            coTask->dataTask = [impl createDataTask:task];
        }
        return coTask;
    }
}}  // namespace cocos2d::network

////////////////////////////////////////////////////////////////////////////////
//  OC Classes Implementation
@implementation DownloadTaskWrapper

- (id)init: (std::shared_ptr<const cocos2d::network::DownloadTask>&)t
{
    DLLOG("Construct DonloadTaskWrapper %p", self);
    _dataArray = [NSMutableArray arrayWithCapacity:8];
    [_dataArray retain];
    _task = t;
    return self;
}

-(const cocos2d::network::DownloadTask *)get
{
    return _task.get();
}

-(void) addData:(NSData*) data
{
    [_dataArray addObject:data];
    self.bytesReceived += data.length;
    self.totalBytesReceived += data.length;
}

-(int64_t) transferDataToBuffer:(void*)buffer lengthOfBuffer:(int64_t)len
{
    int64_t bytesReceived = 0;
    int receivedDataObject = 0;
    
    __block char *p = (char *)buffer;
    for (NSData* data in _dataArray)
    {
        // check
        if (bytesReceived + data.length > len)
        {
            break;
        }
        
        // copy data
        [data enumerateByteRangesUsingBlock:^(const void *bytes,
                                              NSRange byteRange,
                                              BOOL *stop)
         {
             memcpy(p, bytes, byteRange.length);
             p += byteRange.length;
             *stop = NO;
         }];
        
        // accumulate
        bytesReceived += data.length;
        ++receivedDataObject;
    }
    
    // remove receivedNSDataObject from dataArray
    [_dataArray removeObjectsInRange:NSMakeRange(0, receivedDataObject)];
    self.bytesReceived -= bytesReceived;
    return bytesReceived;
}

-(void)dealloc
{
    [_dataArray release];
    [super dealloc];
    DLLOG("Destruct DownloadTaskWrapper %p", self);
}

@end

@implementation DownloaderAppleImpl

- (id)init: (const cocos2d::network::DownloaderApple*)o hints:(const cocos2d::network::DownloaderHints&) hints
{
    DLLOG("Construct DownloaderAppleImpl %p", self);
    // save outer task ref
    _outer = o;
    _hints = hints;
    
    // create task dictionary
    self.taskDict = [NSMutableDictionary dictionary];
    
    // create download session
    NSURLSessionConfiguration *defaultConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
    self.downloadSession = [NSURLSession sessionWithConfiguration:defaultConfig delegate:self delegateQueue:[NSOperationQueue mainQueue]];
//    self.downloadSession.sessionDescription = kCurrentSession;
    return self;
}

-(const cocos2d::network::DownloaderHints&)getHints
{
    return _hints;
}

-(NSURLSessionDataTask *)createDataTask:(std::shared_ptr<const cocos2d::network::DownloadTask>&) task
{
    const char *urlStr = task->requestURL.c_str();
    DLLOG("DownloaderAppleImpl createDataTask: %s", urlStr);
    NSURL *url = [NSURL URLWithString:[NSString stringWithUTF8String:urlStr]];
    NSURLRequest *request = nil;
    if (_hints.timeoutInSeconds > 0)
    {
        request = [NSURLRequest requestWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:(NSTimeInterval)_hints.timeoutInSeconds];
    }
    else
    {
        request = [NSURLRequest requestWithURL:url];
    }
    NSURLSessionDataTask *ocTask = [self.downloadSession dataTaskWithRequest:request];
    [self.taskDict setObject:[[DownloadTaskWrapper alloc] init:task] forKey:ocTask];

    if (_taskQueue.size() < _hints.countOfMaxProcessingTasks) {
        [ocTask resume];
        _taskQueue.push(nil);
    } else {
        _taskQueue.push(ocTask);
    }
    return ocTask;
};

-(NSURLSessionDownloadTask *)createFileTask:(std::shared_ptr<const cocos2d::network::DownloadTask>&) task
{
    const char *urlStr = task->requestURL.c_str();
    DLLOG("DownloaderAppleImpl createFileTask: %s", urlStr);
    NSURL *url = [NSURL URLWithString:[NSString stringWithUTF8String:urlStr]];
    NSURLRequest *request = nil;
    if (_hints.timeoutInSeconds > 0)
    {
        request = [NSURLRequest requestWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:(NSTimeInterval)_hints.timeoutInSeconds];
    }
    else
    {
        request = [NSURLRequest requestWithURL:url];
    }
    NSString *tempFilePath = [NSString stringWithFormat:@"%s%s", task->storagePath.c_str(), _hints.tempFileNameSuffix.c_str()];
    NSData *resumeData = [NSData dataWithContentsOfFile:tempFilePath];
    NSURLSessionDownloadTask *ocTask = nil;
    if (resumeData)
    {
        ocTask = [self.downloadSession downloadTaskWithResumeData:resumeData];
    }
    else
    {
        ocTask = [self.downloadSession downloadTaskWithRequest:request];
    }
    [self.taskDict setObject:[[DownloadTaskWrapper alloc] init:task] forKey:ocTask];

    if (_taskQueue.size() < _hints.countOfMaxProcessingTasks) {
        [ocTask resume];
        _taskQueue.push(nil);
    } else {
        _taskQueue.push(ocTask);
    }
    return ocTask;
};

-(void)doDestroy
{
    // cancel all download task
    NSEnumerator * enumeratorKey = [self.taskDict keyEnumerator];
    for (NSURLSessionDownloadTask *task in enumeratorKey)
    {
        DownloadTaskWrapper *wrapper = [self.taskDict objectForKey:task];
        
        // no resume support for a data task
        std::string storagePath = [wrapper get]->storagePath;
        if(storagePath.length() == 0) {
            [task cancel];
        }
        else {
            [task cancelByProducingResumeData:^(NSData *resumeData) {
                if (resumeData)
                {
                    NSString *tempFilePath = [NSString stringWithFormat:@"%s%s", storagePath.c_str(), _hints.tempFileNameSuffix.c_str()];
                    NSString *tempFileDir = [tempFilePath stringByDeletingLastPathComponent];
                    NSFileManager *fileManager = [NSFileManager defaultManager];
                    BOOL isDir = false;
                    if ([fileManager fileExistsAtPath:tempFileDir isDirectory:&isDir])
                    {
                        if (NO == isDir)
                        {
                            // TODO: the directory is a file, not a directory, how to echo to developer?
                            DLLOG("DownloaderAppleImpl temp dir is a file!");
                            return;
                        }
                    }
                    else
                    {
                        NSURL *tempFileURL = [NSURL fileURLWithPath:tempFileDir];
                        if (NO == [fileManager createDirectoryAtURL:tempFileURL withIntermediateDirectories:YES attributes:nil error:nil])
                        {
                            // create directory failed
                            DLLOG("DownloaderAppleImpl create temp dir failed");
                            return;
                        }
                    }

                    [resumeData writeToFile:tempFilePath atomically:YES];
                }
            }];
        }
    }
    _outer = nullptr;
    
    [self.downloadSession invalidateAndCancel];
    [self release];
}

-(void)dealloc
{
    [super dealloc];
    DLLOG("Destruct DownloaderAppleImpl %p", self);
}
#pragma mark - NSURLSessionTaskDelegate methods

//@optional

/* An HTTP request is attempting to perform a redirection to a different
 * URL. You must invoke the completion routine to allow the
 * redirection, allow the redirection with a modified request, or
 * pass nil to the completionHandler to cause the body of the redirection
 * response to be delivered as the payload of this request. The default
 * is to follow redirections.
 *
 * For tasks in background sessions, redirections will always be followed and this method will not be called.
 */
//- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
//willPerformHTTPRedirection:(NSHTTPURLResponse *)response
//        newRequest:(NSURLRequest *)request
// completionHandler:(void (^)(NSURLRequest *))completionHandler;

/* The task has received a request specific authentication challenge.
 * If this delegate is not implemented, the session specific authentication challenge
 * will *NOT* be called and the behavior will be the same as using the default handling
 * disposition.
 */
//- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
//didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
// completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential))completionHandler;

/* Sent if a task requires a new, unopened body stream.  This may be
 * necessary when authentication has failed for any request that
 * involves a body stream.
 */
//- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
// needNewBodyStream:(void (^)(NSInputStream *bodyStream))completionHandler;

/* Sent periodically to notify the delegate of upload progress.  This
 * information is also available as properties of the task.
 */
//- (void)URLSession:(NSURLSession *)session task :(NSURLSessionTask *)task
//                                 didSendBodyData:(int64_t)bytesSent
//                                  totalBytesSent:(int64_t)totalBytesSent
//                        totalBytesExpectedToSend:(int64_t)totalBytesExpectedToSend;

/* Sent as the last message related to a specific task.  Error may be
 * nil, which implies that no error occurred and this task is complete.
 */
- (void)URLSession:(NSURLSession *)session task :(NSURLSessionTask *)task
                            didCompleteWithError:(NSError *)error
{
    DLLOG("DownloaderAppleImpl task: \"%s\" didCompleteWithError: %d errDesc: %s"
          , [task.originalRequest.URL.absoluteString cStringUsingEncoding:NSUTF8StringEncoding]
          , (error ? (int)error.code: 0)
          , [error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding]);

    // clean wrapper C++ object
    DownloadTaskWrapper *wrapper = [self.taskDict objectForKey:task];
    
    if(_outer)
    {
        if(error)
        {
            std::vector<unsigned char> buf; // just a placeholder
            _outer->onTaskFinish(*[wrapper get],
                             cocos2d::network::DownloadTask::ERROR_IMPL_INTERNAL,
                             (int)error.code,
                             [error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding],
                             buf);
        }
        else if (![wrapper get]->storagePath.length())
        {
            // call onTaskFinish for a data task
            // (for a file download task, callback is called in didFinishDownloadingToURL)
            std::string errorString;

            const int64_t buflen = [wrapper totalBytesReceived];
            char buf[buflen];
            [wrapper transferDataToBuffer:buf lengthOfBuffer:buflen];
            std::vector<unsigned char> data(buf, buf + buflen);
            
            _outer->onTaskFinish(*[wrapper get],
                                 cocos2d::network::DownloadTask::ERROR_NO_ERROR,
                                 0,
                                 errorString,
                                 data);
        }
        else
        {
            NSInteger statusCode = ((NSHTTPURLResponse*)task.response).statusCode;
            
            // Check for error status code
            if (statusCode >= 400)
            {
                std::vector<unsigned char> buf; // just a placeholder
                const char *orignalURL = [task.originalRequest.URL.absoluteString cStringUsingEncoding:NSUTF8StringEncoding];
                std::string errorMessage = cocos2d::StringUtils::format("Downloader: Failed to download %s with status code (%d)", orignalURL, (int)statusCode);
                
                _outer->onTaskFinish(*[wrapper get],
                                     cocos2d::network::DownloadTask::ERROR_IMPL_INTERNAL,
                                     0,
                                     errorMessage,
                                     buf);
            }
        }
    }
    [self.taskDict removeObjectForKey:task];
    [wrapper release];

    while (!_taskQueue.empty() && _taskQueue.front() == nil) {
        _taskQueue.pop();
    }
    if (!_taskQueue.empty()) {
        [_taskQueue.front() resume];
        _taskQueue.pop();
    }
}

#pragma mark - NSURLSessionDataDelegate methods
//@optional
/* The task has received a response and no further messages will be
 * received until the completion block is called. The disposition
 * allows you to cancel a request or to turn a data task into a
 * download task. This delegate message is optional - if you do not
 * implement it, you can get the response as a property of the task.
 *
 * This method will not be called for background upload tasks (which cannot be converted to download tasks).
 */
//- (void)URLSession:(NSURLSession *)session dataTask :(NSURLSessionDataTask *)dataTask
//                                  didReceiveResponse:(NSURLResponse *)response
//                                   completionHandler:(void (^)(NSURLSessionResponseDisposition disposition))completionHandler
//{
//    DLLOG("DownloaderAppleImpl dataTask: response:%s", [response.description cStringUsingEncoding:NSUTF8StringEncoding]);
//    completionHandler(NSURLSessionResponseAllow);
//}

/* Notification that a data task has become a download task.  No
 * future messages will be sent to the data task.
 */
//- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
//didBecomeDownloadTask:(NSURLSessionDownloadTask *)downloadTask;

/* Sent when data is available for the delegate to consume.  It is
 * assumed that the delegate will retain and not copy the data.  As
 * the data may be discontiguous, you should use
 * [NSData enumerateByteRangesUsingBlock:] to access it.
 */
- (void)URLSession:(NSURLSession *)session dataTask :(NSURLSessionDataTask *)dataTask
                                      didReceiveData:(NSData *)data
{
    DLLOG("DownloaderAppleImpl dataTask: \"%s\" didReceiveDataLen %d",
          [dataTask.originalRequest.URL.absoluteString cStringUsingEncoding:NSUTF8StringEncoding],
          (int)data.length);
    if (nullptr == _outer)
    {
        return;
    }
    DownloadTaskWrapper *wrapper = [self.taskDict objectForKey:dataTask];
    [wrapper addData:data];
    
    std::function<int64_t(void *, int64_t)> transferDataToBuffer =
    [wrapper](void *buffer, int64_t bufLen)->int64_t
    {
        return [wrapper transferDataToBuffer:buffer lengthOfBuffer: bufLen];
    };
    
    _outer->onTaskProgress(*[wrapper get],
                          wrapper.bytesReceived,
                          wrapper.totalBytesReceived,
                          dataTask.countOfBytesExpectedToReceive,
                          transferDataToBuffer);
}

/* Invoke the completion routine with a valid NSCachedURLResponse to
 * allow the resulting data to be cached, or pass nil to prevent
 * caching. Note that there is no guarantee that caching will be
 * attempted for a given resource, and you should not rely on this
 * message to receive the resource data.
 */
//- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
// willCacheResponse:(NSCachedURLResponse *)proposedResponse
// completionHandler:(void (^)(NSCachedURLResponse *cachedResponse))completionHandler;

#pragma mark - NSURLSessionDownloadDelegate methods

/* Sent when a download task that has completed a download.  The delegate should
 * copy or move the file at the given location to a new location as it will be
 * removed when the delegate message returns. URLSession:task:didCompleteWithError: will
 * still be called.
 */
- (void)URLSession:(NSURLSession *)session downloadTask :(NSURLSessionDownloadTask *)downloadTask
                               didFinishDownloadingToURL:(NSURL *)location
{
    DLLOG("DownloaderAppleImpl downloadTask: \"%s\" didFinishDownloadingToURL %s",
          [downloadTask.originalRequest.URL.absoluteString cStringUsingEncoding:NSUTF8StringEncoding],
          [location.absoluteString cStringUsingEncoding:NSUTF8StringEncoding]);
    if (nullptr == _outer)
    {
        return;
    }
    
    // On iOS 9 a response with status code 4xx(Client Error) or 5xx(Server Error)
    // might end up calling this delegate method, saving the error message to the storage path
    // and treating this download task as a successful one, so we need to check the status code here
    NSInteger statusCode = ((NSHTTPURLResponse*)downloadTask.response).statusCode;
    if (statusCode >= 400)
    {
        return;
    }
    
    DownloadTaskWrapper *wrapper = [self.taskDict objectForKey:downloadTask];
    const char * storagePath = [wrapper get]->storagePath.c_str();
    NSString *destPath = [NSString stringWithUTF8String:storagePath];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSURL *destURL = nil;

    do
    {
        if ([destPath hasPrefix:@"file://"])
        {
            break;
        }
        
        if ('/' == [destPath characterAtIndex:0])
        {
            destURL = [NSURL fileURLWithPath:destPath];
            break;
        }
        
        // relative path, store to user domain default
        NSArray *URLs = [fileManager URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask];
        NSURL *documentsDirectory = URLs[0];
        destURL = [documentsDirectory URLByAppendingPathComponent:destPath];
    } while (0);
    
    // Make sure we overwrite anything that's already there
    [fileManager removeItemAtURL:destURL error:NULL];
    
    // copy file to dest location
    int errorCode = cocos2d::network::DownloadTask::ERROR_NO_ERROR;
    int errorCodeInternal = 0;
    std::string errorString;
    
    NSError *error = nil;
    if ([fileManager copyItemAtURL:location toURL:destURL error:&error])
    {
        // success, remove temp file if it exist
        if (_hints.tempFileNameSuffix.length())
        {
            NSString *tempStr = [[destURL absoluteString] stringByAppendingFormat:@"%s", _hints.tempFileNameSuffix.c_str()];
            NSURL *tempDestUrl = [NSURL URLWithString:tempStr];
            [fileManager removeItemAtURL:tempDestUrl error:NULL];
        }
    }
    else
    {
        errorCode = cocos2d::network::DownloadTask::ERROR_FILE_OP_FAILED;
        if (error)
        {
            errorCodeInternal = (int)error.code;
            errorString = [error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding];
        }
    }

    std::vector<unsigned char> buf; // just a placeholder
    _outer->onTaskFinish(*[wrapper get], errorCode, errorCodeInternal, errorString, buf);
}

// @optional
/* Sent periodically to notify the delegate of download progress. */
- (void)URLSession:(NSURLSession *)session downloadTask :(NSURLSessionDownloadTask *)downloadTask
                                            didWriteData:(int64_t)bytesWritten
                                       totalBytesWritten:(int64_t)totalBytesWritten
                               totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite
{
//    NSLog(@"DownloaderAppleImpl downloadTask: \"%@\" received: %lld total: %lld", downloadTask.originalRequest.URL, totalBytesWritten, totalBytesExpectedToWrite);

    if (nullptr == _outer)
    {
        return;
    }
    
    DownloadTaskWrapper *wrapper = [self.taskDict objectForKey:downloadTask];
    
    std::function<int64_t(void *, int64_t)> transferDataToBuffer;   // just a placeholder
    _outer->onTaskProgress(*[wrapper get], bytesWritten, totalBytesWritten, totalBytesExpectedToWrite, transferDataToBuffer);
}

/* Sent when a download has been resumed. If a download failed with an
 * error, the -userInfo dictionary of the error will contain an
 * NSURLSessionDownloadTaskResumeData key, whose value is the resume
 * data.
 */
- (void)URLSession:(NSURLSession *)session downloadTask :(NSURLSessionDownloadTask *)downloadTask
                                       didResumeAtOffset:(int64_t)fileOffset
                                      expectedTotalBytes:(int64_t)expectedTotalBytes
{
    NSLog(@"[TODO]DownloaderAppleImpl downloadTask: \"%@\" didResumeAtOffset: %lld", downloadTask.originalRequest.URL, fileOffset);
    // 下载失败
//    self.downloadFail([self getDownloadRespose:XZDownloadFail identifier:self.identifier progress:0.00 downloadUrl:nil downloadSaveFileUrl:nil downloadData:nil downloadResult:@"下载失败"]);
}

@end
