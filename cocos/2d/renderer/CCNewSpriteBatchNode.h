//
// Created by NiTe Luo on 11/11/13.
//



#ifndef __CCNewSpriteBatchNode_H_
#define __CCNewSpriteBatchNode_H_

#include "CCPlatformMacros.h"
#include "CCTexture2D.h"
#include "CCSpriteBatchNode.h"

NS_CC_BEGIN

class NewSpriteBatchNode : public SpriteBatchNode
{
    static const int DEFAULT_CAPACITY = 29;
public:
    static NewSpriteBatchNode* createWithTexture(Texture2D* tex, int capacity = DEFAULT_CAPACITY);
    static NewSpriteBatchNode* create(const char* fileImage, long capacity = DEFAULT_CAPACITY);

    NewSpriteBatchNode();
    virtual ~NewSpriteBatchNode();

    bool init();

    void draw(void);
};

NS_CC_END

#endif //__CCNewSpriteBatchNode_H_
