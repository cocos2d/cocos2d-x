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

// Static tokens: Note, that the order must be the same as the enum
static const std::string token[1000] =
{
    // Generic
    "group_mask",
    "acceleration",
    "max_increment",
    "min_increment",
    "number_of_iterations",
    "colour_change",
    "initial_colour",
    "random_initial_colour",
    "use_vertex_colours",
    "use_own_rotation",
    "max_deviation",
    "time_step",
    "box_width",
    "box_height",
    "box_depth",
    "velocity",
    "speed",
    "rotation_speed",
    "rotation",
    "rotation_axis",
    "normal",
    "step",
    "number_of_segments",
    "max_elements",
    "update_interval",
    "distance_threshold",
    "material",
    "mesh_name",
    "radius",
    "enabled",
    "position",
    "keep_local",
    "less_than",
    "greater_than",
    "equals",
    "visual_particle",
    "emitter_particle",
    "affector_particle",
    "technique_particle",
    "system_particle",
    "point",
    "vertex",
    "increase",
    "alias",
    "use_alias",
    "since_start_system",
    
    // Particle System
    "system",
    "iteration_interval",
    "nonvisible_update_timeout",
    "fixed_timeout",
    "lod_distances",
    "main_camera_name",
    "smooth_lod",
    "fast_forward",
    "scale",
    "scale_velocity",
    "scale_time",
    "tight_bounding_box",
    "category",
    
    // Particle Technique
    "technique",
    "visual_particle_quota",
    "emitted_emitter_quota",
    "emitted_affector_quota",
    "emitted_technique_quota",
    "emitted_system_quota",
    "lod_index",
    "default_particle_width",
    "default_particle_height",
    "default_particle_depth",
    "spatial_hashing_cell_dimension",
    "spatial_hashing_cell_overlap",
    "spatial_hashtable_size",
    "spatial_hashing_update_interval",
    "max_velocity",
    
    // Particle Renderer
    "renderer",
    "render_queue_group",
    "sorting",
    "texture_coords_define",
    "texture_coords_rows",
    "texture_coords_set",
    "texture_coords_columns",
    "use_soft_particles",
    "soft_particles_contrast_power",
    "soft_particles_scale",
    "soft_particles_delta",
    
    // Particle Emitter
    "emitter",
    "direction",
    "orientation",
    "range_start_orientation",
    "range_end_orientation",
    "start_orientation_range",
    "end_orientation_range",
    "duration",
    "repeat_delay",
    "emits",
    "angle",
    "emission_rate",
    "time_to_live",
    "mass",
    "start_texture_coords",
    "end_texture_coords",
    "start_texture_coords_range",
    "end_texture_coords_range",
    "texture_coords",
    "start_colour_range",
    "end_colour_range",
    "colour",
    "all_particle_dimensions",
    "particle_width",
    "particle_height",
    "particle_depth",
    "auto_direction",
    "force_emission",
    
    // Particle Affector
    "affector",
    "mass_affector",
    "exclude_emitter",
    "affect_specialisation",
    "special_default",
    "special_ttl_increase",
    "special_ttl_decrease",
    
    // Particle Observer
    "observer",
    "observe_particle_type",
    "observe_interval",
    "observe_until_event",
    
    // Particle Event Handler
    "handler",
    
    // Particle Behaviour
    "behaviour",
    
    // Extern
    "extern",
    "attachable_distance_threshold",
    
    // Dynamic Attribute
    "control_point",
    "min",
    "max",
    "oscillate_frequency",
    "oscillate_phase",
    "oscillate_base",
    "oscillate_amplitude",
    "oscillate_type",
    "dyn_oscillate",
    "dyn_random",
    "dyn_curved_linear",
    "dyn_curved_spline",
    "sine",
    "square",
    
    // CameraDependency (unused)
    "camera_dependency",
    
    // ------------------------- Renderers -------------------------
    // BeamRenderer
    "beam_update_interval",
    "beam_max_elements",
    "beam_deviation",
    "beam_number_segments",
    "beam_jump_segments",
    "beam_texcoord_direction",
    "beam_vertex_colours",
    "tcd_u",
    "tcd_v",
    
    // BillboardRenderer
    "billboard_type",
    "billboard_origin",
    "billboard_rotation_type",
    "common_direction",
    "common_up_vector",
    "point_rendering",
    "accurate_facing",
    "oriented_common",
    "oriented_self",
    "oriented_shape",
    "perpendicular_common",
    "perpendicular_self",
    "top_left",
    "top_center",
    "top_right",
    "center_left",
    "center_right",
    "center",
    "bottom_left",
    "bottom_center",
    "bottom_right",
    "texcoord",
    
    // BoxRenderer: No properties itself
    
    // EntityRenderer
    "entity_renderer_mesh_name",
    "entity_orientation_type",
    "ent_oriented_self",
    "ent_oriented_self_mirrored",
    "ent_oriented_shape",
    
    // LightRenderer
    "light_renderer_light_type",
    "light_renderer_queue_group",
    "light_renderer_specular",
    "light_renderer_att_range",
    "light_renderer_att_constant",
    "light_renderer_att_linear",
    "light_renderer_att_quadratic",
    "light_renderer_spot_inner",
    "light_renderer_spot_outer",
    "light_renderer_falloff",
    "light_renderer_powerscale",
    "spot",
    "flash_frequency",
    "flash_length",
    "flash_random",
    
    // RibbonTrailRenderer
    "ribbontrail_vertex_colours",
    "ribbontrail_max_elements",
    "ribbontrail_length",
    "ribbontrail_width",
    "ribbontrail_random_initial_colour",
    "ribbontrail_initial_colour",
    "ribbontrail_colour_change",
    
    // SphereRenderer: No properties itself
    
    // ------------------------- Emitters -------------------------
    // BoxEmitter
    "box_em_width",
    "box_em_height",
    "box_em_depth",
    
    // CircleEmitter
    "circle_em_radius",
    "circle_em_step",
    "circle_em_angle",
    "circle_em_random",
    "emit_random",
    "circle_em_normal",
    
    // LineEmitter
    "line_em_end",
    "line_em_max_increment",
    "line_em_min_increment",
    "line_em_max_deviation",
    
    // MeshSurfaceEmitter
    "mesh_surface_mesh_name",
    "mesh_surface_distribution",
    "mesh_surface_scale",
    "edge",
    "heterogeneous_1",
    "heterogeneous_2",
    "homogeneous",
    
    // PointEmitter: No properties itself
    
    // PositionEmitter
    "add_position",
    "random_position",
    
    // SlaveEmitter
    "master_technique_name",
    "master_emitter_name",
    
    // SphereSurfaceEmitter
    "sphere_surface_em_radius",
    
    // VertexEmitter
    "vertex_em_step",
    "vertex_em_segments",
    "vertex_em_iterations",
    "vertex_em_mesh_name",
    
    // ------------------------- Affectors -------------------------
    // AlignAffector
    "align_aff_resize",
    "resize",
    
    // BoxCollider
    "box_collider_width",
    "box_collider_height",
    "box_collider_depth",
    
    // BaseCollider
    "friction",
    "bouncyness",
    "intersection",
    "collision_friction",
    "collision_bouncyness",
    "collision_intersection",
    "collision_type",
    "bounce",
    "flow",
    "none",
    "point",
    "box",
    "inner_collision",
    
    // CollisionAvoidanceAffector
    "avoidance_radius",
    
    // ColourAffector
    "time_colour",
    "colour_aff_time_colour",
    "colour_operation",
    "multiply",
    "set",
    
    // FlockCenteringAffector: No properties itself
    
    // BaseForceAffector
    "force_vector",
    "force_application",
    "force_aff_vector",
    "force_aff_application",
    "add",
    "average",
    
    // ForceFieldAffector
    "forcefield_type",
    "realtime",
    "matrix",
    "delta",
    "force",
    "octaves",
    "frequency",
    "amplitude",
    "persistence",
    "forcefield_size",
    "worldsize",
    "ignore_negative_x",
    "ignore_negative_y",
    "ignore_negative_z",
    "movement",
    "movement_frequency",
    
    // GeometryRotator
    "geom_rot_use_own_rotation",
    "geom_rot_rotation_speed",
    "geom_rot_axis",
    
    // GravityAffector
    "gravity",
    
    // InterParticleCollider
    "adjustment",
    "collision_response",
    "ip_adjustment",
    "ip_collision_response",
    "average_velocity",
    "angle_based_velocity",
    
    // JetAffector
    "jet_aff_accel",
    
    // LineAffector
    "end",
    "drift",
    "line_aff_max_deviation",
    "line_aff_time_step",
    "line_aff_end",
    "line_aff_drift",
    
    // LinearForceAffector: No properties itself
    
    // ParticleFollower
    "follower_max_distance",
    "follower_min_distance",
    "max_distance",
    "min_distance",
    
    // PathFollower
    "path_follower_point",
    
    // PlaneCollider
    "plane_collider_normal",
    
    // Randomiser
    "rand_aff_max_deviation_x",
    "rand_aff_max_deviation_y",
    "rand_aff_max_deviation_z",
    "max_deviation_x",
    "max_deviation_y",
    "max_deviation_z",
    "rand_aff_time_step",
    "rand_aff_direction",
    "use_direction",
    
    // ScaleAffector
    "xyz_scale",
    "x_scale",
    "y_scale",
    "z_scale",
    
    // ScaleVelocityAffector
    "velocity_scale",
    "stop_at_flip",
    
    // SineForceAffector
    "sinef_aff_frequency_min",
    "sinef_aff_frequency_max",
    "min_frequency",
    "max_frequency",
    
    // SphereCollider
    "sphere_collider_radius",
    
    // TextureAnimator
    "time_step_animation",
    "texture_coords_start",
    "texture_coords_end",
    "start_texture_coords_range",
    "end_texture_coords_range",
    "texture_animation_type",
    "texture_start_random",
    "loop",
    "up_down",
    "random",
    
    // TextureRotator
    "tex_rot_use_own_rotation",
    "tex_rot_speed",
    "tex_rot_rotation",
    
    // VelocityMatchingAffector
    "velocity_matching_radius",
    
    // VortexAffector
    "vortex_aff_vector",
    "vortex_aff_speed",
    
    // ------------------------- Observers -------------------------
    // OnClearObserver: No properties itself
    
    // OnCollisionObserver: No properties itself
    
    // OnCountObserver
    "count_threshold",
    
    // OnEmissionObserver: No properties itself
    
    // OnEventFlagObserver
    "event_flag",
    
    // OnExpireObserver: No properties itself
    
    // OnPositionObserver
    "position_x",
    "position_y",
    "position_z",
    
    // OnQuotaObserver: No properties itself
    
    // OnRandomObserver
    "random_threshold",
    
    // OnTimeObserver
    "on_time",
    
    // OnVelocityObserver
    "velocity_threshold",
    
    // ------------------------- Event Handlers ------------------------- 
    // DoAffectorEventHandler
    "force_affector",
    "pre_post",
    
    // DoEnableComponentEventHandler
    "enable_component",
    "emitter_component",
    "affector_component",
    "technique_component",
    "observer_component",
    
    // DoExpireEventHandler: No properties itself
    
    // DoFreezeEventHandler: No properties itself
    
    // DoPlacementParticleEventHandler
    "force_emitter",
    "number_of_particles",
    "inherit_position",
    "inherit_direction",
    "inherit_orientation",
    "inherit_time_to_live",
    "inherit_mass",
    "inherit_texture_coord",
    "inherit_colour",
    "inherit_width",
    "inherit_height",
    "inherit_depth",
    
    // DoScaleEventHandler
    "scale_fraction",
    "scale_type",
    "st_time_to_live",
    "st_velocity",
    
    // DoStopSystemEventHandler: No properties itself
    
    // ------------------------- Behaviours ------------------------- 
    // SlaveBehaviour: No properties itself
    
    // ------------------------- Externs ------------------------- 
    // BoxColliderExtern: Defined in BoxCollider
    
    // GravityExtern: Defined in GravityAffector
    
    // PhysXActorExtern
    "physx_shape",
    "physx_actor_group",
    "physx_shape_group",
    "physx_group_mask",
    "physx_angular_velocity",
    "physx_angular_damping",
    "physx_material_index",
    "shape",
    "actor_group",
    "shape_group",
    "angular_velocity",
    "angular_damping",
    "material_index",
    "Box",
    "Sphere",
    "Capsule",
    
    // PhysXFluidExtern
    "rest_particles_per_meter",
    "rest_density",
    "kernel_radius_multiplier",
    "motion_limit_multiplier",
    "collision_distance_multiplier",
    "packet_size_multiplier",
    "stiffness",
    "viscosity",
    "surface_tension",
    "damping",
    "external_acceleration",
    "restitution_for_static_shapes",
    "dynamic_friction_for_static_shapes",
    "static_friction_for_static_shapes",
    "attraction_for_static_shapes",
    "restitution_for_dynamic_shapes",
    "dynamic_friction_for_dynamic_shapes",
    "static_friction_for_dynamic_shapes",
    "attraction_for_dynamic_shapes",
    "collision_response_coefficient",
    "collision_group",
    "simulation_method",
    "collision_method",
    "flags",
    "visualization", 
    "disable_gravity", 
    "collision_twoway",
    "fluid_enabled",
    "hardware",
    "priority_mode",
    "project_to_plane",
    "strict_cooking_format",
    "intercollision",
    "no_intercollision",
    "mix_intercollision",
    "static",
    "dynamic",
    
    // SceneDecoratorExtern
    "scene_mesh_name",
    "scene_material_name",
    "scene_node_scale",
    "scene_node_position",
    
    // SphereColliderExtern: Defined in SphereCollider
    
    // VortexExtern: Defined in VortexAffector
};


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
