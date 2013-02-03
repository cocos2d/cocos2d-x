pushd ../../

echo "generating libcocos2dx"
mkdir -p template/xcode4/lib_cocos2dx.xctemplate
python ./tools/xcode4_template_generator/template_generator.py --directory cocos2dx --identifier libcocos2dx --prefix libs --exclude "android win32 blackberry linux marmalade CCImage.cpp CCThread.cpp proj.ios CCImageCommon_cpp.h Android.mk mac" > ./template/xcode4/lib_cocos2dx.xctemplate/TemplateInfo.plist

echo "generating libcocosdenshion"
mkdir -p template/xcode4/lib_cocosdenshion.xctemplate
python ./tools/xcode4_template_generator/template_generator.py --directory CocosDenshion --identifier libcocosdenshion --prefix libs --exclude "android win32 blackberry linux marmalade proj.android proj.win32 proj.blackberry proj.linux proj.marmalade third_party Android.mk mac" > ./template/xcode4/lib_cocosdenshion.xctemplate/TemplateInfo.plist

echo "generating libbox2d"
mkdir -p template/xcode4/lib_box2d.xctemplate
pushd external
python ../tools/xcode4_template_generator/template_generator.py --directory Box2D --identifier libbox2d --prefix libs --exclude "proj.android proj.win32 proj.blackberry proj.linux proj.marmalade Android.mk" > ../template/xcode4/lib_box2d.xctemplate/TemplateInfo.plist
popd

echo "generating libchipmunk"
mkdir -p template/xcode4/lib_chipmunk.xctemplate
pushd external
python ../tools/xcode4_template_generator/template_generator.py --directory chipmunk --identifier libchipmunk --prefix libs --exclude "proj.android proj.win32 proj.blackberry proj.linux proj.marmalade Android.mk CMakeFiles Makefile" > ../template/xcode4/lib_chipmunk.xctemplate/TemplateInfo.plist
popd

echo "generating liblua"
mkdir -p template/xcode4/lib_lua.xctemplate
pushd scripting
python ../tools/xcode4_template_generator/template_generator.py --directory lua --identifier liblua --prefix libs --append ../tools/xcode4_template_generator/template_lua_patch.txt --exclude "proj.android proj.win32 proj.blackberry proj.linux proj.marmalade Makefile CMakeFiles" > ../template/xcode4/lib_lua.xctemplate/TemplateInfo.plist
popd


echo "generating libjs"
mkdir -p template/xcode4/lib_js.xctemplate
pushd scripting
python ../tools/xcode4_template_generator/template_generator.py --directory javascript/bindings --identifier libjs --prefix libs --append ../tools/xcode4_template_generator/template_js_patch.txt --exclude "Android.mk helper.js sample.js proj.win32"  > ../template/xcode4/lib_js.xctemplate/TemplateInfo.plist
popd

echo "generating libspidermonkey"
mkdir -p template/xcode4/lib_spidermonkey.xctemplate
pushd scripting
python ../tools/xcode4_template_generator/template_generator.py --directory javascript/spidermonkey-ios --identifier libspidermonkey --exclude "bin host" --prefix libs  > ../template/xcode4/lib_spidermonkey.xctemplate/TemplateInfo.plist
popd


echo "generating libextensions"
python ./tools/xcode4_template_generator/template_generator.py --directory extensions --identifier libextensions --prefix libs --exclude "proj.win32 proj.blackberry proj.linux Android.mk CCEditBoxImplAndroid.cpp CCEditBoxImplAndroid.h" > ./template/xcode4/lib_extensions.xctemplate/TemplateInfo.plist

echo "done"

popd
