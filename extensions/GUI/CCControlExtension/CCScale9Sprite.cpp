/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

http://www.cocos2d-x.org

Created by Jung Sang-Taik on 12. 3. 16..
Copyright (c) 2012 Neofect. All rights reserved.

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

#include "CCScale9Sprite.h"

NS_CC_EXT_BEGIN

enum positions
{
    pCentre = 0,
    pTop,
    pLeft,
    pRight,
    pBottom,
    pTopRight,
    pTopLeft,
    pBottomRight,
    pBottomLeft
};

CCScale9Sprite::CCScale9Sprite()
: m_insetLeft(0)
, m_insetTop(0)
, m_insetRight(0)
, m_insetBottom(0)
, m_bSpritesGenerated(false)
, m_bSpriteFrameRotated(false)
, m_positionsAreDirty(false)
, scale9Image(NULL)
, topLeft(NULL)
, top(NULL)
, topRight(NULL)
, left(NULL)
, centre(NULL)
, right(NULL)
, bottomLeft(NULL)
, bottom(NULL)
, bottomRight(NULL)
, m_bIsOpacityModifyRGB(false)
{

}

CCScale9Sprite::~CCScale9Sprite()
{
    CC_SAFE_RELEASE(topLeft);
    CC_SAFE_RELEASE(top);
    CC_SAFE_RELEASE(topRight);
    CC_SAFE_RELEASE(left);
    CC_SAFE_RELEASE(centre);
    CC_SAFE_RELEASE(right);
    CC_SAFE_RELEASE(bottomLeft);
    CC_SAFE_RELEASE(bottom);
    CC_SAFE_RELEASE(bottomRight);
    CC_SAFE_RELEASE(scale9Image);
}

bool CCScale9Sprite::init()
{
    return this->initWithBatchNode(NULL, CCRectZero, CCRectZero);
}

bool CCScale9Sprite::initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, CCRect capInsets)
{
    return this->initWithBatchNode(batchnode, rect, false, capInsets);
}

bool CCScale9Sprite::initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets)
{
    if(batchnode)
    {
        this->updateWithBatchNode(batchnode, rect, rotated, capInsets);
        this->setAnchorPoint(ccp(0.5f, 0.5f));
    }
    this->m_positionsAreDirty = true;
    
    return true;
}

#define    TRANSLATE_X(x, y, xtranslate) \
    x+=xtranslate;                       \

#define    TRANSLATE_Y(x, y, ytranslate) \
    y+=ytranslate;                       \

