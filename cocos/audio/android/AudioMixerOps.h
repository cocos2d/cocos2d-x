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

#pragma once

#include "audio/android/cutils/log.h"

namespace cocos2d {

/* Behavior of is_same<>::value is true if the types are identical,
 * false otherwise. Identical to the STL std::is_same.
 */
template<typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template<typename T>
struct is_same<T, T>  // partial specialization
{
    static const bool value = true;
};


/* MixMul is a multiplication operator to scale an audio input signal
 * by a volume gain, with the formula:
 *
 * O(utput) = I(nput) * V(olume)
 *
 * The output, input, and volume may have different types.
 * There are 27 variants, of which 14 are actually defined in an
 * explicitly templated class.
 *
 * The following type variables and the underlying meaning:
 *
 * Output type       TO: int32_t (Q4.27) or int16_t (Q.15) or float [-1,1]
 * Input signal type TI: int32_t (Q4.27) or int16_t (Q.15) or float [-1,1]
 * Volume type       TV: int32_t (U4.28) or int16_t (U4.12) or float [-1,1]
 *
 * For high precision audio, only the <TO, TI, TV> = <float, float, float>
 * needs to be accelerated. This is perhaps the easiest form to do quickly as well.
 *
 * A generic version is NOT defined to catch any mistake of using it.
 */

template <typename TO, typename TI, typename TV>
TO MixMul(TI value, TV volume);

template <>
inline int32_t MixMul<int32_t, int16_t, int16_t>(int16_t value, int16_t volume) {
    return value * volume;
}

template <>
inline int32_t MixMul<int32_t, int32_t, int16_t>(int32_t value, int16_t volume) {
    return (value >> 12) * volume;
}

template <>
inline int32_t MixMul<int32_t, int16_t, int32_t>(int16_t value, int32_t volume) {
    return value * (volume >> 16);
}

template <>
inline int32_t MixMul<int32_t, int32_t, int32_t>(int32_t value, int32_t volume) {
    return (value >> 12) * (volume >> 16);
}

template <>
inline float MixMul<float, float, int16_t>(float value, int16_t volume) {
    static const float norm = 1. / (1 << 12);
    return value * volume * norm;
}

template <>
inline float MixMul<float, float, int32_t>(float value, int32_t volume) {
    static const float norm = 1. / (1 << 28);
    return value * volume * norm;
}

template <>
inline int16_t MixMul<int16_t, float, int16_t>(float value, int16_t volume) {
    return clamp16_from_float(MixMul<float, float, int16_t>(value, volume));
}

template <>
inline int16_t MixMul<int16_t, float, int32_t>(float value, int32_t volume) {
    return clamp16_from_float(MixMul<float, float, int32_t>(value, volume));
}

template <>
inline float MixMul<float, int16_t, int16_t>(int16_t value, int16_t volume) {
    static const float norm = 1. / (1 << (15 + 12));
    return static_cast<float>(value) * static_cast<float>(volume) * norm;
}

template <>
inline float MixMul<float, int16_t, int32_t>(int16_t value, int32_t volume) {
    static const float norm = 1. / (1ULL << (15 + 28));
    return static_cast<float>(value) * static_cast<float>(volume) * norm;
}

template <>
inline int16_t MixMul<int16_t, int16_t, int16_t>(int16_t value, int16_t volume) {
    return clamp16(MixMul<int32_t, int16_t, int16_t>(value, volume) >> 12);
}

template <>
inline int16_t MixMul<int16_t, int32_t, int16_t>(int32_t value, int16_t volume) {
    return clamp16(MixMul<int32_t, int32_t, int16_t>(value, volume) >> 12);
}

template <>
inline int16_t MixMul<int16_t, int16_t, int32_t>(int16_t value, int32_t volume) {
    return clamp16(MixMul<int32_t, int16_t, int32_t>(value, volume) >> 12);
}

template <>
inline int16_t MixMul<int16_t, int32_t, int32_t>(int32_t value, int32_t volume) {
    return clamp16(MixMul<int32_t, int32_t, int32_t>(value, volume) >> 12);
}

/* Required for floating point volume.  Some are needed for compilation but
 * are not needed in execution and should be removed from the final build by
 * an optimizing compiler.
 */
template <>
inline float MixMul<float, float, float>(float value, float volume) {
    return value * volume;
}

template <>
inline float MixMul<float, int16_t, float>(int16_t value, float volume) {
    static const float float_from_q_15 = 1. / (1 << 15);
    return value * volume * float_from_q_15;
}

template <>
inline int32_t MixMul<int32_t, int32_t, float>(int32_t value, float volume) {
    LOG_ALWAYS_FATAL("MixMul<int32_t, int32_t, float> Runtime Should not be here");
    return value * volume;
}

template <>
inline int32_t MixMul<int32_t, int16_t, float>(int16_t value, float volume) {
    LOG_ALWAYS_FATAL("MixMul<int32_t, int16_t, float> Runtime Should not be here");
    static const float u4_12_from_float = (1 << 12);
    return value * volume * u4_12_from_float;
}

template <>
inline int16_t MixMul<int16_t, int16_t, float>(int16_t value, float volume) {
    LOG_ALWAYS_FATAL("MixMul<int16_t, int16_t, float> Runtime Should not be here");
    return clamp16_from_float(MixMul<float, int16_t, float>(value, volume));
}

template <>
inline int16_t MixMul<int16_t, float, float>(float value, float volume) {
    return clamp16_from_float(value * volume);
}

/*
 * MixAccum is used to add into an accumulator register of a possibly different
 * type. The TO and TI types are the same as MixMul.
 */

template <typename TO, typename TI>
inline void MixAccum(TO *auxaccum, TI value) {
    if (!is_same<TO, TI>::value) {
        LOG_ALWAYS_FATAL("MixAccum type not properly specialized: %zu %zu\n",
                sizeof(TO), sizeof(TI));
    }
    *auxaccum += value;
}

template<>
inline void MixAccum<float, int16_t>(float *auxaccum, int16_t value) {
    static const float norm = 1. / (1 << 15);
    *auxaccum += norm * value;
}

template<>
inline void MixAccum<float, int32_t>(float *auxaccum, int32_t value) {
    static const float norm = 1. / (1 << 27);
    *auxaccum += norm * value;
}

template<>
inline void MixAccum<int32_t, int16_t>(int32_t *auxaccum, int16_t value) {
    *auxaccum += value << 12;
}

template<>
inline void MixAccum<int32_t, float>(int32_t *auxaccum, float value) {
    *auxaccum += clampq4_27_from_float(value);
}

/* MixMulAux is just like MixMul except it combines with
 * an accumulator operation MixAccum.
 */

template <typename TO, typename TI, typename TV, typename TA>
inline TO MixMulAux(TI value, TV volume, TA *auxaccum) {
    MixAccum<TA, TI>(auxaccum, value);
    return MixMul<TO, TI, TV>(value, volume);
}

/* MIXTYPE is used to determine how the samples in the input frame
 * are mixed with volume gain into the output frame.
 * See the volumeRampMulti functions below for more details.
 */
enum {
    MIXTYPE_MULTI,
    MIXTYPE_MONOEXPAND,
    MIXTYPE_MULTI_SAVEONLY,
    MIXTYPE_MULTI_MONOVOL,
    MIXTYPE_MULTI_SAVEONLY_MONOVOL,
};

/*
 * The volumeRampMulti and volumeRamp functions take a MIXTYPE
 * which indicates the per-frame mixing and accumulation strategy.
 *
 * MIXTYPE_MULTI:
 *   NCHAN represents number of input and output channels.
 *   TO: int32_t (Q4.27) or float
 *   TI: int32_t (Q4.27) or int16_t (Q0.15) or float
 *   TV: int32_t (U4.28) or int16_t (U4.12) or float
 *   vol: represents a volume array.
 *
 *   This accumulates into the out pointer.
 *
 * MIXTYPE_MONOEXPAND:
 *   Single input channel. NCHAN represents number of output channels.
 *   TO: int32_t (Q4.27) or float
 *   TI: int32_t (Q4.27) or int16_t (Q0.15) or float
 *   TV: int32_t (U4.28) or int16_t (U4.12) or float
 *   Input channel count is 1.
 *   vol: represents volume array.
 *
 *   This accumulates into the out pointer.
 *
 * MIXTYPE_MULTI_SAVEONLY:
 *   NCHAN represents number of input and output channels.
 *   TO: int16_t (Q.15) or float
 *   TI: int32_t (Q4.27) or int16_t (Q0.15) or float
 *   TV: int32_t (U4.28) or int16_t (U4.12) or float
 *   vol: represents a volume array.
 *
 *   MIXTYPE_MULTI_SAVEONLY does not accumulate into the out pointer.
 *
 * MIXTYPE_MULTI_MONOVOL:
 *   Same as MIXTYPE_MULTI, but uses only volume[0].
 *
 * MIXTYPE_MULTI_SAVEONLY_MONOVOL:
 *   Same as MIXTYPE_MULTI_SAVEONLY, but uses only volume[0].
 *
 */

template <int MIXTYPE, int NCHAN,
        typename TO, typename TI, typename TV, typename TA, typename TAV>
inline void volumeRampMulti(TO* out, size_t frameCount,
        const TI* in, TA* aux, TV *vol, const TV *volinc, TAV *vola, TAV volainc)
{
#ifdef ALOGVV
    ALOGVV("volumeRampMulti, MIXTYPE:%d\n", MIXTYPE);
#endif
    if (aux != NULL) {
        do {
            TA auxaccum = 0;
            switch (MIXTYPE) {
            case MIXTYPE_MULTI:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMulAux<TO, TI, TV, TA>(*in++, vol[i], &auxaccum);
                    vol[i] += volinc[i];
                }
                break;
            case MIXTYPE_MONOEXPAND:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMulAux<TO, TI, TV, TA>(*in, vol[i], &auxaccum);
                    vol[i] += volinc[i];
                }
                in++;
                break;
            case MIXTYPE_MULTI_SAVEONLY:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMulAux<TO, TI, TV, TA>(*in++, vol[i], &auxaccum);
                    vol[i] += volinc[i];
                }
                break;
            case MIXTYPE_MULTI_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMulAux<TO, TI, TV, TA>(*in++, vol[0], &auxaccum);
                }
                vol[0] += volinc[0];
                break;
            case MIXTYPE_MULTI_SAVEONLY_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMulAux<TO, TI, TV, TA>(*in++, vol[0], &auxaccum);
                }
                vol[0] += volinc[0];
                break;
            default:
                LOG_ALWAYS_FATAL("invalid mixtype %d", MIXTYPE);
                break;
            }
            auxaccum /= NCHAN;
            *aux++ += MixMul<TA, TA, TAV>(auxaccum, *vola);
            vola[0] += volainc;
        } while (--frameCount);
    } else {
        do {
            switch (MIXTYPE) {
            case MIXTYPE_MULTI:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMul<TO, TI, TV>(*in++, vol[i]);
                    vol[i] += volinc[i];
                }
                break;
            case MIXTYPE_MONOEXPAND:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMul<TO, TI, TV>(*in, vol[i]);
                    vol[i] += volinc[i];
                }
                in++;
                break;
            case MIXTYPE_MULTI_SAVEONLY:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMul<TO, TI, TV>(*in++, vol[i]);
                    vol[i] += volinc[i];
                }
                break;
            case MIXTYPE_MULTI_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMul<TO, TI, TV>(*in++, vol[0]);
                }
                vol[0] += volinc[0];
                break;
            case MIXTYPE_MULTI_SAVEONLY_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMul<TO, TI, TV>(*in++, vol[0]);
                }
                vol[0] += volinc[0];
                break;
            default:
                LOG_ALWAYS_FATAL("invalid mixtype %d", MIXTYPE);
                break;
            }
        } while (--frameCount);
    }
}

