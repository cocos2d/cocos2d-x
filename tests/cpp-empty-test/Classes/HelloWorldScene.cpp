#include "HelloWorldScene.h"

#include <string>

#include "AppMacros.h"
#include "reader/CreatorReader.h"
#include "reader/collider/ColliderManager.h"
#include "ui/UIVideoPlayer.h"
#include "ui/UIButton.h"

USING_NS_CC;

cocos2d::Scene* HelloWorld::g_currentScene = nullptr;;
creator::CreatorReader* HelloWorld::g_reader = nullptr;


Scene* HelloWorld::scene()
{
    auto scene = createScene("creator/scenes/Main.ccreator");
    HelloWorld::handleButtonsClick(scene);
    return scene;
}

////////////////////////////////////////////////////
// private functions
///////////////////////////////////////////////////

cocos2d::Scene* HelloWorld::createScene(const std::string& ccreatorPath)
{
    auto reader = creator::CreatorReader::createWithFilename(ccreatorPath);
    reader->setup();
    auto scene = reader->getSceneGraph();
    
    HelloWorld::g_reader = reader;
    HelloWorld::g_currentScene = scene;
    
    return scene;;
}

cocos2d::ui::Button* HelloWorld::createBackButton()
{
    auto director = Director::getInstance();
    const auto visibleSize = director->getVisibleSize();
    const auto visibleOrigin = director->getVisibleOrigin();
    
    auto backButton = ui::Button::create();
    backButton->setTitleText("back");
    backButton->setTitleFontSize(30);
    auto contentSize = backButton->getContentSize();
    backButton->setPosition(Vec2(visibleOrigin.x + visibleSize.width - contentSize.width/2,
                                 contentSize.height/2));
    
    backButton->addClickEventListener([](Ref*) {
        auto scene = createScene("creator/scenes/Main.ccreator");
        HelloWorld::handleButtonsClick(scene);
        Director::getInstance()->replaceScene(scene);
    });
    
    return backButton;
}

void HelloWorld::repalceScene(const std::string& ccreatorPath)
{
    auto scene = createScene(ccreatorPath);
    auto backButton = HelloWorld::createBackButton();
    scene->addChild(backButton);
    Director::getInstance()->replaceScene(scene);
}

void HelloWorld::handleButtonClick(cocos2d::Scene* scene, const std::string& buttonName, const std::string& ccreatorPath)
{
    auto button = utils::findChild<ui::Button*>(scene, buttonName);
    button->addClickEventListener([=](Ref*) {
        HelloWorld::repalceScene(ccreatorPath);
    });
}

void HelloWorld::handleColliderButtonClick(cocos2d::Scene* scene)
{
    auto button = utils::findChild<ui::Button*>(scene, "collider");
    button->addClickEventListener([](Ref*) {
        HelloWorld::repalceScene("creator/scenes/collider/collider.ccreator");
        
        // regisger call back for collision event
        auto colliderManager = HelloWorld::g_reader->getColliderManager();
        colliderManager->enableAABBDebugDraw(true);
        colliderManager->registerCollitionCallback([=](creator::Contract::CollisionType type,
                                                       creator::Collider* collider1,
                                                       creator::Collider* collider2) {
            if (type == creator::Contract::CollisionType::ENTER)
                colliderManager->enableDebugDraw(true);
            
            if (type == creator::Contract::CollisionType::EXIT)
                colliderManager->enableDebugDraw(false);
            
        }, "");
        
        auto boxCollider = utils::findChild(HelloWorld::g_currentScene, "boxcollider");
        auto polygonCollider = utils::findChild(HelloWorld::g_currentScene, "polygoncollider");
        
        auto action1 = RepeatForever::create(RotateBy::create(1, 5));
        boxCollider->runAction(action1);
        polygonCollider->runAction(action1->clone());
    });
}

void HelloWorld::handleVideoButtonClick(cocos2d::Scene* scene)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto button = utils::findChild<ui::Button*>(scene, "video");
    button->addClickEventListener([=](Ref*) {
        HelloWorld::repalceScene("creator/scenes/video/VideoPlayer.ccreator");

        auto videoPlayer = utils::findChild<experimental::ui::VideoPlayer*>(HelloWorld::g_currentScene, "videoplayer");
        videoPlayer->play();
    });
#endif
}

void HelloWorld::handleAnimationButtonClick(cocos2d::Scene* scene)
{
    auto button = utils::findChild<ui::Button*>(scene, "animation");
    button->addClickEventListener([=](Ref*) {
        HelloWorld::repalceScene("creator/scenes/animation/CreatorAnim.ccreator");
        
        auto grossini_dance_08_2 = utils::findChild<cocos2d::Sprite*>(HelloWorld::g_currentScene, "grossini_dance_08_2");
        auto animationManager = HelloWorld::g_reader->getAnimationManager();
        grossini_dance_08_2->runAction(Sequence::create(DelayTime::create(3),
                                                        CallFunc::create([=]() {
            animationManager->pauseAnimationClip(grossini_dance_08_2, "Animation2");
                                                        }),
                                                        DelayTime::create(1),
                                                        CallFunc::create([=]() {
            animationManager->resumeAnimationClip(grossini_dance_08_2, "Animation2");
                                                        }),
                                                        nullptr));
    });
}

void HelloWorld::handleButtonsClick(cocos2d::Scene* scene)
{
    HelloWorld::handleButtonClick(scene, "label", "creator/scenes/label/CreatorLabels.ccreator");
    HelloWorld::handleButtonClick(scene, "mask", "creator/scenes/mask/Mask.ccreator");
    HelloWorld::handleButtonClick(scene, "pageview", "creator/scenes/pageview/pageview.ccreator");
    HelloWorld::handleButtonClick(scene, "prefab", "creator/scenes/prefab/prefab-test.ccreator");
    HelloWorld::handleButtonClick(scene, "richtext", "creator/scenes/richtext/CreatorRichtext.ccreator");
    HelloWorld::handleButtonClick(scene, "slider", "creator/scenes/slider/slider.ccreator");
    HelloWorld::handleButtonClick(scene, "sprites", "creator/scenes/sprites/CreatorSprites.ccreator");
    HelloWorld::handleButtonClick(scene, "tilemap", "creator/scenes/tilemap/CreatorTilemap.ccreator");
    HelloWorld::handleButtonClick(scene, "toggle", "creator/scenes/toggle/toggle.ccreator");
    HelloWorld::handleButtonClick(scene, "toggle_group", "creator/scenes/toggle_group/toggle_group.ccreator");
    HelloWorld::handleButtonClick(scene, "ui", "creator/scenes/ui/CreatorUI.ccreator");
    
    HelloWorld::handleAnimationButtonClick(scene);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HelloWorld::handleButtonClick(scene, "webview", "creator/scenes/webview/WebView.ccreator");
#endif
    HelloWorld::handleColliderButtonClick(scene);
    HelloWorld::handleVideoButtonClick(scene);
    
}
