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

#include "CCMenuItem.h"
#include "actions/CCActionInterval.h"
#include "sprite_nodes/CCSprite.h"
#include "label_nodes/CCLabelAtlas.h"
#include "label_nodes/CCLabelTTF.h"
#include "script_support/CCScriptSupport.h"
#include <stdarg.h>
#include <cstring>

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

NS_CC_BEGIN
    
static unsigned int _globalFontSize = kItemSize;
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

// XXX deprecated
MenuItem* MenuItem::create(Object *target, SEL_MenuHandler selector)
{
    MenuItem *pRet = new MenuItem();
    pRet->initWithTarget(target, selector);
    pRet->autorelease();
    return pRet;
}

MenuItem* MenuItem::create( const ccMenuCallback& callback)
{
    MenuItem *pRet = new MenuItem();
    pRet->initWithCallback(callback);
    pRet->autorelease();
    return pRet;
}

// XXX deprecated
bool MenuItem::initWithTarget(cocos2d::Object *target, SEL_MenuHandler selector )
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithCallback( std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItem::initWithCallback(const ccMenuCallback& callback)
{
    setAnchorPoint(Point(0.5f, 0.5f));
	_callback = callback;
    _enabled = true;
    _selected = false;
    return true;
}

MenuItem::~MenuItem()
{
	CC_SAFE_RELEASE(_target);
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
        
        if (kScriptTypeNone != _scriptType)
        {
            BasicScriptData data(this);
            ScriptEvent scriptEvent(kMenuClickedEvent,&data);
            ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
        }
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

// XXX deprecated
void MenuItem::setTarget(Object *target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	setCallback( std::bind( selector, target, std::placeholders::_1) );
}

void MenuItem::setCallback(const ccMenuCallback& callback)
{
	_callback = callback;
}


//
//CCMenuItemLabel
//

void MenuItemLabel::setLabel(Node* var)
{
    if (var)
    {
        addChild(var);
        var->setAnchorPoint(Point(0, 0));
        setContentSize(var->getContentSize());
    }
    
    if (_label)
    {
        removeChild(_label, true);
    }
    
    _label = var;
}

// XXX: deprecated
MenuItemLabel * MenuItemLabel::create(Node*label, Object* target, SEL_MenuHandler selector)
{
    MenuItemLabel *pRet = new MenuItemLabel();
    pRet->initWithLabel(label, target, selector);
    pRet->autorelease();
    return pRet;
}

MenuItemLabel * MenuItemLabel::create(Node*label, const ccMenuCallback& callback)
{
    MenuItemLabel *pRet = new MenuItemLabel();
    pRet->initWithLabel(label, callback);
    pRet->autorelease();
    return pRet;
}

MenuItemLabel* MenuItemLabel::create(Node *label)
{
    MenuItemLabel *pRet = new MenuItemLabel();
    pRet->initWithLabel(label, (const ccMenuCallback&) nullptr);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool MenuItemLabel::initWithLabel(Node* label, Object* target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
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

void MenuItemLabel::setString(const char * label)
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
            _colorBackup = dynamic_cast<RGBAProtocol*>(_label)->getColor();
            dynamic_cast<RGBAProtocol*>(_label)->setColor(_disabledColor);
        }
        else
        {
            dynamic_cast<RGBAProtocol*>(_label)->setColor(_colorBackup);
        }
    }
    MenuItem::setEnabled(enabled);
}

//
//CCMenuItemAtlasFont
//

MenuItemAtlasFont * MenuItemAtlasFont::create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap)
{
    return MenuItemAtlasFont::create(value, charMapFile, itemWidth, itemHeight, startCharMap, (const ccMenuCallback&)nullptr);
}

// XXX: deprecated
MenuItemAtlasFont * MenuItemAtlasFont::create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, Object* target, SEL_MenuHandler selector)
{
    MenuItemAtlasFont *pRet = new MenuItemAtlasFont();
    pRet->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, target, selector);
    pRet->autorelease();
    return pRet;
}

