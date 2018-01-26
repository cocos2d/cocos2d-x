/*
 * Copyright (C) 2014 The Android Open Source Project
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

/* #define LOG_NDEBUG 0 */
#define LOG_TAG "audio_utils_format"

#include "audio/android/cutils/log.h"
#include "audio/android/audio_utils/include/audio_utils/primitives.h"
#include "audio/android/audio_utils/include/audio_utils/format.h"
#include "audio/android/audio.h"

void memcpy_by_audio_format(void *dst, audio_format_t dst_format,
        const void *src, audio_format_t src_format, size_t count)
{
    /* default cases for error falls through to fatal log below. */
    if (dst_format == src_format) {
        switch (dst_format) {
        case AUDIO_FORMAT_PCM_16_BIT:
        case AUDIO_FORMAT_PCM_FLOAT:
        case AUDIO_FORMAT_PCM_8_BIT:
        case AUDIO_FORMAT_PCM_24_BIT_PACKED:
        case AUDIO_FORMAT_PCM_32_BIT:
        case AUDIO_FORMAT_PCM_8_24_BIT:
            memcpy(dst, src, count * audio_bytes_per_sample(dst_format));
            return;
        default:
            break;
        }
    }
    switch (dst_format) {
    case AUDIO_FORMAT_PCM_16_BIT:
        switch (src_format) {
        case AUDIO_FORMAT_PCM_FLOAT:
            memcpy_to_i16_from_float((int16_t*)dst, (float*)src, count);
            return;
        case AUDIO_FORMAT_PCM_8_BIT:
            memcpy_to_i16_from_u8((int16_t*)dst, (uint8_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_24_BIT_PACKED:
            memcpy_to_i16_from_p24((int16_t*)dst, (uint8_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_32_BIT:
            memcpy_to_i16_from_i32((int16_t*)dst, (int32_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_8_24_BIT:
            memcpy_to_i16_from_q8_23((int16_t*)dst, (int32_t*)src, count);
            return;
        default:
            break;
        }
        break;
    case AUDIO_FORMAT_PCM_FLOAT:
        switch (src_format) {
        case AUDIO_FORMAT_PCM_16_BIT:
            memcpy_to_float_from_i16((float*)dst, (int16_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_8_BIT:
            memcpy_to_float_from_u8((float*)dst, (uint8_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_24_BIT_PACKED:
            memcpy_to_float_from_p24((float*)dst, (uint8_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_32_BIT:
            memcpy_to_float_from_i32((float*)dst, (int32_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_8_24_BIT:
            memcpy_to_float_from_q8_23((float*)dst, (int32_t*)src, count);
            return;
        default:
            break;
        }
        break;
    case AUDIO_FORMAT_PCM_8_BIT:
        switch (src_format) {
        case AUDIO_FORMAT_PCM_16_BIT:
            memcpy_to_u8_from_i16((uint8_t*)dst, (int16_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_FLOAT:
            memcpy_to_u8_from_float((uint8_t*)dst, (float*)src, count);
            return;
        default:
            break;
        }
        break;
    case AUDIO_FORMAT_PCM_24_BIT_PACKED:
        switch (src_format) {
        case AUDIO_FORMAT_PCM_16_BIT:
            memcpy_to_p24_from_i16((uint8_t*)dst, (int16_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_FLOAT:
            memcpy_to_p24_from_float((uint8_t*)dst, (float*)src, count);
            return;
        default:
            break;
        }
        break;
    case AUDIO_FORMAT_PCM_32_BIT:
        switch (src_format) {
        case AUDIO_FORMAT_PCM_16_BIT:
            memcpy_to_i32_from_i16((int32_t*)dst, (int16_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_FLOAT:
            memcpy_to_i32_from_float((int32_t*)dst, (float*)src, count);
            return;
        default:
            break;
        }
        break;
    case AUDIO_FORMAT_PCM_8_24_BIT:
        switch (src_format) {
        case AUDIO_FORMAT_PCM_16_BIT:
            memcpy_to_q8_23_from_i16((int32_t*)dst, (int16_t*)src, count);
            return;
        case AUDIO_FORMAT_PCM_FLOAT:
            memcpy_to_q8_23_from_float_with_clamp((int32_t*)dst, (float*)src, count);
            return;
        case AUDIO_FORMAT_PCM_24_BIT_PACKED: {
            memcpy_to_q8_23_from_p24((int32_t *)dst, (uint8_t *)src, count);
            return;
        }
        default:
            break;
        }
        break;
    default:
        break;
    }
    LOG_ALWAYS_FATAL("invalid src format %#x for dst format %#x",
            src_format, dst_format);
}

size_t memcpy_by_index_array_initialization_from_channel_mask(int8_t *idxary, size_t arysize,
        audio_channel_mask_t dst_channel_mask, audio_channel_mask_t src_channel_mask)
{
    const audio_channel_representation_t src_representation =
            audio_channel_mask_get_representation(src_channel_mask);
    const audio_channel_representation_t dst_representation =
            audio_channel_mask_get_representation(dst_channel_mask);
    const uint32_t src_bits = audio_channel_mask_get_bits(src_channel_mask);
    const uint32_t dst_bits = audio_channel_mask_get_bits(dst_channel_mask);

    switch (src_representation) {
    case AUDIO_CHANNEL_REPRESENTATION_POSITION:
        switch (dst_representation) {
        case AUDIO_CHANNEL_REPRESENTATION_POSITION:
            return memcpy_by_index_array_initialization(idxary, arysize,
                    dst_bits, src_bits);
        case AUDIO_CHANNEL_REPRESENTATION_INDEX:
            return memcpy_by_index_array_initialization_dst_index(idxary, arysize,
                    dst_bits, src_bits);
        default:
            return 0;
        }
        break;
    case AUDIO_CHANNEL_REPRESENTATION_INDEX:
        switch (dst_representation) {
        case AUDIO_CHANNEL_REPRESENTATION_POSITION:
            return memcpy_by_index_array_initialization_src_index(idxary, arysize,
                    dst_bits, src_bits);
        case AUDIO_CHANNEL_REPRESENTATION_INDEX:
            return memcpy_by_index_array_initialization(idxary, arysize,
                    dst_bits, src_bits);
        default:
            return 0;
        }
        break;
    default:
        return 0;
    }
}
