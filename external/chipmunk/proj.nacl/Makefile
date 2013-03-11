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

SOURCES = ../src/chipmunk.c \
../src/cpBody.c \
../src/cpSpace.c \
../src/cpSpatialIndex.c \
../src/cpArbiter.c \
../src/cpCollision.c \
../src/cpSpaceComponent.c \
../src/cpSweep1D.c \
../src/cpArray.c \
../src/cpHashSet.c \
../src/cpSpaceHash.c \
../src/cpVect.c \
../src/cpBB.c \
../src/cpPolyShape.c \
../src/cpSpaceQuery.c \
../src/cpBBTree.c \
../src/cpShape.c \
../src/cpSpaceStep.c \
../src/constraints/cpConstraint.c \
../src/constraints/cpPivotJoint.c \
../src/constraints/cpDampedRotarySpring.c \
../src/constraints/cpRatchetJoint.c \
../src/constraints/cpDampedSpring.c \
../src/constraints/cpRotaryLimitJoint.c \
../src/constraints/cpGearJoint.c \
../src/constraints/cpSimpleMotor.c \
../src/constraints/cpGrooveJoint.c \
../src/constraints/cpSlideJoint.c \
../src/constraints/cpPinJoint.c

COCOS_ROOT = ../../..

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

TARGET = $(LIB_DIR)/libchipmunk.a

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(NACL_AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(NACL_CC) -MMD $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
