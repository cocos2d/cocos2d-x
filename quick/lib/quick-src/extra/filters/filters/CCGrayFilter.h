#ifndef __CCFILTER_GRAY_H__
#define __CCFILTER_GRAY_H__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== GrayFilter

class GrayFilter : public Filter
{
public:
	static GrayFilter* create();
	static GrayFilter* create(Color4F $param);
	static GrayFilter* create(float $r, float $g, float $b, float $a=0.f);

	GrayFilter();
	void setParameter(Color4F $param);
	void setParameter(float $r, float $g, float $b, float $a=0.f);

protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* $glp);
	virtual void setUniforms(GLProgram* $glp);

private:
	Color4F _param;
};

NS_CC_EXT_END

#endif //__CCFILTER_GRAY_H__