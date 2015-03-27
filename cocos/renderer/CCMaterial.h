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
#include <CCVector.h>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderState.h"

NS_CC_BEGIN

class Technique;
class GLProgramState;

/// Material
class CC_DLL Material : public RenderState
{
public:
    /** Creates a Material with a JSON file containing the definition of the material.
     */
    static Material* createWithFilename(const std::string& path);

    /** Creates a Material with a GLProgramState.
     It will only contain one Technique and one Pass.
     Added in order to support legacy code.
     */
    static Material* createWithGLStateProgram(GLProgramState* programState);

    /// returns the material name
    std::string getName() const;

    /** Returns a Technique by its name.
     returns `nullptr` if the Technique can't be found.
     */
    Technique* getTechniqueByName(const std::string& name);

    /** Returns a Technique by index. 
     returns `nullptr` if the index is invalid.
     */
    Technique* getTechniqueByIndex(ssize_t index);

    /** Adds a Technique into the Material */
    void addTechnique(Technique* technique);

    /** Sets the current technique */
    void setTechnique(const std::string& techniqueName);

    /** Returns the number of Techniques in the Material. */
    ssize_t getTechniqueCount() const;

    /** Returns the Technique used by the Material */
    Technique* getTechnique() const;

protected:
    Material();
    ~Material();

    // material name
    std::string _name;

    // array of techniques
    Vector<Technique*> _techniques;
    Technique* _currentTechnique;
};

NS_CC_END


#endif /* defined(__cocos2d_libs__CCMaterial__) */
