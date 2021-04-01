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

#ifndef Spine_SkeletonClipping_h
#define Spine_SkeletonClipping_h

#include <spine/Vector.h>
#include <spine/Triangulator.h>

namespace spine {
	class Slot;
	class ClippingAttachment;

	class SP_API SkeletonClipping : public SpineObject {
	public:
		SkeletonClipping();

		size_t clipStart(Slot& slot, ClippingAttachment* clip);

		void clipEnd(Slot& slot);

		void clipEnd();

		void clipTriangles(float* vertices, unsigned short* triangles, size_t trianglesLength, float* uvs, size_t stride);

		void clipTriangles(Vector<float>& vertices, Vector<unsigned short>& triangles, Vector<float>& uvs, size_t stride);

		bool isClipping();

		Vector<float>& getClippedVertices();
		Vector<unsigned short>& getClippedTriangles();
		Vector<float>& getClippedUVs();

	private:
		Triangulator _triangulator;
		Vector<float> _clippingPolygon;
		Vector<float> _clipOutput;
		Vector<float> _clippedVertices;
		Vector<unsigned short> _clippedTriangles;
		Vector<float> _clippedUVs;
		Vector<float> _scratch;
		ClippingAttachment* _clipAttachment;
		Vector< Vector<float>* > *_clippingPolygons;

		/** Clips the input triangle against the convex, clockwise clipping area. If the triangle lies entirely within the clipping
		  * area, false is returned. The clipping area must duplicate the first vertex at the end of the vertices list. */
		bool clip(float x1, float y1, float x2, float y2, float x3, float y3, Vector<float>* clippingArea, Vector<float>* output);

		static void makeClockwise(Vector<float>& polygon);
	};
}

#endif /* Spine_SkeletonClipping_h */
