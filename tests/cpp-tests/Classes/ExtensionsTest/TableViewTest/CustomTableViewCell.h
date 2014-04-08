#ifndef __CUSTOMTABELVIEWCELL_H__
#define __CUSTOMTABELVIEWCELL_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_MATH;

class CustomTableViewCell : public cocos2d::extension::TableViewCell
{
public:
	virtual void draw(cocos2d::Renderer *renderer, const Matrix &transform, bool transformUpdated) override;
};

#endif /* __CUSTOMTABELVIEWCELL_H__ */

