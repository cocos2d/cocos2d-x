/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Lam Pham

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
#include "CCProgressTimer.h"

#include "ccMacros.h"
#include "textures/CCTextureCache.h"
#include "support/CCPointExtension.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccGLStateCache.h"
#include "CCDirector.h"
#include "support/TransformUtils.h"
#include "CCDrawingPrimitives.h"
// extern
#include "kazmath/GL/matrix.h"

#include <float.h>

NS_CC_BEGIN

#define kProgressTextureCoordsCount 4
//  kProgressTextureCoords holds points {0,1} {0,0} {1,0} {1,1} we can represent it as bits
const char kCCProgressTextureCoords = 0x4b;


CCProgressTimer::CCProgressTimer()
:m_eType(kCCProgressTimerTypeRadial)
,m_fPercentage(0.0f)
,m_pSprite(NULL)
,m_nVertexDataCount(0)
,m_pVertexData(NULL)
,m_tMidpoint(0,0)
,m_tBarChangeRate(0,0)
,m_bReverseDirection(false)
{}

CCProgressTimer* CCProgressTimer::progressWithSprite(CCSprite* sp)
{
    return CCProgressTimer::create(sp);
}

CCProgressTimer* CCProgressTimer::create(CCSprite* sp)
{
    CCProgressTimer *pProgressTimer = new CCProgressTimer();
    if (pProgressTimer->initWithSprite(sp))
    {
        pProgressTimer->autorelease();
    }
    else
    {
        delete pProgressTimer;
        pProgressTimer = NULL;
    }        

    return pProgressTimer;
}

bool CCProgressTimer::initWithSprite(CCSprite* sp)
{
    setPercentage(0.0f);
    m_pVertexData = NULL;
    m_nVertexDataCount = 0;

    setAnchorPoint(ccp(0.5f,0.5f));
    m_eType = kCCProgressTimerTypeRadial;
    m_bReverseDirection = false;
    setMidpoint(ccp(0.5f, 0.5f));
    setBarChangeRate(ccp(1,1));
    setSprite(sp);
    // shader program
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    return true;
}

CCProgressTimer::~CCProgressTimer(void)
{
    CC_SAFE_FREE(m_pVertexData);
    CC_SAFE_RELEASE(m_pSprite);
}

void CCProgressTimer::setPercentage(float fPercentage)
{
    if (m_fPercentage != fPercentage)
    {
        m_fPercentage = clampf(fPercentage, 0, 100);
        updateProgress();
    }
}

void CCProgressTimer::setSprite(CCSprite *pSprite)
{
    if (m_pSprite != pSprite)
    {
        CC_SAFE_RETAIN(pSprite);
        CC_SAFE_RELEASE(m_pSprite);
        m_pSprite = pSprite;
        setContentSize(m_pSprite->getContentSize());

        //    Every time we set a new sprite, we free the current vertex data
        if (m_pVertexData)
        {
            CC_SAFE_FREE(m_pVertexData);
            m_nVertexDataCount = 0;
        }
    }        
}

void CCProgressTimer::setType(CCProgressTimerType type)
{
    if (type != m_eType)
    {
        //    release all previous information
        if (m_pVertexData)
        {
            CC_SAFE_FREE(m_pVertexData);
            m_pVertexData = NULL;
            m_nVertexDataCount = 0;
        }

        m_eType = type;
    }
}

void CCProgressTimer::setReverseProgress(bool reverse)
{
    if( m_bReverseDirection != reverse ) {
        m_bReverseDirection = reverse;

        //    release all previous information
        CC_SAFE_FREE(m_pVertexData);
        m_nVertexDataCount = 0;
    }
}

void CCProgressTimer::setColor(const ccColor3B& color)
{
    m_pSprite->setColor(color);
    updateColor();
}

const ccColor3B& CCProgressTimer::getColor(void)
{
    return m_pSprite->getColor();
}

void CCProgressTimer::setOpacity(GLubyte opacity)
{
    m_pSprite->setOpacity(opacity);
    updateColor();
}

GLubyte CCProgressTimer::getOpacity(void)
{
    return m_pSprite->getOpacity();
}

void CCProgressTimer::setOpacityModifyRGB(bool bValue)
{
    CC_UNUSED_PARAM(bValue);
}

bool CCProgressTimer::isOpacityModifyRGB(void)
{
    return false;
}

// Interval

