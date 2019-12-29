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

#ifndef Spine_SkeletonJson_h
#define Spine_SkeletonJson_h

#include <spine/Vector.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>

namespace spine {
class CurveTimeline;

class VertexAttachment;

class Animation;

class Json;

class SkeletonData;

class Atlas;

class AttachmentLoader;

class LinkedMesh;

class String;

class SP_API SkeletonJson : public SpineObject {
public:
	explicit SkeletonJson(Atlas *atlas);

	explicit SkeletonJson(AttachmentLoader *attachmentLoader);

	~SkeletonJson();

	SkeletonData *readSkeletonDataFile(const String &path);

	SkeletonData *readSkeletonData(const char *json);

	void setScale(float scale) { _scale = scale; }

	String &getError() { return _error; }

private:
	AttachmentLoader *_attachmentLoader;
	Vector<LinkedMesh *> _linkedMeshes;
	float _scale;
	const bool _ownsLoader;
	String _error;

	static float toColor(const char *value, size_t index);

	static void readCurve(Json *frame, CurveTimeline *timeline, size_t frameIndex);

	Animation *readAnimation(Json *root, SkeletonData *skeletonData);

	void readVertices(Json *attachmentMap, VertexAttachment *attachment, size_t verticesLength);

	void setError(Json *root, const String &value1, const String &value2);
};
}

#endif /* Spine_SkeletonJson_h */
