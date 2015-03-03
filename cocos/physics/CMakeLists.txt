
cocos_target_sources(${COCOS2D_TARGET} GROUP "physics" FILES
    ${CMAKE_CURRENT_LIST_FILE}
    "physics/CCPhysicsBody.cpp"
    "physics/CCPhysicsContact.cpp"
    "physics/CCPhysicsJoint.cpp"
    "physics/CCPhysicsShape.cpp"
    "physics/CCPhysicsWorld.cpp"
)

cocos_use_package(${COCOS2D_TARGET} CHIPMUNK REQUIRED)

