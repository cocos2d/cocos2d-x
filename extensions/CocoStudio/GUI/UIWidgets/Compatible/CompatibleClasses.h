
#ifndef __COMPATIBLECLASSES_H__
#define __COMPATIBLECLASSES_H__

#include "cocos2d.h"
#include "../../BaseClasses/UIWidget.h"
#include "../UIButton.h"
#include "../UICheckBox.h"
#include "../UIImageView.h"
#include "../UILabel.h"
#include "../UILabelAtlas.h"
#include "../UILabelBMFont.h"
#include "../UILoadingBar.h"
#include "../UISlider.h"
#include "../UITextField.h"
#include "../../Layouts/UILayout.h"
#include "../ScrollWidget/UIListView.h"
#include "../ScrollWidget/UIPageView.h"
#include "../ScrollWidget/UIScrollView.h"

//class type define
NS_CC_BEGIN
//
namespace ui {
  
typedef cocos2d::ui::Layout UIPanel;
typedef cocos2d::ui::Layout UILayout;
typedef cocos2d::ui::Widget UIWidget;

typedef cocos2d::ui::LayoutParameter UILayoutParameter;
typedef cocos2d::ui::Margin UIMargin;

typedef cocos2d::ui::ListView UIListView;
typedef cocos2d::ui::PageView UIPageView;
typedef cocos2d::ui::ScrollView UIDragPanel;
typedef cocos2d::ui::ScrollView UIScrollView;
typedef cocos2d::ui::Button UIButton;
typedef cocos2d::ui::Button UITextButton;
typedef cocos2d::ui::CheckBox UICheckBox;
typedef cocos2d::ui::ImageView UIImageView;
typedef cocos2d::ui::Label UILabel;
typedef cocos2d::ui::LabelAtlas UILabelAtlas;
typedef cocos2d::ui::LabelBMFont UILabelBMFont;
typedef cocos2d::ui::LoadingBar UILoadingBar;
typedef cocos2d::ui::Slider UISlider;
typedef cocos2d::ui::TextField UITextField;
typedef cocos2d::ui::TouchGroup UILayer;

typedef cocos2d::ui::LinearGravity UILinearGravity;
typedef cocos2d::ui::RelativeAlign UIRelativeAlign;
typedef cocos2d::ui::LayoutParameter UILayoutParameter;
typedef cocos2d::ui::LinearLayoutParameter UILinearLayoutParameter;
typedef cocos2d::ui::RelativeLayoutParameter UIRelativeLayoutParameter;
}
NS_CC_END


#endif /* defined(__CompatibleClasses__) */
