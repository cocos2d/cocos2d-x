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

#ifndef SPINE_SPINE_H_
#define SPINE_SPINE_H_

#include <spine/Animation.h>
#include <spine/AnimationState.h>
#include <spine/AnimationStateData.h>
#include <spine/Atlas.h>
#include <spine/AtlasAttachmentLoader.h>
#include <spine/Attachment.h>
#include <spine/AttachmentLoader.h>
#include <spine/AttachmentTimeline.h>
#include <spine/AttachmentType.h>
#include <spine/BlendMode.h>
#include <spine/Bone.h>
#include <spine/BoneData.h>
#include <spine/BoundingBoxAttachment.h>
#include <spine/ClippingAttachment.h>
#include <spine/Color.h>
#include <spine/ColorTimeline.h>
#include <spine/ConstraintData.h>
#include <spine/ContainerUtil.h>
#include <spine/CurveTimeline.h>
#include <spine/DeformTimeline.h>
#include <spine/DrawOrderTimeline.h>
#include <spine/Event.h>
#include <spine/EventData.h>
#include <spine/EventTimeline.h>
#include <spine/Extension.h>
#include <spine/HashMap.h>
#include <spine/HasRendererObject.h>
#include <spine/IkConstraint.h>
#include <spine/IkConstraintData.h>
#include <spine/IkConstraintTimeline.h>
#include <spine/Json.h>
#include <spine/LinkedMesh.h>
#include <spine/MathUtil.h>
#include <spine/MeshAttachment.h>
#include <spine/MixBlend.h>
#include <spine/MixDirection.h>
#include <spine/PathAttachment.h>
#include <spine/PathConstraint.h>
#include <spine/PathConstraintData.h>
#include <spine/PathConstraintMixTimeline.h>
#include <spine/PathConstraintPositionTimeline.h>
#include <spine/PathConstraintSpacingTimeline.h>
#include <spine/PointAttachment.h>
#include <spine/Pool.h>
#include <spine/PositionMode.h>
#include <spine/RegionAttachment.h>
#include <spine/RotateMode.h>
#include <spine/RotateTimeline.h>
#include <spine/RTTI.h>
#include <spine/ScaleTimeline.h>
#include <spine/ShearTimeline.h>
#include <spine/Skeleton.h>
#include <spine/SkeletonBinary.h>
#include <spine/SkeletonBounds.h>
#include <spine/SkeletonClipping.h>
#include <spine/SkeletonData.h>
#include <spine/SkeletonJson.h>
#include <spine/Skin.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/SpacingMode.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>
#include <spine/TextureLoader.h>
#include <spine/Timeline.h>
#include <spine/TimelineType.h>
#include <spine/TransformConstraint.h>
#include <spine/TransformConstraintData.h>
#include <spine/TransformConstraintTimeline.h>
#include <spine/TransformMode.h>
#include <spine/TranslateTimeline.h>
#include <spine/Triangulator.h>
#include <spine/TwoColorTimeline.h>
#include <spine/Updatable.h>
#include <spine/Vector.h>
#include <spine/VertexAttachment.h>
#include <spine/VertexEffect.h>
#include <spine/Vertices.h>

#endif
