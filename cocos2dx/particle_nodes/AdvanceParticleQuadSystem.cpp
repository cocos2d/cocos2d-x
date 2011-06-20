//
//  AdvanceParticleQuadSystem.cpp
//  FlyingFreak
//
//  Created by varadharaj on 31/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "AdvanceParticleQuadSystem.h"
#include "platform/CCGL.h"
#include "CCSpriteFrame.h"

namespace cocos2d {
    
    //implementation AdvanceParticleQuadSystem
    
    // overriding the init method
    bool AdvanceParticleQuadSystem::initWithTotalParticles(int numberOfParticles)
    {
        // base initialization
        if( CCParticleSystem::initWithTotalParticles(numberOfParticles) ) 
        {
            // allocating data space
            m_pQuads = new ccV2F_C4F_T2F_Quad[m_nTotalParticles];
            m_pIndices = new GLushort[m_nTotalParticles * 6];
            
            if( !m_pQuads || !m_pIndices) 
            {
                CCLOG("cocos2d: Particle system: not enough memory");
                if( m_pQuads )
                    delete [] m_pQuads;
                if(m_pIndices)
                    delete [] m_pIndices;
                this->release();
                return NULL;
            }
            
            // initialize only once the texCoords and the indices
            if (m_pTexture)
            {
                this->initTexCoordsWithRect(CCRectMake((float)0, (float)0, (float)m_pTexture->getPixelsWide(), (float)m_pTexture->getPixelsHigh()));
            }
            else
            {
                this->initTexCoordsWithRect(CCRectMake((float)0, (float)0, (float)1, (float)1));
            }
            
            this->initIndices();
            
#if CC_USES_VBO
            // create the VBO buffer
            glGenBuffers(1, &m_uQuadsID);
            
            // initial binding
            glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0])*m_nTotalParticles, m_pQuads, GL_DYNAMIC_DRAW);	
            glBindBuffer(GL_ARRAY_BUFFER, 0);	
