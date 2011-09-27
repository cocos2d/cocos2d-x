CC      = gcc
CXX     = g++
TARGET	= libCocosDenshion.so
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
VISIBILITY = 

INCLUDES = -I.. \
		-I../include \
		-I../third_party/fmod/api/inc 

DEFINES = -DLINUX

OBJECTS =   ../Linux/FmodAudioPlayer.o \
            ../Linux/SimpleAudioEngine.o \


STATICLIBS = 
SHAREDLIBS = -lfmodex

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