/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCNewTextureAtlas.h"
#include "CCTexture2D.h"
#include "CCDirector.h"
#include "CCRenderer.h"
#include "CCQuadCommand.h"

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
    return NULL;
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
    return NULL;
}


void NewTextureAtlas::drawNumberOfQuads(long numberOfQuads, long start)
{
//    updateTransform();
//    QuadCommand* renderCommand = new QuadCommand(0, 0,_texture->getName(), _shaderProgram, _blendFunc, _quad);
//
//    Renderer::getInstance()->addCommand(renderCommand);
}

NS_CC_END
