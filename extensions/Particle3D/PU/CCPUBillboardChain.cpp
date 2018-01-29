/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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

#include "extensions/Particle3D/PU/CCPUBillboardChain.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "base/CCDirector.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCVertexAttribBinding.h"
#include "2d/CCCamera.h"
#include "3d/CCSprite3D.h"

NS_CC_BEGIN

const size_t PUBillboardChain::SEGMENT_EMPTY = std::numeric_limits<size_t>::max();
//-----------------------------------------------------------------------
PUBillboardChain::Element::Element()
{
}
//-----------------------------------------------------------------------
PUBillboardChain::Element::Element(const Vec3 &pos,
                                   float w,
                                   float tex,
                                   const Vec4 &col,
                                   const Quaternion &ori) :
position(pos),
width(w),
texCoord(tex),
color(col),
orientation(ori)
{
}
//-----------------------------------------------------------------------
PUBillboardChain::PUBillboardChain(const std::string& /*name*/, const std::string &texFile, size_t maxElements,
                               size_t numberOfChains, bool useTextureCoords, bool useColours, bool dynamic)
                               :_maxElementsPerChain(maxElements),
                               _chainCount(numberOfChains),
                               _useTexCoords(useTextureCoords),
                               _useVertexColour(useColours),
                               _dynamic(dynamic),
                               _vertexDeclDirty(true),
                               _buffersNeedRecreating(true),
                               _boundsDirty(true),
                               _indexContentDirty(true),
                               _vertexContentDirty(true),
                               _texCoordDir(TCD_U),
                               _faceCamera(true),
                               _normalBase(Vec3::UNIT_X),
                               _meshCommand(nullptr),
                               _texture(nullptr),
                               _glProgramState(nullptr),
                               _indexBuffer(nullptr),
                               _vertexBuffer(nullptr),
                               _texFile(texFile)
{

    _stateBlock = RenderState::StateBlock::create();
    CC_SAFE_RETAIN(_stateBlock);

    _stateBlock->setCullFace(false);
    _stateBlock->setCullFaceSide(RenderState::CULL_FACE_SIDE_BACK);
    _stateBlock->setDepthTest(false);
    _stateBlock->setDepthWrite(false);
    _stateBlock->setBlend(true);

    _otherTexCoordRange[0] = 0.0f;
    _otherTexCoordRange[1] = 1.0f;

    setupChainContainers();

    init(texFile);
}
//-----------------------------------------------------------------------
PUBillboardChain::~PUBillboardChain()
{
    CC_SAFE_DELETE(_meshCommand);
    CC_SAFE_RELEASE(_stateBlock);
    //CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_glProgramState);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}
//-----------------------------------------------------------------------
void PUBillboardChain::setupChainContainers(void)
{
    // Allocate enough space for everything
    _chainElementList.resize(_chainCount * _maxElementsPerChain);
    //_vertexData->vertexCount = _chainElementList.size() * 2;

    // Configure chains
    _chainSegmentList.resize(_chainCount);
    for (size_t i = 0; i < _chainCount; ++i)
    {
        ChainSegment& seg = _chainSegmentList[i];
        seg.start = i * _maxElementsPerChain;
        seg.tail = seg.head = SEGMENT_EMPTY;
    }
}
//-----------------------------------------------------------------------
void PUBillboardChain::setupVertexDeclaration(void)
{
    //if (_vertexDeclDirty)
    //{
    //	VertexDeclaration* decl = _vertexData->vertexDeclaration;
    //	decl->removeAllElements();

    //	size_t offset = 0;
    //	// Add a description for the buffer of the positions of the vertices
    //	decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
    //	offset += VertexElement::getTypeSize(VET_FLOAT3);

    //	if (_useVertexColour)
    //	{
    //		decl->addElement(0, offset, VET_COLOUR, VES_DIFFUSE);
    //		offset += VertexElement::getTypeSize(VET_COLOUR);
    //	}

    //	if (_useTexCoords)
    //	{
    //		decl->addElement(0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
    //	}

    //	if (!_useTexCoords && !_useVertexColour)
    //	{
    //		LogManager::getSingleton().logMessage(
    //			"Error - BillboardChain '" + mName + "' is using neither "
    //			"texture coordinates or vertex colours; it will not be "
    //			"visible on some rendering APIs so you should change this "
    //			"so you use one or the other.");
    //	}
    //	_vertexDeclDirty = false;
    //}
}
//-----------------------------------------------------------------------
void PUBillboardChain::setupBuffers(void)
{
    //setupVertexDeclaration();
    if (_buffersNeedRecreating)
    {
        CC_SAFE_RELEASE(_vertexBuffer);
        CC_SAFE_RELEASE(_indexBuffer);

        GLsizei stride = sizeof(VertexInfo);
        _vertexBuffer = VertexBuffer::create(stride, (int)_chainElementList.size() * 2);
        _vertexBuffer->retain();
        VertexInfo vi = {Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f), Vec4::ONE};
        _vertices.resize(_chainElementList.size() * 2, vi);


        _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, (int)(_chainCount * _maxElementsPerChain * 6));
        _indexBuffer->retain();
        _indices.resize(_chainCount * _maxElementsPerChain * 6, 0);

        //// Create the vertex buffer (always dynamic due to the camera adjust)
        //HardwareVertexBufferSharedPtr pBuffer =
        //	HardwareBufferManager::getSingleton().createVertexBuffer(
        //	_vertexData->vertexDeclaration->getVertexSize(0),
        //	_vertexData->vertexCount,
        //	HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

        //// (re)Bind the buffer
        //// Any existing buffer will lose its reference count and be destroyed
        //_vertexData->vertexBufferBinding->setBinding(0, pBuffer);

        //_indexData->indexBuffer =
        //	HardwareBufferManager::getSingleton().createIndexBuffer(
        //	HardwareIndexBuffer::IT_16BIT,
        //	_chainCount * _maxElementsPerChain * 6, // max we can use
        //	_dynamic? HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY : HardwareBuffer::HBU_STATIC_WRITE_ONLY);
        //// NB we don't set the indexCount on IndexData here since we will
        //// probably use less than the maximum number of indices

        _buffersNeedRecreating = false;
    }
}
//-----------------------------------------------------------------------
void PUBillboardChain::setMaxChainElements(size_t maxElements)
{
    _maxElementsPerChain = maxElements;
    setupChainContainers();
    _buffersNeedRecreating = _indexContentDirty = _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::setNumberOfChains(size_t numChains)
{
    _chainCount = numChains;
    setupChainContainers();
    _buffersNeedRecreating = _indexContentDirty = _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::setUseTextureCoords(bool use)
{
    _useTexCoords = use;
    _vertexDeclDirty = _buffersNeedRecreating = true;
    _indexContentDirty = _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::setTextureCoordDirection(PUBillboardChain::TexCoordDirection dir)
{
    _texCoordDir = dir;
    _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::setOtherTextureCoordRange(float start, float end)
{
    _otherTexCoordRange[0] = start;
    _otherTexCoordRange[1] = end;
    _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::setUseVertexColours(bool use)
{
    _useVertexColour = use;
    _vertexDeclDirty = _buffersNeedRecreating = true;
    _indexContentDirty = _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::setDynamic(bool dyn)
{
    _dynamic = dyn;
    _buffersNeedRecreating = _indexContentDirty = _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::addChainElement(size_t chainIndex,
                                     const PUBillboardChain::Element& dtls)
{
    CCASSERT(chainIndex < _chainCount, "chainIndex out of bounds");
    ChainSegment& seg = _chainSegmentList[chainIndex];
    if (seg.head == SEGMENT_EMPTY)
    {
        // Tail starts at end, head grows backwards
        seg.tail = _maxElementsPerChain - 1;
        seg.head = seg.tail;
    }
    else
    {
        if (seg.head == 0)
        {
            // Wrap backwards
            seg.head = _maxElementsPerChain - 1;
        }
        else
        {
            // Just step backward
            --seg.head;
        }
        // Run out of elements?
        if (seg.head == seg.tail)
        {
            // Move tail backwards too, losing the end of the segment and re-using
            // it in the head
            if (seg.tail == 0)
                seg.tail = _maxElementsPerChain - 1;
            else
                --seg.tail;
        }
    }

    // Set the details
    _chainElementList[seg.start + seg.head] = dtls;

    _vertexContentDirty = true;
    _indexContentDirty = true;
    _boundsDirty = true;
    //// tell parent node to update bounds
    //if (mParentNode)
    //	mParentNode->needUpdate();

}
//-----------------------------------------------------------------------
void PUBillboardChain::removeChainElement(size_t chainIndex)
{
    CCASSERT(chainIndex < _chainCount, "chainIndex out of bounds");
    ChainSegment& seg = _chainSegmentList[chainIndex];
    if (seg.head == SEGMENT_EMPTY)
        return; // do nothing, nothing to remove


    if (seg.tail == seg.head)
    {
        // last item
        seg.head = seg.tail = SEGMENT_EMPTY;
    }
    else if (seg.tail == 0)
    {
        seg.tail = _maxElementsPerChain - 1;
    }
    else
    {
        --seg.tail;
    }

    // we removed an entry so indexes need updating
    _vertexContentDirty = true;
    _indexContentDirty = true;
    _boundsDirty = true;
    //// tell parent node to update bounds
    //if (mParentNode)
    //	mParentNode->needUpdate();

}
//-----------------------------------------------------------------------
void PUBillboardChain::clearChain(size_t chainIndex)
{
    CCASSERT(chainIndex < _chainCount, "chainIndex out of bounds");
    ChainSegment& seg = _chainSegmentList[chainIndex];

    // Just reset head & tail
    seg.tail = seg.head = SEGMENT_EMPTY;

    // we removed an entry so indexes need updating
    _vertexContentDirty = true;
    _indexContentDirty = true;
    _boundsDirty = true;
    //// tell parent node to update bounds
    //if (mParentNode)
    //	mParentNode->needUpdate();

}
//-----------------------------------------------------------------------
void PUBillboardChain::clearAllChains(void)
{
    for (size_t i = 0; i < _chainCount; ++i)
    {
        clearChain(i);
    }

}
//-----------------------------------------------------------------------
void PUBillboardChain::setFaceCamera( bool faceCamera, const Vec3 &normalVector )
{
    _faceCamera = faceCamera;
    _normalBase = normalVector;
    _normalBase.normalize();
    _vertexContentDirty = true;
}
//-----------------------------------------------------------------------
void PUBillboardChain::updateChainElement(size_t chainIndex, size_t elementIndex,
                                        const PUBillboardChain::Element& dtls)
{
    CCASSERT(chainIndex < _chainCount, "chainIndex out of bounds");
    ChainSegment& seg = _chainSegmentList[chainIndex];
    CCASSERT(seg.head != SEGMENT_EMPTY, "Chain segment is empty");

    size_t idx = seg.head + elementIndex;
    // adjust for the edge and start
    idx = (idx % _maxElementsPerChain) + seg.start;

    _chainElementList[idx] = dtls;

    _vertexContentDirty = true;
    _boundsDirty = true;

    //// tell parent node to update bounds
    //if (mParentNode)
    //	mParentNode->needUpdate();
}
//-----------------------------------------------------------------------
const PUBillboardChain::Element&
    PUBillboardChain::getChainElement(size_t chainIndex, size_t elementIndex) const
{
    CCASSERT(chainIndex < _chainCount, "chainIndex out of bounds");
    const ChainSegment& seg = _chainSegmentList[chainIndex];

    size_t idx = seg.head + elementIndex;
    // adjust for the edge and start
    idx = (idx % _maxElementsPerChain) + seg.start;

    return _chainElementList[idx];
}
//-----------------------------------------------------------------------
size_t PUBillboardChain::getNumChainElements(size_t chainIndex) const
{
    CCASSERT(chainIndex < _chainCount, "chainIndex out of bounds");
    const ChainSegment& seg = _chainSegmentList[chainIndex];

    if( seg.tail < seg.head )
    {
        return seg.tail - seg.head + _maxElementsPerChain + 1;
    }
    else
    {
        return seg.tail - seg.head + 1;
    }
}
//-----------------------------------------------------------------------
void PUBillboardChain::updateVertexBuffer(const Mat4 &camMat)
{
    setupBuffers();

    // The contents of the vertex buffer are correct if they are not dirty
    // and the camera used to build the vertex buffer is still the current 
    // camera.
    if (!_vertexContentDirty)
        return;

    VertexInfo vi = {Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f), Vec4::ONE};
    _vertices.assign(_vertices.size(), vi);
    //HardwareVertexBufferSharedPtr pBuffer =
    //	_vertexData->vertexBufferBinding->getBuffer(0);
    //void* pBufferStart = pBuffer->lock(HardwareBuffer::HBL_DISCARD);

    //const Vector3& camPos = cam->getDerivedPosition();
    //Vector3 eyePos = mParentNode->_getDerivedOrientation().Inverse() *
    //	(camPos - mParentNode->_getDerivedPosition()) / mParentNode->_getDerivedScale();

    Vec3 eyePos(camMat.m[12], camMat.m[13], camMat.m[14]);

    Vec3 chainTangent;
    for (ChainSegmentList::iterator segi = _chainSegmentList.begin();
        segi != _chainSegmentList.end(); ++segi)
    {
        ChainSegment& seg = *segi;

        // Skip 0 or 1 element segment counts
        if (seg.head != SEGMENT_EMPTY && seg.head != seg.tail)
        {
            size_t laste = seg.head;
            for (size_t e = seg.head; ; ++e) // until break
            {
                // Wrap forwards
                if (e == _maxElementsPerChain)
                    e = 0;

                Element& elem = _chainElementList[e + seg.start];
                CCASSERT (((e + seg.start) * 2) < 65536, "Too many elements!");
                unsigned short vertexIndex = static_cast<unsigned short>((e + seg.start) * 2);
                //// Determine base pointer to vertex #1
                //void* pBase = static_cast<void*>(
                //	static_cast<char*>(pBufferStart) +
                //	pBuffer->getVertexSize() * baseIdx);

                // Get index of next item
                size_t nexte = e + 1;
                if (nexte == _maxElementsPerChain)
                    nexte = 0;

                if (e == seg.head)
                {
                    // No laste, use next item
                    chainTangent = _chainElementList[nexte + seg.start].position - elem.position;
                }
                else if (e == seg.tail)
                {
                    // No nexte, use only last item
                    chainTangent = elem.position - _chainElementList[laste + seg.start].position;
                }
                else
                {
                    // A mid position, use tangent across both prev and next
                    chainTangent = _chainElementList[nexte + seg.start].position - _chainElementList[laste + seg.start].position;

                }

                Vec3 vP1ToEye;

                //if( _faceCamera )
                    vP1ToEye = eyePos - elem.position;
                //else
                //	vP1ToEye = elem.orientation * _normalBase;

                Vec3 vPerpendicular;
                Vec3::cross(chainTangent, vP1ToEye, &vPerpendicular);
                vPerpendicular.normalize();
                vPerpendicular *= (elem.width * 0.5f);

                Vec3 pos0 = elem.position - vPerpendicular;
                Vec3 pos1 = elem.position + vPerpendicular;

                //float* pFloat = static_cast<float*>(pBase);
                //// pos1
                //*pFloat++ = pos0.x;
                //*pFloat++ = pos0.y;
                //*pFloat++ = pos0.z;
                _vertices[vertexIndex + 0].position = pos0;


                //pBase = static_cast<void*>(pFloat);

                if (_useVertexColour)
                {
                    //RGBA* pCol = static_cast<RGBA*>(pBase);
                    //Root::getSingleton().convertColourValue(elem.colour, pCol);
                    //pCol++;
                    //pBase = static_cast<void*>(pCol);
                    _vertices[vertexIndex + 0].color = elem.color;
                }

                if (_useTexCoords)
                {
                    //pFloat = static_cast<float*>(pBase);
                    if (_texCoordDir == TCD_U)
                    {
                        //*pFloat++ = elem.texCoord;
                        //*pFloat++ = _otherTexCoordRange[0];
                        _vertices[vertexIndex + 0].uv.x = elem.texCoord;
                        _vertices[vertexIndex + 0].uv.y = _otherTexCoordRange[0];
                    }
                    else
                    {
                        //*pFloat++ = _otherTexCoordRange[0];
                        //*pFloat++ = elem.texCoord;
                        _vertices[vertexIndex + 0].uv.x = _otherTexCoordRange[0];
                        _vertices[vertexIndex + 0].uv.y = elem.texCoord;
                    }
                    //pBase = static_cast<void*>(pFloat);
                }

                // pos2
                //pFloat = static_cast<float*>(pBase);
                //*pFloat++ = pos1.x;
                //*pFloat++ = pos1.y;
                //*pFloat++ = pos1.z;
                //pBase = static_cast<void*>(pFloat);
                _vertices[vertexIndex + 1].position = pos1;

                if (_useVertexColour)
                {
                    //RGBA* pCol = static_cast<RGBA*>(pBase);
                    //Root::getSingleton().convertColourValue(elem.colour, pCol);
                    //pCol++;
                    //pBase = static_cast<void*>(pCol);
                    _vertices[vertexIndex + 1].color = elem.color;
                }

                if (_useTexCoords)
                {
                    //pFloat = static_cast<float*>(pBase);
                    if (_texCoordDir == TCD_U)
                    {
                        //*pFloat++ = elem.texCoord;
                        //*pFloat++ = _otherTexCoordRange[1];
                        _vertices[vertexIndex + 1].uv.x = elem.texCoord;
                        _vertices[vertexIndex + 1].uv.y = _otherTexCoordRange[1];
                    }
                    else
                    {
                        //*pFloat++ = _otherTexCoordRange[1];
                        //*pFloat++ = elem.texCoord;
                        _vertices[vertexIndex + 1].uv.x = _otherTexCoordRange[1];
                        _vertices[vertexIndex + 1].uv.y = elem.texCoord;
                    }
                }

                if (e == seg.tail)
                    break; // last one

                laste = e;
                //vertexIndex += 2;
            } // element
        } // segment valid?

    } // each segment


    _vertexBuffer->updateVertices(&_vertices[0], (int)_vertices.size(), 0);
    //pBuffer->unlock();
    //_vertexCameraUsed = cam;
    _vertexContentDirty = false;

}
//-----------------------------------------------------------------------
void PUBillboardChain::updateIndexBuffer(void)
{

    setupBuffers();
    if (_indexContentDirty)
    {

        //uint16* pShort = static_cast<uint16*>(
        //	_indexData->indexBuffer->lock(HardwareBuffer::HBL_DISCARD));
        //_indexData->indexCount = 0;
        // indexes
        unsigned short index = 0;
        for (ChainSegmentList::iterator segi = _chainSegmentList.begin();
            segi != _chainSegmentList.end(); ++segi)
        {
            ChainSegment& seg = *segi;

            // Skip 0 or 1 element segment counts
            if (seg.head != SEGMENT_EMPTY && seg.head != seg.tail)
            {
                // Start from head + 1 since it's only useful in pairs
                size_t laste = seg.head;
                while(1) // until break
                {
                    size_t e = laste + 1;
                    // Wrap forwards
                    if (e == _maxElementsPerChain)
                        e = 0;
                    // indexes of this element are (e * 2) and (e * 2) + 1
                    // indexes of the last element are the same, -2
                    CCASSERT (((e + seg.start) * 2) < 65536, "Too many elements!");
                    unsigned short baseIdx = static_cast<unsigned short>((e + seg.start) * 2);
                    unsigned short lastBaseIdx = static_cast<unsigned short>((laste + seg.start) * 2);


                    //*pShort++ = lastBaseIdx;
                    //*pShort++ = lastBaseIdx + 1;
                    //*pShort++ = baseIdx;
                    //*pShort++ = lastBaseIdx + 1;
                    //*pShort++ = baseIdx + 1;
                    //*pShort++ = baseIdx;
                    //_indexData->indexCount += 6;

                    _indices[index++] = lastBaseIdx;
                    _indices[index++] = lastBaseIdx + 1;
                    _indices[index++] = baseIdx;
                    _indices[index++] = lastBaseIdx + 1;
                    _indices[index++] = baseIdx + 1;
                    _indices[index++] = baseIdx;

                    if (e == seg.tail)
                        break; // last one

                    laste = e;

                }
            }

        }

        _indexBuffer->updateIndices(&_indices[0], (int)_indices.size(), 0);
        //_indexData->indexBuffer->unlock();
        _indexContentDirty = false;
    }

}
//-----------------------------------------------------------------------
void PUBillboardChain::init( const std::string &texFile )
{
    GLProgram* glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_PARTICLE_COLOR);
    if (!texFile.empty())
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
        if (tex)
        {
            _texture = tex;
            glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_PARTICLE_TEXTURE);
        }
    }
    auto glProgramState = GLProgramState::create(glProgram);
    glProgramState->retain();

    GLsizei stride = sizeof(VertexInfo);

    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_POSITION], 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(VertexInfo, position));
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_TEX_COORD], 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(VertexInfo, uv));
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_COLOR], 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(VertexInfo, color));

    _glProgramState = glProgramState;

    _meshCommand = new (std::nothrow) MeshCommand();
    _meshCommand->setSkipBatching(true);
    _meshCommand->setTransparent(true);
    _stateBlock->setDepthTest(true);
    _stateBlock->setDepthWrite(false);
    _stateBlock->setCullFaceSide(RenderState::CULL_FACE_SIDE_BACK);
    _stateBlock->setCullFace(true);
}

