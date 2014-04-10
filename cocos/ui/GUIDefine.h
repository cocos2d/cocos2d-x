/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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

#ifndef __TestCpp__GUIDefine__
#define __TestCpp__GUIDefine__

#include "cocos2d.h"
#include "../../extensions/ExtensionMacros.h"
#include <string>
#include "cocostudio/ObjectFactory.h"

//
//// Widget macro
//

#define DECLARE_CLASS_GUI_INFO \
    public: \
    static cocostudio::ObjectFactory::TInfo Type; \
    static cocos2d::Ref* createInstance(void); \

#define IMPLEMENT_CLASS_GUI_INFO(className) \
    cocos2d::Ref* className::createInstance(void) \
    { \
        return className::create(); \
    } \
    cocostudio::ObjectFactory::TInfo className::Type(#className, &className::createInstance); \

#define CREATE_CLASS_GUI_INFO(className) \
    cocostudio::ObjectFactory::TInfo(#className, &className::createInstance) \


//
//// Reader macro
//

#define DECLARE_CLASS_WIDGET_READER_INFO \
    public: \
    static cocostudio::ObjectFactory::TInfo Type; \
    static cocos2d::Ref* createInstance(void); \

#define IMPLEMENT_CLASS_WIDGET_READER_INFO(className) \
    cocos2d::Ref* className::createInstance(void) \
    { \
        return className::getInstance(); \
    } \
    cocostudio::ObjectFactory::TInfo className::Type(#className, &className::createInstance); \

#define CREATE_CLASS_WIDGET_READER_INFO(className) \
    cocostudio::ObjectFactory::TInfo(#className, &className::createInstance) \


#endif /* defined(__TestCpp__GUIDefine__) */
