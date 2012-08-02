CC      = gcc
CXX     = g++
AR      = ar
TARGET	= libbox2d.a
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
ARFLAGS = cr

INCLUDES = -I../../

DEFINES = -DLINUX

OBJECTS = ../Collision/Shapes/b2ChainShape.o \
../Collision/Shapes/b2CircleShape.o \
../Collision/Shapes/b2EdgeShape.o \
../Collision/Shapes/b2PolygonShape.o \
../Collision/b2BroadPhase.o \
../Collision/b2CollideCircle.o \
../Collision/b2CollideEdge.o \
../Collision/b2CollidePolygon.o \
../Collision/b2Collision.o \
../Collision/b2Distance.o \
../Collision/b2DynamicTree.o \
../Collision/b2TimeOfImpact.o \
../Common/b2BlockAllocator.o \
../Common/b2Draw.o \
../Common/b2Math.o \
../Common/b2Settings.o \
../Common/b2StackAllocator.o \
../Common/b2Timer.o \
../Dynamics/Contacts/b2ChainAndCircleContact.o \
../Dynamics/Contacts/b2ChainAndPolygonContact.o \
../Dynamics/Contacts/b2CircleContact.o \
../Dynamics/Contacts/b2Contact.o \
../Dynamics/Contacts/b2ContactSolver.o \
../Dynamics/Contacts/b2EdgeAndCircleContact.o \
../Dynamics/Contacts/b2EdgeAndPolygonContact.o \
../Dynamics/Contacts/b2PolygonAndCircleContact.o \
../Dynamics/Contacts/b2PolygonContact.o \
../Dynamics/Joints/b2DistanceJoint.o \
../Dynamics/Joints/b2FrictionJoint.o \
../Dynamics/Joints/b2GearJoint.o \
../Dynamics/Joints/b2Joint.o \
../Dynamics/Joints/b2MouseJoint.o \
../Dynamics/Joints/b2PrismaticJoint.o \
../Dynamics/Joints/b2PulleyJoint.o \
../Dynamics/Joints/b2RevoluteJoint.o \
../Dynamics/Joints/b2RopeJoint.o \
../Dynamics/Joints/b2WeldJoint.o \
../Dynamics/Joints/b2WheelJoint.o \
../Dynamics/b2Body.o \
../Dynamics/b2ContactManager.o \
../Dynamics/b2Fixture.o \
../Dynamics/b2Island.o \
../Dynamics/b2World.o \
../Dynamics/b2WorldCallbacks.o \
../Rope/b2Rope.o 



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
