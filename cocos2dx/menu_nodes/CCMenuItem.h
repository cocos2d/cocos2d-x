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

typedef std::function<void(Object*)> ccMenuCallback;

class LabelTTF;
class LabelAtlas;
class Sprite;
class SpriteFrame;
#define kItemSize 32
    
/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */

/** @brief MenuItem base class
 *
 *  Subclass MenuItem (or any subclass) to create your custom MenuItem objects.
 */
class CC_DLL MenuItem : public NodeRGBA
{
public:
    MenuItem()
    : _selected(false)
    , _enabled(false)            
    , _scriptTapHandler(0)
	, _callback(nullptr)
    , _target(NULL)
    {}
    virtual ~MenuItem();

    /** Creates a MenuItem with no target/selector */
    static MenuItem* create();
    /** Creates a MenuItem with a target/selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItem* create(Object *rec, SEL_MenuHandler selector);
    /** Creates a MenuItem with a target/selector */
    static MenuItem* create(const ccMenuCallback& callback);
    /** Initializes a MenuItem with a target/selector */
    bool initWithCallback(const ccMenuCallback& callback);
    /** Initializes a MenuItem with a target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget( Object *rec, SEL_MenuHandler selector);
    /** Returns the outside box */
    Rect rect();
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
    CC_DEPRECATED_ATTRIBUTE void setTarget(Object *rec, SEL_MenuHandler selector);
    /** set the callback to the menu item */
    void setCallback(const ccMenuCallback& callback);

protected:
    bool            _selected;
    bool            _enabled;
    int             _scriptTapHandler;
	// callback
	ccMenuCallback _callback;
	// If using the old API, the _target needs to be retained / released
	Object		*_target;
};

/** @brief An abstract class for "label" MenuItemLabel items 
 Any Node that supports the LabelProtocol protocol can be added.
 Supported nodes:
 - BitmapFontAtlas
 - LabelAtlas
 - LabelTTF
 */
class CC_DLL MenuItemLabel : public MenuItem
{
    /** the color that will be used to disable the item */
    CC_PROPERTY_PASS_BY_REF(ccColor3B, _disabledColor, DisabledColor);
    /** Label that is rendered. It can be any Node that implements the LabelProtocol */
    CC_PROPERTY(Node*, _label, Label);
public:
    MenuItemLabel()
    : _label(NULL)
    , _originalScale(0.0)
    {}
    virtual ~MenuItemLabel();

    /** creates a MenuItemLabel with a Label, target and selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemLabel * create(Node*label, Object* target, SEL_MenuHandler selector);

	/** creates a MenuItemLabel with a Label and a callback */
    static MenuItemLabel * create(Node*label, const ccMenuCallback& callback);

    /** creates a MenuItemLabel with a Label. Target and selector will be nil */
    static MenuItemLabel* create(Node *label);

    /** initializes a MenuItemLabel with a Label, target and selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithLabel(Node* label, Object* target, SEL_MenuHandler selector);

	/** initializes a MenuItemLabel with a Label, target and selector */
    bool initWithLabel(Node* label, const ccMenuCallback& callback);

    /** sets a new string to the inner label */
    void setString(const char * label);
    // super methods
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    /** Enable or disabled the MenuItemFont
     @warning setEnabled changes the RGB color of the font
     */
    virtual void setEnabled(bool enabled);
    
protected:
    ccColor3B    _colorBackup;
    float        _originalScale;
};


/** @brief A MenuItemAtlasFont
 Helper class that creates a MenuItemLabel class with a LabelAtlas
 */
class CC_DLL MenuItemAtlasFont : public MenuItemLabel
{
public:
    MenuItemAtlasFont(){}
    virtual ~MenuItemAtlasFont(){}
    
    /** creates a menu item from a string and atlas with a target/selector */
    static MenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle */
    CC_DEPRECATED_ATTRIBUTE static MenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, Object* target, SEL_MenuHandler selector);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle */
    static MenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

    /** initializes a menu item from a string and atlas with a target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, Object* target, SEL_MenuHandler selector);
    /** initializes a menu item from a string and atlas with a target/selector */
    bool initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

};


/** @brief A MenuItemFont
 Helper class that creates a MenuItemLabel class with a Label
 */
class CC_DLL MenuItemFont : public MenuItemLabel
{
public:
    MenuItemFont() : _fontSize(0), _fontName(""){}
    virtual ~MenuItemFont(){}
    /** set default font size */
    static void setFontSize(unsigned int s);
    /** get default font size */
    static unsigned int fontSize();
    /** set the default font name */
    static void setFontName(const char *name);
    /** get the default font name */
    static const char *fontName();

