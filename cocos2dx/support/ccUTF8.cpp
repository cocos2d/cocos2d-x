/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "ccUTF8.h"
#include "platform/CCCommon.h"

/** source code from ConvertUTF.c */

/*===--- ConvertUTF.c - Universal Character Names conversions ---------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is distributed under the University of Illinois Open Source
 * License. See LICENSE.TXT for details.
 *
 *===------------------------------------------------------------------------=*/
/*
 * Copyright 2001-2004 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------
 
 Conversions between UTF32, UTF-16, and UTF-8. Source code file.
 Author: Mark E. Davis, 1994.
 Rev History: Rick McGowan, fixes & updates May 2001.
 Sept 2001: fixed const & error conditions per
 mods suggested by S. Parent & A. Lillich.
 June 2002: Tim Dodd added detection and handling of incomplete
 source sequences, enhanced error detection, added casts
 to eliminate compiler warnings.
 July 2003: slight mods to back out aggressive FFFE detection.
 Jan 2004: updated switches in from-UTF8 conversions.
 Oct 2004: updated to use UNI_MAX_LEGAL_UTF32 in UTF-32 conversions.
 
 See the header file "ConvertUTF.h" for complete documentation.
 
 ------------------------------------------------------------------------ */


#ifdef CVTUTF_DEBUG
#include <stdio.h>
#endif


/** source codes from ConvertUTF.h */

/*===--- ConvertUTF.h - Universal Character Names conversions ---------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is distributed under the University of Illinois Open Source
 * License. See LICENSE.TXT for details.
 *
 *==------------------------------------------------------------------------==*/
/*
 * Copyright 2001-2004 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------
 
 Conversions between UTF32, UTF-16, and UTF-8.  Header file.
 
 Several funtions are included here, forming a complete set of
 conversions between the three formats.  UTF-7 is not included
 here, but is handled in a separate source file.
 
 Each of these routines takes pointers to input buffers and output
 buffers.  The input buffers are const.
 
 Each routine converts the text between *sourceStart and sourceEnd,
 putting the result into the buffer between *targetStart and
 targetEnd. Note: the end pointers are *after* the last item: e.g.
 *(sourceEnd - 1) is the last item.
 
 The return result indicates whether the conversion was successful,
 and if not, whether the problem was in the source or target buffers.
 (Only the first encountered problem is indicated.)
 
 After the conversion, *sourceStart and *targetStart are both
 updated to point to the end of last text successfully converted in
 the respective buffers.
 
 Input parameters:
 sourceStart - pointer to a pointer to the source buffer.
 The contents of this are modified on return so that
 it points at the next thing to be converted.
 targetStart - similarly, pointer to pointer to the target buffer.
 sourceEnd, targetEnd - respectively pointers to the ends of the
 two buffers, for overflow checking only.
 
 These conversion functions take a ConversionFlags argument. When this
 flag is set to strict, both irregular sequences and isolated surrogates
 will cause an error.  When the flag is set to lenient, both irregular
 sequences and isolated surrogates are converted.
 
 Whether the flag is strict or lenient, all illegal sequences will cause
 an error return. This includes sequences such as: <F4 90 80 80>, <C0 80>,
 or <A0> in UTF-8, and values above 0x10FFFF in UTF-32. Conformant code
 must check for illegal sequences.
 
 When the flag is set to lenient, characters over 0x10FFFF are converted
 to the replacement character; otherwise (when the flag is set to strict)
 they constitute an error.
 
 Output parameters:
 The value "sourceIllegal" is returned from some routines if the input
 sequence is malformed.  When "sourceIllegal" is returned, the source
 value will point to the illegal value that caused the problem. E.g.,
 in UTF-8 when a sequence is malformed, it points to the start of the
 malformed sequence.
 
 Author: Mark E. Davis, 1994.
 Rev History: Rick McGowan, fixes & updates May 2001.
 Fixes & updates, Sept 2001.
 
 ------------------------------------------------------------------------ */

//#ifndef LLVM_SUPPORT_CONVERTUTF_H
//#define LLVM_SUPPORT_CONVERTUTF_H

#include <stddef.h>   /* ptrdiff_t */
/* ---------------------------------------------------------------------
 The following 4 definitions are compiler-specific.
 The C standard does not guarantee that wchar_t has at least
 16 bits, so wchar_t is no less portable than unsigned short!
 All should be unsigned values to avoid sign extension during
 bit mask & shift operations.
 ------------------------------------------------------------------------ */

typedef unsigned int    UTF32;  /* at least 32 bits */
typedef unsigned short  UTF16;  /* at least 16 bits */
typedef unsigned char   UTF8;   /* typically 8 bits */
typedef unsigned char   Boolean; /* 0 or 1 */

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF

