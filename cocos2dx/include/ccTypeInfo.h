//
//  ccTypeInfo.h
//  cocos2dx
//
//  Created by Rohan Kuruvilla on 27/08/2012.
//  Copyright (c) 2012 厦门雅基软件有限公司. All rights reserved.
//

#ifndef cocos2dx_ccTypeInfo_h
#define cocos2dx_ccTypeInfo_h

#include "platform/CCPlatformMacros.h"

#include <typeinfo>

NS_CC_BEGIN

class TypeInfo
{
public:
	virtual long getClassTypeInfo() = 0;
};

NS_CC_END

#endif
