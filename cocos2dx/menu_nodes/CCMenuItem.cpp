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
#include "support/CCPointExtension.h"
#include "actions/CCActionInterval.h"
#include "sprite_nodes/CCSprite.h"
#include "label_nodes/CCLabelAtlas.h"
#include "label_nodes/CCLabelTTF.h"
#include "script_support/CCScriptSupport.h"
#include <stdarg.h>
#include <cstring>

NS_CC_BEGIN
    
static unsigned int _globalFontSize = kCCItemSize;
static std::string _globalFontName = "Marker Felt";
static bool _globalFontNameRelease = false;

const unsigned int    kCurrentItem = 0xc0c05001;
const unsigned int    kZoomActionTag = 0xc0c05002;

const unsigned int    kNormalTag = 0x1;
const unsigned int    kSelectedTag = 0x2;
const unsigned int    kDisableTag = 0x3;
//
// CCMenuItem
//

CCMenuItem* CCMenuItem::create()
{
    return CCMenuItem::create((const ccMenuCallback&)nullptr);
}

// XXX deprecated
CCMenuItem* CCMenuItem::create(CCObject *target, SEL_MenuHandler selector)
{
    CCMenuItem *pRet = new CCMenuItem();
    pRet->initWithTarget(target, selector);
    pRet->autorelease();
    return pRet;
}

CCMenuItem* CCMenuItem::create( const ccMenuCallback& callback)
{
    CCMenuItem *pRet = new CCMenuItem();
    pRet->initWithCallback(callback);
    pRet->autorelease();
    return pRet;
}

// XXX deprecated
bool CCMenuItem::initWithTarget(cocos2d::CCObject *target, SEL_MenuHandler selector )
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithCallback( std::bind(selector,target, std::placeholders::_1) );
}

bool CCMenuItem::initWithCallback(const ccMenuCallback& callback)
{
    setAnchorPoint(ccp(0.5f, 0.5f));
	_callback = callback;
    _enabled = true;
    _selected = false;
    return true;
}

CCMenuItem::~CCMenuItem()
{
	CC_SAFE_RELEASE(_target);

    unregisterScriptTapHandler();
}

void CCMenuItem::selected()
{
    _selected = true;
}

void CCMenuItem::unselected()
{
    _selected = false;
}

void CCMenuItem::registerScriptTapHandler(int nHandler)
{
    unregisterScriptTapHandler();
    _scriptTapHandler = nHandler;
    LUALOG("[LUA] Add CCMenuItem script handler: %d", _scriptTapHandler);
}

void CCMenuItem::unregisterScriptTapHandler(void)
{
    if (_scriptTapHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_scriptTapHandler);
        LUALOG("[LUA] Remove CCMenuItem script handler: %d", _scriptTapHandler);
        _scriptTapHandler = 0;
    }
}

void CCMenuItem::activate()
{
    if (_enabled)
    {
        if( _callback )
        {
			_callback(this);
        }
        
        if (kScriptTypeNone != _scriptType)
        {
            CCScriptEngineManager::sharedManager()->getScriptEngine()->executeMenuItemEvent(this);
        }
    }
}

void CCMenuItem::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool CCMenuItem::isEnabled()
{
    return _enabled;
}

CCRect CCMenuItem::rect()
{
    return CCRectMake( _position.x - _contentSize.width * _anchorPoint.x,
                      _position.y - _contentSize.height * _anchorPoint.y,
                      _contentSize.width, _contentSize.height);
}

bool CCMenuItem::isSelected()
{
    return _selected;
}

// XXX deprecated
void CCMenuItem::setTarget(CCObject *target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	setCallback( std::bind( selector, target, std::placeholders::_1) );
}

void CCMenuItem::setCallback(const ccMenuCallback& callback)
{
	_callback = callback;
}


//
//CCMenuItemLabel
//

