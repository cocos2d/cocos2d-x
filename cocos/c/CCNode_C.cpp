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
#include "c/CCVector_C.h"

USING_NS_CC;

extern "C" void* CCNodeCreate()
{
    Node *node = Node::create();
    return (void *)node;
}

extern "C" const char* CCNodeGetDescription(const void *object)
{
    Node *node = (Node *)object;
    std::string string = node->getDescription();
    char *cString = (char*) malloc(string.size() + 1); //as 1 char space for null is also required
    strcpy(cString, string.c_str());
    return cString;
}

extern "C" int CCNodeGetLocalZOrder(const void *object)
{
    Node *node = (Node *)object;
    return node->getLocalZOrder();
}

extern "C" void CCNodeSetLocalZOrder(const void *object, int newValue)
{
    Node *node = (Node *)object;
    node->setLocalZOrder(newValue);
}

extern "C" int CCNodeGetGlobalZOrder(const void *object)
{
    Node *node = (Node *)object;
    return node->getGlobalZOrder();
}

extern "C" void CCNodeSetGlobalZOrder(const void *object, int newValue)
{
    Node *node = (Node *)object;
    node->setGlobalZOrder(newValue);
}

extern "C" float CCNodeGetScaleX(const void *object)
{
    Node *node = (Node *)object;
    return node->getScaleX();
}

extern "C" void CCNodeSetScaleX(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setScaleX(newValue);
}

extern "C" float CCNodeGetScaleY(const void *object)
{
    Node *node = (Node *)object;
    return node->getScaleY();
}

extern "C" void CCNodeSetScaleY(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setScaleY(newValue);
}

extern "C" float CCNodeGetScaleZ(const void *object)
{
    Node *node = (Node *)object;
    return node->getScaleZ();
}

extern "C" void CCNodeSetScaleZ(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setScaleZ(newValue);
}

extern "C" float CCNodeGetScale(const void *object)
{
    Node *node = (Node *)object;
    return node->getScale();
}

extern "C" void CCNodeSetScale(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setScale(newValue);
}

extern "C" CCVector2_C CCNodeGetPosition(const void *object)
{
    Node *node = (Node *)object;
    CCVector2_C vector = CCVector2_C();
    node->getPosition(&vector.x, &vector.y);
    return vector;
}

extern "C" void CCNodeSetPosition(const void *object, CCVector2_C newValue)
{
    Node *node = (Node *)object;
    node->setPosition(newValue.x, newValue.y);
}

extern "C" CCVector2_C CCNodeGetNormalizedPosition(const void *object)
{
    Node *node = (Node *)object;
    Vec2 vector = node->getNormalizedPosition();
    return { vector.x, vector.y };
}

extern "C" void CCNodeSetNormalizedPosition(const void *object, CCVector2_C newValue)
{
    Node *node = (Node *)object;
    Vec2 vector = Vec2(newValue.x, newValue.y);
    node->setNormalizedPosition(vector);
}

extern "C" CCVector3_C CCNodeGetPosition3D(const void *object)
{
    Node *node = (Node *)object;
    Vec3 vector = node->getPosition3D();
    return { vector.x, vector.y, vector.z };
}

extern "C" void CCNodeSetPosition3D(const void *object, CCVector3_C newValue)
{
    Node *node = (Node *)object;
    Vec3 vector = Vec3(newValue.x, newValue.y, newValue.z);
    node->setPosition3D(vector);
}
