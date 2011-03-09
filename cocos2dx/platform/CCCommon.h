/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __CC_COMMON_H__
#define __CC_COMMON_H__

#include "CCPlatformMacros.h"

NS_CC_BEGIN;

// [u]int[8|16|32|64]
// char
typedef unsigned char       ccxByte;
typedef signed short        ccxInt16;
typedef unsigned short      ccxUInt16;
// int
// unsigned
typedef long long           ccxInt64;
typedef unsigned long long  ccxUInt64;	

/// The max length of CCLog message.
static const int kMaxLogLen = 255;

/**
@brief	Output Debug message.
*/
void CC_DLL_PS CCLog(const char * pszFormat, ...);

struct ccxNullDeleter       { template< class TPTR > void operator()(TPTR ) {} };
struct ccxNewDeleter        { template< class TPTR > void operator()(TPTR p) { delete p; } };
struct ccxNewArrayDeleter   { template< class TPTR > void operator()(TPTR p) { delete[] p; } };

/**
@brief	A simple scoped pointer.
*/
template < class T, class D = ccxNewDeleter >
class ccxScopedPtr   // noncopyable
    : private D
{
public:
    explicit ccxScopedPtr(T * p = 0): m_ptr(p) {}
    ~ccxScopedPtr()                     { if (m_ptr) (*static_cast<D*>(this))(m_ptr); }

    void reset(T * p = 0)               { ccxScopedPtr< T >(p).swap(*this); }
    T *  get() const                    { return m_ptr; }
    void swap(ccxScopedPtr & b)         { T * tmp = b.m_ptr; b.m_ptr = m_ptr; m_ptr   = tmp; }

    T & operator*() const               { return * m_ptr; }
    T * operator->() const              { return m_ptr; }
    operator bool () const              { return m_ptr != 0; }

private:
    ccxScopedPtr(const ccxScopedPtr&);
    ccxScopedPtr & operator=(const ccxScopedPtr&);

    void operator==(const ccxScopedPtr& ) const;
    void operator!=(const ccxScopedPtr& ) const;

    T * m_ptr;
};
/**
@brief	A simple scoped point for array.
*/
template< class T, class D = ccxNewArrayDeleter >
class CC_DLL_PS ccxScopedArray // noncopyable
    : private D
{
public:
    explicit ccxScopedArray( T * p = 0 ) : m_ptr( p ) {}
    ~ccxScopedArray()                   { if (m_ptr) (*static_cast<D*>(this))(m_ptr); }

    void reset(T * p = 0)               { ccxScopedArray<T>(p).swap(*this); }
    T *  get() const                    { return m_ptr; }
    void swap(ccxScopedArray & b)       { T * tmp = b.m_ptr; b.m_ptr = m_ptr; m_ptr = tmp; }

    T & operator[](int i) const         { CC_ASSERT(m_ptr && i >= 0); return m_ptr[i]; }
   operator bool () const              { return m_ptr != 0; }

private:
    ccxScopedArray(ccxScopedArray const &);
    ccxScopedArray & operator=(ccxScopedArray const &);

    void operator==( ccxScopedArray const& ) const;
    void operator!=( ccxScopedArray const& ) const;

    T * m_ptr;
};

NS_CC_END;

#endif	// __CC_COMMON_H__
