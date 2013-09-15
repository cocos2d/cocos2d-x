/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Provides a common interface to the ASan (AddressSanitizer) and Valgrind 
 * functions used to mark memory in certain ways. In detail, the following
 * three macros are provided:
 *
 *   MOZ_MAKE_MEM_NOACCESS  - Mark memory as unsafe to access (e.g. freed)
 *   MOZ_MAKE_MEM_UNDEFINED - Mark memory as accessible, with content undefined
 *   MOZ_MAKE_MEM_DEFINED - Mark memory as accessible, with content defined
 *
 * With Valgrind in use, these directly map to the three respective Valgrind
 * macros. With ASan in use, the NOACCESS macro maps to poisoning the memory,
 * while the UNDEFINED/DEFINED macros unpoison memory.
 *
 * With no memory checker available, all macros expand to the empty statement.
 */

#ifndef mozilla_MemoryChecking_h_
#define mozilla_MemoryChecking_h_

#if defined(MOZ_VALGRIND)
#include "valgrind/memcheck.h"
#endif

#if defined(MOZ_ASAN) || defined(MOZ_VALGRIND)
#define MOZ_HAVE_MEM_CHECKS 1
#endif

#if defined(MOZ_ASAN)
#include <stddef.h>

extern "C" {
  /* These definitions are usually provided through the 
   * sanitizer/asan_interface.h header installed by ASan.
   */
  void __asan_poison_memory_region(void const volatile *addr, size_t size)
    __attribute__((visibility("default")));
  void __asan_unpoison_memory_region(void const volatile *addr, size_t size)
    __attribute__((visibility("default")));

#define MOZ_MAKE_MEM_NOACCESS(addr, size) \
  __asan_poison_memory_region((addr), (size))

#define MOZ_MAKE_MEM_UNDEFINED(addr, size) \
  __asan_unpoison_memory_region((addr), (size))

#define MOZ_MAKE_MEM_DEFINED(addr, size) \
  __asan_unpoison_memory_region((addr), (size))
}
#elif defined(MOZ_VALGRIND)
#define MOZ_MAKE_MEM_NOACCESS(addr, size) \
  VALGRIND_MAKE_MEM_NOACCESS((addr), (size))

#define MOZ_MAKE_MEM_UNDEFINED(addr, size) \
  VALGRIND_MAKE_MEM_UNDEFINED((addr), (size))

#define MOZ_MAKE_MEM_DEFINED(addr, size) \
  VALGRIND_MAKE_MEM_DEFINED((addr), (size))
#else

#define MOZ_MAKE_MEM_NOACCESS(addr, size) do {} while(0)
#define MOZ_MAKE_MEM_UNDEFINED(addr, size) do {} while(0)
#define MOZ_MAKE_MEM_DEFINED(addr, size) do {} while(0)

#endif

#endif  /* mozilla_MemoryChecking_h_ */
