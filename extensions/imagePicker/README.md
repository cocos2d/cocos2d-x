ImagePicker
===========

ImagePicker utility for cocos2d-x 3.5 

**Attention**
- Old version cocos2d-x may have some differences in API. If you encounter problems here, feel free to contact me :D
- iOS 8 may crash with default setting. Please check out this issue [iPhone 5S Error](https://github.com/qiankanglai/ImagePicker/issues/2) here. I haven't found an elegant way to fix this, and any pull request is welcomed!

This utility lets you load images from device gallery and load it to your application as a Texture2D. You may draw Sprite with this texture or use it in other ways.

The origin project is https://github.com/Losiowaty/ImagePicker, and I clear the whole project, in addition to:

- add support for iPhone (combined with iPad)
- add support for Win32/OSX
- put Android support together
- take advantage of ccx 3.x API

The image is loaded by platform API and deliveried to ccx in memory directly. No repeated IO is needed.

usage example screenshots: http://qiankanglai.me/project/2014/04/14/cocos2dx-ImagePicker/

Guide
=====
Installation
------------

1. iOS/Mac

Add the following sources into project:

- ImagePicker.h, ImagePicker.cpp
- ImagePickerImpl.h, ImagePickerImpl.mm
- ImagePickerIOS.h, ImagePickerIOS.mm

2. Android/Win32

- ImagePicker.h, ImagePicker.cpp
- ImagePickerImpl.h, ImagePickerImpl.cpp

Modify your `Cocos2dxActivity.java` file according to mine. You may just copy from line 50 to the bottom.

Usage
-----

Just call `ImagePicker::getInstance()->pickImage()` and pass in your delegate. If the image is picked successfully, your delegate will receive the corresponding Texture2D, or nullptr otherwise.
