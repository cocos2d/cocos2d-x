#include "CCInvocation.h"

NS_CC_EXT_BEGIN

CCInvocation* CCInvocation::create(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent)
{
    CCInvocation* pRet = new CCInvocation(target, action, controlEvent);
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

CCInvocation::CCInvocation(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent)
{
    m_target=target;
    m_action=action;
    m_controlEvent=controlEvent;
}

void CCInvocation::invoke(CCObject* sender)
{
    if (m_target && m_action)
    {
        (m_target->*m_action)(sender, m_controlEvent);
    }                
}

NS_CC_EXT_END
