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
        
        /// @return true if a deform originally applied to the specified attachment should be applied to this attachment.
        virtual bool applyDeform(VertexAttachment* sourceAttachment);
        
        /// Gets a unique ID for this attachment.
        int getId();
        
        Vector<size_t>& getBones();
        
        Vector<float>& getVertices();
        
        size_t getWorldVerticesLength();
        void setWorldVerticesLength(size_t inValue);
        
    protected:
        Vector<size_t> _bones;
        Vector<float> _vertices;
        size_t _worldVerticesLength;
        
    private:
        const int _id;
        
        static int getNextID();
    };
}

#endif /* Spine_VertexAttachment_h */
