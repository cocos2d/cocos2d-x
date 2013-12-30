#ifndef Viewport_H__
#define Viewport_H__

#include "EnumDef_GL.h"

namespace cocos2d
{
class C3DCamera;
class C3DRenderTarget;

/**
Defines view port.
With corner(x, y) and width, height
*/
class C3DViewport
{
public:

	/**
	* Constructor & Destructor.
	*/
	C3DViewport(int left, int top, int width, int height);
	C3DViewport(const C3DViewport& viewport);
	virtual ~C3DViewport();

	/**
	* comparison.
	*/
	C3DViewport& operator == (const C3DViewport& viewport);

	/**
	* apply viewport.
	*/
	void apply();

public:
	//properties
	int x;
	int y;
	int width;
	int height;
};
}

#endif
