/**
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2015 Chukong Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 */

#ifndef CC_VERTEXATTRIBUTEBINDING_H_
#define CC_VERTEXATTRIBUTEBINDING_H_

#include <unordered_map>

#include "base/CCRef.h"
#include "renderer/CCGLProgramState.h"

NS_CC_BEGIN

class MeshIndexData;
class VertexAttribValue;

/**
 * @addtogroup support
 * @{
 */

/**
 * @class VertexAttribBinding
 * @brief
 * @~english
 * Defines a binding between the vertex layout of a Mesh and the vertex
 * input attributes of a vertex shader (Effect).
 *
 * In a perfect world, this class would always be a binding directly between
 * a unique VertexFormat and an Effect, where the VertexFormat is simply the
 * definition of the layout of any anonymous vertex buffer. However, the OpenGL
 * mechanism for setting up these bindings is Vertex Array Objects (VAOs).
 * OpenGL requires a separate VAO per vertex buffer object (VBO), rather than per
 * vertex layout definition. Therefore, although we would like to define this
 * binding between a VertexFormat and Effect, we are specifying the binding
 * between a Mesh and Effect to satisfy the OpenGL requirement of one VAO per VBO.
 *
 * Note that this class still does provide a binding between a VertexFormat
 * and an Effect, however this binding is actually a client-side binding and 
 * should only be used when writing custom code that use client-side vertex
 * arrays, since it is slower than the server-side VAOs used by OpenGL
 * (when creating a VertexAttribBinding between a Mesh and Effect).
 * @~chinese 该类定义一个Mesh的顶点和vertex shader之间的绑定关系。理想情况下，这个类应该定义的绑定关系应该只与顶点格式布局和shader相关，而不是与vertex buffer也有关联，这样会阻止该类的通用性。但是OpenGL设置顶点绑定的机制采用的是VAO。对于每个顶点buffer OpenGL需要一个VAO，而不仅仅是顶点格式的布局。因此，尽管我们想定义一个顶点格式和shader的绑定关系，但由于OpenGL的要求，实际上我们定义的是一个Mesh和shader之间的绑定。
 * 
 */
class VertexAttribBinding : public Ref
{
public:

    /**
     * @~english Creates a new VertexAttribBinding between the given MeshVertexData and GLProgramState.
     *
     * If a VertexAttribBinding matching the specified MeshVertexData and GLProgramState already
     * exists, it will be returned. Otherwise, a new VertexAttribBinding will
     * be returned. If OpenGL VAOs are enabled, the a new VAO will be created and
     * stored in the returned VertexAttribBinding, otherwise a client-side
     * array of vertex attribute bindings will be stored.
     * @~chinese 用MeshVertexData和GLProgramState创建一个顶点属性绑定。 如果与给定的MeshVertexData和GLProgramState对应的顶点属性绑定已经存在，直接返回该顶点绑定，否则创建一个新的顶点属性绑定。如果硬件支持VAO，新创建的顶点属性绑定中将创建一个VAO，否则在绘制时采用软件模式使能顶点属性。
     * @param mesh @~english The mesh. @~chinese 用来绑定的网格。
     * @param effect @~english The effect. @~chinese GLProgrameState对象。
     * 
     * @return @~english A VertexAttribBinding for the requested parameters. @~chinese 新创建的或者根据参数索引到的顶点属性绑定对象。
     */
    static VertexAttribBinding* create(MeshIndexData* meshIndexData, GLProgramState* glProgramState);

    /**
     * @~english Binds this vertex array object.
     * @~chinese 绑定顶点数组对象。
     */
    void bind();

    /**
     * @~english Unbinds this vertex array object.
     * @~chinese 解除顶点属性对象的绑定。
     */
    void unbind();

    /**
     * @~english Returns the vertex attrib flags
     * @~chinese 返回顶点属性标记
     * @return @~english verteix attributes flag. @~chinese 顶点属性标记。
     */
    uint32_t getVertexAttribsFlags() const;


private:

    bool init(MeshIndexData* meshIndexData, GLProgramState* glProgramState);

    /**
     * Constructor.
     */
    VertexAttribBinding();

    /**
     * Destructor.
     */
    ~VertexAttribBinding();

    /**
     * Hidden copy assignment operator.
     */
    VertexAttribBinding& operator=(const VertexAttribBinding&);

    void setVertexAttribPointer(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer);
    VertexAttribValue* getVertexAttribValue(const std::string &name);
    void parseAttributes();


    GLuint _handle;

    MeshIndexData* _meshIndexData;
    GLProgramState* _glProgramState;

    std::unordered_map<std::string, VertexAttribValue> _attributes;
    uint32_t _vertexAttribsFlags;
};

/// @cond
extern std::string CC_DLL s_attributeNames[];//attribute names array
/// @endcond

/**
 end of support group
 @}
 */

NS_CC_END

#endif // CC_VERTEXATTRIBUTEBINDING_H_
