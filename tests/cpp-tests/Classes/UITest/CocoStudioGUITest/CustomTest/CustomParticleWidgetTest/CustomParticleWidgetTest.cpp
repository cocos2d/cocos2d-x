#include "CustomParticleWidgetTest.h"
#include "../../CustomGUIScene.h"
#include "../../CustomWidget/CustomParticleWidget.h"
#include "../../CustomWidget/CustomParticleWidgetReader.h"
#include "editor-support/cocostudio/CCSGUIReader.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;


// CustomParticleWidgetLayer
bool CustomParticleWidgetLayer::init()
{
    if (Layer::init())
    {
        GUIReader* guiReader = GUIReader::getInstance();
        guiReader->registerTypeAndCallBack("CustomParticleWidget",
            &CustomParticleWidget::createInstance,
            CustomParticleWidgetReader::getInstance(),
            parseselector(CustomParticleWidgetReader::setProperties));

        CustomParticleWidget* custom = CustomParticleWidget::create();
        custom->setParticlePlist("Particles/BoilingFoam.plist");
        custom->setPosition(Vec2(VisibleRect::center()));
        addChild(custom, 10, -1);

        return true;
    }

    return false;
}

bool CustomParticleWidgetScene::init()
{
    if (TestCase::init())
    {
        addChild(CustomParticleWidgetLayer::create());

        return true;
    }
    
    return false;
}
