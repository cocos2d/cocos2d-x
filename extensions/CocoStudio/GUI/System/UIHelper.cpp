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

NS_CC_BEGIN

namespace gui {

Widget* UIHelper::seekWidgetByTag(Widget* root, int tag)
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
        Widget* child = static_cast<Widget*>(arrayRootChildren->arr[i]);
        Widget* res = seekWidgetByTag(child,tag);
        if (res != NULL)
        {
            return res;
        }
    }
    return NULL;
}

Widget* UIHelper::seekWidgetByName(Widget* root, const char *name)
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
        Widget* child = static_cast<Widget*>(arrayRootChildren->arr[i]);
        Widget* res = seekWidgetByName(child,name);
        if (res != NULL)
        {
            return res;
        }
    }
    return NULL;
}

Widget* UIHelper::seekWidgetByRelativeName(Widget *root, const char *name)
{
    if (!root)
    {
        return NULL;
    }
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
    for (int i=0;i<length;i++)
    {
        Widget* child = static_cast<Widget*>(arrayRootChildren->arr[i]);
        RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
        if (layoutParameter && strcmp(layoutParameter->getRelativeName(), name) == 0)
        {
            return child;
        }
    }
    return NULL;
}

/*temp action*/
Widget* UIHelper::seekActionWidgetByActionTag(Widget* root, int tag)
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
		Widget* child = static_cast<Widget*>(arrayRootChildren->arr[i]);
		Widget* res = seekActionWidgetByActionTag(child,tag);
		if (res != NULL)
		{
			return res;
		}
	}
	return NULL;
}

}

NS_CC_END