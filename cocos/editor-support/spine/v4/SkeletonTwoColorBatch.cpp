/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated May 1, 2019. Replaces all prior versions.
 *
 * Copyright (c) 2013-2019, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS
 * INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/spine-cocos2dx.h>
#if COCOS2D_VERSION >= 0x00040000

#include <spine/Extension.h>
#include <algorithm>
#include <stddef.h> // offsetof
#include "base/ccTypes.h"
#include "base/ccUtils.h"

#include "xxhash.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/Device.h"

USING_NS_CC;
#define EVENT_AFTER_DRAW_RESET_POSITION "director_after_draw"
using std::max;
#define INITIAL_SIZE (10000)
#define MAX_VERTICES 64000
#define MAX_INDICES 64000

#define STRINGIFY(A)  #A

namespace {

    const char* TWO_COLOR_TINT_VERTEX_SHADER = STRINGIFY(
    uniform mat4 u_PMatrix;
    attribute vec4 a_position;
    attribute vec4 a_color;
    attribute vec4 a_color2;
    attribute vec2 a_texCoords;

    \n#ifdef GL_ES\n
        varying lowp vec4 v_light;
    varying lowp vec4 v_dark;
    varying mediump vec2 v_texCoord;
    \n#else\n
        varying vec4 v_light;
    varying vec4 v_dark;
    varying vec2 v_texCoord;

    \n#endif\n

        void main() {
        v_light = a_color;
        v_dark = a_color2;
        v_texCoord = a_texCoords;
        gl_Position = u_PMatrix * a_position;
    }
    );

    const char* TWO_COLOR_TINT_FRAGMENT_SHADER = STRINGIFY(
        \n#ifdef GL_ES\n
        precision lowp float;
    \n#endif\n
        uniform sampler2D u_texture;
    varying vec4 v_light;
    varying vec4 v_dark;
    varying vec2 v_texCoord;

    void main() {
        vec4 texColor = texture2D(u_texture, v_texCoord);
        float alpha = texColor.a * v_light.a;
        gl_FragColor.a = alpha;
        gl_FragColor.rgb = ((texColor.a - 1.0) * v_dark.a + 1.0 - texColor.rgb) * v_dark.rgb + texColor.rgb * v_light.rgb;
    }
    );


    std::shared_ptr<backend::ProgramState>  __twoColorProgramState = nullptr;
    backend::UniformLocation                __locPMatrix;
    backend::UniformLocation                __locTexture;

    void initTwoColorProgramState()
    {
        if (__twoColorProgramState)
        {
            return;
        }
        auto program = backend::Device::getInstance()->newProgram(TWO_COLOR_TINT_VERTEX_SHADER, TWO_COLOR_TINT_FRAGMENT_SHADER);
        auto* programState = new backend::ProgramState(program);
        program->autorelease();

        __locPMatrix = programState->getUniformLocation("u_PMatrix");
        __locTexture = programState->getUniformLocation("u_texture");

        auto layout = programState->getVertexLayout();

        auto locPosition = programState->getAttributeLocation("a_position");
        auto locTexcoord = programState->getAttributeLocation("a_texCoords");
        auto locColor = programState->getAttributeLocation("a_color");
        auto locColor2 = programState->getAttributeLocation("a_color2");

        layout->setAttribute("a_position", locPosition, backend::VertexFormat::FLOAT3, offsetof(spine::V3F_C4B_C4B_T2F, position), false);
        layout->setAttribute("a_color", locColor, backend::VertexFormat::UBYTE4, offsetof(spine::V3F_C4B_C4B_T2F, color), true);
        layout->setAttribute("a_color2", locColor2, backend::VertexFormat::UBYTE4, offsetof(spine::V3F_C4B_C4B_T2F, color2), true);
        layout->setAttribute("a_texCoords", locTexcoord, backend::VertexFormat::FLOAT2, offsetof(spine::V3F_C4B_C4B_T2F, texCoords), false);
        layout->setLayout(sizeof(spine::V3F_C4B_C4B_T2F));

        __twoColorProgramState = std::shared_ptr<backend::ProgramState>(programState);
    }

}

