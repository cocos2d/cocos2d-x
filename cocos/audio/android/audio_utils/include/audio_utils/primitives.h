/*
 * Copyright (C) 2011 The Android Open Source Project
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

#ifndef COCOS_AUDIO_PRIMITIVES_H
#define COCOS_AUDIO_PRIMITIVES_H

#include <stdint.h>
#include <stdlib.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/* The memcpy_* conversion routines are designed to work in-place on same dst as src
 * buffers only if the types shrink on copy, with the exception of memcpy_to_i16_from_u8().
 * This allows the loops to go upwards for faster cache access (and may be more flexible
 * for future optimization later).
 */

/**
 * Dither and clamp pairs of 32-bit input samples (sums) to 16-bit output samples (out).
 * Each 32-bit input sample can be viewed as a signed fixed-point Q19.12 of which the
 * .12 fraction bits are dithered and the 19 integer bits are clamped to signed 16 bits.
 * Alternatively the input can be viewed as Q4.27, of which the lowest .12 of the fraction
 * is dithered and the remaining fraction is converted to the output Q.15, with clamping
 * on the 4 integer guard bits.
 *
 * For interleaved stereo, c is the number of sample pairs,
 * and out is an array of interleaved pairs of 16-bit samples per channel.
 * For mono, c is the number of samples / 2, and out is an array of 16-bit samples.
 * The name "dither" is a misnomer; the current implementation does not actually dither
 * but uses truncation.  This may change.
 * The out and sums buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void ditherAndClamp(int32_t* out, const int32_t *sums, size_t c);

/* Expand and copy samples from unsigned 8-bit offset by 0x80 to signed 16-bit.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i16_from_u8(int16_t *dst, const uint8_t *src, size_t count);

/* Shrink and copy samples from signed 16-bit to unsigned 8-bit offset by 0x80.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_u8_from_i16(uint8_t *dst, const int16_t *src, size_t count);

/* Copy samples from float to unsigned 8-bit offset by 0x80.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_u8_from_float(uint8_t *dst, const float *src, size_t count);

/* Shrink and copy samples from signed 32-bit fixed-point Q0.31 to signed 16-bit Q0.15.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_i16_from_i32(int16_t *dst, const int32_t *src, size_t count);

/* Shrink and copy samples from single-precision floating-point to signed 16-bit.
 * Each float should be in the range -1.0 to 1.0.  Values outside that range are clamped,
 * refer to clamp16_from_float().
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_i16_from_float(int16_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q4.27 to single-precision floating-point.
 * The nominal output float range is [-1.0, 1.0] if the fixed-point range is
 * [0xf8000000, 0x07ffffff].  The full float range is [-16.0, 16.0].  Note the closed range
 * at 1.0 and 16.0 is due to rounding on conversion to float. See float_from_q4_27() for details.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_float_from_q4_27(float *dst, const int32_t *src, size_t count);

/* Copy samples from signed fixed-point 16 bit Q0.15 to single-precision floating-point.
 * The output float range is [-1.0, 1.0) for the fixed-point range [0x8000, 0x7fff].
 * No rounding is needed as the representation is exact.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_float_from_i16(float *dst, const int16_t *src, size_t count);

/* Copy samples from unsigned fixed-point 8 bit to single-precision floating-point.
 * The output float range is [-1.0, 1.0) for the fixed-point range [0x00, 0xFF].
 * No rounding is needed as the representation is exact.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_float_from_u8(float *dst, const uint8_t *src, size_t count);

/* Copy samples from signed fixed-point packed 24 bit Q0.23 to single-precision floating-point.
 * The packed 24 bit input is stored in native endian format in a uint8_t byte array.
 * The output float range is [-1.0, 1.0) for the fixed-point range [0x800000, 0x7fffff].
 * No rounding is needed as the representation is exact.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_float_from_p24(float *dst, const uint8_t *src, size_t count);

/* Copy samples from signed fixed-point packed 24 bit Q0.23 to signed fixed point 16 bit Q0.15.
 * The packed 24 bit output is stored in native endian format in a uint8_t byte array.
 * The data is truncated without rounding.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i16_from_p24(int16_t *dst, const uint8_t *src, size_t count);

/* Copy samples from signed fixed-point packed 24 bit Q0.23 to signed fixed-point 32-bit Q0.31.
 * The packed 24 bit input is stored in native endian format in a uint8_t byte array.
 * The output data range is [0x80000000, 0x7fffff00] at intervals of 0x100.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_i32_from_p24(int32_t *dst, const uint8_t *src, size_t count);

/* Copy samples from signed fixed point 16 bit Q0.15 to signed fixed-point packed 24 bit Q0.23.
 * The packed 24 bit output is assumed to be a native-endian uint8_t byte array.
 * The output data range is [0x800000, 0x7fff00] (not full).
 * Nevertheless there is no DC offset on the output, if the input has no DC offset.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_p24_from_i16(uint8_t *dst, const int16_t *src, size_t count);

/* Copy samples from single-precision floating-point to signed fixed-point packed 24 bit Q0.23.
 * The packed 24 bit output is assumed to be a native-endian uint8_t byte array.
 * The data is clamped and rounded to nearest, ties away from zero. See clamp24_from_float()
 * for details.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_p24_from_float(uint8_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q8.23 to signed fixed-point packed 24 bit Q0.23.
 * The packed 24 bit output is assumed to be a native-endian uint8_t byte array.
 * The data is clamped to the range is [0x800000, 0x7fffff].
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_p24_from_q8_23(uint8_t *dst, const int32_t *src, size_t count);

/* Shrink and copy samples from signed 32-bit fixed-point Q0.31
 * to signed fixed-point packed 24 bit Q0.23.
 * The packed 24 bit output is assumed to be a native-endian uint8_t byte array.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_p24_from_i32(uint8_t *dst, const int32_t *src, size_t count);

/* Copy samples from signed fixed point 16-bit Q0.15 to signed fixed-point 32-bit Q8.23.
 * The output data range is [0xff800000, 0x007fff00] at intervals of 0x100.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_q8_23_from_i16(int32_t *dst, const int16_t *src, size_t count);

/* Copy samples from single-precision floating-point to signed fixed-point 32-bit Q8.23.
 * This copy will clamp the Q8.23 representation to [0xff800000, 0x007fffff] even though there
 * are guard bits available. Fractional lsb is rounded to nearest, ties away from zero.
 * See clamp24_from_float() for details.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_q8_23_from_float_with_clamp(int32_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed point packed 24-bit Q0.23 to signed fixed-point 32-bit Q8.23.
 * The output data range is [0xff800000, 0x007fffff].
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_q8_23_from_p24(int32_t *dst, const uint8_t *src, size_t count);

/* Copy samples from single-precision floating-point to signed fixed-point 32-bit Q4.27.
 * The conversion will use the full available Q4.27 range, including guard bits.
 * Fractional lsb is rounded to nearest, ties away from zero.
 * See clampq4_27_from_float() for details.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_q4_27_from_float(int32_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q8.23 to signed fixed point 16-bit Q0.15.
 * The data is clamped, and truncated without rounding.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i16_from_q8_23(int16_t *dst, const int32_t *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q8.23 to single-precision floating-point.
 * The nominal output float range is [-1.0, 1.0) for the fixed-point
 * range [0xff800000, 0x007fffff]. The maximum output float range is [-256.0, 256.0).
 * No rounding is needed as the representation is exact for nominal values.
 * Rounding for overflow values is to nearest, ties to even.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_float_from_q8_23(float *dst, const int32_t *src, size_t count);

/* Copy samples from signed fixed point 16-bit Q0.15 to signed fixed-point 32-bit Q0.31.
 * The output data range is [0x80000000, 0x7fff0000] at intervals of 0x10000.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_i32_from_i16(int32_t *dst, const int16_t *src, size_t count);

/* Copy samples from single-precision floating-point to signed fixed-point 32-bit Q0.31.
 * If rounding is needed on truncation, the fractional lsb is rounded to nearest,
 * ties away from zero. See clamp32_from_float() for details.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i32_from_float(int32_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q0.31 to single-precision floating-point.
 * The float range is [-1.0, 1.0] for the fixed-point range [0x80000000, 0x7fffffff].
 * Rounding is done according to float_from_i32().
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_float_from_i32(float *dst, const int32_t *src, size_t count);

/* Downmix pairs of interleaved stereo input 16-bit samples to mono output 16-bit samples.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of stereo frames to downmix
 * The destination and source buffers must be completely separate (non-overlapping).
 * The current implementation truncates the mean rather than dither, but this may change.
 */
