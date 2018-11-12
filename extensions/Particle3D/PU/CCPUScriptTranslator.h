/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_PU_SCRIPT_TRANSLATOR_H__
#define __CC_PU_SCRIPT_TRANSLATOR_H__

#include <iostream>

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUScriptCompiler.h"


NS_CC_BEGIN

// Define static tokens
enum eDefineStaticToken
{
    // Generic
    TOKEN_GROUP_MASK,
    TOKEN_ACCELERATION,
    TOKEN_MAX_INCREMENT,
    TOKEN_MIN_INCREMENT,
    TOKEN_ITERATIONS,
    TOKEN_COLOUR_CHANGE,
    TOKEN_INITIAL_COLOUR,
    TOKEN_RANDOM_INITIAL_COLOUR,
    TOKEN_USE_VERTEX_COLOURS,
    TOKEN_USE_OWN_ROTATION,
    TOKEN_MAX_DEVIATION,
    TOKEN_TIME_STEP,
    TOKEN_BOX_WIDTH,
    TOKEN_BOX_HEIGHT,
    TOKEN_BOX_DEPTH,
    TOKEN_VELOCITY,
    TOKEN_SPEED,
    TOKEN_ROTATION_SPEED,
    TOKEN_ROTATION,
    TOKEN_ROTATION_AXIS,
    TOKEN_NORMAL,
    TOKEN_STEP,
    TOKEN_NUMBER_OF_SEGMENTS,
    TOKEN_MAX_ELEMENTS,
    TOKEN_UPDATE_INTERVAL,
    TOKEN_DISTANCE_THRESHOLD,
    TOKEN_MATERIAL,
    TOKEN_MESH_NAME,
    TOKEN_RADIUS,
    TOKEN_ENABLED,
    TOKEN_POSITION,
    TOKEN_KEEP_LOCAL,
    TOKEN_LESS_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_EQUALS,
    TOKEN_VISUAL_PARTICLE,
    TOKEN_EMITTER_PARTICLE,
    TOKEN_AFFECTOR_PARTICLE,
    TOKEN_TECHNIQUE_PARTICLE,
    TOKEN_SYSTEM_PARTICLE,
    TOKEN_POINT,
    TOKEN_VERTEX,
    TOKEN_INCREASE,
    TOKEN_ALIAS,
    TOKEN_USE_ALIAS,
    TOKEN_SINCE_START_SYSTEM,
    
    // Particle System
    TOKEN_SYSTEM,
    TOKEN_PS_ITERATION_INTERVAL,
    TOKEN_PS_NONVIS_UPDATE_TIMEOUT,
    TOKEN_PS_FIXED_TIMEOUT,
    TOKEN_PS_LOD_DISTANCES,
    TOKEN_PS_MAIN_CAMERA_NAME,
    TOKEN_PS_SMOOTH_LOD,
    TOKEN_PS_FAST_FORWARD,
    TOKEN_PS_SCALE,
    TOKEN_PS_SCALE_VELOCITY,
    TOKEN_PS_SCALE_TIME,
    TOKEN_PS_TIGHT_BOUNDING_BOX,
    TOKEN_PS_CATEGORY,
    
    // Particle Technique
    TOKEN_TECHNIQUE,
    TOKEN_TECH_VISUAL_PARTICLE_QUOTA,
    TOKEN_TECH_EMITTED_EMITTER_QUOTA,
    TOKEN_TECH_EMITTED_AFFECTOR_QUOTA,
    TOKEN_TECH_EMITTED_TECHNIQUE_QUOTA,
    TOKEN_TECH_EMITTED_SYSTEM_QUOTA,
    TOKEN_TECH_LOD_INDEX,
    TOKEN_TECH_DEFAULT_PARTICLE_WIDTH,
    TOKEN_TECH_DEFAULT_PARTICLE_HEIGHT,
    TOKEN_TECH_DEFAULT_PARTICLE_DEPTH,
    TOKEN_TECH_SPHASHING_CELL_DIMENSION,
    TOKEN_TECH_SPHASHING_CELL_OVERLAP,
    TOKEN_TECH_SPHASHING_SIZE,
    TOKEN_TECH_SPHASHING_UPDATE_INTERVAL,
    TOKEN_TECH_MAX_VELOCITY,
    
