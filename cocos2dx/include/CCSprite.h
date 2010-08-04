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

#ifndef __SPITE_NODE_CCSPRITE_H__
#define __SPITE_NODE_CCSPRITE_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "CCTextureAtlas.h"
#include "ccTypes.h"
#include "NSMutableDictionary.h"
#include "ccxCommon.h"

#include <string>
namespace   cocos2d {

class CCSpriteSheet;
class CCSpriteFrame;
class CCAnimation;
class CGRect;
class CGPoint;
class CGSize;
class CCTexture2D;
struct transformValues_;

enum {
	/// CCSprite invalid index on the CCSpriteSheet
	CCSpriteIndexNotInitialized = 0xffffffff,
};

/**
 Whether or not an CCSprite will rotate, scale or translate with it's parent.
 Useful in health bars, when you want that the health bar translates with it's parent but you don't
 want it to rotate with its parent.
 @since v0.99.0
 */
typedef enum {
	//! Translate with it's parent
	CC_HONOR_PARENT_TRANSFORM_TRANSLATE =  1 << 0,
	//! Rotate with it's parent
	CC_HONOR_PARENT_TRANSFORM_ROTATE	=  1 << 1,
	//! Scale with it's parent
	CC_HONOR_PARENT_TRANSFORM_SCALE		=  1 << 2,

	//! All possible transformation enabled. Default value.
	CC_HONOR_PARENT_TRANSFORM_ALL		=  CC_HONOR_PARENT_TRANSFORM_TRANSLATE | CC_HONOR_PARENT_TRANSFORM_ROTATE | CC_HONOR_PARENT_TRANSFORM_SCALE,

} ccHonorParentTransform;

/** CCSprite is a 2d image ( http://en.wikipedia.org/wiki/Sprite_(computer_graphics) )
 *
 * CCSprite can be created with an image, or with a sub-rectangle of an image.
 *
 * If the parent or any of its ancestors is a CCSpriteSheet then the following features/limitations are valid
 *	- Features when the parent is a CCSpriteSheet:
 *		- MUCH faster rendering, specially if the CCSpriteSheet has many children. All the children will be drawn in a single batch.
 *
 *	- Limitations
 *		- Camera is not supported yet (eg: CCOrbitCamera action doesn't work)
 *		- GridBase actions are not supported (eg: CCLens, CCRipple, CCTwirl)
 *		- The Alias/Antialias property belongs to CCSpriteSheet, so you can't individually set the aliased property.
 *		- The Blending function property belongs to CCSpriteSheet, so you can't individually set the blending function property.
 *		- Parallax scroller is not supported, but can be simulated with a "proxy" sprite.
 *
 *  If the parent is an standard CCNode, then CCSprite behaves like any other CCNode:
 *    - It supports blending functions
 *    - It supports aliasing / antialiasing
 *    - But the rendering will be slower: 1 draw per children.
 *
 */
class CCX_DLL CCSprite : public CCNode, public CCRGBAProtocol, public CCTextureProtocol
{
public:
	virtual void draw(void);

public:
	// attributes

	// whether or not the Sprite needs to be updated in the Atlas
	inline bool isDirty(void) { return m_bDirty; }
	inline void setDirty(bool bDirty) { m_bDirty = bDirty; }

	// the quad (tex coords, vertex coords and color) information
	inline ccV3F_C4B_T2F_Quad getQuad(void) { return m_sQuad; }

	// The index used on the TextureATlas. Don't modify this value unless you know what you are doing
	inline unsigned int getAtlasIndex(void) { return m_uAtlasIndex; }
	inline void setAtlasIndex(unsigned int uAtlasIndex) { m_uAtlasIndex = uAtlasIndex; }

	// returns the rect of the CCSprite
	inline CGRect getTextureRect(void) { return m_obRect; }

	// whether or not the Sprite is rendered using a CCSpriteSheet
	inline bool isUsesSpriteSheet(void) { return m_bUsesSpriteSheet; }
	inline void setUsesSpriteSheet(bool bUsesSpriteSheet) { m_bUsesSpriteSheet = bUsesSpriteSheet; }

	// weak reference of the CCTextureAtlas used when the sprite is rendered using a CCSpriteSheet 
	inline CCTextureAtlas* getTextureAtlas(void) { return m_pobTextureAtlas; }
	inline void setTextureAtlas(CCTextureAtlas *pobTextureAtlas) { m_pobTextureAtlas = pobTextureAtlas; }

	// weak reference to the CCSpriteSheet that renders the CCSprite
	inline CCSpriteSheet* getSpriteSheet(void) { return m_pobSpriteSheet; }
	inline void setSpriteSheet(CCSpriteSheet *pobSpriteSheet) { m_pobSpriteSheet = pobSpriteSheet; }

	/** whether or not to transform according to its parent transfomrations.
	 Useful for health bars. eg: Don't rotate the health bar, even if the parent rotates.
	 IMPORTANT: Only valid if it is rendered using an CCSpriteSheet.
	 @since v0.99.0
	 */
	inline ccHonorParentTransform getHornorParentTransform(void) { return m_eHonorParentTransform; }
	inline void setHornorParentTransform(ccHonorParentTransform eHonorParentTransform) { m_eHonorParentTransform = eHonorParentTransform; }

