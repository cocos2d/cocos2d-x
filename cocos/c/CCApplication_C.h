//
//  CCApplication_C.hpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/16/16.
//
//

#ifndef CCApplication_C_h
#define CCApplication_C_h
#include <stdint.h>
#include <stdbool.h>

// Function callbacks for @c CCApplication

__attribute__((swift_name("InitGLContextAttributesCallback")))
typedef void (*CCApplicationInitGLContextAttributesCallback_C)();

__attribute__((swift_name("DidFinishLaunchingCallback")))
typedef bool (*CCApplicationDidFinishLaunchingCallback_C)();

__attribute__((swift_name("DidEnterBackgroundCallback")))
typedef void (*CCApplicationDidEnterBackgroundCallback_C)();

__attribute__((swift_name("WillEnterForegroundCallback")))
typedef void (*CCApplicationWillEnterForegroundCallback_C)();

#ifndef __cplusplus
#import <CCocos2D/CCDefines.h>

CC_ASSUME_NONNULL_BEGIN

#pragma mark - Initialization

/** 
 Creates the singleton Application (for use in C).
 Should only be called once. 
 */
SWIFT_PRIVATE
void CCApplicationInit();

#pragma mark - Methods

SWIFT_PRIVATE
void CCApplicationRun();

#pragma mark - Properties

SWIFT_PRIVATE
CCApplicationInitGLContextAttributesCallback_C _Nullable CCApplicationGetInitGLContextAttributesCallback();

SWIFT_PRIVATE
void CCApplicationSetInitGLContextAttributesCallback(CCApplicationInitGLContextAttributesCallback_C _Nullable callback);

SWIFT_PRIVATE
CCApplicationDidFinishLaunchingCallback_C _Nullable CCApplicationGetDidFinishLaunchingCallback();

SWIFT_PRIVATE
void CCApplicationSetDidFinishLaunchingCallback(CCApplicationDidFinishLaunchingCallback_C _Nullable callback);

SWIFT_PRIVATE
CCApplicationDidEnterBackgroundCallback_C _Nullable CCApplicationGetDidEnterBackgroundCallback();

SWIFT_PRIVATE
void CCApplicationSetDidEnterBackgroundCallback(CCApplicationDidEnterBackgroundCallback_C _Nullable callback);

SWIFT_PRIVATE
CCApplicationWillEnterForegroundCallback_C _Nullable CCApplicationGetWillEnterForegroundCallback();

SWIFT_PRIVATE
void CCApplicationSetWillEnterForegroundCallback(CCApplicationWillEnterForegroundCallback_C _Nullable callback);

CC_ASSUME_NONNULL_END

#endif
#endif /* CCApplication_C_hpp */
