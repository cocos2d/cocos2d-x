#ifndef __CCCONTRAST_FILTER__
#define __CCCONTRAST_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== ContrastFilter

class ContrastFilter : public SingleFloatParamFilter
{

public:
	static ContrastFilter* create();
	static ContrastFilter* create(float $param);

	ContrastFilter();

	virtual void setParameter(float $param);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCCONTRAST_FILTER__