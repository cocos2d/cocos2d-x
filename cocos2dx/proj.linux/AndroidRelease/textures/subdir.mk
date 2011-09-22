################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTexture2D.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTextureAtlas.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTextureCache.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTexturePVR.cpp 

OBJS += \
./textures/CCTexture2D.o \
./textures/CCTextureAtlas.o \
./textures/CCTextureCache.o \
./textures/CCTexturePVR.o 

CPP_DEPS += \
./textures/CCTexture2D.d \
./textures/CCTextureAtlas.d \
./textures/CCTextureCache.d \
./textures/CCTexturePVR.d 


# Each subdirectory must supply rules for building sources it contributes
textures/CCTexture2D.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTexture2D.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

textures/CCTextureAtlas.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTextureAtlas.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

textures/CCTextureCache.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTextureCache.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

textures/CCTexturePVR.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/textures/CCTexturePVR.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


