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

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN
    
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
class CC_DLL CCMenuItem : public CCNode
{
protected:
    /** whether or not the item is selected
     @since v0.8.2
     */
    bool m_bIsEnabled;
    bool m_bIsSelected;
public:
    CCMenuItem()
    : m_bIsSelected(false)
    , m_bIsEnabled(false)            
    , m_pListener(NULL)            
    , m_pfnSelector(NULL)
    , m_nScriptHandler(0)
    {}
    virtual ~CCMenuItem();
    /** Creates a CCMenuItem with a target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItem * itemWithTarget(CCObject *rec, SEL_MenuHandler selector);
    /** Creates a CCMenuItem with a target/selector */
    static CCMenuItem * create(CCObject *rec, SEL_MenuHandler selector);
    /** Initializes a CCMenuItem with a target/selector */
    bool initWithTarget(CCObject *rec, SEL_MenuHandler selector);
    /** Returns the outside box */
    CCRect rect();
    /** Activate the item */
    virtual void activate();
    /** The item was selected (not activated), similar to "mouse-over" */
    virtual void selected();
    /** The item was unselected */
    virtual void unselected();
    
    /** Register menu handler script function */
    virtual void registerScriptHandler(int nHandler);
    virtual void unregisterScriptHandler(void);
    
    virtual bool isEnabled();
    //@note: It's 'setIsEnable' in cocos2d-iphone. 
    virtual void setEnabled(bool value);
    virtual bool isSelected();
    
    /** set the target/selector of the menu item*/
    void setTarget(CCObject *rec, SEL_MenuHandler selector);
protected:
    CCObject*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    int             m_nScriptHandler;
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
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tDisabledColor, DisabledColor);
    /** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol */
    CC_PROPERTY(CCNode*, m_pLabel, Label);
public:
    CCMenuItemLabel()
    : m_pLabel(NULL)
    , m_fOriginalScale(0.0)
    {}
    virtual ~CCMenuItemLabel();
    /** creates a CCMenuItemLabel with a Label, target and selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemLabel * itemWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector);
    /** creates a CCMenuItemLabel with a Label. Target and selector will be nill 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemLabel* itemWithLabel(CCNode *label);

    /** creates a CCMenuItemLabel with a Label, target and selector */
    static CCMenuItemLabel * create(CCNode*label, CCObject* target, SEL_MenuHandler selector);
    /** creates a CCMenuItemLabel with a Label. Target and selector will be nill */
    static CCMenuItemLabel* create(CCNode *label);

    /** initializes a CCMenuItemLabel with a Label, target and selector */
    bool initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector);
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
    virtual void setOpacity(GLubyte opacity);
    virtual GLubyte getOpacity();
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor();
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
protected:
    ccColor3B    m_tColorBackup;
    float        m_fOriginalScale;
};

/** @brief A CCMenuItemAtlasFont
 Helper class that creates a MenuItemLabel class with a LabelAtlas
 */
class CC_DLL CCMenuItemAtlasFont : public CCMenuItemLabel
{
public:
    CCMenuItemAtlasFont(){}
    virtual ~CCMenuItemAtlasFont(){}
    /** creates a menu item from a string and atlas with a target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemAtlasFont* itemWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemAtlasFont* itemWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
    
    /** creates a menu item from a string and atlas with a target/selector */
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle */
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
    /** initializes a menu item from a string and atlas with a target/selector */
    bool initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
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
    /** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemFont * itemWithString(const char *value);
    /** creates a menu item from a string with a target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemFont * itemWithString(const char *value, CCObject* target, SEL_MenuHandler selector);

    /** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle */
    static CCMenuItemFont * create(const char *value);
    /** creates a menu item from a string with a target/selector */
    static CCMenuItemFont * create(const char *value, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item from a string with a target/selector */
    bool initWithString(const char *value, CCObject* target, SEL_MenuHandler selector);
    
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
    /** creates a menu item with a normal, selected and disabled image
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemSprite * itemWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemSprite * itemWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemSprite * itemWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

    /** creates a menu item with a normal, selected and disabled image*/
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector */
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    // super methods
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor();
    virtual void setOpacity(GLubyte opacity);
    virtual GLubyte getOpacity();
    
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
    /** creates a menu item with a normal and selected image
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemImage* itemWithNormalImage(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemImage* itemWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemImage* itemWithNormalImage(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemImage* itemWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    
    /** creates a menu item with a normal and selected image*/
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector */
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    
    bool init();
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    /** sets the sprite frame for the normal image */
    void setNormalSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the selected image */
    void setSelectedSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the disabled image */
    void setDisabledSpriteFrame(CCSpriteFrame* frame);
    /** Creates an CCMenuItemImage.
    @deprecated: This interface will be deprecated sooner or later.
     */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemImage* node();

    /** Creates an CCMenuItemImage.
     */
    static CCMenuItemImage* create();
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
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
    /** returns the selected item */
    CC_PROPERTY(unsigned int, m_uSelectedIndex, SelectedIndex);
    /** CCMutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
     @since v0.7.2
     */
    CC_PROPERTY(CCArray*, m_pSubItems, SubItems);
public:
    CCMenuItemToggle()
    : m_cOpacity(0)
    , m_uSelectedIndex(0)
    , m_pSubItems(NULL)            
    {}
    virtual ~CCMenuItemToggle();

    /** creates a menu item from a list of items with a target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemToggle* itemWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, ...);   

    /** creates a menu item from a list of items with a target/selector */
    static CCMenuItemToggle* create(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, ...);  

    /** initializes a menu item from a list of items with a target selector */
    bool initWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, va_list args);
    
    // The follow methods offered to lua
    /** creates a menu item with a item 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemToggle* itemWithItem(CCMenuItem *item);

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
