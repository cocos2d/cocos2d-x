/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#include "CCSpriteBatchNode.h"
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "ccConfig.h"
#include "CCSprite.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "textures/CCTextureCache.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCGLProgram.h"
#include "CCDirector.h"
#include "support/CCPointExtension.h"
#include "cocoa/CCGeometry.h"
#include "textures/CCTexture2D.h"
#include "cocoa/CCAffineTransform.h"
#include "support/TransformUtils.h"
#include "support/CCProfiling.h"
#include "platform/CCImage.h"
// external
#include "kazmath/GL/matrix.h"
#include <string.h>

using namespace std;

NS_CC_BEGIN

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

CCSprite* CCSprite::createWithTexture(CCTexture2D *pTexture)
{
    CCSprite *pobSprite = new CCSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCSprite* CCSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    CCSprite *pobSprite = new CCSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCSprite* CCSprite::create(const char *pszFileName)
{
    CCSprite *pobSprite = new CCSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCSprite* CCSprite::create(const char *pszFileName, const CCRect& rect)
{
    CCSprite *pobSprite = new CCSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCSprite* CCSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCSprite *pobSprite = new CCSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCSprite* CCSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

CCSprite* CCSprite::create()
{
    CCSprite *pSprite = new CCSprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

bool CCSprite::init(void)
{
    return initWithTexture(NULL, CCRectZero);
}

// designated initializer
bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated)
{
    if (CCNodeRGBA::init())
    {
        m_pobBatchNode = NULL;
        
        m_bRecursiveDirty = false;
        setDirty(false);
        
        m_bOpacityModifyRGB = true;
        
        m_sBlendFunc.src = CC_BLEND_SRC;
        m_sBlendFunc.dst = CC_BLEND_DST;
        
        m_bFlipX = m_bFlipY = false;
        
        // default transform anchor: center
        setAnchorPoint(ccp(0.5f, 0.5f));
        
        // zwoptex default values
        m_obOffsetPosition = CCPointZero;
        
        m_bHasChildren = false;
        
        // clean the Quad
        memset(&m_sQuad, 0, sizeof(m_sQuad));
        
        // Atlas: Color
        ccColor4B tmpColor = { 255, 255, 255, 255 };
        m_sQuad.bl.colors = tmpColor;
        m_sQuad.br.colors = tmpColor;
        m_sQuad.tl.colors = tmpColor;
        m_sQuad.tr.colors = tmpColor;

        // shader program
        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
        
        // update texture (calls updateBlendFunc)
        setTexture(pTexture);
        setTextureRect(rect, rotated, rect.size);
        
        // by default use "Self Render".
        // if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
        setBatchNode(NULL);
        
        return true;
    }
    else
    {
        return false;
    }
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    return initWithTexture(pTexture, rect, false);
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture)
{
    CCAssert(pTexture != NULL, "Invalid texture for sprite");

    CCRect rect = CCRectZero;
    rect.size = pTexture->getContentSize();
    
    return initWithTexture(pTexture, rect);
}

bool CCSprite::initWithFile(const char *pszFilename)
{
    CCAssert(pszFilename != NULL, "Invalid filename for sprite");

    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
    if (pTexture)
    {
        CCRect rect = CCRectZero;
        rect.size = pTexture->getContentSize();
        return initWithTexture(pTexture, rect);
    }

    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite than a crashed program
    // this->release(); 
    return false;
}

bool CCSprite::initWithFile(const char *pszFilename, const CCRect& rect)
{
    CCAssert(pszFilename != NULL, "");

    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
    if (pTexture)
    {
        return initWithTexture(pTexture, rect);
    }

    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite than a crashed program
    // this->release(); 
    return false;
}

bool CCSprite::initWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCAssert(pSpriteFrame != NULL, "");

    bool bRet = initWithTexture(pSpriteFrame->getTexture(), pSpriteFrame->getRect());
    setDisplayFrame(pSpriteFrame);

    return bRet;
}

bool CCSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCAssert(pszSpriteFrameName != NULL, "");

    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    return initWithSpriteFrame(pFrame);
}

// XXX: deprecated
/*
CCSprite* CCSprite::initWithCGImage(CGImageRef pImage)
{
    // todo
    // because it is deprecated, so we do not implement it

    return NULL;
}
*/

/*
CCSprite* CCSprite::initWithCGImage(CGImageRef pImage, const char *pszKey)
{
    CCAssert(pImage != NULL);

    // XXX: possible bug. See issue #349. New API should be added
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addCGImage(pImage, pszKey);

    const CCSize& size = pTexture->getContentSize();
    CCRect rect = CCRectMake(0 ,0, size.width, size.height);

    return initWithTexture(texture, rect);
}
*/

CCSprite::CCSprite(void)
: m_bShouldBeHidden(false),
m_pobTexture(NULL)
{
}

CCSprite::~CCSprite(void)
{
    CC_SAFE_RELEASE(m_pobTexture);
}

void CCSprite::setTextureRect(const CCRect& rect)
{
    setTextureRect(rect, false, rect.size);
}


void CCSprite::setTextureRect(const CCRect& rect, bool rotated, const CCSize& untrimmedSize)
{
    m_bRectRotated = rotated;

    setContentSize(untrimmedSize);
    setVertexRect(rect);
    setTextureCoords(rect);

    CCPoint relativeOffset = m_obUnflippedOffsetPositionFromCenter;

    // issue #732
    if (m_bFlipX)
    {
        relativeOffset.x = -relativeOffset.x;
    }
    if (m_bFlipY)
    {
        relativeOffset.y = -relativeOffset.y;
    }

    m_obOffsetPosition.x = relativeOffset.x + (m_obContentSize.width - m_obRect.size.width) / 2;
    m_obOffsetPosition.y = relativeOffset.y + (m_obContentSize.height - m_obRect.size.height) / 2;

    // rendering using batch node
    if (m_pobBatchNode)
    {
        // update dirty_, don't update recursiveDirty_
        setDirty(true);
    }
    else
    {
        // self rendering
        
        // Atlas: Vertex
        float x1 = 0 + m_obOffsetPosition.x;
        float y1 = 0 + m_obOffsetPosition.y;
        float x2 = x1 + m_obRect.size.width;
        float y2 = y1 + m_obRect.size.height;

        // Don't update Z.
        m_sQuad.bl.vertices = vertex3(x1, y1, 0);
        m_sQuad.br.vertices = vertex3(x2, y1, 0);
        m_sQuad.tl.vertices = vertex3(x1, y2, 0);
        m_sQuad.tr.vertices = vertex3(x2, y2, 0);
    }
}

// override this method to generate "double scale" sprites
void CCSprite::setVertexRect(const CCRect& rect)
{
    m_obRect = rect;
}

void CCSprite::setTextureCoords(CCRect rect)
{
    rect = CC_RECT_POINTS_TO_PIXELS(rect);

    CCTexture2D *tex = m_pobBatchNode ? m_pobTextureAtlas->getTexture() : m_pobTexture;
    if (! tex)
    {
        return;
    }

    float atlasWidth = (float)tex->getPixelsWide();
    float atlasHeight = (float)tex->getPixelsHigh();

    float left, right, top, bottom;

    if (m_bRectRotated)
    {
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        left    = (2*rect.origin.x+1)/(2*atlasWidth);
        right    = left+(rect.size.height*2-2)/(2*atlasWidth);
        top        = (2*rect.origin.y+1)/(2*atlasHeight);
        bottom    = top+(rect.size.width*2-2)/(2*atlasHeight);
#else
        left    = rect.origin.x/atlasWidth;
        right    = (rect.origin.x+rect.size.height) / atlasWidth;
        top        = rect.origin.y/atlasHeight;
        bottom    = (rect.origin.y+rect.size.width) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

        if (m_bFlipX)
        {
            CC_SWAP(top, bottom, float);
        }

        if (m_bFlipY)
        {
            CC_SWAP(left, right, float);
        }

        m_sQuad.bl.texCoords.u = left;
        m_sQuad.bl.texCoords.v = top;
        m_sQuad.br.texCoords.u = left;
        m_sQuad.br.texCoords.v = bottom;
        m_sQuad.tl.texCoords.u = right;
        m_sQuad.tl.texCoords.v = top;
        m_sQuad.tr.texCoords.u = right;
        m_sQuad.tr.texCoords.v = bottom;
    }
    else
    {
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        left    = (2*rect.origin.x+1)/(2*atlasWidth);
        right    = left + (rect.size.width*2-2)/(2*atlasWidth);
        top        = (2*rect.origin.y+1)/(2*atlasHeight);
        bottom    = top + (rect.size.height*2-2)/(2*atlasHeight);
#else
        left    = rect.origin.x/atlasWidth;
        right    = (rect.origin.x + rect.size.width) / atlasWidth;
        top        = rect.origin.y/atlasHeight;
        bottom    = (rect.origin.y + rect.size.height) / atlasHeight;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

        if(m_bFlipX)
        {
            CC_SWAP(left,right,float);
        }

        if(m_bFlipY)
        {
            CC_SWAP(top,bottom,float);
        }

        m_sQuad.bl.texCoords.u = left;
        m_sQuad.bl.texCoords.v = bottom;
        m_sQuad.br.texCoords.u = right;
        m_sQuad.br.texCoords.v = bottom;
        m_sQuad.tl.texCoords.u = left;
        m_sQuad.tl.texCoords.v = top;
        m_sQuad.tr.texCoords.u = right;
        m_sQuad.tr.texCoords.v = top;
    }
}

void CCSprite::updateTransform(void)
{
    CCAssert(m_pobBatchNode, "updateTransform is only valid when CCSprite is being rendered using an CCSpriteBatchNode");

    // recalculate matrix only if it is dirty
    if( isDirty() ) {

        // If it is not visible, or one of its ancestors is not visible, then do nothing:
        if( !m_bVisible || ( m_pParent && m_pParent != m_pobBatchNode && ((CCSprite*)m_pParent)->m_bShouldBeHidden) )
        {
            m_sQuad.br.vertices = m_sQuad.tl.vertices = m_sQuad.tr.vertices = m_sQuad.bl.vertices = vertex3(0,0,0);
            m_bShouldBeHidden = true;
        }
        else 
        {
            m_bShouldBeHidden = false;

            if( ! m_pParent || m_pParent == m_pobBatchNode )
            {
                m_transformToBatch = nodeToParentTransform();
            }
            else 
            {
                CCAssert( dynamic_cast<CCSprite*>(m_pParent), "Logic error in CCSprite. Parent must be a CCSprite");
                m_transformToBatch = CCAffineTransformConcat( nodeToParentTransform() , ((CCSprite*)m_pParent)->m_transformToBatch );
            }

            //
            // calculate the Quad based on the Affine Matrix
            //

            CCSize size = m_obRect.size;

            float x1 = m_obOffsetPosition.x;
            float y1 = m_obOffsetPosition.y;

            float x2 = x1 + size.width;
            float y2 = y1 + size.height;
            float x = m_transformToBatch.tx;
            float y = m_transformToBatch.ty;

            float cr = m_transformToBatch.a;
            float sr = m_transformToBatch.b;
            float cr2 = m_transformToBatch.d;
            float sr2 = -m_transformToBatch.c;
            float ax = x1 * cr - y1 * sr2 + x;
            float ay = x1 * sr + y1 * cr2 + y;

            float bx = x2 * cr - y1 * sr2 + x;
            float by = x2 * sr + y1 * cr2 + y;

            float cx = x2 * cr - y2 * sr2 + x;
            float cy = x2 * sr + y2 * cr2 + y;

            float dx = x1 * cr - y2 * sr2 + x;
            float dy = x1 * sr + y2 * cr2 + y;

            m_sQuad.bl.vertices = vertex3( RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), m_fVertexZ );
            m_sQuad.br.vertices = vertex3( RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), m_fVertexZ );
            m_sQuad.tl.vertices = vertex3( RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), m_fVertexZ );
            m_sQuad.tr.vertices = vertex3( RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), m_fVertexZ );
        }

        // MARMALADE CHANGE: ADDED CHECK FOR NULL, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
        if (m_pobTextureAtlas)
		{
            m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
        }
		
        m_bRecursiveDirty = false;
        setDirty(false);
    }

    // MARMALADE CHANGED
    // recursively iterate over children
