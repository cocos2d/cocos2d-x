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
#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleUniverseNoise.h"

namespace ParticleUniverse
{
	static int permutation[] = { 151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};

	//-----------------------------------------------------------------------
	Noise3D::Noise3D(void) : 
		mOctaves(2),
		mFrequency(1.0f),
		mAmplitude(1.0f),
		mPersistence(1.0f)
	{
	}
	//-----------------------------------------------------------------------
	Noise3D::~Noise3D(void)
	{
	}
	//-----------------------------------------------------------------------
	void Noise3D::initialise(ushort octaves, double frequency, double amplitude, double persistence)
	{
		mOctaves = octaves;
		mFrequency = frequency;
		mAmplitude = amplitude;
		mPersistence = persistence;

		for (int i = 0; i < 256; ++i)
		{
			p[i] = permutation[i];
			p[256+i] = permutation[i];
		}
	}
	//-----------------------------------------------------------------------
	void Noise3D::noise2img(ushort dimension)
	{
		double x = 0.0;
		double y = 0.0;
		double step = 1.0 / (double)dimension;
		size_t buffSize = 4 * dimension * dimension; // Assume Image of pixelformat 32 bits (i.e. PF_R8G8B8A8)
		uchar* buff = new uchar[buffSize];
		size_t p = 0;
		while (p < buffSize)
		{
			uchar n = (uchar)(255 * noise(x, y, 0.5));
			buff[p] = n;
			buff[p+1] = n;
			buff[p+2] = n;
			buff[p+3] = n;
			p += 4;

			x += step;
			if (x >= 1.0)
			{
				x = 0.0;
				y += step;
			}
		}
		Ogre::Image* image = new Ogre::Image();
		image->loadDynamicImage(buff, dimension, dimension, 0, Ogre::PF_R8G8B8A8 , false, 1, 0);
		image->save("noise2img.png");
		delete image;
		delete [] buff;
	}
	//-----------------------------------------------------------------------
	double Noise3D::noise(const Vector3& position)
	{
		return noise(position.x, position.y, position.z);
	}
	//-----------------------------------------------------------------------
	double Noise3D::noise(double x, double y, double z)
	{
		double n = 0;
		double freq = mFrequency;
		double ampl = mAmplitude;
		for (ushort u = 0; u < mOctaves; ++u) 
		{ 
			n += _noise(x * freq, y * freq, z * freq) * ampl;
			freq *= 2;
			ampl *= mPersistence;
		}
		return n;
	}
	//-----------------------------------------------------------------------
	double Noise3D::_noise(double x, double y, double z)
	{
		int X = (int)floor(x) & 255;
		int Y = (int)floor(y) & 255;
		int Z = (int)floor(z) & 255;
		x -= floor(x);
		y -= floor(y);
		z -= floor(z);
		double u = _fade(x);
		double v = _fade(y);
		double w = _fade(z);
		int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z;
		int B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;

		double lrp = _lerp(w,	_lerp(v, _lerp(u, _grad(p[AA], x, y, z),
									_grad(p[BA], x-1, y, z)),
								_lerp(u, _grad(p[AB], x, y-1, z),
									_grad(p[BB], x-1, y-1, z))),
								_lerp(v, _lerp(u, _grad(p[AA+1], x, y  , z-1),
									_grad(p[BA+1], x-1, y, z-1)),
								_lerp(u, _grad(p[AB+1], x, y-1, z-1),
									_grad(p[BB+1], x-1, y-1, z-1))));
		return Math::Abs((Real)lrp); // Use absolute value, because lrp in between [-1, 1]
	}
	//-----------------------------------------------------------------------
	double Noise3D::_fade(double t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}
	//-----------------------------------------------------------------------
	double Noise3D::_lerp(double t, double a, double b)
	{
		return a + t * (b - a);
	}
	//-----------------------------------------------------------------------
	double Noise3D::_grad(int hash, double x, double y, double z)
	{
		int h = hash & 15;
		double u = h<8 ? x : y;
		double v = h<4 ? y : h==12||h==14 ? x : z;
		return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
	}
}