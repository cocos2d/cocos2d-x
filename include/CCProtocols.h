#ifndef __CCPROTOCOLS_H__
#define __CCPROTOCOLS_H__

#include "ccTypes.h"
#include "CCTexture2D.h"

#include <string>

// CC RGBA protocol
class CCRGBAProtocol
{
    /** sets Color
     @since v0.8
     */
    virtual void setColor(ccColor3B color) = 0;

	/** returns the color
	 @since v0.8
	 */
	virtual ccColor3B color(void) = 0;

    // returns the opacity
    virtual GLubyte opacity(void) = 0;

	/** sets the opacity.
	 @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
	 Values goes from 0 to 255, where 255 means fully opaque.
	 */
	virtual void setOpacity(GLubyte opacity) = 0;

	// optional

	/** sets the premultipliedAlphaOpacity property.
	 If set to NO then opacity will be applied as: glColor(R,G,B,opacity);
	 If set to YES then oapcity will be applied as: glColor(opacity, opacity, opacity, opacity );
	 Textures with premultiplied alpha will have this property by default on YES. Otherwise the default value is NO
	 @since v0.8
	 */
	virtual void setOpacityModifyRGB(BOOL bValue) {}

	/** returns whether or not the opacity will be applied using glColor(R,G,B,opacity) or glColor(opacity, opacity, opacity, opacity);
	 @since v0.8
	 */
	virtual BOOL doesOpacityModifyRGB(void) = { return FALSE;}
}

/**
 You can specify the blending fuction.
 @since v0.99.0
 */
class CCBlendProtocol
{
	// set the source blending function for the texture
	virtual void setBlendFunc(ccBlendFunc blendFunc) = 0;

	// returns the blending function used for the texture
	virtual ccBlendFunc blendFunc(void);
}

/** CCNode objects that uses a Texture2D to render the images.
 The texture can have a blending function.
 If the texture has alpha premultiplied the default blending function is:
    src=GL_ONE dst= GL_ONE_MINUS_SRC_ALPHA
 else
	src=GL_SRC_ALPHA dst= GL_ONE_MINUS_SRC_ALPHA
 But you can change the blending funtion at any time.
 @since v0.8.0
 */
class CCTextureProtocol : public CCBlendProtocol
{
	// returns the used texture
	virtual CCTexture2D* texture(void) = 0;

	// sets a new texture. it will be retained
	virtual void setTexture(CCTexture2D *texture) {}
}

// Common interface for Labels
class CCLabelProtocol
{
	// sets a new label using an string
	virtual void setString(std::string &label) = 0;

	// optional
	/** sets a new label using a CString.
     It is faster than setString since it doesn't require to alloc/retain/release an NString object.
     @since v0.99.0
    */
	virtual void setCString(char *pLabel) {}
}

#endif // __CCPROTOCOLS_H__
