#ifndef __IMAGEPICKER_TEST_H_
#define __IMAGEPICKER_TEST_H_

#include "cocos2d.h"
#include "extensions/ImagePicker/ImagePicker.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(ImagePickerTests);

class ImagePickerTest : public TestCase, public cocos2d::ImagePickerDelegate
{
public:
    ImagePickerTest();
    CREATE_FUNC(ImagePickerTest);
    
    virtual void didFinishPickingWithResult(cocos2d::Texture2D* result);
};

#endif