const ccColor3B& CCMenuItemLabel::getDisabledColor()
{
    return _disabledColor;
}
void CCMenuItemLabel::setDisabledColor(const ccColor3B& var)
{
    _disabledColor = var;
}
CCNode *CCMenuItemLabel::getLabel()
{
    return _label;
}
void CCMenuItemLabel::setLabel(CCNode* var)
{
    if (var)
    {
        addChild(var);
        var->setAnchorPoint(ccp(0, 0));
        setContentSize(var->getContentSize());
    }
    
    if (_label)
    {
        removeChild(_label, true);
    }
    
    _label = var;
}

// XXX: deprecated
CCMenuItemLabel * CCMenuItemLabel::create(CCNode*label, CCObject* target, SEL_MenuHandler selector)
{
    CCMenuItemLabel *pRet = new CCMenuItemLabel();
    pRet->initWithLabel(label, target, selector);
    pRet->autorelease();
    return pRet;
}

CCMenuItemLabel * CCMenuItemLabel::create(CCNode*label, const ccMenuCallback& callback)
{
    CCMenuItemLabel *pRet = new CCMenuItemLabel();
    pRet->initWithLabel(label, callback);
    pRet->autorelease();
    return pRet;
}

CCMenuItemLabel* CCMenuItemLabel::create(CCNode *label)
{
    CCMenuItemLabel *pRet = new CCMenuItemLabel();
    pRet->initWithLabel(label, (const ccMenuCallback&) nullptr);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool CCMenuItemLabel::initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithLabel(label, std::bind(selector,target, std::placeholders::_1) );
}

bool CCMenuItemLabel::initWithLabel(CCNode* label, const ccMenuCallback& callback)
{
    CCMenuItem::initWithCallback(callback);
    _originalScale = 1.0f;
    _colorBackup = ccWHITE;
    setDisabledColor(ccc3(126,126,126));
    this->setLabel(label);

    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);

    return true;
}


CCMenuItemLabel::~CCMenuItemLabel()
{
}

void CCMenuItemLabel::setString(const char * label)
{
    dynamic_cast<CCLabelProtocol*>(_label)->setString(label);
    this->setContentSize(_label->getContentSize());
}

void CCMenuItemLabel::activate()
{
    if(_enabled)
    {
        this->stopAllActions();
        this->setScale( _originalScale );
        CCMenuItem::activate();
    }
}

void CCMenuItemLabel::selected()
{
    // subclass to change the default action
    if(_enabled)
    {
        CCMenuItem::selected();
        
        CCAction *action = getActionByTag(kZoomActionTag);
        if (action)
        {
            this->stopAction(action);
        }
        else
        {
            _originalScale = this->getScale();
        }
        
        CCAction *zoomAction = CCScaleTo::create(0.1f, _originalScale * 1.2f);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

void CCMenuItemLabel::unselected()
{
    // subclass to change the default action
    if(_enabled)
    {
        CCMenuItem::unselected();
        this->stopActionByTag(kZoomActionTag);
        CCAction *zoomAction = CCScaleTo::create(0.1f, _originalScale);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

void CCMenuItemLabel::setEnabled(bool enabled)
{
    if( _enabled != enabled ) 
    {
        if(enabled == false)
        {
            _colorBackup = dynamic_cast<CCRGBAProtocol*>(_label)->getColor();
            dynamic_cast<CCRGBAProtocol*>(_label)->setColor(_disabledColor);
        }
        else
        {
            dynamic_cast<CCRGBAProtocol*>(_label)->setColor(_colorBackup);
        }
    }
    CCMenuItem::setEnabled(enabled);
}

//
//CCMenuItemAtlasFont
//

CCMenuItemAtlasFont * CCMenuItemAtlasFont::create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap)
{
    return CCMenuItemAtlasFont::create(value, charMapFile, itemWidth, itemHeight, startCharMap, (const ccMenuCallback&)nullptr);
}

// XXX: deprecated
CCMenuItemAtlasFont * CCMenuItemAtlasFont::create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector)
{
    CCMenuItemAtlasFont *pRet = new CCMenuItemAtlasFont();
    pRet->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, target, selector);
    pRet->autorelease();
    return pRet;
}

CCMenuItemAtlasFont * CCMenuItemAtlasFont::create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback)
{
    CCMenuItemAtlasFont *pRet = new CCMenuItemAtlasFont();
    pRet->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, callback);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool CCMenuItemAtlasFont::initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector)
{
    CCAssert( value != NULL && strlen(value) != 0, "value length must be greater than 0");

	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, std::bind(selector,target, std::placeholders::_1) );
}

