/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCPUNoise.h"

NS_CC_BEGIN

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
PUNoise3D::PUNoise3D(void) : 
    _octaves(2),
    _frequency(1.0f),
    _amplitude(1.0f),
    _persistence(1.0f)
{
}
//-----------------------------------------------------------------------
PUNoise3D::~PUNoise3D(void)
{
}
//-----------------------------------------------------------------------
void PUNoise3D::initialise(unsigned short octaves, double frequency, double amplitude, double persistence)
{
    _octaves = octaves;
    _frequency = frequency;
    _amplitude = amplitude;
    _persistence = persistence;

    for (int i = 0; i < 256; ++i)
    {
        _p[i] = permutation[i];
        _p[256+i] = permutation[i];
    }
}
//-----------------------------------------------------------------------
//void Noise3D::noise2img(unsigned short dimension)
//{
//	double x = 0.0;
//	double y = 0.0;
//	double step = 1.0 / (double)dimension;
//	size_t buffSize = 4 * dimension * dimension; // Assume Image of pixelformat 32 bits (i.e. PF_R8G8B8A8)
//	unsigned char* buff = new (std::nothrow) unsigned char[buffSize];
//	size_t p = 0;
//	while (p < buffSize)
//	{
//		unsigned char n = (unsigned char)(255 * noise(x, y, 0.5));
//		buff[p] = n;
//		buff[p+1] = n;
//		buff[p+2] = n;
//		buff[p+3] = n;
//		p += 4;
//
//		x += step;
//		if (x >= 1.0)
//		{
//			x = 0.0;
//			y += step;
//		}
//	}
//	Ogre::Image* image = new (std::nothrow) Ogre::Image();
//	image->loadDynamicImage(buff, dimension, dimension, 0, Ogre::PF_R8G8B8A8 , false, 1, 0);
//	image->save("noise2img.png");
//	delete image;
//	delete [] buff;
//}
//-----------------------------------------------------------------------
double PUNoise3D::noise(const Vec3& position)
{
    return noise(position.x, position.y, position.z);
}
//-----------------------------------------------------------------------
double PUNoise3D::noise(double x, double y, double z)
{
    double n = 0;
    double freq = _frequency;
    double ampl = _amplitude;
    for (unsigned short u = 0; u < _octaves; ++u) 
    { 
        n += genNoise(x * freq, y * freq, z * freq) * ampl;
        freq *= 2;
        ampl *= _persistence;
    }
    return n;
}
//-----------------------------------------------------------------------
double PUNoise3D::genNoise(double x, double y, double z)
{
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);
    int A = _p[X  ]+Y, AA = _p[A]+Z, AB = _p[A+1]+Z;
    int B = _p[X+1]+Y, BA = _p[B]+Z, BB = _p[B+1]+Z;

    double lrp = lerp(w,	lerp(v, lerp(u, grad(_p[AA], x, y, z),
        grad(_p[BA], x-1, y, z)),
        lerp(u, grad(_p[AB], x, y-1, z),
        grad(_p[BB], x-1, y-1, z))),
        lerp(v, lerp(u, grad(_p[AA+1], x, y  , z-1),
        grad(_p[BA+1], x-1, y, z-1)),
        lerp(u, grad(_p[AB+1], x, y-1, z-1),
        grad(_p[BB+1], x-1, y-1, z-1))));
    return fabs(lrp); // Use absolute value, because lrp in between [-1, 1]
}
//-----------------------------------------------------------------------
double PUNoise3D::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}
//-----------------------------------------------------------------------
double PUNoise3D::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}
//-----------------------------------------------------------------------
double PUNoise3D::grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = h<8 ? x : y;
    double v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

NS_CC_END
