/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __CCASYNCREADER_H__
#define __CCASYNCREADER_H__

#include "cocos2d.h"

namespace cocostudio {

class AsyncReader : cocos2d::Ref
{
public:
    static AsyncReader* getInstance();
    static void destroyInstance();

    AsyncReader();

    virtual void readFileAsync(const std::string &filepath, std::function<Ref*(std::string)> loadingCallBack, std::function<void(cocos2d::Ref*)> loadedCallback);

private:
    void loadFile();
    void loadFileAsyncCallBack(float dt);

public:
    struct AsyncStruct
    {
    public:
        AsyncStruct(const std::string& fn, std::function<Ref*(std::string)> lc, std::function<void(cocos2d::Ref*)> ec) 
            : filename(fn), loadingCallBack(lc), loadedCallback(ec) {}

        std::string filename;
        std::function<Ref*(std::string)>   loadingCallBack;
        std::function<void(cocos2d::Ref*)> loadedCallback;
    };

protected:
    typedef struct _RefInfo
    {
        AsyncStruct *asyncStruct;
        Ref         *ref;
    } RefInfo;

    std::thread* _loadingThread;

    std::queue<AsyncStruct*>* _asyncStructQueue;
    std::deque<RefInfo*>* _refInfoQueue;

    std::mutex _asyncStructQueueMutex;
    std::mutex _refInfoMutex;

    std::mutex _sleepMutex;
    std::condition_variable _sleepCondition;

    bool _needQuit;

    int _asyncRefCount;
};

}

#endif /*__CCASYNCREADER_H__*/