bool CCMenuItemAtlasFont::initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback)
{
    CCAssert( value != NULL && strlen(value) != 0, "value length must be greater than 0");
    CCLabelAtlas *label = new CCLabelAtlas();
    label->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap);
    label->autorelease();
    if (CCMenuItemLabel::initWithLabel(label, callback))
    {
        // do something ?
    }
    return true;
}

//
//CCMenuItemFont
//

void CCMenuItemFont::setFontSize(unsigned int s)
{
    _globalFontSize = s;
}

unsigned int CCMenuItemFont::fontSize()
{
    return _globalFontSize;
}

void CCMenuItemFont::setFontName(const char *name)
{
    if (_globalFontNameRelease)
    {
        _globalFontName.clear();
    }
    _globalFontName = name;
    _globalFontNameRelease = true;
}

const char * CCMenuItemFont::fontName()
{
    return _globalFontName.c_str();
}

// XXX: deprecated
CCMenuItemFont * CCMenuItemFont::create(const char *value, CCObject* target, SEL_MenuHandler selector)
{
    CCMenuItemFont *pRet = new CCMenuItemFont();
    pRet->initWithString(value, target, selector);
    pRet->autorelease();
    return pRet;
}

CCMenuItemFont * CCMenuItemFont::create(const char *value, const ccMenuCallback& callback)
{
    CCMenuItemFont *pRet = new CCMenuItemFont();
    pRet->initWithString(value, callback);
    pRet->autorelease();
    return pRet;
}


CCMenuItemFont * CCMenuItemFont::create(const char *value)
{
    CCMenuItemFont *pRet = new CCMenuItemFont();
    pRet->initWithString(value, (const ccMenuCallback&)nullptr);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool CCMenuItemFont::initWithString(const char *value, CCObject* target, SEL_MenuHandler selector)
{
    CCAssert( value != NULL && strlen(value) != 0, "Value length must be greater than 0");

	_target = target;
    CC_SAFE_RETAIN(target);
	return initWithString(value, std::bind(selector,target, std::placeholders::_1) );
}

bool CCMenuItemFont::initWithString(const char *value, const ccMenuCallback& callback)
{
    CCAssert( value != NULL && strlen(value) != 0, "Value length must be greater than 0");

    _fontName = _globalFontName;
    _fontSize = _globalFontSize;

    CCLabelTTF *label = CCLabelTTF::create(value, _fontName.c_str(), (float)_fontSize);
    if (CCMenuItemLabel::initWithLabel(label, callback))
    {
        // do something ?
    }
    return true;
}

void CCMenuItemFont::recreateLabel()
{
    CCLabelTTF *label = CCLabelTTF::create(dynamic_cast<CCLabelProtocol*>(_label)->getString(), 
                                                    _fontName.c_str(), (float)_fontSize);
    this->setLabel(label);
}

void CCMenuItemFont::setFontSizeObj(unsigned int s)
{
    _fontSize = s;
    recreateLabel();
}

unsigned int CCMenuItemFont::fontSizeObj()
{
    return _fontSize;
}

void CCMenuItemFont::setFontNameObj(const char* name)
{
    _fontName = name;
    recreateLabel();
}

const char* CCMenuItemFont::fontNameObj()
{
    return _fontName.c_str();
}

//
//CCMenuItemSprite
//

CCNode * CCMenuItemSprite::getNormalImage()
{
    return _normalImage;
}

void CCMenuItemSprite::setNormalImage(CCNode* pImage)
{
    if (pImage != _normalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kNormalTag);
            pImage->setAnchorPoint(ccp(0, 0));
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

CCNode * CCMenuItemSprite::getSelectedImage()
{
    return _selectedImage;
}

void CCMenuItemSprite::setSelectedImage(CCNode* pImage)
{
    if (pImage != _normalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kSelectedTag);
            pImage->setAnchorPoint(ccp(0, 0));
        }

        if (_selectedImage)
        {
            removeChild(_selectedImage, true);
        }

        _selectedImage = pImage;
        this->updateImagesVisibility();
    }
}

