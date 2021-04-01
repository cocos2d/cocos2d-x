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

#pragma once

// ----------------------------------------------------------------------------

#include <stdint.h>
#include <android/log.h>
#include "audio/android/cutils/bitops.h"

#define PROPERTY_VALUE_MAX 256
#define CONSTEXPR constexpr


#ifdef __cplusplus
#   define CC_LIKELY( exp )    (__builtin_expect( !!(exp), true ))
#   define CC_UNLIKELY( exp )  (__builtin_expect( !!(exp), false ))
#else
#   define CC_LIKELY( exp )    (__builtin_expect( !!(exp), 1 ))
#   define CC_UNLIKELY( exp )  (__builtin_expect( !!(exp), 0 ))
#endif


/* special audio session values
 * (XXX: should this be living in the audio effects land?)
 */
typedef enum {
    /* session for effects attached to a particular output stream
     * (value must be less than 0)
     */
            AUDIO_SESSION_OUTPUT_STAGE = -1,

    /* session for effects applied to output mix. These effects can
     * be moved by audio policy manager to another output stream
     * (value must be 0)
     */
            AUDIO_SESSION_OUTPUT_MIX = 0,

    /* application does not specify an explicit session ID to be used,
     * and requests a new session ID to be allocated
     * TODO use unique values for AUDIO_SESSION_OUTPUT_MIX and AUDIO_SESSION_ALLOCATE,
     * after all uses have been updated from 0 to the appropriate symbol, and have been tested.
     */
            AUDIO_SESSION_ALLOCATE = 0,
} audio_session_t;

/* Audio sub formats (see enum audio_format). */

/* PCM sub formats */
typedef enum {
    /* All of these are in native byte order */
            AUDIO_FORMAT_PCM_SUB_16_BIT          = 0x1, /* DO NOT CHANGE - PCM signed 16 bits */
            AUDIO_FORMAT_PCM_SUB_8_BIT           = 0x2, /* DO NOT CHANGE - PCM unsigned 8 bits */
            AUDIO_FORMAT_PCM_SUB_32_BIT          = 0x3, /* PCM signed .31 fixed point */
            AUDIO_FORMAT_PCM_SUB_8_24_BIT        = 0x4, /* PCM signed 8.23 fixed point */
            AUDIO_FORMAT_PCM_SUB_FLOAT           = 0x5, /* PCM single-precision floating point */
            AUDIO_FORMAT_PCM_SUB_24_BIT_PACKED   = 0x6, /* PCM signed .23 fixed point packed in 3 bytes */
} audio_format_pcm_sub_fmt_t;

/* The audio_format_*_sub_fmt_t declarations are not currently used */

/* MP3 sub format field definition : can use 11 LSBs in the same way as MP3
 * frame header to specify bit rate, stereo mode, version...
 */
typedef enum {
    AUDIO_FORMAT_MP3_SUB_NONE            = 0x0,
} audio_format_mp3_sub_fmt_t;

/* AMR NB/WB sub format field definition: specify frame block interleaving,
 * bandwidth efficient or octet aligned, encoding mode for recording...
 */
typedef enum {
    AUDIO_FORMAT_AMR_SUB_NONE            = 0x0,
} audio_format_amr_sub_fmt_t;

/* AAC sub format field definition: specify profile or bitrate for recording... */
typedef enum {
    AUDIO_FORMAT_AAC_SUB_MAIN            = 0x1,
    AUDIO_FORMAT_AAC_SUB_LC              = 0x2,
    AUDIO_FORMAT_AAC_SUB_SSR             = 0x4,
    AUDIO_FORMAT_AAC_SUB_LTP             = 0x8,
    AUDIO_FORMAT_AAC_SUB_HE_V1           = 0x10,
    AUDIO_FORMAT_AAC_SUB_SCALABLE        = 0x20,
    AUDIO_FORMAT_AAC_SUB_ERLC            = 0x40,
    AUDIO_FORMAT_AAC_SUB_LD              = 0x80,
    AUDIO_FORMAT_AAC_SUB_HE_V2           = 0x100,
    AUDIO_FORMAT_AAC_SUB_ELD             = 0x200,
} audio_format_aac_sub_fmt_t;

/* VORBIS sub format field definition: specify quality for recording... */
typedef enum {
    AUDIO_FORMAT_VORBIS_SUB_NONE         = 0x0,
} audio_format_vorbis_sub_fmt_t;