MenuItemAtlasFont * MenuItemAtlasFont::create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback)
{
    MenuItemAtlasFont *pRet = new MenuItemAtlasFont();
    pRet->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, callback);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool MenuItemAtlasFont::initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, Object* target, SEL_MenuHandler selector)
{
    CCASSERT( value != NULL && strlen(value) != 0, "value length must be greater than 0");

	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItemAtlasFont::initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback)
{
    CCASSERT( value != NULL && strlen(value) != 0, "value length must be greater than 0");
    LabelAtlas *label = new LabelAtlas();
    label->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap);
    label->autorelease();
    if (MenuItemLabel::initWithLabel(label, callback))
    {
        // do something ?
    }
    return true;
}

//
//CCMenuItemFont
//

void MenuItemFont::setFontSize(unsigned int s)
{
    _globalFontSize = s;
}

unsigned int MenuItemFont::getFontSize()
{
    return _globalFontSize;
}

void MenuItemFont::setFontName(const char *name)
{
    if (_globalFontNameRelease)
    {
        _globalFontName.clear();
    }
    _globalFontName = name;
    _globalFontNameRelease = true;
}

const char * MenuItemFont::getFontName()
{
    return _globalFontName.c_str();
}

// XXX: deprecated
MenuItemFont * MenuItemFont::create(const char *value, Object* target, SEL_MenuHandler selector)
{
    MenuItemFont *pRet = new MenuItemFont();
    pRet->initWithString(value, target, selector);
    pRet->autorelease();
    return pRet;
}

MenuItemFont * MenuItemFont::create(const char *value, const ccMenuCallback& callback)
{
    MenuItemFont *pRet = new MenuItemFont();
    pRet->initWithString(value, callback);
    pRet->autorelease();
    return pRet;
}


MenuItemFont * MenuItemFont::create(const char *value)
{
    MenuItemFont *pRet = new MenuItemFont();
    pRet->initWithString(value, (const ccMenuCallback&)nullptr);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool MenuItemFont::initWithString(const char *value, Object* target, SEL_MenuHandler selector)
{
    CCASSERT( value != NULL && strlen(value) != 0, "Value length must be greater than 0");

	_target = target;
    CC_SAFE_RETAIN(target);
	return initWithString(value, std::bind(selector,target, std::placeholders::_1) );
}

bool MenuItemFont::initWithString(const char *value, const ccMenuCallback& callback)
{
    CCASSERT( value != NULL && strlen(value) != 0, "Value length must be greater than 0");

    _fontName = _globalFontName;
    _fontSize = _globalFontSize;

    LabelTTF *label = LabelTTF::create(value, _fontName.c_str(), (float)_fontSize);
    if (MenuItemLabel::initWithLabel(label, callback))
    {
        // do something ?
    }
    return true;
}

void MenuItemFont::recreateLabel()
{
    LabelTTF *label = LabelTTF::create(dynamic_cast<LabelProtocol*>(_label)->getString(), 
                                                    _fontName.c_str(), (float)_fontSize);
    this->setLabel(label);
}

void MenuItemFont::setFontSizeObj(unsigned int s)
{
    _fontSize = s;
    recreateLabel();
}

unsigned int MenuItemFont::getFontSizeObj() const
{
    return _fontSize;
}

void MenuItemFont::setFontNameObj(const char* name)
{
    _fontName = name;
    recreateLabel();
}

const char* MenuItemFont::getFontNameObj() const
{
    return _fontName.c_str();
}

//
//CCMenuItemSprite
//

void MenuItemSprite::setNormalImage(Node* pImage)
{
    if (pImage != _normalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kNormalTag);
            pImage->setAnchorPoint(Point(0, 0));
        }

        if (_normalImage)
        {
            removeChild(_normalImage, true);
        }

        _normalImage = pImage;
        this->setContentSize(_normalImage->getContentSize());
        this->updateImagesVisibility();
    }
}

void MenuItemSprite::setSelectedImage(Node* pImage)
{
    if (pImage != _normalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kSelectedTag);
            pImage->setAnchorPoint(Point(0, 0));
        }

        if (_selectedImage)
        {
            removeChild(_selectedImage, true);
        }

        _selectedImage = pImage;
        this->updateImagesVisibility();
    }
}

void MenuItemSprite::setDisabledImage(Node* pImage)
{
    if (pImage != _normalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kDisableTag);
            pImage->setAnchorPoint(Point(0, 0));
        }

        if (_disabledImage)
        {
            removeChild(_disabledImage, true);
        }

        _disabledImage = pImage;
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

