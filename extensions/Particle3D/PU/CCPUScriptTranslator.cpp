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

#include "CCPUScriptTranslator.h"
#include "extensions/Particle3D/PU/CCPUTranslateManager.h"

NS_CC_BEGIN

const std::string token[1000] =
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

PUScriptTranslator::PUScriptTranslator()
{
}

PUScriptTranslator::~PUScriptTranslator()
{
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

bool PUScriptTranslator::getFloat(const PUAbstractNode &node, float *result)
{
    if(node.type != ANT_ATOM)
        return false;
    
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)(&node);
    int n = sscanf(atom->value.c_str(), "%f", result);
    if(n == 0 || n == EOF)
        return false; // Conversion failed
    
    return true;
}

bool PUScriptTranslator::getInt(const PUAbstractNode &node, int *result)
{
    if(node.type != ANT_ATOM)
        return false;
    
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    int n = sscanf(atom->value.c_str(), "%d", result);
    if(n == 0 || n == EOF)
        return false; // Conversion failed
    
    return true;
}

bool PUScriptTranslator::getUInt(const PUAbstractNode &node, unsigned int *result)
{
    if(node.type != ANT_ATOM)
        return false;
    
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    int n = sscanf(atom->value.c_str(), "%u", result);
    if(n == 0 || n == EOF)
        return false; // Conversion failed
    return true;
}

bool PUScriptTranslator::getBoolean(const PUAbstractNode &node, bool *result)
{
    if(node.type != ANT_ATOM)
        return false;
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    //if(atom->id != 1 && atom->id != 2)
    //    return false;
    
    *result = atom->value == "true" ? true : false;
    return true;
}

bool PUScriptTranslator::getString( const PUAbstractNode &node, std::string *result )
{
    if(node.type != ANT_ATOM)
        return false;
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    *result = atom->value;
    return true;
}

bool PUScriptTranslator::getVector2(PUAbstractNodeList::const_iterator i,
                                  PUAbstractNodeList::const_iterator end,
                                  Vec2* result,
                                  int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->x = v;
                    break;
                case 1:
                    result->y = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xy before end, unless constrained
    return (n >= 2 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::getVector3(PUAbstractNodeList::const_iterator i,
                                  PUAbstractNodeList::const_iterator end,
                                  Vec3* result,
                                  int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->x = v;
                    break;
                case 1:
                    result->y = v;
                    break;
                case 2:
                    result->z = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xyz before end, unless constrained
    return (n >= 3 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::getVector4(PUAbstractNodeList::const_iterator i,
                                  PUAbstractNodeList::const_iterator end,
                                  Vec4* result,
                                  int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->x = v;
                    break;
                case 1:
                    result->y = v;
                    break;
                case 2:
                    result->z = v;
                    break;
                case 3:
                    result->w = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xyz before end, unless constrained
    return (n >= 4 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::getQuaternion(PUAbstractNodeList::const_iterator i,
                                     PUAbstractNodeList::const_iterator end,
                                     Quaternion* result,
                                     int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->w = v;
                    break;
                case 1:
                    result->x = v;
                    break;
                case 2:
                    result->y = v;
                    break;
                case 3:
                    result->z = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xyz before end, unless constrained
    return (n >= 4 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidateProperty(PUScriptCompiler* compiler,
                                            PUPropertyAbstractNode* prop,
                                            const std::string& token2,
                                            ValidationType validationType)
{
    if (!passValidatePropertyNoValues(compiler, prop, token2))
    {
        return false;
    }
    
    bool ret = true;
    switch(validationType)
    {
        case VAL_BOOL:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidBool(compiler, prop);
        }
            break;
        case VAL_COLOURVALUE:
        {
            ret = passValidatePropertyNumberOfValuesRange(compiler, prop, token2, 3, 4);
        }
            break;
        case VAL_INT:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidInt(compiler, prop);
        }
            break;
        case VAL_QUATERNION:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 4) && passValidatePropertyValidQuaternion(compiler, prop);
        }
            break;
        case VAL_REAL:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidReal(compiler, prop);
        }
            break;
        case VAL_STRING:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1);
        }
            break;
        case VAL_UINT:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidUint(compiler, prop);
        }
            break;
        case VAL_VECTOR2:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 2) && passValidatePropertyValidVector2(compiler, prop);
        }
            break;
        case VAL_VECTOR3:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 3) && passValidatePropertyValidVector3(compiler, prop);
        }
            break;
        case VAL_VECTOR4:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 4) && passValidatePropertyValidVector4(compiler, prop);
        }
            break;
    }
    
    return ret;
}