/* Audio format consists of a main format field (upper 8 bits) and a sub format
 * field (lower 24 bits).
 *
 * The main format indicates the main codec type. The sub format field
 * indicates options and parameters for each format. The sub format is mainly
 * used for record to indicate for instance the requested bitrate or profile.
 * It can also be used for certain formats to give informations not present in
 * the encoded audio stream (e.g. octet alignment for AMR).
 */
typedef enum {
    AUDIO_FORMAT_INVALID             = 0xFFFFFFFFUL,
    AUDIO_FORMAT_DEFAULT             = 0,
    AUDIO_FORMAT_PCM                 = 0x00000000UL, /* DO NOT CHANGE */
            AUDIO_FORMAT_MP3                 = 0x01000000UL,
    AUDIO_FORMAT_AMR_NB              = 0x02000000UL,
    AUDIO_FORMAT_AMR_WB              = 0x03000000UL,
    AUDIO_FORMAT_AAC                 = 0x04000000UL,
    AUDIO_FORMAT_HE_AAC_V1           = 0x05000000UL, /* Deprecated, Use AUDIO_FORMAT_AAC_HE_V1*/
            AUDIO_FORMAT_HE_AAC_V2           = 0x06000000UL, /* Deprecated, Use AUDIO_FORMAT_AAC_HE_V2*/
            AUDIO_FORMAT_VORBIS              = 0x07000000UL,
    AUDIO_FORMAT_OPUS                = 0x08000000UL,
    AUDIO_FORMAT_AC3                 = 0x09000000UL,
    AUDIO_FORMAT_E_AC3               = 0x0A000000UL,
    AUDIO_FORMAT_DTS                 = 0x0B000000UL,
    AUDIO_FORMAT_DTS_HD              = 0x0C000000UL,
    AUDIO_FORMAT_MAIN_MASK           = 0xFF000000UL,
    AUDIO_FORMAT_SUB_MASK            = 0x00FFFFFFUL,

    /* Aliases */
    /* note != AudioFormat.ENCODING_PCM_16BIT */
            AUDIO_FORMAT_PCM_16_BIT          = (AUDIO_FORMAT_PCM |
                                                AUDIO_FORMAT_PCM_SUB_16_BIT),
    /* note != AudioFormat.ENCODING_PCM_8BIT */
            AUDIO_FORMAT_PCM_8_BIT           = (AUDIO_FORMAT_PCM |
                                                AUDIO_FORMAT_PCM_SUB_8_BIT),
    AUDIO_FORMAT_PCM_32_BIT          = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_32_BIT),
    AUDIO_FORMAT_PCM_8_24_BIT        = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_8_24_BIT),
    AUDIO_FORMAT_PCM_FLOAT           = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_FLOAT),
    AUDIO_FORMAT_PCM_24_BIT_PACKED   = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_24_BIT_PACKED),
    AUDIO_FORMAT_AAC_MAIN            = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_MAIN),
    AUDIO_FORMAT_AAC_LC              = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_LC),
    AUDIO_FORMAT_AAC_SSR             = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_SSR),
    AUDIO_FORMAT_AAC_LTP             = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_LTP),
    AUDIO_FORMAT_AAC_HE_V1           = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_HE_V1),
    AUDIO_FORMAT_AAC_SCALABLE        = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_SCALABLE),
    AUDIO_FORMAT_AAC_ERLC            = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_ERLC),
    AUDIO_FORMAT_AAC_LD              = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_LD),
    AUDIO_FORMAT_AAC_HE_V2           = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_HE_V2),
    AUDIO_FORMAT_AAC_ELD             = (AUDIO_FORMAT_AAC |
                                        AUDIO_FORMAT_AAC_SUB_ELD),
} audio_format_t;

