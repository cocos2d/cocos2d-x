/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __COCOS2DX_CAMERA_H__
#define __COCOS2DX_CAMERA_H__

#include <string>

#include "cocoa/CCObject.h"
#include "ccMacros.h"
#include "kazmath/mat4.h"


NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

/** 
A Camera is used in every Node.
Useful to look at the object from different views.
The OpenGL gluLookAt() function is used to locate the
camera.

If the object is transformed by any of the scale, rotation or
position attributes, then they will override the camera.

IMPORTANT: Either your use the camera or the rotation/scale/position properties. You can't use both.
World coordinates won't work if you use the camera.

Limitations:

- Some nodes, like ParallaxNode, Particle uses world node coordinates, and they won't work properly if you move them (or any of their ancestors)
using the camera.

- It doesn't work on batched nodes like Sprite objects when they are parented to a SpriteBatchNode object.

- It is recommended to use it ONLY if you are going to create 3D effects. For 2D effects, use the action Follow or position/scale/rotate.

*/
class CC_DLL Camera : public Object
{
public:
    /** returns the Z eye */
    static float getZEye();
    /**
     * @js ctor
     */
    Camera(void);
    /**
     * @js NA
     * @lua NA
     */
    ~Camera(void);

    void init(void);
    /**
     * @js NA
     * @lua NA
     */
    const char* description(void) const;

    /** sets the dirty value */
    inline void setDirty(bool bValue) { _dirty = bValue; }
    /** get the dirty value */
    inline bool isDirty(void) const { return _dirty; }

    /** sets the camera in the default position */
    void restore(void);
    /** Sets the camera using gluLookAt using its eye, center and up_vector */
    void locate(void);
    /** sets the eye values in points */
    void setEye(float fEyeX, float fEyeY, float fEyeZ);
    /**
     @deprecated. Use setEye() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void setEyeXYZ(float fEyeX, float fEyeY, float fEyeZ){ setEye(fEyeX, fEyeY, fEyeZ);}
    /** sets the center values in points */
    void setCenter(float fCenterX, float fCenterY, float fCenterZ);
    /**
     @deprecated. Use setCenter() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void setCenterXYZ(float fCenterX, float fCenterY, float fCenterZ){ setCenter(fCenterX,fCenterY,fCenterZ);}
    /** sets the up values */
    void setUp(float fUpX, float fUpY, float fUpZ);
    /**
     @deprecated. Use setUp() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void setUpXYZ(float fUpX, float fUpY, float fUpZ){ setUp(fUpX,fUpY,fUpZ); }

    /** get the eye vector values in points 
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var getEye()
     * in lua:local getEye()
     * @endcode
     */
    void getEye(float *pEyeX, float *pEyeY, float *pEyeZ) const;
    /**
     @deprecated. Use getEye() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void getEyeXYZ(float *pEyeX, float *pEyeY, float *pEyeZ) const { getEye(pEyeX, pEyeY, pEyeZ); }
    /** get the center vector values int points 
     * when this function bound to js or lua,the input params are changed
     * in js: var getCenter()
     * in lua:local getCenter()
     */
    void getCenter(float *pCenterX, float *pCenterY, float *pCenterZ) const;
    /**
     @deprecated. Use getCenter() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void getCenterXYZ(float *pCenterX, float *pCenterY, float *pCenterZ) const{ getCenter(pCenterX,pCenterY,pCenterZ); }
    /** get the up vector values 
     * when this function bound to js or lua,the input params are changed
     * in js: var getUp()
     * in lua:local getUp()
     */
    void getUp(float *pUpX, float *pUpY, float *pUpZ) const;
    /**
     @deprecated. Use getUp() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void getUpXYZ(float *pUpX, float *pUpY, float *pUpZ) const{ getUp(pUpX, pUpY, pUpZ); }

protected:
    float _eyeX;
    float _eyeY;
    float _eyeZ;

    float _centerX;
    float _centerY;
    float _centerZ;

    float _upX;
    float _upY;
    float _upZ;

    bool _dirty;
    kmMat4    _lookupMatrix;

private:
    DISALLOW_COPY_AND_ASSIGN(Camera);
};

// end of base_node group
/// @}

NS_CC_END

#endif // __COCOS2DX_CAMERA_H__
