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

#include <spine/SkeletonJson.h>

#include <spine/CurveTimeline.h>
#include <spine/VertexAttachment.h>
#include <spine/Json.h>
#include <spine/SkeletonData.h>
#include <spine/Atlas.h>
#include <spine/AtlasAttachmentLoader.h>
#include <spine/LinkedMesh.h>

#include <spine/Skin.h>
#include <spine/ContainerUtil.h>
#include <spine/BoneData.h>
#include <spine/SlotData.h>
#include <spine/IkConstraintData.h>
#include <spine/TransformConstraintData.h>
#include <spine/PathConstraintData.h>
#include <spine/AttachmentType.h>
#include <spine/RegionAttachment.h>
#include <spine/BoundingBoxAttachment.h>
#include <spine/MeshAttachment.h>
#include <spine/PathAttachment.h>
#include <spine/PointAttachment.h>
#include <spine/ClippingAttachment.h>
#include <spine/EventData.h>
#include <spine/AttachmentTimeline.h>
#include <spine/ColorTimeline.h>
#include <spine/TwoColorTimeline.h>
#include <spine/RotateTimeline.h>
#include <spine/TranslateTimeline.h>
#include <spine/ScaleTimeline.h>
#include <spine/ShearTimeline.h>
#include <spine/IkConstraintTimeline.h>
#include <spine/TransformConstraintTimeline.h>
#include <spine/PathConstraintPositionTimeline.h>
#include <spine/PathConstraintSpacingTimeline.h>
#include <spine/PathConstraintMixTimeline.h>
#include <spine/DeformTimeline.h>
#include <spine/DrawOrderTimeline.h>
#include <spine/EventTimeline.h>
#include <spine/Event.h>
#include <spine/Vertices.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define strdup _strdup
#endif

using namespace spine;

SkeletonJson::SkeletonJson(Atlas *atlas) : _attachmentLoader(new(__FILE__, __LINE__) AtlasAttachmentLoader(atlas)),
	_scale(1), _ownsLoader(true)
{}

SkeletonJson::SkeletonJson(AttachmentLoader *attachmentLoader) : _attachmentLoader(attachmentLoader), _scale(1),
	_ownsLoader(false)
{
	assert(_attachmentLoader != NULL);
}

SkeletonJson::~SkeletonJson() {
	ContainerUtil::cleanUpVectorOfPointers(_linkedMeshes);

	if (_ownsLoader) delete _attachmentLoader;
}

SkeletonData *SkeletonJson::readSkeletonDataFile(const String &path) {
	int length;
	SkeletonData *skeletonData;
	const char *json = SpineExtension::readFile(path, &length);
	if (length == 0 || !json) {
		setError(NULL, "Unable to read skeleton file: ", path);
		return NULL;
	}

	skeletonData = readSkeletonData(json);

	SpineExtension::free(json, __FILE__, __LINE__);

	return skeletonData;
}