//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyNoValues(PUScriptCompiler* /*compiler*/,
                                                    PUPropertyAbstractNode* prop,
                                                    const std::string& /*token2*/)
{
    if(prop->values.empty())
    {
//        compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line, "PU Compiler: No values found for " + token2 + ".");
        return false;
    }
    return true;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyNumberOfValues(PUScriptCompiler* /*compiler*/,
                                                          PUPropertyAbstractNode* prop,
                                                          const std::string& /*token2*/,
                                                          unsigned short numberOfValues)
{
    if(prop->values.size() > numberOfValues)
    {
        return false;
    }
    return true;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyNumberOfValuesRange(PUScriptCompiler* /*compiler*/,
                                                               PUPropertyAbstractNode* prop,
                                                               const std::string& /*token2*/,
                                                               unsigned short minNumberOfValues,
                                                               unsigned short maxNumberOfValues)
{
    if(prop->values.size() < minNumberOfValues || prop->values.size() > maxNumberOfValues)
    {
        return false;
    }
    return true;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidReal(PUScriptCompiler* /*compiler*/,
                                                     PUPropertyAbstractNode* prop)
{
    float val = 0.0f;
    if(getFloat(*(prop->values.front()), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Real");
    return false;
}

//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidInt(PUScriptCompiler* /*compiler*/,
                                                    PUPropertyAbstractNode* prop)
{
    int val = 0;
    if(getInt(*prop->values.front(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid int");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidUint(PUScriptCompiler* /*compiler*/,
                                                     PUPropertyAbstractNode* prop)
{
    unsigned int val = 0;
    if(getUInt(*prop->values.front(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid uint");
    return false;
}

//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidBool(PUScriptCompiler* /*compiler*/,
                                                     PUPropertyAbstractNode* prop)
{
    bool val;
    if(getBoolean(*prop->values.front(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid bool");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidVector2(PUScriptCompiler* /*compiler*/,
                                                        PUPropertyAbstractNode* prop)
{
    Vec2 val;
    if(getVector2(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Vector2");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidVector3(PUScriptCompiler* /*compiler*/,
                                                        PUPropertyAbstractNode* prop)
{
    Vec3 val;
    if(getVector3(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Vector3");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidVector4(PUScriptCompiler* /*compiler*/,
                                                        PUPropertyAbstractNode* prop)
{
    Vec4 val;
    if(getVector4(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Vector4");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidQuaternion(PUScriptCompiler* /*compiler*/,
                                                           PUPropertyAbstractNode* prop)
{
    Quaternion val;
    if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Quaternion");
    return false;
}
//-------------------------------------------------------------------------
void PUScriptTranslator::errorUnexpectedToken(PUScriptCompiler* /*compiler*/,
                                            PUAbstractNode* /*token2*/)
{
//    CCLOGERROR("PU Compiler: token2 is not recognized tokenFile:%s tokenLine:%s",)
//    printf()
//    compiler->addError(ScriptCompiler::CE_UNEXPECTEDTOKEN, token.getPointer()->file, token.getPointer()->line, 
//                       );
}
//-------------------------------------------------------------------------
void PUScriptTranslator::errorUnexpectedProperty(PUScriptCompiler* /*compiler*/,
                                               PUPropertyAbstractNode* /*prop*/)
{
//    compiler->addError(ScriptCompiler::CE_UNEXPECTEDTOKEN, prop->file, prop->line, 
//                       "PU Compiler: token \"" + prop->name + "\" is not recognized");
}

void PUScriptTranslator::processNode( PUScriptCompiler *compiler, PUAbstractNode *node )
{
    if(node->type != ANT_OBJECT)
        return;

    // Abstract objects are completely skipped
    if((reinterpret_cast<PUObjectAbstractNode*>(node))->abstract)
        return;

    // Retrieve the translator to use
    PUScriptTranslator *translator = PUTranslateManager::Instance()->getTranslator(node);

    if(translator)
        translator->translate(compiler, node);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

NS_CC_END
