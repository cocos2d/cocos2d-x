LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := \
assets-manager/AssetsManager.cpp \
assets-manager/Downloader.cpp \
assets-manager/Manifest.cpp \
assets-manager/AssetsManagerEx.cpp \
assets-manager/CCEventAssetsManagerEx.cpp \
assets-manager/CCEventListenerAssetsManagerEx.cpp \
GUI/CCControlExtension/CCControl.cpp \
GUI/CCControlExtension/CCControlButton.cpp \
GUI/CCControlExtension/CCControlColourPicker.cpp \
GUI/CCControlExtension/CCControlHuePicker.cpp \
GUI/CCControlExtension/CCControlPotentiometer.cpp \
GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
GUI/CCControlExtension/CCControlSlider.cpp \
GUI/CCControlExtension/CCControlStepper.cpp \
GUI/CCControlExtension/CCControlSwitch.cpp \
GUI/CCControlExtension/CCControlUtils.cpp \
GUI/CCControlExtension/CCInvocation.cpp \
GUI/CCScrollView/CCScrollView.cpp \
GUI/CCScrollView/CCTableView.cpp \
GUI/CCScrollView/CCTableViewCell.cpp \
physics-nodes/CCPhysicsDebugNode.cpp \
physics-nodes/CCPhysicsSprite.cpp \
3dparticle/CCParticle3DAffector.cpp \
3dparticle/CCParticle3DEmitter.cpp \
3dparticle/CCParticle3DRender.cpp \
3dparticle/CCParticleSystem3D.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DDynamicAttribute.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DForceField.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DMaterialManager.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DMaterialTranslator.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DNoise.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DPlane.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DRendererTranslator.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DScriptCompiler.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DScriptLexer.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DScriptParser.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DScriptTranslator.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DSimpleSpline.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DSphere.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DTechniqueTranslator.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DTranslateManager.cpp \
3dparticle/ParticleUniverse/CCPUParticle3DUtil.cpp \
3dparticle/ParticleUniverse/CCPUParticleSystem3D.cpp \
3dparticle/ParticleUniverse/CCPUParticleSystem3DTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffectorManager.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAlignAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAlignAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseCollider.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseColliderTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseForceAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseForceAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DBoxCollider.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DBoxColliderTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DCollisionAvoidanceAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DCollisionAvoidanceAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DColorAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DColorAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DFlockCenteringAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DFlockCenteringAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DForceFieldAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DForceFieldAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DGeometryRotator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DGeometryRotatorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DGravityAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DGravityAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DInterParticleCollider.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DInterParticleColliderTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DJetAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DJetAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DLineAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DLineAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DLinearForceAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DLinearForceAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DParticleFollower.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DParticleFollowerTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DPathFollower.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DPathFollowerTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DPlaneCollider.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DPlaneColliderTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DRandomiser.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DRandomiserTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleVelocityAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleVelocityAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DSineForceAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DSineForceAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DSphereCollider.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DSphereColliderTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureAnimator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureAnimatorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureRotator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureRotatorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DVelocityMatchingAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DVelocityMatchingAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DVortexAffector.cpp \
3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DVortexAffectorTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitterManager.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DBoxEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DBoxEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DCircleEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DCircleEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DLineEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DLineEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DMeshSurfaceEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DMeshSurfaceEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DPointEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DPointEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DPositionEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DPositionEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DSlaveEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DSlaveEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DSphereSurfaceEmitter.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DSphereSurfaceEmitterTranslator.cpp \
3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DVertexEmitter.cpp \
3dparticle/ParticleUniverse/ParticleRenders/CCPUParticle3DRender.cpp \

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += cocos_curl_static
LOCAL_STATIC_LIBRARIES += box2d_static

LOCAL_CXXFLAGS += -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/. \
                           $(LOCAL_PATH)/.. \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCScrollView 
                    
include $(BUILD_STATIC_LIBRARY)