SkeletonData *SkeletonJson::readSkeletonData(const char *json) {
	int i, ii;
	SkeletonData *skeletonData;
	Json *root, *skeleton, *bones, *boneMap, *ik, *transform, *path, *slots, *skins, *animations, *events;

	_error = "";
	_linkedMeshes.clear();

	root = new(__FILE__, __LINE__) Json(json);

	if (!root) {
		setError(NULL, "Invalid skeleton JSON: ", Json::getError());
		return NULL;
	}

	skeletonData = new(__FILE__, __LINE__) SkeletonData();

	skeleton = Json::getItem(root, "skeleton");
	if (skeleton) {
		skeletonData->_hash = Json::getString(skeleton, "hash", 0);
		skeletonData->_version = Json::getString(skeleton, "spine", 0);
		skeletonData->_x = Json::getFloat(skeleton, "x", 0);
		skeletonData->_y = Json::getFloat(skeleton, "y", 0);
		skeletonData->_width = Json::getFloat(skeleton, "width", 0);
		skeletonData->_height = Json::getFloat(skeleton, "height", 0);
		skeletonData->_fps = Json::getFloat(skeleton, "fps", 30);
		skeletonData->_audioPath = Json::getString(skeleton, "audio", 0);
		skeletonData->_imagesPath = Json::getString(skeleton, "images", 0);
	}

	/* Bones. */
	bones = Json::getItem(root, "bones");
	skeletonData->_bones.setSize(bones->_size, 0);
	int bonesCount = 0;
	for (boneMap = bones->_child, i = 0; boneMap; boneMap = boneMap->_next, ++i) {
		BoneData *data;
		const char *transformMode;

		BoneData *parent = 0;
		const char *parentName = Json::getString(boneMap, "parent", 0);
		if (parentName) {
			parent = skeletonData->findBone(parentName);
			if (!parent) {
				delete skeletonData;
				setError(root, "Parent bone not found: ", parentName);
				return NULL;
			}
		}

		data = new(__FILE__, __LINE__) BoneData(bonesCount, Json::getString(boneMap, "name", 0), parent);

		data->_length = Json::getFloat(boneMap, "length", 0) * _scale;
		data->_x = Json::getFloat(boneMap, "x", 0) * _scale;
		data->_y = Json::getFloat(boneMap, "y", 0) * _scale;
		data->_rotation = Json::getFloat(boneMap, "rotation", 0);
		data->_scaleX = Json::getFloat(boneMap, "scaleX", 1);
		data->_scaleY = Json::getFloat(boneMap, "scaleY", 1);
		data->_shearX = Json::getFloat(boneMap, "shearX", 0);
		data->_shearY = Json::getFloat(boneMap, "shearY", 0);
		transformMode = Json::getString(boneMap, "transform", "normal");
		data->_transformMode = TransformMode_Normal;
		if (strcmp(transformMode, "normal") == 0) data->_transformMode = TransformMode_Normal;
		else if (strcmp(transformMode, "onlyTranslation") == 0) data->_transformMode = TransformMode_OnlyTranslation;
		else if (strcmp(transformMode, "noRotationOrReflection") == 0) data->_transformMode = TransformMode_NoRotationOrReflection;
		else if (strcmp(transformMode, "noScale") == 0) data->_transformMode = TransformMode_NoScale;
		else if (strcmp(transformMode, "noScaleOrReflection") == 0) data->_transformMode = TransformMode_NoScaleOrReflection;
		data->_skinRequired = Json::getBoolean(boneMap, "skin", false);

		skeletonData->_bones[i] = data;
		bonesCount++;
	}

	/* Slots. */
	slots = Json::getItem(root, "slots");
	if (slots) {
		Json *slotMap;
		skeletonData->_slots.ensureCapacity(slots->_size);
		skeletonData->_slots.setSize(slots->_size, 0);
		for (slotMap = slots->_child, i = 0; slotMap; slotMap = slotMap->_next, ++i) {
			SlotData *data;
			const char *color;
			const char *dark;
			Json *item;

			const char *boneName = Json::getString(slotMap, "bone", 0);
			BoneData *boneData = skeletonData->findBone(boneName);
			if (!boneData) {
				delete skeletonData;
				setError(root, "Slot bone not found: ", boneName);
				return NULL;
			}

			data = new(__FILE__, __LINE__) SlotData(i, Json::getString(slotMap, "name", 0), *boneData);

			color = Json::getString(slotMap, "color", 0);
			if (color) {
				Color &c = data->getColor();
				c.r = toColor(color, 0);
				c.g = toColor(color, 1);
				c.b = toColor(color, 2);
				c.a = toColor(color, 3);
			}

			dark = Json::getString(slotMap, "dark", 0);
			if (dark) {
				Color &darkColor = data->getDarkColor();
				darkColor.r = toColor(dark, 0);
				darkColor.g = toColor(dark, 1);
				darkColor.b = toColor(dark, 2);
				darkColor.a = 1;
				data->setHasDarkColor(true);
			}

			item = Json::getItem(slotMap, "attachment");
			if (item) data->setAttachmentName(item->_valueString);

			item = Json::getItem(slotMap, "blend");
			if (item) {
				if (strcmp(item->_valueString, "additive") == 0) data->_blendMode = BlendMode_Additive;
				else if (strcmp(item->_valueString, "multiply") == 0) data->_blendMode = BlendMode_Multiply;
				else if (strcmp(item->_valueString, "screen") == 0) data->_blendMode = BlendMode_Screen;
			}

			skeletonData->_slots[i] = data;
		}
	}

	/* IK constraints. */
	ik = Json::getItem(root, "ik");
	if (ik) {
		Json *constraintMap;
		skeletonData->_ikConstraints.ensureCapacity(ik->_size);
		skeletonData->_ikConstraints.setSize(ik->_size, 0);
		for (constraintMap = ik->_child, i = 0; constraintMap; constraintMap = constraintMap->_next, ++i) {
			const char *targetName;

			IkConstraintData *data = new(__FILE__, __LINE__) IkConstraintData(Json::getString(constraintMap, "name", 0));
			data->setOrder(Json::getInt(constraintMap, "order", 0));
			data->setSkinRequired(Json::getBoolean(constraintMap, "skin", false));

			boneMap = Json::getItem(constraintMap, "bones");
			data->_bones.ensureCapacity(boneMap->_size);
			data->_bones.setSize(boneMap->_size, 0);
			for (boneMap = boneMap->_child, ii = 0; boneMap; boneMap = boneMap->_next, ++ii) {
				data->_bones[ii] = skeletonData->findBone(boneMap->_valueString);
				if (!data->_bones[ii]) {
					delete skeletonData;
					setError(root, "IK bone not found: ", boneMap->_valueString);
					return NULL;
				}
			}

			targetName = Json::getString(constraintMap, "target", 0);
			data->_target = skeletonData->findBone(targetName);
			if (!data->_target) {
				delete skeletonData;
				setError(root, "Target bone not found: ", targetName);
				return NULL;
			}

			data->_mix = Json::getFloat(constraintMap, "mix", 1);
			data->_softness = Json::getFloat(constraintMap, "softness", 0) * _scale;
			data->_bendDirection = Json::getInt(constraintMap, "bendPositive", 1) ? 1 : -1;
			data->_compress = Json::getInt(constraintMap, "compress", 0) ? true: false;
			data->_stretch = Json::getInt(constraintMap, "stretch", 0) ? true: false;
			data->_uniform = Json::getInt(constraintMap, "uniform", 0) ? true: false;

			skeletonData->_ikConstraints[i] = data;
		}
	}

	/* Transform constraints. */
	transform = Json::getItem(root, "transform");
	if (transform) {
		Json *constraintMap;
		skeletonData->_transformConstraints.ensureCapacity(transform->_size);
		skeletonData->_transformConstraints.setSize(transform->_size, 0);
		for (constraintMap = transform->_child, i = 0; constraintMap; constraintMap = constraintMap->_next, ++i) {
			const char *name;

			TransformConstraintData *data = new(__FILE__, __LINE__) TransformConstraintData(Json::getString(constraintMap, "name", 0));
			data->setOrder(Json::getInt(constraintMap, "order", 0));
			data->setSkinRequired(Json::getBoolean(constraintMap, "skin", false));

			boneMap = Json::getItem(constraintMap, "bones");
			data->_bones.ensureCapacity(boneMap->_size);
			data->_bones.setSize(boneMap->_size, 0);
			for (boneMap = boneMap->_child, ii = 0; boneMap; boneMap = boneMap->_next, ++ii) {
				data->_bones[ii] = skeletonData->findBone(boneMap->_valueString);
				if (!data->_bones[ii]) {
					delete skeletonData;
					setError(root, "Transform bone not found: ", boneMap->_valueString);
					return NULL;
				}
			}

			name = Json::getString(constraintMap, "target", 0);
			data->_target = skeletonData->findBone(name);
			if (!data->_target) {
				delete skeletonData;
				setError(root, "Target bone not found: ", name);
				return NULL;
			}

			data->_local = Json::getInt(constraintMap, "local", 0) ? true : false;
			data->_relative = Json::getInt(constraintMap, "relative", 0) ? true : false;
			data->_offsetRotation = Json::getFloat(constraintMap, "rotation", 0);
			data->_offsetX = Json::getFloat(constraintMap, "x", 0) * _scale;
			data->_offsetY = Json::getFloat(constraintMap, "y", 0) * _scale;
			data->_offsetScaleX = Json::getFloat(constraintMap, "scaleX", 0);
			data->_offsetScaleY = Json::getFloat(constraintMap, "scaleY", 0);
			data->_offsetShearY = Json::getFloat(constraintMap, "shearY", 0);

			data->_rotateMix = Json::getFloat(constraintMap, "rotateMix", 1);
			data->_translateMix = Json::getFloat(constraintMap, "translateMix", 1);
			data->_scaleMix = Json::getFloat(constraintMap, "scaleMix", 1);
			data->_shearMix = Json::getFloat(constraintMap, "shearMix", 1);

			skeletonData->_transformConstraints[i] = data;
		}
	}

	/* Path constraints */
	path = Json::getItem(root, "path");
	if (path) {
		Json *constraintMap;
		skeletonData->_pathConstraints.ensureCapacity(path->_size);
		skeletonData->_pathConstraints.setSize(path->_size, 0);
		for (constraintMap = path->_child, i = 0; constraintMap; constraintMap = constraintMap->_next, ++i) {
			const char *name;
			const char *item;

			PathConstraintData *data = new(__FILE__, __LINE__) PathConstraintData(Json::getString(constraintMap, "name", 0));
			data->setOrder(Json::getInt(constraintMap, "order", 0));
			data->setSkinRequired(Json::getBoolean(constraintMap, "skin", false));

			boneMap = Json::getItem(constraintMap, "bones");
			data->_bones.ensureCapacity(boneMap->_size);
			data->_bones.setSize(boneMap->_size, 0);
			for (boneMap = boneMap->_child, ii = 0; boneMap; boneMap = boneMap->_next, ++ii) {
				data->_bones[ii] = skeletonData->findBone(boneMap->_valueString);
				if (!data->_bones[ii]) {
					delete skeletonData;
					setError(root, "Path bone not found: ", boneMap->_valueString);
					return NULL;
				}
			}

			name = Json::getString(constraintMap, "target", 0);
			data->_target = skeletonData->findSlot(name);
			if (!data->_target) {
				delete skeletonData;
				setError(root, "Target slot not found: ", name);
				return NULL;
			}

			item = Json::getString(constraintMap, "positionMode", "percent");
			if (strcmp(item, "fixed") == 0) {
				data->_positionMode = PositionMode_Fixed;
			} else if (strcmp(item, "percent") == 0) {
				data->_positionMode = PositionMode_Percent;
			}

			item = Json::getString(constraintMap, "spacingMode", "length");
			if (strcmp(item, "length") == 0) data->_spacingMode = SpacingMode_Length;
			else if (strcmp(item, "fixed") == 0) data->_spacingMode = SpacingMode_Fixed;
			else if (strcmp(item, "percent") == 0) data->_spacingMode = SpacingMode_Percent;

			item = Json::getString(constraintMap, "rotateMode", "tangent");
			if (strcmp(item, "tangent") == 0) data->_rotateMode = RotateMode_Tangent;
			else if (strcmp(item, "chain") == 0) data->_rotateMode = RotateMode_Chain;
			else if (strcmp(item, "chainScale") == 0) data->_rotateMode = RotateMode_ChainScale;

			data->_offsetRotation = Json::getFloat(constraintMap, "rotation", 0);
			data->_position = Json::getFloat(constraintMap, "position", 0);
			if (data->_positionMode == PositionMode_Fixed) data->_position *= _scale;
			data->_spacing = Json::getFloat(constraintMap, "spacing", 0);
			if (data->_spacingMode == SpacingMode_Length || data->_spacingMode == SpacingMode_Fixed) data->_spacing *= _scale;
			data->_rotateMix = Json::getFloat(constraintMap, "rotateMix", 1);
			data->_translateMix = Json::getFloat(constraintMap, "translateMix", 1);

			skeletonData->_pathConstraints[i] = data;
		}
	}

	/* Skins. */
	skins = Json::getItem(root, "skins");
	if (skins) {
		Json *skinMap;
		skeletonData->_skins.ensureCapacity(skins->_size);
		skeletonData->_skins.setSize(skins->_size, 0);
		int skinsIndex = 0;
		for (skinMap = skins->_child, i = 0; skinMap; skinMap = skinMap->_next, ++i) {
			Json *attachmentsMap;
			Json *curves;

			Skin *skin = new(__FILE__, __LINE__) Skin(Json::getString(skinMap, "name", ""));

			Json *item = Json::getItem(skinMap, "bones");
			if (item) {
				for (item = item->_child; item; item = item->_next) {
					BoneData* data = skeletonData->findBone(item->_valueString);
					if (!data) {
						delete skeletonData;
						setError(root, String("Skin bone not found: "), item->_valueString);
						return NULL;
					}
					skin->getBones().add(data);
				}
			}

			item = Json::getItem(skinMap, "ik");
			if (item) {
				for (item = item->_child; item; item = item->_next) {
					IkConstraintData* data = skeletonData->findIkConstraint(item->_valueString);
					if (!data) {
						delete skeletonData;
						setError(root, String("Skin IK constraint not found: "), item->_valueString);
						return NULL;
					}
					skin->getConstraints().add(data);
				}
			}

			item = Json::getItem(skinMap, "transform");
			if (item) {
				for (item = item->_child; item; item = item->_next) {
					TransformConstraintData* data = skeletonData->findTransformConstraint(item->_valueString);
					if (!data) {
						delete skeletonData;
						setError(root, String("Skin transform constraint not found: "), item->_valueString);
						return NULL;
					}
					skin->getConstraints().add(data);
				}
			}

			item = Json::getItem(skinMap, "path");
			if (item) {
				for (item = item->_child; item; item = item->_next) {
					PathConstraintData* data = skeletonData->findPathConstraint(item->_valueString);
					if (!data) {
						delete skeletonData;
						setError(root, String("Skin path constraint not found: "), item->_valueString);
						return NULL;
					}
					skin->getConstraints().add(data);
				}
			}

			skeletonData->_skins[skinsIndex++] = skin;
			if (strcmp(Json::getString(skinMap, "name", ""), "default") == 0) {
				skeletonData->_defaultSkin = skin;
			}

			for (attachmentsMap = Json::getItem(skinMap, "attachments")->_child; attachmentsMap; attachmentsMap = attachmentsMap->_next) {
				SlotData* slot = skeletonData->findSlot(attachmentsMap->_name);
				Json *attachmentMap;

				for (attachmentMap = attachmentsMap->_child; attachmentMap; attachmentMap = attachmentMap->_next) {
					Attachment *attachment = NULL;
					const char *skinAttachmentName = attachmentMap->_name;
					const char *attachmentName = Json::getString(attachmentMap, "name", skinAttachmentName);
					const char *attachmentPath = Json::getString(attachmentMap, "path", attachmentName);
					const char *color;
					Json *entry;

					const char *typeString = Json::getString(attachmentMap, "type", "region");
					AttachmentType type;
					if (strcmp(typeString, "region") == 0) type = AttachmentType_Region;
					else if (strcmp(typeString, "mesh") == 0) type = AttachmentType_Mesh;
					else if (strcmp(typeString, "linkedmesh") == 0) type = AttachmentType_Linkedmesh;
					else if (strcmp(typeString, "boundingbox") == 0) type = AttachmentType_Boundingbox;
					else if (strcmp(typeString, "path") == 0) type = AttachmentType_Path;
					else if (strcmp(typeString, "clipping") == 0) type = AttachmentType_Clipping;
					else if (strcmp(typeString, "point") == 0) type = AttachmentType_Point;
					else {
						delete skeletonData;
						setError(root, "Unknown attachment type: ", typeString);
						return NULL;
					}

					switch (type) {
						case AttachmentType_Region: {
							attachment = _attachmentLoader->newRegionAttachment(*skin, attachmentName, attachmentPath);
							if (!attachment) {
								delete skeletonData;
								setError(root, "Error reading attachment: ", skinAttachmentName);
								return NULL;
							}

							RegionAttachment *region = static_cast<RegionAttachment *>(attachment);
							region->_path = attachmentPath;

							region->_x = Json::getFloat(attachmentMap, "x", 0) * _scale;
							region->_y = Json::getFloat(attachmentMap, "y", 0) * _scale;
							region->_scaleX = Json::getFloat(attachmentMap, "scaleX", 1);
							region->_scaleY = Json::getFloat(attachmentMap, "scaleY", 1);
							region->_rotation = Json::getFloat(attachmentMap, "rotation", 0);
							region->_width = Json::getFloat(attachmentMap, "width", 32) * _scale;
							region->_height = Json::getFloat(attachmentMap, "height", 32) * _scale;

							color = Json::getString(attachmentMap, "color", 0);
							if (color) {
								region->getColor().r = toColor(color, 0);
								region->getColor().g = toColor(color, 1);
								region->getColor().b = toColor(color, 2);
								region->getColor().a = toColor(color, 3);
							}

							region->updateOffset();
							_attachmentLoader->configureAttachment(region);
							break;
						}
						case AttachmentType_Mesh:
						case AttachmentType_Linkedmesh: {
							attachment = _attachmentLoader->newMeshAttachment(*skin, attachmentName, attachmentPath);

							if (!attachment) {
								delete skeletonData;
								setError(root, "Error reading attachment: ", skinAttachmentName);
								return NULL;
							}

							MeshAttachment *mesh = static_cast<MeshAttachment *>(attachment);
							mesh->_path = attachmentPath;

							color = Json::getString(attachmentMap, "color", 0);
							if (color) {
								mesh->getColor().r = toColor(color, 0);
								mesh->getColor().g = toColor(color, 1);
								mesh->getColor().b = toColor(color, 2);
								mesh->getColor().a = toColor(color, 3);
							}

							mesh->_width = Json::getFloat(attachmentMap, "width", 32) * _scale;
							mesh->_height = Json::getFloat(attachmentMap, "height", 32) * _scale;

							entry = Json::getItem(attachmentMap, "parent");
							if (!entry) {
								int verticesLength;
								entry = Json::getItem(attachmentMap, "triangles");
								mesh->_triangles.ensureCapacity(entry->_size);
								mesh->_triangles.setSize(entry->_size, 0);
								for (entry = entry->_child, ii = 0; entry; entry = entry->_next, ++ii)
									mesh->_triangles[ii] = (unsigned short) entry->_valueInt;

								entry = Json::getItem(attachmentMap, "uvs");
								verticesLength = entry->_size;
								mesh->_regionUVs.ensureCapacity(verticesLength);
								mesh->_regionUVs.setSize(verticesLength, 0);
								for (entry = entry->_child, ii = 0; entry; entry = entry->_next, ++ii)
									mesh->_regionUVs[ii] = entry->_valueFloat;

								readVertices(attachmentMap, mesh, verticesLength);

								mesh->updateUVs();

								mesh->_hullLength = Json::getInt(attachmentMap, "hull", 0);

								entry = Json::getItem(attachmentMap, "edges");
								if (entry) {
									mesh->_edges.ensureCapacity(entry->_size);
									mesh->_edges.setSize(entry->_size, 0);
									for (entry = entry->_child, ii = 0; entry; entry = entry->_next, ++ii)
										mesh->_edges[ii] = entry->_valueInt;
								}
								_attachmentLoader->configureAttachment(mesh);
							} else {
								bool inheritDeform = Json::getInt(attachmentMap, "deform", 1) ? true : false;
								LinkedMesh *linkedMesh = new(__FILE__, __LINE__) LinkedMesh(mesh,
									String(Json::getString(attachmentMap, "skin", 0)), slot->getIndex(), String(entry->_valueString),
									inheritDeform);
								_linkedMeshes.add(linkedMesh);
							}
							break;
						}
						case AttachmentType_Boundingbox: {
							attachment = _attachmentLoader->newBoundingBoxAttachment(*skin, attachmentName);

							BoundingBoxAttachment *box = static_cast<BoundingBoxAttachment *>(attachment);

							int vertexCount = Json::getInt(attachmentMap, "vertexCount", 0) << 1;
							readVertices(attachmentMap, box, vertexCount);
							_attachmentLoader->configureAttachment(attachment);
							break;
						}
						case AttachmentType_Path: {
							attachment = _attachmentLoader->newPathAttachment(*skin, attachmentName);

							PathAttachment *pathAttatchment = static_cast<PathAttachment *>(attachment);

							int vertexCount = 0;
							pathAttatchment->_closed = Json::getInt(attachmentMap, "closed", 0) ? true : false;
							pathAttatchment->_constantSpeed = Json::getInt(attachmentMap, "constantSpeed", 1) ? true : false;
							vertexCount = Json::getInt(attachmentMap, "vertexCount", 0);
							readVertices(attachmentMap, pathAttatchment, vertexCount << 1);

							pathAttatchment->_lengths.ensureCapacity(vertexCount / 3);
							pathAttatchment->_lengths.setSize(vertexCount / 3, 0);

							curves = Json::getItem(attachmentMap, "lengths");
							for (curves = curves->_child, ii = 0; curves; curves = curves->_next, ++ii)
								pathAttatchment->_lengths[ii] = curves->_valueFloat * _scale;
							_attachmentLoader->configureAttachment(attachment);
							break;
						}
						case AttachmentType_Point: {
							attachment = _attachmentLoader->newPointAttachment(*skin, attachmentName);

							PointAttachment *point = static_cast<PointAttachment *>(attachment);

							point->_x = Json::getFloat(attachmentMap, "x", 0) * _scale;
							point->_y = Json::getFloat(attachmentMap, "y", 0) * _scale;
							point->_rotation = Json::getFloat(attachmentMap, "rotation", 0);
							_attachmentLoader->configureAttachment(attachment);
							break;
						}
						case AttachmentType_Clipping: {
							attachment = _attachmentLoader->newClippingAttachment(*skin, attachmentName);

							ClippingAttachment *clip = static_cast<ClippingAttachment *>(attachment);

							int vertexCount = 0;
							const char *end = Json::getString(attachmentMap, "end", 0);
							if (end) clip->_endSlot = skeletonData->findSlot(end);
							vertexCount = Json::getInt(attachmentMap, "vertexCount", 0) << 1;
							readVertices(attachmentMap, clip, vertexCount);
							_attachmentLoader->configureAttachment(attachment);
							break;
						}
					}

					skin->setAttachment(slot->getIndex(), skinAttachmentName, attachment);
				}
			}
		}
	}

	/* Linked meshes. */
	int n = _linkedMeshes.size();
	for (i = 0; i < n; ++i) {
		LinkedMesh *linkedMesh = _linkedMeshes[i];
		Skin *skin = linkedMesh->_skin.length() == 0 ? skeletonData->getDefaultSkin() : skeletonData->findSkin(linkedMesh->_skin);
		if (skin == NULL) {
			delete skeletonData;
			setError(root, "Skin not found: ", linkedMesh->_skin.buffer());
			return NULL;
		}
		Attachment *parent = skin->getAttachment(linkedMesh->_slotIndex, linkedMesh->_parent);
		if (parent == NULL) {
			delete skeletonData;
			setError(root, "Parent mesh not found: ", linkedMesh->_parent.buffer());
			return NULL;
		}
		linkedMesh->_mesh->_deformAttachment = linkedMesh->_inheritDeform ? static_cast<VertexAttachment*>(parent) : linkedMesh->_mesh;
		linkedMesh->_mesh->setParentMesh(static_cast<MeshAttachment *>(parent));
		linkedMesh->_mesh->updateUVs();
		_attachmentLoader->configureAttachment(linkedMesh->_mesh);
	}
	ContainerUtil::cleanUpVectorOfPointers(_linkedMeshes);
	_linkedMeshes.clear();

	/* Events. */
	events = Json::getItem(root, "events");
	if (events) {
		Json *eventMap;
		skeletonData->_events.ensureCapacity(events->_size);
		skeletonData->_events.setSize(events->_size, 0);
		for (eventMap = events->_child, i = 0; eventMap; eventMap = eventMap->_next, ++i) {
			EventData *eventData = new(__FILE__, __LINE__) EventData(String(eventMap->_name));

			eventData->_intValue = Json::getInt(eventMap, "int", 0);
			eventData->_floatValue = Json::getFloat(eventMap, "float", 0);
			const char *stringValue = Json::getString(eventMap, "string", 0);
			eventData->_stringValue = stringValue;
			const char *audioPath = Json::getString(eventMap, "audio", 0);
			eventData->_audioPath = audioPath;
			if (audioPath) {
				eventData->_volume = Json::getFloat(eventMap, "volume", 1);
				eventData->_balance = Json::getFloat(eventMap, "balance", 0);
			}
			skeletonData->_events[i] = eventData;
		}
	}

	/* Animations. */
	animations = Json::getItem(root, "animations");
	if (animations) {
		Json *animationMap;
		skeletonData->_animations.ensureCapacity(animations->_size);
		skeletonData->_animations.setSize(animations->_size, 0);
		int animationsIndex = 0;
		for (animationMap = animations->_child; animationMap; animationMap = animationMap->_next) {
			Animation *animation = readAnimation(animationMap, skeletonData);
			if (!animation) {
				delete skeletonData;
				delete root;
				return NULL;
			}
			skeletonData->_animations[animationsIndex++] = animation;
		}
	}

	delete root;

	return skeletonData;
}

