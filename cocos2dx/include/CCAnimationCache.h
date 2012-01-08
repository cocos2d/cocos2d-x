/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CC_ANIMATION_CACHE_H__
#define __CC_ANIMATION_CACHE_H__

#include "CCObject.h"
#include "CCMutableDictionary.h"

#include <string>

namespace cocos2d
{
	class CCAnimation;

	/** Singleton that manages the Animations.
	It saves in a cache the animations. You should use this class if you want to save your animations in a cache.

	Before v0.99.5, the recommend way was to save them on the CCSprite. Since v0.99.5, you should use this class instead.

	@since v0.99.5
	*/
	class CC_DLL CCAnimationCache : public CCObject
	{
	public:
		~CCAnimationCache();
		CCAnimationCache();

		/** Retruns ths shared instance of the Animation cache */
		static CCAnimationCache* sharedAnimationCache(void);

		/** Purges the cache. It releases all the CCAnimation objects and the shared instance.
		*/
		static void purgeSharedAnimationCache(void);

		/** Adds a CCAnimation with a name.
		*/
		void addAnimation(CCAnimation *animation, const char * name);

		/** Deletes a CCAnimation from the cache.
		*/
		void removeAnimationByName(const char* name);

		/** Returns a CCAnimation that was previously added.
		If the name is not found it will return nil.
		You should retain the returned copy if you are going to use it.
		*/
		CCAnimation* animationByName(const char* name);

		bool init(void);

	private:
		CCMutableDictionary<std::string, CCAnimation*> *m_pAnimations;
		static CCAnimationCache *s_pSharedAnimationCache;
	};
}

#endif // __CC_ANIMATION_CACHE_H__