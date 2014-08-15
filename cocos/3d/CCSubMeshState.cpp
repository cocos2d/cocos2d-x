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

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "3d/CCSubMeshState.h"
#include "3d/CCMeshSkin.h"
#include "3d/CCSubMesh.h"

#include "base/ccMacros.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCTextureCache.h"


using namespace std;

NS_CC_BEGIN

SubMeshState::SubMeshState()
: _visible(true)
, _texture(nullptr)
, _skin(nullptr)
, _subMesh(nullptr)
{
    
}
SubMeshState::~SubMeshState()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_skin);
    CC_SAFE_RELEASE(_subMesh);
}

SubMeshState* SubMeshState::create()
{
    auto state = new SubMeshState();
    state->autorelease();
    
    return state;
}

SubMeshState* SubMeshState::create(const std::string& name)
{
    auto state = new SubMeshState();
    state->autorelease();
    
    state->_name = name;
    
    return state;
}

void SubMeshState::setTexture(const std::string& texPath)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texPath);
    setTexture(tex);
}

void SubMeshState::setTexture(Texture2D* tex)
{
    if (tex != _texture)
    {
        CC_SAFE_RETAIN(tex);
        CC_SAFE_RELEASE(_texture);
        _texture = tex;
    }
}

void SubMeshState::setSkin(MeshSkin* skin)
{
    if (_skin != skin)
    {
        CC_SAFE_RETAIN(skin);
        CC_SAFE_RELEASE(_skin);
        _skin = skin;
    }
}

void SubMeshState::setSubMesh(SubMesh* subMesh)
{
    if (_subMesh != subMesh)
    {
        CC_SAFE_RETAIN(subMesh);
        CC_SAFE_RELEASE(_subMesh);
        _subMesh = subMesh;
    }
}

NS_CC_END
