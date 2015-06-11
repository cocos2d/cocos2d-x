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

#ifndef __cocos2d_libs__CCMaterial__
#define __cocos2d_libs__CCMaterial__

#include <string>

#include "renderer/CCRenderState.h"
#include "renderer/CCTechnique.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Mat4.h"
#include "platform/CCPlatformMacros.h"


NS_CC_BEGIN

class Technique;
class Pass;
class GLProgramState;
class Node;
class Properties;

/**
 * @addtogroup support
 * @{
 */

/**
 * @class Material
 * @brief
 * @~english
 * Material defines the apperance of the objects. It contains shaders, uniform values, and OpenGL states. Material can be create from files.
 * @~chinese 材质定义了物体的外观，它包含使用的shader，uniform的值以及OpenGL状态。材质可以从文件创建。
 */
class CC_DLL Material : public RenderState
{
    friend class Node;
    friend class Technique;
    friend class Pass;
    friend class MeshCommand;
    friend class Renderer;
    friend class Mesh;

public:
    /**
     * @~english Creates a Material using the data from the Properties object defined at the specified URL,
     * where the URL is of the format "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     * @~chinese 从定义很多属性的材质文件创建一个材质，材质文件的格式是这样的，"<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     * @param path @~english The URL pointing to the Properties object defining the material. @~chinese 材质文件的路径。
     *
     * @return @~english A new Material or NULL if there was an error. @~chinese 新创建的材质，如果失败返回空指针。
     */
    static Material* createWithFilename(const std::string& path);

    /** @~english Creates a Material with a GLProgramState.
     It will only contain one Technique and one Pass.
     Added in order to support legacy code.
     * @~chinese 用GLProgramState创建新的材质。新创建的材质只包含一个Technique和一个Pass，这个主要是为了跟之前的版本兼容。
     * @param programState @~english programState used to create material. @~chinese 用来创建材质的programState。
     */
    static Material* createWithGLStateProgram(GLProgramState* programState);

    /**
     * @~english Creates a material from the specified properties object.
     * @~chinese 用Properties对象来创建材质。
     * @param materialProperties @~english The properties object defining the
     *      material (must have namespace equal to 'material'). @~chinese 属性对象，定义了材质（名字空间中必须有‘material’）。
     * @return @~english A new Material. @~chinese 新创建的材质。
     */
    static Material* createWithProperties(Properties* materialProperties);

    /**
     * @~english Gets the material name
     * @~chinese 获取材质名称。
     * @return @~english Material name. @~chinese 材质名称。
     */
    std::string getName() const;
    /**
     * @~english Sets the material name
     * @~chinese 设置材质名称。
     * @param name @~english Material name. @~chinese 材质名称。
     */
    void setName(const std::string& name);

    /** @~english Gets a Technique by its name.
     * @~chinese 通过名称获取一个Technique。
     * @param name @~english Technique name. @~chinese Technique名称。
     * @return @~english `nullptr` if the Technique can't be found. @~chinese 找到的Technique，否则返回空指针。
     */
    Technique* getTechniqueByName(const std::string& name);

    /** @~english Gets a Technique by index.
     * @~chinese 通过索引获取一个Technique。
     * @param index @~english technique index. @~chinese Technique索引。
     * @return @~english `nullptr` if the index is invalid. @~chinese 找到的Technique，索引无效时返回空指针。
     */
    Technique* getTechniqueByIndex(ssize_t index);

    /** @~english Gets the Technique used by the Material.
     * @~chinese 获取Material在使用的Technique。
     * @return @~english Technique used by material. @~chinese 使用的Technique。
     */
    Technique* getTechnique() const;

    /** @~english Gets the list of Techniques.
     * @~chinese 获取Technique列表。
     * @return @~english Technique list. @~chinese Technique列表。
     */
    const Vector<Technique*>& getTechniques() const;

    /** @~english Gets the number of Techniques in the Material.
     * @~chinese 获取Technique的数目。
     * @return @~english Technique number. @~chinese Technique数目。
     */
    ssize_t getTechniqueCount() const;

    /** @~english Adds a Technique into the Material.
     * @~chinese 添加一个Technique。
     * @param technique @~english Technique being added. @~chinese 被添加的Technique。
     */
    void addTechnique(Technique* technique);

    /** @~english Sets the current technique.
     * @~chinese 设置当前使用的Technique。
     * @param techniqueName @~english Technique name being current technique. @~chinese 设置为当前Technique的名称。
     */
    void setTechnique(const std::string& techniqueName);

    /** @~english Clone (deep-copy) of the material.
     * @~chinese 拷贝材质（深度拷贝）。
     * @return @~english Copy of material. @~chinese 材质的拷贝。
     */
    Material* clone() const;

protected:
    Material();
    ~Material();
    bool initWithGLProgramState(GLProgramState* state);
    bool initWithFile(const std::string& file);
    bool initWithProperties(Properties* materialProperties);

    void setTarget(Node* target);

    bool parseProperties(Properties* properties);
    bool parseTechnique(Properties* properties);
    bool parsePass(Technique* technique, Properties* properties);
    bool parseSampler(Pass* pass, Properties* properties);
    bool parseShader(Pass* pass, Properties* properties);
    bool parseUniform(GLProgramState* programState, Properties* properties, const char* uniformName);
    bool parseRenderState(RenderState* renderState, Properties* properties);


    // material name
    std::string _name;

    // array of techniques
    Vector<Technique*> _techniques;

    // weak pointer since it is being help by _techniques
    Technique* _currentTechnique;

    // weak reference
    Node* _target;
};

/**
 end of support group
 @}
 */

NS_CC_END


#endif /* defined(__cocos2d_libs__CCMaterial__) */
