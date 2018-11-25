if(NOT IOS)
    set(COCOS_VR_HEADER
        vr/CCVRGenericHeadTracker.h
        vr/CCVRDistortion.h
        vr/CCVRProtocol.h
        vr/CCVRGenericRenderer.h
        vr/CCVRDistortionMesh.h
        )
    set(COCOS_VR_SRC
        vr/CCVRDistortion.cpp
        vr/CCVRDistortionMesh.cpp
        vr/CCVRGenericRenderer.cpp
        vr/CCVRGenericHeadTracker.cpp
        )
endif()
