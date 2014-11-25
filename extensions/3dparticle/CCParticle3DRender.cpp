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

#include "CCParticle3DEmitter.h"
#include "3dparticle/CCParticleSystem3D.h"
#include "3dparticle/CCParticle3DRender.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCRenderer.h"
#include "3d/CCSprite3D.h"

NS_CC_BEGIN

Particle3DQuadRender::Particle3DQuadRender()
: _meshCommand(nullptr)
{
    
}
Particle3DQuadRender::~Particle3DQuadRender()
{
    CC_SAFE_DELETE(_meshCommand);
}

Particle3DQuadRender* Particle3DQuadRender::create()
{
    auto ret = new Particle3DQuadRender();
    ret->autorelease();
    
    return ret;
}

void Particle3DQuadRender::updateRender(const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    if (!_isVisible)
        return;

    //TODO: batch and generate meshcommand
}
void Particle3DQuadRender::render(Renderer* renderer)
{
    if (_isVisible && _meshCommand)
        renderer->addCommand(_meshCommand);
}

//////////////////////////////////////////////////////////////////////////////
Particle3DModelRender::Particle3DModelRender()
: _sprite(nullptr)
{
    
}
Particle3DModelRender::~Particle3DModelRender()
{
    for (auto & it : _meshCommand) {
        delete it;
    }
    _meshCommand.clear();
}


Particle3DModelRender* Particle3DModelRender::create(Sprite3D* sprite)
{
    auto ret = new Particle3DModelRender();
    ret->_sprite = sprite;
    sprite->retain();
    
    return ret;
}

void Particle3DModelRender::updateRender(const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    if (!_isVisible)
        return;
    //TODO: generate mesh commands
}
void Particle3DModelRender::render(Renderer* renderer)
{
    if (!_isVisible)
        return;
    
    for (auto& it : _meshCommand) {
        if (it)
            renderer->addCommand(it);
    }
}

NS_CC_END