    // Particle Renderer
    TOKEN_RENDERER,
    TOKEN_RENDERER_Q_GROUP,
    TOKEN_RENDERER_SORTING,
    TOKEN_RENDERER_TEXCOORDS_DEFINE,
    TOKEN_RENDERER_TEXCOORDS_ROWS,
    TOKEN_RENDERER_TEXCOORDS_SET,
    TOKEN_RENDERER_TEXCOORDS_COLUMNS,
    TOKEN_RENDERER_USE_SOFT_PARTICLES,
    TOKEN_RENDERER_SOFT_PARTICLES_CONTRAST_POWER,
    TOKEN_RENDERER_SOFT_PARTICLES_SCALE,
    TOKEN_RENDERER_SOFT_PARTICLES_DELTA,
    
    // Particle Emitter
    TOKEN_EMITTER,
    TOKEN_EMITTER_DIRECTION,
    TOKEN_EMITTER_ORIENTATION,
    TOKEN_EMITTER_ORIENTATION_RANGE_START,
    TOKEN_EMITTER_ORIENTATION_RANGE_END,
    TOKEN_EMITTER_START_ORIENTATION_RANGE,
    TOKEN_EMITTER_END_ORIENTATION_RANGE,
    TOKEN_EMITTER_DURATION,
    TOKEN_EMITTER_REPEAT_DELAY,
    TOKEN_EMITTER_EMITS,
    TOKEN_ANGLE,
    TOKEN_EMITTER_EMISSION_RATE,
    TOKEN_TIME_TO_LIVE,
    TOKEN_EMITTER_MASS,
    TOKEN_EMITTER_START_TEXCOORDS,
    TOKEN_EMITTER_END_TEXCOORDS,
    TOKEN_EMITTER_START_TEXCOORDS_RANGE,
    TOKEN_EMITTER_END_TEXCOORDS_RANGE,
    TOKEN_EMITTER_TEXCOORDS,
    TOKEN_EMITTER_START_COLOUR_RANGE,
    TOKEN_EMITTER_END_COLOUR_RANGE,
    TOKEN_EMITTER_COLOUR,
    TOKEN_EMITTER_ALL_PARTICLE_DIM,
    TOKEN_EMITTER_PARTICLE_WIDTH,
    TOKEN_EMITTER_PARTICLE_HEIGHT,
    TOKEN_EMITTER_PARTICLE_DEPTH,
    TOKEN_EMITTER_AUTO_DIRECTION,
    TOKEN_EMITTER_FORCE_EMISSION,
    
    // Particle Affector
    TOKEN_AFFECTOR,
    TOKEN_AFFECTOR_MASS,
    TOKEN_AFFECTOR_EXCLUDE_EMITTER,
    TOKEN_AFFECTOR_SPECIALISATION,
    TOKEN_AFFECTOR_SPEC_DEFAULT,
    TOKEN_AFFECTOR_SPEC_TTL_INCREASE,
    TOKEN_AFFECTOR_SPEC_TTL_DECREASE,
    
    // Particle Observer
    TOKEN_OBSERVER,
    TOKEN_OBSERVE_PARTICLE_TYPE,
    TOKEN_OBSERVE_INTERVAL,
    TOKEN_OBSERVE_UNTIL_EVENT,
    
    // Particle Event Handler
    TOKEN_HANDLER,
    
    // Particle Behaviour
    TOKEN_BEHAVIOUR,
    
    // Extern
    TOKEN_EXTERN,
    TOKEN_EXTERN_DISTANCE_THRESHOLD,
    
