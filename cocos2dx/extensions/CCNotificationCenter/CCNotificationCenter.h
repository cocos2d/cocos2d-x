/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2011      Erawppa
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCNOTIFICATIONCENTER_H__
#define __CCNOTIFICATIONCENTER_H__

#include "cocoa/CCObject.h"


namespace cocos2d { class CCArray; }

NS_CC_EXT_BEGIN

class CC_DLL CCNotificationCenter : public CCObject
{
public:
    CCNotificationCenter();
    ~CCNotificationCenter();
    
    static CCNotificationCenter *sharedNotificationCenter(void);
    static void purgeNotificationCenter(void);

    void addObserver(CCObject *target, 
                     SEL_CallFuncO selector,
                     const char *name,
                     CCObject *obj);
    
    void removeObserver(CCObject *target,const char *name);
    
    void postNotification(const char *name);
    void postNotification(const char *name, CCObject *object);
    
private:
    //
    // internal functions
    //
    bool observerExisted(CCObject *target,const char *name);
    
    //
    // variables
    //
    cocos2d::CCArray *m_observers;
};

class CC_DLL CCNotificationObserver : public CCObject
{
public:
    CCNotificationObserver(CCObject *target, 
                           SEL_CallFuncO selector,
                           const char *name,
                           CCObject *obj);
    ~CCNotificationObserver();      
    
    void performSelector(CCObject *obj);
private:
    CC_PROPERTY_READONLY(CCObject *, m_target, Target);
    CC_PROPERTY_READONLY(SEL_CallFuncO, m_selector, Selector);
    CC_PROPERTY_READONLY(char *, m_name, Name);
    CC_PROPERTY_READONLY(CCObject *, m_object, Object);
};

NS_CC_EXT_END

#endif//__CCNOTIFICATIONCENTER_H__