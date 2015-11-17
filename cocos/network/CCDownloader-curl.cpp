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

#include "network/CCDownloader-curl.h"

#include <set>

#include <curl/curl.h>

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "platform/CCFileUtils.h"
#include "network/CCDownloader.h"

// **NOTE**
// In the file:
// member function with suffix "Proc" designed called in DownloaderCURL::_threadProc
// member function without suffix designed called in main thread

namespace cocos2d { namespace network {
    using namespace std;
    
////////////////////////////////////////////////////////////////////////////////
//  Implementation DownloadTaskCURL

    class DownloadTaskCURL : public IDownloadTask
    {
        static int _sSerialId;
        
        // if more than one task write to one file, cause file broken
        // so use a set to check this situation
        static set<string> _sStoragePathSet;
    public:
        int serialId;
        
        DownloadTaskCURL()
        : serialId(_sSerialId++)
        , _fp(nullptr)
        {
            _initInternal();
            DLLOG("Construct DownloadTaskCURL %p", this);
        }
        
        virtual ~DownloadTaskCURL()
        {
            // if task destoried unnormally, we should release WritenFileName stored in set.
            // Normally, this action should done when task finished.
            if (_tempFileName.length() && _sStoragePathSet.end() != _sStoragePathSet.find(_tempFileName))
            {
                DownloadTaskCURL::_sStoragePathSet.erase(_tempFileName);
            }
            if (_fp)
            {
                fclose(_fp);
                _fp = nullptr;
            }
            DLLOG("Destruct DownloadTaskCURL %p", this);
        }
        
        bool init(const string& filename, const string& tempSuffix)
        {
            if (0 == filename.length())
            {
                // data task
                _buf.reserve(CURL_MAX_WRITE_SIZE);
                return true;
            }
            
            // file task
            _fileName = filename;
            _tempFileName = filename;
            _tempFileName.append(tempSuffix);
            
            if (_sStoragePathSet.end() != _sStoragePathSet.find(_tempFileName))
            {
                // there is another task uses this storate path
                _errCode = DownloadTask::ERROR_FILE_OP_FAILED;
                _errCodeInternal = 0;
                _errDescription = "More than one download file task write to same file:";
                _errDescription.append(_tempFileName);
                return false;
            }
            _sStoragePathSet.insert(_tempFileName);
            
            // open temp file handle for write
            bool ret = false;
            do
            {
                string dir;
                unsigned long found = _tempFileName.find_last_of("/\\");
                if (found == string::npos)
                {
                    _errCode = DownloadTask::ERROR_INVALID_PARAMS;
                    _errCodeInternal = 0;
                    _errDescription = "Can't find dirname in storagePath.";
                    break;
                }
                
                // ensure directory is exist
                auto util = FileUtils::getInstance();
                dir = _tempFileName.substr(0, found+1);
                if (false == util->isDirectoryExist(dir))
                {
                    if (false == util->createDirectory(dir))
                    {
                        _errCode = DownloadTask::ERROR_FILE_OP_FAILED;
                        _errCodeInternal = 0;
                        _errDescription = "Can't create dir:";
                        _errDescription.append(dir);
                        break;
                    }
                }

                // open file
                _fp = fopen(util->getSuitableFOpen(_tempFileName).c_str(), "ab");
                if (nullptr == _fp)
                {
                    _errCode = DownloadTask::ERROR_FILE_OP_FAILED;
                    _errCodeInternal = 0;
                    _errDescription = "Can't open file:";
                    _errDescription.append(_tempFileName);
                }
                ret = true;
            } while (0);

            return ret;
        }

        void initProc()
        {
            lock_guard<mutex> lock(_mutex);
            _initInternal();
        }
        
        void setErrorProc(int code, int codeInternal, const char *desc)
        {
            lock_guard<mutex> lock(_mutex);
            _errCode = code;
            _errCodeInternal = codeInternal;
            _errDescription = desc;
        }
        
        size_t writeDataProc(unsigned char *buffer, size_t size, size_t count)
        {
            lock_guard<mutex> lock(_mutex);
            size_t ret = 0;
            if (_fp)
            {
                ret = fwrite(buffer, size, count, _fp);
            }
            else
            {
                ret = size * count;
                auto cap = _buf.capacity();
                auto bufSize = _buf.size();
                if (cap < bufSize + ret)
                {
                    _buf.reserve(bufSize * 2);
                }
                _buf.insert(_buf.end() , buffer, buffer + ret);
            }
            if (ret)
            {
                _bytesReceived += ret;
                _totalBytesReceived += ret;
            }
            return ret;
        }
        
