/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#include "2d/CCMenuItem.h"
#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"
#include "2d/CCLabelAtlas.h"
#include "2d/CCLabel.h"
#include "deprecated/CCString.h"
#include <stdarg.h>

NS_CC_BEGIN
    
static int _globalFontSize = kItemSize;
static std::string _globalFontName = "Marker Felt";
static bool _globalFontNameRelease = false;

const unsigned int    kCurrentItem = 0xc0c05001;
const unsigned int    kZoomActionTag = 0xc0c05002;

const unsigned int    kNormalTag = 0x1;
const unsigned int    kSelectedTag = 0x2;
const unsigned int    kDisableTag = 0x3;
//
// MenuItem
//

MenuItem* MenuItem::create()
{
    return MenuItem::create((const ccMenuCallback&)nullptr);
}

// FIXME: deprecated
MenuItem* MenuItem::create(Ref *target, SEL_MenuHandler selector)
{
    MenuItem *ret = new (std::nothrow) MenuItem();
    ret->initWithCallback(std::bind(selector, target, std::placeholders::_1));
    ret->autorelease();
    return ret;
}

MenuItem* MenuItem::create( const ccMenuCallback& callback)
{
    MenuItem *ret = new (std::nothrow) MenuItem();
    ret->initWithCallback(callback);
    ret->autorelease();
    return ret;
}

// FIXME: deprecated
bool MenuItem::initWithTarget(cocos2d::Ref *target, SEL_MenuHandler selector )
{
    return initWithCallback( std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItem::initWithCallback(const ccMenuCallback& callback)
{
    setAnchorPoint(Vec2(0.5f, 0.5f));
    _callback = callback;
    _enabled = true;
    _selected = false;
    return true;
}

MenuItem::~MenuItem()
{
}

void MenuItem::onExit()
{
    Node::onExit();
}

void MenuItem::selected()
{
    _selected = true;
}

void MenuItem::unselected()
{
    _selected = false;
}

void MenuItem::activate()
{
    if (_enabled)
    {
        if( _callback )
        {
            _callback(this);
        }
#if CC_ENABLE_SCRIPT_BINDING
        if (kScriptTypeNone != _scriptType)
        {
            BasicScriptData data(this);
            ScriptEvent scriptEvent(kMenuClickedEvent,&data);
            ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
        }
#endif
    }
}

void MenuItem::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool MenuItem::isEnabled() const
{
    return _enabled;
}

Rect MenuItem::rect() const
{
    return Rect( _position.x - _contentSize.width * _anchorPoint.x,
                      _position.y - _contentSize.height * _anchorPoint.y,
                      _contentSize.width, _contentSize.height);
}

bool MenuItem::isSelected() const
{
    return _selected;
}

// FIXME: deprecated
void MenuItem::setTarget(Ref *target, SEL_MenuHandler selector)
{
    setCallback( std::bind( selector, target, std::placeholders::_1) );
}

void MenuItem::setCallback(const ccMenuCallback& callback)
{
    _callback = callback;
}

std::string MenuItem::getDescription() const
{
    return StringUtils::format("<MenuItem | tag = %d>", _tag);
}

//
//CCMenuItemLabel
//

void MenuItemLabel::setLabel(Node* var)
{
    if (var)
    {
        var->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        setContentSize(var->getContentSize()); 
        addChild(var);
    }
    
    if (_label)
    {
        removeChild(_label, true);
    }
    
    _label = var;
}

// FIXME:: deprecated
MenuItemLabel * MenuItemLabel::create(Node*label, Ref* target, SEL_MenuHandler selector)
{
    MenuItemLabel *ret = new (std::nothrow) MenuItemLabel();
    ret->initWithLabel(label, std::bind(selector, target, std::placeholders::_1));
    ret->autorelease();
    return ret;
}

MenuItemLabel * MenuItemLabel::create(Node*label, const ccMenuCallback& callback)
{
    MenuItemLabel *ret = new (std::nothrow) MenuItemLabel();
    ret->initWithLabel(label, callback);
    ret->autorelease();
    return ret;
}

MenuItemLabel* MenuItemLabel::create(Node *label)
{
    MenuItemLabel *ret = new (std::nothrow) MenuItemLabel();
    ret->initWithLabel(label, (const ccMenuCallback&) nullptr);
    ret->autorelease();
    return ret;
}

// FIXME:: deprecated
bool MenuItemLabel::initWithLabel(Node* label, Ref* target, SEL_MenuHandler selector)
{
    return initWithLabel(label, std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItemLabel::initWithLabel(Node* label, const ccMenuCallback& callback)
{
    MenuItem::initWithCallback(callback);
    _originalScale = 1.0f;
    _colorBackup = Color3B::WHITE;
    setDisabledColor(Color3B(126,126,126));
    this->setLabel(label);

    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);

    return true;
}


MenuItemLabel::~MenuItemLabel()
{
}

void MenuItemLabel::setString(const std::string& label)
{
    dynamic_cast<LabelProtocol*>(_label)->setString(label);
    this->setContentSize(_label->getContentSize());
}

void MenuItemLabel::activate()
{
    if(_enabled)
    {
        this->stopAllActions();
        this->setScale( _originalScale );
        MenuItem::activate();
    }
}

void MenuItemLabel::selected()
{
    // subclass to change the default action
    if(_enabled)
    {
        MenuItem::selected();
        
        Action *action = getActionByTag(kZoomActionTag);
        if (action)
        {
            this->stopAction(action);
        }
        else
        {
            _originalScale = this->getScale();
        }
        
        Action *zoomAction = ScaleTo::create(0.1f, _originalScale * 1.2f);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

void MenuItemLabel::unselected()
{
    // subclass to change the default action
    if(_enabled)
    {
        MenuItem::unselected();
        this->stopActionByTag(kZoomActionTag);
        Action *zoomAction = ScaleTo::create(0.1f, _originalScale);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

void MenuItemLabel::setEnabled(bool enabled)
{
    if( _enabled != enabled ) 
    {
        if(enabled == false)
        {
            _colorBackup = this->getColor();
            this->setColor(_disabledColor);
        }
        else
        {
            this->setColor(_colorBackup);
        }
    }
    MenuItem::setEnabled(enabled);
}

//
//CCMenuItemAtlasFont
//

MenuItemAtlasFont * MenuItemAtlasFont::create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap)
{
    return MenuItemAtlasFont::create(value, charMapFile, itemWidth, itemHeight, startCharMap, (const ccMenuCallback&)nullptr);
}

// FIXME:: deprecated
MenuItemAtlasFont * MenuItemAtlasFont::create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector)
{
    MenuItemAtlasFont *ret = new (std::nothrow) MenuItemAtlasFont();
    ret->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, std::bind(selector, target, std::placeholders::_1));
    ret->autorelease();
    return ret;
}

MenuItemAtlasFont * MenuItemAtlasFont::create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback)
{
    MenuItemAtlasFont *ret = new (std::nothrow) MenuItemAtlasFont();
    ret->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, callback);
    ret->autorelease();
    return ret;
}

// FIXME:: deprecated
bool MenuItemAtlasFont::initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector)
{
    return initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItemAtlasFont::initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback)
{
    CCASSERT( value.size() != 0, "value length must be greater than 0");
    LabelAtlas *label = LabelAtlas::create();
    label->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap);
    if (MenuItemLabel::initWithLabel(label, callback))
    {
        // do something ?
    }
    return true;
}

