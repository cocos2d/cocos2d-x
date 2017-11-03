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

#include <spine/SkeletonRenderer.h>
#include <spine/extension.h>
#include <spine/SkeletonBatch.h>
#include <spine/SkeletonTwoColorBatch.h>
#include <spine/AttachmentVertices.h>
#include <spine/Cocos2dAttachmentLoader.h>
#include <algorithm>

USING_NS_CC;
using std::min;
using std::max;

namespace spine {

SkeletonRenderer* SkeletonRenderer::createWithData (spSkeletonData* skeletonData, bool ownsSkeletonData) {
	SkeletonRenderer* node = new SkeletonRenderer(skeletonData, ownsSkeletonData);
	node->autorelease();
	return node;
}

SkeletonRenderer* SkeletonRenderer::createWithFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale) {
	SkeletonRenderer* node = new SkeletonRenderer(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}

SkeletonRenderer* SkeletonRenderer::createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
	SkeletonRenderer* node = new SkeletonRenderer(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

void SkeletonRenderer::initialize () {
	_worldVertices = new float[1000]; // Max number of vertices per mesh.
	
	_clipper = spSkeletonClipping_create();

	_blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
	setOpacityModifyRGB(true);

	setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
}

void SkeletonRenderer::setSkeletonData (spSkeletonData *skeletonData, bool ownsSkeletonData) {
	_skeleton = spSkeleton_create(skeletonData);
	_ownsSkeletonData = ownsSkeletonData;
}

SkeletonRenderer::SkeletonRenderer ()
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr) {
}

SkeletonRenderer::SkeletonRenderer (spSkeletonData *skeletonData, bool ownsSkeletonData)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr) {
	initWithData(skeletonData, ownsSkeletonData);
}

SkeletonRenderer::SkeletonRenderer (const std::string& skeletonDataFile, spAtlas* atlas, float scale)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr) {
	initWithJsonFile(skeletonDataFile, atlas, scale);
}

SkeletonRenderer::SkeletonRenderer (const std::string& skeletonDataFile, const std::string& atlasFile, float scale)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr) {
	initWithJsonFile(skeletonDataFile, atlasFile, scale);
}

SkeletonRenderer::~SkeletonRenderer () {
	if (_ownsSkeletonData) spSkeletonData_dispose(_skeleton->data);
	spSkeleton_dispose(_skeleton);
	if (_atlas) spAtlas_dispose(_atlas);
	if (_attachmentLoader) spAttachmentLoader_dispose(_attachmentLoader);
	delete [] _worldVertices;
	spSkeletonClipping_dispose(_clipper);
}

void SkeletonRenderer::initWithData (spSkeletonData* skeletonData, bool ownsSkeletonData) {
	setSkeletonData(skeletonData, ownsSkeletonData);

	initialize();
}

void SkeletonRenderer::initWithJsonFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale) {
    _atlas = atlas;
	_attachmentLoader = SUPER(Cocos2dAttachmentLoader_create(_atlas));

	spSkeletonJson* json = spSkeletonJson_createWithLoader(_attachmentLoader);
	json->scale = scale;
	spSkeletonData* skeletonData = spSkeletonJson_readSkeletonDataFile(json, skeletonDataFile.c_str());
	CCASSERT(skeletonData, json->error ? json->error : "Error reading skeleton data.");
	spSkeletonJson_dispose(json);

	setSkeletonData(skeletonData, true);

	initialize();
}

void SkeletonRenderer::initWithJsonFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
	_atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
	CCASSERT(_atlas, "Error reading atlas file.");

	_attachmentLoader = SUPER(Cocos2dAttachmentLoader_create(_atlas));

	spSkeletonJson* json = spSkeletonJson_createWithLoader(_attachmentLoader);
	json->scale = scale;
	spSkeletonData* skeletonData = spSkeletonJson_readSkeletonDataFile(json, skeletonDataFile.c_str());
	CCASSERT(skeletonData, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);

	setSkeletonData(skeletonData, true);

	initialize();
}
    