void PUBillboardChain::render( Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem )
{
    auto camera = Camera::getVisitingCamera();
    auto cameraMat = camera->getNodeToWorldTransform();

    if (!_chainSegmentList.empty())
    {
        updateVertexBuffer(cameraMat);
        updateIndexBuffer();
        if (!_vertices.empty() && !_indices.empty())
        {
            GLuint texId = this->getTextureName();
            _stateBlock->setBlendFunc(particleSystem->getBlendFunc());
            _meshCommand->init(0,
                               texId,
                               _glProgramState,
                               _stateBlock,
                               _vertexBuffer->getVBO(),
                               _indexBuffer->getVBO(),
                               GL_TRIANGLES,
                               GL_UNSIGNED_SHORT,
                               _indices.size(),
                               transform,
                               Node::FLAGS_RENDER_AS_3D);
            _meshCommand->setSkipBatching(true);
            _meshCommand->setTransparent(true);            
            _glProgramState->setUniformVec4("u_color", Vec4(1,1,1,1));
            renderer->addCommand(_meshCommand);
        }
    }
}

void PUBillboardChain::setDepthTest( bool isDepthTest )
{
    _stateBlock->setDepthTest(isDepthTest);
}

void PUBillboardChain::setDepthWrite( bool isDepthWrite )
{
    _stateBlock->setDepthWrite(isDepthWrite);
}

