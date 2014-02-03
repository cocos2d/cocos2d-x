/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Functions for reading and writing integers in various endiannesses. */

/*
 * The classes LittleEndian and BigEndian expose static methods for
 * reading and writing 16-, 32-, and 64-bit signed and unsigned integers
 * in their respective endianness.  The naming scheme is:
 *
 * {Little,Big}Endian::{read,write}{Uint,Int}<bitsize>
 *
 * For instance, LittleEndian::readInt32 will read a 32-bit signed
 * integer from memory in little endian format.  Similarly,
 * BigEndian::writeUint16 will write a 16-bit unsigned integer to memory
 * in big-endian format.
 *
 * The class NativeEndian exposes methods for conversion of existing
 * data to and from the native endianness.  These methods are intended
 * for cases where data needs to be transferred, serialized, etc.
 * swap{To,From}{Little,Big}Endian byteswap a single value if necessary.
 * Bulk conversion functions are also provided which optimize the
 * no-conversion-needed case:
 *
 * - copyAndSwap{To,From}{Little,Big}Endian;
 * - swap{To,From}{Little,Big}EndianInPlace.
 *
 * The *From* variants are intended to be used for reading data and the
 * *To* variants for writing data.
 *
 * Methods on NativeEndian work with integer data of any type.
 * Floating-point data is not supported.
 *
 * For clarity in networking code, "Network" may be used as a synonym
 * for "Big" in any of the above methods or class names.
 *
 * As an example, reading a file format header whose fields are stored
 * in big-endian format might look like:
 *
 * class ExampleHeader
 * {
 *   private:
 *     uint32_t magic;
 *     uint32_t length;
 *     uint32_t totalRecords;
 *     uint64_t checksum;
 *
 *   public:
 *     ExampleHeader(const void* data) {
 *       const uint8_t* ptr = static_cast<const uint8_t*>(data);
 *       magic = BigEndian::readUint32(ptr); ptr += sizeof(uint32_t);
 *       length = BigEndian::readUint32(ptr); ptr += sizeof(uint32_t);
 *       totalRecords = BigEndian::readUint32(ptr); ptr += sizeof(uint32_t);
 *       checksum = BigEndian::readUint64(ptr);
 *     }
 *     ...
 * };
 */

#ifndef mozilla_Endian_h
#define mozilla_Endian_h

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/Compiler.h"
#include "mozilla/DebugOnly.h"
#include "mozilla/TypeTraits.h"

#include <stdint.h>
#include <string.h>

#if defined(_MSC_VER) && _MSC_VER >= 1300
#  include <stdlib.h>
#  pragma intrinsic(_byteswap_ushort)
#  pragma intrinsic(_byteswap_ulong)
#  pragma intrinsic(_byteswap_uint64)
#endif

#if defined(_WIN64)
#  if defined(_M_X64) || defined(_M_AMD64) || defined(_AMD64_)
#    define MOZ_LITTLE_ENDIAN 1
#  else
#    error "CPU type is unknown"
#  endif
#elif defined(_WIN32)
#  if defined(_M_IX86)
#    define MOZ_LITTLE_ENDIAN 1
#  else
#    error "CPU type is unknown"
#  endif
#elif defined(__APPLE__)
#  if __LITTLE_ENDIAN__
#    define MOZ_LITTLE_ENDIAN 1
#  elif __BIG_ENDIAN__
#    define MOZ_BIG_ENDIAN 1
#  endif
#elif defined(__GNUC__) && \
      defined(__BYTE_ORDER__) && \
      defined(__ORDER_LITTLE_ENDIAN__) && \
      defined(__ORDER_BIG_ENDIAN__)
   /*
    * Some versions of GCC provide architecture-independent macros for
    * this.  Yes, there are more than two values for __BYTE_ORDER__.
    */
#  if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define MOZ_LITTLE_ENDIAN 1
#  elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define MOZ_BIG_ENDIAN 1
#  else
#    error "Can't handle mixed-endian architectures"
#  endif
/*
 * We can't include useful headers like <endian.h> or <sys/isa_defs.h>
 * here because they're not present on all platforms.  Instead we have
 * this big conditional that ideally will catch all the interesting
 * cases.
 */