    // Dynamic Attribute
    TOKEN_DYN_CONTROL_POINT,
    TOKEN_DYN_MIN,
    TOKEN_DYN_MAX,
    TOKEN_DYN_OSCILLATE_FREQUENCY,
    TOKEN_DYN_OSCILLATE_PHASE,
    TOKEN_DYN_OSCILLATE_BASE,
    TOKEN_DYN_OSCILLATE_AMPLITUDE,
    TOKEN_DYN_OSCILLATE_TYPE,
    TOKEN_DYN_OSCILLATE,
    TOKEN_DYN_RANDOM,
    TOKEN_DYN_CURVED_LINEAR,
    TOKEN_DYN_CURVED_SPLINE,
    TOKEN_DYN_SINE,
    TOKEN_DYN_SQUARE,
    
    // CameraDependency (unused)
    TOKEN_CAMERA_DEPENDENCY,
    
    // BeamRenderer
    TOKEN_BEAMRENDERER_UPDATE_INTERVAL,
    TOKEN_BEAMRENDERER_MAX_ELEMENTS,
    TOKEN_BEAMRENDERER_DEVIATION,
    TOKEN_BEAMRENDERER_NUMBER_OF_SEGMENTS,
    TOKEN_BEAMRENDERER_JUMP,
    TOKEN_BEAMRENDERER_TEXCOORD_DIRECTION,
    TOKEN_BEAMRENDERER_VERTEX_COLOURS,
    TOKEN_BEAMRENDERER_TCD_U,
    TOKEN_BEAMRENDERER_TCD_V,
    
    // BillboardRenderer
    TOKEN_BILLBOARD_TYPE,
    TOKEN_BILLBOARD_ORIGIN,
    TOKEN_BILLBOARD_ROTATION_TYPE,
    TOKEN_BILLBOARD_COMMON_DIRECTION,
    TOKEN_BILLBOARD_COMMON_UP_VECTOR,
    TOKEN_BILLBOARD_POINT_RENDERING,
    TOKEN_BILLBOARD_ACCURATE_FACING,
    TOKEN_BILLBOARD_ORIENTED_COMMON,
    TOKEN_BILLBOARD_ORIENTED_SELF,
    TOKEN_BILLBOARD_ORIENTED_SHAPE,
    TOKEN_BILLBOARD_PERPENDICULAR_COMMON,
    TOKEN_BILLBOARD_PERPENDICULAR_SELF,
    TOKEN_BILLBOARD_TOP_LEFT,
    TOKEN_BILLBOARD_TOP_CENTER,
    TOKEN_BILLBOARD_TOP_RIGHT,
    TOKEN_BILLBOARD_CENTER_LEFT,
    TOKEN_BILLBOARD_CENTER_RIGHT,
    TOKEN_BILLBOARD_CENTER,
    TOKEN_BILLBOARD_BOTTON_LEFT,
    TOKEN_BILLBOARD_BOTTOM_CENTER,
    TOKEN_BILLBOARD_BOTTOM_RIGHT,
    TOKEN_BILLBOARD_TEXCOORD,
    
    // EntityRenderer
    TOKEN_ENT_MESH_NAME,
    TOKEN_ENT_ORIENTATION_TYPE,
    TOKEN_ENT_ORIENTED_SELF,
    TOKEN_ENT_ORIENTED_SELF_MIRRORED,
    TOKEN_ENT_ORIENTED_SHAPE,
    
    // LightRenderer
    TOKEN_LIGHT_TYPE,
    TOKEN_LIGHT_RENDER_QUEUE,
    TOKEN_LIGHT_SPECULAR,
    TOKEN_LIGHT_ATT_RANGE,
    TOKEN_LIGHT_ATT_CONSTANT,
    TOKEN_LIGHT_ATT_LINEAR,
    TOKEN_LIGHT_ATT_QUADRATIC,
    TOKEN_LIGHT_SPOT_INNER,
    TOKEN_LIGHT_SPOT_OUTER,
    TOKEN_LIGHT_FALLOFF,
    TOKEN_LIGHT_POWERSCALE,
    TOKEN_LIGHT_SPOT,
    TOKEN_FLASH_FREQUENCY,
    TOKEN_FLASH_LENGTH,
    TOKEN_FLASH_RANDOM,
    