#define UNI_MAX_UTF8_BYTES_PER_CODE_POINT 4

#define UNI_UTF16_BYTE_ORDER_MARK_NATIVE  0xFEFF
#define UNI_UTF16_BYTE_ORDER_MARK_SWAPPED 0xFFFE

typedef enum {
    conversionOK,           /* conversion successful */
    sourceExhausted,        /* partial character in source, but hit end */
    targetExhausted,        /* insuff. room in target for conversion */
    sourceIllegal           /* source sequence is illegal/malformed */
} ConversionResult;

typedef enum {
    strictConversion = 0,
    lenientConversion
} ConversionFlags;

/* This is for C++ and does no harm in C */
//#ifdef __cplusplus
//extern "C" {
//#endif

ConversionResult ConvertUTF8toUTF16 (
                                     const UTF8** sourceStart, const UTF8* sourceEnd,
                                     UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF8toUTF32 (
                                     const UTF8** sourceStart, const UTF8* sourceEnd,
                                     UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF8 (
                                     const UTF16** sourceStart, const UTF16* sourceEnd,
                                     UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF8 (
                                     const UTF32** sourceStart, const UTF32* sourceEnd,
                                     UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF32 (
                                      const UTF16** sourceStart, const UTF16* sourceEnd,
                                      UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF16 (
                                      const UTF32** sourceStart, const UTF32* sourceEnd,
                                      UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd);

Boolean isLegalUTF8String(const UTF8 **source, const UTF8 *sourceEnd);

unsigned getNumBytesForUTF8(UTF8 firstByte);

int getUTF8StringLength(const UTF8* utf8, int max);
    
//#ifdef __cplusplus
//}

/*************************************************************************/
/* Below are LLVM-specific wrappers of the functions above. */

//#include "llvm/ADT/ArrayRef.h"
//#include "llvm/ADT/StringRef.h"

#include <vector>
#include <string>

typedef std::basic_string<unsigned short> CCWideString;

namespace llvm {
    
    /**
     * Convert an UTF8 StringRef to UTF8, UTF16, or UTF32 depending on
     * WideCharWidth. The converted data is written to ResultPtr, which needs to
     * point to at least WideCharWidth * (Source.Size() + 1) bytes. On success,
     * ResultPtr will point one after the end of the copied string. On failure,
     * ResultPtr will not be changed, and ErrorPtr will be set to the location of
     * the first character which could not be converted.
     * \return true on success.
     */
    bool ConvertUTF8toWide(unsigned WideCharWidth, const std::string& Source,
                           char *&ResultPtr, const UTF8 *&ErrorPtr);
    
    /**
     * Convert an Unicode code point to UTF8 sequence.
     *
     * \param Source a Unicode code point.
     * \param [in,out] ResultPtr pointer to the output buffer, needs to be at least
     * \c UNI_MAX_UTF8_BYTES_PER_CODE_POINT bytes.  On success \c ResultPtr is
     * updated one past end of the converted sequence.
     *
     * \returns true on success.
     */
    bool ConvertCodePointToUTF8(unsigned Source, char *&ResultPtr);
    
    /**
     * Convert the first UTF8 sequence in the given source buffer to a UTF32
     * code point.
     *
     * \param [in,out] source A pointer to the source buffer. If the conversion
     * succeeds, this pointer will be updated to point to the byte just past the
     * end of the converted sequence.
     * \param sourceEnd A pointer just past the end of the source buffer.
     * \param [out] target The converted code
     * \param flags Whether the conversion is strict or lenient.
     *
     * \returns conversionOK on success
     *
     * \sa ConvertUTF8toUTF32
     */
    static inline ConversionResult convertUTF8Sequence(const UTF8 **source,
                                                       const UTF8 *sourceEnd,
                                                       UTF32 *target,
                                                       ConversionFlags flags) {
        if (*source == sourceEnd)
            return sourceExhausted;
        unsigned size = getNumBytesForUTF8(**source);
        if ((ptrdiff_t)size > sourceEnd - *source)
            return sourceExhausted;
        return ConvertUTF8toUTF32(source, *source + size, &target, target + 1, flags);
    }
    
    /**
     * Returns true if a blob of text starts with a UTF-16 big or little endian byte
     * order mark.
     */
    bool hasUTF16ByteOrderMark(const char* SrcBytes, size_t len);
    
    /**
     * Converts a stream of raw bytes assumed to be UTF16 into a UTF8 std::string.
     *
     * \param [in] SrcBytes A buffer of what is assumed to be UTF-16 encoded text.
     * \param [out] Out Converted UTF-8 is stored here on success.
     * \returns true on success
     */
    bool convertUTF16ToUTF8String(const CCWideString& utf16, std::string &Out);
    
} /* end namespace llvm */

//#endif

/* --------------------------------------------------------------------- */

//#endif


static const int halfShift  = 10; /* used for shifting by 10 bits */

static const UTF32 halfBase = 0x0010000UL;
static const UTF32 halfMask = 0x3FFUL;

#define UNI_SUR_HIGH_START  (UTF32)0xD800
#define UNI_SUR_HIGH_END    (UTF32)0xDBFF
#define UNI_SUR_LOW_START   (UTF32)0xDC00
#define UNI_SUR_LOW_END     (UTF32)0xDFFF
#define false      0
#define true        1

/* --------------------------------------------------------------------- */

/*
 * Index into the table below with the first byte of a UTF-8 sequence to
 * get the number of trailing bytes that are supposed to follow it.
 * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
 * left as-is for anyone who may want to do such conversion, which was
 * allowed in earlier algorithms.
 */
static const char trailingBytesForUTF8[256] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/*
 * Magic values subtracted from a buffer value during UTF8 conversion.
 * This table contains as many values as there might be trailing bytes
 * in a UTF-8 sequence.
 */
static const UTF32 offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
    0x03C82080UL, 0xFA082080UL, 0x82082080UL };

/*
 * Once the bits are split out into bytes of UTF-8, this is a mask OR-ed
 * into the first byte, depending on how many bytes follow.  There are
 * as many entries in this table as there are UTF-8 sequence types.
 * (I.e., one byte sequence, two byte... etc.). Remember that sequencs
 * for *legal* UTF-8 will be 4 or fewer bytes total.
 */
static const UTF8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

/* --------------------------------------------------------------------- */

/* The interface converts a whole buffer to avoid function-call overhead.
 * Constants have been gathered. Loops & conditionals have been removed as
 * much as possible for efficiency, in favor of drop-through switches.
 * (See "Note A" at the bottom of the file for equivalent code.)
 * If your compiler supports it, the "isLegalUTF8" call can be turned
 * into an inline function.
 */


/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF32toUTF16 (
                                      const UTF32** sourceStart, const UTF32* sourceEnd,
                                      UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF32* source = *sourceStart;
    UTF16* target = *targetStart;
    while (source < sourceEnd) {
        UTF32 ch;
        if (target >= targetEnd) {
            result = targetExhausted; break;
        }
        ch = *source++;
        if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
            /* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
            if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
                if (flags == strictConversion) {
                    --source; /* return to the illegal value itself */
                    result = sourceIllegal;
                    break;
                } else {
                    *target++ = UNI_REPLACEMENT_CHAR;
                }
            } else {
                *target++ = (UTF16)ch; /* normal case */
            }
        } else if (ch > UNI_MAX_LEGAL_UTF32) {
            if (flags == strictConversion) {
                result = sourceIllegal;
            } else {
                *target++ = UNI_REPLACEMENT_CHAR;
            }
        } else {
            /* target is a character in range 0xFFFF - 0x10FFFF. */
            if (target + 1 >= targetEnd) {
                --source; /* Back up source pointer! */
                result = targetExhausted; break;
            }
            ch -= halfBase;
            *target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
            *target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
        }
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF16toUTF32 (
                                      const UTF16** sourceStart, const UTF16* sourceEnd,
                                      UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF16* source = *sourceStart;
    UTF32* target = *targetStart;
    UTF32 ch, ch2;
    while (source < sourceEnd) {
        const UTF16* oldSource = source; /*  In case we have to back up because of target overflow. */
        ch = *source++;
        /* If we have a surrogate pair, convert to UTF32 first. */
        if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {
            /* If the 16 bits following the high surrogate are in the source buffer... */
            if (source < sourceEnd) {
                ch2 = *source;
                /* If it's a low surrogate, convert to UTF32. */
                if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
                    ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
                    + (ch2 - UNI_SUR_LOW_START) + halfBase;
                    ++source;
                } else if (flags == strictConversion) { /* it's an unpaired high surrogate */
                    --source; /* return to the illegal value itself */
                    result = sourceIllegal;
                    break;
                }
            } else { /* We don't have the 16 bits following the high surrogate. */
                --source; /* return to the high surrogate */
                result = sourceExhausted;
                break;
            }
        } else if (flags == strictConversion) {
            /* UTF-16 surrogate values are illegal in UTF-32 */
            if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
                --source; /* return to the illegal value itself */
                result = sourceIllegal;
                break;
            }
        }
        if (target >= targetEnd) {
            source = oldSource; /* Back up source pointer! */
            result = targetExhausted; break;
        }
        *target++ = ch;
    }
    *sourceStart = source;
    *targetStart = target;
#ifdef CVTUTF_DEBUG
    if (result == sourceIllegal) {
        fprintf(stderr, "ConvertUTF16toUTF32 illegal seq 0x%04x,%04x\n", ch, ch2);
        fflush(stderr);
    }
#endif
    return result;
}
ConversionResult ConvertUTF16toUTF8 (
                                     const UTF16** sourceStart, const UTF16* sourceEnd,
                                     UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF16* source = *sourceStart;
    UTF8* target = *targetStart;
    while (source < sourceEnd) {
        UTF32 ch;
        unsigned short bytesToWrite = 0;
        const UTF32 byteMask = 0xBF;
        const UTF32 byteMark = 0x80;
        const UTF16* oldSource = source; /* In case we have to back up because of target overflow. */
        ch = *source++;
        /* If we have a surrogate pair, convert to UTF32 first. */
        if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {
            /* If the 16 bits following the high surrogate are in the source buffer... */
            if (source < sourceEnd) {
                UTF32 ch2 = *source;
                /* If it's a low surrogate, convert to UTF32. */
                if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
                    ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
                    + (ch2 - UNI_SUR_LOW_START) + halfBase;
                    ++source;
                } else if (flags == strictConversion) { /* it's an unpaired high surrogate */
                    --source; /* return to the illegal value itself */
                    result = sourceIllegal;
                    break;
                }
            } else { /* We don't have the 16 bits following the high surrogate. */
                --source; /* return to the high surrogate */
                result = sourceExhausted;
                break;
            }
        } else if (flags == strictConversion) {
            /* UTF-16 surrogate values are illegal in UTF-32 */
            if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
                --source; /* return to the illegal value itself */
                result = sourceIllegal;
                break;
            }
        }
        /* Figure out how many bytes the result will require */
        if (ch < (UTF32)0x80) {      bytesToWrite = 1;
        } else if (ch < (UTF32)0x800) {     bytesToWrite = 2;
        } else if (ch < (UTF32)0x10000) {   bytesToWrite = 3;
        } else if (ch < (UTF32)0x110000) {  bytesToWrite = 4;
        } else {                            bytesToWrite = 3;
            ch = UNI_REPLACEMENT_CHAR;
        }
        
        target += bytesToWrite;
        if (target > targetEnd) {
            source = oldSource; /* Back up source pointer! */
            target -= bytesToWrite; result = targetExhausted; break;
        }
        switch (bytesToWrite) { /* note: everything falls through. */
            case 4: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
            case 3: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
            case 2: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
            case 1: *--target =  (UTF8)(ch | firstByteMark[bytesToWrite]);
        }
        target += bytesToWrite;
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF32toUTF8 (
                                     const UTF32** sourceStart, const UTF32* sourceEnd,
                                     UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF32* source = *sourceStart;
    UTF8* target = *targetStart;
    while (source < sourceEnd) {
        UTF32 ch;
        unsigned short bytesToWrite = 0;
        const UTF32 byteMask = 0xBF;
        const UTF32 byteMark = 0x80;
        ch = *source++;
        if (flags == strictConversion ) {
            /* UTF-16 surrogate values are illegal in UTF-32 */
            if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
                --source; /* return to the illegal value itself */
                result = sourceIllegal;
                break;
            }
        }
        /*
         * Figure out how many bytes the result will require. Turn any
         * illegally large UTF32 things (> Plane 17) into replacement chars.
         */
        if (ch < (UTF32)0x80) {      bytesToWrite = 1;
        } else if (ch < (UTF32)0x800) {     bytesToWrite = 2;
        } else if (ch < (UTF32)0x10000) {   bytesToWrite = 3;
        } else if (ch <= UNI_MAX_LEGAL_UTF32) {  bytesToWrite = 4;
        } else {                            bytesToWrite = 3;
            ch = UNI_REPLACEMENT_CHAR;
            result = sourceIllegal;
        }
        
        target += bytesToWrite;
        if (target > targetEnd) {
            --source; /* Back up source pointer! */
            target -= bytesToWrite; result = targetExhausted; break;
        }
        switch (bytesToWrite) { /* note: everything falls through. */
            case 4: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
            case 3: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
            case 2: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
            case 1: *--target = (UTF8) (ch | firstByteMark[bytesToWrite]);
        }
        target += bytesToWrite;
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}

/* --------------------------------------------------------------------- */

/*
 * Utility routine to tell whether a sequence of bytes is legal UTF-8.
 * This must be called with the length pre-determined by the first byte.
 * If not calling this from ConvertUTF8to*, then the length can be set by:
 *  length = trailingBytesForUTF8[*source]+1;
 * and the sequence is illegal right away if there aren't that many bytes
 * available.
 * If presented with a length > 4, this returns false.  The Unicode
 * definition of UTF-8 goes up to 4-byte sequences.
 */

static Boolean isLegalUTF8(const UTF8 *source, int length) {
    UTF8 a;
    const UTF8 *srcptr = source+length;
    switch (length) {
        default: return false;
            /* Everything else falls through when "true"... */
        case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
        case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
        case 2: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
            
            switch (*source) {
                    /* no fall-through in this inner switch */
                case 0xE0: if (a < 0xA0) return false; break;
                case 0xED: if (a > 0x9F) return false; break;
                case 0xF0: if (a < 0x90) return false; break;
                case 0xF4: if (a > 0x8F) return false; break;
                default:   if (a < 0x80) return false;
            }
            
        case 1: if (*source >= 0x80 && *source < 0xC2) return false;
    }
    if (*source > 0xF4) return false;
    return true;
}

/* --------------------------------------------------------------------- */

/*
 * Exported function to return whether a UTF-8 sequence is legal or not.
 * This is not used here; it's just exported.
 */
Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd) {
    int length = trailingBytesForUTF8[*source]+1;
    if (length > sourceEnd - source) {
        return false;
    }
    return isLegalUTF8(source, length);
}

