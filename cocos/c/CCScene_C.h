//
//  CCScene_C.hpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/16/16.
//
//

#ifndef CCScene_C_h
#define CCScene_C_h
#ifndef __cplusplus
#include <stdint.h>
#include <stdbool.h>
#import <CCocos2D/CCDefines.h>
#import <CCocos2D/CCVector_C.h>

CC_ASSUME_NONNULL_BEGIN

#pragma mark - Initialization

SWIFT_PRIVATE
void* CCSpriteCreate();

SWIFT_PRIVATE
void* _Nullable CCSpriteCreateWithFilename(const char *filename);

CC_ASSUME_NONNULL_END

#endif
#endif /* CCScene_C_h */
