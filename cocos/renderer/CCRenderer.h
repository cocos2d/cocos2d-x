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

#include "base/CCPlatformMacros.h"
#include "CCRenderCommand.h"
#include "2d/CCGLProgram.h"
#include "CCGL.h"
#include <vector>
#include <stack>

NS_CC_BEGIN

class EventListenerCustom;
class QuadCommand;

/** Class that knows how to sort `RenderCommand` objects.
 Since the commands that have `z == 0` are "pushed back" in
 the correct order, the only `RenderCommand` objects that need to be sorted,
 are the ones that have `z < 0` and `z > 0`.
*/
class RenderQueue {

public:
    void push_back(RenderCommand* command);
    ssize_t size() const;
    void sort();
    RenderCommand* operator[](ssize_t index) const;
    void clear();

protected:
    std::vector<RenderCommand*> _queueNegZ;
    std::vector<RenderCommand*> _queue0;
    std::vector<RenderCommand*> _queuePosZ;
};

struct RenderStackElement
{
    int renderQueueID;
    ssize_t currentIndex;
};

class GroupCommandManager;

/* Class responsible for the rendering in.

Whenever possible prefer to use `QuadCommand` objects since the renderer will automatically batch them.
 */
class Renderer
{
public:
    static const int VBO_SIZE = 65536 / 6;
    static const int BATCH_QUADCOMMAND_RESEVER_SIZE = 64;

    Renderer();
    ~Renderer();

    //TODO manage GLView inside Render itself
    void initGLView();

    /** Adds a `RenderComamnd` into the renderer */
    void addCommand(RenderCommand* command);

    /** Adds a `RenderComamnd` into the renderer specifying a particular render queue ID */
    void addCommand(RenderCommand* command, int renderQueue);

    /** Pushes a group into the render queue */
    void pushGroup(int renderQueueID);

    /** Pops a group from the render queue */
    void popGroup();

    /** Creates a render queue and returns its Id */
    int createRenderQueue();

    /** Renders into the GLView all the queued `RenderCommand` objects */
    void render();

    /** Cleans all `RenderCommand`s in the queue */
    void clean();

    /* returns the number of drawn batches in the last frame */
    ssize_t getDrawnBatches() const { return _drawnBatches; }
    /* RenderCommands (except) QuadCommand should update this value */
    void addDrawnBatches(ssize_t number) { _drawnBatches += number; };
    /* returns the number of drawn triangles in the last frame */
    ssize_t getDrawnVertices() const { return _drawnVertices; }
    /* RenderCommands (except) QuadCommand should update this value */
    void addDrawnVertices(ssize_t number) { _drawnVertices += number; };

    inline GroupCommandManager* getGroupCommandManager() const { return _groupCommandManager; };

    /** returns whether or not a rectangle is visible or not */
    bool checkVisibility(const Matrix& transform, const Size& size);

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
    
    void visitRenderQueue(const RenderQueue& queue);

    void convertToWorldCoordinates(V3F_C4B_T2F_Quad* quads, ssize_t quantity, const Matrix& modelView);

    std::stack<int> _commandGroupStack;
    
    std::vector<RenderQueue> _renderGroups;

    uint32_t _lastMaterialID;

    std::vector<QuadCommand*> _batchedQuadCommands;

    V3F_C4B_T2F_Quad _quads[VBO_SIZE];
    GLushort _indices[6 * VBO_SIZE];
    GLuint _quadVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _numQuads;
    
    bool _glViewAssigned;

    // stats
    ssize_t _drawnBatches;
    ssize_t _drawnVertices;
    //the flag for checking whether renderer is rendering
    bool _isRendering;
    
    GroupCommandManager* _groupCommandManager;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _cacheTextureListener;
#endif
};

NS_CC_END

#endif //__CC_RENDERER_H_
