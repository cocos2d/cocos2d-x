#ifndef __CCSHARPEN_FILTER__
#define __CCSHARPEN_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== SharpenFilter

class SharpenFilter : public Filter
{

public:
	static SharpenFilter* create();
	static SharpenFilter* create(float $sharpness, float $widthFactor, float $heightFactor);
	static SharpenFilter* create(float $sharpness, int $amount);

	SharpenFilter();

	void setParameter(float $sharpness, float $widthFactor, float $heightFactor);
	void setParameter(float $sharpness, int $amount);
	virtual void initSprite(FilteredSprite* $sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
	float _sharpness;
	float _widthFactor;
	float _heightFactor;
	int _amount;

};

NS_CC_EXT_END

#endif //__CCSHARPEN_FILTER__