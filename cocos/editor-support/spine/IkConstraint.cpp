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

#include <spine/IkConstraint.h>

#include <spine/IkConstraintData.h>
#include <spine/Skeleton.h>
#include <spine/Bone.h>

#include <spine/BoneData.h>

using namespace spine;

RTTI_IMPL(IkConstraint, Constraint)

void IkConstraint::apply(Bone &bone, float targetX, float targetY, bool compress, bool stretch, bool uniform, float alpha) {
	Bone *p = bone.getParent();
	float id, x, y, tx, ty, rotationIK;
	if (!bone._appliedValid) bone.updateAppliedTransform();
	id = 1 / (p->_a * p->_d - p->_b * p->_c);
	x = targetX - p->_worldX, y = targetY - p->_worldY;
	tx = (x * p->_d - y * p->_b) * id - bone._ax;
	ty = (y * p->_a - x * p->_c) * id - bone._ay;
	rotationIK = MathUtil::atan2(ty, tx) * MathUtil::Rad_Deg - bone._ashearX - bone._arotation;
	if (bone._ascaleX < 0) rotationIK += 180;
	if (rotationIK > 180) rotationIK -= 360;
	else if (rotationIK < -180) rotationIK += 360;
	float sx = bone._ascaleX;
	float sy = bone._ascaleY;
	if (compress || stretch) {
		float b = bone._data.getLength() * sx, dd = MathUtil::sqrt(tx * tx + ty * ty);
		if (((compress && dd < b) || (stretch && dd > b)) && (b > 0.0001f)) {
			float s = (dd / b - 1) * alpha + 1;
			sx *= s;
			if (uniform) sy *= s;
		}
	}
	bone.updateWorldTransform(bone._ax, bone._ay, bone._arotation + rotationIK * alpha, sx,
							  sy, bone._ashearX, bone._ashearY);
}

void IkConstraint::apply(Bone &parent, Bone &child, float targetX, float targetY, int bendDir, bool stretch, float alpha) {
	float px, py, psx, sx, psy;
	float cx, cy, csx, cwx, cwy;
	int o1, o2, s2, u;
	Bone *pp = parent.getParent();
	float tx, ty, dx, dy, dd, l1, l2, a1, a2, r;
	float id, x, y;
	if (alpha == 0) {
		child.updateWorldTransform();
		return;
	}
	if (!parent._appliedValid) parent.updateAppliedTransform();
	if (!child._appliedValid) child.updateAppliedTransform();
	px = parent._ax;
	py = parent._ay;
	psx = parent._ascaleX;
	sx = psx;
	psy = parent._ascaleY;
	csx = child._ascaleX;
	if (psx < 0) {
		psx = -psx;
		o1 = 180;
		s2 = -1;
	} else {
		o1 = 0;
		s2 = 1;
	}
	if (psy < 0) {
		psy = -psy;
		s2 = -s2;
	}
	if (csx < 0) {
		csx = -csx;
		o2 = 180;
	} else
		o2 = 0;
	r = psx - psy;
	cx = child._ax;
	u = (r < 0 ? -r : r) <= 0.0001f;
	if (!u) {
		cy = 0;
		cwx = parent._a * cx + parent._worldX;
		cwy = parent._c * cx + parent._worldY;
	} else {
		cy = child._ay;
		cwx = parent._a * cx + parent._b * cy + parent._worldX;
		cwy = parent._c * cx + parent._d * cy + parent._worldY;
	}
	id = 1 / (pp->_a * pp->_d - pp->_b * pp->_c);
	x = targetX - pp->_worldX;
	y = targetY - pp->_worldY;
	tx = (x * pp->_d - y * pp->_b) * id - px;
	ty = (y * pp->_a - x * pp->_c) * id - py;
	dd = tx * tx + ty * ty;
	x = cwx - pp->_worldX;
	y = cwy - pp->_worldY;
	dx = (x * pp->_d - y * pp->_b) * id - px;
	dy = (y * pp->_a - x * pp->_c) * id - py;
	l1 = MathUtil::sqrt(dx * dx + dy * dy);
	l2 = child.getData().getLength() * csx;
	if (u) {
		float cosine, a, b;
		l2 *= psx;
		cosine = (dd - l1 * l1 - l2 * l2) / (2 * l1 * l2);
		if (cosine < -1) cosine = -1;
		else if (cosine > 1) {
			cosine = 1;
			if (stretch && l1 + l2 > 0.0001f) sx *= (MathUtil::sqrt(dd) / (l1 + l2) - 1) * alpha + 1;
		}
		a2 = MathUtil::acos(cosine) * bendDir;
		a = l1 + l2 * cosine;
		b = l2 * MathUtil::sin(a2);
		a1 = MathUtil::atan2(ty * a - tx * b, tx * a + ty * b);
	} else {
		float a = psx * l2, b = psy * l2;
		float aa = a * a, bb = b * b, ll = l1 * l1, ta = MathUtil::atan2(ty, tx);
		float c0 = bb * ll + aa * dd - aa * bb, c1 = -2 * bb * l1, c2 = bb - aa;
		float d = c1 * c1 - 4 * c2 * c0;
		if (d >= 0) {
			float q = MathUtil::sqrt(d), r0, r1;
			if (c1 < 0) q = -q;
			q = -(c1 + q) / 2;
			r0 = q / c2;
			r1 = c0 / q;
			r = MathUtil::abs(r0) < MathUtil::abs(r1) ? r0 : r1;
			if (r * r <= dd) {
				y = MathUtil::sqrt(dd - r * r) * bendDir;
				a1 = ta - MathUtil::atan2(y, r);
				a2 = MathUtil::atan2(y / psy, (r - l1) / psx);
				goto break_outer;
			}
		}
		{
			float minAngle = MathUtil::Pi, minX = l1 - a, minDist = minX * minX, minY = 0;
			float maxAngle = 0, maxX = l1 + a, maxDist = maxX * maxX, maxY = 0;
			c0 = -a * l1 / (aa - bb);
			if (c0 >= -1 && c0 <= 1) {
				c0 = MathUtil::acos(c0);
				x = a * MathUtil::cos(c0) + l1;
				y = b * MathUtil::sin(c0);
				d = x * x + y * y;
				if (d < minDist) {
					minAngle = c0;
					minDist = d;
					minX = x;
					minY = y;
				}
				if (d > maxDist) {
					maxAngle = c0;
					maxDist = d;
					maxX = x;
					maxY = y;
				}
			}
			if (dd <= (minDist + maxDist) / 2) {
				a1 = ta - MathUtil::atan2(minY * bendDir, minX);
				a2 = minAngle * bendDir;
			} else {
				a1 = ta - MathUtil::atan2(maxY * bendDir, maxX);
				a2 = maxAngle * bendDir;
			}
		}
	}
	break_outer:
	{
		float os = MathUtil::atan2(cy, cx) * s2;
		a1 = (a1 - os) * MathUtil::Rad_Deg + o1 - parent._arotation;
		if (a1 > 180) a1 -= 360;
		else if (a1 < -180) a1 += 360;
		parent.updateWorldTransform(px, py, parent._rotation + a1 * alpha, sx, parent._ascaleY, 0, 0);
		a2 = ((a2 + os) * MathUtil::Rad_Deg - child._ashearX) * s2 + o2 - child._arotation;
		if (a2 > 180) a2 -= 360;
		else if (a2 < -180) a2 += 360;
		child.updateWorldTransform(cx, cy, child._arotation + a2 * alpha, child._ascaleX, child._ascaleY,
								   child._ashearX, child._ashearY);
	}
}

