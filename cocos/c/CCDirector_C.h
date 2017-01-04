//
//  CCDirector_C.hpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/16/16.
//
//

#ifndef CCDirector_C_h
#define CCDirector_C_h
#ifndef __cplusplus
#include <stdint.h>
#include <stdbool.h>
#import <CCocos2D/CCDefines.h>

CC_ASSUME_NONNULL_BEGIN

#pragma mark - Properties

SWIFT_PRIVATE
double CCDirectorGetAnimationInterval();

SWIFT_PRIVATE
void*CCDirectorSetAnimationInterval(double newValue);

SWIFT_PRIVATE
bool CCDirectorGetDisplayAnimationInterval();

SWIFT_PRIVATE
void CCDirectorSetDisplayAnimationInterval(bool newValue);

SWIFT_PRIVATE
float CCDirectorGetSecondsPerFrame();

CC_ASSUME_NONNULL_END

#endif
#endif /* CCDirector_C_h */
