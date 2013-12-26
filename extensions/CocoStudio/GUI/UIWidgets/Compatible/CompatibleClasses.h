
#ifndef __COMPATIBLECLASSES_H__
#define __COMPATIBLECLASSES_H__

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
namespace gui {
  
typedef cocos2d::gui::Layout UIPanel;
typedef cocos2d::gui::Layout UILayout;
typedef cocos2d::gui::Widget UIWidget;

typedef cocos2d::gui::LayoutParameter UILayoutParameter;
typedef cocos2d::gui::Margin UIMargin;

typedef cocos2d::gui::ListView UIListView;
typedef cocos2d::gui::PageView UIPageView;
typedef cocos2d::gui::ScrollView UIDragPanel;
typedef cocos2d::gui::ScrollView UIScrollView;
typedef cocos2d::gui::Button UIButton;
typedef cocos2d::gui::Button UITextButton;
typedef cocos2d::gui::CheckBox UICheckBox;
typedef cocos2d::gui::ImageView UIImageView;
typedef cocos2d::gui::Label UILabel;
typedef cocos2d::gui::LabelAtlas UILabelAtlas;
typedef cocos2d::gui::LabelBMFont UILabelBMFont;
typedef cocos2d::gui::LoadingBar UILoadingBar;
typedef cocos2d::gui::Slider UISlider;
typedef cocos2d::gui::TextField UITextField;
typedef cocos2d::gui::TouchGroup UILayer;

typedef cocos2d::gui::LinearGravity UILinearGravity;
typedef cocos2d::gui::RelativeAlign UIRelativeAlign;    
typedef cocos2d::gui::LayoutParameter UILayoutParameter;
typedef cocos2d::gui::LinearLayoutParameter UILinearLayoutParameter;
typedef cocos2d::gui::RelativeLayoutParameter UIRelativeLayoutParameter;
}
NS_CC_END


#endif /* defined(__CompatibleClasses__) */
