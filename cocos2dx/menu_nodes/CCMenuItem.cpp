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
#include <cstring>
#include "CCMenuItem.h"
#include "CGPointExtension.h"
#include "CCIntervalAction.h"
#include "CCSprite.h"
#include "CCLabelAtlas.h"
#include "CCLabel.h"

namespace cocos2d{

	static int _fontSize = kItemSize;
	static std::string _fontName = "Marker Felt";
	static bool _fontNameRelease = false;

	enum {
		kCurrentItem = 0xc0c05001,
	};

	enum {
		kZoomActionTag = 0xc0c05002,
	};
	//
	// CCMenuItem
	//
	CCMenuItem * CCMenuItem::itemWithTarget(SelectorProtocol *rec, SEL_MunuHandler selector)
	{
		CCMenuItem *pRet = new CCMenuItem();
		pRet->initWithTarget(rec, selector);
		pRet->autorelease();
		return pRet;
	}
	CCMenuItem * CCMenuItem::initWithTarget(SelectorProtocol *rec, SEL_MunuHandler selector)
	{
		m_tAnchorPoint = ccp(0.5f, 0.5f);
		m_pListener = rec;
		m_pfnSelector = selector;
		m_bIsEnabled = true;
		m_bIsSelected = false;
		return this;
	}
	void CCMenuItem::selected()
	{
		m_bIsSelected = true;
	}
	void CCMenuItem::unselected()
	{
		m_bIsSelected = false;
	}
	void CCMenuItem::activate()
	{
		if (m_bIsEnabled && m_pListener)
		{
			(m_pListener->*m_pfnSelector)(this);
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
	CGRect CCMenuItem::rect()
	{
		return CGRectMake( m_tPosition.x - m_tContentSize.width * m_tAnchorPoint.x, 
						m_tPosition.y - m_tContentSize.height * m_tAnchorPoint.y,
						m_tContentSize.width, m_tContentSize.height);
	}
	bool CCMenuItem::getIsSelected()
	{
		return m_bIsSelected;
	}
	//
	//CCMenuItemLabel
	//
	ccColor3B CCMenuItemLabel::getDisabledColor()
	{
		return m_tDisabledColor;
	}
	void CCMenuItemLabel::setDisabledColor(ccColor3B var)
	{
		m_tDisabledColor = var;
	}
	CCNode *CCMenuItemLabel::getLable()
	{
		return m_pLabel;
	}
	void CCMenuItemLabel::setLable(CCNode* var)
	{
		CCX_SAFE_RELEASE(m_pLabel);
		var->retain();
		m_pLabel = var;
		this->setContentSize(m_pLabel->getContentSize());
	}
	CCMenuItemLabel * CCMenuItemLabel::itemWithLabel(CCNode*label, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		CCMenuItemLabel *pRet = new CCMenuItemLabel();
		pRet->initWithLabel(label, target, selector);
		pRet->autorelease();
		return pRet;
	}
	CCMenuItemLabel * CCMenuItemLabel::initWithLabel(CCNode* label, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		__super::initWithTarget(target, selector);
		m_fOriginalScale = 1.0f;
		m_tColorBackup = ccWHITE;
		m_tDisabledColor = ccc3(126,126,126);
		this->setLable(label);
		return this;
	}
	CCMenuItemLabel::~CCMenuItemLabel()
	{
		CCX_SAFE_RELEASE(m_pLabel);
	}
	void CCMenuItemLabel::setString(const char * label)
	{
		dynamic_cast<CCLabelProtocol*>(m_pLabel)->setString(label);
		this->setContentSize(m_pLabel->getContentSize());
// 		[label_ setString:string];
// 		[self setContentSize: [label_ contentSize]];
	}
	void CCMenuItemLabel::activate()
	{
		if(m_bIsEnabled)
		{
			this->stopAllActions();
			this->setScale( m_fOriginalScale );
			__super::activate();
		}
	}
	void CCMenuItemLabel::selected()
	{
		// subclass to change the default action
		if(m_bIsEnabled)
		{
			__super::selected();
			this->stopActionByTag(kZoomActionTag);
			m_fOriginalScale = this->getScale();
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
			__super::unselected();
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
		__super::setIsEnabled(enabled);
	}
	void CCMenuItemLabel::draw()
	{
		m_pLabel->draw();
	}
	void CCMenuItemLabel::setOpacity(GLubyte opacity)
	{
		dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setOpacity(opacity);
	}
	GLubyte CCMenuItemLabel::getOpacity()
	{
		return dynamic_cast<CCRGBAProtocol*>(m_pLabel)->getOpacity();
	}
	void CCMenuItemLabel::setColor(ccColor3B color)
	{
		dynamic_cast<CCRGBAProtocol*>(m_pLabel)->setColor(color);
	}
	ccColor3B CCMenuItemLabel::getColor()
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

	CCMenuItemAtlasFont * CCMenuItemAtlasFont::itemFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		CCMenuItemAtlasFont *pRet = new CCMenuItemAtlasFont();
		pRet->initFromString(value, charMapFile, itemWidth, itemHeight, startCharMap, target, selector);
		pRet->autorelease();
		return pRet;
	}
	CCMenuItemAtlasFont * CCMenuItemAtlasFont::initFromString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		NSAssert( strlen(value) != 0, "value lenght must be greater than 0");
		CCLabelAtlas *label = new CCLabelAtlas();
		label->initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap);
		label->autorelease();
		if (__super::initWithLabel(label, target, selector))
		{
			// do something ?
		}
		return this;
	}
	//
	//CCMenuItemFont
	//
	void CCMenuItemFont::setFontSize(int s)
	{
		_fontSize = s;
	}
	int CCMenuItemFont::fontSize()
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
	CCMenuItemFont * CCMenuItemFont::itemFromString(const char *value, SelectorProtocol* target, SEL_MunuHandler selector)
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
	CCMenuItemFont * CCMenuItemFont::initFromString(const char *value, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		NSAssert( strlen(value) != 0, "Value lenght must be greater than 0");
		CCLabel *label = CCLabel::labelWithString(value, _fontName.c_str(), (float)_fontSize);
		if (__super::initWithLabel(label, target, selector))
		{
			// do something ?
		}
		return this;
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
		m_pNormalImage = var;
	}
	CCNode * CCMenuItemSprite::getSelectedImage()
	{
		return m_pSelectedImage;
	}
	void CCMenuItemSprite::setSelectedImage(CCNode* var)
	{
		m_pSelectedImage = var;
	}
	CCNode * CCMenuItemSprite::getDisabledImage()
	{
		return m_pDisabledImage;
	}
	void CCMenuItemSprite::setDisabledImage(CCNode* var)
	{
		m_pDisabledImage = var;
	}
	CCMenuItemSprite * CCMenuItemSprite::itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite)
	{
		return CCMenuItemSprite::itemFromNormalSprite(normalSprite, selectedSprite, NULL, NULL, NULL);
	}
	CCMenuItemSprite * CCMenuItemSprite::itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		return CCMenuItemSprite::itemFromNormalSprite(normalSprite, selectedSprite, NULL, target, selector);
	}
	CCMenuItemSprite * CCMenuItemSprite::itemFromNormalSprite(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, SelectorProtocol *target, SEL_MunuHandler selector)
	{
		CCMenuItemSprite *pRet = new CCMenuItemSprite();
		pRet->initFromNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector); 
		pRet->autorelease();
		return pRet;
	}
	CCMenuItemSprite * CCMenuItemSprite::initFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		__super::initWithTarget(target, selector); 
		this->m_pNormalImage = normalSprite;
		this->m_pSelectedImage = selectedSprite;
		this->m_pDisabledImage = disabledSprite;
		this->setContentSize(m_pNormalImage->getContentSize());
		return this;
	}
	CCMenuItemSprite::~CCMenuItemSprite()
	{
		m_pNormalImage->release();
		m_pSelectedImage->release();
		m_pDisabledImage->release();
	}
	void CCMenuItemSprite::draw()
	{
		if(m_bIsEnabled)
		{
			if( m_bIsSelected )
			{
				m_pSelectedImage->draw();
			}
			else
			{
				m_pNormalImage->draw();
			}
		} 
		else 
		{
			if(m_pDisabledImage != NULL)
			{
				m_pDisabledImage->draw();
			}
			// disabled image was not provided
			else
			{
				m_pNormalImage->draw();
			}
		}
	}
	//
	//CCMenuItemImage - CCRGBAProtocol protocol
	//
	void CCMenuItemImage::setOpacity(GLubyte opacity)
	{
		dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->setOpacity(opacity);
		dynamic_cast<CCRGBAProtocol*>(m_pSelectedImage)->setOpacity(opacity);
		if (m_pDisabledImage)
		{
			dynamic_cast<CCRGBAProtocol*>(m_pDisabledImage)->setOpacity(opacity);
		}
	}
	void CCMenuItemImage::setColor(ccColor3B color)
	{
		dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->setColor(color);
		dynamic_cast<CCRGBAProtocol*>(m_pSelectedImage)->setColor(color);
		if (m_pDisabledImage)
		{
			dynamic_cast<CCRGBAProtocol*>(m_pDisabledImage)->setColor(color);
		}
	}
	GLubyte CCMenuItemImage::getOpacity()
	{
		return dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->getOpacity();
	}
	ccColor3B CCMenuItemImage::getColor()
	{
		return dynamic_cast<CCRGBAProtocol*>(m_pNormalImage)->getColor();
	}
	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage)
	{
		return CCMenuItemImage::itemFromNormalImage(normalImage, selectedImage, NULL, NULL, NULL);
	}
	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		return CCMenuItemImage::itemFromNormalImage(normalImage, selectedImage, NULL, target, selector);
	}
	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		CCMenuItemImage *pRet = new CCMenuItemImage();
		pRet->initFromNormalImage(normalImage, selectedImage, disabledImage, target, selector);
		pRet->autorelease();
		return pRet;
	}
	CCMenuItemImage * CCMenuItemImage::itemFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage)
	{
		CCMenuItemImage *pRet = new CCMenuItemImage();
		pRet->initFromNormalImage(normalImage, selectedImage, disabledImage, NULL, NULL);
		pRet->autorelease();
		return pRet;
	}
	CCMenuItemImage * CCMenuItemImage::initFromNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, SelectorProtocol* target, SEL_MunuHandler selector)
	{
		CCNode *normalSprite = CCSprite::spriteWithFile(normalImage);
		CCNode *selectedSprite = CCSprite::spriteWithFile(selectedImage); 
		CCNode *disabledSprite = NULL;

		if(disabledImage)
			disabledSprite = CCSprite::spriteWithFile(disabledImage);
		return static_cast<CCMenuItemImage*>(initFromNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector));
	}
	//
	// MenuItemToggle
	//
	void CCMenuItemToggle::setSubItems(NSMutableArray<CCMenuItem*>* var)
	{
		m_pSubItems = var;
	}
	NSMutableArray<CCMenuItem*> *CCMenuItemToggle::getSubItems()
	{
		return m_pSubItems;
	}
	CCMenuItemToggle * CCMenuItemToggle::itemWithTarget(SelectorProtocol* target, SEL_MunuHandler selector, CCMenuItem* item, ...)
	{
		va_list args;
		va_start(args, item);
		CCMenuItemToggle *pRet = new CCMenuItemToggle();
		pRet->initWithTarget(target, selector, item, args);
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	CCMenuItemToggle * CCMenuItemToggle::initWithTarget(SelectorProtocol* target, SEL_MunuHandler selector, CCMenuItem* item, va_list args)
	{
		__super::initWithTarget(target, selector);
		this->m_pSubItems = new NSMutableArray<CCMenuItem*>();
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
		return this;
	}
	CCMenuItemToggle::~CCMenuItemToggle()
	{
		m_pSubItems->release();
	}
	void CCMenuItemToggle::setSelectedIndex(UINT32 index)
	{
		if( index != m_uSelectedIndex )
		{
			m_uSelectedIndex = index;
			this->removeChildByTag(kCurrentItem, false);
			CCMenuItem *item = m_pSubItems->getObjectAtIndex(m_uSelectedIndex);
			this->addChild(item, 0, kCurrentItem);
			CGSize s = item->getContentSize();
			this->setContentSize(s);
			item->setPosition( ccp( s.width/2, s.height/2 ) );
		}
	}
	UINT32 CCMenuItemToggle::getSelectedIndex()
	{
		return m_uSelectedIndex;
	}
	void CCMenuItemToggle::selected()
	{
		__super::selected();
		m_pSubItems->getObjectAtIndex(m_uSelectedIndex)->selected();
	}
	void CCMenuItemToggle::unselected()
	{
		__super::unselected();
		m_pSubItems->getObjectAtIndex(m_uSelectedIndex)->unselected();
	}
	void CCMenuItemToggle::activate()
	{
		// update index
		if( m_bIsEnabled ) 
		{
			UINT32 newIndex = (m_uSelectedIndex + 1) % m_pSubItems->count();
			this->setSelectedIndex(newIndex);
		}
		__super::activate();
	}
	void CCMenuItemToggle::setIsEnabled(bool enabled)
	{
		__super::setIsEnabled(enabled);

		if(m_pSubItems && m_pSubItems->count() > 0)
		{
			NSMutableArray<CCMenuItem*>::NSMutableArrayIterator it;
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
			NSMutableArray<CCMenuItem*>::NSMutableArrayIterator it;
			for( it = m_pSubItems->begin(); it != m_pSubItems->end(); ++it)
			{
				dynamic_cast<CCRGBAProtocol*>(*it)->setOpacity(opacity);
			}
		}
	}
	ccColor3B CCMenuItemToggle::getColor()
	{
		return m_tColor;
	}
	void CCMenuItemToggle::setColor(ccColor3B color)
	{
		m_tColor = color;
		if(m_pSubItems && m_pSubItems->count() > 0)
		{
			NSMutableArray<CCMenuItem*>::NSMutableArrayIterator it;
			for( it = m_pSubItems->begin(); it != m_pSubItems->end(); ++it)
			{
				dynamic_cast<CCRGBAProtocol*>(*it)->setColor(color);
			}
		}
	}

} // namespace cocos2d