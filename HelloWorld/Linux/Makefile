CC      = gcc
CXX     = g++
TARGET	= HelloWorld
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
VISIBILITY = 

INCLUDES = -I../../cocos2dx/platform/third_party/linux \
            -I../../cocos2dx/include \
            -I../../cocos2dx \
            -I../../cocos2dx/platform \
            -I../../CocosDenshion/include \
            -I../Classes/

DEFINES = -DLINUX

OBJECTS = ./main.o \
        ../Classes/AppDelegate.o \
        ../Classes/HelloWorldScene.o 

STATICLIBS =  
SHAREDLIBS = -L../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../lib/linux/Debug/

#$(shell ../../build-linux.sh $<)
####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core