///
//    @returns the vertex position from the texture coordinate
///
ccTex2F CCProgressTimer::textureCoordFromAlphaPoint(CCPoint alpha)
{
    ccTex2F ret = {0.0f, 0.0f};
    if (!m_pSprite) {
        return ret;
    }
    ccV3F_C4B_T2F_Quad quad = m_pSprite->getQuad();
    CCPoint min = ccp(quad.bl.texCoords.u,quad.bl.texCoords.v);
    CCPoint max = ccp(quad.tr.texCoords.u,quad.tr.texCoords.v);
    //  Fix bug #1303 so that progress timer handles sprite frame texture rotation
    if (m_pSprite->isTextureRectRotated()) {
        CC_SWAP(alpha.x, alpha.y, float);
    }
    return tex2(min.x * (1.f - alpha.x) + max.x * alpha.x, min.y * (1.f - alpha.y) + max.y * alpha.y);
}

ccVertex2F CCProgressTimer::vertexFromAlphaPoint(CCPoint alpha)
{
    ccVertex2F ret = {0.0f, 0.0f};
    if (!m_pSprite) {
        return ret;
    }
    ccV3F_C4B_T2F_Quad quad = m_pSprite->getQuad();
    CCPoint min = ccp(quad.bl.vertices.x,quad.bl.vertices.y);
    CCPoint max = ccp(quad.tr.vertices.x,quad.tr.vertices.y);
    ret.x = min.x * (1.f - alpha.x) + max.x * alpha.x;
    ret.y = min.y * (1.f - alpha.y) + max.y * alpha.y;
    return ret;
}

void CCProgressTimer::updateColor(void)
{
    if (!m_pSprite) {
        return;
    }

    if (m_pVertexData)
    {
        ccColor4B sc = m_pSprite->getQuad().tl.colors;
        for (int i = 0; i < m_nVertexDataCount; ++i)
        {
            m_pVertexData[i].colors = sc;
        }            
    }
}

void CCProgressTimer::updateProgress(void)
{
    switch (m_eType)
    {
    case kCCProgressTimerTypeRadial:
        updateRadial();
        break;
    case kCCProgressTimerTypeBar:
        updateBar();
        break;
    default:
        break;
    }
}

void CCProgressTimer::setAnchorPoint(CCPoint anchorPoint)
{
    CCNode::setAnchorPoint(anchorPoint);
}

CCPoint CCProgressTimer::getMidpoint(void)
{
    return m_tMidpoint;
}

void CCProgressTimer::setMidpoint(CCPoint midPoint)
{
    m_tMidpoint = ccpClamp(midPoint, CCPointZero, ccp(1,1));
}

