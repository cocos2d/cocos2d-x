/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <spine/CCSkeleton.h>
#include <spine/spine-cocos2dx.h>

USING_NS_CC;
using std::min;
using std::max;

namespace cocos2d { namespace extension {

CCSkeleton* CCSkeleton::createWithData (SkeletonData* skeletonData, bool ownsSkeletonData) {
	CCSkeleton* node = new CCSkeleton(skeletonData, ownsSkeletonData);
	node->autorelease();
	return node;
}

CCSkeleton* CCSkeleton::createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale) {
	CCSkeleton* node = new CCSkeleton(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}

CCSkeleton* CCSkeleton::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	CCSkeleton* node = new CCSkeleton(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

void CCSkeleton::initialize () {
	atlas = 0;
	debugSlots = false;
	debugBones = false;
	timeScale = 1;

	blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
	setOpacityModifyRGB(true);

	setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
	scheduleUpdate();
}

void CCSkeleton::setSkeletonData (SkeletonData *skeletonData, bool ownsSkeletonData) {
	skeleton = Skeleton_create(skeletonData);
	rootBone = skeleton->bones[0];
	this->ownsSkeletonData = ownsSkeletonData;	
}

CCSkeleton::CCSkeleton () {
	initialize();
}

CCSkeleton::CCSkeleton (SkeletonData *skeletonData, bool ownsSkeletonData) {
	initialize();

	setSkeletonData(skeletonData, ownsSkeletonData);
}

CCSkeleton::CCSkeleton (const char* skeletonDataFile, Atlas* atlas, float scale) {
	initialize();

	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, skeletonDataFile);
	CCASSERT(skeletonData, json->error ? json->error : "Error reading skeleton data.");
	SkeletonJson_dispose(json);

	setSkeletonData(skeletonData, true);
}

CCSkeleton::CCSkeleton (const char* skeletonDataFile, const char* atlasFile, float scale) {
	initialize();

	atlas = Atlas_readAtlasFile(atlasFile);
	CCASSERT(atlas, "Error reading atlas file.");

	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, skeletonDataFile);
	CCASSERT(skeletonData, json->error ? json->error : "Error reading skeleton data file.");
	SkeletonJson_dispose(json);

	setSkeletonData(skeletonData, true);
}

CCSkeleton::~CCSkeleton () {
	if (ownsSkeletonData) SkeletonData_dispose(skeleton->data);
	if (atlas) Atlas_dispose(atlas);
	Skeleton_dispose(skeleton);
}

void CCSkeleton::update (float deltaTime) {
	Skeleton_update(skeleton, deltaTime * timeScale);
}

void CCSkeleton::draw () {
	CC_NODE_DRAW_SETUP();

	GL::blendFunc(blendFunc.src, blendFunc.dst);
	Color3B color = getColor();
	skeleton->r = color.r / (float)255;
	skeleton->g = color.g / (float)255;
	skeleton->b = color.b / (float)255;
	skeleton->a = getOpacity() / (float)255;
	if (premultipliedAlpha) {
		skeleton->r *= skeleton->a;
		skeleton->g *= skeleton->a;
		skeleton->b *= skeleton->a;
	}

	TextureAtlas* textureAtlas = 0;
	V3F_C4B_T2F_Quad quad;
	quad.tl.vertices.z = 0;
	quad.tr.vertices.z = 0;
	quad.bl.vertices.z = 0;
	quad.br.vertices.z = 0;
	for (int i = 0, n = skeleton->slotCount; i < n; i++) {
		Slot* slot = skeleton->slots[i];
		if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
		RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
		TextureAtlas* regionTextureAtlas = getTextureAtlas(attachment);
		if (regionTextureAtlas != textureAtlas) {
			if (textureAtlas) {
				textureAtlas->drawQuads();
				textureAtlas->removeAllQuads();
			}
		}
		textureAtlas = regionTextureAtlas;
		if (textureAtlas->getCapacity() == textureAtlas->getTotalQuads() &&
			!textureAtlas->resizeCapacity(textureAtlas->getCapacity() * 2)) return;
		RegionAttachment_updateQuad(attachment, slot, &quad, premultipliedAlpha);
		textureAtlas->updateQuad(&quad, textureAtlas->getTotalQuads());
	}
	if (textureAtlas) {
		textureAtlas->drawQuads();
		textureAtlas->removeAllQuads();
	}

	if (debugSlots) {
		// Slots.
		DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
		glLineWidth(1);
		Point points[4];
		V3F_C4B_T2F_Quad quad;
		for (int i = 0, n = skeleton->slotCount; i < n; i++) {
			Slot* slot = skeleton->slots[i];
			if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
			RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
			RegionAttachment_updateQuad(attachment, slot, &quad);
			points[0] = Point(quad.bl.vertices.x, quad.bl.vertices.y);
			points[1] = Point(quad.br.vertices.x, quad.br.vertices.y);
			points[2] = Point(quad.tr.vertices.x, quad.tr.vertices.y);
			points[3] = Point(quad.tl.vertices.x, quad.tl.vertices.y);
			DrawPrimitives::drawPoly(points, 4, true);
		}
	}
	if (debugBones) {
		// Bone lengths.
		glLineWidth(2);
		DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
		for (int i = 0, n = skeleton->boneCount; i < n; i++) {
			Bone *bone = skeleton->bones[i];
			float x = bone->data->length * bone->m00 + bone->worldX;
			float y = bone->data->length * bone->m10 + bone->worldY;
			DrawPrimitives::drawLine(Point(bone->worldX, bone->worldY), Point(x, y));
		}
		// Bone origins.
		DrawPrimitives::setPointSize(4);
		DrawPrimitives::setDrawColor4B(0, 0, 255, 255); // Root bone is blue.
		for (int i = 0, n = skeleton->boneCount; i < n; i++) {
			Bone *bone = skeleton->bones[i];
			DrawPrimitives::drawPoint(Point(bone->worldX, bone->worldY));
			if (i == 0) DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
		}
	}
}

TextureAtlas* CCSkeleton::getTextureAtlas (RegionAttachment* regionAttachment) const {
	return (TextureAtlas*)((AtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
}

Rect CCSkeleton::getBoundingBox() const {
	float minX = FLT_MAX, minY = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN;
	float scaleX = getScaleX();
	float scaleY = getScaleY();
	float vertices[8];
	for (int i = 0; i < skeleton->slotCount; ++i) {
		Slot* slot = skeleton->slots[i];
		if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
		RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
		RegionAttachment_computeVertices(attachment, slot->skeleton->x, slot->skeleton->y, slot->bone, vertices);
		minX = min(minX, vertices[VERTEX_X1] * scaleX);
		minY = min(minY, vertices[VERTEX_Y1] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X1] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y1] * scaleY);
		minX = min(minX, vertices[VERTEX_X4] * scaleX);
		minY = min(minY, vertices[VERTEX_Y4] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X4] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y4] * scaleY);
		minX = min(minX, vertices[VERTEX_X2] * scaleX);
		minY = min(minY, vertices[VERTEX_Y2] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X2] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y2] * scaleY);
		minX = min(minX, vertices[VERTEX_X3] * scaleX);
		minY = min(minY, vertices[VERTEX_Y3] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X3] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y3] * scaleY);
	}
	Point position = getPosition();
	return Rect(position.x + minX, position.y + minY, maxX - minX, maxY - minY);
}