void downmix_to_mono_i16_from_stereo_i16(int16_t *dst, const int16_t *src, size_t count);

/* Upmix mono input 16-bit samples to pairs of interleaved stereo output 16-bit samples by
 * duplicating.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of mono samples to upmix
 * The destination and source buffers must be completely separate (non-overlapping).
 */
void upmix_to_stereo_i16_from_mono_i16(int16_t *dst, const int16_t *src, size_t count);

/* Downmix pairs of interleaved stereo input float samples to mono output float samples
 * by averaging the stereo pair together.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of stereo frames to downmix
 * The destination and source buffers must be completely separate (non-overlapping),
 * or they must both start at the same address.
 */
void downmix_to_mono_float_from_stereo_float(float *dst, const float *src, size_t count);

/* Upmix mono input float samples to pairs of interleaved stereo output float samples by
 * duplicating.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of mono samples to upmix
 * The destination and source buffers must be completely separate (non-overlapping).
 */
void upmix_to_stereo_float_from_mono_float(float *dst, const float *src, size_t count);

/* Return the total number of non-zero 32-bit samples */
size_t nonZeroMono32(const int32_t *samples, size_t count);

/* Return the total number of non-zero 16-bit samples */
size_t nonZeroMono16(const int16_t *samples, size_t count);

