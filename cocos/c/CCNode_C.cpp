//
//  CCNode_C.cpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/14/16.
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

extern "C" void* CCNodeCreate()
{
    cocos2d::Node *node = cocos2d::Node::create();
    return (void *)node;
}

extern "C" const char* CCNodeGetDescription(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    std::string string = node->getDescription();
    char *cString = (char*) malloc(string.size() + 1); //as 1 char space for null is also required
    strcpy(cString, string.c_str());
    return cString;
}

extern "C" int CCNodeGetLocalZOrder(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getLocalZOrder();
}

extern "C" void CCNodeSetLocalZOrder(const void *object, int newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setLocalZOrder(newValue);
}

extern "C" int CCNodeGetGlobalZOrder(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getGlobalZOrder();
}

extern "C" void CCNodeSetGlobalZOrder(const void *object, int newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setGlobalZOrder(newValue);
}

extern "C" float CCNodeGetScaleX(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScaleX();
}

extern "C" void CCNodeSetScaleX(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScaleX(newValue);
}

extern "C" float CCNodeGetScaleY(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScaleY();
}

extern "C" void CCNodeSetScaleY(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScaleY(newValue);
}

extern "C" float CCNodeGetScaleZ(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScaleZ();
}

extern "C" void CCNodeSetScaleZ(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScaleZ(newValue);
}

extern "C" float CCNodeGetScale(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScale();
}

extern "C" void CCNodeSetScale(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScale(newValue);
}
