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

#ifndef __SPRITE_CCSPRITE_SHEET_H__
#define __SPRITE_CCSPRITE_SHEET_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "CCTextureAtlas.h"
#include "ccMacros.h"
#include "cocoa/NSMutableArray.h"


class CCSprite;
class CGRect;

/** CCSpriteSheet is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *
 * A CCSpriteSheet can reference one and only one texture (one image file, one texture atlas).
 * Only the CCSprites that are contained in that texture can be added to the CCSpriteSheet.
 * All CCSprites added to a CCSpriteSheet are drawn in one OpenGL ES draw call.
 * If the CCSprites are not added to a CCSpriteSheet then an OpenGL ES draw call will be needed for each one, which is less efficient.
 *
 *
 * Limitations:
 *  - The only object that is accepted as child (or grandchild) is CCSprite or any subclass of CCSprite. eg: particles, labels and layer can't be added to a CCSpriteSheet.
 *  - Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of the texture, and all the sprites share the same texture.
 * 
 * @since v0.7.1
 */
class CCSpriteSheet : public CCNode, public CCTextureProtocol
{
public:
	/** initializes a CCSpriteSheet with a texture2d and capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 */
	CCSpriteSheet* initWithTexture(CCTexture2D *pobTexture, UINT32 uCapacity);

	/** initializes a CCSpriteSheet with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 The file will be loaded using the TextureMgr.
	 */
	CCSpriteSheet* initWithFile(const char *pszFileImage, UINT32 uCapacity);

	void increaceAtlasCapacity(void);

	/** creates an sprite with a rect in the CCSpriteSheet.
	 It's the same as:
	   - create an standard CCSsprite
	   - set the usingSpriteSheet = YES
	   - set the textureAtlas to the same texture Atlas as the CCSpriteSheet
	 @deprecated Use [CCSprite spriteWithSpriteSheet:rect] instead;
	 */
	CCSprite* createSpriteWithRect(CGRect rect);

	/** initializes a previously created sprite with a rect. This sprite will have the same texture as the CCSpriteSheet.
	 It's the same as:
	 - initialize an standard CCSsprite
	 - set the usingSpriteSheet = YES
	 - set the textureAtlas to the same texture Atlas as the CCSpriteSheet
	 @since v0.99.0
	 @deprecated Use [CCSprite initWithSpriteSheet:rect] instead;
	*/ 
	void initSprite(CCSprite* pobSprite, CGRect rect);

	/** removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.
	 @warning Removing a child from a CCSpriteSheet is very slow
	 */
	void removeChildAtIndex(UINT32 uIndex, bool bDoCleanup);

	/** removes a child given a reference. It will also cleanup the running actions depending on the cleanup parameter.
	 @warning Removing a child from a CCSpriteSheet is very slow
	 */
	void removeChild(CCSprite *pobSprite, bool bDoCleanup);

	void insertChild(CCSprite *pobSprite, bool bDoCleanup);
	void removeSpriteFromAtlas(CCSprite *pobSprite);

	UINT32 rebuildIndexInOrder(CCSprite *pobParent, UINT32 uIndex);
	UINT32 atlasIndexForChild(CCSprite *pobSprite, INT32 nZ);
public:
	/** creates a CCSpriteSheet with a texture2d and a default capacity of 29 children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 */
	static CCSpriteSheet* spriteSheetWithTexture(CCTexture2D *pobTexture);

	/** creates a CCSpriteSheet with a texture2d and capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 */
	static CCSpriteSheet* spriteSheetWithTexture(CCTexture2D *pobTexture, UINT32 uCapacity);

	/** creates a CCSpriteSheet with a file image (.png, .jpeg, .pvr, etc) with a default capacity of 29 children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 The file will be loaded using the TextureMgr.
	 */
	static CCSpriteSheet* spriteSheetWithFile(const char *pszFileImage);

	/** creates a CCSpriteSheet with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 The file will be loaded using the TextureMgr.
	*/
	static CCSpriteSheet* spriteSheetWithFile(const char *pszFileImage, UINT32 uCapacity);

public:
	// attributes

	// returns the TextureAtlas that is used, retain
	inline CCTextureAtlas* getTextureAtlas(void) { return m_pobTextureAtlas; }
	inline void setTextureAtlas(CCTextureAtlas *pobTextureAtlas)
	{
		m_pobTextureAtlas = pobTextureAtlas;
		if (pobTextureAtlas)
		{
			pobTextureAtlas->retain();
		}
	}

	// conforms to CCTextureProtocol protocol
	inline ccBlendFunc getBlendFunction(void) { return m_blendFunc; }
	inline void setBlendFunction(ccBlendFunc blendFunc) { m_blendFunc = blendFunc; }

	// descendants (children, gran children, etc)
	inline CCArray<CCSprite*> getDescendants(void) { return m_pobDescendants; }

protected:
	CCTextureAtlas *m_pobTextureAtlas;
	ccBlendFunc m_blendFunc;

	// all descendants: chlidren, gran children, etc...
	NSArray<CCSprite*> *m_pobDescendants;
};

#endif // __SPRITE_CCSPRITE_SHEET_H__
