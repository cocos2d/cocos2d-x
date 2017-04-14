#include "WindowTest.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
USING_NS_CC;

WindowTests::WindowTests() {
    ADD_TEST_CASE(WindowTestWindowed1);
    ADD_TEST_CASE(WindowTestWindowed2);
    ADD_TEST_CASE(WindowTestFullscreen1);
    ADD_TEST_CASE(WindowTestFullscreen2);
}

std::string WindowTest::title() const {
    return "Window Test";
}

void WindowTestWindowed1::onEnter() {
    WindowTest::onEnter();
    GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
    view->setWindowed(480, 320);
}

std::string WindowTestWindowed1::subtitle() const {
    return "Windowed 480x320";
}

void WindowTestWindowed2::onEnter() {
    WindowTest::onEnter();
    GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
    view->setWindowed(960, 640);
}

std::string WindowTestWindowed2::subtitle() const {
    return "Windowed 960x640";
}

void WindowTestFullscreen1::onEnter() {
    WindowTest::onEnter();
    GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
    view->setFullscreen();
}

std::string WindowTestFullscreen1::subtitle() const {
    return "Fullscreen";
}

void WindowTestFullscreen2::onEnter() {
    WindowTest::onEnter();
    GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
    view->setFullscreen(1);
}

std::string WindowTestFullscreen2::subtitle() const {
    return "Fullscreen Monitor 2 (if present)";
}

#endif
