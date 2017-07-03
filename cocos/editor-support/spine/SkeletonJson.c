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

#include <spine/SkeletonJson.h>
#include <stdio.h>
#include <locale.h>
#include "Json.h"
#include <spine/extension.h>
#include <spine/AtlasAttachmentLoader.h>
#include <spine/Animation.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define strdup _strdup
#endif

typedef struct {
	const char* parent;
	const char* skin;
	int slotIndex;
	spMeshAttachment* mesh;
} _spLinkedMesh;

typedef struct {
	spSkeletonJson super;
	int ownsLoader;

	int linkedMeshCount;
	int linkedMeshCapacity;
	_spLinkedMesh* linkedMeshes;
} _spSkeletonJson;

spSkeletonJson* spSkeletonJson_createWithLoader (spAttachmentLoader* attachmentLoader) {
	spSkeletonJson* self = SUPER(NEW(_spSkeletonJson));
	self->scale = 1;
	self->attachmentLoader = attachmentLoader;
	return self;
}

spSkeletonJson* spSkeletonJson_create (spAtlas* atlas) {
	spAtlasAttachmentLoader* attachmentLoader = spAtlasAttachmentLoader_create(atlas);
	spSkeletonJson* self = spSkeletonJson_createWithLoader(SUPER(attachmentLoader));
	SUB_CAST(_spSkeletonJson, self)->ownsLoader = 1;
	return self;
}

void spSkeletonJson_dispose (spSkeletonJson* self) {
	_spSkeletonJson* internal = SUB_CAST(_spSkeletonJson, self);
	if (internal->ownsLoader) spAttachmentLoader_dispose(self->attachmentLoader);
	FREE(internal->linkedMeshes);
	FREE(self->error);
	FREE(self);
}

void _spSkeletonJson_setError (spSkeletonJson* self, Json* root, const char* value1, const char* value2) {
	char message[256];
	int length;
	FREE(self->error);
	strcpy(message, value1);
	length = (int)strlen(value1);
	if (value2) strncat(message + length, value2, 255 - length);
	MALLOC_STR(self->error, message);
	if (root) Json_dispose(root);
}

static float toColor (const char* value, int index) {
	char digits[3];
	char *error;
	int color;

	if (strlen(value) != 8) return -1;
	value += index * 2;

	digits[0] = *value;
	digits[1] = *(value + 1);
	digits[2] = '\0';
	color = (int)strtoul(digits, &error, 16);
	if (*error != 0) return -1;
	return color / (float)255;
}

static void readCurve (Json* frame, spCurveTimeline* timeline, int frameIndex) {
	Json* curve = Json_getItem(frame, "curve");
	if (!curve) return;
	if (curve->type == Json_String && strcmp(curve->valueString, "stepped") == 0)
		spCurveTimeline_setStepped(timeline, frameIndex);
	else if (curve->type == Json_Array) {
		Json* child0 = curve->child;
		Json* child1 = child0->next;
		Json* child2 = child1->next;
		Json* child3 = child2->next;
		spCurveTimeline_setCurve(timeline, frameIndex, child0->valueFloat, child1->valueFloat, child2->valueFloat,
				child3->valueFloat);
	}
}

static void _spSkeletonJson_addLinkedMesh (spSkeletonJson* self, spMeshAttachment* mesh, const char* skin, int slotIndex,
		const char* parent) {
	_spLinkedMesh* linkedMesh;
	_spSkeletonJson* internal = SUB_CAST(_spSkeletonJson, self);

	if (internal->linkedMeshCount == internal->linkedMeshCapacity) {
		_spLinkedMesh* linkedMeshes;
		internal->linkedMeshCapacity *= 2;
		if (internal->linkedMeshCapacity < 8) internal->linkedMeshCapacity = 8;
		linkedMeshes = MALLOC(_spLinkedMesh, internal->linkedMeshCapacity);
		memcpy(linkedMeshes, internal->linkedMeshes, sizeof(_spLinkedMesh) * internal->linkedMeshCount);
		FREE(internal->linkedMeshes);
		internal->linkedMeshes = linkedMeshes;
	}

	linkedMesh = internal->linkedMeshes + internal->linkedMeshCount++;
	linkedMesh->mesh = mesh;
	linkedMesh->skin = skin;
	linkedMesh->slotIndex = slotIndex;
	linkedMesh->parent = parent;
}