void PUBillboardChain::setBlendFunc(const BlendFunc& blendFunc)
{
    _stateBlock->setBlendFunc(blendFunc);
}

GLuint PUBillboardChain::getTextureName()
{
    if (Director::getInstance()->getTextureCache()->getTextureForKey(_texFile) == nullptr)
    {
        _texture = nullptr;
        this->init("");
    }
    else if (_texture == nullptr)
    {
        this->init(_texFile);
    }

    if (_texture == nullptr)
        return 0;

    return _texture->getName();
}

//-----------------------------------------------------------------------
//void PUBillboardChain::_updateRenderQueue(RenderQueue* queue)
//{
//	updateIndexBuffer();
//
//	if (mIndexData->indexCount > 0)
//	{
//		if (mRenderQueuePrioritySet)
//			queue->addRenderable(this, mRenderQueueID, mRenderQueuePriority);
//		else if (mRenderQueueIDSet)
//			queue->addRenderable(this, mRenderQueueID);
//		else
//			queue->addRenderable(this);
//	}
//
//}
//-----------------------------------------------------------------------
//void PUBillboardChain::getRenderOperation(RenderOperation& op)
//{
//	op.indexData = mIndexData;
//	op.operationType = RenderOperation::OT_TRIANGLE_LIST;
//	op.srcRenderable = this;
//	op.useIndexes = true;
//	op.vertexData = mVertexData;
//}
//-----------------------------------------------------------------------
//bool PUBillboardChain::preRender(SceneManager* sm, RenderSystem* rsys)
//{
//	// Retrieve the current viewport from the scene manager.
//	// The viewport is only valid during a viewport update.
//	Viewport *currentViewport = sm->getCurrentViewport();
//	if( !currentViewport )
//		return false;
//
//	updateVertexBuffer(currentViewport->getCamera());
//	return true;
//}
//-----------------------------------------------------------------------
//void PUBillboardChain::getWorldTransforms(Matrix4* xform) const
//{
//	*xform = _getParentNodeFullTransform();
//}
//---------------------------------------------------------------------

NS_CC_END