bool CCScale9Sprite::updateWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets)
{
    GLubyte opacity = getOpacity();
    ccColor3B color = getColor();

    // Release old sprites
    this->removeAllChildrenWithCleanup(true);

    CC_SAFE_RELEASE(this->centre);
    CC_SAFE_RELEASE(this->top);
    CC_SAFE_RELEASE(this->topLeft);
    CC_SAFE_RELEASE(this->topRight);
    CC_SAFE_RELEASE(this->left);
    CC_SAFE_RELEASE(this->right);
    CC_SAFE_RELEASE(this->bottomLeft);
    CC_SAFE_RELEASE(this->bottom);
    CC_SAFE_RELEASE(this->bottomRight);

    
    if(this->scale9Image != batchnode)
    {
        CC_SAFE_RELEASE(this->scale9Image);
        scale9Image = batchnode;
        CC_SAFE_RETAIN(scale9Image);
    }

    scale9Image->removeAllChildrenWithCleanup(true);

    m_capInsets = capInsets;
    
    // If there is no given rect
    if ( rect.equals(CCRectZero) )
    {
        // Get the texture size as original
        CCSize textureSize = scale9Image->getTextureAtlas()->getTexture()->getContentSize();
    
        rect = CCRectMake(0, 0, textureSize.width, textureSize.height);
    }
    
    // Set the given rect's size as original size
    m_spriteRect = rect;
    m_originalSize = rect.size;
    m_preferredSize = m_originalSize;
    m_capInsetsInternal = capInsets;
    
    float w = rect.size.width;
    float h = rect.size.height;

    // If there is no specified center region
    if ( m_capInsetsInternal.equals(CCRectZero) )
    {
        // CCLog("... cap insets not specified : using default cap insets ...");
        m_capInsetsInternal = CCRectMake(w/3, h/3, w/3, h/3);
    }

    float left_w = m_capInsetsInternal.origin.x;
    float center_w = m_capInsetsInternal.size.width;
    float right_w = rect.size.width - (left_w + center_w);

    float top_h = m_capInsetsInternal.origin.y;
    float center_h = m_capInsetsInternal.size.height;
    float bottom_h = rect.size.height - (top_h + center_h);

    // calculate rects

    // ... top row
    float x = 0.0;
    float y = 0.0;

    // top left
    CCRect lefttopbounds = CCRectMake(x, y,
                                      left_w, top_h);

    // top center
    TRANSLATE_X(x, y, left_w);
    CCRect centertopbounds = CCRectMake(x, y,
                                        center_w, top_h);
        
    // top right
    TRANSLATE_X(x, y, center_w);
    CCRect righttopbounds = CCRectMake(x, y,
                                       right_w, top_h);

    // ... center row
    x = 0.0;
    y = 0.0;
    TRANSLATE_Y(x, y, top_h);

    // center left
    CCRect leftcenterbounds = CCRectMake(x, y,
                                         left_w, center_h);

    // center center
    TRANSLATE_X(x, y, left_w);
    CCRect centerbounds = CCRectMake(x, y,
                                     center_w, center_h);

    // center right
    TRANSLATE_X(x, y, center_w);
    CCRect rightcenterbounds = CCRectMake(x, y,
                                          right_w, center_h);

    // ... bottom row
    x = 0.0;
    y = 0.0;
    TRANSLATE_Y(x, y, top_h);
    TRANSLATE_Y(x, y, center_h);

    // bottom left
    CCRect leftbottombounds = CCRectMake(x, y,
                                         left_w, bottom_h);

    // bottom center
    TRANSLATE_X(x, y, left_w);
    CCRect centerbottombounds = CCRectMake(x, y,
                                           center_w, bottom_h);

    // bottom right
    TRANSLATE_X(x, y, center_w);
    CCRect rightbottombounds = CCRectMake(x, y,
                                          right_w, bottom_h);

    if (!rotated) {
        // CCLog("!rotated");

        CCAffineTransform t = CCAffineTransformMakeIdentity();
        t = CCAffineTransformTranslate(t, rect.origin.x, rect.origin.y);

        centerbounds = CCRectApplyAffineTransform(centerbounds, t);
        rightbottombounds = CCRectApplyAffineTransform(rightbottombounds, t);
        leftbottombounds = CCRectApplyAffineTransform(leftbottombounds, t);
        righttopbounds = CCRectApplyAffineTransform(righttopbounds, t);
        lefttopbounds = CCRectApplyAffineTransform(lefttopbounds, t);
        rightcenterbounds = CCRectApplyAffineTransform(rightcenterbounds, t);
        leftcenterbounds = CCRectApplyAffineTransform(leftcenterbounds, t);
        centerbottombounds = CCRectApplyAffineTransform(centerbottombounds, t);
        centertopbounds = CCRectApplyAffineTransform(centertopbounds, t);

        // Centre
        centre = new CCSprite();
        centre->initWithTexture(scale9Image->getTexture(), centerbounds);
        scale9Image->addChild(centre, 0, pCentre);
        
        // Top
        top = new CCSprite();
        top->initWithTexture(scale9Image->getTexture(), centertopbounds);
        scale9Image->addChild(top, 1, pTop);
        
        // Bottom
        bottom = new CCSprite();
        bottom->initWithTexture(scale9Image->getTexture(), centerbottombounds);
        scale9Image->addChild(bottom, 1, pBottom);
        
        // Left
        left = new CCSprite();
        left->initWithTexture(scale9Image->getTexture(), leftcenterbounds);
        scale9Image->addChild(left, 1, pLeft);
        
        // Right
        right = new CCSprite();
        right->initWithTexture(scale9Image->getTexture(), rightcenterbounds);
        scale9Image->addChild(right, 1, pRight);
        
        // Top left
        topLeft = new CCSprite();
        topLeft->initWithTexture(scale9Image->getTexture(), lefttopbounds);
        scale9Image->addChild(topLeft, 2, pTopLeft);
        
        // Top right
        topRight = new CCSprite();
        topRight->initWithTexture(scale9Image->getTexture(), righttopbounds);
        scale9Image->addChild(topRight, 2, pTopRight);
        
        // Bottom left
        bottomLeft = new CCSprite();
        bottomLeft->initWithTexture(scale9Image->getTexture(), leftbottombounds);
        scale9Image->addChild(bottomLeft, 2, pBottomLeft);
        
        // Bottom right
        bottomRight = new CCSprite();
        bottomRight->initWithTexture(scale9Image->getTexture(), rightbottombounds);
        scale9Image->addChild(bottomRight, 2, pBottomRight);
    } else {
        // set up transformation of coordinates
        // to handle the case where the sprite is stored rotated
        // in the spritesheet
        // CCLog("rotated");

        CCAffineTransform t = CCAffineTransformMakeIdentity();

        CCRect rotatedcenterbounds = centerbounds;
        CCRect rotatedrightbottombounds = rightbottombounds;
        CCRect rotatedleftbottombounds = leftbottombounds;
        CCRect rotatedrighttopbounds = righttopbounds;
        CCRect rotatedlefttopbounds = lefttopbounds;
        CCRect rotatedrightcenterbounds = rightcenterbounds;
        CCRect rotatedleftcenterbounds = leftcenterbounds;
        CCRect rotatedcenterbottombounds = centerbottombounds;
        CCRect rotatedcentertopbounds = centertopbounds;
        
        t = CCAffineTransformTranslate(t, rect.size.height+rect.origin.x, rect.origin.y);
        t = CCAffineTransformRotate(t, 1.57079633f);
        
        centerbounds = CCRectApplyAffineTransform(centerbounds, t);
        rightbottombounds = CCRectApplyAffineTransform(rightbottombounds, t);
        leftbottombounds = CCRectApplyAffineTransform(leftbottombounds, t);
        righttopbounds = CCRectApplyAffineTransform(righttopbounds, t);
        lefttopbounds = CCRectApplyAffineTransform(lefttopbounds, t);
        rightcenterbounds = CCRectApplyAffineTransform(rightcenterbounds, t);
        leftcenterbounds = CCRectApplyAffineTransform(leftcenterbounds, t);
        centerbottombounds = CCRectApplyAffineTransform(centerbottombounds, t);
        centertopbounds = CCRectApplyAffineTransform(centertopbounds, t);

        rotatedcenterbounds.origin = centerbounds.origin;
        rotatedrightbottombounds.origin = rightbottombounds.origin;
        rotatedleftbottombounds.origin = leftbottombounds.origin;
        rotatedrighttopbounds.origin = righttopbounds.origin;
        rotatedlefttopbounds.origin = lefttopbounds.origin;
        rotatedrightcenterbounds.origin = rightcenterbounds.origin;
        rotatedleftcenterbounds.origin = leftcenterbounds.origin;
        rotatedcenterbottombounds.origin = centerbottombounds.origin;
        rotatedcentertopbounds.origin = centertopbounds.origin;

        // Centre
        centre = new CCSprite();
        centre->initWithTexture(scale9Image->getTexture(), rotatedcenterbounds, true);
        scale9Image->addChild(centre, 0, pCentre);
        
        // Top
        top = new CCSprite();
        top->initWithTexture(scale9Image->getTexture(), rotatedcentertopbounds, true);
        scale9Image->addChild(top, 1, pTop);
        
        // Bottom
        bottom = new CCSprite();
        bottom->initWithTexture(scale9Image->getTexture(), rotatedcenterbottombounds, true);
        scale9Image->addChild(bottom, 1, pBottom);
        
        // Left
        left = new CCSprite();
        left->initWithTexture(scale9Image->getTexture(), rotatedleftcenterbounds, true);
        scale9Image->addChild(left, 1, pLeft);
        
        // Right
        right = new CCSprite();
        right->initWithTexture(scale9Image->getTexture(), rotatedrightcenterbounds, true);
        scale9Image->addChild(right, 1, pRight);
        
        // Top left
        topLeft = new CCSprite();
        topLeft->initWithTexture(scale9Image->getTexture(), rotatedlefttopbounds, true);
        scale9Image->addChild(topLeft, 2, pTopLeft);
        
        // Top right
        topRight = new CCSprite();
        topRight->initWithTexture(scale9Image->getTexture(), rotatedrighttopbounds, true);
        scale9Image->addChild(topRight, 2, pTopRight);
        
        // Bottom left
        bottomLeft = new CCSprite();
        bottomLeft->initWithTexture(scale9Image->getTexture(), rotatedleftbottombounds, true);
        scale9Image->addChild(bottomLeft, 2, pBottomLeft);
        
        // Bottom right
        bottomRight = new CCSprite();
        bottomRight->initWithTexture(scale9Image->getTexture(), rotatedrightbottombounds, true);
        scale9Image->addChild(bottomRight, 2, pBottomRight);
    }

    this->setContentSize(rect.size);
    this->addChild(scale9Image);
    
    if (m_bSpritesGenerated)
        {
            // Restore color and opacity
            this->setOpacity(opacity);
            this->setColor(color);
        }
    m_bSpritesGenerated = true;

    return true;
}

