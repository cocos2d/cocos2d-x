/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      On-Core

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
#include "ccMacros.h"
#include "effects/CCGrid.h"
#include "CCDirector.h"
#include "effects/CCGrabber.h"
#include "support/ccUtils.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccGLStateCache.h"
#include "CCGL.h"
#include "support/CCPointExtension.h"
#include "support/TransformUtils.h"
#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN
// implementation of CCGridBase

CCGridBase* CCGridBase::create(const CCSize& gridSize)
{
    CCGridBase *pGridBase = new CCGridBase();

    if (pGridBase)
    {
        if (pGridBase->initWithSize(gridSize))
        {
            pGridBase->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pGridBase);
        }
    }

    return pGridBase;
}

CCGridBase* CCGridBase::create(const CCSize& gridSize, CCTexture2D *texture, bool flipped)
{
    CCGridBase *pGridBase = new CCGridBase();

    if (pGridBase)
    {
        if (pGridBase->initWithSize(gridSize, texture, flipped))
        {
            pGridBase->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pGridBase);
        }
    }

    return pGridBase;
}

bool CCGridBase::initWithSize(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped)
{
    bool bRet = true;

    m_bActive = false;
    m_nReuseGrid = 0;
    m_sGridSize = gridSize;

    m_pTexture = pTexture;
    CC_SAFE_RETAIN(m_pTexture);
    m_bIsTextureFlipped = bFlipped;

    CCSize texSize = m_pTexture->getContentSize();
    m_obStep.x = texSize.width / m_sGridSize.width;
    m_obStep.y = texSize.height / m_sGridSize.height;

    m_pGrabber = new CCGrabber();
    if (m_pGrabber)
    {
        m_pGrabber->grab(m_pTexture);
    }
    else
    {
        bRet = false;
    }
    
    m_pShaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture);
    calculateVertexPoints();

    return bRet;
}

bool CCGridBase::initWithSize(const CCSize& gridSize)
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCSize s = pDirector->getWinSizeInPixels();
    
    unsigned long POTWide = ccNextPOT((unsigned int)s.width);
    unsigned long POTHigh = ccNextPOT((unsigned int)s.height);

    // we only use rgba8888
    CCTexture2DPixelFormat format = kCCTexture2DPixelFormat_RGBA8888;

    void *data = calloc((int)(POTWide * POTHigh * 4), 1);
    if (! data)
    {
        CCLOG("cocos2d: CCGrid: not enough memory.");
        this->release();
        return false;
    }

    CCTexture2D *pTexture = new CCTexture2D();
    pTexture->initWithData(data, format, POTWide, POTHigh, s);

    free(data);

    if (! pTexture)
    {
        CCLOG("cocos2d: CCGrid: error creating texture");
        return false;
    }

    initWithSize(gridSize, pTexture, false);

    pTexture->release();

    return true;
}

CCGridBase::~CCGridBase(void)
{
    CCLOGINFO("cocos2d: deallocing %p", this);

//TODO: ? why 2.0 comments this line        setActive(false);
    CC_SAFE_RELEASE(m_pTexture);
    CC_SAFE_RELEASE(m_pGrabber);
}

// properties
void CCGridBase::setActive(bool bActive)
{
    m_bActive = bActive;
    if (! bActive)
    {
        CCDirector *pDirector = CCDirector::sharedDirector();
        ccDirectorProjection proj = pDirector->getProjection();
        pDirector->setProjection(proj);
    }
}

void CCGridBase::setTextureFlipped(bool bFlipped)
{
    if (m_bIsTextureFlipped != bFlipped)
    {
        m_bIsTextureFlipped = bFlipped;
        calculateVertexPoints();
    }
}

