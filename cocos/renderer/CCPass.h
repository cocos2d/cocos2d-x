/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#ifndef __cocos2d_libs__CCPass__
#define __cocos2d_libs__CCPass__

#include <stdio.h>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderState.h"

NS_CC_BEGIN

class GLProgramState;
class Technique;
class Node;
class VertexAttribBinding;

/**
 * @addtogroup support
 * @{
 */

/**
 * @class Pass
 * @brief
 * @~english
 * Material contains one or more techniques. Each technique can contains one or more passes. And material can active one technique for drawing. Pass contains vertex attribute binding and GLProgramState. The Passes in the same Technique are applied one by one when drawing an object.
 * @~chinese 材质包含一个或者多个Technique，每个Technique可以包含一个或者多个Pass。Pass是对顶点属性和GLProgramState的封装，绘制物体时，材质在使用时可以激活一个。Technique中的多个Pass一个接一个的应用。
 */

class CC_DLL Pass : public RenderState
{
    friend class Material;

public:
    
    /**
     * @~english Creates a Pass with a GLProgramState.
     * @~chinese 用GLProgramState创建一个Pass。
     * @param parent @~english Technique who owns this Pass. @~chinese 拥有这个Pass的Technique。
     * @param programState @~english GLProgramState used to create Pass. @~chinese 用来创建Pass的GLProgramState。
     * @return @~english Created Pass. @~chinese 新创建的Pass。
     */
    static Pass* createWithGLProgramState(Technique* parent, GLProgramState* programState);

    /**
     * @~english Creates a Pass.
     * @~chinese 创建一个Pass。
     * @param parent @~english Technique who owns this Pass. @~chinese 拥有这个Pass的Technique。
     * @return @~english Created Pass. @~chinese 新创建的Pass。
     */
    static Pass* create(Technique* parent);

    /**
     * @~english Gets the GLProgramState.
     * @~chinese 获取GLProgramState。
     * @return @~english GLProgramState in the Pass. @~chinese Pass中的GLProgramState。
     */
    GLProgramState* getGLProgramState() const;

    /**
     * @~english Binds the GLProgramState and the RenderState. This method must be called before call the actuall draw call.
     * @~chinese 绑定GLProgramState和渲染状态，这个方法必须在实际绘制之前调用。
     * @param modelView @~english Model view matrix which is going to pass to shader. @~chinese 传染到shader中的模型视图矩阵。
     */
    void bind(const Mat4& modelView);
    /**
     * @~english Binds the GLProgramState and the RenderState. This method must be called before call the actuall draw call.
     * @~chinese 绑定GLProgramState和渲染状态，这个方法必须在实际绘制之前调用。
     * @param modelView @~english Model view matrix which is going to pass to shader. @~chinese 传染到shader中的模型视图矩阵。
     * @param bindAttributes @~english binding vertex attribute ? @~chinese 是否绑定顶点属性？
     */
    void bind(const Mat4& modelView, bool bindAttributes);
    
    /**
     * @~english Unbinds the Pass. This method must be called AFTER calling the actuall draw call.
     * @~chinese 解除该Pass的绑定，这个方法必须在实际绘制之后调用。
     */
    void unbind();

    /**
     * @~english Sets a vertex attribute binding for this pass. When a mesh binding is set, the VertexAttribBinding will be automatically bound when the bind() method is called for the pass.
     * @~chinese 设置该Pass的顶点绑定属性。 当顶点绑定属性设置后调用bind()函数时会自动绑定设置的顶点属性。
     * @param binding @~english The VertexAttribBinding to set (or NULL to remove an existing binding). @~chinese 待设置的顶点绑定属性，当参数为NULL时移除已经绑定的顶点属性。
     */
    void setVertexAttribBinding(VertexAttribBinding* binding);

    /**
     * @~english Returns the vertex attribute binding for this pass.
     * @~chinese 获取顶点绑定属性。
     * @return @~english The vertex attribute binding for this pass. @~chinese Pass中的顶点绑定属性。
     */
    VertexAttribBinding* getVertexAttributeBinding() const;

    /**
     * @~english Get Hash code of the Pass.
     * @~chinese 获取该Pass的哈希码。
     * @return @~english Hash code of this pass. @~chinese Pass的哈希码。
     */
    uint32_t getHash() const;

    /**
     * Returns a clone (deep-copy) of this instance */
    /**
     * @~english Returns a clone (deep-copy) of this instance.
     * @~chinese 获取Pass的一个深度拷贝。
     * @return @~english Copy of this pass. @~chinese Pass的拷贝。
     */
    Pass* clone() const;

protected:
    Pass();
    ~Pass();
    bool init(Technique* parent);
    bool initWithGLProgramState(Technique* parent, GLProgramState *glProgramState);

    void setGLProgramState(GLProgramState* glProgramState);
    Node* getTarget() const;

    GLProgramState* _glProgramState;
    VertexAttribBinding* _vertexAttribBinding;
};

/**
 end of support group
 @}
 */

NS_CC_END



#endif /* defined(__cocos2d_libs__CCPass__) */
