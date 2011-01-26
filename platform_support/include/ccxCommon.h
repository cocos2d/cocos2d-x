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

//////////////////////////////////////////////////////////////////////////
// cocos2d-x string classes
//////////////////////////////////////////////////////////////////////////

#include <string>

// some string utility: trim compaireIgnoreCase toUpper toLower replaceText im/explode sprintf
NS_CC_BEGIN;

// ccxStringTrim
template <class _E, class Tr, class AllocT>
inline std::basic_string<_E, Tr, AllocT>& ccxStringTrim(std::basic_string<_E, Tr, AllocT>& str, const _E* blanks)
{
    typedef std::basic_string<_E, Tr, AllocT> StringT;
    typedef typename StringT::size_type size_type;

    size_type pos1 = str.find_first_not_of(blanks);
    if (pos1 == StringT::npos)
    {
        str.erase();
        return str;
    }

    size_type count = str.find_last_not_of(blanks) - pos1 + 1;
    if (str.length() != count)
        str = str.substr(pos1, count);
    return str;
}

// ccxStringCompareIgnoreCase
inline int compareCharIgnoreCase(int left, int right)
{
    return tolower(left) - tolower(right);
}

template<class LeftIter, class RightIter, class CompT>
inline int compareElementsByIterator(LeftIter leftIterBegin, LeftIter leftIterEnd, RightIter rightIterBegin, RightIter rightIterEnd, CompT cmp)
{
    int ret = 0;
    for (; (leftIterBegin != leftIterEnd) && (rightIterBegin != rightIterEnd); ++leftIterBegin, ++rightIterBegin)
        if (ret = cmp(*leftIterBegin, *rightIterBegin)) break;
    return ret;
}

template <class _E, class Tr, class AllocT>
inline int ccxStringCompareIgnoreCase(std::basic_string<_E, Tr, AllocT >& left, std::basic_string<_E, Tr, AllocT >& right)
{
    return compareElementsByIterator(left.begin(), left.end(), right.begin(), right.end(), compareCharIgnoreCase);
}

// ccxStringToUpper, 
template <class _E, class Tr, class AllocT>
inline std::basic_string<_E, Tr, AllocT >& ccxStringToUpper(std::basic_string<_E, Tr, AllocT >& str)
{
    transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}

// ccxStringToLower
template <class _E, class Tr, class AllocT>
inline std::basic_string<_E, Tr, AllocT >& ccxStringToLower(std::basic_string<_E, Tr, AllocT >& str)
{
    transform(str.begin(), str.end(), str.begin(), tolower);
    return str;
}

// ccxStringReplaceText
template <class StringT>
inline StringT& ccxStringReplaceText(StringT& text, const StringT& findText, const StringT& replaceText)
{
    typedef typename StringT::size_type size_type;
    size_type pos = 0;
    while ((pos = text.find(findText, pos)) != StringT::npos)
    {
        text.replace(pos, findText.size(), replaceText);
        pos += replaceText.size();
    }
    return text;
}

#if ! (CCX_SUPPORT_UNICODE)

// ccxAstring

typedef std::string ccxAString;
typedef ccxAString ccxString;

template <class Tr, class AllocT>
inline void ccxStringTrim(std::basic_string<char, Tr, AllocT>& str)
{
    const char blanks[] = { ' ', '\t', '\r', '\n', '\0' };
    ccxStringTrim(str, blanks);
}

#else   // CCX_SUPPORT_UNICODE

// ccxWstring

typedef std::wstring ccxWString;
typedef ccxWString ccxString;

template <class Tr, class AllocT>
inline void ccxStringTrim(std::basic_string<wchar_t, Tr, AllocT>& str)
{
    const wchar_t blanks[] =
    {
        ' ', 12288, '\t', '\r', '\n', '\0'
    };
    ccxStringTrim(str, blanks);
}

#endif  // CCX_SUPPORT_UNICODE

NS_CC_END;

#endif	// __CCX_COMMON_H__
