#include "include/audio_utils/primitives.h"
#include "../utils/Utils.h"
using namespace cocos2d::experimental::utils;

void ditherAndClamp(int32_t *out, const int32_t *sums, size_t c) {
    size_t i;
    for (i = 0; i < c; i++) {
        int32_t l = *sums++;
        int32_t r = *sums++;
        int32_t nl = l >> 12;
        int32_t nr = r >> 12;
        l = clamp16(nl);
        r = clamp16(nr);
        *out++ = (r << 16) | (l & 0xFFFF);
    }
}

void memcpy_to_i16_from_u8(int16_t *dst, const uint8_t *src, size_t count) {
    dst += count;
    src += count;
    while (count--) {
        *--dst = static_cast<int16_t>(*--src - 0x80) << 8;
    }
}

void memcpy_to_u8_from_i16(uint8_t *dst, const int16_t *src, size_t count) {
    while (count--) {
        *dst++ = (*src++ >> 8) + 0x80;
    }
}

void memcpy_to_u8_from_float(uint8_t *dst, const float *src, size_t count) {
    while (count--) {
        *dst++ = clamp8_from_float(*src++);
    }
}

void memcpy_to_i16_from_i32(int16_t *dst, const int32_t *src, size_t count) {
    while (count--) {
        *dst++ = *src++ >> 16;
    }
}

void memcpy_to_i16_from_float(int16_t *dst, const float *src, size_t count) {
    while (count--) {
        *dst++ = clamp16_from_float(*src++);
    }
}

void memcpy_to_float_from_q4_27(float *dst, const int32_t *src, size_t count) {
    while (count--) {
        *dst++ = float_from_q4_27(*src++);
    }
}

void memcpy_to_float_from_i16(float *dst, const int16_t *src, size_t count) {
    while (count--) {
        *dst++ = float_from_i16(*src++);
    }
}

void memcpy_to_float_from_u8(float *dst, const uint8_t *src, size_t count) {
    while (count--) {
        *dst++ = float_from_u8(*src++);
    }
}

void memcpy_to_float_from_p24(float *dst, const uint8_t *src, size_t count) {
    while (count--) {
        *dst++ = float_from_p24(src);
        src += 3;
    }
}

void memcpy_to_i16_from_p24(int16_t *dst, const uint8_t *src, size_t count) {
    while (count--) {
#ifdef HAVE_BIG_ENDIAN
        *dst++ = src[1] | (src[0] << 8);
#else
        *dst++ = src[1] | (src[2] << 8);
#endif
        src += 3;
    }
}

void memcpy_to_i32_from_p24(int32_t *dst, const uint8_t *src, size_t count) {
    while (count--) {
#ifdef HAVE_BIG_ENDIAN
        *dst++ = (src[2] << 8) | (src[1] << 16) | (src[0] << 24);
#else
        *dst++ = (src[0] << 8) | (src[1] << 16) | (src[2] << 24);
#endif
        src += 3;
    }
}

void memcpy_to_p24_from_i16(uint8_t *dst, const int16_t *src, size_t count) {
    while (count--) {
#ifdef HAVE_BIG_ENDIAN
        *dst++ = *src >> 8;
        *dst++ = *src++;
        *dst++ = 0;
#else
        *dst++ = 0;
        *dst++ = *src;
        *dst++ = *src++ >> 8;
#endif
    }
}

void memcpy_to_p24_from_float(uint8_t *dst, const float *src, size_t count) {
    while (count--) {
        int32_t ival = clamp24_from_float(*src++);

#ifdef HAVE_BIG_ENDIAN
        *dst++ = ival >> 16;
        *dst++ = ival >> 8;
        *dst++ = ival;
#else
        *dst++ = ival;
        *dst++ = ival >> 8;
        *dst++ = ival >> 16;
#endif
    }
}