    private:
        friend class DownloaderCURL;
        
        // for lock object instance
        mutex _mutex;
        
        // header info
        bool    _acceptRanges;
        bool    _headerAchieved;
        int64_t _totalBytesExpected;
        
        string  _header;        // temp buffer for receive header string, only used in thread proc
        
        // progress
        int64_t _bytesReceived;
        int64_t _totalBytesReceived;
        
        // error
        int     _errCode;
        int     _errCodeInternal;
        string  _errDescription;
        
        // for saving data
        string _fileName;
        string _tempFileName;
        vector<unsigned char> _buf;
        FILE*  _fp;
        
        void _initInternal()
        {
            _acceptRanges = (false);
            _headerAchieved = (false);
            _bytesReceived = (0);
            _totalBytesReceived = (0);
            _totalBytesExpected = (0);
            _errCode = (DownloadTask::ERROR_NO_ERROR);
            _errCodeInternal = (CURLE_OK);
            _header.resize(0);
            _header.reserve(384);   // pre alloc header string buffer
        }
    };
    int DownloadTaskCURL::_sSerialId;
    set<string> DownloadTaskCURL::_sStoragePathSet;
    
    typedef pair< shared_ptr<const DownloadTask>, DownloadTaskCURL *> TaskWrapper;
    
////////////////////////////////////////////////////////////////////////////////
//  Implementation DownloaderCURL::Impl
    // This class shared by DownloaderCURL and work thread.
    class DownloaderCURL::Impl : public enable_shared_from_this<DownloaderCURL::Impl>
    {
    public:
        DownloaderHints hints;
        
        Impl()
//        : _thread(nullptr)
        {
            DLLOG("Construct DownloaderCURL::Impl %p", this);
        }
        
        ~Impl()
        {
            DLLOG("Destruct DownloaderCURL::Impl %p %d", this, _thread.joinable());
        }
        
        void addTask(std::shared_ptr<const DownloadTask> task, DownloadTaskCURL* coTask)
        {
            if (DownloadTask::ERROR_NO_ERROR == coTask->_errCode)
            {
                lock_guard<mutex> lock(_requestMutex);
                _requestQueue.push_back(make_pair(task, coTask));
            }
            else
            {
                lock_guard<mutex> lock(_finishedMutex);
                _finishedQueue.push_back(make_pair(task, coTask));
            }
        }
        
        void run()
        {
            lock_guard<mutex> lock(_threadMutex);
            if (false == _thread.joinable())
            {
                thread newThread(&DownloaderCURL::Impl::_threadProc, this);
                _thread.swap(newThread);
            }
        }
        
        void stop()
        {
            lock_guard<mutex> lock(_threadMutex);
            if (_thread.joinable())
            {
                _thread.detach();
            }
        }
        
        bool stoped()
        {
            lock_guard<mutex> lock(_threadMutex);
            return false == _thread.joinable() ? true : false;
        }
        
        void getProcessTasks(vector<TaskWrapper>& outList)
        {
            lock_guard<mutex> lock(_processMutex);
            outList.reserve(_processSet.size());
            outList.insert(outList.end(), _processSet.begin(), _processSet.end());
        }
        
        void getFinishedTasks(vector<TaskWrapper>& outList)
        {
            lock_guard<mutex> lock(_finishedMutex);
            outList.reserve(_finishedQueue.size());
            outList.insert(outList.end(), _finishedQueue.begin(), _finishedQueue.end());
            _finishedQueue.clear();
        }

    private:
        static size_t _outputHeaderCallbackProc(void *buffer, size_t size, size_t count, void *userdata)
        {
            int strLen = int(size * count);
            DLLOG("    _outputHeaderCallbackProc: %.*s", strLen, buffer);
            DownloadTaskCURL& coTask = *((DownloadTaskCURL*)(userdata));
            coTask._header.append((const char *)buffer, strLen);
            return strLen;
        }
        
        static size_t _outputDataCallbackProc(void *buffer, size_t size, size_t count, void *userdata)
        {
//            DLLOG("    _outputDataCallbackProc: size(%ld), count(%ld)", size, count);
            DownloadTaskCURL *coTask = (DownloadTaskCURL*)userdata;

            // If your callback function returns CURL_WRITEFUNC_PAUSE it will cause this transfer to become paused.
            return coTask->writeDataProc((unsigned char *)buffer, size, count);
        }

