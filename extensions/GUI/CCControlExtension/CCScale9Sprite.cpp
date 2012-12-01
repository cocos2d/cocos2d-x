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
, m_cOpacity(0)
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

bool CCScale9Sprite::updateWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets)
{
    GLubyte opacity = m_cOpacity;
    ccColor3B color = m_tColor;

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
    
    // Get the image edges
    float l = rect.origin.x;
    float t = rect.origin.y;
    float h = rect.size.height;
    float w = rect.size.width;

    // If there is no specified center region
    if ( m_capInsetsInternal.equals(CCRectZero) )
    {
        // Apply the 3x3 grid format
        if (rotated)
        {
            m_capInsetsInternal = CCRectMake(l+h/3, t+w/3, w/3, h/3);
        }
        else
        {
            m_capInsetsInternal = CCRectMake(l+w/3, t+h/3, w/3, h/3);
        }
    }

    //
    // Set up the image
    //
    if (rotated)
    {
        // Sprite frame is rotated

        // Centre
        centre      = new CCSprite();
        centre->initWithTexture(scale9Image->getTexture(), m_capInsetsInternal, true);
        scale9Image->addChild(centre, 0, pCentre);

        // Bottom
        bottom         =  new CCSprite();
        bottom->initWithTexture(scale9Image->getTexture(), CCRectMake(l,
                                                            m_capInsetsInternal.origin.y,
                                                            m_capInsetsInternal.size.width,
                                                            m_capInsetsInternal.origin.x - l),
                                                            rotated
                                                            );
        scale9Image->addChild(bottom, 1, pBottom);

        // Top
        top      = new CCSprite();
        top->initWithTexture(scale9Image->getTexture(),CCRectMake(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                                                             m_capInsetsInternal.origin.y,
                                                             m_capInsetsInternal.size.width,
                                                             h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                                                                rotated
                                                                );
        scale9Image->addChild(top, 1, pTop);

        // Right
        right        = new CCSprite();
        right->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x,
                                     m_capInsetsInternal.origin.y+m_capInsetsInternal.size.width,
                                     w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                                     m_capInsetsInternal.size.height),
                                    rotated
                                    );
        scale9Image->addChild(right, 1, pRight);

        // Left
        left       = new CCSprite();
        left->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x,
                                                                     t,
                                                                     m_capInsetsInternal.origin.y - t,
                                                                     m_capInsetsInternal.size.height),
                                                                    rotated
                                                                );
        scale9Image->addChild(left ,1, pLeft);

        // Top right
        topRight     = new CCSprite();
        topRight->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                                                                         m_capInsetsInternal.origin.y + m_capInsetsInternal.size.width,
                                                                         w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                                                                         h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                                                                        rotated
                                                                        );
        scale9Image->addChild(topRight ,2 ,pTopRight);

        // Top left
        topLeft    = new CCSprite();
        topLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                                                                         t,
                                                                         m_capInsetsInternal.origin.y - t,
                                                                         h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                                                                        rotated
                                                                        );
        scale9Image->addChild(topLeft, 2, pTopLeft);

        // Bottom right
        bottomRight  = new CCSprite();
        bottomRight->initWithTexture(scale9Image->getTexture(),CCRectMake(l,
                                             m_capInsetsInternal.origin.y + m_capInsetsInternal.size.width,
                                             w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                                             m_capInsetsInternal.origin.x - l),
                                            rotated
                                            );
        scale9Image->addChild(bottomRight, 2, pBottomRight);

        // Bottom left
        bottomLeft     = new CCSprite();
        bottomLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(l,
                                                                 t,
                                                                 m_capInsetsInternal.origin.y - t,
                                                                 m_capInsetsInternal.origin.x - l),
                                                                    rotated
                                                                );
        scale9Image->addChild(bottomLeft, 2, pBottomLeft);
    }
    else
    {
        // Sprite frame is not rotated
        // Centre
        centre = new CCSprite();
        centre->initWithTexture(scale9Image->getTexture(), m_capInsetsInternal, rotated);
        scale9Image->addChild(centre, 0, pCentre);
        
        // Top
        top = new CCSprite();
        top->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x,
                                                                    t,
                                                                    m_capInsetsInternal.size.width,
                                                                    m_capInsetsInternal.origin.y - t),
                                                                    rotated
                                                                   );
        scale9Image->addChild(top, 1, pTop);
        
        // Bottom
        bottom = new CCSprite();
        bottom->initWithTexture(scale9Image->getTexture(), CCRectMake( m_capInsetsInternal.origin.x,
                                                                       m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                       m_capInsetsInternal.size.width,
                                                                       h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                                                                        rotated);
        scale9Image->addChild(bottom, 1, pBottom);
        
        // Left
        left = new CCSprite();
        left->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                     l,
                                                                     m_capInsetsInternal.origin.y,
                                                                     m_capInsetsInternal.origin.x - l,
                                                                     m_capInsetsInternal.size.height),
                                                                     rotated);
        scale9Image->addChild(left, 1, pLeft);
        
        // Right
        right = new CCSprite();
        right->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                      m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                      m_capInsetsInternal.origin.y,
                                                                      w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                      m_capInsetsInternal.size.height),
                                                                      rotated);
        scale9Image->addChild(right, 1, pRight);
        
        // Top left
        topLeft = new CCSprite();
        topLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                        l,
                                                                        t,
                                                                        m_capInsetsInternal.origin.x - l,
                                                                        m_capInsetsInternal.origin.y - t),
                                                                        rotated);

        scale9Image->addChild(topLeft, 2, pTopLeft);
        
        // Top right
        topRight = new CCSprite();
        topRight->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                         m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                         t,
                                                                         w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                         m_capInsetsInternal.origin.y - t),
                                                                         rotated);
        
        scale9Image->addChild(topRight, 2, pTopRight);
        
        // Bottom left
        bottomLeft = new CCSprite();
        bottomLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                           l,
                                                                           m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                           m_capInsetsInternal.origin.x - l,
                                                                           h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                                                                           rotated);
        scale9Image->addChild(bottomLeft, 2, pBottomLeft);
        
        // Bottom right
        bottomRight = new CCSprite();
        bottomRight->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                            m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                            m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                            w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                            h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                                                                            rotated);
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
    CCAssert(file != NULL, "Invalid file for sprite");
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
    bool pReturn = this->initWithBatchNode(batchnode, spriteFrame->getRect(), spriteFrame->isRotated(), capInsets);
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
    CCAssert(spriteFrame != NULL, "Invalid spriteFrame for sprite");
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

ccColor3B CCScale9Sprite::getColor(void)
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
            insets = CCRectMake(m_spriteRect.origin.x + m_insetBottom,
                m_spriteRect.origin.y + m_insetLeft,
                m_spriteRect.size.width-m_insetRight-m_insetLeft,
                m_spriteRect.size.height-m_insetTop-m_insetBottom);
        }
        else
        {
            insets = CCRectMake(m_spriteRect.origin.x + m_insetLeft,
                m_spriteRect.origin.y + m_insetTop,
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
