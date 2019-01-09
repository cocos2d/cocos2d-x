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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/RegionAttachment.h>

#include <spine/Bone.h>

#include <assert.h>

using namespace spine;

RTTI_IMPL(RegionAttachment, Attachment)

const int RegionAttachment::BLX = 0;
const int RegionAttachment::BLY = 1;
const int RegionAttachment::ULX = 2;
const int RegionAttachment::ULY = 3;
const int RegionAttachment::URX = 4;
const int RegionAttachment::URY = 5;
const int RegionAttachment::BRX = 6;
const int RegionAttachment::BRY = 7;

RegionAttachment::RegionAttachment(const String &name) : Attachment(name), HasRendererObject(),
														 _x(0),
														 _y(0),
														 _rotation(0),
														 _scaleX(1),
														 _scaleY(1),
														 _width(0),
														 _height(0),
														 _regionOffsetX(0),
														 _regionOffsetY(0),
														 _regionWidth(0),
														 _regionHeight(0),
														 _regionOriginalWidth(0),
														 _regionOriginalHeight(0),
														 _path(),
														 _regionU(0),
														 _regionV(0),
														 _regionU2(0),
														 _regionV2(0),
														 _color(1, 1, 1, 1) {
	_vertexOffset.setSize(NUM_UVS, 0);
	_uvs.setSize(NUM_UVS, 0);
}

void RegionAttachment::updateOffset() {
	float regionScaleX = _width / _regionOriginalWidth * _scaleX;
	float regionScaleY = _height / _regionOriginalHeight * _scaleY;
	float localX = -_width / 2 * _scaleX + _regionOffsetX * regionScaleX;
	float localY = -_height / 2 * _scaleY + _regionOffsetY * regionScaleY;
	float localX2 = localX + _regionWidth * regionScaleX;
	float localY2 = localY + _regionHeight * regionScaleY;
	float cos = MathUtil::cosDeg(_rotation);
	float sin = MathUtil::sinDeg(_rotation);
	float localXCos = localX * cos + _x;
	float localXSin = localX * sin;
	float localYCos = localY * cos + _y;
	float localYSin = localY * sin;
	float localX2Cos = localX2 * cos + _x;
	float localX2Sin = localX2 * sin;
	float localY2Cos = localY2 * cos + _y;
	float localY2Sin = localY2 * sin;

	_vertexOffset[BLX] = localXCos - localYSin;
	_vertexOffset[BLY] = localYCos + localXSin;
	_vertexOffset[ULX] = localXCos - localY2Sin;
	_vertexOffset[ULY] = localY2Cos + localXSin;
	_vertexOffset[URX] = localX2Cos - localY2Sin;
	_vertexOffset[URY] = localY2Cos + localX2Sin;
	_vertexOffset[BRX] = localX2Cos - localYSin;
	_vertexOffset[BRY] = localYCos + localX2Sin;
}

void RegionAttachment::setUVs(float u, float v, float u2, float v2, bool rotate) {
	if (rotate) {
		_uvs[URX] = u;
		_uvs[URY] = v2;
		_uvs[BRX] = u;
		_uvs[BRY] = v;
		_uvs[BLX] = u2;
		_uvs[BLY] = v;
		_uvs[ULX] = u2;
		_uvs[ULY] = v2;
	} else {
		_uvs[ULX] = u;
		_uvs[ULY] = v2;
		_uvs[URX] = u;
		_uvs[URY] = v;
		_uvs[BRX] = u2;
		_uvs[BRY] = v;
		_uvs[BLX] = u2;
		_uvs[BLY] = v2;
	}
}

void RegionAttachment::computeWorldVertices(Bone &bone, Vector<float> &worldVertices, size_t offset, size_t stride) {
	assert(worldVertices.size() >= (offset + 8));
	computeWorldVertices(bone, worldVertices.buffer(), offset, stride);
}

