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

#ifndef SPINE_SKELETONTWOCOLORBATCH_H_
#define SPINE_SKELETONTWOCOLORBATCH_H_

#include <spine/spine.h>
#include "cocos2d.h"
#include <vector>

namespace spine {
	struct V3F_C4B_C4B_T2F {
		cocos2d::Vec3 position;
		cocos2d::Color4B color;
		cocos2d::Color4B color2;
		cocos2d::Tex2F texCoords;
	};
	
	struct TwoColorTriangles {
		V3F_C4B_C4B_T2F* verts;
		unsigned short* indices;
		int vertCount;
		int indexCount;
	};
	
	class TwoColorTrianglesCommand : public cocos2d::CustomCommand {
	public:
		TwoColorTrianglesCommand();
		
		~TwoColorTrianglesCommand();

#ifndef CC_USE_NEW_RENDERER
		void init(float globalOrder, GLuint textureID, cocos2d::GLProgramState* glProgramState, cocos2d::BlendFunc blendType, const TwoColorTriangles& triangles, const cocos2d::Mat4& mv, uint32_t flags);

		void useMaterial() const;

        inline GLuint getTextureID() const { return _textureID; }        inline cocos2d::GLProgramState* getGLProgramState() const { return _glProgramState; }

        void draw();
#else
        void init(float globalOrder, cocos2d::Texture2D* texture, cocos2d::BlendFunc blendType, const TwoColorTriangles& triangles, const cocos2d::Mat4& mv, uint32_t flags);

        void updateCommandPipelineDescriptor();

        inline cocos2d::backend::Texture* getTexture() const { return _texture; }

        void draw(cocos2d::Renderer *renderer);

        void updateVertexAndIndexBuffer(cocos2d::Renderer *renderer, V3F_C4B_C4B_T2F *vertices, int verticesSize, uint16_t *indices, int indicesSize);
#endif
		
		inline uint32_t getMaterialID() const { return _materialID; }
		
		inline const TwoColorTriangles& getTriangles() const { return _triangles; }
		
		inline ssize_t getVertexCount() const { return _triangles.vertCount; }
		
		inline ssize_t getIndexCount() const { return _triangles.indexCount; }
		
		inline const V3F_C4B_C4B_T2F* getVertices() const { return _triangles.verts; }
		
		inline const unsigned short* getIndices() const { return _triangles.indices; }
		
		inline cocos2d::BlendFunc getBlendType() const { return _blendType; }
		
		inline const cocos2d::Mat4& getModelView() const { return _mv; }
		
		void setForceFlush (bool forceFlush) { _forceFlush = forceFlush; }
		
		bool isForceFlush () { return _forceFlush; };
		
	protected:
		void generateMaterialID();
		uint32_t _materialID;

#ifndef CC_USE_NEW_RENDERER
		GLuint _textureID;
		cocos2d::GLProgramState* _glProgramState;
		cocos2d::GLProgram* _glProgram;
#else
        void *_prog = nullptr;
        cocos2d::backend::Texture      *_texture        = nullptr;
        cocos2d::backend::ProgramState *_programState   = nullptr;
        cocos2d::backend::UniformLocation   _locPMatrix;
        cocos2d::backend::UniformLocation   _locTexture;
#endif
		cocos2d::BlendFunc _blendType;
		TwoColorTriangles _triangles;
		cocos2d::Mat4 _mv;
		GLuint _alphaTextureID;
		bool _forceFlush;
	};

    class SkeletonTwoColorBatch {
    public:
        static SkeletonTwoColorBatch* getInstance ();

        static void destroyInstance ();

        void update (float delta);

		V3F_C4B_C4B_T2F* allocateVertices(uint32_t numVertices);
		void deallocateVertices(uint32_t numVertices);
		
		unsigned short* allocateIndices(uint32_t numIndices);
		void deallocateIndices(uint32_t numIndices);

#ifndef CC_USE_NEW_RENDERER
		TwoColorTrianglesCommand* addCommand(cocos2d::Renderer* renderer, float globalOrder, GLuint textureID, cocos2d::GLProgramState* glProgramState, cocos2d::BlendFunc blendType, const TwoColorTriangles& triangles, const cocos2d::Mat4& mv, uint32_t flags);

		cocos2d::GLProgramState* getTwoColorTintProgramState () { return _twoColorTintShaderState; }
		
		void batch (TwoColorTrianglesCommand* command);
		
		void flush (TwoColorTrianglesCommand* materialCommand);
#else
        TwoColorTrianglesCommand* addCommand(cocos2d::Renderer* renderer, float globalOrder, cocos2d::Texture2D* texture, cocos2d::BlendFunc blendType, const TwoColorTriangles& triangles, const cocos2d::Mat4& mv, uint32_t flags);

        void batch(cocos2d::Renderer* renderer, TwoColorTrianglesCommand* command);

        void flush(cocos2d::Renderer* renderer, TwoColorTrianglesCommand* materialCommand);
#endif
		uint32_t getNumBatches () { return _numBatches; };
		
    protected:
        SkeletonTwoColorBatch ();
        virtual ~SkeletonTwoColorBatch ();

		void reset ();

		TwoColorTrianglesCommand* nextFreeCommand ();

		// pool of commands
		std::vector<TwoColorTrianglesCommand*> _commandsPool;
		uint32_t _nextFreeCommand;

		// pool of vertices
		std::vector<V3F_C4B_C4B_T2F> _vertices;
		uint32_t _numVertices;
		
		// pool of indices
		Vector<unsigned short> _indices;
		
		
		// VBO handles & attribute locations
		GLuint _vertexBufferHandle;
		V3F_C4B_C4B_T2F* _vertexBuffer;
		uint32_t _numVerticesBuffer;
        uint32_t _numIndicesBuffer;
        unsigned short* _indexBuffer;

#ifndef CC_USE_NEW_RENDERER
        // two color tint shader and state
        cocos2d::GLProgram* _twoColorTintShader;
        cocos2d::GLProgramState* _twoColorTintShaderState;

		GLuint _indexBufferHandle;
		GLint _positionAttributeLocation;
		GLint _colorAttributeLocation;
		GLint _color2AttributeLocation;
		GLint _texCoordsAttributeLocation;
#else

#endif				
		// last batched command, needed for flushing to set material
		TwoColorTrianglesCommand* _lastCommand = nullptr;

		// number of batches in the last frame
		uint32_t _numBatches;
	};
}

#endif // SPINE_SKELETONTWOCOLORBATCH_H_
