CC      = gcc
CXX     = g++
AR      = ar
TARGET	= libchipmunk.a
CCFLAGS = -Wall -g -O2 -std=c99
CXXFLAGS = -Wall -g -O2 
ARFLAGS = cr

INCLUDES = -I../include/chipmunk

DEFINES = -DLINUX

OBJECTS = ../src/chipmunk.o \
../src/cpArbiter.o \
../src/cpArray.o \
../src/cpBB.o \
../src/cpBody.o \
../src/cpCollision.o \
../src/cpHashSet.o \
../src/cpPolyShape.o \
../src/cpShape.o \
../src/cpSpace.o \
../src/cpSpaceComponent.o \
../src/cpSpaceHash.o \
../src/cpSpaceQuery.o \
../src/cpSpaceStep.o \
../src/cpVect.o \
../src/constraints/cpConstraint.o \
../src/constraints/cpDampedRotarySpring.o \
../src/constraints/cpDampedSpring.o \
../src/constraints/cpGearJoint.o \
../src/constraints/cpGrooveJoint.o \
../src/constraints/cpPinJoint.o \
../src/constraints/cpPivotJoint.o \
../src/constraints/cpRatchetJoint.o \
../src/constraints/cpRotaryLimitJoint.o \
../src/constraints/cpSimpleMotor.o \
../src/constraints/cpSlideJoint.o 


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