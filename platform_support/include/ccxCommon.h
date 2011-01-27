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

#ifndef __CCX_COMMON_H__
#define __CCX_COMMON_H__

#include "ccxMacros.h"

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

/// The max length of CCXLog message.
static const int kMaxLogLen = 255;

/**
@brief	Output Debug message.
*/
void CCX_DLL_PS CCXLog(const char * pszFormat, ...);

struct CCXNullDeleter       { template< class TPTR > void operator()(TPTR ) {} };
struct CCXNewDeleter        { template< class TPTR > void operator()(TPTR p) { delete p; } };
struct CCXNewArrayDeleter   { template< class TPTR > void operator()(TPTR p) { delete[] p; } };

/**
@brief	A simple scoped pointer.
*/
template < class T, class D = CCXNewDeleter >
class CCXScopedPtr   // noncopyable
    : private D
{
public:
    explicit CCXScopedPtr(T * p = 0): m_ptr(p) {}
    ~CCXScopedPtr()                     { (*static_cast<D*>(this))(m_ptr); }

    void reset(T * p = 0)               { CCXScopedPtr< T >(p).swap(*this); }
    T *  get() const                    { return m_ptr; }
    void swap(CCXScopedPtr & b)         { T * tmp = b.m_ptr; b.m_ptr = m_ptr; m_ptr   = tmp; }

    T & operator*() const               { return * m_ptr; }
    T * operator->() const              { return m_ptr; }
    operator bool () const              { return m_ptr != 0; }

private:
    CCXScopedPtr(const CCXScopedPtr&);
    CCXScopedPtr & operator=(const CCXScopedPtr&);

    void operator==(const CCXScopedPtr& ) const;
    void operator!=(const CCXScopedPtr& ) const;

    T * m_ptr;
};
/**
@brief	A simple scoped point for array.
*/
template< class T, class D = CCXNewArrayDeleter >
class CCX_DLL_PS CCXScopedArray // noncopyable
    : private D
{
public:
    explicit CCXScopedArray( T * p = 0 ) : m_ptr( p ) {}
    ~CCXScopedArray()                   { (*static_cast<D*>(this))(m_ptr); }

    void reset(T * p = 0)               { CCXScopedArray<T>(p).swap(*this); }
    T *  get() const                    { return m_ptr; }
    void swap(CCXScopedArray & b)       { T * tmp = b.m_ptr; b.m_ptr = m_ptr; m_ptr = tmp; }

    T & operator[](int i) const         { CCX_ASSERT(m_ptr && i >= 0); return m_ptr[i]; }
   operator bool () const              { return m_ptr != 0; }

private:
    CCXScopedArray(CCXScopedArray const &);
    CCXScopedArray & operator=(CCXScopedArray const &);

    void operator==( CCXScopedArray const& ) const;
    void operator!=( CCXScopedArray const& ) const;

    T * m_ptr;
};

NS_CC_END;

#endif	// __CCX_COMMON_H__
