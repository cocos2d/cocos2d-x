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

#ifndef Spine_VertexAttachment_h
#define Spine_VertexAttachment_h

#include <spine/Attachment.h>

#include <spine/Vector.h>

namespace spine {
	class Slot;

	/// An attachment with vertices that are transformed by one or more bones and can be deformed by a slot's vertices.
	class SP_API VertexAttachment : public Attachment {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class DeformTimeline;

		RTTI_DECL

	public:
		explicit VertexAttachment(const String& name);

		virtual ~VertexAttachment();

		void computeWorldVertices(Slot& slot, float* worldVertices);
		void computeWorldVertices(Slot& slot, Vector<float>& worldVertices);

		/// Transforms local vertices to world coordinates.
		/// @param start The index of the first Vertices value to transform. Each vertex has 2 values, x and y.
		/// @param count The number of world vertex values to output. Must be less than or equal to WorldVerticesLength - start.
		/// @param worldVertices The output world vertices. Must have a length greater than or equal to offset + count.
		/// @param offset The worldVertices index to begin writing values.
		/// @param stride The number of worldVertices entries between the value pairs written.
		void computeWorldVertices(Slot& slot, size_t start, size_t count, float* worldVertices, size_t offset, size_t stride = 2);
		void computeWorldVertices(Slot& slot, size_t start, size_t count, Vector<float>& worldVertices, size_t offset, size_t stride = 2);

		/// Gets a unique ID for this attachment.
		int getId();

		Vector<size_t>& getBones();

		Vector<float>& getVertices();

		size_t getWorldVerticesLength();
		void setWorldVerticesLength(size_t inValue);

		VertexAttachment* getDeformAttachment();
		void setDeformAttachment(VertexAttachment* attachment);

		void copyTo(VertexAttachment* other);

	protected:
		Vector<size_t> _bones;
		Vector<float> _vertices;
		size_t _worldVerticesLength;
		VertexAttachment* _deformAttachment;

	private:
		const int _id;

		static int getNextID();
	};
}

#endif /* Spine_VertexAttachment_h */