/* Return the total number of non-zero stereo frames, where a frame is considered non-zero
 * if either of its constituent 32-bit samples is non-zero
 */
size_t nonZeroStereo32(const int32_t *frames, size_t count);

/* Return the total number of non-zero stereo frames, where a frame is considered non-zero
 * if either of its constituent 16-bit samples is non-zero
 */
size_t nonZeroStereo16(const int16_t *frames, size_t count);

/* Copy frames, selecting source samples based on a source channel mask to fit
 * the destination channel mask. Unmatched channels in the destination channel mask
 * are zero filled. Unmatched channels in the source channel mask are dropped.
 * Channels present in the channel mask are represented by set bits in the
 * uint32_t value and are matched without further interpretation.
 * Parameters:
 *  dst         Destination buffer
 *  dst_mask    Bit mask corresponding to destination channels present
 *  src         Source buffer
 *  src_mask    Bit mask corresponding to source channels present
 *  sample_size Size of each sample in bytes.  Must be 1, 2, 3, or 4.
 *  count       Number of frames to copy
 * The destination and source buffers must be completely separate (non-overlapping).
 * If the sample size is not in range, the function will abort.
 */
void memcpy_by_channel_mask(void *dst, uint32_t dst_mask,
        const void *src, uint32_t src_mask, size_t sample_size, size_t count);

/* Copy frames, selecting source samples based on an index array (idxary).
 * The idxary[] consists of dst_channels number of elements.
 * The ith element if idxary[] corresponds the ith destination channel.
 * A non-negative value is the channel index in the source frame.
 * A negative index (-1) represents filling with 0.
 *
 * Example: Swapping L and R channels for stereo streams
 * idxary[0] = 1;
 * idxary[1] = 0;
 *
 * Example: Copying a mono source to the front center 5.1 channel
 * idxary[0] = -1;
 * idxary[1] = -1;
 * idxary[2] = 0;
 * idxary[3] = -1;
 * idxary[4] = -1;
 * idxary[5] = -1;
 *
 * This copy allows swizzling of channels or replication of channels.
 *
 * Parameters:
 *  dst           Destination buffer
 *  dst_channels  Number of destination channels per frame
 *  src           Source buffer
 *  src_channels  Number of source channels per frame
 *  idxary        Array of indices representing channels in the source frame
 *  sample_size   Size of each sample in bytes.  Must be 1, 2, 3, or 4.
 *  count         Number of frames to copy
 * The destination and source buffers must be completely separate (non-overlapping).
 * If the sample size is not in range, the function will abort.
 */
