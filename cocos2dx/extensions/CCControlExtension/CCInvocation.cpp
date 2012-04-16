#include "CCInvocation.h"

CCInvocation::CCInvocation(CCObject* target, SEL_MenuHandler action, CCControlEvent controlEvent)
{
	m_target=target;
	m_action=action;
	m_controlEvent=controlEvent;
}

void CCInvocation::invoke(CCObject* sender)
{
	if (m_target && m_action)
	{
		(m_target->*m_action)(sender);
	}				
}