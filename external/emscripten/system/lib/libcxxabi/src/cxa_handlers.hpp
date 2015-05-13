//===------------------------- cxa_handlers.cpp ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//
// This file implements the functionality associated with the terminate_handler,
//   unexpected_handler, and new_handler.
//===----------------------------------------------------------------------===//

#ifndef _CXA_HANDLERS_H
#define _CXA_HANDLERS_H

#include <exception>

namespace std
{

__attribute__((visibility("hidden"), noreturn))
void
__unexpected(unexpected_handler func);

__attribute__((visibility("hidden"), noreturn))
void
__terminate(terminate_handler func) _NOEXCEPT;

}  // std

extern "C"
{

extern void (*__cxa_terminate_handler)();
extern void (*__cxa_unexpected_handler)();
extern void (*__cxa_new_handler)();

/*

    At some point in the future these three symbols will become
    C++11 atomic variables:

    extern std::atomic<std::terminate_handler>  __cxa_terminate_handler;
    extern std::atomic<std::unexpected_handler> __cxa_unexpected_handler;
    extern std::atomic<std::new_handler>        __cxa_new_handler;

    This change will not impact their ABI.  But it will allow for a
    portable performance optimization.

*/

} // extern "C"

#endif  // _CXA_HANDLERS_H
