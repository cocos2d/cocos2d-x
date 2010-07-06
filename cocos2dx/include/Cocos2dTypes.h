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

#ifndef __SUPPORT_COCOS2D_TYPES_H__
#define __SUPPORT_COCOS2D_TYPES_H__

// we support uphone now
#define _UPHONE 1

// define import export
#if defined(_UPHONE)
    #define COCOS2D_IMPORT SS_IMPORT
    #define COCOS2D_EXPORT SS_EXPORT
// support other platform here
#endif //_UPHONE

// define data types
#if defined(_UPHONE)
    #include <ssTypes.h>
    // undefine the types first
    #undef INT8
    #undef UINT8
    #undef INT16
    #undef UINT16
    #undef INT32
    #undef INT64
    #undef UINT64
	#undef BOOL

    #define INT8	Int8
    #define UINT8	UInt8
    #define INT16	Int16
	#define UINT16	UInt16
	#define INT32	Int32
	#define UINT32	UInt32
	#define INT64	Int64
	#define UINT64	UInt64
#endif // _UPHONE

#endif // __SUPPORT_COCOS2D_TYPES_H__