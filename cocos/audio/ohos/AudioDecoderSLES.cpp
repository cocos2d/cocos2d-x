/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#define LOG_TAG "AudioDecoderSLES"

#include "Macros.h"
#include "AudioDecoderSLES.h"
#include "platform/CCFileUtils.h"

#include <mutex>
#include <thread>

namespace cocos2d { namespace experimental {

/* Explicitly requesting SL_IID_ANDROIDSIMPLEBUFFERQUEUE and SL_IID_PREFETCHSTATUS
* on the UrlAudioPlayer object for decoding, SL_IID_METADATAEXTRACTION for retrieving the
* format of the decoded audio */
#define NUM_EXPLICIT_INTERFACES_FOR_PLAYER 3

/* Size of the decode buffer queue */
#define NB_BUFFERS_IN_QUEUE 4

/* size of the struct to retrieve the PCM format metadata values: the values we're interested in
 * are SLuint32, but it is saved in the data field of a SLMetadataInfo, hence the larger size.
 * Nate that this size is queried and displayed at l.452 for demonstration/test purposes.
 *  */
#define PCM_METADATA_VALUE_SIZE 32

/* used to detect errors likely to have occurred when the OpenSL ES framework fails to open
 * a resource, for instance because a file URI is invalid, or an HTTP server doesn't respond.
 */
#define PREFETCHEVENT_ERROR_CANDIDATE (SL_PREFETCHEVENT_STATUSCHANGE | SL_PREFETCHEVENT_FILLLEVELCHANGE)

//-----------------------------------------------------------------

static std::mutex __SLPlayerMutex; //NOLINT(bugprone-reserved-identifier, readability-identifier-naming)

static int toBufferSizeInBytes(int bufferSizeInFrames, int sampleSize, int channelCount) {
    return bufferSizeInFrames * sampleSize * channelCount;
}

static int BUFFER_SIZE_IN_BYTES = 0; // NOLINT(readability-identifier-naming)

static void checkMetaData(int index, const char *key) {
    if (index != -1) {
        ALOGV("Key %s is at index %d", key, index);
    } else {
        ALOGV("Unable to find key %s", key);
    }
}

class SLAudioDecoderCallbackProxy {
public:
    //-----------------------------------------------------------------
    /* Callback for "prefetch" events, here used to detect audio resource opening errors */
    static void prefetchEventCallback(SLPrefetchStatusItf caller, void *context, SLuint32 event) {
        auto *thiz = reinterpret_cast<AudioDecoderSLES *>(context);
        thiz->prefetchCallback(caller, event);
    }

    static void decPlayCallback(CCSLBufferQueueItf queueItf, void *context) {
        auto *thiz = reinterpret_cast<AudioDecoderSLES *>(context);
        thiz->decodeToPcmCallback(queueItf);
    }

