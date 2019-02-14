/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "spine/SkeletonBatch.h"
#include "spine/extension.h"
#include <algorithm>

USING_NS_CC;
#define EVENT_AFTER_DRAW_RESET_POSITION "director_after_draw"
using std::max;
#define INITIAL_SIZE (10000)

namespace spine {

static SkeletonBatch* instance = nullptr;

SkeletonBatch* SkeletonBatch::getInstance () {
	if (!instance) instance = new SkeletonBatch();
	return instance;
}

void SkeletonBatch::destroyInstance () {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

SkeletonBatch::SkeletonBatch () {
	for (unsigned int i = 0; i < INITIAL_SIZE; i++) {
		_commandsPool.push_back(new TrianglesCommand());
	}
	
	_indices = spUnsignedShortArray_create(8);
	
	reset ();
		
	// callback after drawing is finished so we can clear out the batch state
	// for the next frame
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_AFTER_DRAW_RESET_POSITION, [this](EventCustom* eventCustom){
		this->update(0);
	});;
}

SkeletonBatch::~SkeletonBatch () {
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_AFTER_DRAW_RESET_POSITION);

	spUnsignedShortArray_dispose(_indices);
	
	for (unsigned int i = 0; i < _commandsPool.size(); i++) {
		delete _commandsPool[i];
		_commandsPool[i] = nullptr;
	}
}

void SkeletonBatch::update (float delta) {
	reset();
}
	
cocos2d::V3F_C4B_T2F* SkeletonBatch::allocateVertices(uint32_t numVertices) {
	if (_vertices.size() - _numVertices < numVertices) {
		cocos2d::V3F_C4B_T2F* oldData = _vertices.data();
		_vertices.resize((_vertices.size() + numVertices) * 2 + 1);
		cocos2d::V3F_C4B_T2F* newData = _vertices.data();
		for (uint32_t i = 0; i < this->_nextFreeCommand; i++) {
			TrianglesCommand* command = _commandsPool[i];
			cocos2d::TrianglesCommand::Triangles& triangles = (cocos2d::TrianglesCommand::Triangles&)command->getTriangles();
			triangles.verts = newData + (triangles.verts - oldData);
		}
	}
	
	cocos2d::V3F_C4B_T2F* vertices = _vertices.data() + _numVertices;
	_numVertices += numVertices;
	return vertices;
}
	
void SkeletonBatch::deallocateVertices(uint32_t numVertices) {
	_numVertices -= numVertices;
}

	
unsigned short* SkeletonBatch::allocateIndices(uint32_t numIndices) {	
	if (_indices->capacity - _indices->size < numIndices) {
		unsigned short* oldData = _indices->items;
		int oldSize = _indices->size;
		spUnsignedShortArray_ensureCapacity(_indices, _indices->size + numIndices);
		unsigned short* newData = _indices->items;
		for (uint32_t i = 0; i < this->_nextFreeCommand; i++) {
			TrianglesCommand* command = _commandsPool[i];
			cocos2d::TrianglesCommand::Triangles& triangles = (cocos2d::TrianglesCommand::Triangles&)command->getTriangles();
			if (triangles.indices >= oldData && triangles.indices < oldData + oldSize) {
				triangles.indices = newData + (triangles.indices - oldData);
			}
		}
	}
	
	unsigned short* indices = _indices->items + _indices->size;
	_indices->size += numIndices;
	return indices;
}

void SkeletonBatch::deallocateIndices(uint32_t numIndices) {
	_indices->size -= numIndices;
}

	
cocos2d::TrianglesCommand* SkeletonBatch::addCommand(cocos2d::Renderer* renderer, float globalOrder, cocos2d::Texture2D* texture, cocos2d::GLProgramState* glProgramState, cocos2d::BlendFunc blendType, const cocos2d::TrianglesCommand::Triangles& triangles, const cocos2d::Mat4& mv, uint32_t flags) {
	TrianglesCommand* command = nextFreeCommand();
	command->init(globalOrder, texture, glProgramState, blendType, triangles, mv, flags);
	renderer->addCommand(command);
	return command;
}

void SkeletonBatch::reset() {
	_nextFreeCommand = 0;
	_numVertices = 0;
	_indices->size = 0;
}

cocos2d::TrianglesCommand* SkeletonBatch::nextFreeCommand() {
	if (_commandsPool.size() <= _nextFreeCommand) {
		size_t newSize = _commandsPool.size() * 2 + 1;
		for (size_t i = _commandsPool.size();  i < newSize; i++) {
			_commandsPool.push_back(new TrianglesCommand());
		}
	}
	return _commandsPool[_nextFreeCommand++];
}
}
