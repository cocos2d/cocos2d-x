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

#pragma mark - Initialization

SWIFT_PRIVATE
void* CCNodeCreate();

#pragma mark - Properties

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

SWIFT_PRIVATE
CCVector4_C CCNodeGetRotationByQuaternion(const void *object);

SWIFT_PRIVATE
void CCNodeSetRotationByQuaternion(const void *object, CCVector4_C newValue);

SWIFT_PRIVATE
float CCNodeGetRotationSkewX(const void *object);

SWIFT_PRIVATE
void CCNodeSetRotationSkewX(const void *object, float newValue);

SWIFT_PRIVATE
float CCNodeGetRotationSkewY(const void *object);

SWIFT_PRIVATE
void CCNodeSetRotationSkewY(const void *object, float newValue);

SWIFT_PRIVATE
const char* CCNodeGetName(const void *object);

SWIFT_PRIVATE
void CCNodeSetName(const void *object, const char* newValue);

SWIFT_PRIVATE
int CCNodeGetTag(const void *object);

SWIFT_PRIVATE
void CCNodeSetTag(const void *object, int newValue);

SWIFT_PRIVATE
const void * _Nullable CCNodeGetParent(const void *object);

SWIFT_PRIVATE
void CCNodeSetParent(const void *object, const void * _Nullable parent);

SWIFT_PRIVATE
bool CCNodeGetRunning(const void *object);

#pragma mark - Methods

SWIFT_PRIVATE
void CCNodeAddChild(const void *object, const void *child);

SWIFT_PRIVATE
void CCNodeAddChildWithLocalZOrder(const void *object, const void *child, int localZOrder);

SWIFT_PRIVATE
void CCNodeAddChildWithLocalZOrderAndTag(const void *object, const void *child, int localZOrder, int tag);

SWIFT_PRIVATE
void CCNodeAddChildWithLocalZOrderAndName(const void *object, const void *child, int localZOrder, const char *name);

SWIFT_PRIVATE
void CCNodeRemoveFromParent(const void *object, bool cleanup);

SWIFT_PRIVATE
void CCNodeRemoveChild(const void *object, const void *child, bool cleanup);

CC_ASSUME_NONNULL_END

#endif
#endif /* CCNode_C_h */