    // RibbonTrailRenderer
    TOKEN_RIBBONTRAIL_VERTEX_COLOURS,
    TOKEN_RIBBONTRAIL_MAX_ELEMENTS,
    TOKEN_RIBBONTRAIL_LENGTH,
    TOKEN_RIBBONTRAIL_WIDTH,
    TOKEN_RIBBONTRAIL_RANDOM_INITIAL_COLOUR,
    TOKEN_RIBBONTRAIL_INITIAL_COLOUR,
    TOKEN_RIBBONTRAIL_COLOUR_CHANGE,
    
    // BoxEmitter
    TOKEN_EMITTER_BOX_WIDTH,
    TOKEN_EMITTER_BOX_HEIGHT,
    TOKEN_EMITTER_BOX_DEPTH,
    
    // CircleEmitter
    TOKEN_CIRCLE_RADIUS,
    TOKEN_CIRCLE_STEP,
    TOKEN_CIRCLE_ANGLE,
    TOKEN_CIRCLE_RANDOM,
    TOKEN_EMIT_RANDOM,
    TOKEN_CIRCLE_NORMAL,
    
    // LineEmitter
    TOKEN_LINE_EMIT_END,
    TOKEN_LINE_EMIT_MAX_INCREMENT,
    TOKEN_LINE_EMIT_MIN_INCREMENT,
    TOKEN_LINE_EMIT_MAX_DEVIATION,
    
    // MeshSurfaceEmitter
    TOKEN_MESH_SURFACE_NAME,
    TOKEN_MESH_SURFACE_DISTRIBUTION,
    TOKEN_MESH_SURFACE_MESH_SCALE,
    TOKEN_MESH_SURFACE_EDGE,
    TOKEN_MESH_SURFACE_HETEROGENEOUS_1,
    TOKEN_MESH_SURFACE_HETEROGENEOUS_2,
    TOKEN_MESH_SURFACE_HOMOGENEOUS,
    
    // PositionEmitter
    TOKEN_POS_ADD_POSITION,
    TOKEN_POS_RANDOMIZE,
    
    // SlaveEmitter
    TOKEN_MASTER_TECHNIQUE,
    TOKEN_MASTER_EMITTER,
    
    // SphereSurfaceEmitter
    TOKEN_SPHERE_RADIUS,
    
    // VertexEmitter
    TOKEN_VERTEX_STEP,
    TOKEN_VERTEX_SEGMENTS,
    TOKEN_VERTEX_ITERATIONS,
    TOKEN_VERTEX_MESH_NAME,
    
    // AlignAffector
    TOKEN_ALIGN_RESIZE,
    TOKEN_RESIZE,
    
    // BoxCollider
    TOKEN_BOXCOLL_WIDTH,
    TOKEN_BOXCOLL_HEIGHT,
    TOKEN_BOXCOLL_DEPTH,
    
    // BaseCollider
    TOKEN_FRICTION,
    TOKEN_BOUNCYNESS,
    TOKEN_INTERSECTION,
    TOKEN_COLLIDER_FRICTION,
    TOKEN_COLLIDER_BOUNCYNESS,
    TOKEN_COLLIDER_INTERSECTION,
    TOKEN_COLLIDER_COLLISION_TYPE,
    TOKEN_COLLIDER_BOUNCE,
    TOKEN_COLLIDER_FLOW,
    TOKEN_COLLIDER_NONE,
    TOKEN_COLLIDER_INTERSECTION_POINT,
    TOKEN_COLLIDER_INTERSECTION_BOX,
    TOKEN_INNER_COLLISION,
    
    // CollisionAvoidanceAffector
    TOKEN_AVOIDANCE_RADIUS,
    
