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

#include <spine/SkeletonClipping.h>

#include <spine/Slot.h>
#include <spine/ClippingAttachment.h>

using namespace spine;

SkeletonClipping::SkeletonClipping() : _clipAttachment(NULL) {
	_clipOutput.ensureCapacity(128);
	_clippedVertices.ensureCapacity(128);
	_clippedTriangles.ensureCapacity(128);
	_clippedUVs.ensureCapacity(128);
}

size_t SkeletonClipping::clipStart(Slot &slot, ClippingAttachment *clip) {
	if (_clipAttachment != NULL) {
		return 0;
	}

	_clipAttachment = clip;

	int n = clip->getWorldVerticesLength();
	_clippingPolygon.setSize(n, 0);
	clip->computeWorldVertices(slot, 0, n, _clippingPolygon, 0, 2);
	makeClockwise(_clippingPolygon);
	_clippingPolygons = &_triangulator.decompose(_clippingPolygon, _triangulator.triangulate(_clippingPolygon));

	for (size_t i = 0; i < _clippingPolygons->size(); ++i) {
		Vector<float> *polygonP = (*_clippingPolygons)[i];
		Vector<float> &polygon = *polygonP;
		makeClockwise(polygon);
		polygon.add(polygon[0]);
		polygon.add(polygon[1]);
	}

	return (*_clippingPolygons).size();
}

void SkeletonClipping::clipEnd(Slot &slot) {
	if (_clipAttachment != NULL && _clipAttachment->_endSlot == &slot._data) {
		clipEnd();
	}
}

void SkeletonClipping::clipEnd() {
	if (_clipAttachment == NULL) return;

	_clipAttachment = NULL;
	_clippingPolygons = NULL;
	_clippedVertices.clear();
	_clippedUVs.clear();
	_clippedTriangles.clear();
	_clippingPolygon.clear();
}

void SkeletonClipping::clipTriangles(Vector<float> &vertices, Vector<unsigned short> &triangles, Vector<float> &uvs, size_t stride) {
	clipTriangles(vertices.buffer(), triangles.buffer(), triangles.size(), uvs.buffer(), stride);
}

void SkeletonClipping::clipTriangles(float *vertices, unsigned short *triangles,
	size_t trianglesLength, float *uvs, size_t stride
) {
	Vector<float> &clipOutput = _clipOutput;
	Vector<float> &clippedVertices = _clippedVertices;
	Vector<unsigned short> &clippedTriangles = _clippedTriangles;
	Vector<Vector<float> *> &polygons = *_clippingPolygons;
	size_t polygonsCount = (*_clippingPolygons).size();

	size_t index = 0;
	clippedVertices.clear();
	_clippedUVs.clear();
	clippedTriangles.clear();

	size_t i = 0;
	continue_outer:
	for (; i < trianglesLength; i += 3) {
		int vertexOffset = triangles[i] * stride;
		float x1 = vertices[vertexOffset], y1 = vertices[vertexOffset + 1];
		float u1 = uvs[vertexOffset], v1 = uvs[vertexOffset + 1];

		vertexOffset = triangles[i + 1] * stride;
		float x2 = vertices[vertexOffset], y2 = vertices[vertexOffset + 1];
		float u2 = uvs[vertexOffset], v2 = uvs[vertexOffset + 1];

		vertexOffset = triangles[i + 2] * stride;
		float x3 = vertices[vertexOffset], y3 = vertices[vertexOffset + 1];
		float u3 = uvs[vertexOffset], v3 = uvs[vertexOffset + 1];

		for (size_t p = 0; p < polygonsCount; p++) {
			size_t s = clippedVertices.size();
			if (clip(x1, y1, x2, y2, x3, y3, &(*polygons[p]), &clipOutput)) {
				size_t clipOutputLength = clipOutput.size();
				if (clipOutputLength == 0) continue;
				float d0 = y2 - y3, d1 = x3 - x2, d2 = x1 - x3, d4 = y3 - y1;
				float d = 1 / (d0 * d2 + d1 * (y1 - y3));

				size_t clipOutputCount = clipOutputLength >> 1;
				clippedVertices.setSize(s + clipOutputCount * 2, 0);
				_clippedUVs.setSize(s + clipOutputCount * 2, 0);
				for (size_t ii = 0; ii < clipOutputLength; ii += 2) {
					float x = clipOutput[ii], y = clipOutput[ii + 1];
					clippedVertices[s] = x;
					clippedVertices[s + 1] = y;
					float c0 = x - x3, c1 = y - y3;
					float a = (d0 * c0 + d1 * c1) * d;
					float b = (d4 * c0 + d2 * c1) * d;
					float c = 1 - a - b;
					_clippedUVs[s] = u1 * a + u2 * b + u3 * c;
					_clippedUVs[s + 1] = v1 * a + v2 * b + v3 * c;
					s += 2;
				}

				s = clippedTriangles.size();
				clippedTriangles.setSize(s + 3 * (clipOutputCount - 2), 0);
				clipOutputCount--;
				for (size_t ii = 1; ii < clipOutputCount; ii++) {
					clippedTriangles[s] = (unsigned short)(index);
					clippedTriangles[s + 1] = (unsigned short)(index + ii);
					clippedTriangles[s + 2] = (unsigned short)(index + ii + 1);
					s += 3;
				}
				index += clipOutputCount + 1;
			} else {
				clippedVertices.setSize(s + 3 * 2, 0);
				_clippedUVs.setSize(s + 3 * 2, 0);
				clippedVertices[s] = x1;
				clippedVertices[s + 1] = y1;
				clippedVertices[s + 2] = x2;
				clippedVertices[s + 3] = y2;
				clippedVertices[s + 4] = x3;
				clippedVertices[s + 5] = y3;

				_clippedUVs[s] = u1;
				_clippedUVs[s + 1] = v1;
				_clippedUVs[s + 2] = u2;
				_clippedUVs[s + 3] = v2;
				_clippedUVs[s + 4] = u3;
				_clippedUVs[s + 5] = v3;

				s = clippedTriangles.size();
				clippedTriangles.setSize(s + 3, 0);
				clippedTriangles[s] = (unsigned short)index;
				clippedTriangles[s + 1] = (unsigned short)(index + 1);
				clippedTriangles[s + 2] = (unsigned short)(index + 2);
				index += 3;
				i += 3;
				goto continue_outer;
			}
		}
	}
}

