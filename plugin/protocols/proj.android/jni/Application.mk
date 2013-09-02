# it is needed for ndk-r5
APP_PLATFORM := android-10
APP_STL := gnustl_static
APP_CPPFLAGS += -frtti
APP_MODULES := PluginProtocolStatic
APP_ABI :=armeabi armeabi-v7a
#APP_ABI :=x86
#APP_ABI :=mips mips-r2 mips-r2-sf armeabi
