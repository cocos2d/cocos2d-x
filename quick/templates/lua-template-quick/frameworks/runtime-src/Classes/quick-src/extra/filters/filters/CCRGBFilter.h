
#ifndef __CCRGB_FILTER__
#define __CCRGB_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== RGBFilter

class RGBFilter : public Filter
{

public:
	static RGBFilter* create();
	static RGBFilter* create(float $redAdj, float $greenAdj, float $blueAdj);

	RGBFilter();

	void setParameter(float $redAdj, float $greenAdj, float $blueAdj);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
	float _redAdj;
	float _greenAdj;
	float _blueAdj;
};


NS_CC_EXT_END

#endif //__CCRGB_FILTER__