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

#ifndef __CCMENU_ITEM_H__
#define __CCMENU_ITEM_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "selector_protocol.h"
#include "platform/platform.h"

namespace cocos2d{

	class CCLabel;
	class CCLabelAtlas;
	class CCSprite;

#define kItemSize 32

	/** CCMenuItem base class
	*
	*  Subclass CCMenuItem (or any subclass) to create your custom CCMenuItem objects.
	*/
	class CCX_DLL CCMenuItem : public CCNode
	{
		/** whether or not the item is selected
		@since v0.8.2
		*/
		CCX_PROPERTY_READONLY(bool, m_bIsSelected, IsSelected);
		CCX_PROPERTY(bool, m_bIsEnabled, IsEnabled);
	public:
		CCMenuItem()
			:m_pListener(NULL)
		{}
		virtual ~CCMenuItem(){}
		/** Creates a CCMenuItem with a target/selector */
		static CCMenuItem * itemWithTarget(SelectorProtocol *rec, SEL_MunuHandler selector);
		/** Initializes a CCMenuItem with a target/selector */
		CCMenuItem * initWithTarget(SelectorProtocol *rec, SEL_MunuHandler selector);
		/** Returns the outside box */
		CGRect rect();
		/** Activate the item */
		virtual void activate();
		/** The item was selected (not activated), similar to "mouse-over" */
		virtual void selected();
		/** The item was unselected */
		virtual void unselected();
	protected:
		SelectorProtocol*	m_pListener;
		SEL_MunuHandler		m_pfnSelector;
	};

	/** An abstract class for "label" CCMenuItemLabel items 
	Any CCNode that supports the CCLabelProtocol protocol can be added.
	Supported nodes:
	- CCBitmapFontAtlas
	- CCLabelAtlas
	- CCLabel
	*/
	class CCX_DLL CCMenuItemLabel : public CCMenuItem, public CCRGBAProtocol
	{
		/** the color that will be used to disable the item */
		CCX_PROPERTY(ccColor3B, m_tDisabledColor, DisabledColor);
		/** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol */
		CCX_PROPERTY(CCNode*, m_pLabel, Lable);
	public:
		CCMenuItemLabel()
			:m_pLabel(NULL)
		{}
		virtual ~CCMenuItemLabel();
		/** creates a CCMenuItemLabel with a Label, target and selector */
		static CCMenuItemLabel * itemWithLabel(CCNode*label, SelectorProtocol* target, SEL_MunuHandler selector);
		/** initializes a CCMenuItemLabel with a Label, target and selector */
		CCMenuItemLabel * initWithLabel(CCNode* label, SelectorProtocol* target, SEL_MunuHandler selector);
		/** sets a new string to the inner label */
		void setString(const char * label);
		// super methods
		virtual void activate();
		virtual void selected();
		virtual void unselected();
		/** Enable or disabled the CCMenuItemFont
		@warning setIsEnabled changes the RGB color of the font
		*/
		virtual void setIsEnabled(bool enabled);
		virtual void draw();
		virtual void setOpacity(GLubyte opacity);
		virtual GLubyte getOpacity();
		virtual void setColor(ccColor3B color);
		virtual ccColor3B getColor();
	protected:
		ccColor3B	m_tColorBackup;
		float		m_fOriginalScale;
	};

