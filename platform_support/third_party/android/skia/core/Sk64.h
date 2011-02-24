/*
 * Copyright (C) 2006 The Android Open Source Project
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

#ifndef Sk64_DEFINED
#define Sk64_DEFINED

#include "SkFixed.h"
#include "SkMath.h"

/** \class Sk64

    Sk64 is a 64-bit math package that does not require long long support from the compiler.
*/
struct Sk64 {
    int32_t  fHi;   //!< the high 32 bits of the number (including sign)
    uint32_t fLo;   //!< the low 32 bits of the number

    /** Returns non-zero if the Sk64 can be represented as a signed 32 bit integer
    */
    SkBool is32() const { return fHi == ((int32_t)fLo >> 31); }

    /** Returns non-zero if the Sk64 cannot be represented as a signed 32 bit integer
    */
    SkBool is64() const { return fHi != ((int32_t)fLo >> 31); }

    /** Returns non-zero if the Sk64 can be represented as a signed 48 bit integer. Used to know
        if we can shift the value down by 16 to treat it as a SkFixed.
    */
    SkBool isFixed() const;

    /** Return the signed 32 bit integer equivalent. Asserts that is32() returns non-zero.
    */
    int32_t get32() const { SkASSERT(this->is32()); return (int32_t)fLo; }

    /** Return the number >> 16. Asserts that this does not loose any significant high bits.
    */
    SkFixed getFixed() const {
        SkASSERT(this->isFixed());

        uint32_t sum = fLo + (1 << 15);
        int32_t  hi = fHi;
        if (sum < fLo) {
            hi += 1;
        }
        return (hi << 16) | (sum >> 16);
    }

    /** Return the number >> 30. Asserts that this does not loose any
        significant high bits.
    */
    SkFract getFract() const;

    /** Returns the square-root of the number as a signed 32 bit value. */
    int32_t getSqrt() const;

    /** Returns the number of leading zeros of the absolute value of this.
        Will return in the range [0..64]
    */
    int getClzAbs() const;

    /** Returns non-zero if the number is zero */
    SkBool  isZero() const { return (fHi | fLo) == 0; }

    /** Returns non-zero if the number is non-zero */
    SkBool  nonZero() const { return fHi | fLo; }

    /** Returns non-zero if the number is negative (number < 0) */
    SkBool  isNeg() const { return (uint32_t)fHi >> 31; }

    /** Returns non-zero if the number is positive (number > 0) */
    SkBool  isPos() const { return ~(fHi >> 31) & (fHi | fLo); }

    /** Returns -1,0,+1 based on the sign of the number */
    int     getSign() const { return (fHi >> 31) | Sk32ToBool(fHi | fLo); }

    /** Negate the number */
    void    negate();

    /** If the number < 0, negate the number
    */
    void    abs();

    /** Returns the number of bits needed to shift the Sk64 to the right
        in order to make it fit in a signed 32 bit integer.
    */
    int     shiftToMake32() const;

    /** Set the number to zero */
    void    setZero() { fHi = fLo = 0; }

    /** Set the high and low 32 bit values of the number */
    void    set(int32_t hi, uint32_t lo) { fHi = hi; fLo = lo; }

    /** Set the number to the specified 32 bit integer */
    void    set(int32_t a) { fHi = a >> 31; fLo = a; }

    /** Set the number to the product of the two 32 bit integers */
    void    setMul(int32_t a, int32_t b);

    /** extract 32bits after shifting right by bitCount.
        Note: itCount must be [0..63].
        Asserts that no significant high bits were lost.
    */
    int32_t getShiftRight(unsigned bitCount) const;

    /** Shift the number left by the specified number of bits.
        @param bits How far to shift left, must be [0..63]
    */
    void    shiftLeft(unsigned bits);

    /** Shift the number right by the specified number of bits.
        @param bits How far to shift right, must be [0..63]. This
        performs an arithmetic right-shift (sign extending).
    */
    void    shiftRight(unsigned bits);

    /** Shift the number right by the specified number of bits, but
        round the result.
        @param bits How far to shift right, must be [0..63]. This
        performs an arithmetic right-shift (sign extending).
    */
    void    roundRight(unsigned bits);

    /** Add the specified 32 bit integer to the number */
    void add(int32_t lo) {
        int32_t  hi = lo >> 31; // 0 or -1
        uint32_t sum = fLo + (uint32_t)lo;

        fHi = fHi + hi + (sum < fLo);
        fLo = sum;
    }
    
    /** Add the specified Sk64 to the number */
    void add(int32_t hi, uint32_t lo) {
        uint32_t sum = fLo + lo;

        fHi = fHi + hi + (sum < fLo);
        fLo = sum;
    }
    
    /** Add the specified Sk64 to the number */
    void    add(const Sk64& other) { this->add(other.fHi, other.fLo); }
    
    /** Subtract the specified Sk64 from the number. (*this) = (*this) - num
    */
    void    sub(const Sk64& num);
    
    /** Subtract the number from the specified Sk64. (*this) = num - (*this)
    */
    void    rsub(const Sk64& num);
    
    /** Multiply the number by the specified 32 bit integer
    */
    void    mul(int32_t);

    enum DivOptions {
        kTrunc_DivOption,   //!< truncate the result when calling div()
        kRound_DivOption    //!< round the result when calling div()
    };
    
    /** Divide the number by the specified 32 bit integer, using the specified
        divide option (either truncate or round).
    */
    void    div(int32_t, DivOptions);

    /** return (this + other >> 16) as a 32bit result */
    SkFixed addGetFixed(const Sk64& other) const {
        return this->addGetFixed(other.fHi, other.fLo);
    }

    /** return (this + Sk64(hi, lo) >> 16) as a 32bit result */
    SkFixed addGetFixed(int32_t hi, uint32_t lo) const {
#ifdef SK_DEBUG
        Sk64    tmp(*this);
        tmp.add(hi, lo);
#endif

        uint32_t sum = fLo + lo;
        hi += fHi + (sum < fLo);
        lo = sum;

        sum = lo + (1 << 15);
        if (sum < lo)
            hi += 1;

        hi = (hi << 16) | (sum >> 16);
        SkASSERT(hi == tmp.getFixed());
        return hi;
    }

    /** Return the result of dividing the number by denom, treating the answer
        as a SkFixed. (*this) << 16 / denom. It is an error for denom to be 0.
    */
    SkFixed getFixedDiv(const Sk64& denom) const;

    friend bool operator==(const Sk64& a, const Sk64& b) {
        return a.fHi == b.fHi && a.fLo == b.fLo;
    }

    friend bool operator!=(const Sk64& a, const Sk64& b) {
        return a.fHi != b.fHi || a.fLo != b.fLo;
    }
    
    friend bool operator<(const Sk64& a, const Sk64& b) {
        return a.fHi < b.fHi || (a.fHi == b.fHi && a.fLo < b.fLo);
    }
    
    friend bool operator<=(const Sk64& a, const Sk64& b) {
        return a.fHi < b.fHi || (a.fHi == b.fHi && a.fLo <= b.fLo);
    }
    
    friend bool operator>(const Sk64& a, const Sk64& b) {
        return a.fHi > b.fHi || (a.fHi == b.fHi && a.fLo > b.fLo);
    }
    
    friend bool operator>=(const Sk64& a, const Sk64& b) {
        return a.fHi > b.fHi || (a.fHi == b.fHi && a.fLo >= b.fLo);
    }

#ifdef SkLONGLONG
    SkLONGLONG getLongLong() const;
#endif
};

#endif

