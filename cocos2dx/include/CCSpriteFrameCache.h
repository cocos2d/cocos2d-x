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

#ifndef __SPRITE_CCSPRITE_FRAME_CACHE_H__
#define __SPRITE_CCSPRITE_FRAME_CACHE_H__

/*
 * To create sprite frames and texture atlas, use this tool:
 * http://zwoptex.zwopple.com/
 */

#include "CCSpriteFrame.h"
#include "CCTexture2D.h"
#include "cocoa/NSObject.h"
#include "cocoa/NSMutableDictionary.h"

#include <string>

class CCSpirte;

/** Singleton that handles the loading of the sprite frames.
 It saves in a cache the sprite frames.
 @since v0.9
 */
class CCSpriteFrameCache : public NSObject
{
public:
	void init(void);
	~CCSpriteFrameCache(void);

	/*Adds multiple Sprite Frames with a dictionary. The texture will be associated with the created sprite frames.
	  the pobDictionary look like:
	  "metadata" -> NSMutableDictionary<string, INT32>
	  "frames"   -> NSMutableDictionary<string, string>
	                |
					|__"x"  -> "123"
					   "y"  -> "12"
					   ...
	 */
	void addSpriteFramesWithDictionary(NSMutableDictionary<std::string> *pobDictionary, CCTexture2D *pobTexture);

	/** Adds multiple Sprite Frames from a plist file.
	 * A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png
	 * If you want to use another texture, you should use the addSpriteFramesWithFile:texture method.
	 */
	void addSpriteFramesWithFile(const char *pszPlist);

	// Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
	void addSpriteFramesWithFile(const char *pszPlist, CCTexture2D *pobTexture);

	/** Adds an sprite frame with a given name.
	 If the name already exists, then the contents of the old name will be replaced with the new one.
	 */
	void addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName);

	/** Purges the dictionary of loaded sprite frames.
	 * Call this method if you receive the "Memory Warning".
	 * In the short term: it will free some resources preventing your app from being killed.
	 * In the medium term: it will allocate more resources.
	 * In the long term: it will be the same.
	 */
	void removeSpriteFrames(void);

	/** Removes unused sprite frames.
	 * Sprite Frames that have a retain count of 1 will be deleted.
	 * It is convinient to call this method after when starting a new Scene.
	 */
	void removeUnusedSpriteFrames(void);

	// Deletes an sprite frame from the sprite frame cache.
	void removeSpriteFrameByName(const char *pszName);

	/** Returns an Sprite Frame that was previously added.
	 If the name is not found it will return nil.
	 You should retain the returned copy if you are going to use it.
	 */
	CCSpriteFrame* spriteFrameByName(const char *pszName);

	/** Creates an sprite with the name of an sprite frame.
	 The created sprite will contain the texture, rect and offset of the sprite frame.
	 It returns an autorelease object.
	 @deprecated use [CCSprite spriteWithSpriteFrameName:name]. This method will be removed on final v0.9
	 */
	CCSprite* createSpriteWithFrameName(const char *pszName);

public:
	// Retruns ths shared instance of the Sprite Frame cache
	static CCSpriteFrameCache* sharedSpriteFrameCache(void);

	// Purges the cache. It releases all the Sprite Frames and the retained instance.
	static void purgeSharedSpriteFrameCache(void);

private:
	CCSpriteFrameCache(void) {}

protected:
	NSMutableDictionary<std::string, CCSpriteFrame*> *m_pobSpriteFrames;
};

#endif // __SPRITE_CCSPRITE_FRAME_CACHE_H__