/* For the channel mask for position assignment representation */
enum {
/* These can be a complete audio_channel_mask_t. */
            AUDIO_CHANNEL_NONE                      = 0x0,
    AUDIO_CHANNEL_INVALID                   = 0xC0000000,
/* These can be the bits portion of an audio_channel_mask_t
 * with representation AUDIO_CHANNEL_REPRESENTATION_POSITION.
 * Using these bits as a complete audio_channel_mask_t is deprecated.
 */
    /* output channels */
            AUDIO_CHANNEL_OUT_FRONT_LEFT            = 0x1,
    AUDIO_CHANNEL_OUT_FRONT_RIGHT           = 0x2,
    AUDIO_CHANNEL_OUT_FRONT_CENTER          = 0x4,
    AUDIO_CHANNEL_OUT_LOW_FREQUENCY         = 0x8,
    AUDIO_CHANNEL_OUT_BACK_LEFT             = 0x10,
    AUDIO_CHANNEL_OUT_BACK_RIGHT            = 0x20,
    AUDIO_CHANNEL_OUT_FRONT_LEFT_OF_CENTER  = 0x40,
    AUDIO_CHANNEL_OUT_FRONT_RIGHT_OF_CENTER = 0x80,
    AUDIO_CHANNEL_OUT_BACK_CENTER           = 0x100,
    AUDIO_CHANNEL_OUT_SIDE_LEFT             = 0x200,
    AUDIO_CHANNEL_OUT_SIDE_RIGHT            = 0x400,
    AUDIO_CHANNEL_OUT_TOP_CENTER            = 0x800,
    AUDIO_CHANNEL_OUT_TOP_FRONT_LEFT        = 0x1000,
    AUDIO_CHANNEL_OUT_TOP_FRONT_CENTER      = 0x2000,
    AUDIO_CHANNEL_OUT_TOP_FRONT_RIGHT       = 0x4000,
    AUDIO_CHANNEL_OUT_TOP_BACK_LEFT         = 0x8000,
    AUDIO_CHANNEL_OUT_TOP_BACK_CENTER       = 0x10000,
    AUDIO_CHANNEL_OUT_TOP_BACK_RIGHT        = 0x20000,
/* TODO: should these be considered complete channel masks, or only bits? */
            AUDIO_CHANNEL_OUT_MONO     = AUDIO_CHANNEL_OUT_FRONT_LEFT,
    AUDIO_CHANNEL_OUT_STEREO   = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                  AUDIO_CHANNEL_OUT_FRONT_RIGHT),
    AUDIO_CHANNEL_OUT_QUAD     = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                  AUDIO_CHANNEL_OUT_FRONT_RIGHT |
                                  AUDIO_CHANNEL_OUT_BACK_LEFT |
                                  AUDIO_CHANNEL_OUT_BACK_RIGHT),
    AUDIO_CHANNEL_OUT_QUAD_BACK = AUDIO_CHANNEL_OUT_QUAD,
    /* like AUDIO_CHANNEL_OUT_QUAD_BACK with *_SIDE_* instead of *_BACK_* */
            AUDIO_CHANNEL_OUT_QUAD_SIDE = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                           AUDIO_CHANNEL_OUT_FRONT_RIGHT |
                                           AUDIO_CHANNEL_OUT_SIDE_LEFT |
                                           AUDIO_CHANNEL_OUT_SIDE_RIGHT),
    AUDIO_CHANNEL_OUT_5POINT1  = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                  AUDIO_CHANNEL_OUT_FRONT_RIGHT |
                                  AUDIO_CHANNEL_OUT_FRONT_CENTER |
                                  AUDIO_CHANNEL_OUT_LOW_FREQUENCY |
                                  AUDIO_CHANNEL_OUT_BACK_LEFT |
                                  AUDIO_CHANNEL_OUT_BACK_RIGHT),
    AUDIO_CHANNEL_OUT_5POINT1_BACK = AUDIO_CHANNEL_OUT_5POINT1,
    /* like AUDIO_CHANNEL_OUT_5POINT1_BACK with *_SIDE_* instead of *_BACK_* */
            AUDIO_CHANNEL_OUT_5POINT1_SIDE = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                              AUDIO_CHANNEL_OUT_FRONT_RIGHT |
                                              AUDIO_CHANNEL_OUT_FRONT_CENTER |
                                              AUDIO_CHANNEL_OUT_LOW_FREQUENCY |
                                              AUDIO_CHANNEL_OUT_SIDE_LEFT |
                                              AUDIO_CHANNEL_OUT_SIDE_RIGHT),
    // matches the correct AudioFormat.CHANNEL_OUT_7POINT1_SURROUND definition for 7.1
            AUDIO_CHANNEL_OUT_7POINT1  = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                          AUDIO_CHANNEL_OUT_FRONT_RIGHT |
                                          AUDIO_CHANNEL_OUT_FRONT_CENTER |
                                          AUDIO_CHANNEL_OUT_LOW_FREQUENCY |
                                          AUDIO_CHANNEL_OUT_BACK_LEFT |
                                          AUDIO_CHANNEL_OUT_BACK_RIGHT |
                                          AUDIO_CHANNEL_OUT_SIDE_LEFT |
                                          AUDIO_CHANNEL_OUT_SIDE_RIGHT),
    AUDIO_CHANNEL_OUT_ALL      = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                  AUDIO_CHANNEL_OUT_FRONT_RIGHT |
                                  AUDIO_CHANNEL_OUT_FRONT_CENTER |
                                  AUDIO_CHANNEL_OUT_LOW_FREQUENCY |
                                  AUDIO_CHANNEL_OUT_BACK_LEFT |
                                  AUDIO_CHANNEL_OUT_BACK_RIGHT |
                                  AUDIO_CHANNEL_OUT_FRONT_LEFT_OF_CENTER |
                                  AUDIO_CHANNEL_OUT_FRONT_RIGHT_OF_CENTER |
                                  AUDIO_CHANNEL_OUT_BACK_CENTER|
                                  AUDIO_CHANNEL_OUT_SIDE_LEFT|
                                  AUDIO_CHANNEL_OUT_SIDE_RIGHT|
                                  AUDIO_CHANNEL_OUT_TOP_CENTER|
                                  AUDIO_CHANNEL_OUT_TOP_FRONT_LEFT|
                                  AUDIO_CHANNEL_OUT_TOP_FRONT_CENTER|
                                  AUDIO_CHANNEL_OUT_TOP_FRONT_RIGHT|
                                  AUDIO_CHANNEL_OUT_TOP_BACK_LEFT|
                                  AUDIO_CHANNEL_OUT_TOP_BACK_CENTER|
                                  AUDIO_CHANNEL_OUT_TOP_BACK_RIGHT),
