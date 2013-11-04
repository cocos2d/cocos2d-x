#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include "C3DNode.h"
#include "C3DVector2.h"
#include "C3DPostEffect.h"

namespace cocos3d
{
class C3DFrameBuffer;
class C3DTexture;
class C3DSampler;
class C3DMaterial;
class C3DModel;
class C3DPostEffect;
class C3DPass;

    
/**
Post process
A C3DPostProcess can have serial post effect, but with only one active right now
*/
    

    
class C3DPostProcess : public C3DNode
{
    
public:
    
public:
    /**
     * create post process
     */   
    static C3DPostProcess* create(const char* id, unsigned int texWidth, unsigned int texHeight/*, const char* techniqueId*/);
	
	/**
     * get type inherit from C3DNode
     */
	virtual C3DNode::Type getType() const { return C3DNode::NodeType_PostProcess; };
	/**
     * get frame buffer
     */
	C3DFrameBuffer* getFrameBuffer() const;             

	/**
     * begin & end draw
     */
    virtual bool beginDraw();
    virtual void endDraw();

	/**
     * draw routine
     */
	virtual void draw();
        
    virtual void transformChanged();
    
	/**
     * set active post effect by type
     */
    void setPostEffect(PostEffectType type);

	/**
     * get frame buffer width
     */
	unsigned int getFBWidth();
	/**
     * get frame buffer height
     */
	unsigned int getFBHeight();
    
    C3DModel* getModel()
    {
        return _model;
    }
    
    /**
     * get frame buffer sampler
     */
    C3DSampler* getFramebufferSampler()
    {
        return _sampler;
    }

    C3DPostEffect* getActiveEffect()
    {
        return _curPostEffect;
    }

protected:
	/**
     * constructor & destructor
     */
	C3DPostProcess();    
	C3DPostProcess(const char* id,C3DFrameBuffer* buffer);
    virtual ~C3DPostProcess();

	bool _isDraw;

	// properties
    C3DFrameBuffer* _framebuffer;
    C3DSampler* _sampler;//frame buffer sampler
    

	C3DModel* _model;

	std::vector<C3DPostEffect*> _postEffects;

	C3DPostEffect* _curPostEffect;

	unsigned int _fbWidth;
	unsigned int _fbHeight;
    
};
    	
}

#endif