    // ColourAffector
    TOKEN_TIME_COLOUR,
    TOKEN_COLOUR_TIME_COLOUR,
    TOKEN_COLOUR_OPERATION,
    TOKEN_COLOUR_MULTIPLY,
    TOKEN_COLOUR_SET,
    
    // BaseForceAffector
    TOKEN_FORCE_VECTOR,
    TOKEN_FORCE_APPLICATION,
    TOKEN_FORCE_AFF_VECTOR,
    TOKEN_FORCE_AFF_APPLICATION,
    TOKEN_FORCE_ADD,
    TOKEN_FORCE_AVERAGE,
    
    // ForceFieldAffector
    TOKEN_FORCEFIELD_TYPE,
    TOKEN_REALTIME,
    TOKEN_MATRIX,
    TOKEN_DELTA,
    TOKEN_FORCE,
    TOKEN_OCTAVES,
    TOKEN_FREQUENCY,
    TOKEN_AMPLITUDE,
    TOKEN_PERSISTENCE,
    TOKEN_FORCEFIELDSIZE,
    TOKEN_WORLDSIZE,
    TOKEN_IGNORE_NEGATIVE_X,
    TOKEN_IGNORE_NEGATIVE_Y,
    TOKEN_IGNORE_NEGATIVE_Z,
    TOKEN_MOVEMENT,
    TOKEN_MOVEMENT_FREQUENCY,
    
    // GeometryRotator
    TOKEN_GEOMROT_USE_OWN_ROTATION,
    TOKEN_GEOMROT_ROTATION_SPEED,
    TOKEN_GEOMROT_ROTATION_AXIS,
    
    // GravityAffector
    TOKEN_GRAVITY,
    
    // InterParticleCollider
    TOKEN_ADJUSTMENT,
    TOKEN_COLLISION_RESPONSE,
    TOKEN_IPC_ADJUSTMENT,
    TOKEN_IPC_COLLISION_RESPONSE,
    TOKEN_IPC_AVERAGE_VELOCITY,
    TOKEN_IPC_ANGLE_BASED_VELOCITY,
    
    // JetAffector
    TOKEN_JET_ACCELERATION,
    
    // LineAffector
    TOKEN_END,
    TOKEN_DRIFT,
    TOKEN_LINE_AFF_MAX_DEVIATION,
    TOKEN_LINE_AFF_TIME_STEP,
    TOKEN_LINE_AFF_END,
    TOKEN_LINE_AFF_DRIFT,
    
    // ParticleFollower
    TOKEN_FOLLOW_MAX_DISTANCE,
    TOKEN_FOLLOW_MIN_DISTANCE,
    TOKEN_MAX_DISTANCE,
    TOKEN_MIN_DISTANCE,
    
    // PathFollower
    TOKEN_PATH_POINT,
    
    // PlaneCollider
    TOKEN_PLANECOLL_NORMAL,
    
    // Randomiser
    TOKEN_RND_MAX_DEVIATION_X,
    TOKEN_RND_MAX_DEVIATION_Y,
    TOKEN_RND_MAX_DEVIATION_Z,
    TOKEN_MAX_DEVIATION_X,
    TOKEN_MAX_DEVIATION_Y,
    TOKEN_MAX_DEVIATION_Z,
    TOKEN_RND_TIME_STEP,
    TOKEN_RND_DIRECTION,
    TOKEN_USE_DIRECTION,
    
    // ScaleAffector
    TOKEN_SCALE_XYZ_SCALE,
    TOKEN_SCALE_X_SCALE,
    TOKEN_SCALE_Y_SCALE,
    TOKEN_SCALE_Z_SCALE,
    
    // ScaleVelocityAffector
    TOKEN_SCALE_VELOCITY_SCALE,
    TOKEN_STOP_AT_FLIP,
    
    // SineForceAffector
    TOKEN_SINE_MIN_FREQUENCY,
    TOKEN_SINE_MAX_FREQUENCY,
    TOKEN_MIN_FREQUENCY,
    TOKEN_MAX_FREQUENCY,
    
