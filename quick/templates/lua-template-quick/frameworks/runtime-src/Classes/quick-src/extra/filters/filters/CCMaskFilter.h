#ifndef __CCMASK_FILTER__
#define __CCMASK_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== MaskFilter

class MaskFilter : public Filter
{

public:
	static MaskFilter* create();
	static MaskFilter* create(std::string* $maskImage);
	static MaskFilter* createWithSpriteFrameName(std::string* $maskImage);

	MaskFilter();

	void setParameter(std::string* $param);
	virtual void initSprite(FilteredSprite* $sprite);
	inline void setIsSpriteFrame(bool $isSpriteFrame){ _isSpriteFrame = $isSpriteFrame; };
protected:
	void initProgram();
	std::string* _param;
	bool _isSpriteFrame;

};

NS_CC_EXT_END

#endif //__CCMASK_FILTER__