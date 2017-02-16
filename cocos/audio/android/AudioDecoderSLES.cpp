/****************************************************************************
Copyright (c) 2017 Chukong Technologies Inc.

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

#include "audio/android/AudioDecoderSLES.h"
#include "platform/CCFileUtils.h"

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

static std::mutex __SLPlayerMutex;

static int toBufferSizeInBytes(int bufferSizeInFrames, int sampleSize, int channelCount)
{
    return bufferSizeInFrames * sampleSize * channelCount;
}

static int BUFFER_SIZE_IN_BYTES = 0;

static void checkMetaData(int index, const char *key)
{
    if (index != -1)
    {
        ALOGV("Key %s is at index %d", key, index);
    }
    else
    {
        ALOGE("Unable to find key %s", key);
    }
}

class SLAudioDecoderCallbackProxy
{
public:
    //-----------------------------------------------------------------
    /* Callback for "prefetch" events, here used to detect audio resource opening errors */
    static void prefetchEventCallback(SLPrefetchStatusItf caller, void *context, SLuint32 event)
    {
        AudioDecoderSLES *thiz = reinterpret_cast<AudioDecoderSLES *>(context);
        thiz->prefetchCallback(caller, event);
    }

    static void decPlayCallback(SLAndroidSimpleBufferQueueItf queueItf, void *context)
    {
        AudioDecoderSLES *thiz = reinterpret_cast<AudioDecoderSLES *>(context);
        thiz->decodeToPcmCallback(queueItf);
    }

    static void decProgressCallback(SLPlayItf caller, void *context, SLuint32 event)
    {
        AudioDecoderSLES *thiz = reinterpret_cast<AudioDecoderSLES *>(context);
        thiz->decodeProgressCallback(caller, event);
    }
};

AudioDecoderSLES::AudioDecoderSLES()
    : _engineItf(nullptr), _playObj(nullptr), _formatQueried(false),
      _prefetchError(false), _counter(0), _numChannelsKeyIndex(-1), _sampleRateKeyIndex(-1),
      _bitsPerSampleKeyIndex(-1), _containerSizeKeyIndex(-1), _channelMaskKeyIndex(-1),
      _endiannessKeyIndex(-1), _eos(false), _bufferSizeInFrames(-1),
      _assetFd(0), _fdGetterCallback(nullptr), _isDecodingCallbackInvoked(false)
{
    ALOGV("Create AudioDecoderSLES");
}

AudioDecoderSLES::~AudioDecoderSLES()
{
    {
        std::lock_guard<std::mutex> lk(__SLPlayerMutex);
        SL_DESTROY_OBJ(_playObj);
    }
    ALOGV("After destroying SL play object");
    if (_assetFd > 0)
    {
        ALOGV("Closing assetFd: %d", _assetFd);
        ::close(_assetFd);
        _assetFd = 0;
    }
    free(_pcmData);
}

bool AudioDecoderSLES::init(SLEngineItf engineItf, const std::string &url, int bufferSizeInFrames, int sampleRate, const FdGetterCallback &fdGetterCallback)
{
    if (AudioDecoder::init(url, sampleRate))
    {
        _engineItf = engineItf;
        _bufferSizeInFrames = bufferSizeInFrames;
        _fdGetterCallback = fdGetterCallback;

        BUFFER_SIZE_IN_BYTES = toBufferSizeInBytes(bufferSizeInFrames, 2, 2);
        _pcmData = (char*) malloc(NB_BUFFERS_IN_QUEUE * BUFFER_SIZE_IN_BYTES);
        memset(_pcmData, 0x00, NB_BUFFERS_IN_QUEUE * BUFFER_SIZE_IN_BYTES);
        return true;
    }

    return false;
}

