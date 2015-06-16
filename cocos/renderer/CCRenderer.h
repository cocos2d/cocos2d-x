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

#include <vector>
#include <stack>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "platform/CCGL.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class EventListenerCustom;
class QuadCommand;
class TrianglesCommand;
class MeshCommand;

/** 
@class RenderQueue
@brief @~english Class that knows how to sort `RenderCommand` objects.
 Since the commands that have `z == 0` are "pushed back" in
 the correct order, the only `RenderCommand` objects that need to be sorted,
 are the ones that have `z < 0` and `z > 0`.
 @~chinese 用于对渲染命令进行排序的类
 由于z=0的渲染命令会通过正确的顺序插入到末尾，只有z不等于0的渲染命令需要排序
*/
class RenderQueue {
public:
    /**@~english
    RenderCommand will be divided into Queue Groups.
    @~chinese 
    RenderCommand将分为队列组。
    */
    enum QUEUE_GROUP
    {
        /**
        @~english Objects with globalZ smaller than 0. 
        @~chinese globalZ小于0的对象。*/
        GLOBALZ_NEG = 0,
        /**
        @~english Opaque 3D objects with 0 globalZ. 
        @~chinese globalZ等于0的不透明3d对象。*/
        OPAQUE_3D = 1,
        /**
        @~english Transparent 3D objects with 0 globalZ. 
        @~chinese globalZ等于0的透明3d对象。*/
        TRANSPARENT_3D = 2,
        /**
        @~english 2D objects with 0 globalZ. 
        @~chinese globalZ等于0的2d对象。*/
        GLOBALZ_ZERO = 3,
        /**
        @~english Objects with globalZ bigger than 0. 
        @~chinese globalZ大于0的对象。*/
        GLOBALZ_POS = 4,
        QUEUE_COUNT = 5,
    };

public:
    /**
    @~english Constructor. 
    @~chinese 构造函数。
    */
    RenderQueue();
    /**
    @~english Push a renderCommand into current renderqueue. 
    @~chinese 将渲染命令插入到当前渲染队列末尾。
    @param command @~english The command to be pushed in to renderqueue
    @~chinese 待插入渲染队列的命令。
    */
    void push_back(RenderCommand* command);
    /**
    @~english Return the number of render commands. 
    @~chinese 得到渲染命令的数量。
    @return @~english The number of render commands @~chinese 渲染命令个数
    */
    ssize_t size() const;
    /**
    @~english Sort the render commands. 
    @~chinese 排序渲染命令。
    */
    void sort();
    /**
    @~english Treat sorted commands as an array, access them one by one. 
    @~chinese 将排序后的渲染命令当作一个数组，逐个访问
    @param index @~english array index for commands
    @~chinese 索引值
    @return @~english the RenderCommand in the given index
    @~chinese 给定位置的渲染命令

    */
    RenderCommand* operator[](ssize_t index) const;
    /**
    @~english Clear all rendered commands. 
    @~chinese 清除所有渲染命令。
    */
    void clear();
    /**
    @~english Realloc command queues and reserve with given size. 
    Note: this clears any existing commands. 
    @~chinese 按照指定大小重新分配渲染队列。注意:这个清除任何现有的命令。
    @param reserveSize @~english max size for command queue
    @~chinese 命令队列的最大容量。
    */
    void realloc(size_t reserveSize);
    /**
    @~english Get a sub group of the render queue. 
    @~chinese 得到渲染子队列
    @param group @~english group ID for the sub queque
    @~chinese 子渲染队列的组ID
    @return @~english render command array
    @~chinese 一组渲染命令
    */
    inline std::vector<RenderCommand*>& getSubQueue(QUEUE_GROUP group) { return _commands[group]; }
    /**
    @~english Get the number of render commands contained in a subqueue. 
    @~chinese 得到渲染子队列中的渲染命令数量。
    @param group @~english group ID for the sub queque
    @~chinese 子渲染队列的组ID
    @return @~english the number of command in sub queque
    @~chinese 子渲染队列的渲染命令数量。
    */
    inline ssize_t getSubQueueSize(QUEUE_GROUP group) const { return _commands[group].size();}