//
//CCMenuItemFont
//

void MenuItemFont::setFontSize(int s)
{
    _globalFontSize = s;
}

int MenuItemFont::getFontSize()
{
    return _globalFontSize;
}

void MenuItemFont::setFontName(const std::string& name)
{
    if (_globalFontNameRelease)
    {
        _globalFontName.clear();
    }
    _globalFontName = name;
    _globalFontNameRelease = true;
}

const std::string& MenuItemFont::getFontName()
{
    return _globalFontName;
}

// FIXME:: deprecated
MenuItemFont * MenuItemFont::create(const std::string& value, Ref* target, SEL_MenuHandler selector)
{
    MenuItemFont *ret = new (std::nothrow) MenuItemFont();
    ret->initWithString(value, std::bind(selector, target, std::placeholders::_1));
    ret->autorelease();
    return ret;
}

MenuItemFont * MenuItemFont::create(const std::string& value, const ccMenuCallback& callback)
{
    MenuItemFont *ret = new (std::nothrow) MenuItemFont();
    ret->initWithString(value, callback);
    ret->autorelease();
    return ret;
}


MenuItemFont * MenuItemFont::create(const std::string& value)
{
    MenuItemFont *ret = new (std::nothrow) MenuItemFont();
    ret->initWithString(value, (const ccMenuCallback&)nullptr);
    ret->autorelease();
    return ret;
}

MenuItemFont::MenuItemFont()
 : _fontSize(0), _fontName("")
{}

MenuItemFont::~MenuItemFont()
{
    CCLOGINFO("In the destructor of MenuItemFont (%p).", this);
}