void memcpy_to_p24_from_q8_23(uint8_t *dst, const int32_t *src, size_t count) {
    while (count--) {
        int32_t ival = clamp24_from_q8_23(*src++);

#ifdef HAVE_BIG_ENDIAN
        *dst++ = ival >> 16;
        *dst++ = ival >> 8;
        *dst++ = ival;
#else
        *dst++ = ival;
        *dst++ = ival >> 8;
        *dst++ = ival >> 16;
#endif
    }
}

void memcpy_to_p24_from_i32(uint8_t *dst, const int32_t *src, size_t count) {
    while (count--) {
        int32_t ival = *src++ >> 8;

#ifdef HAVE_BIG_ENDIAN
        *dst++ = ival >> 16;
        *dst++ = ival >> 8;
        *dst++ = ival;
#else
        *dst++ = ival;
        *dst++ = ival >> 8;
        *dst++ = ival >> 16;
#endif
    }
}

void memcpy_to_q8_23_from_i16(int32_t *dst, const int16_t *src, size_t count) {
    while (count--) {
        *dst++ = static_cast<int32_t>(*src++) << 8;
    }
}

void memcpy_to_q8_23_from_float_with_clamp(int32_t *dst, const float *src, size_t count) {
    while (count--) {
        *dst++ = clamp24_from_float(*src++);
    }
}

void memcpy_to_q8_23_from_p24(int32_t *dst, const uint8_t *src, size_t count) {
    while (count--) {
#ifdef HAVE_BIG_ENDIAN
        *dst++ = (int8_t)src[0] << 16 | src[1] << 8 | src[2];
#else
        *dst++ = static_cast<int8_t>(src[2]) << 16 | src[1] << 8 | src[0];
#endif
        src += 3;
    }
}

void memcpy_to_q4_27_from_float(int32_t *dst, const float *src, size_t count) {
    while (count--) {
        *dst++ = clampq4_27_from_float(*src++);
    }
}

void memcpy_to_i16_from_q8_23(int16_t *dst, const int32_t *src, size_t count) {
    while (count--) {
        *dst++ = clamp16(*src++ >> 8);
    }
}

void memcpy_to_float_from_q8_23(float *dst, const int32_t *src, size_t count) {
    while (count--) {
        *dst++ = float_from_q8_23(*src++);
    }
}

void memcpy_to_i32_from_i16(int32_t *dst, const int16_t *src, size_t count) {
    while (count--) {
        *dst++ = static_cast<int32_t>(*src++) << 16;
    }
}

void memcpy_to_i32_from_float(int32_t *dst, const float *src, size_t count) {
    while (count--) {
        *dst++ = clamp32_from_float(*src++);
    }
}

void memcpy_to_float_from_i32(float *dst, const int32_t *src, size_t count) {
    while (count--) {
        *dst++ = float_from_i32(*src++);
    }
}

void downmix_to_mono_i16_from_stereo_i16(int16_t *dst, const int16_t *src, size_t count) {
    while (count--) {
        *dst++ = static_cast<int16_t>((static_cast<int32_t>(src[0]) + static_cast<int32_t>(src[1])) >> 1);
        src += 2;
    }
}

void upmix_to_stereo_i16_from_mono_i16(int16_t *dst, const int16_t *src, size_t count) {
    while (count--) {
        int32_t temp = *src++;
        dst[0] = temp;
        dst[1] = temp;
        dst += 2;
    }
}

void downmix_to_mono_float_from_stereo_float(float *dst, const float *src, size_t frames) {
    while (frames--) {
        *dst++ = (src[0] + src[1]) * 0.5;
        src += 2;
    }
}

void upmix_to_stereo_float_from_mono_float(float *dst, const float *src, size_t frames) {
    while (frames--) {
        float temp = *src++;
        dst[0] = temp;
        dst[1] = temp;
        dst += 2;
    }
}

size_t nonZeroMono32(const int32_t *samples, size_t count) {
    size_t nonZero = 0;
    while (count-- > 0) {
        if (*samples++ != 0) {
            nonZero++;
        }
    }
    return nonZero;
}

