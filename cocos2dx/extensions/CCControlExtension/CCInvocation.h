 /*
 *
 * Helper class to store targets and selectors (and eventually, params?) in the same CCMutableArray. Basically a very crude form of a NSInvocation
 */
#ifndef __CCINVOCATION_H__
#define __CCINVOCATION_H__

#include "cocos2d.h"
#include "CCControl.h"


USING_NS_CC;

typedef unsigned int CCControlEvent;

class CCInvocation : public CCObject
{
	CC_SYNTHESIZE_READONLY(SEL_MenuHandler, m_action, Action);
	CC_SYNTHESIZE_READONLY(CCObject*, m_target, Target);
	CC_SYNTHESIZE_READONLY(CCControlEvent, m_controlEvent, ControlEvent);
	
public:
	CCInvocation(CCObject* target, SEL_MenuHandler action, CCControlEvent controlEvent);

	void invoke(CCObject* sender);
};

#endif