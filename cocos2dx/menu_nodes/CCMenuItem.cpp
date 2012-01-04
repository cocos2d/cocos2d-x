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
#include <cstring>
#include "CCMenuItem.h"
#include "CCPointExtension.h"
#include "CCActionInterval.h"
#include "CCSprite.h"
#include "CCLabelAtlas.h"
#include "CCLabelTTF.h"
#include "CCScriptSupport.h"

#include <stdarg.h>

namespace cocos2d{

	static unsigned int _fontSize = kCCItemSize;
	static std::string _fontName = "Marker Felt";
	static bool _fontNameRelease = false;

    const unsigned int	kCurrentItem = 0xc0c05001;
    const unsigned int	kZoomActionTag = 0xc0c05002;

    const unsigned int	kNormalTag = 0x1;
    const unsigned int	kSelectedTag = 0x2;
    const unsigned int	kDisableTag = 0x3;
	//
	// CCMenuItem
	//
	CCMenuItem * CCMenuItem::itemWithTarget(SelectorProtocol *rec, SEL_MenuHandler selector)
	{
		CCMenuItem *pRet = new CCMenuItem();
		pRet->initWithTarget(rec, selector);
		pRet->autorelease();
		return pRet;
	}
	bool CCMenuItem::initWithTarget(SelectorProtocol *rec, SEL_MenuHandler selector)
	{
		setAnchorPoint(ccp(0.5f, 0.5f));
		m_pListener = rec;
		m_pfnSelector = selector;
		m_bIsEnabled = true;
		m_bIsSelected = false;
		return true;
	}

	void CCMenuItem::selected()
	{
		m_bIsSelected = true;
	}

	void CCMenuItem::unselected()
	{
		m_bIsSelected = false;
	}

	void CCMenuItem::registerScriptHandler(const char* pszFunctionName)
	{
		if (pszFunctionName)
		{
			this->m_functionName = string(pszFunctionName);
		}
		else
		{
			this->m_functionName.clear();
		}
	}

	void CCMenuItem::activate()
	{
		if (m_bIsEnabled)
		{
			if (m_pListener && m_pfnSelector)
			{
				(m_pListener->*m_pfnSelector)(this);
			}

			if (m_functionName.size() && CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine())
			{
				CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine()->executeCallFuncN(m_functionName.c_str(), this);
			}
		}
	}

	void CCMenuItem::setIsEnabled(bool enabled)
	{
		m_bIsEnabled = enabled;
	}

	bool CCMenuItem::getIsEnabled()
	{
		return m_bIsEnabled;
	}

	CCRect CCMenuItem::rect()
	{
		return CCRectMake( m_tPosition.x - m_tContentSize.width * m_tAnchorPoint.x, 
						m_tPosition.y - m_tContentSize.height * m_tAnchorPoint.y,
						m_tContentSize.width, m_tContentSize.height);
	}

	bool CCMenuItem::getIsSelected()
	{
		return m_bIsSelected;
	}

        void CCMenuItem::setTarget(SelectorProtocol *rec, SEL_MenuHandler selector)
        {
            m_pListener = rec;
            m_pfnSelector = selector;
        }

