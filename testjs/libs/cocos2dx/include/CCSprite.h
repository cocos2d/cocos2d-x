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

#ifndef __SPITE_NODE_CCSPRITE_H__
#define __SPITE_NODE_CCSPRITE_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "CCTextureAtlas.h"
#include "ccTypes.h"
#include "CCMutableDictionary.h"

#include <string>
namespace   cocos2d {

class CCSpriteBatchNode;
class CCSpriteFrame;
class CCAnimation;
class CCRect;
class CCPoint;
class CCSize;
class CCTexture2D;
struct transformValues_;

#define CCSpriteIndexNotInitialized 0xffffffff 	/// CCSprite invalid index on the CCSpriteBatchode

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
    //! Skew with it's parent
    CC_HONOR_PARENT_TRANSFORM_SKEW		=  1 << 3,

	//! All possible transformation enabled. Default value.
	CC_HONOR_PARENT_TRANSFORM_ALL		=  CC_HONOR_PARENT_TRANSFORM_TRANSLATE | CC_HONOR_PARENT_TRANSFORM_ROTATE | CC_HONOR_PARENT_TRANSFORM_SCALE | CC_HONOR_PARENT_TRANSFORM_SKEW,

} ccHonorParentTransform;

/** CCSprite is a 2d image ( http://en.wikipedia.org/wiki/Sprite_(computer_graphics) )
*
* CCSprite can be created with an image, or with a sub-rectangle of an image.
*
* If the parent or any of its ancestors is a CCSpriteBatchNode then the following features/limitations are valid
*	- Features when the parent is a CCBatchNode:
*		- MUCH faster rendering, specially if the CCSpriteBatchNode has many children. All the children will be drawn in a single batch.
*
*	- Limitations
*		- Camera is not supported yet (eg: CCOrbitCamera action doesn't work)
*		- GridBase actions are not supported (eg: CCLens, CCRipple, CCTwirl)
*		- The Alias/Antialias property belongs to CCSpriteBatchNode, so you can't individually set the aliased property.
*		- The Blending function property belongs to CCSpriteBatchNode, so you can't individually set the blending function property.
*		- Parallax scroller is not supported, but can be simulated with a "proxy" sprite.
*
*  If the parent is an standard CCNode, then CCSprite behaves like any other CCNode:
*    - It supports blending functions
*    - It supports aliasing / antialiasing
*    - But the rendering will be slower: 1 draw per children.
*
* The default anchorPoint in CCSprite is (0.5, 0.5).
*/
class CC_DLL CCSprite : public CCNode, public CCTextureProtocol, public CCRGBAProtocol
{
	/** Opacity: conforms to CCRGBAProtocol protocol */
	CC_PROPERTY(GLubyte, m_nOpacity, Opacity)
	/** Color: conforms with CCRGBAProtocol protocol */
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_sColor, Color);
public:
	virtual void draw(void);

