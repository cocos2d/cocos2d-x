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

Attachment* PointAttachment::copy() {
	PointAttachment* copy = new(__FILE__, __LINE__) PointAttachment(getName());
	copy->_x = _x;
	copy->_y = _y;
	copy->_rotation = _rotation;
	return copy;
}
