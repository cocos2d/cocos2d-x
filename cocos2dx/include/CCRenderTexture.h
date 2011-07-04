/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      Jason Booth

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
#ifndef __CCRENDER_TEXTURE_H__
#define __CCRENDER_TEXTURE_H__

#include "CCData.h"
#include "CCNode.h"
#include "CCSprite.h"

namespace cocos2d {

typedef enum eImageFormat
{
	kCCImageFormatJPG       = 0,
	kCCImageFormatPNG       = 1,
    kCCImageFormatRawData   = 2
} tImageFormat;
/**
@brief CCRenderTexture is a generic rendering target. To render things into it,
simply construct a render target, call begin on it, call visit on any cocos
scenes or objects to render them, and call end. For convienience, render texture
adds a sprite as it's display child with the results, so you can simply add
the render texture to your scene and treat it like any other CocosNode.
There are also functions for saving the render texture to disk in PNG or JPG format.

@since v0.8.1
*/
class CC_DLL CCRenderTexture : public CCNode 
{
    /** The CCSprite being used.
    The sprite, by default, will use the following blending function: GL_ONE, GL_ONE_MINUS_SRC_ALPHA.
    The blending function can be changed in runtime by calling:
    - [[renderTexture sprite] setBlendFunc:(ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];
    */
	CC_PROPERTY(CCSprite*, m_pSprite, Sprite)
public:
	CCRenderTexture();
	virtual ~CCRenderTexture();
    /** creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    static CCRenderTexture * renderTextureWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat);

    /** creates a RenderTexture object with width and height in Points, pixel format is RGBA8888 */
    static CCRenderTexture * renderTextureWithWidthAndHeight(int w, int h);

    /** initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    bool initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat);

    /** starts grabbing */
	void begin();

    /** starts rendering to the texture while clearing the texture first.
    This is more efficient then calling -clear first and then -begin */
    void beginWithClear(float r, float g, float b, float a);

    
    /** end is key word of lua, use other name to export to lua. */
	inline void endToLua(){ end();};

	/** ends grabbing */
    void end();

    /** clears the texture with a color */
    void clear(float r, float g, float b, float a);

	/** saves the texture into a file */
	bool saveBuffer(const char *name);
	/** saves the texture into a file. The format can be JPG or PNG */
	bool saveBuffer(const char *name, int format);

    /* get buffer as UIImage, can only save a render buffer which has a RGBA8888 pixel format */
    CCData *getUIImageAsDataFromBuffer(int format);
protected:
	GLuint				m_uFBO;
	GLint				m_nOldFBO;
	CCTexture2D*		m_pTexture;

    GLenum              m_ePixelFormat;
};

} // namespace cocos2d

#endif //__CCRENDER_TEXTURE_H__