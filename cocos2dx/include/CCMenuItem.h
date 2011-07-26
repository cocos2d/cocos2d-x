/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2011 Ricardo Quesada
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

#ifndef __CCMENU_ITEM_H__
#define __CCMENU_ITEM_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "selector_protocol.h"

namespace cocos2d{

	class CCLabelTTF;
	class CCLabelAtlas;
	class CCSprite;

#define kCCItemSize 32

	/** @brief CCMenuItem base class
	*
	*  Subclass CCMenuItem (or any subclass) to create your custom CCMenuItem objects.
	*/
	class CC_DLL CCMenuItem : public CCNode
	{
		/** whether or not the item is selected
		@since v0.8.2
		*/
		CC_PROPERTY_READONLY(bool, m_bIsSelected, IsSelected);
		CC_PROPERTY(bool, m_bIsEnabled, IsEnabled);
	public:
		CCMenuItem()
			: m_bIsSelected(false)
            , m_bIsEnabled(false)            
            , m_pListener(NULL)			
			, m_pfnSelector(NULL)
		{}
		virtual ~CCMenuItem(){}
		/** Creates a CCMenuItem with a target/selector */
		static CCMenuItem * itemWithTarget(SelectorProtocol *rec, SEL_MenuHandler selector);
		/** Initializes a CCMenuItem with a target/selector */
		bool initWithTarget(SelectorProtocol *rec, SEL_MenuHandler selector);
		/** Returns the outside box */
		CCRect rect();
		/** Activate the item */
		virtual void activate();
		/** The item was selected (not activated), similar to "mouse-over" */
		virtual void selected();
		/** The item was unselected */
		virtual void unselected();
		/** Register a script function, the function is called in activete
		*  If pszFunctionName is NULL, then unregister it.
		*/
		virtual void registerScriptHandler(const char* pszFunctionName);

                /** set the target/selector of the menu item*/
                void setTarget(SelectorProtocol *rec, SEL_MenuHandler selector);
	protected:
		SelectorProtocol*	m_pListener;
		SEL_MenuHandler		m_pfnSelector;
		std::string         m_functionName;
	};

	/** @brief An abstract class for "label" CCMenuItemLabel items 
	Any CCNode that supports the CCLabelProtocol protocol can be added.
	Supported nodes:
	- CCBitmapFontAtlas
	- CCLabelAtlas
	- CCLabelTTF
	*/
	class CC_DLL CCMenuItemLabel : public CCMenuItem, public CCRGBAProtocol
	{
		/** the color that will be used to disable the item */
		CC_PROPERTY(ccColor3B, m_tDisabledColor, DisabledColor);
		/** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol */
		CC_PROPERTY(CCNode*, m_pLabel, Label);
	public:
		CCMenuItemLabel()
			: m_pLabel(NULL)
			, m_fOriginalScale(0.0)
		{}
		virtual ~CCMenuItemLabel();
		/** creates a CCMenuItemLabel with a Label, target and selector */
		static CCMenuItemLabel * itemWithLabel(CCNode*label, SelectorProtocol* target, SEL_MenuHandler selector);
		/** creates a CCMenuItemLabel with a Label. Target and selector will be nill */
		static CCMenuItemLabel* itemWithLabel(CCNode *label);
		/** initializes a CCMenuItemLabel with a Label, target and selector */
		bool initWithLabel(CCNode* label, SelectorProtocol* target, SEL_MenuHandler selector);
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
		virtual void setOpacity(GLubyte opacity);
		virtual GLubyte getOpacity();
		virtual void setColor(ccColor3B color);
		virtual ccColor3B getColor();

		virtual CCRGBAProtocol* convertToRGBAProtocol() { return (CCRGBAProtocol*)this; }
	protected:
		ccColor3B	m_tColorBackup;
		float		m_fOriginalScale;
	};

