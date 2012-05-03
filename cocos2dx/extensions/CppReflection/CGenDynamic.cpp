//
//  CGenDynamic.cpp
//  cocos2dXReflection
//
//  Created by 晓龙 张 on 12-2-17.
//  Copyright (c) 2012年 chukong-inc. All rights reserved.
//

#include <iostream>
#include "CGenDynamic.h"

CGenDynamic::CGenDynamic(string name, createClass method)
{
    CClassFactory::sharedClassFactory().registClass(name, method) ;
}
