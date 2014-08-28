set(COCOS_3D_SRC
CCRay.cpp
CCAABB.cpp
CCOBB.cpp
CCAnimate3D.cpp
CCAnimation3D.cpp
CCAttachNode.cpp
CCBundle3D.cpp
CCBundleReader.cpp
CCMesh.cpp
CCMeshSkin.cpp
CCMeshVertexIndexData.cpp
CCSprite3DMaterial.cpp
CCObjLoader.cpp
CCSkeleton3D.cpp
CCSprite3D.cpp
)


include_directories(
  3d
)

add_library(cocos3d STATIC
  ${COCOS_3D_SRC}
)

target_link_libraries(cocos3d
  cocos2d
)

set_target_properties(cocos3d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
