#ifdef CHIPMUNK_FFI

// Create non static inlined copies of Chipmunk functions, useful for working with dynamic FFIs
// This file should only be included in chipmunk.c

#ifdef _MSC_VER
 #if _MSC_VER >= 1600
  #define MAKE_REF(name) decltype(name) *_##name = name
 #else
  #define MAKE_REF(name)
 #endif
#else
 #define MAKE_REF(name) __typeof__(name) *_##name = name
#endif

#define MAKE_PROPERTIES_REF(struct, property) \
	MAKE_REF(struct##Get##property); MAKE_REF(struct##Set##property)

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

MAKE_REF(cpfmax);
MAKE_REF(cpfmin);
MAKE_REF(cpfabs);
MAKE_REF(cpfclamp);
MAKE_REF(cpflerp);
MAKE_REF(cpflerpconst);

MAKE_REF(cpBBNew);
MAKE_REF(cpBBNewForCircle);
MAKE_REF(cpBBIntersects);
MAKE_REF(cpBBContainsBB);
MAKE_REF(cpBBContainsVect);
MAKE_REF(cpBBMerge);
MAKE_REF(cpBBExpand);
MAKE_REF(cpBBArea);
MAKE_REF(cpBBMergedArea);
MAKE_REF(cpBBSegmentQuery);
MAKE_REF(cpBBIntersectsSegment);

MAKE_REF(cpBodyGetMass);
MAKE_REF(cpBodyGetMoment);
MAKE_REF(cpBodyGetPos);
MAKE_REF(cpBodyGetAngle);
MAKE_REF(cpBodyGetRot);
MAKE_PROPERTIES_REF(cpBody, Vel);
MAKE_PROPERTIES_REF(cpBody, Force);
MAKE_PROPERTIES_REF(cpBody, AngVel);
MAKE_PROPERTIES_REF(cpBody, Torque);
MAKE_PROPERTIES_REF(cpBody, VelLimit);
MAKE_PROPERTIES_REF(cpBody, AngVelLimit);
MAKE_PROPERTIES_REF(cpBody, UserData);
MAKE_REF(cpBodyIsSleeping);
MAKE_REF(cpBodyIsStatic);
MAKE_REF(cpBodyIsRogue);
MAKE_REF(cpBodyLocal2World);
MAKE_REF(cpBodyWorld2Local);
MAKE_REF(cpBodyKineticEnergy);

MAKE_REF(cpShapeGetBB);
MAKE_PROPERTIES_REF(cpShape, Body);
MAKE_PROPERTIES_REF(cpShape, Sensor);
MAKE_PROPERTIES_REF(cpShape, Elasticity);
MAKE_PROPERTIES_REF(cpShape, Friction);
MAKE_PROPERTIES_REF(cpShape, SurfaceVelocity);
MAKE_PROPERTIES_REF(cpShape, UserData);
MAKE_PROPERTIES_REF(cpShape, CollisionType);
MAKE_PROPERTIES_REF(cpShape, Group);
MAKE_PROPERTIES_REF(cpShape, Layers);

MAKE_REF(cpArbiterGetShapes);
MAKE_REF(cpArbiterGetBodies);
MAKE_REF(cpArbiterIsFirstContact);
MAKE_REF(cpArbiterGetCount);

MAKE_REF(cpConstraintGetA);
MAKE_REF(cpConstraintGetB);
MAKE_PROPERTIES_REF(cpConstraint, MaxForce);
MAKE_PROPERTIES_REF(cpConstraint, ErrorBias);
MAKE_PROPERTIES_REF(cpConstraint, MaxBias);
MAKE_PROPERTIES_REF(cpConstraint, UserData);
MAKE_REF(cpConstraintGetImpulse);

MAKE_PROPERTIES_REF(cpDampedRotarySpring, RestAngle);
MAKE_PROPERTIES_REF(cpDampedRotarySpring, Stiffness);
MAKE_PROPERTIES_REF(cpDampedRotarySpring, Damping);
//MAKE_PROPERTIES_REF(cpDampedRotarySpring, SpringTorqueFunc);

MAKE_PROPERTIES_REF(cpDampedSpring, Anchr1);
MAKE_PROPERTIES_REF(cpDampedSpring, Anchr2);
MAKE_PROPERTIES_REF(cpDampedSpring, RestLength);
MAKE_PROPERTIES_REF(cpDampedSpring, Stiffness);
MAKE_PROPERTIES_REF(cpDampedSpring, Damping);
//MAKE_PROPERTIES_REF(cpDampedSpring, SpringForceFunc);

MAKE_PROPERTIES_REF(cpGearJoint, Phase);
MAKE_REF(cpGearJointGetRatio);

MAKE_PROPERTIES_REF(cpGrooveJoint, Anchr2);
MAKE_REF(cpGrooveJointGetGrooveA);
MAKE_REF(cpGrooveJointGetGrooveB);

MAKE_PROPERTIES_REF(cpPinJoint, Anchr1);
MAKE_PROPERTIES_REF(cpPinJoint, Anchr2);
MAKE_PROPERTIES_REF(cpPinJoint, Dist);

MAKE_PROPERTIES_REF(cpPivotJoint, Anchr1);
MAKE_PROPERTIES_REF(cpPivotJoint, Anchr2);

MAKE_PROPERTIES_REF(cpRatchetJoint, Angle);
MAKE_PROPERTIES_REF(cpRatchetJoint, Phase);
MAKE_PROPERTIES_REF(cpRatchetJoint, Ratchet);

MAKE_PROPERTIES_REF(cpRotaryLimitJoint, Min);
MAKE_PROPERTIES_REF(cpRotaryLimitJoint, Max);

MAKE_PROPERTIES_REF(cpSimpleMotor, Rate);

MAKE_PROPERTIES_REF(cpSlideJoint, Anchr1);
MAKE_PROPERTIES_REF(cpSlideJoint, Anchr2);
MAKE_PROPERTIES_REF(cpSlideJoint, Min);
MAKE_PROPERTIES_REF(cpSlideJoint, Max);

MAKE_REF(cpSegmentQueryHitPoint);
MAKE_REF(cpSegmentQueryHitDist);

MAKE_REF(cpSpatialIndexDestroy);
MAKE_REF(cpSpatialIndexCount);
MAKE_REF(cpSpatialIndexEach);
MAKE_REF(cpSpatialIndexContains);
MAKE_REF(cpSpatialIndexInsert);
MAKE_REF(cpSpatialIndexRemove);
MAKE_REF(cpSpatialIndexReindex);
MAKE_REF(cpSpatialIndexReindexObject);
MAKE_REF(cpSpatialIndexSegmentQuery);
MAKE_REF(cpSpatialIndexQuery);
MAKE_REF(cpSpatialIndexReindexQuery);

MAKE_PROPERTIES_REF(cpSpace, Iterations);
MAKE_PROPERTIES_REF(cpSpace, Gravity);
MAKE_PROPERTIES_REF(cpSpace, Damping);
MAKE_PROPERTIES_REF(cpSpace, IdleSpeedThreshold);
MAKE_PROPERTIES_REF(cpSpace, SleepTimeThreshold);
MAKE_PROPERTIES_REF(cpSpace, CollisionSlop);
MAKE_PROPERTIES_REF(cpSpace, CollisionBias);
MAKE_PROPERTIES_REF(cpSpace, CollisionPersistence);
MAKE_PROPERTIES_REF(cpSpace, EnableContactGraph);
MAKE_PROPERTIES_REF(cpSpace, UserData);
MAKE_REF(cpSpaceGetStaticBody);
MAKE_REF(cpSpaceGetCurrentTimeStep);
MAKE_REF(cpSpaceIsLocked);

#endif
