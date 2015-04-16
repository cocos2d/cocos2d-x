#ifndef __ImagePicker__ImagePicker__
#define __ImagePicker__ImagePicker__

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class Texture2D;

class ImagePickerDelegate {
public:
    virtual void didFinishPickingWithResult(Texture2D* result) = 0;
    virtual ~ImagePickerDelegate() {};
};

class CC_DLL ImagePicker{
public:
    ImagePicker();
    static ImagePicker *getInstance();
    
    void pickImage(ImagePickerDelegate *delegate);
    void finishImage(Texture2D *image);
private:
    ImagePickerDelegate *_delegate;
};

NS_CC_END

#endif