//
//  CObject.h
//  cocos2dXReflection
//
//  Created by 晓龙 张 on 12-2-17.
//  Copyright (c) 2012年 chukong-inc. All rights reserved.
//

#ifndef cocos2dXReflection_CObject_h
#define cocos2dXReflection_CObject_h


#include "CGenDynamic.h"
#include "cocos2d.h"
#define id void*

class CObject ;
typedef void (*setValue)(CObject *t, id c) ;
typedef void (*callBack)(cocos2d::CCObject*sender) ;
/*
 基类
*/

class CObject : public cocos2d::CCLayer
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
    map<string, setValue> propertyMap ;
    map<string, callBack> methodMap ;
};

#define SET(C, P, V)                                                                        \
static void set##V(CObject*t, id cc){                                                       \
    C*  tt = (C*)t ;                                                                        \
    tt->V  = (P)cc ;                                                                        \
}

#define CALLBACKMETHOD(M, sender)                                                           \
{                                                                                           \
map<string, callBack>::const_iterator iter;                                                 \
iter = methodMap.find(#M) ;                                                                 \
if ( iter == methodMap.end() ){                                                             \
    CCLOG("ERROR: can't call this method!!, try to review!") ;                              \
    break ;                                                                                 \
}                                                                                           \
else                                                                                        \
{                                                                                           \
    methodMap[#M](sender) ;                                                                 \
}                                                                                           \
}

#define REGISTPROPERTYS(MethodName, ClassPoint, PropertyType, Property, Map, setProperty)   \
SET(MethodName, ClassPoint, PropertyType, Property)                                         \
virtual void registProperty(){                                                              \
Map.insert(pair<string, setValue>(#setProperty, setProperty)) ;                             \
}

#define REGISTPROPERTY(setProperty)                                                         \
propertyMap.insert(pair<string, setValue>(#setProperty, setProperty)) ;

#define REGISTMETHOD(method)                                                                \
methodMap.insert(pair<string, callBack>(#method, method)) ;

#endif
//}