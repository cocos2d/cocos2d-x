/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 
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

#ifndef _CC_CUSTOM_CLASS_H_
#define _CC_CUSTOM_CLASS_H_

#include "cocos2d.h"
#include <map>

NS_CC_EXT_BEGIN
    
class CCBCustomClass;
typedef CCBCustomClass* (*FUNC_CUSTON_CLASS_CREATOR)(void);
typedef std::map<std::string, FUNC_CUSTON_CLASS_CREATOR> CUSTOM_CLASS_MAP;

// This is a simple reflection implement for custom classes in CocosBuilder
class CCBCustomClass : public cocos2d::CCNode
{
public:    
    static CCBCustomClass* createInstance() { return NULL; }; // cannot create virual class here
    
    CCBCustomClass() {};
    virtual ~CCBCustomClass() {};
    
    // implement 3 pure virtual methods inherited from CCBCustomClass
    virtual bool callbackSetChildren(const char* name, cocos2d::CCObject* node) = 0;
    virtual void callbackInvokeMethods(cocos2d::CCNode *sender) = 0;
    virtual void callbackAfterCCBLoaded() = 0;
};



class CCBCustomClassFactory
{
public:
    CCBCustomClassFactory();
    virtual ~CCBCustomClassFactory();
    
    static CCBCustomClassFactory* sharedFactory();

    bool registCustomClass(const char* name, FUNC_CUSTON_CLASS_CREATOR pfnCreator);
    CCBCustomClass* createCustomClassWithName(const char* name);
    
protected:
    CUSTOM_CLASS_MAP* m_pCustomCreatorsMap;
};

NS_CC_EXT_END;

#endif // _CC_CUSTOM_CLASS_H_
