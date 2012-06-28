 /*
 *
 * Helper class to store targets and selectors (and eventually, params?) in the same CCMutableArray. Basically a very crude form of a NSInvocation
 */
#ifndef __CCINVOCATION_H__
#define __CCINVOCATION_H__

#include "cocoa/CCObject.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

typedef unsigned int CCControlEvent;

typedef void (CCObject::*SEL_CCControlHandler)(CCObject*, CCControlEvent);

#define cccontrol_selector(_SELECTOR) (SEL_CCControlHandler)(&_SELECTOR)

class CC_DLL CCInvocation : public CCObject
{
    CC_SYNTHESIZE_READONLY(SEL_CCControlHandler, m_action, Action);
    CC_SYNTHESIZE_READONLY(CCObject*, m_target, Target);
    CC_SYNTHESIZE_READONLY(CCControlEvent, m_controlEvent, ControlEvent);
    
public:
    CCInvocation(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent);

    void invoke(CCObject* sender);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif