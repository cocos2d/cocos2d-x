/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/SkeletonRenderer.h>
#include <spine/extension.h>
#include <spine/SkeletonBatch.h>
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

	_blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
	setOpacityModifyRGB(true);

	setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
}

void SkeletonRenderer::setSkeletonData (spSkeletonData *skeletonData, bool ownsSkeletonData) {
	_skeleton = spSkeleton_create(skeletonData);
	_ownsSkeletonData = ownsSkeletonData;
}

SkeletonRenderer::SkeletonRenderer ()
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _timeScale(1) {
}

SkeletonRenderer::SkeletonRenderer (spSkeletonData *skeletonData, bool ownsSkeletonData)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _timeScale(1) {
	initWithData(skeletonData, ownsSkeletonData);
}

SkeletonRenderer::SkeletonRenderer (const std::string& skeletonDataFile, spAtlas* atlas, float scale)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _timeScale(1) {
	initWithJsonFile(skeletonDataFile, atlas, scale);
}

SkeletonRenderer::SkeletonRenderer (const std::string& skeletonDataFile, const std::string& atlasFile, float scale)
	: _atlas(nullptr), _attachmentLoader(nullptr), _debugSlots(false), _debugBones(false), _timeScale(1) {
	initWithJsonFile(skeletonDataFile, atlasFile, scale);
}

SkeletonRenderer::~SkeletonRenderer () {
	if (_ownsSkeletonData) spSkeletonData_dispose(_skeleton->data);
	spSkeleton_dispose(_skeleton);
	if (_atlas) spAtlas_dispose(_atlas);
	if (_attachmentLoader) spAttachmentLoader_dispose(_attachmentLoader);
	delete [] _worldVertices;
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
	spSkeleton_update(_skeleton, deltaTime * _timeScale);
}

void SkeletonRenderer::draw (Renderer* renderer, const Mat4& transform, uint32_t transformFlags) {
	SkeletonBatch* batch = SkeletonBatch::getInstance();

	Color3B nodeColor = getColor();
	_skeleton->r = nodeColor.r / (float)255;
	_skeleton->g = nodeColor.g / (float)255;
	_skeleton->b = nodeColor.b / (float)255;
	_skeleton->a = getDisplayedOpacity() / (float)255;
    
    Color4F color;
	AttachmentVertices* attachmentVertices = nullptr;
	for (int i = 0, n = _skeleton->slotsCount; i < n; ++i) {
		spSlot* slot = _skeleton->drawOrder[i];
		if (!slot->attachment) continue;

		switch (slot->attachment->type) {
		case SP_ATTACHMENT_REGION: {
			spRegionAttachment* attachment = (spRegionAttachment*)slot->attachment;
			spRegionAttachment_computeWorldVertices(attachment, slot->bone, _worldVertices);
			attachmentVertices = getAttachmentVertices(attachment);
            color.r = attachment->r;
			color.g = attachment->g;
			color.b = attachment->b;
			color.a = attachment->a;
			break;
		}
		case SP_ATTACHMENT_MESH: {
			spMeshAttachment* attachment = (spMeshAttachment*)slot->attachment;
			spMeshAttachment_computeWorldVertices(attachment, slot, _worldVertices);
			attachmentVertices = getAttachmentVertices(attachment);
            color.r = attachment->r;
            color.g = attachment->g;
            color.b = attachment->b;
            color.a = attachment->a;
			break;
		}
		default:
			continue;
		}

		color.a *= _skeleton->a * slot->a * 255;
		float multiplier = _premultipliedAlpha ? color.a : 255;
		color.r *= _skeleton->r * slot->r * multiplier;
		color.g *= _skeleton->g * slot->g * multiplier;
		color.b *= _skeleton->b * slot->b * multiplier;
        
        
        
		for (int v = 0, w = 0, vn = attachmentVertices->_triangles->vertCount; v < vn; ++v, w += 2) {
			V3F_C4B_T2F* vertex = attachmentVertices->_triangles->verts + v;
			vertex->vertices.x = _worldVertices[w];
			vertex->vertices.y = _worldVertices[w + 1];
            vertex->colors.r = (GLubyte)color.r;
            vertex->colors.g = (GLubyte)color.g;
            vertex->colors.b = (GLubyte)color.b;
            vertex->colors.a = (GLubyte)color.a;
		}

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

		batch->addCommand(renderer, _globalZOrder, attachmentVertices->_texture->getName(), _glProgramState, blendFunc,
			*attachmentVertices->_triangles, transform, transformFlags);
	}

	if (_debugSlots || _debugBones) {
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
            spRegionAttachment_computeWorldVertices(attachment, slot->bone, _worldVertices);
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
			spRegionAttachment_computeWorldVertices(attachment, slot->bone, _worldVertices);
			verticesCount = 8;
		} else if (slot->attachment->type == SP_ATTACHMENT_MESH) {
			spMeshAttachment* mesh = (spMeshAttachment*)slot->attachment;
			spMeshAttachment_computeWorldVertices(mesh, slot, _worldVertices);
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
