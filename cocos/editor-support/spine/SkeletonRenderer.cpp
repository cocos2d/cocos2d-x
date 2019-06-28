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

#include <spine/spine-cocos2dx.h>
#include <spine/SkeletonRenderer.h>
#include <spine/Extension.h>
#include <spine/SkeletonBatch.h>
#include <spine/SkeletonTwoColorBatch.h>
#include <spine/AttachmentVertices.h>
#include <algorithm>

#include "renderer/backend/Types.h"

#define INITIAL_WORLD_VERTICES_LENGTH 1000
// Used for transforming attachments for bounding boxes & debug rendering
static float* worldVertices = nullptr;
static size_t worldVerticesLength = 0;

void ensureWorldVerticesCapacity(size_t capacity) {
	if (worldVerticesLength < capacity) {
		float* newWorldVertices = new float[capacity];
		memcpy(newWorldVertices, worldVertices, capacity * sizeof(float));
		delete[] worldVertices;
		worldVertices = newWorldVertices;
		worldVerticesLength = capacity;
	}
}

USING_NS_CC;
using std::min;
using std::max;

namespace spine {
	
	static Cocos2dTextureLoader textureLoader;
	
	void SkeletonRenderer::destroyScratchBuffers() {
		if (worldVertices) {
			delete[] worldVertices;
			worldVertices = nullptr;
			worldVerticesLength = 0;
		}
	}
	
	SkeletonRenderer* SkeletonRenderer::createWithSkeleton(Skeleton* skeleton, bool ownsSkeleton, bool ownsSkeletonData) {
		SkeletonRenderer* node = new SkeletonRenderer(skeleton, ownsSkeleton, ownsSkeletonData);
		node->autorelease();
		return node;
	}
	
	SkeletonRenderer* SkeletonRenderer::createWithData (SkeletonData* skeletonData, bool ownsSkeletonData) {
		SkeletonRenderer* node = new SkeletonRenderer(skeletonData, ownsSkeletonData);
		node->autorelease();
		return node;
	}
	
	SkeletonRenderer* SkeletonRenderer::createWithFile (const std::string& skeletonDataFile, Atlas* atlas, float scale) {
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
		if (!worldVertices) {
			worldVertices = new float[INITIAL_WORLD_VERTICES_LENGTH];
			worldVerticesLength = INITIAL_WORLD_VERTICES_LENGTH;
		}
		
		_clipper = new (__FILE__, __LINE__) SkeletonClipping();
		
		_blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
		setOpacityModifyRGB(true);
		
		setupGLProgramState(false);
		
		_skeleton->setToSetupPose();
		_skeleton->updateWorldTransform();
	}
	
	void SkeletonRenderer::setupGLProgramState (bool twoColorTintEnabled) {

        _twoColorTintEnabled = twoColorTintEnabled;
		if (twoColorTintEnabled) {
			return;
		}
		
		Texture2D *texture = nullptr;
		for (int i = 0, n = _skeleton->getSlots().size(); i < n; i++) {
			Slot* slot = _skeleton->getDrawOrder()[i];
			if (!slot->getAttachment()) continue;
			if (slot->getAttachment()->getRTTI().isExactly(RegionAttachment::rtti)) {
				RegionAttachment* attachment = (RegionAttachment*)slot->getAttachment();
				texture = static_cast<AttachmentVertices*>(attachment->getRendererObject())->_texture;
			} else if (slot->getAttachment()->getRTTI().isExactly(RegionAttachment::rtti)) {
				MeshAttachment* attachment = (MeshAttachment*)slot->getAttachment();
				texture = static_cast<AttachmentVertices*>(attachment->getRendererObject())->_texture;
			} else {
				continue;
			}
			
			if (texture != nullptr) {
				break;
			}
		}
		//setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, texture));
	}
	
	void SkeletonRenderer::setSkeletonData (SkeletonData *skeletonData, bool ownsSkeletonData) {
		_skeleton = new (__FILE__, __LINE__) Skeleton(skeletonData);
		_ownsSkeletonData = ownsSkeletonData;
	}
	
