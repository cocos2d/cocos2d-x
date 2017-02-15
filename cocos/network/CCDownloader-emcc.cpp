/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.

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

#include "network/CCDownloader-emcc.h"
#include "network/CCDownloader.h"
#include "platform/CCFileUtils.h"
#include "emscripten.h"

namespace cocos2d { namespace network {
    
struct DownloadTaskEmcc : public IDownloadTask
{
    DownloadTaskEmcc()
    {
        DLLOG("Construct DownloadTaskEmcc: %p", this);
    }
    virtual  ~DownloadTaskEmcc()
    {
        DLLOG("Destruct DownloadTaskEmcc: %p", this);
    }
    
    int id = 0;
    DownloaderEmcc *downloader = nullptr;
    int64_t lastReceivedDataSize = 0;
    std::shared_ptr<const DownloadTask> task;    // reference to DownloadTask, when task finish, release
};
    
void DownloaderEmcc::onDataLoad(unsigned, void* userData, void *buffer, unsigned bufferSize)
{
    DownloadTaskEmcc* coTask = static_cast<DownloadTaskEmcc*>(userData);
    std::vector<unsigned char> data;
    data.resize(bufferSize);
    memcpy(&data.front(), buffer, bufferSize);
    if (coTask->task->storagePath.length())
    {
        FILE* file = fopen(FileUtils::getInstance()->getSuitableFOpen(coTask->task->storagePath).c_str(), "ab");
        if (nullptr == file)
        {
            coTask->downloader->onTaskFinish(*coTask->task,
                                             DownloadTask::ERROR_FILE_OP_FAILED,
                                             0,
                                             std::string("Can't open file:") + coTask->task->storagePath,
                                             data
                                             );
            return;
        }
        fwrite(buffer, bufferSize, 1, file);
        fclose(file);
    }
    coTask->downloader->_taskMap.erase(coTask->id);
    coTask->downloader->onTaskFinish(*coTask->task,
                 DownloadTask::ERROR_NO_ERROR,
                 0,
                 "",
                 data
                 );
    coTask->task.reset();
    CCLOG("DownloaderEmcc::onDataLoad loaded:%i\n", bufferSize);
};

void DownloaderEmcc::onDataError(unsigned, void* userData, int errorCode, const char* status)
{
    DownloadTaskEmcc* coTask = static_cast<DownloadTaskEmcc*>(userData);
    std::vector<unsigned char> data;
    coTask->downloader->_taskMap.erase(coTask->id);
    coTask->downloader->onTaskFinish(*coTask->task,
                 DownloadTask::ERROR_IMPL_INTERNAL,
                 errorCode,
                 status?status:"",
                 data
                 );
    coTask->task.reset();
    CCLOG("DownloaderEmcc::onDataError code:%i\n", errorCode);
};

void DownloaderEmcc::onDataProgress(unsigned, void* userData, int loaded, int total)
{
    DownloadTaskEmcc* coTask = static_cast<DownloadTaskEmcc*>(userData);
    std::function<int64_t(void*, int64_t)> transferDataToBuffer;
    coTask->downloader->onTaskProgress(*coTask->task, loaded - coTask->lastReceivedDataSize, loaded, total, transferDataToBuffer);
    coTask->lastReceivedDataSize = loaded;
    CCLOG("DownloaderEmcc::onProgress loaded:%i/%i\n", loaded, total);
};

DownloaderEmcc::DownloaderEmcc(const DownloaderHints& hints)
{
    
}

DownloaderEmcc::~DownloaderEmcc()
{
    for(auto &pair : _taskMap)
    {
        emscripten_async_wget2_abort(pair.first);
        pair.second->task.reset();
    }
}
    
IDownloadTask* DownloaderEmcc::createCoTask(std::shared_ptr<const DownloadTask>& task)
{
    DownloadTaskEmcc *coTask = new DownloadTaskEmcc;
    coTask->task = task;
    coTask->downloader = this;
    coTask->id = emscripten_async_wget2_data(
                                             task->requestURL.c_str(),
                                             "GET",
                                             nullptr,
                                             static_cast<void*>(coTask),
                                             true,
                                             &DownloaderEmcc::onDataLoad,
                                             &DownloaderEmcc::onDataError,
                                             &DownloaderEmcc::onDataProgress
                                             );
    
    DLLOG("DownloaderEmcc::createCoTask id: %d", coTask->id);
    _taskMap.insert(std::make_pair(coTask->id, coTask));
    return coTask;
}

} }  // namespace cocos2d::network
