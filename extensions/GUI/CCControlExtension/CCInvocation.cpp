/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Converted to c++ / cocos2d-x by Angus C
 */

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