        //
	//CCMenuItemLabel
	//
	const ccColor3B& CCMenuItemLabel::getDisabledColor()
	{
		return m_tDisabledColor;
	}
	void CCMenuItemLabel::setDisabledColor(const ccColor3B& var)
	{
		m_tDisabledColor = var;
	}
	CCNode *CCMenuItemLabel::getLabel()
	{
		return m_pLabel;
	}
	void CCMenuItemLabel::setLabel(CCNode* var)
	{
        if (var)
        {
            addChild(var);
            var->setAnchorPoint(ccp(0, 0));
            setContentSize(var->getContentSize());
        }

        if (m_pLabel)
        {
            removeChild(m_pLabel, true);
        }
        
		m_pLabel = var;
	}
	CCMenuItemLabel * CCMenuItemLabel::itemWithLabel(CCNode*label, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCMenuItemLabel *pRet = new CCMenuItemLabel();
		pRet->initWithLabel(label, target, selector);
		pRet->autorelease();
		return pRet;
	}
	CCMenuItemLabel* CCMenuItemLabel::itemWithLabel(CCNode *label)
	{
		CCMenuItemLabel *pRet = new CCMenuItemLabel();
		pRet->initWithLabel(label, NULL, NULL);
		pRet->autorelease();
		return pRet;
	}
	bool CCMenuItemLabel::initWithLabel(CCNode* label, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCMenuItem::initWithTarget(target, selector);
		m_fOriginalScale = 1.0f;
		m_tColorBackup = ccWHITE;
		m_tDisabledColor = ccc3(126,126,126);
		this->setLabel(label);
		return true;
	}
	CCMenuItemLabel::~CCMenuItemLabel()
	{
	}
	void CCMenuItemLabel::setString(const char * label)
	{
		dynamic_cast<CCLabelProtocol*>(m_pLabel)->setString(label);
		this->setContentSize(m_pLabel->getContentSize());
	}
	void CCMenuItemLabel::activate()
	{
		if(m_bIsEnabled)
		{
			this->stopAllActions();
			this->setScale( m_fOriginalScale );
			CCMenuItem::activate();
		}
	}
	void CCMenuItemLabel::selected()
	{
		// subclass to change the default action
		if(m_bIsEnabled)
		{
			CCMenuItem::selected();

			CCAction *action = getActionByTag(kZoomActionTag);
			if (action)
			{
				this->stopAction(action);
			}
			else
			{
				m_fOriginalScale = this->getScale();
			}
			
			CCAction *zoomAction = CCScaleTo::actionWithDuration(0.1f, m_fOriginalScale * 1.2f);
	   	 	zoomAction->setTag(kZoomActionTag);
			this->runAction(zoomAction);
		}
	}
	void CCMenuItemLabel::unselected()
	{
		// subclass to change the default action
		if(m_bIsEnabled)
		{
			CCMenuItem::unselected();
			this->stopActionByTag(kZoomActionTag);
			CCAction *zoomAction = CCScaleTo::actionWithDuration(0.1f, m_fOriginalScale);
			zoomAction->setTag(kZoomActionTag);
			this->runAction(zoomAction);
		}
	}
	void CCMenuItemLabel::setIsEnabled(bool enabled)
	{
		if( m_bIsEnabled != enabled ) 
		{
			if(enabled == false)
			{
				m_tColorBackup = dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getColor();
				dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(m_tDisabledColor);
			}
			else
			{
				dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(m_tColorBackup);
			}
		}
		CCMenuItem::setIsEnabled(enabled);
	}
	void CCMenuItemLabel::setOpacity(GLubyte opacity)
	{
		dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setOpacity(opacity);
	}
	GLubyte CCMenuItemLabel::getOpacity()
	{
		return dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getOpacity();
	}
	void CCMenuItemLabel::setColor(const ccColor3B& color)
	{
		dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(color);
	}
	const ccColor3B& CCMenuItemLabel::getColor()
	{
		return dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getColor();
	}

