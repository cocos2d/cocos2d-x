// Create non static inlined copies of Chipmunk functions, useful for working with dynamic FFIs
// This file should only be included in chipmunk.c

#ifndef _CHIPMUNK_FFI_H_
#define _CHIPMUNK_FFI_H_

#ifdef _MSC_VER
 #if _MSC_VER >= 1600
  #define MAKE_REF(name) decltype(name) *_##name = name
 #else
  #define MAKE_REF(name)
 #endif
#else
 #define MAKE_REF(name) __typeof__(name) *_##name = name
#endif

MAKE_REF(cpv); // makes a variable named _cpv that contains the function pointer for cpv()
MAKE_REF(cpveql);
MAKE_REF(cpvadd);
MAKE_REF(cpvneg);
MAKE_REF(cpvsub);
MAKE_REF(cpvmult);
MAKE_REF(cpvdot);
MAKE_REF(cpvcross);
MAKE_REF(cpvperp);
MAKE_REF(cpvrperp);
MAKE_REF(cpvproject);
MAKE_REF(cpvrotate);
MAKE_REF(cpvunrotate);
MAKE_REF(cpvlengthsq);
MAKE_REF(cpvlerp);
MAKE_REF(cpvnormalize);
MAKE_REF(cpvnormalize_safe);
MAKE_REF(cpvclamp);
MAKE_REF(cpvlerpconst);
MAKE_REF(cpvdist);
MAKE_REF(cpvdistsq);
MAKE_REF(cpvnear);

MAKE_REF(cpBBNew);
MAKE_REF(cpBBintersects);
MAKE_REF(cpBBcontainsBB);
MAKE_REF(cpBBcontainsVect);
MAKE_REF(cpBBmerge);
MAKE_REF(cpBBexpand);

MAKE_REF(cpBodyWorld2Local);
MAKE_REF(cpBodyLocal2World);
MAKE_REF(cpBodyApplyImpulse);
MAKE_REF(cpBodyIsSleeping);
MAKE_REF(cpBodyIsRogue);
MAKE_REF(cpBodyKineticEnergy);

MAKE_REF(cpArbiterIsFirstContact);
MAKE_REF(cpArbiterGetShapes);
MAKE_REF(cpArbiterGetNormal);
MAKE_REF(cpArbiterGetPoint);

MAKE_REF(cpConstraintGetImpulse);

MAKE_REF(cpSegmentQueryHitPoint);
MAKE_REF(cpSegmentQueryHitDist);

#endif // _CHIPMUNK_FFI_H_