void CCGridBase::set2DProjection()
{
    CCDirector *director = CCDirector::sharedDirector();

    CCSize    size = director->getWinSizeInPixels();

    glViewport(0, 0, (GLsizei)(size.width * CC_CONTENT_SCALE_FACTOR()), (GLsizei)(size.height * CC_CONTENT_SCALE_FACTOR()) );
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadIdentity();

    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, 0, size.width * CC_CONTENT_SCALE_FACTOR(), 0, size.height * CC_CONTENT_SCALE_FACTOR(), -1, 1);
    kmGLMultMatrix( &orthoMatrix );

    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadIdentity();


    ccSetProjectionMatrixDirty();
}

void CCGridBase::beforeDraw(void)
{
    // save projection
    CCDirector *director = CCDirector::sharedDirector();
    m_directorProjection = director->getProjection();

    // 2d projection
    //    [director setProjection:kCCDirectorProjection2D];
    set2DProjection();
    m_pGrabber->beforeRender(m_pTexture);
}

void CCGridBase::afterDraw(cocos2d::CCNode *pTarget)
{
    m_pGrabber->afterRender(m_pTexture);

    // restore projection
    CCDirector *director = CCDirector::sharedDirector();
    director->setProjection(m_directorProjection);

    if (pTarget->getCamera()->isDirty())
    {
        CCPoint offset = pTarget->getAnchorPointInPoints();

        //
        // XXX: Camera should be applied in the AnchorPoint
        //
        kmGLTranslatef(offset.x, offset.y, 0);
        pTarget->getCamera()->locate();
        kmGLTranslatef(-offset.x, -offset.y, 0);
    }

    ccGLBindTexture2D(m_pTexture->getName());

    // restore projection for default FBO .fixed bug #543 #544
//TODO:         CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
//TODO:         CCDirector::sharedDirector()->applyOrientation();
    blit();
}

void CCGridBase::blit(void)
{
    CCAssert(0, "");
}

void CCGridBase::reuse(void)
{
    CCAssert(0, "");
}

void CCGridBase::calculateVertexPoints(void)
{
    CCAssert(0, "");
}

// implementation of CCGrid3D

CCGrid3D* CCGrid3D::create(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped)
{
    CCGrid3D *pRet= new CCGrid3D();

    if (pRet)
    {
        if (pRet->initWithSize(gridSize, pTexture, bFlipped))
        {
            pRet->autorelease();
        }
        else
        {
            delete pRet;
            pRet = NULL;
        }
    }

    return pRet;
}

CCGrid3D* CCGrid3D::create(const CCSize& gridSize)
{
    CCGrid3D *pRet= new CCGrid3D();

    if (pRet)
    {
        if (pRet->initWithSize(gridSize))
        {
            pRet->autorelease();
        }
        else
        {
            delete pRet;
            pRet = NULL;
        }
    }

    return pRet;
}


CCGrid3D::CCGrid3D()
    : m_pTexCoordinates(NULL)
    , m_pVertices(NULL)
    , m_pOriginalVertices(NULL)
    , m_pIndices(NULL)
{

}

CCGrid3D::~CCGrid3D(void)
{
    CC_SAFE_FREE(m_pTexCoordinates);
    CC_SAFE_FREE(m_pVertices);
    CC_SAFE_FREE(m_pIndices);
    CC_SAFE_FREE(m_pOriginalVertices);
}

void CCGrid3D::blit(void)
{
    int n = m_sGridSize.width * m_sGridSize.height;

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );
    m_pShaderProgram->use();
    m_pShaderProgram->setUniformsForBuiltins();;

    //
    // Attributes
    //
#ifdef EMSCRIPTEN
    // Size calculations from calculateVertexPoints().
    unsigned int numOfPoints = (m_sGridSize.width+1) * (m_sGridSize.height+1);

    // position
    setGLBufferData(m_pVertices, numOfPoints * sizeof(ccVertex3F), 0);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texCoords
    setGLBufferData(m_pTexCoordinates, numOfPoints * sizeof(ccVertex2F), 1);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLIndexData(m_pIndices, n * 12, 0);
    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, 0);
