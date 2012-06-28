/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2012 NetGragon

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

#include "CCTextureWatcher.h"
#include "cocos2d.h"

using namespace std;
 
NS_CC_EXT_BEGIN

#define NUM_PER_PAGE    4

CCTextureWatcher::CCTextureWatcher()
{
    m_bHide = false;
    m_nCurrnetPage = 1;
    m_nTotalPage = 0;
    m_bFresh = true;
    m_pTextures = NULL;
    m_pszString = NULL;
    m_pLayer = CCLayerColor::create(ccc4(128, 128, 128, 128));
    m_pLayer->retain();

    // layer
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    size.height *= 0.6f;
    m_pLayer->setContentSize(size);

    // the menu of disabling touch event
    //*
    CCLabelTTF *label = CCLabelTTF::create(" ", size, kCCTextAlignmentLeft, "Arial", 12);
    CCMenuItemLabel *menuItem = CCMenuItemLabel::create(label);
    menuItem->setAnchorPoint(ccp(0, 0));
    menuItem->setPosition(ccp(0, 0));
        
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    m_pLayer->addChild(menu);
    //*/

    // list
    CCListView *list = CCListView::create(CCListViewModeHorizontal);
    list->setContentSize(size);
    list->setDelegate(this);
    list->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
    m_pLayer->addChild(list);
    m_pList = list;


    // 'Hide' button
    CCLabelTTF *labelHide = CCLabelTTF::create("Hide  ", "Arial", 24);
    labelHide->setColor(ccc3(255, 0, 0));
    CCMenuItemLabel *menuItem2 = CCMenuItemLabel::create(labelHide, this, menu_selector(CCTextureWatcher::actionHide));
    menuItem2->setAnchorPoint(ccp(0, 0));
    menuItem2->setPosition(ccp(0, 0));

    CCMenu *menu2 = CCMenu::create(menuItem2, NULL);
    menu2->setAnchorPoint(ccp(0, 0));
    menu2->setPosition(ccp(size.width - menuItem2->getContentSize().width, 0));

    m_labelHide = labelHide;
    m_menuHide = menu2;
    m_menuHide->retain();

    // 'Fresh' button
    CCLabelTTF *labelFresh = CCLabelTTF::create("Fresh", "Arial", 24);
    labelFresh->setColor(ccc3(255, 0, 0));
    CCMenuItemLabel *menuItem1 = CCMenuItemLabel::create(labelFresh, this, menu_selector(CCTextureWatcher::actionFresh));
    menuItem1->setAnchorPoint(ccp(0, 0));
    menuItem1->setPosition(ccp(0, 0));

    CCMenu *menu1 = CCMenu::create(menuItem1, NULL);
    menu1->setAnchorPoint(ccp(0, 0));
    menu1->setPosition(ccp(size.width - menuItem1->getContentSize().width - menuItem2->getContentSize().width * 1.5, 0));
    m_pLayer->addChild(menu1);
    
    // label page
    m_labelPage = CCLabelTTF::create(" ", CCSizeMake(size.width * 0.1, labelFresh->getContentSize().height), kCCTextAlignmentCenter, "Arial", 16);
    m_labelPage->setAnchorPoint(ccp(0.5, 0));
    m_labelPage->setPosition(ccp(size.width/2.0, 0));
    m_pLayer->addChild(m_labelPage, 0);
}
CCTextureWatcher::~CCTextureWatcher()
{
    if (m_menuHide) 
    {
        m_menuHide->removeFromParentAndCleanup(true);
        m_menuHide->release();
    }

    if (m_pLayer)
    {
        m_pLayer->removeFromParentAndCleanup(true);
    }
    
    if (m_pTextures) m_pTextures->release();
    if (m_pszString) delete []m_pszString;
}
void CCTextureWatcher::actionFresh(CCObject* object)
{
    CCTextureWatcher::sharedTextureWatcher()->fresh();
}
void CCTextureWatcher::actionHide(CCObject *object)
{
    CCTextureWatcher::sharedTextureWatcher()->hide();
}
void CCTextureWatcher::fresh()
{
    m_nCurrnetPage = 1;
    m_bFresh = true;
}
void CCTextureWatcher::hide()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        m_labelHide->setString("Show");
        m_pLayer->setPosition(ccp(0, -m_pLayer->getContentSize().height));
    }
    else
    {
        m_labelHide->setString("Hide");
        m_pLayer->setPosition(ccp(0, 0));
    }

}