size_t nonZeroMono16(const int16_t *samples, size_t count) {
    size_t nonZero = 0;
    while (count-- > 0) {
        if (*samples++ != 0) {
            nonZero++;
        }
    }
    return nonZero;
}

size_t nonZeroStereo32(const int32_t *frames, size_t count) {
    size_t nonZero = 0;
    while (count-- > 0) {
        if (frames[0] != 0 || frames[1] != 0) {
            nonZero++;
        }
        frames += 2;
    }
    return nonZero;
}

size_t nonZeroStereo16(const int16_t *frames, size_t count) {
    size_t nonZero = 0;
    while (count-- > 0) {
        if (frames[0] != 0 || frames[1] != 0) {
            nonZero++;
        }
        frames += 2;
    }
    return nonZero;
}

/*
 * C macro to do channel mask copying independent of dst/src sample type.
 * Don't pass in any expressions for the macro arguments here.
 */
#define COPY_FRAME_BY_MASK(dst, dmask, src, smask, count, zero) \
    {                                                           \
        uint32_t bit, ormask;                                   \
        while ((count)--) {                                     \
            ormask = (dmask) | (smask);                         \
            while (ormask) {                                    \
                bit = ormask & -ormask; /* get lowest bit */    \
                ormask ^= bit;          /* remove lowest bit */ \
                if ((dmask)&bit) {                              \
                    *(dst)++ = (smask)&bit ? *(src)++ : (zero); \
                } else { /* source channel only */              \
                    ++(src);                                    \
                }                                               \
            }                                                   \
        }                                                       \
    }

void memcpy_by_channel_mask(void *dst, uint32_t dstMask,
                            const void *src, uint32_t srcMask, size_t sampleSize, size_t count) {
#if 0
    /* alternate way of handling memcpy_by_channel_mask by using the idxary */
    int8_t idxary[32];
    uint32_t src_channels = popcount(src_mask);
    uint32_t dst_channels =
            memcpy_by_index_array_initialization(idxary, 32, dst_mask, src_mask);

    memcpy_by_idxary(dst, dst_channels, src, src_channels, idxary, sample_size, count);
#else
    if (dstMask == srcMask) {
        memcpy(dst, src, sampleSize * popcount(dstMask) * count);
        return;
    }
    switch (sampleSize) {
        case 1: {
            auto *udst = static_cast<uint8_t *>(dst);
            const auto *usrc = static_cast<const uint8_t *>(src);

            COPY_FRAME_BY_MASK(udst, dstMask, usrc, srcMask, count, 0);
        } break;
        case 2: {
            auto *udst = static_cast<uint16_t *>(dst);
            const auto *usrc = static_cast<const uint16_t *>(src);

            COPY_FRAME_BY_MASK(udst, dstMask, usrc, srcMask, count, 0);
        } break;
        case 3: { /* could be slow.  use a struct to represent 3 bytes of data. */
            auto *udst = static_cast<uint8x3_t *>(dst);
            const auto *usrc = static_cast<const uint8x3_t *>(src);
            static const uint8x3_t ZERO{0,0,0}; /* tricky - we use this to zero out a sample */

            COPY_FRAME_BY_MASK(udst, dstMask, usrc, srcMask, count, ZERO);
        } break;
        case 4: {
            auto *udst = static_cast<uint32_t *>(dst);
            const auto *usrc = static_cast<const uint32_t *>(src);

            COPY_FRAME_BY_MASK(udst, dstMask, usrc, srcMask, count, 0);
        } break;
        default:
            abort(); /* illegal value */
            break;
    }
#endif
}

/*
 * C macro to do copying by index array, to rearrange samples
 * within a frame.  This is independent of src/dst sample type.
 * Don't pass in any expressions for the macro arguments here.
 */
#define COPY_FRAME_BY_IDX(dst, dst_channels, src, src_channels, idxary, count, zero) \
    {                                                                                \
        unsigned i;                                                                  \
        int index;                                                                   \
        while ((count)--) {                                                          \
            for (i = 0; i < (dst_channels); ++i) {                                   \
                index = (idxary)[i];                                                 \
                *(dst)++ = index < 0 ? (zero) : (src)[index];                        \
            }                                                                        \
            (src) += (src_channels);                                                 \
        }                                                                            \
    }

