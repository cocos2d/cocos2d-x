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

#pragma mark - Initialization

extern "C" void* CCNodeCreate()
{
    Node *node = Node::create();
    return (void *)node;
}

#pragma mark - Properties

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

extern "C" float CCNodeGetSkewX(const void *object)
{
    Node *node = (Node *)object;
    return node->getSkewX();
}

extern "C" void CCNodeSetSkewX(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setSkewX(newValue);
}

extern "C" float CCNodeGetSkewY(const void *object)
{
    Node *node = (Node *)object;
    return node->getSkewY();
}

extern "C" void CCNodeSetSkewY(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setSkewY(newValue);
}

extern "C" CCVector2_C CCNodeGetAnchorPoint(const void *object)
{
    Node *node = (Node *)object;
    Vec2 vector = node->getAnchorPoint();
    return { vector.x, vector.y };
}

extern "C" void CCNodeSetAnchorPoint(const void *object, CCVector2_C newValue)
{
    Node *node = (Node *)object;
    Vec2 vector = Vec2(newValue.x, newValue.y);
    node->setAnchorPoint(vector);
}

extern "C" CCVector2_C CCNodeGetAnchorPointInPoints(const void *object)
{
    Node *node = (Node *)object;
    Vec2 vector = node->getAnchorPointInPoints();
    return { vector.x, vector.y };
}

extern "C" CCVector2_C CCNodeGetContentSize(const void *object)
{
    Node *node = (Node *)object;
    Size size = node->getContentSize();
    return { size.width, size.height };
}

extern "C" void CCNodeSetContentSize(const void *object, CCVector2_C newValue)
{
    Node *node = (Node *)object;
    Size size = Size(newValue.x, newValue.y);
    node->setContentSize(size);
}

extern "C" bool CCNodeGetVisible(const void *object)
{
    Node *node = (Node *)object;
    return node->isVisible();
}

extern "C" void CCNodeSetVisible(const void *object, bool newValue)
{
    Node *node = (Node *)object;
    node->setVisible(newValue);
}

extern "C" float CCNodeGetRotation(const void *object)
{
    Node *node = (Node *)object;
    return node->getRotation();
}

extern "C" void CCNodeSetRotation(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setRotation(newValue);
}

extern "C" CCVector3_C CCNodeGetRotation3D(const void *object)
{
    Node *node = (Node *)object;
    Vec3 vector = node->getRotation3D();
    return { vector.x, vector.y, vector.z };
}

extern "C" void CCNodeSetRotation3D(const void *object, CCVector3_C newValue)
{
    Node *node = (Node *)object;
    Vec3 vector = Vec3(newValue.x, newValue.y, newValue.z);
    node->setRotation3D(vector);
}

extern "C" CCVector4_C CCNodeGetRotationByQuaternion(const void *object)
{
    Node *node = (Node *)object;
    Quaternion vector = node->getRotationQuat();
    return { vector.x, vector.y, vector.z, vector.w };
}

extern "C" void CCNodeSetRotationByQuaternion(const void *object, CCVector4_C newValue)
{
    Node *node = (Node *)object;
    Quaternion vector = Quaternion(newValue.x, newValue.y, newValue.z, newValue.w);
    node->setRotationQuat(vector);
}

extern "C" float CCNodeGetRotationSkewX(const void *object)
{
    Node *node = (Node *)object;
    return node->getRotationSkewX();
}

extern "C" void CCNodeSetRotationSkewX(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setRotationSkewX(newValue);
}

extern "C" float CCNodeGetRotationSkewY(const void *object)
{
    Node *node = (Node *)object;
    return node->getRotationSkewY();
}

extern "C" void CCNodeSetRotationSkewY(const void *object, float newValue)
{
    Node *node = (Node *)object;
    node->setRotationSkewY(newValue);
}

extern "C" const char* CCNodeGetName(const void *object)
{
    Node *node = (Node *)object;
    std::string string = node->getName();
    char *cString = (char*) malloc(string.size() + 1); //as 1 char space for null is also required
    strcpy(cString, string.c_str());
    return cString;
}

extern "C" void CCNodeSetName(const void *object, const char* newValue)
{
    Node *node = (Node *)object;
    std::string string = std::string(newValue);
    node->setName(string);
}

extern "C" int CCNodeGetTag(const void *object)
{
    Node *node = (Node *)object;
    return node->getTag();
}

extern "C" void CCNodeSetTag(const void *object, int newValue)
{
    Node *node = (Node *)object;
    node->setTag(newValue);
}

#pragma mark - Methods

extern "C" void CCNodeAddChild(const void *object, const void *childObject)
{
    Node *node = (Node *)object;
    Node *child = (Node *)childObject;
    node->addChild(child);
}

extern "C" void CCNodeAddChildWithLocalZOrder(const void *object, const void *childObject, int localZOrder)
{
    Node *node = (Node *)object;
    Node *child = (Node *)childObject;
    node->addChild(child, localZOrder);
}

extern "C" void CCNodeAddChildWithLocalZOrderAndTag(const void *object, const void *childObject, int localZOrder, int tag)
{
    Node *node = (Node *)object;
    Node *child = (Node *)childObject;
    node->addChild(child, localZOrder, tag);
}

extern "C" void CCNodeAddChildWithLocalZOrderAndName(const void *object, const void *childObject, int localZOrder, const char* name)
{
    Node *node = (Node *)object;
    Node *child = (Node *)childObject;
    std::string string = std::string(name);
    node->addChild(child, localZOrder, string);
}


