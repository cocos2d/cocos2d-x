//===------------------------- cxa_exception.cpp --------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//  
//  This file implements the "Exception Handling APIs"
//  http://www.codesourcery.com/public/cxx-abi/abi-eh.html
//  
//===----------------------------------------------------------------------===//

#include "cxxabi.h"

#include <exception>        // for std::terminate
#include <cstdlib>          // for malloc, free
#include <string>           // for memset
#include <pthread.h>

#include "cxa_exception.hpp"
#include "cxa_handlers.hpp"

// +---------------------------+-----------------------------+---------------+
// | __cxa_exception           | _Unwind_Exception CLNGC++\0 | thrown object |
// +---------------------------+-----------------------------+---------------+
//                                                           ^
//                                                           |
//   +-------------------------------------------------------+
//   |
// +---------------------------+-----------------------------+
// | __cxa_dependent_exception | _Unwind_Exception CLNGC++\1 |
// +---------------------------+-----------------------------+

namespace __cxxabiv1 {

#pragma GCC visibility push(default)

//  Utility routines
static
inline
__cxa_exception*
cxa_exception_from_thrown_object(void* thrown_object)
{
    return static_cast<__cxa_exception*>(thrown_object) - 1;
}

// Note:  This is never called when exception_header is masquerading as a
//        __cxa_dependent_exception.
static
inline
void*
thrown_object_from_cxa_exception(__cxa_exception* exception_header)
{
    return static_cast<void*>(exception_header + 1);
}

//  Get the exception object from the unwind pointer.
//  Relies on the structure layout, where the unwind pointer is right in
//  front of the user's exception object
static
inline
__cxa_exception*
cxa_exception_from_exception_unwind_exception(_Unwind_Exception* unwind_exception)
{
    return cxa_exception_from_thrown_object(unwind_exception + 1 );
}

static
inline
size_t
cxa_exception_size_from_exception_thrown_size(size_t size)
{
    return size + sizeof (__cxa_exception);
}

static void setExceptionClass(_Unwind_Exception* unwind_exception) {
    unwind_exception->exception_class = kOurExceptionClass;
}

static void setDependentExceptionClass(_Unwind_Exception* unwind_exception) {
    unwind_exception->exception_class = kOurDependentExceptionClass;
}

//  Is it one of ours?
static bool isOurExceptionClass(const _Unwind_Exception* unwind_exception) {
    return (unwind_exception->exception_class & get_vendor_and_language) == 
           (kOurExceptionClass                & get_vendor_and_language);
}

static bool isDependentException(_Unwind_Exception* unwind_exception) {
    return (unwind_exception->exception_class & 0xFF) == 0x01;
}

//  This does not need to be atomic
static inline int incrementHandlerCount(__cxa_exception *exception) {
    return ++exception->handlerCount;
}

//  This does not need to be atomic
static inline  int decrementHandlerCount(__cxa_exception *exception) {
    return --exception->handlerCount;
}

#include "fallback_malloc.ipp"

//  Allocate some memory from _somewhere_
static void *do_malloc(size_t size) {
    void *ptr = std::malloc(size);
    if (NULL == ptr) // if malloc fails, fall back to emergency stash
        ptr = fallback_malloc(size);
    return ptr;
}

static void do_free(void *ptr) {
    is_fallback_ptr(ptr) ? fallback_free(ptr) : std::free(ptr);
}

/*
    If reason isn't _URC_FOREIGN_EXCEPTION_CAUGHT, then the terminateHandler
    stored in exc is called.  Otherwise the exceptionDestructor stored in 
    exc is called, and then the memory for the exception is deallocated.

    This is never called for a __cxa_dependent_exception.
*/
static
void
exception_cleanup_func(_Unwind_Reason_Code reason, _Unwind_Exception* unwind_exception)
{
    __cxa_exception* exception_header = cxa_exception_from_exception_unwind_exception(unwind_exception);
    if (_URC_FOREIGN_EXCEPTION_CAUGHT != reason)
        std::__terminate(exception_header->terminateHandler);
    // Just in case there exists a dependent exception that is pointing to this,
    //    check the reference count and only destroy this if that count goes to zero.
    __cxa_decrement_exception_refcount(unwind_exception + 1);
}

static LIBCXXABI_NORETURN void failed_throw(__cxa_exception* exception_header) {
//  Section 2.5.3 says:
//      * For purposes of this ABI, several things are considered exception handlers:
//      ** A terminate() call due to a throw.
//  and
//      * Upon entry, Following initialization of the catch parameter, 
//          a handler must call:
//      * void *__cxa_begin_catch(void *exceptionObject );
    (void) __cxa_begin_catch(&exception_header->unwindHeader);
    std::__terminate(exception_header->terminateHandler);
}

extern "C" {

//  Allocate a __cxa_exception object, and zero-fill it.
//  Reserve "thrown_size" bytes on the end for the user's exception
//  object. Zero-fill the object. If memory can't be allocated, call
//  std::terminate. Return a pointer to the memory to be used for the
//  user's exception object.
void * __cxa_allocate_exception (size_t thrown_size) throw() {
    size_t actual_size = cxa_exception_size_from_exception_thrown_size(thrown_size);
    __cxa_exception* exception_header = static_cast<__cxa_exception*>(do_malloc(actual_size));
    if (NULL == exception_header)
        std::terminate();
    std::memset(exception_header, 0, actual_size);
    return thrown_object_from_cxa_exception(exception_header);
}


//  Free a __cxa_exception object allocated with __cxa_allocate_exception.
void __cxa_free_exception (void * thrown_object) throw() {
    do_free(cxa_exception_from_thrown_object(thrown_object));
}


//  This function shall allocate a __cxa_dependent_exception and
//  return a pointer to it. (Really to the object, not past its' end).
//  Otherwise, it will work like __cxa_allocate_exception.
void * __cxa_allocate_dependent_exception () {
    size_t actual_size = sizeof(__cxa_dependent_exception);
    void *ptr = do_malloc(actual_size);
    if (NULL == ptr)
        std::terminate();
    std::memset(ptr, 0, actual_size);
    return ptr;
}


//  This function shall free a dependent_exception.
//  It does not affect the reference count of the primary exception.
void __cxa_free_dependent_exception (void * dependent_exception) {
    do_free(dependent_exception);
}


// 2.4.3 Throwing the Exception Object
/*
After constructing the exception object with the throw argument value,
the generated code calls the __cxa_throw runtime library routine. This
routine never returns.

The __cxa_throw routine will do the following:

* Obtain the __cxa_exception header from the thrown exception object address,
which can be computed as follows: 
 __cxa_exception *header = ((__cxa_exception *) thrown_exception - 1); 
* Save the current unexpected_handler and terminate_handler in the __cxa_exception header.
* Save the tinfo and dest arguments in the __cxa_exception header. 
* Set the exception_class field in the unwind header. This is a 64-bit value
representing the ASCII string "XXXXC++\0", where "XXXX" is a
vendor-dependent string. That is, for implementations conforming to this
ABI, the low-order 4 bytes of this 64-bit value will be "C++\0".
* Increment the uncaught_exception flag. 
* Call _Unwind_RaiseException in the system unwind library, Its argument is the
pointer to the thrown exception, which __cxa_throw itself received as an argument.
__Unwind_RaiseException begins the process of stack unwinding, described
in Section 2.5. In special cases, such as an inability to find a
handler, _Unwind_RaiseException may return. In that case, __cxa_throw
will call terminate, assuming that there was no handler for the
exception.
*/
LIBCXXABI_NORETURN
void 
__cxa_throw(void* thrown_object, std::type_info* tinfo, void (*dest)(void*))
{
    __cxa_eh_globals *globals = __cxa_get_globals();
    __cxa_exception* exception_header = cxa_exception_from_thrown_object(thrown_object);

    exception_header->unexpectedHandler = std::get_unexpected();
    exception_header->terminateHandler  = std::get_terminate();
    exception_header->exceptionType = tinfo;
    exception_header->exceptionDestructor = dest;
    setExceptionClass(&exception_header->unwindHeader);
    exception_header->referenceCount = 1;  // This is a newly allocated exception, no need for thread safety.
    globals->uncaughtExceptions += 1;   // Not atomically, since globals are thread-local

    exception_header->unwindHeader.exception_cleanup = exception_cleanup_func;
#if __arm__
    _Unwind_SjLj_RaiseException(&exception_header->unwindHeader);
#else
    _Unwind_RaiseException(&exception_header->unwindHeader);
#endif
    //  This only happens when there is no handler, or some unexpected unwinding
    //     error happens.
    failed_throw(exception_header);
}


// 2.5.3 Exception Handlers
/*
The adjusted pointer is computed by the personality routine during phase 1
  and saved in the exception header (either __cxa_exception or
  __cxa_dependent_exception).

  Requires:  exception is native
*/
void*
__cxa_get_exception_ptr(void* unwind_exception) throw()
{
    return cxa_exception_from_exception_unwind_exception
           (
               static_cast<_Unwind_Exception*>(unwind_exception)
           )->adjustedPtr;
}
    
/*
This routine can catch foreign or native exceptions.  If native, the exception
can be a primary or dependent variety.  This routine may remain blissfully
ignorant of whether the native exception is primary or dependent.

If the exception is native:
* Increment's the exception's handler count.
* Push the exception on the stack of currently-caught exceptions if it is not 
  already there (from a rethrow).
* Decrements the uncaught_exception count.
* Returns the adjusted pointer to the exception object, which is stored in
  the __cxa_exception by the personality routine.

If the exception is foreign, this means it did not originate from one of throw
routines.  The foreign exception does not necessarily have a __cxa_exception
header.  However we can catch it here with a catch (...), or with a call
to terminate or unexpected during unwinding.
* Do not try to increment the exception's handler count, we don't know where
  it is.
* Push the exception on the stack of currently-caught exceptions only if the
  stack is empty.  The foreign exception has no way to link to the current
  top of stack.  If the stack is not empty, call terminate.  Even with an
  empty stack, this is hacked in by pushing a pointer to an imaginary
  __cxa_exception block in front of the foreign exception.  It would be better
  if the __cxa_eh_globals structure had a stack of _Unwind_Exception, but it
  doesn't.  It has a stack of __cxa_exception (which has a next* in it).
* Do not decrement the uncaught_exception count because we didn't increment it
  in __cxa_throw (or one of our rethrow functions).
* If we haven't terminated, assume the exception object is just past the 
  _Unwind_Exception and return a pointer to that.
*/
void*
__cxa_begin_catch(void* unwind_arg) throw()
{
    _Unwind_Exception* unwind_exception = static_cast<_Unwind_Exception*>(unwind_arg);
    bool native_exception = isOurExceptionClass(unwind_exception);
    __cxa_eh_globals* globals = __cxa_get_globals();
    // exception_header is a hackish offset from a foreign exception, but it
    //   works as long as we're careful not to try to access any __cxa_exception
    //   parts.
    __cxa_exception* exception_header =
            cxa_exception_from_exception_unwind_exception
            (
                static_cast<_Unwind_Exception*>(unwind_exception)
            );
    if (native_exception)
    {
        // Increment the handler count, removing the flag about being rethrown
        exception_header->handlerCount = exception_header->handlerCount < 0 ?
            -exception_header->handlerCount + 1 : exception_header->handlerCount + 1;
        //  place the exception on the top of the stack if it's not already
        //    there by a previous rethrow
        if (exception_header != globals->caughtExceptions)
        {
            exception_header->nextException = globals->caughtExceptions;
            globals->caughtExceptions = exception_header;
        }
        globals->uncaughtExceptions -= 1;   // Not atomically, since globals are thread-local
        return exception_header->adjustedPtr;
    }
    // Else this is a foreign exception
    // If the caughtExceptions stack is not empty, terminate
    if (globals->caughtExceptions != 0)
        std::terminate();
    // Push the foreign exception on to the stack
    globals->caughtExceptions = exception_header;
    return unwind_exception + 1;
}


/*
Upon exit for any reason, a handler must call:
    void __cxa_end_catch ();

This routine can be called for either a native or foreign exception.
For a native exception:
* Locates the most recently caught exception and decrements its handler count.
* Removes the exception from the caught exception stack, if the handler count goes to zero.
* If the handler count goes down to zero, and the exception was not re-thrown
  by throw, it locates the primary exception (which may be the same as the one
  it's handling) and decrements its reference count. If that reference count
  goes to zero, the function destroys the exception. In any case, if the current
  exception is a dependent exception, it destroys that.

For a foreign exception:
* If it has been rethrown, there is nothing to do.
* Otherwise delete the exception and pop the catch stack to empty.
*/
void __cxa_end_catch()
{
    static_assert(sizeof(__cxa_exception) == sizeof(__cxa_dependent_exception),
                  "sizeof(__cxa_exception) must be equal to sizeof(__cxa_dependent_exception)");
    __cxa_eh_globals* globals = __cxa_get_globals_fast(); // __cxa_get_globals called in __cxa_begin_catch
    __cxa_exception* exception_header = globals->caughtExceptions;
    // If we've rethrown a foreign exception, then globals->caughtExceptions
    //    will have been made an empty stack by __cxa_rethrow() and there is
    //    nothing more to be done.  Do nothing!
    if (NULL != exception_header)
    {
        bool native_exception = isOurExceptionClass(&exception_header->unwindHeader);
        if (native_exception)
        {
            // This is a native exception
            if (exception_header->handlerCount < 0)
            {
                //  The exception has been rethrown by __cxa_rethrow, so don't delete it
                if (0 == incrementHandlerCount(exception_header))
                {
                    //  Remove from the chain of uncaught exceptions
                    globals->caughtExceptions = exception_header->nextException;
                    // but don't destroy
                }
                // Keep handlerCount negative in case there are nested catch's
                //   that need to be told that this exception is rethrown.  Don't
                //   erase this rethrow flag until the exception is recaught.
            }
            else
            {
                // The native exception has not been rethrown
                if (0 == decrementHandlerCount(exception_header))
                {
                    //  Remove from the chain of uncaught exceptions
                    globals->caughtExceptions = exception_header->nextException;
                    // Destroy this exception, being careful to distinguish
                    //    between dependent and primary exceptions
                    if (isDependentException(&exception_header->unwindHeader))
                    {
                        // Reset exception_header to primaryException and deallocate the dependent exception
                        __cxa_dependent_exception* dep_exception_header =
                            reinterpret_cast<__cxa_dependent_exception*>(exception_header);
                        exception_header =
                            cxa_exception_from_thrown_object(dep_exception_header->primaryException);
                        __cxa_free_dependent_exception(dep_exception_header);
                    }
                    // Destroy the primary exception only if its referenceCount goes to 0
                    //    (this decrement must be atomic)
                    __cxa_decrement_exception_refcount(thrown_object_from_cxa_exception(exception_header));
                }
            }
        }       
        else
        {
            // The foreign exception has not been rethrown.  Pop the stack
            //    and delete it.  If there are nested catch's and they try
            //    to touch a foreign exception in any way, that is undefined
            //     behavior.  They likely can't since the only way to catch
            //     a foreign exception is with catch (...)!
            _Unwind_DeleteException(&globals->caughtExceptions->unwindHeader);
            globals->caughtExceptions = 0;
        }
    }
}

// Note:  exception_header may be masquerading as a __cxa_dependent_exception
//        and that's ok.  exceptionType is there too.
//        However watch out for foreign exceptions.  Return null for them.
std::type_info * __cxa_current_exception_type() {
//  get the current exception
    __cxa_eh_globals *globals = __cxa_get_globals_fast();
    if (NULL == globals)
        return NULL;     //  If there have never been any exceptions, there are none now.
    __cxa_exception *exception_header = globals->caughtExceptions;
    if (NULL == exception_header)
        return NULL;        //  No current exception
    if (!isOurExceptionClass(&exception_header->unwindHeader))
        return NULL;
    return exception_header->exceptionType;
}

// 2.5.4 Rethrowing Exceptions
/*  This routine can rethrow native or foreign exceptions.
If the exception is native:
* marks the exception object on top of the caughtExceptions stack 
  (in an implementation-defined way) as being rethrown. 
* If the caughtExceptions stack is empty, it calls terminate() 
  (see [C++FDIS] [except.throw], 15.1.8). 
* It then calls _Unwind_RaiseException which should not return
   (terminate if it does).
  Note:  exception_header may be masquerading as a __cxa_dependent_exception
         and that's ok.
*/
LIBCXXABI_NORETURN
void
__cxa_rethrow()
{
    __cxa_eh_globals* globals = __cxa_get_globals();
    __cxa_exception* exception_header = globals->caughtExceptions;
    if (NULL == exception_header)
        std::terminate();      // throw; called outside of a exception handler
    bool native_exception = isOurExceptionClass(&exception_header->unwindHeader);
    if (native_exception)
    {
        //  Mark the exception as being rethrown (reverse the effects of __cxa_begin_catch)
        exception_header->handlerCount = -exception_header->handlerCount;
        globals->uncaughtExceptions += 1;
        //  __cxa_end_catch will remove this exception from the caughtExceptions stack if necessary
    }
    else  // this is a foreign exception
    {
        // The only way to communicate to __cxa_end_catch that we've rethrown
        //   a foreign exception, so don't delete us, is to pop the stack here
        //   which must be empty afterwards.  Then __cxa_end_catch will do
        //   nothing
        globals->caughtExceptions = 0;
    }
#if __arm__
    _Unwind_SjLj_RaiseException(&exception_header->unwindHeader);
#else
    _Unwind_RaiseException(&exception_header->unwindHeader);
#endif

    //  If we get here, some kind of unwinding error has occurred.
    //  There is some weird code generation bug happening with 
    //     Apple clang version 4.0 (tags/Apple/clang-418.0.2) (based on LLVM 3.1svn)
    //     If we call failed_throw here.  Turns up with -O2 or higher, and -Os.
    __cxa_begin_catch(&exception_header->unwindHeader);
    if (native_exception)
        std::__terminate(exception_header->terminateHandler);
    // Foreign exception: can't get exception_header->terminateHandler
    std::terminate();
}

/*
    If thrown_object is not null, atomically increment the referenceCount field
    of the __cxa_exception header associated with the thrown object referred to
    by thrown_object.

    Requires:  If thrown_object is not NULL, it is a native exception.
*/
void
__cxa_increment_exception_refcount(void* thrown_object) throw()
{
    if (thrown_object != NULL )
    {
        __cxa_exception* exception_header = cxa_exception_from_thrown_object(thrown_object);
        __sync_add_and_fetch(&exception_header->referenceCount, 1);
    }
}

/*
    If thrown_object is not null, atomically decrement the referenceCount field
    of the __cxa_exception header associated with the thrown object referred to
    by thrown_object.  If the referenceCount drops to zero, destroy and
    deallocate the exception.

    Requires:  If thrown_object is not NULL, it is a native exception.
*/
void
__cxa_decrement_exception_refcount(void* thrown_object) throw()
{
    if (thrown_object != NULL )
    {
        __cxa_exception* exception_header = cxa_exception_from_thrown_object(thrown_object);
        if (__sync_sub_and_fetch(&exception_header->referenceCount, size_t(1)) == 0)
        {
            if (NULL != exception_header->exceptionDestructor)
                exception_header->exceptionDestructor(thrown_object);
            __cxa_free_exception(thrown_object);
        }
    }
}

/*
    Returns a pointer to the thrown object (if any) at the top of the
    caughtExceptions stack.  Atomically increment the exception's referenceCount.
    If there is no such thrown object or if the thrown object is foreign,
    returns null.

    We can use __cxa_get_globals_fast here to get the globals because if there have
    been no exceptions thrown, ever, on this thread, we can return NULL without 
    the need to allocate the exception-handling globals.
*/
void*
__cxa_current_primary_exception() throw()
{
//  get the current exception
    __cxa_eh_globals* globals = __cxa_get_globals_fast();
    if (NULL == globals)
        return NULL;        //  If there are no globals, there is no exception
    __cxa_exception* exception_header = globals->caughtExceptions;
    if (NULL == exception_header)
        return NULL;        //  No current exception
    if (!isOurExceptionClass(&exception_header->unwindHeader))
        return NULL;        // Can't capture a foreign exception (no way to refcount it)
    if (isDependentException(&exception_header->unwindHeader)) {
        __cxa_dependent_exception* dep_exception_header =
            reinterpret_cast<__cxa_dependent_exception*>(exception_header);
        exception_header = cxa_exception_from_thrown_object(dep_exception_header->primaryException);
    }
    void* thrown_object = thrown_object_from_cxa_exception(exception_header);
    __cxa_increment_exception_refcount(thrown_object);
    return thrown_object;
}

/*
    If reason isn't _URC_FOREIGN_EXCEPTION_CAUGHT, then the terminateHandler
    stored in exc is called.  Otherwise the referenceCount stored in the
    primary exception is decremented, destroying the primary if necessary.
    Finally the dependent exception is destroyed.
*/
static
void
dependent_exception_cleanup(_Unwind_Reason_Code reason, _Unwind_Exception* unwind_exception)
{
    __cxa_dependent_exception* dep_exception_header = 
                      reinterpret_cast<__cxa_dependent_exception*>(unwind_exception + 1) - 1;
    if (_URC_FOREIGN_EXCEPTION_CAUGHT != reason)
        std::__terminate(dep_exception_header->terminateHandler);
    __cxa_decrement_exception_refcount(dep_exception_header->primaryException);
    __cxa_free_dependent_exception(dep_exception_header);
}

/*
    If thrown_object is not null, allocate, initialize and throw a dependent
    exception.
*/
void
__cxa_rethrow_primary_exception(void* thrown_object)
{
    if ( thrown_object != NULL )
    {
        // thrown_object guaranteed to be native because
        //   __cxa_current_primary_exception returns NULL for foreign exceptions
        __cxa_exception* exception_header = cxa_exception_from_thrown_object(thrown_object);
        __cxa_dependent_exception* dep_exception_header =
            static_cast<__cxa_dependent_exception*>(__cxa_allocate_dependent_exception());
        dep_exception_header->primaryException = thrown_object;
        __cxa_increment_exception_refcount(thrown_object);
        dep_exception_header->exceptionType = exception_header->exceptionType;
        dep_exception_header->unexpectedHandler = std::get_unexpected();
        dep_exception_header->terminateHandler = std::get_terminate();
        setDependentExceptionClass(&dep_exception_header->unwindHeader);
        __cxa_get_globals()->uncaughtExceptions += 1;
        dep_exception_header->unwindHeader.exception_cleanup = dependent_exception_cleanup;
#if __arm__
        _Unwind_SjLj_RaiseException(&dep_exception_header->unwindHeader);
#else
        _Unwind_RaiseException(&dep_exception_header->unwindHeader);
#endif
        // Some sort of unwinding error.  Note that terminate is a handler.
        __cxa_begin_catch(&dep_exception_header->unwindHeader);
    }
    // If we return client will call terminate()
}

bool
__cxa_uncaught_exception() throw()
{
    // This does not report foreign exceptions in flight
    __cxa_eh_globals* globals = __cxa_get_globals_fast();
    if (globals == 0)
        return false;
    return globals->uncaughtExceptions != 0;
}

}  // extern "C"

#pragma GCC visibility pop

}  // abi
