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