void memcpy_by_index_array(void *dst, uint32_t dst_channels,
        const void *src, uint32_t src_channels,
        const int8_t *idxary, size_t sample_size, size_t count);

/* Prepares an index array (idxary) from channel masks, which can be later
 * used by memcpy_by_index_array(). Returns the number of array elements required.
 * This may be greater than idxcount, so the return value should be checked
 * if idxary size is less than 32. Note that idxary is a caller allocated array
 * of at least as many channels as present in the dst_mask.
 * Channels present in the channel mask are represented by set bits in the
 * uint32_t value and are matched without further interpretation.
 *
 * This function is typically used for converting audio data with different
 * channel position masks.
 *
 * Parameters:
 *  idxary      Updated array of indices of channels in the src frame for the dst frame
 *  idxcount    Number of caller allocated elements in idxary
 *  dst_mask    Bit mask corresponding to destination channels present
 *  src_mask    Bit mask corresponding to source channels present
 */
size_t memcpy_by_index_array_initialization(int8_t *idxary, size_t idxcount,
        uint32_t dst_mask, uint32_t src_mask);

/* Prepares an index array (idxary) from channel masks, which can be later
 * used by memcpy_by_index_array(). Returns the number of array elements required.
 *
 * For a source channel index mask, the source channels will map to the destination
 * channels as if counting the set bits in dst_mask in order from lsb to msb
 * (zero bits are ignored). The ith bit of the src_mask corresponds to the
 * ith SET bit of dst_mask and the ith destination channel.  Hence, a zero ith
 * bit of the src_mask indicates that the ith destination channel plays silence.
 *
 * Parameters:
 *  idxary      Updated array of indices of channels in the src frame for the dst frame
 *  idxcount    Number of caller allocated elements in idxary
 *  dst_mask    Bit mask corresponding to destination channels present
 *  src_mask    Bit mask corresponding to source channels present
 */
size_t memcpy_by_index_array_initialization_src_index(int8_t *idxary, size_t idxcount,
        uint32_t dst_mask, uint32_t src_mask);

/* Prepares an index array (idxary) from channel mask bits, which can be later
 * used by memcpy_by_index_array(). Returns the number of array elements required.
 *
 * This initialization is for a destination channel index mask from a positional
 * source mask.
 *
 * For an destination channel index mask, the input channels will map
 * to the destination channels, with the ith SET bit in the source bits corresponding
 * to the ith bit in the destination bits. If there is a zero bit in the middle
 * of set destination bits (unlikely), the corresponding source channel will
 * be dropped.
 *
 * Parameters:
 *  idxary      Updated array of indices of channels in the src frame for the dst frame
 *  idxcount    Number of caller allocated elements in idxary
 *  dst_mask    Bit mask corresponding to destination channels present
 *  src_mask    Bit mask corresponding to source channels present
 */
size_t memcpy_by_index_array_initialization_dst_index(int8_t *idxary, size_t idxcount,
        uint32_t dst_mask, uint32_t src_mask);

/**
 * Clamp (aka hard limit or clip) a signed 32-bit sample to 16-bit range.
 */
static inline int16_t clamp16(int32_t sample)
{
    if ((sample>>15) ^ (sample>>31))
        sample = 0x7FFF ^ (sample>>31);
    return sample;
}

/*
 * Convert a IEEE 754 single precision float [-1.0, 1.0) to int16_t [-32768, 32767]
 * with clamping.  Note the open bound at 1.0, values within 1/65536 of 1.0 map
 * to 32767 instead of 32768 (early clamping due to the smaller positive integer subrange).
 *
 * Values outside the range [-1.0, 1.0) are properly clamped to -32768 and 32767,
 * including -Inf and +Inf. NaN will generally be treated either as -32768 or 32767,
 * depending on the sign bit inside NaN (whose representation is not unique).
 * Nevertheless, strictly speaking, NaN behavior should be considered undefined.
 *
 * Rounding of 0.5 lsb is to even (default for IEEE 754).
 */
