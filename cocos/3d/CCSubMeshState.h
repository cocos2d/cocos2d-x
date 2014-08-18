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

#ifndef __CCSUBMESHSTATE_H__
#define __CCSUBMESHSTATE_H__

#include <string>
#include <vector>

#include "3d/CCBundle3DData.h"
#include "3d/CCAABB.h"

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"

NS_CC_BEGIN

class Texture2D;
class MeshSkin;
class SubMesh;
/** 
 * SubMeshState: visibility and apperence of submesh
 */
class CC_DLL SubMeshState : public Ref
{
    friend class Sprite3D;
public:

    /**create submesh from primitivetype indexformat and indices*/
    static SubMeshState* create();
    
    static SubMeshState* create(const std::string& name);

    /**texture getter and setter*/
    void setTexture(const std::string& texPath);
    void setTexture(Texture2D* tex);
    Texture2D* getTexture() const { return _texture; }
    
    /**visible getter and setter*/
    void setVisible(bool visible);
    bool isVisible() const { return _visible; }
    
    /**skin getter */
    MeshSkin* getSkin() const { return _skin; }
    
    /**sub mesh getter */
    SubMesh* getSubMesh() const { return _subMesh; }
    
    /**name getter */
    const std::string& getName() const { return _name; }

CC_CONSTRUCTOR_ACCESS:
    
    SubMeshState();
    virtual ~SubMeshState();

    /**skin setter*/
    void setSkin(MeshSkin* skin);
    /**submesh setter*/
    void setSubMesh(SubMesh* subMesh);
    /**name setter*/
    void setName(const std::string& name) { _name = name; }
    
    const AABB& getAABB() const { return _aabb; }
    
    void calcuateAABB();
protected:
    Texture2D* _texture;  //texture that submesh is using
    MeshSkin*  _skin;     //skin
    bool       _visible; // is the submesh visible
    
    //since 3.3
    std::string  _name;
    SubMesh*     _subMesh;
    AABB         _aabb;
    std::function<void()> _visibleChanged;
};

NS_CC_END

#endif // __CCSUBMESHSTATE_H__
