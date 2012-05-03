//
//  CGenDynamic.h
//  cocos2dXReflection
//
//  Created by 晓龙 张 on 12-2-17.
//  Copyright (c) 2012年 chukong-inc. All rights reserved.
//

#ifndef cocos2dXReflection_CGenDynamic_h
#define cocos2dXReflection_CGenDynamic_h
//
#include <iostream>
#include "CClassFactory.h"
using namespace std ;
// 动态创建类 
class CGenDynamic
{
public:
    CGenDynamic(string name, createClass method) ;
} ;

#define DECLARE_RUNTIME(class_name)     \
string class_name##Name ;               \
static CGenDynamic* class_name##gd


#define IMPLEMENT_RUNTIME(class_name)   \
CGenDynamic* class_name::class_name##gd \
= new CGenDynamic(#class_name, class_name::createInstance) ;

#endif
