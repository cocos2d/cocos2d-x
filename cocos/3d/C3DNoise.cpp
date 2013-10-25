#include "C3DNoise.h"
#include <math.h>
namespace cocos3d
{


static inline double noise1d(int x)
{
	x = (x << 13) ^ x;
	int t = (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff;
	return 1.0 - double(t) * 0.931322574615478515625e-9;/// 1073741824.0);
}

static inline double noise2d(int x, int y)
{
	int n = x + y * 57;
	return noise1d(n);
}


C3DPerlinNoise::C3DPerlinNoise(double minValue, double maxValue, double frequency, int seed) 
	: _seed(seed), _factorScale((maxValue - minValue) * 0.5), _factorAdd((maxValue + minValue) * 0.5), _frequency(frequency)
{

}

double C3DPerlinNoise::generateNoise1D(double x)
{
	x *= _frequency;
	int ix = (int)x;
	double s = x - ix;
	ix += _seed;
	double r1 = noise1d(ix);
	double r2 = noise1d(ix + 1);
	return interpolate(r1, r2, s) * _factorScale + _factorAdd;
}

double C3DPerlinNoise::generateNoise2D(double x, double y)
{
	x *= _frequency;
	y *= _frequency;
	int ix = (int)x;
	int iy = (int)y;
	double sx = x - ix;
	double sy = y - iy;
	ix += _seed;
	iy += _seed;

	double r00 = noise2d(ix, iy);
	double r10 = noise2d(ix + 1, iy);
	double r01 = noise2d(ix, iy + 1);
	double r11 = noise2d(ix + 1, iy + 1);

	double r0 = interpolate(r00, r10, sx);
	double r1 = interpolate(r01, r11, sx);
	return interpolate(r0, r1, sy) * _factorScale + _factorAdd;
}

double C3DPerlinNoise::interpolate(double x, double y, double s)
{
	double ft = s * 3.1415927;
	double f =(1.0 - cos(ft))* 0.5;
	return x *(1.0 - f) + y * f;
}

}