#elif defined(__sparc) || defined(__sparc__) || \
      defined(_POWER) || defined(__powerpc__) || \
      defined(__ppc__) || defined(__hppa) || \
      defined(_MIPSEB) || defined(__ARMEB__) || \
      defined(__s390__) || \
      (defined(__sh__) && defined(__LITTLE_ENDIAN__)) || \
      (defined(__ia64) && defined(__BIG_ENDIAN__))
#  define MOZ_BIG_ENDIAN 1
#elif defined(__i386) || defined(__i386__) || \
      defined(__x86_64) || defined(__x86_64__) || \
      defined(_MIPSEL) || defined(__ARMEL__) || \
      defined(__alpha__) || \
      (defined(__sh__) && defined(__BIG_ENDIAN__)) || \
      (defined(__ia64) && !defined(__BIG_ENDIAN__))
#  define MOZ_LITTLE_ENDIAN 1
#endif

#if MOZ_BIG_ENDIAN
#  define MOZ_LITTLE_ENDIAN 0
#elif MOZ_LITTLE_ENDIAN
#  define MOZ_BIG_ENDIAN 0
#else
#  error "Cannot determine endianness"
#endif

#if defined(__clang__)
#  if __has_builtin(__builtin_bswap16)
#    define MOZ_HAVE_BUILTIN_BYTESWAP16 __builtin_bswap16
#  endif
#elif defined(__GNUC__)
#  if MOZ_GCC_VERSION_AT_LEAST(4, 8, 0)
#    define MOZ_HAVE_BUILTIN_BYTESWAP16 __builtin_bswap16
#  endif
#elif defined(_MSC_VER)
#    define MOZ_HAVE_BUILTIN_BYTESWAP16 _byteswap_ushort
#endif

namespace mozilla {

namespace detail {

/*
 * We need wrappers here because free functions with default template
 * arguments and/or partial specialization of function templates are not
 * supported by all the compilers we use.
 */
template<typename T, size_t Size = sizeof(T)>
struct Swapper;

template<typename T>
struct Swapper<T, 2>
{
  static T swap(T value)
  {
#if defined(MOZ_HAVE_BUILTIN_BYTESWAP16)
    return MOZ_HAVE_BUILTIN_BYTESWAP16(value);
#else
    return T(((value & 0x00ff) << 8) | ((value & 0xff00) >> 8));
#endif
  }
};

template<typename T>
struct Swapper<T, 4>
{
  static T swap(T value)
  {
#if defined(__clang__) || defined(__GNUC__)
    return T(__builtin_bswap32(value));
#elif defined(_MSC_VER)
    return T(_byteswap_ulong(value));
#else
    return T(((value & 0x000000ffU) << 24) |
             ((value & 0x0000ff00U) << 8) |
             ((value & 0x00ff0000U) >> 8) |
             ((value & 0xff000000U) >> 24));
#endif
  }
};

template<typename T>
struct Swapper<T, 8>
{
  static inline T swap(T value)
  {
#if defined(__clang__) || defined(__GNUC__)
    return T(__builtin_bswap64(value));
#elif defined(_MSC_VER)
    return T(_byteswap_uint64(value));
#else
    return T(((value & 0x00000000000000ffULL) << 56) |
             ((value & 0x000000000000ff00ULL) << 40) |
             ((value & 0x0000000000ff0000ULL) << 24) |
             ((value & 0x00000000ff000000ULL) << 8) |
             ((value & 0x000000ff00000000ULL) >> 8) |
             ((value & 0x0000ff0000000000ULL) >> 24) |
             ((value & 0x00ff000000000000ULL) >> 40) |
             ((value & 0xff00000000000000ULL) >> 56));
#endif
  }
};

enum Endianness { Little, Big };

#if MOZ_BIG_ENDIAN
#  define MOZ_NATIVE_ENDIANNESS detail::Big
#else
#  define MOZ_NATIVE_ENDIANNESS detail::Little
#endif

class EndianUtils
{
    /**
     * Assert that the memory regions [dest, dest+count) and [src, src+count]
     * do not overlap.  count is given in bytes.
     */
    static void assertNoOverlap(const void* dest, const void* src, size_t count)
    {
      DebugOnly<const uint8_t*> byteDestPtr = static_cast<const uint8_t*>(dest);
      DebugOnly<const uint8_t*> byteSrcPtr = static_cast<const uint8_t*>(src);
      MOZ_ASSERT((byteDestPtr < byteSrcPtr &&
                  byteDestPtr + count <= byteSrcPtr) ||
                 (byteSrcPtr < byteDestPtr &&
                  byteSrcPtr + count <= byteDestPtr));
    }

