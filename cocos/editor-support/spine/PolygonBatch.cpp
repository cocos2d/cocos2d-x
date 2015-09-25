/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/PolygonBatch.h>
#include <spine/extension.h>

USING_NS_CC;

namespace spine {

PolygonBatch* PolygonBatch::createWithCapacity (ssize_t capacity) {
	PolygonBatch* batch = new PolygonBatch();
	batch->initWithCapacity(capacity);
	batch->autorelease();
	return batch;
}

PolygonBatch::PolygonBatch () :
	_capacity(0),
	_vertices(nullptr), _verticesCount(0),
	_triangles(nullptr), _trianglesCount(0),
	_texture(nullptr)
{}

bool PolygonBatch::initWithCapacity (ssize_t capacity) {
	// 32767 is max index, so 32767 / 3 - (32767 / 3 % 3) = 10920.
	CCASSERT(capacity <= 10920, "capacity cannot be > 10920");
	CCASSERT(capacity >= 0, "capacity cannot be < 0");
	_capacity = capacity;
	_vertices = MALLOC(V2F_C4B_T2F, capacity);
	_triangles = MALLOC(GLushort, capacity * 3);
	return true;
}

PolygonBatch::~PolygonBatch () {
	FREE(_vertices);
	FREE(_triangles);
}

void PolygonBatch::add (const Texture2D* addTexture,
		const float* addVertices, const float* uvs, int addVerticesCount,
		const int* addTriangles, int addTrianglesCount,
		Color4B* color) {

	if (
		addTexture != _texture
		|| _verticesCount + (addVerticesCount >> 1) > _capacity
		|| _trianglesCount + addTrianglesCount > _capacity * 3) {
		this->flush();
		_texture = addTexture;
	}

	for (int i = 0; i < addTrianglesCount; ++i, ++_trianglesCount)
		_triangles[_trianglesCount] = addTriangles[i] + _verticesCount;

	for (int i = 0; i < addVerticesCount; i += 2, ++_verticesCount) {
		V2F_C4B_T2F* vertex = _vertices + _verticesCount;
		vertex->vertices.x = addVertices[i];
		vertex->vertices.y = addVertices[i + 1];
		vertex->colors = *color;
		vertex->texCoords.u = uvs[i];
		vertex->texCoords.v = uvs[i + 1];
	}
}

void PolygonBatch::flush () {
	if (!_verticesCount) return;

	GL::bindTexture2D(_texture->getName());
	GL::bindVAO(0);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), &_vertices[0].vertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), &_vertices[0].colors);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), &_vertices[0].texCoords);

	glDrawElements(GL_TRIANGLES, _trianglesCount, GL_UNSIGNED_SHORT, _triangles);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _verticesCount);

	_verticesCount = 0;
	_trianglesCount = 0;

	CHECK_GL_ERROR_DEBUG();
}

}