        // this function designed call in work thread
        // the curl handle destroyed in _threadProc
        // handle inited for get header
        void _initCurlHandleProc(CURL *handle, TaskWrapper& wrapper, bool forContent = false)
        {
            const DownloadTask& task = *wrapper.first;
            const DownloadTaskCURL* coTask = wrapper.second;
            
            // set url
            curl_easy_setopt(handle, CURLOPT_URL, task.requestURL.c_str());
            
            // set write func
            if (forContent)
            {
                curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, DownloaderCURL::Impl::_outputDataCallbackProc);
            }
            else
            {
                curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, DownloaderCURL::Impl::_outputHeaderCallbackProc);
            }
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, coTask);
            
            curl_easy_setopt(handle, CURLOPT_NOPROGRESS, true);
//            curl_easy_setopt(handle, CURLOPT_XFERINFOFUNCTION, DownloaderCURL::Impl::_progressCallbackProc);
//            curl_easy_setopt(handle, CURLOPT_XFERINFODATA, coTask);

            curl_easy_setopt(handle, CURLOPT_FAILONERROR, true);
            curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);
            
            if (forContent)
            {
                /** if server acceptRanges and local has part of file, we continue to download **/
                if (coTask->_acceptRanges && coTask->_totalBytesReceived > 0)
                {
                    curl_easy_setopt(handle, CURLOPT_RESUME_FROM_LARGE,(curl_off_t)coTask->_totalBytesReceived);
                }
            }
            else
            {
                // get header options
                curl_easy_setopt(handle, CURLOPT_HEADER, 1);
                curl_easy_setopt(handle, CURLOPT_NOBODY, 1);
            }

