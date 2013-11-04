#ifndef DEPTHSTENCILTARGET_H_
#define DEPTHSTENCILTARGET_H_

#include "Base.h"
#include "cocos2d.h"

namespace cocos3d
{
class C3DTexture;

/**
 * Defines a contain for depth and stencil targets in a frame buffer object.
 *
 * This class assumes that the target hardware supports depth textures, since
 * creation of a C3DDepthStencilTarget always attempts to create an underlying
 * depth texture.
 */
class C3DDepthStencilTarget : public cocos2d::CCObject
{
    friend class C3DFrameBuffer;

public:

    /**
     * Defines the accepted formats for DepthStencilTargets.
     */
    enum Format
    {
        /**
         * A target with 24-bits of depth data.
         *
         * This format may be internally stored as a 32-bit buffer with 8 bits of unused data.
         */
        DEPTH16 = 1,

        /**
         * A target with 24 bits of depth data and 8 bits stencil data.
         */
        DEPTH24_STENCIL8
    };

	/**
     * create DepthStencilTarget
     */
    static C3DDepthStencilTarget* create(const char* id, Format format, unsigned int width, unsigned int height);
    static C3DDepthStencilTarget* getDepthStencilTarget(const char* id);

	/**
     * id string
     */
    const char* getID() const;

	/**
     * DepthStencilTarget format.
     */
    Format getFormat() const;

	/**
     * Texture associate to DepthStencilTarge.
     */
    C3DTexture* getTexture() const;

private:
	/**
     * Constructor & Destructor.
     */
    C3DDepthStencilTarget(const char* id, Format format);
    ~C3DDepthStencilTarget();

	//properties
    std::string _id;
    Format _format;
    C3DTexture* _depthTexture;
    RenderBufferHandle _stencilBuffer;
};

}

#endif