	/** offset position of the sprite. Calculated automatically by editors like Zwoptex.
	 @since v0.99.0
	 */
	inline CGPoint getOffsetPosition(void) { return m_obOffsetPosition; }
	inline void setSffsetPosition(CGPoint obOffsetPosition) { m_obOffsetPosition = obOffsetPosition; }

	// conforms to CCTextureProtocol protocol
	inline ccBlendFunc getBlendFunc(void) { return m_sBlendFunc; }
	inline void setBlendFunc(ccBlendFunc blendFunc) { m_sBlendFunc = blendFunc; }

public:
	/** Creates an sprite with a texture.
	 The rect used will be the size of the texture.
	 The offset will be (0,0).
	 */
	static CCSprite* spriteWithTexture(CCTexture2D *pTexture);

	/** Creates an sprite with a texture and a rect.
	 The offset will be (0,0).
	 */
	static CCSprite* spriteWithTexture(CCTexture2D *pTexture, CGRect rect);

	// Creates an sprite with a texture, a rect and offset.
    static CCSprite* spriteWithTexture(CCTexture2D *pTexture, CGRect rect, CGPoint offset);

	// Creates an sprite with an sprite frame.
	static CCSprite* spriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

	/** Creates an sprite with an sprite frame name.
	 An CCSpriteFrame will be fetched from the CCSpriteFrameCache by name.
	 If the CCSpriteFrame doesn't exist it will raise an exception.
	 @since v0.9
	 */
	static CCSprite* spriteWithSpriteFrameName(const char *pszSpriteFrameName);

	/** Creates an sprite with an image filename.
	 The rect used will be the size of the image.
	 The offset will be (0,0).
	 */
    static CCSprite* spriteWithFile(const char *pszFileName);

	/** Creates an sprite with an image filename and a rect.
	 The offset will be (0,0).
	 */
	static CCSprite* spriteWithFile(const char *pszFileName, CGRect rect);

	/** Creates an sprite with a CGImageRef.
	 @deprecated Use spriteWithCGImage:key: instead. Will be removed in v1.0 final
	 */
//	static CCSprite* spriteWithCGImage(CGImageRef pImage);

	/** Creates an sprite with a CGImageRef and a key.
	 The key is used by the CCTextureCache to know if a texture was already created with this CGImage.
	 For example, a valid key is: @"sprite_frame_01".
	 If key is nil, then a new texture will be created each time by the CCTextureCache. 
	 @since v0.99.0
	 */
//    static CCSprite* spriteWithCGImage(CGImageRef pImage, const char *pszKey);

	// Creates an sprite with an CCSpriteSheet and a rect
    static CCSprite* spriteWithSpriteSheet(CCSpriteSheet *pSpriteSheet, CGRect rect);

	// Creates an sprite with a texture, a rect and offset.
	static CCSprite* spriteWithSpriteSheet(CCSpriteSheet *pSpriteSheet, CGRect rect, CGPoint offset);

public:
	CCSprite* init(void);
	virtual ~CCSprite(void);
	CCSprite() {}

	virtual void removeChild(CCNode* pChild, bool bCleanup);
	virtual void removeAllChildrenWithCleanup(bool bCleanup);
	virtual void reorderChild(CCNode *pChild, int zOrder);
	virtual CCNode* addChild(CCNode *pChild);
	virtual CCNode* addChild(CCNode *pChild, int zOrder);
	virtual CCNode* addChild(CCNode *pChild, int zOrder, int tag);

	virtual void setDirtyRecursively(bool bValue);
	virtual void setPosition(CGPoint pos);
	virtual void setRotation(float fRotation);
	virtual void setScaleX(float fScaleX);
	virtual void setScaleY(float fScaleY);
	virtual void setScale(float fScale);
	virtual void setVertexZ(float fVertexZ);
	virtual void setAnchorPoint(CGPoint anchor);
	virtual void setIsRelativeAnchorPoint(bool bRelative);
	virtual void setIsVisible(bool bVisible);
	void setFlipX(bool bFlipX);
	void setFlipY(bool bFlipY);
	bool isFlipX(void);
	bool isFlipY(void);

	void updateColor(void);
	// RGBAProtocol
	virtual GLubyte getOpacity(void);
	virtual void setOpacity(GLubyte opacity);
	virtual ccColor3B getColor(void);
	virtual void setColor(ccColor3B color3);
	virtual void setIsOpacityModifyRGB(bool bValue);
	virtual bool getIsOpacityModifyRGB(void);

	// CCTextureProtocol
    virtual void setTexture(CCTexture2D *texture);
	virtual CCTexture2D* getTexture(void);

	/** Initializes an sprite with a texture.
	 The rect used will be the size of the texture.
	 The offset will be (0,0).
	 */
    CCSprite* initWithTexture(CCTexture2D *pTexture);

	/** Initializes an sprite with a texture and a rect.
	 The offset will be (0,0).
	 */
    CCSprite* initWithTexture(CCTexture2D *pTexture, CGRect rect);