    template<typename T>
    static void assertAligned(T* ptr)
    {
      MOZ_ASSERT((uintptr_t(ptr) % sizeof(T)) == 0, "Unaligned pointer!");
    }

  protected:
    /**
     * Return |value| converted from SourceEndian encoding to DestEndian
     * encoding.
     */
    template<Endianness SourceEndian, Endianness DestEndian, typename T>
    static inline T maybeSwap(T value)
    {
      if (SourceEndian == DestEndian)
        return value;

      return Swapper<T>::swap(value);
    }

    /**
     * Convert |count| elements at |ptr| from SourceEndian encoding to
     * DestEndian encoding.
     */
    template<Endianness SourceEndian, Endianness DestEndian, typename T>
    static inline void maybeSwapInPlace(T* ptr, size_t count)
    {
      assertAligned(ptr);

      if (SourceEndian == DestEndian)
        return;

      for (size_t i = 0; i < count; i++)
        ptr[i] = Swapper<T>::swap(ptr[i]);
    }

    /**
     * Write |count| elements to the unaligned address |dest| in DestEndian
     * format, using elements found at |src| in SourceEndian format.
     */
    template<Endianness SourceEndian, Endianness DestEndian, typename T>
    static void copyAndSwapTo(void* dest, const T* src, size_t count)
    {
      assertNoOverlap(dest, src, count * sizeof(T));
      assertAligned(src);

      if (SourceEndian == DestEndian) {
        memcpy(dest, src, count * sizeof(T));
        return;
      }

      uint8_t* byteDestPtr = static_cast<uint8_t*>(dest);
      for (size_t i = 0; i < count; ++i) {
        union {
          T val;
          uint8_t buffer[sizeof(T)];
        } u;
        u.val = maybeSwap<SourceEndian, DestEndian>(src[i]);
        memcpy(byteDestPtr, u.buffer, sizeof(T));
        byteDestPtr += sizeof(T);
      }
    }

    /**
     * Write |count| elements to |dest| in DestEndian format, using elements
     * found at the unaligned address |src| in SourceEndian format.
     */
    template<Endianness SourceEndian, Endianness DestEndian, typename T>
    static void copyAndSwapFrom(T* dest, const void* src, size_t count)
    {
      assertNoOverlap(dest, src, count * sizeof(T));
      assertAligned(dest);

      if (SourceEndian == DestEndian) {
        memcpy(dest, src, count * sizeof(T));
        return;
      }

      const uint8_t* byteSrcPtr = static_cast<const uint8_t*>(src);
      for (size_t i = 0; i < count; ++i) {
        union {
          T val;
          uint8_t buffer[sizeof(T)];
        } u;
        memcpy(u.buffer, byteSrcPtr, sizeof(T));
        dest[i] = maybeSwap<SourceEndian, DestEndian>(u.val);
        byteSrcPtr += sizeof(T);
      }
    }
};

template<Endianness ThisEndian>
class Endian : private EndianUtils
{
  protected:
    /** Read a uint16_t in ThisEndian endianness from |p| and return it. */
    static MOZ_WARN_UNUSED_RESULT uint16_t readUint16(const void* p) {
      return read<uint16_t>(p);
    }

    /** Read a uint32_t in ThisEndian endianness from |p| and return it. */
    static MOZ_WARN_UNUSED_RESULT uint32_t readUint32(const void* p) {
      return read<uint32_t>(p);
    }

    /** Read a uint64_t in ThisEndian endianness from |p| and return it. */
    static MOZ_WARN_UNUSED_RESULT uint64_t readUint64(const void* p) {
      return read<uint64_t>(p);
    }

    /** Read an int16_t in ThisEndian endianness from |p| and return it. */
    static MOZ_WARN_UNUSED_RESULT int16_t readInt16(const void* p) {
      return read<int16_t>(p);
    }

    /** Read an int32_t in ThisEndian endianness from |p| and return it. */
    static MOZ_WARN_UNUSED_RESULT int32_t readInt32(const void* p) {
      return read<uint32_t>(p);
    }

    /** Read an int64_t in ThisEndian endianness from |p| and return it. */
    static MOZ_WARN_UNUSED_RESULT int64_t readInt64(const void* p) {
      return read<int64_t>(p);
    }

