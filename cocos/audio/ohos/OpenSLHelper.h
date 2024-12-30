
#pragma once

#include "cutils/log.h"

#include <SLES/OpenSLES.h>

#include <SLES/OpenSLES_Platform.h>


#include <functional>
#include <string>

#define SL_SAFE_DELETE(obj) \
    if ((obj) != nullptr) { \
        delete (obj);       \
        (obj) = nullptr;    \
    }

#define SL_DESTROY_OBJ(OBJ)     \
    if ((OBJ) != nullptr) {     \
        (*(OBJ))->Destroy(OBJ); \
        (OBJ) = nullptr;        \
    }

#define SL_RETURN_VAL_IF_FAILED(r, rval, ...) \
    if (r != SL_RESULT_SUCCESS) {             \
        ALOGE(__VA_ARGS__);                   \
        return rval;                          \
    }

#define SL_RETURN_IF_FAILED(r, ...) \
    if (r != SL_RESULT_SUCCESS) {   \
        ALOGE(__VA_ARGS__);         \
        return;                     \
    }

#define SL_PRINT_ERROR_IF_FAILED(r, ...) \
    if (r != SL_RESULT_SUCCESS) {        \
        ALOGE(__VA_ARGS__);              \
    }

typedef std::function<int(const std::string &, off_t *start, off_t *length)> FdGetterCallback;

// Copied from OpenSLES_AndroidMetadata.h in android-21
// It's because android-10 doesn't contain this header file
/**
 * Additional metadata keys to be used in SLMetadataExtractionItf:
 *   the ANDROID_KEY_PCMFORMAT_* keys follow the fields of the SLDataFormat_PCM struct, and as such
 *   all values corresponding to these keys are of SLuint32 type, and are defined as the fields
 *   of the same name in SLDataFormat_PCM.  The exception is that sample rate is expressed here
 *   in Hz units, rather than in milliHz units.
 */
#ifndef ANDROID_KEY_PCMFORMAT_NUMCHANNELS
#define ANDROID_KEY_PCMFORMAT_NUMCHANNELS "AndroidPcmFormatNumChannels"
#endif

#ifndef ANDROID_KEY_PCMFORMAT_SAMPLERATE
#define ANDROID_KEY_PCMFORMAT_SAMPLERATE "AndroidPcmFormatSampleRate"
#endif

#ifndef ANDROID_KEY_PCMFORMAT_BITSPERSAMPLE
#define ANDROID_KEY_PCMFORMAT_BITSPERSAMPLE "AndroidPcmFormatBitsPerSample"
#endif

#ifndef ANDROID_KEY_PCMFORMAT_CONTAINERSIZE
#define ANDROID_KEY_PCMFORMAT_CONTAINERSIZE "AndroidPcmFormatContainerSize"
#endif

#ifndef ANDROID_KEY_PCMFORMAT_CHANNELMASK
#define ANDROID_KEY_PCMFORMAT_CHANNELMASK "AndroidPcmFormatChannelMask"
#endif

#ifndef ANDROID_KEY_PCMFORMAT_ENDIANNESS
#define ANDROID_KEY_PCMFORMAT_ENDIANNESS "AndroidPcmFormatEndianness"
#endif

#define clockNow()                     std::chrono::high_resolution_clock::now()
#define intervalInMS(oldTime, newTime) (static_cast<long>(std::chrono::duration_cast<std::chrono::microseconds>((newTime) - (oldTime)).count()) / 1000.f)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
