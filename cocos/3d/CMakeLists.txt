
if(WINDOWS AND BUILD_SHARED_LIBS)
  ADD_DEFINITIONS (-D_USE3DDLL)
endif()

set(COCOS_3D_SRC

  3d/CCAABB.cpp
  3d/CCAnimate3D.cpp
  3d/CCAnimation3D.cpp
  3d/CCAttachNode.cpp
  3d/CCBundle3D.cpp
  3d/CCBundleReader.cpp
  3d/CCFrustum.cpp
  3d/CCMesh.cpp
  3d/CCMeshSkin.cpp
  3d/CCMeshVertexIndexData.cpp
  3d/CCOBB.cpp
  3d/CCObjLoader.cpp
  3d/CCPlane.cpp
  3d/CCRay.cpp
  3d/CCSkeleton3D.cpp
  3d/CCSprite3D.cpp
  3d/CCSprite3DMaterial.cpp
  3d/CCBillBoard.cpp

)
