/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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


#include "renderer/CCBatchCommand.h"
#include "ccGLStateCache.h"
#include "CCTextureAtlas.h"
#include "CCTexture2D.h"

NS_CC_BEGIN

BatchCommand::BatchCommand()
: _textureID(0)
, _blendType(BlendFunc::DISABLE)
, _textureAtlas(nullptr)
{
    _type = RenderCommand::Type::BATCH_COMMAND;
    _shader = nullptr;
}

void BatchCommand::init(float globalOrder, GLProgram* shader, BlendFunc blendType, TextureAtlas *textureAtlas, const kmMat4& modelViewTransform)
{
    CCASSERT(shader, "shader cannot be nill");
    CCASSERT(textureAtlas, "textureAtlas cannot be nill");
    
    _globalOrder = globalOrder;
    _textureID = textureAtlas->getTexture()->getName();
    _blendType = blendType;
    _shader = shader;

    _textureAtlas = textureAtlas;

    _mv = modelViewTransform;
}

BatchCommand::~BatchCommand()
{
}

void BatchCommand::execute()
{
    // Set material
    _shader->use();
    _shader->setUniformsForBuiltins(_mv);
    GL::bindTexture2D(_textureID);
    GL::blendFunc(_blendType.src, _blendType.dst);

    // Draw
    _textureAtlas->drawQuads();
}

NS_CC_END