/*    if( m_bHasChildren ) 
    {
        // MARMALADE: CHANGED TO USE CCNode*
        // NOTE THAT WE HAVE ALSO DEFINED virtual CCNode::updateTransform()
        arrayMakeObjectsPerformSelector(m_pChildren, updateTransform, CCSprite*);
    }*/
    CCNode::updateTransform();

#if CC_SPRITE_DEBUG_DRAW
    // draw bounding box
    CCPoint vertices[4] = {
        ccp( m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y ),
        ccp( m_sQuad.br.vertices.x, m_sQuad.br.vertices.y ),
        ccp( m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y ),
        ccp( m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y ),
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
}

// draw

void CCSprite::draw(void)
{
    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");

    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");

    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

    ccGLBindTexture2D( m_pobTexture->getName() );
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
    long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN

    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CHECK_GL_ERROR_DEBUG();


#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    CCPoint vertices[4]={
        ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
        ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
        ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
        ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
    };
    ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    CCSize s = this->getTextureRect().size;
    CCPoint offsetPix = this->getOffsetPosition();
    CCPoint vertices[4] = {
        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW

    CC_INCREMENT_GL_DRAWS(1);

    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}

// CCNode overrides

void CCSprite::addChild(CCNode* pChild)
{
    CCNode::addChild(pChild);
}

