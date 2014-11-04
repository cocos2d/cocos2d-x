#ifndef __CCBLUR_FILTER__
#define __CCBLUR_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCBlurFilter

class BlurBaseFilter : public SingleFloatParamFilter
{

public:
	BlurBaseFilter();
	virtual void setParameter(float $param);
protected:
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
	float _param;
};

class HBlurFilter : public BlurBaseFilter
{
public:
	static HBlurFilter* create();
	static HBlurFilter* create(float $param);

	HBlurFilter();
protected:
	virtual GLProgram* loadShader();

};

class VBlurFilter : public BlurBaseFilter
{
public:
	static VBlurFilter* create();
	static VBlurFilter* create(float $param);

	VBlurFilter();
protected:
	virtual GLProgram* loadShader();
};

class GaussianHBlurFilter : public BlurBaseFilter
{
public:
	static GaussianHBlurFilter* create();
	static GaussianHBlurFilter* create(float $param);

	GaussianHBlurFilter();
	virtual void initSprite(FilteredSprite* $sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setUniforms(GLProgram* $glp);
private:
	float _resolation;
};

class GaussianVBlurFilter : public BlurBaseFilter
{
public:
	static GaussianVBlurFilter* create();
	static GaussianVBlurFilter* create(float $param);

	GaussianVBlurFilter();
	virtual void initSprite(FilteredSprite* $sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setUniforms(GLProgram* $glp);
private:
	float _resolation;
};

//================== ZoomBlurFilter

class ZoomBlurFilter : public Filter
{

public:
	static ZoomBlurFilter* create();
	static ZoomBlurFilter* create(float $blurSize, float $centerX, float $centerY);

	ZoomBlurFilter();

	void setParameter(float $blurSize, float $centerX, float $centerY);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
	float _blurSize;
	float _centerX;
	float _centerY;
};

//================== MotionBlurFilter

class MotionBlurFilter : public Filter
{

public:
	static MotionBlurFilter* create();
	static MotionBlurFilter* create(float $blurSize, float $blurAngle);

	MotionBlurFilter();

	void setParameter(float $blurSize, float $blurAngle);
	virtual void initSprite(FilteredSprite* $sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
	float _blurSize;
	float _blurAngle;
	float _texelOffsetX;
	float _texelOffsetY;
};

NS_CC_EXT_END
#endif //__CCBLUR_FILTER__