// FIXME:: deprecated
bool MenuItemFont::initWithString(const std::string& value, Ref* target, SEL_MenuHandler selector)
{
    CCASSERT( !value.empty(), "Value length must be greater than 0");

    return initWithString(value, std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItemFont::initWithString(const std::string& value, const ccMenuCallback& callback)
{
    CCASSERT( !value.empty(), "Value length must be greater than 0");

    _fontName = _globalFontName;
    _fontSize = _globalFontSize;

    Label *label = Label::createWithSystemFont(value, _fontName, _fontSize);
    if (MenuItemLabel::initWithLabel(label, callback))
    {
        // do something ?
    }
    return true;
}

void MenuItemFont::setFontSizeObj(int s)
{
    _fontSize = s;
    dynamic_cast<Label*>(_label)->setSystemFontSize(_fontSize);
    this->setContentSize(dynamic_cast<Label*>(_label)->getContentSize());
}

int MenuItemFont::getFontSizeObj() const
{
    return _fontSize;
}

void MenuItemFont::setFontNameObj(const std::string& name)
{
    _fontName = name;
    dynamic_cast<Label*>(_label)->setSystemFontName(_fontName);
    this->setContentSize(dynamic_cast<Label*>(_label)->getContentSize());
}

const std::string& MenuItemFont::getFontNameObj() const
{
    return _fontName;
}

//
//CCMenuItemSprite
//

void MenuItemSprite::setNormalImage(Node* image)
{
    if (image != _normalImage)
    {
        if (image)
        {
            addChild(image, 0, kNormalTag);
            image->setAnchorPoint(Vec2(0, 0));
        }

        if (_normalImage)
        {
            removeChild(_normalImage, true);
        }

        _normalImage = image;
        this->setContentSize(_normalImage->getContentSize());
        this->updateImagesVisibility();
    }
}

void MenuItemSprite::setSelectedImage(Node* image)
{
    if (image != _normalImage)
    {
        if (image)
        {
            addChild(image, 0, kSelectedTag);
            image->setAnchorPoint(Vec2(0, 0));
        }

        if (_selectedImage)
        {
            removeChild(_selectedImage, true);
        }

        _selectedImage = image;
        this->updateImagesVisibility();
    }
}

void MenuItemSprite::setDisabledImage(Node* image)
{
    if (image != _normalImage)
    {
        if (image)
        {
            addChild(image, 0, kDisableTag);
            image->setAnchorPoint(Vec2(0, 0));
        }

        if (_disabledImage)
        {
            removeChild(_disabledImage, true);
        }

        _disabledImage = image;
        this->updateImagesVisibility();
    }
}

//
//CCMenuItemSprite
//

MenuItemSprite * MenuItemSprite::create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite)
{
    return MenuItemSprite::create(normalSprite, selectedSprite, disabledSprite, (const ccMenuCallback&)nullptr);
}

// FIXME: deprecated
MenuItemSprite * MenuItemSprite::create(Node* normalSprite, Node* selectedSprite, Ref* target, SEL_MenuHandler selector)
{
    return MenuItemSprite::create(normalSprite, selectedSprite, nullptr, std::bind(selector, target, std::placeholders::_1));
}

MenuItemSprite * MenuItemSprite::create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback)
{
    return MenuItemSprite::create(normalSprite, selectedSprite, nullptr, callback);
}

// FIXME: deprecated
MenuItemSprite * MenuItemSprite::create(Node *normalSprite, Node *selectedSprite, Node *disabledSprite, Ref *target, SEL_MenuHandler selector)
{
    MenuItemSprite *ret = new (std::nothrow) MenuItemSprite();
    ret->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, std::bind(selector, target, std::placeholders::_1));
    ret->autorelease();
    return ret;
}

MenuItemSprite * MenuItemSprite::create(Node *normalSprite, Node *selectedSprite, Node *disabledSprite, const ccMenuCallback& callback)
{
    MenuItemSprite *ret = new (std::nothrow) MenuItemSprite();
    ret->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
    ret->autorelease();
    return ret;
}

// FIXME: deprecated
bool MenuItemSprite::initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector)
{
    return initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItemSprite::initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback)
{
    MenuItem::initWithCallback(callback);
    setNormalImage(normalSprite);
    setSelectedImage(selectedSprite);
    setDisabledImage(disabledSprite);

    if(_normalImage)
    {
        this->setContentSize(_normalImage->getContentSize());
    }

    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);

    return true;
}

/**
 @since v0.99.5
 */
