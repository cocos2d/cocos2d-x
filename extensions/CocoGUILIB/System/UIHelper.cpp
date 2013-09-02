/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "UIHelper.h"
#include "../../CocostudioReader/DictionaryHelper.h"
#include "cocos2d.h"
#include "CCSReader.h"


NS_CC_EXT_BEGIN
    
static UIHelper* helperInstance = NULL;

UIHelper* UIHelper::instance()
{
    if (!helperInstance)
    {
        helperInstance = new UIHelper();
    }
    return helperInstance;
}

void UIHelper::purgeUIHelper()
{
	CC_SAFE_DELETE(helperInstance);
}

UIHelper::UIHelper():
m_textureFiles(NULL)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    m_fFileDesignWidth = winSize.width;
    m_fFileDesignHeight = winSize.height;
    init();
}

UIHelper::~UIHelper()
{
    cocos2d::extension::CCSReader::purgeCCSReader();
}

void UIHelper::init()
{
    m_textureFiles = CCArray::create();
    m_textureFiles->retain();
}

UIWidget* UIHelper::createWidgetFromJsonFile(const char *fileName)
{
    return CCSReader::shareReader()->widgetFromJsonFile(fileName);
}

void UIHelper::addSpriteFrame(const char *fileName)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    ccArray* arrayTextures = m_textureFiles->data;
    int length = arrayTextures->num;
    for (int i=0;i<length;i++)
    {
        CCString* file = (CCString*)(arrayTextures->arr[i]);
        if (strcmp(file->m_sString.c_str(), fileName) == 0)
        {
            return;
        }
    }
    m_textureFiles->addObject(CCString::create(fileName));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(fileName);
}

void UIHelper::removeSpriteFrame(const char *fileName)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    ccArray* arrayTextures = m_textureFiles->data;
    int length = arrayTextures->num;
    for (int i=0;i<length;i++)
    {
        CCString* file = (CCString*)(arrayTextures->arr[i]);
        if (strcmp(file->m_sString.c_str(), fileName) == 0)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName(fileName);
            m_textureFiles->removeObject(file);
            return;
        }
    }
}

void UIHelper::removeAllSpriteFrame()
{
    ccArray* arrayTextures = m_textureFiles->data;
    int length = arrayTextures->num;
    for (int i=0;i<length;i++)
    {
        CCString* file = (CCString*)(arrayTextures->arr[i]);
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName(file->m_sString.c_str());
    }
    m_textureFiles->removeAllObjects();
}

UIWidget* UIHelper::seekWidgetByTag(UIWidget* root, int tag)
{
    if (!root)
    {
        return NULL;
    }
    if (root->getTag() == tag)
    {
        return root;
    }
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
    for (int i=0;i<length;i++)
    {
        UIWidget* child = (UIWidget*)(arrayRootChildren->arr[i]);
        UIWidget* res = seekWidgetByTag(child,tag);
        if (res != NULL)
        {
            return res;
        }
    }
    return NULL;
}

UIWidget* UIHelper::seekWidgetByName(UIWidget* root, const char *name)
{
    if (!root)
    {
        return NULL;
    }
    if (strcmp(root->getName(), name) == 0)
    {
        return root;
    }
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
    for (int i=0;i<length;i++)
    {
        UIWidget* child = (UIWidget*)(arrayRootChildren->arr[i]);
        UIWidget* res = seekWidgetByName(child,name);
        if (res != NULL)
        {
            return res;
        }
    }
    return NULL;
}

UIWidget* UIHelper::seekWidgetByRelativeName(UIWidget *root, const char *name)
{
    if (!root)
    {
        return NULL;
    }
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
    for (int i=0;i<length;i++)
    {
        UIWidget* child = (UIWidget*)(arrayRootChildren->arr[i]);
        RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter());
        if (layoutParameter && strcmp(layoutParameter->getRelativeName(), name) == 0)
        {
            return child;
        }
    }
    return NULL;
}

void UIHelper::setFileDesignWidth(float width)
{
    m_fFileDesignWidth = width;
}

float UIHelper::getFileDesignWidth()
{
    return m_fFileDesignWidth;
}

void UIHelper::setFileDesignHeight(float height)
{
    m_fFileDesignHeight = height;
}

float UIHelper::getFileDesignHeight()
{
    return m_fFileDesignHeight;
}

/*temp action*/
UIWidget* UIHelper::seekActionWidgetByActionTag(UIWidget* root, int tag)
{
	if (!root)
	{
		return NULL;
	}
	if (root->getActionTag() == tag)
	{
		return root;
	}
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
	for (int i=0;i<length;i++)
	{
		UIWidget* child = (UIWidget*)(arrayRootChildren->arr[i]);
		UIWidget* res = seekActionWidgetByActionTag(child,tag);
		if (res != NULL)
		{
			return res;
		}
	}
	return NULL;
}

NS_CC_EXT_END