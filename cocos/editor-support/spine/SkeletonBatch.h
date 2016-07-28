/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SKELETONBATCH_H_
#define SPINE_SKELETONBATCH_H_

#include <spine/spine.h>
#include "cocos2d.h"

namespace spine {

class SkeletonBatch {
public:
	/* Sets the max number of vertices that can be drawn in a single frame. The buffer will grow automatically as needed, but
	 * setting it to the appropriate is more efficient. Best to call before getInstance is called for the first time. Default is
	 * 8192. */
	static void setBufferSize (int vertexCount);

	static SkeletonBatch* getInstance ();

	void update (float delta);

	void addCommand (cocos2d::Renderer* renderer, float globalOrder, GLuint textureID, cocos2d::GLProgramState* glProgramState,
		cocos2d::BlendFunc blendType, const cocos2d::TrianglesCommand:: Triangles& triangles, const cocos2d::Mat4& mv, uint32_t flags);

protected:
	SkeletonBatch (int capacity);
	virtual ~SkeletonBatch ();

	cocos2d::V3F_C4B_T2F* _buffer;
	int _capacity;
	int _position;

	class Command {
	public:
		Command ();
		virtual ~Command ();

		cocos2d::TrianglesCommand* trianglesCommand;
		cocos2d::TrianglesCommand::Triangles* triangles;
		Command* next;
	};

	Command* _firstCommand;
	Command* _command;
};

}

#endif // SPINE_SKELETONBATCH_H_
