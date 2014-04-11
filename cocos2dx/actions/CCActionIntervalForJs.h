//
// Created by bruce xiao on 8/21/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __CCACTIONINTERVALFORJS_H_
#define __CCACTIONINTERVALFORJS_H_


#include "cocos2d.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

class CCActionIntervalForJs : public CCActionInterval {
public:
    CCActionIntervalForJs();
    virtual ~CCActionIntervalForJs();
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    virtual void update(float time);
    virtual void stop();

protected:
    bool m_bIsStartWithTarget;
    ccScriptType m_eScriptType;
};

NS_CC_END

#endif //__MooActionInterval_H_
