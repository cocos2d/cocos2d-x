echo "generating libcocos2dx"
mkdir -p template/xcode4/lib_cocos2dx.xctemplate
python ./template/xcode4/template_generator.py --directory cocos2dx --identifier libcocos2dx --prefix libs --exclude "android win32 airplay wophone third_party CCImage.cpp Android.mk" > ./template/xcode4/lib_cocos2dx.xctemplate/TemplateInfo.plist

echo "generating libcocosdenshion"
mkdir -p template/xcode4/lib_cocosdenshion.xctemplate
python ./template/xcode4/template_generator.py --directory CocosDenshion --identifier libcocosdenshion --prefix libs --exclude "android win32 airplay wophone Android.mk" > ./template/xcode4/lib_cocosdenshion.xctemplate/TemplateInfo.plist

echo "generating libbox2d"
mkdir -p template/xcode4/lib_box2d.xctemplate
python ./template/xcode4/template_generator.py --directory Box2D --identifier libbox2d --prefix libs --exclude "android win32 airplay wophone Android.mk" > ./template/xcode4/lib_box2d.xctemplate/TemplateInfo.plist

echo "generating libchipmunk"
mkdir -p template/xcode4/lib_chipmunk.xctemplate
python ./template/xcode4/template_generator.py --directory chipmunk --identifier libchipmunk --prefix libs --exclude "android win32 airplay wophone Android.mk" > ./template/xcode4/lib_chipmunk.xctemplate/TemplateInfo.plist

echo "done"