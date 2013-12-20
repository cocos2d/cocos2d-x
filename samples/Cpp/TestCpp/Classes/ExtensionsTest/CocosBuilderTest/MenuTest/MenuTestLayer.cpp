#include "MenuTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

MenuTestLayer::MenuTestLayer()
: mMenuItemStatusLabelBMFont(NULL)
{}

MenuTestLayer::~MenuTestLayer()
{
    CC_SAFE_RELEASE(mMenuItemStatusLabelBMFont);
}

SEL_MenuHandler MenuTestLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemAClicked", MenuTestLayer::onMenuItemAClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemBClicked", MenuTestLayer::onMenuItemBClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemCClicked", MenuTestLayer::onMenuItemCClicked);

    return NULL;
}

Control::Handler MenuTestLayer::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}

bool MenuTestLayer::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuItemStatusLabelBMFont", LabelBMFont *, this->mMenuItemStatusLabelBMFont);

    return false;
}

void MenuTestLayer::onMenuItemAClicked(cocos2d::Object *pSender) {
    this->mMenuItemStatusLabelBMFont->setString("Menu Item A clicked.");
}

void MenuTestLayer::onMenuItemBClicked(cocos2d::Object *pSender) {
    this->mMenuItemStatusLabelBMFont->setString("Menu Item B clicked.");
}

void MenuTestLayer::onMenuItemCClicked(cocos2d::Object *pSender) {
    this->mMenuItemStatusLabelBMFont->setString("Menu Item C clicked.");
}