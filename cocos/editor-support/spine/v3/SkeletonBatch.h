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

#ifndef SPINE_SKELETONBATCH_H_
#define SPINE_SKELETONBATCH_H_

#include "cocos2d.h"
#if COCOS2D_VERSION < 0x00040000

#include <spine/spine.h>
#include <vector>

namespace spine {

	class SkeletonBatch {
	public:
		static SkeletonBatch* getInstance ();

		static void destroyInstance ();

		void update (float delta);

		cocos2d::V3F_C4B_T2F* allocateVertices(uint32_t numVertices);
		void deallocateVertices(uint32_t numVertices);
		unsigned short* allocateIndices(uint32_t numIndices);
		void deallocateIndices(uint32_t numVertices);
		cocos2d::TrianglesCommand* addCommand(cocos2d::Renderer* renderer, float globalOrder, cocos2d::Texture2D* texture, cocos2d::GLProgramState* glProgramState, cocos2d::BlendFunc blendType, const cocos2d::TrianglesCommand::Triangles& triangles, const cocos2d::Mat4& mv, uint32_t flags);

	protected:
		SkeletonBatch ();
		virtual ~SkeletonBatch ();

		void reset ();

		cocos2d::TrianglesCommand* nextFreeCommand ();

		// pool of commands
		std::vector<cocos2d::TrianglesCommand*> _commandsPool;
		uint32_t _nextFreeCommand;

		// pool of vertices
		std::vector<cocos2d::V3F_C4B_T2F> _vertices;
		uint32_t _numVertices;

		// pool of indices
		Vector<unsigned short> _indices;
	};

}

#endif

#endif // SPINE_SKELETONBATCH_H_
