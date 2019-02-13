/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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

#include "DrawNode3D.h"

NS_CC_BEGIN


DrawNode3D::DrawNode3D()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

DrawNode3D::~DrawNode3D()
{
    CC_SAFE_RELEASE_NULL(_programStateLine);
    CC_SAFE_DELETE(_depthstencilDescriptor);
}

DrawNode3D* DrawNode3D::create()
{
    DrawNode3D* ret = new (std::nothrow) DrawNode3D();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

void DrawNode3D::ensureCapacity(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    _bufferLines.reserve(_bufferLines.size() + count);
}

bool DrawNode3D::init()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    auto &pd = _customCommand.getPipelineDescriptor();
    _programStateLine = new backend::ProgramState(lineColor3D_vert, lineColor3D_frag);
    pd.programState = _programStateLine;
    

    _beforeCommand.func = CC_CALLBACK_0(DrawNode3D::onBeforeDraw, this);
    _afterCommand.func = CC_CALLBACK_0(DrawNode3D::onAfterDraw, this);


    auto &layout = _customCommand.getPipelineDescriptor().vertexLayout;
#define INITIAL_VERTEX_BUFFER_LENGTH 512

    ensureCapacity(INITIAL_VERTEX_BUFFER_LENGTH);

    _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::LINE);

    layout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32B32, 0, false);
    layout.setAtrribute("a_color", 1, backend::VertexFormat::UBYTE_R8G8B8A8, sizeof(Vec3), true);
    layout.setLayout(sizeof(V3F_C4B), backend::VertexStepMode::VERTEX);
    
    _customCommand.createVertexBuffer(sizeof(V3F_C4B), INITIAL_VERTEX_BUFFER_LENGTH, CustomCommand::BufferUsage::DYNAMIC);
    _isDirty = true;

#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
    /** listen the event that coming to foreground on Android */
        this->init();
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
    
    return true;
}

void DrawNode3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);

    updateCommand(renderer, transform, flags);

    if (_isDirty && !_bufferLines.empty())
    {
        _customCommand.updateVertexBuffer(_bufferLines.data(), (unsigned int)(_bufferLines.size() * sizeof(_bufferLines[0])));
        _isDirty = false;
    }

    if (!_bufferLines.empty())
    {
        _beforeCommand.init(_globalZOrder);
        _afterCommand.init(_globalZOrder);

        renderer->addCommand(&_beforeCommand);
        renderer->addCommand(&_customCommand);
        renderer->addCommand(&_afterCommand);
    }
}

void DrawNode3D::updateCommand(cocos2d::Renderer* renderer,const Mat4 &transform, uint32_t flags)
{
    _programStateLine->setBuiltinUniforms(transform);

    //TODO arnold: _customcommand should support enable depth !!!
    // glEnable(GL_DEPTH_TEST);
    //TODO arnold
    //RenderState::StateBlock::_globalState->setDepthTest(true);

    cocos2d::utils::setBlending(_blendFunc.src, _blendFunc.dst);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _bufferLines.size());
    CHECK_GL_ERROR_DEBUG();
}

void DrawNode3D::drawLine(const Vec3 &from, const Vec3 &to, const Color4F &color)
{
    unsigned int vertex_count = 2;
    ensureCapacity(vertex_count);
    
    Color4B col = Color4B(color);
    V3F_C4B a = {Vec3(from.x, from.y, from.z), col};
    V3F_C4B b = {Vec3(to.x, to.y, to.z), col, };

    _bufferLines.push_back(a);
    _bufferLines.push_back(b);
    
    _isDirty = true;
}

void DrawNode3D::drawCube(Vec3* vertices, const Color4F &color)
{
    // front face
    drawLine(vertices[0], vertices[1], color);
    drawLine(vertices[1], vertices[2], color);
    drawLine(vertices[2], vertices[3], color);
    drawLine(vertices[3], vertices[0], color);
    
    // back face
    drawLine(vertices[4], vertices[5], color);
    drawLine(vertices[5], vertices[6], color);
    drawLine(vertices[6], vertices[7], color);
    drawLine(vertices[7], vertices[4], color);
    
    // edge
    drawLine(vertices[0], vertices[7], color);
    drawLine(vertices[1], vertices[6], color);
    drawLine(vertices[2], vertices[5], color);
    drawLine(vertices[3], vertices[4], color);
}

void DrawNode3D::clear()
{
    _bufferLines.clear();
    _isDirty = true;
}

const BlendFunc& DrawNode3D::getBlendFunc() const
{
    return _blendFunc;
}

void DrawNode3D::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}


void DrawNode3D::onBeforeDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    renderer->pushGlobalStates();
    renderer->setDepthTest(true);
}

void DrawNode3D::onAfterDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    renderer->popGlobalStates();
}


NS_CC_END
