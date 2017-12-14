/*
 * Copyright (C) 2014 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define LOG_TAG "mp3reader"

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <vector>
#include "audio/android/cutils/log.h"

#include "pvmp3decoder_api.h"
#include "audio/android/mp3reader.h"

using namespace std;

static uint32_t U32_AT(const uint8_t *ptr) {
    return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
}

static bool parseHeader(
        uint32_t header, size_t *frame_size,
        uint32_t *out_sampling_rate = NULL, uint32_t *out_channels = NULL ,
        uint32_t *out_bitrate = NULL, uint32_t *out_num_samples = NULL) {
    *frame_size = 0;

    if (out_sampling_rate) {
        *out_sampling_rate = 0;
    }

    if (out_channels) {
        *out_channels = 0;
    }

    if (out_bitrate) {
        *out_bitrate = 0;
    }

    if (out_num_samples) {
        *out_num_samples = 1152;
    }

    if ((header & 0xffe00000) != 0xffe00000) {
        return false;
    }

    unsigned version = (header >> 19) & 3;

    if (version == 0x01) {
        return false;
    }

    unsigned layer = (header >> 17) & 3;

    if (layer == 0x00) {
        return false;
    }

    unsigned bitrate_index = (header >> 12) & 0x0f;

    if (bitrate_index == 0 || bitrate_index == 0x0f) {
        // Disallow "free" bitrate.
        return false;
    }

    unsigned sampling_rate_index = (header >> 10) & 3;

    if (sampling_rate_index == 3) {
        return false;
    }

    static const int kSamplingRateV1[] = { 44100, 48000, 32000 };
    int sampling_rate = kSamplingRateV1[sampling_rate_index];
    if (version == 2 /* V2 */) {
        sampling_rate /= 2;
    } else if (version == 0 /* V2.5 */) {
        sampling_rate /= 4;
    }

    unsigned padding = (header >> 9) & 1;

    if (layer == 3) {
        // layer I

        static const int kBitrateV1[] = {
            32, 64, 96, 128, 160, 192, 224, 256,
            288, 320, 352, 384, 416, 448
        };

        static const int kBitrateV2[] = {
            32, 48, 56, 64, 80, 96, 112, 128,
            144, 160, 176, 192, 224, 256
        };

        int bitrate =
            (version == 3 /* V1 */)
                ? kBitrateV1[bitrate_index - 1]
                : kBitrateV2[bitrate_index - 1];

        if (out_bitrate) {
            *out_bitrate = bitrate;
        }

        *frame_size = (12000 * bitrate / sampling_rate + padding) * 4;

        if (out_num_samples) {
            *out_num_samples = 384;
        }
    } else {
        // layer II or III

        static const int kBitrateV1L2[] = {
            32, 48, 56, 64, 80, 96, 112, 128,
            160, 192, 224, 256, 320, 384
        };

        static const int kBitrateV1L3[] = {
            32, 40, 48, 56, 64, 80, 96, 112,
            128, 160, 192, 224, 256, 320
        };

        static const int kBitrateV2[] = {
            8, 16, 24, 32, 40, 48, 56, 64,
            80, 96, 112, 128, 144, 160
        };

        int bitrate;
        if (version == 3 /* V1 */) {
            bitrate = (layer == 2 /* L2 */)
                ? kBitrateV1L2[bitrate_index - 1]
                : kBitrateV1L3[bitrate_index - 1];

            if (out_num_samples) {
                *out_num_samples = 1152;
            }
        } else {
            // V2 (or 2.5)

            bitrate = kBitrateV2[bitrate_index - 1];
            if (out_num_samples) {
                *out_num_samples = (layer == 1 /* L3 */) ? 576 : 1152;
            }
        }

        if (out_bitrate) {
            *out_bitrate = bitrate;
        }

        if (version == 3 /* V1 */) {
            *frame_size = 144000 * bitrate / sampling_rate + padding;
        } else {
            // V2 or V2.5
            size_t tmp = (layer == 1 /* L3 */) ? 72000 : 144000;
            *frame_size = tmp * bitrate / sampling_rate + padding;
        }
    }

    if (out_sampling_rate) {
        *out_sampling_rate = sampling_rate;
    }

    if (out_channels) {
        int channel_mode = (header >> 6) & 3;

        *out_channels = (channel_mode == 3) ? 1 : 2;
    }

    return true;
}

// Mask to extract the version, layer, sampling rate parts of the MP3 header,
// which should be same for all MP3 frames.
static const uint32_t kMask = 0xfffe0c00;

static ssize_t sourceReadAt(mp3_callbacks *callback, void* source, off64_t offset, void *data, size_t size) {
    int retVal = callback->seek(source, offset, SEEK_SET);
    if (retVal != EXIT_SUCCESS) {
        return 0;
    } else {
       return callback->read(data, 1, size, source);
    }
}

// Resync to next valid MP3 frame in the file.
static bool resync(
        mp3_callbacks *callback, void* source, uint32_t match_header,
        off64_t *inout_pos, uint32_t *out_header) {

    if (*inout_pos == 0) {
        // Skip an optional ID3 header if syncing at the very beginning
        // of the datasource.

        for (;;) {
            uint8_t id3header[10];
            int retVal = sourceReadAt(callback, source, *inout_pos, id3header,
                                      sizeof(id3header));
            if (retVal < (ssize_t)sizeof(id3header)) {
                // If we can't even read these 10 bytes, we might as well bail
                // out, even if there _were_ 10 bytes of valid mp3 audio data...
                return false;
            }

            if (memcmp("ID3", id3header, 3)) {
                break;
            }

            // Skip the ID3v2 header.

            size_t len =
                ((id3header[6] & 0x7f) << 21)
                | ((id3header[7] & 0x7f) << 14)
                | ((id3header[8] & 0x7f) << 7)
                | (id3header[9] & 0x7f);

            len += 10;

            *inout_pos += len;

            ALOGV("skipped ID3 tag, new starting offset is %lld (0x%016llx)",
                    (long long)*inout_pos, (long long)*inout_pos);
        }

    }

    off64_t pos = *inout_pos;
    bool valid = false;

    const int32_t kMaxReadBytes = 1024;
    const int32_t kMaxBytesChecked = 128 * 1024;
    uint8_t buf[kMaxReadBytes];
    ssize_t bytesToRead = kMaxReadBytes;
    ssize_t totalBytesRead = 0;
    ssize_t remainingBytes = 0;
    bool reachEOS = false;
    uint8_t *tmp = buf;

    do {
        if (pos >= (off64_t)(*inout_pos + kMaxBytesChecked)) {
            // Don't scan forever.
            ALOGV("giving up at offset %lld", (long long)pos);
            break;
        }

        if (remainingBytes < 4) {
            if (reachEOS) {
                break;
            } else {
                memcpy(buf, tmp, remainingBytes);
                bytesToRead = kMaxReadBytes - remainingBytes;

                /*
                 * The next read position should start from the end of
                 * the last buffer, and thus should include the remaining
                 * bytes in the buffer.
                 */
                totalBytesRead = sourceReadAt(callback, source, pos + remainingBytes,
                                             buf + remainingBytes, bytesToRead);

                if (totalBytesRead <= 0) {
                    break;
                }
                reachEOS = (totalBytesRead != bytesToRead);
                remainingBytes += totalBytesRead;
                tmp = buf;
                continue;
            }
        }

        uint32_t header = U32_AT(tmp);

        if (match_header != 0 && (header & kMask) != (match_header & kMask)) {
            ++pos;
            ++tmp;
            --remainingBytes;
            continue;
        }

        size_t frame_size;
        uint32_t sample_rate, num_channels, bitrate;
        if (!parseHeader(
                    header, &frame_size,
                    &sample_rate, &num_channels, &bitrate)) {
            ++pos;
            ++tmp;
            --remainingBytes;
            continue;
        }

        // ALOGV("found possible 1st frame at %lld (header = 0x%08x)", (long long)pos, header);
        // We found what looks like a valid frame,
        // now find its successors.

        off64_t test_pos = pos + frame_size;

        valid = true;
        const int FRAME_MATCH_REQUIRED = 3;
        for (int j = 0; j < FRAME_MATCH_REQUIRED; ++j) {
            uint8_t tmp[4];
            ssize_t retval = sourceReadAt(callback, source, test_pos, tmp, sizeof(tmp));
            if (retval < (ssize_t)sizeof(tmp)) {
                valid = false;
                break;
            }

            uint32_t test_header = U32_AT(tmp);

            ALOGV("subsequent header is %08x", test_header);

            if ((test_header & kMask) != (header & kMask)) {
                valid = false;
                break;
            }

            size_t test_frame_size;
            if (!parseHeader(test_header, &test_frame_size)) {
                valid = false;
                break;
            }

            ALOGV("found subsequent frame #%d at %lld", j + 2, (long long)test_pos);
            test_pos += test_frame_size;
        }

        if (valid) {
            *inout_pos = pos;

            if (out_header != NULL) {
                *out_header = header;
            }
        } else {
            ALOGV("no dice, no valid sequence of frames found.");
        }

        ++pos;
        ++tmp;
        --remainingBytes;
    } while (!valid);

    return valid;
}

Mp3Reader::Mp3Reader() : mSource(NULL), mCallback(NULL) {
}

// Initialize the MP3 reader.
bool Mp3Reader::init(mp3_callbacks *callback, void* source) {

    mSource = source;
    mCallback = callback;
    // Open the file.
    // mFp = fopen(file, "rb");
    // if (mFp == NULL) return false;

    // Sync to the first valid frame.
    off64_t pos = 0;
    uint32_t header;
    bool success = resync(callback, source, 0 /*match_header*/, &pos, &header);
    if (!success)
    {
        ALOGE("%s, resync failed", __FUNCTION__);
        return false;
    }

    mCurrentPos  = pos;
    mFixedHeader = header;

    size_t frame_size;
    return parseHeader(header, &frame_size, &mSampleRate,
                       &mNumChannels, &mBitrate);
}

