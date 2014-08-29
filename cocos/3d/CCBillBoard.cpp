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

#include "3d/CCBillBoard.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCDirector.h"
#include "base/CCCamera.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCVertexIndexBuffer.h"

NS_CC_BEGIN

BillBorad::BillBorad()
: _zDepthInView(0.0f)
//, _vertexBuffer(nullptr)
//, _indexBuffer(nullptr)
{

}

BillBorad::~BillBorad()
{
    //if (_vertexBuffer)
    //	_vertexBuffer->release();

    //if (_indexBuffer)
    //	_indexBuffer->release();
}

BillBorad* BillBorad::createWithTexture(Texture2D *texture)
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->initWithTexture(texture))
    {
        //billborad->genRenderInformation();
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}


BillBorad* BillBorad::create(const std::string& filename)
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->initWithFile(filename))
    {
       //billborad->genRenderInformation();
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

BillBorad* BillBorad::create(const std::string& filename, const Rect& rect)
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->initWithFile(filename, rect))
    {
        //billborad->genRenderInformation();
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

BillBorad* BillBorad::create()
{
    BillBorad *billborad = new (std::nothrow) BillBorad();
    if (billborad && billborad->init())
    {
        //billborad->genRenderInformation();
        billborad->autorelease();
        return billborad;
    }
    CC_SAFE_DELETE(billborad);
    return nullptr;
}

void BillBorad::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    auto camera = Camera::getVisitingCamera();
    if (memcmp(_preViewMat.m, camera->getViewMatrix().m, sizeof(float) * 16) != 0)
    {
        Mat4 viewInverseMat =  camera->getInverseViewMatrix();
        viewInverseMat.m[12] = viewInverseMat.m[13] = viewInverseMat.m[14] = 0;
        Mat4 modelViewMat = camera->getViewMatrix() * transform;
        _preViewMat = camera->getViewMatrix();
        _zDepthInView = -modelViewMat.m[14];
        _mv = viewInverseMat;
    }
    //// Don't do calculate the culling if the transform was not updated
    //_insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transMat, _contentSize) : _insideBounds;

    //if(_insideBounds)
    {
            _quadCommand.init(_zDepthInView, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, transform * _mv);
            //_meshCommand.init(-modelViewMat.m[14], _texture->getName(), getGLProgramState(), _blendFunc, _vertexBuffer->getVBO(), _indexBuffer->getVBO(), GL_TRIANGLES, GL_UNSIGNED_SHORT, _indexBuffer->getIndexNumber(), transMat);
            renderer->addTransparentCommand(&_quadCommand);
    }
}

//void BillBorad::genRenderInformation()
//{
//    _vertexBuffer = VertexBuffer::create(sizeof(_quad), 1);
//    _vertexBuffer->updateVertices((void*)&_quad, 1, 0);
//	_vertexBuffer->retain();
//
//    std::vector<unsigned short> indices;
//    indices.push_back(0);indices.push_back(1);indices.push_back(2);
//    indices.push_back(3);indices.push_back(2);indices.push_back(1);
//    _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, indices.size());
//    _indexBuffer->updateIndices((void*)&indices[0], (int)indices.size(), 0);
//	_indexBuffer->retain();
//
//#define kQuadSize sizeof(_quad.bl)
//	setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
//	getGLProgramState()->setVertexAttribPointer(GLProgram::ATTRIBUTE_NAME_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));
//	getGLProgramState()->setVertexAttribPointer(GLProgram::ATTRIBUTE_NAME_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, colors));
//	getGLProgramState()->setVertexAttribPointer(GLProgram::ATTRIBUTE_NAME_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, texCoords));
//}

NS_CC_END