void CCTextureWatcher::dovisit()
{
    if (m_bFresh)
    {
        if (m_pTextures)
        {
            m_pTextures->removeAllObjects();
            m_pTextures->release();
        }

        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        m_pTextures = CCTextureCache::sharedTextureCache()->snapshotTextures();
        m_nTotalPage = (m_pTextures->count() + NUM_PER_PAGE - 1) / NUM_PER_PAGE;
        if (m_pTextures->count() > 0)
        {
            m_bFresh = false;
            m_pList->reload();
        }
    }
    CCNode *pParent = m_pLayer->getParent();
    if (pParent)
    {
        if (pParent != CCDirector::sharedDirector()->getRunningScene())
        {
            pParent->removeChild(m_pLayer, true);
            CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayer, 9998);
            m_bFresh = true;
        }
    }
    else
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayer, 9998);
    }

    pParent = m_menuHide->getParent();
    if (pParent)
    {
        if (pParent != CCDirector::sharedDirector()->getRunningScene())
        {
            pParent->removeChild(m_menuHide, true);
            CCDirector::sharedDirector()->getRunningScene()->addChild(m_menuHide, 9999);
        }
    }
    else
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(m_menuHide, 9999);
    }
}
void CCTextureWatcher::visit(void* pSender)
{
    CCTextureWatcher *wartcher = (CCTextureWatcher*)pSender;
    wartcher->dovisit();
}

static CCTextureWatcher *g_sharedTextureWatcher = NULL;

CCTextureWatcher* CCTextureWatcher::sharedTextureWatcher()
{
    if (!g_sharedTextureWatcher)
    {
        g_sharedTextureWatcher = new CCTextureWatcher();
    }

    return g_sharedTextureWatcher;
}

void CCTextureWatcher::purgeTextureWatcher()
{
    if (g_sharedTextureWatcher != NULL)
    {
        CC_SAFE_RELEASE_NULL(g_sharedTextureWatcher);
    }
}

void CCTextureWatcher::setDisplayWatcher(bool bDisplayWatcher)
{
    m_bDisplayWatcher = bDisplayWatcher;
    if (m_bDisplayWatcher)
    {
        if (m_pszString == NULL)
        {
            m_pszString = new char[64];
        }
        CCDirector::sharedDirector()->setWatcherCallbackFun(this, &CCTextureWatcher::visit);
    }
    else 
    {
        CCDirector::sharedDirector()->setWatcherCallbackFun(NULL, NULL);
        purgeTextureWatcher();
    }
}

void CCTextureWatcher::CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data)
{
    data->nNumberOfRows = m_nTotalPage;
}