	/** @brief A CCMenuItemAtlasFont
	Helper class that creates a MenuItemLabel class with a LabelAtlas
	*/
	class CC_DLL CCMenuItemAtlasFont : public CCMenuItemLabel
	{
	public:
		CCMenuItemAtlasFont(){}
		virtual ~CCMenuItemAtlasFont(){}
		/** creates a menu item from a string and atlas with a target/selector */
		static CCMenuItemAtlasFont* itemFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
		/** creates a menu item from a string and atlas. Use it with MenuItemToggle */
		static CCMenuItemAtlasFont* itemFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MenuHandler selector);
		/** initializes a menu item from a string and atlas with a target/selector */
		bool initFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MenuHandler selector);
	};

	/** @brief A CCMenuItemFont
	Helper class that creates a CCMenuItemLabel class with a Label
	*/
	class CC_DLL CCMenuItemFont : public CCMenuItemLabel
	{
	public:
		CCMenuItemFont() : m_uFontSize(0), m_strFontName(""){}
		virtual ~CCMenuItemFont(){}
		/** set default font size */
		static void setFontSize(unsigned int s);
		/** get default font size */
		static unsigned int fontSize();
		/** set the default font name */
		static void setFontName(const char *name);
		/** get the default font name */
		static const char *fontName();
		/** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle */
		static CCMenuItemFont * itemFromString(const char *value);
		/** creates a menu item from a string with a target/selector */
		static CCMenuItemFont * itemFromString(const char *value, SelectorProtocol* target, SEL_MenuHandler selector);
		/** initializes a menu item from a string with a target/selector */
		bool initFromString(const char *value, SelectorProtocol* target, SEL_MenuHandler selector);

		/** set font size
		  * c++ can not overload static and non-static member functions with the same parameter types
		  * so change the name to setFontSizeObj
		  */
		void setFontSizeObj(unsigned int s);

		/** get font size */
		unsigned int fontSizeObj();

		/** set the font name 
		 * c++ can not overload static and non-static member functions with the same parameter types
		 * so change the name to setFontNameObj
		 */
		void setFontNameObj(const char* name);

		const char* fontNameObj();

	protected:
		void recreateLabel();

		unsigned int m_uFontSize;
		std::string m_strFontName;
	};

	/** @brief CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.
	The images has 3 different states:
	- unselected image
	- selected image
	- disabled image

	@since v0.8.0
	*/
	class CC_DLL CCMenuItemSprite : public CCMenuItem, public CCRGBAProtocol
	{
		/** the image used when the item is not selected */
		CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
		/** the image used when the item is selected */
		CC_PROPERTY(CCNode*, m_pSelectedImage, SelectedImage);
		/** the image used when the item is disabled */
		CC_PROPERTY(CCNode*, m_pDisabledImage, DisabledImage);
	public:
		CCMenuItemSprite()
			:m_pNormalImage(NULL)
			,m_pSelectedImage(NULL)
			,m_pDisabledImage(NULL)
		{}
		/** creates a menu item with a normal and selected image*/
		static CCMenuItemSprite * itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite);
		/** creates a menu item with a normal and selected image with target/selector */
		static CCMenuItemSprite * itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector);
		/** creates a menu item with a normal,selected  and disabled image with target/selector */
		static CCMenuItemSprite * itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MenuHandler selector);
		/** initializes a menu item with a normal, selected  and disabled image with target/selector */
		bool initFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MenuHandler selector);
		// super methods
        virtual void setColor(ccColor3B color);
        virtual ccColor3B getColor();
        virtual void setOpacity(GLubyte opacity);
        virtual GLubyte getOpacity();

        /**
        @since v0.99.5
        */
        virtual void selected();
        virtual void unselected();
        virtual void setIsEnabled(bool bEnabled);

		virtual CCRGBAProtocol* convertToRGBAProtocol() { return (CCRGBAProtocol*)this; }
	};

	/** @brief CCMenuItemImage accepts images as items.
	The images has 3 different states:
	- unselected image
	- selected image
	- disabled image

	For best results try that all images are of the same size
	*/
	class CC_DLL CCMenuItemImage : public CCMenuItemSprite
	{
	public:
		CCMenuItemImage(){}
		virtual ~CCMenuItemImage(){}
		/** creates a menu item with a normal and selected image*/
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage);
		/** creates a menu item with a normal,selected  and disabled image*/
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage);
		/** creates a menu item with a normal and selected image with target/selector */
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage, SelectorProtocol* target, SEL_MenuHandler selector);
		/** creates a menu item with a normal,selected  and disabled image with target/selector */
		static CCMenuItemImage* itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MenuHandler selector);
		/** initializes a menu item with a normal, selected  and disabled image with target/selector */
		bool initFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MenuHandler selector);
	};

	/** @brief A CCMenuItemToggle
	A simple container class that "toggles" it's inner items
	The inner itmes can be any MenuItem
	*/
	class CC_DLL CCMenuItemToggle : public CCMenuItem, public CCRGBAProtocol
	{
		/** conforms with CCRGBAProtocol protocol */
		CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
		/** conforms with CCRGBAProtocol protocol */
		CC_PROPERTY(ccColor3B, m_tColor, Color);
		/** returns the selected item */
		CC_PROPERTY(unsigned int, m_uSelectedIndex, SelectedIndex);
		/** CCMutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
		@since v0.7.2
		*/
		CC_PROPERTY(CCMutableArray<CCMenuItem*>*, m_pSubItems, SubItems);
	public:
		CCMenuItemToggle()
			: m_cOpacity(0)
            , m_uSelectedIndex(0)
			, m_pSubItems(NULL)			
		{}
		virtual ~CCMenuItemToggle();
		/** creates a menu item from a list of items with a target/selector */
		static CCMenuItemToggle* itemWithTarget(SelectorProtocol* target, SEL_MenuHandler selector, CCMenuItem* item, ...);		
		/** initializes a menu item from a list of items with a target selector */
		bool initWithTarget(SelectorProtocol* target, SEL_MenuHandler selector, CCMenuItem* item, va_list args);

		// The follow methods offered to lua
		/** creates a menu item with a item */
		static CCMenuItemToggle* itemWithItem(CCMenuItem *item);
		/** initializes a menu item with a item */
		bool initWithItem(CCMenuItem *item);
		/** add more menu item */
		void addSubItem(CCMenuItem *item);

		/** return the selected item */
		CCMenuItem* selectedItem();
		// super methods
		virtual void activate();
		virtual void selected();
		virtual void unselected();
		virtual void setIsEnabled(bool var);

		virtual CCRGBAProtocol* convertToRGBAProtocol() { return (CCRGBAProtocol*)this; }
	};

}

#endif //__CCMENU_ITEM_H__