// XXX deprecated
MenuItemSprite * MenuItemSprite::create(Node* normalSprite, Node* selectedSprite, Object* target, SEL_MenuHandler selector)
{
    return MenuItemSprite::create(normalSprite, selectedSprite, NULL, target, selector);
}

MenuItemSprite * MenuItemSprite::create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback)
{
    return MenuItemSprite::create(normalSprite, selectedSprite, NULL, callback);
}

// XXX deprecated
MenuItemSprite * MenuItemSprite::create(Node *normalSprite, Node *selectedSprite, Node *disabledSprite, Object *target, SEL_MenuHandler selector)
{
    MenuItemSprite *pRet = new MenuItemSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector); 
    pRet->autorelease();
    return pRet;
}

MenuItemSprite * MenuItemSprite::create(Node *normalSprite, Node *selectedSprite, Node *disabledSprite, const ccMenuCallback& callback)
{
    MenuItemSprite *pRet = new MenuItemSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
    pRet->autorelease();
    return pRet;
}

// XXX deprecated
bool MenuItemSprite::initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Object* target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
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
    MenuItemImage *pRet = new MenuItemImage();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool MenuItemImage::init(void)
{
    return initWithNormalImage(NULL, NULL, NULL, (const ccMenuCallback&)nullptr);
}

MenuItemImage * MenuItemImage::create(const char *normalImage, const char *selectedImage)
{
    return MenuItemImage::create(normalImage, selectedImage, NULL, (const ccMenuCallback&)nullptr);
}

// XXX deprecated
MenuItemImage * MenuItemImage::create(const char *normalImage, const char *selectedImage, Object* target, SEL_MenuHandler selector)
{
    return MenuItemImage::create(normalImage, selectedImage, NULL, target, selector);
}

MenuItemImage * MenuItemImage::create(const char *normalImage, const char *selectedImage, const ccMenuCallback& callback)
{
    return MenuItemImage::create(normalImage, selectedImage, NULL, callback);
}

// XXX deprecated
MenuItemImage * MenuItemImage::create(const char *normalImage, const char *selectedImage, const char *disabledImage, Object* target, SEL_MenuHandler selector)
{
    MenuItemImage *pRet = new MenuItemImage();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, target, selector))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

MenuItemImage * MenuItemImage::create(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback)
{
    MenuItemImage *pRet = new MenuItemImage();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, callback))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

MenuItemImage * MenuItemImage::create(const char *normalImage, const char *selectedImage, const char *disabledImage)
{
    MenuItemImage *pRet = new MenuItemImage();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, (const ccMenuCallback&)nullptr))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

