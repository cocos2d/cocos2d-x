/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "tinysndfile"

#include "audio/android/tinysndfile.h"
#include "audio/android/audio_utils/include/audio_utils/primitives.h"
#include "audio/android/cutils/log.h"

// #ifdef HAVE_STDERR
// #include <stdio.h>
// #endif

#include <string.h>
#include <errno.h>

#ifndef HAVE_STDERR
#define HAVE_STDERR
#endif

#define WAVE_FORMAT_PCM         1
#define WAVE_FORMAT_IEEE_FLOAT  3
#define WAVE_FORMAT_EXTENSIBLE  0xFFFE

static snd_callbacks __defaultCallback;
static int __inited = 0;

struct SNDFILE_ {
    uint8_t *temp;  // realloc buffer used for shrinking 16 bits to 8 bits and byte-swapping
    void *stream;
    size_t bytesPerFrame;
    size_t remaining;   // frames unread for SFM_READ, frames written for SFM_WRITE
    SF_INFO info;
    snd_callbacks callback;
};

static unsigned little2u(unsigned char *ptr)
{
    return (ptr[1] << 8) + ptr[0];
}

static unsigned little4u(unsigned char *ptr)
{
    return (ptr[3] << 24) + (ptr[2] << 16) + (ptr[1] << 8) + ptr[0];
}

static int isLittleEndian()
{
    static const short one = 1;
    return *((const char *) &one) == 1;
}

// "swab" conflicts with OS X <string.h>
static void my_swab(short *ptr, size_t numToSwap)
{
    while (numToSwap > 0) {
        *ptr = little2u((unsigned char *) ptr);
        --numToSwap;
        ++ptr;
    }
}

static void* open_func(const char* path, void* user)
{
    return fopen(path, "rb");
}

static size_t read_func(void *ptr, size_t size, size_t nmemb, void* datasource)
{
    return fread(ptr, size, nmemb, (FILE*)datasource);
}

static int seek_func(void* datasource, long offset, int whence)
{
    return fseek((FILE*)datasource, offset, whence);
}

static int close_func(void* datasource)
{
    return fclose((FILE*)datasource);
}

static long tell_func(void* datasource)
{
    return ftell((FILE*)datasource);
}

static void lazyInit()
{
    if (__inited == 0)
    {
        __defaultCallback.open = open_func;
        __defaultCallback.read = read_func;
        __defaultCallback.seek = seek_func;
        __defaultCallback.close = close_func;
        __defaultCallback.tell = tell_func;
        __inited = 1;
    }
}