#else
    // position
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, m_pVertices);

    // texCoords
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, m_pTexCoordinates);

    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, m_pIndices);
#endif // EMSCRIPTEN
    CC_INCREMENT_GL_DRAWS(1);
}

void CCGrid3D::calculateVertexPoints(void)
{
    float width = (float)m_pTexture->getPixelsWide();
    float height = (float)m_pTexture->getPixelsHigh();
    float imageH = m_pTexture->getContentSizeInPixels().height;

    int x, y, i;
    CC_SAFE_FREE(m_pVertices);
    CC_SAFE_FREE(m_pOriginalVertices);
    CC_SAFE_FREE(m_pTexCoordinates);
    CC_SAFE_FREE(m_pIndices);

    unsigned int numOfPoints = (m_sGridSize.width+1) * (m_sGridSize.height+1);

    m_pVertices = malloc(numOfPoints * sizeof(ccVertex3F));
    m_pOriginalVertices = malloc(numOfPoints * sizeof(ccVertex3F));
    m_pTexCoordinates = malloc(numOfPoints * sizeof(ccVertex2F));
    m_pIndices = (GLushort*)malloc(m_sGridSize.width * m_sGridSize.height * sizeof(GLushort) * 6);

    GLfloat *vertArray = (GLfloat*)m_pVertices;
    GLfloat *texArray = (GLfloat*)m_pTexCoordinates;
    GLushort *idxArray = m_pIndices;

    for (x = 0; x < m_sGridSize.width; ++x)
    {
        for (y = 0; y < m_sGridSize.height; ++y)
        {
            int idx = (y * m_sGridSize.width) + x;

            GLfloat x1 = x * m_obStep.x;
            GLfloat x2 = x1 + m_obStep.x;
            GLfloat y1 = y * m_obStep.y;
            GLfloat y2= y1 + m_obStep.y;

            GLushort a = (GLushort)(x * (m_sGridSize.height + 1) + y);
            GLushort b = (GLushort)((x + 1) * (m_sGridSize.height + 1) + y);
            GLushort c = (GLushort)((x + 1) * (m_sGridSize.height + 1) + (y + 1));
            GLushort d = (GLushort)(x * (m_sGridSize.height + 1) + (y + 1));

            GLushort tempidx[6] = {a, b, d, b, c, d};

            memcpy(&idxArray[6*idx], tempidx, 6*sizeof(GLushort));

            int l1[4] = {a*3, b*3, c*3, d*3};
            ccVertex3F e = {x1, y1, 0};
            ccVertex3F f = {x2, y1, 0};
            ccVertex3F g = {x2, y2, 0};
            ccVertex3F h = {x1, y2, 0};

            ccVertex3F l2[4] = {e, f, g, h};

            int tex1[4] = {a*2, b*2, c*2, d*2};
            CCPoint tex2[4] = {ccp(x1, y1), ccp(x2, y1), ccp(x2, y2), ccp(x1, y2)};

            for (i = 0; i < 4; ++i)
            {
                vertArray[l1[i]] = l2[i].x;
                vertArray[l1[i] + 1] = l2[i].y;
                vertArray[l1[i] + 2] = l2[i].z;

                texArray[tex1[i]] = tex2[i].x / width;
                if (m_bIsTextureFlipped)
                {
                    texArray[tex1[i] + 1] = (imageH - tex2[i].y) / height;
                }
                else
                {
                    texArray[tex1[i] + 1] = tex2[i].y / height;
                }
            }
        }
    }

    memcpy(m_pOriginalVertices, m_pVertices, (m_sGridSize.width+1) * (m_sGridSize.height+1) * sizeof(ccVertex3F));
}

