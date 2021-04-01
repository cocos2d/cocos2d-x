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

#ifndef Spine_RegionAttachment_h
#define Spine_RegionAttachment_h

#include <spine/Attachment.h>
#include <spine/Vector.h>
#include <spine/Color.h>

#include <spine/HasRendererObject.h>

#define NUM_UVS 8

namespace spine {
	class Bone;

	/// Attachment that displays a texture region.
	class SP_API RegionAttachment : public Attachment, public HasRendererObject {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class AtlasAttachmentLoader;

		RTTI_DECL

	public:
		explicit RegionAttachment(const String& name);

		void updateOffset();

		void setUVs(float u, float v, float u2, float v2, bool rotate);

		/// Transforms the attachment's four vertices to world coordinates.
		/// @param bone The parent bone.
		/// @param worldVertices The output world vertices. Must have a length greater than or equal to offset + 8.
		/// @param offset The worldVertices index to begin writing values.
		/// @param stride The number of worldVertices entries between the value pairs written.
		void computeWorldVertices(Bone& bone, float *worldVertices, size_t offset, size_t stride = 2);
		void computeWorldVertices(Bone& bone, Vector<float>& worldVertices, size_t offset, size_t stride = 2);

		float getX();
		void setX(float inValue);
		float getY();
		void setY(float inValue);
		float getRotation();
		void setRotation(float inValue);
		float getScaleX();
		void setScaleX(float inValue);
		float getScaleY();
		void setScaleY(float inValue);
		float getWidth();
		void setWidth(float inValue);
		float getHeight();
		void setHeight(float inValue);

		Color& getColor();

		const String& getPath();
		void setPath(const String& inValue);

		float getRegionOffsetX();
		void setRegionOffsetX(float inValue);

		float getRegionOffsetY();
		void setRegionOffsetY(float inValue);

		float getRegionWidth();
		void setRegionWidth(float inValue);

		float getRegionHeight();
		void setRegionHeight(float inValue);

		float getRegionOriginalWidth();
		void setRegionOriginalWidth(float inValue);

		float getRegionOriginalHeight();
		void setRegionOriginalHeight(float inValue);

		Vector<float>& getOffset();
		Vector<float>& getUVs();

		virtual Attachment* copy();

	private:
		static const int BLX;
		static const int BLY;
		static const int ULX;
		static const int ULY;
		static const int URX;
		static const int URY;
		static const int BRX;
		static const int BRY;

		float _x, _y, _rotation, _scaleX, _scaleY, _width, _height;
		float _regionOffsetX, _regionOffsetY, _regionWidth, _regionHeight, _regionOriginalWidth, _regionOriginalHeight;
		Vector<float> _vertexOffset;
		Vector<float> _uvs;
		String _path;
		float _regionU;
		float _regionV;
		float _regionU2;
		float _regionV2;
		Color _color;
	};
}

#endif /* Spine_RegionAttachment_h */
