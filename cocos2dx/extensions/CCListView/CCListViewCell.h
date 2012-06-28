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

#ifndef __CC_LIST_VIEW_CELL_H_
#define __CC_LIST_VIEW_CELL_H_

#include "CCControlDefine.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 */

class CCListView;
typedef enum
{
    CCListViewCellSeparatorStyleNone,
    CCListViewCellSeparatorStyleSingleLine,
}CCListViewCellSeparatorStyle;

class CC_DLL CCListViewCell : public CCLayerColor
{
    public:
        CCListViewCell(void);
        virtual ~CCListViewCell(void);

        static CCListViewCell *node(void);

        void selected(void);
        void unselected(void);

        inline CCListViewCellSeparatorStyle getSeparatorStyle(void) { return m_nSeparatorStyle; }
        inline void setSeparatorStyle(CCListViewCellSeparatorStyle style) { m_nSeparatorStyle = style; }

        inline ccColor4B getSelectionColor(void) { return m_selectionColor; }
        inline void setSelectionColor(ccColor4B color) { m_selectionColor = color; }

        inline ccColor3B getSeparatorLineColor(void) { return m_separatorLineColor; }
        inline void setSeparatorLineColor(ccColor3B color) { m_separatorLineColor = color; }

    public:
        virtual bool initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
        virtual void draw(void);
        virtual void setColor(ccColor3B color);
        virtual void setOpacity(GLubyte var);

    private:
        inline CCListView *getOwner(void) { return (CCListView*)(this->getParent()->getParent()); }

    private:
        CCListViewCellSeparatorStyle    m_nSeparatorStyle;
        bool            m_bIsSelected;
        ccColor4B        m_selectionColor;
        ccColor4B        m_normalColor;
        ccColor3B        m_separatorLineColor;
};

// end of GUI group
/// @}

NS_CC_EXT_END

#endif // __CC_LIST_VIEW_CELL_H_