void SkeletonRenderer::initWithBinaryFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale) {
    _atlas = atlas;
    _attachmentLoader = SUPER(Cocos2dAttachmentLoader_create(_atlas));
    
    spSkeletonBinary* binary = spSkeletonBinary_createWithLoader(_attachmentLoader);
    binary->scale = scale;
    spSkeletonData* skeletonData = spSkeletonBinary_readSkeletonDataFile(binary, skeletonDataFile.c_str());
    CCASSERT(skeletonData, binary->error ? binary->error : "Error reading skeleton data file.");
    spSkeletonBinary_dispose(binary);
    
    setSkeletonData(skeletonData, true);
    
    initialize();
}

void SkeletonRenderer::initWithBinaryFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
    _atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
    CCASSERT(_atlas, "Error reading atlas file.");
    
    _attachmentLoader = SUPER(Cocos2dAttachmentLoader_create(_atlas));
    
    spSkeletonBinary* binary = spSkeletonBinary_createWithLoader(_attachmentLoader);
    binary->scale = scale;
    spSkeletonData* skeletonData = spSkeletonBinary_readSkeletonDataFile(binary, skeletonDataFile.c_str());
    CCASSERT(skeletonData, binary->error ? binary->error : "Error reading skeleton data file.");
    spSkeletonBinary_dispose(binary);
    
    setSkeletonData(skeletonData, true);
    
    initialize();
}


void SkeletonRenderer::update (float deltaTime) {
	Node::update(deltaTime);
	spSkeleton_update(_skeleton, deltaTime * _timeScale);
}