static inline int16_t clamp16_from_float(float f)
{
    /* Offset is used to expand the valid range of [-1.0, 1.0) into the 16 lsbs of the
     * floating point significand. The normal shift is 3<<22, but the -15 offset
     * is used to multiply by 32768.
     */
    static const float offset = (float)(3 << (22 - 15));
    /* zero = (0x10f << 22) =  0x43c00000 (not directly used) */
    static const int32_t limneg = (0x10f << 22) /*zero*/ - 32768; /* 0x43bf8000 */
    static const int32_t limpos = (0x10f << 22) /*zero*/ + 32767; /* 0x43c07fff */

    union {
        float f;
        int32_t i;
    } u;

    u.f = f + offset; /* recenter valid range */
    /* Now the valid range is represented as integers between [limneg, limpos].
     * Clamp using the fact that float representation (as an integer) is an ordered set.
     */
    if (u.i < limneg)
        u.i = -32768;
    else if (u.i > limpos)
        u.i = 32767;
    return u.i; /* Return lower 16 bits, the part of interest in the significand. */
}

/*
 * Convert a IEEE 754 single precision float [-1.0, 1.0) to uint8_t [0, 0xff]
 * with clamping.  Note the open bound at 1.0, values within 1/128 of 1.0 map
 * to 255 instead of 256 (early clamping due to the smaller positive integer subrange).
 *
 * Values outside the range [-1.0, 1.0) are properly clamped to 0 and 255,
 * including -Inf and +Inf. NaN will generally be treated either as 0 or 255,
 * depending on the sign bit inside NaN (whose representation is not unique).
 * Nevertheless, strictly speaking, NaN behavior should be considered undefined.
 *
 * Rounding of 0.5 lsb is to even (default for IEEE 754).
 */
static inline uint8_t clamp8_from_float(float f)
{
    /* Offset is used to expand the valid range of [-1.0, 1.0) into the 16 lsbs of the
     * floating point significand. The normal shift is 3<<22, but the -7 offset
     * is used to multiply by 128.
     */
    static const float offset = (float)((3 << (22 - 7)) + 1 /* to cancel -1.0 */);
    /* zero = (0x11f << 22) =  0x47c00000 */
    static const int32_t limneg = (0x11f << 22) /*zero*/;
    static const int32_t limpos = (0x11f << 22) /*zero*/ + 255; /* 0x47c000ff */

    union {
        float f;
        int32_t i;
    } u;

    u.f = f + offset; /* recenter valid range */
    /* Now the valid range is represented as integers between [limneg, limpos].
     * Clamp using the fact that float representation (as an integer) is an ordered set.
     */
    if (u.i < limneg)
        return 0;
    if (u.i > limpos)
        return 255;
    return u.i; /* Return lower 8 bits, the part of interest in the significand. */
}

/* Convert a single-precision floating point value to a Q0.23 integer value, stored in a
 * 32 bit signed integer (technically stored as Q8.23, but clamped to Q0.23).
 *
 * Rounds to nearest, ties away from 0.
 *
 * Values outside the range [-1.0, 1.0) are properly clamped to -8388608 and 8388607,
 * including -Inf and +Inf. NaN values are considered undefined, and behavior may change
 * depending on hardware and future implementation of this function.
 */
static inline int32_t clamp24_from_float(float f)
{
    static const float scale = (float)(1 << 23);
    static const float limpos = 0x7fffff / (float)(1 << 23);
    static const float limneg = -0x800000 / (float)(1 << 23);

    if (f <= limneg) {
        return -0x800000;
    } else if (f >= limpos) {
        return 0x7fffff;
    }
    f *= scale;
    /* integer conversion is through truncation (though int to float is not).
     * ensure that we round to nearest, ties away from 0.
     */
    return f > 0 ? f + 0.5 : f - 0.5;
}

