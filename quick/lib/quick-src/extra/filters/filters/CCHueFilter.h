
#ifndef __CCHUE_FILTER__
#define __CCHUE_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== HueFilter

class HueFilter : public SingleFloatParamFilter
{

public:
	static HueFilter* create();
	static HueFilter* create(float $param);

	HueFilter();

	void setParameter(float $param);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCHUE_FILTER__
