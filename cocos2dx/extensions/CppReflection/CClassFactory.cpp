//
//  CClassFactory.cpp
//  cocos2dXReflection
//
//  Created by 晓龙 张 on 12-2-17.
//  Copyright (c) 2012年 chukong-inc. All rights reserved.
//

#include "CClassFactory.h"
#include "CObject.h"
#include "CGenDynamic.h"
#include "cocos2d.h"
using namespace cocos2d ;

CClassFactory& CClassFactory::sharedClassFactory() {
    static CClassFactory _shared;
    return _shared;
}

CClassFactory::CClassFactory()
{
    CClassFactory::m_classMap = map<string, createClass>();
}

void* CClassFactory::getClassByName(string className)
{
    map<string, createClass>::const_iterator iter ;
    
    iter = m_classMap.find(className) ;
    
    if ( iter == m_classMap.end() )
        return NULL ;
    else
        return iter->second() ;
}

void CClassFactory::registClass(string name, createClass method)
{
    CCLog(name.c_str()) ;
    m_classMap.insert(pair<string, createClass>(name, method)) ;
    
}
