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

#include <spine/DeformTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/VertexAttachment.h>

#include <spine/Animation.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>

using namespace spine;

RTTI_IMPL(DeformTimeline, CurveTimeline)

DeformTimeline::DeformTimeline(int frameCount) : CurveTimeline(frameCount), _slotIndex(0), _attachment(NULL) {
	_frames.ensureCapacity(frameCount);
	_frameVertices.ensureCapacity(frameCount);

	_frames.setSize(frameCount, 0);

	for (int i = 0; i < frameCount; ++i) {
		Vector<float> vec;
		_frameVertices.add(vec);
	}
}

void DeformTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
						   MixBlend blend, MixDirection direction) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	Slot *slotP = skeleton._slots[_slotIndex];
	Slot &slot = *slotP;

	Attachment *slotAttachment = slot.getAttachment();
	if (slotAttachment == NULL || !slotAttachment->getRTTI().instanceOf(VertexAttachment::rtti)) {
		return;
	}

	VertexAttachment *attachment = static_cast<VertexAttachment *>(slotAttachment);
	if (!attachment->applyDeform(_attachment)) {
		return;
	}

	Vector<float> &verticesArray = slot._attachmentVertices;
	if (verticesArray.size() == 0) {
		blend = MixBlend_Setup;
	}

	Vector< Vector<float> > &frameVertices = _frameVertices;
	size_t vertexCount = frameVertices[0].size();

	Vector<float> &frames = _frames;
	if (time < _frames[0]) {
		switch (blend) {
		case MixBlend_Setup:
			verticesArray.clear();
			return;
		case MixBlend_First: {
			if (alpha == 1) {
				verticesArray.clear();
				return;
			}
			verticesArray.setSize(vertexCount, 0);
			Vector<float> &vertices = verticesArray;
			if (attachment->getBones().size() == 0) {
				// Unweighted vertex positions.
				Vector<float> &setupVertices = attachment->getVertices();
				for (size_t i = 0; i < vertexCount; i++)
					vertices[i] += (setupVertices[i] - vertices[i]) * alpha;
			} else {
				// Weighted deform offsets.
				alpha = 1 - alpha;
				for (size_t i = 0; i < vertexCount; i++)
					vertices[i] *= alpha;
			}
		}
		case MixBlend_Replace:
		case MixBlend_Add:
			return;
		}
	}

	verticesArray.setSize(vertexCount, 0);
	Vector<float> &vertices = verticesArray;

	if (time >= frames[frames.size() - 1]) { // Time is after last frame.
		Vector<float> &lastVertices = frameVertices[frames.size() - 1];
		if (alpha == 1) {
			if (blend == MixBlend_Add) {
				VertexAttachment *vertexAttachment = static_cast<VertexAttachment*>(slotAttachment);
				if (vertexAttachment->getBones().size() == 0) {
					// Unweighted vertex positions, no alpha.
					Vector<float> &setupVertices = vertexAttachment->getVertices();
					for (size_t i = 0; i < vertexCount; i++)
						vertices[i] += lastVertices[i] - setupVertices[i];
				} else {
					// Weighted deform offsets, no alpha.
					for (size_t i = 0; i < vertexCount; i++)
						vertices[i] += lastVertices[i];
				}
			} else {
				// Vertex positions or deform offsets, no alpha.
				memcpy(vertices.buffer(), lastVertices.buffer(), vertexCount * sizeof(float));
			}
		} else {
			switch (blend) {
				case MixBlend_Setup: {
					VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
					if (vertexAttachment->getBones().size() == 0) {
						// Unweighted vertex positions, with alpha.
						Vector<float> &setupVertices = vertexAttachment->getVertices();
						for (size_t i = 0; i < vertexCount; i++) {
							float setup = setupVertices[i];
							vertices[i] = setup + (lastVertices[i] - setup) * alpha;
						}
					} else {
						// Weighted deform offsets, with alpha.
						for (size_t i = 0; i < vertexCount; i++)
							vertices[i] = lastVertices[i] * alpha;
					}
					break;
				}
				case MixBlend_First:
				case MixBlend_Replace:
					// Vertex positions or deform offsets, with alpha.
					for (size_t i = 0; i < vertexCount; i++)
						vertices[i] += (lastVertices[i] - vertices[i]) * alpha;
					break;
				case MixBlend_Add:
					VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
					if (vertexAttachment->getBones().size() == 0) {
						// Unweighted vertex positions, no alpha.
						Vector<float> &setupVertices = vertexAttachment->getVertices();
						for (size_t i = 0; i < vertexCount; i++)
							vertices[i] += (lastVertices[i] - setupVertices[i]) * alpha;
					} else {
						// Weighted deform offsets, alpha.
						for (size_t i = 0; i < vertexCount; i++)
							vertices[i] += lastVertices[i] * alpha;
					}
			}
		}
		return;
	}

	// Interpolate between the previous frame and the current frame.
	int frame = Animation::binarySearch(frames, time);
	Vector<float>  &prevVertices = frameVertices[frame - 1];
	Vector<float>  &nextVertices = frameVertices[frame];
	float frameTime = frames[frame];
	float percent = getCurvePercent(frame - 1, 1 - (time - frameTime) / (frames[frame - 1] - frameTime));

	if (alpha == 1) {
		if (blend == MixBlend_Add) {
			VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
			if (vertexAttachment->getBones().size() == 0) {
				// Unweighted vertex positions, no alpha.
				Vector<float> &setupVertices = vertexAttachment->getVertices();
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					vertices[i] += prev + (nextVertices[i] - prev) * percent - setupVertices[i];
				}
			} else {
				// Weighted deform offsets, no alpha.
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					vertices[i] += prev + (nextVertices[i] - prev) * percent;
				}
			}
		} else {
			// Vertex positions or deform offsets, no alpha.
			for (size_t i = 0; i < vertexCount; i++) {
				float prev = prevVertices[i];
				vertices[i] = prev + (nextVertices[i] - prev) * percent;
			}
		}
	} else {
		switch (blend) {
			case MixBlend_Setup: {
				VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
				if (vertexAttachment->getBones().size() == 0) {
					// Unweighted vertex positions, with alpha.
					Vector<float> &setupVertices = vertexAttachment->getVertices();
					for (size_t i = 0; i < vertexCount; i++) {
						float prev = prevVertices[i], setup = setupVertices[i];
						vertices[i] = setup + (prev + (nextVertices[i] - prev) * percent - setup) * alpha;
					}
				} else {
					// Weighted deform offsets, with alpha.
					for (size_t i = 0; i < vertexCount; i++) {
						float prev = prevVertices[i];
						vertices[i] = (prev + (nextVertices[i] - prev) * percent) * alpha;
					}
				}
				break;
			}
			case MixBlend_First:
			case MixBlend_Replace:
				// Vertex positions or deform offsets, with alpha.
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					vertices[i] += (prev + (nextVertices[i] - prev) * percent - vertices[i]) * alpha;
				}
				break;
			case MixBlend_Add:
				VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
				if (vertexAttachment->getBones().size() == 0) {
					// Unweighted vertex positions, with alpha.
					Vector<float> &setupVertices = vertexAttachment->getVertices();
					for (size_t i = 0; i < vertexCount; i++) {
						float prev = prevVertices[i];
						vertices[i] += (prev + (nextVertices[i] - prev) * percent - setupVertices[i]) * alpha;
					}
				} else {
					// Weighted deform offsets, with alpha.
					for (size_t i = 0; i < vertexCount; i++) {
						float prev = prevVertices[i];
						vertices[i] += (prev + (nextVertices[i] - prev) * percent) * alpha;
					}
				}
		}
	}
}

int DeformTimeline::getPropertyId() {
	assert(_attachment != NULL);

	return ((int) TimelineType_Deform << 24) + _attachment->_id + _slotIndex;
}

void DeformTimeline::setFrame(int frameIndex, float time, Vector<float> &vertices) {
	_frames[frameIndex] = time;
	_frameVertices[frameIndex].clear();
	_frameVertices[frameIndex].addAll(vertices);
}

int DeformTimeline::getSlotIndex() {
	return _slotIndex;
}

void DeformTimeline::setSlotIndex(int inValue) {
	_slotIndex = inValue;
}

Vector<float> &DeformTimeline::getFrames() {
	return _frames;
}

Vector<Vector<float> > &DeformTimeline::getVertices() {
	return _frameVertices;
}

VertexAttachment *DeformTimeline::getAttachment() {
	return _attachment;
}

void DeformTimeline::setAttachment(VertexAttachment *inValue) {
	_attachment = inValue;
}
