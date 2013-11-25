
#ifndef __COMPATIBLECLASSES_H__
#define __COMPATIBLECLASSES_H__

#include "../UILabel.h"
#include "../../Layouts/UILayout.h"
#include "../UIButton.h"
#include "../ScrollWidget/UIScrollView.h"

NS_CC_EXT_BEGIN

//class type define
typedef UILayout Layout;
typedef UILayout UIPanel;
typedef UILabel UITextArea;
typedef UILayout UIContainerWidget;
typedef UIButton UITextButton;
typedef UIWidget UINodeContainer;
/**
*   @js NA
*   @lua NA
*/
class UIZoomButton : public UITextButton
{
public:
    static UIZoomButton* create()
    {
        UIZoomButton* widget = new UIZoomButton();
        if (widget && widget->init())
        {
            widget->autorelease();
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    };
protected:
    virtual bool init()
    {
        if (UITextButton::init())
        {
            setScale9Enabled(true);
            setPressedActionEnabled(true);
            return true;
        }
        return false;
    };
};

class UIDragPanel : public UIScrollView
{
public:
    static UIDragPanel* create()
    {
        UIDragPanel* widget = new UIDragPanel();
        if (widget && widget->init())
        {
            widget->autorelease();
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    };
protected:
    virtual bool init()
    {
        if (UIScrollView::init())
        {
            setDirection(SCROLLVIEW_DIR_BOTH);
            return true;
        }
        return false;
    };
};

//enmu type define
typedef LayoutBackGroundColorType PanelColorType;

NS_CC_EXT_END

#endif /* defined(__CompatibleClasses__) */