IkConstraint::IkConstraint(IkConstraintData &data, Skeleton &skeleton) : Constraint(),
																		 _data(data),
																		 _bendDirection(data.getBendDirection()),
																		 _compress(data.getCompress()),
																		 _stretch(data.getStretch()),
																		 _mix(data.getMix()),
																		 _target(skeleton.findBone(
																				 data.getTarget()->getName())) {
	_bones.ensureCapacity(_data.getBones().size());
	for (size_t i = 0; i < _data.getBones().size(); i++) {
		BoneData *boneData = _data.getBones()[i];
		_bones.add(skeleton.findBone(boneData->getName()));
	}
}

/// Applies the constraint to the constrained bones.
void IkConstraint::apply() {
	update();
}

void IkConstraint::update() {
	switch (_bones.size()) {
		case 1: {
			Bone *bone0 = _bones[0];
			apply(*bone0, _target->getWorldX(), _target->getWorldY(), _compress, _stretch, _data._uniform, _mix);
		}
			break;
		case 2: {
			Bone *bone0 = _bones[0];
			Bone *bone1 = _bones[1];
			apply(*bone0, *bone1, _target->getWorldX(), _target->getWorldY(), _bendDirection, _stretch, _mix);
		}
			break;
	}
}

int IkConstraint::getOrder() {
	return _data.getOrder();
}

IkConstraintData &IkConstraint::getData() {
	return _data;
}

Vector<Bone *> &IkConstraint::getBones() {
	return _bones;
}

Bone *IkConstraint::getTarget() {
	return _target;
}

void IkConstraint::setTarget(Bone *inValue) {
	_target = inValue;
}

int IkConstraint::getBendDirection() {
	return _bendDirection;
}

void IkConstraint::setBendDirection(int inValue) {
	_bendDirection = inValue;
}

float IkConstraint::getMix() {
	return _mix;
}

void IkConstraint::setMix(float inValue) {
	_mix = inValue;
}

bool IkConstraint::getStretch() {
	return _stretch;
}

void IkConstraint::setStretch(bool inValue) {
	_stretch = inValue;
}

bool IkConstraint::getCompress() {
	return _compress;
}

void IkConstraint::setCompress(bool inValue) {
	_compress = inValue;
}
