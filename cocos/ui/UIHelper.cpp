/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "ui/UIHelper.h"
#include "ui/UIWidget.h"
#include "ui/UILayoutComponent.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"

NS_CC_BEGIN

namespace ui {

static bool _activeLayout = true;

Widget* Helper::seekWidgetByTag(Widget* root, int tag)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getTag() == tag)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    ssize_t length = arrayRootChildren.size();
    for (ssize_t i=0;i<length;i++)
    {
        Widget* child = dynamic_cast<Widget*>(arrayRootChildren.at(i));
        if (child)
        {
            Widget* res = seekWidgetByTag(child,tag);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}

Widget* Helper::seekWidgetByName(Widget* root, const std::string& name)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getName() == name)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            Widget* res = seekWidgetByName(child,name);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}

/*temp action*/
Widget* Helper::seekActionWidgetByActionTag(Widget* root, int tag)
{
	if (!root)
	{
		return nullptr;
	}
	if (root->getActionTag() == tag)
	{
		return root;
	}
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
	{
		Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            Widget* res = seekActionWidgetByActionTag(child,tag);
            if (res != nullptr)
            {
                return res;
            }
        }
	}
	return nullptr;
}
    
std::string Helper::getSubStringOfUTF8String(const std::string& str, std::string::size_type start, std::string::size_type length)
{
    std::u32string utf32;
    if (!StringUtils::UTF8ToUTF32(str, utf32)) {
        CCLOGERROR("Can't convert string to UTF-32: %s", str.c_str());
        return "";
    }
    if (utf32.size() < start) {
        CCLOGERROR("'start' is out of range: %ld, %s", static_cast<long>(start), str.c_str());
        return "";
    }
    std::string result;
    if (!StringUtils::UTF32ToUTF8(utf32.substr(start, length), result)) {
        CCLOGERROR("Can't convert internal UTF-32 string to UTF-8: %s", str.c_str());
        return "";
    }
    return result;
}

void Helper::changeLayoutSystemActiveState(bool bActive)
{
    _activeLayout = bActive;
}
void Helper::doLayout(cocos2d::Node *rootNode)
{
    if(!_activeLayout)
    {
        return;
    }

    for(auto& node : rootNode->getChildren())
    {
        auto com = node->getComponent(__LAYOUT_COMPONENT_NAME);
        Node *parent = node->getParent();
        if (nullptr != com && nullptr != parent) {
            LayoutComponent* layoutComponent = (LayoutComponent*)com;

            layoutComponent->refreshLayout();
        }
    }
}
    
Rect Helper::restrictCapInsetRect(const cocos2d::Rect &capInsets, const Size& textureSize )
{
    float x = capInsets.origin.x;
    float y = capInsets.origin.y;
    float width = capInsets.size.width;
    float height = capInsets.size.height;
    
    if (textureSize.width < width)
    {
        x = textureSize.width / 2.0f;
        width = textureSize.width > 0 ? 1.0f : 0.0f;
    }
    if (textureSize.height < height)
    {
        y = textureSize.height / 2.0f;
        height = textureSize.height > 0 ? 1.0f : 0.0f;
    }
    return Rect(x, y, width, height);
}

Rect Helper::convertBoundingBoxToScreen(Node* node)
{
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
    auto frameSize = glView->getFrameSize();

    auto winSize = director->getWinSize();
    auto leftBottom = node->convertToWorldSpace(Point::ZERO);

    auto contentSize = node->getContentSize();
    auto rightTop = node->convertToWorldSpace(Point(contentSize.width, contentSize.height));

    auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
    auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
    auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
    auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
    
    return Rect(uiLeft, uiTop, uiWidth, uiHeight);
}
}

NS_CC_END