    /** Write |val| to |p| using ThisEndian endianness. */
    static void writeUint16(void* p, uint16_t val) {
      write(p, val);
    }
    /** Write |val| to |p| using ThisEndian endianness. */
    static void writeUint32(void* p, uint32_t val) {
      write(p, val);
    }
    /** Write |val| to |p| using ThisEndian endianness. */
    static void writeUint64(void* p, uint64_t val) {
      write(p, val);
    }

    /** Write |val| to |p| using ThisEndian endianness. */
    static void writeInt16(void* p, int16_t val) {
      write(p, val);
    }
    /** Write |val| to |p| using ThisEndian endianness. */
    static void writeInt32(void* p, int32_t val) {
      write(p, val);
    }
    /** Write |val| to |p| using ThisEndian endianness. */
    static void writeInt64(void* p, int64_t val) {
      write(p, val);
    }

    /*
     * Converts a value of type T to little-endian format.
     *
     * This function is intended for cases where you have data in your
     * native-endian format and you need it to appear in little-endian
     * format for transmission.
     */
    template<typename T>
    MOZ_WARN_UNUSED_RESULT static T swapToLittleEndian(T value) {
      return maybeSwap<ThisEndian, Little>(value);
    }
    /*
     * Copies count values of type T starting at src to dest, converting
     * them to little-endian format if ThisEndian is Big.
     * As with memcpy, dest and src must not overlap.
     */
    template<typename T>
    static void copyAndSwapToLittleEndian(void* dest, const T* src,
                                          size_t count) {
      copyAndSwapTo<ThisEndian, Little>(dest, src, count);
    }
    /*
     * Likewise, but converts values in place.
     */
    template<typename T>
    static void swapToLittleEndianInPlace(T* p, size_t count) {
      maybeSwapInPlace<ThisEndian, Little>(p, count);
    }

    /*
     * Converts a value of type T to big-endian format.
     */
    template<typename T>
    MOZ_WARN_UNUSED_RESULT static T swapToBigEndian(T value) {
      return maybeSwap<ThisEndian, Big>(value);
    }
    /*
     * Copies count values of type T starting at src to dest, converting
     * them to big-endian format if ThisEndian is Little.
     * As with memcpy, dest and src must not overlap.
     */
    template<typename T>
    static void copyAndSwapToBigEndian(void* dest, const T* src, size_t count) {
      copyAndSwapTo<ThisEndian, Big>(dest, src, count);
    }
    /*
     * Likewise, but converts values in place.
     */
    template<typename T>
    static void swapToBigEndianInPlace(T* p, size_t count) {
      maybeSwapInPlace<ThisEndian, Big>(p, count);
    }

    /*
     * Synonyms for the big-endian functions, for better readability
     * in network code.
     */
    template<typename T>
    MOZ_WARN_UNUSED_RESULT static T swapToNetworkOrder(T value) {
      return swapToBigEndian(value);
    }
    template<typename T>
    static void
    copyAndSwapToNetworkOrder(void* dest, const T* src, size_t count) {
      copyAndSwapToBigEndian(dest, src, count);
    }
    template<typename T>
    static void
    swapToNetworkOrderInPlace(T* p, size_t count) {
      swapToBigEndianInPlace(p, count);
    }

    /*
     * Converts a value of type T from little-endian format.
     */
    template<typename T>
    MOZ_WARN_UNUSED_RESULT static T swapFromLittleEndian(T value) {
      return maybeSwap<Little, ThisEndian>(value);
    }
    /*
     * Copies count values of type T starting at src to dest, converting
     * them to little-endian format if ThisEndian is Big.
     * As with memcpy, dest and src must not overlap.
     */
    template<typename T>
    static void copyAndSwapFromLittleEndian(T* dest, const void* src,
                                            size_t count) {
      copyAndSwapFrom<Little, ThisEndian>(dest, src, count);
    }
    /*
     * Likewise, but converts values in place.
     */
    template<typename T>
    static void swapFromLittleEndianInPlace(T* p, size_t count) {
      maybeSwapInPlace<Little, ThisEndian>(p, count);
    }

