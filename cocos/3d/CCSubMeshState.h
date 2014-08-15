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

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"

NS_CC_BEGIN

class Texture2D;
class MeshSkin;
/** 
 * SubMeshState: visibility and apperence of submesh
 */
class CC_DLL SubMeshState : public Ref
{
public:

    /**create submesh from primitivetype indexformat and indices*/
    static SubMeshState* create();

    /**texture getter and setter*/
    void setTexture(Texture2D* tex);
    Texture2D* getTexture() const { return _texture; }
    
    /**visible getter and setter*/
    void setVisible(bool visible) { _visible = visible; }
    bool isVisible() const { return _visible; }
    
    /**skin getter and setter*/
    void setSkin(MeshSkin* skin);
    MeshSkin* getSkin() const { return _skin; }

CC_CONSTRUCTOR_ACCESS:
    
    SubMeshState();
    virtual ~SubMeshState();

protected:
    Texture2D* _texture;  //texture that submesh is using
    MeshSkin*  _skin;     //skin
    bool       _visible; // is the submesh visible
};

NS_CC_END

#endif // __CCSUBMESHSTATE_H__
