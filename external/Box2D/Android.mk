LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := box2d_static

LOCAL_MODULE_FILENAME := libbox2d

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/Collision/b2BroadPhase.cpp \
$(LOCAL_PATH)/Collision/b2CollideCircle.cpp \
$(LOCAL_PATH)/Collision/b2CollideEdge.cpp \
$(LOCAL_PATH)/Collision/b2CollidePolygon.cpp \
$(LOCAL_PATH)/Collision/b2Collision.cpp \
$(LOCAL_PATH)/Collision/b2Distance.cpp \
$(LOCAL_PATH)/Collision/b2DynamicTree.cpp \
$(LOCAL_PATH)/Collision/b2TimeOfImpact.cpp \
$(LOCAL_PATH)/Collision/Shapes/b2ChainShape.cpp \
$(LOCAL_PATH)/Collision/Shapes/b2CircleShape.cpp \
$(LOCAL_PATH)/Collision/Shapes/b2EdgeShape.cpp \
$(LOCAL_PATH)/Collision/Shapes/b2PolygonShape.cpp \
$(LOCAL_PATH)/Common/b2BlockAllocator.cpp \
$(LOCAL_PATH)/Common/b2Draw.cpp \
$(LOCAL_PATH)/Common/b2Math.cpp \
$(LOCAL_PATH)/Common/b2Settings.cpp \
$(LOCAL_PATH)/Common/b2StackAllocator.cpp \
$(LOCAL_PATH)/Common/b2Timer.cpp \
$(LOCAL_PATH)/Dynamics/b2Body.cpp \
$(LOCAL_PATH)/Dynamics/b2ContactManager.cpp \
$(LOCAL_PATH)/Dynamics/b2Fixture.cpp \
$(LOCAL_PATH)/Dynamics/b2Island.cpp \
$(LOCAL_PATH)/Dynamics/b2World.cpp \
$(LOCAL_PATH)/Dynamics/b2WorldCallbacks.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2CircleContact.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2Contact.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2ContactSolver.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
$(LOCAL_PATH)/Dynamics/Contacts/b2PolygonContact.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2DistanceJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2FrictionJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2GearJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2Joint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2MouseJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2PrismaticJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2PulleyJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2RevoluteJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2RopeJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2WeldJoint.cpp \
$(LOCAL_PATH)/Dynamics/Joints/b2WheelJoint.cpp \
$(LOCAL_PATH)/Rope/b2Rope.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..
                                 
include $(BUILD_STATIC_LIBRARY)
