CC      = gcc
CXX     = g++
AR      = ar
TARGET	= libchipmunk.a
CCFLAGS = -Wall -g -O2 -std=gnu99
CXXFLAGS = -Wall -g -O2 
ARFLAGS = cr

INCLUDES = -I../include/chipmunk

DEFINES = -DLINUX

OBJECTS = ../src/chipmunk.o \
			../src/cpBody.o \
			../src/cpSpace.o \
			../src/cpSpatialIndex.o \
			../src/cpArbiter.o \
			../src/cpCollision.o \
			../src/cpSpaceComponent.o \
			../src/cpSweep1D.o \
			../src/cpArray.o \
			../src/cpHashSet.o \
			../src/cpSpaceHash.o \
			../src/cpVect.o \
			../src/cpBB.o \
			../src/cpPolyShape.o \
			../src/cpSpaceQuery.o \
			../src/cpBBTree.o \
			../src/cpShape.o \
			../src/cpSpaceStep.o \
			../src/constraints/cpConstraint.o \
			../src/constraints/cpPivotJoint.o \
			../src/constraints/cpDampedRotarySpring.o \
			../src/constraints/cpRatchetJoint.o \
			../src/constraints/cpDampedSpring.o \
			../src/constraints/cpRotaryLimitJoint.o \
			../src/constraints/cpGearJoint.o \
			../src/constraints/cpSimpleMotor.o \
			../src/constraints/cpGrooveJoint.o \
			../src/constraints/cpSlideJoint.o \
			../src/constraints/cpPinJoint.o \


####### Build rules
$(TARGET): $(OBJECTS) 
	$(AR) $(ARFLAGS) $(TARGET) $(OBJECTS)  
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core
