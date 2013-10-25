#ifndef __C3D_NOISE_H__
#define __C3D_NOISE_H__

namespace cocos3d
{

class C3DNoise
{
public:
	C3DNoise(){}
	virtual ~C3DNoise(){}
	// between -1 and 1
	virtual double generateNoise1D(double x) = 0;
	// between -1 and 1
	virtual double generateNoise2D(double x, double y) = 0;

};

class C3DPerlinNoise : public C3DNoise
{
public:
	C3DPerlinNoise(double mimValue = 0.0, double maxValue = 1.0, double frequency = 1.0, int seed = 0);
	virtual ~C3DPerlinNoise(){}
	// between -1 and 1, frequency is 1
	virtual double generateNoise1D(double x);
	// between -1 and 1, frequency is 1
	virtual double generateNoise2D(double x, double y);

protected:
	double interpolate(double x, double y, double s);

	double _frequency;
	int _seed;
	double _factorScale;
	double _factorAdd;
};

}
#endif