SNDFILE *sf_open_read(const char *path, SF_INFO *info, snd_callbacks* cb, void* user)
{
    lazyInit();

    if (path == NULL || info == NULL) {
#ifdef HAVE_STDERR
        ALOGE("path=%p info=%p\n", path, info);
#endif
        return NULL;
    }

    SNDFILE *handle = (SNDFILE *) malloc(sizeof(SNDFILE));
    handle->temp = NULL;

    handle->info.format = SF_FORMAT_WAV;
    if (cb != NULL) {
        handle->callback = *cb;
    } else {
        handle->callback = __defaultCallback;
    }

    void* stream = handle->callback.open(path, user);
    if (stream == NULL) {
#ifdef HAVE_STDERR
        ALOGE("fopen %s failed errno %d\n", path, errno);
#endif
        free(handle);
        return NULL;
    }
    handle->stream = stream;

    // don't attempt to parse all valid forms, just the most common ones
    unsigned char wav[12];
    size_t actual;
    unsigned riffSize;
    size_t remaining;
    int hadFmt = 0;
    int hadData = 0;
    long dataTell = 0L;

    actual = handle->callback.read(wav, sizeof(char), sizeof(wav), stream);
    if (actual < 12) {
#ifdef HAVE_STDERR
        ALOGE("actual %zu < 44\n", actual);
#endif
        goto close;
    }
    if (memcmp(wav, "RIFF", 4)) {
#ifdef HAVE_STDERR
        ALOGE("wav != RIFF\n");
#endif
        goto close;
    }
    riffSize = little4u(&wav[4]);
    if (riffSize < 4) {
#ifdef HAVE_STDERR
        ALOGE("riffSize %u < 4\n", riffSize);
#endif
        goto close;
    }
    if (memcmp(&wav[8], "WAVE", 4)) {
#ifdef HAVE_STDERR
        ALOGE("missing WAVE\n");
#endif
        goto close;
    }
    remaining = riffSize - 4;

    while (remaining >= 8) {
        unsigned char chunk[8];
        actual = handle->callback.read(chunk, sizeof(char), sizeof(chunk), stream);
        if (actual != sizeof(chunk)) {
#ifdef HAVE_STDERR
            ALOGE("actual %zu != %zu\n", actual, sizeof(chunk));
#endif
            goto close;
        }
        remaining -= 8;
        unsigned chunkSize = little4u(&chunk[4]);
        if (chunkSize > remaining) {
#ifdef HAVE_STDERR
            ALOGE("chunkSize %u > remaining %zu\n", chunkSize, remaining);
#endif
            goto close;
        }
        if (!memcmp(&chunk[0], "fmt ", 4)) {
            if (hadFmt) {
#ifdef HAVE_STDERR
                ALOGE("multiple fmt\n");
#endif
                goto close;
            }
            if (chunkSize < 2) {
#ifdef HAVE_STDERR
                ALOGE("chunkSize %u < 2\n", chunkSize);
#endif
                goto close;
            }
            unsigned char fmt[40];
            actual = handle->callback.read(fmt, sizeof(char), 2, stream);
            if (actual != 2) {
#ifdef HAVE_STDERR
                ALOGE("actual %zu != 2\n", actual);
#endif
                goto close;
            }
            unsigned format = little2u(&fmt[0]);
            size_t minSize = 0;
            switch (format) {
                case WAVE_FORMAT_PCM:
                case WAVE_FORMAT_IEEE_FLOAT:
                    minSize = 16;
                    break;
                case WAVE_FORMAT_EXTENSIBLE:
                    minSize = 40;
                    break;
                default:
#ifdef HAVE_STDERR
                    ALOGE("unsupported format %u\n", format);
#endif
                    goto close;
            }
            if (chunkSize < minSize) {
#ifdef HAVE_STDERR
                ALOGE("chunkSize %u < minSize %zu\n", chunkSize, minSize);
#endif
                goto close;
            }
            actual = handle->callback.read(&fmt[2], sizeof(char), minSize - 2, stream);
            if (actual != minSize - 2) {
#ifdef HAVE_STDERR
                ALOGE("actual %zu != %zu\n", actual, minSize - 16);
#endif
                goto close;
            }
            if (chunkSize > minSize) {
                handle->callback.seek(stream, (long) (chunkSize - minSize), SEEK_CUR);
            }
            unsigned channels = little2u(&fmt[2]);
            // FIXME FCC_8
            if (channels != 1 && channels != 2 && channels != 4 && channels != 6 && channels != 8) {
#ifdef HAVE_STDERR
                ALOGE("unsupported channels %u\n", channels);
#endif
                goto close;
            }
            unsigned samplerate = little4u(&fmt[4]);
            if (samplerate == 0) {
#ifdef HAVE_STDERR
                ALOGE("samplerate %u == 0\n", samplerate);
#endif
                goto close;
            }
            // ignore byte rate
            // ignore block alignment
            unsigned bitsPerSample = little2u(&fmt[14]);
            if (bitsPerSample != 8 && bitsPerSample != 16 && bitsPerSample != 24 &&
                bitsPerSample != 32) {
#ifdef HAVE_STDERR
                ALOGE("bitsPerSample %u != 8 or 16 or 24 or 32\n", bitsPerSample);
#endif
                goto close;
            }
            unsigned bytesPerFrame = (bitsPerSample >> 3) * channels;
            handle->bytesPerFrame = bytesPerFrame;
            handle->info.samplerate = samplerate;
            handle->info.channels = channels;
            switch (bitsPerSample) {
                case 8:
                    handle->info.format |= SF_FORMAT_PCM_U8;
                    break;
                case 16:
                    handle->info.format |= SF_FORMAT_PCM_16;
                    break;
                case 24:
                    handle->info.format |= SF_FORMAT_PCM_24;
                    break;
                case 32:
                    if (format == WAVE_FORMAT_IEEE_FLOAT)
                        handle->info.format |= SF_FORMAT_FLOAT;
                    else
                        handle->info.format |= SF_FORMAT_PCM_32;
                    break;
            }
            hadFmt = 1;
        } else if (!memcmp(&chunk[0], "data", 4)) {
            if (!hadFmt) {
#ifdef HAVE_STDERR
                ALOGE("data not preceded by fmt\n");
#endif
                goto close;
            }
            if (hadData) {
#ifdef HAVE_STDERR
                ALOGE("multiple data\n");
#endif
                goto close;
            }
            handle->remaining = chunkSize / handle->bytesPerFrame;
            handle->info.frames = handle->remaining;
            dataTell = handle->callback.tell(stream);
            if (chunkSize > 0) {
                handle->callback.seek(stream, (long) chunkSize, SEEK_CUR);
            }
            hadData = 1;
        } else if (!memcmp(&chunk[0], "fact", 4)) {
            // ignore fact
            if (chunkSize > 0) {
                handle->callback.seek(stream, (long) chunkSize, SEEK_CUR);
            }
        } else {
            // ignore unknown chunk
#ifdef HAVE_STDERR
            ALOGE("ignoring unknown chunk %c%c%c%c\n",
                    chunk[0], chunk[1], chunk[2], chunk[3]);
#endif
            if (chunkSize > 0) {
                handle->callback.seek(stream, (long) chunkSize, SEEK_CUR);
            }
        }
        remaining -= chunkSize;
    }
    if (remaining > 0) {
#ifdef HAVE_STDERR
        ALOGE("partial chunk at end of RIFF, remaining %zu\n", remaining);
#endif
        goto close;
    }
    if (!hadData) {
#ifdef HAVE_STDERR
        ALOGE("missing data\n");
#endif
        goto close;
    }
    (void) handle->callback.seek(stream, dataTell, SEEK_SET);
    *info = handle->info;
    return handle;

close:
    free(handle);
    handle->callback.close(stream);
    return NULL;
}

