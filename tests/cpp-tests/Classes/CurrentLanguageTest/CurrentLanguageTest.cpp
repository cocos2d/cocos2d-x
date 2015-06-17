#include "CurrentLanguageTest.h"

USING_NS_CC;

CurrentLanguageTests::CurrentLanguageTests()
{
    ADD_TEST_CASE(CurrentLanguageTest);
}

CurrentLanguageTest::CurrentLanguageTest()
{
    auto label = Label::createWithTTF("Current language Test", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition(VisibleRect::center().x, VisibleRect::top().y-50);

    auto labelLanguage = Label::createWithTTF("", "fonts/arial.ttf", 20);
    labelLanguage->setPosition(VisibleRect::center());
    
    auto labelLanguageCode = Label::createWithTTF("", "fonts/arial.ttf", 20);
    labelLanguageCode->setPosition(VisibleRect::center().x, VisibleRect::center().y-50);
    
    const char* currentLanguageCode = Application::getInstance()->getCurrentLanguageCode();
    
    labelLanguageCode->setString(currentLanguageCode);

    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    switch (currentLanguageType)
    {
    case LanguageType::ENGLISH:
        labelLanguage->setString("current language is English");
        break;
    case LanguageType::CHINESE:
        labelLanguage->setString("current language is Chinese");
        break;
    case LanguageType::FRENCH:
        labelLanguage->setString("current language is French");
        break;
    case LanguageType::GERMAN:
        labelLanguage->setString("current language is German");
        break;
    case LanguageType::ITALIAN:
        labelLanguage->setString("current language is Italian");
        break;
    case LanguageType::RUSSIAN:
        labelLanguage->setString("current language is Russian");
        break;
    case LanguageType::SPANISH:
        labelLanguage->setString("current language is Spanish");
        break;
    case LanguageType::KOREAN:
        labelLanguage->setString("current language is Korean");
        break;
    case LanguageType::JAPANESE:
        labelLanguage->setString("current language is Japanese");
        break;
    case LanguageType::HUNGARIAN:
        labelLanguage->setString("current language is Hungarian");
        break;
    case LanguageType::PORTUGUESE:
        labelLanguage->setString("current language is Portuguese");
        break;
    case LanguageType::ARABIC:
        labelLanguage->setString("current language is Arabic");
        break;
    case LanguageType::NORWEGIAN:
        labelLanguage->setString("current language is Norwegian");
        break;
    case LanguageType::POLISH:
        labelLanguage->setString("current language is Polish");
        break;
    case LanguageType::DUTCH:
        labelLanguage->setString("current language is Polish");
        break;
    default:
        CCASSERT(false, "Invalid language type.");
        break;
    }

    addChild(labelLanguage);
    addChild(labelLanguageCode);
}

