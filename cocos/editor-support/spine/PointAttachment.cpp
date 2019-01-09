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

#include <spine/PointAttachment.h>

#include <spine/Bone.h>

#include <spine/MathUtil.h>

using namespace spine;

RTTI_IMPL(PointAttachment, Attachment)

PointAttachment::PointAttachment(const String &name) : Attachment(name), _x(0), _y(0), _rotation(0) {
}

void PointAttachment::computeWorldPosition(Bone &bone, float &ox, float &oy) {
	bone.localToWorld(_x, _y, ox, oy);
}

float PointAttachment::computeWorldRotation(Bone &bone) {
	float cos = MathUtil::cosDeg(_rotation);
	float sin = MathUtil::sinDeg(_rotation);
	float ix = cos * bone._a + sin * bone._b;
	float iy = cos * bone._c + sin * bone._d;

	return MathUtil::atan2(iy, ix) * MathUtil::Rad_Deg;
}

float PointAttachment::getX() {
	return _x;
}

void PointAttachment::setX(float inValue) {
	_x = inValue;
}

float PointAttachment::getY() {
	return _y;
}

void PointAttachment::setY(float inValue) {
	_y = inValue;
}

float PointAttachment::getRotation() {
	return _rotation;
}

void PointAttachment::setRotation(float inValue) {
	_rotation = inValue;
}