// --- Convenience methods for Skeleton_* functions.

void CCSkeleton::updateWorldTransform () {
	Skeleton_updateWorldTransform(skeleton);
}

void CCSkeleton::setToSetupPose () {
	Skeleton_setToSetupPose(skeleton);
}
void CCSkeleton::setBonesToSetupPose () {
	Skeleton_setBonesToSetupPose(skeleton);
}
void CCSkeleton::setSlotsToSetupPose () {
	Skeleton_setSlotsToSetupPose(skeleton);
}

Bone* CCSkeleton::findBone (const char* boneName) const {
	return Skeleton_findBone(skeleton, boneName);
}

Slot* CCSkeleton::findSlot (const char* slotName) const {
	return Skeleton_findSlot(skeleton, slotName);
}

bool CCSkeleton::setSkin (const char* skinName) {
	return Skeleton_setSkinByName(skeleton, skinName) ? true : false;
}

Attachment* CCSkeleton::getAttachment (const char* slotName, const char* attachmentName) const {
	return Skeleton_getAttachmentForSlotName(skeleton, slotName, attachmentName);
}
bool CCSkeleton::setAttachment (const char* slotName, const char* attachmentName) {
	return Skeleton_setAttachment(skeleton, slotName, attachmentName) ? true : false;
}

// --- BlendProtocol

const BlendFunc& CCSkeleton::getBlendFunc() const
{
    return blendFunc;
}

void CCSkeleton::setBlendFunc( const BlendFunc &blendFunc) {
    this->blendFunc = blendFunc;
}

void CCSkeleton::setOpacityModifyRGB (bool value) {
	premultipliedAlpha = value;
}

bool CCSkeleton::isOpacityModifyRGB () const {
	return premultipliedAlpha;
}

}} // namespace cocos2d { namespace extension {
