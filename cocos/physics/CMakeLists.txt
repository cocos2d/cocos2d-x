
option(USE_CHIPMUNK "Use chipmunk for physics library" ON)

cocos_target_sources(${COCOS2D_TARGET} GROUP "physics" FILES
    ${CMAKE_CURRENT_LIST_FILE}
    "physics/CCPhysicsBody.cpp"
    "physics/CCPhysicsContact.cpp"
    "physics/CCPhysicsJoint.cpp"
    "physics/CCPhysicsShape.cpp"
    "physics/CCPhysicsWorld.cpp"
)

cocos_use_package(${COCOS2D_TARGET} CHIPMUNK REQUIRED)

return()
# Chipmunk
if(USE_CHIPMUNK)
  cocos_find_package(Chipmunk CHIPMUNK REQUIRED)
  add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
  if(IOS OR MACOSX)
    # without this chipmunk will try to use apple defined geometry types, that conflicts with cocos
    add_definitions(-DCP_USE_CGPOINTS=0)
  endif()
else(USE_CHIPMUNK)
  add_definitions(-DCC_USE_PHYSICS=0)
endif(USE_CHIPMUNK)