/* Convert a signed fixed-point 32-bit Q8.23 value to a Q0.23 integer value,
 * stored in a 32-bit signed integer (technically stored as Q8.23, but clamped to Q0.23).
 *
 * Values outside the range [-0x800000, 0x7fffff] are clamped to that range.
 */
static inline int32_t clamp24_from_q8_23(int32_t ival)
{
    static const int32_t limpos = 0x7fffff;
    static const int32_t limneg = -0x800000;
    if (ival < limneg) {
        return limneg;
    } else if (ival > limpos) {
        return limpos;
    } else {
        return ival;
    }
}

/* Convert a single-precision floating point value to a Q4.27 integer value.
 * Rounds to nearest, ties away from 0.
 *
 * Values outside the range [-16.0, 16.0) are properly clamped to -2147483648 and 2147483647,
 * including -Inf and +Inf. NaN values are considered undefined, and behavior may change
 * depending on hardware and future implementation of this function.
 */
static inline int32_t clampq4_27_from_float(float f)
{
    static const float scale = (float)(1UL << 27);
    static const float limpos = 16.;
    static const float limneg = -16.;

    if (f <= limneg) {
        return -0x80000000; /* or 0x80000000 */
    } else if (f >= limpos) {
        return 0x7fffffff;
    }
    f *= scale;
    /* integer conversion is through truncation (though int to float is not).
     * ensure that we round to nearest, ties away from 0.
     */
    return f > 0 ? f + 0.5 : f - 0.5;
}

/* Convert a single-precision floating point value to a Q0.31 integer value.
 * Rounds to nearest, ties away from 0.
 *
 * Values outside the range [-1.0, 1.0) are properly clamped to -2147483648 and 2147483647,
 * including -Inf and +Inf. NaN values are considered undefined, and behavior may change
 * depending on hardware and future implementation of this function.
 */
static inline int32_t clamp32_from_float(float f)
{
    static const float scale = (float)(1UL << 31);
    static const float limpos = 1.;
    static const float limneg = -1.;

    if (f <= limneg) {
        return -0x80000000; /* or 0x80000000 */
    } else if (f >= limpos) {
        return 0x7fffffff;
    }
    f *= scale;
    /* integer conversion is through truncation (though int to float is not).
     * ensure that we round to nearest, ties away from 0.
     */
    return f > 0 ? f + 0.5 : f - 0.5;
}

/* Convert a signed fixed-point 32-bit Q4.27 value to single-precision floating-point.
 * The nominal output float range is [-1.0, 1.0] if the fixed-point range is
 * [0xf8000000, 0x07ffffff].  The full float range is [-16.0, 16.0].
 *
 * Note the closed range at 1.0 and 16.0 is due to rounding on conversion to float.
 * In more detail: if the fixed-point integer exceeds 24 bit significand of single
 * precision floating point, the 0.5 lsb in the significand conversion will round
 * towards even, as per IEEE 754 default.
 */
static inline float float_from_q4_27(int32_t ival)
{
    /* The scale factor is the reciprocal of the fractional bits.
     *
     * Since the scale factor is a power of 2, the scaling is exact, and there
     * is no rounding due to the multiplication - the bit pattern is preserved.
     * However, there may be rounding due to the fixed-point to float conversion,
     * as described above.
     */
    static const float scale = 1. / (float)(1UL << 27);

    return ival * scale;
}

/* Convert an unsigned fixed-point 32-bit U4.28 value to single-precision floating-point.
 * The nominal output float range is [0.0, 1.0] if the fixed-point range is
 * [0x00000000, 0x10000000].  The full float range is [0.0, 16.0].
 *
 * Note the closed range at 1.0 and 16.0 is due to rounding on conversion to float.
 * In more detail: if the fixed-point integer exceeds 24 bit significand of single
 * precision floating point, the 0.5 lsb in the significand conversion will round
 * towards even, as per IEEE 754 default.
 */
static inline float float_from_u4_28(uint32_t uval)
{
    static const float scale = 1. / (float)(1UL << 28);

    return uval * scale;
}

