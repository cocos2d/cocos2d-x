/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCGLProgram.h"
#include "base/ccUtils.h"

NS_CC_BEGIN

BatchCommand::BatchCommand()
//: _textureID(0)
: _blendType(BlendFunc::DISABLE)
, _textureAtlas(nullptr)
{
    _type = RenderCommand::Type::BATCH_COMMAND;
//    _shader = nullptr;
}

//TODO coulsonwang
//void BatchCommand::init(float globalZOrder, GLProgram* shader, BlendFunc blendType, TextureAtlas *textureAtlas, const Mat4& modelViewTransform, uint32_t flags)
//{
//    //TODO coulsonwang
//    cocos2d::log("Error in%s %s %d", __FILE__, __FUNCTION__, __LINE__);
//}

void BatchCommand::init(float globalOrder, TextureAtlas *textureAtlas, const Mat4& modelViewTransform, uint32_t flags)
{
//    CCASSERT(shader, "shader cannot be null");
//    CCASSERT(textureAtlas, "textureAtlas cannot be null");
    
    RenderCommand::init(globalOrder, modelViewTransform, flags);
//    _textureID = textureAtlas->getTexture()->getName();
//    _blendType = blendType;
//    _shader = shader;
//
    _textureAtlas = textureAtlas;
    _mv = modelViewTransform;
}

BatchCommand::~BatchCommand()
{
}

//void BatchCommand::execute()
//{
//    // Set material
//    _shader->use();
//    _shader->setUniformsForBuiltins(_mv);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, _textureID);
//    utils::setBlending(_blendType.src, _blendType.dst);
//
//    // Draw
//    _textureAtlas->drawQuads();
//}

V3F_C4B_T2F_Quad* BatchCommand::getQuad() const
{
    return _textureAtlas->getQuads();
}

size_t BatchCommand::getQuadCount() const
{
    return _textureAtlas->getTotalQuads();
}

NS_CC_END
