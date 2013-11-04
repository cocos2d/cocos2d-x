#ifndef C3DPARTICLERENDER_H_
#define C3DPARTICLERENDER_H_

#include "cocos2d.h"
#include "C3DMatrix.h"
#include "C3DRenderBlock.h"

namespace cocos3d
{

class C3DParticleSystem;
    class C3DMaterial;
    class C3DEffect;
    class C3DTexture;
    class C3DVertexDeclaration;
	class C3DElementNode;
    class C3DBatchModel;
    class C3DVector2;
	class C3DSampler;

/**
 * This class render a particle system.
 * Note that C3DParticleRender only use one material, and it will draw it with one draw call.
 */
class C3DParticleRender/*: public cocos2d::CCObject*/
{
   
public:

	/**
     * Destructor & Destructor.
     */
	C3DParticleRender(C3DParticleSystem* system); 
    virtual ~C3DParticleRender();

    /**
     * create particle render.
	 * @param system particle system it belongs to
	 * @param szMaterialFile material file name .material
	 * @param capacity maximum particles it can render
     */
    static C3DParticleRender* create(C3DParticleSystem* system, unsigned int capacity);
    
	/**
     * particle render init method.
	 * @param capacity maximum particles it can render
     */
	bool init(unsigned int capacity);

	
	/**
     * load from element node
     */
	void load(C3DElementNode* properties);

	/**
     * save to element node
     */
	void save(C3DElementNode* properties);
    
	/**
     * called before draw by particle system
     */
    virtual void prepareDraw();
    
    /**
     * draw the particles, call flush() to present it to the render target
     */
    virtual void draw();
    
    /**
     * finish render flush it to the render target
     */
    virtual void flush();
    
    /**
     * resize capacity with new size
     */
    void reSizeCapacity(int nCapacity);

	/**
     * get particle capacity
     */
	int getParticleCapacity() const { return _nCapacity; }
    
    
	/**
     * get & set texture atlas row and column
     */
	void setFrameCountRow(int nRow);
	int getFrameCountRow() const { return _nFrameRow; }
	void setFrameCountCol(int nCol);
	int getFrameCountCol() const { return _nFrameCol; }

	/**
     * get & set texture atlas total frame count, equals to _nFrameRow * _nFrameCol
     */
	int getFrameCount() const { return _nFrameCount; }

	/**
     * get & set Whether animate particle frame
	 * can animate the particle texture when texture _nFrameRow > 1 or _nFrameCol > 1
     */
	bool isSpriteAnimated() const { return _spriteAnimated; }
	void setSpriteAnimated(bool bAnimated) { _spriteAnimated = bAnimated; }

	/**
     * get & set Whether particle texture animation loop ?
     */
	bool isSpriteLoop() const { return _spriteLooped; }
	void setSpriteLoop(bool bSpriteLoop) { _spriteLooped = bSpriteLoop; }

	/**
     * set & get duration between two particle frame, unit seconds
     */
	float getSpriteFrameDurationSecs() const { return _spriteFrameDurationSecs; }
	void setSpriteFrameDurationSecs(float dur) { _spriteFrameDurationSecs = dur; }

	/**
     * set & get random start frame of new particles, particle begin frame 0 - _spriteFrameRandomOffset
     */
	int getSpriteFrameRandomOffset() const { return _spriteFrameRandomOffset; }
	void setSpriteFrameRandomOffset(int randOff) { _spriteFrameRandomOffset = randOff; }

	/**
     * get & set particle is visible
     */
	bool isVisible() const { return _isVisible; }
	void setVisible(bool bVisible) { _isVisible = bVisible; }

	const char* getParticleVs() const{ return _particleVs.c_str(); }
	void setParticleVs(const char* szVs) { _particleVs = szVs; reloadMaterial(); }

	const char* getParticleFs() const { return _particleFs.c_str(); }
	void setParticleFs(const char* szFs) { _particleFs = szFs; reloadMaterial(); }

	const char* getParticleTexture() const { return _partilceTexture.c_str(); }
	void setParticleTexture(const char* szTex) { _partilceTexture = szTex; reloadMaterial(); }

	C3DStateBlock::Blend getParticleSrcBlend() const { return _srcBlend; }
	void setParticleSrcBlend(C3DStateBlock::Blend blend);

	C3DStateBlock::Blend getParticleDstBlend() const { return _dstBlend; }
	void setParticleDstBlend(C3DStateBlock::Blend blend);

	void reloadMaterial();
	/**
     * clone method
     */
	C3DParticleRender* clone(C3DParticleSystem* system) const;
private:

    /**
     * Copy constructor.
     * 
     * @param copy The SpriteBatch to copy.
     */
    C3DParticleRender(const C3DParticleRender& copy);

	/**
     * init particle texture coordinate.
     */
	void initFrameCoord();
    
    int _nCapacity; // max number of particles
    int _nParticle; // number of particles
    
    C3DBatchModel*        _model; // used for render

	C3DParticleSystem* _system; // particle system it belongs to

	cocos3d::C3DVector2* _frameCoord; // texture coord
	int _nFrameRow;//row number of frame texture
	int _nFrameCol;// col number of frame texture
	int _nFrameCount; // _nFrameRow * _nFrameCol

	bool _spriteAnimated; // frame animation
	bool _spriteLooped; // frame loop 
	float _spriteFrameDurationSecs;// used when frame loop is false

	int _spriteFrameRandomOffset; // particle frame start at 0 - _spriteFrameRandomOffset

	bool _isVisible; // is particle visible

	std::string _particleVs;//particle vertex shader
	std::string _particleFs;//particle fragment shader
	std::string _partilceTexture;//particle texture
	C3DStateBlock::Blend _srcBlend;
	C3DStateBlock::Blend _dstBlend;
};

}

#endif