///
//    Update does the work of mapping the texture onto the triangles
//    It now doesn't occur the cost of free/alloc data every update cycle.
//    It also only changes the percentage point but no other points if they have not
//    been modified.
//    
//    It now deals with flipped texture. If you run into this problem, just use the
//    sprite property and enable the methods flipX, flipY.
///
void CCProgressTimer::updateRadial(void)
{
    if (!m_pSprite) {
        return;
    }
    float alpha = m_fPercentage / 100.f;

    float angle = 2.f*((float)M_PI) * ( m_bReverseDirection ? alpha : 1.0f - alpha);

    //    We find the vector to do a hit detection based on the percentage
    //    We know the first vector is the one @ 12 o'clock (top,mid) so we rotate
    //    from that by the progress angle around the m_tMidpoint pivot
    CCPoint topMid = ccp(m_tMidpoint.x, 1.f);
    CCPoint percentagePt = ccpRotateByAngle(topMid, m_tMidpoint, angle);


    int index = 0;
    CCPoint hit = CCPointZero;

    if (alpha == 0.f) {
        //    More efficient since we don't always need to check intersection
        //    If the alpha is zero then the hit point is top mid and the index is 0.
        hit = topMid;
        index = 0;
    } else if (alpha == 1.f) {
        //    More efficient since we don't always need to check intersection
        //    If the alpha is one then the hit point is top mid and the index is 4.
        hit = topMid;
        index = 4;
    } else {
        //    We run a for loop checking the edges of the texture to find the
        //    intersection point
        //    We loop through five points since the top is split in half

        float min_t = FLT_MAX;

        for (int i = 0; i <= kProgressTextureCoordsCount; ++i) {
            int pIndex = (i + (kProgressTextureCoordsCount - 1))%kProgressTextureCoordsCount;

            CCPoint edgePtA = boundaryTexCoord(i % kProgressTextureCoordsCount);
            CCPoint edgePtB = boundaryTexCoord(pIndex);

            //    Remember that the top edge is split in half for the 12 o'clock position
            //    Let's deal with that here by finding the correct endpoints
            if(i == 0){
                edgePtB = ccpLerp(edgePtA, edgePtB, 1-m_tMidpoint.x);
            } else if(i == 4){
                edgePtA = ccpLerp(edgePtA, edgePtB, 1-m_tMidpoint.x);
            }

            //    s and t are returned by ccpLineIntersect
            float s = 0, t = 0;
            if(ccpLineIntersect(edgePtA, edgePtB, m_tMidpoint, percentagePt, &s, &t))
            {

                //    Since our hit test is on rays we have to deal with the top edge
                //    being in split in half so we have to test as a segment
                if ((i == 0 || i == 4)) {
                    //    s represents the point between edgePtA--edgePtB
                    if (!(0.f <= s && s <= 1.f)) {
                        continue;
                    }
                }
                //    As long as our t isn't negative we are at least finding a
                //    correct hitpoint from m_tMidpoint to percentagePt.
                if (t >= 0.f) {
                    //    Because the percentage line and all the texture edges are
                    //    rays we should only account for the shortest intersection
                    if (t < min_t) {
                        min_t = t;
                        index = i;
                    }
                }
            }
        }

        //    Now that we have the minimum magnitude we can use that to find our intersection
        hit = ccpAdd(m_tMidpoint, ccpMult(ccpSub(percentagePt, m_tMidpoint),min_t));

    }


    //    The size of the vertex data is the index from the hitpoint
    //    the 3 is for the m_tMidpoint, 12 o'clock point and hitpoint position.

    bool sameIndexCount = true;
    if(m_nVertexDataCount != index + 3){
        sameIndexCount = false;
        CC_SAFE_FREE(m_pVertexData);
        m_nVertexDataCount = 0;
    }


    if(!m_pVertexData) {
        m_nVertexDataCount = index + 3;
        m_pVertexData = (ccV2F_C4B_T2F*)malloc(m_nVertexDataCount * sizeof(ccV2F_C4B_T2F));
        CCAssert( m_pVertexData, "CCProgressTimer. Not enough memory");
    }
    updateColor();

    if (!sameIndexCount) {

        //    First we populate the array with the m_tMidpoint, then all
        //    vertices/texcoords/colors of the 12 'o clock start and edges and the hitpoint
        m_pVertexData[0].texCoords = textureCoordFromAlphaPoint(m_tMidpoint);
        m_pVertexData[0].vertices = vertexFromAlphaPoint(m_tMidpoint);

        m_pVertexData[1].texCoords = textureCoordFromAlphaPoint(topMid);
        m_pVertexData[1].vertices = vertexFromAlphaPoint(topMid);

        for(int i = 0; i < index; ++i){
            CCPoint alphaPoint = boundaryTexCoord(i);
            m_pVertexData[i+2].texCoords = textureCoordFromAlphaPoint(alphaPoint);
            m_pVertexData[i+2].vertices = vertexFromAlphaPoint(alphaPoint);
        }
    }

    //    hitpoint will go last
    m_pVertexData[m_nVertexDataCount - 1].texCoords = textureCoordFromAlphaPoint(hit);
    m_pVertexData[m_nVertexDataCount - 1].vertices = vertexFromAlphaPoint(hit);

}