public:
	// attributes

	/** whether or not the Sprite needs to be updated in the Atlas */
	inline bool isDirty(void) { return m_bDirty; }
	/** make the Sprite to be updated in the Atlas. */
	inline void setDirty(bool bDirty) { m_bDirty = bDirty; }

	/** get the quad (tex coords, vertex coords and color) information */
	inline ccV3F_C4B_T2F_Quad getQuad(void) { return m_sQuad; }

	/** returns whether or not the texture rectangle is rotated */
	inline bool isTextureRectRotated(void) { return m_bRectRotated; }
	
	/** Set the index used on the TextureAtlas. */
	inline unsigned int getAtlasIndex(void) { return m_uAtlasIndex; }
	/** Set the index used on the TextureAtlas.
	@warning Don't modify this value unless you know what you are doing 
	*/
	inline void setAtlasIndex(unsigned int uAtlasIndex) { m_uAtlasIndex = uAtlasIndex; }

	/** returns the rect of the CCSprite in points */
	inline const CCRect& getTextureRect(void) { return m_obRect; }

	/** whether or not the Sprite is rendered using a CCSpriteBatchNode */
	inline bool isUsesBatchNode(void) { return m_bUsesBatchNode; }
	/** make the Sprite been rendered using a CCSpriteBatchNode */
	inline void setUsesSpriteBatchNode(bool bUsesSpriteBatchNode) { m_bUsesBatchNode = bUsesSpriteBatchNode; }

	inline CCTextureAtlas* getTextureAtlas(void) { return m_pobTextureAtlas; }
	inline void setTextureAtlas(CCTextureAtlas *pobTextureAtlas) { m_pobTextureAtlas = pobTextureAtlas; }

	inline CCSpriteBatchNode* getSpriteBatchNode(void) { return m_pobBatchNode; }
	inline void setSpriteBatchNode(CCSpriteBatchNode *pobSpriteBatchNode) { m_pobBatchNode = pobSpriteBatchNode; }

	/** whether or not to transform according to its parent transformations.
	 Useful for health bars. eg: Don't rotate the health bar, even if the parent rotates.
	 IMPORTANT: Only valid if it is rendered using an CCSpriteSheet.
	 @since v0.99.0
	 */
	inline ccHonorParentTransform getHonorParentTransform(void) { return m_eHonorParentTransform; }
	/** whether or not to transform according to its parent transformations.
	Useful for health bars. eg: Don't rotate the health bar, even if the parent rotates.
	IMPORTANT: Only valid if it is rendered using an CCSpriteSheet.
	@since v0.99.0
	*/
	inline void setHonorParentTransform(ccHonorParentTransform eHonorParentTransform) { m_eHonorParentTransform = eHonorParentTransform; }

	/** Get offset position of the sprite. Calculated automatically by editors like Zwoptex.
	 @since v0.99.0
	 */
	inline const CCPoint& getOffsetPositionInPixels(void) { return m_obOffsetPositionInPixels; }

	/** conforms to CCTextureProtocol protocol */
	inline ccBlendFunc getBlendFunc(void) { return m_sBlendFunc; }
	/** conforms to CCTextureProtocol protocol */
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
	static CCSprite* spriteWithTexture(CCTexture2D *pTexture, const CCRect& rect);

	/** Creates an sprite with a texture, a rect and offset. */
    static CCSprite* spriteWithTexture(CCTexture2D *pTexture, const CCRect& rect, const CCPoint& offset);

	/** Creates an sprite with an sprite frame. */
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
	static CCSprite* spriteWithFile(const char *pszFileName, const CCRect& rect);
    
	/** Creates an sprite with an CCBatchNode and a rect
	*/
	static CCSprite* spriteWithBatchNode(CCSpriteBatchNode *batchNode, const CCRect& rect);
