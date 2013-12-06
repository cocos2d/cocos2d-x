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

    for(const auto &child: _children)
        child->updateTransform();

//    arrayMakeObjectsPerformSelector(_children, updateTransform, NewSprite*);

    auto shader = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);

    kmMat4 mv;
    kmGLGetMatrix(KM_GL_MODELVIEW, &mv);

    QuadCommand* cmd = QuadCommand::getCommandPool().generateCommand();
    cmd->init(0,
              _vertexZ,
              _textureAtlas->getTexture()->getName(),
              shader,
              _blendFunc,
              _textureAtlas->getQuads(),
              _textureAtlas->getTotalQuads(),
              mv);
    Renderer::getInstance()->addCommand(cmd);
}

NS_CC_END