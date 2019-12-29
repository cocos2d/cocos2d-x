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

#ifndef Spine_SkeletonBounds_h
#define Spine_SkeletonBounds_h

#include <spine/Vector.h>
#include <spine/SpineObject.h>

namespace spine {
	class Skeleton;
	class BoundingBoxAttachment;
	class Polygon;

	/// Collects each BoundingBoxAttachment that is visible and computes the world vertices for its polygon.
	/// The polygon vertices are provided along with convenience methods for doing hit detection.
	class SP_API SkeletonBounds : public SpineObject {
	public:
		SkeletonBounds();

		/// Clears any previous polygons, finds all visible bounding box attachments,
		/// and computes the world vertices for each bounding box's polygon.
		/// @param skeleton The skeleton.
		/// @param updateAabb
		/// If true, the axis aligned bounding box containing all the polygons is computed.
		/// If false, the SkeletonBounds AABB methods will always return true.
		///
		void update(Skeleton& skeleton, bool updateAabb);

		/// Returns true if the axis aligned bounding box contains the point.
		bool aabbcontainsPoint(float x, float y);

		/// Returns true if the axis aligned bounding box intersects the line segment.
		bool aabbintersectsSegment(float x1, float y1, float x2, float y2);

		/// Returns true if the axis aligned bounding box intersects the axis aligned bounding box of the specified bounds.
		bool aabbIntersectsSkeleton(SkeletonBounds bounds);

		/// Returns true if the polygon contains the point.
		bool containsPoint(Polygon* polygon, float x, float y);

		/// Returns the first bounding box attachment that contains the point, or NULL. When doing many checks, it is usually more
		/// efficient to only call this method if {@link #aabbcontainsPoint(float, float)} returns true.
		BoundingBoxAttachment* containsPoint(float x, float y);

		/// Returns the first bounding box attachment that contains the line segment, or NULL. When doing many checks, it is usually
		/// more efficient to only call this method if {@link #aabbintersectsSegment(float, float, float, float)} returns true.
		BoundingBoxAttachment* intersectsSegment(float x1, float y1, float x2, float y2);

		/// Returns true if the polygon contains the line segment.
		bool intersectsSegment(Polygon* polygon, float x1, float y1, float x2, float y2);

		Polygon* getPolygon(BoundingBoxAttachment* attachment);

		float getWidth();
		float getHeight();

	private:
		Vector<Polygon*> _polygonPool;
		Vector<BoundingBoxAttachment*> _boundingBoxes;
		Vector<Polygon*> _polygons;
		float _minX, _minY, _maxX, _maxY;

		void aabbCompute();
	};

	class Polygon : public SpineObject {
	public:
		Vector<float> _vertices;
		int _count;

		Polygon() : _count(0) {
			_vertices.ensureCapacity(16);
		}
	};
}

#endif /* Spine_SkeletonBounds_h */