    /**
    @~english Save the current DepthState, CullState, DepthWriteState render state. 
    @~chinese 保存当前DepthState、CullState DepthWriteState状态。
    */
    void saveRenderState();
    /**
    @~english Restore the saved DepthState, CullState, DepthWriteState render state. 
    @~chinese 恢复保存的DepthState、CullState DepthWriteState状态。*/
    void restoreRenderState();
    
protected:
    /**
    @~english The commands in the render queue. 
    @~chinese 渲染队列中的命令。*/
    std::vector<RenderCommand*> _commands[QUEUE_COUNT];
    
    /**
    @~english Cull state. 
    @~chinese Cull状态。
    */
    bool _isCullEnabled;
    /**
    @~english Depth test enable state. 
    @~chinese 深度测试状态。
    */
    bool _isDepthEnabled;
    /**
    @~english Depth buffer write state. 
    @~chinese 深度缓冲写状态。
    */
    GLboolean _isDepthWrite;
};

//the struct is not used outside.
struct RenderStackElement
{
    int renderQueueID;
    ssize_t currentIndex;
};

class GroupCommandManager;

/* 
@class Renderer
@brief @~english Class responsible for the rendering in.

Whenever possible prefer to use `QuadCommand` objects since the renderer will automatically batch them.
@~chinese 负责渲染的类。 
由于可以进行batch渲染，该类更擅长处理QuadCommand。
*/
class CC_DLL Renderer
{
public:
    /**
    @~english The max number of vertices in a vertex buffer object. 
    @~chinese 顶点缓冲区的最大顶点个数。
    */
    static const int VBO_SIZE = 65536;
    /**
    @~english The max numer of indices in a index buffer. 
    @~chinese 索引缓冲区的最大索引个数。
    */
    static const int INDEX_VBO_SIZE = VBO_SIZE * 6 / 4;
    /**
    @~english The rendercommands which can be batched will be saved into a list, this is the reversed size of this list. 
    @~chinese 可以batch的渲染命令被放到一个队列中，这是这个队列的大小。
    */
    static const int BATCH_QUADCOMMAND_RESEVER_SIZE = 64;
    /**
    @~english Reserved for material id, which means that the command could not be batched. 
    @~chinese 不能batch的材质ID。
    */
    static const int MATERIAL_ID_DO_NOT_BATCH = 0;
    /**
    @~english Constructor. 
    @~chinese 构造函数。
    */
    Renderer();
    /**
    @~english Destructor. 
    @~chinese 析构函数。
    */
    ~Renderer();

    //TODO: manage GLView inside Render itself
    void initGLView();

    /** 
    @~english Adds a `RenderComamnd` into the renderer  
    @~chinese 向renderer中添加一个RenderComamnd。
    @param command @~english render command to be insert
    @~chinese 待插入的渲染命令。
    */
    void addCommand(RenderCommand* command);

    /** 
    @~english Adds a `RenderComamnd` into the renderer specifying a particular render queue ID  
    @~chinese 向指定ID的渲染队列中插入RenderComamnd。
    @param command @~english render command to be insert
    @~chinese 待插入的渲染命令。
    @param renderQueue @~english the queue id the command queue
    @~chinese 命令队列的id。
    */
    void addCommand(RenderCommand* command, int renderQueue);

    /** 
    @~english Pushes a group into the render queue  
    @~chinese 渲染队列入栈。
    @param renderQueueID @~english the queue id the command queue
    @~chinese 命令队列的id。
    */
    void pushGroup(int renderQueueID);

    /** 
    @~english Pops a group from the render queue  
    @~chinese 渲染队列出栈。
    */
    void popGroup();

    /** 
    @~english Creates a render queue and returns its Id  
    @~chinese 创建一个渲染队列,并返回它的Id
    @return @~english the id of newly created render queue.
    @~chinese 新创建的渲染队列id。
    */
    int createRenderQueue();

    /** 
    @~english Renders into the GLView all the queued `RenderCommand` objects  
    @~chinese 执行所有保存的渲染命令，将其渲染到GLView上。
    */
    void render();

    /** 
    @~english Cleans all `RenderCommand`s in the queue  
    @~chinese 清理队列中所有的RenderCommand。
    */
    void clean();

    /** 
    @~english Clear GL buffer and screen  
    @~chinese 清晰的GL缓冲和屏幕。
    */
    void clear();