// Get the next valid MP3 frame.
bool Mp3Reader::getFrame(void *buffer, uint32_t *size) {

    size_t frame_size;
    uint32_t bitrate;
    uint32_t num_samples;
    uint32_t sample_rate;
    for (;;) {
        ssize_t n = sourceReadAt(mCallback, mSource, mCurrentPos, buffer, 4);
        if (n < 4) {
            return false;
        }

        uint32_t header = U32_AT((const uint8_t *)buffer);

        if ((header & kMask) == (mFixedHeader & kMask)
            && parseHeader(
                header, &frame_size, &sample_rate, NULL /*out_channels*/,
                &bitrate, &num_samples)) {
            break;
        }

        // Lost sync.
        off64_t pos = mCurrentPos;
        if (!resync(mCallback, mSource, mFixedHeader, &pos, NULL /*out_header*/)) {
            // Unable to resync. Signalling end of stream.
            return false;
        }

        mCurrentPos = pos;

        // Try again with the new position.
    }
    ssize_t n = sourceReadAt(mCallback, mSource, mCurrentPos, buffer, frame_size);
    if (n < (ssize_t)frame_size) {
        return false;
    }

    *size = frame_size;
    mCurrentPos += frame_size;
    return true;
}

// Close the MP3 reader.
void Mp3Reader::close() {
    assert(mCallback != NULL);
    mCallback->close(mSource);
}

Mp3Reader::~Mp3Reader() {
}

enum {
    kInputBufferSize = 10 * 1024,
    kOutputBufferSize = 4608 * 2,
};

int decodeMP3(mp3_callbacks* cb, void* source, std::vector<char>& pcmBuffer, int* numChannels, int* sampleRate, int* numFrames)
{
    // Initialize the config.
    tPVMP3DecoderExternal config;
    config.equalizerType = flat;
    config.crcEnabled = false;

    // Allocate the decoder memory.
    uint32_t memRequirements = pvmp3_decoderMemRequirements();
    void *decoderBuf = malloc(memRequirements);
    assert(decoderBuf != NULL);

    // Initialize the decoder.
    pvmp3_InitDecoder(&config, decoderBuf);

    // Open the input file.
    Mp3Reader mp3Reader;
    bool success = mp3Reader.init(cb, source);
    if (!success) {
        ALOGE("mp3Reader.init: Encountered error reading\n");
        free(decoderBuf);
        return EXIT_FAILURE;
    }

    // Open the output file.
    // SF_INFO sfInfo;
    // memset(&sfInfo, 0, sizeof(SF_INFO));
    // sfInfo.channels = mp3Reader.getNumChannels();
    // sfInfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    // sfInfo.samplerate = mp3Reader.getSampleRate();
    // SNDFILE *handle = sf_open(argv[2], SFM_WRITE, &sfInfo);
    // if (handle == NULL) {
    //     ALOGE("Encountered error writing %s\n", argv[2]);
    //     mp3Reader.close();
    //     free(decoderBuf);
    //     return EXIT_FAILURE;
    // }

    // Allocate input buffer.
    uint8_t *inputBuf = static_cast<uint8_t*>(malloc(kInputBufferSize));
    assert(inputBuf != NULL);

    // Allocate output buffer.
    int16_t *outputBuf = static_cast<int16_t*>(malloc(kOutputBufferSize));
    assert(outputBuf != NULL);

    // Decode loop.
    int retVal = EXIT_SUCCESS;
    while (1) {
        // Read input from the file.
        uint32_t bytesRead;
        bool success = mp3Reader.getFrame(inputBuf, &bytesRead);
        if (!success) break;

        *numChannels = mp3Reader.getNumChannels();
        *sampleRate = mp3Reader.getSampleRate();

        // Set the input config.
        config.inputBufferCurrentLength = bytesRead;
        config.inputBufferMaxLength = 0;
        config.inputBufferUsedLength = 0;
        config.pInputBuffer = inputBuf;
        config.pOutputBuffer = outputBuf;
        config.outputFrameSize = kOutputBufferSize / sizeof(int16_t);

        ERROR_CODE decoderErr;
        decoderErr = pvmp3_framedecoder(&config, decoderBuf);
        if (decoderErr != NO_DECODING_ERROR) {
            ALOGE("Decoder encountered error=%d", decoderErr);
            retVal = EXIT_FAILURE;
            break;
        }

        pcmBuffer.insert(pcmBuffer.end(), (char*)outputBuf, ((char*)outputBuf) + config.outputFrameSize * 2);
        *numFrames += config.outputFrameSize / mp3Reader.getNumChannels();
    }

    // Close input reader and output writer.
    mp3Reader.close();
    // sf_close(handle);

    // Free allocated memory.
    free(inputBuf);
    free(outputBuf);
    free(decoderBuf);

    return retVal;
}
