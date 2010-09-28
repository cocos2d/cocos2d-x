/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCNode.h"
#include "CCSprite.h"

namespace cocos2d {
	enum tImageFormat
	{
		kImageFormatJPG = 0,
		kImageFormatPNG = 1
	};
	/**
	RenderTexture is a generic rendering target. To render things into it,
	simply construct a render target, call begin on it, call visit on any cocos
	scenes or objects to render them, and call end. For convienience, render texture
	adds a sprite as it's display child with the results, so you can simply add
	the render texture to your scene and treat it like any other CocosNode.
	There are also functions for saving the render texture to disk in PNG or JPG format.

	@since v0.8.1
	*/
	class CCX_DLL CCRenderTexture : public CCNode 
	{
		/** sprite being used */
		CCX_PROPERTY(CCSprite*, m_pSprite, Sprite)
	public:
		CCRenderTexture(){}
		virtual ~CCRenderTexture();
		/** creates a RenderTexture object with width and height */
		static CCRenderTexture *renderTextureWithWidthAndHeight(int width, int height);
		/** initializes a RenderTexture object with width and height */
		bool initWithWidthAndHeight(int width, int height);
		void begin();
		void end();
		/** get buffer as UIImage */
		UIImage *getUIImageFromBuffer();
		/** saves the texture into a file */
		bool saveBuffer(const char *name);
		/** saves the texture into a file. The format can be JPG or PNG */
		bool saveBuffer(const char *name, int format);
		/** clears the texture with a color */
		void clear(float r, float g, float b, float a);
	protected:
		GLuint				m_uFBO;
		GLint				m_nOldFBO;
		CCTexture2D*		m_pTexture;
	};
} // namespace cocos2d
#endif //__CCRENDER_TEXTURE_H__