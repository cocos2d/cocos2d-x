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

#include "CCRenderState.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

RenderState* RenderState::create(RenderState* parent)
{
    return new (std::nothrow) RenderState(parent);
}

RenderState::RenderState()
: _parent(nullptr)
, _blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _textures()
, _hash(0)
, _hashDirty(true)
{
}

RenderState::RenderState(RenderState *parent)
{
    _parent = parent;
    CC_SAFE_RETAIN(parent);
}

RenderState::~RenderState()
{
    CC_SAFE_RELEASE(_parent);
}

std::string RenderState::getName() const
{
    return _name;
}

//
void RenderState::setBlendFunc(const BlendFunc& blendFunc)
{
    if (_blendFunc != blendFunc) {
        _hashDirty = true;

        _blendFunc = blendFunc;
    }
}

BlendFunc RenderState::getBlendFunc() const
{
    return _blendFunc;
}

const Vector<Texture2D*>& RenderState::getTextures() const
{
    return _textures;
}

void RenderState::setTexture(Texture2D* texture)
{
    if (_textures.size() > 0)
        _textures.replace(0, texture);
    else
        _textures.pushBack(texture);
}

Texture2D* RenderState::getTexture() const
{
    if (_textures.size() > 0)
        return _textures.at(0);
    return nullptr;
}

NS_CC_END