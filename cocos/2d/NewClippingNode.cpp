//
// Created by NiTe Luo on 11/13/13.
//


#include "NewClippingNode.h"
#include "GroupCommand.h"

NS_CC_BEGIN

NewClippingNode *NewClippingNode::create()
{
    NewClippingNode* pRet = new NewClippingNode();
    if(pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

NewClippingNode *NewClippingNode::create(Node *pStencil)
{
    NewClippingNode* pRet = new NewClippingNode();
    if(pRet && pRet->init(pStencil))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

NewClippingNode::~NewClippingNode()
{

}

NewClippingNode::NewClippingNode()
:ClippingNode()
{

}

void NewClippingNode::visit()
{
    //Add group command
    GroupCommand* groupCommand = new GroupCommand(0,0);
}

NS_CC_END
