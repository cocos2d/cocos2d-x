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

#pragma once

#include "audio/android/OpenSLHelper.h"
#include "audio/android/PcmData.h"

#include <mutex>
#include <condition_variable>

namespace cocos2d { namespace experimental {

class AudioDecoder
{
public:
    AudioDecoder(SLEngineItf engineItf, const std::string &url, int bufferSizeInFrames, int sampleRate, const FdGetterCallback &fdGetterCallback);

    virtual ~AudioDecoder();

    bool start();

    inline PcmData getResult()
    { return _result; };

private:
    bool decodeToPcm();
    bool resample();
    bool interleave();
    void queryAudioInfo();

    void signalEos();
    void decodeToPcmCallback(SLAndroidSimpleBufferQueueItf queueItf);
    void prefetchCallback(SLPrefetchStatusItf caller, SLuint32 event);
    void decodeProgressCallback(SLPlayItf caller, SLuint32 event);

private:
    SLEngineItf _engineItf;
    std::string _url;
    PcmData _result;

    SLObjectItf _playObj;
    /* Local storage for decoded audio data */
    char* _pcmData;

    /* we only want to query / display the PCM format once */
    bool _formatQueried;
    /* Used to signal prefetching failures */
    bool _prefetchError;

    /* to display the number of decode iterations */
    int _counter;

    /* metadata key index for the PCM format information we want to retrieve */
    int _numChannelsKeyIndex;
    int _sampleRateKeyIndex;
    int _bitsPerSampleKeyIndex;
    int _containerSizeKeyIndex;
    int _channelMaskKeyIndex;
    int _endiannessKeyIndex;

    /* to signal to the test app the end of the stream to decode has been reached */
    bool _eos;
    std::mutex _eosLock;
    std::condition_variable _eosCondition;

    /* Structure for passing information to callback function */
    typedef struct CallbackCntxt_
    {
        SLPlayItf playItf;
        SLMetadataExtractionItf metaItf;
        SLuint32 size;
        SLint8 *pDataBase;    // Base address of local audio data storage
        SLint8 *pData;        // Current address of local audio data storage
    } CallbackCntxt;

    CallbackCntxt _decContext;
    int _bufferSizeInFrames;
    int _sampleRate;
    int _assetFd;
    FdGetterCallback _fdGetterCallback;
    bool _isDecodingCallbackInvoked;

    friend class SLAudioDecoderCallbackProxy;
};

}} // namespace cocos2d { namespace experimental {
