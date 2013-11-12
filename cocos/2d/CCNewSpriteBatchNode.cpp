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

    return nullptr;
}

NewSpriteBatchNode::NewSpriteBatchNode()
:SpriteBatchNode()
{

}

NewSpriteBatchNode::~NewSpriteBatchNode()
{

}

bool NewSpriteBatchNode::initWithTexture(Texture2D *tex, long capacity)
{
    CCASSERT(capacity>=0, "Capacity must be >= 0");

    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    _textureAtlas = new TextureAtlas();

    if (capacity == 0)
    {
        capacity = DEFAULT_CAPACITY;
    }

    _textureAtlas->initWithTexture(tex, capacity);

    updateBlendFunc();

    // no lazy alloc in this node
    _children = new Array();
    _children->initWithCapacity(capacity);

    _descendants.reserve(capacity);

    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    return true;
}

bool NewSpriteBatchNode::initWithFile(const char *fileImage, long capacity)
{
    Texture2D* tex = Director::getInstance()->getTextureCache()->addImage(fileImage);
    return initWithTexture(tex, capacity);
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

    CC_NODE_DRAW_SETUP();

    arrayMakeObjectsPerformSelector(_children, updateTransform, NewSprite*);

    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    QuadCommand* cmd = new QuadCommand(0, 0, _textureAtlas->getTexture()->getName(), _shaderProgram, _blendFunc, _textureAtlas->getQuads(), _textureAtlas->getTotalQuads());
    Renderer::getInstance()->addRenderCommand(cmd);
}

NS_CC_END