void sf_close(SNDFILE *handle)
{
    if (handle == NULL)
        return;
    free(handle->temp);
    (void) handle->callback.close(handle->stream);
    free(handle);
}

sf_count_t sf_readf_short(SNDFILE *handle, short *ptr, sf_count_t desiredFrames)
{
    if (handle == NULL || ptr == NULL || !handle->remaining ||
        desiredFrames <= 0) {
        return 0;
    }
    if (handle->remaining < (size_t) desiredFrames) {
        desiredFrames = handle->remaining;
    }
    // does not check for numeric overflow
    size_t desiredBytes = desiredFrames * handle->bytesPerFrame;
    size_t actualBytes;
    void *temp = NULL;
    unsigned format = handle->info.format & SF_FORMAT_SUBMASK;
    if (format == SF_FORMAT_PCM_32 || format == SF_FORMAT_FLOAT || format == SF_FORMAT_PCM_24) {
        temp = malloc(desiredBytes);
        actualBytes = handle->callback.read(temp, sizeof(char), desiredBytes, handle->stream);
    } else {
        actualBytes = handle->callback.read(ptr, sizeof(char), desiredBytes, handle->stream);
    }
    size_t actualFrames = actualBytes / handle->bytesPerFrame;
    handle->remaining -= actualFrames;
    switch (format) {
        case SF_FORMAT_PCM_U8:
            memcpy_to_i16_from_u8(ptr, (unsigned char *) ptr, actualFrames * handle->info.channels);
            break;
        case SF_FORMAT_PCM_16:
            if (!isLittleEndian())
                my_swab(ptr, actualFrames * handle->info.channels);
            break;
        case SF_FORMAT_PCM_32:
            memcpy_to_i16_from_i32(ptr, (const int *) temp, actualFrames * handle->info.channels);
            free(temp);
            break;
        case SF_FORMAT_FLOAT:
            memcpy_to_i16_from_float(ptr, (const float *) temp, actualFrames * handle->info.channels);
            free(temp);
            break;
        case SF_FORMAT_PCM_24:
            memcpy_to_i16_from_p24(ptr, (const uint8_t *) temp, actualFrames * handle->info.channels);
            free(temp);
            break;
        default:
            memset(ptr, 0, actualFrames * handle->info.channels * sizeof(short));
            break;
    }
    return actualFrames;
}

