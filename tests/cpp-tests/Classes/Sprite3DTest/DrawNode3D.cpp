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
#include "renderer/backend/Buffer.h"
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
    
    auto EXTENDED_SIZE = _bufferLines.size() + count;

    _bufferLines.reserve(EXTENDED_SIZE);

    if (!_customCommand.getVertexBuffer() || _customCommand.getVertexBuffer()->getSize() < (EXTENDED_SIZE * sizeof(_bufferLines[0])))
    {
        _customCommand.createVertexBuffer(sizeof(V3F_C4B), EXTENDED_SIZE + (EXTENDED_SIZE >> 1), CustomCommand::BufferUsage::DYNAMIC);
    }

}

bool DrawNode3D::init()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    auto &pd = _customCommand.getPipelineDescriptor();
    auto program = backend::Program::getBuiltinProgram(backend::ProgramType::LINE_COLOR_3D);
    _programStateLine = new backend::ProgramState(program);
    pd.programState = _programStateLine;
    
    _locMVPMatrix = _programStateLine->getUniformLocation("u_MVPMatrix");

    _customCommand.setBeforeCallback(CC_CALLBACK_0(DrawNode3D::onBeforeDraw, this));
    _customCommand.setAfterCallback(CC_CALLBACK_0(DrawNode3D::onAfterDraw, this));

    auto layout = _programStateLine->getVertexLayout();
#define INITIAL_VERTEX_BUFFER_LENGTH 512

    ensureCapacity(INITIAL_VERTEX_BUFFER_LENGTH);

    _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::LINE);

    const auto& attributeInfo = _programStateLine->getProgram()->getActiveAttributes();
    auto iter = attributeInfo.find("a_position");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT3, 0, false);
    }
    iter = attributeInfo.find("a_color");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_color", iter->second.location, backend::VertexFormat::UBYTE4, sizeof(Vec3), true);
    }
    layout->setLayout(sizeof(V3F_C4B));
    
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
        _customCommand.setVertexDrawInfo(0, _bufferLines.size());
        _isDirty = false;
    }

    if (!_bufferLines.empty())
    {
        renderer->addCommand(&_customCommand);
    }
}

void DrawNode3D::updateCommand(cocos2d::Renderer* renderer,const Mat4 &transform, uint32_t flags)
{
    auto &matrixP = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto mvp = matrixP * transform;

    _programStateLine->setUniform(_locMVPMatrix, mvp.m, sizeof(mvp.m));


    auto &blend = _customCommand.getPipelineDescriptor().blendDescriptor;
    blend.blendEnabled = true;
    blend.sourceRGBBlendFactor = blend.sourceAlphaBlendFactor = _blendFunc.src;
    blend.destinationRGBBlendFactor = blend.destinationAlphaBlendFactor = _blendFunc.dst;

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _bufferLines.size());
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
    _rendererDepthTestEnabled = renderer->getDepthTest();
    renderer->setDepthTest(true);
}

void DrawNode3D::onAfterDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    renderer->setDepthTest(_rendererDepthTestEnabled);
}


NS_CC_END