namespace spine {

TwoColorTrianglesCommand::TwoColorTrianglesCommand() :_materialID(0), _texture(nullptr), _blendType(BlendFunc::DISABLE) {
	_type = RenderCommand::Type::CUSTOM_COMMAND;
}

void TwoColorTrianglesCommand::init(float globalOrder, cocos2d::Texture2D *texture, BlendFunc blendType, const TwoColorTriangles& triangles, const Mat4& mv, uint32_t flags) {

    updateCommandPipelineDescriptor();
    const cocos2d::Mat4& projectionMat = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    auto finalMatrix = projectionMat * mv;

    _programState->setUniform(_locPMatrix, finalMatrix.m, sizeof(finalMatrix.m));
    _programState->setTexture(_locTexture, 0, texture->getBackendTexture());


    RenderCommand::init(globalOrder, mv, flags);

    _triangles = triangles;
    if (_triangles.indexCount % 3 != 0) {
        int count = _triangles.indexCount;
        _triangles.indexCount = count / 3 * 3;
        CCLOGERROR("Resize indexCount from %d to %d, size must be multiple times of 3", count, _triangles.indexCount);
    }

    _mv = mv;

    if (_blendType.src != blendType.src || _blendType.dst != blendType.dst ||
        _texture != texture->getBackendTexture() || _pipelineDescriptor.programState != _programState)
    {
		_texture = texture->getBackendTexture();
		_blendType = blendType;

        _prog = _programState->getProgram();

        auto& blendDescriptor = _pipelineDescriptor.blendDescriptor;
        blendDescriptor.blendEnabled = true;
        blendDescriptor.sourceRGBBlendFactor = blendDescriptor.sourceAlphaBlendFactor = blendType.src;
        blendDescriptor.destinationRGBBlendFactor = blendDescriptor.destinationAlphaBlendFactor = blendType.dst;

		generateMaterialID();
	}
}



void TwoColorTrianglesCommand::updateCommandPipelineDescriptor()
{
    if (!__twoColorProgramState)
    {
        initTwoColorProgramState();
    }

    CC_SAFE_RELEASE_NULL(_programState);
    _programState = __twoColorProgramState->clone();
    _locPMatrix = __locPMatrix;
    _locTexture = __locTexture;
    _pipelineDescriptor.programState = _programState;
}

TwoColorTrianglesCommand::~TwoColorTrianglesCommand()
{
    CC_SAFE_RELEASE_NULL(_programState);
}

void TwoColorTrianglesCommand::generateMaterialID() {
	// do not batch if using custom uniforms (since we cannot batch) it


    struct
    {
        void* texture;
        void* prog;
        backend::BlendFactor src;
        backend::BlendFactor dst;
    }hashMe;

    // NOTE: Initialize hashMe struct to make the value of padding bytes be filled with zero.
    // It's important since XXH32 below will also consider the padding bytes which probably
    // are set to random values by different compilers.
    memset(&hashMe, 0, sizeof(hashMe));

    hashMe.texture = _texture;
    hashMe.src = _blendType.src;
    hashMe.dst = _blendType.dst;
    hashMe.prog = _prog;
    _materialID = XXH32((const void*)&hashMe, sizeof(hashMe), 0);
}


void TwoColorTrianglesCommand::draw(Renderer *r) {
	SkeletonTwoColorBatch::getInstance()->batch(r, this);
}

void TwoColorTrianglesCommand::updateVertexAndIndexBuffer(Renderer *r, V3F_C4B_C4B_T2F *vertices, int verticesSize, uint16_t *indices, int indicesSize)
{
    if(verticesSize != _vertexCapacity)
        createVertexBuffer(sizeof(V3F_C4B_C4B_T2F), verticesSize, CustomCommand::BufferUsage::DYNAMIC);
    if(indicesSize != _indexCapacity)
        createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, indicesSize, CustomCommand::BufferUsage::DYNAMIC);

    updateVertexBuffer(vertices, sizeof(V3F_C4B_C4B_T2F) * verticesSize);
    updateIndexBuffer(indices, sizeof(uint16_t) * indicesSize);
}


static SkeletonTwoColorBatch* instance = nullptr;

SkeletonTwoColorBatch* SkeletonTwoColorBatch::getInstance () {
	if (!instance) instance = new SkeletonTwoColorBatch();
	return instance;
}

void SkeletonTwoColorBatch::destroyInstance () {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

SkeletonTwoColorBatch::SkeletonTwoColorBatch () : _vertexBuffer(0), _indexBuffer(0) {
    _commandsPool.reserve(INITIAL_SIZE);
	for (unsigned int i = 0; i < INITIAL_SIZE; i++) {
		_commandsPool.push_back(new TwoColorTrianglesCommand());
	}

	reset ();

	// callback after drawing is finished so we can clear out the batch state
	// for the next frame
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_AFTER_DRAW_RESET_POSITION, [this](EventCustom* eventCustom){
		this->update(0);
	});

}

SkeletonTwoColorBatch::~SkeletonTwoColorBatch () {
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_AFTER_DRAW_RESET_POSITION);

	for (unsigned int i = 0; i < _commandsPool.size(); i++) {
		delete _commandsPool[i];
		_commandsPool[i] = nullptr;
	}

	delete[] _vertexBuffer;
	delete[] _indexBuffer;
}

void SkeletonTwoColorBatch::update (float delta) {
	reset();
}

V3F_C4B_C4B_T2F* SkeletonTwoColorBatch::allocateVertices(uint32_t numVertices) {
	if (_vertices.size() - _numVertices < numVertices) {
		V3F_C4B_C4B_T2F* oldData = _vertices.data();
		_vertices.resize((_vertices.size() + numVertices) * 2 + 1);
		V3F_C4B_C4B_T2F* newData = _vertices.data();
		for (uint32_t i = 0; i < this->_nextFreeCommand; i++) {
			TwoColorTrianglesCommand* command = _commandsPool[i];
			TwoColorTriangles& triangles = (TwoColorTriangles&)command->getTriangles();
			triangles.verts = newData + (triangles.verts - oldData);
		}
	}

	V3F_C4B_C4B_T2F* vertices = _vertices.data() + _numVertices;
	_numVertices += numVertices;
	return vertices;
}


