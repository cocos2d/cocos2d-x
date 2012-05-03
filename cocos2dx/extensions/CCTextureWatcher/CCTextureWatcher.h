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

#ifndef __CCMEMLAYER_H__
#define __CCMEMLAYER_H__

#include "extensions/CCListView/CCListView.h"

namespace cocos2d { class CCDictionary; }
namespace cocos2d { class CCLabelTTF; }
namespace cocos2d { class CCMenu; }
namespace cocos2d { class CCLayerColor; }


NS_CC_EXT_BEGIN

class CC_DLL CCTextureWatcher :public CCObject, public CCListViewDelegate
{
private:
    CCTextureWatcher();
public:
    virtual ~CCTextureWatcher();

    static CCTextureWatcher* sharedTextureWatcher();
    static void purgeTextureWatcher();
    void setDisplayWatcher(bool bDisplayWatcher);    
    void fresh(void);
protected:
    void actionFresh(CCObject* object);
    void actionHide(CCObject* object);
    void hide(void);
    void dovisit(void);
    static void visit(void* pSender);
protected:
    virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data);
private:
    bool m_bDisplayWatcher;
    bool m_bFresh;
    bool m_bHide;
    CCDictionary *m_pTextures;
    char *m_pszString;
    int m_nCurrnetPage;
    int m_nTotalPage;
    CCLabelTTF *m_labelHide;
    CCLabelTTF *m_labelPage;
    CCMenu *m_menuHide;
    CCLayerColor *m_pLayer;
    CCListView *m_pList;    
};

NS_CC_EXT_END

#endif
