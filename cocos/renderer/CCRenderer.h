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
#pragma once

#include <vector>
#include <stack>
#include <array>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgram.h"


/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

namespace backend
{
    class Buffer;
    class CommandBuffer;
    class RenderPipeline;
    class RenderPass;
}

class EventListenerCustom;
class TrianglesCommand;
class MeshCommand;
class GroupCommand;
class CallbackCommand;
struct PipelineDescriptor;
class Texture2D;

/** Class that knows how to sort `RenderCommand` objects.
 Since the commands that have `z == 0` are "pushed back" in
 the correct order, the only `RenderCommand` objects that need to be sorted,
 are the ones that have `z < 0` and `z > 0`.
*/
class RenderQueue
{
public:
    /**
    RenderCommand will be divided into Queue Groups.
    */
    enum QUEUE_GROUP
    {
        /**Objects with globalZ smaller than 0.*/
        GLOBALZ_NEG = 0,
        /**Opaque 3D objects with 0 globalZ.*/
        OPAQUE_3D = 1,
        /**Transparent 3D objects with 0 globalZ.*/
        TRANSPARENT_3D = 2,
        /**2D objects with 0 globalZ.*/
        GLOBALZ_ZERO = 3,
        /**Objects with globalZ bigger than 0.*/
        GLOBALZ_POS = 4,
        QUEUE_COUNT = 5,
    };

public:
    /**Constructor.*/
    RenderQueue();
    /**Push a renderCommand into current renderqueue.*/
    void push_back(RenderCommand* command);
    /**Return the number of render commands.*/
    ssize_t size() const;
    /**Sort the render commands.*/
    void sort();
    /**Treat sorted commands as an array, access them one by one.*/
    RenderCommand* operator[](ssize_t index) const;
    /**Clear all rendered commands.*/
    void clear();
    /**Realloc command queues and reserve with given size. Note: this clears any existing commands.*/
    void realloc(size_t reserveSize);
    /**Get a sub group of the render queue.*/
    std::vector<RenderCommand*>& getSubQueue(QUEUE_GROUP group) { return _commands[group]; }
    /**Get the number of render commands contained in a subqueue.*/
    ssize_t getSubQueueSize(QUEUE_GROUP group) const { return _commands[group].size(); }

    /**Save the current DepthState, CullState, DepthWriteState render state.*/
//    void saveRenderState();
//    /**Restore the saved DepthState, CullState, DepthWriteState render state.*/
//    void restoreRenderState();
    
protected:
    /**The commands in the render queue.*/
    std::vector<RenderCommand*> _commands[QUEUE_COUNT];
    
    /**Cull state.*/
    bool _isCullEnabled;
    /**Depth test enable state.*/
    bool _isDepthEnabled;
    /**Depth buffer write state.*/
    GLboolean _isDepthWrite;
};

class CC_DLL ClearCommandManager
{
public:
    ClearCommandManager();
    ~ClearCommandManager();

    CallbackCommand* getCommand();
    void pushBackCommand(CallbackCommand*);

private:
    std::vector<CallbackCommand*> _commands;
};


class GroupCommandManager;

/* Class responsible for the rendering in.

Whenever possible prefer to use `TrianglesCommand` objects since the renderer will automatically batch them.
 */
class CC_DLL Renderer
{
public:
    
    /**The max number of vertices in a vertex buffer object.*/
    static const int VBO_SIZE = 65536;
    /**The max number of indices in a index buffer.*/
    static const int INDEX_VBO_SIZE = VBO_SIZE * 6 / 4;
    /**The rendercommands which can be batched will be saved into a list, this is the reserved size of this list.*/
    static const int BATCH_TRIAGCOMMAND_RESERVED_SIZE = 64;
    /**Reserved for material id, which means that the command could not be batched.*/
    static const int MATERIAL_ID_DO_NOT_BATCH = 0;
    /**Constructor.*/
    Renderer();
    /**Destructor.*/
    ~Renderer();

    //TODO: manage GLView inside Render itself
    void init();

    /** Adds a `RenderComamnd` into the renderer */
    void addCommand(RenderCommand* command);

    /** Adds a `RenderComamnd` into the renderer specifying a particular render queue ID */
    void addCommand(RenderCommand* command, int renderQueueID);

    /** Pushes a group into the render queue */
    void pushGroup(int renderQueueID);

    /** Pops a group from the render queue */
    void popGroup();

    /** Creates a render queue and returns its Id */
    int createRenderQueue();
    
    void beginFrame();
    void endFrame();

    /** Renders into the GLView all the queued `RenderCommand` objects */
    void render();

    /** Cleans all `RenderCommand`s in the queue */
    void clean();

    /* returns the number of drawn batches in the last frame */
    ssize_t getDrawnBatches() const { return _drawnBatches; }
    /* RenderCommands (except) TrianglesCommand should update this value */
    void addDrawnBatches(ssize_t number) { _drawnBatches += number; };
    /* returns the number of drawn triangles in the last frame */
    ssize_t getDrawnVertices() const { return _drawnVertices; }
    /* RenderCommands (except) TrianglesCommand should update this value */
    void addDrawnVertices(ssize_t number) { _drawnVertices += number; };
    /* clear draw stats */
    void clearDrawStats() { _drawnBatches = _drawnVertices = 0; }

