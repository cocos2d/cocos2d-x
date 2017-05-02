#include "cocos2d.h"

#include "ImagePicker.h"
#include "ImagePickerImpl.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ImagePickerIOS.h"
static ImagePickerIOS *sharedPicker = [[[ImagePickerIOS alloc] init] retain];
#endif

using namespace cocos2d;

void ImagePickerImpl::openImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [sharedPicker takePicture];
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    @autoreleasepool {
        NSOpenPanel* openDlg = [NSOpenPanel openPanel];
        NSArray *fileTypesArray = fileTypesArray = [NSArray arrayWithObjects:@"png", @"jpeg", @"jpg", nil];
        [openDlg setCanChooseFiles:YES];
        [openDlg setAllowedFileTypes:fileTypesArray];
        [openDlg setAllowsMultipleSelection:FALSE];
        if ( [openDlg runModal] == NSOKButton )
        {
            NSArray *files = [openDlg URLs];
            
            if([files count] > 0)
            {
                NSString* path = [[files objectAtIndex:0] path];
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(std::string([path UTF8String]));
                ImagePicker::getInstance()->finishImage(texture);
                return;
            }
        }
        ImagePicker::getInstance()->finishImage(nullptr);
    }
#else
    // unknown platform?
    ImagePicker::getInstance()->finishImage(nullptr);
#endif
}