// XXX: deprecated
bool MenuItemImage::initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, Object* target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithNormalImage(normalImage, selectedImage, disabledImage, std::bind(selector,target, std::placeholders::_1) );
}
bool MenuItemImage::initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback)
{
    Node *normalSprite = NULL;
    Node *selectedSprite = NULL;
    Node *disabledSprite = NULL;

    if (normalImage)
    {
        normalSprite = Sprite::create(normalImage);
    }

    if (selectedImage)
    {
        selectedSprite = Sprite::create(selectedImage);
    }

    if(disabledImage)
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

// XXX: deprecated
MenuItemToggle * MenuItemToggle::createWithTarget(Object* target, SEL_MenuHandler selector, Array* menuItems)
{
    MenuItemToggle *pRet = new MenuItemToggle();
    pRet->MenuItem::initWithTarget(target, selector);
    pRet->_subItems = Array::create();
    pRet->_subItems->retain();
    
    for (unsigned int z=0; z < menuItems->count(); z++)
    {
        MenuItem* menuItem = (MenuItem*)menuItems->objectAtIndex(z);
        pRet->_subItems->addObject(menuItem);
    }
    
    pRet->_selectedIndex = UINT_MAX;
    pRet->setSelectedIndex(0);
    return pRet;
}

MenuItemToggle * MenuItemToggle::createWithCallback(const ccMenuCallback &callback, Array* menuItems)
{
    MenuItemToggle *pRet = new MenuItemToggle();
    pRet->MenuItem::initWithCallback(callback);
    pRet->_subItems = Array::create();
    pRet->_subItems->retain();

    for (unsigned int z=0; z < menuItems->count(); z++)
    {
        MenuItem* menuItem = (MenuItem*)menuItems->objectAtIndex(z);
        pRet->_subItems->addObject(menuItem);
    }

    pRet->_selectedIndex = UINT_MAX;
    pRet->setSelectedIndex(0);
    return pRet;
}

// XXX: deprecated
MenuItemToggle * MenuItemToggle::createWithTarget(Object* target, SEL_MenuHandler selector, MenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    MenuItemToggle *pRet = new MenuItemToggle();
    pRet->initWithTarget(target, selector, item, args);
    pRet->autorelease();
    va_end(args);
    return pRet;
}

MenuItemToggle * MenuItemToggle::createWithCallback(const ccMenuCallback &callback, MenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    MenuItemToggle *pRet = new MenuItemToggle();
    pRet->initWithCallback(callback, item, args);
    pRet->autorelease();
    va_end(args);
    return pRet;
}

MenuItemToggle * MenuItemToggle::create()
{
    MenuItemToggle *pRet = new MenuItemToggle();
    pRet->initWithItem(NULL);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool MenuItemToggle::initWithTarget(Object* target, SEL_MenuHandler selector, MenuItem* item, va_list args)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithCallback(std::bind( selector, target, std::placeholders::_1), item, args);
}

bool MenuItemToggle::initWithCallback(const ccMenuCallback &callback, MenuItem *item, va_list args)
{
    MenuItem::initWithCallback(callback);
    this->_subItems = Array::create();
    this->_subItems->retain();
    int z = 0;
    MenuItem *i = item;
    while(i)
    {
        z++;
        _subItems->addObject(i);
        i = va_arg(args, MenuItem*);
    }
    _selectedIndex = UINT_MAX;
    this->setSelectedIndex(0);
    return true;
}

MenuItemToggle* MenuItemToggle::create(MenuItem *item)
{
    MenuItemToggle *pRet = new MenuItemToggle();
    pRet->initWithItem(item);
    pRet->autorelease();
    return pRet;
}

bool MenuItemToggle::initWithItem(MenuItem *item)
{
    MenuItem::initWithCallback((const ccMenuCallback&)nullptr);
    setSubItems(Array::create());

    if (item)
    {
        _subItems->addObject(item);
    }
    _selectedIndex = UINT_MAX;
    this->setSelectedIndex(0);
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
    return true;
}

void MenuItemToggle::addSubItem(MenuItem *item)
{
    _subItems->addObject(item);
}

MenuItemToggle::~MenuItemToggle()
{
    CC_SAFE_RELEASE(_subItems);
}

void MenuItemToggle::setSelectedIndex(unsigned int index)
{
    if( index != _selectedIndex && _subItems->count() > 0 )
    {
        _selectedIndex = index;
        MenuItem *currentItem = (MenuItem*)getChildByTag(kCurrentItem);
        if( currentItem )
        {
            currentItem->removeFromParentAndCleanup(false);
        }

        MenuItem* item = (MenuItem*)_subItems->objectAtIndex(_selectedIndex);
        this->addChild(item, 0, kCurrentItem);
        Size s = item->getContentSize();
        this->setContentSize(s);
        item->setPosition( Point( s.width/2, s.height/2 ) );
    }
}

void MenuItemToggle::selected()
{
    MenuItem::selected();
    static_cast<MenuItem*>(_subItems->objectAtIndex(_selectedIndex))->selected();
}

void MenuItemToggle::unselected()
{
    MenuItem::unselected();
    static_cast<MenuItem*>(_subItems->objectAtIndex(_selectedIndex))->unselected();
}

void MenuItemToggle::activate()
{
    // update index
    if( _enabled ) 
    {
        unsigned int newIndex = (_selectedIndex + 1) % _subItems->count();
        this->setSelectedIndex(newIndex);
    }
    MenuItem::activate();
}
void MenuItemToggle::setEnabled(bool enabled)
{
    if (_enabled != enabled)
    {
        MenuItem::setEnabled(enabled);

        if(_subItems && _subItems->count() > 0)
        {
            Object* pObj = NULL;
            CCARRAY_FOREACH(_subItems, pObj)
            {
                MenuItem* pItem = static_cast<MenuItem*>(pObj);
                pItem->setEnabled(enabled);
            }
        }
    }
}

MenuItem* MenuItemToggle::getSelectedItem()
{
    return static_cast<MenuItem*>(_subItems->objectAtIndex(_selectedIndex));
}

NS_CC_END

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
