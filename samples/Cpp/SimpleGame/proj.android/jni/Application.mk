APP_STL := gnustl_static

# add -Wno-literal-suffix to avoid warning: warning: invalid suffix on literal; C++11 requires a space between literal and identifier [-Wliteral-suffix] 
# in NDK_ROOT/arch-arm/usr/include/sys/cdefs_elf.h:35:28: when using ndk-r9
APP_CPPFLAGS := -frtti -DCOCOS2D_DEBUG=1 -std=c++11 -Wno-literal-suffix -fsigned-char
