/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSX_MATH_H__
#define __PU_PHYSX_MATH_H__

#include "ParticleUniversePrerequisites.h"
#ifdef PU_PHYSICS_PHYSX

	#include "NxVec3.h"
	#include "NxQuat.h"
	#include "Nxp.h"

	namespace ParticleUniverse
	{
		/** 
		*/
		class _ParticleUniverseExport PhysXMath
		{
			public:
				PhysXMath(void) {};
				virtual ~PhysXMath(void) {};

				// Converters
				static inline Vector3 convert(const NxVec3& nxVec3){ return Vector3(nxVec3.x, nxVec3.y, nxVec3.z); }
				static inline NxVec3 convert(const Vector3& vector3){ return NxVec3(vector3.x, vector3.y, vector3.z); }
				static inline Quaternion convert(const NxQuat& q) {return Quaternion(q.w, q.x, q.y, q.z); }
				static inline NxQuat convert(Quaternion& q, bool _normalise = true)
				{
					if (_normalise)
						q.normalise();
		
					NxQuat a;
					a.x = q.x;
					a.y = q.y;
					a.z = q.z;
					a.w = q.w;
					return a;
				}
				static inline GroupsMask convert(const NxGroupsMask& nxGroupsMask)
				{
					GroupsMask groupsMask;
					groupsMask.bits0 = nxGroupsMask.bits0;
					groupsMask.bits1 = nxGroupsMask.bits1;
					groupsMask.bits2 = nxGroupsMask.bits2;
					groupsMask.bits3 = nxGroupsMask.bits3;
					return groupsMask;
				}
				static inline NxGroupsMask convert(const GroupsMask& groupsMask)
				{
					NxGroupsMask nxGroupsMask;
					nxGroupsMask.bits0 = groupsMask.bits0;
					nxGroupsMask.bits1 = groupsMask.bits1;
					nxGroupsMask.bits2 = groupsMask.bits2;
					nxGroupsMask.bits3 = groupsMask.bits3;
					return nxGroupsMask;
				}
		};
	}
#endif //PU_PHYSICS_PHYSX
#endif