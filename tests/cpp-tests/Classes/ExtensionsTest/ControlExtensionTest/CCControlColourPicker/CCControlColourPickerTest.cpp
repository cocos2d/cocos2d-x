#include "CCControlColourPickerTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

ControlColourPickerTest::ControlColourPickerTest()
{

}

bool ControlColourPickerTest::init()
{
    if (ControlScene::init())
    {
        auto screenSize = Director::getInstance()->getWinSize();

        auto layer  = Node::create();
        layer->setPosition(screenSize.width / 2, screenSize.height / 2);
        addChild(layer, 1);

        double layer_width = 0;

        // Create the colour picker
        ControlColourPicker *colourPicker = ControlColourPicker::create();
        colourPicker->setColor(Color3B(37, 46, 252));
        colourPicker->setPosition(colourPicker->getContentSize().width / 2, 0);

        // Add it to the layer
        layer->addChild(colourPicker);

        // Add the target-action pair
        colourPicker->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlColourPickerTest::colourValueChanged), Control::EventType::VALUE_CHANGED);


        layer_width += colourPicker->getContentSize().width;

        // Add the black background for the text
        auto background = Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(Size(150, 50));
        background->setPosition(layer_width + background->getContentSize().width / 2.0f, 0);
        layer->addChild(background);

        layer_width += background->getContentSize().width;

        _colorLabel = Label::createWithTTF("#color", "fonts/Marker Felt.ttf", 30);
        _colorLabel->retain();

        _colorLabel->setPosition(background->getPosition());
        layer->addChild(_colorLabel);

        // Set the layer size
        layer->setContentSize(Size(layer_width, 0));
        layer->setAnchorPoint(Vec2 (0.5f, 0.5f));

        // Update the color text
        colourValueChanged(colourPicker, Control::EventType::VALUE_CHANGED);
        return true;
    }
    return false;

}

ControlColourPickerTest::~ControlColourPickerTest()
{
    CC_SAFE_RELEASE(_colorLabel);
}

void ControlColourPickerTest::colourValueChanged(Ref *sender, Control::EventType controlEvent)
{
    ControlColourPicker* pPicker = (ControlColourPicker*)sender;
    _colorLabel->setString(String::createWithFormat("#%02X%02X%02X",pPicker->getColor().r, pPicker->getColor().g, pPicker->getColor().b)->getCString());
}


