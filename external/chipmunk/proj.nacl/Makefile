NACL_ARCH ?= x86_64
NACL_AR ?= $(NACL_ARCH)-nacl-ar
NACL_CC ?= $(NACL_ARCH)-nacl-gcc
NACL_CXX ?= $(NACL_ARCH)-nacl-g++
CCFLAGS = -Wall -std=gnu99
CXXFLAGS = -Wall
VISIBILITY =
ARFLAGS = cr

LIBS =

INCLUDES = -I../include/chipmunk

SOURCES = ../src/chipmunk.cpp \
../src/cpBody.cpp \
../src/cpSpace.cpp \
../src/cpSpatialIndex.cpp \
../src/cpArbiter.cpp \
../src/cpCollision.cpp \
../src/cpSpaceComponent.cpp \
../src/cpSweep1D.cpp \
../src/cpArray.cpp \
../src/cpHashSet.cpp \
../src/cpSpaceHash.cpp \
../src/cpVect.cpp \
../src/cpBB.cpp \
../src/cpPolyShape.cpp \
../src/cpSpaceQuery.cpp \
../src/cpBBTree.cpp \
../src/cpShape.cpp \
../src/cpSpaceStep.cpp \
../src/constraints/cpConstraint.cpp \
../src/constraints/cpPivotJoint.cpp \
../src/constraints/cpDampedRotarySpring.cpp \
../src/constraints/cpRatchetJoint.cpp \
../src/constraints/cpDampedSpring.cpp \
../src/constraints/cpRotaryLimitJoint.cpp \
../src/constraints/cpGearJoint.cpp \
../src/constraints/cpSimpleMotor.cpp \
../src/constraints/cpGrooveJoint.cpp \
../src/constraints/cpSlideJoint.cpp \
../src/constraints/cpPinJoint.cpp

COCOS_ROOT = ../../..

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

TARGET = $(LIB_DIR)/libchipmunk.a

all: $(TARGET)

####### Build rules
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(NACL_AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

####### Compile
$(OBJ_DIR)/%.o: ../%.cpp
	@mkdir -p $(@D)
	$(NACL_CXX) -MMD $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c
	@mkdir -p $(@D)
	$(NACL_CC) -MMD $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET) core

-include $(DEPS)
