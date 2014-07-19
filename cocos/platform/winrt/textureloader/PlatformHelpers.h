//--------------------------------------------------------------------------------------
// File: PlatformHelpers.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#pragma warning(disable : 4324 4481)

#include <exception>


namespace DirectX
{
    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw std::exception();
        }
    }


    // Helper for output debug tracing
    inline void DebugTrace( _In_z_ _Printf_format_string_ const char* format, ... )
    {
#ifdef _DEBUG
        va_list args;
        va_start( args, format );

        char buff[1024]={0};
        vsprintf_s( buff, format, args );
        OutputDebugStringA( buff );
#else
        UNREFERENCED_PARAMETER( format );
#endif
    }


    // Helper smart-pointers
    struct handle_closer { void operator()(HANDLE h) { if (h) CloseHandle(h); } };

    typedef public std::unique_ptr<void, handle_closer> ScopedHandle;

    inline HANDLE safe_handle( HANDLE h ) { return (h == INVALID_HANDLE_VALUE) ? 0 : h; }
}


#if defined(_MSC_VER) && (_MSC_VER < 1610)

// Emulate the C++0x mutex and lock_guard types when building with Visual Studio versions < 2012.
namespace std
{
    class mutex
    {
    public:
        mutex()         { InitializeCriticalSection(&mCriticalSection); }
        ~mutex()        { DeleteCriticalSection(&mCriticalSection); }

        void lock()     { EnterCriticalSection(&mCriticalSection); }
        void unlock()   { LeaveCriticalSection(&mCriticalSection); }
        bool try_lock() { return TryEnterCriticalSection(&mCriticalSection) != 0; }

    private:
        CRITICAL_SECTION mCriticalSection;

        mutex(mutex const&);
        mutex& operator= (mutex const&);
    };


    template<typename Mutex>
    class lock_guard
    {
    public:
        typedef Mutex mutex_type;

        explicit lock_guard(mutex_type& mutex)
          : mMutex(mutex)
        {
            mMutex.lock();
        }

        ~lock_guard()
        {
            mMutex.unlock();
        }

    private:
        mutex_type& mMutex;

        lock_guard(lock_guard const&);
        lock_guard& operator= (lock_guard const&);
    };
}

#else   // _MSC_VER < 1610

#include <mutex>

#endif
