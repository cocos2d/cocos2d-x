#ifndef __ImagePicker__ImagePicker__
#define __ImagePicker__ImagePicker__

#include "cocos2d.h"

class ImagePickerDelegate {
public:
    virtual void didFinishPickingWithResult(cocos2d::Texture2D* result) = 0;
};

class ImagePicker{
public:
    ImagePicker();
    static ImagePicker *getInstance();
    
    void pickImage(ImagePickerDelegate *delegate);
    void finishImage(cocos2d::Texture2D *image);
private:
    ImagePickerDelegate *_delegate;
};

#endif /* defined(__ImagePicker__ImagePicker__) */
