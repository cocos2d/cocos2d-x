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

#include <spine/spine-cocos2dx.h>
#include <spine/extension.h>

USING_NS_CC;
using std::min;
using std::max;
namespace cocos2d { namespace extension {

void _AtlasPage_createTexture (AtlasPage* self, const char* path) {
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(path);
	CCTextureAtlas* textureAtlas = CCTextureAtlas::createWithTexture(texture, 4);
	textureAtlas->retain();
	self->texture = textureAtlas;
    
    // Using getContentSize to make it supports the strategy of loading resources in cocos2d-x.
    
//  self->width = texture->getPixelsWide();
//	self->height = texture->getPixelsHigh();
    
	self->width = texture->getContentSize().width;
	self->height = texture->getContentSize().height;
}

void _AtlasPage_disposeTexture (AtlasPage* self) {
	((CCTextureAtlas*)self->texture)->release();
}

char* _Util_readFile (const char* path, int* length) {
	unsigned long size;
    char* data = reinterpret_cast<char*>(CCFileUtils::sharedFileUtils()->getFileData(path, "r", &size));
	*length = size;
	return data;
}

/**/

void RegionAttachment_updateQuad (RegionAttachment* self, Slot* slot, ccV3F_C4B_T2F_Quad* quad) {
	RegionAttachment_updateVertices(self, slot);

	GLubyte r = slot->skeleton->r * slot->r * 255;
	GLubyte g = slot->skeleton->g * slot->g * 255;
	GLubyte b = slot->skeleton->b * slot->b * 255;
	GLubyte a = slot->skeleton->a * slot->a * 255;
	quad->bl.colors.r = r;
	quad->bl.colors.g = g;
	quad->bl.colors.b = b;
	quad->bl.colors.a = a;
	quad->tl.colors.r = r;
	quad->tl.colors.g = g;
	quad->tl.colors.b = b;
	quad->tl.colors.a = a;
	quad->tr.colors.r = r;
	quad->tr.colors.g = g;
	quad->tr.colors.b = b;
	quad->tr.colors.a = a;
	quad->br.colors.r = r;
	quad->br.colors.g = g;
	quad->br.colors.b = b;
	quad->br.colors.a = a;

	quad->bl.vertices.x = self->vertices[VERTEX_X1];
	quad->bl.vertices.y = self->vertices[VERTEX_Y1];
	quad->tl.vertices.x = self->vertices[VERTEX_X2];
	quad->tl.vertices.y = self->vertices[VERTEX_Y2];
	quad->tr.vertices.x = self->vertices[VERTEX_X3];
	quad->tr.vertices.y = self->vertices[VERTEX_Y3];
	quad->br.vertices.x = self->vertices[VERTEX_X4];
	quad->br.vertices.y = self->vertices[VERTEX_Y4];

	if (self->region->rotate) {
		quad->tl.texCoords.u = self->region->u;
		quad->tl.texCoords.v = self->region->v2;
		quad->tr.texCoords.u = self->region->u;
		quad->tr.texCoords.v = self->region->v;
		quad->br.texCoords.u = self->region->u2;
		quad->br.texCoords.v = self->region->v;
		quad->bl.texCoords.u = self->region->u2;
		quad->bl.texCoords.v = self->region->v2;
	} else {
		quad->bl.texCoords.u = self->region->u;
		quad->bl.texCoords.v = self->region->v2;
		quad->tl.texCoords.u = self->region->u;
		quad->tl.texCoords.v = self->region->v;
		quad->tr.texCoords.u = self->region->u2;
		quad->tr.texCoords.v = self->region->v;
		quad->br.texCoords.u = self->region->u2;
		quad->br.texCoords.v = self->region->v2;
	}
}

/**/

CCSkeleton* CCSkeleton::createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale) {
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, skeletonDataFile);
	SkeletonJson_dispose(json);
	CCSkeleton* node = skeletonData ? createWithData(skeletonData) : 0;
	node->ownsSkeleton = true;
	return node;
}

CCSkeleton* CCSkeleton::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	Atlas* atlas = Atlas_readAtlasFile(atlasFile);
	if (!atlas) return 0;
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, skeletonDataFile);
	SkeletonJson_dispose(json);
	if (!skeletonData) {
		Atlas_dispose(atlas);
		return 0;
	}
	CCSkeleton* node = createWithData(skeletonData);
	node->ownsSkeleton = true;
	node->atlas = atlas;
	return node;
}

CCSkeleton* CCSkeleton::createWithData (SkeletonData* skeletonData, AnimationStateData* stateData) {
	CCSkeleton* node = new CCSkeleton(skeletonData, stateData);
	node->autorelease();
	return node;
}

CCSkeleton::CCSkeleton (SkeletonData *skeletonData, AnimationStateData *stateData) :
				ownsSkeleton(false), ownsStateData(false), atlas(0),
				skeleton(0), state(0), debugSlots(false), debugBones(false) {
	CONST_CAST(Skeleton*, skeleton) = Skeleton_create(skeletonData);

	if (!stateData) {
		stateData = AnimationStateData_create(skeletonData);
		ownsStateData = true;
	}
	CONST_CAST(AnimationState*, state) = AnimationState_create(stateData);

	blendFunc.src = GL_ONE;
	blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;

	timeScale = 1;

	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
	scheduleUpdate();
}

CCSkeleton::~CCSkeleton () {
	if (ownsSkeleton) Skeleton_dispose(skeleton);
	if (ownsStateData) AnimationStateData_dispose(state->data);
	if (atlas) Atlas_dispose(atlas);
	AnimationState_dispose(state);
}