    /** 
    @~english set color for clear screen  
    @~chinese 设置屏幕清空的颜色。
    @param clearColor @~english the clear color.
    @~chinese 清空的颜色。
    */
    void setClearColor(const Color4F& clearColor);
    /* 
    @~english returns the number of drawn batches in the last frame  
    @~chinese 返回统计数据：渲染的batch次数。
    @return @~english the number of draw batch.
    @~chinese batch绘制的次数。
    */
    ssize_t getDrawnBatches() const { return _drawnBatches; }
    /* 
    @~english RenderCommands (except) QuadCommand should update this value  
    @~chinese 除了QuadCommand，其他渲染命令应该更新渲染batch这个统计数据值
    @param number @~english the added number of draw batch
    @~chinese 增加的batch绘制的数目。
    */
    void addDrawnBatches(ssize_t number) { _drawnBatches += number; };
    /* 
    @~english returns the number of drawn triangles in the last frame  
    @~chinese 返回统计数据：绘制的三角形数量。
    @return @~english the number of drawn triangles
    @~chinese 绘制的三角形数目。
    */
    ssize_t getDrawnVertices() const { return _drawnVertices; }
    /* 
    @~english RenderCommands (except) QuadCommand should update this value  
    @~chinese 除了QuadCommand，其他渲染命令应该更新渲染的顶点个数这个统计数据值。
    @param number @~english the added number of draw vertices
    @~chinese 增加的绘制顶点的数目。
    */
    void addDrawnVertices(ssize_t number) { _drawnVertices += number; };
    /* 
    @~english clear draw stats  
    @~chinese 清空渲染统计状态。
    */
    void clearDrawStats() { _drawnBatches = _drawnVertices = 0; }

    /**@~english
     * Enable/Disable depth test
     * For 3D object depth test is enabled by default and can not be changed
     * For 2D object depth test is disabled by default
     * @~chinese 
     * 启用和不启用深度测试
     * 3d对象默认会启用深度测试,不能改变
     * 2d对象默认不启用深度测试。

     @param enable @~english depth test enabled or not.
     @~chinese 是否启用深度测试。
     */
    void setDepthTest(bool enable);
    
    //This will not be used outside.
    inline GroupCommandManager* getGroupCommandManager() const { return _groupCommandManager; };

    /** 
    @~english returns whether or not a rectangle is visible or not.
    @~chinese 判断一个长方形是否可见。
    @param transform @~english matrix for the rect. @~chinese 给定物体的变换矩阵。
    @param size @~english the size of rect. @~chinese 长方形的大小。
    */
    bool checkVisibility(const Mat4& transform, const Size& size);

protected:

    //Setup VBO or VAO based on OpenGL extensions
    void setupBuffer();
    void setupVBOAndVAO();
    void setupVBO();
    void mapBuffers();
    void drawBatchedTriangles();
    void drawBatchedQuads();

    //Draw the previews queued quads and flush previous context
    void flush();
    
    void flush2D();
    
    void flush3D();

    void flushQuads();
    void flushTriangles();

    void processRenderCommand(RenderCommand* command);
    void visitRenderQueue(RenderQueue& queue);

    void fillVerticesAndIndices(const TrianglesCommand* cmd);
    void fillQuads(const QuadCommand* cmd);

    /* clear color set outside be used in setGLDefaultValues() */
    Color4F _clearColor;

    std::stack<int> _commandGroupStack;
    
    std::vector<RenderQueue> _renderGroups;

    uint32_t _lastMaterialID;

    MeshCommand*              _lastBatchedMeshCommand;
    std::vector<TrianglesCommand*> _batchedCommands;
    std::vector<QuadCommand*> _batchQuadCommands;

    //for TrianglesCommand
    V3F_C4B_T2F _verts[VBO_SIZE];
    GLushort _indices[INDEX_VBO_SIZE];
    GLuint _buffersVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _filledVertex;
    int _filledIndex;
    
    //for QuadCommand
    V3F_C4B_T2F _quadVerts[VBO_SIZE];
    GLushort _quadIndices[INDEX_VBO_SIZE];
    GLuint _quadVAO;
    GLuint _quadbuffersVBO[2]; //0: vertex  1: indices
    int _numberQuads;
    
    bool _glViewAssigned;

    // stats
    ssize_t _drawnBatches;
    ssize_t _drawnVertices;
    //the flag for checking whether renderer is rendering
    bool _isRendering;
    
    bool _isDepthTestFor2D;
    
    GroupCommandManager* _groupCommandManager;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _cacheTextureListener;
#endif
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //__CC_RENDERER_H_