	/** A CCMenuItemAtlasFont
	Helper class that creates a MenuItemLabel class with a LabelAtlas
	*/
	class CCX_DLL CCMenuItemAtlasFont : public CCMenuItemLabel
	{
	public:
		CCMenuItemAtlasFont(){}
		virtual ~CCMenuItemAtlasFont(){}
		/** creates a menu item from a string and atlas with a target/selector */
		static CCMenuItemAtlasFont* itemFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
		/** creates a menu item from a string and atlas. Use it with MenuItemToggle */
		static CCMenuItemAtlasFont* itemFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MunuHandler selector);
		/** initializes a menu item from a string and atlas with a target/selector */
		CCMenuItemAtlasFont* initFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MunuHandler selector);
	};

	/** A CCMenuItemFont
	Helper class that creates a CCMenuItemLabel class with a Label
	*/
	class CCX_DLL CCMenuItemFont : public CCMenuItemLabel
	{
	public:
		CCMenuItemFont(){}
		virtual ~CCMenuItemFont(){}
		/** set font size */
		static void setFontSize(int s);
		/** get font size */
		static int fontSize();
		/** set the font name */
		static void setFontName(const char *name);
		/** get the font name */
		static const char *fontName();
		/** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle */
		static CCMenuItemFont * itemFromString(const char *value);
		/** creates a menu item from a string with a target/selector */
		static CCMenuItemFont * itemFromString(const char *value, SelectorProtocol* target, SEL_MunuHandler selector);
		/** initializes a menu item from a string with a target/selector */
		CCMenuItemFont * initFromString(const char *value, SelectorProtocol* target, SEL_MunuHandler selector);
	};

	/** CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.
	The images has 3 different states:
	- unselected image
	- selected image
	- disabled image

	@since v0.8.0
	*/
	class CCX_DLL CCMenuItemSprite : public CCMenuItem, public CCRGBAProtocol
	{
		/** the image used when the item is not selected */
		CCX_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
		/** the image used when the item is selected */
		CCX_PROPERTY(CCNode*, m_pSelectedImage, SelectedImage);
		/** the image used when the item is disabled */
		CCX_PROPERTY(CCNode*, m_pDisabledImage, DisabledImage);
	public:
		CCMenuItemSprite()
			:m_pNormalImage(NULL)
			,m_pSelectedImage(NULL)
			,m_pDisabledImage(NULL)
		{}
		virtual ~CCMenuItemSprite();
		/** creates a menu item with a normal and selected image*/
		static CCMenuItemSprite * itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite);
		/** creates a menu item with a normal and selected image with target/selector */
		static CCMenuItemSprite * itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MunuHandler selector);
		/** creates a menu item with a normal,selected  and disabled image with target/selector */
		static CCMenuItemSprite * itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MunuHandler selector);
		/** initializes a menu item with a normal, selected  and disabled image with target/selector */
		CCMenuItemSprite * initFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MunuHandler selector);
		// super methods
		virtual void draw();
		virtual void setColor(ccColor3B color){}
		virtual ccColor3B getColor(){return ccBLACK;}
		virtual void setOpacity(GLubyte opacity){}
		virtual GLubyte getOpacity(){return 0;}
	};

	/** CCMenuItemImage accepts images as items.
	The images has 3 different states:
	- unselected image
	- selected image
	- disabled image

	For best results try that all images are of the same size
	*/
	class CCX_DLL CCMenuItemImage : public CCMenuItemSprite
	{
	public:
		CCMenuItemImage(){}
		virtual ~CCMenuItemImage(){}
		/** creates a menu item with a normal and selected image*/
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage);
		/** creates a menu item with a normal,selected  and disabled image*/
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage);
		/** creates a menu item with a normal and selected image with target/selector */
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage, SelectorProtocol* target, SEL_MunuHandler selector);
		/** creates a menu item with a normal,selected  and disabled image with target/selector */
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MunuHandler selector);
		/** initializes a menu item with a normal, selected  and disabled image with target/selector */
		CCMenuItemImage* initFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MunuHandler selector);
		// super methods
		virtual void setColor(ccColor3B color);
		virtual ccColor3B getColor();
		virtual void setOpacity(GLubyte opacity);
		virtual GLubyte getOpacity();
	};

	/** A CCMenuItemToggle
	A simple container class that "toggles" it's inner items
	The inner itmes can be any MenuItem
	*/
	class CCX_DLL CCMenuItemToggle : public CCMenuItem, public CCRGBAProtocol
	{
		/** conforms with CCRGBAProtocol protocol */
		CCX_PROPERTY(GLubyte, m_cOpacity, Opacity);
		/** conforms with CCRGBAProtocol protocol */
		CCX_PROPERTY(ccColor3B, m_tColor, Color);
		/** returns the selected item */
		CCX_PROPERTY(UINT32, m_uSelectedIndex, SelectedIndex);
		/** NSMutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
		@since v0.7.2
		*/
		CCX_PROPERTY(NSMutableArray<CCMenuItem*>*, m_pSubItems, SubItems);
	public:
		CCMenuItemToggle(){}
		virtual ~CCMenuItemToggle();
		/** creates a menu item from a list of items with a target/selector */
		static CCMenuItemToggle* itemWithTarget(SelectorProtocol* target, SEL_MunuHandler selector, CCMenuItem* item, ...);
		/** initializes a menu item from a list of items with a target selector */
		CCMenuItemToggle* initWithTarget(SelectorProtocol* target, SEL_MunuHandler selector, CCMenuItem* item, va_list args);
		/** return the selected item */
		CCMenuItem* selectedItem();
		// super methods
		virtual void activate();
		virtual void selected();
		virtual void unselected();
		virtual void setIsEnabled(bool var);
	};

}

#endif //__CCMENU_ITEM_H__