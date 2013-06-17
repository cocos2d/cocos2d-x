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
	../src/constraints/cpPinJoint.cpp \

include ../../../cocos2dx/proj.emscripten/cocos2dx.mk

TARGET = $(LIB_DIR)/libchipmunk.a
INCLUDES = -I../include/chipmunk
OBJECTS := $(subst src/,,$(OBJECTS))

all: $(TARGET)

# Egregious hack to force Emscripten to compile as C++. This is necessary as
# Emscripten uses different calling conventions for structs passed on the stack
# in C and C++. See this bug for more info:
# 
# https://github.com/kripken/emscripten/issues/1101
# 
# Note that Make kindly cleans these files up afterwards
%.cpp: %.c
	ln -f $< $@

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o: ../src/%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