//            if (!sProxy.empty())
//            {
//                curl_easy_setopt(curl, CURLOPT_PROXY, sProxy.c_str());
//            }
            if (hints.timeoutInSeconds)
            {
                curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, hints.timeoutInSeconds);
            }
            
            static const long LOW_SPEED_LIMIT = 1;
            static const long LOW_SPEED_TIME = 5;
            curl_easy_setopt(handle, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
            curl_easy_setopt(handle, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
            
            static const int MAX_REDIRS = 2;
            if (MAX_REDIRS)
            {
                curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, true);
                curl_easy_setopt(handle, CURLOPT_MAXREDIRS, MAX_REDIRS);
            }
        }
        
        // get header info, if success set handle to content download state
        bool _getHeaderInfoProc(CURL *handle, TaskWrapper& wrapper)
        {
            DownloadTaskCURL& coTask = *wrapper.second;
            CURLcode rc = CURLE_OK;
            do
            {
                long httpResponseCode = 0;
                rc = curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &httpResponseCode);
                if (CURLE_OK != rc)
                {
                    break;
                }
                if (200 != httpResponseCode)
                {
                    char buf[256] = {0};
                    sprintf(buf
                            , "When crequest url(%s) header info, return unexcept http response code(%ld)"
                            , wrapper.first->requestURL.c_str()
                            , httpResponseCode);
                    coTask.setErrorProc(DownloadTask::ERROR_IMPL_INTERNAL, CURLE_OK, buf);
                }
                
//                curl_easy_getinfo(handle, CURLINFO_EFFECTIVE_URL, &effectiveUrl);
//                curl_easy_getinfo(handle, CURLINFO_CONTENT_TYPE, &contentType);
                double contentLen = 0;
                rc = curl_easy_getinfo(handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &contentLen);
                if (CURLE_OK != rc)
                {
                    break;
                }
                
                bool acceptRanges = (string::npos != coTask._header.find("Accept-Ranges")) ? true : false;
                
                // get current file size
                int64_t fileSize = 0;
                if (acceptRanges && coTask._tempFileName.length())
                {
                    fileSize = FileUtils::getInstance()->getFileSize(coTask._tempFileName);
                }

                // set header info to coTask
                lock_guard<mutex> lock(coTask._mutex);
                coTask._totalBytesExpected = (int64_t)contentLen;
                coTask._acceptRanges = acceptRanges;
                if (acceptRanges && fileSize > 0)
                {
                    coTask._totalBytesReceived = fileSize;
                }
                coTask._headerAchieved = true;
            } while (0);
            
            if (CURLE_OK != rc)
            {
                coTask.setErrorProc(DownloadTask::ERROR_IMPL_INTERNAL, rc, curl_easy_strerror(rc));
            }
            return coTask._headerAchieved;
        }
        
        void _threadProc()
        {
            DLLOG("++++DownloaderCURL::Impl::_threadProc begin %p", this);
            // the holder prevent DownloaderCURL::Impl class instance be destruct in main thread
            auto holder = this->shared_from_this();
            auto thisThreadId = this_thread::get_id();
            uint32_t countOfMaxProcessingTasks = this->hints.countOfMaxProcessingTasks;
            // init curl content
            CURLM* curlmHandle = curl_multi_init();
            unordered_map<CURL*, TaskWrapper> coTaskMap;
            int runningHandles = 0;
            CURLMcode mcode = CURLM_OK;
            int rc = 0;                 // select return code
            
            do
            {
                // check the thread should exit or not
                {
                    lock_guard<mutex> lock(_threadMutex);
                    // if the Impl stoped, this->_thread.reset will be called, thus _thread.get_id() not equal with thisThreadId
                    if (thisThreadId != this->_thread.get_id())
                    {
                        break;
                    }
                }

                if (runningHandles)
                {
                    // get timeout setting from multi-handle
                    long timeoutMS = -1;
                    curl_multi_timeout(curlmHandle, &timeoutMS);
                    
                    if(timeoutMS < 0)
                    {
                        timeoutMS = 1000;
                    }
                    
                    /* get file descriptors from the transfers */
                    fd_set fdread;
                    fd_set fdwrite;
                    fd_set fdexcep;
                    int maxfd = -1;
                    
                    FD_ZERO(&fdread);
                    FD_ZERO(&fdwrite);
                    FD_ZERO(&fdexcep);
                    
                    mcode = curl_multi_fdset(curlmHandle, &fdread, &fdwrite, &fdexcep, &maxfd);
                    if (CURLM_OK != mcode)
                    {
                        break;
                    }
                    
                    // do wait action
                    if(maxfd == -1)
                    {
                        this_thread::sleep_for(chrono::milliseconds(timeoutMS));
                        rc = 0;
                    }
                    else
                    {
                        struct timeval timeout;
                        
                        timeout.tv_sec = timeoutMS / 1000;
                        timeout.tv_usec = (timeoutMS % 1000) * 1000;
                        
                        rc = select(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);
                    }
                    
                    if (rc < 0)
                    {
                        DLLOG("    _threadProc: select return unexpect code: %d", rc);
                    }
                }
                
                if (coTaskMap.size())
                {
                    mcode = CURLM_CALL_MULTI_PERFORM;
                    while(CURLM_CALL_MULTI_PERFORM == mcode)
                    {
                        mcode = curl_multi_perform(curlmHandle, &runningHandles);
                    }
                    if (CURLM_OK != mcode)
                    {
                        break;
                    }
                    
                    struct CURLMsg *m;
                    do {
                        int msgq = 0;
                        m = curl_multi_info_read(curlmHandle, &msgq);
                        if(m && (m->msg == CURLMSG_DONE))
                        {
                            CURL *curlHandle = m->easy_handle;
                            CURLcode errCode = m->data.result;

                            TaskWrapper wrapper = coTaskMap[curlHandle];
                            
                            // remove from multi-handle
                            curl_multi_remove_handle(curlmHandle, curlHandle);
                            bool reinited = false;
                            do
                            {
                                if (CURLE_OK != errCode)
                                {
                                    wrapper.second->setErrorProc(DownloadTask::ERROR_IMPL_INTERNAL, errCode, curl_easy_strerror(errCode));
                                    break;
                                }
                                
                                // if the task is content download task, cleanup the handle
                                if (wrapper.second->_headerAchieved)
                                {
                                    break;
                                }
                                
                                // the task is get header task
                                // first, we get info from response
                                if (false == _getHeaderInfoProc(curlHandle, wrapper))
                                {
                                    // the error info has been set in _getHeaderInfoProc
                                    break;
                                }
                                
                                // after get header info success
                                // wrapper.second->_totalBytesReceived inited by local file size
                                // if the local file size equal with the content size from header, the file has downloaded finish
                                if (wrapper.second->_totalBytesReceived &&
                                    wrapper.second->_totalBytesReceived == wrapper.second->_totalBytesExpected)
                                {
                                    // the file has download complete
                                    // break to move this task to finish queue
                                    break;
                                }
                                // reinit curl handle for download content
                                curl_easy_reset(curlHandle);
                                _initCurlHandleProc(curlHandle, wrapper, true);
                                mcode = curl_multi_add_handle(curlmHandle, curlHandle);
                                if (CURLM_OK != mcode)
                                {
                                    wrapper.second->setErrorProc(DownloadTask::ERROR_IMPL_INTERNAL, mcode, curl_multi_strerror(mcode));
                                    break;
                                }
                                reinited = true;
                            } while (0);
                          
                            if (reinited)
                            {
                                continue;
                            }
                            curl_easy_cleanup(curlHandle);
                            DLLOG("    _threadProc task clean cur handle :%p with errCode:%d",  curlHandle, errCode);
                            
                           // remove from coTaskMap
                            coTaskMap.erase(curlHandle);
                            
                            // remove from _processSet
                            {
                                lock_guard<mutex> lock(_processMutex);
                                if (_processSet.end() != _processSet.find(wrapper)) {
                                    _processSet.erase(wrapper);
                                }
                            }
                            
                            // add to finishedQueue
                            {
                                lock_guard<mutex> lock(_finishedMutex);
                                _finishedQueue.push_back(wrapper);
                            }
                        }
                    } while(m);
                }
                
                // process tasks in _requestList
                while (0 == countOfMaxProcessingTasks || coTaskMap.size() < countOfMaxProcessingTasks)
                {
                    // get task wrapper from request queue
                    TaskWrapper wrapper;
                    {
                        lock_guard<mutex> lock(_requestMutex);
                        if (_requestQueue.size())
                        {
                            wrapper = _requestQueue.front();
                            _requestQueue.pop_front();
                        }
                    }
                    
                    // if request queue is empty, the wrapper.first is nullptr
                    if (! wrapper.first)
                    {
                        break;
                    }
                    
                    wrapper.second->initProc();
                    
                    // create curl handle from task and add into curl multi handle
                    CURL* curlHandle = curl_easy_init();
                    
                    if (nullptr == curlHandle)
                    {
                        wrapper.second->setErrorProc(DownloadTask::ERROR_IMPL_INTERNAL, 0, "Alloc curl handle failed.");
                        lock_guard<mutex> lock(_finishedMutex);
                        _finishedQueue.push_back(wrapper);
                        continue;
                    }
                    
                    // init curl handle for get header info
                    _initCurlHandleProc(curlHandle, wrapper);
                    
                    // add curl handle to process list
                    mcode = curl_multi_add_handle(curlmHandle, curlHandle);
                    if (CURLM_OK != mcode)
                    {
                        wrapper.second->setErrorProc(DownloadTask::ERROR_IMPL_INTERNAL, mcode, curl_multi_strerror(mcode));
                        lock_guard<mutex> lock(_finishedMutex);
                        _finishedQueue.push_back(wrapper);
                        continue;
                    }
                    
                    DLLOG("    _threadProc task create curl handle:%p", curlHandle);
                    coTaskMap[curlHandle] = wrapper;
                    lock_guard<mutex> lock(_processMutex);
                    _processSet.insert(wrapper);
                }
            } while (coTaskMap.size());
            
            curl_multi_cleanup(curlmHandle);
            this->stop();
            DLLOG("----DownloaderCURL::Impl::_threadProc end");
        }
        
        thread _thread;
        deque<TaskWrapper>  _requestQueue;
        set<TaskWrapper>    _processSet;
        deque<TaskWrapper>  _finishedQueue;
        
        mutex _threadMutex;
        mutex _requestMutex;
        mutex _processMutex;
        mutex _finishedMutex;
    };
    

