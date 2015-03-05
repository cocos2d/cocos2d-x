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
Particle3D/PU/CCPUParticle3DDynamicAttribute.cpp \
Particle3D/PU/CCPUParticle3DDynamicAttributeTranslator.cpp \
Particle3D/PU/CCPUParticle3DForceField.cpp \
Particle3D/PU/CCPUParticle3DMaterialManager.cpp \
Particle3D/PU/CCPUParticle3DMaterialTranslator.cpp \
Particle3D/PU/CCPUParticle3DNoise.cpp \
Particle3D/PU/CCPUParticle3DPlane.cpp \
Particle3D/PU/CCPUParticle3DRendererTranslator.cpp \
Particle3D/PU/CCPUParticle3DScriptCompiler.cpp \
Particle3D/PU/CCPUParticle3DScriptLexer.cpp \
Particle3D/PU/CCPUParticle3DScriptParser.cpp \
Particle3D/PU/CCPUParticle3DScriptTranslator.cpp \
Particle3D/PU/CCPUParticle3DSimpleSpline.cpp \
Particle3D/PU/CCPUParticle3DSphere.cpp \
Particle3D/PU/CCPUParticle3DTechniqueTranslator.cpp \
Particle3D/PU/CCPUParticle3DTranslateManager.cpp \
Particle3D/PU/CCPUParticle3DUtil.cpp \
Particle3D/PU/CCPUParticleSystem3D.cpp \
Particle3D/PU/CCPUParticleSystem3DTranslator.cpp \
Particle3D/PU/CCPUParticle3DListener.cpp \
Particle3D/PU/CCPUParticle3DAffector.cpp \
Particle3D/PU/CCPUParticle3DAffectorManager.cpp \
Particle3D/PU/CCPUParticle3DAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DAlignAffector.cpp \
Particle3D/PU/CCPUParticle3DAlignAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DBaseCollider.cpp \
Particle3D/PU/CCPUParticle3DBaseColliderTranslator.cpp \
Particle3D/PU/CCPUParticle3DBaseForceAffector.cpp \
Particle3D/PU/CCPUParticle3DBaseForceAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DBoxCollider.cpp \
Particle3D/PU/CCPUParticle3DBoxColliderTranslator.cpp \
Particle3D/PU/CCPUParticle3DCollisionAvoidanceAffector.cpp \
Particle3D/PU/CCPUParticle3DCollisionAvoidanceAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DColorAffector.cpp \
Particle3D/PU/CCPUParticle3DColorAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DFlockCenteringAffector.cpp \
Particle3D/PU/CCPUParticle3DFlockCenteringAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DForceFieldAffector.cpp \
Particle3D/PU/CCPUParticle3DForceFieldAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DGeometryRotator.cpp \
Particle3D/PU/CCPUParticle3DGeometryRotatorTranslator.cpp \
Particle3D/PU/CCPUParticle3DGravityAffector.cpp \
Particle3D/PU/CCPUParticle3DGravityAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DInterParticleCollider.cpp \
Particle3D/PU/CCPUParticle3DInterParticleColliderTranslator.cpp \
Particle3D/PU/CCPUParticle3DJetAffector.cpp \
Particle3D/PU/CCPUParticle3DJetAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DLineAffector.cpp \
Particle3D/PU/CCPUParticle3DLineAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DLinearForceAffector.cpp \
Particle3D/PU/CCPUParticle3DLinearForceAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DParticleFollower.cpp \
Particle3D/PU/CCPUParticle3DParticleFollowerTranslator.cpp \
Particle3D/PU/CCPUParticle3DPathFollower.cpp \
Particle3D/PU/CCPUParticle3DPathFollowerTranslator.cpp \
Particle3D/PU/CCPUParticle3DPlaneCollider.cpp \
Particle3D/PU/CCPUParticle3DPlaneColliderTranslator.cpp \
Particle3D/PU/CCPUParticle3DRandomiser.cpp \
Particle3D/PU/CCPUParticle3DRandomiserTranslator.cpp \
Particle3D/PU/CCPUParticle3DScaleAffector.cpp \
Particle3D/PU/CCPUParticle3DScaleAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DScaleVelocityAffector.cpp \
Particle3D/PU/CCPUParticle3DScaleVelocityAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DSineForceAffector.cpp \
Particle3D/PU/CCPUParticle3DSineForceAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DSphereCollider.cpp \
Particle3D/PU/CCPUParticle3DSphereColliderTranslator.cpp \
Particle3D/PU/CCPUParticle3DTextureAnimator.cpp \
Particle3D/PU/CCPUParticle3DTextureAnimatorTranslator.cpp \
Particle3D/PU/CCPUParticle3DTextureRotator.cpp \
Particle3D/PU/CCPUParticle3DTextureRotatorTranslator.cpp \
Particle3D/PU/CCPUParticle3DVelocityMatchingAffector.cpp \
Particle3D/PU/CCPUParticle3DVelocityMatchingAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DVortexAffector.cpp \
Particle3D/PU/CCPUParticle3DVortexAffectorTranslator.cpp \
Particle3D/PU/CCPUParticle3DEmitter.cpp \
Particle3D/PU/CCPUParticle3DEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DEmitterManager.cpp \
Particle3D/PU/CCPUParticle3DBoxEmitter.cpp \
Particle3D/PU/CCPUParticle3DBoxEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DCircleEmitter.cpp \
Particle3D/PU/CCPUParticle3DCircleEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DLineEmitter.cpp \
Particle3D/PU/CCPUParticle3DLineEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DMeshSurfaceEmitter.cpp \
Particle3D/PU/CCPUParticle3DMeshSurfaceEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DPointEmitter.cpp \
Particle3D/PU/CCPUParticle3DPointEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DPositionEmitter.cpp \
Particle3D/PU/CCPUParticle3DPositionEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DSlaveEmitter.cpp \
Particle3D/PU/CCPUParticle3DSlaveEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DSphereSurfaceEmitter.cpp \
Particle3D/PU/CCPUParticle3DSphereSurfaceEmitterTranslator.cpp \
Particle3D/PU/CCPUParticle3DVertexEmitter.cpp \
Particle3D/PU/CCPUParticle3DRender.cpp \
Particle3D/PU/CCPUParticle3DBeamRender.cpp \
Particle3D/PU/CCPUParticle3DBillboardChain.cpp \
Particle3D/PU/CCPUParticle3DRibbonTrail.cpp \
Particle3D/PU/CCPUParticle3DRibbonTrailRender.cpp \
Particle3D/PU/CCPUParticle3DDoAffectorEventHandler.cpp \
Particle3D/PU/CCPUParticle3DDoAffectorEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DDoEnableComponentEventHandler.cpp \
Particle3D/PU/CCPUParticle3DDoEnableComponentEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DDoExpireEventHandler.cpp \
Particle3D/PU/CCPUParticle3DDoExpireEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DDoFreezeEventHandler.cpp \
Particle3D/PU/CCPUParticle3DDoFreezeEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DDoPlacementParticleEventHandler.cpp \
Particle3D/PU/CCPUParticle3DDoPlacementParticleEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DDoScaleEventHandler.cpp \
Particle3D/PU/CCPUParticle3DDoScaleEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DDoStopSystemEventHandler.cpp \
Particle3D/PU/CCPUParticle3DDoStopSystemEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DEventHandler.cpp \
Particle3D/PU/CCPUParticle3DEventHandlerManager.cpp \
Particle3D/PU/CCPUParticle3DEventHandlerTranslator.cpp \
Particle3D/PU/CCPUParticle3DObserver.cpp \
Particle3D/PU/CCPUParticle3DObserverManager.cpp \
Particle3D/PU/CCPUParticle3DObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnClearObserver.cpp \
Particle3D/PU/CCPUParticle3DOnClearObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnCollisionObserver.cpp \
Particle3D/PU/CCPUParticle3DOnCollisionObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnCountObserver.cpp \
Particle3D/PU/CCPUParticle3DOnCountObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnEmissionObserver.cpp \
Particle3D/PU/CCPUParticle3DOnEmissionObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnEventFlagObserver.cpp \
Particle3D/PU/CCPUParticle3DOnEventFlagObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnExpireObserver.cpp \
Particle3D/PU/CCPUParticle3DOnExpireObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnPositionObserver.cpp \
Particle3D/PU/CCPUParticle3DOnPositionObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnQuotaObserver.cpp \
Particle3D/PU/CCPUParticle3DOnQuotaObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnRandomObserver.cpp \
Particle3D/PU/CCPUParticle3DOnRandomObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnTimeObserver.cpp \
Particle3D/PU/CCPUParticle3DOnTimeObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DOnVelocityObserver.cpp \
Particle3D/PU/CCPUParticle3DOnVelocityObserverTranslator.cpp \
Particle3D/PU/CCPUParticle3DBehaviour.cpp \
Particle3D/PU/CCPUParticle3DBehaviourManager.cpp \
Particle3D/PU/CCPUParticle3DBehaviourTranslator.cpp \
Particle3D/PU/CCPUParticle3DSlaveBehaviour.cpp \
Particle3D/PU/CCPUParticle3DSlaveBehaviourTranslator.cpp \

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