/* These are bits only, not complete values */
    /* input channels */
            AUDIO_CHANNEL_IN_LEFT            = 0x4,
    AUDIO_CHANNEL_IN_RIGHT           = 0x8,
    AUDIO_CHANNEL_IN_FRONT           = 0x10,
    AUDIO_CHANNEL_IN_BACK            = 0x20,
    AUDIO_CHANNEL_IN_LEFT_PROCESSED  = 0x40,
    AUDIO_CHANNEL_IN_RIGHT_PROCESSED = 0x80,
    AUDIO_CHANNEL_IN_FRONT_PROCESSED = 0x100,
    AUDIO_CHANNEL_IN_BACK_PROCESSED  = 0x200,
    AUDIO_CHANNEL_IN_PRESSURE        = 0x400,
    AUDIO_CHANNEL_IN_X_AXIS          = 0x800,
    AUDIO_CHANNEL_IN_Y_AXIS          = 0x1000,
    AUDIO_CHANNEL_IN_Z_AXIS          = 0x2000,
    AUDIO_CHANNEL_IN_VOICE_UPLINK    = 0x4000,
    AUDIO_CHANNEL_IN_VOICE_DNLINK    = 0x8000,
/* TODO: should these be considered complete channel masks, or only bits, or deprecated? */
            AUDIO_CHANNEL_IN_MONO   = AUDIO_CHANNEL_IN_FRONT,
    AUDIO_CHANNEL_IN_STEREO = (AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_RIGHT),
    AUDIO_CHANNEL_IN_FRONT_BACK = (AUDIO_CHANNEL_IN_FRONT | AUDIO_CHANNEL_IN_BACK),
    AUDIO_CHANNEL_IN_ALL    = (AUDIO_CHANNEL_IN_LEFT |
                               AUDIO_CHANNEL_IN_RIGHT |
                               AUDIO_CHANNEL_IN_FRONT |
                               AUDIO_CHANNEL_IN_BACK|
                               AUDIO_CHANNEL_IN_LEFT_PROCESSED |
                               AUDIO_CHANNEL_IN_RIGHT_PROCESSED |
                               AUDIO_CHANNEL_IN_FRONT_PROCESSED |
                               AUDIO_CHANNEL_IN_BACK_PROCESSED|
                               AUDIO_CHANNEL_IN_PRESSURE |
                               AUDIO_CHANNEL_IN_X_AXIS |
                               AUDIO_CHANNEL_IN_Y_AXIS |
                               AUDIO_CHANNEL_IN_Z_AXIS |
                               AUDIO_CHANNEL_IN_VOICE_UPLINK |
                               AUDIO_CHANNEL_IN_VOICE_DNLINK),
};
/* A channel mask per se only defines the presence or absence of a channel, not the order.
 * But see AUDIO_INTERLEAVE_* below for the platform convention of order.
 *
 * audio_channel_mask_t is an opaque type and its internal layout should not
 * be assumed as it may change in the future.
 * Instead, always use the functions declared in this header to examine.
 *
 * These are the current representations:
 *
 *   AUDIO_CHANNEL_REPRESENTATION_POSITION
 *     is a channel mask representation for position assignment.
 *     Each low-order bit corresponds to the spatial position of a transducer (output),
 *     or interpretation of channel (input).
 *     The user of a channel mask needs to know the context of whether it is for output or input.
 *     The constants AUDIO_CHANNEL_OUT_* or AUDIO_CHANNEL_IN_* apply to the bits portion.
 *     It is not permitted for no bits to be set.
 *
 *   AUDIO_CHANNEL_REPRESENTATION_INDEX
 *     is a channel mask representation for index assignment.
 *     Each low-order bit corresponds to a selected channel.
 *     There is no platform interpretation of the various bits.
 *     There is no concept of output or input.
 *     It is not permitted for no bits to be set.
 *
 * All other representations are reserved for future use.
 *
 * Warning: current representation distinguishes between input and output, but this will not the be
 * case in future revisions of the platform. Wherever there is an ambiguity between input and output
 * that is currently resolved by checking the channel mask, the implementer should look for ways to
 * fix it with additional information outside of the mask.
 */
