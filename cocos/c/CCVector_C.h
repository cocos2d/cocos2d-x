//
//  CCVector_C.h
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/15/16.
//
//

#ifndef CCVector_C_h
#define CCVector_C_h
#import <CCocos2D/CCDefines.h>

struct __attribute__((swift_name("Vector2"))) CCVector2_C {
    float x;
    float y;
};
typedef struct CCVector2_C CCVector2_C;

struct __attribute__((swift_name("Vector3"))) CCVector3_C {
    float x;
    float y;
    float z;
};
typedef struct CCVector3_C CCVector3_C;

#endif /* CCVector_C */