    /*
     * Converts a value of type T from big-endian format.
     */
    template<typename T>
    MOZ_WARN_UNUSED_RESULT static T swapFromBigEndian(T value) {
      return maybeSwap<Big, ThisEndian>(value);
    }
    /*
     * Copies count values of type T starting at src to dest, converting
     * them to big-endian format if ThisEndian is Little.
     * As with memcpy, dest and src must not overlap.
     */
    template<typename T>
    static void copyAndSwapFromBigEndian(T* dest, const void* src,
                                         size_t count) {
      copyAndSwapFrom<Big, ThisEndian>(dest, src, count);
    }
    /*
     * Likewise, but converts values in place.
     */
    template<typename T>
    static void swapFromBigEndianInPlace(T* p, size_t count) {
      maybeSwapInPlace<Big, ThisEndian>(p, count);
    }

    /*
     * Synonyms for the big-endian functions, for better readability
     * in network code.
     */
    template<typename T>
    MOZ_WARN_UNUSED_RESULT static T swapFromNetworkOrder(T value) {
      return swapFromBigEndian(value);
    }
    template<typename T>
    static void copyAndSwapFromNetworkOrder(T* dest, const void* src,
                                            size_t count) {
      copyAndSwapFromBigEndian(dest, src, count);
    }
    template<typename T>
    static void swapFromNetworkOrderInPlace(T* p, size_t count) {
      swapFromBigEndianInPlace(p, count);
    }

  private:
    /**
     * Read a value of type T, encoded in endianness ThisEndian from |p|.
     * Return that value encoded in native endianness.
     */
    template<typename T>
    static T read(const void* p) {
      union {
        T val;
        uint8_t buffer[sizeof(T)];
      } u;
      memcpy(u.buffer, p, sizeof(T));
      return maybeSwap<ThisEndian, MOZ_NATIVE_ENDIANNESS>(u.val);
    }

    /**
     * Write a value of type T, in native endianness, to |p|, in ThisEndian
     * endianness.
     */
    template<typename T>
    static void write(void* p, T value) {
      T tmp = maybeSwap<MOZ_NATIVE_ENDIANNESS, ThisEndian>(value);
      memcpy(p, &tmp, sizeof(T));
    }

    Endian() MOZ_DELETE;
    Endian(const Endian& other) MOZ_DELETE;
    void operator=(const Endian& other) MOZ_DELETE;
};

template<Endianness ThisEndian>
class EndianReadWrite : public Endian<ThisEndian>
{
  private:
    typedef Endian<ThisEndian> super;

  public:
    using super::readUint16;
    using super::readUint32;
    using super::readUint64;
    using super::readInt16;
    using super::readInt32;
    using super::readInt64;
    using super::writeUint16;
    using super::writeUint32;
    using super::writeUint64;
    using super::writeInt16;
    using super::writeInt32;
    using super::writeInt64;
};

} /* namespace detail */

class LittleEndian MOZ_FINAL : public detail::EndianReadWrite<detail::Little>
{};

class BigEndian MOZ_FINAL : public detail::EndianReadWrite<detail::Big>
{};

typedef BigEndian NetworkEndian;

class NativeEndian MOZ_FINAL : public detail::Endian<MOZ_NATIVE_ENDIANNESS>
{
  private:
    typedef detail::Endian<MOZ_NATIVE_ENDIANNESS> super;

  public:
    /*
     * These functions are intended for cases where you have data in your
     * native-endian format and you need the data to appear in the appropriate
     * endianness for transmission, serialization, etc.
     */
    using super::swapToLittleEndian;
    using super::copyAndSwapToLittleEndian;
    using super::swapToLittleEndianInPlace;
    using super::swapToBigEndian;
    using super::copyAndSwapToBigEndian;
    using super::swapToBigEndianInPlace;
    using super::swapToNetworkOrder;
    using super::copyAndSwapToNetworkOrder;
    using super::swapToNetworkOrderInPlace;

    /*
     * These functions are intended for cases where you have data in the
     * given endianness (e.g. reading from disk or a file-format) and you
     * need the data to appear in native-endian format for processing.
     */
    using super::swapFromLittleEndian;
    using super::copyAndSwapFromLittleEndian;
    using super::swapFromLittleEndianInPlace;
    using super::swapFromBigEndian;
    using super::copyAndSwapFromBigEndian;
    using super::swapFromBigEndianInPlace;
    using super::swapFromNetworkOrder;
    using super::copyAndSwapFromNetworkOrder;
    using super::swapFromNetworkOrderInPlace;
};

#undef MOZ_NATIVE_ENDIANNESS

} /* namespace mozilla */

#endif /* mozilla_Endian_h */
