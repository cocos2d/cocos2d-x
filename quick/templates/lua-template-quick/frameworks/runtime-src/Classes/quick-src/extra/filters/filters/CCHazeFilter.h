
#ifndef __CCHAZE_FILTER__
#define __CCHAZE_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== HazeFilter

class HazeFilter : public Filter
{

public:
	static HazeFilter* create();
	static HazeFilter* create(float $hazeDistance, float $slope);

	HazeFilter();

	void setParameter(float $hazeDistance, float $slope);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);
	float _hazeDistance;
	float _slope;
};

NS_CC_EXT_END

#endif //__CCHAZE_FILTER__