    // SphereCollider
    TOKEN_SPHERE_COLLIDER_RADIUS,
    
    // TextureAnimator
    TOKEN_TEXANIM_TIME_STEP,
    TOKEN_TEXANIM_TEXCOORDS_START,
    TOKEN_TEXANIM_TEXCOORDS_END,
    TOKEN_START_TEXANIM_TEXCOORDS_RANGE,
    TOKEN_END_TEXANIM_TEXCOORDS_RANGE,
    TOKEN_TEXANIM_ANIMATION_TYPE,
    TOKEN_TEXANIM_START_RANDOM,
    TOKEN_TEXANIM_LOOP,
    TOKEN_TEXANIM_UP_DOWN,
    TOKEN_TEXANIM_RANDOM,
    
    // TextureRotator
    TOKEN_TEXROT_USE_OWN_ROTATION,
    TOKEN_TEXROT_ROTATION_SPEED,
    TOKEN_TEXROT_ROTATION,
    
    // VelocityMatchingAffector
    TOKEN_VELO_MATCHING_RADIUS,
    
    // VortexAffector
    TOKEN_VORTEX_ROTATION_VECTOR,
    TOKEN_VORTEX_ROTATION_SPEED,
    
    // OnCountObserver
    TOKEN_ONCOUNT_THRESHOLD,
    
    // OnEventFlagObserver
    TOKEN_ONEVENT_FLAG,
    
    // OnPositionObserver
    TOKEN_ONPOSITION_X,
    TOKEN_ONPOSITION_Y,
    TOKEN_ONPOSITION_Z,
    
    // OnRandomObserver
    TOKEN_ONRANDOM_THRESHOLD,
    
    // OnTimeObserver
    TOKEN_ONTIME,
    
    // OnVelocityObserver
    TOKEN_ONVELOCITY_THRESHOLD,
    
    // DoAffectorEventHandler
    TOKEN_FORCE_AFFECTOR,
    TOKEN_FORCE_AFFECTOR_PRE_POST,
    
    // DoEnableComponentEventHandler
    TOKEN_DOENABLE_COMPONENT,
    TOKEN_DOENABLE_EMITTER_COMPONENT,
    TOKEN_DOENABLE_AFFECTOR_COMPONENT,
    TOKEN_DOENABLE_TECHNIQUE_COMPONENT,
    TOKEN_DOENABLE_OBSERVER_COMPONENT,
    
    // DoPlacementParticleEventHandler
    TOKEN_DOPLACE_FORCE_EMITTER,
    TOKEN_DOPLACE_NUMBER_OF_PARTICLES,
    TOKEN_INHERIT_POSITION,
    TOKEN_INHERIT_DIRECTION,
    TOKEN_INHERIT_ORIENTATION,
    TOKEN_INHERIT_TIME_TO_LIVE,
    TOKEN_INHERIT_MASS,
    TOKEN_INHERIT_TEXTURE_COORDINATE,
    TOKEN_INHERIT_COLOUR,
    TOKEN_INHERIT_WIDTH,
    TOKEN_INHERIT_HEIGHT,
    TOKEN_INHERIT_DEPTH,
    
    // DoScaleEventHandler
    TOKEN_DOSCALE_FRACTION,
    TOKEN_DOSCALE_TYPE,
    TOKEN_DOSCALE_TIME_TO_LIVE,
    TOKEN_DOSCALE_VELOCITY,
    
    // SlaveBehaviour
    
