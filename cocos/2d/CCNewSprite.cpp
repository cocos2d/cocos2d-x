//
//  CCNewSprite.cpp
//  cocos2d_libs
//
//  Created by NiTe Luo on 10/31/13.
//
//

#include "CCNewSprite.h"
#include "RenderCommand.h"
#include "Renderer.h"

NS_CC_BEGIN

NewSprite* NewSprite::create()
{
    NewSprite* sprite = new NewSprite();
    if(sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

NewSprite* NewSprite::create(const char *filename)
{
    NewSprite* sprite = new NewSprite();
    if(sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

NewSprite::NewSprite()
:Sprite()
{

}

void NewSprite::draw(void)
{
    kmMat4 transform;
    kmGLGetMatrix(KM_GL_MODELVIEW, &transform);
    RenderCommand* renderCommand = new RenderCommand();
    renderCommand->setKeyData(0, true, false, _ZOrder);
    renderCommand->setMaterialData(_texture->getName(), _shaderProgram->getProgram(), _blendFunc);
    renderCommand->setQuadData(&transform, _quad);

    Renderer::getInstance()->addRenderCommand(renderCommand);
}

NS_CC_END