public:
    CCSprite(void);
	virtual ~CCSprite(void);
	virtual bool init(void);

	virtual void removeChild(CCNode* pChild, bool bCleanup);
	virtual void removeAllChildrenWithCleanup(bool bCleanup);
	virtual void reorderChild(CCNode *pChild, int zOrder);
	virtual void addChild(CCNode *pChild);
	virtual void addChild(CCNode *pChild, int zOrder);
	virtual void addChild(CCNode *pChild, int zOrder, int tag);

	virtual void setDirtyRecursively(bool bValue);
	virtual void setPosition(const CCPoint& pos);
	virtual void setPositionInPixels(const CCPoint& pos);
	virtual void setRotation(float fRotation);
    virtual void setSkewX(float sx);
    virtual void setSkewY(float sy);
	virtual void setScaleX(float fScaleX);
	virtual void setScaleY(float fScaleY);
	virtual void setScale(float fScale);
	virtual void setVertexZ(float fVertexZ);
	virtual void setAnchorPoint(const CCPoint& anchor);
	virtual void setIsRelativeAnchorPoint(bool bRelative);
	virtual void setIsVisible(bool bVisible);
	void setFlipX(bool bFlipX);
	void setFlipY(bool bFlipY);
	/** whether or not the sprite is flipped horizontally. 
	It only flips the texture of the sprite, and not the texture of the sprite's children.
	Also, flipping the texture doesn't alter the anchorPoint.
	If you want to flip the anchorPoint too, and/or to flip the children too use:

	sprite->setScaleX(sprite->getScaleX() * -1);
	*/
	bool isFlipX(void);
	/** whether or not the sprite is flipped vertically.
	It only flips the texture of the sprite, and not the texture of the sprite's children.
	Also, flipping the texture doesn't alter the anchorPoint.
	If you want to flip the anchorPoint too, and/or to flip the children too use:

	sprite->setScaleY(sprite->getScaleY() * -1);
	*/
	bool isFlipY(void);

	void updateColor(void);
	// RGBAProtocol
	/** opacity: conforms to CCRGBAProtocol protocol */
	virtual void setIsOpacityModifyRGB(bool bValue);
	virtual bool getIsOpacityModifyRGB(void);

	// CCTextureProtocol
    virtual void setTexture(CCTexture2D *texture);
	virtual CCTexture2D* getTexture(void);

	/** Initializes an sprite with a texture.
	 The rect used will be the size of the texture.
	 The offset will be (0,0).
	 */
    bool initWithTexture(CCTexture2D *pTexture);

	/** Initializes an sprite with a texture and a rect.
	 The offset will be (0,0).
	 */
    bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect);

	// Initializes an sprite with an sprite frame.
    bool initWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

	/** Initializes an sprite with an sprite frame name.
	 An CCSpriteFrame will be fetched from the CCSpriteFrameCache by name.
	 If the CCSpriteFrame doesn't exist it will raise an exception.
	 @since v0.9
	 */
    bool initWithSpriteFrameName(const char *pszSpriteFrameName);

	/** Initializes an sprite with an image filename.
	 The rect used will be the size of the image.
	 The offset will be (0,0).
	 */
    bool initWithFile(const char *pszFilename);

	/** Initializes an sprite with an image filename, and a rect.
	 The offset will be (0,0).
	 */
    bool initWithFile(const char *pszFilename, const CCRect& rect);

	/** Initializes an sprite with an CCSpriteBatchNode and a rect in points */
	bool initWithBatchNode(CCSpriteBatchNode *batchNode, const CCRect& rect);

	/** Initializes an sprite with an CCSpriteBatchNode and a rect in pixels
	@since v0.99.5
	*/
	bool initWithBatchNodeRectInPixels(CCSpriteBatchNode *batchNode, const CCRect& rect);

	// BatchNode methods

	/** updates the quad according the the rotation, position, scale values. */
	void updateTransform(void);

	/** tell the sprite to use self-render.
	 @since v0.99.0
	 */
	void useSelfRender(void);

	/** updates the texture rect of the CCSprite in points. */
     void setTextureRect(const CCRect& rect);

	 /** updates the texture rect, rectRotated and untrimmed size of the CCSprite in pixels
	 */
	 void setTextureRectInPixels(const CCRect& rect, bool rotated, const CCSize& size);

	/** tell the sprite to use batch node render.
	 @since v0.99.0
	 */
	 void useBatchNode(CCSpriteBatchNode *batchNode);

	// Frames

	/** sets a new display frame to the CCSprite. */
	void setDisplayFrame(CCSpriteFrame *pNewFrame);

	/** returns whether or not a CCSpriteFrame is being displayed */
	bool isFrameDisplayed(CCSpriteFrame *pFrame);

	/** returns the current displayed frame. */
	CCSpriteFrame* displayedFrame(void);

	// Animation

	/** changes the display frame with animation name and index.
	The animation name will be get from the CCAnimationCache
	@since v0.99.5
	*/
	void setDisplayFrameWithAnimationName(const char *animationName, int frameIndex);

protected:
	void updateTextureCoords(const CCRect& rect);
	void updateBlendFunc(void);
    void getTransformValues(struct transformValues_ *tv); // optimization

protected:
	//
	// Data used when the sprite is rendered using a CCSpriteSheet
	//
	CCTextureAtlas			*m_pobTextureAtlas;		// Sprite Sheet texture atlas (weak reference)
	unsigned int			m_uAtlasIndex;			// Absolute (real) Index on the SpriteSheet
	CCSpriteBatchNode       *m_pobBatchNode;        // Used batch node (weak reference)
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

	// whether or not it's parent is a CCSpriteBatchNode
	bool m_bUsesBatchNode;

	// texture
	CCRect m_obRect;
	CCRect m_obRectInPixels;
	bool   m_bRectRotated;

	// Offset Position (used by Zwoptex)
	CCPoint m_obOffsetPositionInPixels; // absolute
	CCPoint m_obUnflippedOffsetPositionFromCenter;

	// vertex coords, texture coords and color info
	ccV3F_C4B_T2F_Quad m_sQuad;

	// opacity and RGB protocol
	ccColor3B m_sColorUnmodified;
	bool m_bOpacityModifyRGB;

	// image is flipped
	bool m_bFlipX;
	bool m_bFlipY;
};
}//namespace   cocos2d 

#endif // __SPITE_NODE_CCSPRITE_H__