void SkeletonRenderer::draw (Renderer* renderer, const Mat4& transform, uint32_t transformFlags) {
	SkeletonBatch* batch = SkeletonBatch::getInstance();
	SkeletonTwoColorBatch* twoColorBatch = SkeletonTwoColorBatch::getInstance();
	bool isTwoColorTint = this->isTwoColorTint();
	
	if (_effect) _effect->begin(_effect, _skeleton);

	Color4F nodeColor;
	nodeColor.r = getDisplayedColor().r / (float)255;
	nodeColor.g = getDisplayedColor().g / (float)255;
	nodeColor.b = getDisplayedColor().b / (float)255;
	nodeColor.a = getDisplayedOpacity() / (float)255;
	
    Color4F color;
	Color4F darkColor;
	AttachmentVertices* attachmentVertices = nullptr;
	TwoColorTrianglesCommand* lastTwoColorTrianglesCommand = nullptr;
	for (int i = 0, n = _skeleton->slotsCount; i < n; ++i) {
		spSlot* slot = _skeleton->drawOrder[i];
		if (!slot->attachment) {
			spSkeletonClipping_clipEnd(_clipper, slot);
			continue;
		}
		
		cocos2d::TrianglesCommand::Triangles triangles;
		TwoColorTriangles trianglesTwoColor;
		
		switch (slot->attachment->type) {
		case SP_ATTACHMENT_REGION: {
			spRegionAttachment* attachment = (spRegionAttachment*)slot->attachment;
			attachmentVertices = getAttachmentVertices(attachment);
			
			if (!isTwoColorTint) {
				triangles.indices = attachmentVertices->_triangles->indices;
				triangles.indexCount = attachmentVertices->_triangles->indexCount;
				triangles.verts = batch->allocateVertices(attachmentVertices->_triangles->vertCount);
				triangles.vertCount = attachmentVertices->_triangles->vertCount;
				memcpy(triangles.verts, attachmentVertices->_triangles->verts, sizeof(cocos2d::V3F_C4B_T2F) * attachmentVertices->_triangles->vertCount);
				spRegionAttachment_computeWorldVertices(attachment, slot->bone, (float*)triangles.verts, 0, 6);
			} else {
				trianglesTwoColor.indices = attachmentVertices->_triangles->indices;
				trianglesTwoColor.indexCount = attachmentVertices->_triangles->indexCount;
				trianglesTwoColor.verts = twoColorBatch->allocateVertices(attachmentVertices->_triangles->vertCount);
				trianglesTwoColor.vertCount = attachmentVertices->_triangles->vertCount;
				for (int ii = 0; ii < trianglesTwoColor.vertCount; ii++) {
					trianglesTwoColor.verts[ii].texCoords = attachmentVertices->_triangles->verts[ii].texCoords;
				}
				spRegionAttachment_computeWorldVertices(attachment, slot->bone, (float*)trianglesTwoColor.verts, 0, 7);
			}
			
            color.r = attachment->color.r;
			color.g = attachment->color.g;
			color.b = attachment->color.b;
			color.a = attachment->color.a;
			
			break;
		}
		case SP_ATTACHMENT_MESH: {
			spMeshAttachment* attachment = (spMeshAttachment*)slot->attachment;
			attachmentVertices = getAttachmentVertices(attachment);
			
			if (!isTwoColorTint) {
				triangles.indices = attachmentVertices->_triangles->indices;
				triangles.indexCount = attachmentVertices->_triangles->indexCount;
				triangles.verts = batch->allocateVertices(attachmentVertices->_triangles->vertCount);
				triangles.vertCount = attachmentVertices->_triangles->vertCount;
				memcpy(triangles.verts, attachmentVertices->_triangles->verts, sizeof(cocos2d::V3F_C4B_T2F) * attachmentVertices->_triangles->vertCount);
				spVertexAttachment_computeWorldVertices(SUPER(attachment), slot, 0, triangles.vertCount * sizeof(cocos2d::V3F_C4B_T2F) / 4, (float*)triangles.verts, 0, 6);
			} else {
				trianglesTwoColor.indices = attachmentVertices->_triangles->indices;
				trianglesTwoColor.indexCount = attachmentVertices->_triangles->indexCount;
				trianglesTwoColor.verts = twoColorBatch->allocateVertices(attachmentVertices->_triangles->vertCount);
				trianglesTwoColor.vertCount = attachmentVertices->_triangles->vertCount;
				for (int ii = 0; i < trianglesTwoColor.vertCount; ii++) {
					trianglesTwoColor.verts[ii].texCoords = attachmentVertices->_triangles->verts[ii].texCoords;
				}
				spVertexAttachment_computeWorldVertices(SUPER(attachment), slot, 0, trianglesTwoColor.vertCount * sizeof(V3F_C4B_C4B_T2F) / 4, (float*)trianglesTwoColor.verts, 0, 7);
			}
			
			color.r = attachment->color.r;
			color.g = attachment->color.g;
			color.b = attachment->color.b;
			color.a = attachment->color.a;
			
			break;
		}
		case SP_ATTACHMENT_CLIPPING: {
			spClippingAttachment* clip = (spClippingAttachment*)slot->attachment;
			spSkeletonClipping_clipStart(_clipper, slot, clip);
		}
		default:
			spSkeletonClipping_clipEnd(_clipper, slot);
			continue;
		}
		
		if (slot->darkColor) {
			darkColor.r = slot->darkColor->r * 255;
			darkColor.g = slot->darkColor->g * 255;
			darkColor.b = slot->darkColor->b * 255;
		} else {
			darkColor.r = 0;
			darkColor.g = 0;
			darkColor.b = 0;
		}
		
		color.a *= nodeColor.a * _skeleton->color.a * slot->color.a * 255;
		// skip rendering if the color of this attachment is 0
		if (color.a == 0){
			spSkeletonClipping_clipEnd(_clipper, slot);
			continue;
		}
		float multiplier = _premultipliedAlpha ? color.a : 255;
		color.r *= nodeColor.r * _skeleton->color.r * slot->color.r * multiplier;
		color.g *= nodeColor.g * _skeleton->color.g * slot->color.g * multiplier;
		color.b *= nodeColor.b * _skeleton->color.b * slot->color.b * multiplier;
		
		BlendFunc blendFunc;
		switch (slot->data->blendMode) {
			case SP_BLEND_MODE_ADDITIVE:
				blendFunc.src = _premultipliedAlpha ? GL_ONE : GL_SRC_ALPHA;
				blendFunc.dst = GL_ONE;
				break;
			case SP_BLEND_MODE_MULTIPLY:
				blendFunc.src = GL_DST_COLOR;
				blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
				break;
			case SP_BLEND_MODE_SCREEN:
				blendFunc.src = GL_ONE;
				blendFunc.dst = GL_ONE_MINUS_SRC_COLOR;
				break;
			default:
				blendFunc.src = _premultipliedAlpha ? GL_ONE : GL_SRC_ALPHA;
				blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
		}
		
		if (!isTwoColorTint) {
			if (spSkeletonClipping_isClipping(_clipper)) {
				spSkeletonClipping_clipTriangles(_clipper, (float*)&triangles.verts[0].vertices, triangles.vertCount * sizeof(cocos2d::V3F_C4B_T2F) / 4, triangles.indices, triangles.indexCount, (float*)&triangles.verts[0].texCoords, 6);
				batch->deallocateVertices(triangles.vertCount);
				
				if (_clipper->clippedTriangles->size == 0){
					spSkeletonClipping_clipEnd(_clipper, slot);
					continue;
				}
				
				triangles.vertCount = _clipper->clippedVertices->size >> 1;
				triangles.verts = batch->allocateVertices(triangles.vertCount);
				triangles.indexCount = _clipper->clippedTriangles->size;
				triangles.indices = batch->allocateIndices(triangles.indexCount);
				memcpy(triangles.indices, _clipper->clippedTriangles->items, sizeof(unsigned short) * _clipper->clippedTriangles->size);
				
				cocos2d::TrianglesCommand* batchedTriangles = batch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture, _glProgramState, blendFunc, triangles, transform, transformFlags);
				
				float* verts = _clipper->clippedVertices->items;
				float* uvs = _clipper->clippedUVs->items;
				if (_effect) {
					spColor light;
					spColor dark;
					light.r = color.r / 255.0f;
					light.g = color.g / 255.0f;
					light.b = color.b / 255.0f;
					light.a = color.a / 255.0f;
					dark.r = dark.g = dark.b = dark.a = 0;
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount, vv = 0; v < vn; ++v, vv+=2) {
						V3F_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						spColor lightCopy = light;
						spColor darkCopy = dark;
						vertex->vertices.x = verts[vv];
						vertex->vertices.y = verts[vv + 1];
						vertex->texCoords.u = uvs[vv];
						vertex->texCoords.v = uvs[vv + 1];
						_effect->transform(_effect, &vertex->vertices.x, &vertex->vertices.y, &vertex->texCoords.u, &vertex->texCoords.v, &lightCopy, &darkCopy);
						vertex->colors.r = (GLubyte)(lightCopy.r * 255);
						vertex->colors.g = (GLubyte)(lightCopy.g * 255);
						vertex->colors.b = (GLubyte)(lightCopy.b * 255);
						vertex->colors.a = (GLubyte)(lightCopy.a * 255);
					}
				} else {
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount, vv = 0; v < vn; ++v, vv+=2) {
						V3F_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						vertex->vertices.x = verts[vv];
						vertex->vertices.y = verts[vv + 1];
						vertex->texCoords.u = uvs[vv];
						vertex->texCoords.v = uvs[vv + 1];
						vertex->colors.r = (GLubyte)color.r;
						vertex->colors.g = (GLubyte)color.g;
						vertex->colors.b = (GLubyte)color.b;
						vertex->colors.a = (GLubyte)color.a;
					}
				}
			} else {
				cocos2d::TrianglesCommand* batchedTriangles = batch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture, _glProgramState, blendFunc, triangles, transform, transformFlags);
				
				if (_effect) {
					spColor light;
					spColor dark;
					light.r = color.r / 255.0f;
					light.g = color.g / 255.0f;
					light.b = color.b / 255.0f;
					light.a = color.a / 255.0f;
					dark.r = dark.g = dark.b = dark.a = 0;
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount; v < vn; ++v) {
						V3F_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						spColor lightCopy = light;
						spColor darkCopy = dark;
						_effect->transform(_effect, &vertex->vertices.x, &vertex->vertices.y, &vertex->texCoords.u, &vertex->texCoords.v, &lightCopy, &darkCopy);
						vertex->colors.r = (GLubyte)(lightCopy.r * 255);
						vertex->colors.g = (GLubyte)(lightCopy.g * 255);
						vertex->colors.b = (GLubyte)(lightCopy.b * 255);
						vertex->colors.a = (GLubyte)(lightCopy.a * 255);
					}
				} else {
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount; v < vn; ++v) {
						V3F_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						vertex->colors.r = (GLubyte)color.r;
						vertex->colors.g = (GLubyte)color.g;
						vertex->colors.b = (GLubyte)color.b;
						vertex->colors.a = (GLubyte)color.a;
					}
				}
			}
		} else {
			if (spSkeletonClipping_isClipping(_clipper)) {
				spSkeletonClipping_clipTriangles(_clipper, (float*)&trianglesTwoColor.verts[0].position, trianglesTwoColor.vertCount * sizeof(V3F_C4B_C4B_T2F) / 4, trianglesTwoColor.indices, trianglesTwoColor.indexCount, (float*)&trianglesTwoColor.verts[0].texCoords, 7);
				twoColorBatch->deallocateVertices(trianglesTwoColor.vertCount);
				
				if (_clipper->clippedTriangles->size == 0){
					spSkeletonClipping_clipEnd(_clipper, slot);
					continue;
				}
				
				trianglesTwoColor.vertCount = _clipper->clippedVertices->size >> 1;
				trianglesTwoColor.verts = twoColorBatch->allocateVertices(trianglesTwoColor.vertCount);
				trianglesTwoColor.indexCount = _clipper->clippedTriangles->size;
				trianglesTwoColor.indices = twoColorBatch->allocateIndices(trianglesTwoColor.indexCount);
				memcpy(trianglesTwoColor.indices, _clipper->clippedTriangles->items, sizeof(unsigned short) * _clipper->clippedTriangles->size);
				
				TwoColorTrianglesCommand* batchedTriangles = lastTwoColorTrianglesCommand = twoColorBatch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture->getName(), _glProgramState, blendFunc, trianglesTwoColor, transform, transformFlags);
				
				float* verts = _clipper->clippedVertices->items;
				float* uvs = _clipper->clippedUVs->items;
				
				if (_effect) {
					spColor light;
					spColor dark;
					light.r = color.r / 255.0f;
					light.g = color.g / 255.0f;
					light.b = color.b / 255.0f;
					light.a = color.a / 255.0f;
					dark.r = darkColor.r / 255.0f;
					dark.g = darkColor.g / 255.0f;
					dark.b = darkColor.b / 255.0f;
					dark.a = darkColor.a / 255.0f;
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount, vv = 0; v < vn; ++v, vv += 2) {
						V3F_C4B_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						spColor lightCopy = light;
						spColor darkCopy = dark;
						vertex->position.x = verts[vv];
						vertex->position.y = verts[vv + 1];
						vertex->texCoords.u = uvs[vv];
						vertex->texCoords.v = uvs[vv + 1];
						_effect->transform(_effect, &vertex->position.x, &vertex->position.y, &vertex->texCoords.u, &vertex->texCoords.v, &lightCopy, &darkCopy);
						vertex->color.r = (GLubyte)(lightCopy.r * 255);
						vertex->color.g = (GLubyte)(lightCopy.g * 255);
						vertex->color.b = (GLubyte)(lightCopy.b * 255);
						vertex->color.a = (GLubyte)(lightCopy.a * 255);
						vertex->color2.r = (GLubyte)(darkCopy.r * 255);
						vertex->color2.g = (GLubyte)(darkCopy.g * 255);
						vertex->color2.b = (GLubyte)(darkCopy.b * 255);
						vertex->color2.a = 1;
					}
				} else {
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount, vv = 0; v < vn; ++v, vv += 2) {
						V3F_C4B_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						vertex->position.x = verts[vv];
						vertex->position.y = verts[vv + 1];
						vertex->texCoords.u = uvs[vv];
						vertex->texCoords.v = uvs[vv + 1];
						vertex->color.r = (GLubyte)color.r;
						vertex->color.g = (GLubyte)color.g;
						vertex->color.b = (GLubyte)color.b;
						vertex->color.a = (GLubyte)color.a;
						vertex->color2.r = (GLubyte)darkColor.r;
						vertex->color2.g = (GLubyte)darkColor.g;
						vertex->color2.b = (GLubyte)darkColor.b;
						vertex->color2.a = 1;
					}
				}
			} else {
				TwoColorTrianglesCommand* batchedTriangles = lastTwoColorTrianglesCommand = twoColorBatch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture->getName(), _glProgramState, blendFunc, trianglesTwoColor, transform, transformFlags);
				
				if (_effect) {
					spColor light;
					spColor dark;
					light.r = color.r / 255.0f;
					light.g = color.g / 255.0f;
					light.b = color.b / 255.0f;
					light.a = color.a / 255.0f;
					dark.r = darkColor.r / 255.0f;
					dark.g = darkColor.g / 255.0f;
					dark.b = darkColor.b / 255.0f;
					dark.a = darkColor.a / 255.0f;
					
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount; v < vn; ++v) {
						V3F_C4B_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						spColor lightCopy = light;
						spColor darkCopy = dark;
						_effect->transform(_effect, &vertex->position.x, &vertex->position.y, &vertex->texCoords.u, &vertex->texCoords.v, &lightCopy, &darkCopy);
						vertex->color.r = (GLubyte)(lightCopy.r * 255);
						vertex->color.g = (GLubyte)(lightCopy.g * 255);
						vertex->color.b = (GLubyte)(lightCopy.b * 255);
						vertex->color.a = (GLubyte)(lightCopy.a * 255);
						vertex->color2.r = (GLubyte)(darkCopy.r * 255);
						vertex->color2.g = (GLubyte)(darkCopy.g * 255);
						vertex->color2.b = (GLubyte)(darkCopy.b * 255);
						vertex->color2.a = 1;
					}
				} else {
					for (int v = 0, vn = batchedTriangles->getTriangles().vertCount; v < vn; ++v) {
						V3F_C4B_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
						vertex->color.r = (GLubyte)color.r;
						vertex->color.g = (GLubyte)color.g;
						vertex->color.b = (GLubyte)color.b;
						vertex->color.a = (GLubyte)color.a;
						vertex->color2.r = (GLubyte)darkColor.r;
						vertex->color2.g = (GLubyte)darkColor.g;
						vertex->color2.b = (GLubyte)darkColor.b;
						vertex->color2.a = 1;
					}
				}
			}
		}
		spSkeletonClipping_clipEnd(_clipper, slot);
	}
	spSkeletonClipping_clipEnd2(_clipper);
	
	if (lastTwoColorTrianglesCommand) {
		Node* parent = this->getParent();
		
		// We need to decide if we can postpone flushing the current
		// batch. We can postpone if the next sibling node is a
		// two color tinted skeleton with the same global-z.
		// The parent->getChildrenCount() > 100 check is a hack
		// as checking for a sibling is an O(n) operation, and if
		// all children of this nodes parent are skeletons, we
		// are in O(n2) territory.
		if (!parent || parent->getChildrenCount() > 100 || getChildrenCount() != 0) {
			lastTwoColorTrianglesCommand->setForceFlush(true);
		} else {
			Vector<Node*>& children = parent->getChildren();
			Node* sibling = nullptr;
			for (ssize_t i = 0; i < children.size(); i++) {
				if (children.at(i) == this) {
					if (i < children.size() - 1) {
						sibling = children.at(i+1);
						break;
					}
				}
			}
			if (!sibling) {
				lastTwoColorTrianglesCommand->setForceFlush(true);
			} else {
				SkeletonRenderer* siblingSkeleton = dynamic_cast<SkeletonRenderer*>(sibling);
				if (!siblingSkeleton || // flush is next sibling isn't a SkeletonRenderer
					!siblingSkeleton->isTwoColorTint() || // flush if next sibling isn't two color tinted
					!siblingSkeleton->isVisible() || // flush if next sibling is two color tinted but not visible
					(siblingSkeleton->getGlobalZOrder() != this->getGlobalZOrder())) { // flush if next sibling is two color tinted but z-order differs
					lastTwoColorTrianglesCommand->setForceFlush(true);
				}
			}
		}
	}
	
	if (_effect) _effect->end(_effect);

	if (_debugSlots || _debugBones || _debugMeshes) {
        drawDebug(renderer, transform, transformFlags);
	}
}

