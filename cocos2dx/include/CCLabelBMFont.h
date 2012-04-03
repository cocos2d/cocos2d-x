/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

Use any of these editors to generate BMFonts:
  http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
  http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
  http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
  http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#ifndef __CCBITMAP_FONT_ATLAS_H__
#define __CCBITMAP_FONT_ATLAS_H__

#include "CCSpriteBatchNode.h"
#include <map>
#include <vector>

namespace cocos2d{

	struct _KerningHashElement;

	/**
    @struct ccBMFontDef
    BMFont definition
	*/
	typedef struct _BMFontDef {
		//! ID of the character
		unsigned int charID;
		//! origin and size of the font
		CCRect rect;
		//! The X amount the image should be offset when drawing the image (in pixels)
		int xOffset;
		//! The Y amount the image should be offset when drawing the image (in pixels)
		int yOffset;
		//! The amount to move the current position after drawing the character (in pixels)
		int xAdvance;
	} ccBMFontDef;

    /** @struct ccBMFontPadding
    BMFont padding
	@since v0.8.2
	*/
	typedef struct _BMFontPadding {
		/// padding left
		int	left;
		/// padding top
		int top;
		/// padding right
		int right;
		/// padding bottom
		int bottom;
	} ccBMFontPadding;


	/** @brief CCBMFontConfiguration has parsed configuration of the the .fnt file
	@since v0.8
	*/
	class CC_DLL CCBMFontConfiguration : public CCObject
	{
		// XXX: Creating a public interface so that the bitmapFontArray[] is accesible
	public://@public
		//! The characters building up the font
        std::map<unsigned int, ccBMFontDef>* m_pBitmapFontArray;

		//! FNTConfig: Common Height
		unsigned int m_uCommonHeight;
		//! Padding
		ccBMFontPadding	m_tPadding;
		//! atlas name
		std::string m_sAtlasName;
		//! values for kerning
		struct _KerningHashElement	*m_pKerningDictionary;
	public:
		CCBMFontConfiguration();
		virtual ~CCBMFontConfiguration();
		char * description();
		/** allocates a CCBMFontConfiguration with a FNT file */
		static CCBMFontConfiguration * configurationWithFNTFile(const char *FNTfile);
		/** initializes a BitmapFontConfiguration with a FNT file */
		bool initWithFNTfile(const char *FNTfile);
	private:
		void parseConfigFile(const char *controlFile);
		void parseCharacterDefinition(std::string line, ccBMFontDef *characterDefinition);
		void parseInfoArguments(std::string line);
		void parseCommonArguments(std::string line);
		void parseImageFileName(std::string line, const char *fntFile);
		void parseKerningCapacity(std::string line);
		void parseKerningEntry(std::string line);
		void purgeKerningDictionary();
	};

	/** @brief CCLabelBMFont is a subclass of CCSpriteSheet.

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

	CCLabelBMFont implements the protocol CCLabelProtocol, like CCLabel and CCLabelAtlas.
	CCLabelBMFont has the flexibility of CCLabel, the speed of CCLabelAtlas and all the features of CCSprite.
	If in doubt, use CCLabelBMFont instead of CCLabelAtlas / CCLabel.

	Supported editors:
    http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
    http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
    http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
    http://www.angelcode.com/products/bmfont/ (Free, Windows only)

	@since v0.8
	*/

	class CC_DLL CCLabelBMFont : public CCSpriteBatchNode, public CCLabelProtocol, public CCRGBAProtocol
	{
		/** conforms to CCRGBAProtocol protocol */
		CC_PROPERTY(GLubyte, m_cOpacity, Opacity)
		/** conforms to CCRGBAProtocol protocol */
		CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color)
		/** conforms to CCRGBAProtocol protocol */
		CC_PROPERTY(bool, m_bIsOpacityModifyRGB, IsOpacityModifyRGB)
	protected:
		// string to render
		unsigned short* m_sString;
		std::string m_sString_initial;
		CCBMFontConfiguration *m_pConfiguration;
		CCTextAlignment m_pAlignment;
		float m_fWidth;
		bool m_bLineBreakWithoutSpaces;
	public:
		CCLabelBMFont()
			: m_cOpacity(0)           
			, m_bIsOpacityModifyRGB(false)
            , m_pConfiguration(NULL)
			, m_bLineBreakWithoutSpaces(false)
		{}
		virtual ~CCLabelBMFont();
		/** Purges the cached data.
		Removes from memory the cached configurations and the atlas name dictionary.
		@since v0.99.3
		*/
		static void purgeCachedData();
		/** creates a bitmap font altas with an initial string and the FNT file */
		static CCLabelBMFont * labelWithString(const char *str, const char *fntFile);
		static CCLabelBMFont * labelWithString(const char *str, const char *fntFile, CCTextAlignment alignment, float width);

		/** init a bitmap font altas with an initial string and the FNT file */
		bool initWithString(const char *str, const char *fntFile, CCTextAlignment alignment, float width);
		bool initWithString(const char *str, const char *fntFile);
		/** updates the font chars based on the string to render */
		void createFontChars();
		// super method
		virtual void setString(const char *label);
		virtual void setString(const char *label, bool fromUpdate);
		virtual void updateString(bool fromUpdate);
		virtual const char* getString(void);
        virtual void setCString(const char *label);
		virtual void setAnchorPoint(const CCPoint& var);
		virtual void updateLabel();
		virtual void setAlignment(CCTextAlignment alignment);
		virtual void setWidth(float width);
		virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);

#if CC_LABELBMFONT_DEBUG_DRAW
		virtual void draw();
#endif // CC_LABELBMFONT_DEBUG_DRAW
	private:
		char * atlasNameFromFntFile(const char *fntFile);
		int kerningAmountForFirst(unsigned short first, unsigned short second);

	};

	/** Free function that parses a FNT file a place it on the cache
	*/
	CC_DLL CCBMFontConfiguration * FNTConfigLoadFile( const char *file );
	/** Purges the FNT config cache
	*/
	CC_DLL void FNTConfigRemoveCache( void );
}// namespace cocos2d

#endif //__CCBITMAP_FONT_ATLAS_H__
