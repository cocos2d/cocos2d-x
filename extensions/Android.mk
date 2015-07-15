LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

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
Particle3D/PU/CCPUDynamicAttribute.cpp \
Particle3D/PU/CCPUDynamicAttributeTranslator.cpp \
Particle3D/PU/CCPUForceField.cpp \
Particle3D/PU/CCPUMaterialManager.cpp \
Particle3D/PU/CCPUMaterialTranslator.cpp \
Particle3D/PU/CCPUNoise.cpp \
Particle3D/PU/CCPUPlane.cpp \
Particle3D/PU/CCPURendererTranslator.cpp \
Particle3D/PU/CCPUScriptCompiler.cpp \
Particle3D/PU/CCPUScriptLexer.cpp \
Particle3D/PU/CCPUScriptParser.cpp \
Particle3D/PU/CCPUScriptTranslator.cpp \
Particle3D/PU/CCPUSimpleSpline.cpp \
Particle3D/PU/CCPUSphere.cpp \
Particle3D/PU/CCPUTechniqueTranslator.cpp \
Particle3D/PU/CCPUTranslateManager.cpp \
Particle3D/PU/CCPUUtil.cpp \
Particle3D/PU/CCPUParticleSystem3D.cpp \
Particle3D/PU/CCPUParticleSystem3DTranslator.cpp \
Particle3D/PU/CCPUListener.cpp \
Particle3D/PU/CCPUAffector.cpp \
Particle3D/PU/CCPUAffectorManager.cpp \
Particle3D/PU/CCPUAffectorTranslator.cpp \
Particle3D/PU/CCPUAlignAffector.cpp \
Particle3D/PU/CCPUAlignAffectorTranslator.cpp \
Particle3D/PU/CCPUBaseCollider.cpp \
Particle3D/PU/CCPUBaseColliderTranslator.cpp \
Particle3D/PU/CCPUBaseForceAffector.cpp \
Particle3D/PU/CCPUBaseForceAffectorTranslator.cpp \
Particle3D/PU/CCPUBoxCollider.cpp \
Particle3D/PU/CCPUBoxColliderTranslator.cpp \
Particle3D/PU/CCPUCollisionAvoidanceAffector.cpp \
Particle3D/PU/CCPUCollisionAvoidanceAffectorTranslator.cpp \
Particle3D/PU/CCPUColorAffector.cpp \
Particle3D/PU/CCPUColorAffectorTranslator.cpp \
Particle3D/PU/CCPUFlockCenteringAffector.cpp \
Particle3D/PU/CCPUFlockCenteringAffectorTranslator.cpp \
Particle3D/PU/CCPUForceFieldAffector.cpp \
Particle3D/PU/CCPUForceFieldAffectorTranslator.cpp \
Particle3D/PU/CCPUGeometryRotator.cpp \
Particle3D/PU/CCPUGeometryRotatorTranslator.cpp \
Particle3D/PU/CCPUGravityAffector.cpp \
Particle3D/PU/CCPUGravityAffectorTranslator.cpp \
Particle3D/PU/CCPUInterParticleCollider.cpp \
Particle3D/PU/CCPUInterParticleColliderTranslator.cpp \
Particle3D/PU/CCPUJetAffector.cpp \
Particle3D/PU/CCPUJetAffectorTranslator.cpp \
Particle3D/PU/CCPULineAffector.cpp \
Particle3D/PU/CCPULineAffectorTranslator.cpp \
Particle3D/PU/CCPULinearForceAffector.cpp \
Particle3D/PU/CCPULinearForceAffectorTranslator.cpp \
Particle3D/PU/CCPUParticleFollower.cpp \
Particle3D/PU/CCPUParticleFollowerTranslator.cpp \
Particle3D/PU/CCPUPathFollower.cpp \
Particle3D/PU/CCPUPathFollowerTranslator.cpp \
Particle3D/PU/CCPUPlaneCollider.cpp \
Particle3D/PU/CCPUPlaneColliderTranslator.cpp \
Particle3D/PU/CCPURandomiser.cpp \
Particle3D/PU/CCPURandomiserTranslator.cpp \
Particle3D/PU/CCPUScaleAffector.cpp \
Particle3D/PU/CCPUScaleAffectorTranslator.cpp \
Particle3D/PU/CCPUScaleVelocityAffector.cpp \
Particle3D/PU/CCPUScaleVelocityAffectorTranslator.cpp \
Particle3D/PU/CCPUSineForceAffector.cpp \
Particle3D/PU/CCPUSineForceAffectorTranslator.cpp \
Particle3D/PU/CCPUSphereCollider.cpp \
Particle3D/PU/CCPUSphereColliderTranslator.cpp \
Particle3D/PU/CCPUTextureAnimator.cpp \
Particle3D/PU/CCPUTextureAnimatorTranslator.cpp \
Particle3D/PU/CCPUTextureRotator.cpp \
Particle3D/PU/CCPUTextureRotatorTranslator.cpp \
Particle3D/PU/CCPUVelocityMatchingAffector.cpp \
Particle3D/PU/CCPUVelocityMatchingAffectorTranslator.cpp \
Particle3D/PU/CCPUVortexAffector.cpp \
Particle3D/PU/CCPUVortexAffectorTranslator.cpp \
Particle3D/PU/CCPUEmitter.cpp \
Particle3D/PU/CCPUEmitterTranslator.cpp \
Particle3D/PU/CCPUEmitterManager.cpp \
Particle3D/PU/CCPUBoxEmitter.cpp \
Particle3D/PU/CCPUBoxEmitterTranslator.cpp \
Particle3D/PU/CCPUCircleEmitter.cpp \
Particle3D/PU/CCPUCircleEmitterTranslator.cpp \
Particle3D/PU/CCPULineEmitter.cpp \
Particle3D/PU/CCPULineEmitterTranslator.cpp \
Particle3D/PU/CCPUMeshSurfaceEmitter.cpp \
Particle3D/PU/CCPUMeshSurfaceEmitterTranslator.cpp \
Particle3D/PU/CCPUPointEmitter.cpp \
Particle3D/PU/CCPUPointEmitterTranslator.cpp \
Particle3D/PU/CCPUPositionEmitter.cpp \
Particle3D/PU/CCPUPositionEmitterTranslator.cpp \
Particle3D/PU/CCPUSlaveEmitter.cpp \
Particle3D/PU/CCPUSlaveEmitterTranslator.cpp \
Particle3D/PU/CCPUSphereSurfaceEmitter.cpp \
Particle3D/PU/CCPUSphereSurfaceEmitterTranslator.cpp \
Particle3D/PU/CCPUVertexEmitter.cpp \
Particle3D/PU/CCPURender.cpp \
Particle3D/PU/CCPUBeamRender.cpp \
Particle3D/PU/CCPUBillboardChain.cpp \
Particle3D/PU/CCPURibbonTrail.cpp \
Particle3D/PU/CCPURibbonTrailRender.cpp \
Particle3D/PU/CCPUDoAffectorEventHandler.cpp \
Particle3D/PU/CCPUDoAffectorEventHandlerTranslator.cpp \
Particle3D/PU/CCPUDoEnableComponentEventHandler.cpp \
Particle3D/PU/CCPUDoEnableComponentEventHandlerTranslator.cpp \
Particle3D/PU/CCPUDoExpireEventHandler.cpp \
Particle3D/PU/CCPUDoExpireEventHandlerTranslator.cpp \
Particle3D/PU/CCPUDoFreezeEventHandler.cpp \
Particle3D/PU/CCPUDoFreezeEventHandlerTranslator.cpp \
Particle3D/PU/CCPUDoPlacementParticleEventHandler.cpp \
Particle3D/PU/CCPUDoPlacementParticleEventHandlerTranslator.cpp \
Particle3D/PU/CCPUDoScaleEventHandler.cpp \
Particle3D/PU/CCPUDoScaleEventHandlerTranslator.cpp \
Particle3D/PU/CCPUDoStopSystemEventHandler.cpp \
Particle3D/PU/CCPUDoStopSystemEventHandlerTranslator.cpp \
Particle3D/PU/CCPUEventHandler.cpp \
Particle3D/PU/CCPUEventHandlerManager.cpp \
Particle3D/PU/CCPUEventHandlerTranslator.cpp \
Particle3D/PU/CCPUObserver.cpp \
Particle3D/PU/CCPUObserverManager.cpp \
Particle3D/PU/CCPUObserverTranslator.cpp \
Particle3D/PU/CCPUOnClearObserver.cpp \
Particle3D/PU/CCPUOnClearObserverTranslator.cpp \
Particle3D/PU/CCPUOnCollisionObserver.cpp \
Particle3D/PU/CCPUOnCollisionObserverTranslator.cpp \
Particle3D/PU/CCPUOnCountObserver.cpp \
Particle3D/PU/CCPUOnCountObserverTranslator.cpp \
Particle3D/PU/CCPUOnEmissionObserver.cpp \
Particle3D/PU/CCPUOnEmissionObserverTranslator.cpp \
Particle3D/PU/CCPUOnEventFlagObserver.cpp \
Particle3D/PU/CCPUOnEventFlagObserverTranslator.cpp \
Particle3D/PU/CCPUOnExpireObserver.cpp \
Particle3D/PU/CCPUOnExpireObserverTranslator.cpp \
Particle3D/PU/CCPUOnPositionObserver.cpp \
Particle3D/PU/CCPUOnPositionObserverTranslator.cpp \
Particle3D/PU/CCPUOnQuotaObserver.cpp \
Particle3D/PU/CCPUOnQuotaObserverTranslator.cpp \
Particle3D/PU/CCPUOnRandomObserver.cpp \
Particle3D/PU/CCPUOnRandomObserverTranslator.cpp \
Particle3D/PU/CCPUOnTimeObserver.cpp \
Particle3D/PU/CCPUOnTimeObserverTranslator.cpp \
Particle3D/PU/CCPUOnVelocityObserver.cpp \
Particle3D/PU/CCPUOnVelocityObserverTranslator.cpp \
Particle3D/PU/CCPUBehaviour.cpp \
Particle3D/PU/CCPUBehaviourManager.cpp \
Particle3D/PU/CCPUBehaviourTranslator.cpp \
Particle3D/PU/CCPUSlaveBehaviour.cpp \
Particle3D/PU/CCPUSlaveBehaviourTranslator.cpp

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += cocos_curl_static
LOCAL_STATIC_LIBRARIES += box2d_static
LOCAL_STATIC_LIBRARIES += bullet_static

LOCAL_CXXFLAGS += -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/. \
                           $(LOCAL_PATH)/.. \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCScrollView 
                    
include $(BUILD_STATIC_LIBRARY)
