//
// Created by NiTe Luo on 11/11/13.
//


#include "CCNewTextureAtlas.h"
#include "CCTexture2D.h"
#include "CCDirector.h"
#include "Renderer.h"
#include "QuadCommand.h"

NS_CC_BEGIN

NewTextureAtlas::NewTextureAtlas()
:TextureAtlas()
{

}

NewTextureAtlas::~NewTextureAtlas()
{

}

NewTextureAtlas *NewTextureAtlas::create(const char *file, long capacity)
{
    NewTextureAtlas * textureAtlas = new NewTextureAtlas();
    if(textureAtlas && textureAtlas->initWithFile(file, capacity))
    {
        textureAtlas->autorelease();
        return textureAtlas;
    }
    CC_SAFE_DELETE(textureAtlas);
    return nullptr;
}

NewTextureAtlas *NewTextureAtlas::createWithTexture(Texture2D *texture, long capacity)
{
    NewTextureAtlas * textureAtlas = new NewTextureAtlas();
    if (textureAtlas && textureAtlas->initWithTexture(texture, capacity))
    {
        textureAtlas->autorelease();
        return textureAtlas;
    }
    CC_SAFE_DELETE(textureAtlas);
    return nullptr;
}


void NewTextureAtlas::drawNumberOfQuads(long numberOfQuads, long start)
{
//    updateTransform();
//    QuadCommand* renderCommand = new QuadCommand(0, 0,_texture->getName(), _shaderProgram, _blendFunc, _quad);
//
//    Renderer::getInstance()->addCommand(renderCommand);
}

NS_CC_END