void CCScale9Sprite::setContentSize(const CCSize &size)
{
    CCNode::setContentSize(size);
    this->m_positionsAreDirty = true;
}

void CCScale9Sprite::updatePositions()
{
    // Check that instances are non-NULL
    if(!((topLeft) &&
         (topRight) &&
         (bottomRight) &&
         (bottomLeft) &&
         (centre))) {
        // if any of the above sprites are NULL, return
        return;
    }

    CCSize size = this->m_obContentSize;

    float sizableWidth = size.width - topLeft->getContentSize().width - topRight->getContentSize().width;
    float sizableHeight = size.height - topLeft->getContentSize().height - bottomRight->getContentSize().height;
    
    float horizontalScale = sizableWidth/centre->getContentSize().width;
    float verticalScale = sizableHeight/centre->getContentSize().height;

    centre->setScaleX(horizontalScale);
    centre->setScaleY(verticalScale);

    float rescaledWidth = centre->getContentSize().width * horizontalScale;
    float rescaledHeight = centre->getContentSize().height * verticalScale;

    float leftWidth = bottomLeft->getContentSize().width;
    float bottomHeight = bottomLeft->getContentSize().height;

    bottomLeft->setAnchorPoint(ccp(0,0));
    bottomRight->setAnchorPoint(ccp(0,0));
    topLeft->setAnchorPoint(ccp(0,0));
    topRight->setAnchorPoint(ccp(0,0));
    left->setAnchorPoint(ccp(0,0));
    right->setAnchorPoint(ccp(0,0));
    top->setAnchorPoint(ccp(0,0));
    bottom->setAnchorPoint(ccp(0,0));
    centre->setAnchorPoint(ccp(0,0));

    // Position corners
    bottomLeft->setPosition(ccp(0,0));
    bottomRight->setPosition(ccp(leftWidth+rescaledWidth,0));
    topLeft->setPosition(ccp(0, bottomHeight+rescaledHeight));
    topRight->setPosition(ccp(leftWidth+rescaledWidth, bottomHeight+rescaledHeight));

    // Scale and position borders
    left->setPosition(ccp(0, bottomHeight));
    left->setScaleY(verticalScale);
    right->setPosition(ccp(leftWidth+rescaledWidth,bottomHeight));
    right->setScaleY(verticalScale);
    bottom->setPosition(ccp(leftWidth,0));
    bottom->setScaleX(horizontalScale);
    top->setPosition(ccp(leftWidth,bottomHeight+rescaledHeight));
    top->setScaleX(horizontalScale);

    // Position centre
    centre->setPosition(ccp(leftWidth, bottomHeight));
}