static spAnimation* _spSkeletonJson_readAnimation (spSkeletonJson* self, Json* root, spSkeletonData *skeletonData) {
	int frameIndex;
	spAnimation* animation;
	Json* valueMap;
	int timelinesCount = 0;

	Json* bones = Json_getItem(root, "bones");
	Json* slots = Json_getItem(root, "slots");
	Json* ik = Json_getItem(root, "ik");
	Json* transform = Json_getItem(root, "transform");
	Json* paths = Json_getItem(root, "paths");
	Json* deformObj = Json_getItem(root, "deform");
	Json* drawOrderObj = Json_getItem(root, "drawOrder");
	Json* events = Json_getItem(root, "events");
	Json *boneMap, *slotMap, *constraintMap;
	if (!drawOrderObj) drawOrderObj = Json_getItem(root, "draworder");

	for (boneMap = bones ? bones->child : 0; boneMap; boneMap = boneMap->next)
		timelinesCount += boneMap->size;
	for (slotMap = slots ? slots->child : 0; slotMap; slotMap = slotMap->next)
		timelinesCount += slotMap->size;
	timelinesCount += ik ? ik->size : 0;
	timelinesCount += transform ? transform->size : 0;
	for (constraintMap = paths ? paths->child : 0; constraintMap; constraintMap = constraintMap->next)
		timelinesCount += constraintMap->size;
	for (constraintMap = deformObj ? deformObj->child : 0; constraintMap; constraintMap = constraintMap->next)
		for (slotMap = constraintMap->child; slotMap; slotMap = slotMap->next)
			timelinesCount += slotMap->size;
	if (drawOrderObj) ++timelinesCount;
	if (events) ++timelinesCount;

	animation = spAnimation_create(root->name, timelinesCount);
	animation->timelinesCount = 0;

	/* Slot timelines. */
	for (slotMap = slots ? slots->child : 0; slotMap; slotMap = slotMap->next) {
		Json *timelineMap;

		int slotIndex = spSkeletonData_findSlotIndex(skeletonData, slotMap->name);
		if (slotIndex == -1) {
			spAnimation_dispose(animation);
			_spSkeletonJson_setError(self, root, "Slot not found: ", slotMap->name);
			return 0;
		}

		for (timelineMap = slotMap->child; timelineMap; timelineMap = timelineMap->next) {
			if (strcmp(timelineMap->name, "color") == 0) {
				spColorTimeline *timeline = spColorTimeline_create(timelineMap->size);
				timeline->slotIndex = slotIndex;

				for (valueMap = timelineMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
					const char* s = Json_getString(valueMap, "color", 0);
					spColorTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), toColor(s, 0), toColor(s, 1), toColor(s, 2),
							toColor(s, 3));
					readCurve(valueMap, SUPER(timeline), frameIndex);
				}
				animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
				animation->duration = MAX(animation->duration, timeline->frames[(timelineMap->size - 1) * COLOR_ENTRIES]);

			} else if (strcmp(timelineMap->name, "attachment") == 0) {
				spAttachmentTimeline *timeline = spAttachmentTimeline_create(timelineMap->size);
				timeline->slotIndex = slotIndex;

				for (valueMap = timelineMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
					Json* name = Json_getItem(valueMap, "name");
					spAttachmentTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0),
							name->type == Json_NULL ? 0 : name->valueString);
				}
				animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
				animation->duration = MAX(animation->duration, timeline->frames[timelineMap->size - 1]);

			} else {
				spAnimation_dispose(animation);
				_spSkeletonJson_setError(self, 0, "Invalid timeline type for a slot: ", timelineMap->name);
				return 0;
			}
		}
	}

	/* Bone timelines. */
	for (boneMap = bones ? bones->child : 0; boneMap; boneMap = boneMap->next) {
		Json *timelineMap;

		int boneIndex = spSkeletonData_findBoneIndex(skeletonData, boneMap->name);
		if (boneIndex == -1) {
			spAnimation_dispose(animation);
			_spSkeletonJson_setError(self, root, "Bone not found: ", boneMap->name);
			return 0;
		}

		for (timelineMap = boneMap->child; timelineMap; timelineMap = timelineMap->next) {
			if (strcmp(timelineMap->name, "rotate") == 0) {
				spRotateTimeline *timeline = spRotateTimeline_create(timelineMap->size);
				timeline->boneIndex = boneIndex;

				for (valueMap = timelineMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
					spRotateTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), Json_getFloat(valueMap, "angle", 0));
					readCurve(valueMap, SUPER(timeline), frameIndex);
				}
				animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
				animation->duration = MAX(animation->duration, timeline->frames[(timelineMap->size - 1) * ROTATE_ENTRIES]);

			} else {
				int isScale = strcmp(timelineMap->name, "scale") == 0;
				int isTranslate = strcmp(timelineMap->name, "translate") == 0;
				int isShear = strcmp(timelineMap->name, "shear") == 0;
				if (isScale || isTranslate || isShear) {
					float timelineScale = isTranslate ? self->scale: 1;
					spTranslateTimeline *timeline = 0;
					if (isScale) timeline = spScaleTimeline_create(timelineMap->size);
					else if (isTranslate) timeline = spTranslateTimeline_create(timelineMap->size);
					else if (isShear) timeline = spShearTimeline_create(timelineMap->size);
					timeline->boneIndex = boneIndex;

					for (valueMap = timelineMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
						spTranslateTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), Json_getFloat(valueMap, "x", 0) * timelineScale,
								Json_getFloat(valueMap, "y", 0) * timelineScale);
						readCurve(valueMap, SUPER(timeline), frameIndex);
					}
					animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
					animation->duration = MAX(animation->duration, timeline->frames[(timelineMap->size - 1) * TRANSLATE_ENTRIES]);

				} else {
					spAnimation_dispose(animation);
					_spSkeletonJson_setError(self, 0, "Invalid timeline type for a bone: ", timelineMap->name);
					return 0;
				}
			}
		}
	}

	/* IK constraint timelines. */
	for (constraintMap = ik ? ik->child : 0; constraintMap; constraintMap = constraintMap->next) {
		spIkConstraintData* constraint = spSkeletonData_findIkConstraint(skeletonData, constraintMap->name);
		spIkConstraintTimeline* timeline = spIkConstraintTimeline_create(constraintMap->size);
		for (frameIndex = 0; frameIndex < skeletonData->ikConstraintsCount; ++frameIndex) {
			if (constraint == skeletonData->ikConstraints[frameIndex]) {
				timeline->ikConstraintIndex = frameIndex;
				break;
			}
		}
		for (valueMap = constraintMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
			spIkConstraintTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), Json_getFloat(valueMap, "mix", 1),
					Json_getInt(valueMap, "bendPositive", 1) ? 1 : -1);
			readCurve(valueMap, SUPER(timeline), frameIndex);
		}
		animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
		animation->duration = MAX(animation->duration, timeline->frames[(constraintMap->size - 1) * IKCONSTRAINT_ENTRIES]);
	}

	/* Transform constraint timelines. */
	for (constraintMap = transform ? transform->child : 0; constraintMap; constraintMap = constraintMap->next) {
		spTransformConstraintData* constraint = spSkeletonData_findTransformConstraint(skeletonData, constraintMap->name);
		spTransformConstraintTimeline* timeline = spTransformConstraintTimeline_create(constraintMap->size);
		for (frameIndex = 0; frameIndex < skeletonData->transformConstraintsCount; ++frameIndex) {
			if (constraint == skeletonData->transformConstraints[frameIndex]) {
				timeline->transformConstraintIndex = frameIndex;
				break;
			}
		}
		for (valueMap = constraintMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
			spTransformConstraintTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), Json_getFloat(valueMap, "rotateMix", 1),
					Json_getFloat(valueMap, "translateMix", 1), Json_getFloat(valueMap, "scaleMix", 1), Json_getFloat(valueMap, "shearMix", 1));
			readCurve(valueMap, SUPER(timeline), frameIndex);
		}
		animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
		animation->duration = MAX(animation->duration, timeline->frames[(constraintMap->size - 1) * TRANSFORMCONSTRAINT_ENTRIES]);
	}

	/** Path constraint timelines. */
	for(constraintMap = paths ? paths->child : 0; constraintMap; constraintMap = constraintMap->next ) {
		int constraintIndex, i;
		Json* timelineMap;

		spPathConstraintData* data = spSkeletonData_findPathConstraint(skeletonData, constraintMap->name);
		if (!data) {
			spAnimation_dispose(animation);
			_spSkeletonJson_setError(self, root, "Path constraint not found: ", constraintMap->name);
			return 0;
		}
		for (i = 0; i < skeletonData->pathConstraintsCount; i++) {
			if (skeletonData->pathConstraints[i] == data) {
				constraintIndex = i;
				break;
			}
		}

		for (timelineMap = constraintMap->child; timelineMap; timelineMap = timelineMap->next) {
			const char* timelineName = timelineMap->name;
			if (strcmp(timelineName, "position") == 0 || strcmp(timelineName, "spacing") == 0) {
				spPathConstraintPositionTimeline* timeline;
				float timelineScale = 1;
				if (strcmp(timelineName, "spacing") == 0) {
					timeline = (spPathConstraintPositionTimeline*)spPathConstraintSpacingTimeline_create(timelineMap->size);
					if (data->spacingMode == SP_SPACING_MODE_LENGTH || data->spacingMode == SP_SPACING_MODE_FIXED) timelineScale = self->scale;
				} else {
					timeline = spPathConstraintPositionTimeline_create(timelineMap->size);
					if (data->positionMode == SP_POSITION_MODE_FIXED) timelineScale = self->scale;
				}
				timeline->pathConstraintIndex = constraintIndex;
				for (valueMap = timelineMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
					spPathConstraintPositionTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), Json_getFloat(valueMap, timelineName, 0) * timelineScale);
					readCurve(valueMap, SUPER(timeline), frameIndex);
				}
				animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
				animation->duration = MAX(animation->duration, timeline->frames[(timelineMap->size - 1) * PATHCONSTRAINTPOSITION_ENTRIES]);
			} else if (strcmp(timelineName, "mix")) {
				spPathConstraintMixTimeline* timeline = spPathConstraintMixTimeline_create(timelineMap->size);
				timeline->pathConstraintIndex = constraintIndex;
				for (valueMap = timelineMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
					spPathConstraintMixTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0),
						Json_getFloat(valueMap, "rotateMix", 1), Json_getFloat(valueMap, "translateMix", 1));
					readCurve(valueMap, SUPER(timeline), frameIndex);
				}
				animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
				animation->duration = MAX(animation->duration, timeline->frames[(timelineMap->size - 1) * PATHCONSTRAINTMIX_ENTRIES]);
			}
		}
	}

	/* Deform timelines. */
	for (constraintMap = deformObj ? deformObj->child : 0; constraintMap; constraintMap = constraintMap->next) {
		spSkin* skin = spSkeletonData_findSkin(skeletonData, constraintMap->name);
		for (slotMap = constraintMap->child; slotMap; slotMap = slotMap->next) {
			int slotIndex = spSkeletonData_findSlotIndex(skeletonData, slotMap->name);
			Json* timelineMap;
			for (timelineMap = slotMap->child; timelineMap; timelineMap = timelineMap->next) {
				float* tempDeform;
				spDeformTimeline *timeline;
				int weighted, deformLength;

				spVertexAttachment* attachment = SUB_CAST(spVertexAttachment, spSkin_getAttachment(skin, slotIndex, timelineMap->name));
				if (!attachment) {
					spAnimation_dispose(animation);
					_spSkeletonJson_setError(self, 0, "Attachment not found: ", timelineMap->name);
					return 0;
				}
				weighted = attachment->bones != 0;
				deformLength = weighted ? attachment->verticesCount / 3 * 2 : attachment->verticesCount;
				tempDeform = MALLOC(float, deformLength);

				timeline = spDeformTimeline_create(timelineMap->size, deformLength);
				timeline->slotIndex = slotIndex;
				timeline->attachment = SUPER(attachment);

				for (valueMap = timelineMap->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
					Json* verticesObj = Json_getItem(valueMap, "vertices");
					float* deform;
					if (!verticesObj) {
						if (weighted) {
							deform = tempDeform;
							memset(deform, 0, sizeof(float) * deformLength);
						} else
							deform = attachment->vertices;
					} else {
						int v, start = Json_getInt(valueMap, "offset", 0);
						Json* vertex;
						deform = tempDeform;
						memset(deform, 0, sizeof(float) * start);
						if (self->scale == 1) {
							for (vertex = verticesObj->child, v = start; vertex; vertex = vertex->next, ++v)
								deform[v] = vertex->valueFloat;
						} else {
							for (vertex = verticesObj->child, v = start; vertex; vertex = vertex->next, ++v)
								deform[v] = vertex->valueFloat * self->scale;
						}
						memset(deform + v, 0, sizeof(float) * (deformLength - v));
						if (!weighted) {
							float* vertices = attachment->vertices;
							for (v = 0; v < deformLength; ++v)
								deform[v] += vertices[v];
						}
					}
					spDeformTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), deform);
					readCurve(valueMap, SUPER(timeline), frameIndex);
				}
				FREE(tempDeform);

				animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
				animation->duration = MAX(animation->duration, timeline->frames[timelineMap->size - 1]);
			}
		}
	}

	/* Draw order timeline. */
	if (drawOrderObj) {
		spDrawOrderTimeline* timeline = spDrawOrderTimeline_create(drawOrderObj->size, skeletonData->slotsCount);
		for (valueMap = drawOrderObj->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
			int ii;
			int* drawOrder = 0;
			Json* offsets = Json_getItem(valueMap, "offsets");
			if (offsets) {
				Json* offsetMap;
				int* unchanged = MALLOC(int, skeletonData->slotsCount - offsets->size);
				int originalIndex = 0, unchangedIndex = 0;

				drawOrder = MALLOC(int, skeletonData->slotsCount);
				for (ii = skeletonData->slotsCount - 1; ii >= 0; --ii)
					drawOrder[ii] = -1;

				for (offsetMap = offsets->child; offsetMap; offsetMap = offsetMap->next) {
					int slotIndex = spSkeletonData_findSlotIndex(skeletonData, Json_getString(offsetMap, "slot", 0));
					if (slotIndex == -1) {
						spAnimation_dispose(animation);
						_spSkeletonJson_setError(self, 0, "Slot not found: ", Json_getString(offsetMap, "slot", 0));
						return 0;
					}
					/* Collect unchanged items. */
					while (originalIndex != slotIndex)
						unchanged[unchangedIndex++] = originalIndex++;
					/* Set changed items. */
					drawOrder[originalIndex + Json_getInt(offsetMap, "offset", 0)] = originalIndex;
					originalIndex++;
				}
				/* Collect remaining unchanged items. */
				while (originalIndex < skeletonData->slotsCount)
					unchanged[unchangedIndex++] = originalIndex++;
				/* Fill in unchanged items. */
				for (ii = skeletonData->slotsCount - 1; ii >= 0; ii--)
					if (drawOrder[ii] == -1) drawOrder[ii] = unchanged[--unchangedIndex];
				FREE(unchanged);
			}
			spDrawOrderTimeline_setFrame(timeline, frameIndex, Json_getFloat(valueMap, "time", 0), drawOrder);
			FREE(drawOrder);
		}
		animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
		animation->duration = MAX(animation->duration, timeline->frames[drawOrderObj->size - 1]);
	}

	/* Event timeline. */
	if (events) {
		spEventTimeline* timeline = spEventTimeline_create(events->size);
		for (valueMap = events->child, frameIndex = 0; valueMap; valueMap = valueMap->next, ++frameIndex) {
			spEvent* event;
			const char* stringValue;
			spEventData* eventData = spSkeletonData_findEvent(skeletonData, Json_getString(valueMap, "name", 0));
			if (!eventData) {
				spAnimation_dispose(animation);
				_spSkeletonJson_setError(self, 0, "Event not found: ", Json_getString(valueMap, "name", 0));
				return 0;
			}
			event = spEvent_create(Json_getFloat(valueMap, "time", 0), eventData);
			event->intValue = Json_getInt(valueMap, "int", eventData->intValue);
			event->floatValue = Json_getFloat(valueMap, "float", eventData->floatValue);
			stringValue = Json_getString(valueMap, "string", eventData->stringValue);
			if (stringValue) MALLOC_STR(event->stringValue, stringValue);
			spEventTimeline_setFrame(timeline, frameIndex, event);
		}
		animation->timelines[animation->timelinesCount++] = SUPER_CAST(spTimeline, timeline);
		animation->duration = MAX(animation->duration, timeline->frames[events->size - 1]);
	}

	return animation;
}

