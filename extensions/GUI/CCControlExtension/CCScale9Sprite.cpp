//
//  CCScale9Sprite.cpp
//  PlantCaring
//
//  Created by Jung Sang-Taik on 12. 3. 16..
//  Copyright (c) 2012 Neofect. All rights reserved.
//

#include "CCScale9Sprite.h"
#include "sprite_nodes/CCSpriteBatchNode.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCSpriteFrameCache.h"
#include "sprite_nodes/CCSprite.h"
#include "support/CCPointExtension.h"

NS_CC_EXT_BEGIN

CCScale9Sprite::CCScale9Sprite()
: m_insetLeft(0)
, m_insetTop(0)
, m_insetRight(0)
, m_insetBottom(0)
{

}

CCScale9Sprite::~CCScale9Sprite()
{

}

bool CCScale9Sprite::init()
{
    return this->initWithBatchNode(NULL, CCRectZero, CCRectZero);
}

bool CCScale9Sprite::initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, CCRect capInsets)
{
    if(batchnode)
    {
        this->updateWithBatchNode(batchnode, rect, capInsets);
        this->setAnchorPoint(ccp(0.5f, 0.5f));
    }
    this->m_positionsAreDirty = true;
    
    return true;
}

bool CCScale9Sprite::updateWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, CCRect capInsets)
{
    // Release old sprites
    this->removeAllChildrenWithCleanup(true);

    // TODO Is this needed?
    /*
    if(this->topLeft != NULL)
    {
        CC_SAFE_RELEASE(this->topLeft);
        CC_SAFE_RELEASE(this->top);
        CC_SAFE_RELEASE(this->topRight);
        CC_SAFE_RELEASE(this->left);
        CC_SAFE_RELEASE(this->centre);
        CC_SAFE_RELEASE(this->right);
        CC_SAFE_RELEASE(this->bottomLeft);
        CC_SAFE_RELEASE(this->bottom);
        CC_SAFE_RELEASE(this->bottomRight);
    }
    */
    
    if(this->scale9Image != batchnode)
    {
        // TODO Is this needed?
        /*
        if(this->scale9Image != NULL)
        {
            CC_SAFE_RELEASE(this->scale9Image);
        }
        */
        scale9Image = batchnode; // TODO No retain on purpose?
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
    
    // If there is no specified center region
    if ( m_capInsetsInternal.equals(CCRectZero) )
    {
        // Apply the 3x3 grid format
        m_capInsetsInternal = CCRectMake(
                                rect.origin.x + m_originalSize.width / 3, 
                                rect.origin.y + m_originalSize.height / 3, 
                                m_originalSize.width / 3,
                                m_originalSize.height / 3);
    }
    
    // Get the image edges
    float l = rect.origin.x;
    float t = rect.origin.y;
    float h = rect.size.height;
    float w = rect.size.width;

    //
    // Set up the image
    //
    
    // Centre
    centre = CCSprite::createWithTexture(scale9Image->getTexture(), m_capInsetsInternal);
    scale9Image->addChild(centre, 0, pCentre);
    
    // Top
    top = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x,
                                                                t,
                                                                m_capInsetsInternal.size.width,
                                                                m_capInsetsInternal.origin.y - t));
    scale9Image->addChild(top, 1, pTop);
    
    // Bottom
    bottom = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake( m_capInsetsInternal.origin.x,
                                                                   m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                   m_capInsetsInternal.size.width,
                                                                   h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height) ));
    scale9Image->addChild(bottom, 1, pBottom);
    
    // Left
    left = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                 l,
                                                                 m_capInsetsInternal.origin.y,
                                                                 m_capInsetsInternal.origin.x - l,
                                                                 m_capInsetsInternal.size.height) );
    scale9Image->addChild(left, 1, pLeft);
    
    // Right
    right = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                  m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                  m_capInsetsInternal.origin.y,
                                                                  w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                  m_capInsetsInternal.size.height));
    scale9Image->addChild(right, 1, pRight);
    
    // Top left
    topLeft = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                    l,
                                                                    t,
                                                                    m_capInsetsInternal.origin.x - l,
                                                                    m_capInsetsInternal.origin.y - t));

    scale9Image->addChild(topLeft, 2, pTopLeft);
    
    // Top right
    topRight = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                     m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                     t,
                                                                     w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                     m_capInsetsInternal.origin.y - t));
    
    scale9Image->addChild(topRight, 2, pTopRight);
    
    // Bottom left
    bottomLeft = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                       l,
                                                                       m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                       m_capInsetsInternal.origin.x - l,
                                                                       h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)) );
    scale9Image->addChild(bottomLeft, 2, pBottomLeft);
    
    // Bottom right
    bottomRight = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                        m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                        m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                        w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                        h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)) );
    scale9Image->addChild(bottomRight, 2, pBottomRight);
    
    
    this->setContentSize(rect.size);
    this->addChild(scale9Image);
    
    return true;
}