typedef uint32_t audio_channel_mask_t;

/* Maximum number of channels for all representations */
#define AUDIO_CHANNEL_COUNT_MAX             30

/* log(2) of maximum number of representations, not part of public API */
#define AUDIO_CHANNEL_REPRESENTATION_LOG2   2

/* Representations */
typedef enum {
    AUDIO_CHANNEL_REPRESENTATION_POSITION    = 0,    // must be zero for compatibility
    // 1 is reserved for future use
            AUDIO_CHANNEL_REPRESENTATION_INDEX       = 2,
    // 3 is reserved for future use
} audio_channel_representation_t;

/* The return value is undefined if the channel mask is invalid. */
static inline uint32_t audio_channel_mask_get_bits(audio_channel_mask_t channel)
{
    return channel & ((1 << AUDIO_CHANNEL_COUNT_MAX) - 1);
}

/* The return value is undefined if the channel mask is invalid. */
static inline audio_channel_representation_t audio_channel_mask_get_representation(
        audio_channel_mask_t channel)
{
    // The right shift should be sufficient, but also "and" for safety in case mask is not 32 bits
    return (audio_channel_representation_t)
            ((channel >> AUDIO_CHANNEL_COUNT_MAX) & ((1 << AUDIO_CHANNEL_REPRESENTATION_LOG2) - 1));
}

/* Returns the number of channels from an output channel mask,
 * used in the context of audio output or playback.
 * If a channel bit is set which could _not_ correspond to an output channel,
 * it is excluded from the count.
 * Returns zero if the representation is invalid.
 */
static inline uint32_t audio_channel_count_from_out_mask(audio_channel_mask_t channel)
{
    uint32_t bits = audio_channel_mask_get_bits(channel);
    switch (audio_channel_mask_get_representation(channel)) {
        case AUDIO_CHANNEL_REPRESENTATION_POSITION:
            // TODO: We can now merge with from_in_mask and remove anding
            bits &= AUDIO_CHANNEL_OUT_ALL;
            // fall through
        case AUDIO_CHANNEL_REPRESENTATION_INDEX:
            return popcount(bits);
        default:
            return 0;
    }
}