/*
sf_count_t sf_readf_float(SNDFILE *handle, float *ptr, sf_count_t desiredFrames)
{
    if (handle == NULL || ptr == NULL || !handle->remaining ||
        desiredFrames <= 0) {
        return 0;
    }
    if (handle->remaining < (size_t) desiredFrames) {
        desiredFrames = handle->remaining;
    }
    // does not check for numeric overflow
    size_t desiredBytes = desiredFrames * handle->bytesPerFrame;
    size_t actualBytes;
    void *temp = NULL;
    unsigned format = handle->info.format & SF_FORMAT_SUBMASK;
    if (format == SF_FORMAT_PCM_16 || format == SF_FORMAT_PCM_U8 || format == SF_FORMAT_PCM_24) {
        temp = malloc(desiredBytes);
        actualBytes = handle->callback.read(temp, sizeof(char), desiredBytes, handle->stream);
    } else {
        actualBytes = handle->callback.read(ptr, sizeof(char), desiredBytes, handle->stream);
    }
    size_t actualFrames = actualBytes / handle->bytesPerFrame;
    handle->remaining -= actualFrames;
    switch (format) {
        case SF_FORMAT_PCM_U8:
#if 0
            // TODO - implement
            memcpy_to_float_from_u8(ptr, (const unsigned char *) temp,
                                    actualFrames * handle->info.channels);
#endif
            free(temp);
            break;
        case SF_FORMAT_PCM_16:
            memcpy_to_float_from_i16(ptr, (const short *) temp, actualFrames * handle->info.channels);
            free(temp);
            break;
        case SF_FORMAT_PCM_32:
            memcpy_to_float_from_i32(ptr, (const int *) ptr, actualFrames * handle->info.channels);
            break;
        case SF_FORMAT_FLOAT:
            break;
        case SF_FORMAT_PCM_24:
            memcpy_to_float_from_p24(ptr, (const uint8_t *) temp, actualFrames * handle->info.channels);
            free(temp);
            break;
        default:
            memset(ptr, 0, actualFrames * handle->info.channels * sizeof(float));
            break;
    }
    return actualFrames;
}

sf_count_t sf_readf_int(SNDFILE *handle, int *ptr, sf_count_t desiredFrames)
{
    if (handle == NULL || ptr == NULL || !handle->remaining ||
        desiredFrames <= 0) {
        return 0;
    }
    if (handle->remaining < (size_t) desiredFrames) {
        desiredFrames = handle->remaining;
    }
    // does not check for numeric overflow
    size_t desiredBytes = desiredFrames * handle->bytesPerFrame;
    void *temp = NULL;
    unsigned format = handle->info.format & SF_FORMAT_SUBMASK;
    size_t actualBytes;
    if (format == SF_FORMAT_PCM_16 || format == SF_FORMAT_PCM_U8 || format == SF_FORMAT_PCM_24) {
        temp = malloc(desiredBytes);
        actualBytes = handle->callback.read(temp, sizeof(char), desiredBytes, handle->stream);
    } else {
        actualBytes = handle->callback.read(ptr, sizeof(char), desiredBytes, handle->stream);
    }
    size_t actualFrames = actualBytes / handle->bytesPerFrame;
    handle->remaining -= actualFrames;
    switch (format) {
        case SF_FORMAT_PCM_U8:
#if 0
            // TODO - implement
            memcpy_to_i32_from_u8(ptr, (const unsigned char *) temp,
                                  actualFrames * handle->info.channels);
#endif
            free(temp);
            break;
        case SF_FORMAT_PCM_16:
            memcpy_to_i32_from_i16(ptr, (const short *) temp, actualFrames * handle->info.channels);
            free(temp);
            break;
        case SF_FORMAT_PCM_32:
            break;
        case SF_FORMAT_FLOAT:
            memcpy_to_i32_from_float(ptr, (const float *) ptr, actualFrames * handle->info.channels);
            break;
        case SF_FORMAT_PCM_24:
            memcpy_to_i32_from_p24(ptr, (const uint8_t *) temp, actualFrames * handle->info.channels);
            free(temp);
            break;
        default:
            memset(ptr, 0, actualFrames * handle->info.channels * sizeof(int));
            break;
    }
    return actualFrames;
}
 */
