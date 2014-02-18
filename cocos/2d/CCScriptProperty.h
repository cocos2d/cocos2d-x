//
//  ScriptProperty.h
//  cocos2d_libs
//
//  Created by James Chen on 14-2-18.
//
//

#ifndef __cocos2d_libs__ScriptProperty__
#define __cocos2d_libs__ScriptProperty__

#include "CCPlatformMacros.h"
#include "ccMacros.h"

NS_CC_BEGIN

class CC_DLL ScriptProperty
{
public:
    ScriptProperty();
    ~ScriptProperty();
    
    int _ID;
    int _luaID;
    void* _owner;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__ScriptProperty__) */