static void _readVertices (spSkeletonJson* self, Json* attachmentMap, spVertexAttachment* attachment, int verticesLength) {
	Json* entry;
	float* vertices;
	int i, b, w, nn, entrySize;

	attachment->worldVerticesLength = verticesLength;

	entry = Json_getItem(attachmentMap, "vertices");
	entrySize = entry->size;
	vertices = MALLOC(float, entrySize);
	for (entry = entry->child, i = 0; entry; entry = entry->next, ++i)
		vertices[i] = entry->valueFloat;

	if (verticesLength == entrySize) {
		if (self->scale != 1)
			for (i = 0; i < entrySize; ++i)
				vertices[i] *= self->scale;
		attachment->verticesCount = verticesLength;
		attachment->vertices = vertices;

		attachment->bonesCount = 0;
		attachment->bones = 0;
	} else {
		attachment->verticesCount = 0;
		attachment->bonesCount = 0;

		for (i = 0; i < entrySize;) {
			int bonesCount = (int)vertices[i];
			attachment->bonesCount += 1 + bonesCount;
			attachment->verticesCount += 3 * bonesCount;
			i += 1 + bonesCount * 4;
		}

		attachment->vertices = MALLOC(float, attachment->verticesCount);
		attachment->bones = MALLOC(int, attachment->bonesCount);

		for (i = 0, b = 0, w = 0; i < entrySize;) {
			int bonesCount = (int)vertices[i++];
			attachment->bones[b++] = bonesCount;
			for (nn = i + bonesCount * 4; i < nn;) {
				attachment->bones[b++] = (int)vertices[i++];
				attachment->vertices[w++] = vertices[i++] * self->scale;
				attachment->vertices[w++] = vertices[i++] * self->scale;
				attachment->vertices[w++] = vertices[i++];
			}
		}

		FREE(vertices);
	}
}