static inline bool audio_is_valid_format(audio_format_t format)
{
    switch (format & AUDIO_FORMAT_MAIN_MASK) {
        case AUDIO_FORMAT_PCM:
            switch (format) {
                case AUDIO_FORMAT_PCM_16_BIT:
                case AUDIO_FORMAT_PCM_8_BIT:
                case AUDIO_FORMAT_PCM_32_BIT:
                case AUDIO_FORMAT_PCM_8_24_BIT:
                case AUDIO_FORMAT_PCM_FLOAT:
                case AUDIO_FORMAT_PCM_24_BIT_PACKED:
                    return true;
                default:
                    return false;
            }
            /* not reached */
        case AUDIO_FORMAT_MP3:
        case AUDIO_FORMAT_AMR_NB:
        case AUDIO_FORMAT_AMR_WB:
        case AUDIO_FORMAT_AAC:
        case AUDIO_FORMAT_HE_AAC_V1:
        case AUDIO_FORMAT_HE_AAC_V2:
        case AUDIO_FORMAT_VORBIS:
        case AUDIO_FORMAT_OPUS:
        case AUDIO_FORMAT_AC3:
        case AUDIO_FORMAT_E_AC3:
        case AUDIO_FORMAT_DTS:
        case AUDIO_FORMAT_DTS_HD:
            return true;
        default:
            return false;
    }
}

static inline bool audio_is_linear_pcm(audio_format_t format)
{
    return ((format & AUDIO_FORMAT_MAIN_MASK) == AUDIO_FORMAT_PCM);
}

static inline size_t audio_bytes_per_sample(audio_format_t format)
{
    size_t size = 0;

    switch (format) {
        case AUDIO_FORMAT_PCM_32_BIT:
        case AUDIO_FORMAT_PCM_8_24_BIT:
            size = sizeof(int32_t);
            break;
        case AUDIO_FORMAT_PCM_24_BIT_PACKED:
            size = sizeof(uint8_t) * 3;
            break;
        case AUDIO_FORMAT_PCM_16_BIT:
            size = sizeof(int16_t);
            break;
        case AUDIO_FORMAT_PCM_8_BIT:
            size = sizeof(uint8_t);
            break;
        case AUDIO_FORMAT_PCM_FLOAT:
            size = sizeof(float);
            break;
        default:
            break;
    }
    return size;
}

/* Not part of public API */
static inline audio_channel_mask_t audio_channel_mask_from_representation_and_bits(
        audio_channel_representation_t representation, uint32_t bits)
{
    return (audio_channel_mask_t) ((representation << AUDIO_CHANNEL_COUNT_MAX) | bits);
}

/* Derive an output channel mask for position assignment from a channel count.
 * This is to be used when the content channel mask is unknown. The 1, 2, 4, 5, 6, 7 and 8 channel
 * cases are mapped to the standard game/home-theater layouts, but note that 4 is mapped to quad,
 * and not stereo + FC + mono surround. A channel count of 3 is arbitrarily mapped to stereo + FC
 * for continuity with stereo.
 * Returns the matching channel mask,
 * or AUDIO_CHANNEL_NONE if the channel count is zero,
 * or AUDIO_CHANNEL_INVALID if the channel count exceeds that of the
 * configurations for which a default output channel mask is defined.
 */
static inline audio_channel_mask_t audio_channel_out_mask_from_count(uint32_t channel_count)
{
    uint32_t bits;
    switch (channel_count) {
        case 0:
            return AUDIO_CHANNEL_NONE;
        case 1:
            bits = AUDIO_CHANNEL_OUT_MONO;
            break;
        case 2:
            bits = AUDIO_CHANNEL_OUT_STEREO;
            break;
        case 3:
            bits = AUDIO_CHANNEL_OUT_STEREO | AUDIO_CHANNEL_OUT_FRONT_CENTER;
            break;
        case 4: // 4.0
            bits = AUDIO_CHANNEL_OUT_QUAD;
            break;
        case 5: // 5.0
            bits = AUDIO_CHANNEL_OUT_QUAD | AUDIO_CHANNEL_OUT_FRONT_CENTER;
            break;
        case 6: // 5.1
            bits = AUDIO_CHANNEL_OUT_5POINT1;
            break;
        case 7: // 6.1
            bits = AUDIO_CHANNEL_OUT_5POINT1 | AUDIO_CHANNEL_OUT_BACK_CENTER;
            break;
        case 8:
            bits = AUDIO_CHANNEL_OUT_7POINT1;
            break;
            // FIXME FCC_8
        default:
            return AUDIO_CHANNEL_INVALID;
    }
    return audio_channel_mask_from_representation_and_bits(
            AUDIO_CHANNEL_REPRESENTATION_POSITION, bits);
}

