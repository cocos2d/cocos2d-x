
#pragma once

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

#include "renderer/CCRenderCommand.h"
#include "2d/CCNode.h"
#include <stack>

NS_CC_BEGIN

class GLProgram;

class StencilCommand
    : public RenderCommand
{
protected:

    struct tStencilState
    {
        GLboolean _enabled;
        GLboolean _depthWriteMask;
        GLboolean _alphaTestEnabled;
        
        GLint _writeMask;
        GLint _func;
        GLint _ref;
        GLint _valueMask;
        GLint _fail;
        GLint _passDepthFail;
        GLint _passDepthPass;
        GLint _alphaTestFunc;
        
        GLint _mask_layer;
        GLint _mask_layer_l;
        GLint _mask_layer_le;
        
        GLclampf _alphaTestRef;
    };

    static void setProgram(Node *n, GLProgram *p);
    tStencilState getCurrentState() const;
    void drawFullScreenQuadClearStencil();

protected:
    
    typedef std::stack<tStencilState> tStencilStates;
    static tStencilStates _stencilStates;
    
    static int _stencilCount;
    static GLint  _stencilBits;
    static GLuint _layer;
};


class BeginStencilCommand
    : public StencilCommand
{
public:
    
    BeginStencilCommand()
    {
        _type = RenderCommand::Type::BEGIN_STENCIL_COMMAND;
    }
    void init(float depth, bool inverted = false, float alphaThreshold = 0, Node* stencil = nullptr, bool clearStencil = true);
    void execute();
    
protected:
    
    bool _inverted;
    float _alphaThreshold;
    Node* _stencil;
    bool _clearStencil;
};


class AfterStencilCommand
    : public StencilCommand
{
public:
    
    AfterStencilCommand()
    {
        _type = RenderCommand::Type::AFTER_STENCIL_COMMAND;
    }
    void init(float depth, float alphaThreshold = 0);
    void execute();
    
protected:
    
    float _alphaThreshold;
};


class EndStencilCommand
    : public StencilCommand
{
public:
    
    EndStencilCommand()
    {
        _type = RenderCommand::Type::END_STENCIL_COMMAND;
    }
    void init(float depth);
    void execute();    
};

NS_CC_END