void CCSprite::addChild(CCNode *pChild, int zOrder)
{
    CCNode::addChild(pChild, zOrder);
}

void CCSprite::addChild(CCNode *pChild, int zOrder, int tag)
{
    CCAssert(pChild != NULL, "Argument must be non-NULL");

    if (m_pobBatchNode)
    {
        CCSprite* pChildSprite = dynamic_cast<CCSprite*>(pChild);
        CCAssert( pChildSprite, "CCSprite only supports CCSprites as children when using CCSpriteBatchNode");
        CCAssert(pChildSprite->getTexture()->getName() == m_pobTextureAtlas->getTexture()->getName(), "");
        //put it in descendants array of batch node
        m_pobBatchNode->appendChild(pChildSprite);

        if (!m_bReorderChildDirty)
        {
            setReorderChildDirtyRecursively();
        }
    }
    //CCNode already sets isReorderChildDirty_ so this needs to be after batchNode check
    CCNode::addChild(pChild, zOrder, tag);
    m_bHasChildren = true;
}

void CCSprite::reorderChild(CCNode *pChild, int zOrder)
{
    CCAssert(pChild != NULL, "");
    CCAssert(m_pChildren->containsObject(pChild), "");

    if (zOrder == pChild->getZOrder())
    {
        return;
    }

    if( m_pobBatchNode && ! m_bReorderChildDirty)
    {
        setReorderChildDirtyRecursively();
        m_pobBatchNode->reorderBatch(true);
    }

    CCNode::reorderChild(pChild, zOrder);
}