void CCSkeleton::update (float deltaTime) {
	Skeleton_update(skeleton, deltaTime);
	AnimationState_update(state, deltaTime * timeScale);
	AnimationState_apply(state, skeleton);
	Skeleton_updateWorldTransform(skeleton);
}

void CCSkeleton::draw () {
	CC_NODE_DRAW_SETUP();

	ccGLBlendFunc(blendFunc.src, blendFunc.dst);
	ccColor3B color = getColor();
	skeleton->r = color.r / (float)255;
	skeleton->g = color.g / (float)255;
	skeleton->b = color.b / (float)255;
	skeleton->a = getOpacity() / (float)255;

	CCTextureAtlas* textureAtlas = 0;
	ccV3F_C4B_T2F_Quad quad;
	quad.tl.vertices.z = 0;
	quad.tr.vertices.z = 0;
	quad.bl.vertices.z = 0;
	quad.br.vertices.z = 0;
	for (int i = 0, n = skeleton->slotCount; i < n; i++) {
		Slot* slot = skeleton->slots[i];
		if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
		RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
		CCTextureAtlas* regionTextureAtlas = (CCTextureAtlas*)attachment->region->page->texture;
		if (regionTextureAtlas != textureAtlas) {
			if (textureAtlas) {
				textureAtlas->drawQuads();
				textureAtlas->removeAllQuads();
			}
		}
		textureAtlas = regionTextureAtlas;
		if (textureAtlas->getCapacity() == textureAtlas->getTotalQuads() &&
			!textureAtlas->resizeCapacity(textureAtlas->getCapacity() * 2)) return;
		RegionAttachment_updateQuad(attachment, slot, &quad);
		textureAtlas->updateQuad(&quad, textureAtlas->getTotalQuads());
	}
	if (textureAtlas) {
		textureAtlas->drawQuads();
		textureAtlas->removeAllQuads();
	}

	if (debugSlots) {
		// Slots.
		ccDrawColor4B(0, 0, 255, 255);
		glLineWidth(1);
		CCPoint points[4];
		ccV3F_C4B_T2F_Quad quad;
		for (int i = 0, n = skeleton->slotCount; i < n; i++) {
			Slot* slot = skeleton->slots[i];
			if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
			RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
			RegionAttachment_updateQuad(attachment, slot, &quad);
			points[0] = ccp(quad.bl.vertices.x, quad.bl.vertices.y);
			points[1] = ccp(quad.br.vertices.x, quad.br.vertices.y);
			points[2] = ccp(quad.tr.vertices.x, quad.tr.vertices.y);
			points[3] = ccp(quad.tl.vertices.x, quad.tl.vertices.y);
			ccDrawPoly(points, 4, true);
		}
	}
	if (debugBones) {
		// Bone lengths.
		glLineWidth(2);
		ccDrawColor4B(255, 0, 0, 255);
		for (int i = 0, n = skeleton->boneCount; i < n; i++) {
			Bone *bone = skeleton->bones[i];
			float x = bone->data->length * bone->m00 + bone->worldX;
			float y = bone->data->length * bone->m10 + bone->worldY;
			ccDrawLine(ccp(bone->worldX, bone->worldY), ccp(x, y));
		}
		// Bone origins.
		ccPointSize(4);
		ccDrawColor4B(0, 0, 255, 255); // Root bone is blue.
		for (int i = 0, n = skeleton->boneCount; i < n; i++) {
			Bone *bone = skeleton->bones[i];
			ccDrawPoint(ccp(bone->worldX, bone->worldY));
			if (i == 0) ccDrawColor4B(0, 255, 0, 255);
		}
	}
}

CCRect CCSkeleton::boundingBox () {
	float minX = FLT_MAX, minY = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN;
	float scaleX = getScaleX();
	float scaleY = getScaleY();
	ccV3F_C4B_T2F_Quad quad;
	for (int i = 0; i < skeleton->slotCount; ++i) {
		Slot* slot = skeleton->slots[i];
		if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
		RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
		RegionAttachment_updateQuad(attachment, slot, &quad);
		minX = min(minX, quad.bl.vertices.x * scaleX);
		minY = min(minY, quad.bl.vertices.y * scaleY);
		maxX = max(maxX, quad.bl.vertices.x * scaleX);
		maxY = max(maxY, quad.bl.vertices.y * scaleY);
		minX = min(minX, quad.br.vertices.x * scaleX);
		minY = min(minY, quad.br.vertices.y * scaleY);
		maxX = max(maxX, quad.br.vertices.x * scaleX);
		maxY = max(maxY, quad.br.vertices.y * scaleY);
		minX = min(minX, quad.tl.vertices.x * scaleX);
		minY = min(minY, quad.tl.vertices.y * scaleY);
		maxX = max(maxX, quad.tl.vertices.x * scaleX);
		maxY = max(maxY, quad.tl.vertices.y * scaleY);
		minX = min(minX, quad.tr.vertices.x * scaleX);
		minY = min(minY, quad.tr.vertices.y * scaleY);
		maxX = max(maxX, quad.tr.vertices.x * scaleX);
		maxY = max(maxY, quad.tr.vertices.y * scaleY);
	}
	CCPoint position = getPosition();
	minX = position.x + minX;
	minY = position.y + minY;
	maxX = position.x + maxX;
	maxY = position.y + maxY;
	return CCRectMake(minX, minY, maxX - minX, maxY - minY);
}

// CCBlendProtocol

ccBlendFunc CCSkeleton::getBlendFunc () {
    return blendFunc;
}

void CCSkeleton::setBlendFunc (ccBlendFunc blendFunc) {
    this->blendFunc = blendFunc;
}

}} // namespace cocos2d { namespace extension {