void SkeletonRenderer::drawDebug (Renderer* renderer, const Mat4 &transform, uint32_t transformFlags) {

    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    DrawNode* drawNode = DrawNode::create();
    
    if (_debugSlots) {
        // Slots.
        // DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
        glLineWidth(1);
        Vec2 points[4];
        V3F_C4B_T2F_Quad quad;
        for (int i = 0, n = _skeleton->slotsCount; i < n; i++) {
            spSlot* slot = _skeleton->drawOrder[i];
            if (!slot->attachment || slot->attachment->type != SP_ATTACHMENT_REGION) continue;
            spRegionAttachment* attachment = (spRegionAttachment*)slot->attachment;
            spRegionAttachment_computeWorldVertices(attachment, slot->bone, _worldVertices, 0, 2);
            points[0] = Vec2(_worldVertices[0], _worldVertices[1]);
            points[1] = Vec2(_worldVertices[2], _worldVertices[3]);
            points[2] = Vec2(_worldVertices[4], _worldVertices[5]);
            points[3] = Vec2(_worldVertices[6], _worldVertices[7]);
            drawNode->drawPoly(points, 4, true, Color4F::BLUE);
        }
    }
    if (_debugBones) {
        // Bone lengths.
        glLineWidth(2);
        for (int i = 0, n = _skeleton->bonesCount; i < n; i++) {
            spBone *bone = _skeleton->bones[i];
            float x = bone->data->length * bone->a + bone->worldX;
            float y = bone->data->length * bone->c + bone->worldY;
            drawNode->drawLine(Vec2(bone->worldX, bone->worldY), Vec2(x, y), Color4F::RED);
        }
        // Bone origins.
        auto color = Color4F::BLUE; // Root bone is blue.
        for (int i = 0, n = _skeleton->bonesCount; i < n; i++) {
            spBone *bone = _skeleton->bones[i];
            drawNode->drawPoint(Vec2(bone->worldX, bone->worldY), 4, color);
            if (i == 0) color = Color4F::GREEN;
        }
    }
	
	if (_debugMeshes) {
		// Meshes.
		glLineWidth(1);
		for (int i = 0, n = _skeleton->slotsCount; i < n; ++i) {
			spSlot* slot = _skeleton->drawOrder[i];
			if (!slot->attachment || slot->attachment->type != SP_ATTACHMENT_MESH) continue;
			spMeshAttachment* attachment = (spMeshAttachment*)slot->attachment;			
			spVertexAttachment_computeWorldVertices(SUPER(attachment), slot, 0, attachment->super.worldVerticesLength, _worldVertices, 0, 2);
			for (int ii = 0; ii < attachment->trianglesCount;) {
				Vec2 v1(_worldVertices + (attachment->triangles[ii++] * 2));
				Vec2 v2(_worldVertices + (attachment->triangles[ii++] * 2));
				Vec2 v3(_worldVertices + (attachment->triangles[ii++] * 2));
				drawNode->drawLine(v1, v2, Color4F::YELLOW);
				drawNode->drawLine(v2, v3, Color4F::YELLOW);
				drawNode->drawLine(v3, v1, Color4F::YELLOW);
			}
		}
		
	}
    
    drawNode->draw(renderer, transform, transformFlags);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

AttachmentVertices* SkeletonRenderer::getAttachmentVertices (spRegionAttachment* attachment) const {
	return (AttachmentVertices*)attachment->rendererObject;
}

AttachmentVertices* SkeletonRenderer::getAttachmentVertices (spMeshAttachment* attachment) const {
	return (AttachmentVertices*)attachment->rendererObject;
}

Rect SkeletonRenderer::getBoundingBox () const {
	float minX = FLT_MAX, minY = FLT_MAX, maxX = -FLT_MAX, maxY = -FLT_MAX;
	float scaleX = getScaleX(), scaleY = getScaleY();
	for (int i = 0; i < _skeleton->slotsCount; ++i) {
		spSlot* slot = _skeleton->slots[i];
		if (!slot->attachment) continue;
		int verticesCount;
		if (slot->attachment->type == SP_ATTACHMENT_REGION) {
			spRegionAttachment* attachment = (spRegionAttachment*)slot->attachment;
			spRegionAttachment_computeWorldVertices(attachment, slot->bone, _worldVertices, 0, 2);
			verticesCount = 8;
		} else if (slot->attachment->type == SP_ATTACHMENT_MESH) {
			spMeshAttachment* mesh = (spMeshAttachment*)slot->attachment;
			spVertexAttachment_computeWorldVertices(SUPER(mesh), slot, 0, mesh->super.worldVerticesLength, _worldVertices, 0, 2);
			verticesCount = mesh->super.worldVerticesLength;
		} else
			continue;
		for (int ii = 0; ii < verticesCount; ii += 2) {
			float x = _worldVertices[ii] * scaleX, y = _worldVertices[ii + 1] * scaleY;
			minX = min(minX, x);
			minY = min(minY, y);
			maxX = max(maxX, x);
			maxY = max(maxY, y);
		}
	}
	Vec2 position = getPosition();
    if (minX == FLT_MAX) minX = minY = maxX = maxY = 0;    
	return Rect(position.x + minX, position.y + minY, maxX - minX, maxY - minY);
}

// --- Convenience methods for Skeleton_* functions.

void SkeletonRenderer::updateWorldTransform () {
	spSkeleton_updateWorldTransform(_skeleton);
}

void SkeletonRenderer::setToSetupPose () {
	spSkeleton_setToSetupPose(_skeleton);
}
void SkeletonRenderer::setBonesToSetupPose () {
	spSkeleton_setBonesToSetupPose(_skeleton);
}
void SkeletonRenderer::setSlotsToSetupPose () {
	spSkeleton_setSlotsToSetupPose(_skeleton);
}

spBone* SkeletonRenderer::findBone (const std::string& boneName) const {
	return spSkeleton_findBone(_skeleton, boneName.c_str());
}

spSlot* SkeletonRenderer::findSlot (const std::string& slotName) const {
	return spSkeleton_findSlot(_skeleton, slotName.c_str());
}

bool SkeletonRenderer::setSkin (const std::string& skinName) {
	return spSkeleton_setSkinByName(_skeleton, skinName.empty() ? 0 : skinName.c_str()) ? true : false;
}
bool SkeletonRenderer::setSkin (const char* skinName) {
	return spSkeleton_setSkinByName(_skeleton, skinName) ? true : false;
}

spAttachment* SkeletonRenderer::getAttachment (const std::string& slotName, const std::string& attachmentName) const {
	return spSkeleton_getAttachmentForSlotName(_skeleton, slotName.c_str(), attachmentName.c_str());
}
bool SkeletonRenderer::setAttachment (const std::string& slotName, const std::string& attachmentName) {
	return spSkeleton_setAttachment(_skeleton, slotName.c_str(), attachmentName.empty() ? 0 : attachmentName.c_str()) ? true : false;
}
bool SkeletonRenderer::setAttachment (const std::string& slotName, const char* attachmentName) {
	return spSkeleton_setAttachment(_skeleton, slotName.c_str(), attachmentName) ? true : false;
}
	
void SkeletonRenderer::setTwoColorTint(bool enabled) {
	if (enabled)
		setGLProgramState(SkeletonTwoColorBatch::getInstance()->getTwoColorTintProgramState());
	else
		setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
}

bool SkeletonRenderer::isTwoColorTint() {
	return getGLProgramState() == SkeletonTwoColorBatch::getInstance()->getTwoColorTintProgramState();
}
	
void SkeletonRenderer::setVertexEffect(spVertexEffect *effect) {
	this->_effect = effect;
}

spSkeleton* SkeletonRenderer::getSkeleton () {
	return _skeleton;
}

void SkeletonRenderer::setTimeScale (float scale) {
	_timeScale = scale;
}
float SkeletonRenderer::getTimeScale () const {
	return _timeScale;
}

void SkeletonRenderer::setDebugSlotsEnabled (bool enabled) {
	_debugSlots = enabled;
}
bool SkeletonRenderer::getDebugSlotsEnabled () const {
	return _debugSlots;
}

void SkeletonRenderer::setDebugBonesEnabled (bool enabled) {
	_debugBones = enabled;
}
bool SkeletonRenderer::getDebugBonesEnabled () const {
	return _debugBones;
}
	
void SkeletonRenderer::setDebugMeshesEnabled (bool enabled) {
	_debugMeshes = enabled;
}
bool SkeletonRenderer::getDebugMeshesEnabled () const {
	return _debugMeshes;
}

void SkeletonRenderer::onEnter () {
#if CC_ENABLE_SCRIPT_BINDING
	if (_scriptType == kScriptTypeJavascript && ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter)) return;
#endif
	Node::onEnter();
	scheduleUpdate();
}

void SkeletonRenderer::onExit () {
#if CC_ENABLE_SCRIPT_BINDING
	if (_scriptType == kScriptTypeJavascript && ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExit)) return;
#endif
	Node::onExit();
	unscheduleUpdate();
}

// --- CCBlendProtocol

const BlendFunc& SkeletonRenderer::getBlendFunc () const {
	return _blendFunc;
}

void SkeletonRenderer::setBlendFunc (const BlendFunc &blendFunc) {
	_blendFunc = blendFunc;
}

void SkeletonRenderer::setOpacityModifyRGB (bool value) {
	_premultipliedAlpha = value;
}

bool SkeletonRenderer::isOpacityModifyRGB () const {
	return _premultipliedAlpha;
}

}