bool CCScale9Sprite::initWithFile(const char* file, CCRect rect,  CCRect capInsets)
{
    CCAssert(file != NULL, "Invalid file for sprite");
    
    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::create(file, 9);
    bool pReturn = this->initWithBatchNode(batchnode, rect, capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::create(const char* file, CCRect rect,  CCRect capInsets)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithFile(file, rect, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9Sprite::initWithFile(const char* file, CCRect rect)
{
    CCAssert(file != NULL, "Invalid file for sprite");
    bool pReturn = this->initWithFile(file, rect, CCRectZero);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::create(const char* file, CCRect rect)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithFile(file, rect) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}


bool CCScale9Sprite::initWithFile(CCRect capInsets, const char* file)
{
    bool pReturn = this->initWithFile(file, CCRectZero, capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::create(CCRect capInsets, const char* file)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithFile(capInsets, file) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9Sprite::initWithFile(const char* file)
{
    bool pReturn = this->initWithFile(file, CCRectZero);
    return pReturn;
    
}

CCScale9Sprite* CCScale9Sprite::create(const char* file)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithFile(file) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9Sprite::initWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets)
{
    CCTexture2D* texture = spriteFrame->getTexture();
    CCAssert(texture != NULL, "CCTexture must be not nil");

    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::createWithTexture(texture, 9);
    CCAssert(batchnode != NULL, "CCSpriteBatchNode must be not nil");

    bool pReturn = this->initWithBatchNode(batchnode, spriteFrame->getRect(), spriteFrame->isRotated(), capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::createWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}
bool CCScale9Sprite::initWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
    CCAssert(spriteFrame != NULL, "Invalid spriteFrame for sprite");
    bool pReturn = this->initWithSpriteFrame(spriteFrame, CCRectZero);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::createWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9Sprite::initWithSpriteFrameName(const char* spriteFrameName, CCRect capInsets)
{
    CCAssert((CCSpriteFrameCache::sharedSpriteFrameCache()) != NULL, "sharedSpriteFrameCache must be non-NULL");

    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
    CCAssert(frame != NULL, "CCSpriteFrame must be non-NULL");

    if (NULL == frame) return false;

    bool pReturn = this->initWithSpriteFrame(frame, capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::createWithSpriteFrameName(const char* spriteFrameName, CCRect capInsets)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9Sprite::initWithSpriteFrameName(const char* spriteFrameName)
{
    bool pReturn = this->initWithSpriteFrameName(spriteFrameName, CCRectZero);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::createWithSpriteFrameName(const char* spriteFrameName)
{
    CCAssert(spriteFrameName != NULL, "spriteFrameName must be non-NULL");

    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);

    CCLog("Could not allocate CCScale9Sprite()");
    return NULL;
    
}

CCScale9Sprite* CCScale9Sprite::resizableSpriteWithCapInsets(CCRect capInsets)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithBatchNode(scale9Image, m_spriteRect, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

CCScale9Sprite* CCScale9Sprite::create()
{ 
    CCScale9Sprite *pReturn = new CCScale9Sprite();
    if (pReturn)
    { 
        pReturn->autorelease();   
        return pReturn;
    } 
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

/** sets the opacity.
 @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
 Values goes from 0 to 255, where 255 means fully opaque.
 */

void CCScale9Sprite::setPreferredSize(CCSize preferedSize)
{
    this->setContentSize(preferedSize);
    this->m_preferredSize = preferedSize;
}

CCSize CCScale9Sprite::getPreferredSize()
{
    return this->m_preferredSize;
}

void CCScale9Sprite::setCapInsets(CCRect capInsets)
{
    CCSize contentSize = this->m_obContentSize;
    this->updateWithBatchNode(this->scale9Image, this->m_spriteRect, m_bSpriteFrameRotated, capInsets);
    this->setContentSize(contentSize);
}

CCRect CCScale9Sprite::getCapInsets()
{
    return m_capInsets;
}

void CCScale9Sprite::updateCapInset()
{
    CCRect insets;
    if (this->m_insetLeft == 0 && this->m_insetTop == 0 && this->m_insetRight == 0 && this->m_insetBottom == 0)
    {
        insets = CCRectZero;
    }
    else
    {
        if (m_bSpriteFrameRotated)
        {
            insets = CCRectMake(m_insetBottom,
                m_insetLeft,
                m_spriteRect.size.width-m_insetRight-m_insetLeft,
                m_spriteRect.size.height-m_insetTop-m_insetBottom);
        }
        else
        {
            insets = CCRectMake(m_insetLeft,
                m_insetTop,
                m_spriteRect.size.width-m_insetLeft-m_insetRight,
                m_spriteRect.size.height-m_insetTop-m_insetBottom);
        }
    }
    this->setCapInsets(insets);
}

void CCScale9Sprite::setOpacityModifyRGB(bool var)
{
    m_bIsOpacityModifyRGB = var;
    if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(scale9Image->getChildren(), child)
        {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
            }
        }
    }
}
bool CCScale9Sprite::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}

void CCScale9Sprite::setSpriteFrame(CCSpriteFrame * spriteFrame)
{
    CCSpriteBatchNode * batchnode = CCSpriteBatchNode::createWithTexture(spriteFrame->getTexture(), 9);
    this->updateWithBatchNode(batchnode, spriteFrame->getRect(), spriteFrame->isRotated(), CCRectZero);

    // Reset insets
    this->m_insetLeft = 0;
    this->m_insetTop = 0;
    this->m_insetRight = 0;
    this->m_insetBottom = 0;
}

float CCScale9Sprite::getInsetLeft()
{
    return this->m_insetLeft;
}

float CCScale9Sprite::getInsetTop()
{
    return this->m_insetTop;
}

float CCScale9Sprite::getInsetRight()
{
    return this->m_insetRight;
}

float CCScale9Sprite::getInsetBottom()
{
    return this->m_insetBottom;
}

void CCScale9Sprite::setInsetLeft(float insetLeft)
{
    this->m_insetLeft = insetLeft;
    this->updateCapInset();
}

void CCScale9Sprite::setInsetTop(float insetTop)
{
    this->m_insetTop = insetTop;
    this->updateCapInset();
}

void CCScale9Sprite::setInsetRight(float insetRight)
{
    this->m_insetRight = insetRight;
    this->updateCapInset();
}

void CCScale9Sprite::setInsetBottom(float insetBottom)
{
    this->m_insetBottom = insetBottom;
    this->updateCapInset();
}

void CCScale9Sprite::visit()
{
    if(this->m_positionsAreDirty)
    {
        this->updatePositions();
        this->m_positionsAreDirty = false;
    }
    CCNode::visit();
}

NS_CC_EXT_END