float SkeletonJson::toColor(const char *value, size_t index) {
	char digits[3];
	char *error;
	int color;

	if (index >= strlen(value) / 2) return -1;

	value += index * 2;

	digits[0] = *value;
	digits[1] = *(value + 1);
	digits[2] = '\0';
	color = (int) strtoul(digits, &error, 16);
	if (*error != 0) return -1;

	return color / (float) 255;
}

void SkeletonJson::readCurve(Json *frame, CurveTimeline *timeline, size_t frameIndex) {
	Json *curve = Json::getItem(frame, "curve");
	if (!curve) return;
	if (curve->_type == Json::JSON_STRING && strcmp(curve->_valueString, "stepped") == 0)
		timeline->setStepped(frameIndex);
	else {
		float c1 = Json::getFloat(frame, "curve", 0);
		float c2 = Json::getFloat(frame, "c2", 0);
		float c3 = Json::getFloat(frame, "c3", 1);
		float c4 = Json::getFloat(frame, "c4", 1);
		timeline->setCurve(frameIndex, c1, c2, c3, c4);
	}
}

Animation *SkeletonJson::readAnimation(Json *root, SkeletonData *skeletonData) {
	Vector<Timeline *> timelines;
	float duration = 0;

	size_t frameIndex;
	Json *valueMap;
	int timelinesCount = 0;

	Json *bones = Json::getItem(root, "bones");
	Json *slots = Json::getItem(root, "slots");
	Json *ik = Json::getItem(root, "ik");
	Json *transform = Json::getItem(root, "transform");
	Json *paths = Json::getItem(root, "path");
	Json *deform = Json::getItem(root, "deform");
	Json *drawOrder = Json::getItem(root, "drawOrder");
	Json *events = Json::getItem(root, "events");
	Json *boneMap, *slotMap, *constraintMap;
	if (!drawOrder) drawOrder = Json::getItem(root, "draworder");

	for (boneMap = bones ? bones->_child : NULL; boneMap; boneMap = boneMap->_next)
		timelinesCount += boneMap->_size;

	for (slotMap = slots ? slots->_child : NULL; slotMap; slotMap = slotMap->_next)
		timelinesCount += slotMap->_size;

	timelinesCount += ik ? ik->_size : 0;
	timelinesCount += transform ? transform->_size : 0;

	for (constraintMap = paths ? paths->_child : NULL; constraintMap; constraintMap = constraintMap->_next)
		timelinesCount += constraintMap->_size;

	for (constraintMap = deform ? deform->_child : NULL; constraintMap; constraintMap = constraintMap->_next)
		for (slotMap = constraintMap->_child; slotMap; slotMap = slotMap->_next)
			timelinesCount += slotMap->_size;

	if (drawOrder) ++timelinesCount;

	if (events) ++timelinesCount;

	/** Slot timelines. */
	for (slotMap = slots ? slots->_child : 0; slotMap; slotMap = slotMap->_next) {
		Json *timelineMap;

		int slotIndex = skeletonData->findSlotIndex(slotMap->_name);
		if (slotIndex == -1) {
			ContainerUtil::cleanUpVectorOfPointers(timelines);
			setError(NULL, "Slot not found: ", slotMap->_name);
			return NULL;
		}

		for (timelineMap = slotMap->_child; timelineMap; timelineMap = timelineMap->_next) {
			if (strcmp(timelineMap->_name, "attachment") == 0) {
				AttachmentTimeline *timeline = new(__FILE__, __LINE__) AttachmentTimeline(timelineMap->_size);

				timeline->_slotIndex = slotIndex;

				for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
					Json *name = Json::getItem(valueMap, "name");
					String attachmentName = name->_type == Json::JSON_NULL ? "" : name->_valueString;
					timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0), attachmentName);
				}
				timelines.add(timeline);
				timelinesCount++;
				duration = MathUtil::max(duration, timeline->_frames[timelineMap->_size - 1]);

			} else if (strcmp(timelineMap->_name, "color") == 0) {
				ColorTimeline *timeline = new(__FILE__, __LINE__) ColorTimeline(timelineMap->_size);

				timeline->_slotIndex = slotIndex;

				for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
					const char *s = Json::getString(valueMap, "color", 0);
					timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0), toColor(s, 0), toColor(s, 1),
						toColor(s, 2), toColor(s, 3));
					readCurve(valueMap, timeline, frameIndex);
				}
				timelines.add(timeline);
				timelinesCount++;
				duration = MathUtil::max(duration, timeline->_frames[(timelineMap->_size - 1) * ColorTimeline::ENTRIES]);

			} else if (strcmp(timelineMap->_name, "twoColor") == 0) {
				TwoColorTimeline *timeline = new(__FILE__, __LINE__) TwoColorTimeline(timelineMap->_size);

				timeline->_slotIndex = slotIndex;

				for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
					const char *s = Json::getString(valueMap, "light", 0);
					const char *ds = Json::getString(valueMap, "dark", 0);
					timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0), toColor(s, 0), toColor(s, 1),
						toColor(s, 2), toColor(s, 3), toColor(ds, 0), toColor(ds, 1), toColor(ds, 2));
					readCurve(valueMap, timeline, frameIndex);
				}
				timelines.add(timeline);
				timelinesCount++;
				duration = MathUtil::max(duration,
										 timeline->_frames[(timelineMap->_size - 1) * TwoColorTimeline::ENTRIES]);
			} else {
				ContainerUtil::cleanUpVectorOfPointers(timelines);
				setError(NULL, "Invalid timeline type for a slot: ", timelineMap->_name);
				return NULL;
			}
		}
	}

	/** Bone timelines. */
	for (boneMap = bones ? bones->_child : 0; boneMap; boneMap = boneMap->_next) {
		Json *timelineMap;

		int boneIndex = skeletonData->findBoneIndex(boneMap->_name);
		if (boneIndex == -1) {
			ContainerUtil::cleanUpVectorOfPointers(timelines);
			setError(NULL, "Bone not found: ", boneMap->_name);
			return NULL;
		}

		for (timelineMap = boneMap->_child; timelineMap; timelineMap = timelineMap->_next) {
			if (strcmp(timelineMap->_name, "rotate") == 0) {
				RotateTimeline *timeline = new(__FILE__, __LINE__) RotateTimeline(timelineMap->_size);

				timeline->_boneIndex = boneIndex;

				for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
					timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0), Json::getFloat(valueMap, "angle", 0));
					readCurve(valueMap, timeline, frameIndex);
				}
				timelines.add(timeline);
				timelinesCount++;
				duration = MathUtil::max(duration, timeline->_frames[(timelineMap->_size - 1) * RotateTimeline::ENTRIES]);
			} else {
				int isScale = strcmp(timelineMap->_name, "scale") == 0;
				int isTranslate = strcmp(timelineMap->_name, "translate") == 0;
				int isShear = strcmp(timelineMap->_name, "shear") == 0;
				if (isScale || isTranslate || isShear) {
					float timelineScale = isTranslate ? _scale : 1;
					float defaultValue = 0;
					TranslateTimeline *timeline = 0;
					if (isScale) {
						timeline = new(__FILE__, __LINE__) ScaleTimeline(timelineMap->_size);
						defaultValue = 1;
					} else if (isTranslate) {
						timeline = new(__FILE__, __LINE__) TranslateTimeline(timelineMap->_size);
					} else if (isShear) {
						timeline = new(__FILE__, __LINE__) ShearTimeline(timelineMap->_size);
					}
					timeline->_boneIndex = boneIndex;

					for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
						timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0),
							Json::getFloat(valueMap, "x", defaultValue) * timelineScale,
							Json::getFloat(valueMap, "y", defaultValue) * timelineScale);
						readCurve(valueMap, timeline, frameIndex);
					}

					timelines.add(timeline);
					timelinesCount++;
					duration = MathUtil::max(duration, timeline->_frames[(timelineMap->_size - 1) * TranslateTimeline::ENTRIES]);
				} else {
					ContainerUtil::cleanUpVectorOfPointers(timelines);
					setError(NULL, "Invalid timeline type for a bone: ", timelineMap->_name);
					return NULL;
				}
			}
		}
	}

	/** IK constraint timelines. */
	for (constraintMap = ik ? ik->_child : 0; constraintMap; constraintMap = constraintMap->_next) {
		IkConstraintData *constraint = skeletonData->findIkConstraint(constraintMap->_name);
		IkConstraintTimeline *timeline = new(__FILE__, __LINE__) IkConstraintTimeline(constraintMap->_size);

		for (frameIndex = 0; frameIndex < skeletonData->_ikConstraints.size(); ++frameIndex) {
			if (constraint == skeletonData->_ikConstraints[frameIndex]) {
				timeline->_ikConstraintIndex = frameIndex;
				break;
			}
		}
		for (valueMap = constraintMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
			timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0), Json::getFloat(valueMap, "mix", 1),
				Json::getFloat(valueMap, "softness", 0) * _scale, Json::getInt(valueMap, "bendPositive", 1) ? 1 : -1,
				Json::getInt(valueMap, "compress", 0) ? true : false, Json::getInt(valueMap, "stretch", 0) ? true : false);
			readCurve(valueMap, timeline, frameIndex);
		}
		timelines.add(timeline);
		timelinesCount++;
		duration = MathUtil::max(duration, timeline->_frames[(constraintMap->_size - 1) * IkConstraintTimeline::ENTRIES]);
	}

	/** Transform constraint timelines. */
	for (constraintMap = transform ? transform->_child : 0; constraintMap; constraintMap = constraintMap->_next) {
		TransformConstraintData *constraint = skeletonData->findTransformConstraint(constraintMap->_name);
		TransformConstraintTimeline *timeline = new(__FILE__, __LINE__) TransformConstraintTimeline(constraintMap->_size);

		for (frameIndex = 0; frameIndex < skeletonData->_transformConstraints.size(); ++frameIndex) {
			if (constraint == skeletonData->_transformConstraints[frameIndex]) {
				timeline->_transformConstraintIndex = frameIndex;
				break;
			}
		}
		for (valueMap = constraintMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
			timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0),
				Json::getFloat(valueMap, "rotateMix", 1), Json::getFloat(valueMap, "translateMix", 1),
				Json::getFloat(valueMap, "scaleMix", 1), Json::getFloat(valueMap, "shearMix", 1));
			readCurve(valueMap, timeline, frameIndex);
		}
		timelines.add(timeline);
		timelinesCount++;
		duration = MathUtil::max(duration, timeline->_frames[(constraintMap->_size - 1) * TransformConstraintTimeline::ENTRIES]);
	}

	/** Path constraint timelines. */
	for (constraintMap = paths ? paths->_child : 0; constraintMap; constraintMap = constraintMap->_next) {
		size_t constraintIndex = 0, i;
		Json *timelineMap;

		PathConstraintData *data = skeletonData->findPathConstraint(constraintMap->_name);
		if (!data) {
			ContainerUtil::cleanUpVectorOfPointers(timelines);
			setError(NULL, "Path constraint not found: ", constraintMap->_name);
			return NULL;
		}

		for (i = 0; i < skeletonData->_pathConstraints.size(); i++) {
			if (skeletonData->_pathConstraints[i] == data) {
				constraintIndex = i;
				break;
			}
		}

		for (timelineMap = constraintMap->_child; timelineMap; timelineMap = timelineMap->_next) {
			const char *timelineName = timelineMap->_name;
			if (strcmp(timelineName, "position") == 0 || strcmp(timelineName, "spacing") == 0) {
				PathConstraintPositionTimeline *timeline;
				float timelineScale = 1;
				if (strcmp(timelineName, "spacing") == 0) {
					timeline = new(__FILE__, __LINE__) PathConstraintSpacingTimeline(timelineMap->_size);

					if (data->_spacingMode == SpacingMode_Length || data->_spacingMode == SpacingMode_Fixed) {
						timelineScale = _scale;
					}
				} else {
					timeline = new(__FILE__, __LINE__) PathConstraintPositionTimeline(timelineMap->_size);

					if (data->_positionMode == PositionMode_Fixed) {
						timelineScale = _scale;
					}
				}

				timeline->_pathConstraintIndex = constraintIndex;
				for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
					timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0),
						Json::getFloat(valueMap, timelineName, 0) * timelineScale);
					readCurve(valueMap, timeline, frameIndex);
				}
				timelines.add(timeline);
				timelinesCount++;
				duration = MathUtil::max(duration, timeline->_frames[(timelineMap->_size - 1) *
																	 PathConstraintPositionTimeline::ENTRIES]);
			} else if (strcmp(timelineName, "mix") == 0) {
				PathConstraintMixTimeline *timeline = new(__FILE__, __LINE__) PathConstraintMixTimeline(timelineMap->_size);
				timeline->_pathConstraintIndex = constraintIndex;
				for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
					timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0),
						Json::getFloat(valueMap, "rotateMix", 1),
						Json::getFloat(valueMap, "translateMix", 1));
					readCurve(valueMap, timeline, frameIndex);
				}
				timelines.add(timeline);
				timelinesCount++;
				duration = MathUtil::max(duration, timeline->_frames[(timelineMap->_size - 1) * PathConstraintMixTimeline::ENTRIES]);
			}
		}
	}

	/** Deform timelines. */
	for (constraintMap = deform ? deform->_child : NULL; constraintMap; constraintMap = constraintMap->_next) {
		Skin *skin = skeletonData->findSkin(constraintMap->_name);
		for (slotMap = constraintMap->_child; slotMap; slotMap = slotMap->_next) {
			int slotIndex = skeletonData->findSlotIndex(slotMap->_name);
			Json *timelineMap;
			for (timelineMap = slotMap->_child; timelineMap; timelineMap = timelineMap->_next) {
				DeformTimeline *timeline;
				int weighted, deformLength;

				Attachment *baseAttachment = skin->getAttachment(slotIndex, timelineMap->_name);

				if (!baseAttachment) {
					ContainerUtil::cleanUpVectorOfPointers(timelines);
					setError(NULL, "Attachment not found: ", timelineMap->_name);
					return NULL;
				}

				VertexAttachment *attachment = static_cast<VertexAttachment *>(baseAttachment);

				weighted = attachment->_bones.size() != 0;
				Vector<float> &verts = attachment->_vertices;
				deformLength = weighted ? verts.size() / 3 * 2 : verts.size();

				timeline = new(__FILE__, __LINE__) DeformTimeline(timelineMap->_size);

				timeline->_slotIndex = slotIndex;
				timeline->_attachment = attachment;

				for (valueMap = timelineMap->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
					Json *vertices = Json::getItem(valueMap, "vertices");
					Vector<float> deformed;
					if (!vertices) {
						if (weighted) {
							deformed.setSize(deformLength, 0);
						} else {
							deformed.clearAndAddAll(attachment->_vertices);
						}
					} else {
						int v, start = Json::getInt(valueMap, "offset", 0);
						Json *vertex;
						deformed.setSize(deformLength, 0);
						if (_scale == 1) {
							for (vertex = vertices->_child, v = start; vertex; vertex = vertex->_next, ++v) {
								deformed[v] = vertex->_valueFloat;
							}
						} else {
							for (vertex = vertices->_child, v = start; vertex; vertex = vertex->_next, ++v) {
								deformed[v] = vertex->_valueFloat * _scale;
							}
						}
						if (!weighted) {
							Vector<float> &verticesAttachment = attachment->_vertices;
							for (v = 0; v < deformLength; ++v) {
								deformed[v] += verticesAttachment[v];
							}
						}
					}
					timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0), deformed);
					readCurve(valueMap, timeline, frameIndex);
				}

				timelines.add(timeline);
				timelinesCount++;
				duration = MathUtil::max(duration, timeline->_frames[timelineMap->_size - 1]);
			}
		}
	}

	/** Draw order timeline. */
	if (drawOrder) {
		DrawOrderTimeline *timeline = new(__FILE__, __LINE__) DrawOrderTimeline(drawOrder->_size);

		for (valueMap = drawOrder->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
			int ii;
			Vector<int> drawOrder2;
			Json *offsets = Json::getItem(valueMap, "offsets");
			if (offsets) {
				Json *offsetMap;
				Vector<int> unchanged;
				unchanged.ensureCapacity(skeletonData->_slots.size() - offsets->_size);
				unchanged.setSize(skeletonData->_slots.size() - offsets->_size, 0);
				size_t originalIndex = 0, unchangedIndex = 0;

				drawOrder2.ensureCapacity(skeletonData->_slots.size());
				drawOrder2.setSize(skeletonData->_slots.size(), 0);
				for (ii = (int)skeletonData->_slots.size() - 1; ii >= 0; --ii)
					drawOrder2[ii] = -1;

				for (offsetMap = offsets->_child; offsetMap; offsetMap = offsetMap->_next) {
					int slotIndex = skeletonData->findSlotIndex(Json::getString(offsetMap, "slot", 0));
					if (slotIndex == -1) {
						ContainerUtil::cleanUpVectorOfPointers(timelines);
						setError(NULL, "Slot not found: ", Json::getString(offsetMap, "slot", 0));
						return NULL;
					}
					/* Collect unchanged items. */
					while (originalIndex != (size_t)slotIndex)
						unchanged[unchangedIndex++] = originalIndex++;
					/* Set changed items. */
					drawOrder2[originalIndex + Json::getInt(offsetMap, "offset", 0)] = originalIndex;
					originalIndex++;
				}
				/* Collect remaining unchanged items. */
				while (originalIndex < skeletonData->_slots.size())
					unchanged[unchangedIndex++] = originalIndex++;
				/* Fill in unchanged items. */
				for (ii = (int)skeletonData->_slots.size() - 1; ii >= 0; ii--)
					if (drawOrder2[ii] == -1) drawOrder2[ii] = unchanged[--unchangedIndex];
			}
			timeline->setFrame(frameIndex, Json::getFloat(valueMap, "time", 0), drawOrder2);
		}
		timelines.add(timeline);
		timelinesCount++;
		duration = MathUtil::max(duration, timeline->_frames[drawOrder->_size - 1]);
	}

	/** Event timeline. */
	if (events) {
		EventTimeline *timeline = new(__FILE__, __LINE__) EventTimeline(events->_size);

		for (valueMap = events->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
			Event *event;
			EventData *eventData = skeletonData->findEvent(Json::getString(valueMap, "name", 0));
			if (!eventData) {
				ContainerUtil::cleanUpVectorOfPointers(timelines);
				setError(NULL, "Event not found: ", Json::getString(valueMap, "name", 0));
				return NULL;
			}

			event = new(__FILE__, __LINE__) Event(Json::getFloat(valueMap, "time", 0), *eventData);
			event->_intValue = Json::getInt(valueMap, "int", eventData->_intValue);
			event->_floatValue = Json::getFloat(valueMap, "float", eventData->_floatValue);
			event->_stringValue = Json::getString(valueMap, "string", eventData->_stringValue.buffer());
			if (!eventData->_audioPath.isEmpty()) {
				event->_volume = Json::getFloat(valueMap, "volume", 1);
				event->_balance = Json::getFloat(valueMap, "balance", 0);
			}
			timeline->setFrame(frameIndex, event);
		}
		timelines.add(timeline);
		timelinesCount++;
		duration = MathUtil::max(duration, timeline->_frames[events->_size - 1]);
	}

	return new(__FILE__, __LINE__) Animation(String(root->_name), timelines, duration);
}

