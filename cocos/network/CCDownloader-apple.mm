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
#include <set>

////////////////////////////////////////////////////////////////////////////////
//  OC Classes Declaration
#import <Foundation/NSData.h>

namespace {
    class DownloadTaskWrapper;
}

@interface DownloaderAppleImpl : NSObject <NSURLSessionDataDelegate, NSURLSessionDownloadDelegate>
{
    const cocos2d::network::DownloaderApple *_outer;
    cocos2d::network::DownloaderHints _hints;
    std::queue<NSURLSessionTask*> _taskQueue;
    std::unordered_map<NSURLSessionTask*, std::shared_ptr<DownloadTaskWrapper>> _taskDict;
    std::set<NSURLSessionTask*> _runningTasks;
}
@property (nonatomic, strong) NSURLSession *downloadSession;
@property (nonatomic, assign) BOOL isSuspended;

-(id)init:(const cocos2d::network::DownloaderApple *)o hints:(const cocos2d::network::DownloaderHints&) hints;
-(const cocos2d::network::DownloaderHints&)getHints;
-(NSURLSessionDataTask *)createDataTask:(std::shared_ptr<const cocos2d::network::DownloadTask>&) task;
-(NSURLSessionDownloadTask *)createFileTask:(std::shared_ptr<const cocos2d::network::DownloadTask>&) task;
-(void)suspend;
-(void)resume;
-(void)doDestroy;

@end

// dispatch queue for asynchronously perform expensive task operation
static dispatch_queue_t task_operation_queue()
{
    static dispatch_queue_t queue;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        queue = dispatch_queue_create("org.cocos2dx.downloader.task.operation", DISPATCH_QUEUE_SERIAL);
    });
    return queue;
}

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
        std::shared_ptr<const DownloadTask> retainedTask = nullptr; // for retaining DownloadTask for asynchronous task creation
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
        DownloadTaskApple* coTask = new DownloadTaskApple();
        coTask->retainedTask = task;
        // put expensive task creation into background
        dispatch_async(task_operation_queue(), ^{
            DeclareDownloaderImplVar;
            if (coTask->retainedTask->storagePath.length())
            {
                coTask->downloadTask = [impl createFileTask:coTask->retainedTask];
            }
            else
            {
                coTask->dataTask = [impl createDataTask:coTask->retainedTask];
            }
            // release after asynchronous task creation completed
            coTask->retainedTask.reset();
        });
        return coTask;
    }

    void DownloaderApple::suspend()
    {
        dispatch_async(task_operation_queue(), ^{
            DeclareDownloaderImplVar;
            [impl suspend];
        });
    }

    void DownloaderApple::resume()
    {
        dispatch_async(task_operation_queue(), ^{
            DeclareDownloaderImplVar;
            [impl resume];
        });
    }

    bool DownloaderApple::isSuspended() const
    {
        DeclareDownloaderImplVar;
        return impl.isSuspended;
    }
}}  // namespace cocos2d::network

// internal C++ classes are declared in anonymous namespace
namespace {
    //// this wrapper used to hold received data for data tasks
    struct DownloadTaskWrapper
    {
        std::shared_ptr<const cocos2d::network::DownloadTask> cppTask;
        std::vector<NSData*> dataVector;
        int64_t bytesReceived = 0;
        int64_t totalBytesReceived = 0;

        static std::shared_ptr<DownloadTaskWrapper> createShared(const std::shared_ptr<const cocos2d::network::DownloadTask>& cppTask)
        {
            auto wrapper = new DownloadTaskWrapper;
            wrapper->cppTask = cppTask;
            return std::shared_ptr<DownloadTaskWrapper>(wrapper);
        }
        
        void appendData(NSData* data)
        {
            dataVector.push_back(data);
            bytesReceived += data.length;
            totalBytesReceived += data.length;
        }
        
