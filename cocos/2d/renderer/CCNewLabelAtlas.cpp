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


#include "CCNewLabelAtlas.h"
#include "CCRenderCommand.h"
#include "CCRenderer.h"
#include "CCQuadCommand.h"
#include "CCMenuItem.h"
#include "CCFrustum.h"
#include "CCDirector.h"
#include "CCTextureAtlas.h"
#include "CCShaderCache.h"

NS_CC_BEGIN


void NewLabelAtlas::draw()
{
//    LabelAtlas::draw();
//    _renderCommand.init(0, _vertexZ, _textureAtlas->getTexture()->getName(), _shaderProgram, _blendFunc,
//                        _textureAtlas->getQuads(), _textureAtlas->getTotalQuads() );
//
//    Renderer::getInstance()->addCommand(&_renderCommand);


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