#ifndef __CCSATURATION_FILTER__
#define __CCSATURATION_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== SaturationFilter

class SaturationFilter : public SingleFloatParamFilter
{

public:
	static SaturationFilter* create();
	static SaturationFilter* create(float $param);

	SaturationFilter();

	virtual void setParameter(float $param);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
};


NS_CC_EXT_END

#endif //__CCSATURATION_FILTER__