#endif
            return true;
        }
        return false;
    }
    AdvanceParticleQuadSystem::~AdvanceParticleQuadSystem()
    {
        CC_SAFE_DELETE_ARRAY(m_pQuads);
        CC_SAFE_DELETE_ARRAY(m_pIndices);
#if CC_USES_VBO
        glDeleteBuffers(1, &m_uQuadsID);
#endif
    }
    
    
    /*************************************   Animation Classes ***************************************************/
    
    void AdvanceParticleQuadSystem::setDisplayFrameForAnimation(cocos2d::CCSpriteFrame *spriteFrame, int tileWidth, int tileHeight, int number_Frames_per_Second, bool NeedsToRemoveParticleAfterAniamtion)
    {
        m_nItemWidth = tileWidth;
        m_nItemHeight = tileHeight;
        m_bNeedsToRemoveParticleAfterAniamtion = NeedsToRemoveParticleAfterAniamtion;
        // Only update the texture if is different from the current one
        if( !m_pTexture || spriteFrame->getTexture()->getName() != m_pTexture->getName() )
        {
            CCParticleSystem::setTexture(spriteFrame->getTexture());
        }
        
        if(tileWidth > 0 && tileHeight > 0 && number_Frames_per_Second > 0)
        {
            calculateMaxItems();
            m_FrameRate = calculateFrameRate(number_Frames_per_Second);
        }
        else
            this->initTexCoordsWithRect(spriteFrame->getRect());
    }
    
    void AdvanceParticleQuadSystem::setTextureWithRectForAnimation(cocos2d::CCTexture2D *texture, cocos2d::CCRect rect, int tileWidth, int tileHeight, int number_Frames_per_Second, bool NeedsToRemoveParticleAfterAniamtion)
    {
        m_nItemWidth = tileWidth;
        m_nItemHeight = tileHeight;
        m_bNeedsToRemoveParticleAfterAniamtion = NeedsToRemoveParticleAfterAniamtion;
        // Only update the texture if is different from the current one
        if( !m_pTexture || texture->getName() != m_pTexture->getName() )
        {
            CCParticleSystem::setTexture(texture);
        }
        
        if(tileWidth > 0 && tileHeight > 0 && number_Frames_per_Second > 0)
        {
            calculateMaxItems();
            m_FrameRate = calculateFrameRate(number_Frames_per_Second);
        }
        else
            this->initTexCoordsWithRect(rect);
    }
    
    void AdvanceParticleQuadSystem::calculateMaxItems()
    {
        if(m_nItemHeight <= 0 || m_nItemWidth<= 0)return;
        
        CCSize s = m_pTexture->getContentSizeInPixels();
        m_nItemsPerColumn = (int)(s.height / m_nItemHeight);
        m_nItemsPerRow = (int)(s.width / m_nItemWidth);
    }
    
    /***************************************************************************************/
    
    
    // rect should be in Texture coordinates, not pixel coordinates
    void AdvanceParticleQuadSystem::initTexCoordsWithRect(CCRect pointRect)
    {
        // convert to Tex coords
        
        CCRect rect = CCRectMake(
                                 pointRect.origin.x * CC_CONTENT_SCALE_FACTOR(),
                                 pointRect.origin.y * CC_CONTENT_SCALE_FACTOR(),
                                 pointRect.size.width * CC_CONTENT_SCALE_FACTOR(),
                                 pointRect.size.height * CC_CONTENT_SCALE_FACTOR());
        
        GLfloat wide = (GLfloat) pointRect.size.width;
        GLfloat high = (GLfloat) pointRect.size.height;
        
        if (m_pTexture)
        {
            wide = (GLfloat)m_pTexture->getPixelsWide();
            high = (GLfloat)m_pTexture->getPixelsHigh();
        }
        
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        GLfloat left = (rect.origin.x*2+1) / (wide*2);
        GLfloat bottom = (rect.origin.y*2+1) / (high*2);
        GLfloat right = left + (rect.size.width*2-2) / (wide*2);
        GLfloat top = bottom + (rect.size.height*2-2) / (high*2);
#else
        GLfloat left = rect.origin.x / wide;
        GLfloat bottom = rect.origin.y / high;
        GLfloat right = left + rect.size.width / wide;
        GLfloat top = bottom + rect.size.height / high;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        
        // Important. Texture in cocos2d are inverted, so the Y component should be inverted
        CC_SWAP( top, bottom, float);
        
        for(int i=0; i<m_nTotalParticles; i++) 
        {
            // bottom-left vertex:
            m_pQuads[i].bl.texCoords.u = left;
            m_pQuads[i].bl.texCoords.v = bottom;
            // bottom-right vertex:
            m_pQuads[i].br.texCoords.u = right;
            m_pQuads[i].br.texCoords.v = bottom;
            // top-left vertex:
            m_pQuads[i].tl.texCoords.u = left;
            m_pQuads[i].tl.texCoords.v = top;
            // top-right vertex:
            m_pQuads[i].tr.texCoords.u = right;
            m_pQuads[i].tr.texCoords.v = top;
        }
    }
    
    void AdvanceParticleQuadSystem::setTextureWithRect(CCTexture2D *texture, CCRect rect)
    {
        // Only update the texture if is different from the current one
        if( !m_pTexture || texture->getName() != m_pTexture->getName() )
        {
            CCParticleSystem::setTexture(texture);
        }
        
        this->initTexCoordsWithRect(rect);
    }
    void AdvanceParticleQuadSystem::setTexture(CCTexture2D* var)
    {
        this->setTextureWithRect(var, CCRectMake(0, 0, 
                                                 (float)(var->getPixelsWide() / CC_CONTENT_SCALE_FACTOR()), 
                                                 (float)(var->getPixelsHigh() / CC_CONTENT_SCALE_FACTOR())));
    }
    void AdvanceParticleQuadSystem::setDisplayFrame(CCSpriteFrame *spriteFrame)
    {
        CCAssert( CCPoint::CCPointEqualToPoint( spriteFrame->getOffsetInPixels() , CCPointZero ), "QuadParticle only supports SpriteFrames with no offsets");
        
        // update texture before updating texture rect
        if ( !m_pTexture || spriteFrame->getTexture()->getName() != m_pTexture->getName())
        {
            this->setTexture(spriteFrame->getTexture());
        }
    }
    void AdvanceParticleQuadSystem::initIndices()
    {
        for( int i = 0; i < m_nTotalParticles; ++i)
        {
            const int i6 = i*6;
            const int i4 = i*4;
            m_pIndices[i6+0] = (GLushort) i4+0;
            m_pIndices[i6+1] = (GLushort) i4+1;
            m_pIndices[i6+2] = (GLushort) i4+2;
            
            m_pIndices[i6+5] = (GLushort) i4+1;
            m_pIndices[i6+4] = (GLushort) i4+2;
            m_pIndices[i6+3] = (GLushort) i4+3;
        }
    }
    
    void AdvanceParticleQuadSystem::update(ccTime dt)
    {
        m_dt = dt;
        CCParticleSystem::update(dt);
    }
    
    void AdvanceParticleQuadSystem::updateQuadWithParticle(tCCParticle* particle, CCPoint newPosition)
    {
        //Texture
        
        if(m_nItemWidth > 0 && m_nItemHeight > 0 && m_FrameRate > 0)
        {
            particle->pElaspeTime += m_dt;
            
            while (particle->pElaspeTime >= m_FrameRate) 
            {
                particle->pElaspeTime -= m_FrameRate;
                
                particle->pTexPos.width++;
                if(particle->pTexPos.width == m_nItemsPerRow)
                {
                    particle->pTexPos.width = 0;
                    particle->pTexPos.height++;
                    if(particle->pTexPos.height == m_nItemsPerColumn)
                    {
                        particle->pTexPos.height = 0;
                        if(m_bNeedsToRemoveParticleAfterAniamtion)
                            particle->timeToLive = 0;
                        return;
                    }
                } 
                
            }
            GLfloat wide = 0;
            GLfloat high = 0;
            if (m_pTexture)
            {
                wide = (GLfloat)m_pTexture->getPixelsWide();
                high = (GLfloat)m_pTexture->getPixelsHigh();
            }
        
            GLfloat left = (particle->pTexPos.width * m_nItemWidth)/ wide;
            GLfloat bottom = (particle->pTexPos.height * m_nItemHeight) / high;
            GLfloat right = left + m_nItemWidth / wide;
            GLfloat top = bottom + m_nItemHeight / high;
            
            // Important. Texture in cocos2d are inverted, so the Y component should be inverted
            CC_SWAP( top, bottom, float);
            
            // bottom-left vertex:
            m_pQuads[m_nParticleIdx].bl.texCoords.u = left;
            m_pQuads[m_nParticleIdx].bl.texCoords.v = bottom;
            // bottom-right vertex:
            m_pQuads[m_nParticleIdx].br.texCoords.u = right;
            m_pQuads[m_nParticleIdx].br.texCoords.v = bottom;
            // top-left vertex:
            m_pQuads[m_nParticleIdx].tl.texCoords.u = left;
            m_pQuads[m_nParticleIdx].tl.texCoords.v = top;
            // top-right vertex:
            m_pQuads[m_nParticleIdx].tr.texCoords.u = right;
            m_pQuads[m_nParticleIdx].tr.texCoords.v = top;
        }
        
        // colors
        ccV2F_C4F_T2F_Quad *quad = &(m_pQuads[m_nParticleIdx]);
        quad->bl.colors = particle->color;
        quad->br.colors = particle->color;
        quad->tl.colors = particle->color;
        quad->tr.colors = particle->color;
        
        // vertices
        GLfloat size_2 = particle->size/2;
        if( particle->rotation ) 
        {
            GLfloat x1 = -size_2;
            GLfloat y1 = -size_2;
            
            GLfloat x2 = size_2;
            GLfloat y2 = size_2;
            GLfloat x = newPosition.x;
            GLfloat y = newPosition.y;
            
            GLfloat r = (GLfloat)-CC_DEGREES_TO_RADIANS(particle->rotation);
            GLfloat cr = cosf(r);
            GLfloat sr = sinf(r);
            GLfloat ax = x1 * cr - y1 * sr + x;
            GLfloat ay = x1 * sr + y1 * cr + y;
            GLfloat bx = x2 * cr - y1 * sr + x;
            GLfloat by = x2 * sr + y1 * cr + y;
            GLfloat cx = x2 * cr - y2 * sr + x;
            GLfloat cy = x2 * sr + y2 * cr + y;
            GLfloat dx = x1 * cr - y2 * sr + x;
            GLfloat dy = x1 * sr + y2 * cr + y;
            
            // bottom-left
            quad->bl.vertices.x = ax;
            quad->bl.vertices.y = ay;
            
            // bottom-right vertex:
            quad->br.vertices.x = bx;
            quad->br.vertices.y = by;
            
            // top-left vertex:
            quad->tl.vertices.x = dx;
            quad->tl.vertices.y = dy;
            
            // top-right vertex:
            quad->tr.vertices.x = cx;
            quad->tr.vertices.y = cy;
        } else {
            // bottom-left vertex:
            quad->bl.vertices.x = newPosition.x - size_2;
            quad->bl.vertices.y = newPosition.y - size_2;
            
            // bottom-right vertex:
            quad->br.vertices.x = newPosition.x + size_2;
            quad->br.vertices.y = newPosition.y - size_2;
            
            // top-left vertex:
            quad->tl.vertices.x = newPosition.x - size_2;
            quad->tl.vertices.y = newPosition.y + size_2;
            
            // top-right vertex:
            quad->tr.vertices.x = newPosition.x + size_2;
            quad->tr.vertices.y = newPosition.y + size_2;				
        }
    }
    void AdvanceParticleQuadSystem::postStep()
    {
#if CC_USES_VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_pQuads[0])*m_nParticleCount, m_pQuads);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
    }
    
    // overriding draw method
    void AdvanceParticleQuadSystem::draw()
    {	
        // Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
        // Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
        // Unneeded states: -
        glBindTexture(GL_TEXTURE_2D, m_pTexture->getName());
        
#define kQuadSize sizeof(m_pQuads[0].bl)
        
#if CC_USES_VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsID);
        
#if CC_ENABLE_CACHE_TEXTTURE_DATA
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0])*m_nTotalParticles, m_pQuads, GL_DYNAMIC_DRAW);	
#endif
        glVertexPointer(2,GL_FLOAT, kQuadSize, 0);
        
        glColorPointer(4, GL_FLOAT, kQuadSize, (GLvoid*) offsetof(ccV2F_C4F_T2F,colors) );
        
        glTexCoordPointer(2, GL_FLOAT, kQuadSize, (GLvoid*) offsetof(ccV2F_C4F_T2F,texCoords) );
