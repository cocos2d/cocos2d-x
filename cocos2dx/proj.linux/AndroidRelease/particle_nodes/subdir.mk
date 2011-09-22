################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/particle_nodes/CCParticleExamples.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/particle_nodes/CCParticleSystem.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/particle_nodes/CCParticleSystemQuad.cpp 

OBJS += \
./particle_nodes/CCParticleExamples.o \
./particle_nodes/CCParticleSystem.o \
./particle_nodes/CCParticleSystemQuad.o 

CPP_DEPS += \
./particle_nodes/CCParticleExamples.d \
./particle_nodes/CCParticleSystem.d \
./particle_nodes/CCParticleSystemQuad.d 


# Each subdirectory must supply rules for building sources it contributes
particle_nodes/CCParticleExamples.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/particle_nodes/CCParticleExamples.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

particle_nodes/CCParticleSystem.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/particle_nodes/CCParticleSystem.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

particle_nodes/CCParticleSystemQuad.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/particle_nodes/CCParticleSystemQuad.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


