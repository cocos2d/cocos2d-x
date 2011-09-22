################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/android/CCAccelerometer_android.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/android/CCApplication_android.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/android/CCEGLView_android.cpp 

OBJS += \
./platform/android/CCAccelerometer_android.o \
./platform/android/CCApplication_android.o \
./platform/android/CCEGLView_android.o 

CPP_DEPS += \
./platform/android/CCAccelerometer_android.d \
./platform/android/CCApplication_android.d \
./platform/android/CCEGLView_android.d 


# Each subdirectory must supply rules for building sources it contributes
platform/android/CCAccelerometer_android.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/android/CCAccelerometer_android.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/android/CCApplication_android.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/android/CCApplication_android.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/android/CCEGLView_android.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/android/CCEGLView_android.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


