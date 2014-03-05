#ifndef RAY3_H
#define RAY3_H

#include "utility.h"
#include "vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kmRay3 {
    kmVec3 start;
    kmVec3 dir;
} kmRay3;

struct kmPlane;

CC_DLL kmRay3* kmRay3Fill(kmRay3* ray, kmScalar px, kmScalar py, kmScalar pz, kmScalar vx, kmScalar vy, kmScalar vz);
CC_DLL kmRay3* kmRay3FromPointAndDirection(kmRay3* ray, const kmVec3* point, const kmVec3* direction);
CC_DLL kmBool kmRay3IntersectPlane(kmVec3* pOut, const kmRay3* ray, const struct kmPlane* plane);

#ifdef __cplusplus
}
#endif

#endif // RAY3_H