CCNode * CCMenuItemSprite::getDisabledImage()
{
    return _disabledImage;
}

void CCMenuItemSprite::setDisabledImage(CCNode* pImage)
{
    if (pImage != _normalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kDisableTag);
            pImage->setAnchorPoint(ccp(0, 0));
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

CCMenuItemSprite * CCMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite)
{
    return CCMenuItemSprite::create(normalSprite, selectedSprite, disabledSprite, (const ccMenuCallback&)nullptr);
}

// XXX deprecated
CCMenuItemSprite * CCMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector)
{
    return CCMenuItemSprite::create(normalSprite, selectedSprite, NULL, target, selector);
}

CCMenuItemSprite * CCMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite, const ccMenuCallback& callback)
{
    return CCMenuItemSprite::create(normalSprite, selectedSprite, NULL, callback);
}

// XXX deprecated
CCMenuItemSprite * CCMenuItemSprite::create(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
    CCMenuItemSprite *pRet = new CCMenuItemSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector); 
    pRet->autorelease();
    return pRet;
}

CCMenuItemSprite * CCMenuItemSprite::create(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, const ccMenuCallback& callback)
{
    CCMenuItemSprite *pRet = new CCMenuItemSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
    pRet->autorelease();
    return pRet;
}

// XXX deprecated
bool CCMenuItemSprite::initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, std::bind(selector,target, std::placeholders::_1) );
}

bool CCMenuItemSprite::initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, const ccMenuCallback& callback)
{
    CCMenuItem::initWithCallback(callback);
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
void CCMenuItemSprite::selected()
{
    CCMenuItem::selected();

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

void CCMenuItemSprite::unselected()
{
    CCMenuItem::unselected();
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

void CCMenuItemSprite::setEnabled(bool bEnabled)
{
    if( _enabled != bEnabled ) 
    {
        CCMenuItem::setEnabled(bEnabled);
        this->updateImagesVisibility();
    }
}

// Helper 
void CCMenuItemSprite::updateImagesVisibility()
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
/// CCMenuItemImage
///

CCMenuItemImage* CCMenuItemImage::create()
{
    CCMenuItemImage *pRet = new CCMenuItemImage();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCMenuItemImage::init(void)
{
    return initWithNormalImage(NULL, NULL, NULL, (const ccMenuCallback&)nullptr);
}

CCMenuItemImage * CCMenuItemImage::create(const char *normalImage, const char *selectedImage)
{
    return CCMenuItemImage::create(normalImage, selectedImage, NULL, (const ccMenuCallback&)nullptr);
}

// XXX deprecated
CCMenuItemImage * CCMenuItemImage::create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector)
{
    return CCMenuItemImage::create(normalImage, selectedImage, NULL, target, selector);
}

CCMenuItemImage * CCMenuItemImage::create(const char *normalImage, const char *selectedImage, const ccMenuCallback& callback)
{
    return CCMenuItemImage::create(normalImage, selectedImage, NULL, callback);
}

// XXX deprecated
CCMenuItemImage * CCMenuItemImage::create(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector)
{
    CCMenuItemImage *pRet = new CCMenuItemImage();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, target, selector))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCMenuItemImage * CCMenuItemImage::create(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback)
{
    CCMenuItemImage *pRet = new CCMenuItemImage();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, callback))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCMenuItemImage * CCMenuItemImage::create(const char *normalImage, const char *selectedImage, const char *disabledImage)
{
    CCMenuItemImage *pRet = new CCMenuItemImage();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, (const ccMenuCallback&)nullptr))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

