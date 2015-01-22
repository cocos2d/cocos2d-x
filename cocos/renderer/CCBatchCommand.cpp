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
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCVertexIndexData.h"

NS_CC_BEGIN

BatchCommand::BatchCommand()
    : _textureID(0)
    , _blendType(BlendFunc::DISABLE)
    , _textureAtlas(nullptr)
    , _batch(nullptr)
{
    _type = RenderCommand::Type::BATCH_COMMAND;
    _shader = nullptr;
}

void BatchCommand::init(float globalOrder, GLProgram* shader, BlendFunc blendType, TextureAtlas *textureAtlas, const Mat4& modelViewTransform, uint32_t flags)
{
    CCASSERT(shader, "shader cannot be nill");
    CCASSERT(textureAtlas, "textureAtlas cannot be nill");
    
    RenderCommand::init(globalOrder, modelViewTransform, flags);
    _textureID = textureAtlas->getTexture()->getName();
    _blendType = blendType;
    _shader = shader;

    CC_SAFE_RELEASE(_textureAtlas);
    CC_SAFE_RELEASE(_batch);
    _textureAtlas = textureAtlas;
    _textureAtlas->retain();
    
    _mv = modelViewTransform;
}

void BatchCommand::init(float globalOrder, GLProgram* shader, BlendFunc blendType, Texture2D* texture, VertexData* batch, const Mat4& modelViewTransform, uint32_t flags)
{
    CCASSERT(shader,  "shader cannot be nullptr");
    CCASSERT(batch,   "vertexData cannot be nullptr");
    
    RenderCommand::init(globalOrder, modelViewTransform, flags);
    _globalOrder = globalOrder;
    _textureID = texture ? texture->getName() : 0;
    _blendType = blendType;
    _shader = shader;
    
    CC_SAFE_RELEASE(_textureAtlas);
    CC_SAFE_RELEASE(_batch);
    _batch = batch;
    _batch->retain();

    _mv = modelViewTransform;
}

BatchCommand::~BatchCommand()
{
    CC_SAFE_RELEASE(_textureAtlas);
    CC_SAFE_RELEASE(_batch);
}

void BatchCommand::execute()
{
    // Set material
    _shader->use();
    _shader->setUniformsForBuiltins(_mv);

    // Draw
    if (_textureAtlas)
    {
        GL::bindTexture2D(_textureID);
        GL::blendFunc(_blendType.src, _blendType.dst);
        _textureAtlas->drawQuads();
    }
    else if (_batch)
    {
        if (_textureID)
            GL::bindTexture2D(_textureID);
        GL::blendFunc(_blendType.src, _blendType.dst);
        _batch->draw();
    }
    else
    {
        CCASSERT(false, "BatchCommand::execute - nothing to draw");
    }
}

NS_CC_END