void CCTextureWatcher::CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data)
{
    m_nCurrnetPage = data->nRow + 1;
    CCListViewCell *cell = CCListViewCell::node();
    cell->setOpacity(0);
    cell->setContentSize(m_pList->getContentSize());
    cell->setSelectionColor(ccc4(0, 0, 0, 0));
    data->cell = cell;

    CCSize listItemSize = CCSize(m_pList->getContentSize().width / NUM_PER_PAGE, m_pList->getContentSize().height);

    CCSize size = CCSize(listItemSize.width * 0.9f, listItemSize.height * 0.6f);

    sprintf(m_pszString, "%d/%d", m_nCurrnetPage, m_nTotalPage);
    m_labelPage->setString(m_pszString);

    float offX = 0.0f, offY = 0.0f, offsetX = 0.0f, offsetY = 0.0f;
    CC_UNUSED_PARAM(offsetY);
    int nCount = 0;
    int nStart = (m_nCurrnetPage - 1) * NUM_PER_PAGE;
    int nEnd = nStart + NUM_PER_PAGE;

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(m_pTextures, pElement)
    {
        if (nCount >= nStart && nCount < nEnd)
        {
            string key = pElement->getStrKey();
            CCTexture2D* textrue = (CCTexture2D*)pElement->getObject();
            //textrue = m_pTextures->objectForKey(*it);
            if (textrue)
            {
                // reference count
                sprintf(m_pszString, "[%d]", textrue->retainCount() - 2);
                CCLabelTTF *labelCount = CCLabelTTF::create(m_pszString, "Arial", 16);
                if (textrue->retainCount() - 2 > 0)
                {
                    labelCount->setColor(ccc3(0, 255, 0));
                }
                else
                {
                    labelCount->setColor(ccc3(255, 0, 0));
                }
                offX = offsetX + listItemSize.width * 0.5f - labelCount->getContentSize().width * 0.5f;
                offY = (listItemSize.height - size.height) * 0.5f - labelCount->getContentSize().height;
                labelCount->setPosition(ccp(offX, offY));
                labelCount->setAnchorPoint(ccp(0, 0));
                cell->addChild(labelCount);

                // texture size
                sprintf(m_pszString, "%.0f*%.0f", textrue->getContentSize().width, textrue->getContentSize().height);
                CCLabelTTF *labelSize = CCLabelTTF::create(m_pszString, "Arial", 16);
                offX = offsetX + listItemSize.width * 0.5f;
                offY = (listItemSize.height - size.height) * 0.5f + size.height;
                labelSize->setPosition(ccp(offX, offY));
                labelSize->setAnchorPoint(ccp(0.5f, 0));
                cell->addChild(labelSize);

                // texture name
                int len = key.length();
                int pos = 0;

                pos = key.rfind('\\') + 1;
                int pos2 = key.rfind('/') + 1;
                pos = pos > pos2 ? pos : pos2;

                string name = key.substr(pos, len - pos);
                sprintf(m_pszString, "%s", name.c_str());
                CCSize dimensions = CCSizeMake(listItemSize.width * 0.9f, labelSize->getContentSize().height);
                CCLabelTTF *labelName = CCLabelTTF::create(m_pszString, dimensions, kCCTextAlignmentCenter, "Arial", 16);
                offX = offsetX + listItemSize.width * 0.5f;
                offY = offY + labelName->getContentSize().height;
                labelName->setPosition(ccp(offX, offY));
                labelName->setAnchorPoint(ccp(0.5f, 0));
                cell->addChild(labelName);

                CCSprite *sprite = CCSprite::create(textrue);
                sprite->setAnchorPoint(ccp(0, 0));

                CCSize spriteSize = sprite->getContentSize();
                float scale;
                if (spriteSize.width < size.width && spriteSize.height < size.height)
                {
                    scale = 1;
                }
                else if (spriteSize.width * size.height >= spriteSize.height * size.width)
                {
                    scale = size.width / spriteSize.width;
                }
                else
                {
                    scale = size.height / spriteSize.height;
                }
                sprite->setScale(scale);
                spriteSize.width *= scale;
                spriteSize.height *= scale;
                offX = offsetX + (listItemSize.width - spriteSize.width) * 0.5f;
                offY = (listItemSize.height - spriteSize.height) * 0.5f;
                sprite->setPosition(ccp(offX, offY));
                cell->addChild(sprite);
                offsetX += listItemSize.width;
            }
        }
        ++nCount;
    }
}

void CCTextureWatcher::CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data)
{

}

void CCTextureWatcher::CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data)
{

}

NS_CC_EXT_END
