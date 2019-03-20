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

#include <spine/CurveTimeline.h>

#include <spine/MathUtil.h>

using namespace spine;

RTTI_IMPL(CurveTimeline, Timeline)

const float CurveTimeline::LINEAR = 0;
const float CurveTimeline::STEPPED = 1;
const float CurveTimeline::BEZIER = 2;
const int CurveTimeline::BEZIER_SIZE = 10 * 2 - 1;

CurveTimeline::CurveTimeline(int frameCount) {
	assert(frameCount > 0);

	_curves.setSize((frameCount - 1) * BEZIER_SIZE, 0);
}

CurveTimeline::~CurveTimeline() {
}

size_t CurveTimeline::getFrameCount() {
	return _curves.size() / BEZIER_SIZE + 1;
}

void CurveTimeline::setLinear(size_t frameIndex) {
	_curves[frameIndex * BEZIER_SIZE] = LINEAR;
}

void CurveTimeline::setStepped(size_t frameIndex) {
	_curves[frameIndex * BEZIER_SIZE] = STEPPED;
}

void CurveTimeline::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	float tmpx = (-cx1 * 2 + cx2) * 0.03f, tmpy = (-cy1 * 2 + cy2) * 0.03f;
	float dddfx = ((cx1 - cx2) * 3 + 1) * 0.006f, dddfy = ((cy1 - cy2) * 3 + 1) * 0.006f;
	float ddfx = tmpx * 2 + dddfx, ddfy = tmpy * 2 + dddfy;
	float dfx = cx1 * 0.3f + tmpx + dddfx * 0.16666667f, dfy = cy1 * 0.3f + tmpy + dddfy * 0.16666667f;

	size_t i = frameIndex * BEZIER_SIZE;
	_curves[i++] = BEZIER;

	float x = dfx, y = dfy;
	for (size_t n = i + BEZIER_SIZE - 1; i < n; i += 2) {
		_curves[i] = x;
		_curves[i + 1] = y;
		dfx += ddfx;
		dfy += ddfy;
		ddfx += dddfx;
		ddfy += dddfy;
		x += dfx;
		y += dfy;
	}
}

float CurveTimeline::getCurvePercent(size_t frameIndex, float percent) {
	percent = MathUtil::clamp(percent, 0, 1);
	size_t i = frameIndex * BEZIER_SIZE;
	float type = _curves[i];

	if (type == LINEAR) {
		return percent;
	}

	if (type == STEPPED) {
		return 0;
	}

	i++;
	float x = 0;
	for (size_t start = i, n = i + BEZIER_SIZE - 1; i < n; i += 2) {
		x = _curves[i];
		if (x >= percent) {
			float prevX, prevY;
			if (i == start) {
				prevX = 0;
				prevY = 0;
			} else {
				prevX = _curves[i - 2];
				prevY = _curves[i - 1];
			}

			return prevY + (_curves[i + 1] - prevY) * (percent - prevX) / (x - prevX);
		}
	}

	float y = _curves[i - 1];

	return y + (1 - y) * (percent - x) / (1 - x); // Last point is 1,1.
}

float CurveTimeline::getCurveType(size_t frameIndex) {
	return _curves[frameIndex * BEZIER_SIZE];
}