spSkeletonData* spSkeletonJson_readSkeletonDataFile (spSkeletonJson* self, const char* path) {
	int length;
	spSkeletonData* skeletonData;
	const char* json = _spUtil_readFile(path, &length);
	if (length == 0 || !json) {
		_spSkeletonJson_setError(self, 0, "Unable to read skeleton file: ", path);
		return 0;
	}
	skeletonData = spSkeletonJson_readSkeletonData(self, json);
	FREE(json);
	return skeletonData;
}

spSkeletonData* spSkeletonJson_readSkeletonData (spSkeletonJson* self, const char* json) {
	int i, ii;
	spSkeletonData* skeletonData;
	Json *root, *skeleton, *bones, *boneMap, *ik, *transform, *pathObj, *slots, *skins, *animations, *events;
	char* oldLocale;
	_spSkeletonJson* internal = SUB_CAST(_spSkeletonJson, self);

	FREE(self->error);
	CONST_CAST(char*, self->error) = 0;
	internal->linkedMeshCount = 0;

#ifndef __ANDROID__
	oldLocale = strdup(setlocale(LC_NUMERIC, NULL));
	setlocale(LC_NUMERIC, "C");
#endif

	root = Json_create(json);

#ifndef __ANDROID__
	setlocale(LC_NUMERIC, oldLocale);
	free(oldLocale);
#endif

	if (!root) {
		_spSkeletonJson_setError(self, 0, "Invalid skeleton JSON: ", Json_getError());
		return 0;
	}

	skeletonData = spSkeletonData_create();

	skeleton = Json_getItem(root, "skeleton");
	if (skeleton) {
		MALLOC_STR(skeletonData->hash, Json_getString(skeleton, "hash", 0));
		MALLOC_STR(skeletonData->version, Json_getString(skeleton, "spine", 0));
		skeletonData->width = Json_getFloat(skeleton, "width", 0);
		skeletonData->height = Json_getFloat(skeleton, "height", 0);
	}

	/* Bones. */
	bones = Json_getItem(root, "bones");
	skeletonData->bones = MALLOC(spBoneData*, bones->size);
	for (boneMap = bones->child, i = 0; boneMap; boneMap = boneMap->next, ++i) {
		spBoneData* data;
		const char* transformMode;

		spBoneData* parent = 0;
		const char* parentName = Json_getString(boneMap, "parent", 0);
		if (parentName) {
			parent = spSkeletonData_findBone(skeletonData, parentName);
			if (!parent) {
				spSkeletonData_dispose(skeletonData);
				_spSkeletonJson_setError(self, root, "Parent bone not found: ", parentName);
				return 0;
			}
		}

		data = spBoneData_create(skeletonData->bonesCount, Json_getString(boneMap, "name", 0), parent);
		data->length = Json_getFloat(boneMap, "length", 0) * self->scale;
		data->x = Json_getFloat(boneMap, "x", 0) * self->scale;
		data->y = Json_getFloat(boneMap, "y", 0) * self->scale;
		data->rotation = Json_getFloat(boneMap, "rotation", 0);
		data->scaleX = Json_getFloat(boneMap, "scaleX", 1);
		data->scaleY = Json_getFloat(boneMap, "scaleY", 1);
		data->shearX = Json_getFloat(boneMap, "shearX", 0);
		data->shearY = Json_getFloat(boneMap, "shearY", 0);
		transformMode = Json_getString(boneMap, "transform", "normal");
		data->transformMode = SP_TRANSFORMMODE_NORMAL;
		if (strcmp(transformMode, "normal") == 0)
			data->transformMode = SP_TRANSFORMMODE_NORMAL;
		if (strcmp(transformMode, "onlyTranslation") == 0)
			data->transformMode = SP_TRANSFORMMODE_ONLYTRANSLATION;
		if (strcmp(transformMode, "noRotationOrReflection") == 0)
			data->transformMode = SP_TRANSFORMMODE_NOROTATIONORREFLECTION;
		if (strcmp(transformMode, "noScale") == 0)
			data->transformMode = SP_TRANSFORMMODE_NOSCALE;
		if (strcmp(transformMode, "noScaleOrReflection") == 0)
			data->transformMode = SP_TRANSFORMMODE_NOSCALEORREFLECTION;

		skeletonData->bones[i] = data;
		skeletonData->bonesCount++;
	}

	/* Slots. */
	slots = Json_getItem(root, "slots");
	if (slots) {
		Json *slotMap;
		skeletonData->slotsCount = slots->size;
		skeletonData->slots = MALLOC(spSlotData*, slots->size);
		for (slotMap = slots->child, i = 0; slotMap; slotMap = slotMap->next, ++i) {
			spSlotData* data;
			const char* color;
			Json *item;

			const char* boneName = Json_getString(slotMap, "bone", 0);
			spBoneData* boneData = spSkeletonData_findBone(skeletonData, boneName);
			if (!boneData) {
				spSkeletonData_dispose(skeletonData);
				_spSkeletonJson_setError(self, root, "Slot bone not found: ", boneName);
				return 0;
			}

			data = spSlotData_create(i, Json_getString(slotMap, "name", 0), boneData);

			color = Json_getString(slotMap, "color", 0);
			if (color) {
				data->r = toColor(color, 0);
				data->g = toColor(color, 1);
				data->b = toColor(color, 2);
				data->a = toColor(color, 3);
			}

			item = Json_getItem(slotMap, "attachment");
			if (item) spSlotData_setAttachmentName(data, item->valueString);

			item = Json_getItem(slotMap, "blend");
			if (item) {
				if (strcmp(item->valueString, "additive") == 0)
					data->blendMode = SP_BLEND_MODE_ADDITIVE;
				else if (strcmp(item->valueString, "multiply") == 0)
					data->blendMode = SP_BLEND_MODE_MULTIPLY;
				else if (strcmp(item->valueString, "screen") == 0)
					data->blendMode = SP_BLEND_MODE_SCREEN;
			}

			skeletonData->slots[i] = data;
		}
	}

	/* IK constraints. */
	ik = Json_getItem(root, "ik");
	if (ik) {
		Json *constraintMap;
		skeletonData->ikConstraintsCount = ik->size;
		skeletonData->ikConstraints = MALLOC(spIkConstraintData*, ik->size);
		for (constraintMap = ik->child, i = 0; constraintMap; constraintMap = constraintMap->next, ++i) {
			const char* targetName;

			spIkConstraintData* data = spIkConstraintData_create(Json_getString(constraintMap, "name", 0));
			data->order = Json_getInt(constraintMap, "order", 0);

			boneMap = Json_getItem(constraintMap, "bones");
			data->bonesCount = boneMap->size;
			data->bones = MALLOC(spBoneData*, boneMap->size);
			for (boneMap = boneMap->child, ii = 0; boneMap; boneMap = boneMap->next, ++ii) {
				data->bones[ii] = spSkeletonData_findBone(skeletonData, boneMap->valueString);
				if (!data->bones[ii]) {
					spSkeletonData_dispose(skeletonData);
					_spSkeletonJson_setError(self, root, "IK bone not found: ", boneMap->valueString);
					return 0;
				}
			}

			targetName = Json_getString(constraintMap, "target", 0);
			data->target = spSkeletonData_findBone(skeletonData, targetName);
			if (!data->target) {
				spSkeletonData_dispose(skeletonData);
				_spSkeletonJson_setError(self, root, "Target bone not found: ", boneMap->name);
				return 0;
			}

			data->bendDirection = Json_getInt(constraintMap, "bendPositive", 1) ? 1 : -1;
			data->mix = Json_getFloat(constraintMap, "mix", 1);

			skeletonData->ikConstraints[i] = data;
		}
	}

	/* Transform constraints. */
	transform = Json_getItem(root, "transform");
	if (transform) {
		Json *constraintMap;
		skeletonData->transformConstraintsCount = transform->size;
		skeletonData->transformConstraints = MALLOC(spTransformConstraintData*, transform->size);
		for (constraintMap = transform->child, i = 0; constraintMap; constraintMap = constraintMap->next, ++i) {
			const char* name;

			spTransformConstraintData* data = spTransformConstraintData_create(Json_getString(constraintMap, "name", 0));
			data->order = Json_getInt(constraintMap, "order", 0);

			boneMap = Json_getItem(constraintMap, "bones");
			data->bonesCount = boneMap->size;
			CONST_CAST(spBoneData**, data->bones) = MALLOC(spBoneData*, boneMap->size);
			for (boneMap = boneMap->child, ii = 0; boneMap; boneMap = boneMap->next, ++ii) {
				data->bones[ii] = spSkeletonData_findBone(skeletonData, boneMap->valueString);
				if (!data->bones[ii]) {
					spSkeletonData_dispose(skeletonData);
					_spSkeletonJson_setError(self, root, "Transform bone not found: ", boneMap->valueString);
					return 0;
				}
			}

			name = Json_getString(constraintMap, "target", 0);
			data->target = spSkeletonData_findBone(skeletonData, name);
			if (!data->target) {
				spSkeletonData_dispose(skeletonData);
				_spSkeletonJson_setError(self, root, "Target bone not found: ", boneMap->name);
				return 0;
			}

			data->offsetRotation = Json_getFloat(constraintMap, "rotation", 0);
			data->offsetX = Json_getFloat(constraintMap, "x", 0) * self->scale;
			data->offsetY = Json_getFloat(constraintMap, "y", 0) * self->scale;
			data->offsetScaleX = Json_getFloat(constraintMap, "scaleX", 0);
			data->offsetScaleY = Json_getFloat(constraintMap, "scaleY", 0);
			data->offsetShearY = Json_getFloat(constraintMap, "shearY", 0);

			data->rotateMix = Json_getFloat(constraintMap, "rotateMix", 1);
			data->translateMix = Json_getFloat(constraintMap, "translateMix", 1);
			data->scaleMix = Json_getFloat(constraintMap, "scaleMix", 1);
			data->shearMix = Json_getFloat(constraintMap, "shearMix", 1);

			skeletonData->transformConstraints[i] = data;
		}
	}

	/* Path constraints */
	pathObj = Json_getItem(root, "path");
	if (pathObj) {
		Json *constraintMap;
		skeletonData->pathConstraintsCount = pathObj->size;
		skeletonData->pathConstraints = MALLOC(spPathConstraintData*, pathObj->size);
		for (constraintMap = pathObj->child, i = 0; constraintMap; constraintMap = constraintMap->next, ++i) {
			const char* name;
			const char* item;

			spPathConstraintData* data = spPathConstraintData_create(Json_getString(constraintMap, "name", 0));
			data->order = Json_getInt(constraintMap, "order", 0);

			boneMap = Json_getItem(constraintMap, "bones");
			data->bonesCount = boneMap->size;
			CONST_CAST(spBoneData**, data->bones) = MALLOC(spBoneData*, boneMap->size);
			for (boneMap = boneMap->child, ii = 0; boneMap; boneMap = boneMap->next, ++ii) {
				data->bones[ii] = spSkeletonData_findBone(skeletonData, boneMap->valueString);
				if (!data->bones[ii]) {
					spSkeletonData_dispose(skeletonData);
					_spSkeletonJson_setError(self, root, "Path bone not found: ", boneMap->valueString);
					return 0;
				}
			}

			name = Json_getString(constraintMap, "target", 0);
			data->target = spSkeletonData_findSlot(skeletonData, name);
			if (!data->target) {
				spSkeletonData_dispose(skeletonData);
				_spSkeletonJson_setError(self, root, "Target slot not found: ", boneMap->name);
				return 0;
			}

			item = Json_getString(constraintMap, "positionMode", "percent");
			if (strcmp(item, "fixed") == 0) data->positionMode = SP_POSITION_MODE_FIXED;
			else if (strcmp(item, "percent") == 0) data->positionMode = SP_POSITION_MODE_PERCENT;

			item = Json_getString(constraintMap, "spacingMode", "length");
			if (strcmp(item, "length") == 0) data->spacingMode = SP_SPACING_MODE_LENGTH;
			else if (strcmp(item, "fixed") == 0) data->spacingMode = SP_SPACING_MODE_FIXED;
			else if (strcmp(item, "percent") == 0) data->spacingMode = SP_SPACING_MODE_PERCENT;

			item = Json_getString(constraintMap, "rotateMode", "tangent");
			if (strcmp(item, "tangent") == 0) data->rotateMode = SP_ROTATE_MODE_TANGENT;
			else if (strcmp(item, "chain") == 0) data->rotateMode = SP_ROTATE_MODE_CHAIN;
			else if (strcmp(item, "chainScale") == 0) data->rotateMode = SP_ROTATE_MODE_CHAIN_SCALE;

			data->offsetRotation = Json_getFloat(constraintMap, "rotation", 0);
			data->position = Json_getFloat(constraintMap, "position", 0);
			if (data->positionMode == SP_POSITION_MODE_FIXED) data->position *= self->scale;
			data->spacing = Json_getFloat(constraintMap, "spacing", 0);
			if (data->spacingMode == SP_SPACING_MODE_LENGTH || data->spacingMode == SP_SPACING_MODE_FIXED) data->spacing *= self->scale;
			data->rotateMix = Json_getFloat(constraintMap, "rotateMix", 1);
			data->translateMix = Json_getFloat(constraintMap, "translateMix", 1);

			skeletonData->pathConstraints[i] = data;
		}
	}

	/* Skins. */
	skins = Json_getItem(root, "skins");
	if (skins) {
		Json *skinMap;
		skeletonData->skins = MALLOC(spSkin*, skins->size);
		for (skinMap = skins->child, i = 0; skinMap; skinMap = skinMap->next, ++i) {
			Json *attachmentsMap;
			Json *curves;
			spSkin *skin = spSkin_create(skinMap->name);

			skeletonData->skins[skeletonData->skinsCount++] = skin;
			if (strcmp(skinMap->name, "default") == 0) skeletonData->defaultSkin = skin;

			for (attachmentsMap = skinMap->child; attachmentsMap; attachmentsMap = attachmentsMap->next) {
				int slotIndex = spSkeletonData_findSlotIndex(skeletonData, attachmentsMap->name);
				Json *attachmentMap;

				for (attachmentMap = attachmentsMap->child; attachmentMap; attachmentMap = attachmentMap->next) {
					spAttachment* attachment;
					const char* skinAttachmentName = attachmentMap->name;
					const char* attachmentName = Json_getString(attachmentMap, "name", skinAttachmentName);
					const char* path = Json_getString(attachmentMap, "path", attachmentName);
					const char* color;
					Json* entry;

					const char* typeString = Json_getString(attachmentMap, "type", "region");
					spAttachmentType type;
					if (strcmp(typeString, "region") == 0)
						type = SP_ATTACHMENT_REGION;
					else if (strcmp(typeString, "mesh") == 0)
						type = SP_ATTACHMENT_MESH;
					else if (strcmp(typeString, "linkedmesh") == 0)
						type = SP_ATTACHMENT_LINKED_MESH;
					else if (strcmp(typeString, "boundingbox") == 0)
						type = SP_ATTACHMENT_BOUNDING_BOX;
					else if (strcmp(typeString, "path") == 0)
						type = SP_ATTACHMENT_PATH;
					else {
						spSkeletonData_dispose(skeletonData);
						_spSkeletonJson_setError(self, root, "Unknown attachment type: ", typeString);
						return 0;
					}

					attachment = spAttachmentLoader_createAttachment(self->attachmentLoader, skin, type, attachmentName, path);
					if (!attachment) {
						if (self->attachmentLoader->error1) {
							spSkeletonData_dispose(skeletonData);
							_spSkeletonJson_setError(self, root, self->attachmentLoader->error1, self->attachmentLoader->error2);
							return 0;
						}
						continue;
					}

					switch (attachment->type) {
					case SP_ATTACHMENT_REGION: {
						spRegionAttachment* region = SUB_CAST(spRegionAttachment, attachment);
						if (path) MALLOC_STR(region->path, path);
						region->x = Json_getFloat(attachmentMap, "x", 0) * self->scale;
						region->y = Json_getFloat(attachmentMap, "y", 0) * self->scale;
						region->scaleX = Json_getFloat(attachmentMap, "scaleX", 1);
						region->scaleY = Json_getFloat(attachmentMap, "scaleY", 1);
						region->rotation = Json_getFloat(attachmentMap, "rotation", 0);
						region->width = Json_getFloat(attachmentMap, "width", 32) * self->scale;
						region->height = Json_getFloat(attachmentMap, "height", 32) * self->scale;

						color = Json_getString(attachmentMap, "color", 0);
						if (color) {
							region->r = toColor(color, 0);
							region->g = toColor(color, 1);
							region->b = toColor(color, 2);
							region->a = toColor(color, 3);
						}

						spRegionAttachment_updateOffset(region);

						spAttachmentLoader_configureAttachment(self->attachmentLoader, attachment);
						break;
					}
					case SP_ATTACHMENT_MESH:
					case SP_ATTACHMENT_LINKED_MESH: {
						spMeshAttachment* mesh = SUB_CAST(spMeshAttachment, attachment);

						MALLOC_STR(mesh->path, path);

						color = Json_getString(attachmentMap, "color", 0);
						if (color) {
							mesh->r = toColor(color, 0);
							mesh->g = toColor(color, 1);
							mesh->b = toColor(color, 2);
							mesh->a = toColor(color, 3);
						}

						mesh->width = Json_getFloat(attachmentMap, "width", 32) * self->scale;
						mesh->height = Json_getFloat(attachmentMap, "height", 32) * self->scale;

						entry = Json_getItem(attachmentMap, "parent");
						if (!entry) {
							int verticesLength;
							entry = Json_getItem(attachmentMap, "triangles");
							mesh->trianglesCount = entry->size;
							mesh->triangles = MALLOC(unsigned short, entry->size);
							for (entry = entry->child, ii = 0; entry; entry = entry->next, ++ii)
								mesh->triangles[ii] = (unsigned short)entry->valueInt;

							entry = Json_getItem(attachmentMap, "uvs");
							verticesLength = entry->size;
							mesh->regionUVs = MALLOC(float, verticesLength);
							for (entry = entry->child, ii = 0; entry; entry = entry->next, ++ii)
								mesh->regionUVs[ii] = entry->valueFloat;

							_readVertices(self, attachmentMap, SUPER(mesh), verticesLength);

							spMeshAttachment_updateUVs(mesh);

							mesh->hullLength = Json_getInt(attachmentMap, "hull", 0);

							entry = Json_getItem(attachmentMap, "edges");
							if (entry) {
								mesh->edgesCount = entry->size;
								mesh->edges = MALLOC(int, entry->size);
								for (entry = entry->child, ii = 0; entry; entry = entry->next, ++ii)
									mesh->edges[ii] = entry->valueInt;
							}

							spAttachmentLoader_configureAttachment(self->attachmentLoader, attachment);
						} else {
							mesh->inheritDeform = Json_getInt(attachmentMap, "deform", 1);
							_spSkeletonJson_addLinkedMesh(self, SUB_CAST(spMeshAttachment, attachment), Json_getString(attachmentMap, "skin", 0), slotIndex,
									entry->valueString);
						}
						break;
					}
					case SP_ATTACHMENT_BOUNDING_BOX: {
						spBoundingBoxAttachment* box = SUB_CAST(spBoundingBoxAttachment, attachment);
						int vertexCount = Json_getInt(attachmentMap, "vertexCount", 0) << 1;
						_readVertices(self, attachmentMap, SUPER(box), vertexCount);
						box->super.verticesCount = vertexCount;
						spAttachmentLoader_configureAttachment(self->attachmentLoader, attachment);
						break;
					}
					case SP_ATTACHMENT_PATH: {
						spPathAttachment* pathAttachment = SUB_CAST(spPathAttachment, attachment);
						int vertexCount = 0;
						pathAttachment->closed = Json_getInt(attachmentMap, "closed", 0);
						pathAttachment->constantSpeed = Json_getInt(attachmentMap, "constantSpeed", 1);
						vertexCount = Json_getInt(attachmentMap, "vertexCount", 0);
						_readVertices(self, attachmentMap, SUPER(pathAttachment), vertexCount << 1);

						pathAttachment->lengthsLength = vertexCount / 3;
						pathAttachment->lengths = MALLOC(float, pathAttachment->lengthsLength);

						curves = Json_getItem(attachmentMap, "lengths");
						for (curves = curves->child, ii = 0; curves; curves = curves->next, ++ii) {
							pathAttachment->lengths[ii] = curves->valueFloat * self->scale;
						}
						break;
					}
					}

					spSkin_addAttachment(skin, slotIndex, skinAttachmentName, attachment);
				}
			}
		}
	}

	/* Linked meshes. */
	for (i = 0; i < internal->linkedMeshCount; i++) {
		spAttachment* parent;
		_spLinkedMesh* linkedMesh = internal->linkedMeshes + i;
		spSkin* skin = !linkedMesh->skin ? skeletonData->defaultSkin : spSkeletonData_findSkin(skeletonData, linkedMesh->skin);
		if (!skin) {
			spSkeletonData_dispose(skeletonData);
			_spSkeletonJson_setError(self, 0, "Skin not found: ", linkedMesh->skin);
			return 0;
		}
		parent = spSkin_getAttachment(skin, linkedMesh->slotIndex, linkedMesh->parent);
		if (!parent) {
			spSkeletonData_dispose(skeletonData);
			_spSkeletonJson_setError(self, 0, "Parent mesh not found: ", linkedMesh->parent);
			return 0;
		}
		spMeshAttachment_setParentMesh(linkedMesh->mesh, SUB_CAST(spMeshAttachment, parent));
		spMeshAttachment_updateUVs(linkedMesh->mesh);
		spAttachmentLoader_configureAttachment(self->attachmentLoader, SUPER(SUPER(linkedMesh->mesh)));
	}

	/* Events. */
	events = Json_getItem(root, "events");
	if (events) {
		Json *eventMap;
		const char* stringValue;
		skeletonData->eventsCount = events->size;
		skeletonData->events = MALLOC(spEventData*, events->size);
		for (eventMap = events->child, i = 0; eventMap; eventMap = eventMap->next, ++i) {
			spEventData* eventData = spEventData_create(eventMap->name);
			eventData->intValue = Json_getInt(eventMap, "int", 0);
			eventData->floatValue = Json_getFloat(eventMap, "float", 0);
			stringValue = Json_getString(eventMap, "string", 0);
			if (stringValue) MALLOC_STR(eventData->stringValue, stringValue);
			skeletonData->events[i] = eventData;
		}
	}

	/* Animations. */
	animations = Json_getItem(root, "animations");
	if (animations) {
		Json *animationMap;
		skeletonData->animations = MALLOC(spAnimation*, animations->size);
		for (animationMap = animations->child; animationMap; animationMap = animationMap->next) {
			spAnimation* animation = _spSkeletonJson_readAnimation(self, animationMap, skeletonData);
			if (!animation) {
				spSkeletonData_dispose(skeletonData);
				return 0;
			}
			skeletonData->animations[skeletonData->animationsCount++] = animation;
		}
	}

	Json_dispose(root);
	return skeletonData;
}
