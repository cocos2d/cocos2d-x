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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/MeshAttachment.h>
#include <spine/HasRendererObject.h>

using namespace spine;

RTTI_IMPL(MeshAttachment, VertexAttachment)

MeshAttachment::MeshAttachment(const String &name) : VertexAttachment(name), HasRendererObject(),
	_regionOffsetX(0),
	_regionOffsetY(0),
	_regionWidth(0),
	_regionHeight(0),
	_regionOriginalWidth(0),
	_regionOriginalHeight(0),
	_parentMesh(NULL),
	_path(),
	_regionU(0),
	_regionV(0),
	_regionU2(0),
	_regionV2(0),
	_width(0),
	_height(0),
	_color(1, 1, 1, 1),
	_hullLength(0),
	_regionRotate(false),
	_regionDegrees(0)
{}

MeshAttachment::~MeshAttachment() {}

void MeshAttachment::updateUVs() {
	if (_uvs.size() != _regionUVs.size()) {
		_uvs.setSize(_regionUVs.size(), 0);
	}

	int i = 0, n = _regionUVs.size();
	float u = _regionU, v = _regionV;
	float width = 0, height = 0;

	switch (_regionDegrees) {
	case 90: {
		float textureWidth = _regionHeight / (_regionU2 - _regionU);
		float textureHeight = _regionWidth / (_regionV2 - _regionV);
		u -= (_regionOriginalHeight - _regionOffsetY - _regionHeight) / textureWidth;
		v -= (_regionOriginalWidth - _regionOffsetX - _regionWidth) / textureHeight;
		width = _regionOriginalHeight / textureWidth;
		height = _regionOriginalWidth / textureHeight;
		for (i = 0; i < n; i += 2) {
			_uvs[i] = u + _regionUVs[i + 1] * width;
			_uvs[i + 1] = v + (1 - _regionUVs[i]) * height;
		}
		return;
	}
	case 180: {
		float textureWidth = _regionWidth / (_regionU2 - _regionU);
		float textureHeight = _regionHeight / (_regionV2 - _regionV);
		u -= (_regionOriginalWidth - _regionOffsetX - _regionWidth) / textureWidth;
		v -= _regionOffsetY / textureHeight;
		width = _regionOriginalWidth / textureWidth;
		height = _regionOriginalHeight / textureHeight;
		for (i = 0; i < n; i += 2) {
			_uvs[i] = u + (1 - _regionUVs[i]) * width;
			_uvs[i + 1] = v + (1 - _regionUVs[i + 1]) * height;
		}
		return;
	}
	case 270: {
		float textureHeight = _regionHeight / (_regionV2 - _regionV);
		float textureWidth = _regionWidth / (_regionU2 - _regionU);
		u -= _regionOffsetY / textureWidth;
		v -= _regionOffsetX / textureHeight;
		width = _regionOriginalHeight / textureWidth;
		height = _regionOriginalWidth / textureHeight;
		for (i = 0; i < n; i += 2) {
			_uvs[i] = u + (1 - _regionUVs[i + 1]) * width;
			_uvs[i + 1] = v + _regionUVs[i] * height;
		}
		return;
	}
	default: {
		float textureWidth = _regionWidth / (_regionU2 - _regionU);
		float textureHeight = _regionHeight / (_regionV2 - _regionV);
		u -= _regionOffsetX / textureWidth;
		v -= (_regionOriginalHeight - _regionOffsetY - _regionHeight) / textureHeight;
		width = _regionOriginalWidth / textureWidth;
		height = _regionOriginalHeight / textureHeight;
		for (i = 0; i < n; i += 2) {
			_uvs[i] = u + _regionUVs[i] * width;
			_uvs[i + 1] = v + _regionUVs[i + 1] * height;
		}
	}
	}
}

int MeshAttachment::getHullLength() {
	return _hullLength;
}

void MeshAttachment::setHullLength(int inValue) {
	_hullLength = inValue;
}

Vector<float> &MeshAttachment::getRegionUVs() {
	return _regionUVs;
}

Vector<float> &MeshAttachment::getUVs() {
	return _uvs;
}

Vector<unsigned short> &MeshAttachment::getTriangles() {
	return _triangles;
}

const String &MeshAttachment::getPath() {
	return _path;
}

void MeshAttachment::setPath(const String &inValue) {
	_path = inValue;
}

float MeshAttachment::getRegionU() {
	return _regionU;
}

void MeshAttachment::setRegionU(float inValue) {
	_regionU = inValue;
}

float MeshAttachment::getRegionV() {
	return _regionV;
}

void MeshAttachment::setRegionV(float inValue) {
	_regionV = inValue;
}

float MeshAttachment::getRegionU2() {
	return _regionU2;
}

void MeshAttachment::setRegionU2(float inValue) {
	_regionU2 = inValue;
}

float MeshAttachment::getRegionV2() {
	return _regionV2;
}

void MeshAttachment::setRegionV2(float inValue) {
	_regionV2 = inValue;
}

bool MeshAttachment::getRegionRotate() {
	return _regionRotate;
}

