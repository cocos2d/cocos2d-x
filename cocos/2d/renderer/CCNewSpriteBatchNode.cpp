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

#include "CCNewSpriteBatchNode.h"
#include "CCDirector.h"
#include "CCShaderCache.h"
#include "CCTextureCache.h"
#include "CCSprite.h"
#include "CCNewSprite.h"
#include "CCQuadCommand.h"
#include "CCRenderer.h"

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
    Director::getInstance()->getRenderer()->addCommand(cmd);
}

NS_CC_END