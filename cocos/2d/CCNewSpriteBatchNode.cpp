//
// Created by NiTe Luo on 11/11/13.
//


#include "CCNewSpriteBatchNode.h"
#include "CCDirector.h"
#include "CCShaderCache.h"
#include "CCTextureCache.h"
#include "CCSprite.h"
#include "CCNewSprite.h"
#include "QuadCommand.h"
#include "Renderer.h"

NS_CC_BEGIN

NewSpriteBatchNode *NewSpriteBatchNode::createWithTexture(Texture2D *tex, int capacity)
{
    NewSpriteBatchNode* batchNode = new NewSpriteBatchNode();
    batchNode->initWithTexture(tex, capacity);
    batchNode->autorelease();

    return batchNode;
}

NewSpriteBatchNode *NewSpriteBatchNode::create(const char *fileImage, long capacity)
{
    NewSpriteBatchNode* batchNode = new NewSpriteBatchNode();
    batchNode->initWithFile(fileImage, capacity);
    batchNode->autorelease();

    return batchNode;
}

NewSpriteBatchNode::NewSpriteBatchNode()
:SpriteBatchNode()
{

}

NewSpriteBatchNode::~NewSpriteBatchNode()
{

}

bool NewSpriteBatchNode::init()
{
    Texture2D* texture = new Texture2D();
    texture->autorelease();
    return this->initWithTexture(texture, 0);
}

void NewSpriteBatchNode::draw()
{
    // Optimization: Fast Dispatch
    if( _textureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    arrayMakeObjectsPerformSelector(_children, updateTransform, NewSprite*);

    QuadCommand* cmd = new QuadCommand(0, 0, _textureAtlas->getTexture()->getName(), _shaderProgram, _blendFunc, _textureAtlas->getQuads(), _textureAtlas->getTotalQuads());
    Renderer::getInstance()->addRenderCommand(cmd);
}

NS_CC_END