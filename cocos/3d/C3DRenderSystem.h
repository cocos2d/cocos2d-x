#ifndef RenderSystem_H_
#define RenderSystem_H_
#include "EnumDef_GL.h"
#include "cocos2d.h"

namespace cocos2d
{
class Rectangle;
class Vector4;
class C3DViewport;
class C3DAnimationController;
class RenderChannelManager;
class C3DEffectManager;
class C3DMaterialManager;
/**
Defines the view port and clear flag
*/
class  C3DRenderSystem : public cocos2d::CCObject
{
	friend class C3DLayer;
public:
	/**
	* get singleton
	*/
	static C3DRenderSystem* getInstance();

	/**
	* set & get view port
	*/
	void setViewport(float x,float y,float width,float height);
	void setViewport(const C3DViewport* viewport = nullptr);
	const C3DViewport* getViewport() const;

	/**
	* get render channel manager
	*/
	RenderChannelManager* getRenderChannelManager() const;

	/**
	* update routine
	*/
	void update(long elapsedTime);
	/**
	* Clears the specified resource buffers to the specified clear values.
	*
	* @param flags The flags indicating which buffers to be cleared.
	* @param clearColor The color value to clear to when the flags includes the color buffer.
	* @param clearDepth The depth value to clear to when the flags includes the color buffer.
	* @param clearStencil The stencil value to clear to when the flags includes the color buffer.
	*/
	void clear(ClearFlags flags, const Vector4* clearColor, float clearDepth, int clearStencil);

protected:

	/**
	* constructor & destructor
	*/
	C3DRenderSystem();
	virtual ~C3DRenderSystem();

	/**
	* create render system
	*/
	static C3DRenderSystem* create();
	/**
	* initialize & finalize
	*/
	void initialize();
	void finalize();

	// properties
	C3DViewport* _viewport;                        // the games's current viewport.
	RenderChannelManager* _renderChannelManager;

	C3DEffectManager* _effectManager;
	C3DMaterialManager* _materialManager;

	Vector4* _clearColor;                        // The clear color value last used for clearing the color buffer.

	float _clearDepth;                          // The clear depth value last used for clearing the depth buffer.
	int _clearStencil;                          // The clear stencil value last used for clearing the stencil buffer.
};
}

#endif
