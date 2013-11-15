//
// Created by NiTe Luo on 11/14/13.
//



#ifndef __CCNewDrawNode_H_
#define __CCNewDrawNode_H_

#include "CCPlatformMacros.h"
#include "CCDrawNode.h"

NS_CC_BEGIN

class NewDrawNode : public DrawNode
{
public:
    static NewDrawNode* create();

    virtual ~NewDrawNode();

    virtual bool init();

    void draw();

protected:
    NewDrawNode();
};

NS_CC_END

#endif //__CCNewDrawNode_H_
