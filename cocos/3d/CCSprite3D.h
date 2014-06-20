/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCSPRITE3D_H__
#define __CCSPRITE3D_H__

#include <vector>

#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "renderer/CCMeshCommand.h"

NS_CC_BEGIN

class GLProgramState;
class Mesh;
class Texture2D;
class MeshSkin;

/** Sprite3D: A sprite can be loaded from 3D model files, .obj, .c3t, .c3b, then can be drawed as sprite */
class Sprite3D : public Node, public BlendProtocol
{
public:
    /** creates a Sprite3D*/
    static Sprite3D* create(const std::string &modelPath);

    // creates a Sprite3D. It only supports one texture, and overrides the internal texture with 'texturePath'
    static Sprite3D* create(const std::string &modelPath, const std::string &texturePath);
    
    /**set texture*/
    void setTexture(const std::string& texFile);
    void setTexture(Texture2D* texture);

    /**get mesh*/
    Mesh* getMesh() const { return _mesh; }
    
    /**get skin*/
    MeshSkin* getSkin() const { return _skin; }

    // overrides
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    virtual const BlendFunc &getBlendFunc() const override;

CC_CONSTRUCTOR_ACCESS:
    
    Sprite3D();
    virtual ~Sprite3D();
    bool initWithFile(const std::string &path);
    
    /**.mtl file should at the same directory with the same name if exist*/
    bool loadFromObj(const std::string& path);
    
    /**load from .c3b or .c3t*/
    bool loadFromC3x(const std::string& path);

    /**draw*/
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    /**get default shader*/
    virtual GLProgram* getDefaultGLProgram(bool textured = true);
    
    /**generate default GLProgramState*/
    void genGLProgramState();

protected:
    Mesh*              _mesh;//mesh
    MeshSkin*          _skin;//skin
    
    MeshCommand       _meshCommand; //render command
    Texture2D*        _texture;
    BlendFunc         _blend;
};

extern std::string s_attributeNames[];//attribute names array

NS_CC_END
#endif // __SPRITE3D_H_