/* Convert an unsigned fixed-point 16-bit U4.12 value to single-precision floating-point.
 * The nominal output float range is [0.0, 1.0] if the fixed-point range is
 * [0x0000, 0x1000].  The full float range is [0.0, 16.0).
 */
static inline float float_from_u4_12(uint16_t uval)
{
    static const float scale = 1. / (float)(1UL << 12);

    return uval * scale;
}

/* Convert a single-precision floating point value to a U4.28 integer value.
 * Rounds to nearest, ties away from 0.
 *
 * Values outside the range [0, 16.0] are properly clamped to [0, 4294967295]
 * including -Inf and +Inf. NaN values are considered undefined, and behavior may change
 * depending on hardware and future implementation of this function.
 */
static inline uint32_t u4_28_from_float(float f)
{
    static const float scale = (float)(1 << 28);
    static const float limpos = 0xffffffffUL / (float)(1 << 28);

    if (f <= 0.) {
        return 0;
    } else if (f >= limpos) {
        return 0xffffffff;
    }
    /* integer conversion is through truncation (though int to float is not).
     * ensure that we round to nearest, ties away from 0.
     */
    return f * scale + 0.5;
}

/* Convert a single-precision floating point value to a U4.12 integer value.
 * Rounds to nearest, ties away from 0.
 *
 * Values outside the range [0, 16.0) are properly clamped to [0, 65535]
 * including -Inf and +Inf. NaN values are considered undefined, and behavior may change
 * depending on hardware and future implementation of this function.
 */
static inline uint16_t u4_12_from_float(float f)
{
    static const float scale = (float)(1 << 12);
    static const float limpos = 0xffff / (float)(1 << 12);

    if (f <= 0.) {
        return 0;
    } else if (f >= limpos) {
        return 0xffff;
    }
    /* integer conversion is through truncation (though int to float is not).
     * ensure that we round to nearest, ties away from 0.
     */
    return f * scale + 0.5;
}

/* Convert a signed fixed-point 16-bit Q0.15 value to single-precision floating-point.
 * The output float range is [-1.0, 1.0) for the fixed-point range
 * [0x8000, 0x7fff].
 *
 * There is no rounding, the conversion and representation is exact.
 */
static inline float float_from_i16(int16_t ival)
{
    /* The scale factor is the reciprocal of the nominal 16 bit integer
     * half-sided range (32768).
     *
     * Since the scale factor is a power of 2, the scaling is exact, and there
     * is no rounding due to the multiplication - the bit pattern is preserved.
     */
    static const float scale = 1. / (float)(1UL << 15);

    return ival * scale;
}

/* Convert an unsigned fixed-point 8-bit U0.8 value to single-precision floating-point.
 * The nominal output float range is [-1.0, 1.0) if the fixed-point range is
 * [0x00, 0xff].
 */
static inline float float_from_u8(uint8_t uval)
{
    static const float scale = 1. / (float)(1UL << 7);

    return ((int)uval - 128) * scale;
}

/* Convert a packed 24bit Q0.23 value stored native-endian in a uint8_t ptr
 * to a signed fixed-point 32 bit integer Q0.31 value. The output Q0.31 range
 * is [0x80000000, 0x7fffff00] for the fixed-point range [0x800000, 0x7fffff].
 * Even though the output range is limited on the positive side, there is no
 * DC offset on the output, if the input has no DC offset.
 *
 * Avoid relying on the limited output range, as future implementations may go
 * to full range.
 */
static inline int32_t i32_from_p24(const uint8_t *packed24)
{
    /* convert to 32b */
    return (packed24[0] << 8) | (packed24[1] << 16) | (packed24[2] << 24);
}

/* Convert a 32-bit Q0.31 value to single-precision floating-point.
 * The output float range is [-1.0, 1.0] for the fixed-point range
 * [0x80000000, 0x7fffffff].
 *
 * Rounding may occur in the least significant 8 bits for large fixed point
 * values due to storage into the 24-bit floating-point significand.
 * Rounding will be to nearest, ties to even.
 */
static inline float float_from_i32(int32_t ival)
{
    static const float scale = 1. / (float)(1UL << 31);

    return ival * scale;
}