void MeshAttachment::setRegionRotate(bool inValue) {
	_regionRotate = inValue;
}

int MeshAttachment::getRegionDegrees() {
	return _regionDegrees;
}

void MeshAttachment::setRegionDegrees(int inValue) {
	_regionDegrees = inValue;
}

float MeshAttachment::getRegionOffsetX() {
	return _regionOffsetX;
}

void MeshAttachment::setRegionOffsetX(float inValue) {
	_regionOffsetX = inValue;
}

float MeshAttachment::getRegionOffsetY() {
	return _regionOffsetY;
}

void MeshAttachment::setRegionOffsetY(float inValue) {
	_regionOffsetY = inValue;
}

float MeshAttachment::getRegionWidth() {
	return _regionWidth;
}

void MeshAttachment::setRegionWidth(float inValue) {
	_regionWidth = inValue;
}

float MeshAttachment::getRegionHeight() {
	return _regionHeight;
}

void MeshAttachment::setRegionHeight(float inValue) {
	_regionHeight = inValue;
}

float MeshAttachment::getRegionOriginalWidth() {
	return _regionOriginalWidth;
}

void MeshAttachment::setRegionOriginalWidth(float inValue) {
	_regionOriginalWidth = inValue;
}

float MeshAttachment::getRegionOriginalHeight() {
	return _regionOriginalHeight;
}

void MeshAttachment::setRegionOriginalHeight(float inValue) {
	_regionOriginalHeight = inValue;
}

MeshAttachment *MeshAttachment::getParentMesh() {
	return _parentMesh;
}

void MeshAttachment::setParentMesh(MeshAttachment *inValue) {
	_parentMesh = inValue;
	if (inValue != NULL) {
		_bones.clearAndAddAll(inValue->_bones);
		_vertices.clearAndAddAll(inValue->_vertices);
		_worldVerticesLength = inValue->_worldVerticesLength;
		_regionUVs.clearAndAddAll(inValue->_regionUVs);
		_triangles.clearAndAddAll(inValue->_triangles);
		_hullLength = inValue->_hullLength;
		_edges.clearAndAddAll(inValue->_edges);
		_width = inValue->_width;
		_height = inValue->_height;
	}
}

Vector<unsigned short> &MeshAttachment::getEdges() {
	return _edges;
}

float MeshAttachment::getWidth() {
	return _width;
}

void MeshAttachment::setWidth(float inValue) {
	_width = inValue;
}

float MeshAttachment::getHeight() {
	return _height;
}

void MeshAttachment::setHeight(float inValue) {
	_height = inValue;
}

spine::Color &MeshAttachment::getColor() {
	return _color;
}

Attachment* MeshAttachment::copy() {
	if (_parentMesh) return newLinkedMesh();

	MeshAttachment* copy = new (__FILE__, __LINE__) MeshAttachment(getName());
	copy->setRendererObject(getRendererObject());
	copy->_regionU = _regionU;
	copy->_regionV = _regionV;
	copy->_regionU2 = _regionU2;
	copy->_regionV2 = _regionV2;
	copy->_regionRotate = _regionRotate;
	copy->_regionDegrees = _regionDegrees;
	copy->_regionOffsetX = _regionOffsetX;
	copy->_regionOffsetY = _regionOffsetY;
	copy->_regionWidth = _regionWidth;
	copy->_regionHeight = _regionHeight;
	copy->_regionOriginalWidth = _regionOriginalWidth;
	copy->_regionOriginalHeight = _regionOriginalHeight;
	copy->_path = _path;
	copy->_color.set(_color);

	copyTo(copy);
	copy->_regionUVs.clearAndAddAll(_regionUVs);
	copy->_uvs.clearAndAddAll(_uvs);
	copy->_triangles.clearAndAddAll(_triangles);
	copy->_hullLength = _hullLength;

	// Nonessential.
	copy->_edges.clearAndAddAll(copy->_edges);
	copy->_width = _width;
	copy->_height = _height;
	return copy;
}

MeshAttachment* MeshAttachment::newLinkedMesh() {
	MeshAttachment* copy = new (__FILE__, __LINE__) MeshAttachment(getName());
	copy->setRendererObject(getRendererObject());
	copy->_regionU = _regionU;
	copy->_regionV = _regionV;
	copy->_regionU2 = _regionU2;
	copy->_regionV2 = _regionV2;
	copy->_regionRotate = _regionRotate;
	copy->_regionDegrees = _regionDegrees;
	copy->_regionOffsetX = _regionOffsetX;
	copy->_regionOffsetY = _regionOffsetY;
	copy->_regionWidth = _regionWidth;
	copy->_regionHeight = _regionHeight;
	copy->_regionOriginalWidth = _regionOriginalWidth;
	copy->_regionOriginalHeight = _regionOriginalHeight;
	copy->_path = _path;
	copy->_color.set(_color);
	copy->_deformAttachment = this->_deformAttachment;
	copy->setParentMesh(_parentMesh ? _parentMesh : this);
	copy->updateUVs();
	return copy;
}
