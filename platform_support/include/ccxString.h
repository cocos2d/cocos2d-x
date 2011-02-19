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

#ifndef __CCX_STRING_H_YANGWS_20110127__
#define __CCX_STRING_H_YANGWS_20110127__

#include "ccxCommon.h"

/**
@file
@brief  cocos2d-x uses std::string or std::wstring as ccxString now.

There are some useful tool for ccxString:
- ccxStringTrim
- ccxStringCompareIgnoreCase
- ccxStringToUpper
- ccxStringToLower
- ccxStringReplaceText
- ccxStringExplode
@todo ccxStringPrintf, ccxStringConvertToAnsi, ccxStringConvertToWide
*/

#include <string>

NS_CC_BEGIN;

typedef std::string ccxAString;
typedef ccxAString ccxString;

// ccxStringTrim
/** 
@todo ccxStringTrim must re-implement.
Because basic_string is not have the same implement on different platform.
*/
#if 0
template <class _E, class Tr, class AllocT >
inline std::basic_string<_E, Tr, AllocT >& ccxStringTrim(std::basic_string<_E, Tr, AllocT >& str, 
                                                 const _E* blanks)
{
    typedef std::basic_string<_E, Tr, AllocT > StringT;

    StringT::size_type pos1 = str.find_first_not_of(blanks);
    if (pos1 == StringT::npos)
    {
        str.erase();
        return str;
    }

    StringT::size_type count = str.find_last_not_of(blanks) - pos1 + 1;
    if (str.length() != count)
        str = str.substr(pos1, count);
    return str;
}

// ccxStringCompareIgnoreCase
inline int compareCharIgnoreCase(int left, int right)
{
    return tolower(left) - tolower(right);
}

template<class LeftIter, class RightIter, class CompT >
inline int compareElementsByIterator(LeftIter  leftIterBegin, 
                              LeftIter  leftIterEnd, 
                              RightIter rightIterBegin, 
                              RightIter rightIterEnd, 
                              CompT     cmp)
{
    int ret = 0;
    for (;
        (leftIterBegin != leftIterEnd) && (rightIterBegin != rightIterEnd);
        ++leftIterBegin, ++rightIterBegin)
        if (ret = cmp(*leftIterBegin, *rightIterBegin)) break;
    return ret;
}

template <class _E, class Tr, class AllocT >
inline int ccxStringCompareIgnoreCase(std::basic_string<_E, Tr, AllocT >& left, 
                                      std::basic_string<_E, Tr, AllocT >& right)
{
    return compareElementsByIterator(left.begin(), left.end(), 
        right.begin(), right.end(), compareCharIgnoreCase);
}

// ccxStringToUpper 
template <class _E, class Tr, class AllocT >
inline std::basic_string<_E, Tr, AllocT >& ccxStringToUpper(std::basic_string<_E, Tr, AllocT >& str)
{
    transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}

// ccxStringToLower
template <class _E, class Tr, class AllocT >
inline std::basic_string<_E, Tr, AllocT >& ccxStringToLower(std::basic_string<_E, Tr, AllocT >& str)
{
    transform(str.begin(), str.end(), str.begin(), tolower);
    return str;
}

/**
@brief	Replace the sub text to another text in string.
@param  text        The string will be processed.
@param  findText    The sub text will be replaced.
@param  replaceText The new sub text.
@return             The reference of string which after replace text.
*/
template <class StringT >
inline StringT& ccxStringReplaceText(StringT&      text, 
                             const StringT& findText, 
                             const StringT& replaceText)
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

// ccxStringExplode

// ccxString Explode Flags
enum
{
    kefTrim             = 0x1,
    kefSkipEmpty        = 0x2,
    kefEraseDelimiters  = 0x4,  // only support left right pair delimiter
    kefDefaultFlag      = 0xff,    
};

/**
@brief	Verify every tokens parsed by ccxStringExplode from sequence.
*/
template <int flag >
struct TokenVerifier
{
    template<class StringT >
    StringT * operator()(StringT&       token, 
                         const StringT& delimiters)
    {
        if (kefTrim & flag) ccxStringTrim(token);
        return (kefSkipEmpty & flag && token.length() <= 0) ? 0 : &token;
    }

    template<class StringT >
    StringT * operator()(StringT&       token, 
                         const StringT& deliLeft, 
                         const StringT& deliRight)
    {
        if (kefEraseDelimiters & flag) token = token.substr(1, token.length() - 2);
        if (kefTrim & flag) ccxStringTrim(token);
        return (kefSkipEmpty & flag && token.length() <= 0) ? 0 : &token;
    }
};

