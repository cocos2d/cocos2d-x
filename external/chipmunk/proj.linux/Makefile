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

include ../../../cocos2dx/proj.linux/cocos2dx.mk

TARGET = $(LIB_DIR)/libchipmunk.a
INCLUDES = -I../include/chipmunk
DEFINES = -DLINUX
CCFLAGS += -std=gnu99
OBJECTS := $(subst src/,,$(OBJECTS))

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o: ../src/%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
