
本例是集成AnySDK v1.1.1(2014-06-23)

详细文档参见 <http://docs.anysdk.com/%E9%A6%96%E9%A1%B5>


** 对javaactivity.cpp的修改，这个文件在样例工程外，需要手动添加 **


#### 修改javaactivity.cpp ####

编译前请在

$(COCOS2DX_ROOT)/cocos/platform/javaactivity.cpp中的JNI_OnLoad函数中加入

anysdk::framework::PluginJniHelper::setJavaVM(vm);

对应头文件
include "PluginJniHelper.h"

~~~

#include "PluginJniHelper.h"        //for anysdk

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);
    anysdk::framework::PluginJniHelper::setJavaVM(vm); // add for plugin, for anysdk

    return JNI_VERSION_1_4;
}

~~~

参见 $(COCOS2DX_ROOT)/qucik/lib/sdk/anysdk/src/javaactivity.cpp
