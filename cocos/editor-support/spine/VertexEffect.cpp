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

#include <spine/VertexEffect.h>
#include <spine/MathUtil.h>
#include <spine/Skeleton.h>

using namespace spine;

JitterVertexEffect::JitterVertexEffect(float jitterX, float jitterY): _jitterX(jitterX), _jitterY(jitterY) {
}

void JitterVertexEffect::begin(Skeleton &skeleton) {
	SP_UNUSED(skeleton);
}

void JitterVertexEffect::transform(float &x, float &y, float &u, float &v, Color &light, Color &dark) {
	SP_UNUSED(u);
	SP_UNUSED(v);
	SP_UNUSED(light);
	SP_UNUSED(dark);
	float jitterX = _jitterX;
	float jitterY = _jitterY;
	x += MathUtil::randomTriangular(-jitterX, jitterX);
	y += MathUtil::randomTriangular(-jitterX, jitterY);
}

void JitterVertexEffect::end() {
}

void JitterVertexEffect::setJitterX(float jitterX) {
	_jitterX = jitterX;
}

float JitterVertexEffect::getJitterX() {
	return _jitterX;
}

void JitterVertexEffect::setJitterY(float jitterY) {
	_jitterY = jitterY;
}

float JitterVertexEffect::getJitterY() {
	return _jitterY;
}

SwirlVertexEffect::SwirlVertexEffect(float radius, Interpolation &interpolation):
	_centerX(0),
	_centerY(0),
	_radius(radius),
	_angle(0),
	_worldX(0),
	_worldY(0),
	_interpolation(interpolation) {
}

void SwirlVertexEffect::begin(Skeleton &skeleton) {
	_worldX = skeleton.getX() + _centerX;
	_worldY = skeleton.getY() + _centerY;
}

void SwirlVertexEffect::transform(float &positionX, float &positionY, float &u, float &v, Color &light, Color &dark) {
	SP_UNUSED(u);
	SP_UNUSED(v);
	SP_UNUSED(light);
	SP_UNUSED(dark);

	float x = positionX - _worldX;
	float y = positionY - _worldY;
	float dist = (float)MathUtil::sqrt(x * x + y * y);
	if (dist < _radius) {
		float theta = _interpolation.interpolate(0, _angle, (_radius - dist) / _radius);
		float cos = MathUtil::cos(theta), sin = MathUtil::sin(theta);
		positionX = cos * x - sin * y + _worldX;
		positionY = sin * x + cos * y + _worldY;
	}
}

void SwirlVertexEffect::end() {

}

void SwirlVertexEffect::setCenterX(float centerX) {
	_centerX = centerX;
}

float SwirlVertexEffect::getCenterX() {
	return _centerX;
}

void SwirlVertexEffect::setCenterY(float centerY) {
	_centerY = centerY;
}

float SwirlVertexEffect::getCenterY() {
	return _centerY;
}

void SwirlVertexEffect::setRadius(float radius) {
	_radius = radius;
}

float SwirlVertexEffect::getRadius() {
	return _radius;
}

void SwirlVertexEffect::setAngle(float angle) {
	_angle = angle * MathUtil::Deg_Rad;
}

float SwirlVertexEffect::getAngle() {
	return _angle;
}

void SwirlVertexEffect::setWorldX(float worldX) {
	_worldX = worldX;
}

float SwirlVertexEffect::getWorldX() {
	return _worldX;
}

void SwirlVertexEffect::setWorldY(float worldY) {
	_worldY = worldY;
}

float SwirlVertexEffect::getWorldY() {
	return _worldY;
}
