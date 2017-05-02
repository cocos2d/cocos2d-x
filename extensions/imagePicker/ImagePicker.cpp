#include "ImagePicker.h"
#include "ImagePickerImpl.h"

ImagePicker*  sharedPicker = nullptr;

ImagePicker::ImagePicker(){
    _delegate = nullptr;
}

ImagePicker* ImagePicker::getInstance(){
    if(sharedPicker == nullptr){
        sharedPicker = new ImagePicker();
    }
    return sharedPicker;
}

void ImagePicker::pickImage(ImagePickerDelegate *delegate) {
    _delegate = delegate;
    
    ImagePickerImpl::openImage();
}

void ImagePicker::finishImage(cocos2d::Texture2D *image){
    if(_delegate != nullptr){
        _delegate->didFinishPickingWithResult(image);
    }
}