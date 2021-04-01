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

#ifndef SPINE_COCOS2DX_H_
#define SPINE_COCOS2DX_H_

#include <spine/spine.h>
#include "cocos2d.h"

#include <spine/SkeletonRenderer.h>

#if COCOS2D_VERSION < 0x00040000
#include <spine/v3/SkeletonBatch.h>
#include <spine/v3/SkeletonTwoColorBatch.h>
#else
#include <spine/v4/SkeletonBatch.h>
#include <spine/v4/SkeletonTwoColorBatch.h>
#endif

#include <spine/SkeletonAnimation.h>

namespace spine {
	class Cocos2dAtlasAttachmentLoader: public AtlasAttachmentLoader {
	public:
		Cocos2dAtlasAttachmentLoader(Atlas* atlas);
		virtual ~Cocos2dAtlasAttachmentLoader();
		virtual void configureAttachment(Attachment* attachment);
	};

	class Cocos2dTextureLoader: public TextureLoader {
	public:
		Cocos2dTextureLoader();
		
		virtual ~Cocos2dTextureLoader();
		
		virtual void load(AtlasPage& page, const String& path);

		virtual void unload(void* texture);
	};

	class Cocos2dExtension: public DefaultSpineExtension {
	public:
		Cocos2dExtension();
		
		virtual ~Cocos2dExtension();
		
	protected:
		virtual char *_readFile(const String &path, int *length);
	};
}

#endif /* SPINE_COCOS2DX_H_ */
