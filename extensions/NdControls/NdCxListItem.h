#ifndef __NDCX_LIST_ITEM_H_
#define __NDCX_LIST_ITEM_H_

#include "ControlDefine.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace NdCxControl {

#define NdCxListItemChild CCNode

class NdCxListItem : public CCLayerColor
{
    friend class NdCxList;
protected:
    NdCxListItem(void);
    virtual ~NdCxListItem(void);

public:
    static NdCxListItem *itemWithColor(const ccColor3B &color);

    CCRect rect(void);
    void selected(void);
    void unselected(void);
    void setItemColor(const ccColor3B &color);
    void setMargin(CCSize margin);
    CCSize getMargin(void);

public:
    void addChild(NdCxListItemChild *child, const LayoutParam &layout);
    void addChild(NdCxListItemChild *child, const LayoutParam &layout, int tag);
    NdCxListItemChild *getChildByTag(int tag);
    void setDrawTopLine(bool value) { draw_top_line_ = value; }
    void setDrawBottomLine(bool value) { draw_bottom_line_ = value; }
    
protected:
    bool initWithWidthHeight(GLfloat width, GLfloat height);
    void requestLayout(void);
    void setLineColor(const ccColor3B &color);
    void setSelectedColor(const ccColor3B &start_color, const ccColor3B &end_color);
    void updateColor(void);

    virtual void draw(void);
    
private:
    bool selected_;
    ccColor3B line_color_;
    ccColor3B sel_item_start_color_;
    ccColor3B sel_item_end_color_;
    bool draw_top_line_;
    bool draw_bottom_line_;
    std::map<CCNode *, LayoutParam> layout_info_;
    float horizontal_margin_;
    float vertical_margin_;
};

}

#endif