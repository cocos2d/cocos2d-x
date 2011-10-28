CC      = gcc
CXX     = g++
TARGET	= libcocosdenshion.so
CCFLAGS = -Wall -g -O2 -fPIC
CXXFLAGS = -Wall -g -O2 -fPIC
VISIBILITY = 

INCLUDES = -I.. \
		-I../include \
		-I../third_party/fmod/api/inc 

DEFINES = -DLINUX

OBJECTS =   ../Linux/FmodAudioPlayer.o \
            ../Linux/SimpleAudioEngine.o \

STATICLIBS = 
SHAREDLIBS_DIR = ../third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex

####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core
