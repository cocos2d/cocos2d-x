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

#ifndef __UIACTIONNODE_H__
#define __UIACTIONNODE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../BaseClasses/UIWidget.h"
#include "UIActionFrame.h"
#include "../../CCArmature/external_tool/Json/CSContentJsonDictionary.h"

NS_CC_EXT_BEGIN

class UIActionNode:public CCObject
{
protected:
	int currentIndex;
	CCAction* m_action;
	UIWidget* m_actionNode;
    //data
	CCArray* m_ActionFrameList;/*action frame*/
    CC_SYNTHESIZE(int, m_nActionTag, ActionTag);
public:
    UIActionNode();
    virtual ~UIActionNode();

	void SetActionNode(UIWidget* widget);

	void InsertFrame(int index, UIActionFrame* frame);
	void AddFrame(UIActionFrame* frame);
	void DeleteFrame(UIActionFrame* frame);
	void ClearAllFrame();

	void UpdateToFrameByIndex(int index);
	void UpdateToFrame(UIActionFrame* frame);

	void RunAction(float fUnitTime, bool bloop);
	void StopAction();
    void initWithDictionary(cs::CSJsonDictionary* dic,UIWidget* root);
    void releaseBindingWidget();
};

NS_CC_EXT_END

#endif
