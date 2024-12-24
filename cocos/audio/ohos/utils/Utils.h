/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include <algorithm>
#include <bitset>
#include <cerrno>
#include <climits>
#include <limits>
#include <cstdint>
#include <type_traits>
#include "../Macros.h"

#include <string>
#include <vector>
/** @file ccUtils.h
Misc free functions
*/

namespace cocos2d {
namespace utils {
std::string getStacktrace(uint32_t skip = 0, uint32_t maxDepth = UINT32_MAX);

/**
 * Returns the Next Power of Two value.
 * Examples:
 * - If "value" is 15, it will return 16.
 * - If "value" is 16, it will return 16.
 * - If "value" is 17, it will return 32.
 * @param value The value to get next power of two.
 * @return Returns the next power of two value.
 * @since v0.99.5
*/
uint32_t nextPOT(uint32_t x);

/**
 * Same to ::atof, but strip the string, remain 7 numbers after '.' before call atof.
 * Why we need this? Because in android c++_static, atof ( and std::atof ) is unsupported for numbers have long decimal part and contain
 * several numbers can approximate to 1 ( like 90.099998474121094 ), it will return inf. This function is used to fix this bug.
 * @param str The string be to converted to double.
 * @return Returns converted value of a string.
 */
double atof(const char *str);

#pragma warning(disable : 4146)
template <typename T, typename = typename std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value>>
inline T getLowestBit(T mask) {
    return mask & (-mask);
}
#pragma warning(default : 4146)

template <typename T, typename = typename std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value>>
inline T clearLowestBit(T mask) {
    return mask & (mask - 1);
}

// v must be power of 2
inline uint32_t getBitPosition(uint32_t v) {
    if (!v) return 0;
    uint32_t c = 32;
    if (v & 0x0000FFFF) c -= 16;
    if (v & 0x00FF00FF) c -= 8;
    if (v & 0x0F0F0F0F) c -= 4;
    if (v & 0x33333333) c -= 2;
    if (v & 0x55555555) c -= 1;
    return c;
}

// v must be power of 2
inline uint64_t getBitPosition(uint64_t v) {
    if (!v) return 0;
    uint64_t c = 64;
    if (v & 0x00000000FFFFFFFFLL) c -= 32;
    if (v & 0x0000FFFF0000FFFFLL) c -= 16;
    if (v & 0x00FF00FF00FF00FFLL) c -= 8;
    if (v & 0x0F0F0F0F0F0F0F0FLL) c -= 4;
    if (v & 0x3333333333333333LL) c -= 2;
    if (v & 0x5555555555555555LL) c -= 1;
    return c;
}

template <typename T, typename = typename std::enable_if_t<std::is_integral<T>::value>>
inline size_t popcount(T mask) {
    return std::bitset<sizeof(T)>(mask).count();
}

template <typename T, typename = typename std::enable_if_t<std::is_integral<T>::value>>
inline T alignTo(T size, T alignment) {
    return ((size - 1) / alignment + 1) * alignment;
}

template <uint32_t size, uint32_t alignment>
constexpr uint32_t ALIGN_TO = ((size - 1) / alignment + 1) * alignment;

template <class T>
inline uint32_t toUint(T value) {
    static_assert(std::is_arithmetic<T>::value, "T must be numeric");

    CC_ASSERT(static_cast<uintmax_t>(value) <= static_cast<uintmax_t>(std::numeric_limits<uint32_t>::max()));

    return static_cast<uint32_t>(value);
}

template <typename Map>
Map &mergeToMap(Map &outMap, const Map &inMap) {
    for (const auto &e : inMap) {
        outMap.emplace(e.first, e.second);
    }
    return outMap;
}

namespace numext {

template <typename Tgt, typename Src>
CC_FORCE_INLINE Tgt bit_cast(const Src &src) { // NOLINT(readability-identifier-naming)
    // The behaviour of memcpy is not specified for non-trivially copyable types
    static_assert(std::is_trivially_copyable<Src>::value, "THIS_TYPE_IS_NOT_SUPPORTED");
    static_assert(std::is_trivially_copyable<Tgt>::value && std::is_default_constructible<Tgt>::value,
                  "THIS_TYPE_IS_NOT_SUPPORTED");
    static_assert(sizeof(Src) == sizeof(Tgt), "THIS_TYPE_IS_NOT_SUPPORTED");

    Tgt tgt;
    // Load src into registers first. This allows the memcpy to be elided by CUDA.
    const Src staged = src;
    memcpy(&tgt, &staged, sizeof(Tgt));
    return tgt;
}

} // namespace numext

// Following the Arm ACLE arm_neon.h should also include arm_fp16.h but not all
// compilers seem to follow this. We therefore include it explicitly.
// See also: https://bugs.llvm.org/show_bug.cgi?id=47955
#if defined(CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC)
    #include <arm_fp16.h>
#endif

// Code from https://gitlab.com/libeigen/eigen/-/blob/master/Eigen/src/Core/arch/Default/Half.h#L586
struct HalfRaw {
    constexpr HalfRaw() : x(0) {}
#if defined(CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC)
    explicit HalfRaw(uint16_t raw) : x(numext::bit_cast<__fp16>(raw)) {
    }
    __fp16 x;
#else
    explicit constexpr HalfRaw(uint16_t raw) : x(raw) {}
    uint16_t x; // NOLINT(modernize-use-default-member-init)
#endif
};

// Conversion routines, including fallbacks for the host or older CUDA.
// Note that newer Intel CPUs (Haswell or newer) have vectorized versions of
// these in hardware. If we need more performance on older/other CPUs, they are
// also possible to vectorize directly.

CC_FORCE_INLINE HalfRaw rawUint16ToHalf(uint16_t x) {
    // We cannot simply do a "return HalfRaw(x)" here, because HalfRaw is union type
    // in the hip_fp16 header file, and that will trigger a compile error
    // On the other hand, having anything but a return statement also triggers a compile error
    // because this is constexpr function.
    // Fortunately, since we need to disable EIGEN_CONSTEXPR for GPU anyway, we can get out
    // of this catch22 by having separate bodies for GPU / non GPU
#if defined(CC_HAS_GPU_FP16)
    HalfRaw h;
    h.x = x;
    return h;
#else
    return HalfRaw(x);
#endif
}

CC_FORCE_INLINE uint16_t rawHalfAsUint16(const HalfRaw &h) {
    // HIP/CUDA/Default have a member 'x' of type uint16_t.
    // For ARM64 native half, the member 'x' is of type __fp16, so we need to bit-cast.
    // For SYCL, cl::sycl::half is _Float16, so cast directly.
#if defined(CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC)
    return numext::bit_cast<uint16_t>(h.x);
#else
    return h.x;
#endif
}

union float32_bits {
    unsigned int u;
    float f;
};

CC_FORCE_INLINE HalfRaw floatToHalf(float ff) {
#if defined(CC_HAS_FP16_C)
    HalfRaw h;
    #ifdef _MSC_VER
    // MSVC does not have scalar instructions.
    h.x = _mm_extract_epi16(_mm_cvtps_ph(_mm_set_ss(ff), 0), 0);
    #else
    h.x = _cvtss_sh(ff, 0);
    #endif
    return h;

#elif defined(CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC)
    HalfRaw h;
    h.x = static_cast<__fp16>(ff);
    return h;

#else
    float32_bits f;
    f.f = ff;

    const float32_bits f32infty = {255 << 23};
    const float32_bits f16max = {(127 + 16) << 23};
    const float32_bits denorm_magic = {((127 - 15) + (23 - 10) + 1) << 23}; // NOLINT(readability-identifier-naming)
    unsigned int sign_mask = 0x80000000U;                                   // NOLINT
    HalfRaw o;
    o.x = static_cast<uint16_t>(0x0U);

    unsigned int sign = f.u & sign_mask;
    f.u ^= sign;

    // NOTE all the integer compares in this function can be safely
    // compiled into signed compares since all operands are below
    // 0x80000000. Important if you want fast straight SSE2 code
    // (since there's no unsigned PCMPGTD).

    if (f.u >= f16max.u) {                          // result is Inf or NaN (all exponent bits set)
        o.x = (f.u > f32infty.u) ? 0x7e00 : 0x7c00; // NaN->qNaN and Inf->Inf
    } else {                                        // (De)normalized number or zero
        if (f.u < (113 << 23)) {                    // resulting FP16 is subnormal or zero
            // use a magic value to align our 10 mantissa bits at the bottom of
            // the float. as long as FP addition is round-to-nearest-even this
            // just works.
            f.f += denorm_magic.f;

            // and one integer subtract of the bias later, we have our final float!
            o.x = static_cast<uint16_t>(f.u - denorm_magic.u);
        } else {
            unsigned int mant_odd = (f.u >> 13) & 1; // NOLINT(readability-identifier-naming) // resulting mantissa is odd

            // update exponent, rounding bias part 1
            // Equivalent to `f.u += ((unsigned int)(15 - 127) << 23) + 0xfff`, but
            // without arithmetic overflow.
            f.u += 0xc8000fffU;
            // rounding bias part 2
            f.u += mant_odd;
            // take the bits!
            o.x = static_cast<uint16_t>(f.u >> 13);
        }
    }

    o.x |= static_cast<uint16_t>(sign >> 16);
    return o;
#endif
}

CC_FORCE_INLINE float halfToFloat(HalfRaw h) {
#if defined(CC_HAS_FP16_C)
    #ifdef _MSC_VER
    // MSVC does not have scalar instructions.
    return _mm_cvtss_f32(_mm_cvtph_ps(_mm_set1_epi16(h.x)));
    #else
    return _cvtsh_ss(h.x);
    #endif
#elif defined(CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC)
    return static_cast<float>(h.x);
#else
    const float32_bits magic = {113 << 23};
    const unsigned int shifted_exp = 0x7c00 << 13; // NOLINT(readability-identifier-naming) // exponent mask after shift
    float32_bits o;

    o.u = (h.x & 0x7fff) << 13;           // exponent/mantissa bits
    unsigned int exp = shifted_exp & o.u; // just the exponent
    o.u += (127 - 15) << 23;              // exponent adjust

    // handle exponent special cases
    if (exp == shifted_exp) {    // Inf/NaN?
        o.u += (128 - 16) << 23; // extra exp adjust
    } else if (exp == 0) {       // Zero/Denormal?
        o.u += 1 << 23;          // extra exp adjust
        o.f -= magic.f;          // renormalize
    }

    o.u |= (h.x & 0x8000) << 16; // sign bit
    return o.f;
#endif
}

namespace array {

/**
 * @zh
 * 移除首个指定的数组元素。判定元素相等时相当于于使用了 `Array.prototype.indexOf`。
 * @en
 * Removes the first occurrence of a specific object from the array.
 * Decision of the equality of elements is similar to `Array.prototype.indexOf`.
 * @param array 数组。
 * @param value 待移除元素。
 */
template <typename T>
bool remove(std::vector<T> &array, T value) {
    auto iter = std::find(array.begin(), array.end(), value);
    if (iter != array.end()) {
        array.erase(iter);
        return true;
    }
    return false;
}

/**
 * @zh
 * 移除指定索引的数组元素。
 * @en
 * Removes the array item at the specified index.
 * @param array 数组。
 * @param index 待移除元素的索引。
 */
template <typename T>
bool removeAt(std::vector<T> &array, int32_t index) {
    if (index >= 0 && index < static_cast<int32_t>(array.size())) {
        array.erase(array.begin() + index);
        return true;
    }
    return false;
}

/**
 * @zh
 * 移除指定索引的数组元素。
 * 此函数十分高效，但会改变数组的元素次序。
 * @en
 * Removes the array item at the specified index.
 * It's faster but the order of the array will be changed.
 * @param array 数组。
 * @param index 待移除元素的索引。
 */
template <typename T>
bool fastRemoveAt(std::vector<T> &array, int32_t index) {
    const auto length = static_cast<int32_t>(array.size());
    if (index < 0 || index >= length) {
        return false;
    }
    array[index] = array[length - 1];
    array.resize(length - 1);
    return true;
}

/**
 * @zh
 * 移除首个指定的数组元素。判定元素相等时相当于于使用了 `Array.prototype.indexOf`。
 * 此函数十分高效，但会改变数组的元素次序。
 * @en
 * Removes the first occurrence of a specific object from the array.
 * Decision of the equality of elements is similar to `Array.prototype.indexOf`.
 * It's faster but the order of the array will be changed.
 * @param array 数组。
 * @param value 待移除元素。
 */
template <typename T>
bool fastRemove(std::vector<T> &array, T value) {
    auto iter = std::find(array.begin(), array.end(), value);
    if (iter != array.end()) {
        *iter = array[array.size() - 1];
        array.resize(array.size() - 1);
        return true;
    }
    return false;
}

} // namespace array
} // namespace utils
} // namespace cc
