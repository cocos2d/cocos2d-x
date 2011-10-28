TOP		=	../..

include $(TOP)/linux.config.mk

TARGET		=	libcocosdenshion.so
VISIBILITY	=	

INCLUDES	=	-I.. \
			-I../include \
			-I$(FMODINC)

OBJECTS		=	../Linux/FmodAudioPlayer.o \
			../Linux/SimpleAudioEngine.o \

STATICLIBS	= 
#SHAREDLIBS_DIR	=	../third_party/fmod/api/lib
#SHAREDLIBS	=	-L$(SHAREDLIBS_DIR) -lfmodex
SHAREDLIBS_DIR	=	
SHAREDLIBS	=	-L$(FMODDIR)/lib -l$(FMODLIB)

####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(CXXLIBFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)

####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXLIBFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(CCLIBFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET) core