void SkeletonTwoColorBatch::deallocateVertices(uint32_t numVertices) {
	_numVertices -= numVertices;
}


unsigned short* SkeletonTwoColorBatch::allocateIndices(uint32_t numIndices) {
	if (_indices.getCapacity() - _indices.size() < numIndices) {
		unsigned short* oldData = _indices.buffer();
		int oldSize =_indices.size();
		_indices.ensureCapacity(_indices.size() + numIndices);
		unsigned short* newData = _indices.buffer();
		for (uint32_t i = 0; i < this->_nextFreeCommand; i++) {
			TwoColorTrianglesCommand* command = _commandsPool[i];
			TwoColorTriangles& triangles = (TwoColorTriangles&)command->getTriangles();
			if (triangles.indices >= oldData && triangles.indices < oldData + oldSize) {
				triangles.indices = newData + (triangles.indices - oldData);
			}
		}
	}

	unsigned short* indices = _indices.buffer() + _indices.size();
	_indices.setSize(_indices.size() + numIndices, 0);
	return indices;
}

void SkeletonTwoColorBatch::deallocateIndices(uint32_t numIndices) {
	_indices.setSize(_indices.size() - numIndices, 0);
}

TwoColorTrianglesCommand* SkeletonTwoColorBatch::addCommand(cocos2d::Renderer* renderer, float globalOrder, cocos2d::Texture2D* texture, cocos2d::BlendFunc blendType, const TwoColorTriangles& triangles, const cocos2d::Mat4& mv, uint32_t flags) {
	TwoColorTrianglesCommand* command = nextFreeCommand();
	command->init(globalOrder, texture, blendType, triangles, mv, flags);
    command->updateVertexAndIndexBuffer(renderer, triangles.verts, triangles.vertCount, triangles.indices, triangles.indexCount);
	renderer->addCommand(command);
	return command;
}

void SkeletonTwoColorBatch::batch (cocos2d::Renderer *renderer, TwoColorTrianglesCommand* command) {
	if (_numVerticesBuffer + command->getTriangles().vertCount >= MAX_VERTICES || _numIndicesBuffer + command->getTriangles().indexCount >= MAX_INDICES) {
		flush(renderer, _lastCommand);
	}

	uint32_t materialID = command->getMaterialID();
	if (_lastCommand && _lastCommand->getMaterialID() != materialID) {
		flush(renderer, _lastCommand);
	}

	memcpy(_vertexBuffer + _numVerticesBuffer, command->getTriangles().verts, sizeof(V3F_C4B_C4B_T2F) * command->getTriangles().vertCount);
	const Mat4& modelView = command->getModelView();
	for (int i = _numVerticesBuffer; i < _numVerticesBuffer + command->getTriangles().vertCount; i++) {
		modelView.transformPoint(&_vertexBuffer[i].position);
	}

	unsigned short vertexOffset = (unsigned short)_numVerticesBuffer;
	unsigned short* indices = command->getTriangles().indices;
	for (int i = 0, j = _numIndicesBuffer; i < command->getTriangles().indexCount; i++, j++) {
		_indexBuffer[j] = indices[i] + vertexOffset;
	}

	_numVerticesBuffer += command->getTriangles().vertCount;
	_numIndicesBuffer += command->getTriangles().indexCount;

	if (command->isForceFlush()) {
		flush(renderer, command);
	}
	_lastCommand = command;
}

void SkeletonTwoColorBatch::flush (cocos2d::Renderer *renderer, TwoColorTrianglesCommand* materialCommand) {
	if (!materialCommand)
		return;

    materialCommand->updateVertexAndIndexBuffer(renderer, _vertexBuffer, _numVerticesBuffer, _indexBuffer, _numIndicesBuffer);

    renderer->addCommand(materialCommand);

    _numVerticesBuffer = 0;
	_numIndicesBuffer = 0;
	_numBatches++;
}

void SkeletonTwoColorBatch::reset() {
	_nextFreeCommand = 0;
	_numVertices = 0;
	_indices.setSize(0, 0);
	_numVerticesBuffer = 0;
	_numIndicesBuffer = 0;
	_lastCommand = nullptr;
	_numBatches = 0;
}

TwoColorTrianglesCommand* SkeletonTwoColorBatch::nextFreeCommand() {
	if (_commandsPool.size() <= _nextFreeCommand) {
		unsigned int newSize = _commandsPool.size() * 2 + 1;
		for (int i = _commandsPool.size();  i < newSize; i++) {
			_commandsPool.push_back(new TwoColorTrianglesCommand());
		}
	}
	TwoColorTrianglesCommand* command = _commandsPool[_nextFreeCommand++];
	command->setForceFlush(false);
	return command;
}
}

#endif