void memcpy_by_index_array(void *dst, uint32_t dstChannels,
                           const void *src, uint32_t srcChannels,
                           const int8_t *idxary, size_t sampleSize, size_t count) {
    switch (sampleSize) {
        case 1: {
            auto *udst = static_cast<uint8_t *>(dst);
            const auto *usrc = static_cast<const uint8_t *>(src);

            COPY_FRAME_BY_IDX(udst, dstChannels, usrc, srcChannels, idxary, count, 0); // NOLINT
        } break;
        case 2: {
            auto *udst = static_cast<uint16_t *>(dst);
            const auto *usrc = static_cast<const uint16_t *>(src);

            COPY_FRAME_BY_IDX(udst, dstChannels, usrc, srcChannels, idxary, count, 0); // NOLINT
        } break;
        case 3: { /* could be slow.  use a struct to represent 3 bytes of data. */
            auto *udst = static_cast<uint8x3_t *>(dst);
            const auto *usrc = static_cast<const uint8x3_t *>(src);
            static const uint8x3_t ZERO{0,0,0};

            COPY_FRAME_BY_IDX(udst, dstChannels, usrc, srcChannels, idxary, count, ZERO);
        } break;
        case 4: {
            auto *udst = static_cast<uint32_t *>(dst);
            const auto *usrc = static_cast<const uint32_t *>(src);

            COPY_FRAME_BY_IDX(udst, dstChannels, usrc, srcChannels, idxary, count, 0);
        } break;
        default:
            abort(); /* illegal value */
            break;
    }
}

size_t memcpy_by_index_array_initialization(int8_t *idxary, size_t idxcount,
                                            uint32_t dstMask, uint32_t srcMask) {
    size_t n = 0;
    int srcidx = 0;
    uint32_t bit;
    uint32_t ormask = srcMask | dstMask;

    while (ormask && n < idxcount) {
        bit = ormask & -ormask;          /* get lowest bit */
        ormask ^= bit;                   /* remove lowest bit */
        if (srcMask & dstMask & bit) { /* matching channel */
            idxary[n++] = srcidx++;
        } else if (srcMask & bit) { /* source channel only */
            ++srcidx;
        } else { /* destination channel only */
            idxary[n++] = -1;
        }
    }
    return n + popcount(ormask & dstMask);
}

size_t memcpy_by_index_array_initialization_src_index(int8_t *idxary, size_t idxcount,
                                                      uint32_t dstMask, uint32_t srcMask) {
    size_t dstCount = popcount(dstMask);
    if (idxcount == 0) {
        return dstCount;
    }
    if (dstCount > idxcount) {
        dstCount = idxcount;
    }

    size_t srcIdx;
    size_t dstIdx;
    for (srcIdx = 0, dstIdx = 0; dstIdx < dstCount; ++dstIdx) {
        if (srcMask & 1) {
            idxary[dstIdx] = srcIdx++;
        } else {
            idxary[dstIdx] = -1;
        }
        srcMask >>= 1;
    }
    return dstIdx;
}

size_t memcpy_by_index_array_initialization_dst_index(int8_t *idxary, size_t idxcount,
                                                      uint32_t dstMask, uint32_t srcMask) {
    size_t srcIdx;
    size_t dstIdx;
    size_t dstCount = popcount(dstMask);
    size_t srcCount = popcount(srcMask);
    if (idxcount == 0) {
        return dstCount;
    }
    if (dstCount > idxcount) {
        dstCount = idxcount;
    }
    for (srcIdx = 0, dstIdx = 0; dstIdx < dstCount; ++srcIdx) {
        if (dstMask & 1) {
            idxary[dstIdx++] = srcIdx < srcCount ? static_cast<signed>(srcIdx) : -1;
        }
        dstMask >>= 1;
    }
    return dstIdx;
}
//} // namespace
