//
//  CCNode_C.h
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/14/16.
//
//

#ifndef CCNode_C_h
#define CCNode_C_h
#ifndef __cplusplus
#include <stdint.h>
#include <stdbool.h>
#import <CCocos2D/CCDefines.h>
#import <CCocos2D/CCVector_C.h>

CC_ASSUME_NONNULL_BEGIN

SWIFT_PRIVATE
void* CCNodeCreate();

SWIFT_PRIVATE
const char* CCNodeGetDescription(const void *object);

SWIFT_PRIVATE
int CCNodeGetLocalZOrder(const void *object);

SWIFT_PRIVATE
void CCNodeSetLocalZOrder(const void *object, int newValue);

SWIFT_PRIVATE
int CCNodeGetGlobalZOrder(const void *object);

SWIFT_PRIVATE
void CCNodeSetGlobalZOrder(const void *object, int newValue);

SWIFT_PRIVATE
float CCNodeGetScaleX(const void *object);

SWIFT_PRIVATE
void CCNodeSetScaleX(const void *object, float newValue);

SWIFT_PRIVATE
float CCNodeGetScaleY(const void *object);

SWIFT_PRIVATE
void CCNodeSetScaleY(const void *object, float newValue);

SWIFT_PRIVATE
float CCNodeGetScaleZ(const void *object);

SWIFT_PRIVATE
void CCNodeSetScaleZ(const void *object, float newValue);

SWIFT_PRIVATE
float CCNodeGetScale(const void *object);

SWIFT_PRIVATE
void CCNodeSetScale(const void *object, float newValue);

SWIFT_PRIVATE
CCVector2_C CCNodeGetPosition(const void *object);

SWIFT_PRIVATE
void CCNodeSetPosition(const void *object, CCVector2_C newValue);

SWIFT_PRIVATE
CCVector2_C CCNodeGetNormalizedPosition(const void *object);

SWIFT_PRIVATE
void CCNodeSetNormalizedPosition(const void *object, CCVector2_C newValue);

SWIFT_PRIVATE
CCVector3_C CCNodeGetPosition3D(const void *object);

SWIFT_PRIVATE
void CCNodeSetPosition3D(const void *object, CCVector3_C newValue);

SWIFT_PRIVATE
float CCNodeGetSkewX(const void *object);

SWIFT_PRIVATE
void CCNodeSetSkewX(const void *object, float newValue);

SWIFT_PRIVATE
float CCNodeGetSkewY(const void *object);

SWIFT_PRIVATE
void CCNodeSetSkewY(const void *object, float newValue);

SWIFT_PRIVATE
CCVector2_C CCNodeGetAnchorPoint(const void *object);

SWIFT_PRIVATE
void CCNodeSetAnchorPoint(const void *object, CCVector2_C newValue);

SWIFT_PRIVATE
CCVector2_C CCNodeGetAnchorPointInPoints(const void *object);

SWIFT_PRIVATE
CCVector2_C CCNodeGetContentSize(const void *object);

SWIFT_PRIVATE
void CCNodeSetContentSize(const void *object, CCVector2_C newValue);

SWIFT_PRIVATE
bool CCNodeGetVisible(const void *object);

SWIFT_PRIVATE
void CCNodeSetVisible(const void *object, bool newValue);

SWIFT_PRIVATE
float CCNodeGetRotation(const void *object);

SWIFT_PRIVATE
void CCNodeSetRotation(const void *object, float newValue);

SWIFT_PRIVATE
CCVector3_C CCNodeGetRotation3D(const void *object);

SWIFT_PRIVATE
void CCNodeSetRotation3D(const void *object, CCVector3_C newValue);

CC_ASSUME_NONNULL_END

#endif
#endif /* CCNode_C_h */
