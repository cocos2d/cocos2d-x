//===-- ConvertUTFWrapper.cpp - Wrap ConvertUTF.h with clang data types -----===
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ConvertUTF.h"
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

bool convertUTF16ToUTF8String(const std::u16string& utf16, std::string &Out) {
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