bool AudioDecoderSLES::decodeToPcm()
{
   SLresult result;

    /* Objects this application uses: one audio player */
    SLObjectItf player;

    /* Interfaces for the audio player */
    SLAndroidSimpleBufferQueueItf decBuffQueueItf;
    SLPrefetchStatusItf prefetchItf;
    SLPlayItf playItf;
    SLMetadataExtractionItf mdExtrItf;

    /* Source of audio data for the decoding */
    SLDataSource decSource;

    // decUri & locFd should be defined here
    SLDataLocator_URI decUri;
    SLDataLocator_AndroidFD locFd;

    /* Data sink for decoded audio */
    SLDataSink decDest;
    SLDataLocator_AndroidSimpleBufferQueue decBuffQueue;
    SLDataFormat_PCM pcm;

    SLboolean required[NUM_EXPLICIT_INTERFACES_FOR_PLAYER];
    SLInterfaceID iidArray[NUM_EXPLICIT_INTERFACES_FOR_PLAYER];

    /* Initialize arrays required[] and iidArray[] */
    for (int i = 0; i < NUM_EXPLICIT_INTERFACES_FOR_PLAYER; i++)
    {
        required[i] = SL_BOOLEAN_FALSE;
        iidArray[i] = SL_IID_NULL;
    }

    /* ------------------------------------------------------ */
    /* Configuration of the player  */

    /* Request the AndroidSimpleBufferQueue interface */
    required[0] = SL_BOOLEAN_TRUE;
    iidArray[0] = SL_IID_ANDROIDSIMPLEBUFFERQUEUE;
    /* Request the PrefetchStatus interface */
    required[1] = SL_BOOLEAN_TRUE;
    iidArray[1] = SL_IID_PREFETCHSTATUS;
    /* Request the PrefetchStatus interface */
    required[2] = SL_BOOLEAN_TRUE;
    iidArray[2] = SL_IID_METADATAEXTRACTION;

    SLDataFormat_MIME formatMime = {SL_DATAFORMAT_MIME, nullptr, SL_CONTAINERTYPE_UNSPECIFIED};
    decSource.pFormat = &formatMime;

    if (_url[0] != '/')
    {
        off_t start = 0, length = 0;
        std::string relativePath;
        size_t position = _url.find("assets/");

        if (0 == position)
        {
            // "assets/" is at the beginning of the path and we don't want it
            relativePath = _url.substr(strlen("assets/"));
        } else
        {
            relativePath = _url;
        }

        _assetFd = _fdGetterCallback(relativePath, &start, &length);

        if (_assetFd <= 0)
        {
            ALOGE("Failed to open file descriptor for '%s'", _url.c_str());
            return false;
        }

        // configure audio source
        locFd = {SL_DATALOCATOR_ANDROIDFD, _assetFd, start, length};

        decSource.pLocator = &locFd;
    }
    else
    {
        decUri = {SL_DATALOCATOR_URI, (SLchar *) _url.c_str()};
        decSource.pLocator = &decUri;
    }

    /* Setup the data sink */
    decBuffQueue.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
    decBuffQueue.numBuffers = NB_BUFFERS_IN_QUEUE;
    /*    set up the format of the data in the buffer queue */
    pcm.formatType = SL_DATAFORMAT_PCM;
    // FIXME valid value required but currently ignored
    pcm.numChannels = 2;
    pcm.samplesPerSec = SL_SAMPLINGRATE_44_1;
    pcm.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
    pcm.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    pcm.channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;

    decDest.pLocator = (void *) &decBuffQueue;
    decDest.pFormat = (void *) &pcm;

    {
        std::lock_guard<std::mutex> lk(__SLPlayerMutex);
        /* Create the audio player */
        result = (*_engineItf)->CreateAudioPlayer(_engineItf, &player, &decSource, &decDest,
                                                  NUM_EXPLICIT_INTERFACES_FOR_PLAYER, iidArray,
                                                  required);
        SL_RETURN_VAL_IF_FAILED(result, false, "CreateAudioPlayer failed");

        _playObj = player;
        /* Realize the player in synchronous mode. */
        result = (*player)->Realize(player, SL_BOOLEAN_FALSE);
        SL_RETURN_VAL_IF_FAILED(result, false, "Realize failed");
    }

    /* Get the play interface which is implicit */
    result = (*player)->GetInterface(player, SL_IID_PLAY, (void *) &playItf);
    SL_RETURN_VAL_IF_FAILED(result, false, "GetInterface SL_IID_PLAY failed");

    /* Set up the player callback to get events during the decoding */
    // FIXME currently ignored
    result = (*playItf)->SetMarkerPosition(playItf, 2000);
    SL_RETURN_VAL_IF_FAILED(result, false, "SetMarkerPosition failed");

    result = (*playItf)->SetPositionUpdatePeriod(playItf, 500);
    SL_RETURN_VAL_IF_FAILED(result, false, "SetPositionUpdatePeriod failed");
    result = (*playItf)->SetCallbackEventsMask(playItf,
                                               SL_PLAYEVENT_HEADATMARKER |
                                               SL_PLAYEVENT_HEADATNEWPOS | SL_PLAYEVENT_HEADATEND);
    SL_RETURN_VAL_IF_FAILED(result, false, "SetCallbackEventsMask failed");
    result = (*playItf)->RegisterCallback(playItf, SLAudioDecoderCallbackProxy::decProgressCallback,
                                          this);
    SL_RETURN_VAL_IF_FAILED(result, false, "RegisterCallback failed");
    ALOGV("Play callback registered");


    /* Get the buffer queue interface which was explicitly requested */
    result = (*player)->GetInterface(player, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
                                     (void *) &decBuffQueueItf);
    SL_RETURN_VAL_IF_FAILED(result, false, "GetInterface SL_IID_ANDROIDSIMPLEBUFFERQUEUE failed");

    /* Get the prefetch status interface which was explicitly requested */
    result = (*player)->GetInterface(player, SL_IID_PREFETCHSTATUS, (void *) &prefetchItf);
    SL_RETURN_VAL_IF_FAILED(result, false, "GetInterface SL_IID_PREFETCHSTATUS failed");

    /* Get the metadata extraction interface which was explicitly requested */
    result = (*player)->GetInterface(player, SL_IID_METADATAEXTRACTION, (void *) &mdExtrItf);
    SL_RETURN_VAL_IF_FAILED(result, false, "GetInterface SL_IID_METADATAEXTRACTION failed");

    /* ------------------------------------------------------ */
    /* Initialize the callback and its context for the decoding buffer queue */
    _decContext.playItf = playItf;
    _decContext.metaItf = mdExtrItf;
    _decContext.pDataBase = (int8_t *) _pcmData;
    _decContext.pData = _decContext.pDataBase;
    _decContext.size = NB_BUFFERS_IN_QUEUE * BUFFER_SIZE_IN_BYTES;

    result = (*decBuffQueueItf)->RegisterCallback(decBuffQueueItf,
                                                  SLAudioDecoderCallbackProxy::decPlayCallback,
                                                  this);
    SL_RETURN_VAL_IF_FAILED(result, false, "decBuffQueueItf RegisterCallback failed");

    /* Enqueue buffers to map the region of memory allocated to store the decoded data */
//    ALOGV("Enqueueing buffer ");
    for (int i = 0; i < NB_BUFFERS_IN_QUEUE; i++)
    {
        result = (*decBuffQueueItf)->Enqueue(decBuffQueueItf, _decContext.pData,
                                             BUFFER_SIZE_IN_BYTES);
        SL_RETURN_VAL_IF_FAILED(result, false, "Enqueue failed");
        _decContext.pData += BUFFER_SIZE_IN_BYTES;
    }

    _decContext.pData = _decContext.pDataBase;

    /* ------------------------------------------------------ */
    /* Initialize the callback for prefetch errors, if we can't open the resource to decode */
    result = (*prefetchItf)->RegisterCallback(prefetchItf,
                                              SLAudioDecoderCallbackProxy::prefetchEventCallback,
                                              this);
    SL_RETURN_VAL_IF_FAILED(result, false, "prefetchItf RegisterCallback failed");

    result = (*prefetchItf)->SetCallbackEventsMask(prefetchItf, PREFETCHEVENT_ERROR_CANDIDATE);
    SL_RETURN_VAL_IF_FAILED(result, false, "prefetchItf SetCallbackEventsMask failed");

    /* ------------------------------------------------------ */
    /* Prefetch the data so we can get information about the format before starting to decode */
    /*     1/ cause the player to prefetch the data */
    result = (*playItf)->SetPlayState(playItf, SL_PLAYSTATE_PAUSED);
    SL_RETURN_VAL_IF_FAILED(result, false, "SetPlayState SL_PLAYSTATE_PAUSED failed");

    /*     2/ block until data has been prefetched */
    SLuint32 prefetchStatus = SL_PREFETCHSTATUS_UNDERFLOW;
    SLuint32 timeOutIndex = 1000; //cjh time out prefetching after 2s
    while ((prefetchStatus != SL_PREFETCHSTATUS_SUFFICIENTDATA) && (timeOutIndex > 0) &&
           !_prefetchError)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        (*prefetchItf)->GetPrefetchStatus(prefetchItf, &prefetchStatus);
        timeOutIndex--;
    }
    if (timeOutIndex == 0 || _prefetchError)
    {
        ALOGE("Failure to prefetch data in time, exiting");
        SL_RETURN_VAL_IF_FAILED(SL_RESULT_CONTENT_NOT_FOUND, false,
                                "Failure to prefetch data in time");
    }

    /* ------------------------------------------------------ */
    /* Display duration */
    SLmillisecond durationInMsec = SL_TIME_UNKNOWN;
    result = (*playItf)->GetDuration(playItf, &durationInMsec);
    SL_RETURN_VAL_IF_FAILED(result, false, "GetDuration failed");

    if (durationInMsec == SL_TIME_UNKNOWN)
    {
        ALOGV("Content duration is unknown");
    } else
    {
        ALOGV("Content duration is %dms", (int)durationInMsec);
    }

    /* ------------------------------------------------------ */
    /* Display the metadata obtained from the decoder */
    //   This is for test / demonstration purposes only where we discover the key and value sizes
    //   of a PCM decoder. An application that would want to directly get access to those values
    //   can make assumptions about the size of the keys and their matching values (all SLuint32)
    SLuint32 itemCount;
    result = (*mdExtrItf)->GetItemCount(mdExtrItf, &itemCount);
    SLuint32 i, keySize, valueSize;
    SLMetadataInfo *keyInfo, *value;
    for (i = 0; i < itemCount; i++)
    {
        keyInfo = nullptr;
        keySize = 0;
        value = nullptr;
        valueSize = 0;
        result = (*mdExtrItf)->GetKeySize(mdExtrItf, i, &keySize);
        SL_RETURN_VAL_IF_FAILED(result, false, "GetKeySize(%d) failed", (int)i);

        result = (*mdExtrItf)->GetValueSize(mdExtrItf, i, &valueSize);
        SL_RETURN_VAL_IF_FAILED(result, false, "GetValueSize(%d) failed", (int)i);

        keyInfo = (SLMetadataInfo *) malloc(keySize);
        if (nullptr != keyInfo)
        {
            result = (*mdExtrItf)->GetKey(mdExtrItf, i, keySize, keyInfo);

            SL_RETURN_VAL_IF_FAILED(result, false, "GetKey(%d) failed", (int)i);

            ALOGV("key[%d] size=%d, name=%s, value size=%d",
                  (int)i, (int)keyInfo->size, keyInfo->data, (int)valueSize);
            /* find out the key index of the metadata we're interested in */
            if (!strcmp((char *) keyInfo->data, ANDROID_KEY_PCMFORMAT_NUMCHANNELS))
            {
                _numChannelsKeyIndex = i;
            } else if (!strcmp((char *) keyInfo->data, ANDROID_KEY_PCMFORMAT_SAMPLERATE))
            {
                _sampleRateKeyIndex = i;
            } else if (!strcmp((char *) keyInfo->data, ANDROID_KEY_PCMFORMAT_BITSPERSAMPLE))
            {
                _bitsPerSampleKeyIndex = i;
            } else if (!strcmp((char *) keyInfo->data, ANDROID_KEY_PCMFORMAT_CONTAINERSIZE))
            {
                _containerSizeKeyIndex = i;
            } else if (!strcmp((char *) keyInfo->data, ANDROID_KEY_PCMFORMAT_CHANNELMASK))
            {
                _channelMaskKeyIndex = i;
            } else if (!strcmp((char *) keyInfo->data, ANDROID_KEY_PCMFORMAT_ENDIANNESS))
            {
                _endiannessKeyIndex = i;
            }
            free(keyInfo);
        }
    }

    checkMetaData(_numChannelsKeyIndex, ANDROID_KEY_PCMFORMAT_NUMCHANNELS);
    checkMetaData(_sampleRateKeyIndex, ANDROID_KEY_PCMFORMAT_SAMPLERATE);
    checkMetaData(_bitsPerSampleKeyIndex, ANDROID_KEY_PCMFORMAT_BITSPERSAMPLE);
    checkMetaData(_containerSizeKeyIndex, ANDROID_KEY_PCMFORMAT_CONTAINERSIZE);
    checkMetaData(_channelMaskKeyIndex, ANDROID_KEY_PCMFORMAT_CHANNELMASK);
    checkMetaData(_endiannessKeyIndex, ANDROID_KEY_PCMFORMAT_ENDIANNESS);

    /* ------------------------------------------------------ */
    /* Start decoding */
    result = (*playItf)->SetPlayState(playItf, SL_PLAYSTATE_PLAYING);
    SL_RETURN_VAL_IF_FAILED(result, false, "SetPlayState SL_PLAYSTATE_PLAYING failed");

    ALOGV("Starting to decode");

    /* Decode until the end of the stream is reached */
    {
        std::unique_lock<std::mutex> autoLock(_eosLock);
        while (!_eos)
        {
            _eosCondition.wait(autoLock);
        }
    }
    ALOGV("EOS signaled");

    /* ------------------------------------------------------ */
    /* End of decoding */

    /* Stop decoding */
    result = (*playItf)->SetPlayState(playItf, SL_PLAYSTATE_STOPPED);
    SL_RETURN_VAL_IF_FAILED(result, false, "SetPlayState SL_PLAYSTATE_STOPPED failed");

    ALOGV("Stopped decoding");

    /* Destroy the UrlAudioPlayer object */
    {
        std::lock_guard<std::mutex> lk(__SLPlayerMutex);
        SL_DESTROY_OBJ(_playObj);
    }

    ALOGV("After destroy player ...");

    _result.numFrames =
            _result.pcmBuffer->size() / _result.numChannels / (_result.bitsPerSample / 8);

    std::string info = _result.toString();
    ALOGI("Original audio info: %s, total size: %d", info.c_str(), (int)_result.pcmBuffer->size());
    return true;
}

