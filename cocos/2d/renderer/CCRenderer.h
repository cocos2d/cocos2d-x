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


#ifndef __CC_RENDERER_H_
#define __CC_RENDERER_H_

#include "CCPlatformMacros.h"
#include "CCRenderCommand.h"
#include "CCGLProgram.h"
#include "CCGL.h"
#include <vector>
#include <stack>

NS_CC_BEGIN

class EventListenerCustom;

typedef std::vector<RenderCommand*> RenderQueue;

struct RenderStackElement
{
    int renderQueueID;
    ssize_t currentIndex;
};

class Renderer
{
public:
    static const int VBO_SIZE = 65536 / 6;

    Renderer();
    ~Renderer();

    //TODO manage GLView inside Render itself
    void initGLView();
    
    //TODO support multiple viewport
    void addCommand(RenderCommand* command);
    void addCommand(RenderCommand* command, int renderQueue);
    void pushGroup(int renderQueueID);
    void popGroup();
    
    int createRenderQueue();
    void render();

protected:

    void setupIndices();
    //Setup VBO or VAO based on OpenGL extensions
    void setupBuffer();
    void setupVBOAndVAO();
    void setupVBO();
    void mapBuffers();

    void drawBatchedQuads();

    //Draw the previews queued quads and flush previous context
    void flush();

    void convertToWorldCoordiantes(V3F_C4B_T2F_Quad* quads, ssize_t quantity, const kmMat4& modelView);

    std::stack<int> _commandGroupStack;
    
    std::stack<RenderStackElement> _renderStack;
    std::vector<RenderQueue> _renderGroups;

    uint32_t _lastMaterialID;

    ssize_t _firstCommand;
    ssize_t _lastCommand;

    V3F_C4B_T2F_Quad _quads[VBO_SIZE];
    GLushort _indices[6 * VBO_SIZE];
    GLuint _quadVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _numQuads;
    
    bool _glViewAssigned;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _cacheTextureListener;
#endif
};

NS_CC_END

#endif //__CC_RENDERER_H_