// XXX: deprecated
bool CCMenuItemImage::initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithNormalImage(normalImage, selectedImage, disabledImage, std::bind(selector,target, std::placeholders::_1) );
}
bool CCMenuItemImage::initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, const ccMenuCallback& callback)
{
    CCNode *normalSprite = NULL;
    CCNode *selectedSprite = NULL;
    CCNode *disabledSprite = NULL;

    if (normalImage)
    {
        normalSprite = CCSprite::create(normalImage);
    }

    if (selectedImage)
    {
        selectedSprite = CCSprite::create(selectedImage);
    }

    if(disabledImage)
    {
        disabledSprite = CCSprite::create(disabledImage);
    }
    return initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
}

//
// Setter of sprite frames
//
void CCMenuItemImage::setNormalSpriteFrame(CCSpriteFrame * frame)
{
    setNormalImage(CCSprite::createWithSpriteFrame(frame));
}

void CCMenuItemImage::setSelectedSpriteFrame(CCSpriteFrame * frame)
{
    setSelectedImage(CCSprite::createWithSpriteFrame(frame));
}

void CCMenuItemImage::setDisabledSpriteFrame(CCSpriteFrame * frame)
{
    setDisabledImage(CCSprite::createWithSpriteFrame(frame));
}

//
// MenuItemToggle
//

void CCMenuItemToggle::setSubItems(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_subItems);
    _subItems = var;
}

CCArray* CCMenuItemToggle::getSubItems()
{
    return _subItems;
}

// XXX: deprecated
CCMenuItemToggle * CCMenuItemToggle::createWithTarget(CCObject* target, SEL_MenuHandler selector, CCArray* menuItems)
{
    CCMenuItemToggle *pRet = new CCMenuItemToggle();
    pRet->CCMenuItem::initWithTarget(target, selector);
    pRet->_subItems = CCArray::create();
    pRet->_subItems->retain();
    
    for (unsigned int z=0; z < menuItems->count(); z++)
    {
        CCMenuItem* menuItem = (CCMenuItem*)menuItems->objectAtIndex(z);
        pRet->_subItems->addObject(menuItem);
    }
    
    pRet->_selectedIndex = UINT_MAX;
    pRet->setSelectedIndex(0);
    return pRet;
}

CCMenuItemToggle * CCMenuItemToggle::createWithCallback(const ccMenuCallback &callback, CCArray* menuItems)
{
    CCMenuItemToggle *pRet = new CCMenuItemToggle();
    pRet->CCMenuItem::initWithCallback(callback);
    pRet->_subItems = CCArray::create();
    pRet->_subItems->retain();

    for (unsigned int z=0; z < menuItems->count(); z++)
    {
        CCMenuItem* menuItem = (CCMenuItem*)menuItems->objectAtIndex(z);
        pRet->_subItems->addObject(menuItem);
    }

    pRet->_selectedIndex = UINT_MAX;
    pRet->setSelectedIndex(0);
    return pRet;
}

// XXX: deprecated
CCMenuItemToggle * CCMenuItemToggle::createWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    CCMenuItemToggle *pRet = new CCMenuItemToggle();
    pRet->initWithTarget(target, selector, item, args);
    pRet->autorelease();
    va_end(args);
    return pRet;
}

