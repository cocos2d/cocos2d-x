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
#include "cocoa/NSMutableArray.h"
#include "cocoa/NSObject.h"

class CGRect;
class CGPoint;
class CGSize;
class CCTexture2D;

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
	/** Create a CCSpriteFrame with a texture, rect and offset.
	 It is assumed that the frame was not trimmed.
	 */
	CCSpriteFrame* frameWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset);

	/** Create a CCSpriteFrame with a texture, rect, offset and originalSize.
	 The originalSize is the size in pixels of the frame before being trimmed.
	 */
    CCSpriteFrame* frameWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset, CGSize originalSize);

public:
	/** Initializes a CCSpriteFrame with a texture, rect and offset.
	 It is assumed that the frame was not trimmed.
	 */
	CCSpriteFrame* initWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset);

	/** Initializes a CCSpriteFrame with a texture, rect, offset and originalSize.
	 The originalSize is the size in pixels of the frame before being trimmed.
	 */
	CCSpriteFrame* initWithTexture(CCTexture2D* pobTexture, CGRect rect, CGPoint offset, CGSize originalSize);
protected:
	CGRect m_obRect;
	CGPoint m_obOffset;
	CGSize m_obOriginalSize;
	CCTexture2D *m_pobTexture;
};

// an Animation object used within Sprites to perform animations 
class CCAnimation : public NSObject
{
public:
	// attributes

	// name of the animation
	inline char* getName(void) { return m_pszName; }
	inline void setName(char *pszName) { m_pszName = pszName; }

	// delay between frames in seconds
	inline float getDelay(void) { return m_fDelay; }
	inline void setDelay(float fDelay) { m_fDelay = fDelay; }

	// array of frames, retain
	inline NSMutableArray<CCSpriteFrame*> getFrames(void) { return m_pobFrames; }
	inline void setFrames(NSMutableArray<CCSpriteFrame*> *pobFrames)
	{
		m_pobFrames = pobFrames;
		if (pobFrames)
		{
			pobFrames->retain();
		}
	}

public:
	/** Creates a CCAnimation with a name
	 @since v0.99.3
	 */
	CCAnimation* animationWithName(char *pszName);

	/** Creates a CCAnimation with a name and frames
	 @since v0.99.3
	 */
	CCAnimation* animationWithName(char *pszName, NSArray<CCSpriteFrame*> *pobFrames);

	// Creates a CCAnimation with a name and delay between frames.
	CCAnimation* animationWithName(char *pszName, NSArray<CCSpriteFrame*> *pobFrames, float fDelay);

	// Creates a CCAnimation with a name, delay and an array of CCSpriteFrames
    CCAnimation* animationWithName(char *pszName, NSArray<CCSpriteFrame*> *pobFrames, float fDelay, NSArray *pobFrames);

public:
	/** Initializes a CCAnimation with a name
	 @since v0.99.3
	 */
	CCAnimation* initWithName(char *pszName);

	/** Initializes a CCAnimation with a name and frames
	 @since v0.99.3
	 */
    CCAnimation* initWithName(char *pszName, NSArray<CCSpriteFrame*> *pobFrames);

	// Initializes a CCAnimation with a name and delay between frames.
    CCAnimation* initWithName(char *pszName, float fDelay);

	// Initializes a CCAnimation with a name, delay and an array of CCSpriteFrames.
	CCAnimation* initWithName(char *pszName, float fDelay, NSArray<CCSpriteFrame*> *pobFrames);

	// adds a frame to a CCAnimation
	void addFrame(CCSpriteFrame *pobFrame);

	/** Adds a frame with an image filename. Internally it will create a CCSpriteFrame and it will add it.
	 Added to facilitate the migration from v0.8 to v0.9.
	 */
	void addFrameWithFileName(char *pszFileName);

	/** Adds a frame with a texture and a rect. Internally it will create a CCSpriteFrame and it will add it.
	 Added to facilitate the migration from v0.8 to v0.9.
	 */
	void addFrameWithTexture(CCTexture2D* pobTexture, CGRect rect);

protected:
	char *m_pszName;
	float m_fDelay;
	NSMutableArray<CCSpriteFrame*> *m_pobFrames;
};

#endif //__SPRITE_CCSPRITE_FRAME_H__
