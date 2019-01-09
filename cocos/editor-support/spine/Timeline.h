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

#ifndef Spine_Timeline_h
#define Spine_Timeline_h

#include <spine/RTTI.h>
#include <spine/Vector.h>
#include <spine/MixBlend.h>
#include <spine/MixDirection.h>
#include <spine/SpineObject.h>

namespace spine {
class Skeleton;

class Event;

class SP_API Timeline : public SpineObject {
RTTI_DECL

public:
	Timeline();

	virtual ~Timeline();

	/// Sets the value(s) for the specified time.
	/// @param skeleton The skeleton the timeline is being applied to. This provides access to the bones, slots, and other skeleton components the timeline may change.
	/// @param lastTime lastTime The time this timeline was last applied. Timelines such as EventTimeline trigger only at specific times rather than every frame. In that case, the timeline triggers everything between lastTime (exclusive) and time (inclusive).
	/// @param time The time within the animation. Most timelines find the key before and the key after this time so they can interpolate between the keys.
	/// @param pEvents If any events are fired, they are added to this array. Can be NULL to ignore firing events or if the timeline does not fire events. May be NULL.
	/// @param alpha alpha 0 applies the current or setup pose value (depending on pose parameter). 1 applies the timeline
	///     value. Between 0 and 1 applies a value between the current or setup pose and the timeline value. By adjusting
	///     alpha over time, an animation can be mixed in or out. alpha can also be useful to
	///      apply animations on top of each other (layered).
	/// @param blend Controls how mixing is applied when alpha is than 1.
	/// @param direction Indicates whether the timeline is mixing in or out. Used by timelines which perform instant transitions such as DrawOrderTimeline and AttachmentTimeline.
	virtual void
	apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha, MixBlend blend,
		  MixDirection direction) = 0;

	virtual int getPropertyId() = 0;
};
}

#endif /* Spine_Timeline_h */
