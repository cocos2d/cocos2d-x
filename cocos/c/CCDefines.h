//
//  CCDefines.h
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/14/16.
//
//

#ifndef CCDefines_h
#define CCDefines_h

#define SWIFT_PRIVATE __attribute__((swift_private))

#define SWIFT_NAME(x) __attribute__((swift_name(#x)))

#define CC_ENUM CF_ENUM

#if !__has_feature(nullability)
#ifndef _Nullable
#define _Nullable
#endif
#ifndef _Nonnull
#define _Nonnull
#endif
#ifndef _Null_unspecified
#define _Null_unspecified
#endif
#endif

#ifndef CC_ASSUME_NONNULL_BEGIN
#if __has_feature(assume_nonnull)
#define CC_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#else
#define CC_ASSUME_NONNULL_BEGIN
#endif
#endif

#ifndef CC_ASSUME_NONNULL_END
#if __has_feature(assume_nonnull)
#define CC_ASSUME_NONNULL_END _Pragma("clang assume_nonnull end")
#else
#define CC_ASSUME_NONNULL_END
#endif
#endif

#if __LP64__ || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
typedef long CCInteger;
typedef unsigned long CCUInteger;
#else
typedef int CCInteger;
typedef unsigned int CCUInteger;
#endif

#endif /* CCDefines_h */
