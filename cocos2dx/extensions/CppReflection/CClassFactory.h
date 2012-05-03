//
//  CClassFactory.h
//  cocos2dXReflection
//
//  Created by 晓龙 张 on 12-2-17.
//  Copyright (c) 2012年 chukong-inc. All rights reserved.
//

#ifndef cocos2dXReflection_CClassFactory_h
#define cocos2dXReflection_CClassFactory_h

#include <string>
#include <map>
#include <iostream>
#include "cocos2d.h"

using namespace std ;

typedef void* (*createClass)(void);

// 类工厂 
class CClassFactory
{
public:
    CClassFactory() ;
    
     void* getClassByName(string className); 

     void registClass(string name, createClass method) ;
    
     static CClassFactory& sharedClassFactory() ;
    
private:
     map<string, createClass> m_classMap ;
} ;


#endif
