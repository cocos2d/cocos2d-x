#import <QuartzCore/QuartzCore.h>

//#import "CCDirector.h"
//#import "CCEAGLView.h"

#import "ImagePicker.h"
#import "ImagePickerIOS.h"

@implementation ImagePickerIOS

-(void) takePicture
{
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    [imagePicker setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    [imagePicker setDelegate:self];
    imagePicker.wantsFullScreenLayout = YES;
    
    // CCEAGLView is a subclass of UIView
    UIView *view = (UIView *)cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView();
    [view addSubview:imagePicker.view];
}

-(void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
    
    cocos2d::Image *imf =new cocos2d::Image();
    imf->autorelease();
    
    @autoreleasepool
    {
        NSData *imgData = UIImagePNGRepresentation(image);
        NSUInteger len = [imgData length];
        
        Byte *byteData = (Byte*)malloc(len);
        memcpy(byteData, [imgData bytes], len);
    
        imf->initWithImageData(byteData, len);
        
        free(byteData);
    }
    
    cocos2d::Texture2D* pTexture = new cocos2d::Texture2D();
    pTexture->initWithImage(imf);
    pTexture->autorelease();

    ImagePicker::getInstance()->finishImage(pTexture);
    
    [picker.view removeFromSuperview];
    [picker release];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    ImagePicker::getInstance()->finishImage(nullptr);
    [picker.view removeFromSuperview];
    [picker release];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