/**
@brief  Splits a given string into tokens separated by supplied delimiters as a string.

Every token will be processed by verifier before save to container.
@param  container   The container of token, which stored in.
@param  sequence    The string which contained tokens.
@param  delimiters  The possible delimiters, one delimiter is a char element.
@param  verifier    The functor for process tokens.
@return             The count of tokens which saved to container.
*/
template<class StringT, class ContainerT, class VerifierT >
inline int ccxStringExplode(ContainerT&    container, 
                     const StringT& sequence, 
                     const StringT& delimiters, 
                     VerifierT&     verifier)
{
    int nRet = 0;       // the count of tokens parsed from sequence
    StringT::size_type lastPos  = sequence.find_first_not_of(delimiters, 0);
    StringT::size_type pos      = lastPos;

    StringT * pToken = 0;
    while (StringT::npos != pos)
    {
        // find the next delimiter pos
        pos = sequence.find_first_of(delimiters, lastPos);
        StringT token = sequence.substr(lastPos, pos - lastPos);
        if (pToken = verifier(token, delimiters)) 
        {
            container.push_back(*pToken);
            ++nRet;
        }
        lastPos = pos + 1;
    }

    return nRet;
}

/**
@brief  Splits a given string into tokens separated by supplied delimiters as a string.

Every token will be processed by default verifier, which erase the delimiters, trim it and skip empty token.
@param  container   The container of token, which stored in.
@param  sequence    The string which contained tokens.
@param  delimiters  The possible delimiters, one delimiter is a char element.
@return             The count of tokens which saved to container.
*/
template<class StringT, class ContainerT >
inline int ccxStringExplode(ContainerT&    container, 
                     const StringT& sequence, 
                     const StringT& delimiters)
{
    return ccxStringExplode(container, sequence, delimiters, 
        TokenVerifier<kefDefaultFlag >());
}

/**
@brief  Splits a given string into tokens separated by one starting delimiter and ending one.

Every token will be processed by verifier before save to container.
@param  container   The container of token, which stored in.
@param  sequence    The string which contained tokens.
@param  deliLeft    The possible starting delimiters, one delimiter is a char element.
@param  deliRight   The possible ending delimiters, one delimiter is a char element.
@param  verifier    The functor for process tokens.
@return             The count of tokens which saved to container.
*/
template<class StringT, class ContainerT, class VerifierT >
inline int ccxStringExplode2(ContainerT&       container, 
                      const StringT&    sequence, 
                      const StringT&    deliLeft, 
                      const StringT&    deliRight, 
                      VerifierT&        verifier)
{
    int nRet = 0;       // the count of tokens parsed from sequence
    StringT::size_type lpos = sequence.find_first_of(deliLeft, 0);
    StringT::size_type rpos = sequence.find_first_of(deliRight, lpos + 1);

    StringT * pToken = 0;
    while (StringT::npos != lpos && StringT::npos != rpos)
    {
        // find the token, get sub string with delimiters
        StringT token = sequence.substr(lpos, rpos - lpos + 1);
        if (pToken = verifier(token, deliLeft, deliRight)) 
        {
            container.push_back(*pToken);
            ++nRet;
        }
        lpos = sequence.find_first_of(deliLeft, rpos + 1);
        rpos = sequence.find_first_of(deliRight, lpos + 1);
    }

    return nRet;
}

/**
@brief  Splits a given string into tokens separated by one starting delimiter and ending one.

Every token will be processed by default verifier, which erase the delimiters, trim it and skip empty token.
@param  container   The container of token, which stored in.
@param  sequence    The string which contained tokens.
@param  deliLeft    The possible starting delimiters, one delimiter is a char element.
@param  deliRight   The possible ending delimiters, one delimiter is a char element.
@return             The count of tokens which saved to container.
*/
template<class StringT, class ContainerT >
inline int ccxStringExplode2(ContainerT&       container, 
                      const StringT&    sequence, 
                      const StringT&    deliLeft, 
                      const StringT&    deliRight)
{
    return ccxStringExplode2(container, sequence, deliLeft, deliRight, 
        TokenVerifier<kefDefaultFlag >());
}

#if ! (CCX_SUPPORT_UNICODE)

// ccxAstring

typedef std::string ccxAString;
typedef ccxAString ccxString;

template <class Tr, class AllocT >
inline void ccxStringTrim(std::basic_string<char, Tr, AllocT >& str)
{
    const char blanks[] = { ' ', '\t', '\r', '\n', '\0' };
    ccxStringTrim(str, blanks);
}

#else   // CCX_SUPPORT_UNICODE

// ccxWString

typedef std::wstring ccxWString;
typedef ccxWString ccxString;

template <class Tr, class AllocT >
inline inline void ccxStringTrim(std::basic_string<wchar_t, Tr, AllocT >& str)
{
    const wchar_t blanks[] =
    {
        ' ', 12288, '\t', '\r', '\n', '\0'
    };
    ccxStringTrim(str, blanks);
}

#endif  // CCX_SUPPORT_UNICODE
#endif

NS_CC_END;

#endif	// __CCX_STRING_H_YANGWS_20110127__
