LOCAL_PATH := $(call my-dir)

# compile box2d.a
include $(CLEAR_VARS)
LOCAL_MODULE := libbox2d

LOCAL_SRC_FILES := \
Collision/Shapes/b2CircleShape.cpp \
Collision/Shapes/b2PolygonShape.cpp \
Collision/b2BroadPhase.cpp \
Collision/b2CollideCircle.cpp \
Collision/b2CollidePolygon.cpp \
Collision/b2Collision.cpp \
Collision/b2Distance.cpp \
Collision/b2DynamicTree.cpp \
Collision/b2TimeOfImpact.cpp \
Common/b2BlockAllocator.cpp \
Common/b2Math.cpp \
Common/b2Settings.cpp \
Common/b2StackAllocator.cpp \
Dynamics/Contacts/b2CircleContact.cpp \
Dynamics/Contacts/b2Contact.cpp \
Dynamics/Contacts/b2ContactSolver.cpp \
Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
Dynamics/Contacts/b2PolygonContact.cpp \
Dynamics/Contacts/b2TOISolver.cpp \
Dynamics/Joints/b2DistanceJoint.cpp \
Dynamics/Joints/b2FrictionJoint.cpp \
Dynamics/Joints/b2GearJoint.cpp \
Dynamics/Joints/b2Joint.cpp \
Dynamics/Joints/b2LineJoint.cpp \
Dynamics/Joints/b2MouseJoint.cpp \
Dynamics/Joints/b2PrismaticJoint.cpp \
Dynamics/Joints/b2PulleyJoint.cpp \
Dynamics/Joints/b2RevoluteJoint.cpp \
Dynamics/Joints/b2WeldJoint.cpp \
Dynamics/b2Body.cpp \
Dynamics/b2ContactManager.cpp \
Dynamics/b2Fixture.cpp \
Dynamics/b2Island.cpp \
Dynamics/b2World.cpp \
Dynamics/b2WorldCallbacks.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..
                                 
include $(BUILD_SHARED_LIBRARY)