bool SkeletonClipping::isClipping() {
	return _clipAttachment != NULL;
}

Vector<float> &SkeletonClipping::getClippedVertices() {
	return _clippedVertices;
}

Vector<unsigned short> &SkeletonClipping::getClippedTriangles() {
	return _clippedTriangles;
}

Vector<float> &SkeletonClipping::getClippedUVs() {
	return _clippedUVs;
}

bool SkeletonClipping::clip(float x1, float y1, float x2, float y2, float x3, float y3, Vector<float> *clippingArea,
	Vector<float> *output
) {
	Vector<float> *originalOutput = output;
	bool clipped = false;

	// Avoid copy at the end.
	Vector<float> *input;
	if (clippingArea->size() % 4 >= 2) {
		input = output;
		output = &_scratch;
	} else
		input = &_scratch;

	input->clear();
	input->add(x1);
	input->add(y1);
	input->add(x2);
	input->add(y2);
	input->add(x3);
	input->add(y3);
	input->add(x1);
	input->add(y1);
	output->clear();

	Vector<float> &clippingVertices = *clippingArea;
	size_t clippingVerticesLast = clippingArea->size() - 4;
	for (size_t i = 0;; i += 2) {
		float edgeX = clippingVertices[i], edgeY = clippingVertices[i + 1];
		float edgeX2 = clippingVertices[i + 2], edgeY2 = clippingVertices[i + 3];
		float deltaX = edgeX - edgeX2, deltaY = edgeY - edgeY2;

		Vector<float> &inputVertices = *input;
		size_t inputVerticesLength = input->size() - 2, outputStart = output->size();
		for (size_t ii = 0; ii < inputVerticesLength; ii += 2) {
			float inputX = inputVertices[ii], inputY = inputVertices[ii + 1];
			float inputX2 = inputVertices[ii + 2], inputY2 = inputVertices[ii + 3];
			bool side2 = deltaX * (inputY2 - edgeY2) - deltaY * (inputX2 - edgeX2) > 0;
			if (deltaX * (inputY - edgeY2) - deltaY * (inputX - edgeX2) > 0) {
				if (side2) {
					// v1 inside, v2 inside
					output->add(inputX2);
					output->add(inputY2);
					continue;
				}
				// v1 inside, v2 outside
				float c0 = inputY2 - inputY, c2 = inputX2 - inputX;
				float s = c0 * (edgeX2 - edgeX) - c2 * (edgeY2 - edgeY);
				if (MathUtil::abs(s) > 0.000001f) {
					float ua = (c2 * (edgeY - inputY) - c0 * (edgeX - inputX)) / s;
					output->add(edgeX + (edgeX2 - edgeX) * ua);
					output->add(edgeY + (edgeY2 - edgeY) * ua);
				} else {
					output->add(edgeX);
					output->add(edgeY);
				}
			} else if (side2) {
				// v1 outside, v2 inside
				float c0 = inputY2 - inputY, c2 = inputX2 - inputX;
				float s = c0 * (edgeX2 - edgeX) - c2 * (edgeY2 - edgeY);
				if (MathUtil::abs(s) > 0.000001f) {
					float ua = (c2 * (edgeY - inputY) - c0 * (edgeX - inputX)) / s;
					output->add(edgeX + (edgeX2 - edgeX) * ua);
					output->add(edgeY + (edgeY2 - edgeY) * ua);
				} else {
					output->add(edgeX);
					output->add(edgeY);
				}
				output->add(inputX2);
				output->add(inputY2);
			}
			clipped = true;
		}

		if (outputStart == output->size()) {
			// All edges outside.
			originalOutput->clear();
			return true;
		}

		output->add((*output)[0]);
		output->add((*output)[1]);

		if (i == clippingVerticesLast) {
			break;
		}
		Vector<float> *temp = output;
		output = input;
		output->clear();
		input = temp;
	}

	if (originalOutput != output) {
		originalOutput->clear();
		for (size_t i = 0, n = output->size() - 2; i < n; ++i)
			originalOutput->add((*output)[i]);
	} else
		originalOutput->setSize(originalOutput->size() - 2, 0);

	return clipped;
}

void SkeletonClipping::makeClockwise(Vector<float> &polygon) {
	size_t verticeslength = polygon.size();

	float area = polygon[verticeslength - 2] * polygon[1] - polygon[0] * polygon[verticeslength - 1];
	float p1x, p1y, p2x, p2y;

	for (size_t i = 0, n = verticeslength - 3; i < n; i += 2) {
		p1x = polygon[i];
		p1y = polygon[i + 1];
		p2x = polygon[i + 2];
		p2y = polygon[i + 3];
		area += p1x * p2y - p2x * p1y;
	}

	if (area < 0) return;

	for (size_t i = 0, lastX = verticeslength - 2, n = verticeslength >> 1; i < n; i += 2) {
		float x = polygon[i], y = polygon[i + 1];
		int other = lastX - i;
		polygon[i] = polygon[other];
		polygon[i + 1] = polygon[other + 1];
		polygon[other] = x;
		polygon[other + 1] = y;
	}
}
