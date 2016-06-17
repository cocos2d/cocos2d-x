/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.

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

#ifndef COCOS_AUDIOMIXER_CONTROLLER_H
#define COCOS_AUDIOMIXER_CONTROLLER_H

#include "audio/android/utils/Errors.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>

namespace cocos2d {

class Track;
class AudioMixer;

class AudioMixerController
{
public:
//    enum class BufferState
//    {
//        BUSY,
//        EMPTY,
//        FULL
//    };

    struct OutputBuffer
    {
        void* buf;
        size_t size;
//        BufferState state;
    };

    AudioMixerController(int bufferSizeInFrames, int sampleRate, int channelCount);

    ~AudioMixerController();

    bool init();

    bool addTrack(Track* track);
//    void switchBuffers();

//    inline bool hasActiveTracks()
//    {
//        std::lock_guard<std::mutex> lk(_activeTracksMutex);
//        return !_activeTracks.empty();
//    }
//    inline bool isCurrentBufferFull()
//    {
////        std::lock_guard<std::mutex> lk(_switchMutex);
//        return _current->state == BufferState::FULL;
//    }
//
//    inline bool isAllBuffersFull()
//    {
////        std::lock_guard<std::mutex> lk(_switchMutex);
//        return _current->state == BufferState::FULL;// && _next->state == BufferState::FULL && _afterNext->state == BufferState::FULL;
//    }

    bool hasPlayingTacks();

    void pause();
    void resume();
    inline bool isPaused() const { return _isPaused; };

    void mixOneFrame();

    inline OutputBuffer* current() { return _current; }

private:
    void destroy();
//    void mixingThreadLoop();

private:
    int _bufferSizeInFrames;
    int _sampleRate;
    int _channelCount;

//    std::thread* _mixingThread;

//    std::mutex _mixingMutex;
//    std::condition_variable _mixingCondition;

    AudioMixer* _mixer;

    std::mutex _activeTracksMutex;
    std::vector<Track*> _activeTracks;
//    std::mutex _switchMutex;

    OutputBuffer _buffers[1];
    OutputBuffer* _current;
//    OutputBuffer* _next;
//    OutputBuffer* _afterNext;

    OutputBuffer* _mixing;

    std::atomic_bool _isDestroy;
    std::atomic_bool _isPaused;
    std::atomic_bool _isMixingFrame;
};

} // namespace cocos2d {

#endif //COCOS_AUDIOMIXER_CONTROLLER_H
