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
Particle3D/CCParticle3DAffector.cpp \
Particle3D/CCParticle3DEmitter.cpp \
Particle3D/CCParticle3DRender.cpp \
Particle3D/CCParticleSystem3D.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DForceField.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DMaterialManager.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DMaterialTranslator.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DNoise.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DPlane.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DRendererTranslator.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DScriptCompiler.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DScriptLexer.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DScriptParser.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DScriptTranslator.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DSimpleSpline.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DSphere.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DTechniqueTranslator.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DTranslateManager.cpp \
Particle3D/ParticleUniverse/CCPUParticle3DUtil.cpp \
Particle3D/ParticleUniverse/CCPUParticleSystem3D.cpp \
Particle3D/ParticleUniverse/CCPUParticleSystem3DTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffectorManager.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAlignAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAlignAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseCollider.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseColliderTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseForceAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseForceAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBoxCollider.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBoxColliderTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DCollisionAvoidanceAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DCollisionAvoidanceAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DColorAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DColorAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DFlockCenteringAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DFlockCenteringAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DForceFieldAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DForceFieldAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGeometryRotator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGeometryRotatorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGravityAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGravityAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DInterParticleCollider.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DInterParticleColliderTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DJetAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DJetAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLineAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLineAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLinearForceAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLinearForceAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DParticleFollower.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DParticleFollowerTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPathFollower.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPathFollowerTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPlaneCollider.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPlaneColliderTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DRandomiser.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DRandomiserTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleVelocityAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleVelocityAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSineForceAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSineForceAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSphereCollider.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSphereColliderTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureAnimator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureAnimatorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureRotator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureRotatorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVelocityMatchingAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVelocityMatchingAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVortexAffector.cpp \
Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVortexAffectorTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitterManager.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DBoxEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DBoxEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DCircleEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DCircleEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DLineEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DLineEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DMeshSurfaceEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DMeshSurfaceEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPointEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPointEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPositionEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPositionEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSlaveEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSlaveEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSphereSurfaceEmitter.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSphereSurfaceEmitterTranslator.cpp \
Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DVertexEmitter.cpp \
Particle3D/ParticleUniverse/ParticleRenders/CCPUParticle3DRender.cpp \

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