	//
	//CCMenuItemAtlasFont
	//
	CCMenuItemAtlasFont * CCMenuItemAtlasFont::itemFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap)
	{
		return CCMenuItemAtlasFont::itemFromString(value, charMapFile, itemWidth, itemHeight, startCharMap, NULL, NULL);
	}

	CCMenuItemAtlasFont * CCMenuItemAtlasFont::itemFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCMenuItemAtlasFont *pRet = new CCMenuItemAtlasFont();
		pRet->initFromString(value, charMapFile, itemWidth, itemHeight, startCharMap, target, selector);
		pRet->autorelease();
		return pRet;
	}
	bool CCMenuItemAtlasFont::initFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCAssert( value != NULL && strlen(value) != 0, "value length must be greater than 0");
		CCLabelAtlas *label = new CCLabelAtlas();
		label->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap);
		label->autorelease();
		if (CCMenuItemLabel::initWithLabel(label, target, selector))
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
		_fontSize = s;
	}
	unsigned int CCMenuItemFont::fontSize()
	{
		return _fontSize;
	}
	void CCMenuItemFont::setFontName(const char *name)
	{
		if( _fontNameRelease )
		{
			_fontName.clear();
		}
		_fontName = name;
		_fontNameRelease = true;
	}
	const char * CCMenuItemFont::fontName()
	{
		return _fontName.c_str();
	}
	CCMenuItemFont * CCMenuItemFont::itemFromString(const char *value, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCMenuItemFont *pRet = new CCMenuItemFont();
		pRet->initFromString(value, target, selector);
		pRet->autorelease();
		return pRet;
	}
	CCMenuItemFont * CCMenuItemFont::itemFromString(const char *value)
	{
		CCMenuItemFont *pRet = new CCMenuItemFont();
		pRet->initFromString(value, NULL, NULL);
		pRet->autorelease();
		return pRet;
	}
	bool CCMenuItemFont::initFromString(const char *value, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCAssert( value != NULL && strlen(value) != 0, "Value length must be greater than 0");

		m_strFontName = _fontName;
		m_uFontSize = _fontSize;

		CCLabelTTF *label = CCLabelTTF::labelWithString(value, m_strFontName.c_str(), (float)m_uFontSize);
		if (CCMenuItemLabel::initWithLabel(label, target, selector))
		{
			// do something ?
		}
		return true;
	}

	void CCMenuItemFont::recreateLabel()
	{
		CCLabelTTF *label = CCLabelTTF::labelWithString(dynamic_cast<CCLabelProtocol*>(m_pLabel)->getString(), 
			m_strFontName.c_str(), (float)m_uFontSize);
		this->setLabel(label);
	}

	void CCMenuItemFont::setFontSizeObj(unsigned int s)
	{
		m_uFontSize = s;
		recreateLabel();
	}

	unsigned int CCMenuItemFont::fontSizeObj()
	{
		return m_uFontSize;
	}

	void CCMenuItemFont::setFontNameObj(const char* name)
	{
		m_strFontName = name;
		recreateLabel();
	}

	const char* CCMenuItemFont::fontNameObj()
	{
		return m_strFontName.c_str();
	}

	//
	//CCMenuItemSprite
	//
	CCNode * CCMenuItemSprite::getNormalImage()
	{
		return m_pNormalImage;
	}
	void CCMenuItemSprite::setNormalImage(CCNode* var)
	{
        if (var)
        {
            addChild(var, 0, kNormalTag);
            var->setAnchorPoint(ccp(0, 0));
            var->setIsVisible(true);
        }

        if (m_pNormalImage)
        {
            removeChild(m_pNormalImage, true);
        }

        m_pNormalImage = var;
	}
	CCNode * CCMenuItemSprite::getSelectedImage()
	{
		return m_pSelectedImage;
	}
	void CCMenuItemSprite::setSelectedImage(CCNode* var)
	{
        if (var)
        {
            addChild(var, 0, kSelectedTag);
            var->setAnchorPoint(ccp(0, 0));
            var->setIsVisible(false);
        }

        if (m_pSelectedImage)
        {
            removeChild(m_pSelectedImage, true);
        }

        m_pSelectedImage = var;
	}
	CCNode * CCMenuItemSprite::getDisabledImage()
	{
		return m_pDisabledImage;
	}
	void CCMenuItemSprite::setDisabledImage(CCNode* var)
	{
        if (var)
        {
            addChild(var, 0, kDisableTag);
            var->setAnchorPoint(ccp(0, 0));
            var->setIsVisible(false);
        }

        if (m_pDisabledImage)
        {
            removeChild(m_pDisabledImage, true);
        }

        m_pDisabledImage = var;
	}
    //
    //CCMenuItemSprite - CCRGBAProtocol protocol
    //
    void CCMenuItemSprite::setOpacity(GLubyte opacity)
    {
        dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->setOpacity(opacity);

		if (m_pSelectedImage)
		{
			dynamic_cast<CCRGBAProtocol*>(m_pSelectedImage)->setOpacity(opacity);
		}

        if (m_pDisabledImage)
        {
            dynamic_cast<CCRGBAProtocol*>(m_pDisabledImage)->setOpacity(opacity);
        }
    }
    void CCMenuItemSprite::setColor(const ccColor3B& color)
    {
        dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->setColor(color);

		if (m_pSelectedImage)
		{
			dynamic_cast<CCRGBAProtocol*>(m_pSelectedImage)->setColor(color);
		}    

        if (m_pDisabledImage)
        {
            dynamic_cast<CCRGBAProtocol*>(m_pDisabledImage)->setColor(color);
        }
    }
    GLubyte CCMenuItemSprite::getOpacity()
    {
        return dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->getOpacity();
    }
    const ccColor3B& CCMenuItemSprite::getColor()
    {
        return dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->getColor();
    }
	CCMenuItemSprite * CCMenuItemSprite::itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite)
	{
		return CCMenuItemSprite::itemFromNormalSprite(normalSprite, selectedSprite, NULL, NULL, NULL);
	}
	CCMenuItemSprite * CCMenuItemSprite::itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		return CCMenuItemSprite::itemFromNormalSprite(normalSprite, selectedSprite, NULL, target, selector);
	}
	CCMenuItemSprite * CCMenuItemSprite::itemFromNormalSprite(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, SelectorProtocol *target, SEL_MenuHandler selector)
	{
		CCMenuItemSprite *pRet = new CCMenuItemSprite();
		pRet->initFromNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector); 
		pRet->autorelease();
		return pRet;
	}
	bool CCMenuItemSprite::initFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCAssert(normalSprite != NULL, "");
		CCMenuItem::initWithTarget(target, selector); 
        setNormalImage(normalSprite);
        setSelectedImage(selectedSprite);
        setDisabledImage(disabledSprite);

		this->setContentSize(m_pNormalImage->getContentSize());
		return true;
	}

    /**
    @since v0.99.5
    */
    void CCMenuItemSprite::selected()
    {
        CCMenuItem::selected();

        if (m_pDisabledImage)
        {
            m_pDisabledImage->setIsVisible(false);
        }

        if (m_pSelectedImage)
        {
            m_pNormalImage->setIsVisible(false);
            m_pSelectedImage->setIsVisible(true);
        }
        else
        {
            m_pNormalImage->setIsVisible(true);
        }
    }

    void CCMenuItemSprite::unselected()
    {
        CCMenuItem::unselected();

        m_pNormalImage->setIsVisible(true);

        if (m_pSelectedImage)
        {
            m_pSelectedImage->setIsVisible(false);
        }

        if (m_pDisabledImage)
        {
            m_pDisabledImage->setIsVisible(false);
        }
    }

    void CCMenuItemSprite::setIsEnabled(bool bEnabled)
    {
        CCMenuItem::setIsEnabled(bEnabled);

        if (m_pSelectedImage)
        {
            m_pSelectedImage->setIsVisible(false);
        }

        if (bEnabled)
        {
            m_pNormalImage->setIsVisible(true);

            if (m_pDisabledImage)
            {
                m_pDisabledImage->setIsVisible(false);
            }
        }
        else
        {
            if (m_pDisabledImage)
            {
                m_pDisabledImage->setIsVisible(true);
                m_pNormalImage->setIsVisible(false);
            }
            else
            {
                m_pNormalImage->setIsVisible(true);
            }
        }
    }

	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage)
	{
		return CCMenuItemImage::itemFromNormalImage(normalImage, selectedImage, NULL, NULL, NULL);
	}
	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		return CCMenuItemImage::itemFromNormalImage(normalImage, selectedImage, NULL, target, selector);
	}
	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCMenuItemImage *pRet = new CCMenuItemImage();
		if (pRet && pRet->initFromNormalImage(normalImage, selectedImage, disabledImage, target, selector))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage)
	{
		CCMenuItemImage *pRet = new CCMenuItemImage();
		if (pRet && pRet->initFromNormalImage(normalImage, selectedImage, disabledImage, NULL, NULL))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
	bool CCMenuItemImage::initFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MenuHandler selector)
	{
		CCNode *normalSprite = CCSprite::spriteWithFile(normalImage);
		CCNode *selectedSprite = NULL;
		CCNode *disabledSprite = NULL;

        if (selectedImage)
        {
            selectedSprite = CCSprite::spriteWithFile(selectedImage);
        }

		if(disabledImage)
		{
			disabledSprite = CCSprite::spriteWithFile(disabledImage);
		}
		return initFromNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
	}
	//
	// MenuItemToggle
	//
	void CCMenuItemToggle::setSubItems(CCMutableArray<CCMenuItem*>* var)
	{
		CC_SAFE_RETAIN(var);
		CC_SAFE_RELEASE(m_pSubItems);
		m_pSubItems = var;
	}
	CCMutableArray<CCMenuItem*> *CCMenuItemToggle::getSubItems()
	{
		return m_pSubItems;
	}
	CCMenuItemToggle * CCMenuItemToggle::itemWithTarget(SelectorProtocol* target, SEL_MenuHandler selector, CCMenuItem* item, ...)
	{
		va_list args;
		va_start(args, item);
		CCMenuItemToggle *pRet = new CCMenuItemToggle();
		pRet->initWithTarget(target, selector, item, args);
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	bool CCMenuItemToggle::initWithTarget(SelectorProtocol* target, SEL_MenuHandler selector, CCMenuItem* item, va_list args)
	{
		CCMenuItem::initWithTarget(target, selector);
		this->m_pSubItems = new CCMutableArray<CCMenuItem*>();
		int z = 0;
		CCMenuItem *i = item;
		while(i) 
		{
			z++;
			m_pSubItems->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
		m_uSelectedIndex = UINT_MAX;
		this->setSelectedIndex(0);
		return true;
	}

	CCMenuItemToggle* CCMenuItemToggle::itemWithItem(CCMenuItem *item)
	{
		CCMenuItemToggle *pRet = new CCMenuItemToggle();
		pRet->initWithItem(item);
		pRet->autorelease();
		return pRet;
	}

	bool CCMenuItemToggle::initWithItem(CCMenuItem *item)
	{
		CCMenuItem::initWithTarget(NULL, NULL);
		this->m_pSubItems = new CCMutableArray<CCMenuItem*>();
		m_pSubItems->addObject(item);
		m_uSelectedIndex = UINT_MAX;
		this->setSelectedIndex(0);
		return true;
	}

	void CCMenuItemToggle::addSubItem(CCMenuItem *item)
	{
		m_pSubItems->addObject(item);
	}

	CCMenuItemToggle::~CCMenuItemToggle()
	{
		CC_SAFE_RELEASE(m_pSubItems);
	}
	void CCMenuItemToggle::setSelectedIndex(unsigned int index)
	{
		if( index != m_uSelectedIndex )
		{
			m_uSelectedIndex = index;
			this->removeChildByTag(kCurrentItem, false);
			CCMenuItem *item = m_pSubItems->getObjectAtIndex(m_uSelectedIndex);
			this->addChild(item, 0, kCurrentItem);
			const CCSize& s = item->getContentSize();
			this->setContentSize(s);
			item->setPosition( ccp( s.width/2, s.height/2 ) );
		}
	}
	unsigned int CCMenuItemToggle::getSelectedIndex()
	{
		return m_uSelectedIndex;
	}
	void CCMenuItemToggle::selected()
	{
		CCMenuItem::selected();
		m_pSubItems->getObjectAtIndex(m_uSelectedIndex)->selected();
	}
	void CCMenuItemToggle::unselected()
	{
		CCMenuItem::unselected();
		m_pSubItems->getObjectAtIndex(m_uSelectedIndex)->unselected();
	}
	void CCMenuItemToggle::activate()
	{
		// update index
		if( m_bIsEnabled ) 
		{
			unsigned int newIndex = (m_uSelectedIndex + 1) % m_pSubItems->count();
			this->setSelectedIndex(newIndex);
		}
		CCMenuItem::activate();
	}
	void CCMenuItemToggle::setIsEnabled(bool enabled)
	{
		CCMenuItem::setIsEnabled(enabled);

		if(m_pSubItems && m_pSubItems->count() > 0)
		{
			CCMutableArray<CCMenuItem*>::CCMutableArrayIterator it;
			for( it = m_pSubItems->begin(); it != m_pSubItems->end(); ++it)
			{
				(*it)->setIsEnabled(enabled);
			}
		}
	}
	CCMenuItem * CCMenuItemToggle::selectedItem()
	{
		return m_pSubItems->getObjectAtIndex(m_uSelectedIndex);
	}
	//
	//CCMenuItemToggle - CCRGBAProtocol protocol
	//
	GLubyte CCMenuItemToggle::getOpacity()
	{
		return m_cOpacity;
	}
	void CCMenuItemToggle::setOpacity(GLubyte opacity)
	{
		m_cOpacity = opacity;
		if(m_pSubItems && m_pSubItems->count() > 0)
		{
			CCMutableArray<CCMenuItem*>::CCMutableArrayIterator it;
			for( it = m_pSubItems->begin(); it != m_pSubItems->end(); ++it)
			{
				dynamic_cast<CCRGBAProtocol*>(*it)->setOpacity(opacity);
			}
		}
	}
	const ccColor3B& CCMenuItemToggle::getColor()
	{
		return m_tColor;
	}
	void CCMenuItemToggle::setColor(const ccColor3B& color)
	{
		m_tColor = color;
		if(m_pSubItems && m_pSubItems->count() > 0)
		{
			CCMutableArray<CCMenuItem*>::CCMutableArrayIterator it;
			for( it = m_pSubItems->begin(); it != m_pSubItems->end(); ++it)
			{
				dynamic_cast<CCRGBAProtocol*>(*it)->setColor(color);
			}
		}
	}

} // namespace cocos2d
