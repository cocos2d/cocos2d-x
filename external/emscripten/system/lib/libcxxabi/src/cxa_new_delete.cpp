//===------------------------ cxa_new_delete.cpp --------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//
// This file implements the new and delete operators.
//===----------------------------------------------------------------------===//

#include <new>
#include <cstdlib>

/*
[new.delete.single]

* Executes a loop: Within the loop, the function first attempts to allocate
  the requested storage. Whether the attempt involves a call to the Standard C
  library function malloc is unspecified.

* Returns a pointer to the allocated storage if the attempt is successful.
  Otherwise, if the current new_handler (18.6.2.5) is a null pointer value,
  throws bad_alloc.

* Otherwise, the function calls the current new_handler function (18.6.2.3).
  If the called function returns, the loop repeats.

* The loop terminates when an attempt to allocate the requested storage is
  successful or when a called new_handler function does not return.
*/
__attribute__((__weak__, __visibility__("default")))
void *
operator new(std::size_t size)
#if !__has_feature(cxx_noexcept)
    throw(std::bad_alloc)
#endif
{
    if (size == 0)
        size = 1;
    void* p;
    while ((p = std::malloc(size)) == 0)
    {
        std::new_handler nh = std::get_new_handler();
        if (nh)
            nh();
        else
            throw std::bad_alloc();
    }
    return p;
}

/*
Note:  The relationships among these operators is both carefully considered
and standard in C++11.  Please do not change them without fully understanding
the consequences of doing so.  Reference:
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2158.html
*/
/*
[new.delete.single]

Calls operator new(size). If the call returns normally, returns the result of
that call. Otherwise, returns a null pointer.
*/
__attribute__((__weak__, __visibility__("default")))
void*
operator new(size_t size, const std::nothrow_t&)
#if __has_feature(cxx_noexcept)
    noexcept
#else
    throw()
#endif
{
    void* p = 0;
    try
    {
        p = ::operator new(size);
    }
    catch (...)
    {
    }
    return p;
}

/*
[new.delete.array]

Returns operator new(size).
*/
__attribute__((__weak__, __visibility__("default")))
void*
operator new[](size_t size)
#if !__has_feature(cxx_noexcept)
    throw(std::bad_alloc)
#endif
{
    return ::operator new(size);
}

/*
[new.delete.array]

Calls operator new[](size). If the call returns normally, returns the result
of that call. Otherwise, returns a null pointer.
*/
__attribute__((__weak__, __visibility__("default")))
void*
operator new[](size_t size, const std::nothrow_t&)
#if __has_feature(cxx_noexcept)
    noexcept
#else
    throw()
#endif
{
    void* p = 0;
    try
    {
        p = ::operator new[](size);
    }
    catch (...)
    {
    }
    return p;
}

/*
[new.delete.single]

If ptr is null, does nothing. Otherwise, reclaims the storage allocated by the
earlier call to operator new.
*/
__attribute__((__weak__, __visibility__("default")))
void
operator delete(void* ptr)
#if __has_feature(cxx_noexcept)
    noexcept
#else
    throw()
#endif
{
    if (ptr)
        std::free(ptr);
}

/*
[new.delete.single]

calls operator delete(ptr)
*/
__attribute__((__weak__, __visibility__("default")))
void
operator delete(void* ptr, const std::nothrow_t&)
#if __has_feature(cxx_noexcept)
    noexcept
#else
    throw()
#endif
{
    ::operator delete(ptr);
}

/*
[new.delete.array]

Calls operator delete(ptr)
*/
__attribute__((__weak__, __visibility__("default")))
void
operator delete[] (void* ptr)
#if __has_feature(cxx_noexcept)
    noexcept
#else
    throw()
#endif
{
    ::operator delete(ptr);
}

/*
[new.delete.array]

calls operator delete[](ptr)
*/
__attribute__((__weak__, __visibility__("default")))
void
operator delete[] (void* ptr, const std::nothrow_t&)
#if __has_feature(cxx_noexcept)
    noexcept
#else
    throw()
#endif
{
    ::operator delete[](ptr);
}

namespace std
{

//  bad_alloc

bad_alloc::bad_alloc() _NOEXCEPT
{
}

bad_alloc::~bad_alloc() _NOEXCEPT
{
}

const char*
bad_alloc::what() const _NOEXCEPT
{
    return "std::bad_alloc";
}

// bad_array_new_length

bad_array_new_length::bad_array_new_length() _NOEXCEPT
{
}

bad_array_new_length::~bad_array_new_length() _NOEXCEPT
{
}

const char*
bad_array_new_length::what() const _NOEXCEPT
{
    return "bad_array_new_length";
}

#ifdef EMSCRIPTEN
// We don't build the new.cpp from libcxx, so we need to define this.
void
__throw_bad_alloc()
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    throw bad_alloc();
#endif
}
#endif

}  // std
