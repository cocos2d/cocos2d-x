#include "ImagePickerTest.h"

using namespace cocos2d;

ImagePickerTests::ImagePickerTests()
{
    ADD_TEST_CASE(ImagePickerTest);
}

//------------------------------------------------------------------
//
// ImagePickerTests
//
//------------------------------------------------------------------
ImagePickerTest::ImagePickerTest()
{
    ImagePicker::getInstance()->pickImage(this);
}

void ImagePickerTest::didFinishPickingWithResult(cocos2d::Texture2D* result)
{
    if(result == nullptr)
        return;
    
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::createWithTexture(result);
    sprite->setPosition(s.width/2, s.height/2);
    addChild(sprite);
}