//-----------------------------------------------------------------
void AudioDecoderSLES::signalEos()
{
    std::unique_lock<std::mutex> autoLock(_eosLock);
    _eos = true;
    _eosCondition.notify_one();
}

void AudioDecoderSLES::queryAudioInfo()
{
    if (_formatQueried)
    {
        return;
    }

    SLresult result;
    /* Get duration in callback where we use the callback context for the SLPlayItf*/
    SLmillisecond durationInMsec = SL_TIME_UNKNOWN;
    result = (*_decContext.playItf)->GetDuration(_decContext.playItf, &durationInMsec);
    SL_RETURN_IF_FAILED(result, "decodeProgressCallback,GetDuration failed");

    if (durationInMsec == SL_TIME_UNKNOWN)
    {
        ALOGV("Content duration is unknown (in dec callback)");
    } else
    {
        ALOGV("Content duration is %dms (in dec callback)", (int)durationInMsec);
        _result.duration = durationInMsec / 1000.0f;
    }

    /* used to query metadata values */
    SLMetadataInfo pcmMetaData;

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _sampleRateKeyIndex,
                                              PCM_METADATA_VALUE_SIZE, &pcmMetaData);

    SL_RETURN_IF_FAILED(result, "%s GetValue _sampleRateKeyIndex failed", __FUNCTION__);
    // Note: here we could verify the following:
    //         pcmMetaData->encoding == SL_CHARACTERENCODING_BINARY
    //         pcmMetaData->size == sizeof(SLuint32)
    //       but the call was successful for the PCM format keys, so those conditions are implied

    _result.sampleRate = *((SLuint32 *) pcmMetaData.data);
    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _numChannelsKeyIndex,
                                              PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _numChannelsKeyIndex failed", __FUNCTION__);

    _result.numChannels = *((SLuint32 *) pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _bitsPerSampleKeyIndex,
                                              PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _bitsPerSampleKeyIndex failed", __FUNCTION__)
    _result.bitsPerSample = *((SLuint32 *) pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _containerSizeKeyIndex,
                                              PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _containerSizeKeyIndex failed", __FUNCTION__)
    _result.containerSize = *((SLuint32 *) pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _channelMaskKeyIndex,
                                              PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _channelMaskKeyIndex failed", __FUNCTION__)
    _result.channelMask = *((SLuint32 *) pcmMetaData.data);

    result = (*_decContext.metaItf)->GetValue(_decContext.metaItf, _endiannessKeyIndex,
                                              PCM_METADATA_VALUE_SIZE, &pcmMetaData);
    SL_RETURN_IF_FAILED(result, "%s GetValue _endiannessKeyIndex failed", __FUNCTION__)
    _result.endianness = *((SLuint32 *) pcmMetaData.data);

    _formatQueried = true;
}

void AudioDecoderSLES::prefetchCallback(SLPrefetchStatusItf caller, SLuint32 event)
{
    SLpermille level = 0;
    SLresult result;
    result = (*caller)->GetFillLevel(caller, &level);
    SL_RETURN_IF_FAILED(result, "GetFillLevel failed");

    SLuint32 status;
    //ALOGV("PrefetchEventCallback: received event %u", event);
    result = (*caller)->GetPrefetchStatus(caller, &status);

    SL_RETURN_IF_FAILED(result, "GetPrefetchStatus failed");

    if ((PREFETCHEVENT_ERROR_CANDIDATE == (event & PREFETCHEVENT_ERROR_CANDIDATE))
        && (level == 0) && (status == SL_PREFETCHSTATUS_UNDERFLOW))
    {
        ALOGV("PrefetchEventCallback: Error while prefetching data, exiting");
        _prefetchError = true;
        signalEos();
    }
}

/* Callback for "playback" events, i.e. event happening during decoding */
void AudioDecoderSLES::decodeProgressCallback(SLPlayItf caller, SLuint32 event)
{
    if (SL_PLAYEVENT_HEADATEND & event)
    {
        ALOGV("SL_PLAYEVENT_HEADATEND");
        if (!_isDecodingCallbackInvoked)
        {
            queryAudioInfo();

            for (int i = 0; i < NB_BUFFERS_IN_QUEUE; ++i)
            {
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
void AudioDecoderSLES::decodeToPcmCallback(SLAndroidSimpleBufferQueueItf queueItf)
{
    _isDecodingCallbackInvoked = true;
    ALOGV("%s ...", __FUNCTION__);
    _counter++;
    SLresult result;
    // FIXME: ??
    if (_counter % 1000 == 0)
    {
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

    if (_decContext.pData >= _decContext.pDataBase + (NB_BUFFERS_IN_QUEUE * BUFFER_SIZE_IN_BYTES))
    {
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

}} // namespace cocos2d { namespace experimental {