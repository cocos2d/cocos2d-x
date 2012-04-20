/*
 * Copyright (C) 2006-2008 The Android Open Source Project
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

#ifndef SkFloat_DEFINED
#define SkFloat_DEFINED

#include "SkFixed.h"

class SkFloat {
public:
    SkFloat() {}

    void    setZero() { fPacked = 0; }
//  void    setShift(int value, int shift) { fPacked = SetShift(value, shift); }
    void    setInt(int value) { fPacked = SetShift(value, 0); }
    void    setFixed(SkFixed value) { fPacked = SetShift(value, -16); }
    void    setFract(SkFract value) { fPacked = SetShift(value, -30); }

//  int     getShift(int shift) const { return GetShift(fPacked, shift); }
    int     getInt() const { return GetShift(fPacked, 0); }
    SkFixed getFixed() const { return GetShift(fPacked, -16); }
    SkFract getFract() const { return GetShift(fPacked, -30); }

    void    abs() { fPacked = Abs(fPacked); }
    void    negate() { fPacked = Neg(fPacked); }

    void    shiftLeft(int bits) { fPacked = Shift(fPacked, bits); }
    void    setShiftLeft(const SkFloat& a, int bits) { fPacked = Shift(a.fPacked, bits); }

    void    shiftRight(int bits) { fPacked = Shift(fPacked, -bits); }
    void    setShiftRight(const SkFloat& a, int bits) { fPacked = Shift(a.fPacked, -bits); }

    void    add(const SkFloat& a) { fPacked = Add(fPacked, a.fPacked); }
    void    setAdd(const SkFloat& a, const SkFloat& b) { fPacked = Add(a.fPacked, b.fPacked); }

    void    sub(const SkFloat& a) { fPacked = Add(fPacked, Neg(a.fPacked)); }
    void    setSub(const SkFloat& a, const SkFloat& b) { fPacked = Add(a.fPacked, Neg(b.fPacked)); }

    void    mul(const SkFloat& a) { fPacked = Mul(fPacked, a.fPacked); }
    void    setMul(const SkFloat& a, const SkFloat& b) { fPacked = Mul(a.fPacked, b.fPacked); }

    void    div(const SkFloat& a) { fPacked = Div(fPacked, a.fPacked); }
    void    setDiv(const SkFloat& a, const SkFloat& b) { fPacked = Div(a.fPacked, b.fPacked); }

    void    sqrt() { fPacked = Sqrt(fPacked); }
    void    setSqrt(const SkFloat& a) { fPacked = Sqrt(a.fPacked); }
    void    cubeRoot() { fPacked = CubeRoot(fPacked); }
    void    setCubeRoot(const SkFloat& a) { fPacked = CubeRoot(a.fPacked); }

    friend bool operator==(const SkFloat& a, const SkFloat& b) { return a.fPacked == b.fPacked; }
    friend bool operator!=(const SkFloat& a, const SkFloat& b) { return a.fPacked != b.fPacked; }
    friend bool operator<(const SkFloat& a, const SkFloat& b) { return Cmp(a.fPacked, b.fPacked) < 0; }
    friend bool operator<=(const SkFloat& a, const SkFloat& b) { return Cmp(a.fPacked, b.fPacked) <= 0; }
    friend bool operator>(const SkFloat& a, const SkFloat& b) { return Cmp(a.fPacked, b.fPacked) > 0; }
    friend bool operator>=(const SkFloat& a, const SkFloat& b) { return Cmp(a.fPacked, b.fPacked) >= 0; }

#ifdef SK_DEBUG
    static void UnitTest();

    void assertEquals(float f, int tolerance = 0)
    {
        union {
            float   fFloat;
            int32_t fPacked;
        } tmp;
        
        tmp.fFloat = f;
        int d = tmp.fPacked - fPacked;
        SkASSERT(SkAbs32(d) <= tolerance);
    }
    float getFloat() const
    {
        union {
            float   fFloat;
            int32_t fPacked;
        } tmp;
        
        tmp.fPacked = fPacked;
        return tmp.fFloat;
    }
#endif

private:
    int32_t fPacked;

public:
    static int GetShift(int32_t packed, int shift);
    static int32_t SetShift(int value, int shift);
    static int32_t Neg(int32_t);
    static int32_t Abs(int32_t packed) { return (uint32_t)(packed << 1) >> 1; }
    static int32_t Shift(int32_t, int bits);
    static int32_t Add(int32_t, int32_t);
    static int32_t Mul(int32_t, int32_t);
    static int32_t MulInt(int32_t, int);
    static int32_t Div(int32_t, int32_t);
    static int32_t DivInt(int32_t, int);
    static int32_t Invert(int32_t);
    static int32_t Sqrt(int32_t);
    static int32_t CubeRoot(int32_t);
    static int Cmp(int32_t, int32_t);
};

#endif
