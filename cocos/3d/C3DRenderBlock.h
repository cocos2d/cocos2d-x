#ifndef RENDERBLOCK_H_
#define RENDERBLOCK_H_

#include "Base.h"

#include "cocos2d.h"

NS_CC_BEGIN


class C3DNode;

class C3DPass;

class ElementNode;

/**
* Defines the render state of the graphics device.
*/
class C3DStateBlock : public cocos2d::CCObject
{
	friend class C3DRenderState;       
	friend class C3DRenderSystem;

public:

	enum Blend
	{
		BLEND_ZERO = GL_ZERO,
		BLEND_ONE = GL_ONE,
		BLEND_SRC_COLOR = GL_SRC_COLOR,
		BLEN_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
		BLEND_DST_COLOR = GL_DST_COLOR,
		BLEND_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
		BLEND_SRC_ALPHA = GL_SRC_ALPHA,
		BLEND_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		BLEND_DST_ALPHA = GL_DST_ALPHA,
		BLEND_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
		BLEND_CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
		BLEND_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
		BLEND_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE
	};

	static void initialize();

	/**
	* Static finalizer that is called during game shutdown.
	*/
	static void finalize();

	/**
	* Creates a new StateBlock with default render state settings.
	*/
	static C3DStateBlock* create();

	/**
	* Binds the state in this StateBlock to the renderer.
	*
	* This method handles both setting and restoring of render states to ensure that
	* only the state explicitly defined by this StateBlock is applied to the renderer.
	*/
	void bind();

	/**
	* Toggles blending.
	*
	* @param enabled true to enable, false to disable.
	*/
	void setBlend(bool enabled);

	/**
	* Explicitly sets the source used in the blend function for this render state.
	*
	* Note that the blend function is only applied when blending is enabled.
	*
	* @param blend Specifies how the source blending factors are computed.
	*/
	void setBlendSrc(Blend blend);

	/**
	* Explicitly sets the source used in the blend function for this render state.
	*
	* Note that the blend function is only applied when blending is enabled.
	*
	* @param blend Specifies how the destination blending factors are computed.
	*/
	void setBlendDst(Blend blend);

	/**
	* Explicitly enables or disables backface culling.
	*
	* @param enabled true to enable, false to disable.
	*/
	void setCullFace(bool enabled);

	/**
	* Toggles depth testing.
	*
	* @param enabled true to enable, false to disable.
	*/
	void setDepthTest(bool enabled);

	/** 
	* Toggles depth writing.
	*
	* @param enabled true to enable, false to disable.
	*/
	void setDepthWrite(bool enabled);

	/**
	* Sets a render state from the given name and value strings.
	*
	* This method attempts to interpret the passed in strings as render state
	* name and value. This is normally used when loading render states from
	* material files.
	*
	* @param name Name of the render state to set.
	* @param value Value of the specified render state.
	*/
	void setState(const char* name, const char* value);

	/**
	* backup current opengl state to this instance, and sync current state with the opengl state.
	*/
	void backUpGLState();

	/**
	* restore opengl state.
	*/
	void restoreGLState(bool bforce = false);

	bool load(ElementNode* node);
	bool save(ElementNode* node);

	bool getBlendEnable()const{return _blendEnabled;}
	bool getCullFaceEnable()const{return _cullFaceEnabled;}
	bool getDepthTestEnabled()const{return _depthTestEnabled;}
	bool getDepthWriteEnabled()const{return _depthWriteEnabled;}
	Blend getSrcBlend()const{return _srcBlend;}
	Blend getDstBlend()const{return _dstBlend;}
	long getBits()const{return _bits;}

private:

	/**
	* Constructor.
	*/
	C3DStateBlock();

	/**
	* Destructor.
	*/
	~C3DStateBlock();

	void bindNoRestore();

	static void restore(long stateOverrideBits);

	static void enableDepthWrite();

	// States
	bool _blendEnabled;
	bool _cullFaceEnabled;
	bool _depthTestEnabled;
	bool _depthWriteEnabled;
	Blend _srcBlend;
	Blend _dstBlend;
	// State bits
	long _bits;

	static C3DStateBlock* _defaultState;
};

extern const char* blendToString(C3DStateBlock::Blend blend);
extern C3DStateBlock::Blend parseBlend(const char* value);

NS_CC_END


#endif // RENDERBLOCK_H_