        int64_t transferDataToBuffer(void* buffer, int64_t length)
        {
            int64_t bytesReceived = 0;
            int receivedDataObject = 0;

            __block char *p = (char *)buffer;
            for (auto data : dataVector)
            {
                // check
                if (bytesReceived + data.length > length)
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
            dataVector.clear();
            this->bytesReceived -= bytesReceived;
            return bytesReceived;
        }
    };
}

@implementation DownloaderAppleImpl

- (id)init: (const cocos2d::network::DownloaderApple*)o hints:(const cocos2d::network::DownloaderHints&) hints
{
    DLLOG("Construct DownloaderAppleImpl %p", self);
    // save outer task ref
    _outer = o;
    _hints = hints;
    _isSuspended = NO;
    
    // create download session
    NSURLSessionConfiguration *defaultConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
    // there will be many I/O operations in delegate methods, we should put them in background then dispatch callbacks in main queue
    self.downloadSession = [NSURLSession sessionWithConfiguration:defaultConfig delegate:self delegateQueue:nil];
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

    [self enqueueTask:ocTask withCppTask:task];
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
    [self enqueueTask:ocTask withCppTask:task];
    return ocTask;
};

// This method should only be run in task_operation_queue
-(void)suspend
{
    _isSuspended = YES;
    for (auto& task : _runningTasks)
    {
        [task suspend];
    }
}

// This method should only be run in task_operation_queue
-(void)resume
{
    _isSuspended = NO;
    for (auto task : _runningTasks)
    {
        [task resume];
    }
}

-(void)doDestroy
{
    // cancel all download task
    for (const auto& entry : _taskDict)
    {
        const auto& task = entry.first;
        const auto& wrapper = entry.second;
        
        // no resume support for a data task
        std::string storagePath = wrapper->cppTask->storagePath;
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

#pragma mark - Private

// This method should only be run in task_operation_queue
-(void)enqueueTask:(NSURLSessionTask*)task
       withCppTask:(std::shared_ptr<const cocos2d::network::DownloadTask>&)cppTask
{
    _taskDict[task] = DownloadTaskWrapper::createShared(cppTask);
    if (_runningTasks.size() < _hints.countOfMaxProcessingTasks)
    {
        _runningTasks.insert(task);
        if (!_isSuspended)
        {
            [task resume];
        }
    }
    else
    {
        _taskQueue.push(task);
    }
}

// This method should only be run in task_operation_queue
-(void)runNextTaskIfExists
{
    if (!_taskQueue.empty() && _runningTasks.size() < _hints.countOfMaxProcessingTasks)
    {
        NSURLSessionTask* task = _taskQueue.front();
        _taskQueue.pop();
        _runningTasks.insert(task);
        if (!_isSuspended)
        {
            [task resume];
        }
    }
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
    DLLOG("DownloaderAppleImpl task: \"%s\" didCompleteWithError: %d errDesc: %s taskQueue: %u"
          , [task.originalRequest.URL.absoluteString cStringUsingEncoding:NSUTF8StringEncoding]
          , (error ? (int)error.code: 0)
          , [error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding]
          , _taskQueue.size());
    
    if(_outer)
    {
        if(error)
        {
            dispatch_async(dispatch_get_main_queue(), ^{
                std::vector<unsigned char> buf; // just a placeholder
                _outer->onTaskFinish(*_taskDict[task]->cppTask,
                                     cocos2d::network::DownloadTask::ERROR_IMPL_INTERNAL,
                                     (int)error.code,
                                     [error.localizedDescription cStringUsingEncoding:NSUTF8StringEncoding],
                                     buf);
            });
        }
        else if(!_taskDict[task]->cppTask->storagePath.length())
        {
            // call onTaskFinish for a data task
            // (for a file download task, callback is called in didFinishDownloadingToURL)
            dispatch_async(dispatch_get_main_queue(), ^{
                auto& wrapper = _taskDict[task];
                std::string errorMessage;
                const int64_t buflen = wrapper->totalBytesReceived;
                char buf[buflen];

                wrapper->transferDataToBuffer(buf, buflen);
                std::vector<unsigned char> data(buf, buf + buflen);
                _outer->onTaskFinish(*(wrapper->cppTask),
                                     cocos2d::network::DownloadTask::ERROR_NO_ERROR,
                                     0,
                                     errorMessage,
                                     data);
            });
        }
        else
        {
            NSInteger statusCode = ((NSHTTPURLResponse*)task.response).statusCode;
            
            // Check for error status code
            if (statusCode >= 400)
            {
                dispatch_async(dispatch_get_main_queue(), ^{
                    std::vector<unsigned char> buf; // just a placeholder
                    const char *orignalURL = [task.originalRequest.URL.absoluteString cStringUsingEncoding:NSUTF8StringEncoding];
                    std::string errorMessage = cocos2d::StringUtils::format("Downloader: Failed to download %s with status code (%d)", orignalURL, (int)statusCode);
                
                    _outer->onTaskFinish(*_taskDict[task]->cppTask,
                                         cocos2d::network::DownloadTask::ERROR_IMPL_INTERNAL,
                                         0,
                                         errorMessage,
                                         buf);
                });
            }
        }
    }
    // dispatch to main queue to make sure this happens after _outer->onTaskFinish callback
    dispatch_async(dispatch_get_main_queue(), ^{
        dispatch_async(task_operation_queue(), ^{
            _runningTasks.erase(task);
            _taskDict.erase(task);
            [self runNextTaskIfExists];
        });
    });
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
    
    auto &wrapper = _taskDict[dataTask];
    wrapper->appendData(data);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        std::function<int64_t(void *, int64_t)> transferDataToBuffer =
        [wrapper](void *buffer, int64_t bufLen)->int64_t
        {
            return wrapper->transferDataToBuffer(buffer, bufLen);
        };
        _outer->onTaskProgress(*wrapper->cppTask,
                               wrapper->bytesReceived,
                               wrapper->totalBytesReceived,
                               dataTask.countOfBytesExpectedToReceive,
                               transferDataToBuffer);
    });
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

    const char * storagePath = _taskDict[downloadTask]->cppTask->storagePath.c_str();
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
    dispatch_async(dispatch_get_main_queue(), ^{
        std::vector<unsigned char> buf; // just a placeholder
        _outer->onTaskFinish(*_taskDict[downloadTask]->cppTask, errorCode, errorCodeInternal, errorString, buf);
    });
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
    dispatch_async(dispatch_get_main_queue(), ^{
        std::function<int64_t(void *, int64_t)> transferDataToBuffer;   // just a placeholder
        _outer->onTaskProgress(*_taskDict[downloadTask]->cppTask, bytesWritten, totalBytesWritten, totalBytesExpectedToWrite, transferDataToBuffer);
    });
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