void CCScale9Sprite::setContentSize(const CCSize &size)
{
    CCNode::setContentSize(size);
    this->m_positionsAreDirty = true;
}

void CCScale9Sprite::updatePositions()
{
    CCSize size = this->m_tContentSize;

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

CCScale9Sprite* CCScale9Sprite::spriteWithFile(const char* file, CCRect rect,  CCRect capInsets)
{
    return CCScale9Sprite::create(file, rect, capInsets);
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
    bool pReturn = this->initWithFile(file, rect, CCRectZero);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithFile(const char* file, CCRect rect)
{
    return CCScale9Sprite::create(file, rect);
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

CCScale9Sprite* CCScale9Sprite::spriteWithFile(CCRect capInsets, const char* file)
{
    return CCScale9Sprite::create(capInsets, file);
}

CCScale9Sprite* CCScale9Sprite::create(CCRect capInsets, const char* file)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithFile(file, capInsets) )
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

CCScale9Sprite* CCScale9Sprite::spriteWithFile(const char* file)
{
    return CCScale9Sprite::create(file);
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
    CCAssert(spriteFrame != NULL, "Sprite frame must be not nil");

    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::createWithTexture(spriteFrame->getTexture(), 9);
    bool pReturn = this->initWithBatchNode(batchnode, spriteFrame->getRect(), capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets)
{
    return CCScale9Sprite::createWithSpriteFrame(spriteFrame, capInsets);
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
    bool pReturn = this->initWithSpriteFrame(spriteFrame, CCRectZero);
    return pReturn;
}


CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
    return CCScale9Sprite::createWithSpriteFrame(spriteFrame);
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
    CCAssert(spriteFrameName != NULL, "Invalid spriteFrameName for sprite");

    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
    bool pReturn = this->initWithSpriteFrame(frame, capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrameName(const char* spriteFrameName, CCRect capInsets)
{
    return CCScale9Sprite::createWithSpriteFrameName(spriteFrameName, capInsets);
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

CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrameName(const char* spriteFrameName)
{
    return CCScale9Sprite::createWithSpriteFrameName(spriteFrameName);
}

CCScale9Sprite* CCScale9Sprite::createWithSpriteFrameName(const char* spriteFrameName)
{
    CCScale9Sprite* pReturn = new CCScale9Sprite();
    if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
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

CCScale9Sprite* CCScale9Sprite::node()
{
    return CCScale9Sprite::create();
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


//LabelBMFont - CCRGBAProtocol protocol
void CCScale9Sprite::setColor(const ccColor3B& color3)
{
    m_tColor = color3;
    if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(scale9Image->getChildren(), child)
        {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
            if (pNode)
            {
                pNode->setColor(m_tColor);
            }
        }
    }
}
const ccColor3B& CCScale9Sprite::getColor(void)
{
    return m_tColor;
}

void CCScale9Sprite::setOpacity(GLubyte var)
{
    m_cOpacity = var;

    if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(scale9Image->getChildren(), child)
        {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setOpacity(m_cOpacity);
            }
            //CCNode* pNode = (CCNode*) child;
            //if (pNode)
            //{
            //    CCRGBAProtocol *pRGBAProtocol = (CCRGBAProtocol *)pNode;
            //    if (pRGBAProtocol)
            //    {
            //        pRGBAProtocol->setOpacity(m_cOpacity);
            //    }
            //}
        }
    }
}

/** sets the opacity.
 @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
 Values goes from 0 to 255, where 255 means fully opaque.
 */
GLubyte CCScale9Sprite::getOpacity()
{
    return m_cOpacity;
}

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
    CCSize contentSize = this->m_tContentSize;
    this->updateWithBatchNode(this->scale9Image, this->m_spriteRect, capInsets);
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
        insets = CCRectMake(this->m_insetLeft,
                            this->m_insetTop,
                            this->m_spriteRect.size.width-this->m_insetLeft-this->m_insetRight,
                            this->m_spriteRect.size.height-this->m_insetTop-this->m_insetBottom);
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
            //CCNode* pNode = (CCNode*) child;
            //if (pNode)
            //{
            //    CCRGBAProtocol *pRGBAProtocol = (CCRGBAProtocol *)pNode;
            //    if (pRGBAProtocol)
            //    {
            //        pRGBAProtocol->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
            //    }
            //}
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
    this->updateWithBatchNode(batchnode, spriteFrame->getRect(), CCRectZero);

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
