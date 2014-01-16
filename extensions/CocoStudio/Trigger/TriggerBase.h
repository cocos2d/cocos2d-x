/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __TRIGGEREVENT_H__
#define __TRIGGEREVENT_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"
#include "ObjectFactory.h"
#include "TriggerObj.h"
#include "TriggerMng.h"

NS_CC_EXT_BEGIN

#define DECLARE_CLASS_INFO \
    public: \
        static cocos2d::extension::ObjectFactory::TInfo Type; \
        static cocos2d::CCObject* createInstance(void); \
        
#define IMPLEMENT_CLASS_INFO(className) \
        cocos2d::CCObject* className::createInstance(void) \
        { \
            return new className; \
        } \
        cocos2d::extension::ObjectFactory::TInfo className::Type(#className, &className::createInstance); \


void sendEvent(unsigned int event);

NS_CC_EXT_END

#endif