    // PhysXActorExtern
    TOKEN_PHYSX_SHAPE_TYPE,
    TOKEN_PHYSX_ACTOR_COLLISION_GROUP,
    TOKEN_PHYSX_SHAPE_COLLISION_GROUP,
    TOKEN_PHYSX_GROUP_MASK,
    TOKEN_PHYSX_ANGULAR_VELOCITY,
    TOKEN_PHYSX_ANGULAR_DAMPING,
    TOKEN_PHYSX_MATERIAL_INDEX,
    TOKEN_SHAPE_TYPE,
    TOKEN_ACTOR_COLLISION_GROUP,
    TOKEN_SHAPE_COLLISION_GROUP,
    TOKEN_ANGULAR_VELOCITY,
    TOKEN_ANGULAR_DAMPING,
    TOKEN_MATERIAL_INDEX,
    TOKEN_PHYSX_BOX,
    TOKEN_PHYSX_SPHERE,
    TOKEN_PHYSX_CAPSULE,
    
    // PhysXFluidExtern
    TOKEN_REST_PARTICLE_PER_METER,
    TOKEN_REST_DENSITY,
    TOKEN_KERNEL_RADIUS_MULTIPLIER,
    TOKEN_MOTION_LIMIT_MULTIPLIER,
    TOKEN_COLLISION_DISTANCE_MULTIPLIER,
    TOKEN_PACKET_SIZE_MULTIPLIER,
    TOKEN_STIFFNESS,
    TOKEN_VISCOSITY,
    TOKEN_SURFACE_TENSION,
    TOKEN_DAMPING,
    TOKEN_EXTERNAL_ACCELERATION,
    TOKEN_RESTITUTION_FOR_STATIC_SHAPES,
    TOKEN_DYNAMIC_FRICTION_FOR_STATIC_SHAPES,
    TOKEN_STATIC_FRICTION_FOR_STATIC_SHAPES,
    TOKEN_ATTRACTION_FOR_STATIC_SHAPES,
    TOKEN_RESTITUTION_FOR_DYNAMIC_SHAPES,
    TOKEN_DYNAMIC_FRICTION_FOR_DYNAMIC_SHAPES,
    TOKEN_STATIC_FRICTION_FOR_DYNAMIC_SHAPES,
    TOKEN_ATTRACTION_FOR_DYNAMIC_SHAPES,
    TOKEN_COLLISION_RESPONSE_COEFFICIENT,
    TOKEN_COLLISION_GROUP,
    TOKEN_SIMULATION_METHOD,
    TOKEN_COLLISION_METHOD,
    TOKEN_FLAGS,
    TOKEN_FLAG_VISUALIZATION,
    TOKEN_FLAG_DISABLE_GRAVITY,
    TOKEN_FLAG_COLLISION_TWOWAY,
    TOKEN_FLAG_FLUID_ENABLED,
    TOKEN_FLAG_HARDWARE,
    TOKEN_FLAG_PRIORITY_MODE,
    TOKEN_FLAG_PROJECT_TO_PLANE,
    TOKEN_FLAG_STRICT_COOKING_FORMAT,
    TOKEN_INTERCOLLISION,
    TOKEN_NOINTERCOLLISION,
    TOKEN_MIX_INTERCOLLISION,
    TOKEN_STATIC,
    TOKEN_DYNAMIC,
    
    // SceneDecoratorExtern
    TOKEN_SCENE_MESH_NAME,
    TOKEN_SCENE_MATERIAL_NAME,
    TOKEN_SCENE_SCALE,
    TOKEN_SCENE_POSITION
};

// tokens: Note, that the order must be the same as the enum
extern const std::string token[];

/**script translator*/
class PUScriptTranslator
{
    public:
        PUScriptTranslator();
        virtual ~PUScriptTranslator();
    
    public:
        static bool getFloat(const PUAbstractNode &node, float *result);
        static bool getInt(const PUAbstractNode &node, int *result);
        static bool getUInt(const PUAbstractNode &node, unsigned int *result);
        static bool getBoolean(const PUAbstractNode &node, bool *result);
        static bool getString(const PUAbstractNode &node, std::string *result);
    
