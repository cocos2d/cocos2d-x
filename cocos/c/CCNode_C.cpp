//
//  CCNode_C.cpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/14/16.
//
//

#include <stdio.h>

#ifndef __cplusplus

void* CCNodeCreate()
{
    cocos2d::Node *node = cocos2d::Node::create();
    return (void *)node;
}

const char* CCNodeGetDescription(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    std::string string = node->getDescription();
    char *cString = (char*) malloc(string.size() + 1); //as 1 char space for null is also required
    strcpy(cString, string.c_str());
    return cString;
}

int CCNodeGetLocalZOrder(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getLocalZOrder();
}

void CCNodeSetLocalZOrder(const void *object, int newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setLocalZOrder(newValue);
}

int CCNodeGetGlobalZOrder(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getGlobalZOrder();
}

void CCNodeSetGlobalZOrder(const void *object, int newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setGlobalZOrder(newValue);
}

float CCNodeGetScaleX(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScaleX();
}

void CCNodeSetScaleX(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScaleX(newValue);
}

float CCNodeGetScaleY(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScaleY();
}

void CCNodeSetScaleY(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScaleY(newValue);
}

float CCNodeGetScaleZ(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScaleZ();
}

void CCNodeSetScaleZ(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScaleZ(newValue);
}

float CCNodeGetScale(const void *object)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    return node->getScale();
}

void CCNodeSetScale(const void *object, float newValue)
{
    cocos2d::Node *node = (cocos2d::Node *)object;
    node->setScale(newValue);
}

#endif
