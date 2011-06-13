//
//  AdvanceParticleQuadSystem.h
//  FlyingFreak
//
//  Created by varadharaj on 31/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef __ADVANCE_PARTICLE_QUAD_SYSTEM_H__
#define __ADVANCE_PARTICLE_QUAD_SYSTEM_H__

#include  "CCParticleSystem.h"

namespace cocos2d {
    
    class CCSpriteFrame;
    
    /** @brief CCParticleSystemQuad is a subclass of CCParticleSystem
     
     It includes all the features of ParticleSystem.
     
     Special features and Limitations:	
     - Particle size can be any float number.
     - The system can be scaled
     - The particles can be rotated
     - On 1st and 2nd gen iPhones: It is only a bit slower that CCParticleSystemPoint
     - On 3rd gen iPhone and iPads: It is MUCH faster than CCParticleSystemPoint
     - It consumes more RAM and more GPU memory than CCParticleSystemPoint
     - It supports subrects
     @since v0.8
     */
    class CC_DLL AdvanceParticleQuadSystem : public CCParticleSystem
    {
    protected:
        ccV2F_C4F_T2F_Quad	*m_pQuads;		// quads to be rendered
        GLushort			*m_pIndices;	// indices
        ccTime m_dt;
        //! chars per row
        int m_nItemsPerRow;
        //! chars per column
        int m_nItemsPerColumn;
        
        //! width of each char
        int	m_nItemWidth;
        //! height of each char
        int	m_nItemHeight;
        
        ccTime m_FrameRate;
        
        bool m_bNeedsToRemoveParticleAfterAniamtion;
        
#if CC_USES_VBO
        GLuint				m_uQuadsID;	// VBO id
#endif
    public:
        AdvanceParticleQuadSystem()
		:m_pQuads(NULL)
		,m_pIndices(NULL)
        ,m_nItemsPerRow(0)
        ,m_nItemsPerColumn(0)
        ,m_nItemWidth(0)
        ,m_nItemHeight(0)
        ,m_bNeedsToRemoveParticleAfterAniamtion(false)
        {}
        virtual ~AdvanceParticleQuadSystem();
        /** initialices the indices for the vertices*/
        void initIndices();
        
        /** initilizes the texture with a rectangle measured Points */
        void initTexCoordsWithRect(CCRect rect);
        
        /** Sets a new CCSpriteFrame as particle.
         WARNING: this method is experimental. Use setTexture:withRect instead.
         @since v0.99.4
         */
        void setDisplayFrame(CCSpriteFrame *spriteFrame);
        
        /** Sets a new texture with a rect. The rect is in Points.
         @since v0.99.4
         */
        void setTextureWithRect(CCTexture2D *texture, CCRect rect);
        
        /****************  Setting Particle Animation Texture  *****************/
        
        void setDisplayFrameForAnimation(CCSpriteFrame *spriteFrame, int tileWidth, int tileHeight, int number_Frames_per_Second, bool NeedsToRemoveParticleAfterAniamtion);
        
        void setTextureWithRectForAnimation(CCTexture2D *texture, CCRect rect, int tileWidth, int tileHeight, int number_Frames_per_Second, bool NeedsToRemoveParticleAfterAniamtion);
        
        void setFrameRate(int number_Frames_per_Second){m_FrameRate = calculateFrameRate(number_Frames_per_Second);}
        void setFrameRate(float frameRate){m_FrameRate = frameRate;}
        
         /**********************************************************************/
        // super methods
        virtual bool initWithTotalParticles(int numberOfParticles);
        virtual void setTexture(CCTexture2D* var);
        virtual void updateQuadWithParticle(tCCParticle* particle, CCPoint newPosition);
        virtual void postStep();
        virtual void update(ccTime dt);
        virtual void draw();
        //
        
    private :
        void calculateMaxItems();
        float calculateFrameRate(int number_frames){return 1.0f / number_frames;}
    };
    
}// namespace cocos2d

#endif //__CC_PARTICLE_SYSTEM_QUAD_H__

