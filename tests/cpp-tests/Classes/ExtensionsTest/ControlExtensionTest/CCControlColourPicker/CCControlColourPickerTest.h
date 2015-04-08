#include "../CCControlScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class ControlColourPickerTest : public ControlScene
{
public:
    ControlColourPickerTest();
    virtual ~ControlColourPickerTest();
    virtual bool init() override;
    /** Callback for the change value. */
    void colourValueChanged(Ref *sender, Control::EventType controlEvent);

    CC_SYNTHESIZE_RETAIN(Label*, _colorLabel, ColorLabel)

    CREATE_FUNC(ControlColourPickerTest)
};

