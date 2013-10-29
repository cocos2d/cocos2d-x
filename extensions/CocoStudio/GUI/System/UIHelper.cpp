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

#include "CocosGUI.h"

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
    cocos2d::extension::CCSGUIReader::purgeCCSGUIReader();
}

void UIHelper::init()
{
    m_textureFiles = CCArray::create();
    m_textureFiles->retain();
}

UIWidget* UIHelper::createWidgetFromJsonFile(const char *fileName)
{
    return CCSGUIReader::shareReader()->widgetFromJsonFile(fileName);
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
        RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
        if (layoutParameter && strcmp(layoutParameter->getRelativeName(), name) == 0)
        {
            return child;
        }
    }
    return NULL;
}

UIWidget* UIHelper::cloneWidget(UIWidget *widget)
{
    if (!widget)
    {
        return NULL;
    }
    UIWidget* clonedWidget = NULL;
    const char* classType = widget->getDescription();
    if (strcmp(classType, "Widget") == 0)
    {
        clonedWidget = UIWidget::create();
    }
    else if (strcmp(classType, "Button") == 0)
    {
        clonedWidget = UIButton::create();
    }
    else if (strcmp(classType, "CheckBox") == 0)
    {
        clonedWidget = UICheckBox::create();
    }
    else if (strcmp(classType, "ImageView") == 0)
    {
        clonedWidget = UIImageView::create();
    }
    else if (strcmp(classType, "Label") == 0)
    {
        clonedWidget = UILabel::create();
    }
    else if (strcmp(classType, "LabelAtlas") == 0)
    {
        clonedWidget = UILabelAtlas::create();
    }
    else if (strcmp(classType, "LabelBMFont") == 0)
    {
        clonedWidget = UILabelBMFont::create();
    }
    else if (strcmp(classType, "LoadingBar") == 0)
    {
        clonedWidget = UILoadingBar::create();
    }
    else if (strcmp(classType, "Slider") == 0)
    {
        clonedWidget = UISlider::create();
    }
    else if (strcmp(classType, "Layout") == 0)
    {
        clonedWidget = Layout::create();
    }
    else if (strcmp(classType, "ScrollView") == 0)
    {
        clonedWidget = UIScrollView::create();
    }
    else if (strcmp(classType, "PageView") == 0)
    {
        clonedWidget = UIPageView::create();
    }
    else if (strcmp(classType, "TextField") == 0)
    {
        clonedWidget = UITextField::create();
    }
    else if (strcmp(classType, "ListView") == 0)
    {
        clonedWidget = UIListView::create();
    }
    else if (strcmp(classType, "ListViewEx") == 0)
    {
        clonedWidget = UIListViewEx::create();
    }

    clonedWidget->copyProperties(widget);
    
    switch (clonedWidget->getWidgetType())
    {
        case WidgetTypeWidget:
        {
            ccArray* arrayWidgetChildren = widget->getChildren()->data;
            int length = arrayWidgetChildren->num;
            for (int i=0; i<length; i++)
            {
                UIWidget* child = (UIWidget*)(arrayWidgetChildren->arr[i]);
                clonedWidget->addChild(cloneWidget(child));
            }
            break;
        }
        case WidgetTypeContainer:
        {
            if (strcmp(classType, "Layout") == 0
                || strcmp(classType, "ScrollView") == 0)
            {
                Layout* layout = dynamic_cast<Layout*>(clonedWidget);
                ccArray* arrayWidgetChildren = widget->getChildren()->data;
                int length = arrayWidgetChildren->num;
                for (int i=0; i<length; i++)
                {
                    UIWidget* child = (UIWidget*)(arrayWidgetChildren->arr[i]);
                    layout->addChild(cloneWidget(child));
                }
                layout->doLayout();
            }
            else if (strcmp(classType, "PageView") == 0)
            {
                UIPageView* pageView = dynamic_cast<UIPageView*>(clonedWidget);
                ccArray* arrayPages = dynamic_cast<UIPageView*>(widget)->getPages()->data;
                int length = arrayPages->num;
                for (int i=0; i<length; i++)
                {
                    Layout* page = (Layout*)(arrayPages->arr[i]);
                    pageView->addPage(dynamic_cast<Layout*>(cloneWidget(page)));
                }
            }
            else if (strcmp(classType, "ListView") == 0)
            {
                UIListView* listView = dynamic_cast<UIListView*>(clonedWidget);
                ccArray* arrayChildren = dynamic_cast<UIListView*>(widget)->getChildren()->data;
                int length = arrayChildren->num;
                for (int i=0; i<length; i++)
                {
                    UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
                    listView->addChild(cloneWidget(child));
                }
            }
            else if (strcmp(classType, "ListViewEx") == 0)
            {
                UIListViewEx* listViewEx = dynamic_cast<UIListViewEx*>(clonedWidget);
                ccArray* arrayItems = dynamic_cast<UIListViewEx*>(widget)->getItems()->data;
                int length = arrayItems->num;
                for (int i=0; i<length; i++)
                {
                    UIWidget* item = (UIWidget*)(arrayItems->arr[i]);
                    listViewEx->pushBackCustomItem(cloneWidget(item));
                }
            }
            break;
        }
        default:
            break;
    }

    return clonedWidget;
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