void SkeletonJson::readVertices(Json *attachmentMap, VertexAttachment *attachment, size_t verticesLength) {
	Json *entry;
	size_t i, n, nn, entrySize;
	Vector<float> vertices;

	attachment->setWorldVerticesLength(verticesLength);

	entry = Json::getItem(attachmentMap, "vertices");
	entrySize = entry->_size;
	vertices.ensureCapacity(entrySize);
	vertices.setSize(entrySize, 0);
	for (entry = entry->_child, i = 0; entry; entry = entry->_next, ++i)
		vertices[i] = entry->_valueFloat;

	if (verticesLength == entrySize) {
		if (_scale != 1) {
			for (i = 0; i < entrySize; ++i)
				vertices[i] *= _scale;
		}

		attachment->getVertices().clearAndAddAll(vertices);
		return;
	}

	Vertices bonesAndWeights;
	bonesAndWeights._bones.ensureCapacity(verticesLength * 3);
	bonesAndWeights._vertices.ensureCapacity(verticesLength * 3 * 3);

	for (i = 0, n = entrySize; i < n;) {
		int boneCount = (int) vertices[i++];
		bonesAndWeights._bones.add(boneCount);
		for (nn = i + boneCount * 4; i < nn; i += 4) {
			bonesAndWeights._bones.add((int) vertices[i]);
			bonesAndWeights._vertices.add(vertices[i + 1] * _scale);
			bonesAndWeights._vertices.add(vertices[i + 2] * _scale);
			bonesAndWeights._vertices.add(vertices[i + 3]);
		}
	}

	attachment->getVertices().clearAndAddAll(bonesAndWeights._vertices);
	attachment->getBones().clearAndAddAll(bonesAndWeights._bones);
}

void SkeletonJson::setError(Json *root, const String &value1, const String &value2) {
	_error = String(value1).append(value2);
	delete root;
}
