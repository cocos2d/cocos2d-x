#ifndef POSTEFFECT_H
#define POSTEFFECT_H
#include "cocos2d.h"
#include "C3DVector2.h"
#include "C3DVector3.h"


namespace cocos3d
{

class C3DPostProcess;
class C3DTechnique;
class C3DSampler;
class C3DMaterial;
class C3DFrameBuffer;
class C3DModel;

/**
* post effect type
*/
enum PostEffectType
{
    Post_Effect_None,
    Post_Effect_Color,
    Post_Effect_Blur,
    Post_Effect_Outline,
    Post_Effect_SpaceWrap,
    Post_Effect_Bloom,
};


/**
  Base class of post effect 
*/
class C3DPostEffect : public cocos2d::CCObject
{
protected:

	/**
     * Constructor & Destructor
     */
	
    C3DPostEffect(C3DPostProcess* postProcess, const char* szName);
    virtual ~C3DPostEffect();
    
    
    
public:
    
    virtual PostEffectType getPostEffectType() const
    {
        return Post_Effect_None;
    }

	/**
     * create post effect
     */
	static C3DPostEffect* create(PostEffectType type, C3DPostProcess* postProcess, const char* name);
    
    
    /**
     * draw routine
     */
    virtual void draw();
	
	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter(){};
    
    
    virtual bool init(const char* szMaterial);

public:
	// properties
	C3DPostProcess* _postProcess;
    std::string _name;
    C3DMaterial* _material;
    
};

/**
Blur post effect
*/
class C3DBlurPE : public C3DPostEffect
{
    friend class C3DPostEffect;
protected:
	/**
     * Constructor & Destructor
     */
	
    C3DBlurPE(C3DPostProcess* postProcess, const char* szName): C3DPostEffect(postProcess, szName)
    {
        
    }
    virtual ~C3DBlurPE();
    
public:
    
    virtual PostEffectType getPostEffectType() const
    {
        return Post_Effect_Blur;
    }
    

	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter();
   	
       
};

/**
Gray color post effect
*/
class C3DColorPE : public C3DPostEffect
{
    friend class C3DPostEffect;
protected:
	/**
     * Constructor & Destructor
     */
	C3DColorPE(C3DPostProcess* postProcess, const char* name): C3DPostEffect(postProcess, name), _colorRate(1.5f, 1.0f, 0.5f)
    {
        
    }
    virtual ~C3DColorPE();
    
public:
    
    virtual PostEffectType getPostEffectType() const
    {
        return Post_Effect_Color;
    }

	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter();
    
    void setColorRate(const C3DVector3& colorRate)
    {
        _colorRate = colorRate;
    }
    
    const C3DVector3& getColorRate() const
    {
        return _colorRate;
    }
    
protected:
    
    C3DVector3 _colorRate;
};

/**
Edge post effect
*/
class C3DOutlinePE : public C3DPostEffect
{
    friend class C3DPostEffect;
protected:
	/**
     * Constructor & Destructor
     */
	C3DOutlinePE(C3DPostProcess* postProcess, const char* name): C3DPostEffect(postProcess, name)
    {
        
    }
    virtual ~C3DOutlinePE();
    
public:
    virtual PostEffectType getPostEffectType() const
    {
        return Post_Effect_Outline;
    }

	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter();
       
};

/**
Space wrap post effect
*/
class C3DSpaceWrap : public C3DPostEffect
{
    friend class C3DPostEffect;
protected:
	/**
     * Constructor & Destructor
     */
	C3DSpaceWrap(C3DPostProcess* postProcess, const char* name);
    
	virtual ~C3DSpaceWrap();
    
public:
    
    virtual PostEffectType getPostEffectType() const
    {
        return Post_Effect_SpaceWrap;
    }

	/**
     * set post effect shader parameter
     */
	virtual void setShaderParameter();

	/**
     * set pixelsize
     */
	void setPixelSize(const C3DVector2& pixelsize)
	{
		_pixelSize = pixelsize;
	}

	/**
     * set space wrap speed
     */
	void setWrapSpeed(float wrapSpeed)
	{
		_wrapSpeed = wrapSpeed;
	}

	/**
     * set space wrap scale
     */
	void setWrapScale(float wrapScale)
	{
		_wrapScale = wrapScale;
	}

protected:
	// properties
	C3DVector2 _pixelSize;
	float _wrapSpeed;
	float _wrapScale;
	C3DSampler* _wrapSampler;
};

/**
* Bloom effect
*/
class C3DBloomPE : public C3DPostEffect
{
    friend class C3DPostEffect;
    
protected:
    /**
     * Constructor & Destructor
     */
	C3DBloomPE(C3DPostProcess* postProcess, const char* name);
    
	virtual ~C3DBloomPE();
    
public:

    
    virtual bool init(const char* szMaterial);
        
    /**
     * draw routine
     */
    virtual void draw();
        
    /**
     * get & set bloom parameter, brightness threshold
     */
    void setBloomThreshold(float threshold);
    float getBloomThreshold() const;
        
    
protected:
                
    bool initBloomParam();
                
    //bloom parameter
    float  _BloomThreshold;    //
        
        
    C3DFrameBuffer* _brightFrameBuffer; // frame buffer for select bright pixels
    C3DFrameBuffer* _blurFrameBufferX; // frame buffer for blur
    C3DFrameBuffer* _blurFrameBufferY;
    
    C3DFrameBuffer* _blurFrameBuffer;
        
};

	
}

#endif
