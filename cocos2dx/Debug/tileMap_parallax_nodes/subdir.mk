################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tileMap_parallax_nodes/CCParallaxNode.cpp \
../tileMap_parallax_nodes/CCTMXLayer.cpp \
../tileMap_parallax_nodes/CCTMXObjectGroup.cpp \
../tileMap_parallax_nodes/CCTMXTiledMap.cpp \
../tileMap_parallax_nodes/CCTMXXMLParser.cpp \
../tileMap_parallax_nodes/CCTileMapAtlas.cpp 

OBJS += \
./tileMap_parallax_nodes/CCParallaxNode.o \
./tileMap_parallax_nodes/CCTMXLayer.o \
./tileMap_parallax_nodes/CCTMXObjectGroup.o \
./tileMap_parallax_nodes/CCTMXTiledMap.o \
./tileMap_parallax_nodes/CCTMXXMLParser.o \
./tileMap_parallax_nodes/CCTileMapAtlas.o 

CPP_DEPS += \
./tileMap_parallax_nodes/CCParallaxNode.d \
./tileMap_parallax_nodes/CCTMXLayer.d \
./tileMap_parallax_nodes/CCTMXObjectGroup.d \
./tileMap_parallax_nodes/CCTMXTiledMap.d \
./tileMap_parallax_nodes/CCTMXXMLParser.d \
./tileMap_parallax_nodes/CCTileMapAtlas.d 


# Each subdirectory must supply rules for building sources it contributes
tileMap_parallax_nodes/%.o: ../tileMap_parallax_nodes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libfreetype2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libxml2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libjpeg" -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


