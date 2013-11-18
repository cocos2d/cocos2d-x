//
// Created by NiTe Luo on 11/14/13.
//


#include "CCNewDrawNode.h"
#include "QuadCommand.h"

NS_CC_BEGIN

NewDrawNode *NewDrawNode::create()
{
    NewDrawNode* pRet = new NewDrawNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

NewDrawNode::NewDrawNode()
{

}

NewDrawNode::~NewDrawNode()
{

}

bool NewDrawNode::init()
{
    return DrawNode::init();
}

void NewDrawNode::draw()
{
    updateTransform();

//    QuadCommand* quadCommand = new QuadCommand(0, _vertexZ, 0, _shaderProgram, _blendFunc, )
}

NS_CC_END