# need review
set(COCOS_VR_SRC)
if(NOT IOS)
    set(COCOS_VR_SRC
        vr/CCVRDistortion.cpp
        vr/CCVRDistortionMesh.cpp
        vr/CCVRGenericRenderer.cpp
        vr/CCVRGenericHeadTracker.cpp
    )
endif()
