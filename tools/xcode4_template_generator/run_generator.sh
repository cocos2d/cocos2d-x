pushd ../../

echo "generating libcocos2dx"
mkdir -p template/xcode4/lib_cocos2dx.xctemplate
python ./tools/xcode4_template_generator/template_generator.py --directory cocos2dx --identifier libcocos2dx --prefix libs --exclude "android win32  third_party CCImage.cpp CCThread.cpp proj.ios CCFileUtilsCommon_cpp.h CCImageCommon_cpp.h CCFileUtils.cpp Android.mk" > ./template/xcode4/lib_cocos2dx.xctemplate/TemplateInfo.plist

echo "generating libcocosdenshion"
mkdir -p template/xcode4/lib_cocosdenshion.xctemplate
python ./tools/xcode4_template_generator/template_generator.py --directory CocosDenshion --identifier libcocosdenshion --prefix libs --exclude "android win32 third_party Android.mk" > ./template/xcode4/lib_cocosdenshion.xctemplate/TemplateInfo.plist

echo "generating libbox2d"
mkdir -p template/xcode4/lib_box2d.xctemplate
python ./tools/xcode4_template_generator/template_generator.py --directory Box2D --identifier libbox2d --prefix libs --exclude "android win32 Android.mk" > ./template/xcode4/lib_box2d.xctemplate/TemplateInfo.plist

echo "generating libchipmunk"
mkdir -p template/xcode4/lib_chipmunk.xctemplate
python ./tools/xcode4_template_generator/template_generator.py --directory chipmunk --identifier libchipmunk --prefix libs --exclude "android win32 Android.mk CMakeFiles Makefile" > ./template/xcode4/lib_chipmunk.xctemplate/TemplateInfo.plist

echo "generating liblua"
mkdir -p template/xcode4/lib_lua.xctemplate
python ./tools/xcode4_template_generator/template_generator.py --directory lua --identifier liblua --prefix libs --append ./tools/xcode4_template_generator/template_lua_patch.txt --exclude "android win32 Makefile CMakeFiles" > ./template/xcode4/lib_lua.xctemplate/TemplateInfo.plist

echo "done"

popd
