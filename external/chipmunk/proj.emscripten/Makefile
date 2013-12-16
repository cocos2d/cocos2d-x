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
	../src/constraints/cpPinJoint.c \

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
