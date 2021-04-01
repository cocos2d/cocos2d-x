/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "physics3d/CCPhysics3D.h"
#include <stddef.h> // offsetof
#include "base/ccTypes.h"
#include "base/CCConfiguration.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/ccUtils.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/Buffer.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN

void Physics3DDebugDrawer::drawLine( const btVector3& from,const btVector3& to,const btVector3& color )
{
    Vec3 col = convertbtVector3ToVec3(color);

    V3F_V4F a, b;
    a.vertex = convertbtVector3ToVec3(from);
    a.color = Vec4(col.x, col.y, col.z, 1.0f);
    b.vertex = convertbtVector3ToVec3(to);
    b.color = Vec4(col.x, col.y, col.z, 1.0f);

    _buffer.emplace_back(a);
    _buffer.emplace_back(b);

    _dirty = true;
}

void Physics3DDebugDrawer::drawContactPoint( const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int /*lifeTime*/,const btVector3& color )
{
    drawLine(PointOnB, PointOnB + normalOnB * distance, color);
}

void Physics3DDebugDrawer::reportErrorWarning( const char* warningString )
{
    CCLOG("%s", warningString);
}

void Physics3DDebugDrawer::draw3dText( const btVector3& /*location*/,const char* /*textString*/ )
{

}

void Physics3DDebugDrawer::setDebugMode( int debugMode )
{
    _debugMode = debugMode;
}

int Physics3DDebugDrawer::getDebugMode() const 
{
    return _debugMode;
}

void Physics3DDebugDrawer::draw( Renderer *renderer)
{
    
    auto &transform = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    _programState->setUniform(_locMVP, transform.m, sizeof(transform.m));
    _customCommand.init(0, Mat4::IDENTITY, 0);

    auto &blend = _customCommand.getPipelineDescriptor().blendDescriptor;
    blend.blendEnabled = true;
    blend.sourceAlphaBlendFactor = blend.sourceRGBBlendFactor = _blendFunc.src;
    blend.destinationAlphaBlendFactor = blend.destinationRGBBlendFactor = _blendFunc.dst;


    if (_customCommand.getVertexBuffer() == nullptr || _customCommand.getVertexBuffer()->getSize() < _buffer.size() * sizeof(_buffer[0]))
    {
        _customCommand.createVertexBuffer(sizeof(_buffer[0]), _buffer.size(), CustomCommand::BufferUsage::DYNAMIC);
        _dirty = true;
    }

    if (_dirty)
    {
        _customCommand.updateVertexBuffer(_buffer.data(), _buffer.size() * sizeof(_buffer[0]));
        _dirty = false;
    }

    _customCommand.setVertexDrawInfo(0, _buffer.size());

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _buffer.size());

    renderer->addCommand(&_customCommand);

}

Physics3DDebugDrawer::Physics3DDebugDrawer()
{
    init();
}

Physics3DDebugDrawer::~Physics3DDebugDrawer()
{
    CC_SAFE_RELEASE(_programState);
}

void Physics3DDebugDrawer::init()
{
    CC_SAFE_RELEASE_NULL(_programState);
    auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_COLOR);
    _programState = new backend::ProgramState(program);
    _locMVP = _programState->getUniformLocation("u_MVPMatrix");
    
    auto attributes = _programState->getProgram()->getActiveAttributes();
    auto locPosition = attributes["a_position"];
    auto locColor = attributes["a_color"];
    
    auto layout = _programState->getVertexLayout();
    layout->setAttribute(locPosition.attributeName.c_str(), locPosition.location, backend::VertexFormat::FLOAT3, offsetof(V3F_V4F, vertex), false);
    layout->setAttribute(locColor.attributeName.c_str(), locColor.location, backend::VertexFormat::FLOAT4, offsetof(V3F_V4F, color), false);
    layout->setLayout(sizeof(V3F_V4F));

    _buffer.reserve(512);

    _customCommand.getPipelineDescriptor().programState = _programState;
    _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::LINE);
    _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommand.setBeforeCallback(CC_CALLBACK_0(Physics3DDebugDrawer::onBeforeDraw, this));
    _customCommand.setAfterCallback(CC_CALLBACK_0(Physics3DDebugDrawer::onAfterDraw, this));
}

void Physics3DDebugDrawer::onBeforeDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    _oldDepthTestEnabled = renderer->getDepthTest();
    renderer->setDepthTest(true);
}

void Physics3DDebugDrawer::onAfterDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    renderer->setDepthTest(_oldDepthTestEnabled);
}

void Physics3DDebugDrawer::clear()
{
    _buffer.clear();
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS
