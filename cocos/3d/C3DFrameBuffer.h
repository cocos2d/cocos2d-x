#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include "Base.h"

#include "cocos2d.h"
#include "C3DViewport.h"

namespace cocos3d
{

class C3DRenderTarget;
class C3DDepthStencilTarget;

/**
 * Defines a frame buffer object that may contain one or more render targets and optionally
 * a depth-stencil target.
 *
 * Frame buffers can be created and used for off-screen rendering, which is useful for 
 * techniques such as shadow mapping and post-processing. 
 *
 * When binding a custom frame buffer, you should always store the return value of 
 * C3DFrameBuffer::bind and restore it when you are finished drawing to your frame buffer.
 *
 * To bind the default frame buffer, call C3DFrameBuffer::bindDefault.
 */
class C3DFrameBuffer : public cocos2d::CCObject
{
public:

    /**
     * Creates a new C3DFrameBuffer with a C3DRenderTarget of the specified width and height.
     */
	static C3DFrameBuffer* create(const char* id, unsigned int width, unsigned int height, unsigned int fmtColor = GL_RGBA, unsigned int fmtDepth = 0);
    static C3DFrameBuffer* getFrameBuffer(const char* id);

	/**
     * string id
     */
    const char* getID() const;

	/**
     * get & set render target.
     */
    void setRenderTarget(C3DRenderTarget* target);
    C3DRenderTarget* getRenderTarget() const;
 
	/**
     * get & set DepthStencilTarget
     */
    void setDepthStencilTarget(C3DDepthStencilTarget* target);
    C3DDepthStencilTarget* getDepthStencilTarget() const;
 
	/**
     * bind this frame buffer and render to it.
     */
    void bind();

	/**
     * bind default and render to display.
     */
    static void bindDefault(); //rendering to the display

	/**
     * restore to frame buffer before bind.
     */
    void unbind(); //restore framebuffer
	
	/**
     * get fbo handle.
     */
    FrameBufferHandle getFBO()
	{
		return _handle;
	}
    
    unsigned int getWidth() const
    {
        return _width;
    }
    
    unsigned int getHeight() const
    {
        return  _height;
    }
     
private:
 
	/**
     * Constructor & Destructor.
     */
    C3DFrameBuffer(const char* id);
    ~C3DFrameBuffer();

	// properties
    std::string _id;
    FrameBufferHandle _handle;
    C3DRenderTarget* _renderTarget;
    C3DDepthStencilTarget* _depthStencilTarget;

    unsigned int _width;
    unsigned int _height;
    bool _isBind;
    C3DViewport _oldViewport;
    GLint _oldFBO;
};

}

#endif
