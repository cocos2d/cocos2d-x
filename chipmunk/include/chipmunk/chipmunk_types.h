#ifndef _CHIPMUNK_TYPES_H_
#define _CHIPMUNK_TYPES_H_

#ifdef __APPLE__
#ifndef AIRPLAYUSECHIPMUNK
	#import "TargetConditionals.h"
#endif
#endif

// Use single precision floats on the iPhone.
#if TARGET_OS_IPHONE==1
	#define CP_USE_DOUBLES 0
#else
	// use doubles by default for higher precision
	#define CP_USE_DOUBLES 1
#endif

#if CP_USE_DOUBLES
	typedef double cpFloat;
	#define cpfsqrt sqrt
	#define cpfsin sin
	#define cpfcos cos
	#define cpfacos acos
	#define cpfatan2 atan2
	#define cpfmod fmod
	#define cpfexp exp
	#define cpfpow pow
	#define cpffloor floor
	#define cpfceil ceil
#else
	typedef float cpFloat;
	#define cpfsqrt sqrtf
	#define cpfsin sinf
	#define cpfcos cosf
	#define cpfacos acosf
	#define cpfatan2 atan2f
	#define cpfmod fmodf
	#define cpfexp expf
	#define cpfpow powf
	#define cpffloor floorf
	#define cpfceil ceilf
#endif

//#if TARGET_OS_IPHONE
	// CCPoints are structurally the same, and allow
	// easy interoperability with other iPhone libraries
	//#import <CoreGraphics/CCGeometry.h>
	//typedef CCPoint cpVect;
//#else
	typedef struct cpVect{cpFloat x,y;} cpVect;
//#endif

typedef unsigned int cpHashValue;

#ifdef CP_DATA_POINTER_TYPE
	typedef CP_DATA_POINTER_TYPE cpDataPointer;
#else
	typedef void * cpDataPointer;
#endif

#ifdef CP_COLLISION_TYPE_TYPE
	typedef CP_COLLISION_TYPE_TYPE cpCollisionType;
#else
	typedef unsigned int cpCollisionType;
#endif

#ifdef CP_GROUP_TYPE
	typedef CP_GROUP_TYPE cpGroup;
#else
	typedef unsigned int cpGroup;
#endif

#ifdef CP_LAYERS_TYPE
	typedef CP_GROUP_TYPE cpLayers;
#else
	typedef unsigned int cpLayers;
#endif

#ifndef CP_NO_GROUP
	#define CP_NO_GROUP ((cpGroup)0)
#endif

#ifndef CP_ALL_LAYERS
	#define CP_ALL_LAYERS (~(cpLayers)0)
#endif

#endif // _CHIPMUNK_TYPES_H_