    //protected:
    //    virtual void translate(PUScriptCompiler *compiler, const PUConcreteNode &node) = 0;
    
public:
    
    
    // Define validation types
    enum ValidationType
    {
        VAL_REAL,
        VAL_BOOL,
        VAL_UINT,
        VAL_INT,
        VAL_STRING,
        VAL_VECTOR2,
        VAL_VECTOR3,
        VAL_VECTOR4,
        VAL_COLOURVALUE,
        VAL_QUATERNION
    };
    
    
    /** @See ScriptTranslator
     */
    virtual void translate(PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/)
    {
        // No own implementation
    }
    
    /** Only parses a certain child property
     */
    virtual bool translateChildProperty(PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/)
    {
        // No own implementation
        return false;
    }
    
    /** Only parses a certain child objec
     */
    virtual bool translateChildObject(PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/)
    {
        // No own implementation
        return false;
    }
    
    /** Parse Vector2
     */
    bool getVector2(PUAbstractNodeList::const_iterator i,
                    PUAbstractNodeList::const_iterator end,
                    Vec2* result,
                    int maxEntries = 2);
    
    /** Parse Vector3
     */
    bool getVector3(PUAbstractNodeList::const_iterator i,
                    PUAbstractNodeList::const_iterator end,
                    Vec3* result,
                    int maxEntries = 3);
    
    /** Parse Vector4
     */
    bool getVector4(PUAbstractNodeList::const_iterator i,
                    PUAbstractNodeList::const_iterator end,
                    Vec4* result,
                    int maxEntries = 4);
    
    /** Parse Quaternion
     */
    bool getQuaternion(PUAbstractNodeList::const_iterator i,
                       PUAbstractNodeList::const_iterator end,
                       Quaternion* result,
                       int maxEntries = 4);
    
    /** Validate a property.
     */
    bool passValidateProperty(PUScriptCompiler* compiler,
                              PUPropertyAbstractNode* prop,
                              const std::string& token,
                              ValidationType validationType);
    
    /** Validate whether a property has values.
     */
    bool passValidatePropertyNoValues(PUScriptCompiler* compiler,
                                      PUPropertyAbstractNode* prop,
                                      const std::string& token);
    
    /** Validate whether the number of values is correct.
     */
    bool passValidatePropertyNumberOfValues(PUScriptCompiler* compiler,
                                            PUPropertyAbstractNode* prop,
                                            const std::string& token,
                                            unsigned short numberOfValues);
    
    /** Validate whether the number of values is between a range.
     */
    bool passValidatePropertyNumberOfValuesRange(PUScriptCompiler* compiler,
                                                 PUPropertyAbstractNode* prop,
                                                 const std::string& token,
                                                 unsigned short minNumberOfValues,
                                                 unsigned short maxNumberOfValues);
    
    /** Validate whether the value is a correct Real.
     */
    bool passValidatePropertyValidReal(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Validate whether the value is a correct int.
     */
    bool passValidatePropertyValidInt(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Validate whether the value is a correct uint.
     */
    bool passValidatePropertyValidUint(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Validate whether the value is a correct bool.
     */
    bool passValidatePropertyValidBool(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Validate whether the value is a correct Vector2.
     */
    bool passValidatePropertyValidVector2(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Validate whether the value is a correct Vector3.
     */
    bool passValidatePropertyValidVector3(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Validate whether the value is a correct Vector4.
     */
    bool passValidatePropertyValidVector4(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Validate whether the value is a correct Quaternion.
     */
    bool passValidatePropertyValidQuaternion(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);
    
    /** Adds an error to the compiler: An unknown token is read.
     */
    void errorUnexpectedToken(PUScriptCompiler* compiler, PUAbstractNode* node);
    
    /** Adds an error to the compiler: An unknown property is read.
     */
    void errorUnexpectedProperty(PUScriptCompiler* compiler, PUPropertyAbstractNode* prop);

    void processNode(PUScriptCompiler *compiler, PUAbstractNode *node);
    
    virtual bool isParticleSystemTranslator() const { return false; }
};
NS_CC_END

#endif /* defined(__ssaafsdf__CCScriptTranslator__) */