void MenuItemSprite::selected()
{
    MenuItem::selected();

    if (_normalImage)
    {
        if (_disabledImage)
        {
            _disabledImage->setVisible(false);
        }

        if (_selectedImage)
        {
            _normalImage->setVisible(false);
            _selectedImage->setVisible(true);
        }
        else
        {
            _normalImage->setVisible(true);
        }
    }
}

void MenuItemSprite::unselected()
{
    MenuItem::unselected();
    if (_normalImage)
    {
        _normalImage->setVisible(true);

        if (_selectedImage)
        {
            _selectedImage->setVisible(false);
        }

        if (_disabledImage)
        {
            _disabledImage->setVisible(false);
        }
    }
}

void MenuItemSprite::setEnabled(bool bEnabled)
{
    if( _enabled != bEnabled ) 
    {
        MenuItem::setEnabled(bEnabled);
        this->updateImagesVisibility();
    }
}

// Helper 
void MenuItemSprite::updateImagesVisibility()
{
    if (_enabled)
    {
        if (_normalImage)   _normalImage->setVisible(true);
        if (_selectedImage) _selectedImage->setVisible(false);
        if (_disabledImage) _disabledImage->setVisible(false);
    }
    else
    {
        if (_disabledImage)
        {
            if (_normalImage)   _normalImage->setVisible(false);
            if (_selectedImage) _selectedImage->setVisible(false);
            if (_disabledImage) _disabledImage->setVisible(true);
        }
        else
        {
            if (_normalImage)   _normalImage->setVisible(true);
            if (_selectedImage) _selectedImage->setVisible(false);
            if (_disabledImage) _disabledImage->setVisible(false);
        }
    }
}

///
/// MenuItemImage
///

MenuItemImage* MenuItemImage::create()
{
    MenuItemImage *ret = new (std::nothrow) MenuItemImage();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MenuItemImage::init(void)
{
    return initWithNormalImage("", "", "", (const ccMenuCallback&)nullptr);
}

MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage)
{
    return MenuItemImage::create(normalImage, selectedImage, "", (const ccMenuCallback&)nullptr);
}

// FIXME: deprecated
MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, Ref* target, SEL_MenuHandler selector)
{
    return MenuItemImage::create(normalImage, selectedImage, "", std::bind(selector, target, std::placeholders::_1));
}

MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback)
{
    return MenuItemImage::create(normalImage, selectedImage, "", callback);
}

// FIXME: deprecated
MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector)
{
    MenuItemImage *ret = new (std::nothrow) MenuItemImage();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, std::bind(selector, target, std::placeholders::_1)))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
    MenuItemImage *ret = new (std::nothrow) MenuItemImage();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, callback))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage)
{
    MenuItemImage *ret = new (std::nothrow) MenuItemImage();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, (const ccMenuCallback&)nullptr))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// FIXME:: deprecated
bool MenuItemImage::initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector)
{
    return initWithNormalImage(normalImage, selectedImage, disabledImage, std::bind(selector,target, std::placeholders::_1) );
}
bool MenuItemImage::initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
    Node *normalSprite = nullptr;
    Node *selectedSprite = nullptr;
    Node *disabledSprite = nullptr;

    if (normalImage.size() >0)
    {
        normalSprite = Sprite::create(normalImage);
    }

    if (selectedImage.size() >0)
    {
        selectedSprite = Sprite::create(selectedImage);
    }

    if(disabledImage.size() >0)
    {
        disabledSprite = Sprite::create(disabledImage);
    }
    return initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
}

//
// Setter of sprite frames
//
void MenuItemImage::setNormalSpriteFrame(SpriteFrame * frame)
{
    setNormalImage(Sprite::createWithSpriteFrame(frame));
}

void MenuItemImage::setSelectedSpriteFrame(SpriteFrame * frame)
{
    setSelectedImage(Sprite::createWithSpriteFrame(frame));
}

void MenuItemImage::setDisabledSpriteFrame(SpriteFrame * frame)
{
    setDisabledImage(Sprite::createWithSpriteFrame(frame));
}

//
// MenuItemToggle
//

// FIXME:: deprecated
MenuItemToggle * MenuItemToggle::createWithTarget(Ref* target, SEL_MenuHandler selector, const Vector<MenuItem*>& menuItems)
{
    MenuItemToggle *ret = new (std::nothrow) MenuItemToggle();
    ret->MenuItem::initWithCallback(std::bind(selector, target, std::placeholders::_1));
    ret->_subItems = menuItems;
    ret->_selectedIndex = UINT_MAX;
    ret->setSelectedIndex(0);
    return ret;
}

