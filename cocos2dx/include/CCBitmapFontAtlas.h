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
#ifndef __CCBITMAP_FONT_ATLAS_H__
#define __CCBITMAP_FONT_ATLAS_H__
#include "CCSpriteSheet.h"
#include "platform/platform.h"
namespace cocos2d{

	struct _KerningHashElement;

	/** @struct ccBitmapFontDef
	bitmap font definition
	*/
	typedef struct _bitmapFontDef {
		//! ID of the character
		unsigned int charID;
		//! origin and size of the font
		CGRect rect;
		//! The X amount the image should be offset when drawing the image (in pixels)
		int xOffset;
		//! The Y amount the image should be offset when drawing the image (in pixels)
		int yOffset;
		//! The amount to move the current position after drawing the character (in pixels)
		int xAdvance;
	} ccBitmapFontDef;

	/** @struct ccBitmapFontPadding
	bitmap font padding
	@since v0.8.2
	*/
	typedef struct _bitmapFontPadding {
		/// padding left
		int	left;
		/// padding top
		int top;
		/// padding right
		int right;
		/// padding bottom
		int bottom;
	} ccBitmapFontPadding;

	enum {
		// how many characters are supported
		kCCBitmapFontAtlasMaxChars = 2048, //256,
	};

	/** CCBitmapFontConfiguration has parsed configuration of the the .fnt file
	@since v0.8
	*/
	class CCX_DLL CCBitmapFontConfiguration : public NSObject
	{
		// XXX: Creating a public interface so that the bitmapFontArray[] is accesible
	public://@public
		// The characters building up the font
		ccBitmapFontDef	m_pBitmapFontArray[kCCBitmapFontAtlasMaxChars];
		// FNTConfig: Common Height
		UINT32 m_uCommonHeight;
		// Padding
		ccBitmapFontPadding	m_tPadding;
		// atlas name
		std::string m_sAtlasName;
		// values for kerning
		struct _KerningHashElement	*m_pKerningDictionary;
	public:
		CCBitmapFontConfiguration(){}
		virtual ~CCBitmapFontConfiguration();
		char * description();
		/** allocates a CCBitmapFontConfiguration with a FNT file */
		static CCBitmapFontConfiguration * configurationWithFNTFile(const char *FNTfile);
		/** initializes a BitmapFontConfiguration with a FNT file */
		CCBitmapFontConfiguration * initWithFNTfile(const char *FNTfile);
	private:
		void parseConfigFile(const char *controlFile);
		void parseCharacterDefinition(std::string line, ccBitmapFontDef *characterDefinition);
		void parseInfoArguments(std::string line);
		void parseCommonArguments(std::string line);
		void parseImageFileName(std::string line, const char *fntFile);
		void parseKerningCapacity(std::string line);
		void parseKerningEntry(std::string line);
		void purgeKerningDictionary();
	};

	/** CCBitmapFontAtlas is a subclass of CCSpriteSheet.

	Features:
	- Treats each character like a CCSprite. This means that each individual character can be:
	- rotated
	- scaled
	- translated
	- tinted
	- chage the opacity
	- It can be used as part of a menu item.
	- anchorPoint can be used to align the "label"
	- Supports AngelCode text format

	Limitations:
	- All inner characters are using an anchorPoint of (0.5f, 0.5f) and it is not recommend to change it
	because it might affect the rendering

	CCBitmapFontAtlas implements the protocol CCLabelProtocol, like CCLabel and CCLabelAtlas.
	CCBitmapFontAtlas has the flexibility of CCLabel, the speed of CCLabelAtlas and all the features of CCSprite.
	If in doubt, use CCBitmapFontAtlas instead of CCLabelAtlas / CCLabel.

	Supported editors:
	- http://www.n4te.com/hiero/hiero.jnlp
	- http://slick.cokeandcode.com/demos/hiero.jnlp
	- http://www.angelcode.com/products/bmfont/

	@since v0.8
	*/

	class CCX_DLL CCBitmapFontAtlas : public CCSpriteSheet, public CCLabelProtocol, public CCRGBAProtocol
	{
		/** conforms to CCRGBAProtocol protocol */
		CCX_PROPERTY(GLubyte, m_cOpacity, Opacity)
		/** conforms to CCRGBAProtocol protocol */
		CCX_PROPERTY(ccColor3B, m_tColor, Color)
		/** conforms to CCRGBAProtocol protocol */
		CCX_PROPERTY(bool, m_bIsOpacityModifyRGB, IsOpacityModifyRGB)
	protected:
		// string to render
		std::string m_sString;
		CCBitmapFontConfiguration *m_pConfiguration;
	public:
		CCBitmapFontAtlas(){}
		virtual ~CCBitmapFontAtlas();
		/** Purges the cached data.
		Removes from memory the cached configurations and the atlas name dictionary.
		@since v0.99.3
		*/
		void purgeCachedData();
		/** creates a bitmap font altas with an initial string and the FNT file */
		static CCBitmapFontAtlas * bitmapFontAtlasWithString(const char *str, const char *fntFile);
		/** init a bitmap font altas with an initial string and the FNT file */
		CCBitmapFontAtlas * initWithString(const char *str, const char *fntFile);
		/** updates the font chars based on the string to render */
		void createFontChars();
		// super method
		virtual void setString(const char *label);
		virtual void setAnchorPoint(CGPoint var);
#if CC_BITMAPFONTATLAS_DEBUG_DRAW
		virtual void draw();
#endif // CC_BITMAPFONTATLAS_DEBUG_DRAW
	private:
		char * atlasNameFromFntFile(const char *fntFile);
		int kerningAmountForFirst(INT16 first, INT16 second);

	};

	/** Free function that parses a FNT file a place it on the cache
	*/
	CCBitmapFontConfiguration * FNTConfigLoadFile( const char *file );
	/** Purges the FNT config cache
	*/
	void FNTConfigRemoveCache( void );

}// namespace cocos2d

#endif //__CCBITMAP_FONT_ATLAS_H__