    /** creates a menu item from a string without target/selector. To be used with MenuItemToggle */
    static MenuItemFont * create(const char *value);
    /** creates a menu item from a string with a target/selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemFont * create(const char *value, Object* target, SEL_MenuHandler selector);
    /** creates a menu item from a string with a target/selector */
    static MenuItemFont * create(const char *value, const ccMenuCallback& callback);

    /** initializes a menu item from a string with a target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const char *value, Object* target, SEL_MenuHandler selector);
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


/** @brief MenuItemSprite accepts Node<RGBAProtocol> objects as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 @since v0.8.0
 */
class CC_DLL MenuItemSprite : public MenuItem
{
    /** the image used when the item is not selected */
    CC_PROPERTY(Node*, _normalImage, NormalImage);
    /** the image used when the item is selected */
    CC_PROPERTY(Node*, _selectedImage, SelectedImage);
    /** the image used when the item is disabled */
    CC_PROPERTY(Node*, _disabledImage, DisabledImage);
public:
    MenuItemSprite()
    :_normalImage(NULL)
    ,_selectedImage(NULL)
    ,_disabledImage(NULL)
    {}

    /** creates a menu item with a normal, selected and disabled image*/
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Object* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Object* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal and selected image with a callable object */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);

    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Object* target, SEL_MenuHandler selector);
    /** initializes a menu item with a normal, selected  and disabled image with a callable object */
    bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);

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


/** @brief MenuItemImage accepts images as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 For best results try that all images are of the same size
 */
class CC_DLL MenuItemImage : public MenuItemSprite
{
public:
    MenuItemImage(){}
    virtual ~MenuItemImage(){}
    
    /** creates a menu item with a normal and selected image*/
    static MenuItemImage* create(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    static MenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const char *normalImage, const char *selectedImage, Object* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal and selected image with a callable object */
    static MenuItemImage* create(const char *normalImage, const char *selectedImage, const ccMenuCallback& callback);

    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, Object* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with a callable object */
    static MenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback);

    bool init();
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, Object* target, SEL_MenuHandler selector);
    /** initializes a menu item with a normal, selected  and disabled image with a callable object */
    bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback);

    /** sets the sprite frame for the normal image */
    void setNormalSpriteFrame(SpriteFrame* frame);
    /** sets the sprite frame for the selected image */
    void setSelectedSpriteFrame(SpriteFrame* frame);
    /** sets the sprite frame for the disabled image */
    void setDisabledSpriteFrame(SpriteFrame* frame);

    /** Creates an MenuItemImage.
     */
    static MenuItemImage* create();
};


/** @brief A MenuItemToggle
 A simple container class that "toggles" it's inner items
 The inner items can be any MenuItem
 */
class CC_DLL MenuItemToggle : public MenuItem
{
    /** returns the selected item */
    CC_PROPERTY(unsigned int, _selectedIndex, SelectedIndex);
    /** MutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
     @since v0.7.2
     */
    CC_PROPERTY(Array*, _subItems, SubItems);
public:
    MenuItemToggle()
    : _selectedIndex(0)
    , _subItems(NULL)            
    {}
    virtual ~MenuItemToggle();
    
    /** creates a menu item from a Array with a target selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle * createWithTarget(Object* target, SEL_MenuHandler selector, Array* menuItems);
    /** creates a menu item from a Array with a callable object */
    static MenuItemToggle * createWithCallback(const ccMenuCallback& callback, Array* menuItems);

    /** creates a menu item from a list of items with a target/selector */
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle* createWithTarget(Object* target, SEL_MenuHandler selector, MenuItem* item, ...);
    /** creates a menu item from a list of items with a callable object */
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, MenuItem* item, ...);

    /** creates a menu item with no target/selector and no items */
    static MenuItemToggle* create();

    /** initializes a menu item from a list of items with a target selector */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Object* target, SEL_MenuHandler selector, MenuItem* item, va_list args);
    /** initializes a menu item from a list of items with a callable object */
    bool initWithCallback(const ccMenuCallback& callback, MenuItem* item, va_list args);

    /** creates a menu item with a item */
    static MenuItemToggle* create(MenuItem *item);

    /** initializes a menu item with a item */
    bool initWithItem(MenuItem *item);
    /** add more menu item */
    void addSubItem(MenuItem *item);
    
    /** return the selected item */
    MenuItem* selectedItem();
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
