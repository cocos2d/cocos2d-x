//
// When a pageview set to relative position & size, if it
//  has child widget set to relative position & size either,
//  when change layer size, relayout won't correctly effect
//  to the child.
// In this test, if button at the center of panel, bug is fixed!
//

#include "Bug-PageViewLayout.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;
using namespace ui;

bool BugPageViewLayer::init()
{
    if (BugsTestBase::init())
    {
        auto size = Director::getInstance()->getWinSize();

        FileUtils::getInstance()->addSearchPath("ccs-res/cocosui/CustomTest/CustomWidgetCallbackBindTest");
        auto rootNode = CSLoader::createNode("cocosui/CustomTest/CustomWidgetCallbackBindTest/PageViewBugScene.csb");
        auto child = rootNode->getChildByName("ProjectNode_1");
        child->setContentSize(Size(480, 320));
        Helper::doLayout(child);
        addChild(rootNode);

        auto label = Label::create();
        label->setString(std::string("If button is at the center of panel, the bug is fixed!"));
        label->setPosition(size.width / 2, size.height / 4);
        label->setTextColor(Color4B::ORANGE);
        this->addChild(label);

        return true;
    }

    return false;
}