/* --------------------------------------------------------------------- */

/*
 * Exported function to return the total number of bytes in a codepoint
 * represented in UTF-8, given the value of the first byte.
 */
unsigned getNumBytesForUTF8(UTF8 first) {
    return trailingBytesForUTF8[first] + 1;
}

int getUTF8StringLength(const UTF8* utf8)
{
    size_t len = strlen((const char*)utf8);
    if (len == 0)
        return 0;

    const UTF8** source = &utf8;
    const UTF8* sourceEnd = utf8 + len;
    int ret = 0;
    while (*source != sourceEnd) {
        int length = trailingBytesForUTF8[**source] + 1;
        if (length > sourceEnd - *source || !isLegalUTF8(*source, length))
            return 0;
        *source += length;
        ++ret;
    }
    return ret;
}


/* --------------------------------------------------------------------- */

/*
 * Exported function to return whether a UTF-8 string is legal or not.
 * This is not used here; it's just exported.
 */
Boolean isLegalUTF8String(const UTF8 **source, const UTF8 *sourceEnd) {
    while (*source != sourceEnd) {
        int length = trailingBytesForUTF8[**source] + 1;
        if (length > sourceEnd - *source || !isLegalUTF8(*source, length))
            return false;
        *source += length;
    }
    return true;
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF8toUTF16 (
                                     const UTF8** sourceStart, const UTF8* sourceEnd,
                                     UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF8* source = *sourceStart;
    UTF16* target = *targetStart;
    while (source < sourceEnd) {
        UTF32 ch = 0;
        unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
        if (extraBytesToRead >= sourceEnd - source) {
            result = sourceExhausted; break;
        }
        /* Do this check whether lenient or strict */
        if (!isLegalUTF8(source, extraBytesToRead+1)) {
            result = sourceIllegal;
            break;
        }
        /*
         * The cases all fall through. See "Note A" below.
         */
        switch (extraBytesToRead) {
            case 5: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
            case 4: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
            case 3: ch += *source++; ch <<= 6;
            case 2: ch += *source++; ch <<= 6;
            case 1: ch += *source++; ch <<= 6;
            case 0: ch += *source++;
        }
        ch -= offsetsFromUTF8[extraBytesToRead];
        
        if (target >= targetEnd) {
            source -= (extraBytesToRead+1); /* Back up source pointer! */
            result = targetExhausted; break;
        }
        if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
            /* UTF-16 surrogate values are illegal in UTF-32 */
            if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
                if (flags == strictConversion) {
                    source -= (extraBytesToRead+1); /* return to the illegal value itself */
                    result = sourceIllegal;
                    break;
                } else {
                    *target++ = UNI_REPLACEMENT_CHAR;
                }
            } else {
                *target++ = (UTF16)ch; /* normal case */
            }
        } else if (ch > UNI_MAX_UTF16) {
            if (flags == strictConversion) {
                result = sourceIllegal;
                source -= (extraBytesToRead+1); /* return to the start */
                break; /* Bail out; shouldn't continue */
            } else {
                *target++ = UNI_REPLACEMENT_CHAR;
            }
        } else {
            /* target is a character in range 0xFFFF - 0x10FFFF. */
            if (target + 1 >= targetEnd) {
                source -= (extraBytesToRead+1); /* Back up source pointer! */
                result = targetExhausted; break;
            }
            ch -= halfBase;
            *target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
            *target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
        }
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF8toUTF32 (
                                     const UTF8** sourceStart, const UTF8* sourceEnd,
                                     UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF8* source = *sourceStart;
    UTF32* target = *targetStart;
    while (source < sourceEnd) {
        UTF32 ch = 0;
        unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
        if (extraBytesToRead >= sourceEnd - source) {
            result = sourceExhausted; break;
        }
        /* Do this check whether lenient or strict */
        if (!isLegalUTF8(source, extraBytesToRead+1)) {
            result = sourceIllegal;
            break;
        }
        /*
         * The cases all fall through. See "Note A" below.
         */
        switch (extraBytesToRead) {
            case 5: ch += *source++; ch <<= 6;
            case 4: ch += *source++; ch <<= 6;
            case 3: ch += *source++; ch <<= 6;
            case 2: ch += *source++; ch <<= 6;
            case 1: ch += *source++; ch <<= 6;
            case 0: ch += *source++;
        }
        ch -= offsetsFromUTF8[extraBytesToRead];
        
        if (target >= targetEnd) {
            source -= (extraBytesToRead+1); /* Back up the source pointer! */
            result = targetExhausted; break;
        }
        if (ch <= UNI_MAX_LEGAL_UTF32) {
            /*
             * UTF-16 surrogate values are illegal in UTF-32, and anything
             * over Plane 17 (> 0x10FFFF) is illegal.
             */
            if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
                if (flags == strictConversion) {
                    source -= (extraBytesToRead+1); /* return to the illegal value itself */
                    result = sourceIllegal;
                    break;
                } else {
                    *target++ = UNI_REPLACEMENT_CHAR;
                }
            } else {
                *target++ = ch;
            }
        } else { /* i.e., ch > UNI_MAX_LEGAL_UTF32 */
            result = sourceIllegal;
            *target++ = UNI_REPLACEMENT_CHAR;
        }
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}

/* ---------------------------------------------------------------------
 
 Note A.
 The fall-through switches in UTF-8 reading code save a
 temp variable, some decrements & conditionals.  The switches
 are equivalent to the following loop:
 {
 int tmpBytesToRead = extraBytesToRead+1;
 do {
 ch += *source++;
 --tmpBytesToRead;
 if (tmpBytesToRead) ch <<= 6;
 } while (tmpBytesToRead > 0);
 }
 In UTF-8 writing code, the switches on "bytesToWrite" are
 similarly unrolled loops.
 
 --------------------------------------------------------------------- */

/** Source codes from ConvertUTFWrapper.cpp */

//===-- ConvertUTFWrapper.cpp - Wrap ConvertUTF.h with clang data types -----===
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//#include "ConvertUTF.h"
//#include "llvm/Support/SwapByteOrder.h"
#include <string>
#include <vector>
#include <stdint.h>  // uint16_t
#include <assert.h>
#include <memory.h>

namespace llvm {
    
    bool ConvertUTF8toWide(unsigned WideCharWidth, const std::string& Source,
                           char *&ResultPtr, const UTF8 *&ErrorPtr) {
        assert(WideCharWidth == 1 || WideCharWidth == 2 || WideCharWidth == 4);
        ConversionResult result = conversionOK;
        // Copy the character span over.
        if (WideCharWidth == 1) {
            const UTF8 *Pos = reinterpret_cast<const UTF8*>(Source.data());
            if (!isLegalUTF8String(&Pos, reinterpret_cast<const UTF8*>(Source.data() + Source.length()))) {
                result = sourceIllegal;
                ErrorPtr = Pos;
            } else {
                memcpy(ResultPtr, Source.data(), Source.size());
                ResultPtr += Source.size();
            }
        } else if (WideCharWidth == 2) {
            const UTF8 *sourceStart = (const UTF8*)Source.data();
            // FIXME: Make the type of the result buffer correct instead of
            // using reinterpret_cast.
            UTF16 *targetStart = reinterpret_cast<UTF16*>(ResultPtr);
            ConversionFlags flags = strictConversion;
            result = ConvertUTF8toUTF16(
                                        &sourceStart, sourceStart + Source.size(),
                                        &targetStart, targetStart + 2*Source.size(), flags);
            if (result == conversionOK)
                ResultPtr = reinterpret_cast<char*>(targetStart);
            else
                ErrorPtr = sourceStart;
        } else if (WideCharWidth == 4) {
            const UTF8 *sourceStart = (const UTF8*)Source.data();
            // FIXME: Make the type of the result buffer correct instead of
            // using reinterpret_cast.
            UTF32 *targetStart = reinterpret_cast<UTF32*>(ResultPtr);
            ConversionFlags flags = strictConversion;
            result = ConvertUTF8toUTF32(
                                        &sourceStart, sourceStart + Source.size(),
                                        &targetStart, targetStart + 4*Source.size(), flags);
            if (result == conversionOK)
                ResultPtr = reinterpret_cast<char*>(targetStart);
            else
                ErrorPtr = sourceStart;
        }
        assert((result != targetExhausted)
               && "ConvertUTF8toUTFXX exhausted target buffer");
        return result == conversionOK;
    }
    
    bool ConvertCodePointToUTF8(unsigned Source, char *&ResultPtr) {
        const UTF32 *SourceStart = &Source;
        const UTF32 *SourceEnd = SourceStart + 1;
        UTF8 *TargetStart = reinterpret_cast<UTF8 *>(ResultPtr);
        UTF8 *TargetEnd = TargetStart + 4;
        ConversionResult CR = ConvertUTF32toUTF8(&SourceStart, SourceEnd,
                                                 &TargetStart, TargetEnd,
                                                 strictConversion);
        if (CR != conversionOK)
            return false;
        
        ResultPtr = reinterpret_cast<char*>(TargetStart);
        return true;
    }
    
    bool hasUTF16ByteOrderMark(const char* S, size_t len) {
        return (len >= 2 &&
                ((S[0] == '\xff' && S[1] == '\xfe') ||
                 (S[0] == '\xfe' && S[1] == '\xff')));
    }
    
    /// SwapByteOrder_16 - This function returns a byte-swapped representation of
    /// the 16-bit argument.
    inline uint16_t SwapByteOrder_16(uint16_t value) {
#if defined(_MSC_VER) && !defined(_DEBUG)
        // The DLL version of the runtime lacks these functions (bug!?), but in a
        // release build they're replaced with BSWAP instructions anyway.
        return _byteswap_ushort(value);
#else
        uint16_t Hi = value << 8;
        uint16_t Lo = value >> 8;
        return Hi | Lo;
#endif
    }
    
    bool convertUTF16ToUTF8String(const CCWideString& utf16, std::string &Out) {
        assert(Out.empty());
        
        // Avoid OOB by returning early on empty input.
        if (utf16.empty())
            return true;
        
        const UTF16 *Src = reinterpret_cast<const UTF16 *>(utf16.data());
        const UTF16 *SrcEnd = reinterpret_cast<const UTF16 *>(utf16.data() + utf16.length());
        
        // Byteswap if necessary.
        std::vector<UTF16> ByteSwapped;
        if (Src[0] == UNI_UTF16_BYTE_ORDER_MARK_SWAPPED) {
            ByteSwapped.insert(ByteSwapped.end(), Src, SrcEnd);
            for (size_t I = 0, E = ByteSwapped.size(); I != E; ++I)
                ByteSwapped[I] = SwapByteOrder_16(ByteSwapped[I]);
            Src = &ByteSwapped[0];
            SrcEnd = &ByteSwapped[ByteSwapped.size() - 1] + 1;
        }
        
        // Skip the BOM for conversion.
        if (Src[0] == UNI_UTF16_BYTE_ORDER_MARK_NATIVE)
            Src++;
        
        // Just allocate enough space up front.  We'll shrink it later.
        Out.resize(utf16.length() * UNI_MAX_UTF8_BYTES_PER_CODE_POINT + 1);
        UTF8 *Dst = reinterpret_cast<UTF8 *>(&Out[0]);
        UTF8 *DstEnd = Dst + Out.size();
        
        ConversionResult CR =
        ConvertUTF16toUTF8(&Src, SrcEnd, &Dst, DstEnd, strictConversion);
        assert(CR != targetExhausted);
        
        if (CR != conversionOK) {
            Out.clear();
            return false;
        }
        
        Out.resize(reinterpret_cast<char *>(Dst) - &Out[0]);
        return true;
    }
    
} // end namespace llvm


NS_CC_BEGIN

/*
 * @str:    the string to search through.
 * @c:        the character to not look for.
 *
 * Return value: the index of the last character that is not c.
 * */
unsigned int cc_utf8_find_last_not_char(const std::vector<unsigned short>& str, unsigned short c)
{
    int len = static_cast<int>(str.size());
    
    int i = len - 1;
    for (; i >= 0; --i)
        if (str[i] != c) return i;
    
    return i;
}

/*
 * @str:    the string to trim
 * @index:    the index to start trimming from.
 *
 * Trims str st str=[0, index) after the operation.
 *
 * Return value: the trimmed string.
 * */
static void cc_utf8_trim_from(std::vector<unsigned short>* str, int index)
{
    int size = static_cast<int>(str->size());
    if (index >= size || index < 0)
        return;

    str->erase(str->begin() + index, str->begin() + size);
}

/*
 * @ch is the unicode character whitespace?
 *
 * Reference: http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 *
 * Return value: weather the character is a whitespace character.
 * */
bool isspace_unicode(unsigned short ch)
{
    return  (ch >= 0x0009 && ch <= 0x000D) || ch == 0x0020 || ch == 0x0085 || ch == 0x00A0 || ch == 0x1680
    || (ch >= 0x2000 && ch <= 0x200A) || ch == 0x2028 || ch == 0x2029 || ch == 0x202F
    ||  ch == 0x205F || ch == 0x3000;
}

bool iscjk_unicode(unsigned short ch)
{
    return (ch >= 0x4E00 && ch <= 0x9FBF)   // CJK Unified Ideographs
        || (ch >= 0x2E80 && ch <= 0x2FDF)   // CJK Radicals Supplement & Kangxi Radicals
        || (ch >= 0x2FF0 && ch <= 0x30FF)   // Ideographic Description Characters, CJK Symbols and Punctuation & Japanese
        || (ch >= 0x3100 && ch <= 0x31BF)   // Korean
        || (ch >= 0xAC00 && ch <= 0xD7AF)   // Hangul Syllables
        || (ch >= 0xF900 && ch <= 0xFAFF)   // CJK Compatibility Ideographs
        || (ch >= 0xFE30 && ch <= 0xFE4F)   // CJK Compatibility Forms
        || (ch >= 0x31C0 && ch <= 0x4DFF);  // Other exiensions
}

void cc_utf8_trim_ws(std::vector<unsigned short>* str)
{
    int len = str->size();
    
    if ( len <= 0 )
        return;
    
    int last_index = len - 1;
    
    // Only start trimming if the last character is whitespace..
    if (isspace_unicode((*str)[last_index]))
    {
        for (int i = last_index - 1; i >= 0; --i)
        {
            if (isspace_unicode((*str)[i]))
                last_index = i;
            else
                break;
        }
        
        cc_utf8_trim_from(str, last_index);
    }
}

long getCharacterCountInUTF8String(const std::string& utf8)
{
    return getUTF8StringLength((const UTF8*)utf8.c_str());
}

int cc_wcslen(const unsigned short* str)
{
    int i=0;
    while(*str++) i++;
    return i;
}

long cc_utf8_strlen (const char * p)
{
    if (p == NULL)
        return 0;
    return getCharacterCountInUTF8String(p);
}

std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str)
{
    int len = cc_wcslen(str);
    std::vector<unsigned short> str_new;
    
    for (int i = 0; i < len; ++i)
    {
        str_new.push_back(str[i]);
    }
    return str_new;
}

