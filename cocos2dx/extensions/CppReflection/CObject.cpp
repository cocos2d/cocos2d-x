//
//  CObject.cpp
//  cocos2dXReflection
//
//  Created by 晓龙 张 on 12-2-17.
//  Copyright (c) 2012年 chukong-inc. All rights reserved.
//

#include "CObject.h"
using namespace cocos2d;

IMPLEMENT_RUNTIME(CObject)

CObject::CObject()
{
    
}
CObject::~CObject()
{
    
}
void* CObject::createInstance()
{
    return new CObject ;
    
}
void CObject::didLoadFromCCB()
{
    //overwrite this Method
}
void CObject::registProperty()
{
    //overwrite this Method
}
void CObject::registMethod()
{
    //overwrite this Method
}
void CObject::menuCallBack(CCObject*sender) 
{
    //overwrite this Method
}