template <int MIXTYPE, int NCHAN,
        typename TO, typename TI, typename TV, typename TA, typename TAV>
inline void volumeMulti(TO* out, size_t frameCount,
        const TI* in, TA* aux, const TV *vol, TAV vola)
{
#ifdef ALOGVV
    ALOGVV("volumeMulti MIXTYPE:%d\n", MIXTYPE);
#endif
    if (aux != NULL) {
        do {
            TA auxaccum = 0;
            switch (MIXTYPE) {
            case MIXTYPE_MULTI:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMulAux<TO, TI, TV, TA>(*in++, vol[i], &auxaccum);
                }
                break;
            case MIXTYPE_MONOEXPAND:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMulAux<TO, TI, TV, TA>(*in, vol[i], &auxaccum);
                }
                in++;
                break;
            case MIXTYPE_MULTI_SAVEONLY:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMulAux<TO, TI, TV, TA>(*in++, vol[i], &auxaccum);
                }
                break;
            case MIXTYPE_MULTI_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMulAux<TO, TI, TV, TA>(*in++, vol[0], &auxaccum);
                }
                break;
            case MIXTYPE_MULTI_SAVEONLY_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMulAux<TO, TI, TV, TA>(*in++, vol[0], &auxaccum);
                }
                break;
            default:
                LOG_ALWAYS_FATAL("invalid mixtype %d", MIXTYPE);
                break;
            }
            auxaccum /= NCHAN;
            *aux++ += MixMul<TA, TA, TAV>(auxaccum, vola);
        } while (--frameCount);
    } else {
        do {
            switch (MIXTYPE) {
            case MIXTYPE_MULTI:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMul<TO, TI, TV>(*in++, vol[i]);
                }
                break;
            case MIXTYPE_MONOEXPAND:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMul<TO, TI, TV>(*in, vol[i]);
                }
                in++;
                break;
            case MIXTYPE_MULTI_SAVEONLY:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMul<TO, TI, TV>(*in++, vol[i]);
                }
                break;
            case MIXTYPE_MULTI_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ += MixMul<TO, TI, TV>(*in++, vol[0]);
                }
                break;
            case MIXTYPE_MULTI_SAVEONLY_MONOVOL:
                for (int i = 0; i < NCHAN; ++i) {
                    *out++ = MixMul<TO, TI, TV>(*in++, vol[0]);
                }
                break;
            default:
                LOG_ALWAYS_FATAL("invalid mixtype %d", MIXTYPE);
                break;
            }
        } while (--frameCount);
    }
}

} // namespace cocos2d {

