/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

// C++ includes
#include <functional>

// cocos2d includes
#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

typedef std::function<void(CCObject*)> ccMenuCallback;

class CCLabelTTF;
class CCLabelAtlas;
class CCSprite;
class CCSpriteFrame;
#define kCCItemSize 32
    
/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */

/** @brief CCMenuItem base class
 *
 *  Subclass CCMenuItem (or any subclass) to create your custom CCMenuItem objects.
 */
class CC_DLL CCMenuItem : public CCNodeRGBA
{
public:
    CCMenuItem()
    : _selected(false)
    , _enabled(false)            
    , _scriptTapHandler(0)
	, _callback(nullptr)
    , _target(NULL)
    {}
    virtual ~CCMenuItem();

    /** Creates a CCMenuItem with no target/selector */
    static CCMenuItem* create();
    /** Creates a CCMenuItem with a target/selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItem* create(CCObject *rec, SEL_MenuHandler selector);
    /** Creates a CCMenuItem with a target/selector */
    static CCMenuItem* create(const ccMenuCallback& callback);
    /** Initializes a CCMenuItem with a target/selector */
    bool initWithCallback(const ccMenuCallback& callback);
    /** Initializes a CCMenuItem with a target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget( CCObject *rec, SEL_MenuHandler selector);
    /** Returns the outside box */
    CCRect rect();
    /** Activate the item */
    virtual void activate();
    /** The item was selected (not activated), similar to "mouse-over" */
    virtual void selected();
    /** The item was unselected */
    virtual void unselected();
    
    /** Register menu handler script function */
    virtual void registerScriptTapHandler(int nHandler);
    virtual void unregisterScriptTapHandler(void);
    int getScriptTapHandler() { return _scriptTapHandler; };

    virtual bool isEnabled();
    //@note: It's 'setIsEnable' in cocos2d-iphone. 
    virtual void setEnabled(bool value);
    virtual bool isSelected();
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    /** set the target/selector of the menu item*/
    CC_DEPRECATED_ATTRIBUTE void setTarget(CCObject *rec, SEL_MenuHandler selector);
    /** set the callback to the menu item */
    void setCallback(const ccMenuCallback& callback);

protected:
    bool            _selected;
    bool            _enabled;
    int             _scriptTapHandler;
	// callback
	ccMenuCallback _callback;
	// If using the old API, the _target needs to be retained / released
	CCObject		*_target;
};

/** @brief An abstract class for "label" CCMenuItemLabel items 
 Any CCNode that supports the CCLabelProtocol protocol can be added.
 Supported nodes:
 - CCBitmapFontAtlas
 - CCLabelAtlas
 - CCLabelTTF
 */
class CC_DLL CCMenuItemLabel : public CCMenuItem
{
    /** the color that will be used to disable the item */
    CC_PROPERTY_PASS_BY_REF(ccColor3B, _disabledColor, DisabledColor);
    /** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol */
    CC_PROPERTY(CCNode*, _label, Label);
public:
    CCMenuItemLabel()
    : _label(NULL)
    , _originalScale(0.0)
    {}
    virtual ~CCMenuItemLabel();

    /** creates a CCMenuItemLabel with a Label, target and selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemLabel * create(CCNode*label, CCObject* target, SEL_MenuHandler selector);

	/** creates a CCMenuItemLabel with a Label and a callback */
    static CCMenuItemLabel * create(CCNode*label, const ccMenuCallback& callback);

    /** creates a CCMenuItemLabel with a Label. Target and selector will be nil */
    static CCMenuItemLabel* create(CCNode *label);

    /** initializes a CCMenuItemLabel with a Label, target and selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector);

	/** initializes a CCMenuItemLabel with a Label, target and selector */
    bool initWithLabel(CCNode* label, const ccMenuCallback& callback);

    /** sets a new string to the inner label */
    void setString(const char * label);
    // super methods
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    /** Enable or disabled the CCMenuItemFont
     @warning setEnabled changes the RGB color of the font
     */
    virtual void setEnabled(bool enabled);
    
protected:
    ccColor3B    _colorBackup;
    float        _originalScale;
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
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle */
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