    static void decProgressCallback(SLPlayItf caller, void *context, SLuint32 event) {
        auto *thiz = reinterpret_cast<AudioDecoderSLES *>(context);
        thiz->decodeProgressCallback(caller, event);
    }
};

AudioDecoderSLES::AudioDecoderSLES()
: _engineItf(nullptr), _playObj(nullptr), _formatQueried(false), _prefetchError(false), _counter(0), _numChannelsKeyIndex(-1), _sampleRateKeyIndex(-1), _bitsPerSampleKeyIndex(-1), _containerSizeKeyIndex(-1), _channelMaskKeyIndex(-1), _endiannessKeyIndex(-1), _eos(false), _bufferSizeInFrames(-1), _assetFd(0), _fdGetterCallback(nullptr), _isDecodingCallbackInvoked(false) {
    ALOGV("Create AudioDecoderSLES");
}

AudioDecoderSLES::~AudioDecoderSLES() {
    {
        std::lock_guard<std::mutex> lk(__SLPlayerMutex);
        SL_DESTROY_OBJ(_playObj);
    }
    ALOGV("After destroying SL play object");
    if (_assetFd > 0) {
        ALOGV("Closing assetFd: %d", _assetFd);
        ::close(_assetFd);
        _assetFd = 0;
    }
    free(_pcmData);
}

bool AudioDecoderSLES::init(SLEngineItf engineItf, const std::string &url, int bufferSizeInFrames, int sampleRate, const FdGetterCallback &fdGetterCallback) {
    if (AudioDecoder::init(url, sampleRate)) {
        _engineItf = engineItf;
        _bufferSizeInFrames = bufferSizeInFrames;
        _fdGetterCallback = fdGetterCallback;

        BUFFER_SIZE_IN_BYTES = toBufferSizeInBytes(bufferSizeInFrames, 2, 2);
        _pcmData = static_cast<char *>(malloc(NB_BUFFERS_IN_QUEUE * BUFFER_SIZE_IN_BYTES));
        memset(_pcmData, 0x00, NB_BUFFERS_IN_QUEUE * BUFFER_SIZE_IN_BYTES);
        return true;
    }

    return false;
}

bool AudioDecoderSLES::decodeToPcm() {
    // 当前oh不支持，直接返回true
    return true;
}

//-----------------------------------------------------------------
void AudioDecoderSLES::signalEos() {
    std::unique_lock<std::mutex> autoLock(_eosLock);
    _eos = true;
    _eosCondition.notify_one();
}

void AudioDecoderSLES::queryAudioInfo() {
    if (_formatQueried) {
        return;
    }

    SLresult result;
    /* Get duration in callback where we use the callback context for the SLPlayItf*/
    SLmillisecond durationInMsec = SL_TIME_UNKNOWN;
    result = (*_decContext.playItf)->GetDuration(_decContext.playItf, &durationInMsec);
    SL_RETURN_IF_FAILED(result, "decodeProgressCallback,GetDuration failed");

    if (durationInMsec == SL_TIME_UNKNOWN) {
        ALOGV("Content duration is unknown (in dec callback)");
    } else {
        ALOGV("Content duration is %dms (in dec callback)", (int)durationInMsec);
        _result.duration = durationInMsec / 1000.0F;
    }

    /* used to query metadata values */
    SLMetadataInfo pcmMetaData;

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _sampleRateKeyIndex, PCM_METADATA_VALUE_SIZE, &pcmMetaData);

    SL_RETURN_IF_FAILED(result, "%s GetValue _sampleRateKeyIndex failed", __FUNCTION__);
    // Note: here we could verify the following:
    //         pcmMetaData->encoding == SL_CHARACTERENCODING_BINARY
    //         pcmMetaData->size == sizeof(SLuint32)
    //       but the call was successful for the PCM format keys, so those conditions are implied

    _result.sampleRate = *reinterpret_cast<SLuint32 *>(pcmMetaData.data);
    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _numChannelsKeyIndex, PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _numChannelsKeyIndex failed", __FUNCTION__);