////////////////////////////////////////////////////////////////////////////////
//  Implementation DownloaderCURL
    DownloaderCURL::DownloaderCURL(const DownloaderHints& hints)
    : _impl(std::make_shared<Impl>())
    , _currTask(nullptr)
    {
        DLLOG("Construct DownloaderCURL %p", this);
        _impl->hints = hints;
        _scheduler = Director::getInstance()->getScheduler();
        _scheduler->retain();
        
        _transferDataToBuffer = [this](void *buf, int64_t len)->int64_t
        {
            DownloadTaskCURL& coTask = *_currTask;
            int64_t dataLen = coTask._buf.size();
            if (len < dataLen)
            {
                return 0;
            }
            
            memcpy(buf, coTask._buf.data(), dataLen);
            coTask._buf.resize(0);
            return dataLen;
        };
        
        char key[128];
        sprintf(key, "DownloaderCURL(%p)", this);
        _schedulerKey = key;
        
        _scheduler->schedule(bind(&DownloaderCURL::_onSchedule, this, placeholders::_1),
                             this,
                             0.1f,
                             true,
                             _schedulerKey);
    }
    
    DownloaderCURL::~DownloaderCURL()
    {
        _scheduler->unschedule(_schedulerKey, this);
        _scheduler->release();
        
        _impl->stop();
        DLLOG("Destruct DownloaderCURL %p", this);
    }
    
    IDownloadTask *DownloaderCURL::createCoTask(std::shared_ptr<const DownloadTask>& task)
    {
        DownloadTaskCURL *coTask = new DownloadTaskCURL;
        coTask->init(task->storagePath, _impl->hints.tempFileNameSuffix);
        
        DLLOG("    DownloaderCURL: createTask: Id(%d)", coTask->serialId);

        _impl->addTask(task, coTask);
        _impl->run();
        _scheduler->resumeTarget(this);
        return coTask;
    }

    void DownloaderCURL::_onSchedule(float)
    {
        vector<TaskWrapper> tasks;
        
        // update processing tasks
        _impl->getProcessTasks(tasks);
        for (auto& wrapper : tasks)
        {
            const DownloadTask& task = *wrapper.first;
            DownloadTaskCURL& coTask = *wrapper.second;
            
            lock_guard<mutex> lock(coTask._mutex);
            if (coTask._bytesReceived)
            {
                _currTask = &coTask;
                onTaskProgress(task,
                               coTask._bytesReceived,
                               coTask._totalBytesReceived,
                               coTask._totalBytesExpected,
                               _transferDataToBuffer);
                _currTask = nullptr;
                coTask._bytesReceived = 0;
            }
        }
        tasks.resize(0);
        
        // update finished tasks
        _impl->getFinishedTasks(tasks);

        if (_impl->stoped())
        {
            _scheduler->pauseTarget(this);
        }

        for (auto& wrapper : tasks)
        {
            const DownloadTask& task = *wrapper.first;
            DownloadTaskCURL& coTask = *wrapper.second;
            
            // if there is bytesReceived, call progress update first
            if (coTask._bytesReceived)
            {
                _currTask = &coTask;
                onTaskProgress(task,
                               coTask._bytesReceived,
                               coTask._totalBytesReceived,
                               coTask._totalBytesExpected,
                               _transferDataToBuffer);
                coTask._bytesReceived = 0;
                _currTask = nullptr;
            }
            
            // if file task, close file handle and rename file if needed
            if (coTask._fp)
            {
                fclose(coTask._fp);
                coTask._fp = nullptr;
                do
                {
                    if (0 == coTask._fileName.length())
                    {
                        break;
                    }
                    
                    auto util = FileUtils::getInstance();
                    // if file already exist, remove it
                    if (util->isFileExist(coTask._fileName))
                    {
                        if (false == util->removeFile(coTask._fileName))
                        {
                            coTask._errCode = DownloadTask::ERROR_FILE_OP_FAILED;
                            coTask._errCodeInternal = 0;
                            coTask._errDescription = "Can't remove old file: ";
                            coTask._errDescription.append(coTask._fileName);
                            break;
                        }
                    }
                    
                    // rename file
                    if (util->renameFile(coTask._tempFileName, coTask._fileName))
                    {
                        // success, remove storage from set
                        DownloadTaskCURL::_sStoragePathSet.erase(coTask._tempFileName);
                        break;
                    }
                    // failed
                    coTask._errCode = DownloadTask::ERROR_FILE_OP_FAILED;
                    coTask._errCodeInternal = 0;
                    coTask._errDescription = "Can't renamefile from: ";
                    coTask._errDescription.append(coTask._tempFileName);
                    coTask._errDescription.append(" to: ");
                    coTask._errDescription.append(coTask._fileName);
                } while (0);
                
            }
            // needn't lock coTask here, because tasks has removed form _impl
            onTaskFinish(task, coTask._errCode, coTask._errCodeInternal, coTask._errDescription, coTask._buf);
            DLLOG("    DownloaderCURL: finish Task: Id(%d)", coTask.serialId);
        }
    }
    
}}  //  namespace cocos2d::network
