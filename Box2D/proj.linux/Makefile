CC      = gcc
CXX     = g++
AR      = ar
TARGET	= libBox2D.a
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
ARFLAGS = cr

INCLUDES = -I../../

DEFINES = -DLINUX

OBJECTS = ../Collision/b2BroadPhase.o \
        ../Collision/b2CollideCircle.o \
        ../Collision/b2CollidePolygon.o \
        ../Collision/b2Collision.o \
        ../Collision/b2Distance.o \
        ../Collision/b2DynamicTree.o \
        ../Collision/b2TimeOfImpact.o \
        ../Collision/Shapes/b2CircleShape.o \
        ../Collision/Shapes/b2PolygonShape.o \
        ../Common/b2BlockAllocator.o \
        ../Common/b2Math.o \
        ../Common/b2Settings.o \
        ../Common/b2StackAllocator.o \
        ../Dynamics/b2Body.o \
        ../Dynamics/b2ContactManager.o \
        ../Dynamics/b2Fixture.o \
        ../Dynamics/b2Island.o \
        ../Dynamics/b2World.o \
        ../Dynamics/b2WorldCallbacks.o \
        ../Dynamics/Contacts/b2CircleContact.o \
        ../Dynamics/Contacts/b2Contact.o \
        ../Dynamics/Contacts/b2ContactSolver.o \
        ../Dynamics/Contacts/b2PolygonAndCircleContact.o \
        ../Dynamics/Contacts/b2PolygonContact.o \
        ../Dynamics/Contacts/b2TOISolver.o \
        ../Dynamics/Joints/b2DistanceJoint.o \
        ../Dynamics/Joints/b2FrictionJoint.o \
        ../Dynamics/Joints/b2GearJoint.o \
        ../Dynamics/Joints/b2Joint.o \
        ../Dynamics/Joints/b2LineJoint.o \
        ../Dynamics/Joints/b2MouseJoint.o \
        ../Dynamics/Joints/b2PrismaticJoint.o \
        ../Dynamics/Joints/b2PulleyJoint.o \
        ../Dynamics/Joints/b2RevoluteJoint.o \
        ../Dynamics/Joints/b2WeldJoint.o 


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