CCMenuItemToggle * CCMenuItemToggle::createWithCallback(const ccMenuCallback &callback, CCMenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    CCMenuItemToggle *pRet = new CCMenuItemToggle();
    pRet->initWithCallback(callback, item, args);
    pRet->autorelease();
    va_end(args);
    return pRet;
}

CCMenuItemToggle * CCMenuItemToggle::create()
{
    CCMenuItemToggle *pRet = new CCMenuItemToggle();
    pRet->initWithItem(NULL);
    pRet->autorelease();
    return pRet;
}

// XXX: deprecated
bool CCMenuItemToggle::initWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, va_list args)
{
	_target = target;
	CC_SAFE_RETAIN(_target);
	return initWithCallback(std::bind( selector, target, std::placeholders::_1), item, args);
}

bool CCMenuItemToggle::initWithCallback(const ccMenuCallback &callback, CCMenuItem *item, va_list args)
{
    CCMenuItem::initWithCallback(callback);
    this->_subItems = CCArray::create();
    this->_subItems->retain();
    int z = 0;
    CCMenuItem *i = item;
    while(i)
    {
        z++;
        _subItems->addObject(i);
        i = va_arg(args, CCMenuItem*);
    }
    _selectedIndex = UINT_MAX;
    this->setSelectedIndex(0);
    return true;
}

CCMenuItemToggle* CCMenuItemToggle::create(CCMenuItem *item)
{
    CCMenuItemToggle *pRet = new CCMenuItemToggle();
    pRet->initWithItem(item);
    pRet->autorelease();
    return pRet;
}

bool CCMenuItemToggle::initWithItem(CCMenuItem *item)
{
    CCMenuItem::initWithCallback((const ccMenuCallback&)nullptr);
    setSubItems(CCArray::create());

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

void CCMenuItemToggle::addSubItem(CCMenuItem *item)
{
    _subItems->addObject(item);
}

CCMenuItemToggle::~CCMenuItemToggle()
{
    CC_SAFE_RELEASE(_subItems);
}
void CCMenuItemToggle::setSelectedIndex(unsigned int index)
{
    if( index != _selectedIndex && _subItems->count() > 0 )
    {
        _selectedIndex = index;
        CCMenuItem *currentItem = (CCMenuItem*)getChildByTag(kCurrentItem);
        if( currentItem )
        {
            currentItem->removeFromParentAndCleanup(false);
        }

        CCMenuItem* item = (CCMenuItem*)_subItems->objectAtIndex(_selectedIndex);
        this->addChild(item, 0, kCurrentItem);
        CCSize s = item->getContentSize();
        this->setContentSize(s);
        item->setPosition( ccp( s.width/2, s.height/2 ) );
    }
}
unsigned int CCMenuItemToggle::getSelectedIndex()
{
    return _selectedIndex;
}
void CCMenuItemToggle::selected()
{
    CCMenuItem::selected();
    ((CCMenuItem*)(_subItems->objectAtIndex(_selectedIndex)))->selected();
}
void CCMenuItemToggle::unselected()
{
    CCMenuItem::unselected();
    ((CCMenuItem*)(_subItems->objectAtIndex(_selectedIndex)))->unselected();
}
void CCMenuItemToggle::activate()
{
    // update index
    if( _enabled ) 
    {
        unsigned int newIndex = (_selectedIndex + 1) % _subItems->count();
        this->setSelectedIndex(newIndex);
    }
    CCMenuItem::activate();
}
void CCMenuItemToggle::setEnabled(bool enabled)
{
    if (_enabled != enabled)
    {
        CCMenuItem::setEnabled(enabled);

        if(_subItems && _subItems->count() > 0)
        {
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(_subItems, pObj)
            {
                CCMenuItem* pItem = (CCMenuItem*)pObj;
                pItem->setEnabled(enabled);
            }
        }
    }
}

CCMenuItem* CCMenuItemToggle::selectedItem()
{
    return (CCMenuItem*)_subItems->objectAtIndex(_selectedIndex);
}

NS_CC_END
