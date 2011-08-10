/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
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
#ifndef __CC_ANIMATION_H__
#define __CC_ANIMATION_H__

#include "CCPlatformConfig.h"
#include "CCObject.h"
#include "CCMutableArray.h"
#include "CCGeometry.h"
#include <string>

namespace   cocos2d {
	class CCSpriteFrame;
    class CCTexture2D;
	/** A CCAnimation object is used to perform animations on the CCSprite objects.

	The CCAnimation object contains CCSpriteFrame objects, and a possible delay between the frames.
	You can animate a CCAnimation object by using the CCAnimate action. Example:

	[sprite runAction:[CCAnimate actionWithAnimation:animation]];

	*/
	class CC_DLL CCAnimation : public CCObject
	{
	protected:
		std::string m_nameStr;
		float m_fDelay;
		CCMutableArray<CCSpriteFrame*> *m_pobFrames;

	public:
		// attributes

		/** get name of the animation */
		inline const char* getName(void) { return m_nameStr.c_str(); }
		/** set name of the animation */
		inline void setName(const char *pszName){ m_nameStr = pszName; }

		/** get delay between frames in seconds */
		inline float getDelay(void) { return m_fDelay; }
		/** set delay between frames in seconds */
		inline void setDelay(float fDelay) { m_fDelay = fDelay; }

		/** get array of frames */
		inline CCMutableArray<CCSpriteFrame*>* getFrames(void) { return m_pobFrames; }
		/** set array of frames, the Frames is retained */
		inline void setFrames(CCMutableArray<CCSpriteFrame*> *pFrames)
		{
			CC_SAFE_RETAIN(pFrames);
			CC_SAFE_RELEASE(m_pobFrames);
			m_pobFrames = pFrames;
		}

	public:
		~CCAnimation(void);

		/** Initializes a CCAnimation with frames.
		@since v0.99.5
		*/
		bool initWithFrames(CCMutableArray<CCSpriteFrame*> *pFrames);

		/** Initializes a CCAnimation with frames and a delay between frames
		@since v0.99.5
		*/
		bool initWithFrames(CCMutableArray<CCSpriteFrame*> *pFrames, float delay);

		/** adds a frame to a CCAnimation */
		void addFrame(CCSpriteFrame *pFrame);

		/** Adds a frame with an image filename. Internally it will create a CCSpriteFrame and it will add it.
		Added to facilitate the migration from v0.8 to v0.9.
		*/
		void addFrameWithFileName(const char *pszFileName);

		/** Adds a frame with a texture and a rect. Internally it will create a CCSpriteFrame and it will add it.
		Added to facilitate the migration from v0.8 to v0.9.
		*/
		void addFrameWithTexture(CCTexture2D* pobTexture, CCRect rect);

		bool init(void);

	public:
		/** Creates an animation
		@since v0.99.5
		*/
        static CCAnimation* animation(void);

		/** Creates an animation with frames.
		@since v0.99.5
		*/
		static CCAnimation* animationWithFrames(CCMutableArray<CCSpriteFrame*> *frames);

		/* Creates an animation with frames and a delay between frames.
		@since v0.99.5
		*/
		static CCAnimation* animationWithFrames(CCMutableArray<CCSpriteFrame*> *frames, float delay);
	};
} // end of name sapce cocos2d

#endif // __CC_ANIMATION_H__