    /** initializes a menu item from a string and atlas with a target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
    /** initializes a menu item from a string and atlas with a target/selector */
    bool initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

};


/** @brief A CCMenuItemFont
 Helper class that creates a CCMenuItemLabel class with a Label
 */
class CC_DLL CCMenuItemFont : public CCMenuItemLabel
{
public:
    CCMenuItemFont() : _fontSize(0), _fontName(""){}
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
    static CCMenuItemFont * create(const char *value);
    /** creates a menu item from a string with a target/selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemFont * create(const char *value, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item from a string with a target/selector */
    static CCMenuItemFont * create(const char *value, const ccMenuCallback& callback);

    /** initializes a menu item from a string with a target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const char *value, CCObject* target, SEL_MenuHandler selector);
    /** initializes a menu item from a string with a target/selector */
    bool initWithString(const char *value, const ccMenuCallback& callback);

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
    
    unsigned int _fontSize;
    std::string _fontName;
};


/** @brief CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 @since v0.8.0
 */
class CC_DLL CCMenuItemSprite : public CCMenuItem
{
    /** the image used when the item is not selected */
    CC_PROPERTY(CCNode*, _normalImage, NormalImage);
    /** the image used when the item is selected */
    CC_PROPERTY(CCNode*, _selectedImage, SelectedImage);
    /** the image used when the item is disabled */
    CC_PROPERTY(CCNode*, _disabledImage, DisabledImage);
public:
    CCMenuItemSprite()
    :_normalImage(NULL)
    ,_selectedImage(NULL)
    ,_disabledImage(NULL)
    {}

    /** creates a menu item with a normal, selected and disabled image*/
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal and selected image with a callable object */
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, const ccMenuCallback& callback);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, const ccMenuCallback& callback);

    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    /** initializes a menu item with a normal, selected  and disabled image with a callable object */
    bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, const ccMenuCallback& callback);

    /**
     @since v0.99.5
     */
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled);
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
protected:
    virtual void updateImagesVisibility();
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
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal and selected image with a callable object */
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const ccMenuCallback& callback);

    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with a callable object */
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback);

    bool init();
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    /** initializes a menu item with a normal, selected  and disabled image with a callable object */
    bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback);

    /** sets the sprite frame for the normal image */
    void setNormalSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the selected image */
    void setSelectedSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the disabled image */
    void setDisabledSpriteFrame(CCSpriteFrame* frame);

    /** Creates an CCMenuItemImage.
     */
    static CCMenuItemImage* create();
};


/** @brief A CCMenuItemToggle
 A simple container class that "toggles" it's inner items
 The inner items can be any MenuItem
 */
class CC_DLL CCMenuItemToggle : public CCMenuItem
{
    /** returns the selected item */
    CC_PROPERTY(unsigned int, _selectedIndex, SelectedIndex);
    /** CCMutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
     @since v0.7.2
     */
    CC_PROPERTY(CCArray*, _subItems, SubItems);
public:
    CCMenuItemToggle()
    : _selectedIndex(0)
    , _subItems(NULL)            
    {}
    virtual ~CCMenuItemToggle();
    
    /** creates a menu item from a CCArray with a target selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemToggle * createWithTarget(CCObject* target, SEL_MenuHandler selector, CCArray* menuItems);
    /** creates a menu item from a CCArray with a callable object */
    static CCMenuItemToggle * createWithCallback(const ccMenuCallback& callback, CCArray* menuItems);

    /** creates a menu item from a list of items with a target/selector */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemToggle* createWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, ...);
    /** creates a menu item from a list of items with a callable object */
    static CCMenuItemToggle* createWithCallback(const ccMenuCallback& callback, CCMenuItem* item, ...);

    /** creates a menu item with no target/selector and no items */
    static CCMenuItemToggle* create();

    /** initializes a menu item from a list of items with a target selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, va_list args);
    /** initializes a menu item from a list of items with a callable object */
    bool initWithCallback(const ccMenuCallback& callback, CCMenuItem* item, va_list args);

    /** creates a menu item with a item */
    static CCMenuItemToggle* create(CCMenuItem *item);

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
    virtual void setEnabled(bool var);
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCMENU_ITEM_H__