void CCSprite::removeChild(CCNode *pChild, bool bCleanup)
{
    if (m_pobBatchNode)
    {
        m_pobBatchNode->removeSpriteFromAtlas((CCSprite*)(pChild));
    }

    CCNode::removeChild(pChild, bCleanup);
    
}

void CCSprite::removeAllChildrenWithCleanup(bool bCleanup)
{
    if (m_pobBatchNode)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCSprite* pChild = dynamic_cast<CCSprite*>(pObject);
            if (pChild)
            {
                m_pobBatchNode->removeSpriteFromAtlas(pChild);
            }
        }
    }

    CCNode::removeAllChildrenWithCleanup(bCleanup);
    
    m_bHasChildren = false;
}

void CCSprite::sortAllChildren()
{
    if (m_bReorderChildDirty)
    {
        int i = 0,j = 0,length = m_pChildren->data->num;
        CCNode** x = (CCNode**)m_pChildren->data->arr;
        CCNode *tempItem = NULL;

        // insertion sort
        for(i=1; i<length; i++)
        {
            tempItem = x[i];
            j = i-1;

            //continue moving element downwards while zOrder is smaller or when zOrder is the same but orderOfArrival is smaller
            while(j>=0 && ( tempItem->getZOrder() < x[j]->getZOrder() || ( tempItem->getZOrder() == x[j]->getZOrder() && tempItem->getOrderOfArrival() < x[j]->getOrderOfArrival() ) ) )
            {
                x[j+1] = x[j];
                j = j-1;
            }
            x[j+1] = tempItem;
        }

        if ( m_pobBatchNode)
        {
            arrayMakeObjectsPerformSelector(m_pChildren, sortAllChildren, CCSprite*);
        }

        m_bReorderChildDirty = false;
    }
}

