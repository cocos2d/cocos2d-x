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

void* CCNodeCreate()

const char* CCNodeGetDescription(const void *object);

int CCNodeGetLocalZOrder(const void *object);

void CCNodeSetLocalZOrder(const void *object, int newValue);

int CCNodeGetGlobalZOrder(const void *object);

void CCNodeSetGlobalZOrder(const void *object, int newValue);

float CCNodeGetScaleX(const void *object);

void CCNodeSetScaleX(const void *object, float newValue);

float CCNodeGetScaleY(const void *object);

void CCNodeSetScaleY(const void *object, float newValue);

float CCNodeGetScaleZ(const void *object);

void CCNodeSetScaleZ(const void *object, float newValue);

float CCNodeGetScale(const void *object);

void CCNodeSetScale(const void *object, float newValue);

#endif

#endif /* CCNode_C_h */