unsigned short* cc_utf8_to_utf16(const char* utf8, int* outUTF16CharacterCount /*= NULL*/)
{
    if (utf8 == NULL)
        return NULL;
    
    unsigned short* ret = NULL;
    
    std::string utf8Str = utf8;
    
    const size_t utf16Size = utf8Str.length()+1;
    unsigned short* utf16 = new unsigned short[utf16Size];
    memset(utf16, 0, utf16Size * sizeof(unsigned short));
    
    char* utf16ptr = reinterpret_cast<char*>(utf16);
    const UTF8* error = NULL;
    
    if (utf8Str.empty() || llvm::ConvertUTF8toWide(2, utf8Str, utf16ptr, error))
    {
        ret = utf16;
        if (outUTF16CharacterCount)
        {
            *outUTF16CharacterCount = cc_wcslen(ret);
        }
    }
    else
    {
        delete [] utf16;
    }
    
    return ret;
}

char * cc_utf16_to_utf8(const unsigned short* utf16, int* outUTF8CharacterCount /*= NULL*/)
{
    if (utf16 == NULL)
        return NULL;
    
    CCWideString utf16Str;
    int utf16Len = cc_wcslen(utf16);
    
    for (int i = 0; i < utf16Len; ++i)
    {
        utf16Str.push_back(utf16[i]);
    }
    
    char* ret = NULL;
    std::string outUtf8;
    
    if (utf16Len == 0 || llvm::convertUTF16ToUTF8String(utf16Str, outUtf8))
    {

        ret = new char[outUtf8.length() + 1];
        ret[outUtf8.length()] = '\0';
        if (utf16Len > 0)
        {
            memcpy(ret, outUtf8.data(), outUtf8.length());
        }
        
        if (outUTF8CharacterCount)
        {
            *outUTF8CharacterCount = outUtf8.length();
        }
    }
    
    return ret;
}


NS_CC_END