//
// CCNode property overloads
// used only when parent is CCSpriteBatchNode
//

void CCSprite::setReorderChildDirtyRecursively(void)
{
    //only set parents flag the first time
    if ( ! m_bReorderChildDirty )
    {
        m_bReorderChildDirty = true;
        CCNode* pNode = (CCNode*)m_pParent;
        while (pNode && pNode != m_pobBatchNode)
        {
            ((CCSprite*)pNode)->setReorderChildDirtyRecursively();
            pNode=pNode->getParent();
        }
    }
}


void CCSprite::setDirtyRecursively(bool bValue)
{
    m_bRecursiveDirty = bValue;
    setDirty(bValue);
    // recursively set dirty
    if (m_bHasChildren)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCSprite* pChild = dynamic_cast<CCSprite*>(pObject);
            if (pChild)
            {
                pChild->setDirtyRecursively(true);
            }
        }
    }
}

// XXX HACK: optimization
#define SET_DIRTY_RECURSIVELY() {                                    \
                    if (m_pobBatchNode && ! m_bRecursiveDirty) {    \
                        m_bRecursiveDirty = true;                    \
                        setDirty(true);                              \
                        if ( m_bHasChildren)                        \
                            setDirtyRecursively(true);                \
                        }                                            \
                    }

void CCSprite::setPosition(const CCPoint& pos)
{
    CCNode::setPosition(pos);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotation(float fRotation)
{
    CCNode::setRotation(fRotation);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotationX(float fRotationX)
{
    CCNode::setRotationX(fRotationX);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotationY(float fRotationY)
{
    CCNode::setRotationY(fRotationY);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setSkewX(float sx)
{
    CCNode::setSkewX(sx);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setSkewY(float sy)
{
    CCNode::setSkewY(sy);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleX(float fScaleX)
{
    CCNode::setScaleX(fScaleX);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleY(float fScaleY)
{
    CCNode::setScaleY(fScaleY);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScale(float fScale)
{
    CCNode::setScale(fScale);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setVertexZ(float fVertexZ)
{
    CCNode::setVertexZ(fVertexZ);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setAnchorPoint(const CCPoint& anchor)
{
    CCNode::setAnchorPoint(anchor);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::ignoreAnchorPointForPosition(bool value)
{
    CCAssert(! m_pobBatchNode, "ignoreAnchorPointForPosition is invalid in CCSprite");
    CCNode::ignoreAnchorPointForPosition(value);
}

void CCSprite::setVisible(bool bVisible)
{
    CCNode::setVisible(bVisible);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setFlipX(bool bFlipX)
{
    if (m_bFlipX != bFlipX)
    {
        m_bFlipX = bFlipX;
        setTextureRect(m_obRect, m_bRectRotated, m_obContentSize);
    }
}

bool CCSprite::isFlipX(void)
{
    return m_bFlipX;
}

void CCSprite::setFlipY(bool bFlipY)
{
    if (m_bFlipY != bFlipY)
    {
        m_bFlipY = bFlipY;
        setTextureRect(m_obRect, m_bRectRotated, m_obContentSize);
    }
}

bool CCSprite::isFlipY(void)
{
    return m_bFlipY;
}

//
// RGBA protocol
//

void CCSprite::updateColor(void)
{
    ccColor4B color4 = { _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity };
    
    // special opacity for premultiplied textures
	if (m_bOpacityModifyRGB)
    {
		color4.r *= _displayedOpacity/255.0f;
		color4.g *= _displayedOpacity/255.0f;
		color4.b *= _displayedOpacity/255.0f;
    }

    m_sQuad.bl.colors = color4;
    m_sQuad.br.colors = color4;
    m_sQuad.tl.colors = color4;
    m_sQuad.tr.colors = color4;

    // renders using batch node
    if (m_pobBatchNode)
    {
        if (m_uAtlasIndex != CCSpriteIndexNotInitialized)
        {
            m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
        }
        else
        {
            // no need to set it recursively
            // update dirty_, don't update recursiveDirty_
            setDirty(true);
        }
    }

    // self render
    // do nothing
}

void CCSprite::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);

    updateColor();
}

void CCSprite::setColor(const ccColor3B& color3)
{
    CCNodeRGBA::setColor(color3);

    updateColor();
}

void CCSprite::setOpacityModifyRGB(bool modify)
{
    if (m_bOpacityModifyRGB != modify)
    {
        m_bOpacityModifyRGB = modify;
        updateColor();
    }
}

bool CCSprite::isOpacityModifyRGB(void)
{
    return m_bOpacityModifyRGB;
}

void CCSprite::updateDisplayedColor(const ccColor3B& parentColor)
{
    CCNodeRGBA::updateDisplayedColor(parentColor);
    
    updateColor();
}

void CCSprite::updateDisplayedOpacity(GLubyte opacity)
{
    CCNodeRGBA::updateDisplayedOpacity(opacity);
    
    updateColor();
}

// Frames

void CCSprite::setDisplayFrame(CCSpriteFrame *pNewFrame)
{
    m_obUnflippedOffsetPositionFromCenter = pNewFrame->getOffset();

    CCTexture2D *pNewTexture = pNewFrame->getTexture();
    // update texture before updating texture rect
    if (pNewTexture != m_pobTexture)
    {
        setTexture(pNewTexture);
    }

    // update rect
    m_bRectRotated = pNewFrame->isRotated();
    setTextureRect(pNewFrame->getRect(), m_bRectRotated, pNewFrame->getOriginalSize());
}

void CCSprite::setDisplayFrameWithAnimationName(const char *animationName, int frameIndex)
{
    CCAssert(animationName, "CCSprite#setDisplayFrameWithAnimationName. animationName must not be NULL");

    CCAnimation *a = CCAnimationCache::sharedAnimationCache()->animationByName(animationName);

    CCAssert(a, "CCSprite#setDisplayFrameWithAnimationName: Frame not found");

    CCAnimationFrame* frame = (CCAnimationFrame*)a->getFrames()->objectAtIndex(frameIndex);

    CCAssert(frame, "CCSprite#setDisplayFrame. Invalid frame");

    setDisplayFrame(frame->getSpriteFrame());
}

bool CCSprite::isFrameDisplayed(CCSpriteFrame *pFrame)
{
    CCRect r = pFrame->getRect();

    return (r.equals(m_obRect) &&
            pFrame->getTexture()->getName() == m_pobTexture->getName() &&
            pFrame->getOffset().equals(m_obUnflippedOffsetPositionFromCenter));
}

CCSpriteFrame* CCSprite::displayFrame(void)
{
    return CCSpriteFrame::createWithTexture(m_pobTexture,
                                           CC_RECT_POINTS_TO_PIXELS(m_obRect),
                                           m_bRectRotated,
                                           CC_POINT_POINTS_TO_PIXELS(m_obUnflippedOffsetPositionFromCenter),
                                           CC_SIZE_POINTS_TO_PIXELS(m_obContentSize));
}

CCSpriteBatchNode* CCSprite::getBatchNode(void)
{
    return m_pobBatchNode;
}

void CCSprite::setBatchNode(CCSpriteBatchNode *pobSpriteBatchNode)
{
    m_pobBatchNode = pobSpriteBatchNode; // weak reference

    // self render
    if( ! m_pobBatchNode ) {
        m_uAtlasIndex = CCSpriteIndexNotInitialized;
        setTextureAtlas(NULL);
        m_bRecursiveDirty = false;
        setDirty(false);

        float x1 = m_obOffsetPosition.x;
        float y1 = m_obOffsetPosition.y;
        float x2 = x1 + m_obRect.size.width;
        float y2 = y1 + m_obRect.size.height;
        m_sQuad.bl.vertices = vertex3( x1, y1, 0 );
        m_sQuad.br.vertices = vertex3( x2, y1, 0 );
        m_sQuad.tl.vertices = vertex3( x1, y2, 0 );
        m_sQuad.tr.vertices = vertex3( x2, y2, 0 );

    } else {

        // using batch
        m_transformToBatch = CCAffineTransformIdentity;
        setTextureAtlas(m_pobBatchNode->getTextureAtlas()); // weak ref
    }
}

// Texture protocol

void CCSprite::updateBlendFunc(void)
{
    CCAssert (! m_pobBatchNode, "CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a CCSpriteBatchNode");

    // it is possible to have an untextured sprite
    if (! m_pobTexture || ! m_pobTexture->hasPremultipliedAlpha())
    {
        m_sBlendFunc.src = GL_SRC_ALPHA;
        m_sBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
        setOpacityModifyRGB(false);
    }
    else
    {
        m_sBlendFunc.src = CC_BLEND_SRC;
        m_sBlendFunc.dst = CC_BLEND_DST;
        setOpacityModifyRGB(true);
    }
}

/*
 * This array is the data of a white image with 2 by 2 dimension.
 * It's used for creating a default texture when sprite's texture is set to NULL.
 * Supposing codes as follows:
 *
 *   CCSprite* sp = new CCSprite();
 *   sp->init();  // Texture was set to NULL, in order to make opacity and color to work correctly, we need to create a 2x2 white texture.
 *
 * The test is in "TestCpp/SpriteTest/Sprite without texture".
 */
static unsigned char cc_2x2_white_image[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};

#define CC_2x2_WHITE_IMAGE_KEY  "cc_2x2_white_image"

void CCSprite::setTexture(CCTexture2D *texture)
{
    // If batchnode, then texture id should be the same
    CCAssert(! m_pobBatchNode || texture->getName() == m_pobBatchNode->getTexture()->getName(), "CCSprite: Batched sprites should use the same texture as the batchnode");
    // accept texture==nil as argument
    CCAssert( !texture || dynamic_cast<CCTexture2D*>(texture), "setTexture expects a CCTexture2D. Invalid argument");

    if (NULL == texture)
    {
        // Gets the texture by key firstly.
        texture = CCTextureCache::sharedTextureCache()->textureForKey(CC_2x2_WHITE_IMAGE_KEY);

        // If texture wasn't in cache, create it from RAW data.
        if (NULL == texture)
        {
            CCImage* image = new CCImage();
            bool isOK = image->initWithImageData(cc_2x2_white_image, sizeof(cc_2x2_white_image), CCImage::kFmtRawData, 2, 2, 8);
            CCAssert(isOK, "The 2x2 empty texture was created unsuccessfully.");

            texture = CCTextureCache::sharedTextureCache()->addUIImage(image, CC_2x2_WHITE_IMAGE_KEY);
            CC_SAFE_RELEASE(image);
        }
    }

    if (!m_pobBatchNode && m_pobTexture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(m_pobTexture);
        m_pobTexture = texture;
        updateBlendFunc();
    }
}

CCTexture2D* CCSprite::getTexture(void)
{
    return m_pobTexture;
}

NS_CC_END
