//
//  CCScene_C.cpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/16/16.
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
#include "2d/CCScene.h"
#include "c/CCVector_C.h"
#include "c/CCDefines.h"

USING_NS_CC;

#pragma mark - Initialization

extern "C" void* CCSceneCreate()
{
    Scene *scene = Scene::create();
    return (void *)scene;
}

extern "C" void* CCSceneCreateWithSize(CCVector2_C size)
{
    Size sizeObject = Size(size.x, size.y);
    Scene *scene = Scene::createWithSize(sizeObject);
    return (void *)scene;
}