ccVertex3F CCGrid3D::vertex(const CCPoint& pos)
{
    CCAssert( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    
    int index = (pos.x * (m_sGridSize.height+1) + pos.y) * 3;
    float *vertArray = (float*)m_pVertices;

    ccVertex3F vert = {vertArray[index], vertArray[index+1], vertArray[index+2]};

    return vert;
}

ccVertex3F CCGrid3D::originalVertex(const CCPoint& pos)
{
    CCAssert( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    
    int index = (pos.x * (m_sGridSize.height+1) + pos.y) * 3;
    float *vertArray = (float*)m_pOriginalVertices;

    ccVertex3F vert = {vertArray[index], vertArray[index+1], vertArray[index+2]};

    return vert;
}

void CCGrid3D::setVertex(const CCPoint& pos, const ccVertex3F& vertex)
{
    CCAssert( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int index = (pos.x * (m_sGridSize.height + 1) + pos.y) * 3;
    float *vertArray = (float*)m_pVertices;
    vertArray[index] = vertex.x;
    vertArray[index+1] = vertex.y;
    vertArray[index+2] = vertex.z;
}

void CCGrid3D::reuse(void)
{
    if (m_nReuseGrid > 0)
    {
        memcpy(m_pOriginalVertices, m_pVertices, (m_sGridSize.width+1) * (m_sGridSize.height+1) * sizeof(ccVertex3F));
        --m_nReuseGrid;
    }
}

// implementation of CCTiledGrid3D

CCTiledGrid3D::CCTiledGrid3D()
    : m_pTexCoordinates(NULL)
    , m_pVertices(NULL)
    , m_pOriginalVertices(NULL)
    , m_pIndices(NULL)
{

}

CCTiledGrid3D::~CCTiledGrid3D(void)
{
    CC_SAFE_FREE(m_pTexCoordinates);
    CC_SAFE_FREE(m_pVertices);
    CC_SAFE_FREE(m_pOriginalVertices);
    CC_SAFE_FREE(m_pIndices);
}

CCTiledGrid3D* CCTiledGrid3D::create(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped)
{
    CCTiledGrid3D *pRet= new CCTiledGrid3D();

    if (pRet)
    {
        if (pRet->initWithSize(gridSize, pTexture, bFlipped))
        {
            pRet->autorelease();
        }
        else
        {
            delete pRet;
            pRet = NULL;
        }
    }

    return pRet;
}

CCTiledGrid3D* CCTiledGrid3D::create(const CCSize& gridSize)
{
    CCTiledGrid3D *pRet= new CCTiledGrid3D();

    if (pRet)
    {
        if (pRet->initWithSize(gridSize))
        {
            pRet->autorelease();
        }
        else
        {
            delete pRet;
            pRet = NULL;
        }
    }

    return pRet;
}

void CCTiledGrid3D::blit(void)
{
    int n = m_sGridSize.width * m_sGridSize.height;

    
    m_pShaderProgram->use();
    m_pShaderProgram->setUniformsForBuiltins();

    //
    // Attributes
    //
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );
#ifdef EMSCRIPTEN
    int numQuads = m_sGridSize.width * m_sGridSize.height;

    // position
    setGLBufferData(m_pVertices, (numQuads*4*sizeof(ccVertex3F)), 0);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texCoords
    setGLBufferData(m_pTexCoordinates, (numQuads*4*sizeof(ccVertex2F)), 1);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLIndexData(m_pIndices, n * 12, 0);
    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, 0);
#else
    // position
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, m_pVertices);

    // texCoords
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, m_pTexCoordinates);

    glDrawElements(GL_TRIANGLES, (GLsizei)n*6, GL_UNSIGNED_SHORT, m_pIndices);
#endif // EMSCRIPTEN


    CC_INCREMENT_GL_DRAWS(1);
}

