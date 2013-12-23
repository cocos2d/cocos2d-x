#ifndef C3DMath_H_
#define C3DMath_H_

#include <math.h>

#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DQuaternion.h"
#include "C3DMatrix.h"
#include "C3DMathUtilty.h"


#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_EPSILON                0.000001f

#endif
