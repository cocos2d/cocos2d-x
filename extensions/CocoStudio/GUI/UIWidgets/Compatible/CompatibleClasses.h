
#ifndef __COMPATIBLECLASSES_H__
#define __COMPATIBLECLASSES_H__

#include "../UILabel.h"
#include "../../Layouts/Layout.h"
#include "../UIButton.h"

NS_CC_EXT_BEGIN

//class type define
typedef Layout UIPanel;
typedef UILabel UITextArea;
typedef Layout UIContainerWidget;
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

//enmu type define
typedef LayoutBackGroundColorType PanelColorType;

NS_CC_EXT_END

#endif /* defined(__CompatibleClasses__) */