void CCTiledGrid3D::calculateVertexPoints(void)
{
    float width = (float)m_pTexture->getPixelsWide();
    float height = (float)m_pTexture->getPixelsHigh();
    float imageH = m_pTexture->getContentSizeInPixels().height;
    
    int numQuads = m_sGridSize.width * m_sGridSize.height;
    CC_SAFE_FREE(m_pVertices);
    CC_SAFE_FREE(m_pOriginalVertices);
    CC_SAFE_FREE(m_pTexCoordinates);
    CC_SAFE_FREE(m_pIndices);

    m_pVertices = malloc(numQuads*4*sizeof(ccVertex3F));
    m_pOriginalVertices = malloc(numQuads*4*sizeof(ccVertex3F));
    m_pTexCoordinates = malloc(numQuads*4*sizeof(ccVertex2F));
    m_pIndices = (GLushort*)malloc(numQuads*6*sizeof(GLushort));

    GLfloat *vertArray = (GLfloat*)m_pVertices;
    GLfloat *texArray = (GLfloat*)m_pTexCoordinates;
    GLushort *idxArray = m_pIndices;
    
    int x, y;
    
    for( x = 0; x < m_sGridSize.width; x++ )
    {
        for( y = 0; y < m_sGridSize.height; y++ )
        {
            float x1 = x * m_obStep.x;
            float x2 = x1 + m_obStep.x;
            float y1 = y * m_obStep.y;
            float y2 = y1 + m_obStep.y;
            
            *vertArray++ = x1;
            *vertArray++ = y1;
            *vertArray++ = 0;
            *vertArray++ = x2;
            *vertArray++ = y1;
            *vertArray++ = 0;
            *vertArray++ = x1;
            *vertArray++ = y2;
            *vertArray++ = 0;
            *vertArray++ = x2;
            *vertArray++ = y2;
            *vertArray++ = 0;
            
            float newY1 = y1;
            float newY2 = y2;
            
            if (m_bIsTextureFlipped) 
            {
                newY1 = imageH - y1;
                newY2 = imageH - y2;
            }

            *texArray++ = x1 / width;
            *texArray++ = newY1 / height;
            *texArray++ = x2 / width;
            *texArray++ = newY1 / height;
            *texArray++ = x1 / width;
            *texArray++ = newY2 / height;
            *texArray++ = x2 / width;
            *texArray++ = newY2 / height;
        }
    }
    
    for (x = 0; x < numQuads; x++)
    {
        idxArray[x*6+0] = (GLushort)(x * 4 + 0);
        idxArray[x*6+1] = (GLushort)(x * 4 + 1);
        idxArray[x*6+2] = (GLushort)(x * 4 + 2);
        
        idxArray[x*6+3] = (GLushort)(x * 4 + 1);
        idxArray[x*6+4] = (GLushort)(x * 4 + 2);
        idxArray[x*6+5] = (GLushort)(x * 4 + 3);
    }
    
    memcpy(m_pOriginalVertices, m_pVertices, numQuads * 12 * sizeof(GLfloat));
}

void CCTiledGrid3D::setTile(const CCPoint& pos, const ccQuad3& coords)
{
    CCAssert( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (m_sGridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)m_pVertices;
    memcpy(&vertArray[idx], &coords, sizeof(ccQuad3));
}

ccQuad3 CCTiledGrid3D::originalTile(const CCPoint& pos)
{
    CCAssert( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (m_sGridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)m_pOriginalVertices;

    ccQuad3 ret;
    memcpy(&ret, &vertArray[idx], sizeof(ccQuad3));

    return ret;
}

ccQuad3 CCTiledGrid3D::tile(const CCPoint& pos)
{
    CCAssert( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (m_sGridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)m_pVertices;

    ccQuad3 ret;
    memcpy(&ret, &vertArray[idx], sizeof(ccQuad3));

    return ret;
}

void CCTiledGrid3D::reuse(void)
{
    if (m_nReuseGrid > 0)
    {
        int numQuads = m_sGridSize.width * m_sGridSize.height;

        memcpy(m_pOriginalVertices, m_pVertices, numQuads * 12 * sizeof(GLfloat));
        --m_nReuseGrid;
    }
}

NS_CC_END
