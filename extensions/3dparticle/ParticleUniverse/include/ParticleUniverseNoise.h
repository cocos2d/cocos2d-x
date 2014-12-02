/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode
The Noise algorithm however is based on the Improved Noise reference implementation 
by Ken Perlin (copyright by Ken Perlin (c) 2002)

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_NOISE_H__
#define __PU_NOISE_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	class _ParticleUniverseExport Noise3D
	{
		public:
			/* Constructor / Destructor */
			Noise3D(void);
			virtual ~Noise3D(void);

			/* Inititialises the noise function */
			void initialise(ushort octaves, double frequency = 1.0, double amplitude = 1.0, double persistence = 1.0);

			/* Returns a noise value between [0, 1]
			@remarks
				The noise is calculated in realtime
			*/
			double noise(double x, double y, double z);

			/* Returns a noise value between [0, 1]
			@remarks
				The noise is calculated in realtime
			*/
			double noise(const Vector3& position);

			/* Creates an image file to test the noise */
			void noise2img(ushort dimension = 255);

		protected:
			int p[512];
			ushort mOctaves;
			double mFrequency;
			double mAmplitude;
			double mPersistence;

			/* Returns a noise value between [0, 1]
			@remarks
				The noise is calculated in realtime
			*/
			double _noise(double x, double y, double z);

			double _fade(double t);
			double _lerp(double t, double a, double b);
			double _grad(int hash, double x, double y, double z);
	};
}

#endif
