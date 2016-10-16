//
//  CCSprite_C.cpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/15/16.
//
//

#include <stdio.h>

#include <cstdint>
#include "base/ccMacros.h"
#include "base/CCVector.h"
#include "base/CCProtocols.h"
#include "base/CCScriptSupport.h"
#include "math/CCAffineTransform.h"
#include "math/CCMath.h"
#include "2d/CCComponentContainer.h"
#include "2d/CCComponent.h"

#if CC_USE_PHYSICS
#include "physics/CCPhysicsBody.h"
#endif

#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "c/CCVector_C.h"
#include "c/CCDefines.h"

USING_NS_CC;

#pragma mark - Initialization

extern "C" void* CCSpriteCreate()
{
    Sprite *sprite = Sprite::create();
    return (void *)sprite;
}

extern "C" void* _Nullable CCSpriteCreateWithFilename(const char *filename)
{
    std::string string = std::string(filename);
    Sprite *sprite = Sprite::create(string);
    return (void *)sprite;
}
