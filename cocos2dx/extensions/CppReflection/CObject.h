/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2012 XiaoLong Zhang, Chukong Inc.
 
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

#ifndef cocos2dXReflection_CObject_h
#define cocos2dXReflection_CObject_h

#include "CGenDynamic.h"
#include "cocos2d.h"

class CObject ;
typedef void (*setValue)(CObject *t, void* c) ;
typedef void (*callBack)(cocos2d::CCObject*sender) ;

class CObject : public cocos2d::CCNode
{
private:
    DECLARE_RUNTIME(CObject);
public:
    CObject();
    virtual ~CObject() ;
    static void* createInstance() ;
    virtual void didLoadFromCCB() ;
    virtual void registProperty() ;
    virtual void registMethod() ;
    virtual void menuCallBack(CCObject*sender) ;
public:
    std::map<std::string, setValue> propertyMap ;
    std::map<std::string, callBack> methodMap ;
};

#define SET(C, P, V)                        \
static void set##V(CObject*t, void* cc){    \
    C*  tt = (C*)t ;                        \
    tt->V  = (P)cc ;                        \
}

#define CALLBACKMETHOD(M, sender)                                \
{                                                                \
map<string, callBack>::const_iterator iter;                      \
iter = methodMap.find(#M) ;                                      \
if ( iter == methodMap.end() ){                                  \
    CCLOG("ERROR: can't call this method!!, try to review!") ;   \
    break ;                                                      \
}                                                                \
else                                                             \
{                                                                \
    methodMap[#M](sender) ;                                      \
}                                                                \
}

#define REGIST_PROPERTYS(MethodName, ClassPoint, PropertyType, Property, Map, setProperty)   \
SET(MethodName, ClassPoint, PropertyType, Property)                                         \
virtual void registProperty(){                                                              \
Map.insert(std::pair<std::string, setValue>(#setProperty, setProperty)) ;                             \
}

#define REGIST_PROPERTY(setProperty)                                                         \
propertyMap.insert(std::pair<std::string, setValue>(#setProperty, setProperty)) ;

#define REGISTMETHOD(method)                                                                \
methodMap.insert(std::pair<std::string, callBack>(#method, method)) ;

#endif
