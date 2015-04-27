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

#ifndef __cocos2d_libs__CCRenderState__
#define __cocos2d_libs__CCRenderState__

#include <string>
#include <functional>
#include <cstdint>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Texture2D;

class CC_DLL RenderState : public Ref
{
    friend class Material;
    friend class Technique;
    friend class Pass;

public:
    static RenderState* create(RenderState* parent);

    std::string getName() const;

    void setBlendFunc(const BlendFunc& blendFunc);
    BlendFunc getBlendFunc() const;

    const Vector<Texture2D*>& getTextures() const;

    /** Replaces the texture that is at the front of _textures array.
     Added to be backwards compatible.
     */
    void setTexture(Texture2D* texture);

    /** Returns the texture that is at the front of the _textures array.
     Added to be backwards compatible.
     */
    Texture2D* getTexture() const;

protected:
    RenderState();
    RenderState(RenderState* parent);
    ~RenderState();

    // parent, for inheritance
    RenderState* _parent;

    // name, for filtering
    std::string _name;


    mutable uint32_t _hash;
    mutable bool _hashDirty;

    Vector<Texture2D*> _textures;

    BlendFunc _blendFunc;

    // taken from MeshCommand
    bool _cullFaceEnabled;
    GLenum _cullFace;
    bool _depthTestEnabled;
    bool _depthWriteEnabled;
    bool _forceDepthWrite;

    bool _renderStateCullFaceEnabled;
    bool _renderStateDepthTest;
    GLboolean _renderStateDepthWrite;
    GLenum    _renderStateCullFace;

    // TODO: add stencil operations
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCRenderState__) */