	// Initializes an sprite with an sprite frame.
    CCSprite* initWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

	/** Initializes an sprite with an sprite frame name.
	 An CCSpriteFrame will be fetched from the CCSpriteFrameCache by name.
	 If the CCSpriteFrame doesn't exist it will raise an exception.
	 @since v0.9
	 */
    CCSprite* initWithSpriteFrameName(const char *pszSpriteFrameName);

	/** Initializes an sprite with an image filename.
	 The rect used will be the size of the image.
	 The offset will be (0,0).
	 */
    CCSprite* initWithFile(const char *pszFilename);

	/** Initializes an sprite with an image filename, and a rect.
	 The offset will be (0,0).
	 */
    CCSprite* initWithFile(const char *pszFilename, CGRect rect);

	/** Initializes an sprite with a CGImageRef
	 @deprecated Use spriteWithCGImage:key: instead. Will be removed in v1.0 final
	 */
//	CCSprite* initWithCGImage(CGImageRef pImage);

	/** Initializes an sprite with a CGImageRef and a key
	 The key is used by the CCTextureCache to know if a texture was already created with this CGImage.
	 For example, a valid key is: @"sprite_frame_01".
	 If key is nil, then a new texture will be created each time by the CCTextureCache. 
	 @since v0.99.0
	 */
//    CCSprite* initWithCGImage(CGImageRef pImage, const char *pszKey);

	// Initializes an sprite with an CCSpriteSheet and a rect
    CCSprite* initWithSpriteSheet(CCSpriteSheet *pSpriteSheet, CGRect rect);

	// sprite sheet methods

	// updates the quad according the the rotation, position, scale values.
	void updateTransform(void);

	/** tell the sprite to use self-render.
	 @since v0.99.0
	 */
	void useSelfRender(void);

	// updates the texture rect of the CCSprite.
     void setTextureRect(CGRect rect);

	/** tell the sprite to use sprite sheet render.
	 @since v0.99.0
	 */
	void useSpriteSheetRender(CCSpriteSheet *pSpriteSheet);

	// Frames

	// sets a new display frame to the CCSprite.
	void setDisplayFrame(CCSpriteFrame *pNewFrame);

	// returns whether or not a CCSpriteFrame is being displayed
	bool isFrameDisplayed(CCSpriteFrame *pFrame);

	// returns the current displayed frame.
	CCSpriteFrame* displayedFrame(void);

	// adds an Animation to the Sprite.
	void addAnimation(CCAnimation *pAnimation);

    // returns an Animation given it's name.
	CCAnimation* animationByName(const char *pszAnimationName);

	// Animation

	// changes the display frame based on an animation and an index.
	void setDisplayFrame(const char *pszAnimationName, int nFrameIndex);

protected:
    /*
	@interface CCSprite (Private)
	-(void)updateTextureCoords:(CGRect)rect;
	-(void)updateBlendFunc;
	-(void) initAnimationDictionary;
	-(void) setTextureRect:(CGRect)rect untrimmedSize:(CGSize)size;
	-(struct transformValues_) getTransformValues;	// optimization
	@end
	 */
	void updateTextureCoords(CGRect rect);
	void updateBlendFunc(void);
	void initAnimationDictionary(void);
	void setTextureRect(CGRect rect, CGSize size);
    struct transformValues_ getTransformValues(void);

protected:
	//
	// Data used when the sprite is rendered using a CCSpriteSheet
	//
	CCTextureAtlas			*m_pobTextureAtlas;		// Sprite Sheet texture atlas (weak reference)
	unsigned int					m_uAtlasIndex;			// Absolute (real) Index on the SpriteSheet
	CCSpriteSheet			*m_pobSpriteSheet;		// Used spritesheet (weak reference)
	ccHonorParentTransform	m_eHonorParentTransform;// whether or not to transform according to its parent transformations
	bool					m_bDirty;				// Sprite needs to be updated
	bool					m_bRecursiveDirty;		// Subchildren needs to be updated
	bool					m_bHasChildren;			// optimization to check if it contain children

	//
	// Data used when the sprite is self-rendered
	//
	ccBlendFunc		m_sBlendFunc;	// Needed for the texture protocol
	CCTexture2D		*m_pobTexture;// Texture used to render the sprite

	//
	// Shared data
	//

	// whether or not it's parent is a CCSpriteSheet
	bool m_bUsesSpriteSheet;

	// texture pixels
	CGRect m_obRect;

	// Offset Position (used by Zwoptex)
	CGPoint m_obOffsetPosition;

	// vertex coords, texture coords and color info
	ccV3F_C4B_T2F_Quad m_sQuad;

	// opacity and RGB protocol
	GLubyte m_nOpacity;
	ccColor3B m_sColor;
	ccColor3B m_sColorUnmodified;
	bool m_bOpacityModifyRGB;

	// image is flipped
	bool m_bFlipX;
	bool m_bFlipY;

	// Animations that belong to the sprite
	NSMutableDictionary<std::string, CCAnimation*> *m_pAnimations;
};
}//namespace   cocos2d 

#endif // __SPITE_NODE_CCSPRITE_H__
