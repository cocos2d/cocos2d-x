[
{
    'mkfile' : 'cocos/2d/Android.mk',
    'pathes' : ("cocos/2d/","cocos/base","cocos/math","cocos/physics","external/tinyxml2","external/unzip"),
    'exclude' : ("cocos/2d/platform/android", "cocos/2d/platform/emscripten", "cocos/2d/platform/ios", "cocos/2d/platform/apple", "cocos/2d/platform/linux", "cocos/2d/platform/mac", "cocos/2d/platform/win32")
},
{
    'mkfile' : 'samples/Cpp/TestCpp/Android.mk',
    'pathes' : ("samples/Cpp/TestCpp/Classes",),
},
{
    'mkfile' : 'extensions/Android.mk',
    'pathes' : ("extensions/",),
    'exclude' : ("extensions/proj.win32", "extensions/proj.emscripten", "extensions/proj.ios", "extensions/proj.linux", "extensions/proj.mac", "extensions/proj.nacl", "extensions/proj.qt5", "extensions/proj.tizen")
},
{
    'mkfile' : 'external/Box2D/Android.mk',
    'pathes' : ("external/Box2D/",),
},
{
    'mkfile' : 'external/chipmunk/Android.mk',
    'pathes' : ("external/chipmunk/",),
}
]