#else   // vertex array list
        
        int offset = (int) m_pQuads;
        
        // vertex
        int diff = offsetof( ccV2F_C4F_T2F, vertices);
        glVertexPointer(2,GL_FLOAT, kQuadSize, (GLvoid*) (offset+diff) );
        
        // color
        diff = offsetof( ccV2F_C4F_T2F, colors);
        glColorPointer(4, GL_FLOAT, kQuadSize, (GLvoid*)(offset + diff));
        
        // tex coords
        diff = offsetof( ccV2F_C4F_T2F, texCoords);
        glTexCoordPointer(2, GL_FLOAT, kQuadSize, (GLvoid*)(offset + diff));
        
#endif // ! CC_USES_VBO
        
        bool newBlend = (m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST) ? true : false;
        if( newBlend )
        {
            glBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
        }
        
        CCAssert( m_nParticleIdx == m_nParticleCount, "Abnormal error in particle quad");
        
        glDrawElements(GL_TRIANGLES, m_nParticleIdx*6, GL_UNSIGNED_SHORT, m_pIndices);
        
        // restore blend state
        if( newBlend )
            glBlendFunc( CC_BLEND_SRC, CC_BLEND_DST );
        
#if CC_USES_VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
        
        // restore GL default state
        // -
    }
    
}// namespace cocos2d
