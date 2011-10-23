TOP		=	../..

include $(TOP)/linux.config.mk

TARGET		=	HelloWorld

VISIBILITY	=	

INCLUDES	=	\
			-I$(TOP)/cocos2dx/include \
			-I$(TOP)/cocos2dx \
			-I$(TOP)/cocos2dx/platform \
			-I$(TOP)/CocosDenshion/include \
			-I../Classes \

OBJECTS		=	./main.o \
			../Classes/AppDelegate.o \
			../Classes/HelloWorldScene.o 

STATICLIBS =  
SHAREDLIBS = -L$(TOP)/lib/linux/$(OUTDIRSUFFIX) -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,$(TOP)/lib/linux/$(OUTDIRSUFFIX)

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
