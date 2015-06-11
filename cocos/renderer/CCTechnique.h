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

#ifndef __cocos2d_libs__CCTechnique__
#define __cocos2d_libs__CCTechnique__

#include <string>
#include "renderer/CCRenderState.h"
#include "renderer/CCPass.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Pass;
class GLProgramState;
class Material;

/**
 * @addtogroup support
 * @{
 */

/**
 * @class Technique
 * @brief
 * @~english
 * Material contains one or more techniques. Each technique can contains one or more passes. And material can active one technique for drawing.
 * @~chinese 材质包含一个或者多个Technique，每个Technique可以包含一个或者多个Pass，材质在使用时可以激活一个Technique。
 */
class CC_DLL Technique : public RenderState
{
    friend class Material;
    friend class Renderer;
    friend class Pass;
    friend class MeshCommand;
    friend class Mesh;

public:
    /** @~english Creates a new Technique with a GLProgramState. Method added to support legacy code.
     * @~chinese 用GLProgramState创建一个新的Technique，加入该方法主要为保持旧代码的兼容性。
     * @param parent @~english Material who owns this technique. @~chinese 拥有这个Technique的材质。
     * @param state @~english GLProgramState used to create the technique. @~chinese 用来创建technique的GLProgramState。
     * @return @~english Created Technique. @~chinese 新创建的Technique。
     */
    static Technique* createWithGLProgramState(Material* parent, GLProgramState* state);
    
    /**
     * @~english Create Technique.
     * @~chinese 创建新的Technique。
     * @param parent @~english Material who owns this technique. @~chinese 拥有这个Technique的材质。
     * @return @~english Created Technique. @~chinese 新创建的Technique。
     */
    static Technique* create(Material* parent);

    /** 
     * @~english Adds a new pass to the Technique. Order matters. First added, first rendered
     * @~chinese 添加一个pass, 其中pass的渲染顺序按添加顺序。
     * @param pass @~english Added pass. @~chinese 待添加的pass。
     */
    void addPass(Pass* pass);

    /** 
     * @~english Gets the name of the Technique 
     * @~chinese 获取Technique的名称。
     * @return @~english Technique name. @~chinese Technique的名称。
     */
    std::string getName() const;

    /**
     * @~english Gets the Pass at given index.
     * @~chinese 获取给定索引处的Pass。
     * @return @~english Pass at specific index. @~chinese 指定索引处的Pass。
     */
    Pass* getPassByIndex(ssize_t index) const;

    /**
     * @~english Gets the number of Passes in the Technique.
     * @~chinese 获取Technique中Pass的数量。
     * @return @~english Number of Pass. @~chinese Pass的数量。
     */
    ssize_t getPassCount() const;

    /**
     * @~english Gets the list of passes.
     * @~chinese 获取Pass列表。
     * @return @~english List of Pass. @~chinese Pass列表。
     */
    const Vector<Pass*>& getPasses() const;

    /**
     * @~english Gets a new clone of the Technique.
     * @~chinese 获取Technique的拷贝。
     * @return @~english Copy of Technique. @~chinese Techinque的拷贝。
     */
    Technique* clone() const;

protected:
    Technique();
    ~Technique();
    bool init(Material* parent);

    void setName(const std::string& name);

    std::string _name;
    Vector<Pass*> _passes;
};

/**
 end of support group
 @}
 */

NS_CC_END

#endif /* defined(__cocos2d_libs__CCTechnique__) */
