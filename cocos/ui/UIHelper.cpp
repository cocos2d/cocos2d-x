/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

NS_CC_BEGIN

namespace ui {

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

Widget* Helper::seekWidgetByName(Widget* root, const char *name)
{
    if (!root)
    {
        return nullptr;
    }
    if (strcmp(root->getName(), name) == 0)
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

}

NS_CC_END