/* Convert a packed 24bit Q0.23 value stored native endian in a uint8_t ptr
 * to single-precision floating-point. The output float range is [-1.0, 1.0)
 * for the fixed-point range [0x800000, 0x7fffff].
 *
 * There is no rounding, the conversion and representation is exact.
 */
static inline float float_from_p24(const uint8_t *packed24)
{
    return float_from_i32(i32_from_p24(packed24));
}

/* Convert a 24-bit Q8.23 value to single-precision floating-point.
 * The nominal output float range is [-1.0, 1.0) for the fixed-point
 * range [0xff800000, 0x007fffff].  The maximum float range is [-256.0, 256.0).
 *
 * There is no rounding in the nominal range, the conversion and representation
 * is exact. For values outside the nominal range, rounding is to nearest, ties to even.
 */
static inline float float_from_q8_23(int32_t ival)
{
    static const float scale = 1. / (float)(1UL << 23);

    return ival * scale;
}

/**
 * Multiply-accumulate 16-bit terms with 32-bit result: return a + in*v.
 */
static inline
int32_t mulAdd(int16_t in, int16_t v, int32_t a)
{
#if defined(__arm__) && !defined(__thumb__)
    int32_t out;
    asm( "smlabb %[out], %[in], %[v], %[a] \n"
         : [out]"=r"(out)
         : [in]"%r"(in), [v]"r"(v), [a]"r"(a)
         : );
    return out;
#else
    return a + in * (int32_t)v;
#endif
}

/**
 * Multiply 16-bit terms with 32-bit result: return in*v.
 */
static inline
int32_t mul(int16_t in, int16_t v)
{
#if defined(__arm__) && !defined(__thumb__)
    int32_t out;
    asm( "smulbb %[out], %[in], %[v] \n"
         : [out]"=r"(out)
         : [in]"%r"(in), [v]"r"(v)
         : );
    return out;
#else
    return in * (int32_t)v;
#endif
}

/**
 * Similar to mulAdd, but the 16-bit terms are extracted from a 32-bit interleaved stereo pair.
 */
static inline
int32_t mulAddRL(int left, uint32_t inRL, uint32_t vRL, int32_t a)
{
#if defined(__arm__) && !defined(__thumb__)
    int32_t out;
    if (left) {
        asm( "smlabb %[out], %[inRL], %[vRL], %[a] \n"
             : [out]"=r"(out)
             : [inRL]"%r"(inRL), [vRL]"r"(vRL), [a]"r"(a)
             : );
    } else {
        asm( "smlatt %[out], %[inRL], %[vRL], %[a] \n"
             : [out]"=r"(out)
             : [inRL]"%r"(inRL), [vRL]"r"(vRL), [a]"r"(a)
             : );
    }
    return out;
#else
    if (left) {
        return a + (int16_t)(inRL&0xFFFF) * (int16_t)(vRL&0xFFFF);
    } else {
        return a + (int16_t)(inRL>>16) * (int16_t)(vRL>>16);
    }
#endif
}

/**
 * Similar to mul, but the 16-bit terms are extracted from a 32-bit interleaved stereo pair.
 */
static inline
int32_t mulRL(int left, uint32_t inRL, uint32_t vRL)
{
#if defined(__arm__) && !defined(__thumb__)
    int32_t out;
    if (left) {
        asm( "smulbb %[out], %[inRL], %[vRL] \n"
             : [out]"=r"(out)
             : [inRL]"%r"(inRL), [vRL]"r"(vRL)
             : );
    } else {
        asm( "smultt %[out], %[inRL], %[vRL] \n"
             : [out]"=r"(out)
             : [inRL]"%r"(inRL), [vRL]"r"(vRL)
             : );
    }
    return out;
#else
    if (left) {
        return (int16_t)(inRL&0xFFFF) * (int16_t)(vRL&0xFFFF);
    } else {
        return (int16_t)(inRL>>16) * (int16_t)(vRL>>16);
    }
#endif
}

__END_DECLS

#endif  // COCOS_AUDIO_PRIMITIVES_H