    _result.numChannels = *reinterpret_cast<SLuint32 *>(pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _bitsPerSampleKeyIndex, PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _bitsPerSampleKeyIndex failed", __FUNCTION__)
    _result.bitsPerSample = *reinterpret_cast<SLuint32 *>(pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _containerSizeKeyIndex, PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _containerSizeKeyIndex failed", __FUNCTION__)
    _result.containerSize = *reinterpret_cast<SLuint32 *>(pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _channelMaskKeyIndex, PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _channelMaskKeyIndex failed", __FUNCTION__)
    _result.channelMask = *reinterpret_cast<SLuint32 *>(pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _endiannessKeyIndex, PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _endiannessKeyIndex failed", __FUNCTION__)
    _result.endianness = *reinterpret_cast<SLuint32 *>(pcmMetaData.data);

    _formatQueried = true;
}

void AudioDecoderSLES::prefetchCallback(SLPrefetchStatusItf caller, SLuint32 event) {
    SLpermille level = 0;
    SLresult result;
    result = (*caller)->GetFillLevel(caller, &level);
    SL_RETURN_IF_FAILED(result, "GetFillLevel failed");

    SLuint32 status;
    //ALOGV("PrefetchEventCallback: received event %u", event);
    result = (*caller)->GetPrefetchStatus(caller, &status);

    SL_RETURN_IF_FAILED(result, "GetPrefetchStatus failed");

    if ((PREFETCHEVENT_ERROR_CANDIDATE == (event & PREFETCHEVENT_ERROR_CANDIDATE)) && (level == 0) && (status == SL_PREFETCHSTATUS_UNDERFLOW)) {
        ALOGV("PrefetchEventCallback: Error while prefetching data, exiting");
        _prefetchError = true;
        signalEos();
    }
}

/* Callback for "playback" events, i.e. event happening during decoding */
void AudioDecoderSLES::decodeProgressCallback(SLPlayItf caller, SLuint32 event) {
    CC_UNUSED_PARAM(caller);
    if (SL_PLAYEVENT_HEADATEND & event) {
        ALOGV("SL_PLAYEVENT_HEADATEND");
        if (!_isDecodingCallbackInvoked) {
            queryAudioInfo();

            for (int i = 0; i < NB_BUFFERS_IN_QUEUE; ++i) {
                _result.pcmBuffer->insert(_result.pcmBuffer->end(), _decContext.pData,
                                          _decContext.pData + BUFFER_SIZE_IN_BYTES);

                /* Increase data pointer by buffer size */
                _decContext.pData += BUFFER_SIZE_IN_BYTES;
            }
        }
        signalEos();
    }
}

//-----------------------------------------------------------------
/* Callback for decoding buffer queue events */
void AudioDecoderSLES::decodeToPcmCallback(CCSLBufferQueueItf queueItf) {
    _isDecodingCallbackInvoked = true;
    ALOGV("%s ...", __FUNCTION__);
    _counter++;
    SLresult result;
    // IDEA: ??
    if (_counter % 1000 == 0) {
        SLmillisecond msec;
        result = (*_decContext.playItf)->GetPosition(_decContext.playItf, &msec);
        SL_RETURN_IF_FAILED(result, "%s, GetPosition failed", __FUNCTION__);
        ALOGV("%s called (iteration %d): current position=%d ms", __FUNCTION__, _counter, (int)msec);
    }

    _result.pcmBuffer->insert(_result.pcmBuffer->end(), _decContext.pData,
                              _decContext.pData + BUFFER_SIZE_IN_BYTES);

    result = (*queueItf)->Enqueue(queueItf, _decContext.pData, BUFFER_SIZE_IN_BYTES);
    SL_RETURN_IF_FAILED(result, "%s, Enqueue failed", __FUNCTION__);

    /* Increase data pointer by buffer size */
    _decContext.pData += BUFFER_SIZE_IN_BYTES;

    if (_decContext.pData >= _decContext.pDataBase + (NB_BUFFERS_IN_QUEUE * BUFFER_SIZE_IN_BYTES)) {
        _decContext.pData = _decContext.pDataBase;
    }

    // Note: adding a sleep here or any sync point is a way to slow down the decoding, or
    //  synchronize it with some other event, as the OpenSL ES framework will block until the
    //  buffer queue callback return to proceed with the decoding.

#if 0
    /* Example: buffer queue state display */
    SLAndroidSimpleBufferQueueState decQueueState;
    result =(*queueItf)->GetState(queueItf, &decQueueState);
    SL_RETURN_IF_FAILED(result, "decQueueState.GetState failed");

    ALOGV("DecBufferQueueCallback now has _decContext.pData=%p, _decContext.pDataBase=%p, queue: "
                 "count=%u playIndex=%u, count: %d",
         _decContext.pData, _decContext.pDataBase, decQueueState.count, decQueueState.index, _counter);
#endif

#if 0
    /* Example: display position in callback where we use the callback context for the SLPlayItf*/
    SLmillisecond posMsec = SL_TIME_UNKNOWN;
    result = (*_decContext.playItf)->GetPosition(_decContext.playItf, &posMsec);
    SL_RETURN_IF_FAILED(result, "decodeToPcmCallback,GetPosition2 failed");

    if (posMsec == SL_TIME_UNKNOWN) {
        ALOGV("Content position is unknown (in dec callback)");
    } else {
        ALOGV("Content position is %ums (in dec callback)",
                posMsec);
    }
#endif

    queryAudioInfo();
}

}} // namespace cocos2d { namespace experimental