///
//    Update does the work of mapping the texture onto the triangles for the bar
//    It now doesn't occur the cost of free/alloc data every update cycle.
//    It also only changes the percentage point but no other points if they have not
//    been modified.
//    
//    It now deals with flipped texture. If you run into this problem, just use the
//    sprite property and enable the methods flipX, flipY.
///
void CCProgressTimer::updateBar(void)
{
    if (!m_pSprite) {
        return;
    }
    float alpha = m_fPercentage / 100.0f;
    CCPoint alphaOffset = ccpMult(ccp(1.0f * (1.0f - m_tBarChangeRate.x) + alpha * m_tBarChangeRate.x, 1.0f * (1.0f - m_tBarChangeRate.y) + alpha * m_tBarChangeRate.y), 0.5f);
    CCPoint min = ccpSub(m_tMidpoint, alphaOffset);
    CCPoint max = ccpAdd(m_tMidpoint, alphaOffset);

    if (min.x < 0.f) {
        max.x += -min.x;
        min.x = 0.f;
    }

    if (max.x > 1.f) {
        min.x -= max.x - 1.f;
        max.x = 1.f;
    }

    if (min.y < 0.f) {
        max.y += -min.y;
        min.y = 0.f;
    }

    if (max.y > 1.f) {
        min.y -= max.y - 1.f;
        max.y = 1.f;
    }


    if (!m_bReverseDirection) {
        if(!m_pVertexData) {
            m_nVertexDataCount = 4;
            m_pVertexData = (ccV2F_C4B_T2F*)malloc(m_nVertexDataCount * sizeof(ccV2F_C4B_T2F));
            CCAssert( m_pVertexData, "CCProgressTimer. Not enough memory");
        }
        //    TOPLEFT
        m_pVertexData[0].texCoords = textureCoordFromAlphaPoint(ccp(min.x,max.y));
        m_pVertexData[0].vertices = vertexFromAlphaPoint(ccp(min.x,max.y));

        //    BOTLEFT
        m_pVertexData[1].texCoords = textureCoordFromAlphaPoint(ccp(min.x,min.y));
        m_pVertexData[1].vertices = vertexFromAlphaPoint(ccp(min.x,min.y));

        //    TOPRIGHT
        m_pVertexData[2].texCoords = textureCoordFromAlphaPoint(ccp(max.x,max.y));
        m_pVertexData[2].vertices = vertexFromAlphaPoint(ccp(max.x,max.y));

        //    BOTRIGHT
        m_pVertexData[3].texCoords = textureCoordFromAlphaPoint(ccp(max.x,min.y));
        m_pVertexData[3].vertices = vertexFromAlphaPoint(ccp(max.x,min.y));
    } else {
        if(!m_pVertexData) {
            m_nVertexDataCount = 8;
            m_pVertexData = (ccV2F_C4B_T2F*)malloc(m_nVertexDataCount * sizeof(ccV2F_C4B_T2F));
            CCAssert( m_pVertexData, "CCProgressTimer. Not enough memory");
            //    TOPLEFT 1
            m_pVertexData[0].texCoords = textureCoordFromAlphaPoint(ccp(0,1));
            m_pVertexData[0].vertices = vertexFromAlphaPoint(ccp(0,1));

            //    BOTLEFT 1
            m_pVertexData[1].texCoords = textureCoordFromAlphaPoint(ccp(0,0));
            m_pVertexData[1].vertices = vertexFromAlphaPoint(ccp(0,0));

            //    TOPRIGHT 2
            m_pVertexData[6].texCoords = textureCoordFromAlphaPoint(ccp(1,1));
            m_pVertexData[6].vertices = vertexFromAlphaPoint(ccp(1,1));

            //    BOTRIGHT 2
            m_pVertexData[7].texCoords = textureCoordFromAlphaPoint(ccp(1,0));
            m_pVertexData[7].vertices = vertexFromAlphaPoint(ccp(1,0));
        }

        //    TOPRIGHT 1
        m_pVertexData[2].texCoords = textureCoordFromAlphaPoint(ccp(min.x,max.y));
        m_pVertexData[2].vertices = vertexFromAlphaPoint(ccp(min.x,max.y));

        //    BOTRIGHT 1
        m_pVertexData[3].texCoords = textureCoordFromAlphaPoint(ccp(min.x,min.y));
        m_pVertexData[3].vertices = vertexFromAlphaPoint(ccp(min.x,min.y));

        //    TOPLEFT 2
        m_pVertexData[4].texCoords = textureCoordFromAlphaPoint(ccp(max.x,max.y));
        m_pVertexData[4].vertices = vertexFromAlphaPoint(ccp(max.x,max.y));

        //    BOTLEFT 2
        m_pVertexData[5].texCoords = textureCoordFromAlphaPoint(ccp(max.x,min.y));
        m_pVertexData[5].vertices = vertexFromAlphaPoint(ccp(max.x,min.y));
    }
    updateColor();
}

CCPoint CCProgressTimer::boundaryTexCoord(char index)
{
    if (index < kProgressTextureCoordsCount) {
        if (m_bReverseDirection) {
            return ccp((kCCProgressTextureCoords>>(7-(index<<1)))&1,(kCCProgressTextureCoords>>(7-((index<<1)+1)))&1);
        } else {
            return ccp((kCCProgressTextureCoords>>((index<<1)+1))&1,(kCCProgressTextureCoords>>(index<<1))&1);
        }
    }
    return CCPointZero;
}

void CCProgressTimer::draw(void)
{
    if( ! m_pVertexData || ! m_pSprite)
        return;

    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc( m_pSprite->getBlendFunc().src, m_pSprite->getBlendFunc().dst );

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );

    ccGLBindTexture2D( m_pSprite->getTexture()->getName() );

    glVertexAttribPointer( kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(m_pVertexData[0]) , &m_pVertexData[0].vertices);
    glVertexAttribPointer( kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(m_pVertexData[0]), &m_pVertexData[0].texCoords);
    glVertexAttribPointer( kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(m_pVertexData[0]), &m_pVertexData[0].colors);

    if(m_eType == kCCProgressTimerTypeRadial)
    {
        glDrawArrays(GL_TRIANGLE_FAN, 0, m_nVertexDataCount);
    } 
    else if (m_eType == kCCProgressTimerTypeBar)
    {
        if (!m_bReverseDirection) 
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, m_nVertexDataCount);
        } 
        else 
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, m_nVertexDataCount/2);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, m_nVertexDataCount/2);
            // 2 draw calls
            CC_INCREMENT_GL_DRAWS(1);
        }
    }
    CC_INCREMENT_GL_DRAWS(1);
}

NS_CC_END
