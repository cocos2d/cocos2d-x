#include <stdint.h>

#ifdef __APPLE__
   #include "TargetConditionals.h"
#endif

#if (TARGET_OS_IPHONE == 1) || (TARGET_OS_MAC == 1) && (!defined CP_USE_CGPOINTS)
	#define CP_USE_CGPOINTS 1
#endif

#if CP_USE_CGPOINTS == 1
	#if TARGET_OS_IPHONE
		#import <CoreGraphics/CGGeometry.h>
	#elif TARGET_OS_MAC
		#include <ApplicationServices/ApplicationServices.h>
	#endif
	
	#if defined(__LP64__) && __LP64__
		#define CP_USE_DOUBLES 1
	#else
		#define CP_USE_DOUBLES 0
	#endif
#endif

#ifndef CP_USE_DOUBLES
	// use doubles by default for higher precision
	#define CP_USE_DOUBLES 1
#endif

/// @defgroup basicTypes Basic Types
/// Most of these types can be configured at compile time.
/// @{

#if CP_USE_DOUBLES
/// Chipmunk's floating point type.
/// Can be reconfigured at compile time.
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

#ifndef INFINITY
	#ifdef _MSC_VER
		union MSVC_EVIL_FLOAT_HACK
		{
			unsigned __int8 Bytes[4];
			float Value;
		};
		static union MSVC_EVIL_FLOAT_HACK INFINITY_HACK = {{0x00, 0x00, 0x80, 0x7F}};
		#define INFINITY (INFINITY_HACK.Value)
	#endif
	
	#ifdef __GNUC__
		#define INFINITY (__builtin_inf())
	#endif
	
	#ifndef INFINITY
		#define INFINITY (1e1000)
	#endif
#endif

#ifndef M_PI
	#define M_PI 3.14159265358979323846264338327950288
#endif

#ifndef M_E
	#define M_E 2.71828182845904523536028747135266250
#endif


/// Return the max of two cpFloats.
static inline cpFloat cpfmax(cpFloat a, cpFloat b)
{
	return (a > b) ? a : b;
}

/// Return the min of two cpFloats.
static inline cpFloat cpfmin(cpFloat a, cpFloat b)
{
	return (a < b) ? a : b;
}

/// Return the absolute value of a cpFloat.
static inline cpFloat cpfabs(cpFloat f)
{
	return (f < 0) ? -f : f;
}

/// Clamp @c f to be between @c min and @c max.
static inline cpFloat cpfclamp(cpFloat f, cpFloat min, cpFloat max)
{
	return cpfmin(cpfmax(f, min), max);
}

/// Clamp @c f to be between 0 and 1.
static inline cpFloat cpfclamp01(cpFloat f)
{
	return cpfmax(0.0f, cpfmin(f, 1.0f));
}



/// Linearly interpolate (or extrapolate) between @c f1 and @c f2 by @c t percent.
static inline cpFloat cpflerp(cpFloat f1, cpFloat f2, cpFloat t)
{
	return f1*(1.0f - t) + f2*t;
}

/// Linearly interpolate from @c f1 to @c f2 by no more than @c d.
static inline cpFloat cpflerpconst(cpFloat f1, cpFloat f2, cpFloat d)
{
	return f1 + cpfclamp(f2 - f1, -d, d);
}

/// Hash value type.
typedef uintptr_t cpHashValue;

// Oh C, how we love to define our own boolean types to get compiler compatibility
/// Chipmunk's boolean type.
#ifdef CP_BOOL_TYPE
	typedef CP_BOOL_TYPE cpBool;
#else
	typedef int cpBool;
#endif

#ifndef cpTrue
/// true value.
	#define cpTrue 1
#endif

#ifndef cpFalse
/// false value.
	#define cpFalse 0
#endif

#ifdef CP_DATA_POINTER_TYPE
	typedef CP_DATA_POINTER_TYPE cpDataPointer;
#else
/// Type used for user data pointers.
	typedef void * cpDataPointer;
#endif

#ifdef CP_COLLISION_TYPE_TYPE
	typedef CP_COLLISION_TYPE_TYPE cpCollisionType;
#else
/// Type used for cpSpace.collision_type.
	typedef uintptr_t cpCollisionType;
#endif

#ifdef CP_GROUP_TYPE
	typedef CP_GROUP_TYPE cpGroup;
#else
/// Type used for cpShape.group.
	typedef uintptr_t cpGroup;
#endif

#ifdef CP_LAYERS_TYPE
	typedef CP_LAYERS_TYPE cpLayers;
#else
/// Type used for cpShape.layers.
	typedef unsigned int cpLayers;
#endif

#ifdef CP_TIMESTAMP_TYPE
	typedef CP_TIMESTAMP_TYPE cpTimestamp;
#else
/// Type used for various timestamps in Chipmunk.
	typedef unsigned int cpTimestamp;
#endif

#ifndef CP_NO_GROUP
/// Value for cpShape.group signifying that a shape is in no group.
	#define CP_NO_GROUP ((cpGroup)0)
#endif

#ifndef CP_ALL_LAYERS
/// Value for cpShape.layers signifying that a shape is in every layer.
	#define CP_ALL_LAYERS (~(cpLayers)0)
#endif
/// @}

// CGPoints are structurally the same, and allow
// easy interoperability with other Cocoa libraries
#if CP_USE_CGPOINTS
	typedef CGPoint cpVect;
#else
/// Chipmunk's 2D vector type.
/// @addtogroup cpVect
	typedef struct cpVect{cpFloat x,y;} cpVect;
#endif

typedef struct cpMat2x2 {
	// Row major [[a, b][c d]]
	cpFloat a, b, c, d;
} cpMat2x2;
