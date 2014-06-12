#include "CCAsyncReader.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace cocostudio {

static AsyncReader* _sharedAsyncReader = nullptr;


AsyncReader* AsyncReader::getInstance()
{
    if (! _sharedAsyncReader)
    {
        _sharedAsyncReader = new AsyncReader();
    }

    return _sharedAsyncReader;
}

void AsyncReader::destroyInstance()
{
    CC_SAFE_DELETE(_sharedAsyncReader);
}

AsyncReader::AsyncReader()
    : _loadingThread(nullptr)
    , _asyncStructQueue(nullptr)
    , _refInfoQueue(nullptr)
    , _needQuit(false)
    , _asyncRefCount(0)
{
}

void AsyncReader::readFileAsync(const std::string &path, std::function<Ref*(std::string)> loadingCallBack, std::function<void(cocos2d::Ref*)> loadedCallback)
{
    Ref *ref = nullptr;

    // lazy init
    if (_asyncStructQueue == nullptr)
    {             
        _asyncStructQueue = new std::queue<AsyncStruct*>();
        _refInfoQueue   = new std::deque<RefInfo*>();        

        // create a new thread to load images
        _loadingThread = new std::thread(&AsyncReader::loadFile, this);

        _needQuit = false;
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->schedule(schedule_selector(AsyncReader::loadFileAsyncCallBack), this, 0, false);
    }

    ++_asyncRefCount;

    // generate async struct
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
    AsyncStruct *data = new AsyncStruct(fullpath, loadingCallBack, loadedCallback);

    // add async struct into queue
    _asyncStructQueueMutex.lock();
    _asyncStructQueue->push(data);
    _asyncStructQueueMutex.unlock();

    _sleepCondition.notify_one();
}


void AsyncReader::loadFile()
{
    AsyncStruct *asyncStruct = nullptr;

    while (true)
    {
        std::queue<AsyncStruct*> *pQueue = _asyncStructQueue;
        _asyncStructQueueMutex.lock();
        if (pQueue->empty())
        {
            _asyncStructQueueMutex.unlock();
            if (_needQuit) {
                break;
            }
            else {
                std::unique_lock<std::mutex> lk(_sleepMutex);
                _sleepCondition.wait(lk);
                continue;
            }
        }
        else
        {
            asyncStruct = pQueue->front();
            pQueue->pop();
            _asyncStructQueueMutex.unlock();
        }        

        Ref *ref = nullptr;

        const std::string& filename = asyncStruct->filename;
        // generate ref      
        ref = asyncStruct->loadingCallBack(filename);
        if (!ref)
            continue;

        ref->retain();

        // generate image info
        RefInfo *refInfo = new RefInfo();
        refInfo->asyncStruct = asyncStruct;
        refInfo->ref = ref;

        // put the image info into the queue
        _refInfoMutex.lock();
        _refInfoQueue->push_back(refInfo);
        _refInfoMutex.unlock();
    }

    if(_asyncStructQueue != nullptr)
    {
        delete _asyncStructQueue;
        _asyncStructQueue = nullptr;
        delete _refInfoQueue;
        _refInfoQueue = nullptr;
    }
}

void AsyncReader::loadFileAsyncCallBack(float dt)
{
    // the image is generated in loading thread
    std::deque<RefInfo*> *refsQueue = _refInfoQueue;

    _refInfoMutex.lock();
    if (refsQueue->empty())
    {
        _refInfoMutex.unlock();
    }
    else
    {
        RefInfo *refInfo = refsQueue->front();
        refsQueue->pop_front();
        _refInfoMutex.unlock();

        AsyncStruct *asyncStruct = refInfo->asyncStruct;
        Ref *ref = refInfo->ref;

        if (asyncStruct->loadedCallback)
        {
            asyncStruct->loadedCallback(ref);
        }

        ref->release();

        delete asyncStruct;
        delete refInfo;

        --_asyncRefCount;
        if (0 == _asyncRefCount)
        {
            Director::getInstance()->getScheduler()->unschedule(schedule_selector(AsyncReader::loadFileAsyncCallBack), this);
        }
    }
}

}