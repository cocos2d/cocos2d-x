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

/// Material
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
     * Creates a Material using the data from the Properties object defined at the specified URL,
     * where the URL is of the format "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     *
     * @param url The URL pointing to the Properties object defining the material.
     *
     * @return A new Material or NULL if there was an error.
     */
    static Material* createWithFilename(const std::string& path);

    /** Creates a Material with a GLProgramState.
     It will only contain one Technique and one Pass.
     Added in order to support legacy code.
     */
    static Material* createWithGLStateProgram(GLProgramState* programState);

    /**
     * Creates a material from the specified properties object.
     *
     * @param materialProperties The properties object defining the
     *      material (must have namespace equal to 'material').
     * @return A new Material.
     */
    static Material* createWithProperties(Properties* materialProperties);

    /// returns the material name
    std::string getName() const;
    /// sets the material name
    void setName(const std::string& name);

    /** Returns a Technique by its name.
     returns `nullptr` if the Technique can't be found.
     */
    Technique* getTechniqueByName(const std::string& name);

    /** Returns a Technique by index. 
     returns `nullptr` if the index is invalid.
     */
    Technique* getTechniqueByIndex(ssize_t index);

    /** Returns the Technique used by the Material */
    Technique* getTechnique() const;

    /** Returns the list of Techniques */
    const Vector<Technique*>& getTechniques() const;

    /** Returns the number of Techniques in the Material. */
    ssize_t getTechniqueCount() const;

    /** Adds a Technique into the Material */
    void addTechnique(Technique* technique);

    /** Sets the current technique */
    void setTechnique(const std::string& techniqueName);

    /** returns a clone (deep-copy) of the material */
    virtual Material* clone() const;

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
    bool parseShader(Pass* pass, Properties* properties);
    bool parseSampler(GLProgramState* glProgramState, Properties* properties);
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

NS_CC_END


#endif /* defined(__cocos2d_libs__CCMaterial__) */