void RegionAttachment::computeWorldVertices(Bone &bone, float* worldVertices, size_t offset, size_t stride) {
	float x = bone.getWorldX(), y = bone.getWorldY();
	float a = bone.getA(), b = bone.getB(), c = bone.getC(), d = bone.getD();
	float offsetX, offsetY;

	offsetX = _vertexOffset[BRX];
	offsetY = _vertexOffset[BRY];
	worldVertices[offset] = offsetX * a + offsetY * b + x; // br
	worldVertices[offset + 1] = offsetX * c + offsetY * d + y;
	offset += stride;

	offsetX = _vertexOffset[BLX];
	offsetY = _vertexOffset[BLY];
	worldVertices[offset] = offsetX * a + offsetY * b + x; // bl
	worldVertices[offset + 1] = offsetX * c + offsetY * d + y;
	offset += stride;

	offsetX = _vertexOffset[ULX];
	offsetY = _vertexOffset[ULY];
	worldVertices[offset] = offsetX * a + offsetY * b + x; // ul
	worldVertices[offset + 1] = offsetX * c + offsetY * d + y;
	offset += stride;

	offsetX = _vertexOffset[URX];
	offsetY = _vertexOffset[URY];
	worldVertices[offset] = offsetX * a + offsetY * b + x; // ur
	worldVertices[offset + 1] = offsetX * c + offsetY * d + y;
}

float RegionAttachment::getX() {
	return _x;
}

void RegionAttachment::setX(float inValue) {
	_x = inValue;
}

float RegionAttachment::getY() {
	return _y;
}

void RegionAttachment::setY(float inValue) {
	_y = inValue;
}

float RegionAttachment::getRotation() {
	return _rotation;
}

void RegionAttachment::setRotation(float inValue) {
	_rotation = inValue;
}

float RegionAttachment::getScaleX() {
	return _scaleX;
}

void RegionAttachment::setScaleX(float inValue) {
	_scaleX = inValue;
}

float RegionAttachment::getScaleY() {
	return _scaleY;
}

void RegionAttachment::setScaleY(float inValue) {
	_scaleY = inValue;
}

float RegionAttachment::getWidth() {
	return _width;
}

void RegionAttachment::setWidth(float inValue) {
	_width = inValue;
}

float RegionAttachment::getHeight() {
	return _height;
}

void RegionAttachment::setHeight(float inValue) {
	_height = inValue;
}

const String &RegionAttachment::getPath() {
	return _path;
}

void RegionAttachment::setPath(const String &inValue) {
	_path = inValue;
}

float RegionAttachment::getRegionOffsetX() {
	return _regionOffsetX;
}

void RegionAttachment::setRegionOffsetX(float inValue) {
	_regionOffsetX = inValue;
}

float RegionAttachment::getRegionOffsetY() {
	return _regionOffsetY;
}

void RegionAttachment::setRegionOffsetY(float inValue) {
	_regionOffsetY = inValue;
}

float RegionAttachment::getRegionWidth() {
	return _regionWidth;
}

void RegionAttachment::setRegionWidth(float inValue) {
	_regionWidth = inValue;
}

float RegionAttachment::getRegionHeight() {
	return _regionHeight;
}

void RegionAttachment::setRegionHeight(float inValue) {
	_regionHeight = inValue;
}

float RegionAttachment::getRegionOriginalWidth() {
	return _regionOriginalWidth;
}

void RegionAttachment::setRegionOriginalWidth(float inValue) {
	_regionOriginalWidth = inValue;
}

float RegionAttachment::getRegionOriginalHeight() {
	return _regionOriginalHeight;
}

void RegionAttachment::setRegionOriginalHeight(float inValue) {
	_regionOriginalHeight = inValue;
}

Vector<float> &RegionAttachment::getOffset() {
	return _vertexOffset;
}

Vector<float> &RegionAttachment::getUVs() {
	return _uvs;
}

spine::Color &RegionAttachment::getColor() {
	return _color;
}
