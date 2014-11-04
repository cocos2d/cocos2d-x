
#ifndef __CC_EXTENSION_CCALERTVIEW_DELEGATE_H_
#define __CC_EXTENSION_CCALERTVIEW_DELEGATE_H_

#include "cocos2dx_extra.h"

NS_CC_EXTRA_BEGIN

class AlertViewDelegate
{
public:
    virtual void alertViewClickedButtonAtIndex(int buttonIndex) = 0;
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCALERTVIEW_DELEGATE_H_
