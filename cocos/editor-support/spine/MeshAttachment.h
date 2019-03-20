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

#ifndef Spine_MeshAttachment_h
#define Spine_MeshAttachment_h

#include <spine/VertexAttachment.h>
#include <spine/Vector.h>
#include <spine/Color.h>
#include <spine/HasRendererObject.h>

namespace spine {
    /// Attachment that displays a texture region using a mesh.
    class SP_API MeshAttachment : public VertexAttachment, public HasRendererObject {
        friend class SkeletonBinary;
        friend class SkeletonJson;
        friend class AtlasAttachmentLoader;
        
        RTTI_DECL
        
    public:
        explicit MeshAttachment(const String& name);

        virtual ~MeshAttachment();

        void updateUVs();

        virtual bool applyDeform(VertexAttachment* sourceAttachment);
        
        int getHullLength();
        void setHullLength(int inValue);
        
        Vector<float>& getRegionUVs();
        
        /// The UV pair for each vertex, normalized within the entire texture. See also MeshAttachment::updateUVs
        Vector<float>& getUVs();
        
        Vector<unsigned short>& getTriangles();
        
        Color& getColor();
        
        const String& getPath();
        void setPath(const String& inValue);
        
        float getRegionU();
        void setRegionU(float inValue);
        
        float getRegionV();
        void setRegionV(float inValue);
        
        float getRegionU2();
        void setRegionU2(float inValue);
        
        float getRegionV2();
        void setRegionV2(float inValue);
        
        bool getRegionRotate();
        void setRegionRotate(bool inValue);
        
        float getRegionOffsetX();
        void setRegionOffsetX(float inValue);
        
        // Pixels stripped from the bottom left, unrotated.
        float getRegionOffsetY();
        void setRegionOffsetY(float inValue);
        
        float getRegionWidth();
        void setRegionWidth(float inValue);
        
        // Unrotated, stripped size.
        float getRegionHeight();
        void setRegionHeight(float inValue);
        
        float getRegionOriginalWidth();
        void setRegionOriginalWidth(float inValue);
        
        // Unrotated, unstripped size.
        float getRegionOriginalHeight();
        void setRegionOriginalHeight(float inValue);
        
        bool getInheritDeform();
        void setInheritDeform(bool inValue);
        
        MeshAttachment* getParentMesh();
        void setParentMesh(MeshAttachment* inValue);
        
        // Nonessential.
        Vector<unsigned short>& getEdges();
        float getWidth();
        void setWidth(float inValue);
        float getHeight();
        void setHeight(float inValue);

    private:
        float _regionOffsetX, _regionOffsetY, _regionWidth, _regionHeight, _regionOriginalWidth, _regionOriginalHeight;
        MeshAttachment* _parentMesh;
        Vector<float> _uvs;
        Vector<float> _regionUVs;
        Vector<unsigned short> _triangles;
        Vector<unsigned short> _edges;
        String _path;
        float _regionU;
        float _regionV;
        float _regionU2;
        float _regionV2;
        float _width;
        float _height;
        Color _color;
        int _hullLength;
        bool _inheritDeform;
        bool _regionRotate;
    };
}

#endif /* Spine_MeshAttachment_h */