	SkeletonRenderer::SkeletonRenderer ()
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr), _startSlotIndex(-1), _endSlotIndex(-1) {
	}
	
	SkeletonRenderer::SkeletonRenderer(Skeleton* skeleton, bool ownsSkeleton, bool ownsSkeletonData, bool ownsAtlas)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr), _startSlotIndex(-1), _endSlotIndex(-1) {
		initWithSkeleton(skeleton, ownsSkeleton, ownsSkeletonData, ownsAtlas);
	}
	
	SkeletonRenderer::SkeletonRenderer (SkeletonData *skeletonData, bool ownsSkeletonData)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr), _startSlotIndex(-1), _endSlotIndex(-1) {
		initWithData(skeletonData, ownsSkeletonData);
	}
	
	SkeletonRenderer::SkeletonRenderer (const std::string& skeletonDataFile, Atlas* atlas, float scale)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr), _startSlotIndex(-1), _endSlotIndex(-1) {
		initWithJsonFile(skeletonDataFile, atlas, scale);
	}
	
	SkeletonRenderer::SkeletonRenderer (const std::string& skeletonDataFile, const std::string& atlasFile, float scale)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _debugMeshes(false), _timeScale(1), _effect(nullptr), _startSlotIndex(-1), _endSlotIndex(-1) {
		initWithJsonFile(skeletonDataFile, atlasFile, scale);
	}
	
	SkeletonRenderer::~SkeletonRenderer () {
		if (_ownsSkeletonData) delete _skeleton->getData();
		if (_ownsSkeleton) delete _skeleton;
		if (_ownsAtlas && _atlas) delete _atlas;
		if (_attachmentLoader) delete _attachmentLoader;
		delete _clipper;
	}
	
	void SkeletonRenderer::initWithSkeleton(Skeleton* skeleton, bool ownsSkeleton, bool ownsSkeletonData, bool ownsAtlas) {
		_skeleton = skeleton;
		_ownsSkeleton = ownsSkeleton;
		_ownsSkeletonData = ownsSkeletonData;
		_ownsAtlas = ownsAtlas;
		
		initialize();
	}
	
	void SkeletonRenderer::initWithData (SkeletonData* skeletonData, bool ownsSkeletonData) {
		_ownsSkeleton = true;
		setSkeletonData(skeletonData, ownsSkeletonData);
		initialize();
	}
	
	void SkeletonRenderer::initWithJsonFile (const std::string& skeletonDataFile, Atlas* atlas, float scale) {
		_atlas = atlas;
		_attachmentLoader = new (__FILE__, __LINE__) Cocos2dAtlasAttachmentLoader(_atlas);
		
		SkeletonJson* json = new (__FILE__, __LINE__) SkeletonJson(_attachmentLoader);
		json->setScale(scale);
		SkeletonData* skeletonData = json->readSkeletonDataFile(skeletonDataFile.c_str());
		CCASSERT(skeletonData, !json->getError().isEmpty() ? json->getError().buffer() : "Error reading skeleton data.");
		delete json;
		
		_ownsSkeleton = true;
		setSkeletonData(skeletonData, true);
		
		initialize();
	}
	
	void SkeletonRenderer::initWithJsonFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
		_atlas = new (__FILE__, __LINE__) Atlas(atlasFile.c_str(), &textureLoader);
		CCASSERT(_atlas, "Error reading atlas file.");
		
		_attachmentLoader = new (__FILE__, __LINE__) Cocos2dAtlasAttachmentLoader(_atlas);
		
		SkeletonJson* json = new (__FILE__, __LINE__) SkeletonJson(_attachmentLoader);
		json->setScale(scale);
		SkeletonData* skeletonData = json->readSkeletonDataFile(skeletonDataFile.c_str());
		CCASSERT(skeletonData, !json->getError().isEmpty() ? json->getError().buffer() : "Error reading skeleton data.");
		delete json;
		
		_ownsSkeleton = true;
		_ownsAtlas = true;
		setSkeletonData(skeletonData, true);
		
		initialize();
	}
	
	void SkeletonRenderer::initWithBinaryFile (const std::string& skeletonDataFile, Atlas* atlas, float scale) {
		_atlas = atlas;
		_attachmentLoader = new (__FILE__, __LINE__) Cocos2dAtlasAttachmentLoader(_atlas);
		
		SkeletonBinary* binary = new (__FILE__, __LINE__) SkeletonBinary(_attachmentLoader);
		binary->setScale(scale);
		SkeletonData* skeletonData = binary->readSkeletonDataFile(skeletonDataFile.c_str());
		CCASSERT(skeletonData, !binary->getError().isEmpty() ? binary->getError().buffer() : "Error reading skeleton data.");
		delete binary;
		_ownsSkeleton = true;
		setSkeletonData(skeletonData, true);
		
		initialize();
	}
	
	void SkeletonRenderer::initWithBinaryFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
		_atlas = new (__FILE__, __LINE__) Atlas(atlasFile.c_str(), &textureLoader);
		CCASSERT(_atlas, "Error reading atlas file.");
		
		_attachmentLoader = new (__FILE__, __LINE__) Cocos2dAtlasAttachmentLoader(_atlas);
		
		SkeletonBinary* binary = new (__FILE__, __LINE__) SkeletonBinary(_attachmentLoader);
		binary->setScale(scale);
		SkeletonData* skeletonData = binary->readSkeletonDataFile(skeletonDataFile.c_str());
		CCASSERT(skeletonData, !binary->getError().isEmpty() ? binary->getError().buffer() : "Error reading skeleton data.");
		delete binary;
		_ownsSkeleton = true;
		_ownsAtlas = true;
		setSkeletonData(skeletonData, true);
		
		initialize();
	}
	
	void SkeletonRenderer::update (float deltaTime) {
		Node::update(deltaTime);
		if (_ownsSkeleton) _skeleton->update(deltaTime * _timeScale);
	}
	
	void SkeletonRenderer::draw (Renderer* renderer, const Mat4& transform, uint32_t transformFlags) {
		SkeletonBatch* batch = SkeletonBatch::getInstance();
		SkeletonTwoColorBatch* twoColorBatch = SkeletonTwoColorBatch::getInstance();
		bool isTwoColorTint = this->isTwoColorTint();
		
		// Early exit if the skeleton is invisible
		if (getDisplayedOpacity() == 0 || _skeleton->getColor().a == 0){
			return;
		}
		
		if (_effect) _effect->begin(*_skeleton);
		
		Color4F nodeColor;
		nodeColor.r = getDisplayedColor().r / (float)255;
		nodeColor.g = getDisplayedColor().g / (float)255;
		nodeColor.b = getDisplayedColor().b / (float)255;
		nodeColor.a = getDisplayedOpacity() / (float)255;
		
		Color4F color;
		Color4F darkColor;
		float darkPremultipliedAlpha = _premultipliedAlpha ? 255 : 0;
		AttachmentVertices* attachmentVertices = nullptr;
		TwoColorTrianglesCommand* lastTwoColorTrianglesCommand = nullptr;
		bool inRange = _startSlotIndex != -1 || _endSlotIndex != -1 ? false : true;
		for (int i = 0, n = _skeleton->getSlots().size(); i < n; ++i) {
			Slot* slot = _skeleton->getDrawOrder()[i];
			
			if (_startSlotIndex >= 0 && _startSlotIndex == slot->getData().getIndex()) {
				inRange = true;
			}
			
			if (!inRange) {
				_clipper->clipEnd(*slot);
				continue;
			}
			
			if (_endSlotIndex >= 0 && _endSlotIndex == slot->getData().getIndex()) {
				inRange = false;
			}
			
			if (!slot->getAttachment()) {
				_clipper->clipEnd(*slot);
				continue;
			}
			
			// Early exit if slot is invisible
			if (slot->getColor().a == 0) {
				_clipper->clipEnd(*slot);
				continue;
			}
			
			cocos2d::TrianglesCommand::Triangles triangles;
			TwoColorTriangles trianglesTwoColor;
			
			if (slot->getAttachment()->getRTTI().isExactly(RegionAttachment::rtti)) {
				RegionAttachment* attachment = (RegionAttachment*)slot->getAttachment();
				attachmentVertices = (AttachmentVertices*)attachment->getRendererObject();
				
				// Early exit if attachment is invisible
				if (attachment->getColor().a == 0) {
					_clipper->clipEnd(*slot);
					continue;
				}
				
				if (!isTwoColorTint) {
					triangles.indices = attachmentVertices->_triangles->indices;
					triangles.indexCount = attachmentVertices->_triangles->indexCount;
					triangles.verts = batch->allocateVertices(attachmentVertices->_triangles->vertCount);
					triangles.vertCount = attachmentVertices->_triangles->vertCount;
					memcpy(triangles.verts, attachmentVertices->_triangles->verts, sizeof(cocos2d::V3F_C4B_T2F) * attachmentVertices->_triangles->vertCount);
					attachment->computeWorldVertices(slot->getBone(), (float*)triangles.verts, 0, 6);
				} else {
					trianglesTwoColor.indices = attachmentVertices->_triangles->indices;
					trianglesTwoColor.indexCount = attachmentVertices->_triangles->indexCount;
					trianglesTwoColor.verts = twoColorBatch->allocateVertices(attachmentVertices->_triangles->vertCount);
					trianglesTwoColor.vertCount = attachmentVertices->_triangles->vertCount;
					for (int i = 0; i < trianglesTwoColor.vertCount; i++) {
						trianglesTwoColor.verts[i].texCoords = attachmentVertices->_triangles->verts[i].texCoords;
					}
					attachment->computeWorldVertices(slot->getBone(), (float*)trianglesTwoColor.verts, 0, 7);
				}
				
				color.r = attachment->getColor().r;
				color.g = attachment->getColor().g;
				color.b = attachment->getColor().b;
				color.a = attachment->getColor().a;
			}
			else if (slot->getAttachment()->getRTTI().isExactly(MeshAttachment::rtti)) {
				MeshAttachment* attachment = (MeshAttachment*)slot->getAttachment();
				attachmentVertices = (AttachmentVertices*)attachment->getRendererObject();
				
				// Early exit if attachment is invisible
				if (attachment->getColor().a == 0) {
					_clipper->clipEnd(*slot);
					continue;
				}
				
				if (!isTwoColorTint) {
					triangles.indices = attachmentVertices->_triangles->indices;
					triangles.indexCount = attachmentVertices->_triangles->indexCount;
					triangles.verts = batch->allocateVertices(attachmentVertices->_triangles->vertCount);
					triangles.vertCount = attachmentVertices->_triangles->vertCount;
					memcpy(triangles.verts, attachmentVertices->_triangles->verts, sizeof(cocos2d::V3F_C4B_T2F) * attachmentVertices->_triangles->vertCount);
					attachment->computeWorldVertices(*slot, 0, attachment->getWorldVerticesLength(), (float*)triangles.verts, 0, 6);
				} else {
					trianglesTwoColor.indices = attachmentVertices->_triangles->indices;
					trianglesTwoColor.indexCount = attachmentVertices->_triangles->indexCount;
					trianglesTwoColor.verts = twoColorBatch->allocateVertices(attachmentVertices->_triangles->vertCount);
					trianglesTwoColor.vertCount = attachmentVertices->_triangles->vertCount;
					for (int i = 0; i < trianglesTwoColor.vertCount; i++) {
						trianglesTwoColor.verts[i].texCoords = attachmentVertices->_triangles->verts[i].texCoords;
					}
					attachment->computeWorldVertices(*slot, 0,  attachment->getWorldVerticesLength(), (float*)trianglesTwoColor.verts, 0, 7);
				}
				
				color.r = attachment->getColor().r;
				color.g = attachment->getColor().g;
				color.b = attachment->getColor().b;
				color.a = attachment->getColor().a;
			}
			else if (slot->getAttachment()->getRTTI().isExactly(ClippingAttachment::rtti)) {
				ClippingAttachment* clip = (ClippingAttachment*)slot->getAttachment();
				_clipper->clipStart(*slot, clip);
				continue;
			} else {
				_clipper->clipEnd(*slot);
				continue;
			}
			
			float alpha = nodeColor.a * _skeleton->getColor().a * slot->getColor().a * color.a * 255;
			// skip rendering if the color of this attachment is 0
			if (alpha == 0){
				_clipper->clipEnd(*slot);
				continue;
			}
			float multiplier = _premultipliedAlpha ? alpha : 255;
			float red = nodeColor.r * _skeleton->getColor().r * color.r * multiplier;
			float green = nodeColor.g * _skeleton->getColor().g * color.g * multiplier;
			float blue = nodeColor.b * _skeleton->getColor().b * color.b * multiplier;
			
			color.r = red * slot->getColor().r;
			color.g = green * slot->getColor().g;
			color.b = blue * slot->getColor().b;
			color.a = alpha;
			
			if (slot->hasDarkColor()) {
				darkColor.r = red * slot->getDarkColor().r;
				darkColor.g = green * slot->getDarkColor().g;
				darkColor.b = blue * slot->getDarkColor().b;
			} else {
				darkColor.r = 0;
				darkColor.g = 0;
				darkColor.b = 0;
			}
			darkColor.a = darkPremultipliedAlpha;
			
			BlendFunc blendFunc;
			switch (slot->getData().getBlendMode()) {
				case BlendMode_Additive:
					blendFunc.src = _premultipliedAlpha ? backend::BlendFactor::ONE : backend::BlendFactor::SRC_ALPHA;
					blendFunc.dst = backend::BlendFactor::ONE;
					break;
				case BlendMode_Multiply:
					blendFunc.src = backend::BlendFactor::DST_COLOR;
					blendFunc.dst = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
					break;
				case BlendMode_Screen:
					blendFunc.src = backend::BlendFactor::ONE;
					blendFunc.dst = backend::BlendFactor::ONE_MINUS_SRC_COLOR;
					break;
				default:
					blendFunc.src = _premultipliedAlpha ? backend::BlendFactor::ONE : backend::BlendFactor::SRC_ALPHA;
					blendFunc.dst = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
			}
			
			if (!isTwoColorTint) {
				if (_clipper->isClipping()) {
					_clipper->clipTriangles((float*)&triangles.verts[0].vertices, triangles.indices, triangles.indexCount, (float*)&triangles.verts[0].texCoords, sizeof(cocos2d::V3F_C4B_T2F) / 4);
					batch->deallocateVertices(triangles.vertCount);
					
					if (_clipper->getClippedTriangles().size() == 0){
						_clipper->clipEnd(*slot);
						continue;
					}
					
					triangles.vertCount = _clipper->getClippedVertices().size() >> 1;
					triangles.verts = batch->allocateVertices(triangles.vertCount);
					triangles.indexCount = _clipper->getClippedTriangles().size();
					triangles.indices = batch->allocateIndices(triangles.indexCount);
					memcpy(triangles.indices, _clipper->getClippedTriangles().buffer(), sizeof(unsigned short) * _clipper->getClippedTriangles().size());
					
					cocos2d::TrianglesCommand* batchedTriangles = batch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture, blendFunc, triangles, transform, transformFlags);
					
					float* verts = _clipper->getClippedVertices().buffer();
					float* uvs = _clipper->getClippedUVs().buffer();
					if (_effect) {
						Color light;
						Color dark;
						light.r = color.r / 255.0f;
						light.g = color.g / 255.0f;
						light.b = color.b / 255.0f;
						light.a = color.a / 255.0f;
						dark.r = dark.g = dark.b = dark.a = 0;
						for (int v = 0, vn = batchedTriangles->getTriangles().vertCount, vv = 0; v < vn; ++v, vv+=2) {
							V3F_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
							Color lightCopy = light;
							Color darkCopy = dark;
							vertex->vertices.x = verts[vv];
							vertex->vertices.y = verts[vv + 1];
							vertex->texCoords.u = uvs[vv];
							vertex->texCoords.v = uvs[vv + 1];
							_effect->transform(vertex->vertices.x, vertex->vertices.y, vertex->texCoords.u, vertex->texCoords.v, lightCopy, darkCopy);
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
					cocos2d::TrianglesCommand* batchedTriangles = batch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture, blendFunc, triangles, transform, transformFlags);
					
					if (_effect) {
						Color light;
						Color dark;
						light.r = color.r / 255.0f;
						light.g = color.g / 255.0f;
						light.b = color.b / 255.0f;
						light.a = color.a / 255.0f;
						dark.r = dark.g = dark.b = dark.a = 0;
						for (int v = 0, vn = batchedTriangles->getTriangles().vertCount; v < vn; ++v) {
							V3F_C4B_T2F* vertex = batchedTriangles->getTriangles().verts + v;
							Color lightCopy = light;
							Color darkCopy = dark;
							_effect->transform(vertex->vertices.x, vertex->vertices.y, vertex->texCoords.u, vertex->texCoords.v, lightCopy,  darkCopy);
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
				if (_clipper->isClipping()) {
					_clipper->clipTriangles((float*)&trianglesTwoColor.verts[0].position, trianglesTwoColor.indices, trianglesTwoColor.indexCount, (float*)&trianglesTwoColor.verts[0].texCoords, sizeof(V3F_C4B_C4B_T2F) / 4);
					twoColorBatch->deallocateVertices(trianglesTwoColor.vertCount);
					
					if (_clipper->getClippedTriangles().size() == 0){
						_clipper->clipEnd(*slot);
						continue;
					}
					
					trianglesTwoColor.vertCount = _clipper->getClippedVertices().size() >> 1;
					trianglesTwoColor.verts = twoColorBatch->allocateVertices(trianglesTwoColor.vertCount);
					trianglesTwoColor.indexCount = _clipper->getClippedTriangles().size();
					trianglesTwoColor.indices = twoColorBatch->allocateIndices(trianglesTwoColor.indexCount);
					memcpy(trianglesTwoColor.indices, _clipper->getClippedTriangles().buffer(), sizeof(unsigned short) * _clipper->getClippedTriangles().size());
					
					TwoColorTrianglesCommand* batchedTriangles = lastTwoColorTrianglesCommand = twoColorBatch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture, blendFunc, trianglesTwoColor, transform, transformFlags);
					
					float* verts = _clipper->getClippedVertices().buffer();
					float* uvs = _clipper->getClippedUVs().buffer();
					
					if (_effect) {
						Color light;
						Color dark;
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
							Color lightCopy = light;
							Color darkCopy = dark;
							vertex->position.x = verts[vv];
							vertex->position.y = verts[vv + 1];
							vertex->texCoords.u = uvs[vv];
							vertex->texCoords.v = uvs[vv + 1];
							_effect->transform(vertex->position.x, vertex->position.y, vertex->texCoords.u, vertex->texCoords.v, lightCopy, darkCopy);
							vertex->color.r = (GLubyte)(lightCopy.r * 255);
							vertex->color.g = (GLubyte)(lightCopy.g * 255);
							vertex->color.b = (GLubyte)(lightCopy.b * 255);
							vertex->color.a = (GLubyte)(lightCopy.a * 255);
							vertex->color2.r = (GLubyte)(darkCopy.r * 255);
							vertex->color2.g = (GLubyte)(darkCopy.g * 255);
							vertex->color2.b = (GLubyte)(darkCopy.b * 255);
							vertex->color2.a = (GLubyte)darkColor.a;
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
							vertex->color2.a = (GLubyte)darkColor.a;
						}
					}
				} else {
					TwoColorTrianglesCommand* batchedTriangles = lastTwoColorTrianglesCommand = twoColorBatch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture, blendFunc, trianglesTwoColor, transform, transformFlags);
					
					if (_effect) {
						Color light;
						Color dark;
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
							Color lightCopy = light;
							Color darkCopy = dark;
							_effect->transform(vertex->position.x, vertex->position.y, vertex->texCoords.u, vertex->texCoords.v, lightCopy, darkCopy);
							vertex->color.r = (GLubyte)(lightCopy.r * 255);
							vertex->color.g = (GLubyte)(lightCopy.g * 255);
							vertex->color.b = (GLubyte)(lightCopy.b * 255);
							vertex->color.a = (GLubyte)(lightCopy.a * 255);
							vertex->color2.r = (GLubyte)(darkCopy.r * 255);
							vertex->color2.g = (GLubyte)(darkCopy.g * 255);
							vertex->color2.b = (GLubyte)(darkCopy.b * 255);
							vertex->color2.a = (GLubyte)darkColor.a;
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
							vertex->color2.a = (GLubyte)darkColor.a;
						}
					}
				}
			}
			_clipper->clipEnd(*slot);
		}
		_clipper->clipEnd();
		
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
				cocos2d::Vector<Node*>& children = parent->getChildren();
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
		
		if (_effect) _effect->end();
		
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
            drawNode->setLineWidth(1.0f);
			Vec2 points[4];
			V3F_C4B_T2F_Quad quad;
			for (int i = 0, n = _skeleton->getSlots().size(); i < n; i++) {
				Slot* slot = _skeleton->getDrawOrder()[i];
				if (!slot->getAttachment() || !slot->getAttachment()->getRTTI().isExactly(RegionAttachment::rtti)) continue;
				RegionAttachment* attachment = (RegionAttachment*)slot->getAttachment();
				attachment->computeWorldVertices(slot->getBone(), worldVertices, 0, 2);
				points[0] = Vec2(worldVertices[0], worldVertices[1]);
				points[1] = Vec2(worldVertices[2], worldVertices[3]);
				points[2] = Vec2(worldVertices[4], worldVertices[5]);
				points[3] = Vec2(worldVertices[6], worldVertices[7]);
				drawNode->drawPoly(points, 4, true, Color4F::BLUE);
			}
		}
		if (_debugBones) {
			// Bone lengths.
            drawNode->setLineWidth(2.0f);
			for (int i = 0, n = _skeleton->getBones().size(); i < n; i++) {
				Bone *bone = _skeleton->getBones()[i];
				float x = bone->getData().getLength() * bone->getA() + bone->getWorldX();
				float y = bone->getData().getLength() * bone->getC() + bone->getWorldY();
				drawNode->drawLine(Vec2(bone->getWorldX(), bone->getWorldY()), Vec2(x, y), Color4F::RED);
			}
			// Bone origins.
			auto color = Color4F::BLUE; // Root bone is blue.
			for (int i = 0, n = _skeleton->getBones().size(); i < n; i++) {
				Bone *bone = _skeleton->getBones()[i];
				drawNode->drawPoint(Vec2(bone->getWorldX(), bone->getWorldY()), 4, color);
				if (i == 0) color = Color4F::GREEN;
			}
		}
		
		if (_debugMeshes) {
			// Meshes.
            drawNode->setLineWidth(1.0f);
			for (int i = 0, n = _skeleton->getSlots().size(); i < n; ++i) {
				Slot* slot = _skeleton->getDrawOrder()[i];
				if (!slot->getAttachment() || !slot->getAttachment()->getRTTI().isExactly(MeshAttachment::rtti)) continue;
				MeshAttachment* attachment = (MeshAttachment*)slot->getAttachment();
				ensureWorldVerticesCapacity(attachment->getWorldVerticesLength());
				attachment->computeWorldVertices(*slot, 0, attachment->getWorldVerticesLength(), worldVertices, 0, 2);
				for (int ii = 0; ii < attachment->getTriangles().size();) {
					Vec2 v1(worldVertices + (attachment->getTriangles()[ii++] * 2));
					Vec2 v2(worldVertices + (attachment->getTriangles()[ii++] * 2));
					Vec2 v3(worldVertices + (attachment->getTriangles()[ii++] * 2));
					drawNode->drawLine(v1, v2, Color4F::YELLOW);
					drawNode->drawLine(v2, v3, Color4F::YELLOW);
					drawNode->drawLine(v3, v1, Color4F::YELLOW);
				}
			}
			
		}
		
		drawNode->draw(renderer, transform, transformFlags);
		director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	}
	
	Rect SkeletonRenderer::getBoundingBox () const {
		float minX = FLT_MAX, minY = FLT_MAX, maxX = -FLT_MAX, maxY = -FLT_MAX;
		float scaleX = getScaleX(), scaleY = getScaleY();
		for (int i = 0; i < _skeleton->getSlots().size(); ++i) {
			Slot* slot = _skeleton->getSlots()[i];
			if (!slot->getAttachment()) continue;
			int verticesCount;
			if (slot->getAttachment()->getRTTI().isExactly(RegionAttachment::rtti)) {
				RegionAttachment* attachment = (RegionAttachment*)slot->getAttachment();
				attachment->computeWorldVertices(slot->getBone(), worldVertices, 0, 2);
				verticesCount = 8;
			} else if (slot->getAttachment()->getRTTI().isExactly(MeshAttachment::rtti)) {
				MeshAttachment* mesh = (MeshAttachment*)slot->getAttachment();
				ensureWorldVerticesCapacity(mesh->getWorldVerticesLength());
				mesh->computeWorldVertices(*slot, 0, mesh->getWorldVerticesLength(), worldVertices, 0, 2);
				verticesCount = mesh->getWorldVerticesLength();
			} else
				continue;
			for (int ii = 0; ii < verticesCount; ii += 2) {
				float x = worldVertices[ii] * scaleX, y = worldVertices[ii + 1] * scaleY;
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
		_skeleton->updateWorldTransform();
	}
	
	void SkeletonRenderer::setToSetupPose () {
		_skeleton->setToSetupPose();
	}
	void SkeletonRenderer::setBonesToSetupPose () {
		_skeleton->setBonesToSetupPose();
	}
	void SkeletonRenderer::setSlotsToSetupPose () {
		_skeleton->setSlotsToSetupPose();
	}
	
	Bone* SkeletonRenderer::findBone (const std::string& boneName) const {
		return _skeleton->findBone(boneName.c_str());
	}
	
	Slot* SkeletonRenderer::findSlot (const std::string& slotName) const {
		return _skeleton->findSlot(slotName.c_str());
	}
	
	void SkeletonRenderer::setSkin (const std::string& skinName) {
		_skeleton->setSkin(skinName.empty() ? 0 : skinName.c_str());
	}
	void SkeletonRenderer::setSkin (const char* skinName) {
		_skeleton->setSkin(skinName);
	}
	
	Attachment* SkeletonRenderer::getAttachment (const std::string& slotName, const std::string& attachmentName) const {
		return _skeleton->getAttachment(slotName.c_str(), attachmentName.c_str());
	}
	bool SkeletonRenderer::setAttachment (const std::string& slotName, const std::string& attachmentName) {
		return _skeleton->getAttachment(slotName.c_str(), attachmentName.empty() ? 0 : attachmentName.c_str()) ? true : false;
	}
	bool SkeletonRenderer::setAttachment (const std::string& slotName, const char* attachmentName) {
		return _skeleton->getAttachment(slotName.c_str(), attachmentName) ? true : false;
	}
	
	void SkeletonRenderer::setTwoColorTint(bool enabled) {
		setupGLProgramState(enabled);
	}
	
	bool SkeletonRenderer::isTwoColorTint() {
        return _twoColorTintEnabled;
	}
	
	void SkeletonRenderer::setVertexEffect(VertexEffect *effect) {
		this->_effect = effect;
	}
	
	void SkeletonRenderer::setSlotsRange(int startSlotIndex, int endSlotIndex) {
		this->_startSlotIndex = startSlotIndex;
		this->_endSlotIndex = endSlotIndex;
	}
	
	Skeleton* SkeletonRenderer::getSkeleton () {
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
