
#ifndef __CCSEPIA_FILTER__
#define __CCSEPIA_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== SepiaFilter

class SepiaFilter : public Filter
{

public:
	static SepiaFilter* create();
	static SepiaFilter* create(float $resolation);

	SepiaFilter();

	void setParameter();
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCSEPIA_FILTER__