MenuItemToggle * MenuItemToggle::createWithCallback(const ccMenuCallback &callback, const Vector<MenuItem*>& menuItems)
{
    MenuItemToggle *ret = new (std::nothrow) MenuItemToggle();
    ret->MenuItem::initWithCallback(callback);
    ret->_subItems = menuItems;
    ret->_selectedIndex = UINT_MAX;
    ret->setSelectedIndex(0);
    return ret;
}

// FIXME:: deprecated
MenuItemToggle * MenuItemToggle::createWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    MenuItemToggle *ret = new (std::nothrow) MenuItemToggle();
    ret->initWithCallback(std::bind(selector, target, std::placeholders::_1), item, args);
    ret->autorelease();
    va_end(args);
    return ret;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
MenuItemToggle * MenuItemToggle::createWithCallbackVA(const ccMenuCallback &callback, MenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    MenuItemToggle *ret = new (std::nothrow) MenuItemToggle();
    ret->initWithCallback(callback, item, args);
    ret->autorelease();
    va_end(args);
    return ret;
}
#else
MenuItemToggle * MenuItemToggle::createWithCallback(const ccMenuCallback &callback, MenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    MenuItemToggle *ret = new (std::nothrow) MenuItemToggle();
    ret->initWithCallback(callback, item, args);
    ret->autorelease();
    va_end(args);
    return ret;
}
#endif

MenuItemToggle * MenuItemToggle::create()
{
    MenuItemToggle *ret = new (std::nothrow) MenuItemToggle();
    ret->initWithItem(nullptr);
    ret->autorelease();
    return ret;
}

// FIXME:: deprecated
bool MenuItemToggle::initWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, va_list args)
{
    return initWithCallback(std::bind( selector, target, std::placeholders::_1), item, args);
}

bool MenuItemToggle::initWithCallback(const ccMenuCallback &callback, MenuItem *item, va_list args)
{
    MenuItem::initWithCallback(callback);

    int z = 0;
    MenuItem *i = item;
    while(i)
    {
        z++;
        _subItems.pushBack(i);
        i = va_arg(args, MenuItem*);
    }
    _selectedIndex = UINT_MAX;
    this->setSelectedIndex(0);
    return true;
}

MenuItemToggle* MenuItemToggle::create(MenuItem *item)
{
    MenuItemToggle *ret = new (std::nothrow) MenuItemToggle();
    ret->initWithItem(item);
    ret->autorelease();
    return ret;
}

bool MenuItemToggle::initWithItem(MenuItem *item)
{
    MenuItem::initWithCallback((const ccMenuCallback&)nullptr);

    if (item)
    {
        _subItems.pushBack(item);
    }
    _selectedIndex = UINT_MAX;
    this->setSelectedIndex(0);
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
    return true;
}

void MenuItemToggle::addSubItem(MenuItem *item)
{
    _subItems.pushBack(item);
}

MenuItemToggle::~MenuItemToggle()
{
    for(const auto &item : _subItems) {
        item->cleanup();
    }
}

void MenuItemToggle::setSelectedIndex(unsigned int index)
{
    if( index != _selectedIndex && _subItems.size() > 0 )
    {
        _selectedIndex = index;
        MenuItem *currentItem = (MenuItem*)getChildByTag(kCurrentItem);
        if( currentItem )
        {
            currentItem->removeFromParentAndCleanup(false);
        }

        MenuItem* item = _subItems.at(_selectedIndex);
        this->addChild(item, 0, kCurrentItem);
        Size s = item->getContentSize();
        this->setContentSize(s);
        item->setPosition(s.width/2, s.height/2);
    }
}

void MenuItemToggle::selected()
{
    MenuItem::selected();
    _subItems.at(_selectedIndex)->selected();
}

void MenuItemToggle::unselected()
{
    MenuItem::unselected();
    _subItems.at(_selectedIndex)->unselected();
}

void MenuItemToggle::activate()
{
    // update index
    if( _enabled ) 
    {
        unsigned int newIndex = (_selectedIndex + 1) % _subItems.size();
        this->setSelectedIndex(newIndex);
    }
    MenuItem::activate();
}
void MenuItemToggle::setEnabled(bool enabled)
{
    if (_enabled != enabled)
    {
        MenuItem::setEnabled(enabled);

        for(const auto &item : _subItems) {
            item->setEnabled(enabled);
        }
    }
}

MenuItem* MenuItemToggle::getSelectedItem()
{
    return _subItems.at(_selectedIndex);
}

NS_CC_END
