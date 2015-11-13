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


#ifndef __CCRENDERCOMMAND_H_
#define __CCRENDERCOMMAND_H_

#include <stdint.h>

#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

/**
@class RenderCommand
@brief
@~english Base class of the `RenderCommand` hierarchy.
*
 The `Renderer` knows how to render `RenderCommands` objects.
 * @~chinese “RenderCommand”类层次结构的基类。
 * 
 * 渲染器的知道如何呈现“RenderCommands”对象。
 */
class CC_DLL RenderCommand
{
public:
    /**
    @~english Enum the type of render command.  
    @~chinese 枚举：渲染命令的类型。
    */
    enum class Type
    {
        /** 
        @~english Reserved type. 
        @~chinese 保留,未知类型。
        */
        UNKNOWN_COMMAND,
        /** 
        @~english Quad command, used for draw quad. 
        @~chinese Quad Command,用于画四边形。
        */
        QUAD_COMMAND,
        /**
        @~english Custom command, used for calling callback for rendering. 
        @~chinese 自定义命令,用于调用回调函数进行渲染。
        */
        CUSTOM_COMMAND,
        /**
        @~english Batch command, used for draw batches in texture atlas. 
        @~chinese 批处理命令,用于批量渲染TextureAtlas。
        */
        BATCH_COMMAND,
        /**
        @~english Group command, which can group command in a tree hierarchy. 
        @~chinese Group command, 可以将渲染命令组织成树形结构。
        */
        GROUP_COMMAND,
        /**
        @~english Mesh command, used to draw 3D meshes. @
        ~chinese 网格命令,用来绘制3d网格。
        */
        MESH_COMMAND,
        /**
        @~english Primitive command, used to draw primitives such as lines, points and triangles. 
        @~chinese Primitive command,用于绘制各种图元,如线,点和三角形。*/
        PRIMITIVE_COMMAND,
        /**
        @~english Triangles command, used to draw triangles. 
        @~chinese Triangles command,用来绘制三角形。
        */
        TRIANGLES_COMMAND
    };

    /**@~english
     Init function, will be called by all the render commands.
     * @~chinese 
     * 初始化函数，每一个渲染命令都会调用。
     @param globalZOrder @~english The global order of command, used for rendercommand sorting.
     * @~chinese 渲染命令的global Z,用于rendercommand排序。
     @param modelViewTransform @~english Modelview matrix when submitting the render command.
     * @~chinese 渲染命令的ModelView矩阵。
     @param flags @~english Flag used to indicate whether the command should be draw at 3D mode or not.
     * @~chinese 用于标示渲染命令是否是采用3D渲染模式。
     */
    void init(float globalZOrder, const Mat4& modelViewTransform, uint32_t flags);
    
    /** 
    @~english Get global Z order.  
    @~chinese 获得Global Z。
    @return 
    @~english the global Z of render command.
    @~chinese 渲染命令的global Z。
    */
    inline float getGlobalOrder() const { return _globalOrder; }

    /** 
    @~english Returns the Command type.  
    @~chinese 返回命令的类型。
    @return
    @~english The type of render command.
    @~chinese 渲染命令类型。
    */
    inline Type getType() const { return _type; }
    
    /** 
    @~english Retruns whether is transparent.  
    @~chinese 是否是透明的物体。
    @return
    @~english The transparent status.
    @~chinese 透明状态。
    */
    inline bool isTransparent() const { return _isTransparent; }
    
    /** 
    @~english Set transparent flag.  
    @~chinese 设置透明的标示。
    @param isTransparent
    @~english The transparent status.
    @~chinese 透明状态。
    */
    inline void setTransparent(bool isTransparent) { _isTransparent = isTransparent; }
    /**@~english
     Get skip batching status, if a rendering is skip batching, it will be forced to be rendering separately.
     * @~chinese 
     * 取得Skip Batching状态,该状态下的命令会单独进行一次渲染。
     @return 
     @~english the Skip Batching status.
     @~chinese Skip Batching的状态。
     */
    inline bool isSkipBatching() const { return _skipBatching; }
    /**
    @~english Set skip batching. 
    @~chinese 设置Skip Batching 状态。
    @param value
    @~english the skip batching status.
    @~chinese skip batching 的状态。
    */
    inline void setSkipBatching(bool value) { _skipBatching = value; }
    /**
    @~english Whether the command should be rendered at 3D mode. 
    @~chinese 命令是否是3d渲染模式。
    @return
    @~english the 3D mode status.
    @~chinese 3D渲染模式。
    */
    inline bool is3D() const { return _is3D; }
    /**
    @~english Set the command rendered in 3D mode or not. 
    @~chinese 设置3d渲染模式。
    @param value
    @~english the 3D model status.
    @~chinese 3D渲染模式的状态。
    */
    inline void set3D(bool value) { _is3D = value; }
    /**
    @~english Get the depth by current model view matrix. 
    @~chinese 得到在目前的模型视图矩阵下的深度。
    @return
    @~english the depth value.
    @~chinese 深度值。
    */
    inline float getDepth() const { return _depth; }
    
protected:
    /**Constructor.*/
    RenderCommand();
    /**Destructor.*/
    virtual ~RenderCommand();
    //used for debug but it is not implemented.
    void printID();

    /**Type used in order to avoid dynamic cast, faster.*/
    Type _type;

    /**Commands are sort by global Z order.*/
    float _globalOrder;
    
    /**Transparent flag.*/
    bool  _isTransparent;
    
    /**
     QuadCommand and TrianglesCommand could be auto batched if there material ID is the same, however, if
     a command is skip batching, it would be forced to draw in a separate function call, and break the batch.
     */
    bool _skipBatching;
    
    /**Is the command been rendered on 3D pass.*/
    bool _is3D;
    
    /**Depth from the model view matrix.*/
    float _depth;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif //__CCRENDERCOMMAND_H_