    void setRenderTarget(RenderTargetFlag flags, Texture2D* colorAttachment, Texture2D* depthAttachment, Texture2D* stencilAttachment);
    void clear(ClearFlag flags, const Color4F& color, float depth, unsigned int stencil);
    Texture2D* getColorAttachment() const;
    Texture2D* getDepthAttachment() const;
    Texture2D* getStencilAttachment() const;
    const Color4F& getClearColor() const;
    float getClearDepth() const;
    unsigned int getClearStencil() const;
    ClearFlag getClearFlag() const;
    RenderTargetFlag getRenderTargetFlag() const;

    // depth/stencil state.

    void setDepthTest(bool value);
    void setDepthWrite(bool value);
    bool getDepthTest() const;
    bool getDepthWrite() const;

    void setStencilTest(bool value);
    void setStencilCompareFunction(backend::CompareFunction func, unsigned int ref, unsigned int readMask);
    void setStencilOperation(backend::StencilOperation stencilFailureOp,
                             backend::StencilOperation depthFailureOp,
                             backend::StencilOperation stencilDepthPassOp);
    void setStencilWriteMask(unsigned int mask);
    bool getStencilTest() const;
    backend::StencilOperation getStencilFailureOperation() const;
    backend::StencilOperation getStencilPassDepthFailureOperation() const;
    backend::StencilOperation getStencilDepthPassOperation() const;
    backend::CompareFunction getStencilCompareFunction() const;
    unsigned int getStencilReadMask() const;
    unsigned int getStencilWriteMask() const;
    unsigned int getStencilReferenceValue() const;

    void setViewPort(int x, int y, unsigned int w, unsigned int h);
    const Viewport& getViewport() const { return _viewport; }
    
    //This will not be used outside.
    GroupCommandManager* getGroupCommandManager() const { return _groupCommandManager; }

    /** returns whether or not a rectangle is visible or not */
    bool checkVisibility(const Mat4& transform, const Size& size);
    
    bool getScissorTest() const;
    void setScissorTest(bool enabled);
    const ScissorRect& getScissorRect() const;
    void setScissorRect(float x, float y, float width, float height);

protected:
    void drawBatchedTriangles();
    void drawCustomCommand(RenderCommand* command);

    //Draw the previews queued triangles and flush previous context
    void flush();
    
    void flush2D();
    
    void flush3D();

    void flushTriangles();

    void processRenderCommand(RenderCommand* command);
    void processGroupCommand(GroupCommand*);
    void visitRenderQueue(RenderQueue& queue);
    void doVisitRenderQueue(const std::vector<RenderCommand*>&);

    void fillVerticesAndIndices(const TrianglesCommand* cmd, unsigned int vertexBufferOffset, unsigned int& filledVertexCount, unsigned int& filledIndexCount);
    void beginRenderPass(RenderCommand*);
    
    void setRenderPipeline(const PipelineDescriptor&, const backend::RenderPassDescriptor&);


    Viewport _viewport;

    std::stack<int> _commandGroupStack;
    
    std::vector<RenderQueue> _renderGroups;

    MeshCommand* _lastBatchedMeshCommand = nullptr;
    std::vector<TrianglesCommand*> _queuedTriangleCommands;

    //for TrianglesCommand
    V3F_C4B_T2F _verts[VBO_SIZE];
    unsigned short _indices[INDEX_VBO_SIZE];
    backend::Buffer* _vertexBuffer = nullptr;
    backend::Buffer* _indexBuffer = nullptr;
    
    backend::CommandBuffer* _commandBuffer = nullptr;
    backend::RenderPassDescriptor _renderPassDescriptor;
    backend::DepthStencilDescriptor _depthStencilDescriptor;

    ClearCommandManager _clearCommandManager;
    std::vector<CallbackCommand*> _cachedClearCommands;

    // Internal structure that has the information for the batches
    struct TriBatchToDraw
    {
        TrianglesCommand* cmd = nullptr;  // needed for the Material
        unsigned int indicesToDraw = 0;
        unsigned int offset = 0;
    };
    // capacity of the array of TriBatches
    int _triBatchesToDrawCapacity = 500;
    // the TriBatches
    TriBatchToDraw* _triBatchesToDraw = nullptr;

//    unsigned int _filledVertex = 0;
//    unsigned int _filledIndex = 0;

    unsigned int _queuedTotalVertexCount = 0;
    unsigned int _queuedTotalIndexCount = 0;
    unsigned int _queuedVertexCount = 0;
    unsigned int _queuedIndexCount = 0;

    // stats
    unsigned int _drawnBatches = 0;
    unsigned int _drawnVertices = 0;
    //the flag for checking whether renderer is rendering
    bool _isRendering = false;
    bool _isDepthTestFor2D = false;
        
    GroupCommandManager* _groupCommandManager = nullptr;

    unsigned int _stencilRef = 0;

    // weak reference
    Texture2D* _colorAttachment = nullptr;
    Texture2D* _depthAttachment = nullptr;
    Texture2D* _stencilAttachment = nullptr;
    Color4F _clearColor = Color4F::BLACK;
    ClearFlag _clearFlag;
    RenderTargetFlag _renderTargetFlag = RenderTargetFlag::COLOR;

    struct ScissorState
    {
        ScissorRect rect;
        bool isEnabled = false;
    };
    ScissorState _scissorState;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _cacheTextureListener = nullptr;
#endif
};

NS_CC_END

/**
 end of support group
 @}
 */
