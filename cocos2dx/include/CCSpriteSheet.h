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
#include "NSMutableArray.h"


namespace   cocos2d {
class CCSprite;
class CGRect;

/** @brief CCSpriteSheet is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
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
class CCX_DLL CCSpriteSheet : public CCNode, public CCTextureProtocol
{
public:
    ~CCSpriteSheet(void);

	/** initializes a CCSpriteSheet with a texture2d and capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 */
	bool initWithTexture(CCTexture2D *pobTexture, unsigned int uCapacity);

	/** initializes a CCSpriteSheet with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 The file will be loaded using the TextureMgr.
	 */
	bool initWithFile(const char *pszFileImage, unsigned int uCapacity);

	void increaseAtlasCapacity(void);

	/** creates an sprite with a rect in the CCSpriteSheet.
	 It's the same as:
	   - create an standard CCSsprite
	   - set the usingSpriteSheet = true
	   - set the textureAtlas to the same texture Atlas as the CCSpriteSheet
	 @deprecated Use CCSprite::spriteWithSpriteSheet(rect) instead;
	 */
	CCSprite* createSpriteWithRect(CGRect rect);

	/** initializes a previously created sprite with a rect. This sprite will have the same texture as the CCSpriteSheet.
	 It's the same as:
	 - initialize an standard CCSsprite
	 - set the usingSpriteSheet = true
	 - set the textureAtlas to the same texture Atlas as the CCSpriteSheet
	 @since v0.99.0
	 @deprecated Use CCSprite::spriteWithSpriteSheet(rect) instead;
	*/ 
	void initSprite(CCSprite* pobSprite, CGRect rect);

	/** removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.
	 @warning Removing a child from a CCSpriteSheet is very slow
	 */
	void removeChildAtIndex(unsigned int uIndex, bool bDoCleanup);	

	void insertChild(CCSprite *pobSprite, unsigned int uIndex);
	void removeSpriteFromAtlas(CCSprite *pobSprite);

	unsigned int rebuildIndexInOrder(CCSprite *pobParent, unsigned int uIndex);
	unsigned int atlasIndexForChild(CCSprite *pobSprite, int nZ);
	unsigned int highestAtlasIndexInChild(CCSprite *pSprite);
	unsigned int lowestAtlasIndexInChild(CCSprite *pSprite);

	// CCTextureProtocol
	virtual CCTexture2D* getTexture(void);
	virtual void setTexture(CCTexture2D *texture);
	virtual void setBlendFunc(ccBlendFunc blendFunc);
	virtual ccBlendFunc getBlendFunc(void);

	virtual void visit(void);
	virtual CCNode * addChild(CCNode * child);
	virtual CCNode * addChild(CCNode * child, int zOrder);
	virtual CCNode * addChild(CCNode * child, int zOrder, int tag);
	virtual void reorderChild(CCNode * child, int zOrder);
	/** removes a child given a reference. It will also cleanup the running actions depending on the cleanup parameter.
	@warning Removing a child from a CCSpriteSheet is very slow
	*/
	virtual void removeChild(CCNode* child, bool cleanup);
	virtual void removeAllChildrenWithCleanup(bool cleanup);
	virtual void draw(void);
public:
	/** creates a CCSpriteSheet with a texture2d and a default capacity of 29 children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 */
	static CCSpriteSheet* spriteSheetWithTexture(CCTexture2D *pobTexture);

	/** creates a CCSpriteSheet with a texture2d and capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 */
	static CCSpriteSheet* spriteSheetWithTexture(CCTexture2D *pobTexture, unsigned int uCapacity);

	/** creates a CCSpriteSheet with a file image (.png, .jpeg, .pvr, etc) with a default capacity of 29 children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 The file will be loaded using the TextureMgr.
	 */
	static CCSpriteSheet* spriteSheetWithFile(const char *pszFileImage);

	/** creates a CCSpriteSheet with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
	 The capacity will be increased in 33% in runtime if it run out of space.
	 The file will be loaded using the TextureMgr.
	*/
	static CCSpriteSheet* spriteSheetWithFile(const char *pszFileImage, unsigned int uCapacity);

private:
	void updateBlendFunc(void);

public:
	// attributes

	// descendants (children, gran children, etc)
	inline NSArray<CCSprite*>* getDescendants(void) { return m_pobDescendants; }

	// TextureAtlas
	inline CCTextureAtlas* getTextureAtlas(void) { return m_pobTextureAtlas; }
	inline void setTextureAtlas(CCTextureAtlas *pTextureAtlas)
	{
		m_pobTextureAtlas = pTextureAtlas;
		if (pTextureAtlas)
		{
			pTextureAtlas->retain();
		}
	}

protected:
	CCTextureAtlas *m_pobTextureAtlas;
	ccBlendFunc m_blendFunc;

	// all descendants: children, gran children, etc...
	NSArray<CCSprite*> *m_pobDescendants;
protected:
	/* IMPORTANT XXX IMPORTNAT:
	* These 2 methods can't be part of CCTMXLayer since they call [super add...], and CCSpriteSheet#add SHALL not be called
	*/
	
	/* Adds a quad into the texture atlas but it won't be added into the children array.
	This method should be called only when you are dealing with very big AtlasSrite and when most of the CCSprite won't be updated.
	For example: a tile map (CCTMXMap) or a label with lots of characters (BitmapFontAtlas)
	*/
	void addQuadFromSprite(CCSprite *sprite, unsigned int index);
	/* This is the opposite of "addQuadFromSprite.
	It add the sprite to the children and descendants array, but it doesn't update add it to the texture atlas
	*/
	CCSpriteSheet * addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag);

};
}//namespace   cocos2d 

#endif // __SPRITE_CCSPRITE_SHEET_H__
