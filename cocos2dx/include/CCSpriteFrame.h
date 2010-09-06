/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __SPRITE_CCSPRITE_FRAME_H__
#define __SPRITE_CCSPRITE_FRAME_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "NSMutableArray.h"
#include "NSObject.h"

#include <string.h>

namespace   cocos2d {
class CGRect;
class CGPoint;
class CGSize;
class CCTexture2D;
class NSZone;

/** A CCSpriteFrame has:
	- texture: A CCTexture2D that will be used by the CCSprite
	- rectangle: A rectangle of the texture


 You can modify the frame of a CCSprite by doing:
 
	CCSpriteFrame *frame = [CCSpriteFrame frameWithTexture:texture rect:rect offset:offset];
	[sprite setDisplayFrame:frame];
 */
class CCSpriteFrame : public NSObject
{
public:
	// attributes

	// rect of the frame
	inline CGRect getRect(void) { return m_obRect; }
	inline void setRect(CGRect rect) { m_obRect = rect; }

	// offset of the frame
	inline CGPoint getOffset(void) { return m_obOffset; }
	inline void setOffset(CGPoint offset) { m_obOffset = offset; }

	// original size of the trimed image
	inline CGSize getOriginalSize(void) { return m_obOriginalSize; }
	inline void setOriginalSize(CGSize size) { m_obOriginalSize = size; }

	// texture of the frame, retain
	inline CCTexture2D* getTexture(void) { return m_pobTexture; }
	inline void setTexture(CCTexture2D* pobTexture)
	{
		m_pobTexture = pobTexture;
		if (pobTexture)
		{
			pobTexture->retain();
		}
	}

public:
	~CCSpriteFrame(void);
	virtual NSObject* copyWithZone(NSZone *pZone);

	/** Create a CCSpriteFrame with a texture, rect and offset.
	 It is assumed that the frame was not trimmed.
	 */
	static CCSpriteFrame* frameWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset);

	/** Create a CCSpriteFrame with a texture, rect, offset and originalSize.
	 The originalSize is the size in pixels of the frame before being trimmed.
	 */
    static CCSpriteFrame* frameWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset, CGSize originalSize);

public:
	/** Initializes a CCSpriteFrame with a texture, rect and offset.
	 It is assumed that the frame was not trimmed.
	 */
	bool initWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset);

	/** Initializes a CCSpriteFrame with a texture, rect, offset and originalSize.
	 The originalSize is the size in pixels of the frame before being trimmed.
	 */
	bool initWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset, CGSize originalSize);
protected:
	CGRect m_obRect;
	CGPoint m_obOffset;
	CGSize m_obOriginalSize;
	CCTexture2D *m_pobTexture;
};

// an Animation object used within Sprites to perform animations 
class CCX_DLL CCAnimation : public NSObject
{
protected:
	std::string m_nameStr;
	float m_fDelay;
	NSMutableArray<CCSpriteFrame*> *m_pobFrames;

public:
	// attributes

	// name of the animation
	inline const char* getName(void) { return m_nameStr.c_str(); }
	inline void setName(const char *pszName){ m_nameStr = pszName; }

	// delay between frames in seconds
	inline float getDelay(void) { return m_fDelay; }
	inline void setDelay(float fDelay) { m_fDelay = fDelay; }

	// array of frames, retain
	inline NSMutableArray<CCSpriteFrame*>* getFrames(void) { return m_pobFrames; }
	inline void setFrames(NSMutableArray<CCSpriteFrame*> *pFrames)
	{
		CCX_SAFE_RELEASE(m_pobFrames);
		m_pobFrames = pFrames;
		CCX_SAFE_RETAIN(m_pobFrames);
	}

public:
	~CCAnimation(void);

	/** Initializes a CCAnimation with a name
	 @since v0.99.3
	 */
	bool initWithName(const char *pszName);

	/** Initializes a CCAnimation with a name and frames
	 @since v0.99.3
	 */
    bool initWithName(const char *pszName, NSArray<CCSpriteFrame*> *pFrames);

	// Initializes a CCAnimation with a name and delay between frames.
    bool initWithName(const char *pszName, float fDelay);

	// Initializes a CCAnimation with a name, delay and an array of CCSpriteFrames.
	bool initWithName(const char *pszName, float fDelay, NSArray<CCSpriteFrame*> *pFrames);

	// adds a frame to a CCAnimation
	void addFrame(CCSpriteFrame *pFrame);

	/** Adds a frame with an image filename. Internally it will create a CCSpriteFrame and it will add it.
	 Added to facilitate the migration from v0.8 to v0.9.
	 */
	void addFrameWithFileName(const char *pszFileName);

	/** Adds a frame with a texture and a rect. Internally it will create a CCSpriteFrame and it will add it.
	 Added to facilitate the migration from v0.8 to v0.9.
	 */
	void addFrameWithTexture(CCTexture2D* pobTexture, CGRect rect);

public:
	/** Creates a CCAnimation with a name
	 @since v0.99.3
	 */
	static CCAnimation* animationWithName(const char *pszName);

	/** Creates a CCAnimation with a name and frames
	 @since v0.99.3
	 */
	static CCAnimation* animationWithName(const char *pszName, NSArray<CCSpriteFrame*> *pFrames);

	// Creates a CCAnimation with a name and delay between frames.
	static CCAnimation* animationWithName(const char *pszName, float fDelay);

	// Creates a CCAnimation with a name, delay and an array of CCSpriteFrames.
	static CCAnimation* animationWithName(const char *pszName, float fDelay, NSArray<CCSpriteFrame*> *pFrames);
};
}//namespace   cocos2d 

#endif //__SPRITE_CCSPRITE_FRAME_H__
