This library support for cocos2d-x 3.x and SpriteBuilder 1.1


You can pull from git hub: https://github.com/nguyenduong
or my home page: www.jacos2d-x.org


How to integrate to cocos2d-x:

I. Copy spritebuilder folder to cocos2d/cocos/editor-support

II. iOS: 
  1. Open cocos2d_libs project setting/ build target/cocos2dxiOS
  2. Choose Build Phases
  3. Expand Compile Sources
  4. Add all of cpp file under spritebuilder folder

III. Android:
  1. Open file proj.android/jni/Android.mk
  2. Add following lines:
     LOCAL_WHOLE_STATIC_LIBRARIES += spritebuilder_static
     LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
     $(call import-module,editor-support/spritebuilder)

IV. Thanks
  1. Beckheng Lam (beckheng@gmail.com)

Please let me know if you have any problem.

Good luck!

Thanks,

Nguyen Thai Duong

home: http://jacos2d-x.org
email: nguyen.duong@jacos2d-x.org
